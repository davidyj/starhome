#ifdef UTILITY_VALIDATE_HEAP

#include "memalloc.h"

extern IMemAlloc &ActualAlloc( );

//-----------------------------------------------------------------------------
// NOTE! This should never be called directly from leaf code
// Just use new,delete,malloc,free etc. They will call into this eventually
//-----------------------------------------------------------------------------
class CValidateAlloc : public IMemAlloc
{
public:
	enum
	{
		HEAP_PREFIX_BUFFER_SIZE = 12,
		HEAP_SUFFIX_BUFFER_SIZE = 8,
	};

	CValidateAlloc();

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
	void* CrtSetReportFile( int nRptType, void* hFile );
	void* CrtSetReportHook( void* pfnNewHook );
	int CrtDbgReport( int nRptType, const char * szFile,
		int nLine, const char * szModule, const char * pMsg );
	virtual int heapchk();

	virtual void DumpStats() {}

private:
	struct HeapPrefix_t
	{
		HeapPrefix_t *m_pPrev;
		HeapPrefix_t *m_pNext;
		int m_nSize;
		unsigned char m_Prefix[HEAP_PREFIX_BUFFER_SIZE];
	};

	struct HeapSuffix_t
	{
		unsigned char m_Suffix[HEAP_SUFFIX_BUFFER_SIZE];
	};

private:
	HeapSuffix_t *Suffix( HeapPrefix_t *pPrefix );
	void *AllocationStart( HeapPrefix_t *pBase );
	HeapPrefix_t *PrefixFromAllocation( void *pAlloc );
	const HeapPrefix_t *PrefixFromAllocation( const void *pAlloc );

	// Add to the list!
	void AddToList( HeapPrefix_t *pHeap, int nSize );

	// Remove from the list!
	void RemoveFromList( HeapPrefix_t *pHeap );

	// Validate the allocation
	bool ValidateAllocation( HeapPrefix_t *pHeap );

private:
	HeapPrefix_t *m_pFirstAllocation;
	char m_pPrefixImage[HEAP_PREFIX_BUFFER_SIZE];
	char m_pSuffixImage[HEAP_SUFFIX_BUFFER_SIZE];
};

#endif