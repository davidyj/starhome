//========= Copyright ?1996-2001, Valve LLC, All rights reserved. ============
//
// Purpose: Memory allocation!
//
// $NoKeywords: $
//=============================================================================

#include "../stdafx.h"

#ifndef _DEBUG
#include "memstd.h"
//-----------------------------------------------------------------------------
// Singleton interface
//-----------------------------------------------------------------------------
// #ifndef UTILITY_VALIDATE_HEAP
// IMemAlloc &MemAlloc( )
// {
// 	static CStdMemAlloc s_StdMemAlloc;
// 	return s_StdMemAlloc;
// }
// #else
// IMemAlloc &ActualAlloc( )
// {
// 	static CStdMemAlloc s_StdMemAlloc;
// 	return s_StdMemAlloc;
// }
// #endif


//-----------------------------------------------------------------------------
// Release versions
//-----------------------------------------------------------------------------
void *CStdMemAlloc::Alloc( size_t nSize )
{
	return malloc( nSize );
/*	size_t nNewSize = nSize + sizeof( size_t );
	void* ptr = MemoryAllocator( ).allocate( nNewSize );
	*(size_t*)ptr = nNewSize;
	return (char*)ptr + sizeof( size_t );*/
}

void *CStdMemAlloc::Realloc( void *pMem, size_t nSize )
{
	return realloc( pMem, nSize );
/*	void * ptr = (char*)pMem - sizeof( size_t );
	size_t nNewSize = nSize + sizeof( size_t );
	size_t nOldSize = *(size_t*)ptr;
	ptr = MemoryAllocator( ).reallocate( ptr, nOldSize, nNewSize );
	*(size_t*)ptr = nNewSize;
	return (char*)ptr + sizeof( size_t );*/
}

void CStdMemAlloc::Free( void *pMem )
{
	free( pMem );
/*	void * ptr = (char*)pMem - sizeof( size_t );
	size_t nSize = *(size_t*)ptr;
	MemoryAllocator( ).deallocate( ptr, nSize );*/
}

void *CStdMemAlloc::Expand( void *pMem, size_t nSize )
{
#ifdef WIN32
	return _expand( pMem, nSize );
#else
	return realloc( pMem, nSize );
#endif
}


//-----------------------------------------------------------------------------
// Debug versions
//-----------------------------------------------------------------------------
void *CStdMemAlloc::Alloc( size_t nSize, const char *pFileName, int nLine )
{
	return malloc( nSize );
//	size_t nNewSize = nSize + sizeof( size_t );
//	void* ptr = MemoryAllocator( ).allocate( nNewSize );
//	*(size_t*)ptr = nNewSize;
//	return (char*)ptr + sizeof( size_t );
}

void *CStdMemAlloc::Realloc( void *pMem, size_t nSize, const char *pFileName, int nLine )
{
	return realloc( pMem, nSize );
//	void * ptr = (char*)pMem - sizeof( size_t );
//	size_t nNewSize = nSize + sizeof( size_t );
//	size_t nOldSize = *(size_t*)ptr;
//	ptr = MemoryAllocator( ).reallocate( ptr, nOldSize, nNewSize );
//	*(size_t*)ptr = nNewSize;
//	return (char*)ptr + sizeof( size_t );
}

void  CStdMemAlloc::Free( void *pMem, const char *pFileName, int nLine )
{
	free( pMem );
//	void * ptr = (char*)pMem - sizeof( size_t );
//	size_t nSize = *(size_t*)ptr;
//	MemoryAllocator( ).deallocate( ptr, nSize );
}

void *CStdMemAlloc::Expand( void *pMem, size_t nSize, const char *pFileName, int nLine )
{
#ifdef WIN32
	return _expand( pMem, nSize );
#else
	return realloc( pMem, nSize );
#endif
}


//-----------------------------------------------------------------------------
// Returns size of a particular allocation
//-----------------------------------------------------------------------------
size_t CStdMemAlloc::GetSize( void *pMem )
{
#ifdef WIN32
	return _msize( pMem );
#else
	Assert( "GetSize() not implemented");
#endif
}


//-----------------------------------------------------------------------------
// Force file + line information for an allocation
//-----------------------------------------------------------------------------
void CStdMemAlloc::PushAllocDbgInfo( const char *pFileName, int nLine )
{
}

void CStdMemAlloc::PopAllocDbgInfo()
{
}

//-----------------------------------------------------------------------------
// FIXME: Remove when we make our own heap! Crt stuff we're currently using
//-----------------------------------------------------------------------------
long CStdMemAlloc::CrtSetBreakAlloc( long lNewBreakAlloc )
{
	return 0;
}

int CStdMemAlloc::CrtSetReportMode( int nReportType, int nReportMode )
{
	return 0;
}

int CStdMemAlloc::CrtIsValidHeapPointer( const void *pMem )
{
	return 1;
}

int CStdMemAlloc::CrtCheckMemory( void )
{
	return 1;
}

int CStdMemAlloc::CrtSetDbgFlag( int nNewFlag )
{
	return 0;
}

void CStdMemAlloc::CrtMemCheckpoint( _CrtMemState *pState )
{
}

// FIXME: Remove when we have our own allocator
void* CStdMemAlloc::CrtSetReportFile( int nRptType, void* hFile )
{
	return 0;
}

void* CStdMemAlloc::CrtSetReportHook( void* pfnNewHook )
{
	return 0;
}

int CStdMemAlloc::CrtDbgReport( int nRptType, const char * szFile,
		int nLine, const char * szModule, const char * pMsg )
{
	return 0;
}

int CStdMemAlloc::heapchk()
{
#ifdef WIN32
	return _HEAPOK;
#else
	return 1;
#endif
}


#endif
