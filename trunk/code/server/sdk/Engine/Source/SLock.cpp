#include "../stdafx.h"
#include "SLock.h"
#ifndef WIN32
#include <pthread.h>

#endif

//=====================================================
SCritSect::SCritSect( )
{
#ifdef WIN32	
	InitializeCriticalSection( &m_opaqueData );
#else
	pthread_mutex_init(&mtx, NULL);
#endif	
}

SCritSect::~SCritSect( )
{
#ifdef WIN32	
	DeleteCriticalSection( &m_opaqueData );
#else
	pthread_mutex_destroy(&mtx);
#endif
}

void SCritSect::Enter( )
{
#ifdef WIN32	
	EnterCriticalSection( &m_opaqueData );
#else
	pthread_mutex_lock(&mtx);
#endif	
}

void SCritSect::Leave( )
{
#ifdef WIN32	
	LeaveCriticalSection( &m_opaqueData );
#else
	pthread_mutex_unlock(&mtx);
#endif	
}

//=====================================================
SEvent::SEvent(BOOL bManualReset, BOOL bInitialState )
{
#ifdef WIN32	
	m_hHandle = 0;
	m_hHandle = CreateEvent( NULL, bManualReset, bInitialState, NULL );
#else
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&cond, NULL);
#endif	
}

SEvent::~SEvent( )
{
#ifdef WIN32	
	if ( m_hHandle != 0 )
	{
		CloseHandle( m_hHandle );
	}
#else
	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond);

#endif	
}

DWORD SEvent::Wait( ULONG timeoutMs )
{
#ifdef WIN32	
	return WaitForSingleObject( m_hHandle, timeoutMs );
#else
	//reference file : Engine/Include/POSIX/GLock_.h	
	if (!timeoutMs) {
		pthread_mutex_lock(&mtx);
		pthread_cond_wait(&cond, &mtx);
		pthread_mutex_unlock(&mtx);
		return WAIT_OBJECT_0;

	}else {
		struct timespec abstime;
		int nsec = (timeoutMs % 1000);
		abstime.tv_sec = time(NULL) + (timeoutMs - nsec)/1000;
		abstime.tv_nsec = nsec*1000*1000;


		int result = 0;
		pthread_mutex_lock(&mtx);
		result = pthread_cond_timedwait(&cond, &mtx, &abstime);
		pthread_mutex_unlock(&mtx);
		if (!result) {
			return WAIT_OBJECT_0;
		}else {
			return WAIT_TIMEOUT;
		}

	}		
#endif	
}

BOOL SEvent::Set( )
{
#ifdef WIN32	
	return SetEvent( m_hHandle );
#else
	pthread_cond_broadcast(&cond);
#endif	
}

BOOL SEvent::Reset( )
{
#ifdef WIN32	
	return ResetEvent( m_hHandle );
#endif	
}

//=======================================
#ifdef WIN32
HANDLE SCreateThread(unsigned long dwStackSize, 
		LPTHREAD_START_ROUTINE  lpStartAddress, 
		void * lpParameter, 
		unsigned long dwCreationFlags, 
		DWORD * lpThreadId, 
		char * threadName)
{

	return CreateThread( NULL, 0, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId ); 

}


HANDLE SCreateThread(LPTHREAD_START_ROUTINE  lpStartAddress, 
		void * lpParameter, 
		DWORD * lpThreadId, 
		void * linuxData, 
		char * threadName)
{
	return SCreateThread( 0, 
			lpStartAddress,
			lpParameter,
			0,
			lpThreadId,
			threadName);



}
#endif

SThread::SThread( )
{
	m_hHandle = 0;
}

SThread::~SThread( )
{	
#ifdef WIN32	
	if ( m_hHandle != 0 )
	{
		CloseHandle( m_hHandle );
	}
#else
//Here we'd better not use pthread_kill to stop the thread	
#endif	
}

DWORD SThread::Wait( ULONG timeoutMs )
{
#ifdef WIN32		
	return WaitForSingleObject( m_hHandle, timeoutMs );
#else
	if (!pthread_join(m_hHandle, NULL)){ //succ
		WAIT_OBJECT_0;
	}else {	
		WAIT_TIMEOUT;
	}	
#endif
}

int SThread::Create( LPTHREAD_START_ROUTINE ThreadProc, void *param, SThread & Thread, char *ThreadName )
{
#ifdef WIN32	
	DWORD id;
//	int ret = 0;
	HANDLE handle = SCreateThread( ThreadProc, param,  &id, NULL, NULL );
	Thread.m_hHandle = handle;
	return (handle == 0);
#else
	if (!pthread_create(&(Thread.m_hHandle), NULL, ThreadProc, param)){
		return 1;
	}else {
		return 0;
	}	
#endif
}
