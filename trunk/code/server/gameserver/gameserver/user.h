#include "stdafx.h"
#include "utlsymbol.h"
#include "utlmap.h"
#include "npc.h"
#include "build.h"

class CUser
{
public:
	CUser();
	~CUser();

public:
	CNPC* createNPC(const char* name);
	CNPC* destroyNPC(CNPC* pNPC);
	
	bool addNPC(CNPC* pNPC);
	bool removeNPC(CNPC* pNPC);
	CNPC* getNPC(const char* name);

public:
	CUtlLinkedList<CNPC*>	m_NPCList;
};

typedef CMemoryPool<CUser> UserPool;

class CUserMgr
{
public:
	CUserMgr();
	~CUserMgr();

	static CUserMgr &getsingle()
	{
		static CUserMgr mgr;
		return mgr;
	}

public:
	bool	init();

	CUser*	create();
	void	destroy(CUser* pUser);

	bool	add(CUser* pUser);
	void	remove(CUtlSymbol id);

	CUser* get(CUtlSymbol id);

protected:
	CUtlMap<CUtlSymbol,CUser*>	m_UserMap;
	UserPool		m_UserPool;
};