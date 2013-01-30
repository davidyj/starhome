#pragma once
#include "PacketDefine.h"
#include "GLock.h"
#include "NetBuffer.h"
#include "memorypool.h"

#define	RECV_THREAD_MAX	50

// ȫ�ֺ�������
GAMENETCOMMON_GLOBAL	PACKET_COMMAND*	g_AllocPacket();
GAMENETCOMMON_GLOBAL	void			g_FreePacket(PACKET_COMMAND* pPack);

//////////////////////////////////////////////////////////////////////////
//�յ�����Ϣ��
class GAMENETCOMMON_CLASS CPacketPool
{
public:
	CPacketPool();
	~CPacketPool();
	
	void Create(int nPacketMax);	

	PACKET_COMMAND*	Alloc();
	void			Free(PACKET_COMMAND* pPacket);	

	inline float		MemSize()		{return (float)0;}
	inline float		UsedSize()		{return (float)0;}
protected:
	int					m_PacketTableMax;				//���ݰ����������
	CGLock				m_Lock;
	CObjectMemoryPool<PACKET_COMMAND>	m_PacketPool;
};

GAMENETCOMMON_GLOBAL CPacketPool &PacketPool();


//////////////////////////////////////////////////////////////////////////
//���͵���Ϣ�� by zhao 
// ȫ�ֺ�������
GAMENETCOMMON_GLOBAL	PACKET_COMMAND*	g_AllocSendPacket();
GAMENETCOMMON_GLOBAL	void			g_FreeSendPacket(PACKET_COMMAND* pPack);

//////////////////////////////////////////////////////////////////////////
//�յ�����Ϣ��
class GAMENETCOMMON_CLASS CSendPacketPool
{
public:
	CSendPacketPool();
	~CSendPacketPool();

	void Create(int nPacketMax);	

	PACKET_COMMAND*	Alloc();
	void			Free(PACKET_COMMAND* pPacket);	

	inline float		MemSize()		{return (float)0;}
	inline float		UsedSize()		{return (float)0;}

protected:
	int					m_PacketTableMax;				//���ݰ����������
	CGLock				m_Lock;
	CObjectMemoryPool<PACKET_COMMAND>	m_SendPacketPool;
};

GAMENETCOMMON_GLOBAL CSendPacketPool &SendPacketPool();
