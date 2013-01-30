//=========== (C) Copyright 1999 Valve, L.L.C. All rights reserved. ===========
//
// The copyright to the contents herein is the property of Valve, L.L.C.
// The contents may be used and/or copied only with the written permission of
// Valve, L.L.C., or in accordance with the terms and conditions stipulated in
// the agreement/contract under which the contents have been supplied.
//
// $Header: $
// $NoKeywords: $
//
// The main debug library implementation
//=============================================================================

#include "../stdafx.h"
#include "dbg.h"

#ifdef WIN32
#include <malloc.h>
#include <crtdbg.h>
#else
#include <stdlib.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <signal.h> // raise

#ifdef WIN32
#include <extendedtrace.h>
#include "direct.h"
#endif
//#include "memdbgon.h"
//-----------------------------------------------------------------------------
// internal structures
//-----------------------------------------------------------------------------
#include <vector>
using namespace std;
vector< char* > g_vecVprofMessage;

enum
{
	MAX_GROUP_NAME_LENGTH = 48
};

struct SpewGroup_t
{
	char	m_GroupName[MAX_GROUP_NAME_LENGTH];
	int		m_Level;
};


//-----------------------------------------------------------------------------
// Templates to assist in validating pointers:

void _AssertValidReadPtr( void* ptr, int count/* = 1*/ )
{
#ifdef WIN32
	Assert(!IsBadReadPtr( ptr, count ));
#else
	Assert(ptr);
#endif

}

void _AssertValidWritePtr( void* ptr, int count/* = 1*/ )
{
#ifdef WIN32
	Assert(!IsBadWritePtr( ptr, count ));
#else
	Assert(ptr);
#endif
}

void _AssertValidReadWritePtr( void* ptr, int count/* = 1*/ )
{
#ifdef WIN32
	Assert(!( IsBadWritePtr(ptr, count) || IsBadReadPtr(ptr,count)));
#else
	Assert(ptr);
#endif
}

void AssertValidStringPtr( const char* ptr, int maxchar/* = 0xFFFFFF */ )
{
#ifdef WIN32
	Assert(!IsBadStringPtr( ptr, maxchar ));
#else
	Assert(ptr);
#endif
}

//-----------------------------------------------------------------------------
// globals
//-----------------------------------------------------------------------------

SpewRetval_t DefaultSpewFunc( SpewType_t type, char const *pMsg )
{
	static char s_Msg[1024];
	//printf( "%s", pMsg );
	if( type == SPEW_ASSERT )
	{
		{
			int nID = MessageBox( NULL, pMsg , "Assert", MB_ABORTRETRYIGNORE );
			switch( nID )
			{
			case IDRETRY:
				return SPEW_DEBUGGER;
			case IDABORT:
				raise(SIGABRT);
				_exit(3);
				return SPEW_CONTINUE;
			case IDIGNORE:
				return SPEW_CONTINUE;
			}
		}

		return SPEW_DEBUGGER;
	}
	else if( type == SPEW_ERROR )
	{
		MessageBox( NULL, pMsg , "Error", MB_OK );
		return SPEW_ABORT;
	}
	else if( type == SPEW_LOG )
	{
		strcpy( s_Msg, "[Log] " );
		strcat( s_Msg, pMsg );
		Plat_SimpleLog( s_Msg, __LINE__ );
		return SPEW_CONTINUE;
	}
	else if( type == SPEW_WARNING )
	{
		sprintf( s_Msg, "[Warning] %s", pMsg );
		int nLen = lstrlen( s_Msg );
		if( s_Msg[nLen-1] == '\n' )
			s_Msg[nLen-1] = '\0';
		OutputDebugStringA( s_Msg );
		return SPEW_CONTINUE;
	}
	else
		return SPEW_CONTINUE;
}

static SpewOutputFunc_t   s_SpewOutputFunc = DefaultSpewFunc;

static char const*	s_pFileName;
static int			s_Line;
static SpewType_t	s_SpewType;

static SpewGroup_t* s_pSpewGroups = 0;
static int			s_GroupCount = 0;
static int			s_DefaultLevel = 0;



//-----------------------------------------------------------------------------
// Spew output management.
//-----------------------------------------------------------------------------

void  SpewOutputFunc( SpewOutputFunc_t func )
{
	s_SpewOutputFunc = func ? func : DefaultSpewFunc;
}

SpewOutputFunc_t GetSpewOutputFunc( void )
{
	if( s_SpewOutputFunc )
	{
		return s_SpewOutputFunc;
	}
	else
	{
		return DefaultSpewFunc;
	}
}

//-----------------------------------------------------------------------------
// Spew functions
//-----------------------------------------------------------------------------

void  _SpewInfo( SpewType_t type, char const* pFile, int line )
{
	// Only grab the file name. Ignore the path.
	char const* pSlash = strrchr( pFile, '\\' );
	char const* pSlash2 = strrchr( pFile, '/' );
	if (pSlash < pSlash2) pSlash = pSlash2;

	s_pFileName = pSlash ? pSlash + 1: pFile;
	s_Line = line;
	s_SpewType = type;
}

SpewRetval_t  _SpewMessage( SpewType_t spewType, char const* pMsgFormat, va_list args )
{
	char pTempBuffer[1024] = {0,};

	/* Printf the file and line for warning + assert only... */
	int len = 0;
	if ((spewType == SPEW_ASSERT) )
	{
		len = sprintf( pTempBuffer, "%s (%d) : ", s_pFileName, s_Line );
	}

	/* Create the message.... */
	//len += vsprintf( &pTempBuffer[len], pMsgFormat, args );
	//pTempBuffer[1023] = 0;

#ifdef FREEBSD
	/*
	const char* bit64 = "I64d";
	const int   formatlen = strlen(pMsgFormat);
	char pTempFormat[1024] ={0};
	int tfidx = 0;

	for( int mfidx=0; mfidx<formatlen; mfidx++ )
	{
		pTempFormat[tfidx++] = pMsgFormat[mfidx];

		if( '%' == pMsgFormat[mfidx] )
		{
			int bit64idx = 0;
			int scanidx = mfidx + 1;

			for( ; bit64idx<4; bit64idx++ )
			{
				if( scanidx >= formatlen ) { break; }
				if( bit64[bit64idx] != pMsgFormat[scanidx] ) { break; }
				scanidx++;
			}

			if( bit64idx == 4 )
			{
				memcpy( pTempFormat+tfidx, "lld", 3 );
				tfidx += 3;
				mfidx += 4;
			}
		}
	}
	pTempFormat[tfidx] = '\0';
	*/

	const char* bit64 = "I64";
	const int   formatlen = strlen(pMsgFormat);
	char pTempFormat[1024] ={0};
	int tfidx = 0;

	for( int mfidx=0; mfidx<formatlen; mfidx++ )
	{
		pTempFormat[tfidx++] = pMsgFormat[mfidx];

		if( '%' == pMsgFormat[mfidx] )
		{
			int bit64idx = 0;
			int scanidx = mfidx + 1;

			for( ; bit64idx<3; bit64idx++ )
			{
				if( scanidx >= formatlen ) { break; }
				if( bit64[bit64idx] != pMsgFormat[scanidx] ) { break; }
				scanidx++;
			}

			if( bit64idx == 3 )
			{
				memcpy( pTempFormat+tfidx, "ll", 2 );
				tfidx += 2;
				mfidx += 3;
			}
		}
	}
	pTempFormat[tfidx] = '\0';

	len += vsnprintf(&pTempBuffer[len], 1023, pTempFormat, args);

#else
	len += _vsnprintf(&pTempBuffer[len], 1023, pMsgFormat, args);
#endif

	if( pTempBuffer[1023] != 0)
	{
		pTempBuffer[1023] = 0;
	}

	// Add \n for warning and assert
	if ((spewType == SPEW_ASSERT) )
	{
		len += sprintf( &pTempBuffer[len], "\n" );
	}

	assert( len < 1024 ); /* use normal assert here; to avoid recursion. */
	assert( s_SpewOutputFunc );
	if( spewType == SPEW_MONITOR )
	{
		char * szMsg = new char[lstrlen(pTempBuffer)+1];
		strcpy( szMsg, pTempBuffer );
		g_vecVprofMessage.push_back( szMsg );
	}

	/* direct it to the appropriate target(s) */
	SpewRetval_t ret = s_SpewOutputFunc( spewType, pTempBuffer );
	switch (ret)
	{
		// Put the break into the macro so it would occur in the right place
		//	case SPEW_DEBUGGER:
		//		DebuggerBreak();
		//		break;

	case SPEW_ABORT:
		//		MessageBox(NULL,"Error in _SpewMessage","Error",MB_OK);
		exit(0);
	}

	return ret;
}

SpewRetval_t  _SpewMessage( char const* pMsgFormat, ... )
{
	va_list args;
	va_start( args, pMsgFormat );
	SpewRetval_t ret = _SpewMessage( s_SpewType, pMsgFormat, args );
	va_end(args);
	return ret;
}

SpewRetval_t _DSpewMessage( char const *pGroupName, int level, char const* pMsgFormat, ... )
{
	if( !IsSpewActive( pGroupName, level ) )
		return SPEW_CONTINUE;

	va_list args;
	va_start( args, pMsgFormat );
	SpewRetval_t ret = _SpewMessage( s_SpewType, pMsgFormat, args );
	va_end(args);
	return ret;
}

void Msg( char const* pMsgFormat, ... )
{
//#ifdef _DEBUG
	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_MESSAGE, pMsgFormat, args );
	va_end(args);
//#endif
}

void MonitorMsg( char const* pMsgFormat, ... )
{
	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_MONITOR, pMsgFormat, args );
	va_end(args);

}

void DMsg( char const *pGroupName, int level, char const *pMsgFormat, ... )
{
	if( !IsSpewActive( pGroupName, level ) )
		return;

	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_MESSAGE, pMsgFormat, args );
	va_end(args);
}

void Warning( char const *pMsgFormat, ... )
{
//#ifdef __DEV__
	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_WARNING, pMsgFormat, args );
	va_end(args);
//#endif
}

void DWarning( char const *pGroupName, int level, char const *pMsgFormat, ... )
{
	if( !IsSpewActive( pGroupName, level ) )
		return;

	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_WARNING, pMsgFormat, args );
	va_end(args);
}

void DLog( char const *pGroupName, int level, char const *pMsgFormat, ... )
{
	if( !IsSpewActive( pGroupName, level ) )
		return;

	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_LOG, pMsgFormat, args );
	va_end(args);
}

void Error( char const *pMsgFormat, ... )
{
	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_ERROR, pMsgFormat, args );
	va_end(args);
}

void See(char const* pMsgFormat,...)
{
	char pTempBuffer[1024]={0};
	va_list args;
	va_start( args, pMsgFormat );
	//_SpewMessage( SPEW_MONITOR, pMsgFormat, args );
	vsprintf( &pTempBuffer[0], pMsgFormat, args );
	printf(pTempBuffer);
	va_end(args);
}

//-----------------------------------------------------------------------------
// A couple of super-common dynamic spew messages, here for convenience
// These looked at the "developer" group, print if it's level 1 or higher
//-----------------------------------------------------------------------------

void DevMsg( int level, char const* pMsgFormat, ... )
{
	if( !IsSpewActive( "developer", level ) )
		return;

	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_MESSAGE, pMsgFormat, args );
	va_end(args);
}

void DevWarning( int level, char const *pMsgFormat, ... )
{
	if( !IsSpewActive( "developer", level ) )
		return;

	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_WARNING, pMsgFormat, args );
	va_end(args);
}

void DevLog( int level, char const *pMsgFormat, ... )
{
	if( !IsSpewActive( "developer", level ) )
		return;

	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_LOG, pMsgFormat, args );
	va_end(args);
}

void DevMsg( char const *pMsgFormat, ... )
{
	if( !IsSpewActive( "developer", 1 ) )
		return;

	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_MESSAGE, pMsgFormat, args );
	va_end(args);
}

void DevWarning( char const *pMsgFormat, ... )
{
	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_WARNING, pMsgFormat, args );
	va_end(args);
}

void DevLog( char const *pMsgFormat, ... )
{
	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_LOG, pMsgFormat, args );
	va_end(args);
}

//-----------------------------------------------------------------------------
// Find a group, return true if found, false if not. Return in ind the
// index of the found group, or the index of the group right before where the
// group should be inserted into the list to maintain sorted order.
//-----------------------------------------------------------------------------

bool FindSpewGroup( char const* pGroupName, int* pInd )
{
	int s = 0;
	if (s_GroupCount)
	{
		int e = (int)(s_GroupCount - 1);
		while ( s <= e )
		{
			int m = (s+e) >> 1;
			int cmp = stricmp( pGroupName, s_pSpewGroups[m].m_GroupName );
			if ( !cmp )
			{
				*pInd = m;
				return true;
			}
			if ( cmp < 0 )
				e = m - 1;
			else
				s = m + 1;
		}
	}
	*pInd = s;
	return false;
}


//-----------------------------------------------------------------------------
// Sets the priority level for a spew group
//-----------------------------------------------------------------------------

void SpewActivate( char const* pGroupName, int level )
{
	Assert( pGroupName );

	// check for the default group first...
	if ((pGroupName[0] == '*') && (pGroupName[1] == '\0'))
	{
		s_DefaultLevel = level;
		return;
	}

	// Normal case, search in group list using binary search.
	// If not found, grow the list of groups and insert it into the
	// right place to maintain sorted order. Then set the level.
	int ind;
	if ( !FindSpewGroup( pGroupName, &ind ) )
	{
		// not defined yet, insert an entry.
		++s_GroupCount;
		if (s_pSpewGroups)
		{
			s_pSpewGroups = (SpewGroup_t*)realloc( s_pSpewGroups,
				s_GroupCount * sizeof(SpewGroup_t) );

			// shift elements down to preserve order
			int numToMove = s_GroupCount - ind - 1;
			memmove( &s_pSpewGroups[ind+1], &s_pSpewGroups[ind],
				numToMove * sizeof(SpewGroup_t) );
		}
		else
			s_pSpewGroups = (SpewGroup_t*)malloc( s_GroupCount * sizeof(SpewGroup_t) );

		Assert( strlen( pGroupName ) < MAX_GROUP_NAME_LENGTH );
		strcpy( s_pSpewGroups[ind].m_GroupName, pGroupName );
	}
	s_pSpewGroups[ind].m_Level = level;
}


//-----------------------------------------------------------------------------
// Tests to see if a particular spew is active
//-----------------------------------------------------------------------------

bool IsSpewActive( char const* pGroupName, int level )
{
	// If we don't find the spew group, use the default level.
	int ind;
	if ( FindSpewGroup( pGroupName, &ind ) )
		return s_pSpewGroups[ind].m_Level >= level;
	else
		return s_DefaultLevel >= level;
}


// If we don't have a function from math.h, then it doesn't link certain floating-point
// functions in and printfs with %f cause runtime errors in the C libraries.
float CrackSmokingCompiler( float a )
{
	return fabs( a );
}

//void Log( char const *pMsgFormat, ... )
//{
//	va_list args;
//	va_start( args, pMsgFormat );
//	_SpewMessage( SPEW_LOG, pMsgFormat, args );
//	va_end(args);
//}

/*
class ClearLogName
{
public:
ClearLogName( )
{
g_LogName[0] = 0;
}
};*/

#ifdef WIN32	//	li9chuan	2010-11-29

void DeleteFileByTime(const char * filepath ,int numDaysToDelete , char * subDir/* = NULL*/)
{
	//只删除1层目录的文件
	char szFindDir[512] = {};
	char szFindFileName[512] = {};
	WIN32_FIND_DATA  findFileData;
	strcpy( szFindDir,filepath );
	strcat( szFindDir , "Log\\");
	if( subDir )
	{
		strcat( szFindDir , subDir );
		strcat( szFindDir , "\\");
	}
	strcat( szFindFileName ,filepath );
	if( subDir )
	{
		char temp[256] = { };
		sprintf( temp ,"Log\\%s\\*.*" ,subDir );
		strcat( szFindFileName ,temp );
	}
	else
		strcat( szFindFileName,"Log\\*.*");
	HANDLE hfile = FindFirstFile( szFindFileName , &findFileData);
	if(INVALID_HANDLE_VALUE == hfile)    return;
	SYSTEMTIME sysytemtime;
	struct tm *newtime;
	time_t aclock;
	time( &aclock );
	newtime = localtime( &aclock );
	newtime->tm_mon += 1; //  int tm_mday;    /* day of the month - [1,31] */  /* months since January - [0,11] */
	while(TRUE)
	{
		{
			//if( GetFileTime( hfile ,NULL ,NULL ,&filetime) )
			char temp[512] = { };
			strcpy( temp , szFindDir);
			strcat( temp ,findFileData.cFileName );

			if( strcmp( findFileData.cFileName ,"errorlog.txt") != 0)
			{
				if ( strcmp(".",  findFileData.cFileName) &&  strcmp("..",  findFileData.cFileName) )
				{
					if( findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY  )
					{
						FileTimeToSystemTime( &findFileData.ftLastWriteTime , &sysytemtime);

						DeleteFileByTime( filepath  , numDaysToDelete , findFileData.cFileName );
						if( abs(sysytemtime.wDay - newtime->tm_mday) >= numDaysToDelete  )
						{
#ifdef	WIN32
							if( sysytemtime.wMonth == newtime->tm_mon )
							{
								rmdir( temp );
							}
							else if( ( abs( sysytemtime.wMonth - newtime->tm_mon ) == 1 || abs( sysytemtime.wMonth - newtime->tm_mon ) == 11 )
								&& ( ( sysytemtime.wDay > 30 - numDaysToDelete ) && ( newtime->tm_mday < numDaysToDelete ) ) )
							{
								;
							}
							else
							{
								rmdir( temp );
							}


#endif
						}

					}
					else
					{
						FileTimeToSystemTime( &findFileData.ftLastWriteTime , &sysytemtime);
						if( abs(sysytemtime.wDay - newtime->tm_mday) >= numDaysToDelete  )
						{
#ifdef	WIN32
							if( sysytemtime.wMonth == newtime->tm_mon )
							{
								unlink( temp );
							}
							else if( ( abs( sysytemtime.wMonth - newtime->tm_mon ) == 1 || abs( sysytemtime.wMonth - newtime->tm_mon ) == 11 )
								&& ( ( sysytemtime.wDay > 30 - numDaysToDelete ) && ( newtime->tm_mday < numDaysToDelete ) ) )
							{
								;
							}
							else
							{
								unlink( temp );
							}


#endif
						}

					}
				}
			}
		}
		if(!FindNextFile(hfile,&findFileData))    break;
	}
	FindClose( hfile );

}
#else	///	Be operating

#endif

#ifdef _CLIENT_

//
//int NewCrtMemReport( int nRtpType, char * szMsg, int * pRetVal )
//{
//
//	FILE* f = NULL;
//	char szLogName[256] = { 0 };
//	strcpy( szLogName, g_LogName );
//	strcat( szLogName, "mem.log" );
//	f = fopen( szLogName,"at+");
//	if( f )
//	{
//		fprintf(f, "%s", szMsg );
//		fclose(f);
//	}
//	if( pRetVal )
//		*pRetVal = 0;
//	return 1;
//}

//char g_LogName[512] = { 0 };
//
//#define THREAD_LOG
//
//class _LogUnit : public CHAINITEM
//{
//public:
//	char szLog[1024];
//};
//
//CHAINHEADER * g_pLogUnitHead = NULL;
//
////CMemoryPool g_LogPool( sizeof( _LogUnit ), 10, GROW_SLOW );
//
//
//#ifdef WIN32		//	li9chuan	2010-11-29
//
//	HANDLE g_hLogEvent = NULL;
////	HANDLE g_hLogThread = NULL;
//
//#else
//
//	#include <semaphore.h>
//	sem_t g_hLogEvent = NULL;
////	pthread_t g_hLogThread = NULL;
//
//#endif
//
//ThreadLib::ThreadID g_hLogThread = NULL;
//
//char * g_pLogInfo = NULL;
//BOOL g_bLogRun = FALSE;
//FILE* g_hFile = NULL;
////DWORD WINAPI LogThreadFunc( void* pArguments );
//void LogThreadFunc( void* pArguments );

//void Plat_SetSimpleLogName( const char * szLogName )
//{
//	Plat_GetExePath( g_LogName, 256 );
//	//DeleteFileByTime( g_LogName ,1);
//#ifdef WIN32
//	strcat( g_LogName, "Log\\" );
//#else
//	strcat( g_LogName, "Log/" );
//#endif
//
//	struct tm *newtime;
//	time_t aclock;
//	time( &aclock );   // Get time in seconds
//	newtime = localtime( &aclock );   // Convert time to struct tm form
//
//	char strSubLogName[256] = { };
//
//#ifdef WIN32
//
//	FILETIME tmCreateTime ;
//	FILETIME tmExitTime ;
//	FILETIME tmKernalTime ;
//	FILETIME tmUserTime ;
//	SYSTEMTIME tmSystemTime;
//
//	GetProcessTimes( GetCurrentProcess( ),&tmCreateTime , &tmExitTime , &tmKernalTime , &tmUserTime );
//	FileTimeToSystemTime( &tmCreateTime ,&tmSystemTime );
//	TIME_ZONE_INFORMATION    zinfo;
//
//	GetTimeZoneInformation(&zinfo);//得到时区信息
//	SystemTimeToTzSpecificLocalTime(&zinfo,&tmSystemTime,&tmSystemTime);//将格林威治时间转换为对应的当前时区的时间
//	//SetLocalTime(&stime);//设置时间
//	//tReturning = CTime(stime);
//
//	sprintf( strSubLogName ,"[LOG_%d_%d_%d_%d_%d_%d]\\" ,tmSystemTime.wYear ,tmSystemTime.wMonth, tmSystemTime.wDay,tmSystemTime.wHour ,tmSystemTime.wMinute , tmSystemTime.wSecond );
//#else
//	//sprintf( strSubLogName ,"[LOG_%d_%d_%d]\\" , newtime->tm_hour,newtime->tm_min ,newtime->tm_sec );
//	sprintf( strSubLogName ,"[LOG_%d_%d_%d]/" , newtime->tm_hour,newtime->tm_min ,newtime->tm_sec );
//#endif
//	strcat( g_LogName , strSubLogName );
//	strcat( g_LogName, szLogName );
//	if (!Plat_CreatePath( g_LogName )){
//		//return;
//	}
//
//
//	char fileTime[512] = {};
//	sprintf( fileTime ,"[%d_%d_%d].log" , newtime->tm_hour,newtime->tm_min ,newtime->tm_sec );
//	strcat( g_LogName , fileTime );
//
//	//if( g_LogName[0] != 0 )
//	//	g_hFile = fopen(g_LogName,"at+");
//	//unlink( g_LogName );
//#ifdef WIN32
//	//by jinsheng 2009.1.7
//	_CrtSetReportHook( NewCrtMemReport );
//#endif
//
//#ifdef THREAD_LOG
//
//	g_pLogUnitHead = new CHAINHEADER;
////	DWORD dwThreadID = 0;
//	g_bLogRun = TRUE;// by sun 2009.2.7
//
//	#ifdef WIN32
//		g_hLogEvent = CreateEvent( NULL, TRUE, FALSE, NULL );// by sun 2009.2.7 //  [4/10/2010 sun ]
//	//	g_hLogThread = (HANDLE)CreateThread( NULL, 0, &LogThreadFunc, NULL, 0, &dwThreadID );
//	#else
//		sem_init( &g_hLogEvent, 1, 0 );			// li9chuan	2010-12-1
//	#endif
//
//	g_hLogThread = ThreadLib::Create( LogThreadFunc, NULL );
//
//#endif
//}


//void Plat_DestroyLog( )
//{
//	g_bLogRun = FALSE;
//#ifdef WIN32
//	SetEvent( g_hLogEvent );
//#else
//	sem_post( &g_hLogEvent );
//#endif
//	fclose(g_hFile);
//}
//

//
//CPlatformCS g_LogInfoCS;
//
//#ifdef THREAD_LOG
//void* Plat_SimpleLog( const char* file, int line )
//#else
//void* _Plat_SimpleLog( const char* file, int line )
//#endif
//{
//	if( !g_bLogRun )
//		return NULL;
//	_LogUnit * pUnit = new _LogUnit;
//
//	if ( !pUnit )
//	{
//		OutputDebugString( "new logunit failed !!!!!\n" );
//		return NULL;
//	}
//	pUnit->szLog[0] = 0;
//
//	struct tm *newtime;
//	time_t aclock;
//	time( &aclock );   // Get time in seconds
//	newtime = localtime( &aclock );   // Convert time to struct tm form
//	char * sztime = asctime( newtime );
//	int nLen = lstrlen( sztime );
//	if( nLen > 0 )
//	{
//		sztime[nLen-1] = 0;
//		strcat( pUnit->szLog, "[" );
//		strcat( pUnit->szLog, "[" );
//		strcat( pUnit->szLog, sztime );
//		strcat( pUnit->szLog, "]" );
//		strncat( pUnit->szLog, file, 900);//strcat( pUnit->szLog, file );
//	}
//	pUnit->szLog[1023] = 0;
//
//	g_LogInfoCS.Lock( );
//	g_pLogUnitHead->Add( pUnit );
//	g_LogInfoCS.Unlock( );
//
//#ifdef WIN32	//	2010-11-29	li9chuan
//	SetEvent( g_hLogEvent );
//#else
//	sem_post( &g_hLogEvent );
//#endif
//
//	return NULL;
//}
//
//
//CPlatformCS g_LogCS;
//
//#ifdef THREAD_LOG
//void* _Plat_SimpleLog( const char* file, int line )
//#else
//void* Plat_SimpleLog( const char* file, int line )
//#endif
//{
//	g_LogCS.Lock( );
//	//FILE* f = NULL;
//
//	g_hFile = fopen(g_LogName,"at+");
//	if( g_hFile )
//	{
//		fprintf( g_hFile, "%s\n", file );
//
//	}
//	fclose( g_hFile );
//	g_LogCS.Unlock( );
//
//	return NULL;
//}
//
//BOOL GetLogHead( char * szLogTemp )
//{
//	BOOL bRet = FALSE;
//	g_LogInfoCS.Lock( );
//	if( g_pLogUnitHead )
//	{
//		_LogUnit * pUnit = (_LogUnit *)g_pLogUnitHead->First( );
//		if( pUnit )
//		{
//			strcpy( szLogTemp, pUnit->szLog );
//			pUnit->DisConnect( );
//			delete pUnit;
//			bRet = TRUE;
//		}
//	}
//	g_LogInfoCS.Unlock( );
//	return bRet;
//}
//
//#ifdef WIN32
//#else	///	Be operating
//
//#endif
////DWORD WINAPI LogThreadFunc( void* pArguments )
//void LogThreadFunc( void* pArguments )
//{
//	char g_szLogInfoTemp[1024] = { 0 };
//	for(;;)
//	{
//
//#ifdef WIN32
// 		WaitForSingleObject( g_hLogEvent, INFINITE );
//#else
// 		sem_wait( &g_hLogEvent );
//#endif
//
//		if( !g_bLogRun )
//			break;
//
//		while( GetLogHead( g_szLogInfoTemp ) )
//		{
//			if( g_szLogInfoTemp[0] != 0 )
//				_Plat_SimpleLog( g_szLogInfoTemp, 0 );
//			g_szLogInfoTemp[0] = 0;
//		}
//
//#ifdef WIN32
//		ResetEvent( g_hLogEvent );
//#endif
//	}
//	//ExitThread( 30 );
//
//	if( g_hLogEvent )
//	{
//#ifdef WIN32
//		CloseHandle( g_hLogEvent );
//#else
//		sem_destroy( &g_hLogEvent );
//#endif
//		g_hLogEvent = NULL;
//	}
//
//	if( g_hLogThread )
//	{
//		//CloseHandle( g_hLogThread );
//		ThreadLib::WaitForFinish( g_hLogThread );
//		g_hLogThread = NULL;
//	}
//
//	while( GetLogHead( g_szLogInfoTemp ) );
//
//	if( g_pLogUnitHead )
//	{
//		delete g_pLogUnitHead;
//		g_pLogUnitHead = NULL;//by sun
//	}
////	return 30;
//}

#endif

/*
void RunMemReport( )
{
	MEMREPORTITEM * pItem = (MEMREPORTITEM *)s_MemreportList.First( );
	while( pItem )
	{
		(*pItem->pFn)( );
		pItem = (MEMREPORTITEM *)pItem->Next( );
	}
}
*/

void _ClearVprof(  )
{
 	for( vector<char *>::iterator it = g_vecVprofMessage.begin( ) ; it != g_vecVprofMessage.end( ) ; ++it )
 	{
 		delete *it;
 	}
	g_vecVprofMessage.clear( );
}

int _GetVprofSize( )
{
	return g_vecVprofMessage.size( );
}

char * _GetVprofstr( int itPos )
{
	vector< char* >::iterator it = g_vecVprofMessage.begin( );
	return it[itPos];
}

//#endif


void Log( char const *pMsgFormat, ... )
{
	va_list args;
	va_start( args, pMsgFormat );

	_SpewMessage( SPEW_LOG, pMsgFormat, args );

	va_end(args);
}


