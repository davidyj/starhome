#include "stdafx.h"
#include "baseentity.h"

class CEntity : public CBaseEntity
{
public:
	CEntity();
	~CEntity();

public:
	


protected:	
};

typedef CClassMemoryPool<CEntity>	EntityPool;

class CEntityMgr
{
public:
	CEntityMgr();
	~CEntityMgr();

	static CEntityMgr &getsingle()
	{
		static CEntityMgr mgr;
		return mgr;
	}

public:
	void		init(int count);

	CEntity*	create();
	void		destroy(CEntity* pEntity);

protected:
	EntityPool	m_pool;
};