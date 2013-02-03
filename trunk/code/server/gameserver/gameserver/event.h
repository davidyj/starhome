#include "stdafx.h"

class CEvent
{
public:
	CEvent();
	~CEvent();

public:
	CUtlSymbol	m_id;
	int			m_param[4];
};

typedef CClassMemoryPool<CEvent>	EventPool;

class CEventMangaer
{
public:
	CEventMangaer();
	~CEventMangaer();

	static CEventMangaer& getsingle()
	{
		static CEventMangaer mgr;
		return mgr;
	}

public:
	CEvent* create(const char* key,int param1,int param2,int param3,int param4);
	void	destroy(CEvent* pEvent);
};