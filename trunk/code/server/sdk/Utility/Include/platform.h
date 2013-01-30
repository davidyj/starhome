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
// Extremely low-level platform-specific stuff
//=============================================================================

#pragma once
#include "CommDef.h"

// need this for _alloca
#ifdef WIN32
#include <malloc.h>
#else
#include <stdlib.h>
#endif

// need this for memset
#include <string.h>

#if defined(WIN32) && !defined(WINDED)

#if defined(_M_IX86)
#define __i386__	1
#endif

#elif defined(POSIX)
//these tow types have been defined by the config.h file ---lujd 2009.06.05
//typedef unsigned int DWORD;
//typedef unsigned short WORD;
typedef void * HINSTANCE;
#define _MAX_PATH PATH_MAX
#endif // defined(WIN32) && !defined(WINDED)

// Defines MAX_PATH
#ifndef MAX_PATH
	#ifdef WIN32
	#define MAX_PATH  260
	#else
	#define MAX_PATH  PATH_MAX
	#endif
#endif

#if defined __i386__ && !defined __linux__
#define id386	1
#else
#define id386	0
#endif  // __i386__

#define SINGLE_INHERITANCE __single_inheritance
#define MULTIPLE_INHERITANCE __multiple_inheritance

// Used to step into the debugger
//#define  DebuggerBreak()  __asm { int 3 }
#define  DebuggerBreak()

// Used for standard calling conventions
#ifdef WIN32
	#define  STDCALL	__stdcall
	#define  FASTCALL   	__fastcall
	#define  FORCEINLINE 	__forceinline
#else
	#define  STDCALL
	#define  FASTCALL
	#define  FORCEINLINE		   inline
#endif

// Force a function call site -not- to inlined. (useful for profiling)
#define DONT_INLINE(a) (((int)(a)+1)?(a):(a))

// Pass hints to the compiler to prevent it from generating unnessecary / stupid code
// in certain situations.  Several compilers other than MSVC also have an equivilent
// construct.
//
// Essentially the 'Hint' is that the condition specified is assumed to be true at
// that point in the compilation.  If '0' is passed, then the compiler assumes that
// any subsequent code in the same 'basic block' is unreachable, and thus usually
// removed.
#ifdef _MSC_VER
	#define HINT(THE_HINT)	__assume((THE_HINT))
#else
	#define HINT(THE_HINT)	0
#endif

// Marks the codepath from here until the next branch entry point as unreachable,
// and asserts if any attempt is made to execute it.
#define UNREACHABLE() { Assert(0); HINT(0); }

// In cases where no default is present or appropriate, this causes MSVC to generate
// as little code as possible, and throw an assertion in debug.
#define NO_DEFAULT default: UNREACHABLE();

// Alloca defined for this platform
#define  stackalloc( _size ) _alloca( _size )
#define  stackfree( _p )   0

// Remove warnings from warning level 4.
#ifdef WIN32
#pragma warning(disable : 4514) // warning C4514: 'acosl' : unreferenced inline function has been removed
#pragma warning(disable : 4100) // warning C4100: 'hwnd' : unreferenced formal parameter
#pragma warning(disable : 4127) // warning C4127: conditional expression is constant
#pragma warning(disable : 4512) // warning C4512: 'InFileRIFF' : assignment operator could not be generated
#pragma warning(disable : 4611) // warning C4611: interaction between '_setjmp' and C++ object destruction is non-portable
#pragma warning(disable : 4706) // warning C4706: assignment within conditional expression
#pragma warning(disable : 4710) // warning C4710: function 'x' not inlined
#pragma warning(disable : 4702) // warning C4702: unreachable code
#pragma warning(disable : 4505) // unreferenced local function has been removed
#pragma warning(disable : 4239) // nonstandard extension used : 'argument' ( conversion from class Vector to class Vector& )
#pragma warning(disable : 4097) // typedef-name 'BaseClass' used as synonym for class-name 'CFlexCycler::CBaseFlex'
#pragma warning(disable : 4324) // Padding was added at the end of a structure
#pragma warning(disable : 4244) // type conversion warning.
#pragma warning(disable : 4267) // type conversion warning.
#pragma warning(disable : 4305)	// truncation from 'const double ' to 'float '
#pragma warning(disable : 4786)	// Disable warnings about long symbol names

#pragma warning(disable : 4511)	// Disable warnings about private copy constructors
#endif

double		Plat_FloatTime();		// Returns time in seconds since the module was loaded.
unsigned long	Plat_MSTime();			// Time in milliseconds.
unsigned long	Plat_MMSTime();			// Time in milliseconds.

// b/w compatibility
#define Sys_FloatTime Plat_FloatTime

// Processor Information:
struct CPUInformation
{
	int	 m_Size;		// Size of this structure, for forward compatability.

	bool m_bRDTSC : 1,	// Is RDTSC supported?
		 m_bCMOV  : 1,  // Is CMOV supported?
		 m_bFCMOV : 1,  // Is FCMOV supported?
		 m_bSSE	  : 1,	// Is SSE supported?
		 m_bSSE2  : 1,	// Is SSE2 Supported?
		 m_b3DNow : 1,	// Is 3DNow! Supported?
		 m_bMMX   : 1,	// Is MMX supported?
		 m_bHT	  : 1;	// Is HyperThreading supported?

	unsigned char m_nLogicalProcessors,		// Number op logical processors.
		          m_nPhysicalProcessors;	// Number of physical processors

#ifdef WIN32
	int64 m_Speed;						// In cycles per second.
#else
	long long m_Speed;
#endif

	char* m_szProcessorID;				// Processor vendor Identification.
};

const CPUInformation& GetCPUInformation();
#ifndef WIN32
uint64 CalculateCPUFreq();
#endif

// ---------------------------------------------------------------------------------- //
// Memory allocation.
// ---------------------------------------------------------------------------------- //

typedef void (*Plat_AllocErrorFn)( unsigned long size );

// Use these to allocate and free memory.
void*		Debug_Plat_Alloc( unsigned long size, const char * szFile, int nLine );				// Allocate some memory.
void*		Debug_Plat_Realloc( void *ptr, unsigned long size, const char * szFile, int nLine );	// Rellocate some memory. It may or may not return the same
void		Debug_Plat_Free( void *ptr, const char * szFile, int nLine );							// Free some memory.
// block of memory.
// Use these to allocate and free memory.
void*		Release_Plat_Alloc( unsigned long size );				// Allocate some memory.
void*		Release_Plat_Realloc( void *ptr, unsigned long size );	// Rellocate some memory. It may or may not return the same
void		Release_Plat_Free( void *ptr );							// Free some memory.
// block of memory.


// Use this to hook allocation errors.
void		Plat_SetAllocErrorFn( Plat_AllocErrorFn fn );

#ifdef _DEBUG
#define		Plat_Alloc( size ) Debug_Plat_Alloc( size, __FILE__, __LINE__ )					// Allocate some memory.
#define		Plat_Realloc( ptr, size ) Debug_Plat_Realloc( ptr, size, __FILE__, __LINE__ )	// Rellocate some memory. It may or may not return the same
#define		Plat_Free( ptr ) Debug_Plat_Free( ptr, __FILE__, __LINE__ )							// Free some memory.
// block of memory.
#else
#define		Plat_Alloc( size ) Release_Plat_Alloc( size )					// Allocate some memory.
#define		Plat_Realloc( ptr, size ) Release_Plat_Realloc( ptr, size )	// Rellocate some memory. It may or may not return the same
#define		Plat_Free( ptr ) Release_Plat_Free( ptr )							// Free some memory.
// block of memory.
#endif


//-----------------------------------------------------------------------------
// Thread related functions
//-----------------------------------------------------------------------------
// Registers the current thread with Tier0's thread management system.
// This should be called on every thread created in the game.
unsigned long Plat_RegisterThread( const char *pName = "Source Thread");

// Registers the current thread as the primary thread.
unsigned long Plat_RegisterPrimaryThread();

// VC-specific. Sets the thread's name so it has a friendly name in the debugger.
// This should generally only be handled by Plat_RegisterThread and Plat_RegisterPrimaryThread
void	Plat_SetThreadName( unsigned long dwThreadID, const char *pName );

// These would be private if it were possible to export private variables from a .DLL.
// They need to be variables because they are checked by inline functions at performance
// critical places.
extern unsigned long Plat_PrimaryThreadID;

// Returns the ID of the currently executing thread.
unsigned long Plat_GetCurrentThreadID();

// Returns the ID of the primary thread.
inline unsigned long Plat_GetPrimaryThreadID()
{
	return Plat_PrimaryThreadID;
}

// Returns true if the current thread is the primary thread.
inline bool Plat_IsPrimaryThread()
{
	//return true;
	return (Plat_GetPrimaryThreadID() == Plat_GetCurrentThreadID() );
}


//-----------------------------------------------------------------------------
// Just logs file and line to simple.log
//-----------------------------------------------------------------------------
void Plat_SetSimpleLogName( const char * szLogName );
void Plat_DestroyLog( );
void* Plat_SimpleLog( const char* file, int line );
void* Plat_BlockLog( char const *pMsgFormat, ... );

//#define Plat_dynamic_cast Plat_SimpleLog(__FILE__,__LINE__),dynamic_cast

//-----------------------------------------------------------------------------
// Methods to invoke the constructor, copy constructor, and destructor
//-----------------------------------------------------------------------------

template <class T>
inline void Construct( T* pMemory )
{
	new( pMemory ) T;
}

template <class T>
inline void CopyConstruct( T* pMemory, T const& src )
{
	new( pMemory ) T(src);
}

template <class T>
inline void Destruct( T* pMemory )
{
	pMemory->~T();

//#ifdef _DEBUG
//	memset( pMemory, 0xDD, sizeof(T) );
//#endif
}


//
// GET_OUTER()
//
// A platform-independent way for a contained class to get a pointer to its
// owner. If you know a class is exclusively used in the context of some
// "outer" class, this is a much more space efficient way to get at the outer
// class than having the inner class store a pointer to it.
//
//	class COuter
//	{
//		class CInner // Note: this does not need to be a nested class to work
//		{
//			void PrintAddressOfOuter()
//			{
//				printf( "Outer is at 0x%x\n", GET_OUTER( COuter, m_Inner ) );
//			}
//		};
//
//		CInner m_Inner;
//		friend class CInner;
//	};

#define GET_OUTER( OuterType, OuterMember ) \
   	( ( OuterType * ) ( (char *)this - offsetof( OuterType, OuterMember ) ) )


/*	TEMPLATE_FUNCTION_TABLE()

(Note added to platform.h so platforms that correctly support templated
functions can handle portions as templated functions rather than wrapped
functions)

	Helps automate the process of creating an array of function
	templates that are all specialized by a single integer.
	This sort of thing is often useful in optimization work.

	For example, using TEMPLATE_FUNCTION_TABLE, this:

	TEMPLATE_FUNCTION_TABLE(int, Function, ( int blah, int blah ), 10)
	{
		return argument * argument;
	}

	is equivilent to the following:

	(NOTE: the function has to be wrapped in a class due to code
	generation bugs involved with directly specializing a function
	based on a constant.)

	template<int argument>
	class FunctionWrapper
	{
	public:
		int Function( int blah, int blah )
		{
			return argument*argument;
		}
	}

	typedef int (*FunctionType)( int blah, int blah );

	class FunctionName
	{
	public:
		enum { count = 10 };
		FunctionType functions[10];
	};

	FunctionType FunctionName::functions[] =
	{
		FunctionWrapper<0>::Function,
		FunctionWrapper<1>::Function,
		FunctionWrapper<2>::Function,
		FunctionWrapper<3>::Function,
		FunctionWrapper<4>::Function,
		FunctionWrapper<5>::Function,
		FunctionWrapper<6>::Function,
		FunctionWrapper<7>::Function,
		FunctionWrapper<8>::Function,
		FunctionWrapper<9>::Function
	};
*/

bool vtune( bool resume );


#define TEMPLATE_FUNCTION_TABLE(RETURN_TYPE, NAME, ARGS, COUNT)			\
																		\
typedef RETURN_TYPE (FASTCALL *__Type_##NAME) ARGS;						\
																		\
template<const int nArgument>											\
struct __Function_##NAME												\
{																		\
	static RETURN_TYPE FASTCALL Run ARGS;								\
};																		\
																		\
template <int i>														\
struct __MetaLooper_##NAME : __MetaLooper_##NAME<i-1>					\
{																		\
	__Type_##NAME func;													\
	inline __MetaLooper_##NAME() { func = __Function_##NAME<i>::Run; }	\
};																		\
																		\
template<>																\
struct __MetaLooper_##NAME<0>											\
{																		\
	__Type_##NAME func;													\
	inline __MetaLooper_##NAME() { func = __Function_##NAME<0>::Run; }	\
};																		\
																		\
class NAME																\
{																		\
private:																\
    static const __MetaLooper_##NAME<COUNT> m;							\
public:																	\
	enum { count = COUNT };												\
	static const __Type_##NAME* functions;								\
};																		\
const __MetaLooper_##NAME<COUNT> NAME::m;								\
const __Type_##NAME* NAME::functions = (__Type_##NAME*)&m;				\
template<int nArgument>													\
RETURN_TYPE FASTCALL __Function_##NAME<nArgument>::Run ARGS


#define LOOP_INTERCHANGE(BOOLEAN, CODE)\
	if( (BOOLEAN) )\
	{\
		CODE;\
	} else\
	{\
		CODE;\
	}

#include "../../Engine/Include/GLock.h"
#ifdef WIN32
class CPlatformCS
{
public:
	inline void Lock( )
	{
		if( !m_bInited )
		{
			InitializeCriticalSection( &m_CS );
			m_bInited = TRUE;
		}
		EnterCriticalSection( &m_CS );
	}
	inline void Unlock( )
	{
		LeaveCriticalSection( &m_CS );
	}
	CPlatformCS( )
	{
		m_bInited = FALSE;
	}
	~CPlatformCS( )
	{
		//by jinsheng 2007.11.19
		if ( m_bInited )
			DeleteCriticalSection( &m_CS );
	}

private:
	BOOL m_bInited;
	CRITICAL_SECTION m_CS;
};
#else

class CPlatformCS
{
public:
	inline void Lock( )
	{
		globalLock.LOCK();
	}

	inline void Unlock( )
	{
		globalLock.UNLOCK();

	}
	CPlatformCS( )
	{
	}

	~CPlatformCS( )
	{
	}

private:
		CGLock globalLock;
};
#endif

/*
 * XXX: This function is not implemented on FreeBSD.It does nothing on FreeBSD.
 */
void Plat_GetExePath( char * szExePath, int nSize );

BOOL Plat_CreatePath( LPCTSTR fullname );
