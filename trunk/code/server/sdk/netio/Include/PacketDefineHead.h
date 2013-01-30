//#pragma	  once
#ifndef __PACKETDEFINE__
#define __PACKETDEFINE__
#pragma once
#include "PacketDefine.h"

enum PACKET_DEFINE_HEAD
{
	// 公共的
	PACKET_TYPE_COMMAND_REGISTER_SERVER				= 1,				// 向自己所映射的主服务器发送消息
	PACKET_TYPE_COMMAND_NET_BREAK,										// 网络中断
	CORE_LIVING,														// 心跳
	CORE_LIVING_RETURN,													// 心跳回复
	PACKET_KICK_USER,													// 强制玩家下线

	
	PACKET_END,
};


static const CmdInfo PACKET_PARAM[] =
{
	{ PACKET_TYPE_COMMAND_REGISTER_SERVER,					"%d%d%d%n"				},//%d:ServerID %d:ServerType %d:ServerPort %n:ServerIP
	{ PACKET_TYPE_COMMAND_NET_BREAK,						"%d"					},//%d:Break Socket
	{ CORE_LIVING,											""						},//%d:
	{ CORE_LIVING_RETURN,									"%d%l"					},//%d:Time
	{ PACKET_KICK_USER,										"%m"					},//%l:UserName

};

#endif
