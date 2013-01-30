#include "../stdafx.h"
#include "vprof.h"
#include "FileStdio.h"
#include "BaseFileSystem.h"
#include "strtools.h" // WideCharToChar

#define _CRTBLD

#ifdef WIN32
//#ifndef VC2008
//#include "mtdll.h"
//#include "internal.h"
//#endif
#else
#include <stdio.h>
#include <stdlib.h>
#endif

CFileStdio::CFileStdio(void)
{
	m_pFile = NULL;
}

CFileStdio::~CFileStdio(void)
{
	Close( );
}

IMPLEMENT_CLASS( CFileStdio, IFile )

BOOL CFileStdio::Open( const char * szName, const char *pFlags, const char * szPathID )
{
	Assert( m_pFile == NULL );
	m_pFile = FileSystem( ).Open( szName, pFlags, szPathID );

	return m_pFile ? TRUE : FALSE;
}

BOOL CFileStdio::Open( const wchar_t * szName, const wchar_t *pFlags, const wchar_t * szPathID )
{
	Assert( m_pFile == NULL );

	char szAnsiName[256];
	char szAnsiFlags[256];
	char szAnsiPathID[256];
	WideCharToChar( szName, szAnsiName, 256 );
	WideCharToChar( pFlags, szAnsiFlags, 256 );
	WideCharToChar( szPathID, szAnsiPathID, 256 );

	m_pFile = FileSystem( ).Open( szAnsiName, szAnsiFlags, szAnsiPathID );

	return m_pFile ? TRUE : FALSE;
}

void CFileStdio::Close( )
{
	if( m_pFile )
	{
		FileSystem( ).Close( m_pFile );
		m_pFile = NULL;
	}
}

int	CFileStdio::Read( void * pBuf, uint uSize )
{
	Assert( m_pFile != NULL );
	return FileSystem( ).Read( pBuf, uSize,0, m_pFile );
}

int	CFileStdio::Write( void * pBuf, uint uSize )
{
	Assert( m_pFile != NULL );
	return FileSystem( ).Write( pBuf, uSize, m_pFile );
}

void CFileStdio::Seek( int nPos, int nFrom )
{
	Assert( m_pFile != NULL );
	FileSystem( ).Seek( m_pFile, nPos, (FileSystemSeek_t)nFrom );
}

char *CFileStdio::ReadLine( char * pBuf, uint uSize )
{
	Assert( m_pFile != NULL );
	return FileSystem( ).ReadLine( pBuf, uSize, m_pFile );
}

uint CFileStdio::GetLength( )
{
	Assert( m_pFile != NULL );
	return FileSystem( ).Size( m_pFile );
}

int	CFileStdio::PrintF2( const char * format, ... )
{
	Assert( m_pFile != NULL );

	va_list arglist;
	va_start(arglist, format);

	FILE * stream = ((CBaseFileSystem::CFileHandle*)m_pFile)->m_pFile;

	Assert(stream != NULL);
	Assert(format != NULL);

	return vfprintf( stream, format, arglist );
}

#ifdef WIN32
#if 0
int	CFileStdio::ScanF( const char * format, ... )
{
	Assert( m_pFile != NULL );
	int retval = 0;
#ifndef _ENGINELIB
    va_list arglist;
    va_start(arglist, format);

    FILE * stream = ((CBaseFileSystem::CFileHandle*)m_pFile)->m_pFile;

    Assert(stream != NULL);
    Assert(format != NULL);

#ifdef _MT
    _lock_str(stream);
    __try {
#endif  /* _MT */

    retval = (_input(stream,(const unsigned char*)format,arglist));

#ifdef _MT
    }
    __finally {
            _unlock_str(stream);
    }
#endif  /* _MT */
	va_end(arglist);
#endif
    return(retval);
}
#endif
#else
#if 0
int	CFileStdio::ScanF( const char * format, ... )
{
	Assert( m_pFile != NULL );
	int retval = 0;
    	va_list arglist;
    	va_start(arglist, format);

    	FILE * stream = ((CBaseFileSystem::CFileHandle*)m_pFile)->m_pFile;

    	Assert(stream != NULL);
    	Assert(format != NULL);

    	//retval = (_input(stream,(const unsigned char*)format,arglist));
	retval = vfscanf(stream, format, arglist);

	va_end(arglist);
    	return(retval);

}
#endif
#endif

ENGINE_GLOBAL void * LoadFileToBuffer( const wchar_t * szName, const wchar_t * szPathID, uint * pnLength /*= NULL*/ )
{
	Assert( szName );
	Assert( szPathID );

	char szAnsiName[256];
	char szAnsiPathID[256];
	WideCharToChar( szName, szAnsiName, 256 );
	WideCharToChar( szPathID, szAnsiPathID, 256 );

	return LoadFileToBuffer( szAnsiName, szAnsiPathID, pnLength );
}

ENGINE_GLOBAL void  SaveBufferToFile( void *pBuffer, const char * szName, const char * szPathID, uint nLength )
{

	CFileStdio DataFile;
	if( DataFile.Open( szName, "wb", szPathID ) )
	{
		DataFile.Write(pBuffer, nLength);
		DataFile.Close();
	}

}


ENGINE_GLOBAL void * LoadFileToBuffer( const char * szName, const char * szPathID, uint * pnLength /*= NULL*/ )
{
	AssertValidStringPtr( szName );
	AssertValidStringPtr( szPathID );

	BYTE * pData = NULL;
	CFileStdio DataFile;
	if( DataFile.Open( szName, "rb", szPathID ) )
	{
		int nSize = DataFile.GetLength( );
		if( pnLength )
			*pnLength = nSize;
		// FIX_ME 处理图像文件结尾未按4字对其的地方可能越界，暂时多加入3个字以防止出错
//		pData = (BYTE*)Plat_Alloc( nSize + 6 );
		if( nSize > 0 )
			pData = (BYTE*)Plat_Alloc( nSize );
		if( pData )
		{
			DataFile.Read( pData, nSize );
		}
		DataFile.Close( );
	}

	return pData;
}

ENGINE_GLOBAL void ReleaseFileBuffer( void * pBuffer )
{
	if( pBuffer )
	{
		Plat_Free( pBuffer );
		pBuffer = NULL;
	}
}

int GetFileLength( const wchar_t * szName, const wchar_t * szPathID )
{
	Assert( szName );
	Assert( szPathID );

	char szAnsiName[256];
	char szAnsiPathID[256];
	WideCharToChar( szName, szAnsiName, 256 );
	WideCharToChar( szPathID, szAnsiPathID, 256 );

	return GetFileLength( szAnsiName, szAnsiPathID );
}

ENGINE_GLOBAL int GetFileLength( const char * szName, const char * szPathID )
{
	AssertValidStringPtr( szName );
	AssertValidStringPtr( szPathID );

	int nSize = 0;
	CFileStdio DataFile;
	if( DataFile.Open( szName, "rb", szPathID ) )
		nSize = DataFile.GetLength( );
	return nSize;
}

#ifdef VPROF_ENABLED
CVProfile & GetVprofEngine( )
{
	return VProfCurrentProfile( );
}
#endif
