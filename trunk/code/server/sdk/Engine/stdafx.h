#pragma once
#include "../Port/config.h"
#ifdef _MINICLIENT		//��̬���� ��Ҫ���¿�
#include <map>
#include <string>
#include <vector>
using std::map;
using std::string;
using std::vector;
#include <WinInet.h>   //��Ҫʹ�� WinInet ����ʵ�� HTTP ����
#pragma comment(lib,"wininet.lib")
#endif
//#ifdef WIN32
//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#endif
