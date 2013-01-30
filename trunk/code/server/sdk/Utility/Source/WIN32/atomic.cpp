//#include "../../Include/atomic.h"
//
//
///**
// * atomically add 'val' to an apr_uint32_t
// * @param mem pointer to the object
// * @param val amount to add
// * @return old value pointed to by mem
// */
//uint32_t atomic_add32(volatile uint32_t *mem, uint32_t val)
//{
//#if (defined(_M_IA64) || defined(_M_AMD64))
//    return InterlockedExchangeAdd(mem, val);
//#else
//    return InterlockedExchangeAdd((LONG *)mem, val);
//#endif
//}	
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
//uint32_t atomic_cas32(volatile uint32_t *mem, uint32_t with, uint32_t cmp)
//{
//#if (defined(_M_IA64) || defined(_M_AMD64)) && !defined(RC_INVOKED)
//    return InterlockedCompareExchange(mem, with, cmp);
//#else
//    return InterlockedCompareExchange((LONG *)mem, with, cmp);
//#endif
//}	
//
//
//
