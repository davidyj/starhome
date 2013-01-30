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
	//����Ϣ����ز���
	int64	m_nSendTotalPackCnt;		//������Ϣ������
	int64	m_nSendTotalPackSize;		//������Ϣ���ܴ�С
	int		m_nSendPeekPackCnt;			//ÿ֡������Ϣ�������ķ�ֵ
	int		m_nSendPeekPackSize;		//ÿ֡������Ϣ����С�ķ�ֵ
	int		m_nSendCurFramePackCnt;		//��ǰ֡�������Ϣ����
	int		m_nSendCurFramePackSize;	//��ǰ֡�������Ϣ�ܴ�С
	int		m_nSendCurFrame;			//��ǰ֡

	int		m_SendPackCnt[PACKET_END];
	int		m_SendPackSize[PACKET_END];

	int		m_OrderSendPackCnt[MAX_ARRAY_NUM];
	int		m_OrderSendPackSize[MAX_ARRAY_NUM];

	///////////////////////////////////////////////////////////////
	//����Ϣ����ز���
	int64	m_nRecvTotalPackCnt;		//������Ϣ������
	int64	m_nRecvTotalPackSize;		//������Ϣ���ܴ�С
	int		m_nRecvPeekPackCnt;			//ÿ֡������Ϣ�������ķ�ֵ
	int		m_nRecvPeekPackSize;		//ÿ֡������Ϣ����С�ķ�ֵ
	int		m_nRecvCurFramePackCnt;		//��ǰ֡�������Ϣ����
	int		m_nRecvCurFramePackSize;	//��ǰ֡�������Ϣ�ܴ�С
	int		m_nRecvCurFrame;			//��ǰ֡

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
