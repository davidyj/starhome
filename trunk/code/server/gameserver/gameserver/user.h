#include "stdafx.h"
#include "utlsymbol.h"
#include "utlmap.h"

class CUser
{
public:
	CUser();
	~CUser();

public:
	CUtlSymbol m_name;
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