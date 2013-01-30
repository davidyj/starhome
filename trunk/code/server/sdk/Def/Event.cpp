#include "StdAfx.h"
#include "Event.h"
#include "ThreadLibFunctions.h"

Event* MakeEvent(Event_ID nEventID,PersonID PID,SCENEID SID, int64 nParam1, int64 nParam2, int64 nParam3, int64 nParam4,int64 nParam5,int64 nParam6,char* szParam1,BOOL bUpdateDB)
{
	Event* pEvent = EventPool().Alloc();
	if(pEvent)
	{
		if ( pEvent->m_bIsUsing )
		{
			//assert(0);//--使用了一个已经分配过的内存--
			//Log("MakeEvent使用了一个已经分配过的内存！EventID == %d,PID = %I64d",nEventID,PID);
		}
		pEvent->Create(nEventID,PID,SID,nParam1,nParam2,nParam3,nParam4,nParam5,nParam6,szParam1,bUpdateDB);
	}
	return pEvent;
}

Event* MakeEvent(Event* pEvent)
{
	Event* pNewEvent = EventPool().Alloc();//g_AllocEvent();
	*pNewEvent = *pEvent;
	return pNewEvent;
}

CEventPool& EventPool()
{
	static CEventPool pool;
	return pool;
}
//////////////////////////////////////////////////////////////////////////
//
Event::Event()
{
	m_nEventID	= Event_INVALID;
	m_nPID		= INVALID_PID;
	m_nSceneID	= INVALID_SCENEID;
	m_nParam[0] = 0;
	m_nParam[1] = 0;
	m_nParam[2] = 0;
	m_nParam[3] = 0;
	m_nParam[4] = 0;
	m_nParam[5] = 0;
	memset(m_szParam,0,sizeof(char)*SHORT_STRING_LEN);
	m_bUpdateDB = FALSE;
	m_bIsUsing = FALSE;

}

Event::~Event()
{
}

//////////////////////////////////////////////////////////////////////////
//
CEventPool::CEventPool()
{
	m_EventTableIndex = 0;
	m_EventPoolSize = 0;
}

CEventPool::~CEventPool()
{
	Release();
}

bool CEventPool::Create(int nPoolSize)
{
	m_EventPoolSize = nPoolSize;


    if(m_EventPoolSize	> 0)
		m_EventTable = new Event[m_EventPoolSize];//(Event*)Plat_Alloc(sizeof(Event) * m_EventPoolSize);
	//for(int i=0;i<m_EventPoolSize;i++)
	//	NEW(&m_EventTable[i]) Event;

	return true;
}

void CEventPool::Release()
{
	SAFE_DELETE_ARRAY(m_EventTable);
}

Event* CEventPool::Alloc()
{
	//if(++m_EventTableIndex >= m_EventPoolSize)
	//	m_EventTableIndex = 0;
	//return (Event*)&m_EventTable[m_EventTableIndex];

	ULONG tmpidx = ThreadLib::LocketAdd((volatile LONG *)&(m_EventTableIndex),1);
	return  (Event*)&m_EventTable[tmpidx%m_EventPoolSize];
}

