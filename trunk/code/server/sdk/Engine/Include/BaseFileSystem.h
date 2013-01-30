#ifdef WIN32
#pragma once
#endif

#include "../stdafx.h"
#include "EngineDefine.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#ifdef WIN32
#include <direct.h>
#include <windows.h>
#undef GetCurrentDirectory
#include <malloc.h>
#else
#include <stdlib.h>
#include "posix_support.h"
#endif

#include <time.h>
#include "BufferScheduler.h"
#include "utlMD5.h"
#include "filesystem.h"
#include "utlvector.h"

#include <stdarg.h>

//#include "utlrbtree.h"
#include "utlmap.h"
#include "utlsymbol.h"
#include "SLock.h"

#ifdef WIN32
#define CORRECT_PATH_SEPARATOR '\\'
#define INCORRECT_PATH_SEPARATOR '/'
#else
#define CORRECT_PATH_SEPARATOR '/'
#define INCORRECT_PATH_SEPARATOR '\\'
#endif

#ifdef	WIN32
#define PATHSEPARATOR(c) ((c) == '\\' || (c) == '/')
#else
#define PATHSEPARATOR(c) ((c) == '/')
#endif	//WIN32


#pragma pack(push,1)
struct ZIP_EndOfCentralDirRecord
{
	unsigned int signature; // 4 bytes (0x06054b50)
	unsigned short numberOfThisDisk;  // 2 bytes
	unsigned short numberOfTheDiskWithStartOfCentralDirectory; // 2 bytes
	unsigned short nCentralDirectoryEntries_ThisDisk;	// 2 bytes
	unsigned short nCentralDirectoryEntries_Total;	// 2 bytes
	unsigned int centralDirectorySize; // 4 bytes
	unsigned int startOfCentralDirOffset; // 4 bytes
	unsigned short commentLength; // 2 bytes
	// zip file comment follows
};

struct ZIP_FileHeader
{
	unsigned int signature; //  4 bytes (0x02014b50) 
	unsigned short versionMadeBy; // version made by 2 bytes 
	unsigned short versionNeededToExtract; // version needed to extract 2 bytes 
	unsigned short flags; // general purpose bit flag 2 bytes 
	unsigned short compressionMethod; // compression method 2 bytes 
	unsigned short lastModifiedTime; // last mod file time 2 bytes 
	unsigned short lastModifiedDate; // last mod file date 2 bytes 
	unsigned int crc32; // crc-32 4 bytes 
	unsigned int compressedSize; // compressed size 4 bytes 
	unsigned int uncompressedSize; // uncompressed size 4 bytes 
	unsigned short fileNameLength; // file name length 2 bytes 
	unsigned short extraFieldLength; // extra field length 2 bytes 
	unsigned short fileCommentLength; // file comment length 2 bytes 
	unsigned short diskNumberStart; // disk number start 2 bytes 
	unsigned short internalFileAttribs; // internal file attributes 2 bytes 
	unsigned int externalFileAttribs; // external file attributes 4 bytes 
	unsigned int relativeOffsetOfLocalHeader; // relative offset of local header 4 bytes 
	// file name (variable size) 
	// extra field (variable size) 
	// file comment (variable size) 
};

struct ZIP_LocalFileHeader
{
	unsigned int signature; //local file header signature 4 bytes (0x04034b50) 
	unsigned short versionNeededToExtract; // version needed to extract 2 bytes 
	unsigned short flags; // general purpose bit flag 2 bytes 
	unsigned short compressionMethod; // compression method 2 bytes 
	unsigned short lastModifiedTime; // last mod file time 2 bytes 
	unsigned short lastModifiedDate; // last mod file date 2 bytes 
	unsigned int crc32; // crc-32 4 bytes 
	unsigned int compressedSize; // compressed size 4 bytes 
	unsigned int uncompressedSize; // uncompressed size 4 bytes 
	unsigned short fileNameLength; // file name length 2 bytes 
	unsigned short extraFieldLength; // extra field length 2 bytes 
};
#pragma pack(pop)


class CBaseFileSystem : public IFileSystem
{
public:
	CBaseFileSystem();
	~CBaseFileSystem();

	virtual bool				InitFileCache( const char* szName, uint totalSize, uint oneSize );
	virtual const char*			FileCacheReport();
	virtual BOOL				Init();
	virtual void				Shutdown();

	void						ParsePathID( const char* &pFilename, const char* &pPathID, char tempPathID[MAX_PATH] );

	// file handling
	virtual FileHandle_t		Open( const char *pFileName, const char *pOptions, const char *pathID = 0  );
	virtual FileHandle_t		OpenReadorWrite( const char *pFileName, const char *pOptions, const char *pathID = 0  );
	virtual FileHandle_t        OpenAbsolutePath( const char *pFileName, const char *pOptions, const char *pathID=0 );
	virtual void				Close( FileHandle_t );
	virtual void				Seek( FileHandle_t file, int pos, FileSystemSeek_t method );
	virtual unsigned int		Tell( FileHandle_t file );
	virtual unsigned int		Size( FileHandle_t file );
	virtual unsigned int		Size( const char *pFileName, const char *pPathID );

	virtual bool				IsOk( FileHandle_t file );
	virtual void				Flush( FileHandle_t file );
	virtual bool				Precache( const char *pFileName, const char *pPathID);
	virtual bool				EndOfFile( FileHandle_t file );
 
	virtual int					SyncRead( void *pOutput, int size, FileHandle_t file );
	virtual int					Read( void *pOutput, int size,int nPos, FileHandle_t file );
	virtual int					ReadFileCache( void *pOutput, int size,int nPos, FileHandle_t file );
	virtual int					Write( void const* pInput, int size, FileHandle_t file );
	virtual char				*ReadLine( char *pOutput, int maxChars, FileHandle_t file );
	virtual int					FPrintf( FileHandle_t file, char *pFormat, ... );

	// Gets the current working directory
	virtual bool				GetCurrentDirectory( char* pDirectory, int maxlen );

	// this isn't implementable on STEAM as is.
	virtual void				CreateDirHierarchy( const char *path, const char *pathID );

	// returns true if the file is a directory
	virtual bool				IsDirectory( const char *pFileName, const char *pathID );

	// path info
	virtual const char			*GetLocalPath( const char *pFileName, char *pLocalPath );
	virtual bool				FullPathToRelativePath( const char *pFullpath, char *pRelative );
	virtual int					GetLocalPathLen( const char *pFileName );

	// removes a file from disk
	virtual void				RemoveFile( char const* pRelativePath, const char *pathID );

	// Remove all search paths (including write path?)
	virtual void				RemoveAllSearchPaths( void );
	// STUFF FROM IFileSystem
	// Add paths in priority order (mod dir, game dir, ....)
	// Can also add pak files (errr, NOT YET!)
	virtual bool				AddSearchPath( const char *pPath, const char *pathID, SearchPathAdd_t addType );
	virtual bool				RemoveSearchPath( const char *pPath, const char *pathID );
	virtual const char *			GetSearchPath( const char *pathID );

	virtual	void				SetFileFindOrder(bool fileOrder);

	virtual bool				FileExists( const char *pFileName, const char *pPathID = NULL );  //太长了，没时间看，下面重写了一个  edit by wmy
	virtual bool                IsUIFileExists( const char* pFileName);
	virtual long				GetFileTime( const char *pFileName, const char *pPathID = NULL );
	virtual bool				IsFileWritable( char const *pFileName, const char *pPathID = NULL );
	virtual void				FileTimeToString( char *pString, int maxChars, long fileTime );
	
	virtual const char			*FindFirst( const char *pWildCard, FileFindHandle_t *pHandle );
	virtual const char			*FindNext( FileFindHandle_t handle );
	virtual bool				FindIsDirectory( FileFindHandle_t handle );
	virtual void				FindClose( FileFindHandle_t handle );

	virtual void				PrintOpenedFiles( void );
	virtual void				SetWarningFunc( void (*pfnWarning)( const char *fmt, ... ) );
	virtual void				SetWarningLevel( FileWarningLevel_t level );
	virtual void				RenameFile( char const *pOldPath, char const *pNewPath, const char *pathID );

	virtual void				GetLocalCopy( const char *pFileName );

	// Returns the file system statistics retreived by the implementation.  Returns NULL if not supported.
	virtual const FileSystemStatistics *GetFilesystemStatistics();
	
	class CFileHandle
	{
	public:
		CFileHandle( void )
		{
			m_pFile = NULL;
			m_nStartOffset = 0;
			m_nLength = 0;
			m_nFileTime = 0;
			m_bPack = false;
			m_bEncry = false;
			m_pFileLock = NULL;
			m_nReadOffset = 0;
			m_md5[0]  = 0;
		}

		FILE			*m_pFile;
		bool			m_bPack;
		bool			m_bEncry;
		int				m_nStartOffset;
		int				m_nLength;
		long			m_nFileTime;
		SCritSect*		m_pFileLock;
		int				m_nReadOffset;
		char            m_md5[MD5LEN];
	};

protected:
	// IMPLEMENTATION DETAILS FOR CBaseFileSystem 
	struct FindData_t
	{
		WIN32_FIND_DATA findData;
		int currentSearchPathID;
		CUtlVector<char> wildCardString;
		HANDLE findHandle;
	};
	
	enum
	{
		MAX_FILES_IN_PACK = 32768,
	};

	class CPackFileEntry
	{
	public:
		CUtlSymbol			m_Name;
		int					m_nPosition;
		int					m_nLength;
	};

	class CSearchPath 
	{

	public:
							CSearchPath( void );
							~CSearchPath( void );

		static bool PackFileLessFunc( CPackFileEntry const& src1, CPackFileEntry const& src2 );
		const char* GetPathString() const;
		const char* GetPathIDString() const;

		CUtlSymbol			m_Path;
		CUtlSymbol			m_PathID;
		
		bool				m_bIsEncrypt;
		bool				m_bIsMapPath;
		bool				m_bIsPackFile;
		long				m_lPackFileTime;
		CFileHandle			*m_hPackFile;
		int					m_nNumPackFiles;

//		CUtlRBTree< CPackFileEntry, int > m_PackFiles;
		CUtlMap< CPackFileEntry, CPackFileEntry, int > m_PackFiles;

		static CBaseFileSystem*	m_fs;
	};
	
	friend class CSearchPath;

	// Global list of pack file handles
	CUtlVector< FILE * > m_PackFileHandles;
	CUtlVector< FindData_t>  m_FindData;
	CUtlVector< CSearchPath > m_SearchPaths;
	FILE *m_pLogFile;
	bool m_bOutputDebugString;

	// Statistics:
	FileSystemStatistics m_Stats;

protected:
	//----------------------------------------------------------------------------
	// Purpose: Functions implementing basic file system behavior.
	//----------------------------------------------------------------------------
	virtual FILE *FS_fopen( const char *filename, const char *options ) = 0;
	virtual void FS_fclose( FILE *fp ) = 0;
	virtual void FS_fseek( FILE *fp, long pos, int seekType ) = 0;
	virtual long FS_ftell( FILE *fp ) = 0;
	virtual int FS_feof( FILE *fp ) = 0;
	virtual size_t FS_fread( void *dest, size_t count, size_t size, FILE *fp ) = 0;
	virtual size_t FS_fwrite( const void *src, size_t count, size_t size, FILE *fp ) = 0;
	virtual size_t FS_vfprintf( FILE *fp, const char *fmt, va_list list ) = 0;
	virtual int FS_ferror( FILE *fp ) = 0;
	virtual int FS_fflush( FILE *fp ) = 0;
	virtual char *FS_fgets( char *dest, int destSize, FILE *fp ) = 0;
	virtual int FS_stat( const char *path, struct _stat *buf ) = 0;
	virtual HANDLE FS_FindFirstFile(char *findname, WIN32_FIND_DATA *dat) = 0;
	virtual bool FS_FindNextFile(HANDLE handle, WIN32_FIND_DATA *dat) = 0;
	virtual bool FS_FindClose(HANDLE handle) = 0;

protected:
	//-----------------------------------------------------------------------------
	// Purpose: For tracking unclosed files
	// NOTE:  The symbol table could take up memory that we don't want to eat here.
	// In that case, we shouldn't store them in a table, or we should store them as locally allocates stings
	//  so we can control the size
	//-----------------------------------------------------------------------------
	class COpenedFile
	{
	public:
					COpenedFile( void );
					~COpenedFile( void );

					COpenedFile( const COpenedFile& src );

		bool operator==( const COpenedFile& src ) const;

		void		SetName( char const *name );
		char const	*GetName( void );

		FILE		*m_pFile;
		char		*m_pName;
	};

	//CUtlRBTree< COpenedFile, int > m_OpenedFiles;
	CUtlVector <COpenedFile> m_OpenedFiles;

	static bool OpenedFileLessFunc( COpenedFile const& src1, COpenedFile const& src2 );

	FileWarningLevel_t			m_fwLevel;
	void						(*m_pfnWarning)( const char *fmt, ... );

	FILE						*Trace_FOpen( const char *filename, const char *options );
	void						Trace_FClose( FILE *fp );
	void						Trace_FRead( int size, FILE* file );
	void						Trace_FWrite( int size, FILE* file );

	void						Trace_DumpUnclosedFiles( void );

	void						Warning( FileWarningLevel_t level, const char *fmt, ... );

	bool						FileInSearchPaths( const char *pSearchWildcard, const char *pFileName, 
								int minSearchPathID, int maxSearchPathID );
	bool						FindNextFileHelper( FindData_t *pFindData );

	int							AddPackFiles( const char *pPath, SearchPathAdd_t addType );
	bool						PreparePackFile( CSearchPath& packfile, int offsetofpackinmetafile, int filelen );
	void						PrintSearchPaths( void );

	FileHandle_t				FindFile( const CSearchPath *path, const char *pFileName, const char *pOptions );
	int							FastFindFile( const CSearchPath *path, const char *pFileName );

	const char					*GetWritePath(const char *pathID);

	// Computes a full write path
	void						ComputeFullWritePath( char* pDest, const char *pWritePathID, char const *pRelativePath );

	// Opens a file for read or write
	FileHandle_t OpenForRead( const char *pFileName, const char *pOptions, const char *pathID );
	FileHandle_t OpenForWrite( const char *pFileName, const char *pOptions, const char *pathID );
	CSearchPath *FindWritePath( const char *pathID );

	CUtlVector <CPackFileEntry*> g_vec;

	CBufferScheduler  bufferScheduler;
	CUtlMD5 md5;
};

//-----------------------------------------------------------------------------
// Singleton interface
//-----------------------------------------------------------------------------
ENGINE_GLOBAL CBaseFileSystem            &FileSystem();

ENGINE_GLOBAL BOOL CheckDatFile( const char * szDatFile );
ENGINE_GLOBAL BOOL RepairDatFile( const char * szDatFile );
