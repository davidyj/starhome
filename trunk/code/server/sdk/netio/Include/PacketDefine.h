#pragma once
#pragma warning(disable:4312) // warning C4312: “类型转换” : 从“int”转换到更大的“int *”
///////////////////////////////////////////////////////////////////////////
//
#include <stdarg.h>
#include <string.h>
#include "Gamenetcommondefine.h"
#include "dbg.h"
#include "utllinkedlist.h"
#include "GlobalConst.h"

#include "GLock.h"

const int BUFFER_SIZE		= 800;						//传送二进制数据是 指定的大小
//////////////////////////////////////////////////////////////////////////
//
const char BYTE_FLAG	= 1;
const char WORD_FLAG	= 2;
const char INT_FLAG		= 3;
const char INT64_FLAG	= 4;
const char FLOAT_FLAG	= 5;
const char STRING_FLAG	= 6;
const char WSTRING_FLAG	= 7;
const char BUFFER_FLAG	= 8;
const char MAX_STRING_FLAG = 9;
const char MEDIAL_STRING_FLAG = 10;

const int SHORT_STRING_LEN  = 32;
const int DOUBLE_STRING_LEN = 64;
const int MEDIAL_STRING_LEN = 128;
const int LONG_STRING_LEN = 200;
const int HIGH_STRING_LEN = 512;
//////////////////////////////////////////////////////////////////////////
//
const int DATA_BOARDCAST_OFF	= 0;
const int DATA_BOARDCAST_ON		= 1;


inline WORD Caluation_CRC16(BYTE buff[], int nSize)
{
	WORD m_Crc;
	WORD m_InitCrc = 0xffff;
	unsigned short i,j;
	for(i=0; i<nSize; i++)
	{
		m_InitCrc ^= buff[i];
		for(j=0; j<8; j++)
		{
			m_Crc = m_InitCrc;
			m_InitCrc >>= 1;
			if(m_Crc&0x0001)
			m_InitCrc ^= 0xa001;
		}
	}
	return m_InitCrc;
}

//inline void AddCRC16Flag(/*void*& pParam,*/void* begin_pParam,WORD wSize)
//{
//	WORD CRC16Flag = Caluation_CRC16((BYTE*)begin_pParam,wSize);
//	*(WORD*)((BYTE*)begin_pParam - sizeof(WORD)) = CRC16Flag;
////	pParam = (WORD*)pParam + sizeof(WORD);
////	wSize += sizeof(WORD);
//}

//inline void PassEndFlag(void*& pParam,int& nSize)
//{
//	pParam = (WORD*)pParam + sizeof(WORD);
//	nSize += sizeof(WORD);
//}


inline void AppendFlag( void *& pParam, BYTE bFlag, WORD & wSize )
{
	*(char*)pParam = bFlag;
	pParam = (char*)pParam + sizeof( char );
	wSize += sizeof( char );
}

inline BOOL CheckFlag( void *& pParam, BYTE bFlag, int & nSize ,int nType)//change by zhao  消息参数类型不匹配时，根据传入的类型可以快速定位
{
	AssertMsg3( *(char*)pParam == bFlag, "参数类型不匹配！正确类型(%d) 消息参数(%d) 消息type(%d)", bFlag, *(char*)pParam,nType);
	if( *(char*)pParam != bFlag )
	{
		Log( "参数类型不匹配！正确类型(%d) 消息参数(%d) 消息type(%d)", bFlag, *(char*)pParam ,nType);
		return FALSE;
	}
	pParam = (char*)pParam + sizeof( char );
	nSize += sizeof( char );
	return TRUE;
}

inline int GetParamLen(LPCTSTR lpszFormat)
{
	int nDataSize = 0;
	while( *lpszFormat )
	{
		Assert(*lpszFormat == '%');
		lpszFormat++;        // skip '%'

		switch( *lpszFormat )
		{
		case 'c': // BYTE
		case 'b': // BYTE
			nDataSize += sizeof( char );
			nDataSize++;
			lpszFormat++;
			break;
		case 'w': // WORD
			nDataSize += sizeof( short );
			nDataSize++;
			lpszFormat++;
			break;
		case 'd': // int
		case 'i': // int
			nDataSize += sizeof( int );
			nDataSize++;
			lpszFormat++;
			break;
		case 'l': // int64
			nDataSize += sizeof( __int64 );
			nDataSize++;
			lpszFormat++;
			break;
		case 'f': // float
			nDataSize += sizeof( float );
			nDataSize++;
			lpszFormat++;
			break;
		case 's':
			nDataSize += LONG_STRING_LEN;
			nDataSize++;
			lpszFormat++;
			break;
		case 'h':
			nDataSize += HIGH_STRING_LEN;
			nDataSize++;
			lpszFormat++;
			break;
		case 't': // wchar_t*
			nDataSize += sizeof( wchar_t );
			nDataSize++;
			lpszFormat++;
			break;
		case 'u':
			nDataSize += BUFFER_SIZE;
			nDataSize++;
			lpszFormat++;
			break;
		case 'n':
			nDataSize += SHORT_STRING_LEN;
			nDataSize++;
			lpszFormat++;
			break;
		case 'o':
			nDataSize += DOUBLE_STRING_LEN;
			nDataSize++;
			lpszFormat++;
			break;
		case 'm':
			nDataSize += MEDIAL_STRING_LEN;
			nDataSize++;
			lpszFormat++;
			break;
		default:
			Assert( 0 );
			break;
		}
	}

	// all ok
	return nDataSize;
}

static bool _PacketParamSimplePrint( void * pParam, const char* lpszFormat, va_list pData, WORD & wSize )
{
	Assert(pData != NULL);
	Assert(lpszFormat != NULL);
	int checklen  = 0; //用来验证字符串长度
	wSize = 0;
	while( *lpszFormat )
	{
		Assert(*lpszFormat == '%');
		lpszFormat++;        // skip '%'
		checklen = 0;
		switch( *lpszFormat )
		{
		case 'c': // BYTE
		case 'b': // BYTE
			AssertValidReadWritePtr( pData, sizeof( char ) );

			AppendFlag( pParam, BYTE_FLAG, wSize );

			*(char*)pParam = va_arg(pData, int);
			pParam = (char*)pParam + sizeof( char );
			wSize += sizeof( char );
			lpszFormat++;
			break;
		case 'w': // WORD
			AssertValidReadWritePtr( pData, sizeof( short ) );

			AppendFlag( pParam, WORD_FLAG, wSize );

			*(short*)pParam = va_arg(pData, int);
			pParam = (char*)pParam + sizeof( short );
			wSize += sizeof( short );
			lpszFormat++;
			break;
		case 'd': // int
		case 'i': // int
			AssertValidReadWritePtr( pData, sizeof( int ) );

			AppendFlag( pParam, INT_FLAG, wSize );

			*(int*)pParam = va_arg(pData, int);
			pParam = (char*)pParam + sizeof( int );
			wSize += sizeof( int );
			lpszFormat++;
			break;
		case 'l': // int64
			AssertValidReadWritePtr( pData, sizeof( __int64 ) );

			AppendFlag( pParam, INT64_FLAG, wSize );

			*(__int64*)pParam = va_arg(pData, __int64);
			pParam = (char*)pParam + sizeof( __int64 );
			wSize += sizeof( __int64 );
			lpszFormat++;
			break;
		case 'f': // float
			AssertValidReadWritePtr( pData, sizeof( float ) );

			AppendFlag( pParam, FLOAT_FLAG, wSize );

			*(float*)pParam = va_arg(pData, double);
			pParam = (char*)pParam + sizeof( float );
			wSize += sizeof( float );
			lpszFormat++;
			break;
//		case 'n':
//		case 'm':
		case 's': // 200
			{
// 				AssertValidReadWritePtr( pData, sizeof( char ) );
//
// 				AppendFlag( pParam, STRING_FLAG, wSize );
//
// 				char * pString = (char*)va_arg(pData, char*);
//
// 				if(strlen(pString) >= LONG_STRING_LEN)
// 					strncpy((char*)pParam,pString,LONG_STRING_LEN);
// 				else
// 					strncpy((char*)pParam,pString,strlen(pString) + 1);
// 				pParam = (char*)pParam + LONG_STRING_LEN;
// 				wSize += LONG_STRING_LEN;
// 				lpszFormat++;
//				break;

				AssertValidReadWritePtr( pData, sizeof( char ) );
				AppendFlag( pParam, STRING_FLAG, wSize );
				char * pString = (char*)va_arg(pData, char*);
				do
				{
					AssertValidReadPtr( pString, sizeof( char ) );

					*(char*)pParam = *pString;
					pParam = (char*)pParam + 1;
					wSize += sizeof( char );

					if( checklen++ >= LONG_STRING_LEN )
						return false;
				}
				while( *pString++ );

				//不足最大长度的补零
				while(LONG_STRING_LEN - checklen > 0)
				{
					*(char*)pParam = '\0';
					pParam = (char*)pParam + 1;
					wSize += sizeof( char );
					checklen++;
				}

				lpszFormat++;
			}
			break;
		case 'h': // 400
			{
				AssertValidReadWritePtr( pData, sizeof( char ) );
				AppendFlag( pParam, STRING_FLAG, wSize );
				char * pString = (char*)va_arg(pData, char*);
				do
				{
					AssertValidReadPtr( pString, sizeof( char ) );

					*(char*)pParam = *pString;
					pParam = (char*)pParam + 1;
					wSize += sizeof( char );

					if( checklen++ >= HIGH_STRING_LEN )
						return false;
				}
				while( *pString++ );

				//不足最大长度的补零
				while(HIGH_STRING_LEN - checklen > 0)
				{
					*(char*)pParam = '\0';
					pParam = (char*)pParam + 1;
					wSize += sizeof( char );
					checklen++;
				}

				lpszFormat++;
			}
			break;
		case 't': // wchar_t*
			{
				AssertValidReadWritePtr( pData, sizeof( wchar_t ) );

				AppendFlag( pParam, WSTRING_FLAG, wSize );

				wchar_t * pString = (wchar_t*)va_arg(pData, wchar_t*);
				do
				{
					AssertValidReadPtr( pString, sizeof( wchar_t ) );

					*(wchar_t*)pParam = *pString;
					pParam = (wchar_t*)pParam + 1;
					wSize += sizeof( wchar_t );
				}
				while( *pString++ );
				lpszFormat++;
			}
			break;
		case 'u':
			{
				AssertValidReadWritePtr( pData, BUFFER_SIZE);
				AppendFlag( pParam, BUFFER_FLAG, wSize );
				void * pBuffer = (void*)va_arg(pData, void*);
				memcpy(pParam, pBuffer, BUFFER_SIZE);
				pParam = (char*)pParam + BUFFER_SIZE;
				wSize += BUFFER_SIZE;
				lpszFormat++;
				break;
			}
 		case 'n': //32
 			{
// 				AssertValidReadWritePtr( pData, sizeof( char ) );
//
// 				AppendFlag( pParam, SHORT_STRING_LEN, wSize );
//
// 				char * pString = (char*)va_arg(pData, char*);
// 				if(strlen(pString) >= SHORT_STRING_LEN)
// 					strncpy((char*)pParam,pString,SHORT_STRING_LEN);
// 				else
// 					strncpy((char*)pParam,pString,strlen(pString) + 1);
// 				pParam = (char*)pParam + SHORT_STRING_LEN;
// 				wSize += SHORT_STRING_LEN;
// 				lpszFormat++;
// 				break;

				AssertValidReadWritePtr( pData, sizeof( char ) );
				AppendFlag( pParam, STRING_FLAG, wSize );
				char * pString = (char*)va_arg(pData, char*);
				do
				{
					AssertValidReadPtr( pString, sizeof( char ) );

					*(char*)pParam = *pString;
					pParam = (char*)pParam + 1;
					wSize += sizeof( char );

					if(checklen++ >= SHORT_STRING_LEN )
						return false;
				}
				while( *pString++ );

				//不足最大长度的补零
				while(SHORT_STRING_LEN - checklen > 0)
				{
					*(char*)pParam = '\0';
					pParam = (char*)pParam + 1;
					wSize += sizeof( char );
					checklen++;
				}

				lpszFormat++;
				break;
 			}
 		case 'o': //64
 			{
				AssertValidReadWritePtr( pData, sizeof( char ) );
				AppendFlag( pParam, STRING_FLAG, wSize );
				char * pString = (char*)va_arg(pData, char*);
				do
				{
					AssertValidReadPtr( pString, sizeof( char ) );

					*(char*)pParam = *pString;
					pParam = (char*)pParam + 1;
					wSize += sizeof( char );

					if(checklen++ >= DOUBLE_STRING_LEN )
						return false;
				}
				while( *pString++ );

				//不足最大长度的补零
				while(DOUBLE_STRING_LEN - checklen > 0)
				{
					*(char*)pParam = '\0';
					pParam = (char*)pParam + 1;
					wSize += sizeof( char );
					checklen++;
				}

				lpszFormat++;
				break;
 			}
 		case 'm'://80
 			{
// 				AssertValidReadWritePtr( pData, sizeof( char ) );
//
// 				AppendFlag( pParam, MEDIAL_STRING_FLAG, wSize );
//
// 				char * pString = (char*)va_arg(pData, char*);
// 				if(strlen(pString) >= MEDIAL_STRING_LEN)
// 					strncpy((char*)pParam,pString,MEDIAL_STRING_LEN);
// 				else
// 					strncpy((char*)pParam,pString,strlen(pString) + 1);
// 				pParam = (char*)pParam + MEDIAL_STRING_LEN;
// 				wSize += MEDIAL_STRING_LEN;
// 				lpszFormat++;
// 				break;

				AssertValidReadWritePtr( pData, sizeof( char ) );
				AppendFlag( pParam, STRING_FLAG, wSize );
				char * pString = (char*)va_arg(pData, char*);
				do
				{
					AssertValidReadPtr( pString, sizeof( char ) );

					*(char*)pParam = *pString;
					pParam = (char*)pParam + 1;
					wSize += sizeof( char );

					if(checklen++ >= MEDIAL_STRING_LEN )
						return false;
				}
				while( *pString++ );

				//不足最大长度的补零
				while(MEDIAL_STRING_LEN - checklen > 0)
				{
					*(char*)pParam = '\0';
					pParam = (char*)pParam + 1;
					wSize += sizeof( char );
					checklen++;
				}

				lpszFormat++;
				break;
 			}
		default:
			Assert( 0 );
			break;
		}
	}
//	AddCRC16Flag(/*pParam,*/begin_pParam,wSize);		//Add by xuyuan 2010-6-26
	// all ok
	return true;
}

static bool _PacketParamSimpleScan( int &nDataSize,int nType,void * pParam,const char* lpszFormat, va_list pData )
{
	Assert(pData != NULL);
	Assert(lpszFormat != NULL);

	//void* begin_pParam = pParam;

	int	checklen=0;
	nDataSize = 0;
	while( *lpszFormat )
	{
		checklen=0;
		Assert(*lpszFormat == '%');
		lpszFormat++;        // skip '%'

		switch( *lpszFormat )
		{
		case 'c': // BYTE
		case 'b': // BYTE
			AssertValidReadWritePtr( pData, sizeof( char* ) );
			AssertValidReadWritePtr( (int*)*(int*)pData, sizeof( char ) );

			if( !CheckFlag( pParam, BYTE_FLAG, nDataSize,nType ) )
				break;

			nDataSize += sizeof( char );

			*va_arg(pData, char*) = *(char*)pParam;
			pParam = (char*)pParam + sizeof( char );

			lpszFormat++;
			break;
		case 'w': // WORD
			AssertValidReadWritePtr( pData, sizeof( short* ) );
			AssertValidReadWritePtr( (int*)*(int*)pData, sizeof( short ) );

			if( !CheckFlag( pParam, WORD_FLAG, nDataSize,nType ) )
				break;

			nDataSize += sizeof( short );
			*va_arg(pData, short*) = *(short*)pParam;
			pParam = (char*)pParam + sizeof( short );
			lpszFormat++;
			break;
		case 'd': // int
		case 'i': // int
			AssertValidReadWritePtr( pData, sizeof( int* ) );
			AssertValidReadWritePtr( (int*)*(int*)pData, sizeof( int ) );

			if( !CheckFlag( pParam, INT_FLAG, nDataSize,nType ) )
				break;

			nDataSize += sizeof( int );
			*va_arg(pData, int*) = *(int*)pParam;
			pParam = (char*)pParam + sizeof( int );
			lpszFormat++;
			break;
		case 'l': // int64
			AssertValidReadWritePtr( pData, sizeof( __int64* ) );
			AssertValidReadWritePtr( (int*)*(int*)pData, sizeof( __int64 ) );

			if( !CheckFlag( pParam, INT64_FLAG, nDataSize,nType) )
				break;

			nDataSize += sizeof( __int64 );
			*va_arg(pData, __int64*) = *(__int64*)pParam;
			pParam = (char*)pParam + sizeof( __int64 );
			lpszFormat++;
			break;
		case 'f': // float
			AssertValidReadWritePtr( pData, sizeof( float* ) );
			AssertValidReadWritePtr( (int*)*(int*)pData, sizeof( float ) );

			if( !CheckFlag( pParam, FLOAT_FLAG, nDataSize,nType ) )
				break;

			nDataSize += sizeof( float );
			*va_arg(pData, float*) = *(float*)pParam;
			pParam = (char*)pParam + sizeof( float );
			lpszFormat++;
			break;
//		case 'n':
//		case 'm':
		case 's': // char*
			{
// 				AssertValidReadWritePtr( pData, sizeof( char* ) );
// 				if( !CheckFlag( pParam, STRING_FLAG, nDataSize,nType ) )
// 					break;
// 				nDataSize += LONG_STRING_LEN;
// 				void * pBuffer = va_arg(pData, void*);
// 				if(strlen((char*)pParam) <= LONG_STRING_LEN)
// 					strncpy((char*)pBuffer,(char*)pParam, strlen((char*)pParam));
// 				else
// 					strncpy((char*)pBuffer,(char*)pParam, LONG_STRING_LEN);
// 				pParam = (char*)pParam + LONG_STRING_LEN;
// 				lpszFormat++;

				AssertValidReadWritePtr( pData, sizeof( char* ) );
				if( !CheckFlag( pParam, STRING_FLAG, nDataSize ,nType) )
					break;
				char * pString = va_arg(pData, char*);
				while( *(char*)pParam )
				{
					AssertValidWritePtr( pString, sizeof( char ) );

					*pString = *(char*)pParam;
					pString++;
					pParam = (char*)pParam + 1;

					if(checklen++ >= LONG_STRING_LEN)
						return false;
				}
				//过滤掉填充的零
				while(LONG_STRING_LEN - checklen++ > 0)
				{
					pParam = (char*)pParam + 1;
				}

				nDataSize += sizeof( char ) * LONG_STRING_LEN;

				*pString = 0;
				lpszFormat++;
			}
			break;
		case 'h': // 400 char
			{
// 				AssertValidReadWritePtr( pData, sizeof( char* ) );
// 				if( !CheckFlag( pParam, STRING_FLAG, nDataSize,nType ) )
// 					break;
// 				nDataSize += LONG_STRING_LEN;
// 				void * pBuffer = va_arg(pData, void*);
// 				if(strlen((char*)pParam) <= LONG_STRING_LEN)
// 					strncpy((char*)pBuffer,(char*)pParam, strlen((char*)pParam));
// 				else
// 					strncpy((char*)pBuffer,(char*)pParam, LONG_STRING_LEN);
// 				pParam = (char*)pParam + LONG_STRING_LEN;
// 				lpszFormat++;

				AssertValidReadWritePtr( pData, sizeof( char* ) );
				if( !CheckFlag( pParam, STRING_FLAG, nDataSize ,nType) )
					break;
				char * pString = va_arg(pData, char*);
				while( *(char*)pParam )
				{
					AssertValidWritePtr( pString, sizeof( char ) );

					*pString = *(char*)pParam;
					pString++;
					pParam = (char*)pParam + 1;

					if(checklen++ >= HIGH_STRING_LEN)
						return false;
				}
				//过滤掉填充的零
				while(HIGH_STRING_LEN - checklen++ > 0)
				{
					pParam = (char*)pParam + 1;
				}

				nDataSize += sizeof( char ) * HIGH_STRING_LEN;

				*pString = 0;
				lpszFormat++;
			}
			break;
		case 't': // wchar_t*
			{
				AssertValidReadWritePtr( pData, sizeof( wchar_t* ) );

				if( !CheckFlag( pParam, WSTRING_FLAG, nDataSize,nType ) )
					break;

				wchar_t * pString = va_arg(pData, wchar_t*);
				while( *(wchar_t*)pParam )
				{
					nDataSize += sizeof( wchar_t );
					AssertValidWritePtr( pString, sizeof( wchar_t ) );

					*pString = *(wchar_t*)pParam;
					pString++;
					pParam = (wchar_t*)pParam + 1;
				}
				nDataSize += sizeof( wchar_t );
				*pString = 0;
				pParam = (wchar_t*)pParam + 1;
				lpszFormat++;
			}
			break;
		case 'u':
			{
				AssertValidReadWritePtr( pData, sizeof( char* ) );
				AssertValidReadWritePtr( (int*)*(int*)pData, BUFFER_SIZE );

				if( !CheckFlag( pParam, BUFFER_FLAG, nDataSize,nType ) )
					break;

				nDataSize += BUFFER_SIZE;

				void * pBuffer = va_arg(pData, void*);

				memcpy(pBuffer, pParam, BUFFER_SIZE);
				pParam = (char*)pParam + BUFFER_SIZE;
				lpszFormat++;
				break;

			}
		case 'n':
			{
// 				AssertValidReadWritePtr( pData, sizeof( char* ) );
// 				AssertValidReadWritePtr( (int*)*(int*)pData, SHORT_STRING_LEN );
//
// 				if( !CheckFlag( pParam, SHORT_STRING_LEN, nDataSize,nType ) )
// 					break;
//
// 				nDataSize += SHORT_STRING_LEN;
//
// 				void * pBuffer = va_arg(pData, void*);
//
// 				if(strlen((char*)pParam) <= SHORT_STRING_LEN)
// 					strncpy((char*)pBuffer,(char*)pParam, strlen((char*)pParam));
// 				else
// 					strncpy((char*)pBuffer,(char*)pParam, SHORT_STRING_LEN);
// 				pParam = (char*)pParam + SHORT_STRING_LEN;
// 				lpszFormat++;
// 				break;
				AssertValidReadWritePtr( pData, sizeof( char* ) );
				if( !CheckFlag( pParam, STRING_FLAG, nDataSize ,nType) )
					break;
				char * pString = va_arg(pData, char*);
				while( *(char*)pParam )
				{
					AssertValidWritePtr( pString, sizeof( char ) );

					*pString = *(char*)pParam;
					pString++;
					pParam = (char*)pParam + 1;

					if(checklen++ >= SHORT_STRING_LEN)
						return false;
				}
				//过滤掉填充的零
				while(SHORT_STRING_LEN - checklen++ > 0)
				{
					pParam = (char*)pParam + 1;
				}
				nDataSize += sizeof( char ) * SHORT_STRING_LEN;
				*pString = 0;
				lpszFormat++;
				break;
			}
		case 'o':
			{
				AssertValidReadWritePtr( pData, sizeof( char* ) );
				if( !CheckFlag( pParam, STRING_FLAG, nDataSize ,nType) )
					break;
				char * pString = va_arg(pData, char*);
				while( *(char*)pParam )
				{
					AssertValidWritePtr( pString, sizeof( char ) );

					*pString = *(char*)pParam;
					pString++;
					pParam = (char*)pParam + 1;

					if(checklen++ >= DOUBLE_STRING_LEN)
						return false;
				}
				//过滤掉填充的零
				while(DOUBLE_STRING_LEN - checklen++ > 0)
				{
					pParam = (char*)pParam + 1;
				}
				nDataSize += sizeof( char ) * DOUBLE_STRING_LEN;
				*pString = 0;
				lpszFormat++;
				break;
			}

		case 'm':
			{
// 				AssertValidReadWritePtr( pData, sizeof( char* ) );
// 				AssertValidReadWritePtr( (int*)*(int*)pData, MEDIAL_STRING_FLAG );
//
// 				if( !CheckFlag( pParam, MEDIAL_STRING_FLAG, nDataSize,nType ) )
// 					break;
//
// 				nDataSize += MEDIAL_STRING_LEN;
//
// 				void * pBuffer = va_arg(pData, void*);
//
// 				if(strlen((char*)pParam) <= MEDIAL_STRING_LEN)
// 					strncpy((char*)pBuffer,(char*)pParam, strlen((char*)pParam));
// 				else
// 					strncpy((char*)pBuffer,(char*)pParam,MEDIAL_STRING_LEN);
// 				pParam = (char*)pParam + MEDIAL_STRING_LEN;
// 				lpszFormat++;
// 				break;

				AssertValidReadWritePtr( pData, sizeof( char* ) );
				if( !CheckFlag( pParam, STRING_FLAG, nDataSize ,nType) )
					break;
				char * pString = va_arg(pData, char*);
				while( *(char*)pParam )
				{
					AssertValidWritePtr( pString, sizeof( char ) );

					*pString = *(char*)pParam;
					pString++;
					pParam = (char*)pParam + 1;

					if(checklen++ >= MEDIAL_STRING_LEN)
						return false;
				}
				//过滤掉填充的零
				while(MEDIAL_STRING_LEN - checklen++ > 0)
				{
					pParam = (char*)pParam + 1;
				}
				nDataSize += sizeof( char ) * MEDIAL_STRING_LEN;
				*pString = 0;
				lpszFormat++;
				break;
			}
		default:
			Assert( 0 );
			assert(0);
			Log( "_PacketParamSimpleScan %d %d", nType,*lpszFormat );
			break;
		}
	}
	//if(!CheckEndFlag(pParam,begin_pParam,nDataSize))
	//{
	//	Log("不一致\n");
	//}
	//else
	//{
	//	Log("一致\n");
	//}
	//PassEndFlag(pParam,nDataSize);			//Add by xuyuan 2010-6-26
	// all ok
	return true;
}

struct CmdInfo
{
	int			nCmd;
	const char*     szMsgFormat;
};

void PacketDefineInit();

LPCSTR GAMENETCOMMON_GLOBAL GetCmdFormat( int nCmd );

//#define CHECK_PACKET_SEND(Packet)\
//	bool bSendOK = Packet.PacketOver();\
//	if (bSendOK == false)\
//	{\
//		Log("CHECK_PACKET_SEND Failed ......  PacketID = %d",Packet.Type());\
//	}
//
//
//#define  CHECK_PACKET_RECV(Packet)\
//	AssertMsg(Packet,"CHECK_PACKET_RECV  ......  Packet==NULL");\
//	bool bRecvOK = Packet->CheckRecvPacket();\
//	if (bRecvOK == false)\
//	{\
//		Log("CHECK_PACKET_RECV Failed ......  PacketID = %d",Packet->Type());\
//	}


#pragma warning (push)

struct PACKET_COMMAND
{
public:
	int m_Ref;
	int nNetid;			// 发送的网络id,在接受Packet时设置
	WORD nSize; //消息数据区大小
	//////////////////////////////////////////
	////	Packet 数据结构定义：
	////	网络发送和接收的消息数据保存在 pParam 内存块中
	////	其中 HEAD_PSIZE 为消息长度数据的起始位置，长度数据占一个WORD
	////		 HEAD_PTYPE 为消息类型数据的起始位置，类型数据占一个WORD
	////		 DATA_PARAM 为消息内容数据的其实位置，
	////	消息总长度不超过 PACKET_BUFFER_SIZE
	//////////////////////////////////////////
	static const BYTE HEAD_PSIZE = 0;
	static const BYTE HEAD_PID	 = 2;
	static const BYTE HEAD_BOARDCAST = 10;	//广播位
	static const BYTE HEAD_PTYPE = 12;
	static const BYTE DATA_PCRC16Flag = 14; //数据校验位
	static const BYTE DATA_PARAM = 16;
	BYTE pParam[PACKET_BUFFER_SIZE];	// 消息缓冲

	PACKET_COMMAND( )
	{
		memset((void*)pParam,0,PACKET_BUFFER_SIZE*sizeof(BYTE));
		m_Ref = 0;
		nNetid = -1;
		nSize = 0;
		SetSize(0);
		SetType(0);
		SetPacketPID(0xFFFFFFFF);
		SetBoardCast(DATA_BOARDCAST_OFF);
	}

	inline void	Init()
	{
		nNetid = -1;
		SetSize(0);
		SetType(0);
		SetPacketPID(0xFFFFFFFF);
		m_Ref = 0;		//最好放到最后面,否则可能会被别人先用
		nSize = 0;
		SetBoardCast(DATA_BOARDCAST_OFF);
	}

	inline void			SetNetID(int netid) { nNetid = netid; }
	inline WORD			Size()				{ return *(WORD*)(pParam + HEAD_PSIZE);	}
	inline static WORD	HeadSize()			{ return DATA_PARAM - HEAD_PSIZE;}
	inline int			DataSize( )			{ return Size() - HeadSize(); }
	inline int			PacketSize()		{ return Size() + sizeof(int);}			//Packet + nNetID的长度
	inline BYTE*		Data()				{ return pParam + DATA_PARAM;}
	inline WORD			Type()				{ return *(WORD*)(pParam + HEAD_PTYPE); }    //设置包头
	inline WORD			CRC16Flag()			{ return *(WORD*)(pParam + DATA_PCRC16Flag);}
	inline UINT64		PacketPID()			{ return *(UINT64*)(pParam + HEAD_PID); }
	inline bool			BoardCast()			{ return *(BYTE*)(pParam + HEAD_BOARDCAST) == DATA_BOARDCAST_ON; }


	inline int			GetNetID()			{ return nNetid;}
	inline int			GetSocket()			{ return nNetid;}
	inline void			SetSize(WORD wSize) { *(WORD*)(pParam + HEAD_PSIZE) = wSize;}
	inline void			SetType(WORD wType) { *(WORD*)(pParam + HEAD_PTYPE) = wType;}
	inline void			SetPacketPID(UINT64 PID)	{*(UINT64*)(pParam + HEAD_PID) = PID;}
	inline void         SetCRC16Flag(WORD CRC16)	{*(WORD*)(pParam + DATA_PCRC16Flag) = CRC16;}
	inline void			SetBoardCast(BYTE flag)		{*(BYTE*)(pParam + HEAD_BOARDCAST) = flag;}

	inline void CopyFrom(PACKET_COMMAND* pPacket)
	{
		nNetid = pPacket->nNetid;
		memcpy(pParam, pPacket->pParam, pPacket->Size());
	}

	//重新设置本对象
	inline void Copy(int sock, unsigned char* buffer, unsigned int length)
	{
		nNetid = sock;
		if (PACKET_BUFFER_SIZE < length)
			return ;
		memcpy(pParam, buffer, length);
	}

	inline bool SetParam( WORD par_wType, const char * pFormat, ... )
	{
		SetType( par_wType );
		WORD wSize;
		va_list pValue;
		va_start( pValue, pFormat );
		if(!_PacketParamSimplePrint( pParam + DATA_PARAM, pFormat, pValue, wSize ))
		{
			Assert(0);
			Log("_PacketParamSimplePrint错误,消息type:%d,格式:%s",Type(),pFormat);  // by zhao
			return false;
		}

		//add by xuyuan 2010-7-5
		//WORD CRC16 = Caluation_CRC16(pParam +DATA_PARAM,wSize);

		wSize += HeadSize();
		Assert(wSize<=PACKET_BUFFER_SIZE);
		if(wSize > PACKET_BUFFER_SIZE)
		{
			SetSize(0);
			return false;
		}
		SetSize(wSize);

		//
		WORD CRC16 = 0;
		Caluation_CRC16(CRC16);
		SetCRC16Flag(CRC16);

		va_end( pValue );
		return true;
	}

	inline BOOL IsSameDataSize( int nSize )
	{
		return DataSize( ) == nSize;
	}

	// 读取全部数据需要判断大小察看数据读取是否正确
	inline int GetParam( const char * pFormat, ... )
	{
		va_list pValue;
		va_start( pValue, pFormat );
		int wRealDataSize = 0;
		if(!_PacketParamSimpleScan( wRealDataSize,Type(), pParam + DATA_PARAM, pFormat, pValue ))
		{
			Assert(0);
			Log("_PacketParamSimpleScan错误,消息type:%d,格式:%s",Type(),pFormat);  //by zhao
			return false;
		}
		WORD wPacketDataSize = Size() - HeadSize();
		va_end( pValue );
		//Assert( wRealDataSize == wPacketDataSize );
		if( wRealDataSize != wPacketDataSize )
			Log( "GetParam %d %s", Type(), pFormat );

		return wRealDataSize;
	}

	// 只读取一部分数据所以不用判断大小 不用检测
	inline BOOL GetParamEx( const char * pFormat, ... )
	{
		va_list pValue;
		va_start( pValue, pFormat );
		int wRealDataSize = 0;
		if(!_PacketParamSimpleScan( wRealDataSize, Type(), pParam + DATA_PARAM, pFormat, pValue ))
			return FALSE;
		WORD wPacketDataSize = Size() - HeadSize();
		va_end( pValue );
		return wRealDataSize == wPacketDataSize;
	}

	inline uint64 GetPID()
	{
		uint64 pid;
		GetParamEx("%l",&pid);
		return pid;
	}

	inline int GetUID()
	{
		int uid;
		GetParamEx("%d",&uid);
		return uid;
	}

	inline WORD Caluation_CRC16(WORD & CRC16Flag)
	{
		WORD m_Crc;
		WORD m_InitCrc = 0xffff;
		BYTE* buff = Data();
		int nSize = DataSize();
		unsigned short i,j;
		for(i=0; i<nSize; i++)
		{
			m_InitCrc ^= buff[i];
			for(j=0; j<8; j++)
			{
				m_Crc = m_InitCrc;
				m_InitCrc >>= 1;
				if(m_Crc&0x0001)
					m_InitCrc ^= 0xa001;
			}
		}
		CRC16Flag = m_InitCrc;
		return CRC16Flag;
	}


	//add by lzq
	//增加一种新的发包方式，不需要设置 CmdFormat 具体应用见相关代码。
	//现只有宠物部分使用
	//void SetCommond(WORD nID) { SetType(nID); }

	//template<class T>
	//void Add(T * pData)
	//{
	//	AssertMsg(pData != NULL,"PACKET_COMMAND::Add(T * pData) ...... pData == NULL");
	//	AssertValidReadWritePtr(pData,sizeof(T));

	//	BYTE * pOffset = pParam + DATA_PARAM + nSize;
	//	memcpy((void*)pOffset,pData,sizeof(T));
	//	nSize += sizeof(T);

	//	PacketOver();
	//}
	//template<class T>
	//void Get(T * pData)
	//{
	//	AssertMsg(pData != NULL,"PACKET_COMMAND::Get(T * pData) ...... pData == NULL");
	//	AssertValidReadWritePtr(pData,sizeof(T));

	//	BYTE * pOffset = pParam + DATA_PARAM + nSize;
	//	memcpy((void*)pData,(void*)pOffset,sizeof(T));
	//	nSize += sizeof(T);
	//}


	//void AddString(char * pData)
	//{
	//	AssertMsg(pData != NULL,"PACKET_COMMAND::Add(T * pData) ...... pData == NULL");
	//	AssertValidReadWritePtr(pData,sizeof(char));

	//	//保存字符串长度,占两字节
	//	short nLen = strlen(pData);
	//	BYTE * pOffset = pParam + DATA_PARAM + nSize;
	//	memcpy((void *)pOffset,(void *)&nLen,sizeof(nLen));
	//	pOffset += sizeof(nLen);
	//	nSize += sizeof(nLen);
	//	//保存内容
	//	memcpy((void*)pOffset,(void*)pData,nLen);
	//	nSize += (sizeof(char) * nLen);

	//	PacketOver();
	//}

	//void AddString(const char * pData)
	//{
	//	AssertMsg(pData != NULL,"PACKET_COMMAND::Add(T * pData) ...... pData == NULL");
	//	AssertValidReadWritePtr(pData,sizeof(char));

	//	//保存字符串长度,占两字节
	//	short nLen = strlen(pData);
	//	BYTE * pOffset = pParam + DATA_PARAM + nSize;
	//	memcpy((void *)pOffset,(void *)&nLen,sizeof(nLen));
	//	pOffset += sizeof(nLen);
	//	nSize += sizeof(nLen);
	//	//保存内容
	//	memcpy((void*)pOffset,(void*)pData,nLen);
	//	nSize += (sizeof(char) * nLen);

	//	PacketOver();
	//}
	//void GetString(char * pData)
	//{
	//	AssertMsg(pData != NULL,"PACKET_COMMAND::Get(T * pData) ...... pData == NULL");
	//	AssertValidReadWritePtr(pData,sizeof(char));

	//	//读取字符串长度, 两字节
	//	BYTE * pOffset = pParam + DATA_PARAM + nSize;
	//	short nLen = 0;
	//	memcpy((void*)&nLen,(void*)pOffset,sizeof(nLen));
	//	AssertMsg(nLen >= 0,"PACKET_COMMAND::Get<char *> ...... nLen < 0");
	//	nSize += sizeof(nLen);
	//	pOffset += sizeof(nLen);

	//	//读取字符串内容
	//	memcpy((void*)(pData),(void*)pOffset,nLen);
	//	pData[nLen] = '\0';
	//	nSize += (sizeof(char) * nLen);
	//}


	bool PacketOver()
	{
		WORD wTotalSize = HeadSize() + nSize;

		Assert(wTotalSize <= PACKET_BUFFER_SIZE);
		if(wTotalSize > PACKET_BUFFER_SIZE)
		{
			SetSize(0);
			Log( "PacketOver : Failed(wTotalSize > PACKET_BUFFER_SIZE) ......  PacketID = %d;   Size = %d", Type(),wTotalSize);
			return false;
		}

		SetSize(wTotalSize);

		WORD CRC16 = 0;
		Caluation_CRC16(CRC16);
		SetCRC16Flag(CRC16);

		return true;
	}

	//bool CheckRecvPacket()
	//{
	//	WORD wPacketDataSize = Size() - HeadSize();
	//	if( nSize != wPacketDataSize )
	//	{
	//		Log( "CheckRecvPacket : %d     wPacketDataSize = %d;    nSize  = %d", Type(),wPacketDataSize,nSize);
	//		return false;
	//	}
	//	return true;
	//}
};

#pragma warning (pop)

inline int GetPacketDefSize(int type)
{
	LPCSTR lpszFormat = GetCmdFormat(type);
	if( lpszFormat == NULL )
	{
		return 0;
	}
	return GetParamLen((LPCTSTR)lpszFormat);
}
