// SocketHashTable:
// ���� socket��keyֵ��hash���ʵ��
// �����洦hash��ķ�ʽ
// ���̰߳�ȫ��
#pragma once
#include "Gamenetcommondefine.h"
#include "GLock.h"

struct hash_param 
{
	SOCKET		sock;				// socket ֵ
	PVOID		param;				// ��Ӧ������
	hash_param*	nextpram;			// ָ�����һ��Ԫ��
	void Init()
	{
		sock     = INVALID_SOCKET;
		param    = NULL;
		nextpram = NULL;
	}
};

class GAMENETCOMMON_CLASS CSocketHashTable
{
public:
	CSocketHashTable();
	~CSocketHashTable();	

	void Purge(int nSize);
	void Release();

	bool Insert(SOCKET s,void* p);
	void* Find(SOCKET s);
	bool Remove(SOCKET s);

protected:
	int			m_TableSize;
	int			m_TempTableSize;
	int			m_TempTableIdx;
	CGLock		m_Lock;
	hash_param*	m_ElementTable;
	hash_param*	m_TempElementTable;
};
