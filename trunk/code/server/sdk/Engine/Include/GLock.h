#ifndef GLOCK_H
#define GLOCK_H

#ifdef WIN32
#include <winsock2.h>
#include <windows.h>
#include "WIN32/GLock_.h"
#else
#include "POSIX/GLock_.h"
#endif

class CLockAutoPtr
{
private:
	CGLock *m_Lock;
public:
	CLockAutoPtr(CGLock *lock):m_Lock(lock)
	{
		m_Lock->LOCK();
	}
	~CLockAutoPtr()
	{
		m_Lock->UNLOCK();
	}
};

class CLockGuard{
private:
	CGLock *m_Lock;
public:
	CLockGuard(CGLock *lock):m_Lock(lock){
		m_Lock->LOCK();

	}
	~CLockGuard(){
		m_Lock->UNLOCK();
	}
};

#if defined WIN32
    #define mb() MemoryBarrier()
	#define rmb() MemoryBarrier()
	#define wmb() MemoryBarrier()
#elif defined __linux__
	// Memory barrier, copy from linux kernel
	#define __ASM_FORM(x)	" " #x " "
	#define __ASM_SEL(a,b) __ASM_FORM(a)

	#define _ASM_ALIGN	__ASM_SEL(.balign 4, .balign 8)
	#define _ASM_PTR	__ASM_SEL(.long, .quad)
	#define __stringify_1(x...)	#x
	#define __stringify(x...)	__stringify_1(x)

	#define ALTERNATIVE(oldinstr, newinstr, feature)			\
											\
		  "661:\n\t" oldinstr "\n662:\n"					\
		  ".section .altinstructions,\"a\"\n"				\
		  _ASM_ALIGN "\n"							\
		  _ASM_PTR "661b\n"				/* label           */	\
		  _ASM_PTR "663f\n"				/* new instruction */	\
		  "	 .byte " __stringify(feature) "\n"	/* feature bit     */	\
		  "	 .byte 662b-661b\n"			/* sourcelen       */	\
		  "	 .byte 664f-663f\n"			/* replacementlen  */	\
		  ".previous\n"							\
		  ".section .altinstr_replacement, \"ax\"\n"			\
		  "663:\n\t" newinstr "\n664:\n"		/* replacement     */	\
		  ".previous"

	#define alternative(oldinstr, newinstr, feature) \
		asm volatile (ALTERNATIVE(oldinstr, newinstr, feature) : : : "memory")

	#define X86_FEATURE_XMM		(0*32+25) /* "sse" */
	#define X86_FEATURE_XMM2	(0*32+26) /* "sse2" */

	#define mb() alternative("lock; addl $0,0(%%esp)", "mfence", X86_FEATURE_XMM2)
	#define rmb() alternative("lock; addl $0,0(%%esp)", "lfence", X86_FEATURE_XMM2)
	#define wmb() alternative("lock; addl $0,0(%%esp)", "sfence", X86_FEATURE_XMM)
#elif defined FREEBSD
//    #define mb()
//	#define rmb()
//	#define wmb()
#else
	#error "MemoryBarrier don't support this platform!"
#endif // #if defined __linux__

#define smp_mb() mb()
#define smp_rmb() rmb()
#define smp_wmb() wmb()


#endif
