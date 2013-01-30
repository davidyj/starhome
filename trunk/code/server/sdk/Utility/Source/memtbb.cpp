#include "../stdafx.h"

#ifndef _DEBUG

#if !defined(X64_WIN) && !defined(FREEBSD)

#include "memtbb.h"
#include "tbb/scalable_allocator.h"

void *CTbbMemAlloc::Alloc( size_t nSize )
{
	if (nSize == 0)
	{
		nSize =1;
	}

	void *ptr = scalable_malloc(nSize);

	if (ptr)
	{
		return ptr;
	}
	else
	{
		return NULL;
	}
}

void *CTbbMemAlloc::Realloc( void *pMem, size_t nSize )
{
	if (nSize == 0)
	{
		if (pMem)
		{
			scalable_free(pMem);
		}

		return NULL;
	}

	if (pMem)
	{
		return scalable_realloc(pMem, nSize);
	}
	else
	{
		return scalable_malloc(nSize);
	}
}

void CTbbMemAlloc::Free( void *pMem )
{
	if (pMem)
	{
		scalable_free(pMem);
	}
}

void *CTbbMemAlloc::Expand( void *pMem, size_t nSize )
{
	if (nSize == 0)
	{
		if (pMem)
		{
			scalable_free(pMem);
		}

		return NULL;
	}

	if (pMem)
	{
		return scalable_realloc(pMem, nSize);
	}
	else
	{
		return scalable_malloc(nSize);
	}
}

void *CTbbMemAlloc::Alloc( size_t nSize, const char *pFileName, int nLine )
{
	if (nSize == 0)
	{
		nSize =1;
	}

	void *ptr = scalable_malloc(nSize);

	if (ptr)
	{
		return ptr;
	}
	else
	{
		return NULL;
	}
}

void *CTbbMemAlloc::Realloc( void *pMem, size_t nSize, const char *pFileName, int nLine )
{
	if (nSize == 0)
	{
		if (pMem)
		{
			scalable_free(pMem);
		}

		return NULL;
	}

	if (pMem)
	{
		return scalable_realloc(pMem, nSize);
	}
	else
	{
		return scalable_malloc(nSize);
	}
}

void  CTbbMemAlloc::Free( void *pMem, const char *pFileName, int nLine )
{
	if (pMem)
	{
		scalable_free(pMem);
	}
}

void *CTbbMemAlloc::Expand( void *pMem, size_t nSize, const char *pFileName, int nLine )
{
	if (nSize == 0)
	{
		if (pMem)
		{
			scalable_free(pMem);
		}

		return NULL;
	}

	if (pMem)
	{
		return scalable_realloc(pMem, nSize);
	}
	else
	{
		return scalable_malloc(nSize);
	}
}


size_t CTbbMemAlloc::GetSize( void *pMem )
{
	Assert( "GetSize() not implemented");
	return 0;
}

void CTbbMemAlloc::PushAllocDbgInfo( const char *pFileName, int nLine )
{
}

void CTbbMemAlloc::PopAllocDbgInfo()
{
}

long CTbbMemAlloc::CrtSetBreakAlloc( long lNewBreakAlloc )
{
	return 0;
}

int CTbbMemAlloc::CrtSetReportMode( int nReportType, int nReportMode )
{
	return 0;
}

int CTbbMemAlloc::CrtIsValidHeapPointer( const void *pMem )
{
	return 1;
}

int CTbbMemAlloc::CrtCheckMemory( void )
{
	return 1;
}

int CTbbMemAlloc::CrtSetDbgFlag( int nNewFlag )
{
	return 0;
}

void CTbbMemAlloc::CrtMemCheckpoint( _CrtMemState *pState )
{
}

void* CTbbMemAlloc::CrtSetReportFile( int nRptType, void* hFile )
{
	return 0;
}

void* CTbbMemAlloc::CrtSetReportHook( void* pfnNewHook )
{
	return 0;
}

int CTbbMemAlloc::CrtDbgReport( int nRptType, const char * szFile, int nLine, const char * szModule, const char * pMsg )
{
	return 0;
}

int CTbbMemAlloc::heapchk()
{
#ifdef WIN32
	return _HEAPOK;
#else
	return 1;
#endif
}

#endif //X64_WIN
#endif //_DEBUG
