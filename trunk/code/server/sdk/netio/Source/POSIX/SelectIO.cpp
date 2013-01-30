#include "StdAfx.h"
#include "core.h"
#include "PacketDefineHead.h"
#include "GameNet.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#define LINGER linger
#include <netinet/in.h>
#include <netinet/tcp_timer.h>
#include <arpa/inet.h>
#include <errno.h>
#include "SelectIO.h"


//////////////////////////////////////////////////////////////////////////
//
CSelectIO::CSelectIO(CGameNet* pGameNet)
{
//	SetDefLessFunc(m_IOKeyMap);

	m_StarFlag		= FALSE;
	m_pGameNet		= pGameNet;
	m_nListenSocket	= INVALID_SOCKET;
	m_nConnectMax	= 0;
	m_IOKeyTable	= NULL;
	m_IOKeyTableIndex = 0;
	m_nRecvBuffSize	= 0;
	m_nSendBuffSize	= 0;
	m_nWorkSocketCount = 0;
	m_nPacketPoolSize = 0;
}

CSelectIO::~CSelectIO()
{
	m_StarFlag = FALSE;
//	m_IOKeyMap.RemoveAll();
	if(m_IOKeyTable)
		Plat_Free(m_IOKeyTable);
}

// nPort		: 监听的端口
//nPacketPoolSize:接受消息的缓冲区大小
// nConnectMax	: 连接的最大数
// nRecvBuffSize: 接受缓冲的大小
// nSendBuffSize: 发送缓冲区大小
// nTimeout		: 发送超时
BOOL CSelectIO::Begin(int nPort,int nPacketPoolSize,int nConnecMax,int nRecvBuffSize,int nSendBuffSize,int nTimeout)
{
	//初始化Net
	if (!NetWorkStart())
	{
		printf("wsastarup初始化失败！\n");
		return FALSE;
	}

	Assert(nConnecMax);
	if(!nConnecMax)
		return FALSE;

	m_nConnectMax		= nConnecMax;
	m_nRecvBuffSize		= nRecvBuffSize;
	m_nSendBuffSize		= nSendBuffSize;
	m_nPacketPoolSize	= nPacketPoolSize;

	//分派 HashTable
	m_IOKeyMap.Purge(nConnecMax);

	//预分配空间
	m_IOKeyTable = (IOKEY*)Plat_Alloc(sizeof(IOKEY)*nConnecMax);
	for(int i=0;i<nConnecMax;i++)
	{
		new(&m_IOKeyTable[i]) IOKEY;
		m_IOKeyTable[i].Construct(nRecvBuffSize,nSendBuffSize,nTimeout);
	}

	m_StarFlag = TRUE;

	if(nPort)
	{
		m_nListenSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (m_nListenSocket == INVALID_SOCKET)
		{
			printf("failed to socket in selectio begin(), errno = %d, %s\n", errno, strerror(errno));
			return INVALID_SOCKET;
		}
		//设置监听套接字为非阻塞
		if (!SetNonblock(m_nListenSocket))
		{
			printf(" failed to SetNonblock,sockfd = %d\n", m_nListenSocket);
			return FALSE;
		}

		struct sockaddr_in localAddr;
		ZeroMemory (&localAddr, sizeof (localAddr));
		localAddr.sin_family = AF_INET;
		localAddr.sin_port = htons (nPort);
		localAddr.sin_addr.s_addr = htonl(INADDR_ANY);

		int iState = bind (m_nListenSocket, (struct sockaddr *) & localAddr, sizeof (localAddr));
		if (iState < 0)
		{
#if (!defined(_DEBUG)) && defined(WIN32)
			printf( "Socket Bind Failed\n");
			if (WSAGetLastError () == WSAEADDRINUSE)
				printf( "The port number may already be in use.\n");
#endif
			return FALSE;
		}

		iState = listen(m_nListenSocket, LISTEN_BACKLOG);
		if (iState < 0) //failed to listen
		{
			printf("failed to listen! port = %d ,%s\n", nPort,strerror(errno));
			return FALSE;
		}
		m_nWorkSocketCount++;

	}
	pthread_t RecvThrid;
	pthread_create(&RecvThrid, NULL, RecvThread, this);

	pthread_t SendThrid;
	pthread_create(&SendThrid, NULL, SendThread, this);

	pthread_t CloseThrid;
	pthread_create(&CloseThrid, NULL, CloseThread, this);

//    printf("CSelectIO::Begin done\n");
	return TRUE;
}

void CSelectIO::End()
{
	Log("Client End");
	m_StarFlag = FALSE;
	for(int i=0;i<m_nConnectMax;i++)
	{
		if(m_IOKeyTable[i].m_bFree)
			continue;

		close(m_IOKeyTable[i].m_sock);
	}
}

IOKEY*	CSelectIO::GetFreeKey()
{
	for(int i=0;i<m_nConnectMax;i++)
	{
		if(m_IOKeyTable[i].m_bFree)
		{
			m_IOKeyTable[i].m_bFree = false;
			m_nWorkSocketCount++;
			return &m_IOKeyTable[i];
		}
	}
	return NULL;
}

void CSelectIO::SetKey( SOCKET sock,IOKEY* pKey )
{
	m_IOKeyMap.Insert(sock,pKey);

}

IOKEY* CSelectIO::GetKey( SOCKET sock)
{
	return (IOKEY*)m_IOKeyMap.Find(sock);
}

void CSelectIO::RemoveKey(SOCKET sock)
{
	m_IOKeyMap.Remove(sock);

}


//使用accept()接受所有的网络连接
void CSelectIO::AcceptAllConnections()
{
//printf("CSelectIO::AcceptAllConnections()\n");
	SOCKET sockfd = INVALID_SOCKET;
	do
	{
		sockaddr client_addr;
		socklen_t nAddrLen = sizeof(client_addr);
		sockfd = accept(m_nListenSocket,&client_addr,&nAddrLen);
//printf("CSelectIO::AcceptAllConnections accept sockfd=%d\n",sockfd);
		if(sockfd != INVALID_SOCKET)
		{
			IOKEY* pIOKey = GetFreeKey();//new IOKEY;
			if(pIOKey)
			{
				pIOKey->m_sock = sockfd;

				int nSendSize = 100*1024*1024;		//系统发送缓冲区100M
				int nRecvSize = 100*1024*1024;		//系统接收缓冲区100M
				int dtime = 30;						//使用30秒超时优雅关闭设置，避免偶尔发送过快导致的10054错误把socket关闭 by zhao
				int	idle = 5;						// 开始首次KeepAlive探测前的TCP空闭时间
				int intv = 60;						// 两次KeepAlive探测间的时间间隔1分钟
				int cnt = 3;

				int ret = SetSockOpt(sockfd, nRecvSize, nSendSize, dtime, idle, intv, cnt);
//printf("CSelectIO::SetSockOpt ret=%d\n",ret);
				if(ret != 0)
				{
					printf(" +-Connect Server Error %d\n", WSAGetLastError());
					closesocket(sockfd);
					break;
				}

				SetKey(sockfd,pIOKey);
			}
			else
			{
				close(sockfd);
				break;
			}


			sockaddr_in* pRemote = (sockaddr_in*)&client_addr;
			char* szIP;
			szIP = inet_ntoa(pRemote->sin_addr);
			pIOKey->SetIP(szIP);
			m_pGameNet->Accept(sockfd);
			Log("Accept Socket %d %s\n",sockfd,szIP);
		}
	}
	while(sockfd != INVALID_SOCKET);
}

SOCKET	CSelectIO::Connect( const char *szIP,ULONG lPort)
{
	SOCKET sock = socket(AF_INET,SOCK_STREAM,0);

	/*LINGER lingerStruct;
	lingerStruct.l_onoff = 1;
	lingerStruct.l_linger = 0;
	setsockopt( sock, SOL_SOCKET, SO_LINGER,(char *)&lingerStruct,	sizeof(lingerStruct) );*/

	int nSendSize = 100*1024*1024;		//系统发送缓冲区100M
 	int nRecvSize = 100*1024*1024;		//系统接收缓冲区100M
	int dtime = 30;						//使用30秒超时优雅关闭设置，避免偶尔发送过快导致的10054错误把socket关闭 by zhao
	int	idle = 5;						// 开始首次KeepAlive探测前的TCP空闭时间
	int intv = 60;						// 两次KeepAlive探测间的时间间隔1分钟
	int cnt = 3;

//*
	int optname;
	socklen_t optlen;
	optlen = sizeof(optname);
	getsockopt(sock,SOL_SOCKET,SO_RCVBUF,(char *)&optname,&optlen);
//	printf("getsockopt() %u \n",optname);
//*/

	int ret = SetSockOpt(sock, nRecvSize, nSendSize, dtime, idle, intv, cnt);
	if(ret != 0)
	{
		printf(" +-Connect Server Error %d\n", WSAGetLastError());
		closesocket(sock);
		return INVALID_SOCKET;
	}

	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_port = htons(lPort);
	add.sin_addr.s_addr = inet_addr(szIP);

	if (connect(sock,(struct sockaddr*)&add,sizeof(sockaddr)) < 0)
	{
		printf(" +-Connect Server Error %d\n",WSAGetLastError());
		closesocket(sock);
		return INVALID_SOCKET;
	}

	// 设置非阻塞模式
	if (!SetNonblock(sock))
	{
		printf(" +-Set FIOBiO Error\n");
		closesocket(sock);
		return INVALID_SOCKET;
	}

	IOKEY* pIOKey = GetFreeKey();//new IOKEY;
	if(pIOKey)
	{
		pIOKey->m_sock = sock;
		pIOKey->SetIP(szIP);
		SetKey(sock,pIOKey);
		Log("Connect socket = %d\n",sock);
	}
	else
	{
		closesocket(sock);
		return INVALID_SOCKET;
	}

	m_pGameNet->Accept(sock);

	return sock;
}

int CSelectIO::Recv( SOCKET sock,char *buf,int nSize )
{
//	Warning("recv buf size %d\n",nSize);
//printf("CSelectIO::Recv recv buf size %d\n",nSize);

/*
if(nSize>0)
{
	for(int i=0; i<nSize; i++)
	{
		printf("%02X ",buf[i]);
	}
	printf("\n");
	for(int i=0; i<nSize; i++)
	{
		printf("%c ",buf[i]);
	}
	printf("\n");
}*/
	return m_pGameNet->Recv(sock,buf,nSize);
}


// return
// 0 ：发送不成功
// -1：网络中断
//int CSelectIO::Send( SOCKET sock,PACKET_COMMAND* pPacket )
int CSelectIO::Send( SOCKET sock, char *szBuf, int nSize )
{
	if(!szBuf)
		return -1;

	IOKEY* IO = GetKey(sock);
//	Assert(IO);		//  Abort (core dumped)         li9chuan  2011-3-4
	if(!IO)
	{
		Break(sock);
//		printf("Break %d\n",sock);
		return -1;
	}

	if(IO->m_bClosed)
		return -1;


//	int flag = IO->m_WriteBufferQueue.Write((char*)pPacket->pParam,pPacket->Size());
    int flag = IO->m_WriteBufferQueue.Write( szBuf, nSize );
	m_Event.Event();
	return flag;
}

void CSelectIO::Break( SOCKET sock )
{
	IOKEY* IO = GetKey(sock);
	if(IO)
	{
		//Log("Set IOKEY Close Break socket %d\n",sock);
		IO->SetClosed();
	}
}

char* CSelectIO::IP(SOCKET sock)
{
	IOKEY* pKey = GetKey(sock);
	if(pKey)
		return pKey->m_IP;
	return "";
}

BOOL CSelectIO::Close(SOCKET sock) //仅用于工作线程关闭一个socket, 主逻辑不可调用此函数
{
	Log("SelectID Close sock:%d",sock);
	m_pGameNet->Break(sock);
	Log("m_pGameNet Break()");

	IOKEY* pKey = GetKey(sock);
	if(!pKey)
		return FALSE;
	RemoveKey(sock);
	close(sock);
	pKey->Release();
//printf("close socket =%d \n",sock);
	Log("close socket =%d \n",sock);
	m_nWorkSocketCount--;
	return TRUE;
}


int CSelectIO::SetSockOpt(SOCKET sock, int nRecv, int nSend, int dtime, int idle, int intv, int ctn)
{
	//设置系统缓冲区
 	int ret = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (const char *)&nRecv, sizeof(int));
	if(ret != 0)
		 return ret;
 	ret = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (const char *)&nSend, sizeof(int));
	if(ret != 0)
		return ret;

	//优雅关闭设置
	struct linger so_linger;
	so_linger.l_onoff	= TRUE;
	so_linger.l_linger	= dtime;
	ret =  setsockopt(sock, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(struct linger));
	if(ret != 0)
		return ret;

	//tcp心跳
	BOOL bKeepAlive = TRUE;
	ret = ::setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&bKeepAlive, sizeof(bKeepAlive));
	if (ret < 0)
		return ret;

	/*
	// 设置心跳存活参数
	//send keepalive packet after 5 seconds idle
	ret = setsockopt(sock, SOL_TCP, TCPTV_KEEP_IDLE, &idle, sizeof(idle));
	if (ret < 0)
		return ret;

	//retry after 60 seconds failed keepalive packet
	ret = setsockopt(sock, SOL_TCP, TCPTV_KEEPINTVL, &intv, sizeof(intv));
	if (ret < 0)
		return ret;

	//failed for 3 times
	ret = setsockopt(sock, SOL_TCP, TCPTV_KEEPCNT, &ctn, sizeof(ctn));
	if (ret < 0)
		return ret;
	*/

	return ret;
}

//接受线程
void* CSelectIO::RecvThread(void *Param)
{
#if (!defined(_DEBUG)) && defined(WIN32)
	__try
#endif
	{
		if(!Param)
			return 0;

		CSelectIO*	pThis= (CSelectIO*)Param;
		int			ret	 = 0;
		timeval		t	 = {1,0};
		//timeval		t	 = {0,1000};
		fd_set		fdread;

		while( pThis->m_StarFlag )
		{
			if(pThis->m_nWorkSocketCount==0)
			{
				Sleep(100);
				continue;
			}

			FD_ZERO(&fdread);
			int nfds = 0;

			//添加监听socket的事件
			if(pThis->m_nListenSocket != INVALID_SOCKET)
			{
				FD_SET( pThis->m_nListenSocket, &fdread );
				nfds = pThis->m_nListenSocket;
			}

			for(int j=0;j<pThis->m_nConnectMax;j++)
			{
				if(pThis->m_IOKeyTable[j].m_bFree)
					continue;

				if( pThis->m_IOKeyTable[j].m_bClosed )
				{
					//Log("IOKEY is bClosed,Close(),sock:%d,line:%d",pThis->m_IOKeyTable[j].m_sock,__LINE__);
					pThis->Break(pThis->m_IOKeyTable[j].m_sock);
					continue;
				}
//printf("CSelectIO::FD_SET pThis->m_IOKeyTable[j].m_sock=%d\n",pThis->m_IOKeyTable[j].m_sock);
				FD_SET( pThis->m_IOKeyTable[j].m_sock,&fdread );
				if( nfds < pThis->m_IOKeyTable[j].m_sock )
				{
					nfds = pThis->m_IOKeyTable[j].m_sock;
				}
			}
//printf("CSelectIO::RecvThread nfds = %d\n",nfds);
			//ret = select( 0,&fdread,NULL,NULL,&t);		//		2011-1-5		li9chuan
			ret = select( nfds+1,&fdread,NULL,NULL,&t);

//printf("CSelectIO::RecvThread ret=%d\n",ret);

			if (ret < 0)
			{
				//Warning("select error %d\n",WSAGetLastError());
				printf("select error %d\n",WSAGetLastError());
				continue;
			}

			if( ret > 0 )  //有事件发生了
			{
//printf("CSelectIO::RecvThread if( ret > 0 ) ret=%d\n",ret);
				if ( pThis->m_nListenSocket != INVALID_SOCKET&& FD_ISSET( pThis->m_nListenSocket,&fdread))//有网络连接到了
					pThis->AcceptAllConnections();

				for(int i=0;i<pThis->m_nConnectMax;i++)
				{
					if(pThis->m_IOKeyTable[i].m_bFree)
						continue;
					if(pThis->m_IOKeyTable[i].m_bClosed)
					{
						//Log("IOKEY is bClosed,Close(),sock:%d,line:%d",pThis->m_IOKeyTable[i].m_sock,__LINE__);
						pThis->Break(pThis->m_IOKeyTable[i].m_sock);
						continue;
					}

					if ( FD_ISSET( pThis->m_IOKeyTable[i].m_sock,&fdread))
					{
						pThis->m_IOKeyTable[i].m_nRecvBufSize= pThis->m_nRecvBuffSize;
						DWORD nNum = recv(pThis->m_IOKeyTable[i].m_sock,pThis->m_IOKeyTable[i].m_RecvBuff,pThis->m_IOKeyTable[i].m_nRecvBufSize,NULL);

						if( nNum == 0 )
						{
							pThis->Break(pThis->m_IOKeyTable[i].m_sock);
							continue;
						}

						if (nNum < 0)
						{
							DWORD err = WSAGetLastError();
							if (err == EAGAIN)
							{
								//Log("IOKEY is bClosed,Close(),sock:%d,err %d,line:%d",pThis->m_IOKeyTable[i].m_sock,err,__LINE__);
								pThis->Break(pThis->m_IOKeyTable[i].m_sock);
							}

							Log("%d recv Error %d\n",pThis->m_IOKeyTable[i].m_sock,err);
/*#ifdef WIN32
							if(err==WSAECONNRESET)
							{
								Log("RecvThread WSAGetLastError is:%d,no need to break ,sleep a moment\n",err);
								Sleep(500);
							}
#endif*/

							//if(err==WSAENOBUFS)
							//{
								//Sleep(10);
							//}

							continue;
						}

						pThis->m_RecvLock.LOCK();
						if(pThis->m_IOKeyTable[i].m_bFree)
						{
							//一定要再判断一下是否执行过close操作
							pThis->m_RecvLock.UNLOCK();
							continue;
						}
						pThis->Recv(pThis->m_IOKeyTable[i].m_sock,pThis->m_IOKeyTable[i].m_RecvBuff,nNum);
						pThis->m_RecvLock.UNLOCK();
					}
				}
			}
		}
		Log("Recv thread Quit\n");
	}
#if (!defined(_DEBUG)) && defined(WIN32)
	__except (HandleException(GetExceptionInformation(), "CIOCP::MainThread"))
	{

	}
#endif
	return 0;
}

void* CSelectIO::SendThread(void *Param)
{
#if (!defined(_DEBUG)) && defined(WIN32)
	__try
#endif
	{
		if(!Param)
			return 0;

		CSelectIO*	pThis= (CSelectIO*)Param;
		int			ret	 = 0;
		timeval		t	 = {0,100};
		fd_set		fdwrite;
		while( pThis->m_StarFlag )
		{
			pThis->m_Event.Wait(1000);

			if(pThis->m_nWorkSocketCount==0)
			{
				Sleep(100);
				continue;
			}

			FD_ZERO(&fdwrite);

			int fd_count = 0;
			int nfds = 0;
			for(int i=0;i<pThis->m_nConnectMax;i++)
			{
				if(pThis->m_IOKeyTable[i].m_bFree)
					continue;

				pThis->m_IOKeyTable[i].m_WriteBufferQueue.Switch();

				if(pThis->m_IOKeyTable[i].m_bClosed)
				{
					if(!pThis->m_IOKeyTable[i].m_WriteBufferQueue.IsDataWaiting())
					{
						Log("Send Thread close %d line %d\n",pThis->m_IOKeyTable[i].m_sock,__LINE__);
						pThis->Break(pThis->m_IOKeyTable[i].m_sock);
						continue;
					}
				}

				if(pThis->m_IOKeyTable[i].m_WriteBufferQueue.IsDataWaiting())
				{
					FD_SET( pThis->m_IOKeyTable[i].m_sock,&fdwrite);
					++fd_count;
					if( nfds < pThis->m_IOKeyTable[i].m_sock )
					{
						nfds = pThis->m_IOKeyTable[i].m_sock;
					}
				}
			}

			if( fd_count == 0 )
				continue;

			//ret = select( 0,NULL,&fdwrite,NULL,&t);		2011-1-5		li9chuan
			ret = select( nfds+1,NULL,&fdwrite,NULL,&t);
//printf("CSelectIO::SendThread ret = %d \n",ret);
			if (ret < 0)
			{
				//Warning("select error %d",WSAGetLastError());
				continue;
			}

			if( ret > 0 )  //有事件发生了
			{
//printf("CSelectIO::SendThread if( ret > 0 ) \n");
//				Warning("select return..");
				for(int index=0;index<pThis->m_nConnectMax;index++)
				{
					if(pThis->m_IOKeyTable[index].m_bFree)
						continue;

					if(pThis->m_IOKeyTable[index].m_bClosed)
					{
						if(!pThis->m_IOKeyTable[index].m_WriteBufferQueue.IsDataWaiting())
						{
							Log("Send Thread close i = %d socket = %d line = %d\n",index,pThis->m_IOKeyTable[index].m_sock,__LINE__);
							pThis->Break(pThis->m_IOKeyTable[index].m_sock);
							continue;
						}
					}

					if(FD_ISSET(pThis->m_IOKeyTable[index].m_sock,&fdwrite))
					{
						u_long nSendSize=0;

						char* szSendBuf = pThis->m_IOKeyTable[index].m_WriteBufferQueue.Read(nSendSize);
						if(nSendSize > 0)
						{
							pThis->m_SendLock.LOCK();
							if(pThis->m_IOKeyTable[index].m_bFree)
							{
								pThis->m_SendLock.UNLOCK();
								continue;
							}

							int nRet = send(pThis->m_IOKeyTable[index].m_sock,szSendBuf,nSendSize,NULL);
/*
printf( "Send Hex:\n");
for( int i=0; i<nRet; i++ )
{
	printf( "%02X ",szSendBuf[i] );
}
printf( " \n");
//*/

							pThis->m_SendLock.UNLOCK();

							if (nRet < 0)
							{
								DWORD err = WSAGetLastError();
								if (err == EAGAIN)
								{
									//Log("IOKEY is bClosed,Close(),sock:%d,err %d,line:%d",pThis->m_IOKeyTable[index].m_sock,err,__LINE__);
									pThis->Break(pThis->m_IOKeyTable[index].m_sock);
								}

								Log("%d send error %d \n",pThis->m_IOKeyTable[index].m_sock,err);
/*#ifdef WIN32
								if(err==WSAECONNRESET)
								{
									Log("SendThread WSAGetLastError is:%d,no need to break ,sleep a moment\n",err);
									Sleep(500);
								}

								if(err==WSAENOBUFS)
								{
									//系统缓冲区满了，没办法只有把双缓冲清空了 by zhao
									pThis->m_IOKeyTable[index].m_WriteBufferQueue.Clear();
									Sleep(10);
								}
#endif*/

								continue;
							}
							else
							{
								if(nRet == 0)
								{
									Log("Send Return = 0\n");
								}
								pThis->m_IOKeyTable[index].m_WriteBufferQueue.Delete(nRet);
							}
						}
					}
				}
			}
		}
		Log("Recv thread Quit\n");
	}
#if (!defined(_DEBUG)) && defined(WIN32)
	__except (HandleException(GetExceptionInformation(), "CIOCP::MainThread"))
	{

	}
#endif
	return 0;
}

//
void* CSelectIO::CloseThread(void *Param)
{
#if (!defined(_DEBUG)) && defined(WIN32)
	__try
#endif
	{
		if(!Param)
			return 0;

		CSelectIO*	pThis= (CSelectIO*)Param;

		while( pThis->m_StarFlag )
		{
			Sleep(1000);
			for(int i=0;i<pThis->m_nConnectMax;i++)
			{
				if(pThis->m_IOKeyTable[i].m_bFree)
					continue;

				if(pThis->m_IOKeyTable[i].m_bClosed)
				{
					pThis->m_RecvLock.LOCK();
					pThis->m_SendLock.LOCK();
					pThis->Close(pThis->m_IOKeyTable[i].m_sock);
					pThis->m_SendLock.UNLOCK();
					pThis->m_RecvLock.UNLOCK();
					continue;
				}
			}
		}
	}
#if (!defined(_DEBUG)) && defined(WIN32)
	__except (HandleException(GetExceptionInformation(), "CIOCP::MainThread"))
	{

	}
#endif
	return 0;
}

