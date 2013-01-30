#include "StdAfx.h"
#include "GameNet.h"
#include  <stdlib.h>
#include  "GLock.h"
#include "PacketDefineHead.h"
#include "ZipSystem.h"
#include "base64.h"
#include "strtools.h"
#ifndef WIN32
#include <pthread.h>
#endif
#ifdef WIN32
#include <IPTypes.h>
#include <iphlpapi.h>
#include <tchar.h>
#endif

//////////////////////////////////////////////////////////////////////////
//
CGameNet::CGameNet()
{
	m_dRunFlag		= FALSE;
	m_Net			= NULL;
	m_ConnectMax	= 0;
	m_BufferPacketTable		= NULL;
	m_BufferPacketTableIndex= 0;
	m_nBuffToPacketCountMax	= 0;
	m_BuffToPacketTableUsed = 0;
	m_isClient = false;
	memset(m_MacAddress,0,sizeof(char)*256);
}

CGameNet::~CGameNet()
{
	m_isClient = false;
	End();
}

//	Param:
//	Type		: ���������
//	nListenPort	: �����˿ں�
//  nConnectMax	: ���ӵ������ ������Ԥ���ٿռ�
//  nQueueSize	: ��Ϣ���еĳ���
//  nRecvSize	: ������Ϣ�Ļ�������С
//	nSendSize	: ������Ϣ�Ļ�������С
//  nTimeout	: ���ͳ�ʱ
BOOL CGameNet::Begin(NET_IO_TYPE Type,int nPacketPoolSize,int nListenPort,int nConnectMax,int nQueueSize,int nRecvSize,int nSendSize,int nTimeout,int nAcceptCount)
{
	Assert(nConnectMax);
	if(!nConnectMax)
		return FALSE;

	// Ԥ���� m_BufferPacketTable;
	m_ConnectMax = nConnectMax;

	m_BufferPacketTable = (BUFFER_TO_PACKET*)Plat_Alloc(sizeof(BUFFER_TO_PACKET)*nConnectMax);
	for(int i=0;i<nConnectMax;i++)
	{
		m_BufferPacketTable[i].Init();
	}

	m_nBuffToPacketCountMax = nConnectMax;

	//��ʼ��Socket������
	//m_SocketMap.Purge(m_ConnectMax);
	SetDefLessFunc(m_SocketMap);

	m_PacketPool.Init("PacketPool", nPacketPoolSize);

#ifdef WIN32
	if (Type == NET_IO_TYPE_IOCP)
	{
		m_Net = new CIOCP(this);
//		m_Net->m_LLimitByte = CGMServerMgr::getSingle().
		Assert(m_Net);
		if(!m_Net)
			return FALSE;

		if (!m_Net->Begin(nListenPort,nPacketPoolSize,nConnectMax,nRecvSize,nSendSize,nTimeout,nAcceptCount))
			return FALSE;
	}
#else
	if (Type == NET_IO_TYPE_KQUEUE)
	{
		m_Net = new CKQueue(this);
//		if (m_Net->Begin(nListenPort))
		if (m_Net && m_Net->Begin(nListenPort,nPacketPoolSize,nConnectMax,nRecvSize,nSendSize,nTimeout,nAcceptCount))
		{
			//Log("KQueue init succ\n");
		}
		else
		{
			Log("KQueue init failed\n");
		}
		if(m_Net)
		{
			Log("m_Net is not NULL\n");
		}
		else
		{
			Log("m_Net is NULL\n");
			exit(0);
		}
	}
#endif
	else if(Type == NET_IO_TYPE_SELECT)
	{
		m_Net = new CSelectIO(this);
		Assert(m_Net);
		if(!m_Net)
			return FALSE;
		if(!m_Net->Begin(nListenPort,nPacketPoolSize,nConnectMax,nRecvSize,nSendSize,nTimeout))
			return FALSE;
	}
	else
	{
		Log("this net type(%d) has not been implemented...!\n", Type);
		exit(0);
	}

	//get mac address by david
#ifdef WIN32
	GetLocalMAC(m_MacAddress);
#endif

	m_dRunFlag = TRUE;


	return TRUE;
}

void CGameNet::End()
{
	if(m_Net)
		m_Net->End();

	Sleep(500);

	if(m_BufferPacketTable)
	{
		Plat_Free(m_BufferPacketTable);
		m_BufferPacketTable = NULL;
	}

	SAFE_DELETE(m_Net);
}

void CGameNet::SetLimitByteSize(LONG nLimitByteSize)
{
#ifdef WIN32
	if(m_Net)
		((CIOCP*)m_Net)->m_LLimitByte = nLimitByteSize;
#endif
}

bool CGameNet::AddBuffPacket(SOCKET sock, BUFFER_TO_PACKET* pBuffPacket)
{
	if(!pBuffPacket || sock == INVALID_SOCKET)
		return false;

	m_SocketLock.LOCK();
	pBuffPacket->m_sock = sock;
	if(m_SocketMap.Insert(sock,pBuffPacket) == m_SocketMap.InvalidIndex())
	{
		m_SocketLock.UNLOCK();
		return false;
	}
	m_SocketLock.UNLOCK();
	return true;
}

bool CGameNet::RemoveBuffPacket(SOCKET sock)
{
	if(sock == INVALID_SOCKET)
		return false;
	m_SocketLock.LOCK();
	int index = m_SocketMap.Find(sock);
	if(m_SocketMap.IsValidIndex(index)){
		m_SocketMap.RemoveAt(index);
	}
	m_SocketLock.UNLOCK();
	return true;
}

BUFFER_TO_PACKET* CGameNet::GetPacketBySocket(UINT s)
{
	BUFFER_TO_PACKET* res = NULL;
	m_SocketLock.LOCK();
	int index = m_SocketMap.Find(s);
	if(m_SocketMap.IsValidIndex(index))
		res = m_SocketMap.Element(index);
	m_SocketLock.UNLOCK();
	return res;
//	return (BUFFER_TO_PACKET*)m_SocketMap.Find(s);
}

void CGameNet::Accept( SOCKET sock)
{
	if(sock == INVALID_SOCKET)
		return;

	BUFFER_TO_PACKET* pBuffer = GetPacketBySocket(sock);
	if(pBuffer)
	{
		RemoveBuffPacket(sock);
		Free(pBuffer);
		Warning("Accept %d Get pBuffer %d\n",sock,pBuffer);
		Log("already have BUFFER_TO_PACKET by sock:%d",sock);
	}

	pBuffer = Alloc();
	if(pBuffer)
	{
		if(!AddBuffPacket(sock,pBuffer)){
			Free(pBuffer);
		}
	}
}

void CGameNet::Break( SOCKET sock )
{
	if(sock == INVALID_SOCKET)
		return;

	BUFFER_TO_PACKET* pBuffer = GetPacketBySocket(sock);
	if(pBuffer)
	{
		RemoveBuffPacket(sock);
		Free(pBuffer);
	}
}

char* CGameNet::IP(SOCKET sock)
{
	if(m_Net)
		return m_Net->IP(sock);
//	Log("m_Net==NULL socket=%d",sock);
	return "";
}

SOCKET CGameNet::Connect( const char *szIp,ULONG nPort  )
{
	if(!m_Net)
		return INVALID_SOCKET;

	return m_Net->Connect(szIp,nPort);
}

SOCKET CGameNet::ConnectAsync( const char *szIp,ULONG nPort,ConnectCallBackFunc pfn )
{
	if(!m_Net)
		return INVALID_SOCKET;

	return m_Net->ConnectAsync(szIp,nPort,pfn);
}


/*
* ��PACKET_COMMAND�����ѹ�����ֽ�����ɸ�PACKET_COMMAND����
* pkt: ���������
* pktList: ���������
* pktCnt: �������ĸ���
*/
bool CGameNet::DecompressPacketCommand(int nThreadID,PACKET_COMMAND *pkt)
{
#ifdef _DEBUG
	if (!pkt)
	{
		Log("pkt is null, file %s\n", __FILE__);
		return false;
	}	
	if (pkt->DataSize() > (int)PACKET_BUFFER_SIZE)
	{
		Log("pkt is too long,in file %s\n", __FILE__);
		return false;
	}
#else
	if ((!pkt) || (pkt->DataSize() > PACKET_BUFFER_SIZE))
		return false;
#endif

	unsigned long len = pkt->Size() * 20;

	byte *result =(byte*)Plat_Alloc(len);
	if(!result)
		return false;

	unsigned char *p = pkt->Data(); //ָ�����PACKET_COMMAND��data����

	int ret = UnZipBufferToBuffer(result, len, p, pkt->DataSize());
	if (ret != Z_OK)
	{
		Plat_Free(result);
		Log("+-Error UnZip ret = %d size=%d",ret,pkt->DataSize());
		return false;
	}
	int size = 0;
	int type = 0;

	p = result;
	while (len > 0)
	{
		size = *(WORD*)(p + PACKET_COMMAND::HEAD_PSIZE);
		type = *(WORD*)(p + PACKET_COMMAND::HEAD_PTYPE);

		//У����Ϣͷ�е����ݳ���
		if(GetParamLen(GetCmdFormat(type)) != (size - PACKET_COMMAND::DATA_PARAM))
		{
			Plat_Free(result);
			Log("+-���յ������ݳ��ȴ���");
			return false;
		}

// 		PACKET_COMMAND* pNewPacket = PacketResMgr().Alloc(nThreadID);
// 		if (!pNewPacket)
// 			break;
// 		pNewPacket->Copy(pkt->nNetid, p, size);

//		addPacket(nThreadID,p);

		p += size;
		len -= size;
	}
	Plat_Free(result);
	return true;
}

int g_ret = 0;
int CGameNet::Send(SOCKET sock,PACKET_COMMAND* pPack)
{
	if ( pPack )
		m_nSendSize+=pPack->Size();
	//int i = m_Net->Send(sock,pPack);
	//Log("SendSize = %d",i-12);
	//return i;
	//return m_Net->Send(sock,pPack);
	//printf("Send size = %d",m_nSendSize);
	if ( m_Net )
		g_ret = m_Net->Send( sock, (char*)pPack->pParam, pPack->Size());
	/*if( g_ret <= 0){
		Log(" socket %d ����ʧ�� packet type %d size %d",sock,pPack->Type(),pPack->Size());
	}*/
	return g_ret;
}

int CGameNet::Send(SOCKET sock, char* buf, DWORD size)
{
	m_nSendSize += size;

	if (  m_Net )
		g_ret = m_Net->Send( sock, buf, size);
	/*if( g_ret <= 0){
		Log(" socket %d ����ʧ�� buff size %d", sock, size);
	}*/
	return g_ret;
}

void CGameNet::ShutDown(SOCKET sock)
{
	if (m_Net)
		m_Net->ShutDown(sock);
}

BOOL CGameNet::CloseConnect(SOCKET sock)
{
	if (m_Net)
		return m_Net->Close(sock);
	return FALSE;
}

SOCKET CGameNet::ConnectReturn( SOCKET sock, int error )
{
	return sock;
}

int CGameNet::Recv( SOCKET sock,char *buf,DWORD nSize )
{
	m_nRecvSize += nSize;
	if(nSize<=0)
	{
		Log("Recv�Ĵ�СΪ<=0����,sock=%d\n", sock);
		return 0;
	}

	UINT nReadPtr = 0;
	BUFFER_TO_PACKET* pBufPacket = GetPacketBySocket(sock);
	if(!pBufPacket)
	{
		Log("Can't find BUFFER_TO_PACKET by sock:%d",sock);
		return 0;
	}

	if(pBufPacket->m_sock != sock)
	{
		Log("pBufPacket->m_sock %d != sock %d \n",pBufPacket->m_sock,sock);
		pBufPacket->Reset();
		return 0;
	}

	while (nReadPtr < nSize)
	{
		if (pBufPacket->pPacket == NULL)							//��� socket ��Ӧ�� Packet �����Ѿ�����գ��ͷ���һ���µĻ���
		{
			pBufPacket->pPacket = m_PacketPool.Alloc();
			if(pBufPacket->pPacket == NULL)
			{
				Log(" +-g_AllocPacket Error!\n");
				pBufPacket->Reset();
				return 0;
			}
			pBufPacket->pPacket->SetNetID(sock);
		}

		if(pBufPacket->pPacket->nNetid != sock)
		{
			Log("Get buff_to_Packet Error netid = %d type = %d size = %d socket = %d\n",pBufPacket->pPacket->nNetid,pBufPacket->pPacket->Type(),pBufPacket->pPacket->Size(),sock);
			m_PacketPool.Free(pBufPacket->pPacket);
			pBufPacket->Reset();
			return 0;
		}

		int nChunkLeftSize = nSize - nReadPtr;    //Chunk ʣ�೤��
		if( nChunkLeftSize <= 0)
		{
			Log("nChunkLeftSize = %d\n",nChunkLeftSize);
			m_PacketPool.Free(pBufPacket->pPacket);
			pBufPacket->Reset();
			return nSize;
		}

		if(pBufPacket->IsHeadFull())					// ���Packet������ ��Ϣͷ�Ѿ�д�꣬��ô���Ĵ�С������֪�ģ�����ժ����������
		{
			if(pBufPacket->GetPacketLeftSize() < 0)
			{
				Log("Get GetPacketLeftSize Error %d \n",pBufPacket->GetPacketLeftSize());
				m_PacketPool.Free(pBufPacket->pPacket);
				pBufPacket->Reset();
				return 0;
			}

			if(pBufPacket->GetPacketLeftSize() <= nChunkLeftSize)  // ���Packet�����У���δд��ĳ���С�� Chunk ʣ�೤��
			{

				int ret = pBufPacket->Write( buf + nReadPtr, pBufPacket->GetPacketLeftSize());
				if( ret == 0 )
				{
					Log("Write Failed  GetPacketLeftSize = %d \n",pBufPacket->GetPacketLeftSize());
					m_PacketPool.Free(pBufPacket->pPacket);
					pBufPacket->Reset();
					return 0;
				}

				if(nReadPtr + ret> nSize)
				{
					Log("nReadPtr > nSize ReadPtr = %d nSize = %d \n",nReadPtr,nSize);
					m_PacketPool.Free(pBufPacket->pPacket);
					pBufPacket->Reset();
					return 0;
				}

				nReadPtr = nReadPtr + ret;
			}
			else													// ����Chunk ʣ��ĳ�����Ȼ������д�����Packet����
			{
				int ret = pBufPacket->Write( buf + nReadPtr, nChunkLeftSize);
				if(ret == 0)
				{
					Log("Write Failed  nChunkLeftsize = %d \n",nChunkLeftSize);
					m_PacketPool.Free(pBufPacket->pPacket);
					pBufPacket->Reset();
					return 0;
				}
				if(nReadPtr + ret != nSize)
				{
					Log("nReadPtr != nSize nReadPtr = %d\n",nReadPtr);
					m_PacketPool.Free(pBufPacket->pPacket);
					pBufPacket->Reset();
					return 0;
				}
				nReadPtr = nReadPtr + ret;
			}
		}
		else											// ����Packet������ ��Ϣͷδд�꣬�Ȱ���Ϣͷд����
		{
			if(pBufPacket->GetHeadLeftSize() < 0)
			{
				Log("Get GetHeadLeftSize Error %d \n",pBufPacket->GetHeadLeftSize());
				m_PacketPool.Free(pBufPacket->pPacket);
				pBufPacket->Reset();
				return nSize;
			}

			if(pBufPacket->GetHeadLeftSize() <= nChunkLeftSize)  // ���Packet�����У���Ϣͷ��δд��ĳ���С�� Chunk ʣ�೤��
			{
				int ret = pBufPacket->Write( buf + nReadPtr, pBufPacket->GetHeadLeftSize());
				if(ret == 0)
				{
					Log("Write Failed  GetHeadLeftSize = %d \n",pBufPacket->GetHeadLeftSize());
					m_PacketPool.Free(pBufPacket->pPacket);
					pBufPacket->Reset();
					return 0;
				}

				if(nReadPtr + ret > nSize)
				{
					Log("nReadPtr > nSize ReadPtr = %d nSize = %d \n",nReadPtr,nSize);
					m_PacketPool.Free(pBufPacket->pPacket);
					pBufPacket->Reset();
					return 0;
				}

				nReadPtr = nReadPtr + ret;

			}
			else													// ����Chunk ʣ��ĳ�����Ȼ������д�����Packet�������Ϣͷ
			{
				int ret = pBufPacket->Write( buf + nReadPtr, nChunkLeftSize);
				if(ret == 0)
				{
					Log("Write Failed  nChunkLeftSize = %d \n",nChunkLeftSize);
					m_PacketPool.Free(pBufPacket->pPacket);
					pBufPacket->Reset();
					return 0;
				}
				if(nReadPtr + ret != nSize)
				{
					Log("nReadPtr != nSize nReadPtr = %d\n",nReadPtr);
					m_PacketPool.Free(pBufPacket->pPacket);
					pBufPacket->Reset();
					return 0;
				}

				nReadPtr = nReadPtr + ret;
			}
		}


		if(pBufPacket->pPacket && pBufPacket->IsHeadFull()) // �����һ��������Packet�ڻ����оͰ�������������ջ���
		{
			Assert(pBufPacket->GetPacketLeftSize() >= 0);
			if(pBufPacket->GetPacketLeftSize() < 0)
			{
				Log("Error pBufPacket->GetPacketLeftSize() < 0, %d", pBufPacket->GetPacketLeftSize());
				m_PacketPool.Free(pBufPacket->pPacket);
				pBufPacket->Reset();
				return 0;
			}
			else if(pBufPacket->GetPacketLeftSize() == 0)
			{
				// ��Ϊ���ڷ�ѹ�������� ������Ҫ�ж�һ�� By David 2010-2-18
				if(true)
				{
					//�ͻ��˲����ܷ���ѹ������Ϣ��
					//fixed by david  2012��11��5��
					if(m_isClient)
					{
						Log("�յ���ҵķǷ���Ϣ��");
						BlockUser(pBufPacket->pPacket->GetNetID(),60*24);		

						m_PacketPool.Free(pBufPacket->pPacket);
						pBufPacket->Reset();
						pBufPacket->m_RecvCompSize = 0;
						pBufPacket->m_RecvCompIdx  = 0;
						return 0;
					}

					if( pBufPacket->m_RecvCompSize == 0 )
					{
						if( pBufPacket->pPacket->CRC16Flag() != 0x5e8a )
						{
							Log("Error CRC16(%d) != 0x5e8a", pBufPacket->pPacket->CRC16Flag());
							m_PacketPool.Free(pBufPacket->pPacket);
							pBufPacket->Reset();
							pBufPacket->m_RecvCompSize = 0;
							pBufPacket->m_RecvCompIdx  = 0;
							return 0;
						}
						pBufPacket->m_RecvCompSize = *(WORD*)( pBufPacket->pPacket->Data() );
						memcpy( pBufPacket->m_RecvCompressBuf, pBufPacket->pPacket->Data()+COMPRESS_BUFF_HEAD, pBufPacket->pPacket->DataSize()-COMPRESS_BUFF_HEAD );
						pBufPacket->m_RecvCompIdx += pBufPacket->pPacket->DataSize()-COMPRESS_BUFF_HEAD;
					}
					else
					{
						if( pBufPacket->pPacket->CRC16Flag() != 0xda7a )
						{
							Log("Error CRC16(%d) != 0xda7a", pBufPacket->pPacket->CRC16Flag());
							m_PacketPool.Free(pBufPacket->pPacket);
							pBufPacket->Reset();
							pBufPacket->m_RecvCompSize = 0;
							pBufPacket->m_RecvCompIdx  = 0;
							return 0;
						}
						memcpy( &(pBufPacket->m_RecvCompressBuf[pBufPacket->m_RecvCompIdx]), pBufPacket->pPacket->Data(), pBufPacket->pPacket->DataSize() );
						pBufPacket->m_RecvCompIdx += pBufPacket->pPacket->DataSize();
					}

					if( pBufPacket->m_RecvCompSize == pBufPacket->m_RecvCompIdx )
					{
						ULONG uncompsize = COMPRESS_BUFF_SIZE;
						int ret = UnZipBufferToBuffer( pBufPacket->m_RecvUnCompressBuf, uncompsize, (byte*)pBufPacket->m_RecvCompressBuf, pBufPacket->m_RecvCompSize );
						if (ret != Z_OK)
						{
							Log("+-Error UnZip ret = %d size=%d",ret,pBufPacket->m_RecvCompSize);
							m_PacketPool.Free(pBufPacket->pPacket);
							pBufPacket->Reset();
							pBufPacket->m_RecvCompSize = 0;
							pBufPacket->m_RecvCompIdx  = 0;
							return 0;
						}

						ULONG uncompidx = 0;
						do
						{
							int  pkgsize = *(WORD*)(&(pBufPacket->m_RecvUnCompressBuf[uncompidx])+PACKET_COMMAND::HEAD_PSIZE);
							PACKET_COMMAND* pkg = m_PacketPool.Alloc();
							if( !pkg )
								return 0;
							pkg->Copy( sock, &(pBufPacket->m_RecvUnCompressBuf[uncompidx]), pkgsize );
							uncompidx += pkgsize;

							WORD flag = 0;
							pkg->Caluation_CRC16(flag);
							if(flag != pkg->CRC16Flag())
							{
								Log("CRC16Error %d %d\n",flag ,pkg->CRC16Flag());
								m_PacketPool.Free(pkg);
								pBufPacket->Reset();
								continue;
							}
							else
							{
								if(!addPacket(pkg))
								{
									m_PacketPool.Free(pkg);
								}
							}
						}while( uncompidx<uncompsize );

						pBufPacket->m_RecvCompSize = 0;
						pBufPacket->m_RecvCompIdx  = 0;
					}
					else if( pBufPacket->m_RecvCompSize < pBufPacket->m_RecvCompIdx )
					{
						Log("pBufPacket->m_RecvCompSize < pBufPacket->m_RecvCompIdx");
					}

					m_PacketPool.Free(pBufPacket->pPacket);
					pBufPacket->Reset();
				}
				else
				{
					WORD flag = 0;
					pBufPacket->pPacket->Caluation_CRC16(flag);
					if(flag != pBufPacket->pPacket->CRC16Flag())
					{
						Log("CRC16Error %d %d\n",flag ,pBufPacket->pPacket->CRC16Flag());
						m_PacketPool.Free(pBufPacket->pPacket);
						pBufPacket->Reset();
						return 0;
					}
					else
					{
						if(!addPacket(pBufPacket->pPacket))
						{
							m_PacketPool.Free(pBufPacket->pPacket);//fixed by david 2011-12-13
						}
						pBufPacket->Reset();
					}
				}
			}
		}
	}
	return nSize;
}



//////////////////////////////////////////////////////////////////////////
//

BOOL CStringNet::Begin(int nListenPort,int nPacketPoolSize,int nConnectMax,int nQueueSize,int nRecvSize,int nSendSize,int nTimeout,int nAcceptCount)
{
	token.setToken("@|");

	SetDefLessFunc(PACKET_RECV_NAME_FAST_TABLE);

	SetDefLessFunc(m_recvbuff);

//	int buffidx = m_recvbuff.Insert( 1024, "" );
//	m_recvbuff[buffidx].reserve( PACKET_BUFFER_SIZE );

	return CGameNet::Begin(NET_IO_TYPE_SELECT,nPacketPoolSize,nListenPort,nConnectMax,nQueueSize,nRecvSize,nSendSize,nTimeout,nAcceptCount);
}

void CStringNet::End()
{
	if(m_Net)
		m_Net->End();

	m_recvbuff.RemoveAll();
}

void CStringNet::Accept( SOCKET sock)
{
	if(sock == INVALID_SOCKET)
	{
		Log("Accept sock is INVALID_SOCKET");
		return;
	}

	int buffidx = m_recvbuff.Find( sock );
	if( buffidx != m_recvbuff.InvalidIndex() )
	{
		Warning( "Accept %d Get pBuffer %d\n", sock, buffidx );
		Log( "already have BUFFER_TO_PACKET by sock:%d", sock );
	}

	m_Lock.LOCK();
	buffidx = m_recvbuff.Insert( sock, "" );
	m_Lock.UNLOCK();
	if( buffidx == m_recvbuff.InvalidIndex() )
	{
		Log( "CStringNet::Accept _ m_recvbuff.Insert return InvalidIndex" );
		return;
	}
	m_recvbuff[buffidx].reserve( PACKET_BUFFER_SIZE );

//	Warning("Accept %d bufftopacket %d\n",sock,pBuffer);
}

void CStringNet::Break( SOCKET sock )
{
	int buffidx = m_recvbuff.Find( sock );
	if( buffidx == m_recvbuff.InvalidIndex() )
	{
		Log("CStringNet::Break _ Can't find buffer by sock:%d",sock);
	}
	m_recvbuff.RemoveAt( buffidx );
}



SOCKET CStringNet::Connect( const char *szIp,ULONG nPort  )
{
	if(!m_Net)
		return INVALID_SOCKET;

	return m_Net->Connect(szIp,nPort);
}

int CStringNet::_FormatPacket( char* pkgTmp, PACKET_COMMAND* pPacket )
{
	if( !pkgTmp || !pPacket )
		return 0;

	int pkgidx = 0;

	/*
	//ƴ��ͷ
	for( uint16_t i=0; i<sizeof( PACKET_SEND_NAME )/sizeof( CmdInfo ); i++ )
	{
		
		if( PACKET_SEND_NAME[i].nCmd == pPacket->Type() )
		{
			sprintf( pkgTmp, "%u@"UINT64_FMT"|%s", pPacket->nNetid, pPacket->GetPID(), PACKET_SEND_NAME[i].szMsgFormat );
			pkgidx = strlen(pkgTmp);
			break;
		}
		
	}
	*/

	//����������
	if(!pkgidx)
	{
		/*
		assert( pPacket->Type() == CHECKSERVER_REQUEST_HEARTBEAT );
		if( pPacket->Type() == CHECKSERVER_REQUEST_HEARTBEAT )
		{
			sprintf( pkgTmp, UINT64_FMT, pPacket->GetPID() );
			pkgidx = strlen(pkgTmp);
			goto end;
		}
		*/
	}

	int nType = pPacket->Type();
	LPCSTR lpszFormat = GetCmdFormat( nType );
	//���
	{
		void* pParam  = pPacket->Data();

		//	������һ������  ����������
		++lpszFormat;++lpszFormat;
		pParam = (char*)pParam + sizeof( int64_t ) + sizeof( char );

		int slen = 0;
		char base64Dst[2048] = {0};
		char nfmt[HIGH_STRING_LEN*4] = {0};

		while( *lpszFormat )
		{
			Assert(*lpszFormat == '%');
			++lpszFormat;        // skip '%'

			pkgTmp[pkgidx] = '|';
			base64Dst[0] = '\0';

			switch( *lpszFormat )
			{
			case 'b':
			case 'c':
				{
					if( !CheckFlag( pParam, BYTE_FLAG, pkgidx, nType ) )
						break;

					char intfmt[16] = {0};
					sprintf( intfmt, "%c", *(char*)pParam );
					slen = EncodeBase64( intfmt, base64Dst, strlen(intfmt) );
					if( slen + pkgidx >= PACKET_STRING_SIZE )
						goto error;

					memcpy( &pkgTmp[pkgidx], base64Dst, slen );
					pParam = (char*)pParam + sizeof( char );
					break;
				}
			case 'd': // int
			case 'i': // int
				{
					if( !CheckFlag( pParam, INT_FLAG, pkgidx, nType ) )
						break;

					char intfmt[64] = {0};
					sprintf( intfmt, "%u", *(int*)pParam );
					slen = EncodeBase64( intfmt, base64Dst, strlen(intfmt) );
					if( slen + pkgidx >= PACKET_STRING_SIZE )
						goto error;

					memcpy( &pkgTmp[pkgidx], base64Dst, slen );
					pParam = (char*)pParam + sizeof( int );
					break;
				}
			case 'l': // int64
				{
					if( !CheckFlag( pParam, INT64_FLAG, pkgidx, nType) )
						break;

					char intfmt[128] = {0};
					sprintf( intfmt, UINT64_FMT, *(__int64*)pParam );
					slen = EncodeBase64( intfmt, base64Dst, strlen(intfmt) );
					if( slen + pkgidx >= PACKET_STRING_SIZE )
						goto error;

					memcpy( &pkgTmp[pkgidx], base64Dst, slen );
					pParam = (char*)pParam + sizeof( __int64 );
					break;
				}
			case 'n':
				{
					if( !CheckFlag( pParam, STRING_FLAG, pkgidx, nType) )
						break;

					strncpy( nfmt, (const char*)pParam, SHORT_STRING_LEN );
					slen = EncodeBase64( nfmt, base64Dst, strlen(nfmt) );
					if( slen + pkgidx >= PACKET_STRING_SIZE )
						goto error;

					strncpy( &pkgTmp[pkgidx], base64Dst, slen );
					pParam = (char*)pParam + SHORT_STRING_LEN;
					break;
				}
			case 'o':
				{
					if( !CheckFlag( pParam, STRING_FLAG, pkgidx, nType) )
						break;

					strncpy( nfmt, (const char*)pParam, DOUBLE_STRING_LEN );
					slen = EncodeBase64( nfmt, base64Dst, strlen(nfmt) );
					if( slen + pkgidx >= PACKET_STRING_SIZE )
						goto error;

					strncpy( &pkgTmp[pkgidx], base64Dst, slen );
					pParam = (char*)pParam + DOUBLE_STRING_LEN;
					break;
				}
			case 'm':
				{
					if( !CheckFlag( pParam, STRING_FLAG, pkgidx, nType) )
						break;

					strncpy( nfmt, (const char*)pParam, MEDIAL_STRING_LEN );
					slen = EncodeBase64( nfmt, base64Dst, strlen(nfmt) );
					if( slen + pkgidx >= PACKET_STRING_SIZE )
						goto error;

					strncpy( &pkgTmp[pkgidx], base64Dst, slen );
					pParam = (char*)pParam + MEDIAL_STRING_LEN;
					break;
				}
			case 's':
				{
					if( !CheckFlag( pParam, STRING_FLAG, pkgidx, nType) )
						break;

					strncpy( nfmt, (const char*)pParam, LONG_STRING_LEN );
					slen = EncodeBase64( nfmt, base64Dst, strlen(nfmt) );
					if( slen + pkgidx >= PACKET_STRING_SIZE )
						goto error;

					strncpy( &pkgTmp[pkgidx], base64Dst, slen );
					pParam = (char*)pParam + LONG_STRING_LEN;
					break;
				}
			case 'h':
				{
					if( !CheckFlag( pParam, STRING_FLAG, pkgidx, nType) )
						break;

					strncpy( nfmt, (const char*)pParam, HIGH_STRING_LEN );
					slen = EncodeBase64( nfmt, base64Dst, strlen(nfmt) );
					if( slen + pkgidx >= PACKET_STRING_SIZE )
						goto error;

					strncpy( &pkgTmp[pkgidx], base64Dst, slen );
					pParam = (char*)pParam + HIGH_STRING_LEN;
					break;
				}
			default:
				Assert( 0 );
				Log( "CStringNet������Ϣʱ����ƥ�����ʹ���(Type=%d, Param=%s)", nType, *lpszFormat );
				break;
			}

			pkgidx += slen;
			++lpszFormat;
        }
    }

error:
	if( lpszFormat && *lpszFormat )
	{
		Log("CStringNet����ʱ��Ϣ%d����Խ��", nType);
		return 0;
	}

end:
	pkgTmp[pkgidx] = '\0';

	Log("CStringNet::Send %s",pkgTmp);

	pkgTmp[pkgidx++] = '\n';

	return pkgidx;
}

//	netid@guid(����)|�ӿ�����|�ӿ��������1|�ӿ��������2| �� �� |�ӿ��������n�����ַ�
int CStringNet::Send( SOCKET sock, PACKET_COMMAND* pPacket )
{
	if( !pPacket )
		return 0;

	char pkgTmp[PACKET_STRING_SIZE]={0};

	int pkgidx = _FormatPacket( pkgTmp, pPacket );
	if( pkgidx <= 0 )
	{
		Log("CStringNet::_FormatPacketʧ��");
		return 0;
	}

	if( !m_Net )
	{
		assert(m_Net);
		Log("CStringNet::Send()����Ч��m_Net");
		return 0;
	}

	return m_Net->Send( sock, pkgTmp, pkgidx );
}

//	netid@guid(����)|�ӿ�����|������|�����Ϣ|�������1|�������2| �� �� |�������n�����ַ�
#define		STRINGNET_NETID		0
#define		STRINGNET_GUID		1
#define		STRINGNET_NAME		2
#define		STRINGNET_RES		3	//	������	true  false
#define		STRINGNET_RESC		4	//	�����Ϣ	������˴���ɹ�������ϢΪ:����ɹ�,������˴���ʧ���Ҳ�׽����ʧ��ԭ��������ϢΪʧ��ԭ��,��������ϢΪ:����ʧ��
#define		STRINGNET_ARGS_SVR	(STRINGNET_NAME + 1)//5
#define		STRINGNET_ARGS_CLI	5
#define		PAKET_MAX_FIELDS	5

int CStringNet::Recv( SOCKET sock,char* buf,DWORD nSize )
{
	m_nRecvSize += nSize;
	if(nSize<=0)
	{
		Log("Recv�Ĵ�СΪ<=0����\n");
		return 0;
	}

	_ParserPacket( sock, buf, nSize );
	
	
	return nSize;
}

PACKET_COMMAND* CStringNet::_ParserPacket( SOCKET sock, char* buf, DWORD nSize )
{
	if( !buf )
		return NULL;

	int buffidx = m_recvbuff.Find( sock );
	if( buffidx == m_recvbuff.InvalidIndex() )
	{
		Log("CStringNet::Recv _ Can't find buffer by sock:%d",sock);
		return 0;
	}

	UINT nReadPtr = 0;
	while (nReadPtr < nSize)
	{
		UINT nScanPtr = nReadPtr;
		for( ; nScanPtr<nSize; nScanPtr++ )
		{
			if( buf[nScanPtr] == '\n' )
			{
				break;
			}
		}

		//		д��pkg����
		int cpbuffsize = nScanPtr - nReadPtr;
		std::string& recvbuff = m_recvbuff[buffidx];
		recvbuff.append( buf + nReadPtr, cpbuffsize );
		nReadPtr = nReadPtr + cpbuffsize + 1;

		//	pkg��������ȫ��ת���� PACKET_COMMAND
		if( nScanPtr > 0 && nScanPtr < nSize )
		{
			Log("CStringNet::Recv %s", recvbuff.c_str());

			if( recvbuff.compare( 0, 4, "echo" ) == 0 )			//	������
			{
				goto end;
			}

			token.parseString( recvbuff );						//	����ַ���
			if( token.size() <= STRINGNET_NAME  )				//	���ٻ���    ������Ϣ����@��|�ӿ�����|������|�����Ϣ     ������Ϣ����@��|�ӿ�����
			{
				goto end;
			}
			
			{
				PACKET_COMMAND* pkgcmd = m_PacketPool.Alloc();		//	���� PACKET_COMMAND
				if( pkgcmd == NULL )
				{
					Log(" +-StringNet AllocPacket Error!\n");
					goto end;
				}

				pkgcmd->SetNetID( sock );
				pkgcmd->m_Ref = token.getInt32( STRINGNET_NETID );

				int fidx = PACKET_RECV_NAME_FAST_TABLE.Find(token.getStr( STRINGNET_NAME ));
				if( fidx != PACKET_RECV_NAME_FAST_TABLE.InvalidIndex() )
				{
					pkgcmd->SetType( PACKET_RECV_NAME_FAST_TABLE[fidx] );
				}
				else
				{
					Log(" +-StringNet Packet Type Error!\n");
					m_PacketPool.Free( pkgcmd );
					goto end;
				}

				int nType = pkgcmd->Type();
				LPCSTR lpszFormat = GetCmdFormat( nType );
				if( lpszFormat == NULL )
				{
					Log(" +-StringNet lpszFormat == NULL!\n");
					m_PacketPool.Free( pkgcmd );
					goto end;
				}

				void* pParam  = pkgcmd->Data();
				*(char*)pParam    = INT64_FLAG;
				pParam = (char*)pParam + sizeof( char );
				*(int64_t*)pParam = token.getInt64( STRINGNET_GUID );
				++lpszFormat;++lpszFormat;								//	������һ������    ����������
				pParam = (char*)pParam + sizeof( int64_t );
				WORD wSize = sizeof( int64_t ) + sizeof( char );		//	���� ���������� ������

				int argidx;								// ��������
				int checklen  = 0;						// ������֤�ַ�������
				if( 0 == pkgcmd->m_Ref )				// Ĭ��@ǰ��Ĳ���Ϊ0ʱ���ǶԶ˷�������󣬲�����ʽ���в�ͬ
					argidx = STRINGNET_ARGS_SVR;
				else
					argidx = STRINGNET_ARGS_CLI;

				char base64Dst[2048] = {0};
				while( *lpszFormat )
				{
					Assert(*lpszFormat == '%');
					++lpszFormat;        // skip '%'
					checklen = 0;
					base64Dst[0] = '\0';

					switch( *lpszFormat )
					{
					case 'c': // BYTE
					case 'b': // BYTE
						{
							AppendFlag( pParam, BYTE_FLAG, wSize );
							DecodeBase64( token.getStr(argidx).c_str(), base64Dst, token.getStr(argidx).length() );
							sscanf( base64Dst, "%c", (char*)pParam );
							pParam = (char*)pParam + sizeof( char );
							wSize += sizeof( char );
							break;
						}
					case 'd': // int
					case 'i': // int
						{
							AppendFlag( pParam, INT_FLAG, wSize );
							DecodeBase64( token.getStr(argidx).c_str(), base64Dst, token.getStr(argidx).length() );
							sscanf( base64Dst, "%d", (int*)pParam );
							pParam = (char*)pParam + sizeof( int );
							wSize += sizeof( int );
							break;
						}
					case 'l': // int64
						{
							AppendFlag( pParam, INT64_FLAG, wSize );
							DecodeBase64( token.getStr(argidx).c_str(), base64Dst, token.getStr(argidx).length() );
							sscanf( base64Dst, INT64_FMT, (int64_t*)pParam );
							pParam = (char*)pParam + sizeof( int64_t );
							wSize += sizeof( int64_t );
							break;
						}
					case 'n': //32
						{
							AppendFlag( pParam, STRING_FLAG, wSize );
							DecodeBase64( token.getStr(argidx).c_str(), base64Dst, token.getStr(argidx).length() );
							const char * pString = base64Dst;
							do
							{
								AssertValidReadPtr( pString, sizeof( char ) );
								*(char*)pParam = *pString;
								pParam = (char*)pParam + 1;
								wSize += sizeof( char );

								if(checklen++ >= SHORT_STRING_LEN )
								{
									Log("CStringNet������Ϣʱ�������(Type=%d, Param=%s)", nType, *lpszFormat);
									return NULL;
								}
							}
							while( *pString++ );

							//������󳤶ȵĲ���
							while(SHORT_STRING_LEN - checklen > 0)
							{
								*(char*)pParam = '\0';
								pParam = (char*)pParam + 1;
								wSize += sizeof( char );
								++checklen;
							}
							break;
						}
					case 'o': //64
						{
							AppendFlag( pParam, STRING_FLAG, wSize );
							DecodeBase64( token.getStr(argidx).c_str(), base64Dst, token.getStr(argidx).length() );
							const char * pString = base64Dst;
							do
							{
								AssertValidReadPtr( pString, sizeof( char ) );
								*(char*)pParam = *pString;
								pParam = (char*)pParam + 1;
								wSize += sizeof( char );

								if(checklen++ >= DOUBLE_STRING_LEN )
								{
									Log("CStringNet������Ϣʱ�������(Type=%d, Param=%s)", nType, *lpszFormat);
									return NULL;
								}
							}
							while( *pString++ );

							//������󳤶ȵĲ���
							while(DOUBLE_STRING_LEN - checklen > 0)
							{
								*(char*)pParam = '\0';
								pParam = (char*)pParam + 1;
								wSize += sizeof( char );
								++checklen;
							}
							break;
						}
					case 'm': //128
						{
							AppendFlag( pParam, STRING_FLAG, wSize );
							DecodeBase64( token.getStr(argidx).c_str(), base64Dst, token.getStr(argidx).length() );
							const char * pString = base64Dst;
							do
							{
								AssertValidReadPtr( pString, sizeof( char ) );
								*(char*)pParam = *pString;
								pParam = (char*)pParam + 1;
								wSize += sizeof( char );

								if(checklen++ >= MEDIAL_STRING_LEN )
								{
									Log("CStringNet������Ϣʱ�������(Type=%d, Param=%s)", nType, *lpszFormat);
									return NULL;
								}
							}
							while( *pString++ );
							
							//������󳤶ȵĲ���
							while(MEDIAL_STRING_LEN - checklen > 0)
							{
								*(char*)pParam = '\0';
								pParam = (char*)pParam + 1;
								wSize += sizeof( char );
								++checklen;
							}
							break;
						}
					case 's': //200
						{
							AppendFlag( pParam, STRING_FLAG, wSize );
							DecodeBase64( token.getStr(argidx).c_str(), base64Dst, token.getStr(argidx).length() );
							const char * pString = base64Dst;
							do
							{
								AssertValidReadPtr( pString, sizeof( char ) );
								*(char*)pParam = *pString;
								pParam = (char*)pParam + 1;
								wSize += sizeof( char );

								if(checklen++ >= LONG_STRING_LEN )
								{
									Log("CStringNet������Ϣʱ�������(Type=%d, Param=%s)", nType, *lpszFormat);
									return NULL;
								}
							}
							while( *pString++ );

							//������󳤶ȵĲ���
							while(LONG_STRING_LEN - checklen > 0)
							{
								*(char*)pParam = '\0';
								pParam = (char*)pParam + 1;
								wSize += sizeof( char );
								++checklen;
							}
							break;
						}
					case 'h': //512
						{
							AppendFlag( pParam, STRING_FLAG, wSize );
							DecodeBase64( token.getStr(argidx).c_str(), base64Dst, token.getStr(argidx).length() );
							const char * pString = base64Dst;
							do
							{
								AssertValidReadPtr( pString, sizeof( char ) );
								*(char*)pParam = *pString;
								pParam = (char*)pParam + 1;
								wSize += sizeof( char );

								if(checklen++ >= HIGH_STRING_LEN )
								{
									Log("CStringNet������Ϣʱ�������(Type=%d, Param=%s)", nType, *lpszFormat);
									return NULL;
								}
							}
							while( *pString++ );

							//������󳤶ȵĲ���
							while(HIGH_STRING_LEN - checklen > 0)
							{
								*(char*)pParam = '\0';
								pParam = (char*)pParam + 1;
								wSize += sizeof( char );
								++checklen;
							}
							break;
						}
					default:
						Assert( 0 );
						break;
					}
					
					++argidx;
					++lpszFormat;
				}
				
				pkgcmd->nSize = wSize;
				pkgcmd->PacketOver();

				if( !addPacket(pkgcmd) )
				{
					m_PacketPool.Free(pkgcmd);
				}				
			}

end:
			recvbuff = "";

		}
	}

	return NULL;
}


/////////////////////////////////////////////////////////////////////////////////////
//
CGMStringNet::CGMStringNet()
{
}

CGMStringNet::~CGMStringNet()
{
}

//	guid(����)|�ӿ�����|�ӿ��������1|�ӿ��������2| �� �� |�ӿ��������n�����ַ�
int CGMStringNet::Send( SOCKET sock, PACKET_COMMAND* pPacket )
{
	if( !pPacket )
		return 0;

	char pkgTmp[PACKET_STRING_SIZE]={0};

	int pkgidx = _FormatPacket( pkgTmp, pPacket );
	if( pkgidx <= 0 )
	{
		Log("CStringNet::_FormatPacketʧ��");
		return 0;
	}

	if( !m_Net )
	{
		assert(m_Net);
		Log("CStringNet::Send()����Ч��m_Net");
		return 0;
	}

	//���� 0@
	return m_Net->Send( sock, pkgTmp+2, pkgidx-2 );
}

//	guid(����)|�ӿ�����|������|�����Ϣ|�������1|�������2| �� �� |�������n�����ַ�
int CGMStringNet::Recv( SOCKET sock,char* buf,DWORD nSize )
{
	m_nRecvSize += nSize;
	if(nSize<=0)
	{
		Log("Recv�Ĵ�СΪ<=0����\n");
		return 0;
	}

	//ƴ�� 0@
	char pkgTmp[PACKET_STRING_SIZE]={0};
	sprintf( pkgTmp, "0@%s", buf );

	PACKET_COMMAND* pkgcmd = _ParserPacket( sock, pkgTmp, nSize+2 );
	if( !addPacket(pkgcmd) )
	{
		m_PacketPool.Free(pkgcmd);
	}
	
	return nSize;
}


#ifdef WIN32
void GetLocalMAC(char *buf)
{
	IP_ADAPTER_INFO *IpAdaptersInfo =NULL;
	IP_ADAPTER_INFO *IpAdaptersInfoHead =NULL;
	IpAdaptersInfo = (IP_ADAPTER_INFO *) GlobalAlloc(GPTR, sizeof(IP_ADAPTER_INFO ));
	if (IpAdaptersInfo == NULL)
	{
		return;
	}
	DWORD dwDataSize = sizeof( IP_ADAPTER_INFO );
	DWORD dwRetVal = GetAdaptersInfo(IpAdaptersInfo,&dwDataSize);
	if ( ERROR_SUCCESS != dwRetVal)
	{
		GlobalFree( IpAdaptersInfo );
		IpAdaptersInfo = NULL;
		if( ERROR_BUFFER_OVERFLOW == dwRetVal)
		{
			IpAdaptersInfo =(IP_ADAPTER_INFO *) GlobalAlloc( GPTR, dwDataSize );
			if (IpAdaptersInfo == NULL)
			{
				return;
			}
			if ( ERROR_SUCCESS != GetAdaptersInfo( IpAdaptersInfo, &dwDataSize ))
			{
				GlobalFree( IpAdaptersInfo );
				return;
			}
		}
		else
		{
			return;
		}
	}
	//Save the head pointer of IP_ADAPTER_INFO structures list.
	IpAdaptersInfoHead = IpAdaptersInfo;
	/*
	do{
		if (IsLocalAdapter(IpAdaptersInfo->AdapterName))
		{
			sprintf(buf,"%02x-%02x-%02x-%02x-%02x-%02x",
				IpAdaptersInfo->Address[0],
				IpAdaptersInfo->Address[1],
				IpAdaptersInfo->Address[2],
				IpAdaptersInfo->Address[3],
				IpAdaptersInfo->Address[4],
				IpAdaptersInfo->Address[5]);
			//
			break;
		}
		IpAdaptersInfo = IpAdaptersInfo->Next;
	}while (IpAdaptersInfo);
	*/
	sprintf(buf,"%02x-%02x-%02x-%02x-%02x-%02x",
		IpAdaptersInfo->Address[0],
		IpAdaptersInfo->Address[1],
		IpAdaptersInfo->Address[2],
		IpAdaptersInfo->Address[3],
		IpAdaptersInfo->Address[4],
		IpAdaptersInfo->Address[5]);

	if (IpAdaptersInfoHead != NULL)
	{
		GlobalFree( IpAdaptersInfoHead );
	}
}

BOOL IsLocalAdapter(char *pAdapterName)
{
	BOOL ret_value = FALSE;
#define NET_CARD_KEY _T("System\\CurrentControlSet\\Control\\Network\\{4D36E972-E325-11CE-BFC1-08002BE10318}")
	char szDataBuf[MAX_PATH+1];
	DWORD dwDataLen = MAX_PATH;
	DWORD dwType = REG_SZ;
	HKEY hNetKey = NULL;
	HKEY hLocalNet = NULL;
	if(ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, NET_CARD_KEY, 0, KEY_READ, &hNetKey))
		return FALSE;
	wsprintf(szDataBuf, "%s\\Connection", pAdapterName);
	if(ERROR_SUCCESS != RegOpenKeyEx(hNetKey ,szDataBuf ,0 ,KEY_READ, &hLocalNet))
	{
		RegCloseKey(hNetKey);
		return FALSE;
	}
	if (ERROR_SUCCESS != RegQueryValueEx(hLocalNet, "MediaSubType", 0, &dwType, (BYTE *)szDataBuf, &dwDataLen))
	{
		goto ret;
	}
	if (*((DWORD *)szDataBuf)!=0x01)
		goto ret;
	dwDataLen = MAX_PATH;
	if (ERROR_SUCCESS != RegQueryValueEx(hLocalNet, "PnpInstanceID", 0, &dwType, (BYTE *)szDataBuf, &dwDataLen))
	{
		goto ret;
	}
	if (strncmp(szDataBuf, "PCI", strlen("PCI")))
		goto ret;
	ret_value = TRUE;
ret:
	RegCloseKey(hLocalNet);
	RegCloseKey(hNetKey);
	return ret_value;
}
#endif