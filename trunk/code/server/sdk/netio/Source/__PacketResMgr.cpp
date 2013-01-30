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
//PacketPoolÿ���̶߳�Ӧһ������ �������Լ�
CPacketPool::CPacketPool()
{

}

CPacketPool::~CPacketPool()
{

}
//����������Ϣ����Ϣ��
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
//���͵���Ϣ�� by zhao
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
//PacketPoolÿ���̶߳�Ӧһ������ �������Լ�
CSendPacketPool::CSendPacketPool()
{
}

CSendPacketPool::~CSendPacketPool()
{

}
//����������Ϣ����Ϣ��
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
