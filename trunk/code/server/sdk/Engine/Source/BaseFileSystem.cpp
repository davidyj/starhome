//========= Copyright ?1996-2001, Valve LLC, All rights reserved. ============
//
// Purpose:
//
// $NoKeywords: $
//     by fuqiang; 2009.1.14  支持先读散文件，再读pak文件
//    findfile 不再�?seek,seek �?read里面实现，加�?file lock
//    FIXME/by  2009.1.14 如果 fread以前执行 seek,再read, 会引�?readoffset冲突
//    为了支持多线程加载openread pack文件, read前要seek,这样就不好支持主动seek再read
//=============================================================================

#include "../stdafx.h"
#include "BaseFileSystem.h"
#include "BufferScheduler.h"
#include "characterset.h"
#include "dbg.h"
//#include "vprof.h"
#include "ICommandLine.h"
#include <stdlib.h>
#include "strtools.h"
#include <string>

// memdbgon must be the last include file in a .cpp file!!!
#include "memdbgon.h"

#ifndef WIN32
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#define _alloca alloca
#define _vsnprintf vsnprintf
#endif

#define BSPOUTPUT	0	// bsp output flag -- determines type of fs_log output to generate


CBaseFileSystem* CBaseFileSystem::CSearchPath::m_fs = 0;


int		gLastIt = 0;
bool	gWholeFirst = true;

static void FixSlashes( char *str );
static void FixSlashes1( char *str );
static void FixPath( char *str );
static void StripFilename (char *path);
static char s_pScratchFileName[ MAX_PATH ];



// Case-insensitive symbol table for path IDs.
//CUtlSymbolTable g_PathIDTable( 0, 32, true );

//-----------------------------------------------------------------------------
// Singleton interface
//-----------------------------------------------------------------------------
CUtlSymbolTable & PathIDTable( )
{
	static CUtlSymbolTable s_PathIDTable( 0, 32, true );
	return s_PathIDTable;
}


//-----------------------------------------------------------------------------
// constructor
//-----------------------------------------------------------------------------

CBaseFileSystem::CBaseFileSystem()
	//: m_OpenedFiles( 0, 32, OpenedFileLessFunc )
{
	// Clear out statistics
	memset(&m_Stats,0,sizeof(m_Stats));

	CSearchPath::m_fs = this;

	m_fwLevel		= FILESYSTEM_WARNING_REPORTUNCLOSED;
	m_pfnWarning	= NULL;
	m_pLogFile			= NULL;
	m_bOutputDebugString = false;
	//CUtlSymbol::DisableStaticSymbolTable();//by
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CBaseFileSystem::~CBaseFileSystem()
{
}

bool CBaseFileSystem::InitFileCache( const char* szName, uint totalSize, uint oneSize )
{
	return bufferScheduler.Init( szName, totalSize, oneSize );
}

const char* CBaseFileSystem::FileCacheReport()
{
	return bufferScheduler.report();
}

BOOL CBaseFileSystem::Init()
{
	if ( getenv( "fs_debug" ) )
	{
		m_bOutputDebugString = true;
	}

	const char *logFileName = getenv( "fs_log" );
	if( logFileName )
	{
		m_pLogFile = fopen( logFileName, "w" ); // STEAM OK
		if ( !m_pLogFile )
			return FALSE;
	}

	// Add the executable directory as a default search path for the executable.
	if ( CommandLine( ).ParmCount() != 0 )
	{
		const char *pExeName = CommandLine( ).GetParm( 0 );
		if ( pExeName )
		{
			char pExeDir[ MAX_PATH ];
			strcpy( pExeDir, pExeName );
			char *pSlash;
			char *pSlash2;
			pSlash = strrchr( pExeDir,'\\' );
			pSlash2 = strrchr( pExeDir,'/' );
			if ( pSlash2 > pSlash )
			{
				pSlash = pSlash2;
			}
			if (pSlash)
			{
				*pSlash = 0;
			}

			AddSearchPath( pExeDir, "EXECUTABLE_PATH", PATH_ADD_TO_TAIL );
		}
	}

	return TRUE;
}

void CBaseFileSystem::Shutdown()
{
	if( m_pLogFile )
	{
		fclose( m_pLogFile ); // STEAM OK
		m_pLogFile = NULL;
	}

	RemoveAllSearchPaths();
	Trace_DumpUnclosedFiles();

	m_FindData.Purge( );
	m_OpenedFiles.Purge( );
}


//-----------------------------------------------------------------------------
// Computes a full write path
//-----------------------------------------------------------------------------
inline void CBaseFileSystem::ComputeFullWritePath( char* pDest, const char *pRelativePath, const char *pWritePathID )
{
	strcpy( pDest, GetWritePath(pWritePathID) );
	strcat( pDest,"\\");
	strcat( pDest, pRelativePath );
	FixSlashes( pDest );
}


//-----------------------------------------------------------------------------
// Purpose:
// Input  : src1 -
//			src2 -
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseFileSystem::OpenedFileLessFunc( COpenedFile const& src1, COpenedFile const& src2 )
{
	return src1.m_pFile < src2.m_pFile;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *filename -
//			*options -
// Output : FILE
//-----------------------------------------------------------------------------
FILE *CBaseFileSystem::Trace_FOpen( const char *filename, const char *options )
{
	FILE *fp = FS_fopen( filename, options );
	if ( fp )
	{
		/*		COpenedFile		file;

				file.SetName( filename );
				file.m_pFile	= fp;

		//m_OpenedFiles.Insert( file );
		m_OpenedFiles.AddToTail( file );

		if ( m_fwLevel >= FILESYSTEM_WARNING_REPORTALLACCESSES )
		{
		//			Warning( FILESYSTEM_WARNING_REPORTALLACCESSES, "---FS:  open %s %p %i\n", filename, fp, m_OpenedFiles.Count() );
		}*/
	}

	return fp;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *fp -
//-----------------------------------------------------------------------------
void CBaseFileSystem::Trace_FClose( FILE *fp )
{
	if ( fp )
	{
		/*		COpenedFile file;
				file.m_pFile = fp;

				int result = m_OpenedFiles.Find( file );
				if ( result != -1 )//m_OpenedFiles.InvalidIdx() )
				{
				COpenedFile found = m_OpenedFiles[ result ];
				if ( m_fwLevel >= FILESYSTEM_WARNING_REPORTALLACCESSES )
				{
				Warning( FILESYSTEM_WARNING_REPORTALLACCESSES, "---FS:  close %s %p %i\n", found.GetName(), fp, m_OpenedFiles.Count() );
				}
				m_OpenedFiles.Remove( result );
				}
				else
				{
				Assert( 0 );

				if ( m_fwLevel >= FILESYSTEM_WARNING_REPORTALLACCESSES )
				{
				Warning( FILESYSTEM_WARNING_REPORTALLACCESSES, "Tried to close unknown file pointer %p\n", fp );
				}
				}
				*/
		FS_fclose( fp );
	}
}


void CBaseFileSystem::Trace_FRead( int size, FILE* fp )
{
	if ( !fp || m_fwLevel < FILESYSTEM_WARNING_REPORTALLACCESSES_READ )
		return;
	/*
	   COpenedFile file;
	   file.m_pFile = fp;

	   int result = m_OpenedFiles.Find( file );

	   if( result != -1 )
	   {
	   COpenedFile found = m_OpenedFiles[ result ];

	   Warning( FILESYSTEM_WARNING_REPORTALLACCESSES_READ, "---FS:  read %s %i %p\n", found.GetName(), size, fp  );
	   }
	   else
	   {
	   Warning( FILESYSTEM_WARNING_REPORTALLACCESSES_READ, "Tried to read %i bytes from unknown file pointer %p\n", size, fp );

	   }*/
}

void CBaseFileSystem::Trace_FWrite( int size, FILE* fp )
{
	if ( !fp || m_fwLevel < FILESYSTEM_WARNING_REPORTALLACCESSES_READWRITE )
		return;
	/*
	   COpenedFile file;
	   file.m_pFile = fp;

	   int result = m_OpenedFiles.Find( file );

	   if( result != -1 )
	   {
	   COpenedFile found = m_OpenedFiles[ result ];

	   Warning( FILESYSTEM_WARNING_REPORTALLACCESSES_READWRITE, "---FS:  write %s %i %p\n", found.GetName(), size, fp  );
	   }
	   else
	   {
	   Warning( FILESYSTEM_WARNING_REPORTALLACCESSES_READWRITE, "Tried to write %i bytes from unknown file pointer %p\n", size, fp );
	   }*/
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CBaseFileSystem::Trace_DumpUnclosedFiles( void )
{
	/*	for ( int i = 0 ; i < m_OpenedFiles.Count(); i++ )
		{
		COpenedFile *found = &m_OpenedFiles[ i ];

		if ( m_fwLevel >= FILESYSTEM_WARNING_REPORTUNCLOSED )
		{
		Warning( FILESYSTEM_WARNING_REPORTUNCLOSED, "File %s was never closed\n", found->GetName() );
		}
		}*/
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CBaseFileSystem::PrintOpenedFiles( void )
{
	Trace_DumpUnclosedFiles();
}

//-----------------------------------------------------------------------------
// Search path
//-----------------------------------------------------------------------------

typedef struct
{
	CUtlSymbol			m_Name;
	int					filepos;
	int					filelen;
} TmpFileInfo_t;

//-----------------------------------------------------------------------------
// Purpose:
// Input  : packfile -
//			offsetofpackinmetafile - if the .pak is embedded in another file, then all of it's offsets
//				need this offset added to them
//-----------------------------------------------------------------------------



bool CBaseFileSystem::PreparePackFile( CSearchPath& packfile, int offsetofpackinmetafile, int fileLen )
{
	int						i;
	TmpFileInfo_t              *newfiles;

	Assert( packfile.m_bIsPackFile );
	Assert( packfile.m_hPackFile );

	Seek( (FileHandle_t)packfile.m_hPackFile, offsetofpackinmetafile, FILESYSTEM_SEEK_HEAD);

	int offset;
	ZIP_EndOfCentralDirRecord rec;
	rec.startOfCentralDirOffset = 0;
	rec.nCentralDirectoryEntries_Total = 0;

	//bool foundEndOfCentralDirRecord = false;
	offset = fileLen - sizeof( ZIP_EndOfCentralDirRecord );
	//	for( offset = fileLen - sizeof( ZIP_EndOfCentralDirRecord ); offset >= 0; offset-- )
	{
		Seek( (FileHandle_t)packfile.m_hPackFile, offsetofpackinmetafile + offset, FILESYSTEM_SEEK_HEAD);
		SyncRead( (void *)&rec, sizeof(rec), (FileHandle_t)packfile.m_hPackFile );
		if( rec.signature == 0x9c4b4b5a )
		{
			//foundEndOfCentralDirRecord = true;
			packfile.m_bIsPackFile = true;
			packfile.m_bIsEncrypt = true;
			//			break;
		}
		else if (rec.signature == 0x06054b50)
		{
			packfile.m_bIsPackFile = true;
			packfile.m_bIsEncrypt = true;
		}

	}
	//Assert( foundEndOfCentralDirRecord );
	//if( !foundEndOfCentralDirRecord )
	//{
	//	return false;
	//}

	Seek( (FileHandle_t)packfile.m_hPackFile, offsetofpackinmetafile + rec.startOfCentralDirOffset, FILESYSTEM_SEEK_HEAD );

	// Make sure there are some files to parse
	int numpackfiles = rec.nCentralDirectoryEntries_Total;
	if (  numpackfiles <= 0 )
	{
		// No files, sigh...
		return false;
	}

	newfiles = new TmpFileInfo_t[ numpackfiles ];
	Assert( newfiles );
	if ( !newfiles )
	{
		Warning( FILESYSTEM_WARNING, "%s out of memory allocating directoryf for %i files", packfile.GetPathString(), numpackfiles );
		return false;
	}

	for( i = 0; i < rec.nCentralDirectoryEntries_Total; i++ )
	{
		ZIP_FileHeader fileHeader;
		SyncRead( (void *)&fileHeader, sizeof( ZIP_FileHeader ), (FileHandle_t)packfile.m_hPackFile );
		//-edit by youxl 2011.8.8
		//Assert( fileHeader.signature == 0x12118b5a );
		//-end
		Assert( fileHeader.compressionMethod == 0 );

		char tmpString[1024];
		SyncRead( (void *)tmpString, fileHeader.fileNameLength, (FileHandle_t)packfile.m_hPackFile );
		tmpString[fileHeader.fileNameLength] = '\0';
		strlwr( tmpString );
		FixSlashes1( tmpString );
		newfiles[i].m_Name = PathIDTable( ).AddString( tmpString );
		newfiles[i].filepos = fileHeader.relativeOffsetOfLocalHeader +  sizeof( ZIP_LocalFileHeader ) + fileHeader.fileNameLength;
		newfiles[i].filelen = fileHeader.compressedSize;
		if(  fileHeader.extraFieldLength + fileHeader.fileCommentLength != 0 )
			Seek( (FileHandle_t)packfile.m_hPackFile, fileHeader.extraFieldLength + fileHeader.fileCommentLength, FILESYSTEM_SEEK_CURRENT);
	}
//////////////////////////////////////////////////////////////////////////
// 	for( i = 0; i < rec.nCentralDirectoryEntries_Total; i++ )
// 	{
// 		int start = Plat_MMSTime();
//
// 		Seek( (FileHandle_t)packfile.m_hPackFile, offsetofpackinmetafile + newfiles[i].filepos, FILESYSTEM_SEEK_HEAD );
// 		ZIP_LocalFileHeader localFileHeader;
// 		SyncRead( (void *)&localFileHeader, sizeof( ZIP_LocalFileHeader ), (FileHandle_t)packfile.m_hPackFile );
// 		Assert( localFileHeader.signature == 0x04034b50 );
//
// 		Seek( (FileHandle_t)packfile.m_hPackFile, localFileHeader.fileNameLength + localFileHeader.extraFieldLength, FILESYSTEM_SEEK_CURRENT);
// 		int end = Plat_MMSTime();
// 		Log("timer %d",end - start );
// 		start = Plat_MMSTime( );
// 		newfiles[i].filepos = Tell( ( FileHandle_t )packfile.m_hPackFile );
// 		end = Plat_MMSTime( );
// 		Log("timer Tell %d",end - start);
// 	}
//////////////////////////////////////////////////////////////////////////
	// Insert into rb tree
	for ( i=0 ; i<numpackfiles ; i++ )
	{
		CPackFileEntry	*lookup = new CPackFileEntry ;
		lookup->m_Name		= newfiles[ i ].m_Name;
		lookup->m_nPosition	= newfiles[i].filepos /* + offsetofpackinmetafile */;
		lookup->m_nLength	= newfiles[i].filelen;

//		packfile.m_PackFiles.Insert( lookup );
		while( gLastIt <= lookup->m_Name )
		{
			g_vec.AddToTail( NULL );
			gLastIt++;
		}
		g_vec[ lookup->m_Name ] = lookup;
		//packfile.m_PackFiles.InsertOrReplace( lookup, lookup );
	}

	packfile.m_nNumPackFiles = numpackfiles;

	delete[] newfiles;

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: Search pPath for pak?.pak files and add to search path if found
// Input  : *pPath -
//-----------------------------------------------------------------------------
int	CBaseFileSystem::AddPackFiles( const char *pPath, SearchPathAdd_t addType )
{
	char		path[512];
	char		pakfile[ 512 ];
	strcpy( pakfile, pPath );

	FixSlashes( pakfile );

	struct	_stat buf;
	// Should never happen
	if( FS_stat( pakfile, &buf ) == -1 )
	{
		return -1;
	}

	int nIndex;

	if ( addType == PATH_ADD_TO_TAIL )
	{
		nIndex = m_SearchPaths.AddToTail();
	}
	else
	{
		nIndex = m_SearchPaths.AddToHead( );
	}

	CSearchPath *sp = &m_SearchPaths[ nIndex ];

	char szPath[512];
	MakeNakedNameIndex( pPath, path, 512, 0 );
	GetFileNameNoExt( path, szPath, 512 );

	sp->m_Path					= PathIDTable( ).AddString( szPath );
	sp->m_bIsPackFile			= true;
	sp->m_lPackFileTime			= GetFileTime( pakfile );
	sp->m_hPackFile				= new CFileHandle;
	sp->m_hPackFile->m_pFile	= Trace_FOpen( pakfile, "rb" );
	sp->m_hPackFile->m_pFileLock = new SCritSect;

	FS_fseek( ( FILE * )sp->m_hPackFile->m_pFile, 0, FILESYSTEM_SEEK_TAIL );
	int len = FS_ftell( ( FILE * )sp->m_hPackFile->m_pFile );
	FS_fseek( ( FILE * )sp->m_hPackFile->m_pFile, 0, FILESYSTEM_SEEK_HEAD );

	if ( PreparePackFile( *sp, 0, len ) )
	{
		m_PackFileHandles.AddToTail( sp->m_hPackFile->m_pFile );

		return nIndex;
	}
	else
	{
		// Failed for some reason, ignore it
		Trace_FClose( sp->m_hPackFile->m_pFile );
		delete sp->m_hPackFile;
		sp->m_hPackFile = NULL;
		m_SearchPaths.Remove( nIndex );
	}

	return -1;
}

void CBaseFileSystem::PrintSearchPaths( void )
{
#if 0
	int i;
	//Warning( FILESYSTEM_WARNING, "---------------\n" );
	//Warning( FILESYSTEM_WARNING, "Paths:\n" );
	for( i = 0; i < m_SearchPaths.Count(); i++ )
	{
		CSearchPath *pSearchPath = &m_SearchPaths[i];
		//Warning( FILESYSTEM_WARNING, "\"%s\" \"%s\"\n", ( const char * )pSearchPath->GetPathString(), ( const char * )pSearchPath->GetPathIDString() );
	}
#endif
}


//-----------------------------------------------------------------------------
// Purpose: This is where search paths are created.  map files are created at head of list (they occur after
//  file system paths have already been set ) so they get highest priority.  Otherwise, we add the disk (non-packfile)
//  path and then the paks if they exist for the path
// Input  : *pPath -
//-----------------------------------------------------------------------------
bool CBaseFileSystem::AddSearchPath( const char *pPath, const char *pathID, SearchPathAdd_t addType )
{
	// Clean up the name
	BOOL bPak = FALSE;
	char *newPath;
	char pakfile[ 512 ];
	int nPathLen = strlen( pPath );
	// +2 for '\0' and potential slash added at end.
	newPath = ( char * )_alloca( nPathLen + 2 );
	if ( pPath[0] == 0 )
	{
		newPath[0] = newPath[1] = 0;
	}
	else
	{
		strcpy( newPath, pPath );
#ifdef WIN32
		strlwr( newPath );
#endif

		sprintf( pakfile, "%s.dat", newPath );
		struct	_stat buf;
		//if( FS_stat( pakfile, &buf ) == -1 )
		//	FixPath( newPath );
		//else
		//	bPak = TRUE;
		if( FS_stat( pakfile, &buf ) != -1 )
			bPak = TRUE;
	}

	// Make sure that it doesn't already exist

	CUtlSymbol pathSym, pathIDSym;

	pathSym = PathIDTable( ).AddString( newPath );
	pathIDSym = PathIDTable( ).AddString( pathID );
	//if( bPak )
	//{
	//	char szPath[512];
	//	MakeNakedNameIndex( pakfile, newPath, nPathLen, 0 );
	//	GetFileNameNoExt( newPath, szPath, 512 );
	//	pathSym = PathIDTable( ).AddString( szPath );
	//	pathIDSym = PathIDTable( ).AddString( pathID );
	//}
	//else
	//{
	//	pathSym = PathIDTable( ).AddString( newPath );
	//	pathIDSym = PathIDTable( ).AddString( pathID );
	//}
	for( int i = 0; i < m_SearchPaths.Count(); i++ )
	{
		CSearchPath *pSearchPath = &m_SearchPaths[i];
		if( pSearchPath->m_Path == pathSym && pSearchPath->m_PathID == pathIDSym )
		{
			return true;
		}
	}

	int nIndex;
	// Pack files
	if( bPak )
	{
		// Add pack files for this path next
		nIndex = AddPackFiles( pakfile, addType );
		if( nIndex == -1 )
			return false;
	}
	else
	{
		// Add to tail of list
		if ( addType == PATH_ADD_TO_TAIL )
			nIndex = m_SearchPaths.AddToTail();
		else
			nIndex = m_SearchPaths.AddToHead();
	}

	// Grab last entry and set the path
	CSearchPath *sp = &m_SearchPaths[ nIndex ];

	sp->m_Path = pathSym;
	sp->m_PathID = pathIDSym;

#ifdef _DEBUG
	PrintSearchPaths();
#endif

	return true;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *pPath -
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseFileSystem::RemoveSearchPath( const char *pPath, const char *pathID )
{
	char *newPath = NULL;

	if ( pPath )
	{
		// +2 for '\0' and potential slash added at end.
		newPath = ( char * )_alloca( strlen( pPath ) + 2 );
		strcpy( newPath, pPath );
#ifdef WIN32
		strlwr( newPath );
#endif
		FixPath( newPath );
	}

	CUtlSymbol lookup = PathIDTable( ).AddString( newPath );
	CUtlSymbol id = PathIDTable( ).AddString( pathID );

	bool bret = false;

	// Count backward since we're possibly deleting one or more pack files, too
	int i;
	for( i = m_SearchPaths.Count() - 1; i >= 0; i-- )
	{
		if( newPath && m_SearchPaths[i].m_Path != lookup )
			continue;
		if( pathID && m_SearchPaths[i].m_PathID != id )
			continue;

		m_SearchPaths.Remove( i );
		bret = true;
	}
	return bret;
}

const char * CBaseFileSystem::GetSearchPath( const char *pathID )
{
	CUtlSymbol id = PathIDTable( ).AddString( pathID );

	// Count backward since we're possibly deleting one or more pack files, too
	int i;
	for( i = m_SearchPaths.Count() - 1; i >= 0; i-- )
	{
		if( pathID && m_SearchPaths[i].m_PathID != id )
			continue;

		return PathIDTable( ).String( m_SearchPaths[i].m_Path );
	}
	return NULL;
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CBaseFileSystem::CSearchPath *CBaseFileSystem::FindWritePath( const char *pathID )
{
	CUtlSymbol lookup = PathIDTable( ).AddString( pathID );

	// a pathID has been specified, find the first match in the path list
	for (int i = 0; i < m_SearchPaths.Count(); i++)
	{
		// pak files are not allowed to be written to...
		if (m_SearchPaths[i].m_bIsPackFile)
			continue;

		if ( !pathID || (m_SearchPaths[i].m_PathID == lookup) )
		{
			return &m_SearchPaths[i];
		}
	}

	return NULL;
}


//-----------------------------------------------------------------------------
// Purpose: Finds a search path that should be used for writing to, given a pathID
//-----------------------------------------------------------------------------
const char *CBaseFileSystem::GetWritePath( const char *pathID )
{
	CSearchPath *pSearchPath = NULL;
	if (pathID)
	{
		pSearchPath = FindWritePath( pathID );
		if (pSearchPath)
		{
			return pSearchPath->GetPathString();
		}

		Warning( FILESYSTEM_WARNING, "Requested non-existent write path %s!\n", pathID );
	}

	// Choose the topmost writeable path in the list to write to
	// FIXME: Is this really what we want to be doing here?
	pSearchPath = FindWritePath( NULL ); // Should we find "DEFAULT_WRITE_PATH" ?
	if (pSearchPath)
	{
		return pSearchPath->GetPathString();
	}

	// Hope this is reasonable!!
	return ".\\";
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CBaseFileSystem::RemoveAllSearchPaths( void )
{
	m_SearchPaths.Purge();
	m_PackFileHandles.Purge();
}


void CBaseFileSystem::SetFileFindOrder(bool fileOrder)
{
	gWholeFirst = fileOrder;
}

//-----------------------------------------------------------------------------
// Purpose: The base file search goes through here
// Input  : *path -
//			*pFileName -
//			*pOptions -
//			packfile -
//			*filetime -
// Output : FileHandle_t
//-----------------------------------------------------------------------------
static CBaseFileSystem::CFileHandle *s_Filehandle = NULL;
FileHandle_t CBaseFileSystem::FindFile( const CSearchPath *path, const char *pFileName, const char *pOptions )
{

	CFileHandle *fh;

	//先检查打包文�
	if (gWholeFirst)
	{
		if ( path->m_bIsPackFile )
		{
			// Search the tree for the filename
			CPackFileEntry search;


			char szPath[512];
			int nPathLen = strlen( path->GetPathString());
			MakeNakedNameIndex( path->GetPathString(), szPath, nPathLen, 0 );

			int nLen = strlen( pFileName );
			char* temp = (char*)_alloca(strlen(szPath)+ nLen +2);
			strcpy(temp,szPath);
			strcat( temp, "/" );
			strcat( temp, pFileName );
			FixSlashes1( temp );

			strlwr( temp );

			std::string strtemp;
			strtemp = temp;
			int a = strtemp.find( "//" );
			while( a >= 0 )
			{
				strtemp.replace( a, 2, "/" );
				a = strtemp.find( "//" );
			}

			search.m_Name = PathIDTable( ).AddString( strtemp.c_str( ) );
			//		Plat_SimpleLog( temp, __LINE__ );

			//int searchresult = path->m_PackFiles.Find( search );

			if ( g_vec.IsValidIndex( search.m_Name )/*searchresult != path->m_PackFiles.InvalidIndex()*/ )
			{
				CPackFileEntry *result = g_vec[ search.m_Name ];

				//

				fh = new CFileHandle;

				fh->m_pFile = ((CFileHandle *)path->m_hPackFile)->m_pFile;
				fh->m_nStartOffset = result->m_nPosition;
				fh->m_nLength = result->m_nLength;
				fh->m_nFileTime = path->m_lPackFileTime;
				fh->m_bPack = true;
				fh->m_pFileLock = ((CFileHandle *)path->m_hPackFile)->m_pFileLock;
				fh->m_bEncry = path->m_bIsEncrypt;
				return (FileHandle_t)fh;
			}
		}
	}
	// Is it an absolute path?
	char *pTmpFileName;
#ifdef WIN32
	if ( strchr( pFileName, ':' ) )
	{
		pTmpFileName = ( char * )_alloca( strlen( pFileName ) + 2 );

		strcat( pTmpFileName,"\\");

		strcpy( pTmpFileName, pFileName );
	}
	else
#endif
	{
		pTmpFileName = ( char * )_alloca( strlen( path->GetPathString() ) + strlen( pFileName ) + 2 );
		strcpy( pTmpFileName, path->GetPathString() );

		strcat( pTmpFileName,"\\");

		strcat( pTmpFileName, pFileName );
		FixSlashes( pTmpFileName );
	}

	FILE *fp = Trace_FOpen( pTmpFileName, pOptions );
	if( fp )
	{
		if( m_pLogFile )
		{
			static char buf[1024];
#if BSPOUTPUT
			sprintf( buf, "%s\n%s\n", pFileName, pTmpFileName);
#else
			sprintf( buf, "copy \"\\srcdir\\%s\" \"\\targetdir\\%s\"\n", pTmpFileName, pTmpFileName );
			char *tmp = ( char * )_alloca( strlen( pTmpFileName ) + 1 );
			strcpy( tmp, pTmpFileName );
			StripFilename( tmp );
			fprintf( m_pLogFile, "perl u:\\hl2\\bin\\makedirhier.pl \"\\targetdir\\%s\"\n", tmp ); // STEAM OK
#endif
			fprintf( m_pLogFile, "%s", buf ); // STEAM OK
		}

		if( m_bOutputDebugString )
		{
#ifdef WIN32
			OutputDebugString( "fs_debug: " );
			OutputDebugString( pFileName );
			OutputDebugString( "\n" );
#else
			fprintf(stderr, "fs_debug: %s\n",pFileName);
#endif
		}


		fh = new CFileHandle;

		fh->m_pFile = fp;
		fh->m_bPack = false;
		struct	_stat buf;
		int sr = FS_stat( pTmpFileName, &buf );
		if ( sr == -1 )
		{
			Warning( FILESYSTEM_WARNING, "_stat on file %s which appeared to exist failed!!!\n",
					pTmpFileName );
		}
		fh->m_nFileTime = buf.st_mtime;
		fh->m_nLength = buf.st_size;
		fh->m_nStartOffset = 0;

		return ( FileHandle_t )fh;
	}

	//先检查打包文�
	if (!gWholeFirst)
	{
		if ( path->m_bIsPackFile )
		{
			// Search the tree for the filename
			CPackFileEntry search;


			char szPath[512];
			int nPathLen = strlen( path->GetPathString());
			MakeNakedNameIndex( path->GetPathString(), szPath, nPathLen, 0 );

			int nLen = strlen( pFileName );
			char* temp = (char*)_alloca(strlen(szPath)+ nLen +2);
			strcpy(temp,szPath);
			strcat( temp, "/" );
			strcat( temp, pFileName );
			FixSlashes1( temp );

			strlwr( temp );

			std::string strtemp;
			strtemp = temp;
			int a = strtemp.find( "//" );
			while( a >= 0 )
			{
				strtemp.replace( a, 2, "/" );
				a = strtemp.find( "//" );
			}

			search.m_Name = PathIDTable( ).AddString( strtemp.c_str( ) );
			//		Plat_SimpleLog( temp, __LINE__ );

			//int searchresult = path->m_PackFiles.Find( search );

			if ( g_vec.IsValidIndex( search.m_Name )/*searchresult != path->m_PackFiles.InvalidIndex()*/ )
			{
				CPackFileEntry *result = g_vec[ search.m_Name ];

				//

				fh = new CFileHandle;

				fh->m_pFile = ((CFileHandle *)path->m_hPackFile)->m_pFile;
				fh->m_nStartOffset = result->m_nPosition;
				fh->m_nLength = result->m_nLength;
				fh->m_nFileTime = path->m_lPackFileTime;
				fh->m_bPack = true;
				fh->m_pFileLock = ((CFileHandle *)path->m_hPackFile)->m_pFileLock;

				return (FileHandle_t)fh;
			}
		}
	}
	return (FileHandle_t)NULL;
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
FileHandle_t CBaseFileSystem::OpenForRead( const char *pFileName, const char *pOptions, const char *pathID )
{
	CUtlSymbol lookup;
	if (pathID)
	{
		lookup = PathIDTable( ).AddString( pathID );
	}

	// Opening for READ needs to search search paths
	for( int i = 0; i < m_SearchPaths.Count(); i++ )
	{
		if (pathID && m_SearchPaths[i].m_PathID != lookup)
			continue;

		FileHandle_t filehandle = FindFile( &m_SearchPaths[ i ], pFileName, pOptions );
		if ( filehandle == 0 )
			continue;

		int nLen = strlen( pFileName );
		char* temp = (char*)_alloca( nLen + 2 );
		memcpy( temp, pFileName, nLen );
		//char* temp = (char*)_alloca(strlen(pathID)+ nLen +2);
		//strcpy( temp, pathID );
		//strcat( temp, pFileName );
		md5.MDString( temp, (unsigned char*)(((CFileHandle*)filehandle)->m_md5) );

		return filehandle;
	}

	return ( FileHandle_t )0;
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
FileHandle_t CBaseFileSystem::OpenForWrite( const char *pFileName, const char *pOptions, const char *pathID )
{
	// Opening for write or append uses the write path
	// Unless an absolute path is specified...
	const char *pTmpFileName;
	if ( strstr( pFileName, ":" ) || pFileName[0] == '/' || pFileName[0] == '\\' )
	{
		pTmpFileName = pFileName;
	}
	else
	{
		ComputeFullWritePath( s_pScratchFileName, pFileName, pathID );
		pTmpFileName = s_pScratchFileName;
	}

	FILE *fp = Trace_FOpen( pTmpFileName, pOptions );
	if( !fp )
		return ( FileHandle_t )0;

	CFileHandle *fh = new CFileHandle;

	struct	_stat buf;
	int sr = FS_stat( pTmpFileName, &buf );
	if ( sr == -1 )
	{
		Warning( FILESYSTEM_WARNING, "_stat on file %s which appeared to exist failed!!!\n",
				pTmpFileName );
	}
	fh->m_nFileTime = buf.st_mtime;
	fh->m_nLength = buf.st_size;
	fh->m_nStartOffset = 0;

	fh->m_bPack = false;
	fh->m_pFile = fp;

	return ( FileHandle_t )fh;
}


// This looks for UNC-type filename specifiers, which should be used instead of
// passing in path ID. So if it finds //mod/cfg/config.cfg, it translates
// pFilename to "cfg/config.cfg" and pPathID to "mod" (mod is placed in tempPathID).
void CBaseFileSystem::ParsePathID( const char* &pFilename, const char* &pPathID, char tempPathID[MAX_PATH] )
{
	if ( pFilename[0] == 0 )
	{
		return;
	}
	else if ( PATHSEPARATOR( pFilename[0] ) && PATHSEPARATOR( pFilename[1] ) )
	{
		// They're specifying two path IDs. Ignore the one in the filename.
		if ( pPathID )
		{
			Assert( false );
			Warning( FILESYSTEM_WARNING, "FS:  Specified two path IDs (%s, %s).\n", pFilename, pPathID );
			return;
		}

		// Parse out the path ID.
		const char *pIn = &pFilename[2];
		char *pOut = tempPathID;
		while ( *pIn && !PATHSEPARATOR( *pIn ) && (pOut - tempPathID) < (MAX_PATH-1) )
		{
			*pOut++ = *pIn++;
		}

		*pOut = 0;

		if ( tempPathID[0] == '*' )
		{
			// * means NULL.
			pPathID = NULL;
		}
		else
		{
			pPathID = tempPathID;
		}

		// Move pFilename up past the part with the path ID.
		if ( *pIn == 0 )
			pFilename = pIn;
		else
			pFilename = pIn + 1;
	}
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------

FileHandle_t CBaseFileSystem::Open( const char *pFileName, const char *pOptions, const char *pathID )
{
	//VPROF_BUDGET( "CBaseFileSystem::Open", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );

	// Allow for UNC-type syntax to specify the path ID.
	char resourcePathID[128]={0};
	if (pathID&&strcmp(pathID,"STUDIO_PATH" )==0)
	{
		if (FileExists( pFileName,"STUDIO_PATH3" ))
		{
			strcpy( resourcePathID, "STUDIO_PATH3" );
		}
		else
		{
			if (FileExists( pFileName,"STUDIO_PATH2" ))
			{
				strcpy( resourcePathID, "STUDIO_PATH2" );
			}
			else
			{
				if (FileExists( pFileName,"STUDIO_PATH" ))
				{
					strcpy( resourcePathID, "STUDIO_PATH" );
				}
				else
				{
#ifdef __DEV__
					Log("��Դȱʧ %s ",pFileName);
#endif	
					return ( FileHandle_t )0;
				}
			}	
		}
	}
	else
	{
		return OpenReadorWrite( pFileName, pOptions, pathID );	
	}
	return OpenReadorWrite( pFileName, pOptions, resourcePathID );
}
FileHandle_t CBaseFileSystem::OpenReadorWrite( const char *pFileName, const char *pOptions, const char *pathID )
{
	char tempPathID[MAX_PATH];
	ParsePathID( pFileName, pathID, tempPathID );

	// Try each of the search paths in succession
	// FIXME: call createdirhierarchy upon opening for write.
	if( strstr( pOptions, "r" ) && !strstr( pOptions, "+" ) )
	{
		FileHandle_t fh = OpenForRead( pFileName, pOptions, pathID );
		return fh;
	}

	return OpenForWrite( pFileName, pOptions, pathID );
}

FileHandle_t CBaseFileSystem::OpenAbsolutePath( const char *pFileName, const char *pOptions, const char *pathID )
{
	const char *pTmpFileName;
    pTmpFileName = pFileName;

	FILE *fp = Trace_FOpen( pTmpFileName, pOptions );
	if( !fp )
		return ( FileHandle_t )0;

	CFileHandle *fh = new CFileHandle;

	struct	_stat buf;
	int sr = FS_stat( pTmpFileName, &buf );
	if ( sr == -1 )
	{
		Warning( FILESYSTEM_WARNING, "_stat on file %s which appeared to exist failed!!!\n",
			pTmpFileName );
	}
	fh->m_nFileTime = buf.st_mtime;
	fh->m_nLength = buf.st_size;
	fh->m_nStartOffset = 0;

	fh->m_bPack = false;
	fh->m_pFile = fp;

	return ( FileHandle_t )fh;
	  //return (FileHandle_t)fopen( pFileName, pOptions );
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CBaseFileSystem::Close( FileHandle_t file )
{
//	VPROF_BUDGET( "CBaseFileSystem::Close", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	CFileHandle *fh = ( CFileHandle *)file;
	if ( !fh )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Close NULL file handle!\n" );
		return;
	}

	if ( !fh->m_pFile )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Close NULL file pointer inside valid file handle!\n" );
		return;
	}

	// Don't close the underlying fp if this is a pack file file pointer
	bool isPackFilePointer = ( m_PackFileHandles.Find( fh->m_pFile ) != m_PackFileHandles.InvalidIndex() ) ? true : false;
	if ( !isPackFilePointer )
	{
		Trace_FClose( fh->m_pFile );
		fh->m_pFile = 0;
	}

	delete fh;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CBaseFileSystem::Seek( FileHandle_t file, int pos, FileSystemSeek_t whence )
{
//	VPROF_BUDGET( "CBaseFileSystem::Seek", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	CFileHandle *fh = ( CFileHandle *)file;
	if ( !fh )
	{
		Warning( FILESYSTEM_WARNING, "Tried to Seek NULL file handle!\n" );
		return;
	}

	if ( !fh->m_pFile )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Seek NULL file pointer inside valid file handle!\n" );
		return;
	}

	int seekType;
	if (whence == FILESYSTEM_SEEK_HEAD)
		seekType = SEEK_SET;
	else if (whence == FILESYSTEM_SEEK_CURRENT)
		seekType = SEEK_CUR;
	else
		seekType = SEEK_END;

	// Pack files get special handling
	if ( fh->m_bPack )
	{
		if ( whence == FILESYSTEM_SEEK_CURRENT )
		{
			// Just offset from current position
			FS_fseek( fh->m_pFile, pos, seekType );
		}
		else if ( whence == FILESYSTEM_SEEK_HEAD )
		{
			// Go to start and offset by pos
			FS_fseek( fh->m_pFile, pos + fh->m_nStartOffset, seekType );
		}
		else
		{
			// Go to end and offset by pos
			FS_fseek( fh->m_pFile, pos + fh->m_nStartOffset + fh->m_nLength, seekType );
		}
	}
	else
	{
		FS_fseek( fh->m_pFile, pos, seekType );
	}
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : file -
// Output : unsigned int
//-----------------------------------------------------------------------------
unsigned int CBaseFileSystem::Tell( FileHandle_t file )
{
//	VPROF_BUDGET( "CBaseFileSystem::Tell", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	CFileHandle *fh = ( CFileHandle *)file;
	if ( !fh )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Tell NULL file handle!\n" );
		return 0;
	}

	if ( !fh->m_pFile )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Tell NULL file pointer inside valid file handle!\n" );
		return 0;
	}

	// Pack files are relative
	return FS_ftell( fh->m_pFile ) - fh->m_nStartOffset;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : file -
// Output : unsigned int
//-----------------------------------------------------------------------------
unsigned int CBaseFileSystem::Size( FileHandle_t file )
{
//	VPROF_BUDGET( "CBaseFileSystem::Size", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	CFileHandle *fh = ( CFileHandle *)file;
	if ( !fh )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Size NULL file handle!\n" );
		return 0;
	}

	if ( !fh->m_pFile )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Size NULL file pointer inside valid file handle!\n" );
		return 0;
	}

	return fh->m_nLength;
}



//-----------------------------------------------------------------------------
// Purpose:
// Input  : file -
// Output : unsigned int
//-----------------------------------------------------------------------------
unsigned int CBaseFileSystem::Size( const char* pFileName, const char *pPathID )
{
//	VPROF_BUDGET( "CBaseFileSystem::Size", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	// handle the case where no name passed...
	if ( !strcmp(pFileName,"") )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Size NULL filename!\n" );
		return 0;
	}

	// Allow for UNC-type syntax to specify the path ID.
	char tempPathID[MAX_PATH];
	ParsePathID( pFileName, pPathID, tempPathID );

	// Handle adding in searth paths
	int i;
	int iSize = 0;
	CUtlSymbol id = PathIDTable( ).AddString( pPathID );
	for( i = 0; i < m_SearchPaths.Count(); i++ )
	{
		if ( pPathID && m_SearchPaths[i].m_PathID != id )
			continue;

		iSize = FastFindFile( &m_SearchPaths[ i ], pFileName );
		if ( iSize > 0 )
		{
			break;
		}
	}
	return iSize;
}

int CBaseFileSystem::FastFindFile( const CSearchPath *path, const char *pFileName )
{
	struct	_stat buf;

	// Is it an absolute path?
	char *pTmpFileName;
	if ( strchr( pFileName, ':' ) )
	{
		pTmpFileName = ( char * )_alloca( strlen( pFileName ) + 2 );
		strcpy( pTmpFileName, pFileName );
	}
	else
	{
		pTmpFileName = ( char * )_alloca( strlen( path->GetPathString() ) + strlen( pFileName ) + 2 );
		strcpy( pTmpFileName, path->GetPathString() );

		strcat(pTmpFileName,"\\");

		strcat( pTmpFileName, pFileName );
		FixSlashes( pTmpFileName );
	}

	if( _stat( pTmpFileName, &buf ) != -1 )
	{
		return buf.st_size;
	}

	if ( path->m_bIsPackFile )
	{
		// Search the tree for the filename
		CPackFileEntry search;

		char szPath[512];
		int nPathLen = strlen( path->GetPathString());
		MakeNakedNameIndex( path->GetPathString(), szPath, nPathLen, 0 );

		int nLen = strlen( pFileName );
		char* temp = (char*)_alloca(strlen(szPath)+ nLen +2);
		strcpy(temp,szPath);
		strcat( temp, "/" );
		strcat( temp, pFileName );
		FixSlashes1( temp );


		//int nLen = strlen( pFileName );
		//char *temp = ( char * )_alloca( strlen( path->GetPathString() ) + nLen + 2 );
		//strcpy( temp, path->GetPathString() );
		//strcat( temp, "/" );
		//strcat( temp, pFileName );
		//FixSlashes1( temp );

		strlwr( temp );

		std::string strtemp;
		strtemp = temp;
		int a = strtemp.find( "//" );
		while( a >= 0 )
		{
			strtemp.replace( a, 2, "/" );
			a = strtemp.find( "//" );
		}

		search.m_Name = PathIDTable( ).AddString( strtemp.c_str( ) );

		//	int searchresult = path->m_PackFiles.Find( search );

		if (g_vec.IsValidIndex( search.m_Name )/* searchresult != path->m_PackFiles.InvalidIndex()*/ )
		{
			CPackFileEntry *result = g_vec[ search.m_Name ];
			return (result->m_nLength);
		}
	}
	//else
	//{

	//}

	return ( -1 );
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
bool CBaseFileSystem::EndOfFile( FileHandle_t file )
{
	CFileHandle *fh = ( CFileHandle *)file;
	if ( !fh )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to EndOfFile NULL file handle!\n" );
		return true;
	}

	if ( !fh->m_pFile )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to EndOfFile NULL file pointer inside valid file handle!\n" );
		return true;
	}

	if ( fh->m_bPack )
	{
		if ( FS_ftell( fh->m_pFile ) >=
				fh->m_nStartOffset + fh->m_nLength )
		{
			return true;
		}
		return false;
	}
	return !!FS_feof( fh->m_pFile );
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
int CBaseFileSystem::SyncRead( void *pOutput, int size, FileHandle_t file )
{

//	VPROF_BUDGET( "CBaseFileSystem::Read", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	CFileHandle *fh = ( CFileHandle *)file;
	if ( !fh )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Read NULL file handle!\n" );
		return 0;
	}

	if ( !fh->m_pFile )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Read NULL file pointer inside valid file handle!\n" );
		return 0;
	}

	size_t nBytesRead = FS_fread( pOutput, 1, size, fh->m_pFile  );
	m_Stats.nBytesRead += nBytesRead;
	m_Stats.nReads++;

	Trace_FRead(nBytesRead,fh->m_pFile);
	return nBytesRead;
}

//nPos 暂时不起作用
int CBaseFileSystem::Read( void *pOutput, int size,int nPos, FileHandle_t file )
{
//	VPROF_BUDGET( "CBaseFileSystem::Read", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	CFileHandle *fh = ( CFileHandle *)file;
	if ( !fh )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Read NULL file handle!\n" );
		return 0;
	}

	if ( !fh->m_pFile )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Read NULL file pointer inside valid file handle!\n" );
		return 0;
	}

	size_t nBytesRead;
	if (fh->m_bPack)
	{
		fh->m_pFileLock->Enter();
		Seek(fh,fh->m_nReadOffset,FILESYSTEM_SEEK_HEAD);  //nPos = 0
		//Seek( (FileHandle_t)s_Filehandle, fh->m_nStartOffset, FILESYSTEM_SEEK_HEAD );
		//fseek(fh->m_pFile,fh->m_nStartOffset,SEEK_SET);
		nBytesRead = FS_fread( pOutput, 1, size, fh->m_pFile  );
		if (fh->m_bEncry)
		{
			int i=0;
			for( ; i<size ; i++)
			{
				((unsigned char*)pOutput)[i] = ((unsigned char*)pOutput)[i] ^ 0x5E;
			}
		}
		fh->m_nReadOffset += nBytesRead;
		fh->m_pFileLock->Leave();
	}
	else
	{
		//Seek(fh,nPos,FILESYSTEM_SEEK_HEAD);
		nBytesRead = FS_fread( pOutput, 1, size, fh->m_pFile  );
	}
	m_Stats.nBytesRead += nBytesRead;
	m_Stats.nReads++;

	Trace_FRead(nBytesRead,fh->m_pFile);
	return nBytesRead;
}

int CBaseFileSystem::ReadFileCache( void *pOutput, int size,int nPos, FileHandle_t file )
{
	if( !bufferScheduler.m_bisinit )
	{
		return Read( pOutput, size, nPos, file );
	}

//	VPROF_BUDGET( "CBaseFileSystem::Read", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	CFileHandle *fh = ( CFileHandle *)file;
	if ( !fh )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Read NULL file handle!\n" );
		return 0;
	}

	if ( !fh->m_pFile )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Read NULL file pointer inside valid file handle!\n" );
		return 0;
	}

	size_t nBytesRead;
	if (fh->m_bPack)
	{
		nBytesRead = bufferScheduler.getBuffer( fh->m_md5, pOutput, size );
		if( nBytesRead == 0 )
		{
			fh->m_pFileLock->Enter();
			Seek(fh,fh->m_nReadOffset,FILESYSTEM_SEEK_HEAD);  //nPos = 0
			nBytesRead = FS_fread( pOutput, 1, size, fh->m_pFile  );
			if (fh->m_bEncry)
			{
				int i=0;
				for( ; i<size ; i++)
				{
					((unsigned char*)pOutput)[i] = ((unsigned char*)pOutput)[i] ^ 0x5E;
				}
			}
			bufferScheduler.setBuffer( fh->m_md5, pOutput, nBytesRead );
			fh->m_nReadOffset += nBytesRead;
			fh->m_pFileLock->Leave();
		}
	}
	else
	{
		//Seek(fh,nPos,FILESYSTEM_SEEK_HEAD);
		nBytesRead = bufferScheduler.getBuffer( fh->m_md5, pOutput, size );
		if( nBytesRead == 0 )
		{
			nBytesRead = FS_fread( pOutput, 1, size, fh->m_pFile  );
			bufferScheduler.setBuffer( fh->m_md5, pOutput, nBytesRead );
		}
	}
	m_Stats.nBytesRead += nBytesRead;
	m_Stats.nReads++;

	Trace_FRead(nBytesRead,fh->m_pFile);
	return nBytesRead;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
int CBaseFileSystem::Write( void const* pInput, int size, FileHandle_t file )
{
//	VPROF_BUDGET( "CBaseFileSystem::Write", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	CFileHandle *fh = ( CFileHandle *)file;
	if ( !fh )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Write NULL file handle!\n" );
		return 0;
	}

	if ( !fh->m_pFile )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Write NULL file pointer inside valid file handle!\n" );
		return 0;
	}

	size_t nBytesWritten = FS_fwrite( (void *)pInput, 1, size, fh->m_pFile  );
	m_Stats.nWrites++;
	m_Stats.nBytesWritten += nBytesWritten;

	Trace_FWrite(nBytesWritten,fh->m_pFile);


	return nBytesWritten;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
int CBaseFileSystem::FPrintf( FileHandle_t file, char *pFormat, ... )
{
//	VPROF_BUDGET( "CBaseFileSystem::FPrintf", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	CFileHandle *fh = ( CFileHandle *)file;
	if ( !fh )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to FPrintf NULL file handle!\n" );
		return 0;
	}

	if ( !fh->m_pFile )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to FPrintf NULL file pointer inside valid file handle!\n" );
		return 0;
	}

	va_list args;
	va_start( args, pFormat );
	int len = FS_vfprintf( fh->m_pFile , pFormat, args );
	va_end( args );
	return len;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
bool CBaseFileSystem::IsOk( FileHandle_t file )
{
	CFileHandle *fh = ( CFileHandle *)file;
	if ( !fh )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to IsOk NULL file handle!\n" );
		return false;
	}

	if ( !fh->m_pFile )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to IsOk NULL file pointer inside valid file handle!\n" );
		return false;
	}

	return FS_ferror(fh->m_pFile ) == 0;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CBaseFileSystem::Flush( FileHandle_t file )
{
//	VPROF_BUDGET( "CBaseFileSystem::Flush", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	CFileHandle *fh = ( CFileHandle *)file;
	if ( !fh )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Flush NULL file handle!\n" );
		return;
	}

	if ( !fh->m_pFile )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to Flush NULL file pointer inside valid file handle!\n" );
		return;
	}

	FS_fflush(fh->m_pFile );
}

bool CBaseFileSystem::Precache( const char *pFileName, const char *pPathID)
{
	// Really simple, just open, the file, read it all in and close it.
	// We probably want to use file mapping to do this eventually.
	FileHandle_t f = Open(pFileName,"rb", pPathID );
	if( !f )
		return false;


	char buffer[16384];
	while( sizeof(buffer) == SyncRead(buffer,sizeof(buffer),f) )
		;

	Close(f);

	return true;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
char *CBaseFileSystem::ReadLine( char *pOutput, int maxChars, FileHandle_t file )
{
//	VPROF_BUDGET( "CBaseFileSystem::ReadLine", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	CFileHandle *fh = ( CFileHandle *)file;
	if ( !fh )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to ReadLine NULL file handle!\n" );
		return NULL;
	}

	if ( !fh->m_pFile )
	{
		Warning( FILESYSTEM_WARNING, "FS:  Tried to ReadLine NULL file pointer inside valid file handle!\n" );
		return NULL;
	}

	m_Stats.nReads++;

	char* s = FS_fgets( pOutput, maxChars, fh->m_pFile  ); // STEAM ???

	if( s )
	{
		m_Stats.nBytesRead += strlen(s);
	}
	return s;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *pFileName -
// Output : long
//-----------------------------------------------------------------------------
long CBaseFileSystem::GetFileTime( const char *pFileName, const char *pPathID )
{
	// Allow for UNC-type syntax to specify the path ID.
	char tempPathID[MAX_PATH];
	ParsePathID( pFileName, pPathID, tempPathID );


	CUtlSymbol id = PathIDTable( ).AddString( pPathID );

//	VPROF_BUDGET( "CBaseFileSystem::GetFileTime", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	int i;
	for( i = 0; i < m_SearchPaths.Count(); i++ )
	{
		if ( pPathID && m_SearchPaths[i].m_PathID != id )
			continue;

		FileHandle_t filehandle = FindFile( &m_SearchPaths[ i ], pFileName, "rb" );
		if ( filehandle == 0 )
			continue;

		CFileHandle *fh = (CFileHandle *)filehandle;
		if ( !fh )
			continue;

		long time = fh->m_nFileTime;

		// This function should really return a status. As it is, the callers
		// assume it couldn't find the file if it returns 0. So return 1 instead of
		// 0 here...
		if( time == 0 )
			time = 1;

		Close( filehandle );

		return time;
	}
	return 0L;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *pString -
//			maxCharsIncludingTerminator -
//			fileTime -
//-----------------------------------------------------------------------------
void CBaseFileSystem::FileTimeToString( char *pString, int maxCharsIncludingTerminator, long fileTime )
{
	strncpy( pString, ctime( (time_t *)&fileTime ), maxCharsIncludingTerminator );
	pString[maxCharsIncludingTerminator-1] = '\0';
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *pFileName -
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseFileSystem::FileExists( const char *pFileName, const char *pPathID )
{
	// Allow for UNC-type syntax to specify the path ID.
	char tempPathID[MAX_PATH];
	ParsePathID( pFileName, pPathID, tempPathID );


//	VPROF_BUDGET( "CBaseFileSystem::FileExists", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	CUtlSymbol lookup;
	if (pPathID)
	{
		lookup = PathIDTable( ).AddString( pPathID );
	}

	int i;
	for( i = 0; i < m_SearchPaths.Count(); i++ )
	{
		if (pPathID && m_SearchPaths[i].m_PathID != lookup)
			continue;

		FileHandle_t filehandle = FindFile( &m_SearchPaths[ i ], pFileName, "rb" );
		if ( filehandle == 0 )
			continue;

		Close( filehandle );

		return true;
	}
	return false;
}

bool CBaseFileSystem::IsUIFileExists( const char* pFileName )
{
	char szTgaPath[MAX_PATH]={0};
	char szVtfPath[MAX_PATH]={0};

	Q_snprintf( szVtfPath,MAX_PATH, "texture/%s.vtf", pFileName);
	Q_snprintf( szTgaPath, MAX_PATH, "texturesrc/%s.tga", pFileName);
	bool bFound = FileSystem().FileExists( szVtfPath,"STUDIO_PATH" );
	if ( !bFound )  
	{
		bFound = FileSystem().FileExists( szVtfPath,"STUDIO_PATH2" );
		if (!bFound)
		{	
			bFound = FileSystem().FileExists( szVtfPath,"STUDIO_PATH3" );
		}
	}
    return bFound;

}

bool CBaseFileSystem::IsFileWritable( char const *pFileName, char const *pPathID /*=0*/ )
{
	// Allow for UNC-type syntax to specify the path ID.
	char tempPathID[MAX_PATH];
	ParsePathID( pFileName, pPathID, tempPathID );


	CUtlSymbol id = PathIDTable( ).AddString( pPathID );

	struct	_stat buf;
	int i;
	for( i = 0; i < m_SearchPaths.Size(); i++ )
	{
		// Pack files can't be directories
		CSearchPath *sp = &m_SearchPaths[ i ];
		if ( sp->m_bIsPackFile )
			continue;
		if ( pPathID && m_SearchPaths[i].m_PathID != id )
			continue;

		char *pTmpFileName;
		pTmpFileName = ( char * )_alloca( strlen( m_SearchPaths[i].GetPathString() ) + strlen( pFileName ) + 1 );
		strcpy( pTmpFileName, m_SearchPaths[i].GetPathString() );
		strcat( pTmpFileName, pFileName );
		FixSlashes( pTmpFileName );
		if( FS_stat( pTmpFileName, &buf ) != -1 )
		{
#ifdef WIN32
			if( buf.st_mode & _S_IWRITE )
#else
				if( buf.st_mode & S_IWRITE )
#endif
				{
					return true;
				}
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *pFileName -
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseFileSystem::IsDirectory( const char *pFileName, const char *pathID )
{
	// Allow for UNC-type syntax to specify the path ID.
	char tempPathID[MAX_PATH];
	ParsePathID( pFileName, pathID, tempPathID );


	CUtlSymbol id = PathIDTable( ).AddString( pathID );

	struct	_stat buf;
	int i;
	for( i = 0; i < m_SearchPaths.Count(); i++ )
	{
		// Pack files can't be directories
		CSearchPath *sp = &m_SearchPaths[ i ];
		if ( sp->m_bIsPackFile )
			continue;
		if ( pathID && m_SearchPaths[i].m_PathID != id )
			continue;

		char *pTmpFileName;
		pTmpFileName = ( char * )_alloca( strlen( m_SearchPaths[i].GetPathString() ) + strlen( pFileName ) + 1 );
		strcpy( pTmpFileName, m_SearchPaths[i].GetPathString() );
		strcat( pTmpFileName, pFileName );
		FixSlashes( pTmpFileName );
		if( FS_stat( pTmpFileName, &buf ) != -1 )
		{
#ifdef WIN32
			if( buf.st_mode & _S_IFDIR )
#else
				if (S_ISDIR(buf.st_mode))
#endif
				{
					return true;
				}
		}
	}
	return false;
}


//-----------------------------------------------------------------------------
// Purpose:
// Input  : *path -
//-----------------------------------------------------------------------------
void CBaseFileSystem::CreateDirHierarchy( const char *pRelativePath, const char *pathID )
{
	// Allow for UNC-type syntax to specify the path ID.
	char tempPathID[MAX_PATH];
	ParsePathID( pRelativePath, pathID, tempPathID );


	ComputeFullWritePath( s_pScratchFileName, pRelativePath, pathID );
	int len = strlen( s_pScratchFileName ) + 1;

	char *s;
	char *end;

	end = s_pScratchFileName + len;
	s = s_pScratchFileName;

	while( s < end )
	{
		if( *s == CORRECT_PATH_SEPARATOR )
		{
			*s = '\0';
#ifdef WIN32
			_mkdir( s_pScratchFileName );
#else
			mkdir( s_pScratchFileName, S_IRWXU |  S_IRGRP |  S_IROTH );// owner has rwx, rest have r
#endif
			*s = CORRECT_PATH_SEPARATOR;
		}
		s++;
	}
#ifdef WIN32
	_mkdir( s_pScratchFileName );
#else
	mkdir( s_pScratchFileName, S_IRWXU |  S_IRGRP |  S_IROTH );
#endif

}


//-----------------------------------------------------------------------------
// Purpose:
// Input  : *pWildCard -
//			*pHandle -
// Output : const char
//-----------------------------------------------------------------------------
const char *CBaseFileSystem::FindFirst( const char *pWildCard, FileFindHandle_t *pHandle )
{
//	VPROF_BUDGET( "CBaseFileSystem::FindFirst", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	Assert(pWildCard);
	Assert(pHandle);

	FileFindHandle_t hTmpHandle = m_FindData.Count();
	m_FindData.AddToTail();
	FindData_t *pFindData = &m_FindData[hTmpHandle];
	Assert(pFindData);

	pFindData->wildCardString.AddMultipleToTail( strlen( pWildCard ) + 1 );
	strcpy( pFindData->wildCardString.Base(), pWildCard );
	FixSlashes( pFindData->wildCardString.Base() );

	for(	pFindData->currentSearchPathID = 0;
			pFindData->currentSearchPathID < m_SearchPaths.Count();
			pFindData->currentSearchPathID++ )
	{
		// FIXME:  Should findfirst/next work with pak files?
		if ( m_SearchPaths[pFindData->currentSearchPathID].m_bIsPackFile )
			continue;

		char *pTmpFileName;
		int size;
		size = strlen( m_SearchPaths[pFindData->currentSearchPathID].GetPathString() ) + pFindData->wildCardString.Count();
		pTmpFileName = ( char * )_alloca( size + 1 ); // don't need two NULL terminators.
		strcpy( pTmpFileName, m_SearchPaths[pFindData->currentSearchPathID].GetPathString() );
		strcat( pTmpFileName, pFindData->wildCardString.Base() );
		FixSlashes( pTmpFileName );

		pFindData->findHandle = FS_FindFirstFile( pTmpFileName, &pFindData->findData );

		if( pFindData->findHandle != INVALID_HANDLE_VALUE )
		{
			*pHandle = hTmpHandle;
			return pFindData->findData.cFileName;
		}
	}

	// Handle failure here
	pFindData = 0;
	m_FindData.Remove(hTmpHandle);
	*pHandle = -1;

	return NULL;
}

// assumes that pSearchWildcard has the proper slash convention.
bool CBaseFileSystem::FileInSearchPaths( const char *pSearchWildcard,
		const char *pFileName, int minSearchPathID,
		int maxSearchPathID )
{
	if( minSearchPathID > maxSearchPathID )
	{
		return false;
	}

	// FIGURE OUT THE FILENAME WITHOUT THE SEARCH PATH.
	const char *tmp = &pSearchWildcard[strlen( pSearchWildcard ) - 1];
	while( *tmp != CORRECT_PATH_SEPARATOR && tmp > pSearchWildcard )
	{
		tmp--;
	}
	tmp++;
	if( tmp <= pSearchWildcard )
	{
		Assert( 0 );
		return false;
	}
	int pathStrLen = tmp - pSearchWildcard;
	int fileNameStrLen = strlen( pFileName );
	char *pFileNameWithPath = ( char * )_alloca( pathStrLen + fileNameStrLen + 1 );
	memcpy( pFileNameWithPath, pSearchWildcard, pathStrLen );
	pFileNameWithPath[pathStrLen] = '\0';
	strcat( pFileNameWithPath, pFileName );

	// Check each of the search paths and see if the file exists.
	int i;
	for( i = minSearchPathID; i <= maxSearchPathID; i++ )
	{
		// FIXME: Should this work with PAK files?
		if ( m_SearchPaths[i].m_bIsPackFile )
			continue;

		char *fullFilePath;
		int len = strlen( m_SearchPaths[i].GetPathString() ) + strlen( pFileNameWithPath );
		fullFilePath = ( char * )_alloca( len + 1 );
		strcpy( fullFilePath, m_SearchPaths[i].GetPathString() );
		strcat( fullFilePath, pFileNameWithPath );
		struct	_stat buf;
		if( FS_stat( fullFilePath, &buf ) != -1 )
		{
			return true;
		}
	}
	return false;
}

// Get the next file, trucking through the path. . don't check for duplicates.
bool CBaseFileSystem::FindNextFileHelper( FindData_t *pFindData )
{
	// PAK files???

	// Try the same search path that we were already searching on.
	if( FS_FindNextFile( pFindData->findHandle, &pFindData->findData ) )
	{
		return true;
	}
	pFindData->currentSearchPathID++;

	if ( pFindData->findHandle != INVALID_HANDLE_VALUE )
	{
		FS_FindClose( pFindData->findHandle );
	}
	pFindData->findHandle = INVALID_HANDLE_VALUE;

	while( pFindData->currentSearchPathID < m_SearchPaths.Count() )
	{
		// FIXME: Should this work with PAK files?
		if ( m_SearchPaths[pFindData->currentSearchPathID].m_bIsPackFile )
		{
			pFindData->currentSearchPathID++;
			continue;
		}

		char *pTmpFileName;
		pTmpFileName = ( char * )_alloca( strlen( m_SearchPaths[pFindData->currentSearchPathID].GetPathString() ) +
				pFindData->wildCardString.Count() ); // don't need two NULL terminators.
		strcpy( pTmpFileName, m_SearchPaths[pFindData->currentSearchPathID].GetPathString() );
		strcat( pTmpFileName, pFindData->wildCardString.Base() );
		FixSlashes( pTmpFileName );

		pFindData->findHandle = FS_FindFirstFile( pTmpFileName, &pFindData->findData );
		if( pFindData->findHandle != INVALID_HANDLE_VALUE )
		{
			return true;
		}
		pFindData->currentSearchPathID++;
	}
	return false;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : handle -
// Output : const char
//-----------------------------------------------------------------------------
const char *CBaseFileSystem::FindNext( FileFindHandle_t handle )
{
//	VPROF_BUDGET( "CBaseFileSystem::FindNext", VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	FindData_t *pFindData = &m_FindData[handle];

	while( 1 )
	{
		if( FindNextFileHelper( pFindData ) )
		{
			if( !FileInSearchPaths( pFindData->wildCardString.Base(),
						pFindData->findData.cFileName, 0, pFindData->currentSearchPathID - 1 ) )
			{
				return pFindData->findData.cFileName;
			}
		}
		else
		{
			return NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : handle -
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseFileSystem::FindIsDirectory( FileFindHandle_t handle )
{
	FindData_t *pFindData = &m_FindData[handle];
#ifdef WIN32
	return !!( pFindData->findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY );
#else
	if (S_ISDIR(pFindData->findData.dwFileAttributes))
		return true;
	else
		return false;
#endif
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : handle -
//-----------------------------------------------------------------------------
void CBaseFileSystem::FindClose( FileFindHandle_t handle )
{
	if ((handle < 0) || (m_FindData.Count() == 0) || (handle >= m_FindData.Count()))
		return;

	FindData_t *pFindData = &m_FindData[handle];
	Assert(pFindData);

	if ( pFindData->findHandle != INVALID_HANDLE_VALUE)
	{
		FS_FindClose( pFindData->findHandle );
	}
	pFindData->findHandle = INVALID_HANDLE_VALUE;

	pFindData->wildCardString.Purge();
	m_FindData.FastRemove( handle );
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *pFileName -
//-----------------------------------------------------------------------------
void CBaseFileSystem::GetLocalCopy( const char *pFileName )
{
	// do nothing. . everything is local.
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *pFileName -
// Output : int
//-----------------------------------------------------------------------------
int CBaseFileSystem::GetLocalPathLen( const char *pFileName )
{
	struct	_stat buf;
	int i;
	for( i = 0; i < m_SearchPaths.Count(); i++ )
	{
		// FIXME: Should this work with PAK files?
		if ( m_SearchPaths[i].m_bIsPackFile )
			continue;

		char *pTmpFileName;
		int len = strlen( m_SearchPaths[i].GetPathString() ) + strlen( pFileName );
		pTmpFileName = ( char * )_alloca( len + 1 );
		strcpy( pTmpFileName, m_SearchPaths[i].GetPathString() );
		strcat( pTmpFileName, pFileName );
		FixSlashes( pTmpFileName );
		if( FS_stat( pTmpFileName, &buf ) != -1 )
		{
			return len;
		}
	}
	return 0;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *pFileName -
//			*pLocalPath -
// Output : const char
//-----------------------------------------------------------------------------
const char *CBaseFileSystem::GetLocalPath( const char *pFileName, char *pLocalPath )
{
	struct	_stat buf;
	int i;
	for( i = 0; i < m_SearchPaths.Count(); i++ )
	{
		// FIXME: Should this work with PAK files?
		if ( m_SearchPaths[i].m_bIsPackFile )
			continue;

		char *pTmpFileName;
		int len = strlen( m_SearchPaths[i].GetPathString() ) + strlen( pFileName );
		pTmpFileName = ( char * )_alloca( len + 1 );
		strcpy( pTmpFileName, m_SearchPaths[i].GetPathString() );
		strcat( pTmpFileName, pFileName );
		FixSlashes( pTmpFileName );
		if( FS_stat( pTmpFileName, &buf ) != -1 )
		{
			strcpy( pLocalPath, pTmpFileName );
			return pLocalPath;
		}
	}
	return NULL;
}

//-----------------------------------------------------------------------------
// Purpose: Returns true on success ( based on current list of search paths, otherwise false if
//  it can't be resolved )
// Input  : *pFullpath -
//			*pRelative -
//			maxRelativePathLength -
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseFileSystem::FullPathToRelativePath( const char *pFullpath, char *pRelative )
{
	bool success = false;

	int inlen = strlen( pFullpath );
	if ( inlen <= 0 )
	{
		pRelative[ 0 ] = 0;
		return success;
	}

	strcpy( pRelative, pFullpath );

	char *inpath = (char *)_alloca( inlen + 1 );
	Assert( inpath );
	strcpy( inpath, pFullpath );
	FixSlashes( inpath );
#ifdef WIN32
	strlwr( inpath );
#endif

	for( int i = 0; i < m_SearchPaths.Count() && !success; i++ )
	{
		// FIXME: Should this work with embedded pak files
		if ( m_SearchPaths[i].m_bIsMapPath )
			continue;

		//		char *searchbase = new char[ strlen( m_SearchPaths[i].GetPathString() ) + 1 ];
		char *searchbase = (char *)stackalloc( strlen( m_SearchPaths[i].GetPathString() ) + 1 );
		Assert( searchbase );
		strcpy( searchbase, m_SearchPaths[i].GetPathString() );
		FixSlashes( searchbase );
#ifdef WIN32
		strlwr( searchbase );
#endif

		if ( !strnicmp( searchbase, inpath, strlen( searchbase ) ) )
		{
			success = true;
			strcpy( pRelative, &inpath[ strlen( searchbase ) ] );
		}

		//		delete[] searchbase;
	}

	return success;
}


//-----------------------------------------------------------------------------
// Deletes a file
//-----------------------------------------------------------------------------
void CBaseFileSystem::RemoveFile( char const* pRelativePath, const char *pathID )
{
	// Allow for UNC-type syntax to specify the path ID.
	char tempPathID[MAX_PATH];
	ParsePathID( pRelativePath, pathID, tempPathID );


	// Opening for write or append uses Write Path
	ComputeFullWritePath( s_pScratchFileName, pRelativePath, pathID );
	int fail = unlink( s_pScratchFileName );
	if (fail != 0)
	{
		Warning( FILESYSTEM_WARNING, "Unable to remove %s!\n", s_pScratchFileName );
	}
}


//-----------------------------------------------------------------------------
// Renames a file
//-----------------------------------------------------------------------------
void CBaseFileSystem::RenameFile( char const *pOldPath, char const *pNewPath, const char *pathID )
{
	Assert( pOldPath && pNewPath );

	char pNewFileName[ MAX_PATH ];

	ComputeFullWritePath( s_pScratchFileName, pOldPath, pathID );
	ComputeFullWritePath( pNewFileName, pNewPath, pathID );

	int fail = rename( s_pScratchFileName, pNewFileName );
	if (fail != 0)
	{
		Warning( FILESYSTEM_WARNING, "Unable to rename %s to %s!\n", s_pScratchFileName, pNewFileName );
	}
}


//-----------------------------------------------------------------------------
// Purpose:
// Input  : **ppdir -
//-----------------------------------------------------------------------------
bool CBaseFileSystem::GetCurrentDirectory( char* pDirectory, int maxlen )
{
#ifdef WIN32
	if ( !::GetCurrentDirectoryA( maxlen, pDirectory ) )
#else
		if ( !getcwd( pDirectory, maxlen ) )
#endif
			return false;

	FixSlashes(pDirectory);

	// Strip the last slash
	int len = strlen(pDirectory);
	if ( pDirectory[ len-1 ] == CORRECT_PATH_SEPARATOR )
	{
		pDirectory[ len-1 ] = 0;
	}

	return true;
}


//-----------------------------------------------------------------------------
// Purpose:
// Input  : pfnWarning - warning function callback
//-----------------------------------------------------------------------------
void CBaseFileSystem::SetWarningFunc( void (*pfnWarning)( const char *fmt, ... ) )
{
	m_pfnWarning = pfnWarning;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : level -
//-----------------------------------------------------------------------------
void CBaseFileSystem::SetWarningLevel( FileWarningLevel_t level )
{
	m_fwLevel = level;
}

const FileSystemStatistics *CBaseFileSystem::GetFilesystemStatistics()
{
	return &m_Stats;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : level -
//			*fmt -
//			... -
//-----------------------------------------------------------------------------
void CBaseFileSystem::Warning( FileWarningLevel_t level, const char *fmt, ... )
{
	if ( level > m_fwLevel )
		return;

	va_list argptr;
	char warningtext[ 4096 ];

	va_start( argptr, fmt );
	_vsnprintf( warningtext, sizeof( warningtext ), fmt, argptr );
	va_end( argptr );

	// Dump to stdio
	printf( warningtext );
	if ( m_pfnWarning )
	{
		(*m_pfnWarning)( warningtext );
	}
	else
	{
#ifdef WIN32
		OutputDebugString( warningtext );
#endif
	}
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CBaseFileSystem::COpenedFile::COpenedFile( void )
{
	m_pFile = NULL;
	m_pName = NULL;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CBaseFileSystem::COpenedFile::~COpenedFile( void )
{
	//	SAFE_DELETE_ARRAY( m_pName );
	Plat_Free( m_pName );
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : src -
//-----------------------------------------------------------------------------
CBaseFileSystem::COpenedFile::COpenedFile( const COpenedFile& src )
{
	m_pFile = src.m_pFile;
	if ( src.m_pName )
	{
		//		m_pName = new char[ strlen( src.m_pName ) + 1 ];
		m_pName = (char*)Plat_Alloc( strlen( src.m_pName ) + 1 );
		strcpy( m_pName, src.m_pName );
	}
	else
	{
		m_pName = NULL;
	}
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : src -
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseFileSystem::COpenedFile::operator==( const CBaseFileSystem::COpenedFile& src ) const
{
	return src.m_pFile == m_pFile;
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : *name -
//-----------------------------------------------------------------------------
void CBaseFileSystem::COpenedFile::SetName( char const *name )
{
	//	SAFE_DELETE_ARRAY( m_pName );
	//	m_pName = new char[ strlen( name ) + 1 ];
	Plat_Free( m_pName );
	m_pName = (char*)Plat_Alloc( strlen( name ) + 1 );
	strcpy( m_pName, name );
}

//-----------------------------------------------------------------------------
// Purpose:
// Output : char
//-----------------------------------------------------------------------------
char const *CBaseFileSystem::COpenedFile::GetName( void )
{
	return m_pName ? m_pName : "???";
}

//-----------------------------------------------------------------------------
// Purpose:
// Input  : src1 -
//			src2 -
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------
bool CBaseFileSystem::CSearchPath::PackFileLessFunc( CPackFileEntry const& src1, CPackFileEntry const& src2 )
{
	return ( src1.m_Name < src2.m_Name );
}


const char* CBaseFileSystem::CSearchPath::GetPathString() const
{
	return PathIDTable( ).String( m_Path );
}


const char* CBaseFileSystem::CSearchPath::GetPathIDString() const
{
	return PathIDTable( ).String( m_PathID );
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
	CBaseFileSystem::CSearchPath::CSearchPath( void )
: m_PackFiles( 0, 32, PackFileLessFunc )
{
	m_Path				= PathIDTable( ).AddString( "" );
	m_bIsPackFile		= false;
	m_bIsMapPath		= false;
	m_bIsEncrypt		= false;
	m_lPackFileTime		= 0L;
	m_nNumPackFiles		= 0;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CBaseFileSystem::CSearchPath::~CSearchPath( void )
{
	if ( m_bIsPackFile && m_hPackFile )
	{
		// Allow closing to actually occur
		m_fs->m_PackFileHandles.FindAndRemove( m_hPackFile->m_pFile );

		SAFE_DELETE(m_hPackFile->m_pFileLock);
		m_fs->Close( (FileHandle_t)m_hPackFile );

	}
}


//-----------------------------------------------------------------------------
// Fixes slashes in the directory name
//-----------------------------------------------------------------------------
static void FixSlashes( char *str )
{
	while( *str )
	{
		if( *str == INCORRECT_PATH_SEPARATOR )
		{
			*str = CORRECT_PATH_SEPARATOR;
		}
		str++;
	}
}

//-----------------------------------------------------------------------------
// Fixes slashes in the directory name
//-----------------------------------------------------------------------------
static void FixSlashes1( char *str )
{
	while( *str )
	{
		if( *str == CORRECT_PATH_SEPARATOR )
		{
			*str = INCORRECT_PATH_SEPARATOR;
		}
		str++;
	}
}

//-----------------------------------------------------------------------------
// Make sure that slashes are of the right kind and that there is a slash at the
// end of the filename.
// WARNING!!: assumes that you have an extra byte allocated in the case that you need
// a slash at the end.
//-----------------------------------------------------------------------------

static void FixPath( char *str )
{
	char *lastChar = &str[strlen( str ) - 1];
	if( *lastChar != CORRECT_PATH_SEPARATOR && *lastChar != INCORRECT_PATH_SEPARATOR )
	{
		lastChar[1] = CORRECT_PATH_SEPARATOR;
		lastChar[2] = '\0';
	}
	FixSlashes( str );
}


//-----------------------------------------------------------------------------
// Purpose:
// Input  : *path -
// Output : static void StripFilename
//-----------------------------------------------------------------------------
static void StripFilename (char *path)
{
	int             length;

	length = strlen(path)-1;
	while (length > 0 && !PATHSEPARATOR(path[length]))
		length--;
	path[length] = 0;
}

ENGINE_GLOBAL BOOL CheckDatFile( const char * szDatFile )
{
	FILE * pDatFile = fopen( szDatFile, "rb" );
	if( pDatFile )
	{
		fseek( pDatFile, 0, FILESYSTEM_SEEK_TAIL );
		int len = ftell( pDatFile );
		fseek( pDatFile, 0, FILESYSTEM_SEEK_HEAD );

		ZIP_EndOfCentralDirRecord rec;
		rec.startOfCentralDirOffset = 0;
		rec.nCentralDirectoryEntries_Total = 0;
		bool foundEndOfCentralDirRecord = false;
		int offset = len - sizeof( ZIP_EndOfCentralDirRecord );
		fseek( pDatFile, offset, FILESYSTEM_SEEK_HEAD);
		fread( (void *)&rec, 1, sizeof(rec), pDatFile );
		if( rec.signature == 0x06054b50 )
			foundEndOfCentralDirRecord = true;
		fclose( pDatFile );
		return foundEndOfCentralDirRecord;
	}
	return FALSE;
}

ENGINE_GLOBAL BOOL RepairDatFile( const char * szDatFile )
{
	FILE * pDatFile = fopen( szDatFile, "ab+" );
	if( pDatFile )
	{
		fseek( pDatFile, 0, FILESYSTEM_SEEK_TAIL );
		int len = ftell( pDatFile );
		fseek( pDatFile, 0, FILESYSTEM_SEEK_HEAD );

		ZIP_EndOfCentralDirRecord rec;
		rec.startOfCentralDirOffset = 0;
		rec.nCentralDirectoryEntries_Total = 0;
		bool foundEndOfCentralDirRecord = false;
		for( int offset = len - sizeof( ZIP_EndOfCentralDirRecord ); offset >= 0; offset-- )
		{
			fseek( pDatFile, offset, FILESYSTEM_SEEK_HEAD);
			fread( (void *)&rec, 1, sizeof(rec), pDatFile );
			//-edit by youxl 2011.8.8
			if( rec.signature == 0x02014b50 || rec.signature == 0x04034b50 ) // Ŀ¼
			//-end
			{
				int off = sizeof(rec);
				fseek( pDatFile, -off, FILESYSTEM_SEEK_CURRENT );

				int curpos = ftell( pDatFile );
				do
				{
					char szErrorDir[] = "__ERROR_DIR_";
					ZIP_FileHeader fileHeader;
					fileHeader.compressedSize = 0;
					fileHeader.compressionMethod = 0;
					fileHeader.crc32 = 0;
					fileHeader.diskNumberStart = 0;
					fileHeader.externalFileAttribs = 16;
					fileHeader.extraFieldLength = 1;
					fileHeader.fileCommentLength = 0;
					fileHeader.fileNameLength = sizeof( szErrorDir ) - 1;
					fileHeader.flags = 0;
					fileHeader.internalFileAttribs = 0;
					fileHeader.lastModifiedDate = 0;
					fileHeader.lastModifiedTime = 0;
					fileHeader.relativeOffsetOfLocalHeader = 0;
					//edit by youxl 2011.8.8
					fileHeader.signature = 0x02014b50;
					//fileHeader.bF=0x00;
					//-end
					fileHeader.uncompressedSize = 0;
					fileHeader.versionMadeBy = 20;
					fileHeader.versionNeededToExtract = 10;

					fwrite( &fileHeader, 1, sizeof( fileHeader ), pDatFile );
					fwrite( szErrorDir, 1, sizeof( szErrorDir ) - 1, pDatFile );

					curpos = ftell( pDatFile );
				}
				while( curpos < len );
				foundEndOfCentralDirRecord = true;
				break;
			}
		}
		fclose( pDatFile );
		return foundEndOfCentralDirRecord;
	}
	return FALSE;
}
