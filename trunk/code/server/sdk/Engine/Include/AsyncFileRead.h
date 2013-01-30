/*******************************************************************************
* ��Ȩ����(C) 2010ToSheng.com All right reserved
* �ļ����� : AsyncFileRead.h
* ��ǰ�汾 : 1.0.0.1
* ��    �� : david (david_yj@msn.com)
* ������� : 2010��12��24��
* ����ժҪ : ��Ҫʵ�����첽������Դ�ļ�����.
*		   : һ�������˶��̵߳ļ��ط�ʽ;��һ�������˷Ƕ��̵߳ļ��ط�ʽ
* �޸ļ�¼ : 
* ��    ��  ��    ��  �޸���   �޸�ժҪ
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
	 void * userArg;								// ���userPostloadCallback���õĲ��� remark by David 2010-12-24 14:49
	 pfnPostLoadCallBack userPostloadCallback;		// ���������ݺ���õĺ���
	 SCritSect * critSect;
	 bool		isLoaded;
	 bool		canReorder;
	 //@@
	 int        pos_after;
	 int        priority;
	 //TSLink<CAsyncObject> link;  //0x8
	 	 
};
class ENGINE_CLASS CAsyncObjectPriority//���������ȼ�ָ��
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
#ifdef _MINICLIENT		//�¼��� ���� ���غ���
ENGINE_GLOBAL void DownLoadInitialize( );	//������̬��Դ�����߳�
ENGINE_GLOBAL void A_GetCurrentDirectory(char (&path)[MAX_PATH]); //�õ���ǰ�ļ�·��
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
ENGINE_GLOBAL void AsyncFileCheckDeviceLost(bool isFlnish);//�����첽����ʱ�������Դ���ҵ�BUG --���� 2012��7��9��