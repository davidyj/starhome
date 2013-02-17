#include "NetBuffer.h"
#include "memorypool.h"
#include "utlmap.h"
#include "utlsymbol.h"

class CSession
{
public:
	CSession();
	~CSession();

	int		accept(SOCKET s);
	void	break(SOCKET s);

	int		send(char* buf,int size);
	int		recv(char* buf,int size);

protected:
	SOCKET		m_socket;
	CUtlBuffer	m_msgbuffer;
	CUtlSymbol	m_usernameid;
};

typedef CClassMemoryPool<CSession> SesseionPool;

class CSessionMgr
{
public:
	CSessionMgr();
	~CSessionMgr();

	static CSessionMgr &getsingle()
	{
		CSessionMgr mgr;
		return mgr;
	}

public:
	bool	init(int nCount);
	CSession* create(SOCKET sock);
	void	destroy(CSession* pSession);

	bool	add(CSession* pSession);
	void	remove(SOCKET sock);

	CSession* get(SOCKET sock);

protected:
	CUtlMap<SOCKET,CSession*>		m_SessionMap;
};