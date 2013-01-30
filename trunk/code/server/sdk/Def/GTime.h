#pragma	   once
#include <time.h>
#include "GLock.h"
#include "utllinkedlist.h"
#include "PacketDefine.h"
#include "CommData.h"

#ifndef WIN32
#include <sys/time.h>
#endif

typedef int TIME_FORMAT;


class CNetObj;


struct GTime
{
	GTime()
	{
		Clean();
	}

	void Clean()
	{
		gtm_sec = 0;
		gtm_min = 0;
		gtm_hour = 0;
		gtm_mday = 0;
		gtm_mon = 0;
		gtm_year = 0;
		gtm_wday = 0;
	}

	inline GTime& operator = ( const GTime& pt )
	{
		gtm_sec		= pt.gtm_sec;
		gtm_min		= pt.gtm_min;
		gtm_hour	= pt.gtm_hour;
		gtm_mday	= pt.gtm_mday;
		gtm_mon		= pt.gtm_mon;
		gtm_year	= pt.gtm_year;
		gtm_wday	= pt.gtm_wday;
		return *this;
	}

	int gtm_sec;     /* [1,60] */
	int gtm_min;     /* [1,60] */
	int gtm_hour;    /* [1,24] */
	int gtm_mday;    /* [1,31] */
	int gtm_mon;     /* [1,12] */
	int gtm_year;    /* [****] */
	int gtm_wday;    /* [0,6] */
};

struct Timer_Obj
{
	int		m_Ref;
	int     m_nWeek;		//���
	int		m_Moth;			//��
	int		m_Data;			//��
	int 	m_Hour;			//ʱ��
	int 	m_Min;			//����
	int		m_Type;			//����
	int     m_Rule;         //��ʱ����
	int     m_Event;        //��ʱ֪ͨ�������¼�
	UINT64	m_ID;			//��ʱ�¼�
	UINT64  m_Param;		//��ʱ����

	Timer_Obj()
	{
		m_Ref	= 0;
		m_nWeek	= 0;			//���
		m_Moth	= 0;			//��
		m_Data	= 0;			//��
		m_Hour	= 0;			//ʱ��
		m_Min	= 0;			//����
		m_Type	= 0;			//����
		m_Rule	= 0;         //��ʱ����
		m_Event	= 0;        //��ʱ֪ͨ�������¼�
		m_ID	= 0;			//��ʱ�¼�
		m_Param = 0;		//��ʱ����
	}
	inline void Release()
	{
		m_Ref	= 0;
		m_nWeek	= 0;			//���
		m_Moth	= 0;			//��
		m_Data	= 0;			//��
		m_Hour	= 0;			//ʱ��
		m_Min	= 0;			//����
		m_Type	= 0;			//����
		m_Rule	= 0;         //��ʱ����
		m_Event	= 0;        //��ʱ֪ͨ�������¼�
		m_ID	= 0;			//��ʱ�¼�
		m_Param = 0;		//��ʱ����
	}
};

//ע������
enum Time_Reg_Type
{
	Time_Reg_Type_Invalid    =   0,		//��Ч����
	Time_Reg_Type_Person,				//��ɫ
	Time_Reg_Type_Quest,				//Quest
	Time_Reg_Type_AIUnit,				//AI�ű�
	Time_Reg_Type_Question,				//����
	Time_Reg_Type_Question_TVMsgPre5,   //���⿪ʼǰ 5 min ��TVMsg
	Time_Reg_Type_Question_TVMsgPre3,   //���⿪ʼǰ 3 min ��TVMsg
	Time_Reg_Type_Question_TVMsgPre1,   //���⿪ʼǰ 1 min ��TVMsg
	Time_Reg_Type_Top,					//����ϵͳ
	Time_Reg_Type_SignUp,               //ע��ϵͳ
	Time_Reg_Type_Campaign,             //�ϵͳ
	Time_Reg_Type_NewTv,                //���ŵ���ϵͳ
	Time_Reg_Type_Family,				//����ϵͳ
	Time_Reg_Type_Gang,					//���ϵͳ
	Time_Reg_Type_State,				//����ϵͳ
	Time_Reg_Type_Clock_2,              //ʱ���Ծ��2��ʱ����
	Time_Reg_Type_Clock_8,              //ʱ���Ծ��8��ʱ����
	Time_Reg_Type_Clock_14,             //ʱ���Ծ��14��ʱ����
	Time_Reg_Type_Clock_20,             //ʱ���Ծ��20��ʱ����
};

//��ʱ����
enum Time_Call_Rule
{
	Time_Call_Rule_Invalid   =  0, //��Ч
	Time_Call_Rule_Min,
	Time_Call_Rule_Sec,
};

//��ʱ�����¼�
enum Time_Call_Event
{
	Time_Call_Event_Invalid =  0,  //��Ч
	Time_Call_Event_StartSignUp,   //������ʼ
	Time_Call_Event_OverSignUp,		//��������
	Time_Call_Event_Accordance,		//���
	Time_Call_Event_StartGame,     //���ʼ
	Time_Call_Event_OverGame,	   //�����
	Time_Call_Event_Question,	   //����ϵͳˢ��
};

//����
enum Week_Type
{
	Week_Type_Sunday=0,		//������
	Week_Type_Monday,		//����һ
	Week_Type_Tuesday,		//���ڶ�
	Week_Type_Wednesday,	//������
	Week_Type_Thursday,		//������
	Week_Type_Friday,       //������
	Week_Type_Saturday,		//������
	Week_Type_Everyday=8,	//ÿ��
};

//����ʱ���ʽ
enum ChinaTimeFormat
{
	China_S			= 1 << 0,	//��
	China_m			= 1 << 1,	//��
	China_H			= 1 << 2,	//ʱ
	China_D			= 1 << 3,	//��
	China_M			= 1 << 4,	//��
	China_Y		    = 1 << 5,   //��
};

//ˢ������
enum Refresh_Type
{
	Refresh_Type_All = 0,		//ˢ������
	Refresh_Type_Day,			//ÿ��ˢ��
	Refresh_Type_Week,			//ÿ��ˢ��
	Refresh_Type_Month,			//ÿ��ˢ��
};

class CGTime
{
public:
	CGTime();
	~CGTime();

	virtual bool	Init();
	virtual void	Release();
	virtual BOOL	Logic();
	virtual BOOL	OnMsg(PACKET_COMMAND* pPacket);

	void			GetNowTime(GTime &t);				//�õ���ǰʱ��
	TMV				GetCurrentTimeMS( );				//win�£��õ���ǰʱ�䵽��������ʱ�ļ��������
	TMV				GetCurrentTimeMSEx();				//�õ���ǰʱ�䣨��1970��1��1��0��ĺ�������
	inline TMV		GetCurrentTime()			{return m_Tick;}
	inline void		SetCurrentTime(TMV time)	{m_Lock.LOCK();m_Tick = time;m_Lock.UNLOCK();}

	//TMV --> CGTime
	void			CoverTMVToGTM(TMV tmv,GTime &gtm);
	//CGTime --> tm
	void			CoverGTMTotm(GTime &gtm,tm &t);
	//CGTime --> TMV
	TMV				CoverGTMToTMV(GTime &gtm);

    //ע��ʱ��
	//ID:ע��ID��	ntype:ע������Time_Reg_Type,	nTime:int ʱ���ʽ��	nRule:��ʱ����Time_Call_Rule��	nTimeEvent:ͨ���¼�
	BOOL            RegisterTime(uint64 ID,int ntype,TIME_FORMAT nTime,int nRule=Time_Call_Rule_Min,int nWeek=Week_Type_Everyday,int nTimeEvent=Time_Call_Event_Invalid,int64 nParam=INVALID_PID);
	BOOL            UnRegisterTime(uint64 ID,int ntype,int nRule=Time_Call_Rule_Min);

	void			Synch(CNetObj* pNetObj);

	inline void		IncreaceCurrentTime()		{m_Lock.LOCK();++m_Tick;m_Lock.UNLOCK();}

	///////////////////�����������ͻ���˽�нӿ�///////////////////////////////
	//dataserver
//	BOOL			OnDelayShutDownServer(int64 i64BeginTime);                           //ȫ��15���Ӻ�ر������ʾ����    ChenXY 2011/7/16
//	BOOL			OnPlayerLoginFlashBoxFunc(PersonID PID);                             //Player ��½ ����   ����  ��Թط�        ChenXY 2011/7/16
	//communityserver
	char*			FormatChinaTime(GTime gTime, int TimeType);
	//superserver
	void			SynchAllServer();

	//client
	void			Request_SetTime(TMV tm);

#ifdef _SURPERSERVER
	BOOL			RefreshAllServerAttributesEveryDay(int nRefreshType);		//�ֶ�ˢ�����з�����0��ʱ���� add by lfy 2012.7.13
#endif

protected:
	BOOL			Packet_TimeSync(PACKET_COMMAND* pPacket);
	BOOL			Packet_DebugSetTime(PACKET_COMMAND* pPacket);
	BOOL			Packet_RefreshAttribEveryday(PACKET_COMMAND* pPacket);
	BOOL			Packet_REQRefreshAttributes(PACKET_COMMAND* pPacket);	

	BOOL			Logic_DataServer();
	BOOL			Logic_CommunityServer();
	BOOL			Logic_SuperServer();
	BOOL			Logic_LoginServer();
	BOOL			Logic_DBServer();
	BOOL			Logic_DNSServer();
	BOOL			Logic_Client();

#ifdef _COMMUNITYSERVER
	void			RefreshAttributesAll();
	void			RefreshAttributesByDay();
	void			RefreshAttributesByWeek();
	void			RefreshAttributesByMonth();
#endif

protected:
	TMV									m_Tick;	//��ǰʱ��
	CGLock								m_Lock;
	int									m_nLastDay;
	int									m_nLastHour;			//���ʱ�ĵ���
	int									m_nLastMin;			//���ʱ�ķ�����
	int                                 m_nLastSec;         //���ʱ������
	CUtlLinkedList<Timer_Obj*>			m_MinTimeList;			//ע���ʱ��
	CUtlLinkedList<Timer_Obj*>			m_SecTimeList;			//ע���ʱ��
	int64								m_clienttime;
	int64								m_iShutDownTime;
	char								FormatTime[256];

};

//DWORD WINAPI Tick(void *param);
void Tick(void *param);


CGTime& Time();
