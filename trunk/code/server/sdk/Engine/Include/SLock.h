#pragma once
#include "../../Port/config.h"
#include "EngineDefine.h"
#ifndef  WIN32
#include <pthread.h>
#endif

class ENGINE_CLASS SCritSect
{
public:
	SCritSect( );
	~SCritSect( );
	void Enter( );
	void Leave( );
private:
#ifdef WIN32
	CRITICAL_SECTION m_opaqueData;
#else
	pthread_mutex_t mtx;
#endif	
};

#ifndef WIN32	//	2010-12-2	li9chuan
#define INFINITE	0xFFFFFFFF
#endif

class SEvent 
{
public:
	SEvent( BOOL bManualReset, BOOL bInitialState );
	~SEvent( );

	/*
	 * wait timeoutMs milliseconds
	 */
	DWORD Wait( ULONG timeoutMs );
	BOOL  Set( );
	BOOL  Reset( );

protected:
#ifdef WIN32	
	HANDLE m_hHandle;
#else
	pthread_mutex_t mtx;
	pthread_cond_t cond;

#endif
};

#ifndef WIN32
typedef void * (*LPTHREAD_START_ROUTINE)(void *);
#endif
class ENGINE_CLASS SThread
{
public:
	SThread( );
	~SThread( );

	/*
	 * on POSIX, timeoutMs parameter is useless.
	 */
	DWORD Wait( ULONG timeoutMs );

	/*
	 * on POSIX, ThreadName is useless.
	 * return value:whether create thread success
	 */
	static int Create(LPTHREAD_START_ROUTINE  ThreadProc, void *param, SThread & Thread, char *ThreadName );
private:
#ifdef WIN32	
	HANDLE m_hHandle;
#else	
	pthread_t m_hHandle;
#endif	
};
