#pragma once

#include "BaseObj.h"

enum FileSeek_t
{
	FILE_SEEK_HEAD = 0,
	FILE_SEEK_CURRENT,
	FILE_SEEK_TAIL,
};

class ENGINE_CLASS IFile : public IBaseObj
{
	DECLARE_CLASS( IFile )
public:
	IFile(void);
	virtual ~IFile(void);

	virtual BOOL	Open( const char * szName, const char *pFlags, const char * szPathID ) = 0;
	virtual BOOL	Open( const wchar_t * szName, const wchar_t *pFlags, const wchar_t * szPathID ) = 0;
	virtual void	Close( ) = 0;
	virtual int		Read( void * pBuf, uint uSize ) = 0;
	virtual int		Write( void * pBuf, uint uSize ) = 0;
	virtual void	Seek( int nPos, int nFrom ) = 0;

	virtual char*	ReadLine( char * pBuf, uint uSize ) = 0;
	virtual uint	GetLength( ) = 0;

	//virtual int		ScanF( const char * format, ... ) = 0;
};
