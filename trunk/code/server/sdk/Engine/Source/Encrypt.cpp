#include "../stdafx.h"
#include "Encrypt.h"

// ������
//unsigned char ENCRYPT_CODE[10] = { 0x11, 0x01, 0x09, 0x19, 0x80, 0x08, 0x06, 0x03, 0x10, 0x88 };
unsigned char ENCRYPT_CODE[10] = { 0xe1, 0xf1, 0x39, 0x19, 0x80, 0x08, 0xc6, 0x03, 0x19, 0x8a };


////////////////////
// ��һ���ַ�������/����
void StrEncrypt( char* str, int nlen )
{
	for( int i=0; i<nlen; i++ )
	{
		str[i] = str[i] ^ ENCRYPT_CODE[i%10];	// ���xor
	}
}
////////////////////
/*
////////////////////
// ��һ�ָ���һЩ�ٶ���һЩ�ļ���/�����㷨
void StrEncryptTEA( char* str, int nlen )
{
}
////////////////////

////////////////////
// �����ӵ��ٶȸ����ļ���/�����㷨
void StrEncryptDM5( char* str, int nlen )
{
}
////////////////////
*/
