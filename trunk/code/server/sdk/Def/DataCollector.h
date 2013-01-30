#ifndef _DATACOLLECTOR_H
#define _DATACOLLECTOR_H
#if 0
#include "CommData.h"
#include "PacketDefineHead.h"

#define MAX_ARRAY_NUM	20

class CDataCollector
{
public:
	CDataCollector();
	~CDataCollector();

	void	CollectSendMsg(int frame, int id, int size, int time);
	void	CollectRecvMsg(int frame, int id, int size, int time);

	void	PrintOrderRecvPackCnt(int& line);
	void	PrintOrderRecvPackSize(int& line);
	void	PrintOrderRecvPackTime(int& line);

	void	PrintOrderSendPackCnt(int& line);
	void	PrintOrderSendPackSize(int& line);

private:
	void	Order(int id, int value, int* dest);

public:
	///////////////////////////////////////////////////////////////
	//发消息的相关参数
	int64	m_nSendTotalPackCnt;		//处理消息报总数
	int64	m_nSendTotalPackSize;		//处理消息报总大小
	int		m_nSendPeekPackCnt;			//每帧处理消息报数量的峰值
	int		m_nSendPeekPackSize;		//每帧处理消息报大小的峰值
	int		m_nSendCurFramePackCnt;		//当前帧处理的消息总数
	int		m_nSendCurFramePackSize;	//当前帧处理的消息总大小
	int		m_nSendCurFrame;			//当前帧

	int		m_SendPackCnt[PACKET_END];
	int		m_SendPackSize[PACKET_END];

	int		m_OrderSendPackCnt[MAX_ARRAY_NUM];
	int		m_OrderSendPackSize[MAX_ARRAY_NUM];

	///////////////////////////////////////////////////////////////
	//收消息的相关参数
	int64	m_nRecvTotalPackCnt;		//处理消息报总数
	int64	m_nRecvTotalPackSize;		//处理消息报总大小
	int		m_nRecvPeekPackCnt;			//每帧处理消息报数量的峰值
	int		m_nRecvPeekPackSize;		//每帧处理消息报大小的峰值
	int		m_nRecvCurFramePackCnt;		//当前帧处理的消息总数
	int		m_nRecvCurFramePackSize;	//当前帧处理的消息总大小
	int		m_nRecvCurFrame;			//当前帧

	int		m_RecvPackCnt[PACKET_END];
	int		m_RecvPackSize[PACKET_END];
	int		m_RecvPackTime[PACKET_END];

	int		m_OrderRecvPackCnt[MAX_ARRAY_NUM];
	int		m_OrderRecvPackSize[MAX_ARRAY_NUM];
	int		m_OrderRecvPackTime[MAX_ARRAY_NUM];

};

//CDataCollector&		DataCollector();

#endif
#endif
