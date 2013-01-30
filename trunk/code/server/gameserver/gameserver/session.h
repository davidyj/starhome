#include "stdafx.h"
#include "NetBuffer.h"
#include "memorypool.h"
#include "utlmap.h"

class CSession
{
public:
	CSession();
	~CSession();

	int recv(char* buf,int size);

protected:
	SOCKET m_socket;
	CUtlBuffer m_msgbuffer;
};

typedef CClassMemoryPool<CSession> SesseionPool;

class CSessionMgr
{
public:
	CSessionMgr();
	~CSessionMgr();

	static CSessionMgr &getSingle()
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