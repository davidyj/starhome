#include "StdAfx.h"
#include "PacketDefine.h"
#include "PacketDefineHead.h"
#include "inttypes.h"

//////////////////////////////////////////////////////////////////////////
//

static uint16_t _PacketIndexFastTable[PACKET_END];

void PacketDefineInit()
{
	memset( _PacketIndexFastTable, 0xff, PACKET_END*sizeof(uint16_t) );

	for( uint16_t i=0; i<sizeof( PACKET_PARAM )/sizeof( CmdInfo ); i++ )
	{
		_PacketIndexFastTable[PACKET_PARAM[i].nCmd] = i;
	}
}
//
//LPCSTR _GetCmdFormat( int nCmd, const CmdInfo * pInfo, int nCount )
//{
//#ifdef WIN32		
//	LPTSTR lpRet = "";
//	__asm
//	{
//		mov	ecx, nCount
//		mov	ebx, nCmd
//		mov eax, pInfo
//__loop:
//		mov edx, [eax]
//		cmp ebx, edx
//		je	__found
//		dec ecx
//		add eax, size CmdInfo
//		jnz __loop
//		jmp __nofound
//__found:
//		mov eax, [eax+4]
//		jmp __ret
//	}
//__nofound:
//	return lpRet;
//__ret:;
//#else
////XXX:_GetCmdFormat is rewritten in C currently.We may need to modify the algothrim
//     /* 
//	LPTSTR lpRet = "";
//	__asm__ __volatile__
//	(	
//		"movl	%0,	%%ecx	\n\t"
//		"movl	%1,	%%ebx	\n\t"
//		"movl   %2,	%%eax	\n\t"
//		"__loop:		\n\t"
//		"movl 	(%%eax),%%edx	\n\t"
//		"cmp 	%%edx,	%%ebx	\n\t"
//		"je		__found	\n\t"		
//		"decl 	%ecx		\n\t"
//		"addl 	$8,	%eax	\n\t" 
//		"jnz __loop		\n\t"
//		"jmp __nofound		\n\t"
//		"__found:		\n\t"
//		"mov 4(%%eax),	%%eax	\n\t"
//		"jmp __ret	"
//		::"r"(nCount),"r"(nCmd),"r"(pInfo)
//	)
//__nofound:
//	return lpRet;
//__ret:
//
//	return NULL;
//*/	
//     	int i = 0; 
//	for(; i<nCount; i++){
//		if (pInfo[i].nCmd == nCmd) {
//			return pInfo[i].szMsgFormat;
//		}
//	}
//	return NULL;	
//#endif      
//}

LPCSTR GetCmdFormat( int nCmd )
{
	if( _PacketIndexFastTable[nCmd]==0xffff )
	{
		for( int i=0; i<sizeof( PACKET_PARAM )/sizeof( CmdInfo ); i++ )
		{
			if ( PACKET_PARAM[i].nCmd == nCmd )
			{
				Log( "Warning: 包定义在遍历中找到:%d，可能与通信方程序版本不同！", nCmd );
				return PACKET_PARAM[i].szMsgFormat;
			}
		}
//		assert(0);
//		Log( "找不到包定义:%d，可能与通信方程序版本不同！", nCmd );
		return NULL;
	}

	return PACKET_PARAM[_PacketIndexFastTable[nCmd]].szMsgFormat;
//	return _GetCmdFormat( nCmd, PACKET_PARAM, sizeof( PACKET_PARAM ) / sizeof( CmdInfo ) );	
}



