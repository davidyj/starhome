#pragma once
#include "EngineDefine.h"
#include "IDTable.h"

#define IDTABLECOULD  5				// ��½�������������
const int USERTABLE_MAX = 20000;		// һ̨��¼�����������������
#define ARRARYSIZE	70000				// table�ķ���Ŀռ�Ĵ�С
//////////////////////////////////////////////////////////////////////////////////
//
class ENGINE_CLASS CUserIDTable 
{
public:
	CUserIDTable(void);
	~CUserIDTable(void);

public:
	CIDTable m_idtable[ IDTABLECOULD ];

public:
	//����һ������	
	void InitArray( int nServerCounts,int Counts );
	
	//����ڴ�
	void Release();

	//���������������
//	virtual long AddID(unsigned long id ,void *param);			

	//ɾ��һ��id
	virtual void DeleteID(unsigned long id,void *param);					
	virtual void DeleteID(unsigned long id);		

	//��ѯ�û�������
	virtual long Find( void *param);

	//�õ��û�����������
	virtual void *GetID( unsigned long id);
	// �������������
	virtual int SetID( unsigned long id,void *param );

protected:	
	int m_ServerMax;
	int m_PlayerMax;
};
