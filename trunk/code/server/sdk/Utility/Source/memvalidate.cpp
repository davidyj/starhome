//========= Copyright ?1996-2001, Valve LLC, All rights reserved. ============
//
// Purpose: Memory allocation!
//
// $NoKeywords: $
//=============================================================================

#include "../stdafx.h"

#ifdef UTILITY_VALIDATE_HEAP

#include <malloc.h>
#include "dbg.h"
#include "memalloc.h"

//-----------------------------------------------------------------------------
// Singleton interface
//-----------------------------------------------------------------------------
// IMemAlloc &MemAlloc( )
// {
// 	static CValidateAlloc s_ValidateAlloc;
// 	return s_ValidateAlloc;
// }


//-----------------------------------------------------------------------------
// Constructor.
//-----------------------------------------------------------------------------
CValidateAlloc::CValidateAlloc()
{
	m_pFirstAllocation = 0;
	memset( m_pPrefixImage, 0xBE, HEAP_PREFIX_BUFFER_SIZE );
	memset( m_pSuffixImage, 0xAF, HEAP_SUFFIX_BUFFER_SIZE );
}


//-----------------------------------------------------------------------------
// Accessors...
//-----------------------------------------------------------------------------
inline CValidateAlloc::HeapSuffix_t *CValidateAlloc::Suffix( HeapPrefix_t *pPrefix )
{
	return reinterpret_cast<HeapSuffix_t *>( (unsigned char*)( pPrefix + 1 ) + pPrefix->m_nSize );
}

inline void *CValidateAlloc::AllocationStart( HeapPrefix_t *pBase )
{
	return static_cast<void *>( pBase + 1 );
}

inline CValidateAlloc::HeapPrefix_t *CValidateAlloc::PrefixFromAllocation( void *pAlloc )
{
	if ( !pAlloc )
		return NULL;

	return ((HeapPrefix_t*)pAlloc) - 1;
}

inline const CValidateAlloc::HeapPrefix_t *CValidateAlloc::PrefixFromAllocation( const void *pAlloc )
{
	return ((const HeapPrefix_t*)pAlloc) - 1;
}


//-----------------------------------------------------------------------------
// Add to the list!
//-----------------------------------------------------------------------------
void CValidateAlloc::AddToList( HeapPrefix_t *pHeap, int nSize )
{
	pHeap->m_pPrev = NULL;
	pHeap->m_pNext = m_pFirstAllocation;
	if ( m_pFirstAllocation )
	{
		m_pFirstAllocation->m_pPrev = pHeap;
	}
	pHeap->m_nSize = nSize;

	m_pFirstAllocation = pHeap;

	HeapSuffix_t *pSuffix = Suffix( pHeap );
	memcpy( pHeap->m_Prefix, m_pPrefixImage, HEAP_PREFIX_BUFFER_SIZE );
	memcpy( pSuffix->m_Suffix, m_pSuffixImage, HEAP_SUFFIX_BUFFER_SIZE );
}


//-----------------------------------------------------------------------------
// Remove from the list!
//-----------------------------------------------------------------------------
void CValidateAlloc::RemoveFromList( HeapPrefix_t *pHeap )
{
	if ( !pHeap )
		return;

	ValidateAllocation( pHeap );
	if ( pHeap->m_pPrev )
	{
		pHeap->m_pPrev->m_pNext = pHeap->m_pNext;
	}
	else
	{
		m_pFirstAllocation = pHeap->m_pNext;
	}

	if ( pHeap->m_pNext )
	{
		pHeap->m_pNext->m_pPrev = pHeap->m_pPrev;
	}
}


//-----------------------------------------------------------------------------
// Validate the allocation
//-----------------------------------------------------------------------------
bool CValidateAlloc::ValidateAllocation( HeapPrefix_t *pHeap )
{
	HeapSuffix_t *pSuffix = Suffix( pHeap );

	bool bOk = true;
	if ( memcmp( pHeap->m_Prefix, m_pPrefixImage, HEAP_PREFIX_BUFFER_SIZE ) )
	{
		bOk = false;
	}

	if ( memcmp( pSuffix->m_Suffix, m_pSuffixImage, HEAP_SUFFIX_BUFFER_SIZE ) )
	{
		bOk = false;
	}

	if ( !bOk )
	{
		Warning("Memory trash detected in allocation %X!\n", (void*)(pHeap+1) );
		Assert( 0 );
	}

	return bOk;
}

//-----------------------------------------------------------------------------
// Release versions
//-----------------------------------------------------------------------------
void *CValidateAlloc::Alloc( size_t nSize )
{
	int nActualSize = nSize + sizeof(HeapPrefix_t) + sizeof(HeapSuffix_t);
	HeapPrefix_t *pHeap = (HeapPrefix_t*)ActualAlloc( ).Alloc( nActualSize );
	AddToList( pHeap, nSize );
	return AllocationStart( pHeap );
}

void *CValidateAlloc::Realloc( void *pMem, size_t nSize )
{
	HeapPrefix_t *pHeap	= PrefixFromAllocation( pMem );
	RemoveFromList( pHeap );

	int nActualSize = nSize + sizeof(HeapPrefix_t) + sizeof(HeapSuffix_t);
	pHeap = (HeapPrefix_t*)ActualAlloc( ).Realloc( pHeap, nActualSize );
	AddToList( pHeap, nSize );

	return AllocationStart( pHeap );
}

void CValidateAlloc::Free( void *pMem )
{
	HeapPrefix_t *pHeap	= PrefixFromAllocation( pMem );
	RemoveFromList( pHeap );

	ActualAlloc( ).Free( pHeap );
}

void *CValidateAlloc::Expand( void *pMem, size_t nSize )
{
	HeapPrefix_t *pHeap	= PrefixFromAllocation( pMem );
	RemoveFromList( pHeap );

	int nActualSize = nSize + sizeof(HeapPrefix_t) + sizeof(HeapSuffix_t);
	pHeap = (HeapPrefix_t*)ActualAlloc( ).Expand( pHeap, nActualSize );
	AddToList( pHeap, nSize );

	return AllocationStart( pHeap );
}


//-----------------------------------------------------------------------------
// Debug versions
//-----------------------------------------------------------------------------
void *CValidateAlloc::Alloc( size_t nSize, const char *pFileName, int nLine )
{
	int nActualSize = nSize + sizeof(HeapPrefix_t) + sizeof(HeapSuffix_t);
	HeapPrefix_t *pHeap = (HeapPrefix_t*)ActualAlloc( ).Alloc( nActualSize, pFileName, nLine );
	AddToList( pHeap, nSize );
	return AllocationStart( pHeap );
}

void *CValidateAlloc::Realloc( void *pMem, size_t nSize, const char *pFileName, int nLine )
{
	HeapPrefix_t *pHeap	= PrefixFromAllocation( pMem );
	RemoveFromList( pHeap );

	int nActualSize = nSize + sizeof(HeapPrefix_t) + sizeof(HeapSuffix_t);
	pHeap = (HeapPrefix_t*)ActualAlloc( ).Realloc( pHeap, nActualSize, pFileName, nLine );
	AddToList( pHeap, nSize );

	return AllocationStart( pHeap );
}

void  CValidateAlloc::Free( void *pMem, const char *pFileName, int nLine )
{
	HeapPrefix_t *pHeap	= PrefixFromAllocation( pMem );
	RemoveFromList( pHeap );

	ActualAlloc( ).Free( pHeap, pFileName, nLine );
}

void *CValidateAlloc::Expand( void *pMem, size_t nSize, const char *pFileName, int nLine )
{
	HeapPrefix_t *pHeap	= PrefixFromAllocation( pMem );
	RemoveFromList( pHeap );

	int nActualSize = nSize + sizeof(HeapPrefix_t) + sizeof(HeapSuffix_t);
	pHeap = (HeapPrefix_t*)ActualAlloc( ).Expand( pHeap, nActualSize, pFileName, nLine );
	AddToList( pHeap, nSize );

	return AllocationStart( pHeap );
}


//-----------------------------------------------------------------------------
// Returns size of a particular allocation
//-----------------------------------------------------------------------------
size_t CValidateAlloc::GetSize( void *pMem )
{
	HeapPrefix_t *pHeap	= PrefixFromAllocation( pMem );
	return pHeap->m_nSize;
}


//-----------------------------------------------------------------------------
// Force file + line information for an allocation
//-----------------------------------------------------------------------------
void CValidateAlloc::PushAllocDbgInfo( const char *pFileName, int nLine )
{
	ActualAlloc( ).PushAllocDbgInfo( pFileName, nLine );
}

void CValidateAlloc::PopAllocDbgInfo()
{
	ActualAlloc( ).PopAllocDbgInfo( );
}

//-----------------------------------------------------------------------------
// FIXME: Remove when we make our own heap! Crt stuff we're currently using
//-----------------------------------------------------------------------------
long CValidateAlloc::CrtSetBreakAlloc( long lNewBreakAlloc )
{
	return ActualAlloc( ).CrtSetBreakAlloc( lNewBreakAlloc );
}

int CValidateAlloc::CrtSetReportMode( int nReportType, int nReportMode )
{
	return ActualAlloc( ).CrtSetReportMode( nReportType, nReportMode );
}

int CValidateAlloc::CrtIsValidHeapPointer( const void *pMem )
{
	const HeapPrefix_t *pHeap = PrefixFromAllocation( pMem );
	return ActualAlloc( ).CrtIsValidHeapPointer( pHeap );
}

int CValidateAlloc::CrtCheckMemory( void )
{
	return ActualAlloc( ).CrtCheckMemory( );
}

int CValidateAlloc::CrtSetDbgFlag( int nNewFlag )
{
	return ActualAlloc( ).CrtSetDbgFlag( nNewFlag );
}

void CValidateAlloc::CrtMemCheckpoint( _CrtMemState *pState )
{
	ActualAlloc( ).CrtMemCheckpoint( pState );
}

void* CValidateAlloc::CrtSetReportFile( int nRptType, void* hFile )
{
	return ActualAlloc( ).CrtSetReportFile( nRptType, hFile );
}

void* CValidateAlloc::CrtSetReportHook( void* pfnNewHook )
{
	return ActualAlloc( ).CrtSetReportHook( pfnNewHook );
}

int CValidateAlloc::CrtDbgReport( int nRptType, const char * szFile,
		int nLine, const char * szModule, const char * pMsg )
{
	return ActualAlloc( ).CrtDbgReport( nRptType, szFile, nLine, szModule, pMsg );
}

int CValidateAlloc::heapchk()
{
	bool bOk = true;

	// Validate the heap
	HeapPrefix_t *pHeap = m_pFirstAllocation;
	for( pHeap = m_pFirstAllocation; pHeap; pHeap = pHeap->m_pNext )
	{
		if ( !ValidateAllocation( pHeap ) )
		{
			bOk = false;
		}
	}

#ifdef WIN32
	return bOk ? _HEAPOK : 0;
#else
	return bOk;
#endif
}

#endif // UTILITY_VALIDATE_HEAP
