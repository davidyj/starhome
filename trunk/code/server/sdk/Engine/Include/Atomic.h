/*
 * These routines' implementations come from apr of apache project.
 *
 */

#ifndef ATOMIC_H
#define ATOMIC_H

#ifdef __cplusplus 
extern "C" {
#endif

/** 
 * atomically add 'val' to an apr_uint32_t 
 * 
 * @param mem pointer to the object 
 * @param val amount to add 
 * @return old value pointed to by mem */    
unsigned int apr_atomic_add32(volatile unsigned int *mem, unsigned int val);

/** 
 * atomically subtract 'val' from an apr_uint32_t 
 * @param mem pointer to the object 
 * @param val amount to subtract
 */
void apr_atomic_sub32(volatile unsigned int *mem, unsigned int val);

/**
 * atomically increment an apr_uint32_t by 1 
 * @param mem pointer to the object 
 * @return old value pointed to by mem 
 */
unsigned int apr_atomic_inc32(volatile unsigned int *mem);

/**
 *atomically decrement an apr_uint32_t by 1
 *@param mem pointer to the atomic value 
 *@return zero if the value becomes zero on decrement, otherwise non-zero 
 */
int apr_atomic_dec32(volatile unsigned *mem);

#ifndef WIN32
#include "POSIX/atomic_.h"
#endif
#ifdef __cplusplus 
}	
#endif
#endif
