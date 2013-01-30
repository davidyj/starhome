#ifndef _DEBUG

#if !defined(X64_WIN) && !defined(FREEBSD)

#include <malloc.h>
#include "dbg.h"
#include "memalloc.h"
#include "osAllocator.h"

class CTbbMemAlloc : public IMemAlloc
{
public:
	virtual void *Alloc( size_t nSize );
	virtual void *Realloc( void *pMem, size_t nSize );
	virtual void  Free( void *pMem );
	virtual void *Expand( void *pMem, size_t nSize );

	virtual void *Alloc( size_t nSize, const char *pFileName, int nLine );
	virtual void *Realloc( void *pMem, size_t nSize, const char *pFileName, int nLine );
	virtual void  Free( void *pMem, const char *pFileName, int nLine );
	virtual void *Expand( void *pMem, size_t nSize, const char *pFileName, int nLine );

	virtual size_t GetSize( void *pMem );

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
};

#endif //X64_WIN
#endif //_DEBUG