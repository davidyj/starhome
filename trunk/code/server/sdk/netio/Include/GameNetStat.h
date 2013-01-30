#pragma once
#include "EngineDefine.h"
#include "PacketDefine.h"
#include "utllinkedlist.h"
#include "dbg.h"

struct  PACKETSTAT
{
	int		nTime;
	WORD	wType;
};

struct PACKETCOUNTS
{
	WORD	wType;
	int		nCount;
};

// these tow are declared in file GameNet.cpp 
extern CUtlLinkedList<PACKETSTAT*> s_PacketStatList;
extern CUtlLinkedList<PACKETCOUNTS*> s_PacketCountList;

GAMENETCOMMON_GLOBAL void PacketCount(PACKET_COMMAND* pPacket);
GAMENETCOMMON_GLOBAL void GetPacketStat(WORD wType = NULL ,int nFreq = 0);
