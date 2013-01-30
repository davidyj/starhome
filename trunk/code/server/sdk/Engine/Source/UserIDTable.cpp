//
//
//		CUserIDTable:
//
//					idtable的组合类，专门用来保存用户id的table
//	
//					因为userid需要做 与、或处理，所以设计一个专门的类
//					管理userid；
//
//
//										yang jian
//										2004-5-31
///////////////////////////////////////////////////////////////////////////////////////
#include "../stdafx.h"
#include "UserIDTable.h"

#define USERIDTYPE 65536								//00000000 0000 0001 0000000000000000 用户的id
#define USERID 65535									//00000000 0000 0000 1111111111111111 
#define GETLOGIN 983040									//00000000 0000 1111 0000000000000000
#define GETSCENE 15728640								//00000000 1111 0000 0000000000000000 场景服务器的id

#define SETLOGININDEX( nn )		nn << 16				// 得到预算后的登陆服务器的值
#define SETSCENEINDEX( nn )		nn << 24				// 得到预算后的场景的索引
#define GETROLEINDEX( nn )		(nn & 65535)			// 得到主角得id			繁化简
#define GETLOGININDEX( nn )		((nn & GETLOGIN)>>16)	// 得到登陆服务器得索引 繁化简
#define GETSCENEINDEX( nn )		((nn & GETSCENE)>>20)	// 得到场景的index		繁化简

CUserIDTable::CUserIDTable(void)
{
	m_PlayerMax = 0;
	m_ServerMax=IDTABLECOULD;
}

CUserIDTable::~CUserIDTable(void)
{
	Release();
}

/////////////////////////////////////////////////////////////////////////////////////
//
//**************************************************************************
// FUNCTION:- InitArray
//
// RETURNS:
//			
//			
//
// PARAMETERS: 
//			nServerCounts	: 登陆服务器的数量
//			Counts			: 每个table分配的大小
//
// COMMENTS:
//			增加一项记录
//
//	REMARK:
//			
//
//						Yang Jian 
//						2004-5-31			
//
//**************************************************************************
void CUserIDTable::InitArray( int nServerCounts,int Counts )
{	
	m_PlayerMax = Counts;
	m_ServerMax = IDTABLECOULD;
	for( int i = 0;i<nServerCounts;i++ )
	{
		m_idtable[i].CreateArray( Counts );
	}
}
//**************************************************************************
// FUNCTION:- AddID
//
// RETURNS:
//			
//			
//
// PARAMETERS: 
//			
//			
//
// COMMENTS:
//			增加一项记录
//
//	REMARK:
//			
//
//						Yang Jian 
//						2004-5-31			
//
//**************************************************************************
/*
long CUserIDTable::AddID(unsigned long id,void *param)
{
	int nid	  = GETROLEINDEX( id );
	int index = GETLOGININDEX( id );	
	if(index>=0 && index < IDTABLECOULD && 	nid >=0 && nid<m_PlayerMax)
	{
		return m_idtable[ index ].AddID( nid ,param);
	}
	return 0;
}
*/
//**************************************************************************
// FUNCTION:- GetID
//
// RETURNS:
//			
//			
//
// PARAMETERS: 
//			
//			
//
// COMMENTS:
//			得到索引项的内容
//
//	REMARK:
//			
//
//						Yang Jian 
//						2004-5-31			
//
//**************************************************************************
void *CUserIDTable::GetID(unsigned long id)
{
	int index = GETLOGININDEX( id );
	int nid = GETROLEINDEX( id );
	if(index>=0 && index<IDTABLECOULD && 	nid >=0 && nid<m_PlayerMax)
	{
		return m_idtable[ index ].GetID( (unsigned long )nid );
	}
	return NULL;	
}
// 设置数组的内容
int CUserIDTable::SetID( unsigned long id,void *param )
{
	int index = GETLOGININDEX( id );
	int nid = GETROLEINDEX( id );
	if(index>=0 && index<IDTABLECOULD && 	nid >=0 && nid<m_PlayerMax)
	{
		return m_idtable[ index ].SetID( (unsigned long )nid ,param);
	}	
	return -1;
}
//**************************************************************************
// FUNCTION:- DeleteID
//
// RETURNS:
//			
//			
//
// PARAMETERS: 
//			
//			
//
// COMMENTS:
//			删除一项记录
//
//	REMARK:
//			
//
//						Yang Jian 
//						2004-5-31			
//
//**************************************************************************
void CUserIDTable::DeleteID(unsigned long id,void *param)
{
	int index = GETLOGININDEX( id );
	int nid = GETROLEINDEX( id );
	if(index>=0 && index<IDTABLECOULD && 	nid >=0 && nid<m_PlayerMax)
	{
		m_idtable[ index ].DeleteID( nid ,param);
	}	
}
void CUserIDTable::DeleteID(unsigned long id)
{
	int index = GETLOGININDEX( id );
	int nid = GETROLEINDEX( id );
	if(index>=0 && index<IDTABLECOULD && 	nid >=0 && nid<m_PlayerMax)
	{
		m_idtable[ index ].DeleteID( nid );
	}	
}
//**************************************************************************
// FUNCTION:- Find
//
// RETURNS:
//			
//			
//
// PARAMETERS: 
//			
//			
//
// COMMENTS:
//			查询用户的索引
//
//	REMARK:
//			需要特别注意的是：
//				再返回用户id的时候，需要返回游戏世界里的点!!!!!!!!!!!
//
//						Yang Jian 
//						2004-5-31			
//
//**************************************************************************
long CUserIDTable::Find(void *param)
{	
	unsigned long id = 0;
	for( int i = 0; i< IDTABLECOULD ; i++ )
	{
		id = m_idtable[i].Find( param );
		if( id )
		{				
			int loginindex = SETLOGININDEX( i );			
			return id + loginindex;
		}
	}
	return 0;
}

void CUserIDTable::Release()
{
		
}
