#pragma once
#include "GLock.h"
#include "CommData.h"
struct playre_hash_param
{
	PersonID	pid;				// socket 值
	PVOID		param;				// 对应的类型
	playre_hash_param *	nextpram;			// 指向的下一个元素
	void Init()
	{
		pid = INVALID_PID;
		param = NULL;
		nextpram = NULL;
	}
};

class CPlayerHashTable
{
public:
	CPlayerHashTable();
	~CPlayerHashTable();

	bool Purge(int nSize);
	void Release();

	bool Insert(PersonID pid,void* p);
	void* Find(PersonID pid);
	bool Remove(PersonID pid);
	int	 Count();

protected:
	int			m_TableSize;
	CGLock		m_Lock;
	playre_hash_param *	m_ElementTable;
	playre_hash_param *	m_TempElementTable;
	LONG		m_nCount;
};
