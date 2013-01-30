#include "StdAfx.h"
//#define _CRTDBG_MAP_ALLOC
//#include <vld.h>
#include <signal.h> // raise

#include "PacketDefine.h"

#ifdef WIN32
IMPLEMENT_MEMREPORT( GameNetCommon )

SpewRetval_t AppDefaultSpewFunc( SpewType_t spewType, char const *pMsg )
{
//#ifndef __DEV__
//	return SPEW_DEBUGGER;
//#endif
	switch( spewType )
	{
	case SPEW_MESSAGE:		
		return SPEW_CONTINUE;
	case SPEW_WARNING:
		OutputDebugString(pMsg);
		return SPEW_CONTINUE;
	case SPEW_LOG:
		OutputDebugString(pMsg);
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
#ifdef _DEBUG
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
		Plat_SetSimpleLogName("gamenetcommon.log");
		// 替换默认的错误输出函数
		SpewOutputFunc( AppDefaultSpewFunc );
		Log("编译日期: %s %s ", __DATE__ , __TIME__);
		PacketDefineInit();
		break;
	case DLL_PROCESS_DETACH:
		Plat_DestroyLog( );
		break;
	}

	return TRUE;
}
#endif
