#include "stdafx.h"
#include "baseentity.h"

class CBuildTemplate : public CBaseEntity
{
public:
	CBuildTemplate();
	~CBuildTemplate();

};

class CBuildTemplateMgr
{
public:
	CBuildTemplateMgr();
	~CBuildTemplateMgr();

	static CBuildTemplateMgr& getsingle()
	{
		static CBuildTemplateMgr mgr;
		return mgr;
	}

public:
	void setInt(const char* buildname,const char* k,int v);
	int	 getInt(const char* buildname,const char* k);

	void setInt64(const char* buildname,const char* k,int64 v);
	int64 getInt64(const char* buildname,const char* k);

	void setString(const char* buildname,const char* k,const char* v);
	const char* getString(const char* buildname,const char* k);

protected:
	CUtlDict<CBuildTemplate*,byte>		m_BuildTemplate;
};


static