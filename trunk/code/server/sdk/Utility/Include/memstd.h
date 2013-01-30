#ifndef _DEBUG

#ifdef WIN32
#include <malloc.h>
#else
#include <stdlib.h>
#endif
#include "dbg.h"
#include "memalloc.h"
#include "osAllocator.h"

//-----------------------------------------------------------------------------
// NOTE! This should never be called directly from leaf code
// Just use new,delete,malloc,free etc. They will call into this eventually
//-----------------------------------------------------------------------------
class CStdMemAlloc : public IMemAlloc
{
public:
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
};

#endif