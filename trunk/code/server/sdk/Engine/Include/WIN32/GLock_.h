#pragma once

class CGLock
{
public:
	CGLock::CGLock()
	{
		InitializeCriticalSection(&m_lock);
	}

	CGLock::~CGLock()
	{
		DeleteCriticalSection(&m_lock);
	}
	inline void LOCK(){EnterCriticalSection(&m_lock);}
	inline void UNLOCK(){LeaveCriticalSection(&m_lock);}

	CRITICAL_SECTION m_lock;
};



class CGEvent
{
public:
	CGEvent::CGEvent()
	{
		m_Event = CreateEvent(NULL,FALSE,FALSE,NULL);
	}
	CGEvent::~CGEvent()
	{
		CloseHandle(m_Event);
	}

	inline void Event(){SetEvent(m_Event);}
	inline int Wait(){return WaitForSingleObject(m_Event,INFINITE);}
	inline int Wait(int millisecond){return WaitForSingleObject(m_Event,millisecond);}

protected:
	HANDLE m_Event;
};


class CGCount
{
public :
	CGCount::CGCount()
	{
		m_Index = 0;
	}
	CGCount::~CGCount()
	{
	}
	
	inline CGCount& operator++(int)
	{
		InterlockedIncrement(&m_Index);
		return (*this);
	}
	inline CGCount& operator--(int)
	{
		InterlockedDecrement(&m_Index);
		return(*this);
	}
	int Get()
	{
		return m_Index;
	}

protected:
	long m_Index;
};