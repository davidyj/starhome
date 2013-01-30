#pragma once
#include "EngineDefine.h"
enum SFILE_TYPE
{
	SFILE_PLAIN = 0,
	SFILE_COMPRESSED,
	SFILE_PAQ,
	SFILE_OLD_SFILE,
	SFILE_ZIP_FILE,
	
};

//sizeof(SFile)	0x00000060	unsigned int
class ENGINE_CLASS SFile
{
public:
		SFile( );
		~SFile( );

		static bool OpenEx(  /*SArchive * archive,*/
							const char * filename, 
							unsigned long flags, 
							SFile * * file );
	
		static unsigned long Read(void * fileptr, 
							void * buffer, 
							unsigned long bytestoread,
							int nPos,
							unsigned long * bytesread );
		static unsigned long ReadFileCache(void * fileptr, 
							void * buffer, 
							unsigned long bytestoread,
							int nPos,
							unsigned long * bytesread );
		static void Close( SFile * file );

public:
		SFILE_TYPE m_type;
		void * m_fileptr;
		//SArchive * m_archive;
		char * m_filename;
		char * m_actualname;
		unsigned int m_size;
		unsigned char *m_zbuffer;
		//z_stream_s * m_zstream;
		unsigned int m_curOffset;
		//SCritSect m_lock;
		//void * m_hsfile;
		//ZipFileFCB *m_zipFile;
		//MD5 m_md5;
		//int m_haveMD5;
		//int m_closeAfterLoad;
		UINT m_asyncCount;
			
};
