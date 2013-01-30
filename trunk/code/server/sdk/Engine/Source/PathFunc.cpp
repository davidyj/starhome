#include "../stdafx.h"
#include "PathFunc.h"
#include "ICommandLine.h" // CommandLine( )
#include "dbg.h" // Assert
#include "strtools.h" // Q_strcpy
#include "BaseFileSystem.h" // FileSystem( )
#include "LuaEngine_Svr.h"

#ifndef WIN32
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#endif

void GetExePath( char * szExePath, int nSize )
{
	Plat_GetExePath( szExePath, nSize );
}

void GetRootPath( char * szExePath, int nSize )
{
	if ((!szExePath) || (nSize<=0))
		return;
#ifdef WIN32
	char szTempPath[256];
	HMODULE hmodule =  GetModuleHandle( NULL );
	GetModuleFileName( hmodule, szTempPath, 256 );
	// 必须初始化CommandLine( )，使用CommandLine( ).CreateCmdLine
	Assert( CommandLine( ).ParmCount( ) != 0 );
	Q_strcpy( szExePath, CommandLine( ).GetParm( 0 ) );
	if (stricmp(szTempPath,szExePath)!=0)
	{
		char szMsg[1024] = { 0 };
		sprintf( szMsg, "文件路径异常%s,%s",szExePath, szTempPath );
		MessageBox(NULL,szMsg,"异常",MB_OK);
	}
	char * pEnd = szExePath;
	char * p;
	char c = '\\';
	while (p = strchr(pEnd,c)){
		pEnd = ++p;
	}
	pEnd--;
	*pEnd = 0;
	pEnd = szExePath;
	while (p = strchr(pEnd,c)){
		pEnd = ++p;
	}
	*pEnd = 0;
#else
	/*
	 * return the parent directory of current directory
	 */
	getcwd(szExePath, nSize);
	char *p = szExePath + strlen(szExePath) - 1;
	while ((p>szExePath) && ((*p) != '/'))
		p--;
	if ((*p) == '/'){
		p[1] = '\0';
	}
#endif
}

BOOL InitFileSystemSvr()
{
	const char* szPath[10] = {0};
	int nPathCount = GetLuaEngine_Svr().GetLuaVariableNumber( "pathcount" );
	for(int i=0; i<nPathCount; ++i)
	{
		char szparam[32] = {0};
		sprintf( szparam, "path%d", i+1 );
		szPath[i] = GetLuaEngine_Svr().GetLuaVariableString(szparam);
	}

	return InitFileSystemEx( nPathCount, szPath );
}

BOOL InitFileSystemEx( int nCount, const char* pathstr[] )
{
	// 初始化文件系统
	FileSystem( ).Init( );

	char szExePath[256];
	char szPath[256];
//	char szData[256];
	szExePath[0] = 0;

	GetExePath(szExePath,256);

	// 初始化路径
	// 路径系统初始化格式 path%d "PathName PathID"
	for( int i = 1; i <= nCount; i++ )
	{
		const char * szValue = pathstr[i-1];
		if( szValue[0] != '\0' )
		{
			char szPathName[256];
			char szPathID[256];
			CutString( szValue, szPathName, 256, 0, ' ' );
			CutString( szValue, szPathID, 256, 1, ' ' );
			strcpy( szPath, szExePath );
			strcat( szPath, szPathName );
			if( !FileSystem( ).AddSearchPath( szPath, szPathID, PATH_ADD_TO_TAIL ) )
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

#ifdef WIN32
BOOL InitFileSystem( HWND hWnd )
#else
BOOL InitFileSystem(void)
#endif
{
	//printf( "Init file system...\n" );
	// 初始化文件系统
	FileSystem( ).Init( );

	char szExePath[256];
	char szPath[256];
	char szData[256];
	szExePath[0] = 0;

	// 是否使用虚拟文件系统
//	if( CommandLine( ).ParmValue( "UseVirtualFilesystem", 0 ) == 0 )
		//GetRootPath( szExePath, 256 );
	GetExePath(szExePath,256);  //by fuqiang 2010.1.25 binR取消，cursor路径

	// 初始化路径
	// 路径系统初始化格式 path%d "PathName PathID"
	int nCount = CommandLine( ).ParmValue( "pathcount", 0 );
	for( int i = 1; i <= nCount; i++ )
	{
		sprintf( szData, "path%d", i );
		const char * szValue = CommandLine( ).ParmValue( szData, "" );
		if( szValue[0] != '\0' )
		{
			char szPathName[256];
			char szPathID[256];
			CutString( szValue, szPathName, 256, 0, ' ' );
			CutString( szValue, szPathID, 256, 1, ' ' );
			strcpy( szPath, szExePath );
			strcat( szPath, szPathName );
			if( !FileSystem( ).AddSearchPath( szPath, szPathID, PATH_ADD_TO_TAIL ) )
			{
#ifdef WIN32
				if( hWnd )
				{
					char szMsg[1024] = { 0 };
					sprintf( szMsg, "资源包%s.dat损坏，请重新安装客户端或者使用修复功能。", szPath );
				}
#endif
				return FALSE;
			}
		}
	}
	return TRUE;
}

#ifdef WIN32
BOOL InitFileSystemClient( HWND hWnd )
{
//	FileBufferScheduler().Init( "Client File Buffer", 1024*1024*100, 1024*1024*5 );

	//printf( "Init file system...\n" );
	// 初始化文件系统
	int nFileCacheSize = CommandLine( ).ParmValue( "FileChcheSize", 1024*1024*200 );
	int nFileMax	   = CommandLine( ).ParmValue( "FileMax", 1024*1024*5 );

	FileSystem().InitFileCache( "Client File Cache", nFileCacheSize, nFileMax );
	FileSystem( ).Init( );

	char szExePath[256];
	char szPath[256];
	char szData[256];
	szExePath[0] = 0;

	// 是否使用虚拟文件系统
//	if( CommandLine( ).ParmValue( "UseVirtualFilesystem", 0 ) == 0 )
		//GetRootPath( szExePath, 256 );
	GetExePath(szExePath,256);  //by fuqiang 2010.1.25 binR取消，cursor路径

#ifndef __DEV__

	static const char* pathstr[] =
	{
		{"scripts RES_PATH"},
		{"Data DATA_PATH"},
		{"resource STUDIO_PATH"},
		{"resourceSrc STUDIO_SRC_PATH"},
		{"sounds SOUNDS_PATH"},
		{"Fonts FONT_PATH"},
		{"scene MAP_PATH"},
		{"ClientLua AI_PATH"},
		{"picture PIC_PATH"},
		{"effect EFF_PATH"},
		{"resource2 STUDIO_PATH2"},
		{"resource3 STUDIO_PATH3"}
	};
	int nCount = 12;
#else
	int nCount = CommandLine( ).ParmValue( "pathcount", 12 );
#endif

	// 初始化路径
	// 路径系统初始化格式 path%d "PathName PathID"
	for( int i = 1; i <= nCount; i++ )
	{
#ifndef __DEV__
		const char * szValue = pathstr[i-1];
#else
		sprintf( szData, "path%d", i );
		const char * szValue = CommandLine( ).ParmValue( szData, "" );
#endif
		if( szValue[0] != '\0' )
		{
			char szPathName[256];
			char szPathID[256];
			CutString( szValue, szPathName, 256, 0, ' ' );
			CutString( szValue, szPathID, 256, 1, ' ' );
			strcpy( szPath, szExePath );
			strcat( szPath, szPathName );
			if( !FileSystem( ).AddSearchPath( szPath, szPathID, PATH_ADD_TO_TAIL ) )
			{
#ifdef WIN32
				if( hWnd )
				{
					char szMsg[1024] = { 0 };
					sprintf( szMsg, "资源包%s.dat损坏，请重新安装客户端或者使用修复功能。", szPath );
				}
#endif
				return FALSE;
			}
		}
	}
	return TRUE;
}
#endif

void ShutdownFileSystem( )
{
	FileSystem( ).Shutdown( );
}

BOOL CreatePath( LPCTSTR fullname )
{
	return Plat_CreatePath( fullname );
}

//如果有szName，则备份szName到d:\myBak\path\name+time.ext
BOOL BackupFile( LPCSTR szName )
{
#ifdef WIN32
	//建立目录 d:\myBak\path
	char Temp[256];
	MakeNakedPath( szName, Temp, 256 );
	char SrcFilePath[256];
	sprintf( SrcFilePath, "d|\\MyBak\\%s", Temp );
	char * str1 = strstr( SrcFilePath, ":" );
	if( str1 )
		*str1 = ')';
	str1 = strstr( SrcFilePath, "|" );
	if( str1 )
		*str1 = ':';
	CreatePath( SrcFilePath );

	MakeNakedNameIndex( szName, Temp, 256, 0 );
	//文件名前缀
	char szNoExt[256];
	GetFileNameNoExt( Temp,szNoExt,256 );
	//文件名后缀
	char szExt[256];
	GetFileNameExt( Temp,szExt,256 );

	time_t curtime;
	time( &curtime );
	tm * today = localtime( &curtime );

	char szNewName[256];
	sprintf( szNewName, "%s\\%s(%d-%d-%d-%d-%d-%d).%s",SrcFilePath,szNoExt,
		today->tm_year, today->tm_mon, today->tm_mday, today->tm_hour,
		today->tm_min, today->tm_sec, szExt );

	return CopyFile( szName,szNewName,true );
#else
	printf("XXX:BackupFile() could not be implemented, in file %s\n", __FILE__);
	abort();
#endif
	return TRUE;
}

BOOL IsReadOnly( LPCSTR szName, LPCSTR lpszPathID )
{
#ifdef WIN32
	char szBackupFile[256];
	const char * szPath = FileSystem( ).GetSearchPath( lpszPathID );
	sprintf( szBackupFile, "%s\\%s", szPath, szName );
	DWORD dwAttribute = 0;
	dwAttribute = ::GetFileAttributes( szBackupFile );
	if( dwAttribute != 0xffffffff )
		return dwAttribute & FILE_ATTRIBUTE_READONLY;
	return FALSE;
#else
	printf("XXX: BackupFile() could not be implemented, in file %s\n", __FILE__);
	abort();
	return FALSE;
#endif
}

void SetReadOnly( LPCSTR szName, LPCSTR lpszPathID, BOOL bReadOnly )
{
#ifdef WIN32
	char szBackupFile[256];
	const char * szPath = FileSystem( ).GetSearchPath( lpszPathID );
	sprintf( szBackupFile, "%s%s", szPath, szName );
	DWORD dwAttribute = 0;
	dwAttribute = ::GetFileAttributes( szBackupFile );
	if( dwAttribute != 0xffffffff )
	{
		if( bReadOnly )
			dwAttribute |= FILE_ATTRIBUTE_READONLY;
		else
			dwAttribute &= ~FILE_ATTRIBUTE_READONLY;
		::SetFileAttributes( szBackupFile, dwAttribute );
	}
#else
	printf("XXX:SetReadOnly() could not be implemented, in file %s\n", __FILE__);
	abort();
#endif
}

BOOL BackupFileByFileSystem( LPCSTR szName, LPCSTR lpszPathID )
{
	char szBackupFile[256];
	const char * szPath = FileSystem( ).GetSearchPath( lpszPathID );
	sprintf( szBackupFile, "%s%s", szPath, szName );
	if( FileSystem( ).FileExists( szBackupFile ) )
	{
		if( IsReadOnly( szName, lpszPathID ) )
		{
			#ifdef WIN32
			MessageBox( NULL, "请将文件签出再做修改！", "警告",  MB_ICONWARNING | MB_OK );
			#endif
			return FALSE;
		}

		return BackupFile( szBackupFile );
	}

	return TRUE;
}
