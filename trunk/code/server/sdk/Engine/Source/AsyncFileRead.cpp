#include "../stdafx.h"
#include <stdlib.h>
#ifdef _MINICLIENT
#include "SLock.h"
#include "DynamicResMgr.h"
#endif
#include "AsyncFileRead.h"
#include "SLock.h"

#include "platform.h"
#include "dbg.h"
#ifdef WIN32
#include <mmsystem.h>
#endif
//=========================

static SCritSect s_queueLock;
static SEvent s_shutdownEvent( true , false );  //bManualReset = true;bInitialState = false;
static SEvent s_sleepEvent( false , false );  //bManualReset = true;bInitialState = false;

static SEvent s_queueEvent( false, false );
static SThread s_asyncReadThread;
#ifdef _MINICLIENT
static SThread s_DownLoadThread;
#endif
static CAsyncObject *s_asyncCurrentObject = NULL;
static volatile CAsyncObject *s_asyncWaitObject = NULL;  //?? volatile

static CUtlLinkedList<CAsyncObject *> s_asyncFileReadList;			//all file to read
static CUtlLinkedList<CAsyncObject *> s_asyncFileReadPostList;		//all file buffer

static CUtlLinkedList<pfnAsyncHandler> s_handlers_AsyncFileRead;	//all read handle
static bool bCheckLostFlnish = false;
//===========
CAsyncObject::CAsyncObject( )
{
	file = NULL;
	offset = 0;
	buffer = NULL;
	size = 0;
	userArg = NULL;
	userPostloadCallback = NULL;
	critSect = NULL;
	isLoaded = false;
	canReorder = true;
	pos_after = -1;
	priority = 3;
}

CAsyncObject::~CAsyncObject( )
{

}

CAsyncObjectPriority::CAsyncObjectPriority( )
{
	m_highest = -1;
	m_first = -1;
	m_second = -1;
	m_third = -1;
	m_objPriority = 3;
	m_bUsePriority = true;
}
CAsyncObjectPriority::~CAsyncObjectPriority( )
{
}

CAsyncObjectPriority* CAsyncObjectPriority::Mgr()
{

	if( !ms_mgr)
		ms_mgr = new CAsyncObjectPriority;
	 return ms_mgr;
}
CAsyncObjectPriority* CAsyncObjectPriority::ms_mgr = NULL;

//------------------------------------------------------------------------------------------------
CAsyncObjectPriority* objPriorityMgr = new CAsyncObjectPriority;
//------------------------------------------------------------------------------------------------

//=======
//static DWORD WINAPI AsyncFileReadThread( void * param );
#ifdef WIN32
static DWORD WINAPI AsyncFileReadThread( void * param );
#ifdef _MINICLIENT
static DWORD WINAPI AsyncDownLoadThread( void * param );
#endif
#else
static void* AsyncFileReadThread( void * param );
#ifdef _MINICLIENT
static void* AsyncDownLoadThread( void * param );
#endif
#endif

/*******************************************************************************
* �������� : AsyncFileReadInitialize
* �������� : ��ʼ�����̼߳��������߳�
* �� �� ֵ : void
* �������� : david
* ������� : 2010��12��24��
* ע    �� : ��֪�������������ʱ�����,���һ�����һ���Ƕ��̼߳��غ���,�ƺ�Ҳ��ʹ��
* �޸�����     �޸���    �޸�����
*******************************************************************************/
void AsyncFileReadInitialize( )
{
	s_asyncCurrentObject = NULL;
	s_asyncWaitObject = NULL;
	s_shutdownEvent.Reset( );
	s_sleepEvent.Reset( );
	SThread::Create( AsyncFileReadThread, NULL,s_asyncReadThread, "AsyncFileLoader" );
}
#ifdef _MINICLIENT
void A_GetCurrentDirectory(char (&path)[MAX_PATH])
{
	GetCurrentDirectory(MAX_PATH-1, path);
};

void DownLoadInitialize()
{
	SThread::Create( AsyncDownLoadThread, NULL,s_DownLoadThread, "AsyncDownLoad" );
}

#ifdef WIN32
DWORD WINAPI AsyncDownLoadThread(void* param)
#else
static void* AsyncDownLoadThread( void * param )
#endif
{
	MyDownLoadMgr::Mgr().Init();
	MyDownLoadMgr::Mgr().Run();
	return 0;
}
#endif

#ifdef WIN32
static DWORD WINAPI AsyncFileReadThread( void * param )
#else
static void* AsyncFileReadThread( void * param )
#endif
{
	while (s_shutdownEvent.Wait( 0 ) != WAIT_OBJECT_0)
	{
		if(!bCheckLostFlnish)//�����첽����ʱ�������Դ���ҵ�BUG --���� 2012��7��9��
		{//����
			s_queueLock.Enter( );

			int readHead = s_asyncFileReadList.Head();
			if ( s_asyncFileReadList.IsValidIndex( readHead ) )
			{
				CAsyncObject *object = s_asyncFileReadList[readHead];

				CAsyncObjectPriority::Mgr()->PreDeleteObj( object);
				s_asyncFileReadList.Remove(readHead);

				Assert( object );
				Assert( s_asyncCurrentObject == NULL );
				s_asyncCurrentObject = object;

				s_queueLock.Leave( );///

				// error check
				Assert( !object->isLoaded );
				Assert( object->file );
				Assert( object->buffer );
				Assert( object->size != 0 );
				Assert( object->userPostloadCallback );

				//true read
				//SFile::Read( object->file, object->buffer, object->size,0, NULL );
				SFile::ReadFileCache( object->file, object->buffer, object->size,0, NULL );

				//add to s_asyncFileReadPostList
				////
				s_queueLock.Enter( );
				s_asyncFileReadPostList.AddToTail( object );
				s_asyncCurrentObject = NULL;
				s_queueLock.Leave( );
			}
			else
			{
				s_queueLock.Leave( );///
			}

			Sleep(1);
		}
		else
		{//������

		}
	}



	//while ( s_shutdownEvent.Wait( 0 ) != WAIT_OBJECT_0 )// ����shutdown ֪ͨ
	//{
	//	DWORD ret = s_queueEvent.Wait( 500 );// �����л�֪ͨ                                                                                                                                                                                                                                                                               

	//	if ( ret != WAIT_TIMEOUT )  //  asyncreadthread���ȵ�֪ͨ, s_asyncFileReadList �л����
	//	{
	//		if ( ret != WAIT_OBJECT_0 )
	//		{
	//			Assert(0);
	//			MessageBox( NULL, "waitResult == OSWAIT_OBJECT_0 ", "����", 0 );
	//			exit(0);
	//		}

	//		while ( 1 ) //���Ȼ������
	//		{
	//			// read s_asyncFileReadList
	//			////
	//			s_sleepEvent.Wait( INFINITE );
	//			s_queueLock.Enter( );

	//			int readHead = s_asyncFileReadList.Head();
	//			if ( s_asyncFileReadList.IsValidIndex( readHead ) )
	//			{
	//				CAsyncObject *object = s_asyncFileReadList[readHead];

	//				CAsyncObjectPriority::Mgr()->PreDeleteObj( object);
	//				s_asyncFileReadList.Remove(readHead);

	//				Assert( object );
	//				Assert( s_asyncCurrentObject == NULL );
	//				s_asyncCurrentObject = object;

	//				s_queueLock.Leave( );///

	//				// error check
	//				Assert( !object->isLoaded );
	//				Assert( object->file );
	//				Assert( object->buffer );
	//				Assert( object->size != 0 );
	//				Assert( object->userPostloadCallback );

	//				//true read
	//				//SFile::Read( object->file, object->buffer, object->size,0, NULL );
	//				SFile::ReadFileCache( object->file, object->buffer, object->size,0, NULL );

	//				//add to s_asyncFileReadPostList
	//				////
	//				s_queueLock.Enter( );
	//				s_asyncFileReadPostList.AddToTail( object );
	//				s_asyncCurrentObject = NULL;
	//				s_queueLock.Leave( );
	//				////
	//				//Sleep(10);

	//			}
	//			else
	//			{
	//				s_queueLock.Leave( );///
	//				break;
	//			}
	//		} //���Ȼ������
	//	}
	//} // ����shutdown ֪ͨ
	//s_queueEvent.Set( );
	return 0;
}

void AsyncFileReadDestroy( )
{
	//by  2010-9-9 ����˳���s_asyncReadThread������
	s_queueLock.Enter( );
	s_asyncFileReadList.RemoveAll( );
	s_queueLock.Leave( );
	//---end

	s_shutdownEvent.Set( );
	s_queueEvent.Set( );
	s_sleepEvent.Set( );
	s_asyncReadThread.Wait( INFINITE );// ���ȡ�asyncfilereadthread ����

	Assert( s_asyncFileReadList.Count( ) == 0 );
	if ( s_asyncFileReadList.Count( ) != 0 )
	{
		Log( "Error! AsyncFileReadDestroy 's s_asyncFileReadList's count == 0" );
	}

	Assert( s_asyncCurrentObject == NULL );
	if ( s_asyncCurrentObject != NULL )
	{
		Log( "Error! AsyncFileReadDestroy 's s_asyncCurrentObject == NULL" );
	}

	s_asyncFileReadPostList.RemoveAll( );
	s_handlers_AsyncFileRead.RemoveAll( );
}

void AsyncFileReadAddHandler( pfnAsyncHandler handler )
{
	s_handlers_AsyncFileRead.AddToTail( handler );
}

CAsyncObject *AsyncFileReadCreateObject( )
{
	//s_queueLock.Enter( );
	CAsyncObject * object = new CAsyncObject;
	//s_queueLock.Leave( );

	return object;


}

void *AsyncFileReadDestroyObject( CAsyncObject *object )  // ���뷵�� object's file handle, ���ⲿ���������
{

	Assert( object );

	///
	s_queueLock.Enter( );

	CAsyncObjectPriority::Mgr()->PreDeleteObj( object);

	if ( s_asyncCurrentObject == object )  // ����asyncread this object
	{
		s_queueLock.Leave( );//
		while( s_asyncCurrentObject == object )
		{
			Sleep(1);
		}

		s_queueLock.Enter( );
	}

	// ��list��ɾ��
	int index = s_asyncFileReadList.Find( object );
	if ( s_asyncFileReadList.IsValidIndex( index ) )
	{
		s_asyncFileReadList.Remove( index );
	}
	else
	{
		index = s_asyncFileReadPostList.Find( object );
		if (  s_asyncFileReadPostList.IsValidIndex(index))
		{
			s_asyncFileReadPostList.Remove( index );
		}
	}

	s_queueLock.Leave( );//

	void *handle = object->file;
	SAFE_DELETE( object );

	return handle;

}

void AsyncFileReadObject( CAsyncObject * object )
{

	//error check
	Assert( object );
	Assert( !object->isLoaded );
	Assert( object->file );
	Assert( object->buffer );
	Assert( object->userPostloadCallback );


	///
	s_queueLock.Enter( );

	object->pos_after = CAsyncObjectPriority::Mgr()->GetObjectIDbyPriority( object->priority);

	if( !CAsyncObjectPriority::Mgr()->m_bUsePriority)
	{
		s_asyncFileReadList.AddToTail( object );
	}
	else
	{
		object->pos_after = s_asyncFileReadList.InsertAfter( object->pos_after,object);
	}

	CAsyncObjectPriority::Mgr()->SetObjectIDbyPriority( object->priority,object->pos_after );


	s_queueLock.Leave( );///

	s_queueEvent.Set( ); // ֪ͨ asyncfilethread , �л����

}



bool AsyncFileReadIsReading( )
{
	s_queueLock.Enter( );
	//if ( s_asyncCurrentObject || s_asyncFileReadList.IsValidIndex( s_asyncFileReadList.Head( ) )\
	//	|| s_asyncFileReadPostList.IsValidIndex( s_asyncFileReadPostList.Head( )) )
	if ( s_asyncCurrentObject || s_asyncFileReadList.Count( ) > 0 || s_asyncFileReadPostList.Count( ) > 0 )
	{
		s_queueLock.Leave( );
		return true;

	}

	s_queueLock.Leave( );
	return false;


}

void  AsyncFileReadWaitAll( )
{
	if (!bCheckLostFlnish)//�����첽����ʱ�������Դ���ҵ�BUG --���� 2012��7��9��
	{
		AsyncFileReadPollHandler( );  // by  2008.11.12 �ڴ��ģ�첽�����ļ�ʱ�򣬻�������������s_asyncloadlist���У�
		// ���� AsyncFileReadIsReading ����true.
		while( AsyncFileReadIsReading( ))
		{
			AsyncFileReadPollHandler( );
			Sleep(1);
			//by  2009.3.5 --FIXME
			AsyncFileReadWakeup( );
		}
	}

}

void AsyncFileSleepWait( )
{
	s_sleepEvent.Reset( );
}


void AsyncFileReadWakeup( )
{
	s_sleepEvent.Set( );
}

/*******************************************************************************
* �������� : AsyncFileReadPollHandler
* �������� : �첽���ش��ģ����
* �� �� ֵ : void
* �������� : david
* ������� : 2010��12��24��
* ע    �� : ��������ڵ��õĻ��ڻ�����һЩ����ĵط�,��������Ϊ�����߼�bug����
*		   : �������Ҳ���Ƕ��̼߳��ص�,�������߼���������õ�,ģ��ʵ�ֶ��̼߳���
* �޸�����     �޸���    �޸�����
*******************************************************************************/
void AsyncFileReadPollHandler( )
{
	for ( int index = s_handlers_AsyncFileRead.Head( ); s_handlers_AsyncFileRead.IsValidIndex( index );\
		index = s_handlers_AsyncFileRead.Next( index ) )
	{
		s_handlers_AsyncFileRead[index]( );
	}

	///
	s_queueEvent.Set( );

	DWORD start = 0,end = 0;
	start = Plat_MSTime( );
	///
	while( 1 )
	{
		s_queueLock.Enter( );
		int readHead = s_asyncFileReadPostList.Head( );
		if ( s_asyncFileReadPostList.IsValidIndex( readHead ) )
		{
			CAsyncObject *object = s_asyncFileReadPostList[readHead];
			s_asyncFileReadPostList.Remove( readHead );
			if (  object == s_asyncWaitObject )
			{
				s_asyncWaitObject = object;
			}
			object->isLoaded = true;

			s_queueLock.Leave( ); ///

			Assert( object->userPostloadCallback );
			object->userPostloadCallback( object->userArg );
		}
		else
		{
			s_queueLock.Leave( );///
			break;
		}
		
		//by fuq ���������Ŀ����ͬ������
		end = Plat_MSTime( );
		if ( (end-start) > 20) // ����̫��ʱ�ˣ��˳�//edit by youxl 2011.7.18
			break;
	}
}

///-----------------------------------------------------------------------------------------
///-----------------------------------------------------------------------------------------

///-----------------------------------------------------------------------------------------
CUtlLinkedList<CAsyncObject *>* IAsyncFileReadList()
{
	return &s_asyncFileReadList;
}
void SetAsyncLock( bool a_lock)
{
	if( a_lock )
	{
		s_queueLock.Enter();
	}
	else
	{
		s_queueLock.Leave( );
	}
}
void CAsyncObjectPriority::IfUsePriority(bool a_usepriority)
{
	m_bUsePriority = a_usepriority;
}
int CAsyncObjectPriority::GetObjPriority()
{
	return m_objPriority;
}
void CAsyncObjectPriority::SetObjPriority(int a_priority)
{
	m_objPriority = a_priority;
}
int CAsyncObjectPriority::GetObjectIDbyPriority(int a_priority)
{
	RefreshObjectIDbyPriority();
	switch ( a_priority)
	{
	case 0:return m_highest;
	case 1:return m_first;
	case 2:return m_second;
	case 3:return m_third;
	default:return -1;
	}
}
void CAsyncObjectPriority::SetObjectIDbyPriority( int a_priority,int a_id)//���������ȼ���ָ�뵽��Ӧ��ID��ȥ
{
	RefreshObjectIDbyPriority();
	int currentid;
	switch ( a_priority)
	{
	case 0:
		{
			currentid = m_highest;m_highest = a_id;
			if( m_first == currentid){ m_first = m_highest;}
			if( m_second == currentid){ m_second = m_first;}
			if( m_third == currentid){ m_third = m_second;}
			break;
		}
	case 1:
		{
			currentid = m_first;m_first = a_id;
			if( m_second == currentid){ m_second = m_first;}
			if( m_third == currentid){ m_third = m_second;}

			break;
		}
	case 2:
		{
			currentid = m_second;m_second = a_id;
			if( m_third == currentid){ m_third = m_second;}
			break;
		}
	case 3:currentid = m_third;m_third = a_id;break;
	default:return;
	}
}
void CAsyncObjectPriority::PreDeleteObj( void* a_object )
{
	CAsyncObject* t_object = (CAsyncObject*)a_object;
	RefreshObjectIDbyPriority();
	int index = t_object->pos_after;
	int t_id = GetObjectIDbyPriority( t_object->priority );
	if( (t_id == index)&&( t_id != -1))
	{
		t_id = IAsyncFileReadList()->Previous( index);
		SetObjectIDbyPriority(t_object->priority, t_id);
	}

}
void CAsyncObjectPriority::RefreshObjectIDbyPriority()
{
	//SetAsyncLock( true);
	CUtlLinkedList<CAsyncObject *>* t_list = IAsyncFileReadList();

	if( t_list->IsValidIndex(m_highest))
	{
		if( (m_highest != -1)&&(t_list->Element(m_highest)->priority != 0))
		{
			m_highest = -1;
		}
	}
	else
	{
		m_highest = -1;
	}

	if( t_list->IsValidIndex(m_first))
	{
		if( (m_first != -1)&&(t_list->Element(m_first)->priority != 1))
		{
			m_first = m_highest;
		}
	}
	else
	{
		m_first = m_highest;
	}

	if( t_list->IsValidIndex(m_second))
	{
		if( (m_second != -1)&&(t_list->Element(m_second)->priority != 2))
		{
			m_second = m_first;
		}
	}
	else
	{
		m_second = m_first;
	}

	if( t_list->IsValidIndex(m_third))
	{
		if( (m_third != -1)&&(t_list->Element(m_third)->priority != 3))
		{
			m_third = m_second;
		}
	}
	else
	{
		m_third = m_second;
	}
	//SetAsyncLock( false);
}

void AsyncFileCheckDeviceLost(bool isFlnish)//�����첽����ʱ�������Դ���ҵ�BUG --���� 2012��7��9��
{
	bCheckLostFlnish = isFlnish;
}
