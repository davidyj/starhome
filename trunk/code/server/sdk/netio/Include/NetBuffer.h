//
//		CNetBuffer:
//			配合完成端口使用的高效率的的动态内存结构
//
//
//							yang jian
//							2008-3-2
////////////////////////////////////////////////////////////////
#pragma once
#include "config.h"
#include "GLock.h"
#include "dbg.h"
#include "GlobalConst.h"
#include "PacketDefine.h"
#include "utllinkedlist.h"
#include "atomic.h"


struct UnComressedBuffer
{
	inline void Construct(int nBufferSize)
	{
		Assert(nBufferSize);
		m_BuffSize = nBufferSize;
		m_UnCompressedBuffer = (char*)Plat_Alloc(sizeof(char)*nBufferSize);
	}

	inline void Init()
	{
		m_nSize	 = 0;
		m_nCount = 0;
	}

	inline void Release()
	{
		if(m_UnCompressedBuffer)
			Plat_Free(m_UnCompressedBuffer);
	}

	char*	m_UnCompressedBuffer;				//待压缩数据缓冲区
	int		m_nSize;
	int		m_nCount;
	int		m_BuffSize;							//缓冲区大小
};

struct Buffer_Section
{
	PCHAR	m_nBegin;
	PCHAR	m_nEnd;
	PCHAR	m_nRead;
	PCHAR	m_nWrite;

	//待发送空间
	inline int DataSize()
	{
		return m_nWrite - m_nBegin;
	}

	//空闲空间
	inline int FreeSize()
	{
		return m_nEnd - m_nWrite;
	}
};

//enum NET_TYPE
//{
//	NET_TYPE_IOCP,
//	NET_TYPE_SELECT,
//}
//
//////////////////////////////////////////////////////////////////////////
//

#define		PACKET_DATA_SIZE			(PACKET_BUFFER_SIZE-PACKET_COMMAND::DATA_PARAM)
#define		COMPRESS_BUFF_SIZE			(1024 * 5)
#define		COMPRESS_BUFF_HEAD			2
#define		COMPRESS_TYPE				0x5E8A
#define		COMPRESS_DATA_SIZE			(COMPRESS_BUFF_SIZE-COMPRESS_BUFF_HEAD)

class CWDoubleBuff
{
public:
	CWDoubleBuff();
	~CWDoubleBuff();

	void	Create(int nBuffSize,int ntimeout);
	void	Release();
	int		Write(PACKET_COMMAND* pPacket);
	int		Write(const char* buffer,int nSize); //把buff写入缓冲区
	void	Delete(int nSize);
	PCHAR	Read(u_long &nSize);
	bool	IsDataWaiting();
	bool	IsBuffEmpty();
	bool	Switch(bool bCompress = false);
	void	Clear();
	void	Purge( void );
	bool	CompressReadBuffer();

public:
	int					m_nReadSize;			//当前读指针缓冲区位置
	int					m_nWriteSize;			//当前写指针的位置
	int					m_ntimeout;				//发送超时
	int					m_BuffSize;				//缓冲区大小
	char*				m_Buffer;				//数据缓冲区
	Buffer_Section		m_Buffer1;				//写入的Buff
	Buffer_Section		m_Buffer2;				//读取的Buff
	Buffer_Section*		m_WriteBuf;
	Buffer_Section*		m_ReadBuf;
	char				m_CompressBuf[COMPRESS_BUFF_SIZE];
	CGLock				m_Lock;
};
