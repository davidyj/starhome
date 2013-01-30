#ifndef PROCESS_H
#define PROCESS_H
#ifndef WIN32
#include <sys/types.h>
#include <unistd.h>
#endif


/*
 * 进程操作相关的函数
 */
#ifndef WIN32
//获取当前进程id,win32有同名函数
int GetCurrentProcessId();
#endif

#endif
