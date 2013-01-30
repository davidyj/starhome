//
//	PlayerHashTable :
//		通过PersonID（int64） 定位 CPlayerObj。
//		因为一台服务器最多的人数不会大国2w人（GateWay）所以可以采用固定大小
//		的设计。
//		必须是线程安全的。
//
//
//
//							David 2010-07-12
//////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "PlayerHashTable.h"
#include "dbg.h"
#include "platform.h"
#include "atomic.h"

#define BASE_TEMPLATE_TABLE_SIZE	20000
#define HASH_CODE					17519			//素数

CPlayerHashTable::CPlayerHashTable()
{
	m_TableSize = 0;
	m_nCount	= 0;
	m_ElementTable = NULL;
	m_TempElementTable=NULL;
}

CPlayerHashTable::~CPlayerHashTable()
{
	Release();
}

bool CPlayerHashTable::Purge(int nSize)
{
	m_TableSize			= BASE_TEMPLATE_TABLE_SIZE;
	m_ElementTable		= (playre_hash_param *)Plat_Alloc(sizeof(playre_hash_param )*m_TableSize);
	if(!m_ElementTable)
		return false;
	for(int i=0;i<m_TableSize;i++)
	{
		m_ElementTable[i].Init();
	}

	m_TempElementTable	= (playre_hash_param *)Plat_Alloc(sizeof(playre_hash_param )*m_TableSize);
	if(!m_TempElementTable)
		return false;
	for(int i=0;i<m_TableSize;i++)
	{
		m_TempElementTable[i].Init();
	}
	return true;
}

void CPlayerHashTable::Release()
{
	if(m_ElementTable)
	{
		Plat_Free(m_ElementTable);
		m_ElementTable = NULL;
	}
}

bool CPlayerHashTable::Insert(PersonID pid,void* p)
{
	if(pid == INVALID_PID)
		return false;

	m_Lock.LOCK();
	int key = pid % HASH_CODE;

	if( m_ElementTable[key].pid == INVALID_PID)
	{
		m_ElementTable[key].pid = pid;
		m_ElementTable[key].param = p;
		InterlockedIncrement(&m_nCount);
		m_Lock.UNLOCK();

		return true;
	}

	playre_hash_param * np = NULL;
	//在备用table找到一个空闲的位置
	for(int i=0;i<m_TableSize;i++)
	{
		if(m_TempElementTable[i].pid == INVALID_PID)
		{
			m_TempElementTable[i].pid = pid;
			m_TempElementTable[i].param = p;
			np = &m_TempElementTable[i];

			break;
		}
	}

	playre_hash_param * tp = &m_ElementTable[key];
	while(tp)
	{
		if(!tp->nextpram)
		{
			tp->nextpram = np;
			break;
		}
		else
			tp = tp->nextpram;
	}
	InterlockedIncrement(&m_nCount);
	m_Lock.UNLOCK();
	return true;
}

void* CPlayerHashTable::Find(PersonID pid)
{
	if(pid == INVALID_PID)
		return false;

	int key = pid % HASH_CODE;

	playre_hash_param * tp = &m_ElementTable[key];
	while(true)
	{
		if( tp->pid == pid)
			return tp->param;
		tp = tp->nextpram;
		if(!tp)
			return NULL;
	}

	return NULL;

}

bool CPlayerHashTable::Remove(PersonID pid)
{
	if(pid == INVALID_PID)
		return false;


	m_Lock.LOCK();
	int key = pid % HASH_CODE;

	playre_hash_param * p = &m_ElementTable[key];
	while(p)
	{
		if( p->pid == pid)
		{
			if(p->nextpram)
			{
				playre_hash_param * tp = p->nextpram;

				//保证链表的连续
				p->pid		= tp->pid;
				p->param	= tp->param;
				p->nextpram = tp->nextpram;
				tp->Init();
				InterlockedDecrement(&m_nCount);
				Log("hash second remove by sock:%I64d",pid);
			}
			else
			{
				p->Init();

				InterlockedDecrement(&m_nCount);
				//Log("hash first remove by sock:%d",s);
			}
			break;
		}
		else
			p  = p->nextpram;
	}
	m_Lock.UNLOCK();
	return true;
}
int CPlayerHashTable::Count()
{
	return m_nCount;
}
