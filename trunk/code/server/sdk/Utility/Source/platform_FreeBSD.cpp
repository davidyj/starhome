//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

#include "../stdafx.h"
#include "platform.h"
#include "memalloc.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "memdbgon.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>


double Plat_FloatTime()
{
	printf("XXX: Plat_FloatTime not implemented , in file %s\n", __FILE__);
	abort();
	return 0.0;
}

unsigned long Plat_MSTime()
{

        struct timeval  tp;
        static int      secbase = 0;

        gettimeofday( &tp, NULL );

        if ( !secbase )
        {
                secbase = tp.tv_sec;
                return (unsigned long)( tp.tv_usec / 1000000.0 );
        }

	return (unsigned long)(( tp.tv_sec - secbase ) + tp.tv_usec / 1000000.0 );
}

unsigned long Plat_MMSTime()
{
	return Plat_MSTime();
}

bool vtune( bool resume )
{
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

void* Debug_Plat_Alloc( unsigned long size, const char * szFile, int nLine )
{	
	g_AllocCS.Lock( );
#ifdef _ANALYZE_MEMORY_
	void *pRet = analyzealloc( size );
#else
	void *pRet = MemAlloc( ).Alloc( size, szFile, nLine );
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

void Release_Plat_Free(void *ptr)
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

}

BOOL Plat_CreatePath(LPCTSTR fullname)
{
	if (!fullname)
		return FALSE;
	if (mkdir(fullname, S_IRWXU) < 0) {
		
		return FALSE;
	}
	return TRUE;
}
	
