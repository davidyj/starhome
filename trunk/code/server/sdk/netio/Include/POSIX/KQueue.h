#ifndef KQUEUE_H
#define KQUEUE_H
#include "../../Port/config.h"

#include "utllinkedlist.h"
#include "utlmap.h"
#include "GLock.h"
//#include "pthread.h"
#include "NetBuffer.h"
#include "Gamenetcommondefine.h"
#include "Net.h"
#include "SelectIO.h"

#include <pthread.h>
#include <map>

#define KEVENT_MAX_COUNT	4096
#define RECV_BUFFER_MAX		1024
//#define LISTEN_BACKLOG	10
static int kqueue_send_buff_size = 20480000;
static int kqueue_send_timeout = 8192;

struct SocketContext
{
	int		m_sock;
	char		m_szIP[25];
	unsigned 	m_ip;
	unsigned	m_port;

	//CNetBufferQueue	m_WriteBufferQueue;
	CWDoubleBuff	m_WriteBufferQueue;
	void Final(){
	}
	SocketContext(){
		m_sock = INVALID_SOCKET;
		//memset(m_szIP, 0, sizeof(m_szIP));
		m_szIP[0] = '\0';
		m_ip = 0;
		m_port = 0;
		m_WriteBufferQueue.Create(kqueue_send_buff_size,kqueue_send_timeout);
	}
};


SocketContext *MakeSocketContext(void);
void  FreeSocketContext(SocketContext *key);


typedef std::map<int, SocketContext*> KQueueSockets;
typedef CUtlLinkedList<int,int>	intLIST;

class CGameNet;
class CKQueue : public CNet
{
public:
	CKQueue(CGameNet* pGameNet);
	virtual ~CKQueue();

	virtual BOOL	Begin(int nPort);
	virtual void	End();

	virtual int	Connect( const char *szIP, ULONG port);
	virtual int	Recv( int sock,char *szBuf,int nSize );
//	virtual int	Send( int sock,PACKET_COMMAND* pPacket);
	virtual int	Send( SOCKET sock, char *szBuf, int nSize );
	virtual void	Break( int sock );
	virtual char*	IP(SOCKET sock);

protected:

	void RemoveSocketList( int sock );
	inline void SetSocketContext( int sock,SocketContext* ctx)
	{
		CLockGuard  guard(&m_SocketsLock);
		std::map<int, SocketContext *>::iterator it = m_Sockets.find(sock);
		if (it == m_Sockets.end())
			m_Sockets.insert(KQueueSockets::value_type(sock, ctx));
	}
	inline int GetSocketCount()
	{
		CLockGuard guard(&m_SocketsLock);
		return m_Sockets.size();
	}
	inline SocketContext* GetSocketContext( int sock)
	{
		CLockGuard guard(&m_SocketsLock);
		SocketContext* ctx= NULL;
		std::map<int, SocketContext *>::iterator it = m_Sockets.find(sock);
		if(it != m_Sockets.end())
			ctx = it->second;
		return ctx;
	}
	inline SocketContext *RemoveSocketContex(int sock)
	{
		SocketContext *ctx = NULL;
		CLockGuard guard(&m_SocketsLock);
		std::map<int, SocketContext *>::iterator it = m_Sockets.find(sock);
		if( it != m_Sockets.end())
		{
			ctx = it->second;
			m_Sockets.erase(it);
		}
		return ctx;
	}

	int 	CreateListenSocket();
	int 	HandleAccept(int cnt);
	int 	Reading(int fd, int size);
	int 	Writing(int fd);

	void 	FreeSockets()
	{
		CLockGuard guard(&m_SocketsLock);
		std::map<int, SocketContext*>::iterator it = m_Sockets.begin();
		for(; it != m_Sockets.end(); ++it)
		{
			if (it->second)
				FreeSocketContext(it->second);
			m_Sockets.erase(it);
		}
	}

	void AddReadableEvent(SocketContext *key);
	void AddWriteableEvent(int sockfd);
	void RemoveReadableEvent(int sockfd);
	void RemoveWriteableEvent(int sockfd);
	static void *ThreadMain(void *Param);

protected:
	bool	m_StarFlag;

	CGLock m_SocketsLock;
	KQueueSockets m_Sockets;

	int 	m_nListenPort;
	int		m_nListenSocket;

	CGameNet*	m_pGameNet;
	pthread_t 	m_KQueueThrId;

	int 		m_Kqueuefd;
	unsigned int 	m_EvCount;

};
#endif
