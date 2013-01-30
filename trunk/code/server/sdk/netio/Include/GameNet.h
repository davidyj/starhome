#pragma once
#include "StdAfx.h"
#include "utlbuffer.h"
#include "utlmap.h"
#include "PacketDefine.h"
#include "GameNetStat.h"
//#include "PacketResMgr.h"
#include "GlobalConst.h"
#include "SelectIO.h"
#include "OSNet.h"
#include "SocketHashTable.h"
#include "atomic.h"
#include "core.h"
#include "memorypool.h"
#include "Token.h"
#include "utlmap.h"

class CNet;
//////////////////////////////////////////////////////////////////////////
// �ṹ����

struct BUFFER_TO_PACKET
{
	inline void Init()
	{
		m_Ref		   = 0;
		m_sock		   = INVALID_SOCKET;
		m_WritePtr	   = 0;
		pPacket		   = NULL;
		m_RecvCompSize = 0;
		m_RecvCompIdx  = 0;
	}
	inline void Reset()
	{
		m_WritePtr	= 0;
		pPacket		= NULL;
	}

	inline bool IsHeadFull()
	{
		return m_WritePtr >= PACKET_COMMAND::HeadSize();
	}

	inline int GetHeadLeftSize()
	{
		int size = PACKET_COMMAND::HeadSize() - m_WritePtr;
		if( size < 0 )
		{
			Log("GetHeadLeftSize = %d\n",size);
			return -1;
		}
		return size;
	}

	inline int GetPacketLeftSize()
	{
		if(!IsHeadFull())
		{
			Log("GetPacketLeftSize Error Head Not Full\n");
			return -1;
		}

		return pPacket->Size() - m_WritePtr;
	}

	inline int Write(const char* buffer, int nSize)
	{
		if(m_WritePtr + nSize > (int)PACKET_BUFFER_SIZE || nSize <= 0)
		{
			//Log("m_WritePtr + nSize = %d ,%d\n",m_WritePtr,nSize);  //communityserver���ڲ�֪����ô��Ϣ����,��̫��log�˻���� ��ע�͵�
			return 0;
		}

		//int Optr = m_WritePtr;
		memcpy(pPacket->pParam + m_WritePtr, buffer, nSize);
		m_WritePtr += nSize;
		
		return nSize;
	}
	
	int				m_Ref;
	SOCKET			m_sock;
	int				m_WritePtr;		// Packet�� pParam ��дָ��
	PACKET_COMMAND*  pPacket;
	char			m_RecvCompressBuf[COMPRESS_BUFF_SIZE];
	int				m_RecvCompSize;
	int				m_RecvCompIdx;
	unsigned char	m_RecvUnCompressBuf[COMPRESS_BUFF_SIZE];

};


typedef CUtlMap<SOCKET,BUFFER_TO_PACKET*>		BUFFERTOPACKETMAP;


enum NET_IO_TYPE
{
	NET_IO_TYPE_IOCP	= 1,
	NET_IO_TYPE_SELECT,
	NET_IO_TYPE_KQUEUE,
};


//////////////////////////////////////////////////////////////////////////
//
class GAMENETCOMMON_CLASS CGameNet
{
public:
	CGameNet();
	~CGameNet();

public:
	virtual BOOL	Begin(NET_IO_TYPE Type,int nPacketPoolSize,int nListenPort,int nConnectMax,int nQueueSize,int nRecvSize,int nSendSize,int nTimeout,int nAcceptCount=0);
	virtual void	End();

	virtual void	Accept( SOCKET sock);
	virtual void	Break( SOCKET sock );
	virtual int		Send( SOCKET sock,PACKET_COMMAND* pPacket);
	virtual int		Send( SOCKET sock, char* buf, DWORD size);
	virtual int		Recv( SOCKET sock,char*	buf,DWORD nSize );
	virtual bool	addPacket( PACKET_COMMAND* pPacket ){return true;}
	virtual void	SetLimitByteSize(LONG nLimitByteSize);
	virtual void	BlockUser(SOCKET sock,int minute){return;}//��ͣ�˺� by david 2012��11��5��

	char*			IP(SOCKET sock);
	inline int		GetSendBufferUsage(SOCKET sock)	{ return m_Net->GetSendBufferUsage(sock); }

	virtual SOCKET	Connect( const char *szIp,ULONG nPort );
	virtual SOCKET ConnectAsync( const char *szIp,ULONG nPort,ConnectCallBackFunc pfn=NULL );
	virtual void	ShutDown(SOCKET sock);						//�ر�һ������
	virtual BOOL	CloseConnect(SOCKET sock);					//�����ر�һ������
	virtual SOCKET		ConnectReturn( SOCKET sock, int error=0 );

	void			FreePacket(PACKET_COMMAND* pPacket)		{if(pPacket) m_PacketPool.Free(pPacket);}
	CObjectMemoryPool<PACKET_COMMAND>&	GetPacketPool()		{return m_PacketPool;}

	inline char*	GetMacAddress(){return m_MacAddress;}

protected:
	bool	AddBuffPacket(SOCKET sock, BUFFER_TO_PACKET* pBuffPacket);
	bool	RemoveBuffPacket(SOCKET sock);
	BUFFER_TO_PACKET* GetPacketBySocket(UINT Socket);

	inline BUFFER_TO_PACKET*	Alloc()
	{

		BUFFER_TO_PACKET* p = NULL;

		m_Lock.LOCK();
		for(int i=0;i<m_ConnectMax;i++)
		{
			if(++m_BufferPacketTableIndex >= m_ConnectMax)
				m_BufferPacketTableIndex = 0;

			if(m_BufferPacketTable[m_BufferPacketTableIndex].m_Ref == 0)
			{
				m_BuffToPacketTableUsed++;
				m_BufferPacketTable[m_BufferPacketTableIndex].m_Ref++;
				p = &m_BufferPacketTable[m_BufferPacketTableIndex];
				break;
			}
		}
		m_Lock.UNLOCK();
		if(p==NULL)
			Log("BUFFER_TO_PACKET Alloc() faild");
		return p;
	}

	inline void	Free(BUFFER_TO_PACKET* pObj)
	{
		if(pObj)
		{
			m_Lock.LOCK();
			pObj->Init();
			m_BuffToPacketTableUsed--;
			m_Lock.UNLOCK();
		}
	}

	bool DecompressPacketCommand(int nThreadID,PACKET_COMMAND *pkt);
	
	inline void SetClientIO(){m_isClient = true;}
public:
	NET_IO_TYPE			m_NetIOType;
	BOOL				m_dRunFlag;

	UINT				m_nRecvSize;
	UINT				m_nSendSize;

	int					m_nBuffToPacketCountMax;			// �ڴ�ش�С
	int					m_BuffToPacketTableUsed;			// �ڴ��ʹ�õĴ�С
	
protected:
	CUtlMap<SOCKET,BUFFER_TO_PACKET*,int>	m_SocketMap;
	CGLock	m_SocketLock;
	int					m_ConnectMax;						// ���������
	BUFFER_TO_PACKET*	m_BufferPacketTable;				//
	CObjectMemoryPool<PACKET_COMMAND>	m_PacketPool;
	CGLock				m_Lock;
	int32_t				m_BufferPacketTableIndex;
	char				m_MacAddress[256];
	bool				m_isClient;							// true:��Ϣ����client false:��Ϣ���Է������ڲ�

public:
	CNet*				m_Net;

};

/*
* ��PACKET_COMMAND�����ѹ�����ֽ�����ɸ�PACKET_COMMAND����
* pkt: ���������
* pktList: ���������
* pktCnt: �������ĸ���
*/



#if defined(_DEBUG) && (!defined(WIN32))
void Display_Accept(bool enable);
void Display_Read(bool enable);
void Display_Write(bool enable);
void PrintSocketCount();


void Display_Chunk(bool enable);
#endif

#ifdef WIN32
void GetLocalMAC(char *buf);
BOOL IsLocalAdapter(char *pAdapterName);
#endif

