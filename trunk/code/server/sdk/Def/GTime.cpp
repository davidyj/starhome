#include "StdAfx.h"
#include <sys/timeb.h>
#include "mempool.h"
#include "GTime.h"
#include "PacketDefineHead.h"
#include "GameNet.h"
#include "vprof.h"
#include "MemoryPoolDef.h"
#include "NetObj.h"
#include "ThreadLib.h"


#ifdef _DATASERVER_
#include "LuaEngine_Svr.h"
#include "PlayerObj.h"
#include "PlayerMgr.h"
#include "QuestMgr.h"
#include "QuestionObjMgr.h"
#include "AIUnitMgr.h"
#include "Event.h"
#include "SignUpMgr.h"
#include "FamilyMgr.h"
#include "GangMgr.h"
#include "TeamMgr.h"
#include "StateMgr.h"
#include "SceneObj.h"
#include "SceneMgr.h"
#include "VitalityMgr.h"
#include "ErrorIDTable.h"
#endif
#ifdef _COMMUNITYSERVER
#include "LuaEngine_Svr.h"
#include "PlayerObj.h"
#include "PlayerMgr.h"
#include "EventMgr.h"
#include "SignUpMgr.h"
#include "TeamMgr.h"
#include "TopMgr.h"
#include "DBServer.h"
#include "ErrorIDTable.h"
#include "QuestionObjMgr.h"
#endif
#ifdef _LOGINSERVER
#include "UserMgr.h"
#include "User.h"
#include "PlayerObj.h"
#include "PlayerMgr.h"
#include "ErrorIDTable.h"
#endif
#ifdef _SURPERSERVER
#include "SuperServerMgr.h"
#endif
#ifdef _CLIENT_
#include "PlayerObj.h"
#include "PlayerMgr.h"
#include "UIEventMgr.h"
#include "LuaScene.h"
#include "SecurityFilterMgr.h"
#endif

#ifdef WIN32
static LARGE_INTEGER g_PerformanceFrequency;
static LARGE_INTEGER g_MSPerformanceFrequency;
static LARGE_INTEGER g_ClockStart;
#endif

CGTime& Time()
{
	static CGTime tm;
	return tm;
}

#ifdef WIN32
//
static void InitTime()
{
	if( !g_PerformanceFrequency.QuadPart )
	{
		QueryPerformanceFrequency(&g_PerformanceFrequency);
		g_MSPerformanceFrequency.QuadPart = g_PerformanceFrequency.QuadPart / 1000;
		QueryPerformanceCounter(&g_ClockStart);
	}
}
#endif

//DWORD WINAPI Tick(void *param)
void Tick(void *param)
{
#if (!defined(_DEBUG)) && defined(WIN32)
	__try
#endif
	{
		while (true)
		{
			Time().IncreaceCurrentTime();
			Sleep(1000);
		}
	}
#if (!defined(_DEBUG)) && defined(WIN32)
	__except (HandleException(GetExceptionInformation(), "Tick"))
	{

	}
#endif
//	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
CGTime::CGTime()
{
	m_Tick          = 0;
	m_clienttime    = 0;
	m_iShutDownTime = INVALID_VALUE64;
}

CGTime::~CGTime()
{
	Release();
	m_iShutDownTime = INVALID_VALUE64;
}

bool CGTime::Init()
{
	m_nLastDay=0;
	m_nLastMin=0;
	m_nLastSec=0;
	m_nLastHour=0;

#ifdef _SURPERSERVER
	time((time_t*)&m_Tick);
	tm* p = localtime((time_t*)& m_Tick);
#endif
#if defined(_CLIENT_) || defined(_ROBOTPLUS_)
	//启动计时器
	InitTime();

#endif

#if defined(_SURPERSERVER) || defined(_CLIENT_) || defined(_ROBOTPLUS_)
//	DWORD wThreadID;
//	HANDLE hThread = CreateThread(NULL, 0,Tick, NULL,0,&wThreadID);
//	CloseHandle(hThread);
	ThreadLib::ThreadID hThread = ThreadLib::Create( Tick, NULL );
#endif

	return true;
}

void CGTime::Release()
{
}

BOOL CGTime::Logic()
{
#ifdef _DATASERVER_
	return Logic_DataServer();
#endif
#ifdef _COMMUNITYSERVER
	return Logic_CommunityServer();
#endif
#ifdef _CLIENT_
	return Logic_Client();
#endif
#ifdef _SURPERSERVER
	return Logic_SuperServer();
#endif
	return TRUE;
}

#ifdef _SURPERSERVER
BOOL CGTime::Logic_SuperServer()
{
	if( GetCurrentTime() == m_nLastSec )
		return FALSE;

	m_nLastSec = GetCurrentTime();

	SynchAllServer();

	return TRUE;
}
#endif

#ifdef _CLIENT_
BOOL CGTime::Logic_Client()
{
	VPROF("TimeLogic");

	GTime now;
	GetNowTime(now);

	//每分钟向注册的单位发通告
	if(now.gtm_min!=m_nLastMin)
	{
		m_nLastMin=now.gtm_min;
	}
	//一秒走一次
	//	if(Pass1Second())
	if(m_clienttime != time(NULL))
	{
		m_clienttime = time(NULL);

		if (FamilyMgr().GetFamilyZhadanrenFlag() == 1)
		{
			G_TriggerEvent("OpenBomDlg","i",0);
		}

		if(FamilyMgr().GetFamilyTiaozhansaiFlag()==1)                //魏小波添加，解决0000366问题
		{
			G_TriggerEvent("OpenFightDlg","i",0);
		}

		if ( PlayerMgr().GetHero() && PlayerMgr().GetHero()->GetStatusMachine() && PlayerMgr().GetHero()->GetStatusMachine()->IsCurrentStatus(SuperStatus_Death) )	//--死亡倒计时-- add by zhaoguoze
		{
			G_TriggerEvent("UpdateReliveCountDown");
		}

		//--客户端请求同步血值有弊端，如果要显示怪物血条就不如主动同步的效率高-- del by zhaoguoze 2011-08-29
		//CSNetGameObj* pTarget = NULL;
		//CPlayer* pHero = NULL;
		//if ( (pHero = PlayerMgr().GetHero()) && pHero->GetAttribMgr() && ( pTarget = pHero->GetAttribMgr()->GetTarget()) )
		//{
		//	if ( pTarget->IsPlayer() )
		//	{
		//		pHero->GetAttribMgr()->ReqAttribute_Int(pTarget->GetPID(),Role_Attrib_Hp);
		//		//pHero->GetAttribMgr()->ReqAttribute_Int(pTarget->GetPID(),Role_Attrib_Mp);
		//	}
		//	else if ( pTarget->IsNPC() )
		//	{
		//		if ( !RoleTemplateIsBusinessNPC(pTarget->GetTemplateID()) && !RoleTemplateIsQuestNPC(pTarget->GetTemplateID()) )	//--不是任务和买卖NPC，才每秒申请属性--
		//		{
		//			pHero->GetAttribMgr()->ReqAttribute_Int(pTarget->GetPID(),Role_Attrib_Hp);
		//		}
		//	}
		//}
	}

	return TRUE;
}
#endif

#ifdef _COMMUNITYSERVER
BOOL CGTime::Logic_CommunityServer()
{
	VPROF("TimeLogic");

	GTime now;
	GetNowTime(now);

	//每分钟向注册的单位发通告
	if(now.gtm_min!=m_nLastMin)
	{
		m_nLastMin=now.gtm_min;

		//通告
		for(int index =m_MinTimeList.Head();m_MinTimeList.IsValidIndex(index);)
		{
			Timer_Obj* pObj = m_MinTimeList[index];
			if(	pObj &&
				(!pObj->m_Moth || pObj->m_Moth == now.gtm_mon + 1 )&&
				(!pObj->m_Data || pObj->m_Data == now.gtm_mday )&&
				(!pObj->m_Hour || pObj->m_Hour ==now.gtm_hour ) &&
				(!pObj->m_Min  || pObj->m_Min == now.gtm_min)&&
				(pObj->m_nWeek==Week_Type_Everyday||pObj->m_nWeek==now.gtm_wday))
			{
				if (pObj->m_Rule==Time_Call_Rule_Min)
				{
					switch (pObj->m_Type)
					{
					case Time_Reg_Type_Person:
						{
							CSNetGameObj* pPerson=PlayerMgr().GetNetGameObjByPID(pObj->m_ID);
							if (pPerson)
							{
								Event* pEvent = MakeEvent(Event_Logic_Time,pPerson->GetPID(),INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid);
								pPerson->OnEvent(pEvent);
							}
							break;
						}
					case Time_Reg_Type_SignUp:
						{
							Event* pEvent = MakeEvent(Event_Logic_Time,INVALID_PID,INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,pObj->m_Event,pObj->m_Param);
							//SignUpMgr().OnEvent(pEvent);
							//释放
							//g_FreeEvent(pEvent);
							break;
						}
					case Time_Reg_Type_Campaign:
						{
							Event* pEvent = MakeEvent(Event_Logic_Time,INVALID_PID,INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,pObj->m_Event,pObj->m_Param);
							//SignUpMgr().OnEvent(pEvent);
							//释放
							//g_FreeEvent(pEvent);
							break;
						}
					case Time_Reg_Type_Family:
						{
							break;
						}
					case Time_Reg_Type_Gang:
						{
							break;
						}
					case Time_Reg_Type_State:
						{
							break;
						}
					//世界答题
					case Time_Reg_Type_Question:
						{
							QuestionMgr().OnTime(pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid,INVALID_VALUE);
							break;
						}
					case Time_Reg_Type_Question_TVMsgPre5:
						{
							Event* pEvent = MakeEvent(Event_Campaign_5MinPre,INVALID_PID,INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid);
							QuestionMgr().OnEvent(pEvent);
							break;
						}
					case Time_Reg_Type_Question_TVMsgPre3:
						{
							Event* pEvent = MakeEvent(Event_Campaign_3MinPre,INVALID_PID,INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid);
							QuestionMgr().OnEvent(pEvent);
							break;
						}
					case Time_Reg_Type_Question_TVMsgPre1:
						{
							Event* pEvent = MakeEvent(Event_Campaign_1MinPre,INVALID_PID,INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid);
							QuestionMgr().OnEvent(pEvent);
							break;
						}
					default:
						break;
					}
				}
			}
			index = m_MinTimeList.Next(index);
		}

		//每周一计算一次家族工资
		FamilyMgr().OnTime(now.gtm_wday,now.gtm_hour,now.gtm_min,now.gtm_sec);

		//排行榜信息刷新
		TopMgr().OnTime(now.gtm_wday,now.gtm_hour,now.gtm_min, now.gtm_sec);
		TopMgr().UpdataTop( now );


		//游戏数据定时刷新机制 Add By ChenXY
		//Year[年]   Mouth[月]   Date[日]    Week[星期]     Hour[小时]     Min[分钟]     Sec[秒]
		LuaParam param[7];
		param[0].SetDataNum( now.gtm_year );
		param[1].SetDataNum( now.gtm_mon  );
		param[2].SetDataNum( now.gtm_mday );
		param[3].SetDataNum( now.gtm_wday );
		param[4].SetDataNum( now.gtm_hour );
		param[5].SetDataNum( now.gtm_min  );
		param[6].SetDataNum( now.gtm_sec  );

		GetLuaEngine_Svr().RunLuaFunction("RefreshDataOnTime",NULL,NULL,param,7);	//执行脚本

		FamilyMgr().OnEvenyMinProcess();

	}

	//每小时处理
	if (now.gtm_hour != m_nLastHour)
	{
		m_nLastHour = now.gtm_hour;
		FamilyMgr().OnEveryHourUpdate();

		//每天处理 （24 点）
		if(now.gtm_hour==24 || now.gtm_hour==0)
		{
			//家族
			FamilyMgr().OnDayUpdate();

			StateMgr().Init_24();
			QuestionMgr().Init24();
		}
	}



	return TRUE;
}
#endif

#ifdef _COMMUNITYSERVER
void CGTime::RefreshAttributesAll()
{
	RefreshAttributesByDay();
	RefreshAttributesByWeek();
	RefreshAttributesByMonth();
}
void CGTime::RefreshAttributesByDay()
{
	//家族
	FamilyMgr().OnDayUpdate();
	StateMgr().Init_24();
	QuestionMgr().Init24();	
	GetLuaEngine_Svr().RunLuaFunction("Init24","Campaigns");
	TopMgr().BeginUpdataTop();
}
void CGTime::RefreshAttributesByWeek()
{
	FamilyMgr().EveryMondayInit();
}
void CGTime::RefreshAttributesByMonth()
{


}
#endif



#ifdef _DATASERVER_
BOOL CGTime::Logic_DataServer()
{
	/* 长时间运行时，此报时功能比较耗时，并且暂无系统使用，因此注释掉，需要报时功能的话，请重新实现  by songjun 2011.2.22 */
	VPROF("CGTime::Logic");

	GTime now;
	GetNowTime(now);

	//每分钟向注册的单位发通告
	if(now.gtm_min!=m_nLastMin)
	{
		m_nLastMin=now.gtm_min;

		//通告
		for(int index =m_MinTimeList.Head();m_MinTimeList.IsValidIndex(index);)
		{
			Timer_Obj* pObj = m_MinTimeList[index];
			if(	pObj &&
				(!pObj->m_Moth || pObj->m_Moth == now.gtm_mon + 1 )&&
				(!pObj->m_Data || pObj->m_Data == now.gtm_mday )&&
				(!pObj->m_Hour || pObj->m_Hour ==now.gtm_hour ) &&
				(!pObj->m_Min  || pObj->m_Min == now.gtm_min)&&
 				(pObj->m_nWeek==Week_Type_Everyday||pObj->m_nWeek==now.gtm_wday))
			{
				if (pObj->m_Rule==Time_Call_Rule_Min)
				{
					switch (pObj->m_Type)
					{
					case Time_Reg_Type_AIUnit:
						{
							AIUnit* pAIUnit = AIUnitMgr().GetAIUnit(pObj->m_ID);
							if(pAIUnit)
								pAIUnit->OnTime(pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid,INVALID_VALUE);
							break;
						}
					case Time_Reg_Type_Person:
						{
							CSNetGameObj* pPerson=PlayerMgr().GetNetGameObjByPID(pObj->m_ID);
							if (pPerson)
							{
								Event* pEvent = MakeEvent(Event_Logic_Time,pPerson->GetPID(),INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid);
								pPerson->OnEvent(pEvent);
							}
							break;
						}
					case Time_Reg_Type_Quest:
						{
							CQuest* pQuest=QuestMgr().GetQuestByQuestID((QuestID)(pObj->m_ID));
							if(pQuest)
							{
								//任务事件
								Event* pEvent = MakeEvent(Event_Logic_Time,pQuest->m_QID,INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid);
								pQuest->OnEvent(pEvent);
							}
							break;
						}
					case Time_Reg_Type_Question_TVMsgPre5:
						{
							Event* pEvent = MakeEvent(Event_Campaign_5MinPre,INVALID_PID,INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid);
							QuestionMgr().OnEvent(pEvent);
							break;
						}
					case Time_Reg_Type_Question_TVMsgPre3:
						{
							Event* pEvent = MakeEvent(Event_Campaign_3MinPre,INVALID_PID,INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid);
							QuestionMgr().OnEvent(pEvent);
							break;
						}
					case Time_Reg_Type_Question_TVMsgPre1:
						{
							Event* pEvent = MakeEvent(Event_Campaign_1MinPre,INVALID_PID,INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid);
							QuestionMgr().OnEvent(pEvent);
							break;
						}
					case Time_Reg_Type_NewTv:
						{
							Event* pEvent = MakeEvent(Event_Logic_Time,INVALID_PID,INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid);
							TVMgr().OnEvent(pEvent);
							//g_FreeEvent(pEvent);
							break;
						}
					case Time_Reg_Type_Clock_2:
						{
							CVitalityMgr::getSingle().AddVitalityOfTime(pObj->m_ID,Vitality_Attrib_Value3,now.gtm_min,now.gtm_sec);
							break;
						}
					case Time_Reg_Type_Clock_8:
						{
							CVitalityMgr::getSingle().AddVitalityOfTime(pObj->m_ID,Vitality_Attrib_Value4,now.gtm_min,now.gtm_sec);
							break;
						}
					case Time_Reg_Type_Clock_14:
						{
							CVitalityMgr::getSingle().AddVitalityOfTime(pObj->m_ID,Vitality_Attrib_Value5,now.gtm_min,now.gtm_sec);
							break;
						}
					case Time_Reg_Type_Clock_20:
						{
							CVitalityMgr::getSingle().AddVitalityOfTime(pObj->m_ID,Vitality_Attrib_Value6,now.gtm_min,now.gtm_sec);
							break;
						}
					default:
						break;
					}
				}
			}
			index = m_MinTimeList.Next(index);
		}

		//答题报时
		//QuestionMgr().OnTime(now.gtm_mon,now.gtm_mday,now.gtm_hour,now.gtm_min,Time_Call_Event_Question,-1);   //放到脚本层  ChenXY 注释   2011/6/22

		// 个人报时
		FOR_EACH_LIST(PlayerMgr().PlayerList(),index)
		{
			CPlayer* pPlayer = PlayerMgr().PlayerList().Element(index);
			if(pPlayer)
			{
				pPlayer->OnTime( now.gtm_mon, now.gtm_mday, now.gtm_hour, now.gtm_min );

				Event* pEvent = MakeEvent(Event_Logic_Time,pPlayer->GetPID(),pPlayer->GetAttribMgr()->GetAttribInt64(Role_Attrib_SceneID),now.gtm_mon,now.gtm_mday,now.gtm_hour,now.gtm_min,Time_Call_Event_Invalid);
				pPlayer->OnEvent(pEvent);
			}
		}

		//游戏数据定时刷新机制 Add By ChenXY       改为每分钟执行一次  2011/7/29
		//Year[年]   Mouth[月]   Date[日]    Week[星期]     Hour[小时]     Min[分钟]     Sec[秒]
		LuaParam param[7];
		param[0].SetDataNum( now.gtm_year );
		param[1].SetDataNum( now.gtm_mon  );
		param[2].SetDataNum( now.gtm_mday );
		param[3].SetDataNum( now.gtm_wday );
		param[4].SetDataNum( now.gtm_hour );
		param[5].SetDataNum( now.gtm_min  );
		param[6].SetDataNum( now.gtm_sec  );

		GetLuaEngine_Svr().RunLuaFunction("RefreshDataOnTime",NULL,NULL,param,7);	//执行脚本
	}

	//每秒向注册的单位发通告
     if (now.gtm_sec!=m_nLastSec)
     {
          m_nLastSec=now.gtm_sec;
		  //通告
		  for(int index =m_SecTimeList.Head();m_SecTimeList.IsValidIndex(index);)
		  {
			  Timer_Obj* pObj = m_SecTimeList[index];
			  if(	pObj &&
				  (!pObj->m_Moth || pObj->m_Moth == now.gtm_mon + 1 )&&
				  (!pObj->m_Data || pObj->m_Data == now.gtm_mday )&&
				  (!pObj->m_Hour || pObj->m_Hour ==now.gtm_hour ) &&
				  (!pObj->m_Min  || pObj->m_Min == now.gtm_min)&&
				  (pObj->m_nWeek==Week_Type_Everyday||pObj->m_nWeek==now.gtm_wday))
			  {
				  if (pObj->m_Rule==Time_Call_Rule_Sec)
				  {
						switch (pObj->m_Type)
						{
						case Time_Reg_Type_AIUnit:
							{
								AIUnit* pAIUnit = AIUnitMgr().GetAIUnit(pObj->m_ID);
								if(pAIUnit)
								{
									//脚本事件
									pAIUnit->OnTime(pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid,INVALID_VALUE);
								}
								break;
							}
						case Time_Reg_Type_Person:
							{
								CSNetGameObj* pPerson=PlayerMgr().GetNetGameObjByPID(pObj->m_ID);
								if (pPerson)
								{
									//角色事件
									Event* pEvent = MakeEvent(Event_Logic_Time,pPerson->GetPID(),INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid);
									pPerson->OnEvent(pEvent);
								}
								break;
							}
						case Time_Reg_Type_Quest:
							{
								CQuest* pQuest=QuestMgr().GetQuestByQuestID((QuestID)(pObj->m_ID));
								if(pQuest)
								{
									//任务事件
									Event* pEvent = MakeEvent(Event_Logic_Time,pQuest->m_QID,INVALID_SCENEID,pObj->m_Moth,pObj->m_Data,pObj->m_Hour,pObj->m_Min,Time_Call_Event_Invalid);
									pQuest->OnEvent(pEvent);
									//释放
									//g_FreeEvent(pEvent);
								}
								break;
							}
						}
				  }
			  }

			  index = m_SecTimeList.Next(index);
		  }

		  //国家报时
		  /*
		  for(int index = 0;index <STATE_COUNT_MAX;index++)
		  {
			  CState* pState = StateMgr().GetStateByID(index);
			  if(pState)
				  pState->OnTime(now.gtm_hour, now.gtm_min, now.gtm_sec);
		  }
		  */
		  //家族报时
		  for(int index=FamilyMgr().GetFamilyMap().FirstInorder();FamilyMgr().GetFamilyMap().IsValidIndex(index);index=FamilyMgr().GetFamilyMap().NextInorder(index))
		  {
			  CFamily* pFamily=FamilyMgr().GetFamilyMap().Element(index);
			  if(pFamily)
				  pFamily->OnTime(now.gtm_hour,now.gtm_min, now.gtm_sec);
		  }
		  //帮会报时
		  for (int index = GangMgr().GetGangMap().FirstInorder(); GangMgr().GetGangMap().IsValidIndex(index); index = GangMgr().GetGangMap().NextInorder(index))
		  {
			  CGang* pGang=GangMgr().GetGangMap().Element(index);
			  if(pGang)
				  pGang->OnTime(now.gtm_hour,now.gtm_min, now.gtm_sec);
		  }

		  // 关服提示
		  if( m_iShutDownTime != INVALID_VALUE64 )
		  {
			  char szString[64] = {0};
			  int iNum = INVALID_VALUE;
			  int64 i64Time = time(NULL);
			  if( i64Time -m_iShutDownTime == 5*60 )
			  {
				  iNum = 10;
			  }
			  else if( i64Time -m_iShutDownTime == 10*60 )
			  {
				  iNum = 5;
			  }
			  else if( i64Time -m_iShutDownTime == 12*60 )
			  {
				  iNum = 3;
			  }
			  if(iNum != INVALID_VALUE)
			  {
				  sprintf(szString,"服务器将于%d分钟后停机维护，请大家做好下线准备",iNum);
				  //为了支持现在的开服机制，电视消息类型改为个人   ChenXY 2011/8/2
				  CUtlLinkedList<CPlayer*,int>& PlayerList = PlayerMgr().PlayerList();
				  for(int index=PlayerList.Head();PlayerList.IsValidIndex(index);index=PlayerList.Next(index))
				  {
					  CPlayer* pPlayer=PlayerList[index];
					  if(pPlayer)
							ErrorUnit().SendRollNewToCommunity(GTV_Invalid,RollNewCommunity_Type_Person, pPlayer->GetPID(),RollNew_Type_Campaign,"%s", szString);
				  }
			  }

		  }

     }

	return TRUE;
}
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
//

BOOL CGTime::OnMsg(PACKET_COMMAND* pPacket)
{
	if(!pPacket)
		return FALSE;

	switch (pPacket->Type())
	{
	case TIME_SYNCHRONIZATION:
		Packet_TimeSync(pPacket);
		break;
	case TIME_DEBUG_SET_TIME:
		Packet_DebugSetTime(pPacket);
		break;
	case TIME_REFRESHATTRIBEVERYDAY:
		Packet_RefreshAttribEveryday(pPacket);
		break;
	case DEBUG_REFRESHATTRIBEVERYDAY:
		Packet_REQRefreshAttributes(pPacket);	
		break;
	default:
		break;
	}

	return TRUE;
}

BOOL CGTime::Packet_DebugSetTime(PACKET_COMMAND *pPacket)
{
#ifdef __DEV__
	if(!pPacket)
		return false;

	TMV timer = 0;
	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&timer);

#ifdef _SURPERSERVER
	for(int index = SuperServerMgr().ServerMap()->FirstInorder(); SuperServerMgr().ServerMap()->IsValidIndex(index); index = SuperServerMgr().ServerMap()->NextInorder(index))
	{
		CSNetGameObj* pServer = SuperServerMgr().ServerMap()->Element(index);
		if(pServer && pServer->IsLoginServer()){
			pServer->SendMsg( pPacket );
		}
	}
#endif
#ifdef _LOGINSERVER
	//广播时间
	FOR_EACH_MAP(UserMgr().GetUserNameMap(), index)
	{
		CUser* pUser = UserMgr().GetUserNameMap().Element(index);
		if(pUser)
		{
			pUser->SendMsg( pPacket );
		}
	}
#endif

	SetCurrentTime(timer);

#ifdef _SURPERSERVER
	SynchAllServer();
#endif

#endif	//__DEV__
	return true;
}

BOOL CGTime::Packet_RefreshAttribEveryday(PACKET_COMMAND* pPacket)
{
	int nRefreshType = INVALID_VALUE;
	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&nRefreshType);	
#ifdef _DATASERVER_
	switch(nRefreshType)
	{
	case Refresh_Type_All:		//刷新所有
		GetLuaEngine_Svr().RunLuaFunction("RefreshAttributesByAll");	//执行脚本
		break;
	case Refresh_Type_Day:		//每天刷新
		GetLuaEngine_Svr().RunLuaFunction("RefreshAttributesByDay");	//执行脚本
		break;
	case Refresh_Type_Week:		//每周刷新
		GetLuaEngine_Svr().RunLuaFunction("RefreshAttributesByWeek");	//执行脚本
		break;
	case Refresh_Type_Month:	//每月刷新
		GetLuaEngine_Svr().RunLuaFunction("RefreshAttributesByMonth");	//执行脚本
		break;
	default:
		break;
	}
#endif

#ifdef _COMMUNITYSERVER
	switch(nRefreshType)
	{
	case Refresh_Type_All:		//刷新所有
		RefreshAttributesAll();
		break;
	case Refresh_Type_Day:		//每天刷新
		RefreshAttributesByDay();
		break;
	case Refresh_Type_Week:		//每周刷新
		RefreshAttributesByWeek();
		break;
	case Refresh_Type_Month:	//每月刷新
		RefreshAttributesByMonth();
		break;
	default:
		break;
	}
#endif
	return TRUE;
}

#ifdef _SURPERSERVER
BOOL CGTime::RefreshAllServerAttributesEveryDay(int nRefreshType)
{
	PACKET_COMMAND	pPacket;
	pPacket.SetParam(TIME_REFRESHATTRIBEVERYDAY,GetCmdFormat(TIME_REFRESHATTRIBEVERYDAY),nRefreshType);
	for(int index = SuperServerMgr().ServerMap()->FirstInorder(); SuperServerMgr().ServerMap()->IsValidIndex(index); index = SuperServerMgr().ServerMap()->NextInorder(index))
	{
		CSNetGameObj* pServer = SuperServerMgr().ServerMap()->Element(index);
		if(pServer && (pServer->IsDataServer() || pServer->IsCommunityServer()) )
		{
			pServer->SendMsg(&pPacket);
		}
	}
	return TRUE;
}
#endif

BOOL CGTime::Packet_REQRefreshAttributes(PACKET_COMMAND* pPacket)
{
#ifdef __DEV__
#ifdef _SURPERSERVER
	if(!pPacket)
		return FALSE;

	int nRefreshType = -1;
	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&nRefreshType);
	if(nRefreshType >= 0)
	{
		RefreshAllServerAttributesEveryDay(nRefreshType);
	}
#endif
#endif
	return TRUE;
}

BOOL CGTime::Packet_TimeSync(PACKET_COMMAND* pPacket)
{
	if(!pPacket)
		return FALSE;

	TMV tm;
	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&tm);

	SetCurrentTime(tm);

	return TRUE;
}

void CGTime::Synch(CNetObj* pNetObj)
{
	if(!pNetObj)
		return;

	PACKET_COMMAND pack;
	pack.SetParam(TIME_SYNCHRONIZATION,GetCmdFormat(TIME_SYNCHRONIZATION),GetCurrentTime());
	pNetObj->SendMsg(&pack);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
/*
 * note:
 *   on UNIX ,this function returns milliseconds from 1970.1.1
 *
 */
TMV CGTime::GetCurrentTimeMS( )
{
#ifdef WIN32
	InitTime();

	LARGE_INTEGER CurrentTime;

	QueryPerformanceCounter( &CurrentTime );

	return (TMV) ( ( CurrentTime.QuadPart - g_ClockStart.QuadPart ) / g_MSPerformanceFrequency.QuadPart);
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((uint64_t)tv.tv_sec)*(1000ULL) + (((uint64_t)tv.tv_usec)/(1000ULL));
#endif
}

TMV CGTime::GetCurrentTimeMSEx()
{
#ifdef WIN32
	timeb t;
	ftime(&t);
	return 1000 * t.time + t.millitm;
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((uint64_t)tv.tv_sec)*(1000ULL) + (((uint64_t)tv.tv_usec)/(1000ULL));
#endif
}

TMV CGTime::CoverGTMToTMV(GTime &gtm)
{
	tm t;
	CoverGTMTotm(gtm, t);
	return (TMV)mktime(&t);
}

//CGTime --> tm
//mktime将忽略tm_wday,tm_yday这两参数
void  CGTime::CoverGTMTotm(GTime &gtm,tm &t)
{
	//time((time_t*)&m_Tick);
	tm* p = localtime((time_t*)&m_Tick);
	if( !p )
		return;

	t.tm_hour	=	gtm.gtm_hour;
	t.tm_min	=   gtm.gtm_min;
	t.tm_sec	=	gtm.gtm_sec;

	//if(gtm.gtm_wday==0)
	//	t.tm_wday	=   p->tm_wday;
	//else
	//	t.tm_wday	=   gtm.gtm_wday;
	if(0==gtm.gtm_mday||0==gtm.gtm_mon||0==gtm.gtm_year)
	{
		t.tm_mon=p->tm_mon;
		t.tm_mday=p->tm_mday;
		t.tm_year=p->tm_year;
	}
	else
	{
		t.tm_mon=gtm.gtm_mon - 1;
		t.tm_mday=gtm.gtm_mday;
		t.tm_year=gtm.gtm_year - 1900;
	}
	t.tm_isdst=p->tm_isdst;
	//t.tm_yday=p->tm_yday;
}

void CGTime::CoverTMVToGTM(TMV tmv,GTime &gtm)
{
	tm* t = localtime((time_t*)&tmv);
	if(!t)
		return;
	gtm.gtm_sec		= t->tm_sec;
	gtm.gtm_min		= t->tm_min;
	gtm.gtm_hour	= t->tm_hour;
	gtm.gtm_mday	= t->tm_mday;
	gtm.gtm_mon		= t->tm_mon + 1;
	gtm.gtm_year	= t->tm_year + 1900;
	gtm.gtm_wday	= t->tm_wday;
}

// return :
void CGTime::GetNowTime(GTime &t)
{
	//time((time_t*)&m_Tick);
	tm* p = localtime((time_t*)&m_Tick);
	if( !p )
		return;

	t.gtm_sec	= p->tm_sec;
	t.gtm_min	= p->tm_min;
	t.gtm_hour	= p->tm_hour;
	t.gtm_mday	= p->tm_mday;
	t.gtm_mon	= p->tm_mon + 1;
	t.gtm_year	= p->tm_year + 1900;
	t.gtm_wday	= p->tm_wday /*+ 1*/; //ChenXY 注释

}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
BOOL   CGTime::RegisterTime(uint64 ID,int ntype,TIME_FORMAT nTime,int nRule/* =Time_Call_Rule_Min */,int nWeek/* =Week_Type_Everyday */,int nTimeEvent/* =Time_Call_Event_Invalid */,int64 nParam/* =INVALID_PID */)
{
	Timer_Obj* pObj = g_TimerPool().Alloc();
	if(!pObj)
		return FALSE;

	pObj->m_Rule=nRule;
	pObj->m_ID = ID;
	pObj->m_Type = ntype;
	pObj->m_Event=nTimeEvent;
	pObj->m_Param=nParam;
	pObj->m_Moth = nTime/1000000;
	pObj->m_Data = (nTime/10000)%100;
	pObj->m_Hour = (nTime/100)%100;
	pObj->m_Min = nTime%100;
	pObj->m_nWeek=nWeek;

	if(Time_Call_Rule_Min == nRule)
		m_MinTimeList.AddToTail(pObj);
	else if(Time_Call_Rule_Sec == nRule)
		m_SecTimeList.AddToTail(pObj);

	return TRUE;
}

BOOL  CGTime::UnRegisterTime(uint64 ID,int ntype,int nRule)
{
	int nTempIndex;
	if(Time_Call_Rule_Min == nRule)
	{
		for( int index = m_MinTimeList.Head();m_MinTimeList.IsValidIndex(nTempIndex = index);)
		{
			index = m_MinTimeList.Next(index);
			Timer_Obj* pObj = m_MinTimeList[nTempIndex];
			if(pObj)
			{
				if (pObj->m_Type==ntype&&pObj->m_ID==ID&&pObj->m_Rule==nRule)
				{
					m_MinTimeList.Remove(nTempIndex);
					//g_TimerPool().Free(pObj);
					CMemPoolFreeMgr::GetFreeMgr().FreeObj(pObj);
				}
			}
		}
	}
	else if(Time_Call_Rule_Sec == nRule)
	{
		for( int index = m_SecTimeList.Head();m_SecTimeList.IsValidIndex(nTempIndex = index);)
		{
			index = m_SecTimeList.Next(index);
			Timer_Obj* pObj = m_SecTimeList[nTempIndex];
			if(pObj)
			{
				if (pObj->m_Type==ntype&&pObj->m_ID==ID&&pObj->m_Rule==nRule)
				{
					m_SecTimeList.Remove(nTempIndex);
					//g_TimerPool().Free(pObj);
					CMemPoolFreeMgr::GetFreeMgr().FreeObj(pObj);
				}
			}
		}
	}

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
#ifdef _DATASERVER_
/*
BOOL CGTime::OnDelayShutDownServer(int64 i64BeginTime)
{
	m_iShutDownTime = i64BeginTime;

	//电视 消息
	char szString[64] = "服务器将于15分钟后停机维护，请大家做好下线准备";

	//ErrorUnit().SendRollNewToCommunity(RollNewCommunity_Type_State,	DataServerMgr().m_MyStateID ,RollNew_Type_Campaign,"%s", szString);
	//为了支持现在的开服机制，电视消息类型改为个人   ChenXY 2011/8/2
	CUtlLinkedList<CPlayer*,int>& PlayerList = PlayerMgr().PlayerList();
	for(int index=PlayerList.Head();PlayerList.IsValidIndex(index);index=PlayerList.Next(index))
	{
		CPlayer* pPlayer=PlayerList[index];
		if(pPlayer)
			ErrorUnit().SendRollNewToCommunity(RollNewCommunity_Type_Person, pPlayer->GetPID(),RollNew_Type_Campaign,"%s", szString);
	}
	//闪框
	PACKET_COMMAND pack;
	pack.SetParam(	PACKET_TYPE_CLIENT_ADD_FLASHBOXBUTTON,GetCmdFormat(PACKET_TYPE_CLIENT_ADD_FLASHBOXBUTTON), 1, FlashBox_ButtonType_SeverDown, (int64)900, -1, "");
	PlayerMgr().SendAllMsg(&pack);

	return TRUE;
}
BOOL CGTime::OnPlayerLoginFlashBoxFunc(PersonID PID)
{
	if( PID == INVALID_VALUE64 )
		return FALSE;
	if( m_iShutDownTime !=INVALID_VALUE64 )
	{
		int64 i64Time = time(NULL);
		int64 iLastTime = 900 - (i64Time - m_iShutDownTime);
		CPlayer * pPlayer = PlayerMgr().GetPlayerByPID(PID);
		if(pPlayer)
		{
			PACKET_COMMAND pack;
			pack.SetParam(	PACKET_TYPE_CLIENT_ADD_FLASHBOXBUTTON,GetCmdFormat(PACKET_TYPE_CLIENT_ADD_FLASHBOXBUTTON), 1, FlashBox_ButtonType_SeverDown, iLastTime, -1, "");
			pPlayer->SendMsg(&pack);
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}
*/
#endif

#ifdef _COMMUNITYSERVER
char* CGTime::FormatChinaTime(GTime gTime, int TimeType)
{
	// by david 这里没有用到 m_Tick 所以不用这把所，如果单纯的
	// 为了解决这个函数的调用的话 可以重新创建一把锁 2011-11-02
	//m_Lock.LOCK();
	ZeroMemory(FormatTime, sizeof(FormatTime));
	if (TimeType & China_Y)
	{
		char temp[128] = {0};
		sprintf(temp, "%d年", gTime.gtm_year);
		strcat(FormatTime, temp);
	}
	if (TimeType & China_M)
	{
		char temp[128] = {0};
		sprintf(temp, "%d月", gTime.gtm_mon);
		strcat(FormatTime, temp);
	}
	if (TimeType & China_D)
	{
		char temp[128] = {0};
		sprintf(temp, "%d日", gTime.gtm_mday);
		strcat(FormatTime, temp);
	}
	if (TimeType & China_H)
	{
		char temp[128] = {0};
		sprintf(temp, "%d时", gTime.gtm_hour);
		strcat(FormatTime, temp);
	}
	if (TimeType & China_m)
	{
		char temp[128] = {0};
		sprintf(temp, "%d分", gTime.gtm_min);
		strcat(FormatTime, temp);
	}
	if (TimeType & China_S)
	{
		char temp[128] = {0};
		sprintf(temp, "%d秒", gTime.gtm_sec);
		strcat(FormatTime, temp);
	}
	//m_Lock.UNLOCK();
	return FormatTime;
}
#endif

#ifdef _SURPERSERVER
void CGTime::SynchAllServer()
{
	for(int index = SuperServerMgr().ServerMap()->FirstInorder(); SuperServerMgr().ServerMap()->IsValidIndex(index); index = SuperServerMgr().ServerMap()->NextInorder(index))
	{
		CSNetGameObj* pServer = SuperServerMgr().ServerMap()->Element(index);
		if(pServer){
			Synch(pServer);
		}
	}
}

#endif

#ifdef _CLIENT_
void CGTime::Request_SetTime(TMV tm)
{
	PACKET_COMMAND pack;
	pack.SetParam(TIME_DEBUG_SET_TIME,GetCmdFormat(TIME_DEBUG_SET_TIME),tm);
	PlayerMgr().GetHero()->SendGameMsg(&pack);
}
#endif
