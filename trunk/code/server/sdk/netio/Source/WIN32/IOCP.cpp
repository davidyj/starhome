#include "stdafx.h"
#include <WinSock2.h>
#include <mswsock.h>
#include "OSNet.h"
#include "mempool.h"
#include "mynew.h"
#include "core.h"
#include "gamenet.h"
#include "time.h"
#include "GlobalConst.h"
#include <mstcpip.h>
#include "mempool.h"

#pragma warning(disable : 4311) // ����ת��,ָ��ض�

#define _IOMSG_MEMPOOL_
#define _WSACONTEXT_MEMPOOL_

int		CIOCP::m_nRecvBuffSize=0;		//	������Ϣ����
int		CIOCP::m_nSendBuffSize=0;		//	������Ϣ����
int		CIOCP::m_nTimeout=0;			//	��ʱ

struct _WSAContextPreTreatment
{
	inline bool operator()( WSACONTEXT* const context ) const 
	{
		if( !context ) {	return false; }
		
		context->m_WriteBufferQueue.Create(CIOCP::m_nSendBuffSize,CIOCP::m_nTimeout);
		context->m_RecvBuff = (char*)Plat_Alloc(sizeof(char) * CIOCP::m_nRecvBuffSize);
		context->m_Lock = new CGLock;

		context->m_RecvBuffSize		= CIOCP::m_nRecvBuffSize;
		context->m_WSAInBuf.len		= context->m_RecvBuffSize;
		context->m_WSAInBuf.buf		= context->m_RecvBuff;	
		return true;
	}
};

struct _WSAContextAfterTreatment
{
	inline bool operator()( WSACONTEXT* const context ) const 
	{
		if( !context ) {	return false; }
		
		context->m_WriteBufferQueue.Purge();
		Plat_Free(context->m_RecvBuff);
		delete context->m_Lock;
		return true;
	}
};

CObjectMemoryPool<IOMessage>&	   g_IocpIOMsgPool()	{static CObjectMemoryPool<IOMessage> pool; return pool;}
CObjectMemoryPool<WSACONTEXT,_WSAContextPreTreatment,_WSAContextAfterTreatment>&	   g_WsaConntextPool()	{static CObjectMemoryPool<WSACONTEXT,_WSAContextPreTreatment,_WSAContextAfterTreatment> pool; return pool;}
//////////////////////////////////////////////////////////////////////////
//
WSACONTEXT::WSACONTEXT()
{
	m_nStatus			= Key_Free;	
	m_sock				= INVALID_SOCKET;
	m_szIP[0]			= '\0';
	m_WriteCompleteFlag = true;	
	m_IOMsgPending		= 0;
//	m_IOReadPending		= 0;
	m_BreakFlag			= false;
	//m_LClientSocketByte = 0;
	//m_LLastByte = 0;
}

WSACONTEXT::~WSACONTEXT()
{
#ifdef _WSACONTEXT_MEMPOOL_
//	m_nStatus			= Key_Free;	
//	m_sock				= INVALID_SOCKET;
//	m_szIP[0]			= '\0';
//	m_WriteCompleteFlag = true;	
//	m_IOMsgPending		= 0;
////	m_IOReadPending		= 0;
//	m_BreakFlag			= false;
//	//m_LClientSocketByte = 0;
//	//m_LLastByte = 0;
#endif
}

//void WSACONTEXT::Create(int nRecvBuffSize,int nSendBuffSize,int nTimeout)
//{
//#ifdef _RECVBUFF_MEMPOOL_
//	m_WriteBufferQueue.Create(nSendBuffSize,nTimeout);
//	m_RecvBuffSize		= nRecvBuffSize;					
//	m_RecvBuff			= g_ContextRecvBuffPool().Alloc();
//	m_WSAInBuf.len		= m_RecvBuffSize;
//	m_WSAInBuf.buf		= m_RecvBuff;		
//#else
//	m_WriteBufferQueue.Create(nSendBuffSize,nTimeout);
//	m_RecvBuffSize		= nRecvBuffSize;					
//	m_RecvBuff			= (char*)Plat_Alloc(sizeof(char) * m_RecvBuffSize);
//	m_WSAInBuf.len		= m_RecvBuffSize;
//	m_WSAInBuf.buf		= m_RecvBuff;		
//#endif
//	m_Lock = new CGLock;
//}


bool WSACONTEXT::Init()
{
	m_sock = WSASocket(AF_INET, SOCK_STREAM, 0,NULL,0,WSA_FLAG_OVERLAPPED);				
	if(m_sock == INVALID_SOCKET)
	{				
		Assert(0);
		Warning( "InitIOCPKey WSASocket Error: %d",WSAGetLastError());			
		return false;
	}

	// ����socketѡ��			
 	int nSize = 0;
 	LINGER lingerStruct;		
 	lingerStruct.l_onoff = 1;
 	lingerStruct.l_linger = 0;
 	//setsockopt( m_sock,SOL_SOCKET,SO_SNDBUF,(char *)&nSize,sizeof(int) );		//�ײ㷢�ͻ����С��Ϊ0��ֻ��������ǳ����������´�����������
 	//setsockopt( m_sock,SOL_SOCKET,SO_RCVBUF,(char *)&nSize,sizeof(int) );		//���ջ�������Ϊ0����������κ������������ײ�����ݿ����������޷������
 	setsockopt( m_sock,SOL_SOCKET,SO_LINGER,(char *)&lingerStruct, sizeof(lingerStruct) );		
	return true;
}

void WSACONTEXT::Release()
{
	m_nStatus			= Key_Free;
	m_WriteCompleteFlag = true;	
	m_szIP[0]			='\0';	
	m_IOMsgPending		= 0;
	m_BreakFlag			= false;
	//m_BreakTime			= 0;

	if(m_sock != INVALID_SOCKET)
	{
		int ret = shutdown( m_sock, SD_SEND );
		if( ret == SOCKET_ERROR )
		{
			Log("shutdown socket %d error %d\n", m_sock, GetLastError());

			closesocket(m_sock);
		}

		//closesocket(m_sock);
	}

	m_sock				= INVALID_SOCKET;

	m_WriteBufferQueue.Release();
	//g_ContextRecvBuffPool().Free(m_RecvBuff);
}

//////////////////////////////////////////////////////////////////////////
//

CIOCP::CIOCP(CGameNet* pGameNet)
{	
	m_dRunFlag			= false;
	m_hCompletionPort	= NULL;
	m_nConnectMax		= 0;
	m_hAcceptHanle		= 0;
	m_hAcceptMoreHandle	= NULL;
	m_nListenSocket		= INVALID_SOCKET;
	m_pGameNet			= pGameNet;	
	m_AcceptingThreadCount=0;	
	m_KeyTable			= NULL;
	m_IOMsgTable		= NULL;
	m_KeyTableIndex		= 0;
	m_IOMsgTableIndex	= 0;
	m_nRecvBuffSize		= 0;
	m_nSendBuffSize		= 0;
	m_nPacketPoolSize	= 0;	
	m_IOMsgCount		= 0;
	m_IOMsgMax			= 0;
	m_KeyUsedCount		= 0;
//	m_nSwitchThreadSleepTime=0;
	m_LLimitByte = 0;
	g_WaitableTimer = NULL;
//	m_nKeepLiveTime= 5000;	
	SetDefLessFunc(m_KeyMap);
	//////////////////////////////////////////////////////////////////////////
//#ifdef _DEBUG
	m_IOReadCount=0;
	m_IOWriteCount=0;
	m_IOInitializeCount=0;                                                                                                        
	m_IOCloseCount=0;
	m_IOWriteCompleteCount=0;
//#endif
	//////////////////////////////////////////////////////////////////////////
}


CIOCP::~CIOCP()
{	
	if(m_IOMsgTable)
		Plat_Free(m_IOMsgTable);
	if(m_KeyTable)
		Plat_Free(m_KeyTable);
}

void SetReuseAddrOpt(int sockfd)
{	
	int value = 1;
	int len = sizeof(value);
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&value, len);	
}


// FUNCTION:- star
// ��ʼ����ɶ˿�
// 1.Ԥ�ȴ���ָ��������Key
// 2.ȷ����Ҫ�����Ĺ����߳�����
// nPort		: �����Ķ˿�
// nConnectMax	: ���ӵ������
// nRecvBuffSize: ���ܻ���Ĵ�С
// nSendBuffSize: ���ͻ�������С
// nTimeout		: ���ͳ�ʱ
BOOL CIOCP::Begin(int nPort,int nPacketPoolSize,int nConnecMax,int nRecvBuffSize,int nSendBuffSize,int nTimeout,int nAcceptCount)
{	
	Log("port %d\n",nPort);
	if(nPort < 1024)
	{			
		Log("�����ô���1024�Ķ˿�\n");
		Assert(0);
		return false;
	}

	WSAData data;
	if(WSAStartup(MAKEWORD(2,2),&data))
	{
		Log("wsastarup��ʼ��ʧ�� %d\n",GetLastError());
		return FALSE;
	}	

	// get pc info
	SYSTEM_INFO	systemInfo;
	GetSystemInfo(&systemInfo);
	m_dProcessCounts = systemInfo.dwNumberOfProcessors*2+2;	

	m_AcceptThreadMax = nAcceptCount;
	m_nListenPort = nPort;
	m_dRunFlag = true;		

	m_hCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0 );	
	if (!m_hCompletionPort)
	{
		Log("Error : CompletionPort Create Failed %d\n" , WSAGetLastError());
		return  FALSE;
	}		

	//��Ϣ�ش�С
	m_nPacketPoolSize = nPacketPoolSize;	

	m_nRecvBuffSize = nRecvBuffSize;
	m_nSendBuffSize = nSendBuffSize;
	m_nTimeout = nTimeout;

	//����IOMsg�����ֵ
	m_IOMsgMax = nConnecMax * 5;

	//�����������ֵ
	m_nConnectMax = nConnecMax;
	

	//��ʼ��IOMsg
#ifdef _IOMSG_MEMPOOL_
	g_IocpIOMsgPool().Init("IOCP_IOMsg", m_IOMsgMax,0);
#else
	m_IOMsgTable = (IOMessage*)Plat_Alloc(sizeof(IOMessage)*m_IOMsgMax);
	for(int j=0;j<m_IOMsgMax;j++)
	{
		m_IOMsgTable[j].Init();
	}
#endif

	// Ԥ�ȷ���ռ� ����socket
#ifdef _WSACONTEXT_MEMPOOL_
	g_WsaConntextPool().Init("IOCP_WSACONTEXT", nConnecMax,0);
#else
	m_KeyTable = (WSACONTEXT*)Plat_Alloc(sizeof(WSACONTEXT)*nConnecMax);	
	for(int i=0;i<nConnecMax;i++)
	{
		new(&m_KeyTable[i])	WSACONTEXT;
		m_KeyTable[i].Create(nRecvBuffSize,nSendBuffSize,nTimeout);
	}
#endif
	
	WSACONTEXT *pKey = GetFreeKey(Key_Listen);
	Assert(pKey);
	if( !pKey )
	{
		Log("GetFreeKey = NULL\n");
		return false;
	}

	// ���ü���socket
	m_nListenSocket = pKey->m_sock;

	SetReuseAddrOpt(m_nListenSocket);

	SOCKADDR_IN localAddr;
	ZeroMemory (&localAddr, sizeof(localAddr));	
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons (m_nListenPort);
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int iState = bind (m_nListenSocket,(PSOCKADDR)&localAddr,sizeof(localAddr));
	if (iState == SOCKET_ERROR)
	{
		Log("Error : Socket Bind Failed %d\n" , WSAGetLastError());
		return false;
	}

	iState = listen (m_nListenSocket, SOMAXCONN);
	if (iState == SOCKET_ERROR)
	{
		Log("Error : Socket Listen Failed %d\n" , GetLastError());
		return false;
	}

 	DWORD wThreadID;
 	HANDLE hThread= CreateThread(NULL, 0, MainThread, (LPVOID )this,0,&wThreadID); 	
	if( !hThread )
	{
		Log("Error : Create MainThread failed %d\n" , GetLastError());
		return false;
	}
 	CloseHandle(hThread);		

	//���������߳�
	for(int i = 0;i<m_dProcessCounts;i++)
	{
		HANDLE hThread;
		unsigned long wThreadID;
		hThread = CreateThread(NULL,0,WorkThread,(PVOID)this,0,&wThreadID);
		if( !hThread )
		{
			Log("Error : Create WorkThread failed %d\n" , GetLastError());
			return false;
		}
		CloseHandle(hThread);
	}

	//�������˫�������߳�
	int nSwitchProcess = 3;
	for(int i = 0;i<nSwitchProcess;i++)
	{
		HANDLE hThread;
		unsigned long wThreadID;
		hThread = CreateThread(NULL,0,SwitchThread,(PVOID)this,0,&wThreadID);
		if( !hThread )
		{
			Log("Error : Create SwitchThread failed %d\n" , GetLastError());
			return false;
		}
		CloseHandle(hThread);
	}

	//
	hThread = CreateThread(NULL,0,RemoveSocketThread,(PVOID)this,0,&wThreadID);
	if( !hThread )
	{
		Log("Error : Create RemoveSocketThread failed %d\n" , GetLastError() );
		return false;
	}
	CloseHandle(hThread);	

	m_pGetAcceptExSockaddrs = NULL;

	if(!g_WaitableTimer)
	{
		g_WaitableTimer = CreateWaitableTimer(NULL,FALSE,/*name*/NULL);		
	}
	if(!g_WaitableTimer)
	{
		Log("�޷�������ʱ��......\n");
	}

	LARGE_INTEGER lpDueTime;
	lpDueTime.QuadPart = -10000000;

	SetWaitableTimer(g_WaitableTimer,&lpDueTime,1000,NULL,NULL,0);

	return TRUE;
}


void CIOCP::End()
{
	m_dRunFlag = false;	

	PostQueuedCompletionStatus(m_hCompletionPort, 0, (DWORD) NULL, NULL);			
	CloseHandle(m_hCompletionPort);

	WSACleanup();
}

DWORD WINAPI CIOCP::MainThread(void *param)
{	
#ifndef _DEBUG
	__try
#endif
	{
		CIOCP *pThis=(CIOCP *)param;	

		pThis->m_hAcceptHanle		= CreateEvent(NULL,TRUE,FALSE,NULL);
		pThis->m_hAcceptMoreHandle	= CreateEvent(NULL,FALSE,FALSE,NULL);	

		// ֪ͨ��ʼ�����
		//pThis->m_InitEvent.Event();

		DWORD dResult=0;		
		while (pThis->m_dRunFlag)
		{
			do 
			{		
				while(pThis->m_AcceptingThreadCount < pThis->m_AcceptThreadMax && pThis->m_dRunFlag )
				{		
					if(!pThis->AcceptThread())
					{
						Log("GetFreeKey == NULL\n");
						break;
					}
				}		

				// �¼�����
				ResetEvent( pThis->m_hAcceptHanle );
				ResetEvent( pThis->m_hAcceptMoreHandle);

				HANDLE HandleWaitfor[2];
				HandleWaitfor[0] = pThis->m_hAcceptHanle;
				HandleWaitfor[1] = pThis->m_hAcceptMoreHandle;

				//����connectʱ waitforsingleobject ͨ��
				if( dResult= WaitForMultipleObjects(2, HandleWaitfor, false, 1000) == WAIT_FAILED )
				{								
					Log("Error : Waitforsingleobject %d\n" , GetLastError() );
				}
				if( !dResult && pThis->m_dRunFlag )
				{					
					//pThis->CheckPendingList();				
				}
				if( dResult != WAIT_OBJECT_0 &&	dResult != WAIT_OBJECT_0 + 1 && pThis->m_dRunFlag )
				{
					Log("Error:WaitForMutipleObjects %d\n",GetLastError());
				}
				if(dResult==WAIT_OBJECT_0 + 1 && pThis->m_dRunFlag)
				{					
					pThis->m_AcceptThreadMax+=10;					
					dResult=TRUE;				
				}
			} 
			while(dResult==WAIT_OBJECT_0);			
		}
	}
#ifndef _DEBUG
	__except (HandleException(GetExceptionInformation(), "CIOCP::MainThread"))
	{

	}
#endif	
	return 0;	
}
//#define SIO_KEEPALIVE_VALS _WSAIOW(IOC_VENDOR,4)

//����Ƿ����˫������
//2010-2-18
DWORD WINAPI CIOCP::SwitchThread(LPVOID pParam)
{
	if(!pParam)
		return 0;

	CIOCP *pThis=(CIOCP *)pParam;	
#ifndef _DEBUG
	__try
	{
#endif	
	while(pThis->m_dRunFlag)
	{
		int index;
		WSACONTEXT* pKey = NULL;
		while(pKey = pThis->getHeadWorkListKey(index))
		{
			pKey->m_Lock->LOCK();		
			if(pKey->m_BreakFlag && pKey->m_WriteBufferQueue.IsBuffEmpty())
			{
				pThis->addRemoveListKey(pKey);
				pKey->m_Lock->UNLOCK();		
				continue;
			}
			
			if(pKey->m_nStatus == Key_Work)
			{				
				if(pKey->m_WriteBufferQueue.Switch(true))
				{
					if( pKey->m_WriteCompleteFlag )// ��������Ҫ����
					{						
						IOMessage*	pIOMsg = pThis->Overlap_Alloc(pKey,IOWrite);
						if(pIOMsg)
						{
							pIOMsg->m_socket = pKey->m_sock;
							pKey->m_WriteCompleteFlag = false;
					//		pKey->m_WriteBufferQueue.CompressReadBuffer();
							if(PostQueuedCompletionStatus( pThis->m_hCompletionPort,0,(DWORD)pKey,&pIOMsg->m_ol )==0)
							{								
								pThis->Overlap_Free(pKey,pIOMsg);
							}
						}						
					}
				}
				//�ٷŻع�������
				if( !pThis->addWorkListKey(pKey) )
				{
					Log("��������������ظ���key(sock=%d)!", pKey->m_sock);
					pThis->addRemoveListKey(pKey);
				}
			}
			else
			{
				Log("������������쳣key(sock=%d, status=%d, break=%d)", pKey->m_sock, pKey->m_nStatus, pKey->m_BreakFlag);
				pThis->addRemoveListKey(pKey);
			}
			pKey->m_Lock->UNLOCK();
		}	
		//Sleep(pThis->m_pGameNet->m_nSwitchThreadSleepTime);
	}	

#ifndef _DEBUG
	}
	__except (HandleException(GetExceptionInformation(), "CIOCP::SwitchThread"))
	{

	}
#endif
	return 0;
	
}

void CIOCP::AddRemoveSocket(WSACONTEXT* pKey)
{
	if(!pKey)
		return;

	if( pKey->m_nStatus == Key_Work )
		removeWorkListKey(pKey);

	addRemoveListKey(pKey);
}

//�ر�socket���߳�
//ֻ�е��ر������е� ���� ����֮�� ���������Ĺر�socket
DWORD WINAPI CIOCP::RemoveSocketThread(LPVOID pParam)
{
	if(!pParam)
		return 0;

	CIOCP *pThis=(CIOCP *)pParam;	
#ifndef _DEBUG
	__try
	{
#endif	
	while(pThis->m_dRunFlag)
	{
		pThis->m_RemoveEvent.Wait(60000);
		WSACONTEXT *pKey = NULL;
		while(pKey = pThis->getHeadRemoveListKey())
		{
			// IOInitialize��IORead	&&	û������Ҫ���ͣ�Ҳ����Ҫ�Ӹ����������Writing��ͻ
			// Ӧ��֤Ҫ���͵����ݶ���copy��socket�Ļ��������ٹر�
			//if(pKey->m_IOMsgPending <= 2 /*&& timeGetTime() - pKey->m_BreakTime >= 30000*/)
			////if( timeGetTime() - pKey->m_BreakTime >= 30000 )
			//{
			//	pThis->RemoveStaleClient(pKey);	
			//}
			//else
			//{
			//	pThis->addRemoveListKey(pKey);
			//	continue;
			//}
			pThis->RemoveStaleClient(pKey);	
		}
		//Sleep(10);
	}
#ifndef _DEBUG
	}
	__except (HandleException(GetExceptionInformation(), "CIOCP::RemoveSocketThread"))
	{

	}
#endif
	return 0;

}

// ���ӷ�����
//1.���ӷ�����
//2.Ͷ��������ɵ�����
//3.��ӵ���ɶ˿ڹ���
SOCKET CIOCP::Connect( const char *szIp,DWORD nPort )
{
	// New a Socket context 	
	WSACONTEXT* pKey = GetFreeKey(Key_Work);
	if( !pKey )
	{
		Log("Connect GetFreeKey = NULL");
		return INVALID_SOCKET;	 	
	}	
	if( !addWorkListKey(pKey) )
	{
		addRemoveListKey(pKey);
		Log("��������������ظ���key(sock=%d)!", pKey->m_sock);
		return false;
	}
	
	// Create socket to listen 
	SOCKADDR_IN localAddr;
	ZeroMemory (&localAddr, sizeof (localAddr));	
	localAddr.sin_family = AF_INET;
	localAddr.sin_port = htons (nPort);
	localAddr.sin_addr.s_addr = inet_addr(szIp);

	if( WSAConnect( pKey->m_sock,(struct sockaddr*)&localAddr,sizeof(localAddr),NULL,NULL,NULL,NULL) )
	{
		Log(" +-Connect Error %d\n",WSAGetLastError());
		Break(pKey);
		return INVALID_SOCKET;
	}		
	
	if(!PostRecvRequiry(pKey))
		return INVALID_SOCKET;

	m_pGameNet->Accept(pKey->m_sock);

	return pKey->m_sock;
}

char* CIOCP::IP(SOCKET sock)
{
 	WSACONTEXT *pKey = getKey(sock);
 	if(pKey)
 		return pKey->m_szIP;
	return "";
}

void CIOCP::Break( WSACONTEXT *pKey )
{
	if(pKey)
		pKey->m_BreakFlag = true;
 	/*if(pKey && !pKey->m_BreakFlag)
	{
		pKey->m_BreakFlag = true;

		IOMessage*	pIOMsg = Overlap_Alloc(pKey,IOClose);
		Assert(pIOMsg);
		if(pIOMsg)
		{
			pIOMsg->m_socket  = pKey->m_sock;
			if(PostQueuedCompletionStatus(m_hCompletionPort,0,(DWORD)pKey,&pIOMsg->m_ol)==0){
				Overlap_Free(pKey,pIOMsg);
			}		
		}		
	}*/
}

void CIOCP::ShutDown( SOCKET sock )
{	
	Assert(sock != m_nListenSocket);
	if(sock==INVALID_SOCKET || !m_dRunFlag || sock == m_nListenSocket)
	{
		Log("Error:ShutDown socket failed!(sock=%d,RunFlag=%d)", sock, m_dRunFlag);
		return;
	}

 	WSACONTEXT *pKey=getKey(sock);	
	if(pKey){
		pKey->m_Lock->LOCK();
 		Break(pKey);
		pKey->m_Lock->UNLOCK();
	}
}

// read data from socket
uint CIOCP::Reading(WSACONTEXT *pKey,uint nSize)
{
	if(!pKey || pKey->m_nStatus == Key_Free || pKey->m_BreakFlag)
		return false;

	if(nSize==0)
	{
		Break(pKey);
		return 0;
	}

	Recv( pKey->m_sock,pKey->m_WSAInBuf.buf,nSize); 

	if( !PostRecvRequiry(pKey) )
	{
		Break(pKey);
		return FALSE;
	}

	return TRUE;
}

// write data to socket
bool CIOCP::Writing(WSACONTEXT *pKey,uint nSize)
{
	if(!pKey || pKey->m_nStatus == Key_Free)
		return false;


	//��Ҫ�ѷ��ͻ����е����ݷ������ٹر�socket
	////����Ѿ��Ͽ��Ͳ���Ͷ���κ�����
	//if(pKey->m_BreakFlag)
	//{
	//	return false;
	//}

	// û��Ҫ�����͵�����
	if(!pKey->m_WriteBufferQueue.IsDataWaiting())
	{
		pKey->m_WriteCompleteFlag = true;
		return false;
	}


	pKey->m_WSAOutBuf.buf = pKey->m_WriteBufferQueue.Read(pKey->m_WSAOutBuf.len);
	if(!pKey->m_WSAOutBuf.len)
	{
		pKey->m_WriteCompleteFlag = true;
		return false;
	}

	IOMessage*	pMsg = Overlap_Alloc(pKey,IOWriteComplete);			
	if(!pMsg)
	{
		pKey->m_WriteCompleteFlag = true;
		return false;
	}
	pMsg->m_socket = pKey->m_sock;	

	ULONG ulFlags			= MSG_PARTIAL;
	ULONG dwSendNumBytes	= 0;
	int nRetVal = WSASend(pKey->m_sock,&pKey->m_WSAOutBuf,1,&dwSendNumBytes,ulFlags,&pMsg->m_ol,NULL);
	if (nRetVal == SOCKET_ERROR) 
	{	
		int dFlag = WSAGetLastError();
		if(dFlag != WSA_IO_PENDING /*&& dFlag != WSAENOBUFS*/)
		{
			Log("WsaSend error %d GameNetBreak socket %d\n",dFlag,pKey->m_sock);			
			Overlap_Free(pKey,pMsg);			
		}		
	}

	return true;
}

// Write Complete
bool CIOCP::WriteComplete( WSACONTEXT* pKey,uint nSize )
{
	if(!pKey || pKey->m_nStatus == Key_Free)
	{
		Log("WriteComplete��״̬ΪpKey_Free\n");
		return false;
	}

	//��Ҫ�ѷ��ͻ����е����ݷ������ٹر�socket
	////����Ѿ��Ͽ��Ͳ���Ͷ���κ�����
	//if(pKey->m_BreakFlag)
	//{
	//	return false;
	//}

	pKey->m_WriteBufferQueue.Delete(nSize);

	//ѹ���� �� ������ȥ��������� ����Post
	if(pKey->m_WriteBufferQueue.IsDataWaiting())
	{
		IOMessage*	pOverlap=Overlap_Alloc(pKey,IOWrite);
		if(pOverlap)
		{
			if(PostQueuedCompletionStatus( m_hCompletionPort,0,(DWORD)pKey,&pOverlap->m_ol ) == 0)
			{
				Log("Error:Post IOWrite failed!(sock=%d)", pKey->m_sock);
				Overlap_Free(pKey,pOverlap);
			}	
		}		
	}
	else
	{
		pKey->m_WriteCompleteFlag = true;
	}

	return true;
}

// �������
int CIOCP::ConnectComplete( WSACONTEXT* pContext,int nSize )
{
	// TRUE��Ͷ��Recv����
	PostRecvRequiry(pContext);
	return TRUE; 
}

// nStatus : Key����;
WSACONTEXT* CIOCP::GetFreeKey(Key_Status nStatus)
{
	if(m_KeyUsedCount >= m_nConnectMax)
	{
		//Log("GetFreeKey == NULL max = %d\n",m_nConnectMax);
		return NULL;
	}

	WSACONTEXT*  pKey = NULL;	
			
#ifdef _WSACONTEXT_MEMPOOL_
	pKey = g_WsaConntextPool().Alloc();
	if(pKey){
		if( pKey->Init() ){
			if(SetIOComplete(pKey)){				
				pKey->m_nStatus = nStatus;	
				if( addKeyMap(pKey)){
					return pKey;	
				}
			}
		}
		pKey->Release();
		g_WsaConntextPool().Free(pKey);	
	}	
	return NULL;	
#else
	if(m_KeyTable[m_KeyTableIndex].m_nStatus == Key_Free)
	{				
		if(m_KeyTable[m_KeyTableIndex].Init())
		{
			pKey = &m_KeyTable[m_KeyTableIndex];
			pKey->m_nStatus = nStatus;				
			if(SetIOComplete(pKey))
			{
				addKeyMap(pKey);
			}
			break;
		}			
	}				
	if(++m_KeyTableIndex >= m_nConnectMax)
		m_KeyTableIndex = 0;	
#endif
	
	return NULL;
}

void CIOCP::FreeContext(WSACONTEXT* pKey)
{
	if(pKey)
	{
		pKey->Release();

		g_WsaConntextPool().Free(pKey);
	}
}



bool CIOCP::AcceptThread()
{		
	// New a Socket context 	
	WSACONTEXT *pKey = GetFreeKey(Key_Accept);
	if( !pKey )
	{		
		Log("%s %d:SetAcceptContextList pKey = NULL\n", __FILE__, __LINE__);
		return false;	 		
	}

	// Get AcceptEx addr
	GUID functionID = WSAID_ACCEPTEX;
	LPFN_ACCEPTEX lpfn_accept = NULL;	
	DWORD dwBytes = 0;
	if (WSAIoctl(m_nListenSocket,SIO_GET_EXTENSION_FUNCTION_POINTER,&functionID,sizeof(functionID),&lpfn_accept,sizeof(lpfn_accept),&dwBytes,0,0))
	{
		Log("%s %d:WSAIoctl Listen socket %d error %d", __FILE__, __LINE__,m_nListenSocket,WSAGetLastError());
		FreeContext(pKey);
		return false;
	}

	// Get GetAcceptExSockaddrs addr	
	GUID funcID = WSAID_GETACCEPTEXSOCKADDRS;	
	DWORD dwByt = 0;
	if(WSAIoctl(pKey->m_sock,SIO_GET_EXTENSION_FUNCTION_POINTER,&funcID,sizeof(GUID),&m_pGetAcceptExSockaddrs,sizeof(m_pGetAcceptExSockaddrs),&dwByt,0,0))
	{
		Log("Get GetAcceptExSockaddrs addr(sock=%d, error=%d", pKey->m_sock, WSAGetLastError());
		FreeContext(pKey);
		return false;
	}

	//�������,����쵽�����ж�ʱ,GetQueuedCompletionStatus�᷵��FALSE add by zhao
	//BOOL bKeepAlive = TRUE;
	//int nRet = ::setsockopt(pKey->m_sock, SOL_SOCKET, SO_KEEPALIVE, (char*)&bKeepAlive, sizeof(bKeepAlive));
	//if (nRet == SOCKET_ERROR)
	//{
	//	Log("KeepAlive���ô���:%d\n",WSAGetLastError());
	//	FreeContext(pKey);
	//	return FALSE;
	//}

	//// ����KeepAlive����
	//tcp_keepalive alive_in      = {0};
	//tcp_keepalive alive_out     = {0};
	//alive_in.keepalivetime      = 5000;							// ��ʼ�״�KeepAlive̽��ǰ��TCP�ձ�ʱ��
	//alive_in.keepaliveinterval	= 1000;//m_pGameNet->m_nKeepLiveTime;	// ����KeepAlive̽����ʱ����
	//alive_in.onoff				= TRUE;
	//unsigned long ulBytesReturn = 0;
	//nRet = WSAIoctl(pKey->m_sock, SIO_KEEPALIVE_VALS, &alive_in, sizeof(alive_in), &alive_out, sizeof(alive_out), &ulBytesReturn, NULL, NULL);
	//if (nRet == SOCKET_ERROR)
	//{
	//	Log("IOCP KeepAlive���ô���sock:%d,error:%d\n",pKey->m_sock,WSAGetLastError());
	//	FreeContext(pKey);
	//	return FALSE;
	//}

	// get an IOInitialize IOMessage
	IOMessage* pMsg = Overlap_Alloc(pKey,IOInitialize);
	Assert(pMsg);
	if(!pMsg)
	{
		Log("Get IOinitialize IOMessage failed(sock=%d)!", pKey->m_sock);
		FreeContext(pKey);
		return false;
	}
	pMsg->m_socket  = pKey->m_sock;

	// send a accept request
	DWORD wRecvbyte = 0;
	const size_t sizeOfAddress = sizeof(SOCKADDR_IN) + 16;
	const size_t sizeOfAddresses = 2 * sizeOfAddress;	
	int bufsize = pKey->m_RecvBuffSize - sizeOfAddresses;
	BOOL accepflag=lpfn_accept(	m_nListenSocket,pKey->m_sock,pKey->m_RecvBuff,bufsize,sizeOfAddress,sizeOfAddress,&wRecvbyte,&pMsg->m_ol);
	if(!accepflag)
	{			
		if( WSAGetLastError()!=ERROR_IO_PENDING)
		{			
			Assert(0);
			Log("Break lpfn_accept error %d",WSAGetLastError());	
			Overlap_Free(pKey,pMsg);
			FreeContext(pKey);
			return false;
		}		
	}

	InterlockedIncrement(&m_AcceptingThreadCount);	

	return true;
}

//////////////////////////////////////////////////////////////////////////
// Function: AcceptComplated()
// Remark:���յ���һ����������,������в���
// pAcceptOvl:is listen socket context
// s:is accept socket context
//////////////////////////////////////////////////////////////////////////
bool CIOCP::AcceptComplated(WSACONTEXT *pListenKey,SOCKET AcceptSocket,DWORD wSize)
{
	InterlockedDecrement(&m_AcceptingThreadCount);		
	SetEvent(m_hAcceptHanle);

	WSACONTEXT *pAcceptKey = getKey(AcceptSocket);
	if(!pAcceptKey)
	{
		Warning("Error:AcceptComplated() getKey error \n");
		return false;			
	}		
	
	//Log("IOCP::AcceptComplated %d", pAcceptKey->m_sock);

	pAcceptKey->m_nStatus = Key_Work;
	if( addWorkListKey(pAcceptKey) )
	{
		if( m_pGetAcceptExSockaddrs )
		{ 
			const size_t sizeOfAddress = sizeof(SOCKADDR_IN) + 16;
			const size_t sizeOfAddresses = 2 * sizeOfAddress;		
			int bufsize = pAcceptKey->m_RecvBuffSize - sizeOfAddresses;	

			// printf IP address 
			// remark: bufsize = ����ĳ���-������ַ�ṹ��ĳ���
			INT sizeOfLocalAddress = 0;
			INT sizeOfRemoteAddress = 0;

			SOCKADDR *pLocalAddress = 0;
			SOCKADDR *pRemoteAddress = 0;

			m_pGetAcceptExSockaddrs(	pAcceptKey->m_WSAInBuf.buf,
				bufsize,sizeOfAddress,
				sizeOfAddress,
				&pLocalAddress,
				&sizeOfLocalAddress,
				&pRemoteAddress,
				&sizeOfRemoteAddress);	

			sockaddr_in * pRemote = (sockaddr_in*)pRemoteAddress;
			// set key IP
			sprintf( pAcceptKey->m_szIP,"%u.%u.%u.%u",
				pRemote->sin_addr.S_un.S_un_b.s_b1,
				pRemote->sin_addr.S_un.S_un_b.s_b2,
				pRemote->sin_addr.S_un.S_un_b.s_b3,
				pRemote->sin_addr.S_un.S_un_b.s_b4);
		}

		//Log("Accept ip=%s, sock=%d", pAcceptKey->m_szIP, pAcceptKey->m_sock);

		//ʹ������shutdown���óɹ�
		int nRet = setsockopt( pAcceptKey->m_sock, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char*)&m_nListenSocket, sizeof(m_nListenSocket) );
		if (nRet == 0)	// OK
		{
			pAcceptKey->m_Lock->LOCK();
			m_pGameNet->Accept(pAcceptKey->m_sock);
			Recv( pAcceptKey->m_sock,pAcceptKey->m_WSAInBuf.buf,wSize);

			//if( AZeroByteRead(pAcceptKey) )
			{
				if(PostRecvRequiry(pAcceptKey))
				{
					pAcceptKey->m_Lock->UNLOCK();
					return true;	
				}
			}
		}	
		Break(pAcceptKey);
		pAcceptKey->m_Lock->UNLOCK();
	}	
	else
	{
		pAcceptKey->m_Lock->LOCK();
		addRemoveListKey(pAcceptKey);
		pAcceptKey->m_Lock->UNLOCK();
	}
	return false;	
}

//getquiry listenʧ�ܵ�ʱ����õĺ���
bool CIOCP::AcceptNoComplated(WSACONTEXT *pKey,SOCKET s)
{	
	//Ͷ���µ�acceptex��Ϣ	
	InterlockedDecrement( &m_AcceptingThreadCount);		
	SetEvent(m_hAcceptHanle);	

	WSACONTEXT *pClientKey = getKey(s);
	if( pClientKey )
	{
		pClientKey->m_Lock->LOCK();
		Break(pClientKey);
		addRemoveListKey(pClientKey);
		pClientKey->m_Lock->UNLOCK();
	}

	return 0;
}


ULONG WINAPI CIOCP::WorkThread(void *param)
{
#ifndef _DEBUG
	__try
#endif
	{
		CIOCP *pThis = ( CIOCP * )param;	

		ULONG			dwIoSize = 0;	
		WSACONTEXT*		pContext = NULL; 		
		LPOVERLAPPED	lpOvlpEx = NULL;	
		IOMessage*		pMsg = NULL;

		while(pThis->m_dRunFlag)
		{
			dwIoSize = 0;
			lpOvlpEx = NULL;
			pContext = NULL;		
			//bError	 = FALSE;
#ifdef X64_WIN
			BOOL state = GetQueuedCompletionStatus(pThis->m_hCompletionPort,&dwIoSize,(PULONG_PTR)&pContext,&lpOvlpEx,INFINITE);	
#else
			BOOL state = GetQueuedCompletionStatus(pThis->m_hCompletionPort,&dwIoSize,(LPDWORD)&pContext,&lpOvlpEx,INFINITE);	
#endif
			Assert(lpOvlpEx);
			Assert(pContext);
			if(!lpOvlpEx)
				continue;						

			pMsg = CONTAINING_RECORD(lpOvlpEx,IOMessage,m_ol);
			if(!pMsg)
			{
				continue;//add by david 2011��12��6��
			}

			if(!pContext)
			{
				pThis->Overlap_Free(pContext, pMsg );
				continue;
			}

			if( !state )
			{
				int dwErrors = WSAGetLastError();				
				if(pContext->m_nStatus == Key_Listen && pThis->m_dRunFlag )
				{	
					Log("Listen Socket GetQueue %d socket %d client socket %d\n",dwErrors,pContext->m_sock,pMsg->m_socket);
					pThis->AcceptNoComplated(pContext,pMsg->m_socket );
				}				
				//////////////////////////////////////////////////////////////////////////
				//�����ж���,����FALSE add by zhao
				else if(pContext->m_nStatus== Key_Work && pThis->m_dRunFlag)
				{
					//Log("socket %d ������⵽�ͻ��������ж�,WSAGetLastError:%d \n",pContext->m_sock,dwErrors);
					pContext->m_Lock->LOCK();
					pThis->Break(pContext);
					pContext->m_WriteBufferQueue.Clear();//fixed by david 2012-1-12					
					pContext->m_Lock->UNLOCK();
				}
				else
				{
					//Log("WorkThread Get Error Key(sock=%d, status=%d, breakflag=%d, error=%d)", pContext->m_sock, pContext->m_nStatus, pContext->m_BreakFlag, dwErrors);
				}
				//////////////////////////////////////////////////////////////////////////
			}
			else
			{
				//Log("�����̴߳���Ͷ������:ip=%s, sock=%d", pContext->m_szIP, pContext->m_sock);
				pContext->m_Lock->LOCK();
				pThis->ProcessIOMessage(pMsg,pContext,dwIoSize );	
				pContext->m_Lock->UNLOCK();		
			}
			pThis->Overlap_Free(pContext,pMsg );
		}	
	}
#ifndef _DEBUG
	__except (HandleException(GetExceptionInformation(), "CIOCP::WorkThread"))
	{

	}
#endif	

	return 0 ;
}

void CIOCP::RemoveStaleClient( WSACONTEXT *pKey)
{		
	if(!pKey || pKey->m_nStatus == Key_Listen || pKey->m_nStatus == Key_Free)
	{
		Log("�Ͽ�ʧ�� !pKey || pKey->m_nStatus == Key_Listen || pKey->m_nStatus == Key_Free");
		return;
	}

	removeKeyMap(pKey->m_sock);	

	pKey->m_Lock->LOCK();
//	int temp = pKey->m_sock;
	CancelIo((HANDLE)pKey->m_sock);
	m_pGameNet->Break(pKey->m_sock);
	FreeContext(pKey);
	pKey->m_Lock->UNLOCK();

	
	SetEvent(m_hAcceptMoreHandle);
	
	//Log("IOCP::CloseSocket %d", temp);
}

int CIOCP::Recv( SOCKET sock,char *buf,DWORD nSize )
{
	return m_pGameNet->Recv(sock,buf,nSize);
}

// FUNCTION:- GameNetSend
// return : 
// -1 ��ʾ socket �Ѿ��ر�
// 0  ��ʾ��������
int CIOCP::Send( SOCKET sock, char *szBuf, int nSize )
{	
	if(!szBuf)
	{
		Log("%s %d:Send szBuf null\n", __FILE__, __LINE__);
		return -1;
	}

	if(nSize <= 0)
	{
		Log("%s %d:send size=%d, socket=%d", __FILE__, __LINE__,nSize,sock);
		return -1;
	}

	WSACONTEXT *pKey = getKey(sock);
	if ( !pKey )
	{
		//Log("%s %d:getKeyʧ�ܣ�socket=%d\n", __FILE__, __LINE__, sock);
		return -1;
	}
	
	//����Ѿ��Ͽ��Ͳ������ϲ�ķ��͵���
	if(pKey->m_BreakFlag)
	{
		//Log("%s %d:socket %d ����Ϊbreak���\n", __FILE__, __LINE__, sock);
		return -1;
	}

	int res = pKey->m_WriteBufferQueue.Write( szBuf, nSize );
	if(res <= 0)
	{
		Log("IOCP˫����ʣ��ռ䲻��socket=%d, szie=%d", sock, nSize);
		return -1;
	}

	if(pKey->m_BreakFlag)
	{
		pKey->m_WriteBufferQueue.Clear();
		return -1;
	}

	return res;
}


bool CIOCP::ProcessIOMessage( const IOMessage* IOMsg,WSACONTEXT *pContext,DWORD dwIoSize,SOCKET sock)
{
	if(pContext->m_nStatus == Key_Free)
		return false;

	//Log("ProcessIOMessage:ip=%s, sock=%d, type=%d", pContext->m_szIP, pContext->m_sock, IOMsg->m_ioType);
	switch (IOMsg->m_ioType)
	{
	case IORead:
		Reading( pContext, dwIoSize );											
		break;
	case IOInitialize:		
		AcceptComplated( pContext,IOMsg->m_socket, dwIoSize );						 
		break;
	case IOWrite:
		Writing(pContext,dwIoSize);								
		break;
	/*case IOClose:
		AddRemoveSocket(pContext);
		break;*/
	case IOWriteComplete:
		WriteComplete(pContext,dwIoSize);			
		break;
	case IOConnectComplete:
		ConnectComplete(pContext,dwIoSize);		
		break;
	default:
		break;
	}
	return true;
}

//���pKey Ϊ�˼�¼ pKey����Ĺ������
// David  2010-05-19
IOMessage*	CIOCP::Overlap_Alloc(WSACONTEXT* pKey,IOType t)
{	
	if(!pKey)
		return NULL;

#ifdef _IOMSG_MEMPOOL_
	IOMessage* pIOMsg = g_IocpIOMsgPool().Alloc();
	if( !pIOMsg )
		return NULL;
	
	pIOMsg->m_ioType = t;
#else
	while(m_IOMsgCount >= m_IOMsgMax)
	{
		Warning("Alloc OverLap = NULL\n");
		Sleep(0);
	}
	
	IOMessage* pIOMsg = NULL;
	m_IOMsgLock.LOCK();
	while(true)
	{
		if(m_IOMsgTable[m_IOMsgTableIndex].m_Ref == 0)
		{				
			m_IOMsgTable[m_IOMsgTableIndex].m_Ref++;
			m_IOMsgTable[m_IOMsgTableIndex].m_ioType = t;			
			pIOMsg = &m_IOMsgTable[m_IOMsgTableIndex];	
			break;
		}	
		if(++m_IOMsgTableIndex >= m_IOMsgMax)
			m_IOMsgTableIndex = 0;
		
	}
	m_IOMsgLock.UNLOCK();

	if( !pIOMsg )
		Log("%s %d:Overlap_Alloc failed\n", __FILE__, __LINE__);
#endif

//#ifdef _DEBUG
	if(pIOMsg)
	{
		InterlockedIncrement(&m_IOMsgCount);
		switch(t)
		{
		case IORead:
			InterlockedIncrement(&m_IOReadCount);										
			break;
		case IOInitialize:
			InterlockedIncrement(&m_IOInitializeCount);						 
			break;
		case IOWrite:
			InterlockedIncrement(&m_IOWriteCount);								
			break;
		case IOClose:
			InterlockedIncrement(&m_IOCloseCount);			
			break;
		case IOWriteComplete:
			InterlockedIncrement(&m_IOWriteCompleteCount);			
			break;
		default:
			break;
		}		
	}
//#endif	
	InterlockedIncrement(&pKey->m_IOMsgPending);	
	return pIOMsg;
}

void CIOCP::Overlap_Free(WSACONTEXT* pKey,IOMessage* pMsg)
{
	if(!pMsg || !pKey)
		return;


//#ifdef _DEBUG
	switch(pMsg->m_ioType)
	{
	case IORead:
		InterlockedDecrement(&m_IOReadCount);										
		break;
	case IOInitialize:
		InterlockedDecrement(&m_IOInitializeCount);						 
		break;
	case IOWrite:
		InterlockedDecrement(&m_IOWriteCount);								
		break;
	case IOClose:
		InterlockedDecrement(&m_IOCloseCount);			
		break;
	case IOWriteComplete:
		InterlockedDecrement(&m_IOWriteCompleteCount);			
		break;
	default:
		break;
	}		
	InterlockedDecrement(&m_IOMsgCount);
//#endif

#ifdef _IOMSG_MEMPOOL_		
	g_IocpIOMsgPool().Free( pMsg );
#else
	pMsg->Init();
#endif			
	InterlockedDecrement(&pKey->m_IOMsgPending);	
}

BOOL CIOCP::SetIOComplete(WSACONTEXT *pKey)
{
	if(!CreateIoCompletionPort((HANDLE)pKey->m_sock,m_hCompletionPort,(ULONG)pKey,0))
	{
		Assert(0);
		Warning("Err:failed to create complete port %d socket %d\n",GetLastError(),pKey->m_sock);							
		return FALSE;
	}	
	return TRUE;
}

bool CIOCP::PostRecvRequiry(WSACONTEXT* pKey)
{
	if(!pKey)
		return false;

	//����Ѿ��Ͽ��Ͳ���Ͷ�ݶ�����  By David 2010-05-19
	if(pKey->m_BreakFlag)
	{
		Log("PostRecvRequiry break flag = true");
		Break(pKey);
		return false;
	}

	IOMessage* pIOMsg = Overlap_Alloc(pKey,IORead);
	Assert(pIOMsg);
	if(!pIOMsg)
	{
		Log("PostRecvRequiry can't Alloc IOMessage");
		Break(pKey);
		return false;
	}

	ULONG wSize = 0;
	ULONG lpFlags = MSG_PARTIAL;
	
	pKey->m_WSAInBuf.buf = pKey->m_RecvBuff;
	pKey->m_WSAInBuf.len = pKey->m_RecvBuffSize;
	pIOMsg->m_socket	 = pKey->m_sock;

	int nRetVal = WSARecv(pKey->m_sock,&pKey->m_WSAInBuf,1,&wSize,&lpFlags,&pIOMsg->m_ol,NULL);	

	if( nRetVal == SOCKET_ERROR )
	{
		DWORD error = WSAGetLastError();								
		if(error != WSA_IO_PENDING)
		{
			Log(" +-PostRecvRequiry Error %d socket %d!\n",error,pKey->m_sock);
			Overlap_Free(pKey,pIOMsg);
			Break(pKey);
			return false;
		}		
	}


	return true;
}
