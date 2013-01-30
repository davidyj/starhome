//========= Copyright ?1996-2001, Valve LLC, All rights reserved. ============
//
// Purpose: Memory allocation!
//
// $NoKeywords: $
//=============================================================================

#include "../stdafx.h"
#include "mem.h"

#ifdef WIN32
#include <malloc.h>
#else
#include <stdlib.h>
#endif

#include "dbg.h"

enum 
{
	MAX_STACK_DEPTH = 32
};

static unsigned char *s_pBuf = NULL;
static int s_pBufStackDepth[MAX_STACK_DEPTH];
static int s_nBufDepth = -1;
static int s_nBufCurSize = 0;
static int s_nBufAllocSize = 0;

CPlatformCS g_ScratchCS;

//-----------------------------------------------------------------------------
// Other DLL-exported methods for particular kinds of memory
//-----------------------------------------------------------------------------
void *MemAllocScratch( int nMemSize )
{	
	g_ScratchCS.Lock( );
	// Minimally allocate 1M scratch
	if (s_nBufAllocSize < s_nBufCurSize + nMemSize)
	{
		s_nBufAllocSize = s_nBufCurSize + nMemSize;
		if (s_nBufAllocSize < 1024 * 1024)
		{
			s_nBufAllocSize = 1024 * 1024;
		}

		if (s_pBuf)
		{
#ifdef WIN32
			if (s_nBufDepth < 0)
			{
				s_pBuf = (unsigned char*)realloc( s_pBuf, s_nBufAllocSize );
			}
			else
			{
				s_pBuf = (unsigned char*)_expand( s_pBuf, s_nBufAllocSize );
				Assert( s_pBuf );
			}
#else
			s_pBuf = (unsigned char*)realloc( s_pBuf, s_nBufAllocSize );
			Assert( s_pBuf );	
#endif
		}
		else
		{
			s_pBuf = (unsigned char*)malloc( s_nBufAllocSize );
		}
	}

	int nBase = s_nBufCurSize;
	s_nBufCurSize += nMemSize;
	++s_nBufDepth;
	Assert( s_nBufDepth < MAX_STACK_DEPTH );
	s_pBufStackDepth[s_nBufDepth] = nMemSize;

	void * pRet = &s_pBuf[nBase];

	g_ScratchCS.Unlock( );
	return pRet;
}

void MemFreeScratch()
{
	g_ScratchCS.Lock( );
	Assert( s_nBufDepth >= 0 );
	s_nBufCurSize -= s_pBufStackDepth[s_nBufDepth];
	--s_nBufDepth;
	g_ScratchCS.Unlock( );
}


//by jinsheng fix memory leak for studio engine
void MemReleaseScratch( )
{
	if (s_pBuf)
	{
		free(s_pBuf);
		s_pBuf = NULL;
	}
}

