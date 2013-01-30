// Engine.cpp : 定义 DLL 应用程序的入口点。
//

#include "../stdafx.h"
#include <signal.h> // raise
#include "dbg.h"
#include <stdlib.h>
//#include "mathlib.h"
//#include "EngineDefine.h"
#include "PacketDefine.h"

IMPLEMENT_MEMREPORT( Gamenetcommon )

SpewRetval_t AppDefaultSpewFunc( SpewType_t spewType, char const *pMsg )
{
	switch( spewType )
	{
		case SPEW_MESSAGE:
			return SPEW_CONTINUE;
		case SPEW_WARNING:
			//OutputDebugString( pMsg );
			printf("%s\n", pMsg);
			return SPEW_CONTINUE;
		case SPEW_LOG:
			Plat_SimpleLog( pMsg, __LINE__ );
			return SPEW_CONTINUE;
		case SPEW_ASSERT:
			{

#ifdef	_DEBUG
				printf("----------------------assert! pMsg = %s in file %s\n", pMsg, __FILE__);
				//abort();
#else
				printf("assert! pMsg = %s in file %s\n", pMsg, __FILE__);
#endif
			}
			return SPEW_DEBUGGER;
		case SPEW_ERROR:
		default:
			return SPEW_DEBUGGER;
	}
}

__attribute ((constructor)) void Gamenetcommon_DllMain()
{
    PacketDefineInit();
	// 替换默认的错误输出函数
	//		SpewOutputFunc( AppDefaultSpewFunc );
//	Plat_SetSimpleLogName("gamenetcommon.log");
//	Log("编译日期: %s %s ", __DATE__ , __TIME__);
//	MathLib_Init( 2.2f, 2.2f, 0.0f, 2.0f );
#ifdef _DEBUG
	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//		_CrtSetBreakAlloc( 7422 );
#endif

}

