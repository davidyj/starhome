//
//
//		CUserIDTable:
//
//					idtable������࣬ר�����������û�id��table
//	
//					��Ϊuserid��Ҫ�� �롢�����������һ��ר�ŵ���
//					����userid��
//
//
//										yang jian
//										2004-5-31
///////////////////////////////////////////////////////////////////////////////////////
#include "../stdafx.h"
#include "UserIDTable.h"

#define USERIDTYPE 65536								//00000000 0000 0001 0000000000000000 �û���id
#define USERID 65535									//00000000 0000 0000 1111111111111111 
#define GETLOGIN 983040									//00000000 0000 1111 0000000000000000
#define GETSCENE 15728640								//00000000 1111 0000 0000000000000000 ������������id

#define SETLOGININDEX( nn )		nn << 16				// �õ�Ԥ���ĵ�½��������ֵ
#define SETSCENEINDEX( nn )		nn << 24				// �õ�Ԥ���ĳ���������
#define GETROLEINDEX( nn )		(nn & 65535)			// �õ����ǵ�id			������
#define GETLOGININDEX( nn )		((nn & GETLOGIN)>>16)	// �õ���½������������ ������
#define GETSCENEINDEX( nn )		((nn & GETSCENE)>>20)	// �õ�������index		������

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
//			nServerCounts	: ��½������������
//			Counts			: ÿ��table����Ĵ�С
//
// COMMENTS:
//			����һ���¼
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
//			����һ���¼
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
//			�õ������������
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
// �������������
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
//			ɾ��һ���¼
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
//			��ѯ�û�������
//
//	REMARK:
//			��Ҫ�ر�ע����ǣ�
//				�ٷ����û�id��ʱ����Ҫ������Ϸ������ĵ�!!!!!!!!!!!
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
