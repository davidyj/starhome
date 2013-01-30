#ifndef CONFIG_WIN32_H
#define CONFIG_WIN32_H

#ifndef WIN32
#define WIN32
#endif

#ifndef _WIN32
#define _WIN32
#endif

#define USE_INTEL_ASM 1
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>


inline int  NetWorkStart(void)
{
	WSAData data;
	if(WSAStartup(MAKEWORD(2,2),&data))
	{
		printf("wsastarup初始化失败！\n");
		return 0;
	}
	return 1;	
};

inline void	NetWorkClose(void)
{
	WSACleanup();
}


/*
 * return value: whether we set nonblock succ
 */
inline int SetNonblock(SOCKET sockfd)
{
	DWORD NonBlock = 1;
	if (ioctlsocket(sockfd, FIONBIO, &NonBlock) == SOCKET_ERROR)
		return 0;
	else
		return 1;

};

inline int Setblock(SOCKET sockfd)
{
	DWORD NonBlock = 0;
	if (ioctlsocket(sockfd, FIONBIO, &NonBlock) == SOCKET_ERROR)
		return 0;
	else
		return 1;

};



// warning disable 
#pragma warning(disable : 4100) // unreferenced formal parameter	
#pragma warning(disable : 4127) // Conditional expression is constant
#pragma warning(disable : 4201) // nonstandard extension used : nameless struct/union					
#pragma warning(disable : 4211) //warning C4211: 使用了非标准扩展 : 将“extern”重新定义为“static”
#pragma warning(disable : 4244) // conversion to float, possible loss of data
#pragma warning(disable : 4251) // need dll interface 
#pragma warning(disable : 4389) // signed/unsigned mismatch                 
#pragma warning(disable : 4702) // unreachable code in inline expanded function	
#pragma warning(disable : 4995) // 名称被标记为 #pragma deprecated
#pragma warning(disable : 4996) //The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name
#pragma warning(disable : 4819) //该文件包含不能在当前代码页(936)中表示的字符。请将该文件保存为 Unicode 格式以防止数据丢失
#endif
