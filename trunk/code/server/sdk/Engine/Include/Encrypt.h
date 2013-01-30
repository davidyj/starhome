#pragma once

#include "EngineDefine.h"

////////////////////
// 给一个字符串加密/解密
void ENGINE_GLOBAL StrEncrypt( char* str, int nlen );
// 另一种复杂一些速度慢一些的加密/解密算法
void ENGINE_GLOBAL StrEncryptTEA( char* str, int nlen );
// 更复杂的速度更慢的加密/解密算法
void ENGINE_GLOBAL StrEncryptDM5( char* str, int nlen );
////////////////////
