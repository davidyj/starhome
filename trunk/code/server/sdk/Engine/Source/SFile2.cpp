#include "../stdafx.h"
#include "SFile2.h"
#include "BaseFileSystem.h"
#include "strtools.h"

SFile::SFile( )
{
	m_type = SFILE_PLAIN;
	m_fileptr = NULL;
	m_size = 0;
	m_asyncCount = 0;
	m_zbuffer = NULL;
	m_curOffset = 0;
	m_filename = NULL;
	m_actualname = NULL;
}

SFile::~SFile( )
{

}

static int FindFile( const char * filename, 
			 char * realname,
			 int len, 
			 unsigned long flags, 
			 SFILE_TYPE * type )
{

	return 0;

}


bool SFile::OpenEx(  /*SArchive * archive,*/
							const char * filename, 
							unsigned long flags, 
							SFile * * file )
{

	if ( !file )
		return false;

	FileHandle_t fileHandle = FileSystem().Open( filename, "rb" );
	if ( fileHandle == FILESYSTEM_INVALID_HANDLE )
	{
		return false;
	}

	*file = new SFile;
	(*file)->m_fileptr = fileHandle;
	(*file)->m_actualname = SStrDupA(filename);
	
	return true;
}

unsigned long SFile::Read(void * fileptr, 
						  void * buffer, 
						  unsigned long bytestoread,
						  int nPos,
						  unsigned long * bytesread )
{

	if ( !fileptr || !buffer )
		return 0;
	int nReadCount = FileSystem( ).Read( buffer, bytestoread,nPos, fileptr );
	if ( bytesread )
		*bytesread = nReadCount;
	return nReadCount;
}

unsigned long SFile::ReadFileCache(void * fileptr, 
						  void * buffer, 
						  unsigned long bytestoread,
						  int nPos,
						  unsigned long * bytesread )
{

	if ( !fileptr || !buffer )
		return 0;
	int nReadCount = FileSystem( ).ReadFileCache( buffer, bytestoread, nPos, fileptr );
	if ( bytesread )
		*bytesread = nReadCount;
	return nReadCount;
}


void SFile::Close( SFile * file )
{
	if ( !file )
		return;
	FileSystem( ).Close( file->m_fileptr );
	SAFE_DELETE( file );
}
