#pragma once
#include <winsock2.h>
#include <mswsock.h>
#include "utllinkedlist.h"
#include "netbuffer.h"
#include "utlmap.h"
#include "Net.h"
#include "glock.h"
#include "gamenetcommondefine.h"
#include "SocketHashTable.h"
#include "GlobalConst.h"


//////////////////////////////////////////////////////////////////////////
// struct of Socket Obj
enum IOType 
{
	IONULL,
	IOInitialize,		// Accept完成
	IORead,				// Recv
	IOWrite,			// Send
	IOIdle,				// 等待发送结果状态
	IOClose,			// 关闭
	IOConnectComplete,	// Connect完成
	IOWriteComplete,	// 发送完成
};

// 投递操作的结构体
struct  IOMessage 
{
	OVERLAPPED	m_ol;
	IOType		m_ioType;	
	SOCKET		m_socket;	
	int			m_Ref;

	IOMessage()
	{
		/*m_ioType	= IONULL;	
		m_socket	=INVALID_SOCKET;		
		memset(&m_ol,0,sizeof(OVERLAPPED));*/
	}
	~IOMessage()
	{
		m_ioType	= IONULL;	
		m_socket	=INVALID_SOCKET;		
		memset(&m_ol,0,sizeof(OVERLAPPED));
	}	
	void Init()
	{
		m_Ref		= 0;
		m_ioType	= IONULL;	
		m_socket	=INVALID_SOCKET;		
		memset(&m_ol,0,sizeof(OVERLAPPED));
	}
};

enum Key_Status
{
	Key_Free		= 0,		//空闲状态
	Key_Listen,					//监听状态
	Key_Accept,					//Accept
	Key_Work,					//工作状态
	
};
class WSACONTEXT 
{	
public:
	WSACONTEXT();
	~WSACONTEXT();

	void Create(int nRecvBuffSize,int nSendBuffSize,int nTimeout);
	bool Init();
	void Release();

public:
	Key_Status	m_nStatus;					// Socket的状态
	bool		m_WriteCompleteFlag;		// 是否发送完成的标记
	volatile bool		m_BreakFlag;				// Break标识
	SOCKET		m_sock;						// socket 句柄
	LONG		m_IOMsgPending;				// 发送的请求次数	
	int			m_RecvBuffSize;				// 接受内存的大小
	CGLock*		m_Lock;
	WSABUF		m_WSAInBuf;					// socket 接收数据缓冲	
	WSABUF		m_WSAOutBuf;				// socket 发送的地址			
	char*		m_RecvBuff;					// 接收数据的缓冲区
	char		m_szIP[25];					// 玩家的ip地址
	CWDoubleBuff	m_WriteBufferQueue;	
	//DWORD		m_BreakTime;				// break操作的时间

	//LONG m_LClientSocketByte;
	//LONG m_LLastByte;

};


class	CGameNet;
struct	PACKET_COMMAND;

class CIOCP : public CNet
{
public:
	CIOCP(CGameNet* pGameNet);
	virtual ~CIOCP();

public:
	virtual BOOL	Begin(int nPort,int nPacketPoolSize,int nConnecMax,int nRecvBuffSize,int nSendBuffSize,int nTimeout,int nAcceptCount);
	virtual void	End();			
	
	virtual SOCKET	Connect( const char *szIp,DWORD nPort);	
	virtual void	ShutDown( SOCKET sock );
	virtual int		Send( SOCKET sock, char *szBuf, int nSize );
	virtual char*	IP(SOCKET sock);

protected:	
	virtual void	Break( WSACONTEXT *pKey );
	virtual int		Recv( SOCKET sock,char *buf,DWORD nSize );

	WSACONTEXT* 	GetFreeKey(Key_Status nStatus);	
	void			FreeContext(WSACONTEXT* pKey);

	BOOL			SetIOComplete(WSACONTEXT *pKey);
	bool			AcceptThread();		

	bool			ProcessIOMessage(const IOMessage* IOMsg,WSACONTEXT *pContext,DWORD nSize,SOCKET sock = INVALID_SOCKET);
	bool			PostRecvRequiry(WSACONTEXT* pKey);

	uint			Reading(WSACONTEXT* pContext,uint nSize);
	bool			Writing(WSACONTEXT* pContext,uint nSize);
	bool			WriteComplete(WSACONTEXT* pContext,uint nSize);
	int				ConnectComplete(WSACONTEXT* pContext,int nSize);	
	void			RemoveStaleClient(WSACONTEXT *pKey);
	bool			AcceptComplated(WSACONTEXT *pKey,SOCKET s,DWORD wSize);
	bool			AcceptNoComplated(WSACONTEXT *pKey,SOCKET s);
	
	static DWORD WINAPI MainThread( LPVOID pParam );
	static DWORD WINAPI WorkThread( LPVOID pParam );
	static DWORD WINAPI SwitchThread(LPVOID pParam);					//双缓冲交换的线程
	static DWORD WINAPI RemoveSocketThread(LPVOID pParam);				//回收socket的线程

	IOMessage*		Overlap_Alloc(WSACONTEXT* pKey,IOType t);
	void			Overlap_Free(WSACONTEXT* pKey,IOMessage* pOverlap);		
	
	void			AddRemoveSocket(WSACONTEXT* pKey);

	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	inline bool     addWorkListKey(WSACONTEXT* pKey)
	{
		if(!pKey)
			return false;
		m_WorkKeyLock.LOCK();
		int index = m_WorkKeyList.Find(pKey);
		if(m_WorkKeyList.IsValidIndex(index))
		{
			Log("向工作链表中添加key失败!(sock=%d)", pKey->m_sock);
			m_WorkKeyLock.UNLOCK();
			return false;
		}
		//Log("IOCP::WorkListKey Add %d", pKey->m_sock);
		m_WorkKeyList.AddToTail(pKey);
		m_WorkKeyLock.UNLOCK();
		return true;
	}
	
	inline void		removeWorkListKey(WSACONTEXT* pKey)
	{
		if(!pKey)
			return;
		m_WorkKeyLock.LOCK();
		int index = m_WorkKeyList.Find(pKey);
		if(!m_WorkKeyList.IsValidIndex(index))
		{
			Log("从工作链表中删除key失败!(sock=%d)", pKey->m_sock);
			m_WorkKeyLock.UNLOCK();
			return;
		}
		m_WorkKeyList.Remove(index);
		m_WorkKeyLock.UNLOCK();
	}
	
	inline WSACONTEXT*	getHeadWorkListKey(int& index)
	{
		WSACONTEXT* pContext = NULL;
		m_WorkKeyLock.LOCK();
		index = m_WorkKeyList.Head();
		if(m_WorkKeyList.IsValidIndex(index)){
			pContext = m_WorkKeyList.Element(index);
			m_WorkKeyList.Remove(index);
			//Log("IOCP::WorkListKey Del %d", pContext->m_sock);
		}
		m_WorkKeyLock.UNLOCK();
		return pContext;
	}
	
	// remove list opertion
	inline bool     addRemoveListKey(WSACONTEXT* pKey)
	{
		if(!pKey)
		{
			Log("添加RemoveSocketList失败");
			return false;
		}
		m_RemoveSocketLocked.LOCK();
		int index = m_RemoveSocketList.Find(pKey);
		if(m_RemoveSocketList.IsValidIndex(index))
		{
			m_RemoveSocketLocked.UNLOCK();
			Log("重复添加RemoveSocketList(sock=%d)", pKey->m_sock);
			return false;
		}
		//Log("IOCP::RemoveListKey Add %d", pKey->m_sock);
		m_RemoveSocketList.AddToTail(pKey); 
		m_RemoveSocketLocked.UNLOCK();
		m_RemoveEvent.Event();
		return true;
	}
	inline WSACONTEXT*	getHeadRemoveListKey()
	{
		WSACONTEXT* pContext = NULL;
		m_RemoveSocketLocked.LOCK();
		int index = m_RemoveSocketList.Head();
		if(m_RemoveSocketList.IsValidIndex(index)){
			pContext = m_RemoveSocketList.Element(index);
			m_RemoveSocketList.Remove(index);
			//Log("IOCP::RemoveListKey Del %d", pContext->m_sock);
		}
		m_RemoveSocketLocked.UNLOCK();		
		return pContext;
	}

	//key map operation add by david 2011-12-11
	inline bool addKeyMap(WSACONTEXT* pKey){
		m_KeyMapLock.LOCK();
		int idx = m_KeyMap.Find(pKey->m_sock);
		if( m_KeyMap.IsValidIndex(idx) )
		{
			Log("m_KeyMap.IsValidIndex");
			m_KeyMapLock.UNLOCK();
			return false;
		}
		m_KeyMap.Insert(pKey->m_sock,pKey);
		m_KeyMapLock.UNLOCK();
		InterlockedIncrement(&m_KeyUsedCount);
		return true;
	}

	inline bool removeKeyMap(SOCKET sock){
		m_KeyMapLock.LOCK();
		m_KeyMap.Remove(sock);
		m_KeyMapLock.UNLOCK();
		InterlockedDecrement(&m_KeyUsedCount);
		return true;
	}

	WSACONTEXT* CIOCP::getKey(SOCKET s)
	{
		WSACONTEXT* pKey = NULL;
		m_KeyMapLock.LOCK();
		int index = m_KeyMap.Find(s);
		if(m_KeyMap.IsValidIndex(index))
			pKey = m_KeyMap.Element(index);
		m_KeyMapLock.UNLOCK();
		return pKey;
	}
public:
	HANDLE			m_hCompletionPort;		//完成端口句柄
	HANDLE        g_WaitableTimer;

	static int		m_nRecvBuffSize;		//接受消息缓冲
	static int		m_nSendBuffSize;		//发送消息缓冲
	static int		m_nTimeout;				//超时

	LONG			m_nConnectMax;
	int				m_IOMsgMax;
	LONG			m_IOMsgCount;
	LONG			m_KeyUsedCount;
	LONG			m_LLimitByte;
	LONG			m_AcceptingThreadCount;
	
//#ifdef _DEBUG
	LONG			m_IOReadCount;
	LONG			m_IOWriteCount;
	LONG			m_IOInitializeCount;
	LONG			m_IOCloseCount;
	LONG			m_IOWriteCompleteCount;
//#endif

protected:
	int				m_AcceptThreadMax;
	int				m_nListenPort;			//监听端口	
	SOCKET			m_nListenSocket;		//
	int				m_nPacketPoolSize;		//消息池大小

	bool			m_dRunFlag;				// 是否运营的标识	
	BYTE			m_dProcessCounts;
	HANDLE			m_hAcceptHanle;			// accept 完成的事件
	HANDLE			m_hAcceptMoreHandle;	// WsaEventSelect事件,表示目前的accept线程数已经不能满足需求
	LPFN_GETACCEPTEXSOCKADDRS m_pGetAcceptExSockaddrs;	// Get GetAcceptExSockaddrs addr	

	CGLock			m_FreeListLock;			
	CGLock			m_IOMsgLock;
	CGEvent			m_RemoveEvent;

	CUtlMap<SOCKET,WSACONTEXT*,int> m_KeyMap;				// Key的hast table
	CGLock			m_KeyMapLock;
	
	IOMessage*		m_IOMsgTable;	
	LONG			m_IOMsgTableIndex;

	WSACONTEXT*		m_KeyTable;
	LONG			m_KeyTableIndex;
	CGLock			m_RemoveSocketLocked;
	CGLock			m_WorkKeyLock;
	CUtlLinkedList<WSACONTEXT*>		m_WorkKeyList;
	CUtlLinkedList<WSACONTEXT*>		m_RemoveSocketList;		//回收socket的队列
private:
	CGameNet*		m_pGameNet;
};


