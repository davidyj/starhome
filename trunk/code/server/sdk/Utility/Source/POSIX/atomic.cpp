//#include "../../Include/atomic.h"
///**
// * atomically add 'val' to an apr_uint32_t
// * @param mem pointer to the object
// * @param val amount to add
// * @return old value pointed to by mem
// */
//uint32_t atomic_add32(volatile uint32_t *mem, uint32_t val)
//{
//    asm volatile ("lock; xaddl %0,%1"
//                  : "=r" (val), "=m" (*mem)
//                  : "0" (val), "m" (*mem)
//                  : "memory", "cc");
//    return val;
//}	
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
//    uint32_t prev;
//
//    asm volatile ("lock; cmpxchgl %1, %2"
//                  : "=a" (prev)
//                  : "r" (with), "m" (*(mem)), "0"(cmp)
//                  : "memory", "cc");
//    return prev;
//}	
//
//
//
//
