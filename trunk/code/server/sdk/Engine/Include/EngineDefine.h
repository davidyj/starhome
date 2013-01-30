#pragma once

#include "CommDef.h"

#if defined(WIN32) && (!defined (_ENGINELIB))
	#if defined(ENGINE_EXPORTS)
		#define ENGINE_INTERFACE	DLL_EXPORT
		#define ENGINE_CLASS		DLL_CLASS_EXPORT
		#define ENGINE_GLOBAL		DLL_GLOBAL_EXPORT
	#else
		#define ENGINE_INTERFACE	DLL_IMPORT
		#define ENGINE_CLASS		DLL_CLASS_IMPORT
		#define ENGINE_GLOBAL		DLL_GLOBAL_IMPORT
	#endif//#if defined(ENGINE_EXPORTS)
#else
	#define ENGINE_INTERFACE	
	#define ENGINE_CLASS		
	#define ENGINE_GLOBAL		
#endif

ENGINE_GLOBAL void MemReport_Engine( );
#ifndef WIN32
/* libEngine.so的初始化函数，需要手动调用*/
BOOL Engine_DllMain( ); 
#endif
