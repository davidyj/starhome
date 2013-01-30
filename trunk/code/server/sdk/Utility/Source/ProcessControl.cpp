/*
 * 进程操作相关函数
 *
 * 创建人:鲁建东 
 * 时间:2009.10.20
 */

#include "../Port/config.h"
#include "ProcessControl.h"



#ifndef WIN32
int GetCurrentProcessId()
{
	return getpid();
}
#endif

