/*
 * this file defines some genernal macros,routines... used by any libs/apps
 *
 */

#ifndef CONFIG_H
#define CONFIG_H 
//#define _MINICLIENT  //Î¢¶Ëºê
#include "inttypes.h"

//int NetWorkStart(void);

#define MAX_VALUE(x,y) ( ((x)>(y))? (x):(y) )
#define MIN_VALUE(x,y) ( ((x)<(y))? (x):(y) )

#ifndef WIN32

	//#define FREEBSD

	/*
	 *if os is posix compitable ,define POSIX
	 */
	#ifdef FREEBSD
	#include "config_FreeBSD.h"
	#endif

	/*
	 *int64_t,uint64_t format string
	 *
	 *usage example:
	 *int64_t a = -1;  
	 *uint64_t b = 2;
	 *printf("a ="INT64_FMT", b = "UINT64_FMT" \n"); 
	 *
	 */
	#define INT64_FMT 	"%lld"
	#define UINT64_FMT 	"%llu" 
#else

	#ifndef _WIN32_WINNT
	#define _WIN32_WINNT 0x0501
	#endif

	#include "config_WIN32.h"
	#define INT64_FMT 	"%I64d"
	#define UINT64_FMT 	"%I64u"
	#endif

#endif
