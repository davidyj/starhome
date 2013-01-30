#pragma once
#include "File.h"

class ENGINE_CLASS CFileStdio : public IFile
{
	DECLARE_CLASS( CFileStdio )
public:
	CFileStdio(void);
	virtual ~CFileStdio(void);

	virtual BOOL	Open( const char * szName, const char *pFlags, const char * szPathID );
	virtual BOOL	Open( const wchar_t * szName, const wchar_t *pFlags, const wchar_t * szPathID );
	virtual void	Close( );
	virtual int		Read( void * pBuf, uint uSize );
	virtual int		Write( void * pBuf, uint uSize );
	virtual void	Seek( int nPos, int nFrom );

	virtual char*	ReadLine( char * pBuf, uint uSize );
	virtual uint	GetLength( );

	virtual int		PrintF2( const char * format, ... );
	//virtual int		ScanF( const char * format, ... );
	
	void * GetHandle( ){ return m_pFile; }

private:
	void * m_pFile;
};

#ifdef VPROF_ENABLED
class CVProfile;
ENGINE_CLASS CVProfile & GetVprofEngine( );
#endif

// 读取文件到内存中，返回值是文件在内存中的地址。
// 注意：数据使用完毕需要用ReleaseFileBuffer释放所分配的内存。
ENGINE_GLOBAL void * LoadFileToBuffer( const wchar_t * szName, const wchar_t * szPathID, uint * pnLength = NULL );
ENGINE_GLOBAL void * LoadFileToBuffer( const char * szName, const char * szPathID, uint * pnLength = NULL );
ENGINE_GLOBAL void  SaveBufferToFile( void *pBuffer, const char * szName, const char * szPathID, uint nLength );
ENGINE_GLOBAL void ReleaseFileBuffer( void * pBuffer );
ENGINE_GLOBAL int GetFileLength( const wchar_t * szName, const wchar_t * szPathID );
ENGINE_GLOBAL int GetFileLength( const char * szName, const char * szPathID );
