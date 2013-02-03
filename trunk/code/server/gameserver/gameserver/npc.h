#include "stdafx.h"
#include "baseentity.h"
#include "Event.h"



class CNPC : public CBaseEntity
{
public:
	CNPC();
	~CNPC();

public:
	void logic(int timer);
	void triger(CEvent* pEvent);

protected:
	CUtlSymbol	m_username;
};

typedef CClassMemoryPool<CNPC>	NPCPool;

class CNPCManager
{
public:
	CNPCManager();
	~CNPCManager();

	static CNPCManager getsingle()
	{
		static CNPCManager mgr;
		return mgr;
	}

public:
	bool init(int nCountMax);

	CNPC* create();
	void destroy(CNPC* pNPC);
};

static int lua_register_npc(int id);
static int lua_set_int(const char*job,const char* key,int value);
static int lua_set_string(const char* job,const char* key,const char* value);
static int lua_get_int(const char* job,const char* key);
static char* lua_get_string(const char* job,const char* key);