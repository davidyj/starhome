#pragma once
#include "StdAfx.h"
#include "PacketDefineHead.h"
#include "GTime.h"
#include "ThreadLib.h"
#include "randomnumbers.h"
#include "SystemPerformance.h"
#include "core.h"

namespace NetTools
{
#	define NETINFO_NAME_LEN	64
#	define NETINFO_PATH_LEN 1024
#	define NETINFO_PKG_COUNT_MIN_2_PRINT 50

	class CNetInfo
	{
	private:

		int m_nDebugRecvPacket[NETINFO_PKG_COUNT_MIN_2_PRINT];
		int m_nCurrentRecvPacket;
		int m_nDebugSendPacket[NETINFO_PKG_COUNT_MIN_2_PRINT];
		int m_nCurrentSendPacket;

		LONG m_nPlayerCnt;

		LONG m_RecvPacketCounts[PACKET_END];	//	记录每一种收到的类型数据包的个数
		LONG m_SendPacketCounts[PACKET_END];	//	记录发送的类型消息包个数

		unsigned short m_PacketSize[PACKET_END];	//	消息类型的大小

		uint64	m_RecvByte;
		uint64	m_RecvByteSecondMax;
		uint64	m_SendByte;
		uint64	m_SendByteSecondMax;
		uint64	m_PreTime;
		uint64	m_RecvPkgCount;
		uint64	m_SendPkgCount;
		LONG	m_DropPkgCount;

		char	m_Name[NETINFO_NAME_LEN];
		char	m_szExePath[NETINFO_PATH_LEN];

	public:
		static CNetInfo& getSingle(){
			static CNetInfo mgr;
			return mgr;
		}

		static void Sampling( void* pArguments )
		{
#ifdef WIN32
		#if (!defined(_DEBUG)) && defined(WIN32)
			__try
		#endif
			{

			//char rrdstr[2048];
			CNetInfo* pThis = (CNetInfo*)pArguments;

			//长时间运行会导致服务器崩溃 by songjun 2012.5.6
			/*sprintf( rrdstr, "%s..\\bin\\rrdtool\\rrdtool create %sdata.rrd -s 1 --start "UINT64_FMT" \
							DS:recv:GAUGE:2:U:U \
							DS:send:GAUGE:2:U:U \
							DS:cpu:GAUGE:2:U:U \
							DS:memory:GAUGE:2:U:U \
							DS:pagefile:GAUGE:2:U:U \
							DS:player:GAUGE:2:U:U \
							RRA:AVERAGE:0.5:1:86400",
					pThis->m_szExePath, pThis->m_szExePath, time(NULL) );
			system( rrdstr );*/

			while(1)
			{
				Sleep(1000);

				//uint CurTime = Time().GetCurrentTime();
				//int second = CurTime - pThis->m_PreTime;
				//pThis->m_PreTime = CurTime;
				++(pThis->m_PreTime);

				pThis->m_RecvPkgCount = 0;
				uint64 recvbyte = 0;

				for(int i = 0; i<PACKET_END; i++)
				{
					LONG rcv = pThis->m_RecvPacketCounts[i];
					if( rcv > 0 )
					{
						pThis->m_RecvPkgCount += rcv;
						recvbyte += rcv * pThis->m_PacketSize[i];
					}
				}

				pThis->m_SendPkgCount  = 0;
				uint64 sendbyte = 0;

				for(int i = 0; i<PACKET_END; i++)
				{
					LONG send = pThis->m_SendPacketCounts[i];
					if( send > 0 )
					{
						pThis->m_SendPkgCount += send;
						sendbyte += send * pThis->m_PacketSize[i];
					}
				}

				uint recv_b_s = (recvbyte - pThis->m_RecvByte)/*/second*/;
				if( recv_b_s > pThis->m_RecvByteSecondMax )
				{
					pThis->m_RecvByteSecondMax = recv_b_s;
				}

				uint send_b_s = (sendbyte - pThis->m_SendByte)/*/second*/;
				if( send_b_s > pThis->m_SendByteSecondMax )
				{
					pThis->m_SendByteSecondMax = send_b_s;
				}

				pThis->m_RecvByte = recvbyte;
				pThis->m_SendByte = sendbyte;

				/*int64 mem, vmem;
				int cpu = CSystemPerformance::getSingle().GetCpuUsage();
				CSystemPerformance::getSingle().GetMemoryUsage( mem, vmem );

				time_t curtime = time(NULL);*/
				//长时间运行会导致服务器崩溃 by songjun 2012.5.6
				/*sprintf( rrdstr, "%s..\\bin\\rrdtool\\rrdtool update %sdata.rrd "UINT64_FMT":%d:%d:%d:%d:%d:%d",
					pThis->m_szExePath, pThis->m_szExePath, curtime, recv_b_s, send_b_s, cpu, mem/1024/1024, vmem/1024/1024, pThis->m_nPlayerCnt );
				system( rrdstr );*/
			}

			}
		#if (!defined(_DEBUG)) && defined(WIN32)
			__except (HandleException(GetExceptionInformation(), "NetTools::CNetInfo::Sampling"))
			{

			}
		#endif
#endif  // WIN32
		}

		CNetInfo():m_PreTime(1)
		{
			memset( m_szExePath, 0, NETINFO_PATH_LEN*sizeof(char) );
			strncpy( m_Name, "CNetInfo has not been initialized", NETINFO_NAME_LEN );
		}

		void Init( const char* name, const char* szExePath, int pathSize )
		{
			m_nCurrentRecvPacket = 0;
			m_nCurrentSendPacket = 0;
			m_RecvByte = 0;
			m_SendByte = 0;
			m_RecvByteSecondMax = 0;
			m_SendByteSecondMax = 0;
			m_RecvPkgCount = 0;
			m_SendPkgCount = 0;
			m_DropPkgCount = 0;
			m_PreTime = 0;
			m_nPlayerCnt = 0;

			memcpy( m_szExePath, szExePath, pathSize );
			memset( m_nDebugRecvPacket, 0, NETINFO_PKG_COUNT_MIN_2_PRINT*sizeof(int) );
			memset( m_nDebugSendPacket, 0, NETINFO_PKG_COUNT_MIN_2_PRINT*sizeof(int) );
			memset( m_RecvPacketCounts, 0, PACKET_END*sizeof(LONG) );
			memset( m_SendPacketCounts, 0, PACKET_END*sizeof(LONG) );
			strncpy( m_Name, name, NETINFO_NAME_LEN );

			for(int i = 0; i<PACKET_END; i++)
			{
				m_PacketSize[i] = GetPacketDefSize(i) + PACKET_COMMAND::HeadSize();
			}

			ThreadLib::Create( Sampling, this );
		}

		void IncRecvPacketCount(int type)
		{
			if(type>0&&type<PACKET_END)
				InterlockedIncrement(&m_RecvPacketCounts[type]);
		}

		void IncSendPacketCount(int type)
		{
			if(type>0&&type<PACKET_END)
				InterlockedIncrement(&m_SendPacketCounts[type]);
		}

		void IncPlayerCnt()
		{
			InterlockedIncrement(&m_nPlayerCnt);
		}
		void DecPlayerCnt()
		{
			InterlockedDecrement(&m_nPlayerCnt);
		}

		void IncDropPacketCount()
		{
			InterlockedIncrement(&m_DropPkgCount);
		}

		void PrintNetInfo(int outline)
		{
			Print(outline++,"%s - NetTools::CNetInfo.PrintNetInfo()", m_Name );
			Print(outline++,"Run time: %d Second      ", m_PreTime );
			Print(outline++,"");
			Print(outline++,"接收：");
			Print(outline++,"平均：       "UINT64_FMT" 字节/秒       ", m_RecvByte/m_PreTime);
			Print(outline++,"峰值：       "UINT64_FMT" 字节/秒       ", m_RecvByteSecondMax);
			Print(outline++,"总字节数：   "UINT64_FMT"               ", m_RecvByte);
			Print(outline++,"收包个数：   "UINT64_FMT"               ", m_RecvPkgCount);
			Print(outline++,"");
			Print(outline++,"发送：");
			Print(outline++,"平均：       "UINT64_FMT" 字节/秒       ", m_SendByte/m_PreTime);
			Print(outline++,"峰值：       "UINT64_FMT" 字节/秒       ", m_SendByteSecondMax);
			Print(outline++,"总字节数：   "UINT64_FMT"               ", m_SendByte);
			Print(outline++,"发包个数：   "UINT64_FMT"               ", m_SendPkgCount);
			Print(outline++,"丢包个数：   "UINT64_FMT"               ", m_DropPkgCount);
		}

		//打印出数量排在前面的收到的消息信息 by zhao
		void PrintRecvPacketType()
		{
			int nIndex=0;
			LONG lMax=m_RecvPacketCounts[0];

			for(int i = 0; i<PACKET_END; i++)
			{
				bool bFlag=false;

				for(int j=0;j<m_nCurrentRecvPacket;j++)
				{
					if(m_nDebugRecvPacket[j]==i)
					{
						bFlag=true;
						break;
					}
				}

				if(bFlag)
					continue;

				//最大数量的消息
				if(m_RecvPacketCounts[i]>lMax)
				{
					lMax=m_RecvPacketCounts[i];
					nIndex=i;
				}
			}

			m_nDebugRecvPacket[m_nCurrentRecvPacket]=nIndex;
			int nDebugOutLine = GetDebugOutLine();

			Print(nDebugOutLine++,"%s - NetTools::CNetInfo.PrintRecvPacketType()\n", m_Name);

			//打印出数量大的消息
			for(int i=0;i<NETINFO_PKG_COUNT_MIN_2_PRINT;i++)
			{
				if(m_nDebugRecvPacket[i]>=0&&m_nDebugRecvPacket[i]<PACKET_END)
				{
					if(m_RecvPacketCounts[m_nDebugRecvPacket[i]]>0)
					{
						Print(nDebugOutLine++,"PACKET_TYPE:%d\t%d\n",
							m_nDebugRecvPacket[i], m_RecvPacketCounts[m_nDebugRecvPacket[i]]);
					}
				}
			}

			if(++m_nCurrentRecvPacket>=NETINFO_PKG_COUNT_MIN_2_PRINT)
			{
				m_nCurrentRecvPacket=0;
				memset(m_nDebugRecvPacket,0,sizeof(int)*NETINFO_PKG_COUNT_MIN_2_PRINT);
			}
		}


		//打印出数量排在前面的发送的消息信息 by zhao
		void PrintSendPacketType()
		{
			int nIndex=0;
			LONG lMax=m_SendPacketCounts[0];

			for(int i = 0; i<PACKET_END; i++)
			{
				bool bFlag=false;

				for(int j=0;j<m_nCurrentSendPacket;j++)
				{
					if(m_nDebugSendPacket[j]==i)
					{
						bFlag=true;
						break;
					}
				}

				if(bFlag)
					continue;

				//最大数量的消息
				if(m_SendPacketCounts[i]>lMax)
				{
					lMax=m_SendPacketCounts[i];
					nIndex=i;
				}
			}

			m_nDebugSendPacket[m_nCurrentSendPacket]=nIndex;
			int nDebugOutLine = GetDebugOutLine();

			Print(nDebugOutLine++,"%s - NetTools::CNetInfo.PrintSendPacketType()\n", m_Name);

			//打印出数量大的消息
			for(int i=0;i<NETINFO_PKG_COUNT_MIN_2_PRINT;i++)
			{
				if(m_nDebugSendPacket[i]>=0&&m_nDebugSendPacket[i]<PACKET_END)
				{
					if(m_SendPacketCounts[m_nDebugSendPacket[i]]>0)
					{
						Print(nDebugOutLine++,"PACKET_TYPE:%d\t%d\n",
							m_nDebugSendPacket[i], m_SendPacketCounts[m_nDebugSendPacket[i]]);
					}
				}
			}

			if(++m_nCurrentSendPacket>=NETINFO_PKG_COUNT_MIN_2_PRINT)
			{
				m_nCurrentSendPacket=0;
				memset(m_nDebugSendPacket,0,sizeof(int)*NETINFO_PKG_COUNT_MIN_2_PRINT);
			}
		}
	};

};
