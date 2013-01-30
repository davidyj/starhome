#ifndef COMMON_DEF_POSIX_H
#define COMMON_DEF_POSIX_H


#ifndef DLL_EXPORT
#define  DLL_EXPORT
#endif

#ifndef DLL_IMPORT
#define  DLL_IMPORT
#endif

#ifndef DLL_CLASS_EXPORT
#define  DLL_CLASS_EXPORT
#endif

#ifndef DLL_CLASS_IMPORT
#define  DLL_CLASS_IMPORT
#endif

#ifndef DLL_GLOBAL_EXPORT
#define  DLL_GLOBAL_EXPORT
#endif

#ifndef DLL_GLOBAL_IMPORT
#define  DLL_GLOBAL_IMPORT
#endif

#ifndef __stdcall
#define  __stdcall
#endif

#include <string.h>
#include <stdio.h>

//#include <crtdbg.h>
#include <stdint.h>

#ifndef USE_ATT_ASM
#error "not use att style asm"
#endif

//#define __int64 long long
#define __int64 int64_t
// for when we care about how many bits we use
typedef signed char      int8;
typedef signed short     int16;
typedef int32_t   int32;
typedef int64_t   int64;
//typedef signed long      int32;
//typedef long long int64;
//#define int64 long long

typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef uint32_t      uint32;
//typedef unsigned long      uint32;
//typedef unsigned long long   uint64;	define config_FreeBSD

typedef float  float32;
typedef double float64;

// for when we don't care about how many bits we use
typedef unsigned int uint;

typedef float vec_t;
typedef unsigned char byte;	//	windef in rpcndr.h  use in CreatePlayerQueue.h
typedef unsigned char boolean;// windef in RpcNdr.h  use in LuaFunc.cpp

const uint INVALID_ID		= 0xffffffff;
const uint16 WORD_INVALID_ID	= 0xffff;
const uint8 BYTE_INVALID_ID	= 0xff;

#define	EXCEL_INVALID	-1

//-----------------------------------------------------------------------------
// look for NANs, infinities, and underflows.
// This assumes the ANSI/IEEE 754-1985 standard
//-----------------------------------------------------------------------------


#ifdef __cplusplus

//inline unsigned long& FloatBits( vec_t& f )
inline uint32& FloatBits( vec_t& f )
{
	//return *reinterpret_cast<unsigned long*>(&f);
	return *reinterpret_cast<uint32*>(&f);
}

//inline unsigned long const& FloatBits( vec_t const& f )
inline uint32 const& FloatBits( vec_t const& f )
{
	//return *reinterpret_cast<unsigned long const*>(&f);
	return *reinterpret_cast<uint32 const*>(&f);
}

//inline vec_t BitsToFloat( unsigned long i )
inline vec_t BitsToFloat( uint32 i )
{
	return *reinterpret_cast<vec_t*>(&i);
}

inline bool IsFinite( vec_t f )
{
	return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
}

//inline unsigned long FloatAbsBits( vec_t f )
inline uint32 FloatAbsBits( vec_t f )
{
	return FloatBits(f) & 0x7FFFFFFF;
}

inline float FloatMakeNegative( vec_t f )
{
	return BitsToFloat( FloatBits(f) | 0x80000000 );
}

inline float FloatMakePositive( vec_t f )
{
	return BitsToFloat( FloatBits(f) & 0x7FFFFFFF );
}

inline float FloatNegate( vec_t f )
{
	return BitsToFloat( FloatBits(f) ^ 0x80000000 );
}

//#define FLOAT32_NAN_BITS     (unsigned long)0x7FC00000	// not a number!
#define FLOAT32_NAN_BITS     (unsigned int)0x7FC00000	// not a number!
#define FLOAT32_NAN          BitsToFloat( FLOAT32_NAN_BITS )

#define VEC_T_NAN FLOAT32_NAN

#endif

inline int IsOdd(int i){return i & 0x00000001;}
//inline DWORD IsOdd(DWORD i){return i & 0x00000001;}

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

template<class T>
void swap(  T& a,    T& b)
{
	T	tmp = b;
	b = a;
	a = tmp;
}

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

#endif
