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
//	Type		: 引擎的类型
//	nListenPort	: 监听端口号
//  nConnectMax	: 链接的最大数 ，用来预开辟空间
//  nQueueSize	: 消息队列的长度
//  nRecvSize	: 接受消息的缓冲区大小
//	nSendSize	: 发送消息的缓冲区大小
//  nTimeout	: 发送超时
BOOL CGameNet::Begin(NET_IO_TYPE Type,int nPacketPoolSize,int nListenPort,int nConnectMax,int nQueueSize,int nRecvSize,int nSendSize,int nTimeout,int nAcceptCount)
{
	Assert(nConnectMax);
	if(!nConnectMax)
		return FALSE;

	// 预分配 m_BufferPacketTable;
	m_ConnectMax = nConnectMax;

	m_BufferPacketTable = (BUFFER_TO_PACKET*)Plat_Alloc(sizeof(BUFFER_TO_PACKET)*nConnectMax);
	for(int i=0;i<nConnectMax;i++)
	{
		m_BufferPacketTable[i].Init();
	}

	m_nBuffToPacketCountMax = nConnectMax;

	//初始化Socket管理器
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
* 把PACKET_COMMAND命令解压缩，分解成若干个PACKET_COMMAND对象
* pkt: 输入的命令
* pktList: 输出的命令
* pktCnt: 输出命令的个数
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

	unsigned char *p = pkt->Data(); //指向这个PACKET_COMMAND的data部分

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

		//校验消息头中的数据长度
		if(GetParamLen(GetCmdFormat(type)) != (size - PACKET_COMMAND::DATA_PARAM))
		{
			Plat_Free(result);
			Log("+-接收到的数据长度错误！");
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
		Log(" socket %d 发送失败 packet type %d size %d",sock,pPack->Type(),pPack->Size());
	}*/
	return g_ret;
}

int CGameNet::Send(SOCKET sock, char* buf, DWORD size)
{
	m_nSendSize += size;

	if (  m_Net )
		g_ret = m_Net->Send( sock, buf, size);
	/*if( g_ret <= 0){
		Log(" socket %d 发送失败 buff size %d", sock, size);
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
		Log("Recv的大小为<=0的数,sock=%d\n", sock);
		return 0;
	}
	
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

	UINT nReadPtr = 0;
	while (nReadPtr < nSize)
	{
		if (pBufPacket->pPacket == NULL)							//如果 socket 对应的 Packet 缓存已经被清空，就分配一个新的缓存
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

		int nChunkLeftSize = nSize - nReadPtr;    //Chunk 剩余长度
		if( nChunkLeftSize <= 0)
		{
			Log("nChunkLeftSize = %d\n",nChunkLeftSize);
			m_PacketPool.Free(pBufPacket->pPacket);
			pBufPacket->Reset();
			return nSize;
		}

		if(pBufPacket->IsHeadFull())					// 如果Packet缓存中 消息头已经写完，那么包的大小就是已知的，可以摘出整个包了
		{
			if(pBufPacket->GetPacketLeftSize() < 0)
			{
				Log("Get GetPacketLeftSize Error %d \n",pBufPacket->GetPacketLeftSize());
				m_PacketPool.Free(pBufPacket->pPacket);
				pBufPacket->Reset();
				return 0;
			}

			if(pBufPacket->GetPacketLeftSize() <= nChunkLeftSize)  // 如果Packet缓存中，还未写完的长度小于 Chunk 剩余长度
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
			else													// 否则，Chunk 剩余的长度仍然不足以写满这个Packet缓存
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
		else											// 否则Packet缓存中 消息头未写完，先把消息头写完整
		{
			if(pBufPacket->GetHeadLeftSize() < 0)
			{
				Log("Get GetHeadLeftSize Error %d \n",pBufPacket->GetHeadLeftSize());
				m_PacketPool.Free(pBufPacket->pPacket);
				pBufPacket->Reset();
				return nSize;
			}

			if(pBufPacket->GetHeadLeftSize() <= nChunkLeftSize)  // 如果Packet缓存中，消息头还未写完的长度小于 Chunk 剩余长度
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
			else													// 否则，Chunk 剩余的长度仍然不足以写满这个Packet缓存的消息头
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


		if(pBufPacket->pPacket && pBufPacket->IsHeadFull()) // 如果有一个完整的Packet在缓存中就把它送入链表并清空缓存
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
				// 因为存在非压缩的数据 所以需要判断一下 By David 2010-2-18
				if(true)
				{
					//客户端不可能发来压缩的消息包
					//fixed by david  2012年11月5日
					if(m_isClient)
					{
						Log("收到玩家的非法消息包");
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