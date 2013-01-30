#include "../stdafx.h"

#ifdef WIN32
#include <malloc.h>
#else
#include <stdlib.h>
#endif
#include "dbg.h"
#include "memalloc.h"
#include "osAllocator.h"
#include "memdbg.h"
#include "memstd.h"
#include "memvalidate.h"


#ifndef UTILITY_VALIDATE_HEAP
IMemAlloc &MemAlloc( )
{
#if defined(X64_WIN) || defined(FREEBSD)

#ifdef _DEBUG
	static CDbgMemAlloc s_DbgMemAlloc;
	return s_DbgMemAlloc;
#else
	static CStdMemAlloc s_StdMemAlloc;
	return s_StdMemAlloc;
#endif

#else //X64_WIN

#ifdef _DEBUG
	static CDbgMemAlloc s_DbgMemAlloc;
	return s_DbgMemAlloc;
#else
	static CStdMemAlloc s_TbbMemAlloc;
	return s_TbbMemAlloc;
#endif

#endif //X64_WIN

}
#else //UTILITY_VALIDATE_HEAP
IMemAlloc &MemAlloc( )
{
	static CValidateAlloc s_ValidateAlloc;
	return s_ValidateAlloc;
}

IMemAlloc &ActualAlloc( )
{
#ifdef _DEBUG
	static CDbgMemAlloc s_DbgMemAlloc;
	return s_DbgMemAlloc;
#else
 	static CStdMemAlloc s_StdMemAlloc;
 	return s_StdMemAlloc;
#endif
}
#endif //UTILITY_VALIDATE_HEAP