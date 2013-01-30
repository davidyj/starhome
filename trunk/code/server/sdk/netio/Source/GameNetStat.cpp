#include "StdAfx.h"

#ifdef WIN32
#include <MMSystem.h>
#endif

#include "GameNetStat.h"

#pragma comment(lib,"winmm.lib")



void PacketCount(PACKET_COMMAND* pPacket)
{
	static int			nStartTime		= timeGetTime();
	PACKETSTAT*			pPackStat		= new PACKETSTAT;
	PACKETCOUNTS*		pPackCount		= new PACKETCOUNTS;
	pPackStat->wType					= pPacket->Type();
	pPackCount->wType					= pPacket->Type();
	pPackCount->nCount					= 1;
	int nNowTime = timeGetTime();
	pPackStat->nTime					= nNowTime - nStartTime;
	nStartTime = nNowTime;
	s_PacketStatList.AddToTail(pPackStat);
	if (s_PacketCountList.Count() == 0)
	{
		s_PacketCountList.AddToTail(pPackCount);
	}

	for (int i = 0; i<s_PacketCountList.Count();i++)
	{
		if (pPacket->Type() == s_PacketCountList[i]->wType)
		{
			continue;
		}
		pPackCount->nCount++;
		s_PacketCountList.AddToTail(pPackCount);
	}
}

void GetPacketStat(WORD wType,int nFreq)
{
	if (!wType)
	{
		if (nFreq == 0)
		{
			for (int i = 0;i<s_PacketCountList.Count();i++)
			{
				Log("消息种类%s,收发次数%d", s_PacketCountList[i]->wType,s_PacketCountList[i]->nCount);
			}
		}
		else
		{
			static int iTime = 0;
			for (int i = 0;i<s_PacketCountList.Count();i++)
			{
				for (int j = 0;j<s_PacketStatList.Count();j++)
				{
					iTime = s_PacketStatList[j]->nTime - iTime;
					if (iTime>nFreq)
					{
						break;
					}
					if (s_PacketStatList[j]->wType == s_PacketCountList[i]->wType)
					{
						s_PacketCountList[i]->nCount++;
					}
				}
				Log("消息种类%s,在%d时间内，收发次数%d", s_PacketCountList[i]->wType,iTime,s_PacketCountList[i]->nCount);
			}
		}
	}
	else
	{
		if (nFreq == 0)
		{
			PACKETCOUNTS packCount;
			packCount.wType = wType;
			packCount.nCount = 0;
			int readHead = s_PacketStatList.Head();
			if (s_PacketStatList.IsValidIndex( readHead ))
			{
				if (s_PacketStatList[readHead]->wType == wType )
				{
					packCount.nCount++;
				}
				s_PacketStatList.Remove(readHead);
			}
			Log("消息种类%s,收发次数%d", wType,packCount.nCount);
		}
		else
		{
			static int iTime = 0;
			PACKETCOUNTS packCount;
			packCount.wType = wType;
			packCount.nCount = 0;
			int readHead = s_PacketStatList.Head();
			if (s_PacketStatList.IsValidIndex( readHead ))
			{
				iTime = s_PacketStatList[readHead]->nTime - iTime;
				if (s_PacketStatList[readHead]->wType == wType && iTime < nFreq)
				{
					packCount.nCount++;
				}
				s_PacketStatList.Remove(readHead);
			}
			Log("消息种类%s,在%d时间内，收发次数%d", wType,iTime,packCount.nCount);
		}
	}
}
