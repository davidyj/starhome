#pragma once
#include "GLock.h"
#include "CommData.h"
struct playre_hash_param
{
	PersonID	pid;				// socket ֵ
	PVOID		param;				// ��Ӧ������
	playre_hash_param *	nextpram;			// ָ�����һ��Ԫ��
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
