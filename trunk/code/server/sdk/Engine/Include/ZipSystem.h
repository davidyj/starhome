#pragma once



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

#include "zip.h"
#include "unzip.h"
#include "EngineDefine.h"

#ifdef WIN32
#define USEWIN32IOAPI
#include "iowin32.h"
#include <direct.h>
#include <io.h>
#endif

#define WRITEBUFFERSIZE (65535000)
#define MAXFILENAME (512)

typedef unsigned char byte;

BOOL	IsExit(char* filename);

/*
 * return value:whether succ to get file modified time
 */
#ifdef WIN32
ULONG	GetFileTime(const char* fname, tm_zip* tmzip, ULONG *dt);
#else
ULONG	GetFileTime(const char* fname, tm_zip* tmzip);
#endif


int		GetFileCrc(const char* filenameinzip,void* buf,unsigned long size_buf,unsigned long* result_crc);

ENGINE_GLOBAL BOOL	ZipFile( LPCTSTR szZipName, LPCTSTR szFileToZip,int iOverWrite = 0 ,int iCompresssLevel = 0,LPCTSTR szPassword =NULL);
ENGINE_GLOBAL BOOL	ZipFolder(LPCSTR szZipName,LPCTSTR szFolder,int iOverWrite = 0 ,int iCompresssLevel = 0,LPCTSTR szPassword =NULL);

ENGINE_GLOBAL BOOL UnZipOneFile(LPCTSTR szZipName,LPCTSTR szUnzFileName,LPCTSTR szOutFileName = NULL,int iOverWrite = 1,LPCTSTR szPassword = NULL);
ENGINE_GLOBAL BOOL UnZipAllFile( LPCTSTR szZipName);

ENGINE_GLOBAL BOOL	ZipBufferToBuffer(byte* outBufeer,ULONG &uOutLen, byte* inBuffer,ULONG uInLen, int iCompressLevel = 0);
ENGINE_GLOBAL BOOL	UnZipBufferToBuffer(byte* outBufeer,ULONG &uOutLen, byte* inBuffer,ULONG uInLen);
ENGINE_GLOBAL ULONG	ComputeComSize(ULONG inSize);
