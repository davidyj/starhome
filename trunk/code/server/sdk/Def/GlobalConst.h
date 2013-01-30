/*
 * 本文件包含DataServer所需要的一些系统常量。集中在这里，便于调整，以便优化性能
 * 这个头文件把其它头文件的宏重新定义了
 * 使用方法:
 * 
 * 1 引用这个头文件的头文件把本文件作为最后一个include文件
 */

#ifndef GLOBAL_CONST_H
#define GLOBAL_CONST_H

////////////////////////Gamenetcommon/////////////////////////////////////////
//DataDefine.h
//#define BASE_BUFFER_MAX		512
//#define SEND_BUFFER_SIZE	(BASE_BUFFER_MAX)
//#define RECV_BUFFER_SIZE	(BASE_BUFFER_MAX*2)
//#define CHUNK_BUFFER_SIZE	(BASE_BUFFER_MAX*2)

//数据压缩之前最大的长度
//#define COMPRESSION_BUFFER_LEN (BASE_BUFFER_MAX*2)

//最多128个PACKET_COMMAND对象压缩成一个PACKET_COMMAND
#define COMPRESSION_BUFFER_MAX_PKT_CNT 100

#define PACKET_BUFFER_SIZE (1024-sizeof(int))

//字符型消息报大小(base64加密)，长度 = PACKET_BUFFER_SIZE*4/3 + 包头长度 + 若干分隔符 + '\0'
#define PACKET_STRING_SIZE	2048		

//Chunk define
//const int CHUNK_COUNT_MAX	= 10240;
//PacketDefine.h
//#define MAX_PAYLOAD_LEN (PACKET_BUFFER_SIZE - PACKET_COMMAND::DATA_PARAM)
//#ifdef WIN32
//iocp内存池的参数
//g_overlappedpool内存池的初始对象个数
//#define OVERLAPED_INIT_COUNT 2000
//增长
//#define OVERLAPED_INCRU_COUNT 2
//#define CONTEXT_INIT_COUNT 10
//#define CONTEXT_INCRU_COUNT 1
//#endif //WIN32
////////////////////////Gamenetcommon ends/////////////////////////////////////////

//CompressionBufferMgr.h
/*
 * 用于压缩
 * 输入：若干个PACKET_COMMAND类型的对象
 * note:这个类的客户需要主动调用Send()函数来发送数据
 */



#endif //CONST_H

