#include "StdAfx.h"
#include "core.h"
#include "POSIX/KQueue.h"
#include "PacketDefineHead.h"
#include "Net.h"
//#include "CommData.h"
#include "GameNet.h"
#include "mempool.h"
#include "Atomic.h"
#include "SelectIO.h"
#include "vprof.h"

#include <pthread.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <map>
//#include <vector>

using namespace std;

CClassMemoryPool<SocketContext> g_kqueuepool(1024);

/////////////////////////////////////////////////////////////////////////////////////////
//
CKQueue::CKQueue(CGameNet* pGameNet)
{
	m_StarFlag = false;

	m_pGameNet = pGameNet;

	m_Kqueuefd = -1;
	m_EvCount = 0;
	m_nListenPort = -1;
	m_nListenSocket = -1;
}

CKQueue::~CKQueue()
{
	m_StarFlag = false;
	FreeSockets();
}

BOOL CKQueue::Begin(int nPort)
{
	m_nListenPort = nPort;
	m_StarFlag = true;
	m_Kqueuefd = kqueue();

	if (m_Kqueuefd < 0)
	{
		Log("kqueue fd = %d failed !!\n");
		return FALSE;
	}

	//if (!CreateListenSocket())
	if ( CreateListenSocket() < 0 )
	{
		Log("CreateListenSocket() failed ");
		return NULL;
	}

	pthread_create(&m_KQueueThrId, NULL, ThreadMain, this);

	return TRUE;
}

void CKQueue::End()
{
	Log("CKQueue::End()");
	m_StarFlag = false;
	FreeSockets();
}

int CKQueue::Connect(const char *szIP,ULONG port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		return INVALID_SOCKET;
	}

	linger lingerStruct;
	lingerStruct.l_onoff = 1;
	lingerStruct.l_linger = 30;
	setsockopt( sock, SOL_SOCKET, SO_LINGER, (void *)&lingerStruct, sizeof(lingerStruct));

	sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_port = htons(port);
	add.sin_addr.s_addr = inet_addr(szIP);

	if (connect(sock, (struct sockaddr*)&add, sizeof(sockaddr)) < 0)
	{
		//printf(" CKQueue::Connect() Server Error %d ip=%s port=%d \n", WSAGetLastError(), szIP, port);
		close(sock);
		return INVALID_SOCKET;
	}

	if (!SetNonblock(sock))
	{
		close(sock);
		return INVALID_SOCKET;
	}

	SocketContext* ctx = MakeSocketContext();
	if(ctx)
	{
		ctx->m_sock = sock;
		SetSocketContext(sock, ctx);
	}
	else
	{
		close(sock);
		return INVALID_SOCKET;
	}

	//this->AddWriteableEvent(sock);
	this->AddReadableEvent(ctx);

	//printf("Kqueue::Connect() succ, sock  %d ip %s port %d in file %s line %d\n", sock, szIP, port, __FILE__, __LINE__);

	m_pGameNet->Accept(sock);

	return sock;
}

int CKQueue::Recv( int sock,char *buf,int nSize )
{
	return m_pGameNet->Recv(sock,buf,nSize);
}

//int CKQueue::Send( int sock,PACKET_COMMAND* pPacket )
int CKQueue::Send( SOCKET sock, char *szBuf, int nSize )
{
	if(!szBuf)
		return -1;

	SocketContext* ctx = GetSocketContext(sock);
	if(!ctx)
	{
		Log("failed to GetSocketContext(), sock = %d\n", sock);
		Break(sock);
		return 0;
	}

	//	if ((pPacket->nNetid<0) && (pPacket->Type() == 3)){
	//		abort();
	//	}
//printf("ctx->m_WriteBufferQueue\n");

	//if(ctx->m_WriteBufferQueue.Write(pPacket))
	if(ctx->m_WriteBufferQueue.Write( szBuf, nSize ))
	{
		//this socket has some data to be sent , we register write event here
		AddWriteableEvent(sock);
//printf("ctx->m_WriteBufferQueue pPacket->Size()==%d\n",pPacket->Size());
		return nSize;//this packet's content all be copied to m_WriteBufferQueue
	}
	else
	{
		printf("write to WriteBuffQueue failedi. size = %d  \n",nSize);
		return 0;
	}
}

void CKQueue::Break(int sock)
{
	SocketContext* ctx = NULL;

	CLockGuard guard(&m_SocketsLock);
	map<int, SocketContext *>::iterator it = m_Sockets.find(sock);
	if(it != m_Sockets.end())
	{
		ctx = it->second;
		m_Sockets.erase(it);
	}

	if (ctx)
	{
		FreeSocketContext(ctx);
	}
	close(sock);
	m_pGameNet->Break(sock);
	Log(" Break %d",sock);
}

char* CKQueue::IP(SOCKET sock)
{
	SocketContext *pKey = GetSocketContext(sock);

	if(pKey)
		return pKey->m_szIP;
	return "";
}

void *CKQueue::ThreadMain(void *Param)
{
	if(!Param)
		return NULL;
	CKQueue *pThis = (CKQueue*)Param;

	if (pThis->m_nListenPort < 0)
		return NULL;

	struct kevent AllEvents[KEVENT_MAX_COUNT];
	int	count = 0;
	int	ret = 0;
	int	nTempIndex = 0;
	while( pThis->m_StarFlag )
	{
		//memset(AllEvents, 0, sizeof(struct kevent)*(pThis->m_EvCount));
		memset(AllEvents, 0, sizeof(struct kevent)*KEVENT_MAX_COUNT);
		//count = kevent(pThis->m_Kqueuefd, NULL, 0,(struct kevent *)&AllEvents, pThis->m_EvCount, NULL);
		count = kevent(pThis->m_Kqueuefd, NULL, 0,(struct kevent *)&AllEvents, KEVENT_MAX_COUNT, NULL);
		if (!count)
			continue;
//printf("kevent count  = %d \n", count);
		for(int i = 0; i<count; i++)
		{
			if (AllEvents[i].flags & EV_ERROR)
			{
				Log("sockfd = %d got an error, errno = %d in file %s\n", AllEvents[i].ident, errno, __FILE__);
				continue;
			}
			if (AllEvents[i].ident == pThis->m_nListenSocket)
			{
				int iacc = pThis->HandleAccept(AllEvents[i].data);
//printf("HandleAccept  = %d  acceptReturn = %d \n", i, iacc);
			}
			else if (AllEvents[i].filter == EVFILT_READ)
			{
//Print("1.Reading  i = %d ident = %d  data=%d\n", i, AllEvents[i].ident, AllEvents[i].data);
				pThis->Reading(AllEvents[i].ident, AllEvents[i].data);
//Print("2.Reading  i = %d ident = %d  data=%d\n", i, AllEvents[i].ident, AllEvents[i].data);
			}
			else if (AllEvents[i].filter == EVFILT_WRITE)
			{
				pThis->Writing(AllEvents[i].ident);
			}
		}
	}

	Log("Recv thread Quit\n");
	return NULL;
}

void SetReuseAddrOpt(int sockfd)
{
	int value = 1;
	socklen_t len = sizeof(value);
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&value, len);
	printf("sockfd %d set reuse addr\n", sockfd);
}

/*
 * return value : wether create socket succ
 */
int CKQueue::CreateListenSocket()
{
	m_nListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_nListenSocket < 0)
	{
		return -1;
	}
	//why?
	//SetReuseAddrOpt(m_nListenSocket);

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(m_nListenPort);

	int result = bind(m_nListenSocket, (struct sockaddr*)&addr, sizeof(addr));
	if (result < 0)
	{
		Log("CreateListenSocket() bind err = %d\n", errno);
		return -1;
	}

	if (!SetNonblock(m_nListenSocket))
	{
		return -1;
	}

	if (listen(m_nListenSocket, LISTEN_BACKLOG))
	{
		Log("listen error %d\n", errno);
		return -1;
	}

	SocketContext *ctx = MakeSocketContext();
	if(ctx)
	{
		ctx->m_sock = m_nListenSocket;
		SetSocketContext(m_nListenSocket, ctx);
	}
	else
	{
		Log("CreateListenSocket:MakeSocketContext() is null!\n");
		close(m_nListenSocket);
		return -1;
	}
	this->AddReadableEvent(ctx);

	return 0;
}

void PrintAddr(struct sockaddr_in *addr)
{
	char *str = inet_ntoa(addr->sin_addr);
	printf("socket addr, %s:%d\n", str, ntohs(addr->sin_port));
}

int CKQueue::HandleAccept(int cnt)
{
	for(int i=0; i<cnt; i++)
	{
		sockaddr_in addr;
		socklen_t len = sizeof(addr);
		int sockfd = accept(m_nListenSocket, (struct sockaddr *)&addr, &len);
printf( "CKQueue::HandleAccept sockfd=%d\n", sockfd );
		if (sockfd < 0)
			return -1;

		SocketContext *ctx = MakeSocketContext();
		if(ctx)
		{
			ctx->m_sock = sockfd;
			ctx->m_ip = addr.sin_addr.s_addr;
			// set key IP
			strcpy( ctx->m_szIP, inet_ntoa(addr.sin_addr));
			ctx->m_port = addr.sin_port;
			SetSocketContext(sockfd, ctx);
			this->AddReadableEvent(ctx);

			m_pGameNet->Accept(sockfd);
		}
		else
		{
			close(sockfd);
			return -1;
		}
	}
	return 0;
}

int CKQueue::Reading(int fd, int size)
{
	int count = 0;
	if( size <= count )
	{
		RemoveReadableEvent(fd);
		Break(fd);
	}
	else
	{
		while(count < size)
		{
			char szBuf[RECV_BUFFER_MAX] = {0};

			int rsize = recv(fd, szBuf, RECV_BUFFER_MAX, 0);
//printf("rsize  = %d \n", rsize);
			if (rsize <= 0)
			{
				Break(fd);
				return -1;
			}
			m_pGameNet->Recv(fd, szBuf, rsize);
			count += rsize;
//printf("recv count  = %d \n", count);
		}
	}
	return 0;
}

int CKQueue::Writing(int fd)
{
	SocketContext *ctx = GetSocketContext(fd);
	if (!ctx)
	{
		Break(fd);
		return -1;
	}
//printf( "~ CKQueue::Writing\n" );
	int count = 0;
	unsigned long nSendSize = 0;
	//char* szSendBuf = ctx->m_WriteBufferQueue.Read(nSendSize);

	char* szSendBuf = NULL;		//		2011-1-7		li9chuan
	if( ctx->m_WriteBufferQueue.Switch() )
	{
		szSendBuf = ctx->m_WriteBufferQueue.Read(nSendSize);
//printf("~ fd=%d nSendSize = %d\n", fd, nSendSize);
	}

	if(nSendSize > 0)
	{
//printf("nSendSize > 0\n");
		while(count < nSendSize)
		{
//printf("~ szSendBuf+count+1=%d nSendSize-count = %d\n", szSendBuf+count+1, nSendSize-count);

			//count += send(fd, szSendBuf+count+1, nSendSize-count, 0);
			count += send(fd, szSendBuf+count, nSendSize-count, 0);

//printf("count = %d\n",count);
			if(count <= 0)
			{
				Break(fd);
				return -1;
			}
			else
			{
				ctx->m_WriteBufferQueue.Delete(count);	//		更新发过数据的指针		li9chuan		2011-1-17
			}
		}
	}
	else
	{
//printf("nSendSize <= 0\n");
		//this socket has no data write
		RemoveWriteableEvent(fd);
	}
	return 0;
}

void CKQueue::AddReadableEvent(SocketContext *ctx)
{
	if (m_Kqueuefd < 0 || !ctx)
		return;
	struct kevent ev;
	EV_SET(&ev, ctx->m_sock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
	ev.udata = ctx;
	kevent(m_Kqueuefd, &ev, 1, NULL, 0, NULL);
	//apr_atomic_inc32(&m_EvCount);
	//printf("AddReadableEvent sockfd = %d\n", ctx->m_sock);
}

void CKQueue::AddWriteableEvent(int sockfd)
{
	if (m_Kqueuefd < 0){
		printf("m_Kqueuefd = %d\n", m_Kqueuefd);
		return;
	}
	struct kevent ev;
	EV_SET(&ev, sockfd, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
	kevent(m_Kqueuefd, &ev, 1, NULL, 0, NULL);
	//apr_atomic_inc32(&m_EvCount);
	//static int count = 0;
	//count++;
	//if (count <2 )
	//	printf("AddWriteableEvent sockfd = %d\n", sockfd);
}

void CKQueue::RemoveReadableEvent(int sockfd)
{
	if (m_Kqueuefd < 0 || sockfd < 0)
		return;
	struct kevent ev;
	EV_SET(&ev, sockfd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
	kevent(m_Kqueuefd, &ev, 1, NULL, 0, NULL);
	//	apr_atomic_dec32(&m_EvCount);
}


void CKQueue::RemoveWriteableEvent(int sockfd)
{
	if (m_Kqueuefd < 0)
		return;
	struct kevent ev;
	EV_SET(&ev, sockfd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
	kevent(m_Kqueuefd, &ev, 1, NULL, 0, NULL);
	//	apr_atomic_dec32(&m_EvCount);
}

SocketContext *MakeSocketContext(void)
{
	SocketContext *ctx = g_kqueuepool.Alloc();
	return ctx;
}

void FreeSocketContext(SocketContext *ctx)
{
	if (ctx)
	{
		ctx->Final();
		g_kqueuepool.Free(ctx);
	}
}


