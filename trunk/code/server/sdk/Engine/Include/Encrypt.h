#pragma once

#include "EngineDefine.h"

////////////////////
// ��һ���ַ�������/����
void ENGINE_GLOBAL StrEncrypt( char* str, int nlen );
// ��һ�ָ���һЩ�ٶ���һЩ�ļ���/�����㷨
void ENGINE_GLOBAL StrEncryptTEA( char* str, int nlen );
// �����ӵ��ٶȸ����ļ���/�����㷨
void ENGINE_GLOBAL StrEncryptDM5( char* str, int nlen );
////////////////////
