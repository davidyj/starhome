
////		内存池无锁Log系统
////		默认支持多线程写，去掉 THREAD_LOG 定义
////								2011-5-29  li9chuan

///			客户端不适用内存池，加入预编译指令
///			如果未定义 _CLIENT_ 则使用内存池，否则动态new出内存，写完log后释放
///									2011-6-24  li9chuan

#include "../stdafx.h"
#include "platform.h"
#include "ThreadLib.h"
#include "core.h"
#include <time.h>
#ifdef FREEBSD
#include <stdarg.h>
#endif
#define LOG_ITEM_SIZE			5120					//	每个log的长度

#define LOG_MAXCOUNT			50000					//每个log文件最大记录的条数(5万条大概2M,大吗？)

char g_LogName[LOG_ITEM_SIZE] = { 0 };

char g_LogFileName[LOG_ITEM_SIZE] = {0};
char g_FileName[128] ={0};

int	 g_LogCount = 0 ; //log计数
int  g_InitDay = 0 ; //启动log日期用来作对比
CPlatformCS g_LogCS;


BOOL g_bLogRun = FALSE;
ThreadLib::ThreadID g_hLogThread = NULL;
FILE* g_hFile = NULL;

int NewCrtMemReport( int nRtpType, char * szMsg, int * pRetVal )
{
	//FILE* f = NULL;
	//char szLogName[256] = { 0 };
	//strcpy( szLogName, g_LogName );
	//strcat( szLogName, "mem.log" );
	//f = fopen( szLogName, "at+" );
	//if( f )
	//{
	//	fprintf( f, "%s", szMsg );
	//	fclose( f );
	//}
	//if( pRetVal )
	//	*pRetVal = 0;
	return 1;
}

#define THREAD_LOG

void ReCordLogCount()
{


	//SYSTEMTIME	SystemTime;
	//GetSystemTime(&SystemTime);
	// fixed文件夹创建日期错误	
	time_t aclock;
	time( &aclock );  
	struct tm *newtime = localtime( &aclock );   

	newtime->tm_year+=1900;
	newtime->tm_mon+=1;	

	//如果变化日期则重新创建目录
	if( newtime->tm_mday != g_InitDay )
	{
		memset(g_LogName, 0 ,sizeof(g_LogName));
		memset(g_LogFileName,0 ,sizeof(g_LogFileName));
		Plat_GetExePath( g_LogName, 256 );

#ifdef WIN32
		strcat( g_LogName, "Log\\" );
#else
		strcat( g_LogName, "Log/" );
#endif		
		char strSubLogName[256] = { };	
		
#ifdef WIN32
		sprintf( strSubLogName ,"[LOG_%d_%d_%d]\\" ,newtime->tm_year,newtime->tm_mon, newtime->tm_mday);
#else

		sprintf( strSubLogName ,"[LOG_%d_%d_%d]/" , newtime->tm_year,newtime->tm_mon, newtime->tm_mday );
#endif
		strcat( g_LogName , strSubLogName );
		strcat( g_LogName, g_FileName );
		strcpy(g_LogFileName,g_LogName);
		g_InitDay = newtime->tm_mday;
		g_LogCount = 0 ;//重置计数
		Plat_CreatePath( g_LogName );
			
		char fileTime[512] = {};
		sprintf( fileTime ,"[%d_%d_%d].log" , newtime->tm_hour,newtime->tm_min ,newtime->tm_sec );
		strcat( g_LogName , fileTime );

	}

	g_LogCount++;

	#ifdef THREAD_LOG
	if(g_LogCount >= LOG_MAXCOUNT )//如果超过最大记录条数将更换文件名
	{
		
		char fileTime[512] = {};
		char LogFileName[LOG_ITEM_SIZE] = {0};


		sprintf( fileTime ,"[%d_%d_%d].log" , newtime->tm_hour,newtime->tm_min ,newtime->tm_sec);
		strcpy(LogFileName, g_LogFileName);
		strcat( LogFileName , fileTime );


		strcpy(g_LogName,LogFileName);
		
		g_LogCount = 0 ;
	}
	#endif


}

#ifdef THREAD_LOG
void* _Plat_SimpleLog( const char* file, int line )
#else
void* Plat_SimpleLog( const char* file, int line )
#endif
{

	g_LogCS.Lock( );
	//FILE* f = NULL;
	ReCordLogCount();
	g_hFile = fopen(g_LogName,"at+");
	if( g_hFile ){
		fprintf( g_hFile, "%s\n", file );
		fclose( g_hFile );
	}
	g_LogCS.Unlock( );

	return NULL;
}

void* Plat_BlockLog( char const *pMsgFormat, ... )
{
	char temp[LOG_ITEM_SIZE] = {0};
	va_list args;
	va_start( args, pMsgFormat );
	int len = vsprintf( temp, pMsgFormat, args );
	va_end(args);

	return _Plat_SimpleLog( temp ,0 );
}

//#if defined(_CLIENT_) || defined(_ROBOT)
#ifndef X86AMD64
#include "Chain.h"
class _LogUnit : public CHAINITEM
{
public:
	char szLog[LOG_ITEM_SIZE];
};

CHAINHEADER * g_pLogUnitHead = NULL;

#ifdef WIN32		//	li9chuan	2010-11-29

	HANDLE g_hLogEvent = NULL;
//	HANDLE g_hLogThread = NULL;

#else

	#include <semaphore.h>
	sem_t g_hLogEvent = NULL;
//	pthread_t g_hLogThread = NULL;

#endif

char * g_pLogInfo = NULL;

//DWORD WINAPI LogThreadFunc( void* pArguments );
void LogThreadFunc( void* pArguments );

void Plat_SetSimpleLogName( const char * szLogName )
{
	Plat_GetExePath( g_LogName, 256 );
	//DeleteFileByTime( g_LogName ,1);
#ifdef WIN32
	strcat( g_LogName, "Log\\" );
#else
	strcat( g_LogName, "Log/" );
#endif

	struct tm *newtime;
	time_t aclock;
	time( &aclock );   // Get time in seconds
	newtime = localtime( &aclock );   // Convert time to struct tm form

	char strSubLogName[256] = { };

#ifdef WIN32

	FILETIME tmCreateTime ;
	FILETIME tmExitTime ;
	FILETIME tmKernalTime ;
	FILETIME tmUserTime ;
	SYSTEMTIME tmSystemTime;

	GetProcessTimes( GetCurrentProcess( ),&tmCreateTime , &tmExitTime , &tmKernalTime , &tmUserTime );
	FileTimeToSystemTime( &tmCreateTime ,&tmSystemTime );
	TIME_ZONE_INFORMATION    zinfo;

	GetTimeZoneInformation(&zinfo);//得到时区信息
	SystemTimeToTzSpecificLocalTime(&zinfo,&tmSystemTime,&tmSystemTime);//将格林威治时间转换为对应的当前时区的时间
	//SetLocalTime(&stime);//设置时间
	//tReturning = CTime(stime);

	//sprintf( strSubLogName ,"[LOG_%d_%d_%d_%d_%d_%d]\\" ,tmSystemTime.wYear ,tmSystemTime.wMonth, tmSystemTime.wDay,tmSystemTime.wHour ,tmSystemTime.wMinute , tmSystemTime.wSecond );
	sprintf( strSubLogName ,"[LOG_%d_%d_%d]\\" ,tmSystemTime.wYear ,tmSystemTime.wMonth, tmSystemTime.wDay );
#else
	//sprintf( strSubLogName ,"[LOG_%d_%d_%d]\\" , newtime->tm_hour,newtime->tm_min ,newtime->tm_sec );
	sprintf( strSubLogName ,"[LOG_%d_%d_%d]/" , newtime->tm_hour,newtime->tm_min ,newtime->tm_sec );
#endif
	strcat( g_LogName , strSubLogName );
	strcat( g_LogName, szLogName );
	strcpy(g_LogFileName,g_LogName);
	strcpy(g_FileName,szLogName);
	g_InitDay = tmSystemTime.wDay;

	if (!Plat_CreatePath( g_LogName )){
		//return;
	}


	char fileTime[512] = {};
	sprintf( fileTime ,"[%d_%d_%d].log" , newtime->tm_hour,newtime->tm_min ,newtime->tm_sec );
	strcat( g_LogName , fileTime );

	//if( g_LogName[0] != 0 )
	//	g_hFile = fopen(g_LogName,"at+");
	//unlink( g_LogName );
#ifdef WIN32
	//by jinsheng 2009.1.7
	//_CrtSetReportHook( NewCrtMemReport );
#endif

#ifdef THREAD_LOG

	g_pLogUnitHead = new CHAINHEADER;
//	DWORD dwThreadID = 0;
	g_bLogRun = TRUE;// by sun 2009.2.7
	g_LogCount = 0 ;
	#ifdef WIN32
		g_hLogEvent = CreateEvent( NULL, TRUE, FALSE, NULL );// by sun 2009.2.7 //  [4/10/2010 sun ]
	//	g_hLogThread = (HANDLE)CreateThread( NULL, 0, &LogThreadFunc, NULL, 0, &dwThreadID );
	#else
		sem_init( &g_hLogEvent, 1, 0 );			// li9chuan	2010-12-1
	#endif

	g_hLogThread = ThreadLib::Create( LogThreadFunc, NULL );

#endif
}


void Plat_DestroyLog( )
{
	g_LogCS.Lock( );
	g_bLogRun = FALSE;
#ifdef WIN32
	SetEvent( g_hLogEvent );
#else
	sem_post( &g_hLogEvent );
#endif
	//fclose(g_hFile);
	g_LogCS.Unlock();
}

CPlatformCS g_LogInfoCS;

#ifdef THREAD_LOG
void* Plat_SimpleLog( const char* file, int line )
#else
void* _Plat_SimpleLog( const char* file, int line )
#endif
{
	if( !g_bLogRun )
		return NULL;
	_LogUnit * pUnit = new _LogUnit;

	if ( !pUnit )
	{
		OutputDebugString( "new logunit failed !!!!!\n" );
		return NULL;
	}
	pUnit->szLog[0] = 0;

	struct tm *newtime;
	time_t aclock;
	time( &aclock );   // Get time in seconds
	newtime = localtime( &aclock );   // Convert time to struct tm form
	char * sztime = asctime( newtime );
	int nLen = lstrlen( sztime );
	if( nLen > 0 )
	{
		sztime[nLen-1] = 0;
		strcat( pUnit->szLog, "[" );
		strcat( pUnit->szLog, "[" );
		strcat( pUnit->szLog, sztime );
		strcat( pUnit->szLog, "]" );
		strncat( pUnit->szLog, file, 900);//strcat( pUnit->szLog, file );
	}
	pUnit->szLog[1023] = 0;

	g_LogInfoCS.Lock( );
	g_pLogUnitHead->Add( pUnit );
	g_LogInfoCS.Unlock( );

#ifdef WIN32	//	2010-11-29	li9chuan
	SetEvent( g_hLogEvent );
#else
	sem_post( &g_hLogEvent );
#endif

	return NULL;
}



BOOL GetLogHead( char * szLogTemp )
{
	BOOL bRet = FALSE;
	g_LogInfoCS.Lock( );
	if( g_pLogUnitHead )
	{
		_LogUnit * pUnit = (_LogUnit *)g_pLogUnitHead->First( );
		if( pUnit )
		{
			strcpy( szLogTemp, pUnit->szLog );
			pUnit->DisConnect( );
			delete pUnit;
			bRet = TRUE;
		}
	}
	g_LogInfoCS.Unlock( );
	return bRet;
}

#ifdef WIN32
#else	///	Be operating
#endif

//DWORD WINAPI LogThreadFunc( void* pArguments )
void LogThreadFunc( void* pArguments )
{
#ifdef WIN32
#ifndef _DEBUG 
	__try
	{
#endif
#endif
		char g_szLogInfoTemp[LOG_ITEM_SIZE] = { 0 };
		for(;;)
		{

	#ifdef WIN32
 			WaitForSingleObject( g_hLogEvent, INFINITE );
	#else
 			sem_wait( &g_hLogEvent );
	#endif

			if( !g_bLogRun )
				break;

			while( GetLogHead( g_szLogInfoTemp ) )
			{
				if( g_szLogInfoTemp[0] != 0 )
					_Plat_SimpleLog( g_szLogInfoTemp, 0 );
				g_szLogInfoTemp[0] = 0;
			}

	#ifdef WIN32
			ResetEvent( g_hLogEvent );
	#endif
		}
		//ExitThread( 30 );

		if( g_hLogEvent )
		{
	#ifdef WIN32
			CloseHandle( g_hLogEvent );
	#else
			sem_destroy( &g_hLogEvent );
	#endif
			g_hLogEvent = NULL;
		}

		if( g_hLogThread )
		{
			//CloseHandle( g_hLogThread );
			ThreadLib::WaitForFinish( g_hLogThread );
			g_hLogThread = NULL;
		}

		while( GetLogHead( g_szLogInfoTemp ) );

		if( g_pLogUnitHead )
		{
			delete g_pLogUnitHead;
			g_pLogUnitHead = NULL;//by sun
		}
//	return 30;
#ifdef WIN32
#ifndef _DEBUG
	}
	__except (HandleException(GetExceptionInformation(), "LogThreadFunc"))
	{
	}
#endif
#endif
}

#else
#include "../../Engine/Include/utlRWvector.h"
#include "../../Engine/Include/GLock.h"
#include "memorypool.h"

#define LOG_ITEM_DATA_SIZE		LOG_ITEM_SIZE - 100		//	去掉时间戳等附加信息的数据长度
#ifdef _DEBUG
#define LOG_POOL_SIZE			1024 * 32
#define LOG_TABLE_SIZE			1024 * 32
#else
#define LOG_POOL_SIZE			1024 * 8
#define LOG_TABLE_SIZE			1024 * 8
#endif


struct _LogItem
{
	char szLog[LOG_ITEM_SIZE];
};

CObjectMemoryPool<_LogItem> g_LogPool;
CUtlRWVector<_LogItem> g_LogTable;

CGEvent g_LogEvent;

void LogThreadFunc( void* pArguments )
{
	while(1)
	{
		g_LogEvent.Wait();

		if( !g_bLogRun )
			break;

		_LogItem* logitem = NULL;

		FOR_EACH_RW( g_LogTable, i )
		{
			logitem = g_LogTable.Element(i);
			if(logitem){
				_Plat_SimpleLog( logitem->szLog ,0 );
				g_LogPool.Free( logitem );
			}
		}

		Sleep(0);
	}
}

void Plat_SetSimpleLogName( const char * szLogName )
{
	Plat_GetExePath( g_LogName, 256 );
	//DeleteFileByTime( g_LogName ,1);
#ifdef WIN32
	strcat( g_LogName, "Log\\" );
#else
	strcat( g_LogName, "Log/" );
#endif

	struct tm *newtime;
	time_t aclock;
	time( &aclock );   // Get time in seconds
	newtime = localtime( &aclock );   // Convert time to struct tm form

	char strSubLogName[256] = { };

#ifdef WIN32

	FILETIME tmCreateTime ;
	FILETIME tmExitTime ;
	FILETIME tmKernalTime ;
	FILETIME tmUserTime ;
	SYSTEMTIME tmSystemTime;

	GetProcessTimes( GetCurrentProcess( ),&tmCreateTime , &tmExitTime , &tmKernalTime , &tmUserTime );
	FileTimeToSystemTime( &tmCreateTime ,&tmSystemTime );
	TIME_ZONE_INFORMATION    zinfo;

	GetTimeZoneInformation(&zinfo);//得到时区信息
	SystemTimeToTzSpecificLocalTime(&zinfo,&tmSystemTime,&tmSystemTime);//将格林威治时间转换为对应的当前时区的时间
	//SetLocalTime(&stime);//设置时间
	//tReturning = CTime(stime);

	//sprintf( strSubLogName ,"[LOG_%d_%d_%d_%d_%d_%d]\\" ,tmSystemTime.wYear ,tmSystemTime.wMonth, tmSystemTime.wDay,tmSystemTime.wHour ,tmSystemTime.wMinute , tmSystemTime.wSecond );
	sprintf( strSubLogName ,"[LOG_%d_%d_%d]\\" ,tmSystemTime.wYear ,tmSystemTime.wMonth, tmSystemTime.wDay);
#else
	//sprintf( strSubLogName ,"[LOG_%d_%d_%d]\\" , newtime->tm_hour,newtime->tm_min ,newtime->tm_sec );
	sprintf( strSubLogName ,"[LOG_%d_%d_%d]/" , newtime->tm_hour,newtime->tm_min ,newtime->tm_sec );
#endif
	strcat( g_LogName , strSubLogName );
	strcat( g_LogName, szLogName );
	if (!Plat_CreatePath( g_LogName )){
		//return;
	}


	char fileTime[512] = {};
	sprintf( fileTime ,"[%d_%d_%d].log" , newtime->tm_hour,newtime->tm_min ,newtime->tm_sec );
	strcat( g_LogName , fileTime );
	strcpy(g_LogFileName,g_LogName);
	strcpy(g_FileName,szLogName);


	g_InitDay = tmSystemTime.wDay;

	//if( g_LogName[0] != 0 )
	//	g_hFile = fopen(g_LogName,"at+");
	//unlink( g_LogName );
#ifdef WIN32
	//by jinsheng 2009.1.7
	//_CrtSetReportHook( NewCrtMemReport );
#endif

	g_LogPool.Init( "LogPool", LOG_POOL_SIZE );
	g_LogTable.init( LOG_TABLE_SIZE );
	g_bLogRun = TRUE;// by sun 2009.2.7

	g_hLogThread = ThreadLib::Create( LogThreadFunc, NULL );
}

//void* Plat_BlockLog( char const *pMsgFormat, ... )
//{
//	char temp[LOG_ITEM_SIZE] = {0};
//	va_list args;
//	va_start( args, pMsgFormat );
//	int len = vsprintf( temp, pMsgFormat, args );
//	va_end(args);
//
//	return _Plat_SimpleLog( temp ,0 );
//}

void* Plat_SimpleLog( const char* file, int line )
{
	if( !g_bLogRun )
		return NULL;

	_LogItem* pItem = NULL;
	pItem = g_LogPool.Alloc();

	if ( !pItem )
	{
		OutputDebugString( "new logunit failed !!!!!\n" );
		return NULL;
	}

	pItem->szLog[0] = 0;

	struct tm *newtime;
	time_t aclock;
	time( &aclock );   // Get time in seconds
	newtime = localtime( &aclock );   // Convert time to struct tm form
	char * sztime = asctime( newtime );
	int nLen = lstrlen( sztime );
	if( nLen > 0 )
	{
		sztime[nLen-1] = 0;
//		strcat( pItem->szLog, "[" );
		strcat( pItem->szLog, "[" );
		strcat( pItem->szLog, sztime );
		strcat( pItem->szLog, "]" );
		strncat( pItem->szLog, file, LOG_ITEM_DATA_SIZE );//strcat( pUnit->szLog, file );
	}

	pItem->szLog[LOG_ITEM_SIZE-1] = 0;

	if( g_LogTable.add( pItem ) != g_LogTable.invalidIndex() )
	{
		g_LogEvent.Event();
	}
	else
	{
		g_LogPool.Free( pItem );
	}

	return NULL;
}

void Plat_DestroyLog( )
{
	g_bLogRun = FALSE;
	g_LogEvent.Event();
//	fclose(g_hFile);
}

#endif

