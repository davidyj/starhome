#include "StdAfx.h"
#include "SocketHashTable.h"
#include "platform.h"
#include "dbg.h"

#define BASE_TEMPLATE_TABLE_SIZE	100000

CSocketHashTable::CSocketHashTable()
{
	m_TableSize = 0;
	m_TempTableSize = 0;
	m_TempTableIdx  = 0;
	m_ElementTable  = NULL;
	m_TempElementTable = NULL;
}

CSocketHashTable::~CSocketHashTable()
{
	Release();
}

void CSocketHashTable::Purge(int nSize)
{	
	m_TableSize			= nSize * 8;
	m_TempTableSize		= nSize;

	m_ElementTable		= (hash_param*)Plat_Alloc(sizeof(hash_param)*m_TableSize);
	for(int i=0;i<m_TableSize;i++)
	{
		m_ElementTable[i].Init();
	}

	m_TempElementTable	= (hash_param*)Plat_Alloc(sizeof(hash_param)*m_TempTableSize);
	for(int i=0;i<m_TempTableSize;i++)
	{
		m_TempElementTable[i].Init();
	}	
}

void CSocketHashTable::Release()
{
	if(m_ElementTable)
	{
		Plat_Free(m_ElementTable);
		m_ElementTable = NULL;
	}
}

bool CSocketHashTable::Insert(SOCKET s,void* p)
{
	if(s == INVALID_SOCKET)
		return false;

	m_Lock.LOCK();
	int key = s % m_TableSize;

	if( m_ElementTable[key].sock == INVALID_SOCKET)
	{
		m_ElementTable[key].sock = s;
		m_ElementTable[key].param = p;
		m_Lock.UNLOCK();
	
		return true;
	}
	
	hash_param* np = NULL;
	//在备用table找到一个空闲的位置
	for(int i=0;i<m_TempTableSize;i++)		
	{
		m_TempTableIdx++;
		if(m_TempTableIdx>=m_TempTableSize) { m_TempTableIdx = 0; }

		if(m_TempElementTable[m_TempTableIdx].sock == INVALID_SOCKET)
		{
			m_TempElementTable[m_TempTableIdx].sock = s;
			m_TempElementTable[m_TempTableIdx].param = p;				
			np = &m_TempElementTable[m_TempTableIdx];
		
			break;
		}
	}

	if( np == NULL )
	{
		Log("CSocketHashTable::Insert 未找到空闲空间！");
		return false;
	}

	hash_param* tp = &m_ElementTable[key];
	while(tp)
	{
		if(!tp->nextpram)
		{
			//if(tp == np){
			//	Log("abc");
			//}
			tp->nextpram = np;
			break;
		}
		else
			tp = tp->nextpram;
	}
	m_Lock.UNLOCK();
	return true;
}

void* CSocketHashTable::Find(SOCKET s)
{
	if(s == INVALID_SOCKET)
		return false;

	void* res = NULL;
	int key = s % m_TableSize;

	m_Lock.LOCK();
	hash_param* tp = &m_ElementTable[key];
	while(tp!=NULL)
	{
		if(tp->sock == s)
		{
			res = tp->param;
			break;
		}
		tp = tp->nextpram;		
	}
	m_Lock.UNLOCK();
	return res;
}

bool CSocketHashTable::Remove(SOCKET s)
{
	if(s == INVALID_SOCKET)
		return false;

	m_Lock.LOCK();
	int key = s % m_TableSize;
	
	hash_param* p = &m_ElementTable[key];
	hash_param* pre = p;
	while(p)
	{
		if(p->sock == s)
		{			
			if(p->nextpram)
			{
				hash_param* tp = p->nextpram;

				//保证链表的连续
				p->sock		= tp->sock;
				p->param	= tp->param;
				//if(tp->nextpram == p){
				//	Log("abc");
				//}
				p->nextpram = tp->nextpram;
				tp->Init();		
				Log("hash second remove by sock:%d",s);
			}	
			else
			{
				p->Init();
				pre->nextpram = NULL;
				//Log("hash first remove by sock:%d",s);
			}
			break;
		}
		else
		{
			pre = p;
			p  = p->nextpram;
		}
	}
	m_Lock.UNLOCK();
	return true;
}
