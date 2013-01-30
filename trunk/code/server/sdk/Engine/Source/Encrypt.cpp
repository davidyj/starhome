#include "../stdafx.h"
#include "Encrypt.h"

// 密码字
//unsigned char ENCRYPT_CODE[10] = { 0x11, 0x01, 0x09, 0x19, 0x80, 0x08, 0x06, 0x03, 0x10, 0x88 };
unsigned char ENCRYPT_CODE[10] = { 0xe1, 0xf1, 0x39, 0x19, 0x80, 0x08, 0xc6, 0x03, 0x19, 0x8a };


////////////////////
// 给一个字符串加密/解密
void StrEncrypt( char* str, int nlen )
{
	for( int i=0; i<nlen; i++ )
	{
		str[i] = str[i] ^ ENCRYPT_CODE[i%10];	// 异或xor
	}
}
////////////////////
/*
////////////////////
// 另一种复杂一些速度慢一些的加密/解密算法
void StrEncryptTEA( char* str, int nlen )
{
}
////////////////////

////////////////////
// 更复杂的速度更慢的加密/解密算法
void StrEncryptDM5( char* str, int nlen )
{
}
////////////////////
*/
