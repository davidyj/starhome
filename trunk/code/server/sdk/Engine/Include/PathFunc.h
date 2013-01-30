#pragma once
#include "EngineDefine.h"

ENGINE_GLOBAL void GetExePath( char * szExePath, int nSize );
ENGINE_GLOBAL void GetRootPath( char * szExePath, int nSize );

#ifdef WIN32
ENGINE_GLOBAL BOOL InitFileSystem( HWND hWnd = NULL );
ENGINE_GLOBAL BOOL InitFileSystemClient( HWND hWnd = NULL );
#else
ENGINE_GLOBAL BOOL InitFileSystem(void);
#endif
ENGINE_GLOBAL BOOL InitFileSystemEx( int nCount, const char* pathstr[] );
ENGINE_GLOBAL BOOL InitFileSystemSvr();

ENGINE_GLOBAL void ShutdownFileSystem( );
ENGINE_GLOBAL BOOL CreatePath( LPCTSTR fullname );
ENGINE_GLOBAL BOOL BackupFile( LPCSTR szName );
ENGINE_GLOBAL BOOL BackupFileByFileSystem( LPCSTR szName, LPCSTR lpszPathID );
ENGINE_GLOBAL BOOL IsReadOnly( LPCSTR szName, LPCSTR lpszPathID );
ENGINE_GLOBAL void SetReadOnly( LPCSTR szName, LPCSTR lpszPathID, BOOL bReadOnly = TRUE );
