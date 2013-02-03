#include "StdAfx.h"
#include "baseentity.h"

class CWorld : public CBaseEntity
{
public:
	CWorld();
	~CWorld();

	static CWorld& getsingle()
	{
		static CWorld obj;
		return obj;
	}
};

