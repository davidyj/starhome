#pragma once
#include "EngineDefine.h"
#include "IDTable.h"

#define IDTABLECOULD  5				// 登陆服务器得最大数
const int USERTABLE_MAX = 20000;		// 一台登录服务器创建的最大数
#define ARRARYSIZE	70000				// table的分配的空间的大小
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
	//创建一个数组	
	void InitArray( int nServerCounts,int Counts );
	
	//清楚内存
	void Release();

	//想数组中添加数据
//	virtual long AddID(unsigned long id ,void *param);			

	//删除一个id
	virtual void DeleteID(unsigned long id,void *param);					
	virtual void DeleteID(unsigned long id);		

	//查询用户的索引
	virtual long Find( void *param);

	//得到用户索引的内容
	virtual void *GetID( unsigned long id);
	// 设置数组的内容
	virtual int SetID( unsigned long id,void *param );

protected:	
	int m_ServerMax;
	int m_PlayerMax;
};
