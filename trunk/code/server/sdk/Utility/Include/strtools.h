//=========== (C) Copyright 1999 Valve, L.L.C. All rights reserved. ===========
//
// The copyright to the contents herein is the property of Valve, L.L.C.
// The contents may be used and/or copied only with the written permission of
// Valve, L.L.C., or in accordance with the terms and conditions stipulated in
// the agreement/contract under which the contents have been supplied.
//
// $Header: $
// $NoKeywords: $
//
// Contains string tools somehow missing from CRT
//=============================================================================
#pragma warning(disable:4005)
#pragma once
#ifndef WIN32
#include <ctype.h>
#endif

#include <string.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------
// Portable versions of standard string functions
//-----------------------------------------------------------------------------
void	_Q_memset (const char* file, int line, void *dest, int fill, int count);
void	_Q_memcpy (const char* file, int line, void *dest, const void *src, int count);
void	_Q_memmove(const char* file, int line, void *dest, const void *src, int count);
int		_Q_memcmp (const char* file, int line, void *m1, void *m2, int count);
int		_Q_strlen (const char* file, int line, const char *str);
void	_Q_strcpy (const char* file, int line, char *dest, const char *src);
char*	_Q_strrchr (const char* file, int line, const char *s, char c);
int		_Q_strcmp (const char* file, int line, const char *s1, const char *s2);
int		_Q_stricmp( const char* file, int line, const char *s1, const char *s2 );
char*	_Q_strstr( const char* file, int line, const char *s1, const char *search );
char*	_Q_strupr (const char* file, int line, char *start);
char*	_Q_strlower (const char* file, int line, char *start);
int		_Q_strlcpy(const char* file,int line,char* dest,int destsize,const char* src);


#ifdef _DEBUG

#define Q_memset(dest, fill, count)		_Q_memset   (__FILE__, __LINE__, (dest), (fill), (count))	
#define Q_memcpy(dest, src, count)		_Q_memcpy	(__FILE__, __LINE__, (dest), (src), (count))	
#define Q_memmove(dest, src, count)		_Q_memmove	(__FILE__, __LINE__, (dest), (src), (count))	
#define Q_memcmp(m1, m2, count)			_Q_memcmp	(__FILE__, __LINE__, (m1), (m2), (count))		
#define Q_strlen(str)					_Q_strlen	(__FILE__, __LINE__, (str))				
#define Q_strcpy(dest, src)				_Q_strcpy	(__FILE__, __LINE__, (dest), (src))			
#define Q_strrchr(s, c)					_Q_strrchr	(__FILE__, __LINE__, (s), (c))				
#define Q_strcmp(s1, s2)				_Q_strcmp	(__FILE__, __LINE__, (s1), (s2))			
#define Q_stricmp(s1, s2 )				_Q_stricmp	(__FILE__, __LINE__, (s1), (s2) )			
#define Q_strstr(s1, search )			_Q_strstr	(__FILE__, __LINE__, (s1), (search) )		
#define Q_strupr(start)					_Q_strupr	(__FILE__, __LINE__, (start))				
#define Q_strlower(start)				_Q_strlower (__FILE__, __LINE__, (start))			
#define Q_strlcpy(dest,destsize,src)	_Q_strlcpy	(__FILE__, __LINE__,(dest),(destsize),(src));
#ifdef WIN32
inline char *strupr( char *start )
{
	char *str = start;
	while( str && *str )
	{
		*str = (char)toupper(*str);
		str++;
	}
	return start;
}
#endif
#else
#pragma warning(push)
#pragma warning(disable:4267)
#define Q_memset(dest, fill, count)		_Q_memset   (__FILE__, __LINE__, (dest), (fill), (count))	
#define Q_memcpy(dest, src, count)		_Q_memcpy	(__FILE__, __LINE__, (dest), (src), (count))	
#define Q_memmove(dest, src, count)		_Q_memmove	(__FILE__, __LINE__, (dest), (src), (count))	
#define Q_memcmp(m1, m2, count)			_Q_memcmp	(__FILE__, __LINE__, (m1), (m2), (count))		
#define Q_strlen(str)					_Q_strlen	(__FILE__, __LINE__, (str))				
#define Q_strcpy(dest, src)				_Q_strcpy	(__FILE__, __LINE__, (dest), (src))			
#define Q_strrchr(s, c)					_Q_strrchr	(__FILE__, __LINE__, (s), (c))				
#define Q_strcmp(s1, s2)				_Q_strcmp	(__FILE__, __LINE__, (s1), (s2))			
#define Q_stricmp(s1, s2 )				_Q_stricmp	(__FILE__, __LINE__, (s1), (s2) )			
#define Q_strstr(s1, search )			_Q_strstr	(__FILE__, __LINE__, (s1), (search) )		
#define Q_strupr(start)					_Q_strupr	(__FILE__, __LINE__, (start))				
#define Q_strlower(start)				_Q_strlower (__FILE__, __LINE__, (start))			
#define Q_strlcpy(dest,destsize,src)	_Q_strlcpy	(__FILE__, __LINE__,(dest),(destsize),(src));
#ifdef WIN32
inline char *strupr( char *start )
{
	char *str = start;
	while( str && *str )
	{
		*str = (char)toupper(*str);
		str++;
	}
	return start;
}
#endif
#pragma warning(pop)

#endif

int	Q_strncmp (const char *s1, const char *s2, int count);
void Q_strcat (char *dest, const char *src);
int	Q_strcasecmp (const char *s1, const char *s2);
int	Q_strncasecmp (const char *s1, const char *s2, int n);
int	Q_strnicmp (const char *s1, const char *s2, int n);
int	Q_atoi (const char *str);
float Q_atof (const char *str);
char* Q_stristr( char* pStr, char const* pSearch );
char const*	Q_stristr( char const* pStr, char const* pSearch );


// These are versions of functions that guarantee null termination.
//
// maxLen is the maximum number of bytes in the destination string.
// pDest[maxLen-1] is always null terminated if pSrc's length is >= maxLen.
//
// This means the last parameter can usually be a sizeof() of a string.
void Q_strncpy( char *pDest, char const *pSrc, int maxLen );
int Q_snprintf( char *pDest, int destLen, char const *pFormat, ... );
char *Q_strncat(char *, const char *, size_t);
char *Q_strnlwr(char *, size_t);


// UNDONE: Find a non-compiler-specific way to do this
#ifdef _VA_LIST_DEFINED
int Q_vsnprintf( char *pDest, int maxLen, char const *pFormat, va_list params );
#endif

// Prints out a pretified memory counter string value ( e.g., 7,233.27 Mb, 1,298.003 Kb, 127 bytes )

char *Q_pretifymem( float value, int digitsafterdecimal = 2, bool usebinaryonek = false );

void WideCharToChar( const wchar_t * lpSrc, char * lpDst, int nMax );
void CharToWideChar( const char * lpSrc, wchar_t * lpDst, int nMax );

BOOL IsNumber( const char * szNumber );
BOOL IsNumber( const wchar_t * szNumber );

	template< class T >
int T_strlen( T * pString )
{
	int nCount = 0;
	while( *pString )
	{
		nCount++;
		pString++;
	}
	return nCount;
}

/////////////////////////////////////////////////
////////////////////
//----------------Function parameter Functions-----------------
//		函数参数处理函数
////////////////////
// 得到字符串包含的段数
// 该字符串中间以任意多个分隔符分隔
// 注意：当有连续多个连续的分隔符时，被认为是一个分隔符
// lpString		:	被查询的字符串
// szChar		:	分隔符，缺省以空格分隔
	template< class T >
int GetSegmentCount( const T *lpString, T szChar )
{
	int SegmentCount = 0;
	int length = T_strlen( lpString );
	BOOL bNewSegment = TRUE;
	for ( int nLoop = 0; nLoop < length; nLoop++ )
	{
		if ( lpString[nLoop] == szChar )
		{
			if( bNewSegment == FALSE )
			{
				SegmentCount++;
				bNewSegment = TRUE;
			}
			continue;
		}
		else
		{
			bNewSegment = FALSE;
		}
	}

	// 最后一段的计数
	if( length>0 && lpString[length-1]!=szChar )
	{
		SegmentCount++;	
	}
	return SegmentCount;
}
// 得到字符串包含的段数
// 该字符串中间以任意多个分隔符分隔
// 注意：每出现一个分隔符，就是输出一个字符串
// lpString		:	被查询的字符串
// szChar		:	分隔符，缺省以空格分隔
	template< class T >
int GetSegmentCountTable( const T *lpString, T szChar )
{
	int SegmentCount = 0;
	int length = T_strlen( lpString );
	for ( int nLoop = 0; nLoop < length; nLoop++ )
	{
		if ( lpString[nLoop] == szChar )
		{
			SegmentCount++;
			continue;
		}
	}

	// 最后一段的计数
	if( length>0 && lpString[length-1]!=szChar )
	{
		SegmentCount++;	
	}
	return SegmentCount;
}

// 剪切字符串
// 把源字符串中第某段的字符串剪切到目的字符串中
// 注意：当有连续多个连续的分隔符时，被认为是一个分隔符
// lpString		:	源字符串
// szString		:	目的字符串
// nSize		:	目的字符串的长度，如果长度小于目的字符串(szString)的真实长度，则会出现致命错误
// nSegment		:	将源字符串的第几段放到目的字符串中
// szChar		:	分隔符，缺省以空格分隔
	template< class T >
BOOL CutString( const T *lpString, T *szString, int nSize, int nSegment, T szChar )
{
	int SegmentCount = 0;
	BOOL bNewSegment = TRUE;
	int length = T_strlen( lpString );
	int nCharCount = 0;
	BOOL bGet = FALSE;
	for ( int nLoop = 0; nLoop < length; nLoop++ )
	{
		// 是分隔符
		if( lpString[nLoop] == szChar )
		{
			if( bGet == TRUE )
			{	// 已经到了下一段，找到了想要的字符串
				szString[nCharCount] = '\0';
				nCharCount=0;
				return TRUE;
			}
			if( bNewSegment == FALSE )
			{
				SegmentCount++;
				bNewSegment = TRUE;
			}
			continue;
		}
		// 是想要的那一段内容
		if( SegmentCount == nSegment )
		{
			// 不超界
			if( nCharCount < nSize-1 )
			{
				szString[nCharCount] = lpString[nLoop];
				nCharCount++;
			}
			bGet = TRUE;
		}
		bNewSegment = FALSE;
	}
	// 找到的是最后一段
	if( nCharCount > 0 )
	{
		szString[nCharCount] = '\0';
		nCharCount = 0;
		return TRUE;
	}
	// 没有找到
	return FALSE;
}
// 剪切字符串
// 把源字符串中第某段的字符串剪切到目的字符串中
// 注意：每出现一个分隔符，就是输出一个字符串
// lpString		:	源字符串
// szString		:	目的字符串
// nSize		:	目的字符串的长度，如果长度小于目的字符串(szString)的真实长度，则会出现致命错误
// nSegment		:	将源字符串的第几段放到目的字符串中
// szChar		:	分隔符，缺省以空格分隔
	template< class T >
BOOL CutStringTable( const T *lpString, T *szString, int nSize, int nSegment, T szChar )
{
	int SegmentCount = 0;
	int length = T_strlen( lpString );
	int nCharCount = 0;
	BOOL bGet = FALSE;
	for ( int nLoop = 0; nLoop < length; nLoop++ )
	{
		// 是分隔符
		if( lpString[nLoop] == szChar )
		{
			if( bGet == TRUE )
			{	// 已经到了下一段，找到了想要的字符串
				szString[nCharCount] = '\0';
				nCharCount=0;
				return TRUE;
			}
			SegmentCount++;
			continue;
		}
		// 是想要的那一段内容
		if( SegmentCount == nSegment )
		{
			// 不超界
			if( nCharCount < nSize-1 )
			{
				szString[nCharCount] = lpString[nLoop];
				nCharCount++;
			}
			bGet = TRUE;
		}
	}
	// 找到的是最后一段
	if( nCharCount > 0 )
	{
		szString[nCharCount] = '\0';
		nCharCount = 0;
		return TRUE;
	}
	// 没有找到
	return FALSE;
}

// 得到第几段以后的字符串
// lpString		:	源字符串
// szString		:	目的字符串
// nSize		:	目的字符串的长度，如果长度小于目的字符串(szString)的真实长度，则会出现致命错误
// nSegment		:	将源字符串的第几段以后的内容放到目的字符串中
// szChar		:	分隔符，缺省以空格分隔
	template< class T >
BOOL CutStringGetRemainEx( const T *lpString, int nSize, T *szString, int &nSize2, int nSegment, T szChar )
{
	int SegmentCount = 0;
	BOOL bNewSegment = TRUE;
	int length = nSize;
	int nCharCount = 0;
	for ( int nLoop = 0; nLoop < length; nLoop++ )
	{
		// 是分隔符
		if( lpString[nLoop] == szChar )
		{
			if( bNewSegment == FALSE )
			{
				SegmentCount++;
				bNewSegment = TRUE;
			}
			continue;
		}
		// 是想要的那一段内容
		if( SegmentCount == nSegment )
		{
			// 不超界
			if( nSize2 > (length-nLoop) )
			{
				nSize2 = length-nLoop;
			}
			for( nCharCount=0; nCharCount<nSize2; nCharCount++ )
			{
				szString[nCharCount] = lpString[nLoop+nCharCount];
			}
			break;
		}
		bNewSegment = FALSE;
	}
	// 找到的是最后一段
	nSize2 = nCharCount;
	if( nCharCount > 0 )
	{
		szString[nCharCount] = '\0';
		nCharCount = 0;
		return TRUE;
	}
	// 没有找到
	return FALSE;
}
	template< class T >
BOOL CutStringGetRemain( const T *lpString, T *szString, int nSize, int nSegment, T szChar )
{
	int length = T_strlen( lpString );
	return CutStringGetRemainEx( lpString, length, szString, nSize, nSegment, szChar );
}

// 把字符串转换成大写(Windows标准API中有此类函数:_strlwr, _strupr)
// make the string upper case
// str	:	string to be changed
void StrMakeUpper( char *str );

// Find sub string in a given string
// 在一个字符串中找到另一个字符串(Windows标准API中有此类函数:_strstr)
// mystring		:	被查找的字符串
// mysubstring	:	要查找的字符串
// returns		:	找到时第一个字母的位置，-1失败
int FindSubString( char *mystring, char *mysubstring );
////////////////////

// strdupa
char *SStrDupA( const char * string );

////////////////////
//----------------File Name Functions-----------------
//		文件名处理函数
////////////////////
// 剥去文件路径
// fullname :	初始文件名
// newname	:	剥去路径的文件名
// nSize	:	剥去路径的文件名的长度，如果小于输出字符串（第二个参数）的真实长度，则会出现致命错误
// index	:	剥到剩下几层,为0是只有文件名,为1是有一层路径,为2是有两层路径，小于0或多于路径的层数无效
void MakeNakedNameIndex( const char *fullname, char *newname, int nSize, int index );

// 剥去文件名,只剩下路径
// fullname	:	剥去只剩下路径的文件名
// nSize		:	剥去路径的文件名的长度，如果小于输出字符串（第二个参数）的真实长度，则会出现致命错误
void MakeNakedPath( const char *fullname, char *pathname, int nSize );

// 得到文件名前缀，没有后缀
// get a filename's name, without extension
// filename	:	assumed to be a valid filename, that the last 3 characters are extension
// noext	:	filename without extension
// nSize	:	剥去路径的文件名的长度，如果小于输出字符串（第二个参数）的真实长度，则会出现致命错误
void GetFileNameNoExt( const char *filename, char *noext, int nSize );

// 得到文件名后缀
// get a filename's extension
// filename	:	assumed to be a valid filename, that the last 3 characters are extension
// ext		:	extension of the filename
// nSize	:	得到的后缀的最大长度，如果小于输出字符串（第二个参数）的真实长度，则会出现致命错误
void GetFileNameExt( const char *filename, char *ext, int nSize );
////////////////////

// 字符串部分匹配检测
BOOL StrPartCmp( const wchar_t * target, const wchar_t * input );

//字符串加密 解密
void Encrypt(char*   cSrc,char*   cDest);   
void Decrypt(char*   cSrc,char*   cDest);  
