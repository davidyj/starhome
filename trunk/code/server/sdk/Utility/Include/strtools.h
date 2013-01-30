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
//		��������������
////////////////////
// �õ��ַ��������Ķ���
// ���ַ����м����������ָ����ָ�
// ע�⣺����������������ķָ���ʱ������Ϊ��һ���ָ���
// lpString		:	����ѯ���ַ���
// szChar		:	�ָ�����ȱʡ�Կո�ָ�
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

	// ���һ�εļ���
	if( length>0 && lpString[length-1]!=szChar )
	{
		SegmentCount++;	
	}
	return SegmentCount;
}
// �õ��ַ��������Ķ���
// ���ַ����м����������ָ����ָ�
// ע�⣺ÿ����һ���ָ������������һ���ַ���
// lpString		:	����ѯ���ַ���
// szChar		:	�ָ�����ȱʡ�Կո�ָ�
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

	// ���һ�εļ���
	if( length>0 && lpString[length-1]!=szChar )
	{
		SegmentCount++;	
	}
	return SegmentCount;
}

// �����ַ���
// ��Դ�ַ����е�ĳ�ε��ַ������е�Ŀ���ַ�����
// ע�⣺����������������ķָ���ʱ������Ϊ��һ���ָ���
// lpString		:	Դ�ַ���
// szString		:	Ŀ���ַ���
// nSize		:	Ŀ���ַ����ĳ��ȣ��������С��Ŀ���ַ���(szString)����ʵ���ȣ���������������
// nSegment		:	��Դ�ַ����ĵڼ��ηŵ�Ŀ���ַ�����
// szChar		:	�ָ�����ȱʡ�Կո�ָ�
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
		// �Ƿָ���
		if( lpString[nLoop] == szChar )
		{
			if( bGet == TRUE )
			{	// �Ѿ�������һ�Σ��ҵ�����Ҫ���ַ���
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
		// ����Ҫ����һ������
		if( SegmentCount == nSegment )
		{
			// ������
			if( nCharCount < nSize-1 )
			{
				szString[nCharCount] = lpString[nLoop];
				nCharCount++;
			}
			bGet = TRUE;
		}
		bNewSegment = FALSE;
	}
	// �ҵ��������һ��
	if( nCharCount > 0 )
	{
		szString[nCharCount] = '\0';
		nCharCount = 0;
		return TRUE;
	}
	// û���ҵ�
	return FALSE;
}
// �����ַ���
// ��Դ�ַ����е�ĳ�ε��ַ������е�Ŀ���ַ�����
// ע�⣺ÿ����һ���ָ������������һ���ַ���
// lpString		:	Դ�ַ���
// szString		:	Ŀ���ַ���
// nSize		:	Ŀ���ַ����ĳ��ȣ��������С��Ŀ���ַ���(szString)����ʵ���ȣ���������������
// nSegment		:	��Դ�ַ����ĵڼ��ηŵ�Ŀ���ַ�����
// szChar		:	�ָ�����ȱʡ�Կո�ָ�
	template< class T >
BOOL CutStringTable( const T *lpString, T *szString, int nSize, int nSegment, T szChar )
{
	int SegmentCount = 0;
	int length = T_strlen( lpString );
	int nCharCount = 0;
	BOOL bGet = FALSE;
	for ( int nLoop = 0; nLoop < length; nLoop++ )
	{
		// �Ƿָ���
		if( lpString[nLoop] == szChar )
		{
			if( bGet == TRUE )
			{	// �Ѿ�������һ�Σ��ҵ�����Ҫ���ַ���
				szString[nCharCount] = '\0';
				nCharCount=0;
				return TRUE;
			}
			SegmentCount++;
			continue;
		}
		// ����Ҫ����һ������
		if( SegmentCount == nSegment )
		{
			// ������
			if( nCharCount < nSize-1 )
			{
				szString[nCharCount] = lpString[nLoop];
				nCharCount++;
			}
			bGet = TRUE;
		}
	}
	// �ҵ��������һ��
	if( nCharCount > 0 )
	{
		szString[nCharCount] = '\0';
		nCharCount = 0;
		return TRUE;
	}
	// û���ҵ�
	return FALSE;
}

// �õ��ڼ����Ժ���ַ���
// lpString		:	Դ�ַ���
// szString		:	Ŀ���ַ���
// nSize		:	Ŀ���ַ����ĳ��ȣ��������С��Ŀ���ַ���(szString)����ʵ���ȣ���������������
// nSegment		:	��Դ�ַ����ĵڼ����Ժ�����ݷŵ�Ŀ���ַ�����
// szChar		:	�ָ�����ȱʡ�Կո�ָ�
	template< class T >
BOOL CutStringGetRemainEx( const T *lpString, int nSize, T *szString, int &nSize2, int nSegment, T szChar )
{
	int SegmentCount = 0;
	BOOL bNewSegment = TRUE;
	int length = nSize;
	int nCharCount = 0;
	for ( int nLoop = 0; nLoop < length; nLoop++ )
	{
		// �Ƿָ���
		if( lpString[nLoop] == szChar )
		{
			if( bNewSegment == FALSE )
			{
				SegmentCount++;
				bNewSegment = TRUE;
			}
			continue;
		}
		// ����Ҫ����һ������
		if( SegmentCount == nSegment )
		{
			// ������
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
	// �ҵ��������һ��
	nSize2 = nCharCount;
	if( nCharCount > 0 )
	{
		szString[nCharCount] = '\0';
		nCharCount = 0;
		return TRUE;
	}
	// û���ҵ�
	return FALSE;
}
	template< class T >
BOOL CutStringGetRemain( const T *lpString, T *szString, int nSize, int nSegment, T szChar )
{
	int length = T_strlen( lpString );
	return CutStringGetRemainEx( lpString, length, szString, nSize, nSegment, szChar );
}

// ���ַ���ת���ɴ�д(Windows��׼API���д��ຯ��:_strlwr, _strupr)
// make the string upper case
// str	:	string to be changed
void StrMakeUpper( char *str );

// Find sub string in a given string
// ��һ���ַ������ҵ���һ���ַ���(Windows��׼API���д��ຯ��:_strstr)
// mystring		:	�����ҵ��ַ���
// mysubstring	:	Ҫ���ҵ��ַ���
// returns		:	�ҵ�ʱ��һ����ĸ��λ�ã�-1ʧ��
int FindSubString( char *mystring, char *mysubstring );
////////////////////

// strdupa
char *SStrDupA( const char * string );

////////////////////
//----------------File Name Functions-----------------
//		�ļ���������
////////////////////
// ��ȥ�ļ�·��
// fullname :	��ʼ�ļ���
// newname	:	��ȥ·�����ļ���
// nSize	:	��ȥ·�����ļ����ĳ��ȣ����С������ַ������ڶ�������������ʵ���ȣ���������������
// index	:	����ʣ�¼���,Ϊ0��ֻ���ļ���,Ϊ1����һ��·��,Ϊ2��������·����С��0�����·���Ĳ�����Ч
void MakeNakedNameIndex( const char *fullname, char *newname, int nSize, int index );

// ��ȥ�ļ���,ֻʣ��·��
// fullname	:	��ȥֻʣ��·�����ļ���
// nSize		:	��ȥ·�����ļ����ĳ��ȣ����С������ַ������ڶ�������������ʵ���ȣ���������������
void MakeNakedPath( const char *fullname, char *pathname, int nSize );

// �õ��ļ���ǰ׺��û�к�׺
// get a filename's name, without extension
// filename	:	assumed to be a valid filename, that the last 3 characters are extension
// noext	:	filename without extension
// nSize	:	��ȥ·�����ļ����ĳ��ȣ����С������ַ������ڶ�������������ʵ���ȣ���������������
void GetFileNameNoExt( const char *filename, char *noext, int nSize );

// �õ��ļ�����׺
// get a filename's extension
// filename	:	assumed to be a valid filename, that the last 3 characters are extension
// ext		:	extension of the filename
// nSize	:	�õ��ĺ�׺����󳤶ȣ����С������ַ������ڶ�������������ʵ���ȣ���������������
void GetFileNameExt( const char *filename, char *ext, int nSize );
////////////////////

// �ַ�������ƥ����
BOOL StrPartCmp( const wchar_t * target, const wchar_t * input );

//�ַ������� ����
void Encrypt(char*   cSrc,char*   cDest);   
void Decrypt(char*   cSrc,char*   cDest);  
