//#include "../Atomic.h"

/** 
 * atomically add 'val' to an apr_uint32_t 
 * 
 * @param mem pointer to the object 
 * @param val amount to add 
 * @return old value pointed to by mem */    
inline unsigned int apr_atomic_add32(volatile unsigned int *mem, unsigned int val)
{
	asm volatile ("lock; xaddl %0,%1"                  
		: "=r" (val), "=m" (*mem)                  
		: "0" (val), "m" (*mem)                  
		: "memory", "cc");    
	return val;
}	

/** 
 * atomically subtract 'val' from an apr_uint32_t 
 * @param mem pointer to the object 
 * @param val amount to subtract
 */
inline void apr_atomic_sub32(volatile unsigned int *mem, unsigned int val)
{
	asm volatile ("lock; subl %1, %0"                  
		: /* no output */                  
		: "m" (*(mem)), "r" (val)                  
		: "memory", "cc");
}	

/**
 * atomically increment an apr_uint32_t by 1 
 * @param mem pointer to the object 
 * @return old value pointed to by mem 
 */
inline unsigned int apr_atomic_inc32(volatile unsigned int *mem)
{
	return apr_atomic_add32(mem, 1);
}	

/**
 *atomically decrement an apr_uint32_t by 1
 *@param mem pointer to the atomic value 
 *@return zero if the value becomes zero on decrement, otherwise non-zero 
 */
inline int apr_atomic_dec32(volatile unsigned *mem)
{
	unsigned char prev;    
	asm volatile ("lock; decl %0; setnz %1"                  
		: "=m" (*mem), "=qm" (prev)                  
		: "m" (*mem)                  
		: "memory");    
	return prev;
}	


