/*******************************************************************************
* 版权所有(C) 2010ToSheng.com All right reserved
* 文件名称 : AsyncFileRead.h
* 当前版本 : 1.0.0.1
* 作    者 : david (david_yj@msn.com)
* 设计日期 : 2010年12月24日
* 内容摘要 : 主要实现了异步加载资源文件的类.
*		   : 一个采用了多线程的加载方式;另一个采用了非多线程的加载方式
* 修改记录 : 
* 日    期  版    本  修改人   修改摘要
********************************************************************************/
#pragma once
#include "EngineDefine.h"
#include "SFile2.h"
#include "SLock.h"
#include "utllinkedlist.h"

typedef void ( *pfnAsyncHandler ) (void );
typedef void ( *pfnPostLoadCallBack ) ( void *userArg );
class ENGINE_CLASS CAsyncObject
{
public:
	CAsyncObject( );
	~CAsyncObject( );
public:
	 void * file;
	 ULONG	offset;
	 void *buffer;
	 ULONG	size;
	 void * userArg;								// 配合userPostloadCallback调用的参数 remark by David 2010-12-24 14:49
	 pfnPostLoadCallBack userPostloadCallback;		// 加载完数据后调用的函数
	 SCritSect * critSect;
	 bool		isLoaded;
	 bool		canReorder;
	 //@@
	 int        pos_after;
	 int        priority;
	 //TSLink<CAsyncObject> link;  //0x8
	 	 
};
class ENGINE_CLASS CAsyncObjectPriority//管理几个优先级指针
{
public:
	CAsyncObjectPriority();
	~CAsyncObjectPriority();
	static CAsyncObjectPriority* Mgr();
	int GetObjPriority();
	void SetObjPriority( int a_priority);
	int GetObjectIDbyPriority( int a_priority);
	void SetObjectIDbyPriority( int a_priority,int a_id);
	void PreDeleteObj(void* a_object);
	void RefreshObjectIDbyPriority();
	void IfUsePriority( bool a_usepriority);
public:
	int m_highest;
	int m_first;
	int m_second;
	int m_third;
	int m_objPriority;
	static CAsyncObjectPriority* ms_mgr;
	bool m_bUsePriority;
};

ENGINE_GLOBAL void AsyncFileReadInitialize( );
#ifdef _MINICLIENT		//新加了 两个 下载函数
ENGINE_GLOBAL void DownLoadInitialize( );	//创建动态资源下载线程
ENGINE_GLOBAL void A_GetCurrentDirectory(char (&path)[MAX_PATH]); //得到当前文件路径
#endif
ENGINE_GLOBAL void AsyncFileReadDestroy( );
ENGINE_GLOBAL CAsyncObject *AsyncFileReadCreateObject( );
ENGINE_GLOBAL void *AsyncFileReadDestroyObject( CAsyncObject *object );
ENGINE_GLOBAL void AsyncFileReadAddHandler( pfnAsyncHandler handler );
ENGINE_GLOBAL void AsyncFileReadPollHandler( );
ENGINE_GLOBAL void AsyncFileReadObject( CAsyncObject * object );
ENGINE_GLOBAL void AsyncFileReadWaitAll( );
ENGINE_GLOBAL void AsyncFileSleepWait( );
ENGINE_GLOBAL void AsyncFileReadWakeup( );
ENGINE_GLOBAL CUtlLinkedList<CAsyncObject *>* IAsyncFileReadList();
ENGINE_GLOBAL void SetAsyncLock( bool a_lock);
ENGINE_GLOBAL bool AsyncFileReadIsReading();
ENGINE_GLOBAL void AsyncFileCheckDeviceLost(bool isFlnish);//处理异步加载时候添加资源混乱的BUG --王鹏 2012年7月9日