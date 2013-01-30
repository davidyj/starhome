#include "../stdafx.h"
#include <windows.h>  
#include <psapi.h>  
#include <assert.h>  
#include <stdio.h>
#include <time.h>
#include "SystemPerformance.h"  

 
CSystemPerformance::CSystemPerformance()
{
}

CSystemPerformance::~CSystemPerformance()
{
}

/// 时间转换  
__int64 CSystemPerformance::_file_time_2_utc(const FILETIME* ftime)  
{  
    LARGE_INTEGER li;  
  
    assert(ftime);  
    li.LowPart = ftime->dwLowDateTime;  
    li.HighPart = ftime->dwHighDateTime;  
    return li.QuadPart;  
}
  
/// 获得CPU的核数  
int CSystemPerformance::GetProcessorNumber()  
{  
    SYSTEM_INFO info;  
    GetSystemInfo(&info);  
    return (int)info.dwNumberOfProcessors;  
}  

int CSystemPerformance::GetCpuUsage()  
{  
    //cpu数量  
    static int processor_count_ = -1;  
    //上一次的时间  
    static __int64 last_time_ = 0;  
    static __int64 last_system_time_ = 0;  
  
  
    FILETIME now;  
    FILETIME creation_time;  
    FILETIME exit_time;  
    FILETIME kernel_time;  
    FILETIME user_time;  
    __int64 system_time;  
    __int64 time;  
    __int64 system_time_delta;  
    __int64 time_delta;  
  
    int cpu = -1;  
  
  
    if(processor_count_ == -1)  
    {  
        processor_count_ = GetProcessorNumber();  
    }  
  
    GetSystemTimeAsFileTime(&now);  
  
    if (!GetProcessTimes(GetCurrentProcess(), &creation_time, &exit_time,  
        &kernel_time, &user_time))  
    {  
        // We don't assert here because in some cases (such as in the Task Manager)  
        // we may call this function on a process that has just exited but we have  
        // not yet received the notification.  
        return -1;  
    }  
    system_time = (_file_time_2_utc(&kernel_time) + _file_time_2_utc(&user_time)) / processor_count_;  
    time = _file_time_2_utc(&now);  
  
    if ((last_system_time_ == 0) || (last_time_ == 0))  
    {  
        // First call, just set the last values.  
        last_system_time_ = system_time;  
        last_time_ = time;  
        return -1;  
    }  
  
    system_time_delta = system_time - last_system_time_;  
    time_delta = time - last_time_;  
  
    assert(time_delta != 0);  
  
    if (time_delta == 0)  
        return -1;  
  
    // We add time_delta / 2 so the result is rounded.  
    cpu = (int)((system_time_delta * 100 + time_delta / 2) / time_delta);  
    last_system_time_ = system_time;  
    last_time_ = time;  
    return cpu;  
}  

int CSystemPerformance::GetMemoryUsage(__int64& mem, __int64& vmem)  
{  
    PROCESS_MEMORY_COUNTERS pmc;  
    if(GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))  
    {  
        mem = pmc.WorkingSetSize;  
        vmem = pmc.PagefileUsage;  
        return 0;  
    }  
    return -1;  
}  

int CSystemPerformance::GetIOBytes(__int64& read_bytes, __int64& write_bytes)  
{  
    IO_COUNTERS io_counter;  
    if(GetProcessIoCounters(GetCurrentProcess(), &io_counter))  
    {  
        read_bytes = io_counter.ReadTransferCount;  
        write_bytes = io_counter.WriteTransferCount;  
        return 0;  
    }  
    return -1;  
}
