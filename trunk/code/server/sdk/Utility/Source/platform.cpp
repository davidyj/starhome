//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================

#include "stdafx.h"
#include "platform.h"
#include "memalloc.h"
#include "dbg.h"

// memdbgon must be the last include file in a .cpp file!!!
//#include "memdbgon.h"

//////////////////////////////////////////////////////
////
////		2010-11-26		li9chuan
////
//////////////////////////////////////////////////////
//#ifdef WIN32
//
//	static LARGE_INTEGER g_PerformanceFrequency;
//	static LARGE_INTEGER g_MSPerformanceFrequency;
//	static LARGE_INTEGER g_ClockStart;
//
//#else
//
//#endif

static uint64 g_PerformanceFrequency = 0;
static uint64 g_MSPerformanceFrequency;
static uint64 g_ClockStart;

static void InitTime()
{
	//if( !g_PerformanceFrequency.QuadPart )
	//{
	//	QueryPerformanceFrequency(&g_PerformanceFrequency);
	//	g_MSPerformanceFrequency.QuadPart = g_PerformanceFrequency.QuadPart / 1000;
	//	QueryPerformanceCounter(&g_ClockStart);
	//}


	if( !g_PerformanceFrequency )
	{
#ifdef WIN32

		QueryPerformanceFrequency((LARGE_INTEGER*)(&g_PerformanceFrequency));
		g_MSPerformanceFrequency = g_PerformanceFrequency / 1000;
		QueryPerformanceCounter((LARGE_INTEGER*)(&g_ClockStart));
#else

        struct timeval t;

        // get the time of day
        gettimeofday( &t, 0 );

        // calculate the number of milliseconds represented by the seconds
        g_ClockStart = t.tv_sec;
        g_ClockStart *= 1000;
		g_ClockStart *= 1000;

        // calculate the milliseconds now
        g_ClockStart += t.tv_usec;

        g_PerformanceFrequency = 1;

#endif
	}
}

double Plat_FloatTime()
{
	InitTime();
/*
	LARGE_INTEGER CurrentTime;

	QueryPerformanceCounter( &CurrentTime );

	double fRawSeconds = (double)( CurrentTime.QuadPart - g_ClockStart.QuadPart ) / (double)(g_PerformanceFrequency.QuadPart);

	return fRawSeconds;
*/

   #ifdef WIN32
        uint64 CurrentTime;
        QueryPerformanceCounter( (LARGE_INTEGER*)(&CurrentTime) );
        return (double)(CurrentTime - g_ClockStart) / (double)(g_MSPerformanceFrequency);
    #else
        struct timeval CurrentTime;
        uint64 s;

        // get the time of day
        gettimeofday( &CurrentTime, 0 );

        // calculate the number of milliseconds represented by the seconds
        s = CurrentTime.tv_sec;
        s *= 1000;

        // calculate the milliseconds now
        s += (CurrentTime.tv_usec / 1000);

        // return the value
        return (double) s - (g_ClockStart/1000);
    #endif

}

unsigned long Plat_MSTime()
{

/*	2010-11-26
unsigned long Plat_MSTime()
{
	InitTime();

	LARGE_INTEGER CurrentTime;

	QueryPerformanceCounter( &CurrentTime );

	return (unsigned long) ( ( CurrentTime.QuadPart - g_ClockStart.QuadPart ) / g_MSPerformanceFrequency.QuadPart);
//*/

	return (unsigned long) Plat_FloatTime();

}


unsigned long Plat_MMSTime()
//uint32 Plat_MMSTime()
{
	InitTime();
/*
	LARGE_INTEGER CurrentTime;

	QueryPerformanceCounter( &CurrentTime );

	return (unsigned long) ((double)( 1000 * ( CurrentTime.QuadPart - g_ClockStart.QuadPart ) / g_MSPerformanceFrequency.QuadPart));
//*/

   #ifdef WIN32
        uint64 CurrentTime;
        QueryPerformanceCounter( (LARGE_INTEGER*)(&CurrentTime) );
        return (unsigned long) ((double) ( 1000 * (CurrentTime - g_ClockStart)  / g_MSPerformanceFrequency));
    #else
        struct timeval CurrentTime;
        uint64 s;

        // get the time of day
        gettimeofday( &CurrentTime, 0 );

        // calculate the number of milliseconds represented by the seconds
        s = CurrentTime.tv_sec;
        s *= 1000;
		s *= 1000;

        // calculate the milliseconds now
        s += CurrentTime.tv_usec;

        // return the value
        return (unsigned long) (s - g_ClockStart);
    #endif

}

bool vtune( bool resume )
{
#ifdef WIN32
	static bool bInitialized = false;
	static void (__cdecl *VTResume)(void) = NULL;
	static void (__cdecl *VTPause) (void) = NULL;

	// Grab the Pause and Resume function pointers from the VTune DLL the first time through:
	if( !bInitialized )
	{
		bInitialized = true;

		HINSTANCE pVTuneDLL = LoadLibrary( "vtuneapi.dll" );

		if( pVTuneDLL )
		{
			VTResume = (void(__cdecl *)())GetProcAddress( pVTuneDLL, "VTResume" );
			VTPause  = (void(__cdecl *)())GetProcAddress( pVTuneDLL, "VTPause" );
		}
	}

	// Call the appropriate function, as indicated by the argument:
	if( resume && VTResume )
	{
		VTResume();
		return true;

	} else if( !resume && VTPause )
	{
		VTPause();
		return true;
	}
#else
#endif
	return false;

}


// -------------------------------------------------------------------------------------------------- //
// Memory stuff.
// -------------------------------------------------------------------------------------------------- //

void Plat_DefaultAllocErrorFn( unsigned long size )
{
}

Plat_AllocErrorFn g_AllocError = Plat_DefaultAllocErrorFn;


CPlatformCS g_AllocCS;

#include "mynew.h"
//#define _ANALYZE_MEMORY_
int g_AllMem = 0;
void* Debug_Plat_Alloc( unsigned long size, const char * szFile, int nLine )
{
	g_AllocCS.Lock( );
#ifdef _ANALYZE_MEMORY_
	void *pRet = analyzealloc( size );
#else
	void *pRet = MemAlloc( ).Alloc( size, szFile, nLine );
	g_AllMem+=size;
	//if( size > 10000 )
	//	Log( "MemAlloc szie:%d _%s _%d,TotalMem : %d ",size,szFile , nLine ,g_AllMem );
#endif
	g_AllocCS.Unlock( );
	if ( pRet )
	{
		return pRet;
	}
	else
	{
		g_AllocError( size );
		return 0;
	}
}


void* Debug_Plat_Realloc( void *ptr, unsigned long size, const char * szFile, int nLine )
{
	g_AllocCS.Lock( );
#ifdef _ANALYZE_MEMORY_
	void *pRet = analyzerealloc( ptr, size );
#else
	void *pRet = MemAlloc( ).Realloc( ptr, size, szFile, nLine );
#endif
	g_AllocCS.Unlock( );
	if ( pRet )
	{
		return pRet;
	}
	else
	{
		g_AllocError( size );
		return 0;
	}
}

void Debug_Plat_Free( void *ptr, const char * szFile, int nLine )
{
	if( ptr == NULL )
		return;
	g_AllocCS.Lock( );
#ifdef _ANALYZE_MEMORY_
	analyzefree( ptr );
#else
	MemAlloc( ).Free( ptr, szFile, nLine );
#endif
	g_AllocCS.Unlock( );
}

void* Release_Plat_Alloc( unsigned long size )
{
	g_AllocCS.Lock( );
#ifdef _ANALYZE_MEMORY_
	void *pRet = analyzealloc( size );
#else
	void *pRet = MemAlloc( ).Alloc( size );
#endif
	g_AllocCS.Unlock( );
	if ( pRet )
	{
		return pRet;
	}
	else
	{
		g_AllocError( size );
		return 0;
	}
}


void* Release_Plat_Realloc( void *ptr, unsigned long size )
{
	g_AllocCS.Lock( );
#ifdef _ANALYZE_MEMORY_
	void *pRet = analyzerealloc( ptr, size );
#else
	void *pRet = MemAlloc( ).Realloc( ptr, size );
#endif
	g_AllocCS.Unlock( );
	if ( pRet )
	{
		return pRet;
	}
	else
	{
		g_AllocError( size );
		return 0;
	}
}

void Release_Plat_Free( void *ptr )
{
	if( ptr == NULL )
		return;
	g_AllocCS.Lock( );
#ifdef _ANALYZE_MEMORY_
	analyzefree( ptr );
#else
	MemAlloc( ).Free( ptr );
#endif
	g_AllocCS.Unlock( );
}


void Plat_SetAllocErrorFn( Plat_AllocErrorFn fn )
{
	g_AllocError = fn;
}

void Plat_GetExePath( char * szExePath, int nSize )
{
#ifdef WIN32
	HMODULE hmodule =  GetModuleHandle( NULL );
	GetModuleFileName( hmodule, szExePath, nSize );
	// 必须初始化CommandLine( )，使用CommandLine( ).CreateCmdLine
	//	Assert( CommandLine( ).ParmCount( ) != 0 );
	//	Q_strcpy( szExePath, CommandLine( ).GetParm( 0 ) );
	char * pEnd = szExePath;
	char * p;
	char c = '\\';
	while (p = strchr(pEnd,c)){
		pEnd = ++p;
	}
	*pEnd = 0;
#else
	getcwd(szExePath,nSize);
	strcat(szExePath,"/");
#endif
}

BOOL Plat_CreatePath( LPCTSTR fullname )
{
	BOOL booIsCreate = false;
	int i;
	int len = strlen( fullname );
	char szDir[MAX_PATH];

	for( i=0; i<len; i++ )
	{
		if( fullname[i] == '\\' || fullname[i] == '/' )
		{
			strcpy(szDir,fullname);
			szDir[i] = 0;
#ifdef WIN32
			if(CreateDirectory(szDir,NULL) != 0)
				booIsCreate = true;
#else
			if(mkdir( szDir, 0700 ) == 0)
				booIsCreate = true;
#endif
		}
	}
	return booIsCreate;
}

