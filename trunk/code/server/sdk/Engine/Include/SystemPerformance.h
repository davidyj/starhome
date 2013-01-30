#ifndef SYSTEM_PERFORMANCE_H
#define SYSTEM_PERFORMANCE_H
#ifdef WIN32
#include "EngineDefine.h"


class ENGINE_CLASS CSystemPerformance
{
private:
	CSystemPerformance();
	~CSystemPerformance();

	int64 _file_time_2_utc(const FILETIME* ftime);

public:
	static CSystemPerformance& getSingle()
	{
		static CSystemPerformance mgr;
		return mgr;
	}

    /// 获取当前进程的cpu使用率，返回-1失败
    int GetCpuUsage();

    /// 获取当前进程内存和虚拟内存使用量，返回-1失败，0成功
    int GetMemoryUsage(__int64& mem, __int64& vmem);

    /// 获取当前进程总共读和写的IO字节数，返回-1失败，0成功
    int GetIOBytes(__int64& read_bytes, __int64& write_bytes);

	/// 获取cpu数量
	int	GetProcessorNumber();

};
#endif  //  WIN32

#endif	//SYSTEM_PERFORMANCE_H
