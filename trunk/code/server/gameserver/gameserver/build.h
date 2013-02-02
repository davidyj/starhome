#include "stdafx.h"
#include "utlsymbol.h"

class CBuild
{
public:
	CBuild();
	~CBuild();

	void logic(int timer);

protected:
	CUtlSymbol	m_name;
	CUtlSymbol	m_username;
	int			m_level;

};

typedef CClassMemoryPool<CBuild>	BuildPool;

class CBuildMgr
{
public:
	CBuildMgr();
	~CBuildMgr();

	static CBuildMgr &getsingle()
	{
		static CBuildMgr mgr;
		return mgr;
	}

public:
	bool	init();

	CBuild* create();
	void	destroy(CBuild* pBuild);	
};

static int 