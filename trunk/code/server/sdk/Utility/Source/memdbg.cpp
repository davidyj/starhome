/*
 * XXX: memdbg not ported to FreeBSD, for it has tight coupling with windows.
 */
//========= Copyright ?1996-2001, Valve LLC, All rights reserved. ============
//
// Purpose: Memory allocation!
//
// $NoKeywords: $
//=============================================================================


#include "../stdafx.h"
#ifdef _DEBUG
#include "memdbg.h"

//-----------------------------------------------------------------------------
// Singleton interface
//-----------------------------------------------------------------------------
// #ifndef UTILITY_VALIDATE_HEAP
// IMemAlloc &MemAlloc( )
// {
// 	static CDbgMemAlloc s_DbgMemAlloc;
// 	return s_DbgMemAlloc;
// }
// #else
// IMemAlloc &ActualAlloc( )
// {
// 	static CDbgMemAlloc s_DbgMemAlloc;
// 	return s_DbgMemAlloc;
// }
// #endif


//-----------------------------------------------------------------------------
// Byte count buckets
//-----------------------------------------------------------------------------
int CDbgMemAlloc::s_pCountSizes[CDbgMemAlloc::NUM_BYTE_COUNT_BUCKETS] = 
{
	16, 32, 128, 1024, INT_MAX
};

const char *CDbgMemAlloc::s_pCountHeader[CDbgMemAlloc::NUM_BYTE_COUNT_BUCKETS] = 
{
	"<=16 byte allocations", 
	"17-32 byte allocations",
	"33-128 byte allocations", 
	"129-1024 byte allocations",
	">1024 byte allocations"
};


//-----------------------------------------------------------------------------
// Standard output
//-----------------------------------------------------------------------------
static FILE* s_DbgFile;

static void DefaultHeapReportFunc( char const *pFormat, ... )
{
	va_list args;
	va_start( args, pFormat );
	vfprintf( s_DbgFile, pFormat, args );
	va_end( args );
}


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CDbgMemAlloc::CDbgMemAlloc()
{
	m_OutputFunc = DefaultHeapReportFunc;
	m_nDbgInfoStackDepth = -1;
}

CDbgMemAlloc::~CDbgMemAlloc()
{
	StatMapIter_t iter = m_StatMap.begin();
	while(iter != m_StatMap.end())
	{
		if (iter->first.m_pFileName)
		{
			char *pFileName = (char*)iter->first.m_pFileName;
			delete [] pFileName;
		}
		iter++;
	}
}


//-----------------------------------------------------------------------------
// Release versions
//-----------------------------------------------------------------------------
//static char const *pUnknown = "unknown";

void *CDbgMemAlloc::Alloc( size_t nSize )
{
	/*
	// NOTE: Uncomment this to find unknown allocations
	const char *pFileName = pUnknown;
	int nLine;
	GetActualDbgInfo( pFileName, nLine );
	if (pFileName == pUnknown)
	{
		int x = 3;
	}
	*/

	// FIXME: Should these gather stats?
//	return Alloc( nSize, pUnknown, 0 );
//	size_t nNewSize = nSize + sizeof( size_t );
//	void* ptr = MemoryAllocator( ).allocate( nNewSize );
//	*(size_t*)ptr = nNewSize;
//	return (char*)ptr + sizeof( size_t );
	return _malloc_dbg( nSize, _NORMAL_BLOCK, __FILE__, __LINE__ );
//	return malloc( nSize );
}

void *CDbgMemAlloc::Realloc( void *pMem, size_t nSize )
{
	// FIXME: Should these gather stats?
//	return Realloc( pMem, nSize, pUnknown, 0 );
//	void * ptr = (char*)pMem - sizeof( size_t );
//	size_t nNewSize = nSize + sizeof( size_t );
//	size_t nOldSize = *(size_t*)ptr;
//	ptr = MemoryAllocator( ).reallocate( ptr, nOldSize, nNewSize );
//	*(size_t*)ptr = nNewSize;
//	return (char*)ptr + sizeof( size_t );
	return realloc( pMem, nSize );
}

void CDbgMemAlloc::Free( void *pMem )
{
	// FIXME: Should these gather stats?
//	Free( pMem, pUnknown, 0 );
//	void * ptr = (char*)pMem - sizeof( size_t );
//	size_t nSize = *(size_t*)ptr;
//	MemoryAllocator( ).deallocate( ptr, nSize );
	free( pMem );
}

void *CDbgMemAlloc::Expand( void *pMem, size_t nSize )
{
	// FIXME: Should these gather stats?
//	return Expand( pMem, nSize, pUnknown, 0 );
//	void * ptr = (char*)pMem - sizeof( size_t );
//	size_t nNewSize = nSize + sizeof( size_t );
//	size_t nOldSize = *(size_t*)ptr;
//	ptr = MemoryAllocator( ).reallocate( ptr, nOldSize, nNewSize );
//	*(size_t*)ptr = nNewSize;
//	return (char*)ptr + sizeof( size_t );
	return _expand( pMem, nSize );
}


//-----------------------------------------------------------------------------
// Force file + line information for an allocation
//-----------------------------------------------------------------------------
void CDbgMemAlloc::PushAllocDbgInfo( const char *pFileName, int nLine )
{
	++m_nDbgInfoStackDepth;
	Assert( m_nDbgInfoStackDepth < DBG_INFO_STACK_DEPTH );
	m_DbgInfoStack[m_nDbgInfoStackDepth].m_pFileName = pFileName;
	m_DbgInfoStack[m_nDbgInfoStackDepth].m_nLine = nLine;
}

void CDbgMemAlloc::PopAllocDbgInfo()
{
	--m_nDbgInfoStackDepth;
	Assert( m_nDbgInfoStackDepth >= -1 );
}


//-----------------------------------------------------------------------------
// Returns the actual debug info
//-----------------------------------------------------------------------------
void CDbgMemAlloc::GetActualDbgInfo( const char *&pFileName, int &nLine )
{
	if (m_nDbgInfoStackDepth >= 0)
	{
		pFileName = m_DbgInfoStack[m_nDbgInfoStackDepth].m_pFileName;
		nLine = m_DbgInfoStack[m_nDbgInfoStackDepth].m_nLine;
	}
}


//-----------------------------------------------------------------------------
// Finds the file in our map
//-----------------------------------------------------------------------------
CDbgMemAlloc::MemInfo_t &CDbgMemAlloc::FindOrCreateEntry( const char *pFileName, int line )
{
	// Oh how I love crazy STL. retval.first == the StatMapIter_t in the std::pair
	// retval.first->second == the MemInfo_t that's part of the StatMapIter_t 
	std::pair<StatMapIter_t, bool> retval;
	retval = m_StatMap.insert( StatMapEntry_t( MemInfoKey_t( pFileName, line ), MemInfo_t() ) );

	// If we created it for the first time, actually *allocate* the filename memory
	// This is necessary for shutdown conditions: the file name is stored
	// in some piece of memory in a DLL; if that DLL becomes unloaded,
	// we'll have a pointer to crap memory
	if (retval.second)
	{
		int nLen = strlen(pFileName) + 1;
		char **ppStatsFileName = (char**)(&retval.first->first.m_pFileName);
		*ppStatsFileName = new char[nLen];
		memcpy( *ppStatsFileName, pFileName, nLen );
	}

	return retval.first->second;
}


//-----------------------------------------------------------------------------
// Updates stats
//-----------------------------------------------------------------------------
void CDbgMemAlloc::RegisterAllocation( MemInfo_t &info, int nSize, int nTime )
{
	++info.m_nCurrentCount;
	++info.m_nTotalCount;
	if (info.m_nCurrentCount > info.m_nPeakCount)
	{
		info.m_nPeakCount = info.m_nCurrentCount;
	}

	info.m_nCurrentSize += nSize;
	info.m_nTotalSize += nSize;
	if (info.m_nCurrentSize > info.m_nPeakSize)
	{
		info.m_nPeakSize = info.m_nCurrentSize;
	}

	for (int i = 0; i < NUM_BYTE_COUNT_BUCKETS; ++i)
	{
		if (nSize <= s_pCountSizes[i])
		{
			++info.m_pCount[i];
			break;
		}
	}

	Assert( info.m_nPeakCount >= info.m_nCurrentCount );
	Assert( info.m_nPeakSize >= info.m_nCurrentSize );

	// Based on looking at the standard allocator, there's 12 bytes of
	// overhead per allocation + the allocation size is rounded to the
	// next highest 16 bytes
	int nActualSize = ((nSize + 0xF) & 0xFFFFFFF0);
	info.m_nOverheadSize += 12 + (nActualSize - nSize);
	if (info.m_nOverheadSize > info.m_nPeakOverheadSize)
	{
		info.m_nPeakOverheadSize = info.m_nOverheadSize;
	}

	info.m_nTime += nTime;
}

void CDbgMemAlloc::RegisterDeallocation( MemInfo_t &info, int nSize, int nTime )
{
	--info.m_nCurrentCount;
	info.m_nCurrentSize -= nSize;

	Assert( info.m_nPeakCount >= info.m_nCurrentCount );
	Assert( info.m_nPeakSize >= info.m_nCurrentSize );
	Assert( info.m_nCurrentCount >= 0 );
	Assert( info.m_nCurrentSize >= 0 );

	// Based on looking at the standard allocator, there's 12 bytes of
	// overhead per allocation + the allocation size is rounded to the
	// next highest 16 bytes
	int nActualSize = ((nSize + 0xF) & 0xFFFFFFF0);
	info.m_nOverheadSize -= 12 + (nActualSize - nSize);

	info.m_nTime += nTime;
}


//-----------------------------------------------------------------------------
// Gets the allocation file name
//-----------------------------------------------------------------------------
const char *CDbgMemAlloc::GetAllocatonFileName( void *pMem )
{
	if (!pMem)
		return "";

	CrtDbgMemHeader_t *pHeader = (CrtDbgMemHeader_t*)pMem;
	--pHeader;
	return pHeader->m_pFileName;
}

//-----------------------------------------------------------------------------
// Gets the allocation file name
//-----------------------------------------------------------------------------
int CDbgMemAlloc::GetAllocatonLineNumber( void *pMem )
{
	if (!pMem)
		return 0;

	CrtDbgMemHeader_t *pHeader = (CrtDbgMemHeader_t*)pMem;
	--pHeader;
	return pHeader->m_nLineNumber;
}

//-----------------------------------------------------------------------------
// Debug versions of the main allocation methods
//-----------------------------------------------------------------------------
void *CDbgMemAlloc::Alloc( size_t nSize, const char *pFileName, int nLine )
{
//	GetActualDbgInfo( pFileName, nLine );

//	m_Timer.Start();
	void *pMem = _malloc_dbg( nSize, _NORMAL_BLOCK, pFileName, nLine );
//	m_Timer.End();

//	unsigned long nTime = m_Timer.GetDuration().GetMicroseconds();

//	RegisterAllocation( m_GlobalInfo, nSize, nTime );
//	RegisterAllocation( FindOrCreateEntry( pFileName, nLine ), nSize, nTime );

	return pMem;
}

void *CDbgMemAlloc::Realloc( void *pMem, size_t nSize, const char *pFileName, int nLine )
{
/*	GetActualDbgInfo( pFileName, nLine );

	int nOldSize = GetSize( pMem );
	const char *pOldFileName = GetAllocatonFileName( pMem );
	int oldLine = GetAllocatonLineNumber( pMem );

	if ( pMem != 0 )
	{
		RegisterDeallocation( FindOrCreateEntry( pOldFileName, oldLine ), nOldSize, 0 );
		RegisterDeallocation( m_GlobalInfo, nOldSize, 0 );
	}
*/
//	m_Timer.Start();
	pMem = _realloc_dbg( pMem, nSize, _NORMAL_BLOCK, pFileName, nLine );
//	m_Timer.End();
	
//	unsigned long nTime = m_Timer.GetDuration().GetMicroseconds();

//	RegisterAllocation( FindOrCreateEntry( pFileName, nLine ), nSize, nTime );
//	RegisterAllocation( m_GlobalInfo, nSize, nTime );

	return pMem;
}

void  CDbgMemAlloc::Free( void *pMem, const char *pFileName, int nLine )
{
	if (!pMem)
		return;
/*
	int nOldSize = GetSize( pMem );
	const char *pOldFileName = GetAllocatonFileName( pMem );
	int oldLine = GetAllocatonLineNumber( pMem );
*/
//	m_Timer.Start();
	_free_dbg( pMem, _NORMAL_BLOCK );
 //	m_Timer.End();

//	unsigned long nTime = m_Timer.GetDuration().GetMicroseconds();

//	RegisterDeallocation( m_GlobalInfo, nOldSize, nTime );
//	RegisterDeallocation( FindOrCreateEntry( pOldFileName, oldLine ), nOldSize, nTime );
}

void *CDbgMemAlloc::Expand( void *pMem, size_t nSize, const char *pFileName, int nLine )
{
#ifdef WIN32 	
	GetActualDbgInfo( pFileName, nLine );

	int nOldSize = GetSize( pMem );
	const char *pOldFileName = GetAllocatonFileName( pMem );
	int oldLine = GetAllocatonLineNumber( pMem );

	RegisterDeallocation( FindOrCreateEntry( pOldFileName, oldLine ), nOldSize, 0 );
	RegisterDeallocation( m_GlobalInfo, nOldSize, 0 );

	m_Timer.Start();
	pMem = _expand_dbg( pMem, nSize, _NORMAL_BLOCK, pFileName, nLine );
	m_Timer.End();

	unsigned long nTime = m_Timer.GetDuration().GetMicroseconds();

	RegisterAllocation( FindOrCreateEntry( pFileName, nLine ), nSize, nTime );
	RegisterAllocation( m_GlobalInfo, nSize, nTime );
#else
	printf("XXX: CDbgMemAlloc::Expand() not portd to FreeBSD,in file %s\n", __FILE__);
	abort();
#endif	
	return pMem;
}


//-----------------------------------------------------------------------------
// Returns size of a particular allocation
//-----------------------------------------------------------------------------
size_t CDbgMemAlloc::GetSize( void *pMem )
{
	if (!pMem)
		return 0;

	return _msize_dbg( pMem, _NORMAL_BLOCK );
}


//-----------------------------------------------------------------------------
// FIXME: Remove when we make our own heap! Crt stuff we're currently using
//-----------------------------------------------------------------------------
long CDbgMemAlloc::CrtSetBreakAlloc( long lNewBreakAlloc )
{
	return _CrtSetBreakAlloc( lNewBreakAlloc );
}

int CDbgMemAlloc::CrtSetReportMode( int nReportType, int nReportMode )
{
	return _CrtSetReportMode( nReportType, nReportMode );
}

int CDbgMemAlloc::CrtIsValidHeapPointer( const void *pMem )
{
	return _CrtIsValidHeapPointer( pMem );
}

int CDbgMemAlloc::CrtCheckMemory( void )
{
	return CrtCheckMemory( );
}

int CDbgMemAlloc::CrtSetDbgFlag( int nNewFlag )
{
	return _CrtSetDbgFlag( nNewFlag );
}

void CDbgMemAlloc::CrtMemCheckpoint( _CrtMemState *pState )
{
	_CrtMemCheckpoint( pState );
}

// FIXME: Remove when we have our own allocator
void* CDbgMemAlloc::CrtSetReportFile( int nRptType, void* hFile )
{
#ifdef WIN32	
	return (void*)_CrtSetReportFile( nRptType, (_HFILE)hFile );
#else
	printf("XXX: CDbgMemAlloc::CrtSetReportFile() not portd to FreeBSD in file %s\n", __FILE__);
	return NULL;
#endif	
}

void* CDbgMemAlloc::CrtSetReportHook( void* pfnNewHook )
{
#ifdef WIN32	
	return (void*)_CrtSetReportHook( (_CRT_REPORT_HOOK)pfnNewHook );
#else
	printf("XXX: CDbgMemAlloc::CrtSetReportHook() not portd to FreeBSD in file %s\n", __FILE__);
	return NULL;
#endif	
}

int CDbgMemAlloc::CrtDbgReport( int nRptType, const char * szFile,
		int nLine, const char * szModule, const char * pMsg )
{
#ifdef WIN32	
	return _CrtDbgReport( nRptType, szFile, nLine, szModule, pMsg );
#else
	printf("XXX: CDbgMemAlloc::CrtDbgReport() not been portd to FreeBSD in file %s\n",  __FILE__);
	return 0;
#endif	
}

int CDbgMemAlloc::heapchk()
{
#ifdef WIN32	
	return _heapchk();
#else
	printf("XXX: CDbgMemAlloc::heapchk() not portd to FreeBSD in file %s\n", __FILE__);
	return 0;
#endif	

}

//-----------------------------------------------------------------------------
// Stat output
//-----------------------------------------------------------------------------
void CDbgMemAlloc::DumpMemInfo( const char *pAllocationName, int line, const MemInfo_t &info )
{
	m_OutputFunc("%s, line %i\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%d\t%d\t%d\t%d",
		pAllocationName,
		line,
		info.m_nCurrentSize / 1024.0f,
		info.m_nPeakSize / 1024.0f,
		info.m_nTotalSize / 1024.0f,
		info.m_nOverheadSize / 1024.0f,
		info.m_nPeakOverheadSize / 1024.0f,
		(int)(info.m_nTime / 1000),
		info.m_nCurrentCount,
		info.m_nPeakCount,
		info.m_nTotalCount
		);

	for (int i = 0; i < NUM_BYTE_COUNT_BUCKETS; ++i)
	{
		m_OutputFunc( "\t%d", info.m_pCount[i] );
	}

	m_OutputFunc("\n");
}


//-----------------------------------------------------------------------------
// Stat output
//-----------------------------------------------------------------------------
void CDbgMemAlloc::DumpFileStats()
{
	StatMapIter_t iter = m_StatMap.begin();
	while(iter != m_StatMap.end())
	{
		DumpMemInfo( iter->first.m_pFileName, iter->first.m_nLine, iter->second );
		iter++;
	}
}


//-----------------------------------------------------------------------------
// Stat output
//-----------------------------------------------------------------------------
void CDbgMemAlloc::DumpStats()
{
	if (m_OutputFunc == DefaultHeapReportFunc)
	{
		static int s_FileCount = 0;
		char pFileName[64];
		sprintf( pFileName, "memstats%d.txt", s_FileCount );
		++s_FileCount;

		s_DbgFile = fopen(pFileName, "wt");
		if (!s_DbgFile)
			return;
	}

	m_OutputFunc("Allocation type\tCurrent Size(k)\tPeak Size(k)\tTotal Allocations(k)\tOverhead Size(k)\tPeak Overhead Size(k)\tTime(ms)\tCurrent Count\tPeak Count\tTotal Count");

	for (int i = 0; i < NUM_BYTE_COUNT_BUCKETS; ++i)
	{
		m_OutputFunc( "\t%s", s_pCountHeader[i] );
	}

	m_OutputFunc("\n");

	DumpMemInfo( "Totals", 0, m_GlobalInfo );
	DumpFileStats();

	if (m_OutputFunc == DefaultHeapReportFunc)
	{
		fclose(s_DbgFile);
	}
}



#endif // _DEBUG
