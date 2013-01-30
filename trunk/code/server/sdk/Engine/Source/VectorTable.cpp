#include "../stdafx.h"
#include "VectorTable.h"
#include "CommDef.h"

CVectorTable::CVectorTable(void)
{
	m_nCursor=0;
	m_Table=0;
	m_Size=0;
}

CVectorTable::~CVectorTable(void)
{
	SAFE_DELETE(m_Table);
}
//////////////////////////////////////////
//
void CVectorTable::CreateMemory(int nSize)
{
	m_Size = nSize;
//	m_Table = new DWORD[nSize];
//	memset( m_Table, 0, sizeof(DWORD)* nSize );
	m_Table = new uintptr_t[nSize];
	memset( m_Table, 0, sizeof(uintptr_t)* nSize );
}
int CVectorTable::AddTail(void *parm)
{
	int id = m_nCursor;
//	m_Table[m_nCursor]=(DWORD)parm;
	m_Table[m_nCursor]=(uintptr_t)parm;
	m_nCursor++;
	if(m_nCursor >= m_Size )
		m_nCursor = 0;
	return id;
}
int CVectorTable::Insert(int Index,void *parm)
{
	if( Index < m_Size && Index >= 0 )
	{
//		m_Table[Index]=(DWORD)parm;
		m_Table[Index]=(uintptr_t)parm;
		m_nCursor = Index;
		return m_nCursor;
	}
	return 0;
}
void *CVectorTable::Get( int Index )
{
	if( Index < m_Size && Index >=0 )
	{
		return (void *)m_Table[Index];
	}
	return NULL;
}

void CVectorTable::Remorve(int index)
{
	if( index < m_Size && index >= 0 )
	{
		m_Table[index]=0;
	}
}
