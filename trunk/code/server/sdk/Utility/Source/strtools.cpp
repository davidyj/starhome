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

// These are redefined in the project settings to prevent anyone from using them.
// We in this module are of a higher caste and thus are privileged in their use.

// NOTE: I have to include stdio + stdarg first so vsnprintf gets compiled in
#include "../stdafx.h"		// for WideCharToMultiByte and MultiByteToWideChar

#include <stdio.h>
#include <stdarg.h>

#ifndef WIN32
#include <ctype.h>
#include <wchar.h>
#endif

#include "CommDef.h"
#include "dbg.h"
#include "strtools.h"
#include <string.h>
#include <stdlib.h>
//#include "utldict.h"

void _Q_memset (const char* file, int line, void *dest, int fill, int count)
{
	Assert( count >= 0 );
	AssertValidWritePtr( dest, count );

	memset(dest,fill,count);
}

void _Q_memcpy (const char* file, int line, void *dest, const void *src, int count)
{
	Assert( count >= 0 );
	AssertValidReadPtr( src, count );
	AssertValidWritePtr( dest, count );

	memcpy( dest, src, count );
}

void _Q_memmove(const char* file, int line, void *dest, const void *src, int count)
{
	Assert( count >= 0 );
	AssertValidReadPtr( src, count );
	AssertValidWritePtr( dest, count );

	memmove( dest, src, count );
}

int _Q_memcmp (const char* file, int line, void *m1, void *m2, int count)
{
	Assert( count >= 0 );
	AssertValidReadPtr( m1, count );
	AssertValidReadPtr( m2, count );

	return memcmp( m1, m2, count );
}

int _Q_strlen (const char* file, int line, const char *str)
{
	AssertValidStringPtr(str);
	return strlen( str );
}

void _Q_strcpy (const char* file, int line, char *dest, const char *src)
{
	AssertValidWritePtr(dest);
	AssertValidStringPtr(src);	

	strcpy( dest, src );	
}

char *_Q_strrchr(const char* file, int line, const char *s, char c)
{
	AssertValidStringPtr( s );
    int len = Q_strlen(s);
    s += len;
    while (len--)
	if (*--s == c) return (char *)s;
    return 0;
}

int _Q_strcmp (const char* file, int line, const char *s1, const char *s2)
{
	AssertValidStringPtr( s1 );
	AssertValidStringPtr( s2 );

	while (1)
	{
		if (*s1 != *s2)
			return -1;              // strings not equal    
		if (!*s1)
			return 0;               // strings are equal
		s1++;
		s2++;
	}
	
	return -1;
}

int	_Q_stricmp(const char* file, int line,  const char *s1, const char *s2 )
{
	AssertValidStringPtr( s1 );
	AssertValidStringPtr( s2 );

	return stricmp( s1, s2 );
}


char *_Q_strstr(const char* file, int line,  const char *s1, const char *search )
{
	AssertValidStringPtr( s1 );
	AssertValidStringPtr( search );

	return (char *)strstr( s1, search );
}

char *_Q_strupr (const char* file, int line, char *start)
{
	AssertValidStringPtr( start );
	return strupr( start );
}


char *_Q_strlower (const char* file, int line, char *start)
{
	AssertValidStringPtr( start );
	return strlwr(start);
}

int _Q_strlcpy(const char* file,int line,char* dest,int destsize,const char* src)
{
#ifdef WIN32
	return strcpy_s(dest,destsize,src);
#else
	return strlcpy(dest,destsize,src);
#endif
}



void Q_strcat (char *dest, const char *src)
{
	AssertValidStringPtr(dest);
	AssertValidStringPtr(src);

	dest += Q_strlen(dest);
	Q_strcpy (dest, src);
} 

int Q_strncmp (const char *s1, const char *s2, int count)
{
	Assert( count >= 0 );
	AssertValidStringPtr( s1, count );
	AssertValidStringPtr( s2, count );

	while (1)
	{
		if (!count--)
			return 0;
		if (*s1 != *s2)
			return -1;              // strings not equal    
		if (!*s1)
			return 0;               // strings are equal
		s1++;
		s2++;
	}
	
	return -1;
}

char *Q_strnlwr(char *s, size_t count)
{
	Assert( count >= 0 );
	AssertValidStringPtr( s, count );

	char* pRet = s;
	if (!s)
		return s;

	while (--count >= 0)
	{
		if (!*s)
			break;

		*s = tolower(*s);
		++s;
	}

	return pRet;
}


int Q_strncasecmp (const char *s1, const char *s2, int n)
{
	Assert( n >= 0 );
	AssertValidStringPtr( s1 );
	AssertValidStringPtr( s2 );

	int             c1, c2;
	
	while (1)
	{
		c1 = *s1++;
		c2 = *s2++;

		if (!n--)
			return 0;               // strings are equal until end point
		
		if (c1 != c2)
		{
			if (c1 >= 'a' && c1 <= 'z')
				c1 -= ('a' - 'A');
			if (c2 >= 'a' && c2 <= 'z')
				c2 -= ('a' - 'A');
			if (c1 != c2)
				return -1;              // strings not equal
		}
		if (!c1)
			return 0;               // strings are equal
//              s1++;
//              s2++;
	}
	
	return -1;
}

int Q_strcasecmp (const char *s1, const char *s2)
{
	AssertValidStringPtr(s1);
	AssertValidStringPtr(s2);

	return Q_strncasecmp (s1, s2, 99999);
}

int Q_strnicmp (const char *s1, const char *s2, int n)
{
	Assert( n >= 0 );
	AssertValidStringPtr(s1);
	AssertValidStringPtr(s2);

	return Q_strncasecmp( s1, s2, n );
}

int Q_atoi (const char *str)
{
	AssertValidStringPtr( str );

	int             val;
	int             sign;
	int             c;
	
	Assert( str );
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else
		sign = 1;
		
	val = 0;

//
// check for hex
//
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X') )
	{
		str += 2;
		while (1)
		{
			c = *str++;
			if (c >= '0' && c <= '9')
				val = (val<<4) + c - '0';
			else if (c >= 'a' && c <= 'f')
				val = (val<<4) + c - 'a' + 10;
			else if (c >= 'A' && c <= 'F')
				val = (val<<4) + c - 'A' + 10;
			else
				return val*sign;
		}
	}
	
//
// check for character
//
	if (str[0] == '\'')
	{
		return sign * str[1];
	}
	
//
// assume decimal
//
	while (1)
	{
		c = *str++;
		if (c <'0' || c > '9')
			return val*sign;
		val = val*10 + c - '0';
	}
	
	return 0;
}


float Q_atof (const char *str)
{
	AssertValidStringPtr( str );
	double			val;
	int             sign;
	int             c;
	int             decimal, total;
	
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else
		sign = 1;
		
	val = 0;

//
// check for hex
//
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X') )
	{
		str += 2;
		while (1)
		{
			c = *str++;
			if (c >= '0' && c <= '9')
				val = (val*16) + c - '0';
			else if (c >= 'a' && c <= 'f')
				val = (val*16) + c - 'a' + 10;
			else if (c >= 'A' && c <= 'F')
				val = (val*16) + c - 'A' + 10;
			else
				return val*sign;
		}
	}
	
//
// check for character
//
	if (str[0] == '\'')
	{
		return sign * str[1];
	}
	
//
// assume decimal
//
	decimal = -1;
	total = 0;
	while (1)
	{
		c = *str++;
		if (c == '.')
		{
			decimal = total;
			continue;
		}
		if (c <'0' || c > '9')
			break;
		val = val*10 + c - '0';
		total++;
	}

	if (decimal == -1)
		return val*sign;
	while (total > decimal)
	{
		val /= 10;
		total--;
	}
	
	return val*sign;
}




//-----------------------------------------------------------------------------
// Finds a string in another string with a case insensitive test
//-----------------------------------------------------------------------------

char const* Q_stristr( char const* pStr, char const* pSearch )
{
	AssertValidStringPtr(pStr);
	AssertValidStringPtr(pSearch);

	if (!pStr || !pSearch) 
		return 0;

	char const* pLetter = pStr;

	// Check the entire string
	while (*pLetter != 0)
	{
		// Skip over non-matches
		if (tolower(*pLetter) == tolower(*pSearch))
		{
			// Check for match
			char const* pMatch = pLetter + 1;
			char const* pTest = pSearch + 1;
			while (*pTest != 0)
			{
				// We've run off the end; don't bother.
				if (*pMatch == 0)
					return 0;

				if (tolower(*pMatch) != tolower(*pTest))
					break;

				++pMatch;
				++pTest;
			}

			// Found a match!
			if (*pTest == 0)
				return pLetter;
		}

		++pLetter;
	}

	return 0;
}

char* Q_stristr( char* pStr, char const* pSearch )
{
	AssertValidStringPtr( pStr );
	AssertValidStringPtr( pSearch );

	return (char*)Q_stristr( (char const*)pStr, pSearch );
}


void Q_strncpy( char *pDest, char const *pSrc, int maxLen )
{
	Assert( maxLen >= 0 );
	AssertValidWritePtr( pDest, maxLen );
	AssertValidStringPtr( pSrc );

	strncpy( pDest, pSrc, maxLen );
	if( maxLen )
		pDest[maxLen-1] = 0;
}


int Q_snprintf( char *pDest, int maxLen, char const *pFormat, ... )
{
	Assert( maxLen >= 0 );
	AssertValidWritePtr( pDest, maxLen );
	AssertValidStringPtr( pFormat );

#ifdef FREEBSD
	const char* bit64 = "I64";
	const int   formatlen = strlen(pFormat);
	char pTempFormat[1024] ={0};
	int tfidx = 0;

	for( int mfidx=0; mfidx<formatlen; mfidx++ )
	{
		pTempFormat[tfidx++] = pFormat[mfidx];

		if( '%' == pFormat[mfidx] )
		{
			int bit64idx = 0;
			int scanidx = mfidx + 1;

			for( ; bit64idx<3; bit64idx++ )
			{
				if( scanidx >= formatlen ) { break; }
				if( bit64[bit64idx] != pFormat[scanidx] ) { break; }
				scanidx++;
			}

			if( bit64idx == 3 )
			{
				memcpy( pTempFormat+tfidx, "ll", 2 );
				tfidx += 2;
				mfidx += 3;
			}
		}
	}
	pTempFormat[tfidx] = '\0';
#endif

	va_list marker;

	va_start( marker, pFormat );
#ifdef WIN32	
	int len = _vsnprintf( pDest, maxLen, pFormat, marker );
#else
	int len = vsnprintf( pDest, maxLen, pTempFormat, marker );
#endif	
	va_end( marker );

	// Len < 0 represents an overflow
	if( len < 0 )
	{
		len = maxLen;
		pDest[maxLen-1] = 0;
	}

	return len;
}

int Q_vsnprintf( char *pDest, int maxLen, char const *pFormat, va_list params )
{
	Assert( maxLen >= 0 );
	AssertValidWritePtr( pDest, maxLen );
	AssertValidStringPtr( pFormat );
#ifdef WIN32
	int len = _vsnprintf( pDest, maxLen, pFormat, params );
#else
	int len = vsnprintf( pDest, maxLen, pFormat, params );
#endif	
	if( len < 0 )
	{
		len = maxLen;
		pDest[maxLen-1] = 0;
	}

	return len;
}



char *Q_strncat(char *pDest, const char *pSrc, size_t maxLen)
{
	Assert( maxLen >= 0 );
	AssertValidStringPtr( pDest);
	AssertValidStringPtr( pSrc );
	
	int len = strlen(pDest);
	maxLen = (maxLen - 1) - len;
	
	if ( maxLen <= 0 )
		return pDest;

	char *pOut = strncat( pDest, pSrc, maxLen );
	pOut[len + maxLen] = 0;
	return pOut;
}



//-----------------------------------------------------------------------------
// Purpose: Converts value into x.xx MB/ x.xx KB, x.xx bytes format, including commas
// Input  : value - 
//			2 - 
//			false - 
// Output : char
//-----------------------------------------------------------------------------
#define NUM_PRETIFYMEM_BUFFERS 8
char *Q_pretifymem( float value, int digitsafterdecimal /*= 2*/, bool usebinaryonek /*= false*/ )
{
	static char output[ NUM_PRETIFYMEM_BUFFERS ][ 32 ];
	static int  current;

	float		onekb = usebinaryonek ? 1024.0f : 1000.0f;
	float		onemb = onekb * onekb;

	char *out = output[ current ];
	current = ( current + 1 ) & ( NUM_PRETIFYMEM_BUFFERS -1 );

	char suffix[ 8 ];

	// First figure out which bin to use
	if ( value > onemb )
	{
		value /= onemb;
		sprintf( suffix, " Mb" );
	}
	else if ( value > onekb )
	{
		value /= onekb;
		sprintf( suffix, " Kb" );
	}
	else
	{
		sprintf( suffix, " bytes" );
	}

	char val[ 32 ];

	// Clamp to >= 0
//	digitsafterdecimal = max(digitsafterdecimal, 0);
	if (digitsafterdecimal < 0)
		digitsafterdecimal = 0;

	// If it's basically integral, don't do any decimals
	if ( FloatMakePositive( value - (int)value ) < 0.00001 )
	{
		sprintf( val, "%i%s", (int)value, suffix );
	}
	else
	{
		char fmt[ 32 ];

		// Otherwise, create a format string for the decimals
		sprintf( fmt, "%%.%if%s", digitsafterdecimal, suffix );
		sprintf( val, fmt, value );
	}

	// Copy from in to out
	char *i = val;
	char *o = out;

	// Search for decimal or if it was integral, find the space after the raw number
	char *dot = strstr( i, "." );
	if ( !dot )
	{
		dot = strstr( i, " " );
	}

	// Compute position of dot
	int pos = dot - i;
	// Don't put a comma if it's <= 3 long
	pos -= 3;

	while ( *i )
	{
		// If pos is still valid then insert a comma every third digit, except if we would be
		//  putting one in the first spot
		if ( pos >= 0 && !( pos % 3 ) )
		{
			// Never in first spot
			if ( o != out )
			{
				*o++ = ',';
			}
		}

		// Count down comma position
		pos--;

		// Copy rest of data as normal
		*o++ = *i++;
	}

	// Terminate
	*o = 0;

	return out;
}



/////////////////////////////////////////////////
////////////////////
//----------------Function parameter Functions-----------------
////////////////////
// 得到字符串包含的段数
// 该字符串中间以任意多个分隔符分隔
// lpString		:	被查询的字符串
// szChar		:	分隔符，缺省以空格分隔
int GetSegmentCount( const char *lpString, char szChar/*=' '*/ )
{
	int SegmentCount = 0;
	int length = strlen ( lpString );
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
int GetSegmentCountTable( const char *lpString, char szChar ) // =' ' )
{
	int SegmentCount = 0;
	int length = strlen ( lpString );
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
// lpString		:	源字符串
// szString		:	目的字符串
// nSize		:	目的字符串的长度，如果长度小于目的字符串(szString)的真实长度，则会出现致命错误
// nSegment		:	将源字符串的第几段放到目的字符串中，从0开始记数
// szChar		:	分隔符，缺省以空格分隔
BOOL CutString( const char *lpString, char *szString, int nSize, int nSegment, char szChar/* = ' '*/ )
{
	int SegmentCount = 0;
	BOOL bNewSegment = TRUE;
	int length = strlen ( lpString );
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
BOOL CutStringTable( const char *lpString, char *szString, int nSize, int nSegment, char szChar ) // = ' ' )
{
	int SegmentCount = 0;
	int length = strlen ( lpString );
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
BOOL CutStringGetRemain( const char *lpString, char *szString, int nSize, int nSegment, char szChar ) //= ' ' )
{
	int length = strlen ( lpString );
	return CutStringGetRemainEx( lpString, length, szString, nSize, nSegment, szChar );
}

BOOL CutStringGetRemainEx( const char *lpString, int nSize, char *szString, int& nSize2, int nSegment, char szChar ) // = ' ' )
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

// 把字符串转换成大写(Windows标准API中有此类函数:_strlwr, _strupr)
// make the string upper case
// str	:	string to be changed
void StrMakeUpper( char *str )
{
	_strupr( str );
	return;
	int length = strlen( str );
	for( int i=0; i<length; i++ )
	{
		if( str[i]>=97 && str[i] < 123 )
		{
			str[i] -= 32;
		}
	}
}

// Find sub string in a given string
// 在一个字符串中找到另一个字符串(Windows标准API中有此类函数:_strstr)
// mystring		:	被查找的字符串
// mysubstring	:	要查找的字符串
// returns		:	找到时第一个字母的位置，-1失败
int FindSubString( char *mystring, char *mysubstring )
{
	int i, j;
	int nLen = strlen( mystring );
	int nSubLen = strlen( mysubstring );
	int nFindCount = 0;
	int nFind = -1;
	char *string=NULL;
	char *substring=NULL;
	
	string = _strlwr( mystring );
	substring = _strlwr( mysubstring );
	for( i=0; i<nLen; i++ )
	{
		if( string[i] == substring[0] )
		{
			nFindCount = 0;
			for( j=0; j<nSubLen; j++ )
			{
				if( string[i+j] == substring[j] )
				{
					nFindCount++;
				}
			}
			if( nFindCount == nSubLen )
			{
				nFind = i;
			}
		}
		if( nFind >= 0 )
			break;
	}
	return nFind;
}
////////////////////
char *SStrDupA( const char * string )
{
	if ( !string  )
		return NULL;

	int nCount = strlen( string );
	char *dupstring = new char[nCount+1];
	strcpy( dupstring, string );
	return NULL;
}

////////////////////
//----------------File Name Functions-----------------
////////////////////
// 剥去文件路径
// fullname :	初始文件名
// newname	:	剥去路径的文件名
// nSize	:	剥去路径的文件名的长度，如果小于输出字符串（第二个参数）的真实长度，则会出现致命错误
// index	:	剥到剩下几层,为0是只有文件名,为1是有一层路径,为2是有两层路径，小于0或多于路径的层数无效
void MakeNakedNameIndex( const char *fullname, char *newname, int nSize, int index )
{
	int i;
	int begin = -1;
	int len = strlen( fullname );
	int counter = 0;

	Assert( index >= 0 );
	for( i=len-1; i>=0; i-- )
	{
		if( fullname[i] == '\\' || fullname[i] == '/' )
		{
			if( counter == index )
			{
				begin = i;
				break;
			}
			counter++;
		}
	}

	int nCount = 0;
	for( i = begin+1; i<len; i++ )
	{
		if( nCount < nSize-1 )
		{
			newname[i-begin-1] = fullname[i];
			nCount++;
		}
	}
	if( nCount > 0 )
	{
		newname[nCount] = '\0';
	}
}	// End of MakeNakedNameIndex()

// 剥去文件名,只剩下路径
// fullname	:	剥去只剩下路径的文件名
// nSize		:	剥去路径的文件名的长度，如果小于输出字符串（第二个参数）的真实长度，则会出现致命错误
void MakeNakedPath( const char *fullname, char *pathname, int nSize )
{
	int i;
	int begin = -1;
	int len = strlen( fullname );
	for( i=len-1; i>=0; i-- )
	{
		if( fullname[i] == '\\' || fullname[i] == '/' )
		{
			begin = i;
			break;
		}
	}
	if( begin< 0 )
	{
		return;
	}

	if( nSize-1 < begin+1 ) begin = nSize-2;
	for( i = 0; i< begin+1; i++ )
	{
		pathname[i] = fullname[i];
	}
	pathname[i] = 0;
}	// End of MakeNakedPath()

// 得到文件名前缀，没有后缀
// get a filename's name, without extension
// filename	:	assumed to be a valid filename, that the last 3 characters are extension
// noext	:	filename without extension
// nSize	:	剥去路径的文件名的长度，如果小于输出字符串（第二个参数）的真实长度，则会出现致命错误
void GetFileNameNoExt( const char *filename, char *noext, int nSize )
{
	int length = strlen( filename );
	if( nSize-1 < length ) length = nSize-1;
	int i=length-1;
	for(; i>=0; i--)
	{
		if( filename[i] == '.' )
		{
			break;
		}
	}
	if( i == -1 )
		i = length;
	if( i >= 0 )
	{
		memcpy( noext, filename, i );
	}
	Assert( i<nSize );
	noext[i] = 0;
}	// End of GetFileNameNoExt()

// 得到文件名后缀
// get a filename's extension
// filename	:	assumed to be a valid filename, that the last 3 characters are extension
// ext		:	extension of the filename
// nSize	:	得到的后缀的最大长度，如果小于输出字符串（第二个参数）的真实长度，则会出现致命错误
void GetFileNameExt( const char *filename, char *ext, int nSize )
{
	int length = strlen( filename );
	for( int i=length-1; i>=0; i-- )
	{
		if( filename[i] == '.' )
		{
			int nCount = 0;
			for( int j=i+1; j<length; j++ )
			{
				if( nCount < nSize-1 )
				{
					ext[j-i-1] = filename[j];
					nCount++;
				}
			}
			if( nCount > 0 )
			{
				ext[nCount] = '\0';
			}
			break;
		}
	}
}	// End of GetFileNameExt()
////////////////////


////////////////////
// 前端包含匹配两个字符串，不同于strcmp()
// 第二个字符串是否包含在第一个字符串中，而且前面的字符串一样
// 相同则返回0
BOOL StrCompare( const char *str1, const char *str2 )
{
	char* p = (char *)strstr( str1, str2 );
	if( p == str1 )
	{
		return 0;
	}
	return 1;
}
////////////////////
/////////////////////////////////////////////////

void WideCharToChar( const wchar_t * lpSrc, char * lpDst, int nMax )
{
	AssertValidStringPtr( lpDst,nMax );

	int nCountSrc = wcslen( lpSrc ) + 1;
	int nCount = nCountSrc * 2;

	Assert( nCount < nMax );
	if( nCount < nMax )
	{

		#ifdef WIN32
		WideCharToMultiByte(CP_ACP, 0, lpSrc, nCountSrc, lpDst, nCount, NULL, NULL );
		#else
		wcstombs(lpDst, lpSrc, nCount);
		#endif
		lpDst[nCount] = '\0';

	}
	else
	{
		char szLog[512+1] = { 0 };
		#ifdef WIN32
		WideCharToMultiByte(CP_ACP, 0, lpSrc, nCountSrc, szLog, 512, NULL, NULL );
		#else
		wcstombs(szLog, lpSrc, 512);
		#endif	
		Log( "WideCharToChar %s", szLog );
		lpDst[0] = 0;
	}

}

void CharToWideChar( const char * lpSrc, wchar_t * lpDst, int nMax )
{
	AssertValidStringPtr( lpSrc,nMax);

	int nCount = strlen( lpSrc ) + 1;
	Assert( nCount <= nMax );
	if( nCount <= nMax )
	{
		#ifdef 	WIN32	
		MultiByteToWideChar(CP_ACP, 0, lpSrc, nCount, lpDst, nCount );
		#else
		mbstowcs(lpDst, lpSrc, nCount );
		#endif		
	}
	else
	{
		Log( "CharToWideChar %s", lpSrc );
		lpDst[0] = L'\0';
	}
}

BOOL IsNumber( const char * szNumber )
{
	Assert( szNumber );
	int nLen = Q_strlen( szNumber );
	for( int i = 0; i < nLen; i++ )
	{
		if( szNumber[i] > '9' || szNumber[i] < '0' )
			return FALSE;
	}
	return TRUE;
}

BOOL IsNumber( const wchar_t * szNumber )
{
	Assert( szNumber );
	int nLen = T_strlen( szNumber );
	for( int i = 0; i < nLen; i++ )
	{
		if( szNumber[i] > L'9' || szNumber[i] < L'0' )
			return FALSE;
	}
	return TRUE;
}

// 字符串部分匹配检测
BOOL StrPartCmp( const wchar_t * target, const wchar_t * input )
{
	if( !target )
		return FALSE;
	if( !input )
		return FALSE;

	int nTargetCount = wcslen( target );
	int nInputCount = wcslen( input );
	if( nTargetCount == 0 || nInputCount == 0 )
		return FALSE;
	if( nInputCount >= nTargetCount )
	{
		// 输入字符串比数据源长，直接比较数据源长度的字符
		return ( wcsncmp( target, input, nTargetCount ) == 0 );
	}
	else
	{
		// 输入字符串比数据源短，将数据源分段与输入字符串比较
		for( int i = 0; i <= nTargetCount - nInputCount; i++ )
		{
			if( wcsncmp( target + i, input, nInputCount ) == 0 )
				return TRUE;
		}
	}
	return FALSE;
}


void Encrypt(char*   cSrc,char*   cDest)
{   
	char   c;   
	int   i,h,l,j=0;   
	for   (i=0;i<(int)strlen(cSrc);i++)   
	{   
		c=cSrc[i];   
		h=(c>>4)&0xf;   
		l=c&0xf;   
		cDest[j]=h+'x';   
		cDest[j+1]=l+'z';   
		j+=2;   
	}   
	cDest[j]='\0';   
	return;   
}   
void Decrypt(char*   cSrc,char*   cDest)   
{   
	int   i,h,l,m,n,j=0;   
	for   (i=0;i<(int)strlen(cSrc);i=i+2)   
	{   
		h=(cSrc[i]-'x');   
		l=(cSrc[i+1]-'z');   
		m=(h<<4);   
		n=(l&0xf);   
		cDest[j]=m   +   n;   
		j++;   
	}   
	cDest[j]='\0';   
	return;   
} 