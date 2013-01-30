#pragma once
#include "EngineDefine.h"
class ENGINE_CLASS CVectorTable
{
public:
	CVectorTable(void);
	~CVectorTable(void);

public:	
	int		AddTail(void *parm);
	int		Insert( int nIndex,void *parm);
	void*	Get(int Index);
	void	CreateMemory(int nSize);
	void	Remorve(int index);
protected:
	int		m_Size;
	int		m_nCursor;			// 当前的写指针
//	DWORD*	m_Table;
	uintptr_t*  m_Table;
};
