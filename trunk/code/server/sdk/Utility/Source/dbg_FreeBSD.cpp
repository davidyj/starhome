//
//
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
#include <assert.h>

#include <stdlib.h>

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "dbg.h"
#include <math.h>
#include <time.h>
#include <signal.h> // raise
#include <pthread.h>
#include <fcntl.h>

#ifdef WIN32
#error "this file should not used on WIN32"
#endif

/*
 *XXX: 当前的日志，只支持一个日志文件
 */
FILE *g_LogFile = NULL;
CHAINHEADER * g_pLogUnitHead = NULL;

//CMemoryPool g_LogPool( sizeof( _LogUnit ), 10, GROW_SLOW );

//保护日志缓冲区的锁
pthread_mutex_t g_LogInfoMtx = PTHREAD_MUTEX_INITIALIZER;

//条件变量，通知日志线程去写日志
pthread_mutex_t g_LogMtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t g_LogCondVar = PTHREAD_COND_INITIALIZER;

pthread_t  g_hLogThread = NULL;//日志线程
BOOL g_bLogRun = FALSE;
void *LogThreadFunc(void* pArguments); //日志线程的主函数


//#include "memdbgon.h"
//-----------------------------------------------------------------------------
// internal structures
//-----------------------------------------------------------------------------

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
	Assert(ptr);

}

void _AssertValidWritePtr( void* ptr, int count/* = 1*/ )
{
	Assert(ptr);
}

void _AssertValidReadWritePtr( void* ptr, int count/* = 1*/ )
{
	Assert(ptr);
}

void AssertValidStringPtr( const char* ptr, int maxchar/* = 0xFFFFFF */ )
{
	Assert(ptr);
}


//-----------------------------------------------------------------------------
// globals
//-----------------------------------------------------------------------------

SpewRetval_t DefaultSpewFunc( SpewType_t type, char const *pMsg )
{
	static char s_Msg[1024];
	if( type == SPEW_ASSERT )
	{
		raise(SIGABRT);
		return SPEW_DEBUGGER;
	}
	else if( type == SPEW_ERROR )
	{
		fprintf(stderr, "Error: %s\n", pMsg);
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
		int nLen = strlen( s_Msg );
		if( s_Msg[nLen-1] == '\n' )
			s_Msg[nLen-1] = '\0';
		Plat_SimpleLog( s_Msg, __LINE__ );
		return SPEW_CONTINUE;
	}
	else
		return SPEW_CONTINUE;

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
	len += vsnprintf(&pTempBuffer[len], 1023, pMsgFormat, args);
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
	default:
		printf("default switch in file %s line %d\n", __FILE__, __LINE__);
		break;
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
#ifdef _DEBUG
	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_WARNING, pMsgFormat, args );
	va_end(args);
#endif
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

void Log( char const *pMsgFormat, ... )
{
	va_list args;
	va_start( args, pMsgFormat );
	_SpewMessage( SPEW_LOG, pMsgFormat, args );
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

char g_LogName[256] = { 0 };
/*
class ClearLogName
{
public:
ClearLogName( )
{
g_LogName[0] = 0;
}
};*/


int NewCrtMemReport( int nRtpType, char * szMsg, int * pRetVal )
{

	FILE* f = NULL;
	char szLogName[256] = { 0 };
	strcpy( szLogName, g_LogName );
	strcat( szLogName, "mem.log" );
	f = fopen( szLogName,"at+");
	if( f )
	{
		fprintf(f, "%s", szMsg );
		fclose(f);
	}
	if( pRetVal )
		*pRetVal = 0;
	return 1;
}


#define THREAD_LOG

class _LogUnit : public CHAINITEM
{
public:
	char szLog[1024];
};

void DeleteFileByTime(const char * filepath ,int numDaysToDelete)
{
#ifdef WIN32
	char szFindDir[512] = {};
	char szFindFileName[512] = {};
	WIN32_FIND_DATA  findFileData;
	strcpy( szFindDir,filepath);
	strcat( szFindDir , "Log\\");
	strcat( szFindFileName ,filepath);
	strcat( szFindFileName,"Log\\*.*");
	HANDLE hfile = FindFirstFile( szFindFileName , &findFileData);
	if(INVALID_HANDLE_VALUE == hfile)    return;
	SYSTEMTIME sysytemtime;
	struct tm *newtime;
	time_t aclock;
	time( &aclock );
	newtime = localtime( &aclock );
	while(TRUE)
	{
		{
			//if( GetFileTime( hfile ,NULL ,NULL ,&filetime) )
			char temp[512] = {};
			strcpy( temp , szFindDir);
			strcat( temp ,findFileData.cFileName );
			if( strcmp( findFileData.cFileName ,"errorlog.txt") != 0)
			{
				FileTimeToSystemTime( &findFileData.ftLastWriteTime , &sysytemtime);

				if( abs(sysytemtime.wDay - newtime->tm_mday) >= numDaysToDelete )
					unlink( temp );

			}

		}
		if(!FindNextFile(hfile,&findFileData))    break;
	}
	FindClose( hfile );
#else
	printf("function %s not implemented on FreeBSD.\n", __func__);
#endif
}

void Plat_SetSimpleLogName( const char * szLogName )
{
	Plat_GetExePath( g_LogName, 256 );
	//DeleteFileByTime( g_LogName ,1);
	strcat( g_LogName, "/Log/" );
//	strcat( g_LogName, szLogName );

	/*
	if (!Plat_CreatePath( g_LogName )){
		printf("failed to create log file :%s\n", g_LogName);
		return;
	}
	*/


	struct tm *newtime;
	time_t aclock;
	time( &aclock );   // Get time in seconds
	newtime = localtime( &aclock );   // Convert time to struct tm form

	char strSubLogName[256] = { };
	sprintf( strSubLogName ,"[LOG_%d_%d_%d]/" , newtime->tm_hour,newtime->tm_min ,newtime->tm_sec );
	strcat( g_LogName , strSubLogName );
	strcat( g_LogName, szLogName );
	if (!Plat_CreatePath( g_LogName )){
		//return;
	}

	char fileTime[64] = {};
	sprintf( fileTime ,"[%d_%d_%d].log",newtime->tm_hour,newtime->tm_min ,newtime->tm_sec);
	strcat( g_LogName , fileTime );

	g_LogFile = fopen(g_LogName, "a+");
	if (!g_LogFile){
		printf("failed to fdopen this log file:%s\n", szLogName);
		exit(0);
		return;
	}

#ifdef THREAD_LOG
	g_pLogUnitHead = new CHAINHEADER();
	g_bLogRun = TRUE;// by sun 2009.2.7

   pthread_mutex_init( &g_LogInfoMtx, NULL );
   pthread_mutex_init( &g_LogMtx, NULL );
   pthread_cond_init( &g_LogCondVar, NULL );

	pthread_create( &g_hLogThread, NULL, &LogThreadFunc, NULL);
#endif
}

void Plat_DestroyLog( )
{
	g_bLogRun = FALSE;
	if (g_LogFile){
		fclose(g_LogFile);
	}
}


#ifdef THREAD_LOG
void* Plat_SimpleLog( const char* file, int line )
{
	if( !g_bLogRun )
		return NULL;
	_LogUnit * pUnit = new _LogUnit;
	pUnit->szLog[0] = 0;

	struct tm *newtime;
	time_t aclock;
	time( &aclock );   // Get time in seconds
	newtime = localtime( &aclock );   // Convert time to struct tm form
	char * sztime = asctime( newtime );
	int nLen = strlen( sztime );

	if( nLen > 0 )
	{
		sztime[nLen-1] = 0;
		strcat( pUnit->szLog, "[" );
		strcat( pUnit->szLog, "[" );
		strcat( pUnit->szLog, sztime );
		strcat( pUnit->szLog, "]" );
		strcat( pUnit->szLog, file );
	}

	pthread_mutex_lock(&g_LogInfoMtx);
	g_pLogUnitHead->Add( pUnit );
	pthread_mutex_unlock(&g_LogInfoMtx);

	pthread_cond_broadcast(&g_LogCondVar);

	return NULL;
}

/*
 * write the message to the log file
 */
void* _Plat_SimpleLog( const char* file, int line )
#else
void* Plat_SimpleLog( const char* file, int line )
#endif
{
	pthread_mutex_lock(&g_LogInfoMtx);
	if(g_LogFile){
		fprintf(g_LogFile, "%s\n", file );
	}
	pthread_mutex_unlock(&g_LogInfoMtx);
	return NULL;
}

BOOL GetLogHead( char * szLogTemp )
{
	BOOL bRet = FALSE;
	pthread_mutex_lock(&g_LogInfoMtx);
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
	pthread_mutex_unlock(&g_LogInfoMtx);
	return bRet;
}

/*
 * log thread's main function
 */
void *LogThreadFunc( void* pArguments )
{
	char g_szLogInfoTemp[1024] = { 0 };

	for(;;)
	{
		if( !g_bLogRun )
			break;

		pthread_mutex_lock(&g_LogMtx);

		while( !GetLogHead( g_szLogInfoTemp ) )
			pthread_cond_wait(&g_LogCondVar, &g_LogMtx);

		do
		{
			if( g_szLogInfoTemp[0] != 0 ) {
				_Plat_SimpleLog( g_szLogInfoTemp, 0 );
				printf( "%s\n",g_szLogInfoTemp );
			}
			g_szLogInfoTemp[0] = 0;
		}
		while( GetLogHead( g_szLogInfoTemp ) );

		pthread_mutex_unlock(&g_LogMtx);


	/*
		pthread_mutex_lock(&g_LogMtx);
		pthread_cond_wait(&g_LogCondVar, &g_LogMtx);
		pthread_mutex_unlock(&g_LogMtx);

		if( !g_bLogRun )
			break;


		pthread_mutex_lock(&g_LogInfoMtx);
		while( GetLogHead( g_szLogInfoTemp ) )
		{
			if( g_szLogInfoTemp[0] != 0 ) {
				_Plat_SimpleLog( g_szLogInfoTemp, 0 );
			}
			g_szLogInfoTemp[0] = 0;
		}

		pthread_mutex_unlock(&g_LogInfoMtx);
	//*/
	}

	pthread_mutex_lock(&g_LogInfoMtx);
	while( GetLogHead( g_szLogInfoTemp ) );
	pthread_mutex_unlock(&g_LogInfoMtx);

	if( g_pLogUnitHead )
	{
		delete g_pLogUnitHead;
		g_pLogUnitHead = NULL;//by sun
	}
	return NULL;
}
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
