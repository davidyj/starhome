#ifndef CRTDBG_FREEBSD
#define CRTDBG_FREEBSD

#define _HOOK_ALLOC     1
#define _HOOK_REALLOC   2
#define _HOOK_FREE      3

typedef int (* _CRT_ALLOC_HOOK)(int, void *, size_t, int, long, const unsigned char *, int);


//these macros are copied from crtdbg.h of windows
/* Memory block identification */
#define _FREE_BLOCK      0
#define _NORMAL_BLOCK    1
#define _CRT_BLOCK       2
#define _IGNORE_BLOCK    3
#define _CLIENT_BLOCK    4
#define _MAX_BLOCKS      5

typedef void (* _CRT_DUMP_CLIENT)(void *, size_t);


#define _malloc_dbg(s, t, f, l)         malloc(s)
#define _calloc_dbg(c, s, t, f, l)      calloc(c, s)
#define _realloc_dbg(p, s, t, f, l)     realloc(p, s)
#define _free_dbg(p, t)                 free(p)
#define   _expand(p, s)     		NULL
#define _msize_dbg(p, t)		0
#define _CrtSetReportMode(t, f)		0
#define _CrtSetReportFile(t, f)             (0)


#define _CrtDbgBreak()                      ((void)0)
#define _CrtSetBreakAlloc(a)                ((long)0)
#define _CrtSetAllocHook(f)                 ((_CRT_ALLOC_HOOK)0)
#define _CrtCheckMemory()                   ((int)1)
#define _CrtSetDbgFlag(f)                   ((int)0)
#define _CrtDoForAllClientObjects(f, c)     ((void)0)
#define _CrtIsValidPointer(p, n, r)         ((int)1)
#define _CrtIsValidHeapPointer(p)           ((int)1)
#define _CrtIsMemoryBlock(p, t, r, f, l)    ((int)1)
#define _CrtReportBlockType(p)              ((int)-1)
#define _CrtSetDumpClient(f)                ((_CRT_DUMP_CLIENT)0)
#define _CrtMemCheckpoint(s)                ((void)0)
#define _CrtMemDifference(s1, s2, s3)       ((int)0)
#define _CrtMemDumpAllObjectsSince(s)       ((void)0)
#define _CrtMemDumpStatistics(s)            ((void)0)
#define _CrtDumpMemoryLeaks()               ((int)0)



#endif
