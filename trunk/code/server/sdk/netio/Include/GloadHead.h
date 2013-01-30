#pragma once 

#include "stdafx.h"
#include "utllinkedlist.h"

//00000000 0000 0001 0000000000000000 用户的id
#define USERIDTYPE 65536
//00000000 0000 0000 1111111111111111 
#define USERID 65535

//00000000 0000 1111 0000000000000000
#define GETLOGIN 983040

//00000000 1111 0000 0000000000000000 场景服务器的id
#define GETSCENE 15728640

// 得到预算后的登陆服务器的值
#define SETLOGININDEX( nn )		nn << 16
// 得到预算后的场景的索引
#define SETSCENEINDEX( nn )		nn << 24


#define SOCKETMAX		10						// conser管理socket得数组最大值

#define PACKCOUNTMAX	8193
#define PACKINDEXMAX	3000					// 网络层用来缓存数据的数组
#define NET_BUFFER_SIZE	409600

#define MAXSERVERCOUNTS 500					//下级服务器的最大数
#define IP_SIZE			50					//ip字符串长度
#define INVALID_NUM		-1					// 无效的值


typedef CUtlLinkedList<SOCKET,int>	SOCKETLIST;





