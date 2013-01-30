#include "StdAfx.h"
#include "DataCollector.h"
#include "vprof.h"
#if 0
////////////////////////////////////////////////////////////////////////////////
//
//CDataCollector&	DataCollector()
//{
//	static CDataCollector h;
//	return h;
//}

////////////////////////////////////////////////////////////////////////////////
//
CDataCollector::CDataCollector()
{

}

CDataCollector::~CDataCollector()
{

}

void CDataCollector::CollectSendMsg(int frame, int id, int size, int time)
{
	if(id < 0 || id >= PACKET_END)
		return;

	++m_SendPackCnt[id];
	m_SendPackSize[id] += size;

	Order(id, m_SendPackCnt[id], m_OrderSendPackCnt);
	Order(id, m_SendPackSize[id], m_OrderSendPackSize);

	++m_nSendTotalPackCnt;
	m_nSendTotalPackSize += size;

	if(m_nSendCurFrame == frame)
	{
		++m_nSendCurFramePackCnt;
		m_nSendCurFramePackSize +=size;
	}
	else
	{
		m_nSendPeekPackCnt = m_nSendPeekPackCnt > m_nSendCurFramePackCnt ? m_nSendPeekPackCnt : m_nSendCurFramePackCnt;
		m_nSendPeekPackSize = m_nSendPeekPackSize > m_nSendCurFramePackSize ? m_nSendPeekPackSize : m_nSendCurFramePackSize;

		m_nSendCurFrame = frame;
		m_nSendCurFramePackCnt = 1;
		m_nSendCurFramePackSize = size;
	}
}

void CDataCollector::CollectRecvMsg(int frame, int id, int size, int time)
{
	if(id < 0 || id >= PACKET_END)
		return;

	++m_RecvPackCnt[id];
	m_RecvPackSize[id] += size;
	m_RecvPackTime[id] += time;

	Order(id, m_RecvPackCnt[id], m_OrderRecvPackCnt);
	Order(id, m_RecvPackSize[id], m_OrderRecvPackSize);
	Order(id, m_RecvPackTime[id], m_OrderRecvPackTime);

	++m_nRecvTotalPackCnt;
	m_nRecvTotalPackSize += size;

	if(m_nRecvCurFrame == frame)
	{
		++m_nRecvCurFramePackCnt;
		m_nRecvCurFramePackSize +=size;
	}
	else
	{
		m_nRecvPeekPackCnt = m_nRecvPeekPackCnt > m_nRecvCurFramePackCnt ? m_nRecvPeekPackCnt : m_nRecvCurFramePackCnt;
		m_nRecvPeekPackSize = m_nRecvPeekPackSize > m_nRecvCurFramePackSize ? m_nRecvPeekPackSize : m_nRecvCurFramePackSize;

		m_nRecvCurFrame = frame;
		m_nRecvCurFramePackCnt = 1;
		m_nRecvCurFramePackSize = size;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CDataCollector::Order(int id, int value, int* dest)
{
	bool flag = false;
	for(int i=0; i<MAX_ARRAY_NUM; (++i)++)
	{
		if(id == *(dest+i))
		{
			flag = true;
			*(dest+i+1) = value;
			break;
		}
	}

	if(!flag)
	{
		int _id = id;
		int _value = value;
		for(int j=0; j<MAX_ARRAY_NUM; (++j)++)
		{
			if(_value > *(dest+j+1))
			{
				int tempid = *(dest+j);
				int tempvalue = *(dest+j+1);
				*(dest+j) = _id;
				*(dest+j+1) = _value;
				_id = tempid;
				_value = tempvalue;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
void CDataCollector::PrintOrderSendPackCnt(int& line)
{
	for(int i=0; i<MAX_ARRAY_NUM; (++i)++)
	{
		Print(line++, "send pack cnt:%d   %d\n", *(m_OrderSendPackCnt+i), *(m_OrderSendPackCnt+i+1));
	}
}

void CDataCollector::PrintOrderSendPackSize(int& line)
{
	for(int i=0; i<MAX_ARRAY_NUM; (++i)++)
	{
		Print(line++, "send pack size:%d   %d\n", *(m_OrderSendPackSize+i), *(m_OrderSendPackSize+i+1));
	}
}
void CDataCollector::PrintOrderRecvPackTime(int& line)
{
	for(int i=0; i<MAX_ARRAY_NUM; (++i)++)
	{
		Print(line++, "send pack time:%d   %d\n", *(m_OrderRecvPackTime+i), *(m_OrderRecvPackTime+i+1));
	}
}

void CDataCollector::PrintOrderRecvPackCnt(int& line)
{
	for(int i=0; i<MAX_ARRAY_NUM; (++i)++)
	{
		Print(line++, "recv pack cnt:%d   %d\n", *(m_OrderRecvPackCnt+i), *(m_OrderRecvPackCnt+i+1));
	}
}

void CDataCollector::PrintOrderRecvPackSize(int& line)
{
	for(int i=0; i<MAX_ARRAY_NUM; (++i)++)
	{
		Print(line++, "recv pack size:%d   %d\n", *(m_OrderRecvPackSize+i), *(m_OrderRecvPackSize+i+1));
	}
}
#endif