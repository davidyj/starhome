#ifdef _DEBUG

#ifdef WIN32
#include <malloc.h>
#include "crtdbg.h"
#else
#include <stdlib.h>
#include "crtdbg_FreeBSD.h"
#endif

#include <string.h>
#include "dbg.h"

#include "fasttimer.h"
#include "CommDef.h" // int64
#include <map>
#include <limits.h>
#include "memalloc.h"
#include "osAllocator.h"


//-----------------------------------------------------------------------------
// NOTE! This should never be called directly from leaf code
// Just use new,delete,malloc,free etc. They will call into this eventually
//-----------------------------------------------------------------------------
class CDbgMemAlloc : public IMemAlloc
{
public:
	CDbgMemAlloc();
	virtual ~CDbgMemAlloc();

	// Release versions
	virtual void *Alloc( size_t nSize );
	virtual void *Realloc( void *pMem, size_t nSize );
	virtual void  Free( void *pMem );
    virtual void *Expand( void *pMem, size_t nSize );

	// Debug versions
    virtual void *Alloc( size_t nSize, const char *pFileName, int nLine );
    virtual void *Realloc( void *pMem, size_t nSize, const char *pFileName, int nLine );
    virtual void  Free( void *pMem, const char *pFileName, int nLine );
    virtual void *Expand( void *pMem, size_t nSize, const char *pFileName, int nLine );

	// Returns size of a particular allocation
	virtual size_t GetSize( void *pMem );

    // Force file + line information for an allocation
    virtual void PushAllocDbgInfo( const char *pFileName, int nLine );
    virtual void PopAllocDbgInfo();

	virtual long CrtSetBreakAlloc( long lNewBreakAlloc );
	virtual	int CrtSetReportMode( int nReportType, int nReportMode );
	virtual int CrtIsValidHeapPointer( const void *pMem );
	virtual int CrtCheckMemory( void );
	virtual int CrtSetDbgFlag( int nNewFlag );
	virtual void CrtMemCheckpoint( _CrtMemState *pState );

	// FIXME: Remove when we have our own allocator
	virtual void* CrtSetReportFile( int nRptType, void* hFile );
	virtual void* CrtSetReportHook( void* pfnNewHook );
	virtual int CrtDbgReport( int nRptType, const char * szFile,
			int nLine, const char * szModule, const char * szFormat );

	virtual int heapchk();

	enum
	{
		BYTE_COUNT_16 = 0,
		BYTE_COUNT_32,
		BYTE_COUNT_128,
		BYTE_COUNT_1024,
		BYTE_COUNT_GREATER,

		NUM_BYTE_COUNT_BUCKETS
	};

private:
	enum
	{
		DBG_INFO_STACK_DEPTH = 32
	};

	struct DbgInfoStack_t
	{
		const char *m_pFileName;
		int m_nLine;
	};

	struct MemInfo_t
	{
		MemInfo_t()
		{
			memset( this, 0, sizeof(*this) );
		}

		// Size in bytes
		int m_nCurrentSize;
		int m_nPeakSize;
		int m_nTotalSize;
		int m_nOverheadSize;
		int m_nPeakOverheadSize;

		// Count in terms of # of allocations
		int m_nCurrentCount;
		int m_nPeakCount;
		int m_nTotalCount;

		// Count in terms of # of allocations of a particular size
		int m_pCount[NUM_BYTE_COUNT_BUCKETS];

		// Time spent allocating + deallocating	(microseconds)
		int64 m_nTime;
	};

	struct MemInfoKey_t
	{
		MemInfoKey_t( const char *pFileName, int line ) : m_pFileName(pFileName), m_nLine(line) {}
		bool operator<( const MemInfoKey_t &key ) const
		{
			int iret = stricmp( m_pFileName, key.m_pFileName );
			if ( iret < 0 )
				return true;

			if ( iret > 0 )
				return false;

			return m_nLine < key.m_nLine;
		}

		const char *m_pFileName;
		int			m_nLine;
	};

	// NOTE: This exactly mirrors the dbg header in the MSDEV crt
	// eventually when we write our own allocator, we can kill this
	struct CrtDbgMemHeader_t
	{
		unsigned char m_Reserved[8];
		const char *m_pFileName;
		int			m_nLineNumber;
		unsigned char m_Reserved2[16];
	};

	// NOTE: Deliberately using STL here because the UTL stuff
	// is a client of this library; want to avoid circular dependency

	// Maps file name to info
	typedef std::map< MemInfoKey_t, MemInfo_t > StatMap_t;
	typedef StatMap_t::iterator StatMapIter_t;
	typedef StatMap_t::value_type StatMapEntry_t;

	// Heap reporting method
	typedef void (*HeapReportFunc_t)( char const *pFormat, ... );

private:
	// Returns the actual debug info
	void GetActualDbgInfo( const char *&pFileName, int &nLine );

	// Finds the file in our map
	MemInfo_t &FindOrCreateEntry( const char *pFileName, int line );

	// Updates stats
	void RegisterAllocation( MemInfo_t &info, int nSize, int nTime );
	void RegisterDeallocation( MemInfo_t &info, int nSize, int nTime );

	// Gets the allocation file name
	const char *GetAllocatonFileName( void *pMem );
	int GetAllocatonLineNumber( void *pMem );

	// FIXME: specify a spew output func for dumping stats
	// Stat output
	void DumpMemInfo( const char *pAllocationName, int line, const MemInfo_t &info );
	void DumpFileStats();
	void DumpStats();

private:
	DbgInfoStack_t	m_DbgInfoStack[DBG_INFO_STACK_DEPTH];
	int m_nDbgInfoStackDepth;
	StatMap_t m_StatMap;
	MemInfo_t m_GlobalInfo;
	CFastTimer m_Timer;

	HeapReportFunc_t m_OutputFunc;

	static int s_pCountSizes[NUM_BYTE_COUNT_BUCKETS];
	static const char *s_pCountHeader[NUM_BYTE_COUNT_BUCKETS];
};

#endif