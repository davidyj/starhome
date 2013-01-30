//
//		CNetBuffer:
//			�����ɶ˿�ʹ�õĸ�Ч�ʵĵĶ�̬�ڴ�ṹ
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

	char*	m_UnCompressedBuffer;				//��ѹ�����ݻ�����
	int		m_nSize;
	int		m_nCount;
	int		m_BuffSize;							//��������С
};

struct Buffer_Section
{
	PCHAR	m_nBegin;
	PCHAR	m_nEnd;
	PCHAR	m_nRead;
	PCHAR	m_nWrite;

	//�����Ϳռ�
	inline int DataSize()
	{
		return m_nWrite - m_nBegin;
	}

	//���пռ�
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
	int		Write(const char* buffer,int nSize); //��buffд�뻺����
	void	Delete(int nSize);
	PCHAR	Read(u_long &nSize);
	bool	IsDataWaiting();
	bool	IsBuffEmpty();
	bool	Switch(bool bCompress = false);
	void	Clear();
	void	Purge( void );
	bool	CompressReadBuffer();

public:
	int					m_nReadSize;			//��ǰ��ָ�뻺����λ��
	int					m_nWriteSize;			//��ǰдָ���λ��
	int					m_ntimeout;				//���ͳ�ʱ
	int					m_BuffSize;				//��������С
	char*				m_Buffer;				//���ݻ�����
	Buffer_Section		m_Buffer1;				//д���Buff
	Buffer_Section		m_Buffer2;				//��ȡ��Buff
	Buffer_Section*		m_WriteBuf;
	Buffer_Section*		m_ReadBuf;
	char				m_CompressBuf[COMPRESS_BUFF_SIZE];
	CGLock				m_Lock;
};
