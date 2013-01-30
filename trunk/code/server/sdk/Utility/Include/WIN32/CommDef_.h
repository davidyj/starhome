#pragma once

// Used for dll exporting and importing
#define  DLL_EXPORT   extern "C" __declspec( dllexport ) 
#define  DLL_IMPORT   extern "C" __declspec( dllimport )

// Can't use extern "C" when DLL exporting a class
#define  DLL_CLASS_EXPORT   __declspec( dllexport ) 
#define  DLL_CLASS_IMPORT   __declspec( dllimport )

// Can't use extern "C" when DLL exporting a global
#define  DLL_GLOBAL_EXPORT   extern __declspec( dllexport ) 
#define  DLL_GLOBAL_IMPORT   extern __declspec( dllimport )

// need this for memset
#include <string.h>

#include <stdio.h>

#include <crtdbg.h>

// for when we care about how many bits we use
typedef signed char      int8;
typedef signed short     int16;
typedef signed long      int32;
typedef signed __int64   int64;

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned long      uint32;
typedef unsigned __int64   uint64;

typedef unsigned char      byte;

typedef float  float32;
typedef double float64;

// for when we don't care about how many bits we use
typedef unsigned int uint;

typedef float vec_t;

#pragma warning(push)
#pragma warning (disable:4035) // no return value
#pragma warning (disable:4244) // no return value
#pragma warning (disable:4251) // “identifier”: 类“type”需要有 dll 接口由类“type2”的客户端使用


const uint INVALID_ID		= 0xffffffff;
const uint16 WORD_INVALID_ID	= 0xffff;
const uint8 BYTE_INVALID_ID	= 0xff;

#define	EXCEL_INVALID	-1

//-----------------------------------------------------------------------------
// look for NANs, infinities, and underflows. 
// This assumes the ANSI/IEEE 754-1985 standard
//-----------------------------------------------------------------------------

#ifdef __cplusplus

inline unsigned long& FloatBits( vec_t& f )
{
	return *reinterpret_cast<unsigned long*>(&f);
}

inline unsigned long const& FloatBits( vec_t const& f )
{
	return *reinterpret_cast<unsigned long const*>(&f);
}

inline vec_t BitsToFloat( unsigned long i )
{
	return *reinterpret_cast<vec_t*>(&i);
}

inline bool IsFinite( vec_t f )
{
	return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
}

inline unsigned long FloatAbsBits( vec_t f )
{
	return FloatBits(f) & 0x7FFFFFFF;
}

inline float FloatMakeNegative( vec_t f )
{
	return BitsToFloat( FloatBits(f) | 0x80000000 );
}

#if defined( WIN32 )

//#include <math.h>
// Just use prototype from math.h
#ifdef __cplusplus
extern "C" 
{
#endif
	double __cdecl fabs(double);
#ifdef __cplusplus
}
#endif

// In win32 try to use the intrinsic fabs so the optimizer can do it's thing inline in the code
#pragma intrinsic( fabs )
// Also, alias float make positive to use fabs, too
// NOTE:  Is there a perf issue with double<->float conversion?
inline float FloatMakePositive( vec_t f )
{
	return fabs( f );
}
#else
inline float FloatMakePositive( vec_t f )
{
	return BitsToFloat( FloatBits(f) & 0x7FFFFFFF );
}
#endif

inline float FloatNegate( vec_t f )
{
	return BitsToFloat( FloatBits(f) ^ 0x80000000 );
}


#define FLOAT32_NAN_BITS     (unsigned long)0x7FC00000	// not a number!
#define FLOAT32_NAN          BitsToFloat( FLOAT32_NAN_BITS )

#define VEC_T_NAN FLOAT32_NAN

#endif

//-------------------------------------
// Basic swaps
//-------------------------------------

template <typename T>
inline T WordSwapC( T w )
{
	uint16 temp;

	temp  = ((*((uint16 *)&w) & 0xff00) >> 8);
	temp |= ((*((uint16 *)&w) & 0x00ff) << 8);

	return *((T*)&temp);
}

template <typename T>
inline T DWordSwapC( T dw )
{
	uint32 temp;

	temp  =   *((uint32 *)&dw) 				>> 24;
	temp |= ((*((uint32 *)&dw) & 0x00FF0000) >> 8);
	temp |= ((*((uint32 *)&dw) & 0x0000FF00) << 8);
	temp |= ((*((uint32 *)&dw) & 0x000000FF) << 24);

	return *((T*)&temp);
}

//-------------------------------------
// Fast swaps
//-------------------------------------

#define WordSwap  WordSwapAsm
#define DWordSwap DWordSwapAsm

template <typename T>
inline T WordSwapAsm( T w )
{
#ifdef X64_WIN
	assert(0);
#else
	__asm
	{
		mov ax, w
			xchg al, ah
	}
#endif
}

template <typename T>
inline T DWordSwapAsm( T dw )
{
#ifdef X64_WIN
	assert(0);
#else
	__asm
	{
		mov eax, dw
			bswap eax
	}
#endif
}

#pragma warning(pop)

// The assembly implementation is not compatible with floats
template <>
inline float DWordSwapAsm<float>( float f )
{
	return DWordSwapC( f );
}

//-------------------------------------
// The typically used methods. 
//-------------------------------------

/*
 *XXX: These macros should not used in Servers, added by Jiandong Lu 2009.8.18
 */
#ifdef _CLIENT_
#define BigShort( val )		WordSwap( val )
#define BigWord( val )		WordSwap( val )
#define BigLong( val )		DWordSwap( val )
#define BigDWord( val )		DWordSwap( val )
#define BigFloat( val )		DWordSwap( val )
#define LittleShort( val )	( val )
#define LittleWord( val )	( val )
#define LittleLong( val )	( val )
#define LittleDWord( val )	( val )
#define LittleFloat( val )	( val )
#endif

inline int IsOdd(int i){return i & 0x00000001;}
inline DWORD IsOdd(DWORD i){return i & 0x00000001;}

#if !defined(MIN_INT)
#define   MIN_INT      1
#endif//#if !defined(MIN_INT)

#if !defined(MIN_FLOAT)
#define   MIN_FLOAT    0.0001
#endif//#if !defined(MIN_FLOAT)

#if !defined(LENGTH)
#define   LENGTH(a,b)  ((b) - (a) + 1)
#endif//#if !defined(LENGTH)

#if !defined(MIN)
#define   MIN(x,y) ( ((x)>(y))? (y):(x) )
#endif//#if !defined(MIN)

#if !defined(MAX)
#define   MAX(x,y) ( ((x)>(y))? (x):(y) )
#endif//#if !defined(MAX)

#if !defined(MAX_ABS)
#define   MAX_ABS(x,y) ( (abs(x)>abs(y))? abs(x):abs(y) )
#endif//#if !defined(MAX_ABS)

#if !defined(MIN_ABS)
#define   MIN_ABS(x,y) ( (abs(x)>abs(y))? abs(y):abs(x) )
#endif//#if !defined(MIN_ABS)

#if !defined(ADDC)
#define   ADDC(a,b,a_max)( (( (a) + (b)) >= (a_max)) ?  0 : (a) + (b))
#endif//#if !defined(ADDC)

#if !defined(INCC)
#define   INCC(a,a_max)( (( (a) + 1) >= (a_max)) ?  0 : (a) + 1)
#endif//#if !defined(INCC)

#if !defined(DECC)
#define   DECC(a,a_max)( (( (a) - 1) < 0) ?  (a_max)-1 : (a) - 1)
#endif//#if !defined(DECC)

#if !defined(SUBCC)
#define   SUBCC(a,b,a_max) ( ((b) > (a)) ? (a_max) + (a) - (b) : (a) - (b))
#endif//#if !defined(SUBCC)

#if !defined(ADDCC)
#define   ADDCC(a,b,a_max) ( ((b) + (a) >= (a_max)) ?  (a) + (b) - (a_max) : (a) + (b))
#endif//#if !defined(ADDCC)

#if !defined(ISIN)
#define   ISIN(a,b,c)( (((a)>=(b))&&((a)<=(c))) ? TRUE : FALSE )
#endif//#if !defined(ISIN)

#if !defined(Math_Distance)
#define	  Math_Distance(x1,y1,x0,y0) ( sqrt( ((x1) - (x0))*((x1) - (x0)) + ((y1) - (y0))*((y1) - (y0)) ) )
#endif//#if !defined(Math_Distance)

// tell what quadrant it is
// 0 , 1 , 2 , 3 quadrant 
#if !defined(WHAT_QUADRANT)
#define   WHAT_QUADRANT(x,y)( ((x)>=0) ? (((y)>=0) ? 0 : 3) : (((y)>=0)? 1 : 2))
#endif//#if !defined(WHAT_QUADRANT)

//get  sign
#if !defined(SIGN)
#define  SIGN(a)(((a) >= 0 ) ? 1 : -1 )
#endif//#if !defined(SIGN)

// get  direction  if a==0 then 0
#if !defined(DIRECT)
#define  DIRECT(a)(((a) >= 0 ) ? (((a) == 0) ? 0 : 1) : -1 )
#endif//#if !defined(DIRECT)

//if 0 then replace with a min number
#if !defined(INT_NOT_0)
#define  INT_NOT_0(a)(((a) == 0)? MIN_INT : (a))
#endif//#if !defined(INT_NOT_0)

#if !defined(FLOAT_NOT_0)
#define  FLOAT_NOT_0(a)(((a) == 0)? MIN_FLOAT : (a))
#endif//#if !defined(FLOAT_NOT_0)

#ifdef USE_IDE_VC2003
template<class T>
void swap(  T& a,    T& b)
{
	T	tmp = b;
	b = a;
	a = tmp;
}
#endif

typedef int qboolean;

#if !defined(SAFE_RELEASE)
#define SAFE_RELEASE(p)	if(p){p->Release();p=NULL;}
#endif//#if !defined(SAFE_RELEASE)

#if !defined(SAFE_DELETE)
#define SAFE_DELETE(p)	if(p){delete p;p=NULL;}
#endif//#if !defined(SAFE_DELETE)

#if !defined(SAFE_DELETE_ARRAY)
#define SAFE_DELETE_ARRAY(p)	if(p){delete [] p;p=NULL;}
#endif//#if !defined(SAFE_DELETE_ARRAY)

//by jinsheng
typedef struct color32_s
{
	bool operator!=( const struct color32_s &other ) const;

	char r, g, b, a;//by jinsheng byte
} color32;

inline bool color32::operator!=( const color32 &other ) const
{
	return r != other.r || g != other.g || b != other.b || a != other.a;
}
struct Rect_t
{
    int x, y;
	int width, height;
};

struct colorVec
{
	unsigned r, g, b, a;
};

