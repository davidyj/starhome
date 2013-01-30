// SocketHashTable:
// 利用 socket做key值的hash表的实现
// 利用益处hash表的方式
// 是线程安全的
#pragma once
#include "Gamenetcommondefine.h"
#include "GLock.h"

struct hash_param 
{
	SOCKET		sock;				// socket 值
	PVOID		param;				// 对应的类型
	hash_param*	nextpram;			// 指向的下一个元素
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
