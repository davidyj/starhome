// Engine.cpp : ���� DLL Ӧ�ó������ڵ㡣
//

#include "../stdafx.h"
#include <signal.h> // raise
#include "dbg.h"
#include <stdlib.h>
//#include "mathlib.h"
#include "EngineDefine.h"

IMPLEMENT_MEMREPORT( Engine )

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
				printf("\n-assert! pMsg = %s in file %s\n", pMsg, __FILE__);
				//abort();
			}
			return SPEW_DEBUGGER;
		case SPEW_ERROR:
		default:
			return SPEW_DEBUGGER;
	}
}

//BOOL Engine_DllMain( )
__attribute ((constructor)) BOOL Engine_DllMain()
{
	// �滻Ĭ�ϵĴ����������
	//		SpewOutputFunc( AppDefaultSpewFunc );
//	Plat_SetSimpleLogName("engine.log");
//	Log("��������: %s %s ", __DATE__ , __TIME__);
//	MathLib_Init( 2.2f, 2.2f, 0.0f, 2.0f );
#ifdef _DEBUG
	//_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//		_CrtSetBreakAlloc( 7422 );
#endif
	return TRUE;
}

