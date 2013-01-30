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

    /// ��ȡ��ǰ���̵�cpuʹ���ʣ�����-1ʧ��
    int GetCpuUsage();

    /// ��ȡ��ǰ�����ڴ�������ڴ�ʹ����������-1ʧ�ܣ�0�ɹ�
    int GetMemoryUsage(__int64& mem, __int64& vmem);

    /// ��ȡ��ǰ�����ܹ�����д��IO�ֽ���������-1ʧ�ܣ�0�ɹ�
    int GetIOBytes(__int64& read_bytes, __int64& write_bytes);

	/// ��ȡcpu����
	int	GetProcessorNumber();

};
#endif  //  WIN32

#endif	//SYSTEM_PERFORMANCE_H
