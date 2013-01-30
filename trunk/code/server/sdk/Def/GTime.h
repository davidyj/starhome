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
	int     m_nWeek;		//礼拜
	int		m_Moth;			//月
	int		m_Data;			//日
	int 	m_Hour;			//时间
	int 	m_Min;			//分钟
	int		m_Type;			//类型
	int     m_Rule;         //报时机制
	int     m_Event;        //报时通知发生的事件
	UINT64	m_ID;			//报时事件
	UINT64  m_Param;		//报时参数

	Timer_Obj()
	{
		m_Ref	= 0;
		m_nWeek	= 0;			//礼拜
		m_Moth	= 0;			//月
		m_Data	= 0;			//日
		m_Hour	= 0;			//时间
		m_Min	= 0;			//分钟
		m_Type	= 0;			//类型
		m_Rule	= 0;         //报时机制
		m_Event	= 0;        //报时通知发生的事件
		m_ID	= 0;			//报时事件
		m_Param = 0;		//报时参数
	}
	inline void Release()
	{
		m_Ref	= 0;
		m_nWeek	= 0;			//礼拜
		m_Moth	= 0;			//月
		m_Data	= 0;			//日
		m_Hour	= 0;			//时间
		m_Min	= 0;			//分钟
		m_Type	= 0;			//类型
		m_Rule	= 0;         //报时机制
		m_Event	= 0;        //报时通知发生的事件
		m_ID	= 0;			//报时事件
		m_Param = 0;		//报时参数
	}
};

//注册类型
enum Time_Reg_Type
{
	Time_Reg_Type_Invalid    =   0,		//无效类型
	Time_Reg_Type_Person,				//角色
	Time_Reg_Type_Quest,				//Quest
	Time_Reg_Type_AIUnit,				//AI脚本
	Time_Reg_Type_Question,				//答题活动
	Time_Reg_Type_Question_TVMsgPre5,   //答题开始前 5 min 的TVMsg
	Time_Reg_Type_Question_TVMsgPre3,   //答题开始前 3 min 的TVMsg
	Time_Reg_Type_Question_TVMsgPre1,   //答题开始前 1 min 的TVMsg
	Time_Reg_Type_Top,					//排名系统
	Time_Reg_Type_SignUp,               //注册系统
	Time_Reg_Type_Campaign,             //活动系统
	Time_Reg_Type_NewTv,                //新闻电视系统
	Time_Reg_Type_Family,				//家族系统
	Time_Reg_Type_Gang,					//帮会系统
	Time_Reg_Type_State,				//国家系统
	Time_Reg_Type_Clock_2,              //时间活跃度2点时计算
	Time_Reg_Type_Clock_8,              //时间活跃度8点时计算
	Time_Reg_Type_Clock_14,             //时间活跃度14点时计算
	Time_Reg_Type_Clock_20,             //时间活跃度20点时计算
};

//报时机制
enum Time_Call_Rule
{
	Time_Call_Rule_Invalid   =  0, //无效
	Time_Call_Rule_Min,
	Time_Call_Rule_Sec,
};

//报时发生事件
enum Time_Call_Event
{
	Time_Call_Event_Invalid =  0,  //无效
	Time_Call_Event_StartSignUp,   //报名开始
	Time_Call_Event_OverSignUp,		//报名结束
	Time_Call_Event_Accordance,		//配对
	Time_Call_Event_StartGame,     //活动开始
	Time_Call_Event_OverGame,	   //活动结束
	Time_Call_Event_Question,	   //答题系统刷新
};

//星期
enum Week_Type
{
	Week_Type_Sunday=0,		//星期天
	Week_Type_Monday,		//星期一
	Week_Type_Tuesday,		//星期二
	Week_Type_Wednesday,	//星期三
	Week_Type_Thursday,		//星期四
	Week_Type_Friday,       //星期五
	Week_Type_Saturday,		//星期六
	Week_Type_Everyday=8,	//每天
};

//中文时间格式
enum ChinaTimeFormat
{
	China_S			= 1 << 0,	//秒
	China_m			= 1 << 1,	//分
	China_H			= 1 << 2,	//时
	China_D			= 1 << 3,	//日
	China_M			= 1 << 4,	//月
	China_Y		    = 1 << 5,   //年
};

//刷新类型
enum Refresh_Type
{
	Refresh_Type_All = 0,		//刷新所有
	Refresh_Type_Day,			//每天刷新
	Refresh_Type_Week,			//每周刷新
	Refresh_Type_Month,			//每月刷新
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

	void			GetNowTime(GTime &t);				//得到当前时间
	TMV				GetCurrentTimeMS( );				//win下：得到当前时间到程序启动时的间隔毫秒数
	TMV				GetCurrentTimeMSEx();				//得到当前时间（到1970年1月1日0点的毫秒数）
	inline TMV		GetCurrentTime()			{return m_Tick;}
	inline void		SetCurrentTime(TMV time)	{m_Lock.LOCK();m_Tick = time;m_Lock.UNLOCK();}

	//TMV --> CGTime
	void			CoverTMVToGTM(TMV tmv,GTime &gtm);
	//CGTime --> tm
	void			CoverGTMTotm(GTime &gtm,tm &t);
	//CGTime --> TMV
	TMV				CoverGTMToTMV(GTime &gtm);

    //注册时间
	//ID:注册ID，	ntype:注册类型Time_Reg_Type,	nTime:int 时间格式，	nRule:报时机制Time_Call_Rule，	nTimeEvent:通告事件
	BOOL            RegisterTime(uint64 ID,int ntype,TIME_FORMAT nTime,int nRule=Time_Call_Rule_Min,int nWeek=Week_Type_Everyday,int nTimeEvent=Time_Call_Event_Invalid,int64 nParam=INVALID_PID);
	BOOL            UnRegisterTime(uint64 ID,int ntype,int nRule=Time_Call_Rule_Min);

	void			Synch(CNetObj* pNetObj);

	inline void		IncreaceCurrentTime()		{m_Lock.LOCK();++m_Tick;m_Lock.UNLOCK();}

	///////////////////各服务器及客户端私有接口///////////////////////////////
	//dataserver
//	BOOL			OnDelayShutDownServer(int64 i64BeginTime);                           //全服15分钟后关闭玩家提示处理    ChenXY 2011/7/16
//	BOOL			OnPlayerLoginFlashBoxFunc(PersonID PID);                             //Player 登陆 闪框   处理  针对关服        ChenXY 2011/7/16
	//communityserver
	char*			FormatChinaTime(GTime gTime, int TimeType);
	//superserver
	void			SynchAllServer();

	//client
	void			Request_SetTime(TMV tm);

#ifdef _SURPERSERVER
	BOOL			RefreshAllServerAttributesEveryDay(int nRefreshType);		//手动刷新所有服务器0点时属性 add by lfy 2012.7.13
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
	TMV									m_Tick;	//当前时间
	CGLock								m_Lock;
	int									m_nLastDay;
	int									m_nLastHour;			//最后报时的点数
	int									m_nLastMin;			//最后报时的分钟数
	int                                 m_nLastSec;         //最后报时的秒数
	CUtlLinkedList<Timer_Obj*>			m_MinTimeList;			//注册的时间
	CUtlLinkedList<Timer_Obj*>			m_SecTimeList;			//注册的时间
	int64								m_clienttime;
	int64								m_iShutDownTime;
	char								FormatTime[256];

};

//DWORD WINAPI Tick(void *param);
void Tick(void *param);


CGTime& Time();
