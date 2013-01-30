#pragma once
#include "../Port/config.h"
#ifdef _MINICLIENT		//动态下载 需要以下库
#include <map>
#include <string>
#include <vector>
using std::map;
using std::string;
using std::vector;
#include <WinInet.h>   //主要使用 WinInet 库来实现 HTTP 下载
#pragma comment(lib,"wininet.lib")
#endif
//#ifdef WIN32
//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#endif
