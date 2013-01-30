#ifndef UTILITY_ATOMIC_H
#define UTILITY_ATOMIC_H


/*
 * This file provides some atomic routines which are taken by Jiandong Lu from apache apr library
 *
 */

#ifdef WIN32
#include "./WIN32/stdint.h"
#include <windows.h>
#else
#include <stdint.h>
#include <sys/types.h>
#include <machine/atomic.h>
#include  "CommDef.h"
#endif

///**
// * atomically add 'val' to an apr_uint32_t
// * @param mem pointer to the object
// * @param val amount to add
// * @return old value pointed to by mem
// */
//uint32_t atomic_add32(volatile uint32_t *mem, uint32_t val);
//
//
///**
// * compare an apr_uint32_t's value with 'cmp'.
// * If they are the same swap the value with 'with'
// * @param mem pointer to the value
// * @param with what to swap it with
// * @param cmp the value to compare it to
// * @return the old value of *mem
// */
//uint32_t atomic_cas32(volatile uint32_t *mem, uint32_t with, uint32_t cmp);

inline LONG LockedCompareExchange( LONG volatile *Destination, LONG Exchange, LONG Comperand )
{
#ifdef WIN32
	if( InterlockedCompareExchange( Destination, Exchange, Comperand ) == Comperand )
	{
		return 1;
	}
	return 0;
#else
	return atomic_cmpset_rel_long( (u_long*)Destination, (u_long)Comperand, (u_long)Exchange );
#endif
}

#ifdef FREEBSD

inline LONG InterlockedExchangeAdd( LONG volatile *Addend, LONG Value )
{
	return atomic_fetchadd_long( (u_long*)Addend, (u_long)Value );
}

inline LONG InterlockedCompareExchange( LONG volatile *Destination, LONG Exchange, LONG Comperand )
{
	/*	需要注意，这里的返回值与winapi不同, winapi返回原始值。
	 * if (*Destination == Comperand) {
	 *      *Destination = Exchange;
	 *      return 1;
	 *  } else
	 *      return 0;
	 */

	return atomic_cmpset_rel_long( (u_long*)Destination, (u_long)Comperand, (u_long)Exchange );
}

inline void InterlockedIncrement( LONG volatile *linc)
{
	atomic_add_long( (ULONG*)linc, 1 );
}

inline void InterlockedDecrement( LONG volatile *linc)
{
	atomic_subtract_long( (ULONG*)linc, 1 );
}

inline void InterlockedExchange(volatile LONG* param,LONG value)
{
    atomic_store_rel_long( (ULONG*)param, value );
}


#endif

#endif


