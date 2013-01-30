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
// 结构定义

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

//	inline int GetWritePtr() { return m_WritePtr; }

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

//	inline BOOL GetPacketSize()
//	{
//		if(!IsHeadFull())
//			return 0;
//
//		return pPacket->Size();
//	}

	inline int Write(const char* buffer, int nSize)
	{
		if(m_WritePtr + nSize > (int)PACKET_BUFFER_SIZE || nSize <= 0)
		{
			//Log("m_WritePtr + nSize = %d ,%d\n",m_WritePtr,nSize);  //communityserver现在不知道怎么消息超了,打太多log了会崩溃 先注释掉
			return 0;
		}

		//int Optr = m_WritePtr;
		memcpy(pPacket->pParam + m_WritePtr, buffer, nSize);
		m_WritePtr += nSize;

		//if(Optr < PACKET_COMMAND::HeadSize() && m_WritePtr >= PACKET_COMMAND::HeadSize())
		//{
		//	if(!CheckPacket())
		//	{
		//		Log("CheckPacket Error\n");
		//		return 0;
		//	}
		//}
		return nSize;
	}

	//inline bool CheckPacket()
	//{
	//	if(GetPacketSize() < PACKET_COMMAND::HeadSize() || GetPacketSize() > PACKET_BUFFER_SIZE)
	//	{
	//		Assert(0);
	//		return false;
	//	}
	//	if( GetPacketDefSize(pPacket->Type()) < 0 )
	//		return true;
	//	if( GetPacketDefSize(pPacket->Type()) == GetPacketSize() )
	//		return true;

		//包校验失败，做相应处理

	//	return false;
	//}
	int				m_Ref;
	SOCKET			m_sock;
	int				m_WritePtr;		// Packet中 pParam 的写指针
	PACKET_COMMAND*  pPacket;
	char			m_RecvCompressBuf[COMPRESS_BUFF_SIZE];
	int				m_RecvCompSize;
	int				m_RecvCompIdx;
	unsigned char	m_RecvUnCompressBuf[COMPRESS_BUFF_SIZE];

};

//typedef CUtlLinkedList<PACKET_COMMAND *,int>	PACKETLIST;
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
	virtual void	BlockUser(SOCKET sock,int minute){return;}//封停账号 by david 2012年11月5日

	char*			IP(SOCKET sock);
	inline int		GetSendBufferUsage(SOCKET sock)	{ return m_Net->GetSendBufferUsage(sock); }

	virtual SOCKET	Connect( const char *szIp,ULONG nPort );
	virtual SOCKET ConnectAsync( const char *szIp,ULONG nPort,ConnectCallBackFunc pfn=NULL );
	virtual void	ShutDown(SOCKET sock);						//关闭一条连接
	virtual BOOL	CloseConnect(SOCKET sock);					//立即关闭一条连接
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

	int					m_nBuffToPacketCountMax;			// 内存池大小
	int					m_BuffToPacketTableUsed;			// 内存池使用的大小
	
protected:
	CUtlMap<SOCKET,BUFFER_TO_PACKET*,int>	m_SocketMap;
	CGLock	m_SocketLock;
	int					m_ConnectMax;						// 最大连接数
	BUFFER_TO_PACKET*	m_BufferPacketTable;				//
	CObjectMemoryPool<PACKET_COMMAND>	m_PacketPool;
	CGLock				m_Lock;
	int32_t				m_BufferPacketTableIndex;
	char				m_MacAddress[256];
	bool				m_isClient;							// true:消息来自client false:消息来自服务器内部

public:
	CNet*				m_Net;

};

/*
* 把PACKET_COMMAND命令解压缩，分解成若干个PACKET_COMMAND对象
* pkt: 输入的命令
* pktList: 输出的命令
* pktCnt: 输出命令的个数
*/



#if defined(_DEBUG) && (!defined(WIN32))
void Display_Accept(bool enable);
void Display_Read(bool enable);
void Display_Write(bool enable);
void PrintSocketCount();


void Display_Chunk(bool enable);
#endif


class GAMENETCOMMON_CLASS CStringNet : public CGameNet
{
public:
	virtual BOOL	Begin(int nListenPort,int nPacketPoolSize,int nConnectMax,int nQueueSize,int nRecvSize,int nSendSize,int nTimeout,int nAcceptCount=0);
	virtual void	End();
	virtual void	Accept( SOCKET sock);
	virtual void	Break( SOCKET sock );
	virtual int		Send( SOCKET sock, PACKET_COMMAND* pPacket );
	virtual int		Recv( SOCKET sock, char* buf, DWORD nSize );
	virtual bool	addPacket( PACKET_COMMAND* pPacket ){return true;}

	virtual SOCKET	Connect( const char *szIp,ULONG nPort );

protected:
	virtual int				_FormatPacket( char* pkgTmp, PACKET_COMMAND* pPacket );
	virtual PACKET_COMMAND*	_ParserPacket( SOCKET sock, char* buf, DWORD nSize );

protected:
	CToken token;
	CUtlMap<SOCKET,std::string> m_recvbuff;
	CUtlMap<std::string, int> PACKET_RECV_NAME_FAST_TABLE;
};


//GMServer 
class GAMENETCOMMON_CLASS CGMStringNet : public CStringNet
{
public:
	CGMStringNet();
	~CGMStringNet();
public:	
	virtual int		Send( SOCKET sock, PACKET_COMMAND* pPacket );
	virtual int		Recv( SOCKET sock,char*	buf, DWORD nSize );
};


#ifdef WIN32
void GetLocalMAC(char *buf);
BOOL IsLocalAdapter(char *pAdapterName);
#endif

