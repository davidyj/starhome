//
//	CIDTable:
//		管理数组的类；
//	
//		1、该类负责管理数组，数组中对应这用户的id和用户相关信息的map
//		2、再这一次做互斥处理，可以减少工作量
//		
//
//
//										 Yang Jian 
//
//
//											2002-3-3
//
//////////////////////////////////////////////////////////////////////////
#include "../stdafx.h"
#include "IDTable.h"
#include "GLock.h"
#include "platform.h"
#include "dbg.h"
#include <string.h>
#pragma warning (disable:4311)
//////////////////////////////////////////////////////////////////////////
//
static int sc=0;
CIDTable::CIDTable(void)
{
	m_nCursor = 0;
	m_pArray = NULL;	
	m_nCount = 0;
	m_nMemorySize = 0;	
}

CIDTable::CIDTable(DWORD nSize)
{	
	m_pArray = NULL;	
	m_nCount=0;
	m_nCursor=0;
	m_nMemorySize = nSize;	
	CreateArray(nSize);	
}

CIDTable::~CIDTable(void)
{
	ClearUp();		
}

// FUNCTION:- InitArray()
void CIDTable::InitArray()
{}

// FUNCTION:- CreateArray()
void *CIDTable::CreateArray(DWORD dSize)
{	
//	m_pArray = (DWORD  *)Plat_Alloc(sizeof(DWORD)*dSize);
	m_pArray = (uintptr_t  *)Plat_Alloc(sizeof(uintptr_t)*dSize);
	if (!m_pArray) {
		Log("failed allocate mem for m_pArray in file %s line %d\n", __FILE__, __LINE__);
		return NULL;
	}
//	memset(m_pArray, 0, sizeof(DWORD)*dSize);
	memset(m_pArray, 0, sizeof(uintptr_t)*dSize);
	m_nMemorySize = dSize;		
	return m_pArray;
}


// FUNCTION:- GetCursor()
int CIDTable::SetCursor()
{		
	m_Lock.LOCK();
	Assert( m_pArray );

	if( m_nCursor >= m_nMemorySize )
		m_nCursor = 0;

	UINT nCount = 0;
	while( TRUE )
	{					
		m_nCursor++;
		if( m_nCursor >= m_nMemorySize )
			m_nCursor = 1;		//by  2006.10.19 修改第0个位置不能分配
		if( m_pArray[m_nCursor] == 0 )
			break;							
		if( ++nCount >= m_nMemorySize )
		{			
			//UnLock( );
			m_Lock.UNLOCK();
			AssertMsg( FALSE, "CIDTable::SetCursor() full!" );
			Log( "CIDTable::SetCursor( ) full!" );
			return -1;
		}	
	}
	m_Lock.UNLOCK();

	return m_nCursor;
}


// //FUNCTION:- AddID()
//int CIDTable::AddID( DWORD id, void *param )
//{			
//	Assert( id >= 0 && id < m_nMemorySize );
//	if( id <= 0 || id >= m_nMemorySize )
//		return -1;	
//	if( !m_pArray )
//		return -1;
//
//	m_Lock.LOCK();
//	m_pArray[id] = (DWORD)param;	
//	m_nCount++;	
//	m_Lock.UNLOCK();
//
//	return id;
//}


// FUNCTION:- AddID()
int CIDTable::AddID( void *param )
{
	int id = 0;	
	id=SetCursor( );
	if( id < 0 )
		return -1;	

	if( !m_pArray )
		return -1;		

	m_Lock.LOCK();
	if( !m_pArray[m_nCursor] )
	{	
//		m_pArray[m_nCursor] = (DWORD)param;
		m_pArray[m_nCursor] = (uintptr_t)param;
		id = m_nCursor;		
		m_nCount++;	
		//UnLock( );
		m_Lock.UNLOCK();
		return id;
	}
	m_Lock.UNLOCK();

	Log( "插入Table不成功！" );
	return -1;
}

int CIDTable::CreateID( )
{
	int id = 0;	
	id=SetCursor( );
	if( id < 0 )
		return -1;	

	if( !m_pArray )
		return -1;		

	m_Lock.LOCK();
	if( !m_pArray[m_nCursor] )
	{		
		id = m_nCursor;		
		m_nCount++;	
		//UnLock( );
		m_Lock.UNLOCK();
		return id;
	}
	m_Lock.UNLOCK();

	Log( "插入Table不成功！" );
	return -1;
}
void CIDTable::AddID( DWORD id, void *param )
{
	m_Lock.LOCK();
//	m_pArray[id] = (DWORD)param;
	m_pArray[id] = (uintptr_t)param;
	m_Lock.UNLOCK();
}

// FUNCTION:- DeleteID()
void CIDTable::DeleteID( DWORD id )
{
	Assert( id >= 0 && id < m_nMemorySize );
	if( id <= 0 || id >= m_nMemorySize )
	{
		Log( "CIDTable::DeleteID %d", id );
		return;
	}

	if(!m_pArray)
		return ;	

	m_Lock.LOCK();
	Assert( m_pArray[id] != 0 );
	if( m_pArray[id] != 0 )
	{
		m_pArray[id] = 0;
		m_nCount--;	
	}
	else
	{
		Log( "CIDTable::DeleteID( DWORD id ) %d", id );
	}
	m_Lock.UNLOCK();

	return;	
}

// FUNCTION:- DeleteID()
void CIDTable::DeleteID( DWORD id, void *param )
{
 	Assert( id > 0 && id < m_nMemorySize );
	if( id <= 0 || id >= m_nMemorySize )
		return ;

	if(!m_pArray)
		return;

	m_Lock.LOCK( );
//	Assert( m_pArray[id] == (DWORD)param );
//	if( m_pArray[id] == (DWORD)param )
	Assert( m_pArray[id] == (uintptr_t)param );
	if( m_pArray[id] == (uintptr_t)param )
	{
		m_pArray[id] = 0;
		m_nCount--;
	}
	else
	{
		Log( "CIDTable::DeleteID( DWORD id, void *param ) %d", id );
	}
	m_Lock.UNLOCK( );

	return;	
}

// FUNCTION:- GetTableID()
void *CIDTable::GetID(DWORD id)
{
	Assert( id >= 0 && id < m_nMemorySize );
	if( id >= 0 && id < m_nMemorySize )
	{
		if( m_pArray )
			return (void*)m_pArray[id];
	}	
	return NULL;
}

int CIDTable::SetID( DWORD id, void *param )
{
	Assert( id >= 0 && id < m_nMemorySize );
	if( id >= 0 && id < m_nMemorySize )
	{
		if( m_pArray )
		{
			Assert( m_pArray[id] == NULL );
			if( m_pArray[id] == NULL )
			{
//				m_pArray[id] = (DWORD)param;
				m_pArray[id] = (uintptr_t)param;
				return id;
			}
			Log( "CIDTable::SetID %d", id );
		}
	}
	return -1;
}

// FUNCTION:- Find()
int CIDTable::Find( void *ptr )
{
	for( DWORD i = 1; i < m_nMemorySize; i++ )
	{
//		if( m_pArray[i] == (DWORD)ptr )
		if( m_pArray[i] == (uintptr_t)ptr )
			return i;
	}
	return -1;
}

// Get Data
void *CIDTable::operator []( DWORD id )
{
	return GetID( id );
}

// 删除内存
void CIDTable::DeleteArray( )
{
	if( m_pArray )
	{
		Plat_Free( m_pArray );
		m_pArray = NULL;
	}	
	m_nCount = 0;
	m_nCursor = 0;
}

void CIDTable::ClearUp( )
{
	DeleteArray( );	
}
