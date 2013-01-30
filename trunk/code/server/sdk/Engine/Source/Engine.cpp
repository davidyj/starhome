// Engine.cpp : 定义 DLL 应用程序的入口点。
//

#include "../stdafx.h"
#include <crtdbg.h>
#include <signal.h> // raise
#include "dbg.h"
#include <stdlib.h>
#include "mathlib.h"
#include "EngineDefine.h"

IMPLEMENT_MEMREPORT( Engine )

SpewRetval_t AppDefaultSpewFunc( SpewType_t spewType, char const *pMsg )
{
#ifndef __DEV__
	return SPEW_DEBUGGER;
#endif
	switch( spewType )
	{
	case SPEW_MESSAGE:
		return SPEW_CONTINUE;
	case SPEW_WARNING:
		OutputDebugString( pMsg );
		return SPEW_CONTINUE;
	case SPEW_LOG:
		OutputDebugString( pMsg );
		Plat_SimpleLog( pMsg, __LINE__ );
		return SPEW_CONTINUE;
	case SPEW_ASSERT:
		{
			int nID = MessageBox( NULL, pMsg , "Assert", MB_ABORTRETRYIGNORE );
			switch( nID )
			{
			case IDRETRY:
				return SPEW_DEBUGGER;
			case IDABORT:
				raise(SIGABRT);
				_exit(3);
				return SPEW_CONTINUE;
			case IDIGNORE:
				return SPEW_CONTINUE;
			}
		}
		return SPEW_DEBUGGER;
	case SPEW_ERROR:
	default:
		return SPEW_DEBUGGER;
	}
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// 替换默认的错误输出函数
		SpewOutputFunc( AppDefaultSpewFunc );
		Plat_SetSimpleLogName("BaseEngine.log");
		MathLib_Init( 2.2f, 2.2f, 0.0f, 2.0f );
		Log("编译日期: %s %s ", __DATE__ , __TIME__);
#ifdef _DEBUG
		_CrtSetDbgFlag( /*_CRTDBG_ALLOC_MEM_DF*/_CRTDBG_REPORT_FLAG | _CRTDBG_LEAK_CHECK_DF );
//		_CrtSetBreakAlloc( 7422 );
#endif
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		Plat_DestroyLog( );
		break;
	}
	return TRUE;
}

