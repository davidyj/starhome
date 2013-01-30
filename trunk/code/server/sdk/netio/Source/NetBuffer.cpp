#include "StdAfx.h"
#include "NetBuffer.h"
#include "ZipSystem.h"

//////////////////////////////////////////////////////////////////////////
//���ƹ��캯��,��������ռ�
CWDoubleBuff::CWDoubleBuff()
{
	m_nReadSize = 0;
	m_nWriteSize = 0;
}

CWDoubleBuff::~CWDoubleBuff()
{
	//if(m_Buffer)
	//	Plat_Free(m_Buffer);
}

void CWDoubleBuff::Purge( void )
{
	if(m_Buffer)
		Plat_Free(m_Buffer);
}

// nSendBufSize	: ������Ϣ���ڴ��С
void CWDoubleBuff::Create(int nBuffSize,int ntimeout)
{
	m_ntimeout		= ntimeout;
	m_nReadSize		= 0;
	m_nWriteSize	= 0;
	m_WriteBuf		= &m_Buffer1;
	m_ReadBuf		= &m_Buffer2;

//	Assert(m_BuffSize);
	m_BuffSize = nBuffSize;

	m_Buffer = (char*)Plat_Alloc(sizeof(char)* nBuffSize * 2);

	// Init Section 1
	m_Buffer1.m_nBegin	= m_Buffer;
	m_Buffer1.m_nRead	= m_Buffer;
	m_Buffer1.m_nWrite	= m_Buffer;
	m_Buffer1.m_nEnd	= m_Buffer + m_BuffSize ;


	//Init Section 2
	m_Buffer2.m_nBegin	= m_Buffer + m_BuffSize;
	m_Buffer2.m_nRead	= m_Buffer + m_BuffSize;
	m_Buffer2.m_nWrite	= m_Buffer + m_BuffSize;
	m_Buffer2.m_nEnd	= m_Buffer + m_BuffSize + m_BuffSize;
}

void CWDoubleBuff::Release()
{
	m_Lock.LOCK();
	m_nReadSize			= 0;
	m_nWriteSize		= 0;

	m_Buffer1.m_nBegin	= m_Buffer;
	m_Buffer1.m_nRead	= m_Buffer;
	m_Buffer1.m_nWrite	= m_Buffer;
	m_Buffer1.m_nEnd	= m_Buffer + m_BuffSize ;

	m_Buffer2.m_nBegin	= m_Buffer + m_BuffSize;
	m_Buffer2.m_nRead	= m_Buffer + m_BuffSize;
	m_Buffer2.m_nWrite	= m_Buffer + m_BuffSize;
	m_Buffer2.m_nEnd	= m_Buffer + m_BuffSize + m_BuffSize;
	m_Lock.UNLOCK();
}

//��д�뻺��
// ����д������ݳ���
int CWDoubleBuff::Write(PACKET_COMMAND* pPacket)
{
	if(pPacket->Size() == 0)
		return 0;

	m_Lock.LOCK();
	// ʣ��ռ䲻��
	if(m_WriteBuf->FreeSize() <= pPacket->Size())
	{
		m_Lock.UNLOCK();
		return 0;
	}
	memcpy(m_WriteBuf->m_nWrite,pPacket->pParam,pPacket->Size());
	m_WriteBuf->m_nWrite += pPacket->Size();
	m_nWriteSize = m_WriteBuf->DataSize();		//�������������
	m_Lock.UNLOCK();
	return pPacket->Size();
 }

//////////////////////////////////////////////////////////////////////////
//��buffд�뻺�� zhao
//����ֵ:����д������ݳ���
//����;const char* buffer:buffָ��,int nSize:buff��С
//////////////////////////////////////////////////////////////////////////
int CWDoubleBuff::Write(const char* buffer,int nSize)
{
	int nReturnSize=0;
	m_Lock.LOCK();
	// ʣ��ռ䲻��,����nSizeΪ0
	if(m_WriteBuf->FreeSize() <= nSize|| nSize<=0)
	{
		DEBUG_Log("˫����ʣ��ռ䲻�� free %d,packet size %d ��Ϣһ��",m_WriteBuf->FreeSize(),nSize);
		nReturnSize = -1;
//		return -1;
	}
	else
	{
		memcpy(m_WriteBuf->m_nWrite,buffer,nSize);
		m_WriteBuf->m_nWrite += nSize;
		m_nWriteSize = m_WriteBuf->DataSize();		//�������������
		nReturnSize=nSize;
	}
	m_Lock.UNLOCK();

	return nReturnSize;
}

PCHAR CWDoubleBuff::Read(u_long &nReadSize)
{
	//˫����ȥ
	if(!m_ReadBuf->DataSize())
	{
		nReadSize = 0;
		return NULL;
	}
	nReadSize = m_ReadBuf->DataSize();
	PCHAR res = (PCHAR)m_ReadBuf->m_nRead;
	return res;
}


void CWDoubleBuff::Delete(int nSize)
{
	//˫������
	m_ReadBuf->m_nRead += nSize;
	if(m_ReadBuf->m_nRead >= m_ReadBuf->m_nWrite)
	{
		m_ReadBuf->m_nWrite = m_ReadBuf->m_nRead = m_ReadBuf->m_nBegin;
		m_nReadSize = 0;
	}
}

//��ղ�����һ������±�ʹ�� by zhao
void CWDoubleBuff::Clear()
{
	m_ReadBuf->m_nWrite = m_ReadBuf->m_nRead = m_ReadBuf->m_nBegin;
	m_nReadSize = m_nWriteSize = 0;//fixed by david � 2012-1-12

}
//Write Buff �� Read Buff����
// return	:
// true		: �����˽��� ��������Ҫ����
// false	: û�н��� û��������Ҫ����

bool CWDoubleBuff::Switch(bool bCompress)
{
	m_Lock.LOCK();
	if(m_nWriteSize && m_nReadSize == 0 )
	{
#ifdef WIN32
		m_WriteBuf = (Buffer_Section*)InterlockedExchangePointer((void**)&m_ReadBuf,(void*)m_WriteBuf);
#else
		Buffer_Section*		m_TmpBuf = m_ReadBuf;
		atomic_store_rel_ptr((uintptr_t *)&m_ReadBuf,(uintptr_t)m_WriteBuf);
		atomic_store_rel_ptr((uintptr_t *)&m_WriteBuf,(uintptr_t)m_TmpBuf);
#endif
		m_nReadSize = m_nWriteSize;
		m_nWriteSize = 0;

		m_Lock.UNLOCK();

		if( bCompress )
		{
			CompressReadBuffer();
		}
		return true;
	}
	m_Lock.UNLOCK();
	return false;
}

bool CWDoubleBuff::IsBuffEmpty()
{
	return (m_nWriteSize == 0 && m_nReadSize == 0);
}

bool CWDoubleBuff::CompressReadBuffer()
{
	if(!m_ReadBuf->DataSize())
	{
		return false;
	}

	int datasize = m_ReadBuf->DataSize();
	//if( datasize < 256 )
	//{
	//	return false;
	//}

	const PCHAR  basebuff  = m_ReadBuf->m_nRead;	//	˫��������͵�ͷ
	PCHAR        readbuff  = basebuff;				//	˫�����ѹ������
	PCHAR        writebuff = basebuff;				//	д��˫�����ָ��
	int	         readsize  = 0;
	int	         processed = 0;						//	�Ѵ��������
	int	         zipidx    = 0;

	do			//	ÿ�δ���COMPRESS_DATA_SIZE������
	{

		readsize      = 0;
		//	�����ѹ������
		do
		{
			int pkgsize = *(WORD*)(readbuff);
			if(pkgsize>PACKET_BUFFER_SIZE)
			{
				Log("pkgsize>PACKET_BUFFER_SIZE");
				return false;
			}

			readbuff  += pkgsize;
			readsize  += pkgsize;
			processed += pkgsize;

		}while( processed<datasize && readsize<COMPRESS_DATA_SIZE-PACKET_BUFFER_SIZE );

		//	ѹ������
		ULONG compresssize = COMPRESS_DATA_SIZE;
		if( ZipBufferToBuffer( (byte*)&m_CompressBuf[COMPRESS_BUFF_HEAD], compresssize, (byte*)&basebuff[zipidx], readsize, 8) != Z_OK)
		{
			Log("failed to zip in file %s\n", __FILE__);
			return false;
		}

		zipidx += readsize;
		*(WORD*)(m_CompressBuf) = (WORD)compresssize;	//	ѹ������ ǰ�����ֽڴ洢ѹ�������ݵĴ�С

		//	��ѹ������������ɶ��PACKET_COMPRESSED_COMMAND����д�ط��ͻ���
		compresssize += COMPRESS_BUFF_HEAD;
		int compridx = 0;

		do
		{
			int pkgidx  = 0;
			int cmin    = compresssize-compridx;
			int cpysize = cmin<PACKET_DATA_SIZE?cmin:PACKET_DATA_SIZE;
			memcpy( writebuff+PACKET_COMMAND::DATA_PARAM, &m_CompressBuf[compridx], cpysize );

			//	����ѹ����ͷ
			*(WORD*)(writebuff+PACKET_COMMAND::HEAD_PSIZE) = (WORD)(cpysize+PACKET_COMMAND::DATA_PARAM);	//	����С
			*(WORD*)(writebuff+PACKET_COMMAND::HEAD_PTYPE) = 60100;//PACKET_COMPRESSED_COMMAND;	//	������  ѹ��
			if( compridx == 0 )
			{
				*(WORD*)(writebuff+PACKET_COMMAND::DATA_PCRC16Flag) = 0x5e8a;
			}
			else
			{
				*(WORD*)(writebuff+PACKET_COMMAND::DATA_PCRC16Flag) = 0xda7a;
			}

			writebuff += cpysize + PACKET_COMMAND::DATA_PARAM;
			compridx  += cpysize;

		}while( compridx<compresssize );

	}while( processed<datasize );

	m_ReadBuf->m_nWrite = writebuff;
	return true;
}

bool CWDoubleBuff::IsDataWaiting()
{
	return m_nReadSize > 0;
}
