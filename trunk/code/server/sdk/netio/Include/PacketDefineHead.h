//#pragma	  once
#ifndef __PACKETDEFINE__
#define __PACKETDEFINE__
#pragma once
#include "PacketDefine.h"

enum PACKET_DEFINE_HEAD
{
	// ������
	PACKET_TYPE_COMMAND_REGISTER_SERVER				= 1,				// ���Լ���ӳ�����������������Ϣ
	PACKET_TYPE_COMMAND_NET_BREAK,										// �����ж�
	CORE_LIVING,														// ����
	CORE_LIVING_RETURN,													// �����ظ�
	PACKET_KICK_USER,													// ǿ���������

	
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
