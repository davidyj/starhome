#pragma once
#include "StdAfx.h"
#include "PacketResMgr.h"
#include "NetBuffer.h"

CPacketPool &PacketPool()
{
	static CPacketPool pool;
	return pool;
}

PACKET_COMMAND* g_AllocPacket()
{	
 	return PacketPool().Alloc();	
}
void g_FreePacket(PACKET_COMMAND* pPacket)
{		
 	PacketPool().Free(pPacket);
}
//////////////////////////////////////////////////////////////////////////
//PacketPool每个线程对应一个所以 加锁可以简化
CPacketPool::CPacketPool()
{

}

CPacketPool::~CPacketPool()
{

}
//创建保存消息的消息池
void CPacketPool::Create(int nPacketMax)
{
	Assert(nPacketMax);
	if(nPacketMax <=0 )
		return;	

	m_PacketTableMax = nPacketMax;

	if(!m_PacketPool.Init("PacketPool", m_PacketTableMax))
	{
		return;
	}
}

PACKET_COMMAND* CPacketPool::Alloc()
{	
	return m_PacketPool.Alloc();
}

void CPacketPool::Free(PACKET_COMMAND* pPacket)
{
	if(pPacket)
		m_PacketPool.Free(pPacket);
}


//////////////////////////////////////////////////////////////////////////
//发送的消息池 by zhao
CSendPacketPool &SendPacketPool()
{
	static CSendPacketPool pool;
	return pool;
}

PACKET_COMMAND* g_AllocSendPacket()
{	
	return SendPacketPool().Alloc();	
}
void g_FreeSendPacket(PACKET_COMMAND* pPacket)
{		
	SendPacketPool().Free(pPacket);
}
//////////////////////////////////////////////////////////////////////////
//PacketPool每个线程对应一个所以 加锁可以简化
CSendPacketPool::CSendPacketPool()
{
}

CSendPacketPool::~CSendPacketPool()
{

}
//创建保存消息的消息池
void CSendPacketPool::Create(int nPacketMax)
{
	Assert(nPacketMax);
	if(nPacketMax <=0 )
		return;	

	m_PacketTableMax = nPacketMax;

	if(!m_SendPacketPool.Init("PacketPool", m_PacketTableMax))
	{
		return;
	}
}

PACKET_COMMAND* CSendPacketPool::Alloc()
{	
	return m_SendPacketPool.Alloc();
}

void CSendPacketPool::Free(PACKET_COMMAND* pPacket)
{
	if(pPacket)
		m_SendPacketPool.Free(pPacket);
}
