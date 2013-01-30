#include "StdAfx.h"
#include "core.h"
#include "PacketDefineHead.h"
#include "GameNet.h"
#include "mstcpip.h"
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
	m_nRecvBuffSize	= 0;
	m_nSendBuffSize	= 0;
	m_nWorkSocketCount = 0;

	m_ConnectFlag = FALSE;
	m_nConnectSocket = INVALID_SOCKET;
	m_pCallFnConnAsync = NULL;
}

CSelectIO::~CSelectIO()
{
	m_StarFlag = FALSE;	
//	m_IOKeyMap.RemoveAll();
	if(m_IOKeyTable)
		Plat_Free(m_IOKeyTable);
}

// nPort		: �����Ķ˿�
//nPacketPoolSize:������Ϣ�Ļ�������С
// nConnectMax	: ���ӵ������
// nRecvBuffSize: ���ܻ���Ĵ�С
// nSendBuffSize: ���ͻ�������С
// nTimeout		: ���ͳ�ʱ
BOOL CSelectIO::Begin(int nPort,int nPacketPoolSize,int nConnecMax,int nRecvBuffSize,int nSendBuffSize,int nTimeout)
{	
	//��ʼ��Net
	if (!NetWorkStart())
	{
		printf("wsastarup��ʼ��ʧ�ܣ�\n");
		return FALSE;
	}

	Assert(nConnecMax);
	if(!nConnecMax)
		return FALSE;
	
	m_nConnectMax		= nConnecMax;
	m_nRecvBuffSize		= nRecvBuffSize;
	m_nSendBuffSize		= nSendBuffSize;

	//���� HashTable
	m_IOKeyMap.Purge(nConnecMax);

	//Ԥ����ռ�
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
			printf("failed to socket in selectio begin(), errno = %d\n", WSAGetLastError());
			return FALSE;
		}
		//���ü����׽���Ϊ������
		if (!SetNonblock(m_nListenSocket))
		{
			printf(" failed to SetNonblock,sockfd = %d\n", m_nListenSocket);
			return FALSE;
		}

		SOCKADDR_IN localAddr;
		ZeroMemory (&localAddr, sizeof (localAddr));	
		localAddr.sin_family = AF_INET;
		localAddr.sin_port = htons (nPort);
		localAddr.sin_addr.s_addr = htonl(INADDR_ANY);

		int iState = bind (m_nListenSocket, (PSOCKADDR) & localAddr, sizeof (localAddr));
		if (iState < 0)
		{
//#if (!defined(_DEBUG)) && defined(WIN32)
			Log( "Socket Bind Failed %d\n",nPort);
			if (WSAGetLastError () == WSAEADDRINUSE)
				Log( "The port number may already be in use.\n");
//#endif
			return FALSE;
		}

		iState = listen (m_nListenSocket, SOMAXCONN);
		if (iState == SOCKET_ERROR)
		{
			printf( "Socket Listen Failed\n");
			return FALSE;
		}

		m_nWorkSocketCount++;
	}	
		
	DWORD wWorkThreadID;
	HANDLE hWorkThread = CreateThread(NULL,0,RecvThread,(LPVOID)this,0,&wWorkThreadID);	
	if( !hWorkThread )
	{
		Log("Error : Create RecvThread failed %d\n" , GetLastError() );
		return false;
	}
	CloseHandle(hWorkThread);

	hWorkThread = CreateThread(NULL,0,SendThread,(LPVOID)this,0,&wWorkThreadID);	
	if( !hWorkThread )
	{
		Log("Error : Create SendThread failed %d\n" , GetLastError() );
		return false;
	}
	CloseHandle(hWorkThread);

	hWorkThread = CreateThread(NULL,0,CloseThread,(LPVOID)this,0,&wWorkThreadID);	
	if( !hWorkThread )
	{
		Log("Error : Create CloseThread failed %d\n" , GetLastError() );
		return false;
	}
	CloseHandle(hWorkThread);

	return TRUE;
}

void CSelectIO::End()
{
	Log("Client End\n");
	m_StarFlag = FALSE;
	for(int i=0;i<m_nConnectMax;i++)
	{
		if(m_IOKeyTable[i].m_bFree)
			continue;

		int err = shutdown(m_IOKeyTable[i].m_sock, SD_BOTH);
		if(err != 0)
			Log("failed to shutdown socket %d, errno = %d\n", m_IOKeyTable[i].m_sock, WSAGetLastError());

		err = closesocket(m_IOKeyTable[i].m_sock);
		if(err != 0)
			Log("failed to close socket %d, errno = %d\n", m_IOKeyTable[i].m_sock, WSAGetLastError());

		m_IOKeyTable[i].m_sock = INVALID_SOCKET;
	}

	NetWorkClose();
}

IOKEY*	CSelectIO::GetFreeKey()
{
	for(int i=0;i<m_nConnectMax;i++)
	{
		if(m_IOKeyTable[i].m_bFree)
		{
			m_IOKeyTable[i].m_bFree = false;
			m_IOKeyTable[i].m_bClosed = false;
			m_nWorkSocketCount++;
			return &m_IOKeyTable[i];
		}
	}
	return NULL;
}

//ʹ��accept()�������е���������
void CSelectIO::AcceptAllConnections()
{
	SOCKET sockfd = INVALID_SOCKET;
	do
	{
		sockaddr client_addr;
		int nAddrLen = sizeof(client_addr);
		sockfd = accept(m_nListenSocket,&client_addr,&nAddrLen);
		if(sockfd != INVALID_SOCKET)
		{
			IOKEY* pIOKey = GetFreeKey();//new IOKEY;
			if(pIOKey)
			{
				pIOKey->m_sock = sockfd;

				int nSendSize = 100*1024*1024;		//ϵͳ���ͻ�����100M	
 				int nRecvSize = 100*1024*1024;		//ϵͳ���ջ�����100M
				int dtime = 120;						//ʹ��30�볬ʱ���Źر����ã�����ż�����͹��쵼�µ�10054�����socket�ر� by zhao
				int	idle = 5000;					// ��ʼ�״�KeepAlive̽��ǰ��TCP�ձ�ʱ��
				int intv = 60000;					// ����KeepAlive̽����ʱ����1����

				int ret = SetSockOpt(sockfd, nRecvSize, nSendSize, dtime, idle, intv);
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
				closesocket(sockfd);	
				break;
			}
			
			sockaddr_in* pRemote = (sockaddr_in*)&client_addr;
			char szIP[25]={0};
			sprintf(	szIP,"%u.%u.%u.%u",
						pRemote->sin_addr.S_un.S_un_b.s_b1,
						pRemote->sin_addr.S_un.S_un_b.s_b2,
						pRemote->sin_addr.S_un.S_un_b.s_b3,
						pRemote->sin_addr.S_un.S_un_b.s_b4);			
			pIOKey->SetIP(szIP);
			m_pGameNet->Accept(sockfd);
			Log("Accept Socket %d %s\n",sockfd,szIP);
		}
	} 
	while(sockfd != INVALID_SOCKET);
}

SOCKET	CSelectIO::Connect( const char *szIP,ULONG lPort)
{
	SOCKET sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);	
	//Log("Connect sock:%d",sock);

	//LINGER lingerStruct;
	//lingerStruct.l_onoff = 1;
	//lingerStruct.l_linger = 0;
	//setsockopt( sock, SOL_SOCKET, SO_LINGER,(char *)&lingerStruct,	sizeof(lingerStruct) );

	int nSendSize = 100*1024*1024;		//ϵͳ���ͻ�����100M	
 	int nRecvSize = 100*1024*1024;		//ϵͳ���ջ�����100M
	int dtime = 120;						//ʹ��30�볬ʱ���Źر����ã�����ż�����͹��쵼�µ�10054�����socket�ر� by zhao
	int	idle = 5000;					// ��ʼ�״�KeepAlive̽��ǰ��TCP�ձ�ʱ��
	int intv = 60000;					// ����KeepAlive̽����ʱ����1����

	int ret = SetSockOpt(sock, nRecvSize, nSendSize, dtime, idle, intv);
	if(ret != 0)
	{		
		printf(" +-Connect Server Error %d\n", WSAGetLastError());
		closesocket(sock);
		return INVALID_SOCKET;
	}

	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_port = htons(lPort);
	add.sin_addr.S_un.S_addr = inet_addr(szIP);

	if (connect(sock,(struct sockaddr*)&add,sizeof(sockaddr)) ==  SOCKET_ERROR )
	{	
		Log(" +-Connect Server Error %d\n",WSAGetLastError());
		//printf(" +-Connect Server Error %d\n",WSAGetLastError());
		closesocket(sock);
		return INVALID_SOCKET;
	}

	// ���÷�����ģʽ
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

SOCKET CSelectIO::ConnectAsync( const char *szIP, ULONG lPort, ConnectCallBackFunc pfn )
{
	SOCKET sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);	
	//Log("Connect sock:%d",sock);

	//LINGER lingerStruct;
	//lingerStruct.l_onoff = 1;
	//lingerStruct.l_linger = 0;
	//setsockopt( sock, SOL_SOCKET, SO_LINGER,(char *)&lingerStruct,	sizeof(lingerStruct) );

	int nSendSize = 100*1024*1024;		//ϵͳ���ͻ�����100M	
 	int nRecvSize = 100*1024*1024;		//ϵͳ���ջ�����100M
	int dtime = 120;						//ʹ��30�볬ʱ���Źر����ã�����ż�����͹��쵼�µ�10054�����socket�ر� by zhao
	int	idle = 5000;					// ��ʼ�״�KeepAlive̽��ǰ��TCP�ձ�ʱ��
	int intv = 60000;					// ����KeepAlive̽����ʱ����1����

	int ret = SetSockOpt(sock, nRecvSize, nSendSize, dtime, idle, intv);
	if(ret != 0)
	{		
		printf(" +-Connect Server Error %d\n", WSAGetLastError());
		closesocket(sock);
		return INVALID_SOCKET;
	}

	// ���÷�����ģʽ
	if (!SetNonblock(sock))
	{
		printf(" +-Set FIOBiO Error\n");
		closesocket(sock);
		return INVALID_SOCKET;
	}

	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_port = htons(lPort);
	add.sin_addr.S_un.S_addr = inet_addr(szIP);

	bool connflag = false;
	ret = connect(sock,(struct sockaddr*)&add,sizeof(sockaddr));
	if ( ret < 0 )
	{
		ret = WSAGetLastError();
		if( ret != WSAEINPROGRESS && ret != WSAEWOULDBLOCK )
		{
			Log(" +-Async Connect Server Error %d\n", ret);
			closesocket( m_nConnectSocket );
			return INVALID_SOCKET;
		}
	}
	//�ͻ���������������ͬһ�������п��������������ӳɹ�
	else if( ret != SOCKET_ERROR )
	{
		connflag = true;
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

	m_nConnectSocket = sock;

	if( connflag )
	{
		Log("socket %d connect success!\n", sock);
		m_pGameNet->ConnectReturn( sock );
	}
	else
	{
		m_ConnectFlag = TRUE;

		DWORD wWorkThreadID;
		HANDLE hWorkThread = CreateThread(NULL,0,ConnThread,(LPVOID)this,0,&wWorkThreadID);	
		if( !hWorkThread )
		{
			Log("Error : Create ConnThread failed %d\n" , GetLastError() );
			return false;
		}
		CloseHandle(hWorkThread);

		m_pCallFnConnAsync = pfn;
	}

	return sock;	
}

int CSelectIO::Recv( SOCKET sock,char *buf,int nSize )
{
	return m_pGameNet->Recv(sock,buf,nSize);	
}

// return 
// 0 �����Ͳ��ɹ�
// -1�������ж�
//int CSelectIO::Send( SOCKET sock,PACKET_COMMAND* pPacket )
int CSelectIO::Send( SOCKET sock, char *szBuf, int nSize )
{		
	if(!szBuf)
	{
		Log("%s %d:Send szBuf null\n", __FILE__, __LINE__);
		return -1;
	}

	IOKEY* IO = GetKey(sock);
	//Assert(IO);
	if(!IO)
	{
		Break(sock);		

		Log("%s %d:GetKeyʧ�ܣ�socket=%d\n", __FILE__, __LINE__, sock);
		return -1;
	}

	if(IO->m_bClosed)
	{
		Log("%s %d:socket %d ����Ϊm_bClosed���\n", __FILE__, __LINE__, sock);
		return -1;
	}

	int flag = IO->m_WriteBufferQueue.Write( szBuf, nSize );
	if(flag <= 0)
	{
		Log("Select˫����ʣ��ռ䲻��socket=%d, szie=%d", sock, nSize);
		return -1;
	}

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

BOOL CSelectIO::Close( SOCKET sock )
{
	m_pGameNet->Break(sock);
	IOKEY* pKey = GetKey(sock);
	if(!pKey)
	{
		Log("get key by sock = %d failed\n",sock);
		return FALSE;	
	}
	RemoveKey(sock);
	pKey->Release();

	int err = shutdown( sock, SD_SEND );
	if(err != 0)
	{
		Log("shutdown socker %d, error %d, line %d\n", sock, WSAGetLastError(),__LINE__);
		return FALSE;
	}
	err = closesocket( sock );
	if(err != 0)
	{
		Log("close socker %d, error %d, line %d\n", sock, WSAGetLastError(),__LINE__);
		return FALSE;
	}

	m_nWorkSocketCount--;
	Log("close socket =%d \n",sock);
	return TRUE;
}

int CSelectIO::SetSockOpt(SOCKET sock, int nRecv, int nSend, int dtime, int idle, int intv)
{
	//����ϵͳ������
 	int ret = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (const char *)&nRecv, sizeof(int));	
	if(ret != 0)
		 return ret;
 	ret = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (const char *)&nSend, sizeof(int));
	if(ret != 0)
		return ret;

	//���Źر�����
	struct linger so_linger;
	so_linger.l_onoff	= TRUE;
	so_linger.l_linger	= dtime;
	ret =  setsockopt(sock, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(struct linger));
	if(ret != 0)
		return ret;

	//tcp����
	BOOL bKeepAlive = TRUE;
	ret = ::setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&bKeepAlive, sizeof(bKeepAlive));
	if (ret < 0)
		return ret;

	// ��������������
	tcp_keepalive alive_in		= {0};
	tcp_keepalive alive_out     = {0};
	alive_in.keepalivetime      = idle;      // ��ʼ�״�KeepAlive̽��ǰ��TCP�ձ�ʱ��
	alive_in.keepaliveinterval	= intv;      // ����KeepAlive̽����ʱ����1����
	alive_in.onoff               = TRUE;
	unsigned long ulBytesReturn = 0;
	ret = WSAIoctl(sock, SIO_KEEPALIVE_VALS, &alive_in, sizeof(alive_in), &alive_out, sizeof(alive_out), &ulBytesReturn, NULL, NULL);

	return ret;
}

//�����߳�
DWORD WINAPI CSelectIO::RecvThread(PVOID Param)
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
		fd_set		fdread;			

		while( pThis->m_StarFlag )
		{	
			if(pThis->m_nWorkSocketCount==0)
			{
				Sleep(100);
				continue;
			}

			FD_ZERO(&fdread);

			//��Ӽ���socket���¼�
			if(pThis->m_nListenSocket != INVALID_SOCKET)
				FD_SET( pThis->m_nListenSocket, &fdread );

			for(int j=0;j<pThis->m_nConnectMax;j++)
			{
				if(pThis->m_IOKeyTable[j].m_bFree)
					continue;

				if(pThis->m_IOKeyTable[j].m_bClosed)
					continue;
				//if( pThis->m_IOKeyTable[j].m_bClosed )
				//{
				//	//Log("IOKEY is bClosed,Close(),sock:%d,line:%d",pThis->m_IOKeyTable[j].m_sock,__LINE__);					
				//	pThis->Break(pThis->m_IOKeyTable[j].m_sock);
				//	continue;
				//}				
				
				FD_SET( pThis->m_IOKeyTable[j].m_sock,&fdread );				
			}			

			ret = select( 0,&fdread,NULL,NULL,&t);
			if( ret == SOCKET_ERROR )			
			{
				//Warning("select error %d\n",WSAGetLastError());		
				continue;
			}

			if( ret > 0 )  //���¼�������
			{

				if ( pThis->m_nListenSocket != INVALID_SOCKET&& FD_ISSET( pThis->m_nListenSocket,&fdread))//���������ӵ���
					pThis->AcceptAllConnections();

				for(int i=0;i<pThis->m_nConnectMax;i++)
				{					
					if(pThis->m_IOKeyTable[i].m_bFree)
						continue;
					if(pThis->m_IOKeyTable[i].m_bClosed)
						continue;
					//if(pThis->m_IOKeyTable[i].m_bClosed)
					//{
					//	//Log("IOKEY is bClosed,Close(),sock:%d,line:%d",pThis->m_IOKeyTable[i].m_sock,__LINE__);
					//	pThis->Break(pThis->m_IOKeyTable[i].m_sock);
					//	continue;
					//}

					if ( FD_ISSET( pThis->m_IOKeyTable[i].m_sock,&fdread))
					{							
						pThis->m_RecvLock.LOCK();
						pThis->m_IOKeyTable[i].m_nRecvBufSize= pThis->m_nRecvBuffSize;
						int nNum = recv(pThis->m_IOKeyTable[i].m_sock,pThis->m_IOKeyTable[i].m_RecvBuff,pThis->m_IOKeyTable[i].m_nRecvBufSize,NULL);
						pThis->m_RecvLock.UNLOCK();

						//Զ������socket�����ر�
						if(nNum == 0)
						{
							pThis->Break(pThis->m_IOKeyTable[i].m_sock);
							continue;
						}
						if ( nNum == SOCKET_ERROR)
						{						
							int err = WSAGetLastError();
							if ( err != WSAENOTSOCK && err != WSAEWOULDBLOCK && err != WSAENOBUFS && err !=WSAECONNRESET)					
							{
								//Log("IOKEY is bClosed,Close(),sock:%d,err %d,line:%d",pThis->m_IOKeyTable[i].m_sock,err,__LINE__);
								pThis->Break(pThis->m_IOKeyTable[i].m_sock);								
							}

							Log("%d recv Error %d\n",pThis->m_IOKeyTable[i].m_sock,err);

							if(err==WSAECONNRESET)
							{
								Log("RecvThread WSAGetLastError is:%d,no need to break ,sleep a moment\n",err);
								
								//Sleep(500);
								// �ƺ�ֱ��break�ᵼ�·��������������¶Ͽ����ӣ��˴������ʱ��һ������Ϊ��������
								// selectioֻ�ڷ����֮��ʹ�ã��ݲ�break������sleepһ�����Կ�
								// Ϊʲô�˴���break���� ��ʱ��Է��رջ᷵�ش˴���
								// modify by songjun 2010.12.10
								pThis->Break(pThis->m_IOKeyTable[i].m_sock);	
							}

							//if(err==WSAENOBUFS)
							//{
								//Sleep(10);
							//}

							continue;
						} 
						pThis->m_RecvLock.LOCK();
						if(pThis->m_IOKeyTable[i].m_bFree)
						{
							//һ��Ҫ���ж�һ���Ƿ�ִ�й�close����
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

DWORD WINAPI CSelectIO::SendThread(PVOID Param)
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
			for(int i=0;i<pThis->m_nConnectMax;i++)
			{
				if(pThis->m_IOKeyTable[i].m_bFree)
					continue;

				if(pThis->m_IOKeyTable[i].m_bClosed)
					continue;

				pThis->m_IOKeyTable[i].m_WriteBufferQueue.Switch();				

				/*if(pThis->m_IOKeyTable[i].m_bClosed)
				{
					if(!pThis->m_IOKeyTable[i].m_WriteBufferQueue.IsDataWaiting())
					{
						Log("Send Thread close %d line %d\n",pThis->m_IOKeyTable[i].m_sock,__LINE__);
						pThis->Break(pThis->m_IOKeyTable[i].m_sock);									
						continue;
					}
				}*/

				if(pThis->m_IOKeyTable[i].m_WriteBufferQueue.IsDataWaiting())
				{
					FD_SET( pThis->m_IOKeyTable[i].m_sock,&fdwrite);
					++fd_count;
				}
			}	

			if( fd_count == 0 )
				continue;

			ret = select( 0,NULL,&fdwrite,NULL,&t);

			if( ret == SOCKET_ERROR )			
			{
				//Warning("select error %d",WSAGetLastError());		
				continue;
			}

			if( ret > 0 )  //���¼�������
			{
				for(int index=0;index<pThis->m_nConnectMax;index++)
				{					
					if(pThis->m_IOKeyTable[index].m_bFree)
						continue;

					if(pThis->m_IOKeyTable[index].m_bClosed)
						continue;
					/*if(pThis->m_IOKeyTable[index].m_bClosed)
					{
						if(!pThis->m_IOKeyTable[index].m_WriteBufferQueue.IsDataWaiting())
						{
							Log("Send Thread close i = %d socket = %d line = %d\n",index,pThis->m_IOKeyTable[index].m_sock,__LINE__);
							pThis->Break(pThis->m_IOKeyTable[index].m_sock);					
							continue;
						}
					}*/

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
							pThis->m_SendLock.UNLOCK();							

							if ( nRet == SOCKET_ERROR )						
							{						
								DWORD err = WSAGetLastError();

								if ( err != WSAENOTSOCK && err != WSAEWOULDBLOCK && err != WSAENOBUFS && err !=WSAECONNRESET)							
								{
									//Log("IOKEY is bClosed,Close(),sock:%d,err %d,line:%d",pThis->m_IOKeyTable[index].m_sock,err,__LINE__);
									pThis->Break(pThis->m_IOKeyTable[index].m_sock);
								}

								Log("%d send error %d \n",pThis->m_IOKeyTable[index].m_sock,err);

								if(err==WSAECONNRESET)
								{
									Log("SendThread WSAGetLastError is:%d,no need to break ,sleep a moment\n",err);
									
									//Sleep(500);
									
									// �ƺ�ֱ��break�ᵼ�·��������������¶Ͽ����ӣ��˴������ʱ��һ������Ϊ��������
									// selectioֻ�ڷ����֮��ʹ�ã��ݲ�break������sleepһ�����Կ�
									// Ϊʲô�˴���break���� ��ʱ��Է��رջ᷵�ش˴���
									// modify by songjun 2010.12.10
									pThis->Break(pThis->m_IOKeyTable[index].m_sock);	
								}

								if(err==WSAENOBUFS)
								{
									//ϵͳ���������ˣ�û�취ֻ�а�˫��������� by zhao
									//pThis->m_IOKeyTable[index].m_WriteBufferQueue.Clear();
									Log("%d ���ͻ���������Ϣһ��",pThis->m_IOKeyTable[index].m_sock);
									Sleep(1);
								}

								continue;
							}
							else
							{	
								//Log("Send buff size = %d\n", nSendSize);
								if(nRet == 0)
									Log("Send Return = 0\n");
								else
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
DWORD WINAPI CSelectIO::CloseThread(PVOID Param)
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
					//�ڷ����߳��У�m_bClosedΪtrueʱ�Ͳ��ٽ�����Ϣ���ͣ���˴˴��ж������߼�����
					//��break��������������Ϣû�з��͵�����ʱ���޷������ر�socket
					//if( pThis->m_IOKeyTable[i].m_WriteBufferQueue.IsDataWaiting() )
					//	continue;

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

DWORD WINAPI CSelectIO::ConnThread(PVOID pParam)
{
#if (!defined(_DEBUG)) && defined(WIN32)
	__try
#endif
	{
		if(!pParam)
			return 0;

		CSelectIO*	pThis= (CSelectIO*)pParam;  
		int			ret	 = 0;  		
		timeval		t	 = {15,0};
		fd_set		fdwrite;	

		while( pThis->m_ConnectFlag )
		{
			if( INVALID_SOCKET == pThis->m_nConnectSocket)
				return 0;

			FD_ZERO(&fdwrite);

			FD_SET( pThis->m_nConnectSocket, &fdwrite );

			ret = select( 0,NULL,&fdwrite,NULL,&t);

			if( ret > 0 )  //���¼�������
			{			
				if(FD_ISSET( pThis->m_nConnectSocket, &fdwrite ))
				{ 
					//������������ӵķ���

					/*int error;
					int len = sizeof(error);
					getsockopt( pThis->m_nConnectSocket, SOL_SOCKET, SO_ERROR, (char *)&error, &len );
					ret = WSAGetLastError();
					if( ret == 0 )*/
					sockaddr_in add;
					int error = sizeof(sockaddr);
					if( WSAENOTCONN != getpeername( pThis->m_nConnectSocket, (struct sockaddr*)&add, &error ))
					{
						Log("socket %d connect success!\n", pThis->m_nConnectSocket);
					}
					else
					{
						Log("socket %d connect error %d!\n", pThis->m_nConnectSocket, WSAGetLastError());

						pThis->Break( pThis->m_nConnectSocket );
						pThis->m_nConnectSocket = INVALID_SOCKET;
					}
				}
			}
			else if( ret == SOCKET_ERROR )
			{
				Log(" +-Connect Server Error %d\n",WSAGetLastError());
				
				pThis->Break( pThis->m_nConnectSocket );
				pThis->m_nConnectSocket = INVALID_SOCKET;
			}
			else
			{
				continue;
			}

			pThis->m_ConnectFlag = FALSE;
		}

		if( pThis->m_pCallFnConnAsync )
		{
			pThis->m_pCallFnConnAsync( pThis->m_nConnectSocket );
		}
		else
		{
			pThis->m_pGameNet->ConnectReturn( pThis->m_nConnectSocket );
		}

		Log("Conn thread Quit\n");
	}
#if (!defined(_DEBUG)) && defined(WIN32)
	__except (HandleException(GetExceptionInformation(), "SelectIO::ConnectThread"))
	{

	}
#endif	
	return 1;
}
