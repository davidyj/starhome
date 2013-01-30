#include "StdAfx.h"
#include "MemoryPoolDef.h"

#include "GTime.h"

#ifdef _DNSSERVER
#include "User.h"
#endif

#ifdef _LOGINSERVER
#include "PlayerLoginQueue.h"
#include "UserCheckPassMgr.h"
#include "User.h"
#include "SceneObj.h"
#include "PlayerObj.h"
#include "LoginServerMgr.h"
#endif

#ifdef _DATASERVER_
#include "PropObj.h"
#include "PlayerObj.h"
#include "NPCObj.h"
#include "PersonBagMgr.h"
#include "BuffObj.h"
#include "PrivateMgr.h"
#include "PlayerQuestObj.h"
#include "Event.h"
#include "TeamMgr.h"
#include "FamilyMgr.h"
#include "QuestionObjMgr.h"
#include "PersonPetMgr.h"
////#include "CountDownMgr.h"
#include "PacketDefine.h"
#include "SceneObj.h"
#include "ZoneMessageBuffer.h"
#include "VitalityMgr.h"
#include "StateMgr.h"
#include "GlobalBossMgr.h"
#include "DataServerMgr.h"
#include "AuctionMgr.h"
#include "UseCountObj.h"
#include "FellowObj.h"
#include "PaySystem.h"
#include "EventRegistry.h"
#include "RobotAIUnit.h"
#include "StallMgr.h"
#endif

#ifdef _DBSERVER
#include "Event.h"
#include "UserMgr.h"
#include "PropObj.h"
#include "FamilyMgr.h"
#include "LoginUserMgr.h"
#include "PlayerObj.h"
#include "PrivateMgr.h"
#include "OfflineCmdMgr.h"
#include "BuffObj.h"
#include "CreatePlayerQueue.h"
#include "PlayerQuestObj.h"
#include "PersonPetMgr.h"
#include "SignUpMgr.h"
#include "MailMgr.h"
#include "GangMgr.h"
#include "GroupMgr.h"
#include "AuctionMgr.h"
#include "QuestionObjMgr.h"
#include "MySqlDefine.h"
#include "PacketDefine.h"
#include "VitalityMgr.h"
#include "StateMgr.h"
#include "SignUpMgr.h"
#include "TopMgr.h"
#include "ActiveBarMgr.h"
#include "SqlExcPool.h"
#include "UseCountObj.h"
#endif

#ifdef _COMMUNITYSERVER
#include "Event.h"
#include "PlayerObj.h"
#include "TeamMgr.h"
#include "FamilyMgr.h"
#include "GangMgr.h"
#include "GroupMgr.h"
#include "PrivateMgr.h"
#include "OfflineCmdMgr.h"
#include "SummonMgr.h"
#include "TopMgr.h"
////#include "CountDownMgr.h"
#include "StateMgr.h"
#include "GlobalBossMgr.h"
#include "QuestionObjMgr.h"
#include "VitalityMgr.h"
#include "SystemMsgMgr.h"
#endif

#ifdef _CLIENT_
#include "TopMgr.h"
#include "Event.h"
#include "CommodityTemplateMgr.h"
#endif

#ifdef _GMSERVER_
#include "MySqlDefine.h"
#include "SqlExcPool.h"
#include "SqlRetPool.h"
#include "PlayerInfo.h"
#endif

#ifdef _SALESERVER_
#include "MailMgr.h"
#include "PropObj.h"
#include "MySqlDefine.h"
#include "SqlRetPool.h"
#include "SqlExcPool.h"
#endif

#ifdef _NAMESERVER_
#include "MySqlDefine.h"
#include "SqlExcPool.h"
#include "SqlRetPool.h"
#endif

/////////////////////////////////////////////////////////////////////////////////////////
//

CObjectMemoryPool<Timer_Obj>&		g_TimerPool()		{static CObjectMemoryPool<Timer_Obj> pool;	return pool;}

#ifdef _DNSSERVER
CObjectMemoryPool<CUser>&			g_UserPool()		{static CObjectMemoryPool<CUser> pool;		return pool;}
#endif

#ifdef _LOGINSERVER
CObjectMemoryPool<PlayerLoginInfo>&	g_PlayerLoginPool() {static CObjectMemoryPool<PlayerLoginInfo> pool;return pool;}
CObjectMemoryPool<CPlayer>&			g_PlayerPool()		{static CObjectMemoryPool<CPlayer> pool;	return pool;}
CObjectMemoryPool<CScene>&			g_ScenePool()		{static CObjectMemoryPool<CScene> pool;		return pool;}
CObjectMemoryPool<CUser>&			g_UserPool()		{static CObjectMemoryPool<CUser> pool;		return pool;}
CObjectMemoryPool<stPayInfo>&			g_PayPool()		{static CObjectMemoryPool<stPayInfo> pool;		return pool;}

//CObjectMemoryPool<CUserSession>&	g_UserSessionPool()	{static CObjectMemoryPool<CUserSession> pool;	return pool;}
#endif


#ifdef _DATASERVER_
CObjectMemoryPool<Event>&			g_EventPool()		{static CObjectMemoryPool<Event> pool;		return pool;}
CObjectMemoryPool<CProp>&			g_PropPool()		{static CObjectMemoryPool<CProp> pool;		return pool;}
CObjectMemoryPool<CPlayer>&			g_PlayerPool()		{static CObjectMemoryPool<CPlayer> pool;	return pool;}
CObjectMemoryPool<CSGameNPC>&		g_NpcPool()			{static CObjectMemoryPool<CSGameNPC> pool;	return pool;}
CObjectMemoryPool<CFellowNPC>&		g_FellowPool()		{static CObjectMemoryPool<CFellowNPC> pool;	return pool;}
CObjectMemoryPool<CBag>&			g_BagPool()			{static CObjectMemoryPool<CBag> pool;		return pool;}
CObjectMemoryPool<CBuff>&			g_BuffPool()		{static CObjectMemoryPool<CBuff> pool;		return pool;}
CObjectMemoryPool<CPrivate>&		g_PrivatePool()		{static CObjectMemoryPool<CPrivate> pool;	return pool;}
CObjectMemoryPool<CPrivateMember>&	g_PrivateMemberPool()		{static CObjectMemoryPool<CPrivateMember> pool;	return pool;}
CObjectMemoryPool<CTeamSession>&	g_TeamSessionPool()	{static CObjectMemoryPool<CTeamSession> pool;return pool;}
CObjectMemoryPool<Transac>&			g_TransacPool()		{static CObjectMemoryPool<Transac> pool;	return pool;}
CObjectMemoryPool<CTeam>&			g_TeamPool()		{static CObjectMemoryPool<CTeam> pool;		return pool;}
CObjectMemoryPool<CFamily>&			g_FamilyPool()		{static CObjectMemoryPool<CFamily> pool;	return pool;}
CObjectMemoryPool<FeedBoss>&		g_FeedBossPool()	{static CObjectMemoryPool<FeedBoss> pool;	return pool;} //未调用过Free
CObjectMemoryPool<CPetItem>&		g_PetItemPool()		{static CObjectMemoryPool<CPetItem> pool;	return pool;}
CObjectMemoryPool<CScene>&			g_ScenePool()		{static CObjectMemoryPool<CScene> pool;		return pool;}
CObjectMemoryPool<CPlayerQuest>&	g_PlayerQuestPool()	{static CObjectMemoryPool<CPlayerQuest> pool;	return pool;}
//CObjectMemoryPool<CCountDownTime>&	g_CountDownTimePool(){static CObjectMemoryPool<CCountDownTime> pool;return pool;}
//CObjectMemoryPool<PACKET_COMMAND>&	g_PacketPool()		{static CObjectMemoryPool<PACKET_COMMAND> pool;	return pool;}
CObjectMemoryPool<PACKET_COMMAND>&	g_SendPacketPool()	{static CObjectMemoryPool<PACKET_COMMAND> pool;	return pool;}
CObjectMemoryPool<CZoneMessageBuffer>& g_ZoneMessagePool() {static CObjectMemoryPool<CZoneMessageBuffer> pool;return pool;}
CObjectMemoryPool<CVitality>&		g_VitalityPool()    {static CObjectMemoryPool<CVitality> pool;      return pool;}
CObjectMemoryPool<CPrisoner>&		g_PrisonerPool()	{static CObjectMemoryPool<CPrisoner> pool; return pool;}
CObjectMemoryPool<Send2Player>&		g_Send2PlayerPool()	{static CObjectMemoryPool<Send2Player> pool; return pool;}
CObjectMemoryPool<CGlobalBoss>&		g_GlobalBossPool()	{static CObjectMemoryPool<CGlobalBoss> pool;return pool;}	//BOSS内存申请	add by zhangjianli 2011-10-21
CObjectMemoryPool<CAuction>&		g_AuctionPool()		{static CObjectMemoryPool<CAuction> pool;		return pool;} //拍卖内存申请 add by zlm 2011.11.28
CObjectMemoryPool<CShortCutObj>&	g_ShuortCutPool()	{static CObjectMemoryPool<CShortCutObj> pool; return pool;}; // 快捷栏申请 add by 2011.11.28
CObjectMemoryPool<CGang>&			g_GangPool()		{static CObjectMemoryPool<CGang> pool;  return pool;}
CObjectMemoryPool<CFamilyMember>&   g_FamilyMemberPool() {static CObjectMemoryPool<CFamilyMember> pool;  return pool;}
CObjectMemoryPool<CUseCountObj>&		g_UseCountPool()	{static CObjectMemoryPool<CUseCountObj> pool;  return pool;}	// 使用计数内存池 add by zlm 2012.2.6
CObjectMemoryPool<CTeamMember> &	   g_TeamMemberPool() {static CObjectMemoryPool<CTeamMember> pool;  return pool;}
CObjectMemoryPool<EventRegistry> &	   g_EventRegistryPool() {static CObjectMemoryPool<EventRegistry> pool;  return pool;}
CObjectMemoryPool<CRobotAIUnit> &	   g_RobotAIUnitPool() {static CObjectMemoryPool<CRobotAIUnit> pool;  return pool;}
CObjectMemoryPool<CStallBuyPropInfo>&  g_StallBuyPropInfoPool() {static CObjectMemoryPool<CStallBuyPropInfo> pool;  return pool;}

#endif

#ifdef _DBSERVER
CObjectMemoryPool<Event>&			g_EventPool()		{static CObjectMemoryPool<Event> pool;		return pool;}
CObjectMemoryPool<CUser>&			g_UserPool()		{static CObjectMemoryPool<CUser> pool;		return pool;}
CObjectMemoryPool<CProp>&			g_PropPool()		{static CObjectMemoryPool<CProp> pool;		return pool;}
CObjectMemoryPool<CFamily>&			g_FamilyPool()		{static CObjectMemoryPool<CFamily> pool;	return pool;}
CObjectMemoryPool<LogUsr>&			g_LogUsrPool()		{static CObjectMemoryPool<LogUsr> pool;		return pool;}
CObjectMemoryPool<CPlayer>&			g_PlayerPool()		{static CObjectMemoryPool<CPlayer> pool;	return pool;}

CObjectMemoryPool<CPrivate>&		g_PrivatePool()		{static CObjectMemoryPool<CPrivate> pool;	return pool;}
CObjectMemoryPool<CPrivateMember>&	g_PrivateMemberPool() {static CObjectMemoryPool<CPrivateMember> pool; return pool;}

CObjectMemoryPool<COfflineCmd>&		g_OfflineCmdPool()	{static CObjectMemoryPool<COfflineCmd> pool;return pool;}
CObjectMemoryPool<CBuff>&			g_BuffPool()		{static CObjectMemoryPool<CBuff> pool;		return pool;}
//CObjectMemoryPool<FeedBoss>&		g_FeedBossPool()	{static CObjectMemoryPool<FeedBoss> pool;	return pool;}
//CObjectMemoryPool<CPetItem>&		g_PetItemPool()		{static CObjectMemoryPool<CPetItem> pool;	return pool;}
//CObjectMemoryPool<CSignUpObj>&		g_SignUpPool()		{static CObjectMemoryPool<CSignUpObj> pool;	return pool;}
CObjectMemoryPool<CMail>&			g_MailPool()		{static CObjectMemoryPool<CMail> pool;		return pool;}
//CObjectMemoryPool<CGroup>&			g_GroupPool()		{static CObjectMemoryPool<CGroup> pool;		return pool;}
CObjectMemoryPool<CSqlObj>&			g_UpdateSqlPool()	{static CObjectMemoryPool<CSqlObj> pool;	return pool;}
CObjectMemoryPool<CSqlObj>&			g_SelectSqlPool()	{static CObjectMemoryPool<CSqlObj> pool;	return pool;}
CObjectMemoryPool<sql_var>&			g_SqlVarPool()		{static CObjectMemoryPool<sql_var> pool;	return pool;}
CObjectMemoryPool<CSqlRetObj>&		g_SqlRetPool()		{static CObjectMemoryPool<CSqlRetObj> pool;	return pool;}
CObjectMemoryPool<CAuction>&		g_AuctionPool()		{static CObjectMemoryPool<CAuction> pool;		return pool;}
CObjectMemoryPool<CPlayerQuest>&	g_PlayerQuestPool()	{static CObjectMemoryPool<CPlayerQuest> pool;	return pool;}
//CObjectMemoryPool<PACKET_COMMAND>&	g_PacketPool()		{static CObjectMemoryPool<PACKET_COMMAND> pool;	return pool;}
//CObjectMemoryPool<PACKET_COMMAND>&	g_SendPacketPool()	{static CObjectMemoryPool<PACKET_COMMAND> pool;	return pool;}
CObjectMemoryPool<CCreatePlayerInfo>&	g_CrtPlayerInfoPool()	{static CObjectMemoryPool<CCreatePlayerInfo> pool;	return pool;}
CObjectMemoryPool<CVitality>&		g_VitalityPool()    {static CObjectMemoryPool<CVitality> pool;      return pool;}
CObjectMemoryPool<CPrisoner>&		g_PrisonerPool()	{static CObjectMemoryPool<CPrisoner> pool; return pool;}
CObjectMemoryPool<CampaignSignUp>&	g_SignUpPool()		{static CObjectMemoryPool<CampaignSignUp> pool; return pool;}
CObjectMemoryPool<CTop_MemObj>&	    g_TopMemObjPool()	{static CObjectMemoryPool<CTop_MemObj> pool; return pool;}
CObjectMemoryPool<CTopObj>&	        g_TopObjPool()	    {static CObjectMemoryPool<CTopObj> pool; return pool;}
CObjectMemoryPool<CShortCutObj>&	g_ShuortCutPool()	{static CObjectMemoryPool<CShortCutObj> pool; return pool;};				//快捷栏内存池 add by david 2011-11-21
CObjectMemoryPool<CGang>&			g_GangPool()		{static CObjectMemoryPool<CGang> pool;  return pool;}
CObjectMemoryPool<CFamilyMember>&   g_FamilyMemberPool() {static CObjectMemoryPool<CFamilyMember> pool;  return pool;}
CObjectMemoryPool<CUseCountObj>&		g_UseCountPool()	{static CObjectMemoryPool<CUseCountObj> pool;  return pool;}	// 使用计数内存池 add by zlm 2012.2.6
#endif

#ifdef _COMMUNITYSERVER
CObjectMemoryPool<Event>&			g_EventPool()		{static CObjectMemoryPool<Event> pool;		return pool;}
CObjectMemoryPool<CPlayer>&			g_PlayerPool()		{static CObjectMemoryPool<CPlayer> pool;	return pool;}
CObjectMemoryPool<CTeam>&			g_TeamPool()		{static CObjectMemoryPool<CTeam> pool;		return pool;}
CObjectMemoryPool<CFamily>&			g_FamilyPool()		{static CObjectMemoryPool<CFamily> pool;	return pool;}
CObjectMemoryPool<CPrivateMember>&	g_PrivateMemberPool() {static CObjectMemoryPool<CPrivateMember> pool; return pool;}
CObjectMemoryPool<CGroup>&			g_GroupPool()		{static CObjectMemoryPool<CGroup> pool;		return pool;}
CObjectMemoryPool<CPrivate>&		g_PrivatePool()		{static CObjectMemoryPool<CPrivate> pool;	return pool;}
CObjectMemoryPool<CTeamSession>&	g_TeamSessionPool()	{static CObjectMemoryPool<CTeamSession> pool;return pool;}
//CObjectMemoryPool<CSignUpObj>&		g_SignUpPool()		{static CObjectMemoryPool<CSignUpObj> pool;	return pool;}
//CObjectMemoryPool<CCountDownTime>&	g_CountDownTimePool(){static CObjectMemoryPool<CCountDownTime> pool;return pool;}
CObjectMemoryPool<SummonUnit>&	g_SummonPool()		{static CObjectMemoryPool<SummonUnit> pool;	return pool;}
CObjectMemoryPool<CPrisoner>&		g_PrisonerPool()	{static CObjectMemoryPool<CPrisoner> pool; return pool;}
//CObjectMemoryPool<PACKET_COMMAND>&	g_PacketPool()		{static CObjectMemoryPool<PACKET_COMMAND> pool;	return pool;}
//CObjectMemoryPool<PACKET_COMMAND>&	g_SendPacketPool()	{static CObjectMemoryPool<PACKET_COMMAND> pool;	return pool;}
CObjectMemoryPool<CGlobalBoss>&		g_GlobalBossPool()	{static CObjectMemoryPool<CGlobalBoss> pool;return pool;}	//BOSS内存申请	add by zhangjianli 2011-10-21
CObjectMemoryPool<CVitality>&		g_VitalityPool()    {static CObjectMemoryPool<CVitality> pool;      return pool;}
CObjectMemoryPool<CTop_MemObj>&	    g_TopMemObjPool()	{static CObjectMemoryPool<CTop_MemObj> pool; return pool;}
CObjectMemoryPool<CTopObj>&	        g_TopObjPool()	    {static CObjectMemoryPool<CTopObj> pool; return pool;}
CObjectMemoryPool<CQuestionTop>&	g_QuestionTopPool()	{static CObjectMemoryPool<CQuestionTop> pool;	return pool;}
CObjectMemoryPool<CGang>&			g_GangPool()		{static CObjectMemoryPool<CGang> pool;  return pool;}
CObjectMemoryPool<CFamilyMember>&   g_FamilyMemberPool() {static CObjectMemoryPool<CFamilyMember> pool;  return pool;}
CObjectMemoryPool<SystemMsg_t> &	   g_SystemMsgPool() {static CObjectMemoryPool<SystemMsg_t> pool;  return pool;}
CObjectMemoryPool<CTeamMember> &	   g_TeamMemberPool() {static CObjectMemoryPool<CTeamMember> pool;  return pool;}
#endif

#ifdef _CLIENT_
CObjectMemoryPool<Event>&			g_EventPool()			{static CObjectMemoryPool<Event> pool;			return pool;}
CObjectMemoryPool<CommodityGroup>&	g_CommodityGroupPool()	{static CObjectMemoryPool<CommodityGroup> pool;	return pool;}
CObjectMemoryPool<CTop_MemObj>&	    g_TopMemObjPool()		{static CObjectMemoryPool<CTop_MemObj> pool; return pool;}
CObjectMemoryPool<CTopObj>&	        g_TopObjPool()			{static CObjectMemoryPool<CTopObj> pool; return pool;}
#endif

#ifdef _GMSERVER_
CObjectMemoryPool<CSqlObj>&			g_UpdateSqlPool()	{static CObjectMemoryPool<CSqlObj> pool;	return pool;}
CObjectMemoryPool<CSqlObj>&			g_SelectSqlPool()	{static CObjectMemoryPool<CSqlObj> pool;	return pool;}
CObjectMemoryPool<sql_var>&			g_SqlVarPool()		{static CObjectMemoryPool<sql_var> pool;	return pool;}
CObjectMemoryPool<CSqlRetObj>&		g_SqlRetPool()		{static CObjectMemoryPool<CSqlRetObj> pool;	return pool;}
CObjectMemoryPool<CPlayer>&			g_PlayerPool()		{static CObjectMemoryPool<CPlayer> pool;	return pool;}
#endif

#ifdef _SALESERVER_
CObjectMemoryPool<CMail>&			g_MailPool()		{static CObjectMemoryPool<CMail> pool;		return pool;}
CObjectMemoryPool<CProp>&			g_PropPool()		{static CObjectMemoryPool<CProp> pool;		return pool;}
CObjectMemoryPool<sql_var>&			g_SqlVarPool()		{static CObjectMemoryPool<sql_var> pool;	return pool;}
CObjectMemoryPool<CSqlRetObj>&		g_SqlRetPool()		{static CObjectMemoryPool<CSqlRetObj> pool;	return pool;}
CObjectMemoryPool<CSqlObj>&			g_UpdateSqlPool()	{static CObjectMemoryPool<CSqlObj> pool;	return pool;}
CObjectMemoryPool<CSqlObj>&			g_SelectSqlPool()	{static CObjectMemoryPool<CSqlObj> pool;	return pool;}
#endif

#ifdef _NAMESERVER_
CObjectMemoryPool<CSqlObj>&			g_UpdateSqlPool()	{static CObjectMemoryPool<CSqlObj> pool;	return pool;}
CObjectMemoryPool<CSqlObj>&			g_SelectSqlPool()	{static CObjectMemoryPool<CSqlObj> pool;	return pool;}
CObjectMemoryPool<sql_var>&			g_SqlVarPool()		{static CObjectMemoryPool<sql_var> pool;	return pool;}
CObjectMemoryPool<CSqlRetObj>&		g_SqlRetPool()		{static CObjectMemoryPool<CSqlRetObj> pool;	return pool;}
#endif

//////////////////////////////////////////////////////////////////////////
//  CMemoryPoolFreeMgr 内存池释放管理器
//////////////////////////////////////////////////////////////////////////

CMemPoolFreeMgr CMemPoolFreeMgr::m_FreeMgr;

CMemPoolFreeMgr & CMemPoolFreeMgr::GetFreeMgr()
{
	return m_FreeMgr;
}
CMemPoolFreeMgr::CMemPoolFreeMgr()
{
	memset(m_FreeList,0,FREE_POOL_MAX * sizeof(FreeElement));
	m_nCursor = 0;
}

CMemPoolFreeMgr::~CMemPoolFreeMgr()
{
	memset(m_FreeList,0,FREE_POOL_MAX * sizeof(FreeElement));
	m_nCursor = 0;
}

BOOL CMemPoolFreeMgr::Logic()
{
	VPROF("MemPoolFreeLogic");

	if (m_nCursor <= 0)
	{
		return FALSE;
	}

	for(int i = 0; i < m_nCursor; i++)
	{
		if( !_Free(m_FreeList[i]) )
			_FreeEx(m_FreeList[i]);
	}

	m_nCursor = 0;
	memset(m_FreeList,0,FREE_POOL_MAX * sizeof(FreeElement));
	return TRUE;
}

BOOL CMemPoolFreeMgr::_Free(FreeElement & elem)
{
	if (elem.pAddr == NULL)
	{
		return FALSE;
	}

	switch(elem.nType)
	{
	case MPT_GS_TimerObj:
		{
			Timer_Obj * pTimerObj = static_cast<Timer_Obj*>(elem.pAddr);
			if (NULL != pTimerObj)
			{
				g_TimerPool().Free(pTimerObj);
			}
		}
		break;
	default:
		return FALSE;
	}

	elem.pAddr = NULL;
	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(Timer_Obj * pTimerObj)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		AssertMsg(0,"FREE_POOL_MAX too Small");
		return FALSE;
	}

	if (pTimerObj == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_TimerObj;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pTimerObj);
	m_nCursor++;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifdef _DATASERVER_
BOOL CMemPoolFreeMgr::_FreeEx(FreeElement & elem)
{
	if (elem.pAddr == NULL)
	{
		return FALSE;
	}

	switch(elem.nType)
	{
	case MPT_GS_Prop:
		{
			CProp * pProp = static_cast<CProp*>(elem.pAddr);
			if (NULL != pProp)
			{
				g_PropPool().Free(pProp);
			}
		}
		break;
	case MPT_GS_Player:
		{
			CPlayer * pPlayer= static_cast<CPlayer*>(elem.pAddr);
			if (NULL != pPlayer)
			{
				g_PlayerPool().Free(pPlayer);
			}
		}
		break;
	case MPT_GS_Npc:
		{
			CSGameNPC * pNpc = static_cast<CSGameNPC*>(elem.pAddr);
			if (NULL != pNpc)
			{
				g_NpcPool().Free(pNpc);
			}
		}
		break;
	case MPT_GS_Fellow:
		{
			CFellowNPC * pFellow = static_cast<CFellowNPC*>(elem.pAddr);
			if (NULL != pFellow)
			{
				g_FellowPool().Free(pFellow);
			}
		}
		break;
	case MPT_GS_Bag:
		{
			CBag * pBag = static_cast<CBag*>(elem.pAddr);
			if (NULL != pBag)
			{
				g_BagPool().Free(pBag);
			}
		}
		break;
	case MPT_GS_Buff:
		{
			CBuff * pBuff = static_cast<CBuff*>(elem.pAddr);
			if (NULL != pBuff)
			{
				g_BuffPool().Free(pBuff);
			}
		}
		break;
	case MPT_GS_Private:
		{
			CPrivate * pPrivate = static_cast<CPrivate*>(elem.pAddr);
			if (NULL != pPrivate)
			{
				g_PrivatePool().Free(pPrivate);
			}
		}
		break;
	case MPT_GS_PlayerQuest:
		{
			CPlayerQuest * pPlayerQuest = static_cast<CPlayerQuest*>(elem.pAddr);
			if (NULL != pPlayerQuest)
			{
				g_PlayerQuestPool().Free(pPlayerQuest);
			}
		}
		break;
	case MPT_GS_Event:
		{
			Event * pEvent = static_cast<Event*>(elem.pAddr);
			if (NULL != pEvent)
			{
				g_EventPool().Free(pEvent);
			}
		}
		break;
	case MPT_GS_Team:
		{
			CTeam * pTeam = static_cast<CTeam*>(elem.pAddr);
			if (NULL != pTeam)
			{
				g_TeamPool().Free(pTeam);
			}
		}
		break;
	case MPT_GS_Family:
		{
			CFamily * pFamily = static_cast<CFamily*>(elem.pAddr);
			if (NULL != pFamily)
			{
				g_FamilyPool().Free(pFamily);
			}
		}
		break;

	case MPT_GS_FeedBoss:
		{
			FeedBoss * pFeedBoss = static_cast<FeedBoss*>(elem.pAddr);
			if (NULL != pFeedBoss)
			{
				g_FeedBossPool().Free(pFeedBoss); //未有释放的地方
			}
		}
		break;
	case MPT_GS_TimerObj:
		{
			Timer_Obj * pTimerObj = static_cast<Timer_Obj*>(elem.pAddr);
			if (NULL != pTimerObj)
			{
				g_TimerPool().Free(pTimerObj);
			}
		}
		break;
	case MPT_GS_Scene:
		{
			CScene * pScene = static_cast<CScene*>(elem.pAddr);
			if (NULL != pScene)
			{
				g_ScenePool().Free(pScene);
			}
		}
		break;
	case MPT_GS_DownTime:
//		{
//			CCountDownTime * pDownTime = static_cast<CCountDownTime*>(elem.pAddr);
//			if (NULL != pDownTime)
//			{
//				g_CountDownTimePool().Free(pDownTime);
//			}
//		}
		break;
	case MPT_GS_Command:
		{
			PACKET_COMMAND * pCmd = static_cast<PACKET_COMMAND*>(elem.pAddr);
			if (NULL != pCmd)
			{
				g_SendPacketPool().Free(pCmd);
			}
		}
		break;
	case MPT_GS_ZoneMessage:
		{
			CZoneMessageBuffer * pZoneMsg = static_cast<CZoneMessageBuffer*>(elem.pAddr);
			if (NULL != pZoneMsg)
			{
				g_ZoneMessagePool().Free(pZoneMsg);
			}
		}
		break;
	default:
		elem.pAddr = NULL;
		return FALSE;
	}

	elem.pAddr = NULL;
	return TRUE;
}


BOOL CMemPoolFreeMgr::FreeObj(CProp * pProp)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_PropPool().Free(pProp);
		return FALSE;
	}

	if (pProp == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_Prop;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pProp);
	m_nCursor++;

	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(CPlayer * pPlayer)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_PlayerPool().Free(pPlayer);
		return FALSE;
	}

	if (pPlayer == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_Player;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pPlayer);
	m_nCursor++;

	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(CSGameNPC * pNpc)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_NpcPool().Free(pNpc);
		return FALSE;
	}

	if (pNpc == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_Npc;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pNpc);
	m_nCursor++;

	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(CFellowNPC * pFellow)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_FellowPool().Free(pFellow);
		return FALSE;
	}

	if (pFellow == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_Fellow;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pFellow);
	m_nCursor++;

	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(CBag * pBag)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_BagPool().Free(pBag);
		return FALSE;
	}

	if (pBag == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_Bag;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pBag);
	m_nCursor++;

	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(CBuff * pBuff)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_BuffPool().Free(pBuff);
		return FALSE;
	}

	if (pBuff == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_Buff;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pBuff);
	m_nCursor++;

	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(CPrivate * pPrivate)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_PrivatePool().Free(pPrivate);
		return FALSE;
	}

	if (pPrivate == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_Private;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pPrivate);
	m_nCursor++;

	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(CPrivateMember *pPrivateMember)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		return FALSE;
	}

	if (pPrivateMember == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_PrivateMember;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pPrivateMember);
	m_nCursor++;
	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(CPlayerQuest * pPlayerQuest)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_PlayerQuestPool().Free(pPlayerQuest);
		return FALSE;
	}

	if (pPlayerQuest == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_PlayerQuest;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pPlayerQuest);
	m_nCursor++;

	return TRUE;
}


BOOL CMemPoolFreeMgr::FreeObj(Event * pEvent)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_EventPool().Free(pEvent);
		return FALSE;
	}

	if (pEvent == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_Event;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pEvent);
	m_nCursor++;

	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(CTeam * pTeam)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_TeamPool().Free(pTeam);
		return FALSE;
	}

	if (pTeam == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_Team;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pTeam);
	m_nCursor++;

	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(CFamily * pFamily)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_FamilyPool().Free(pFamily);
		return FALSE;
	}

	if (pFamily == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_Family;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pFamily);
	m_nCursor++;

	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(CQuestionTop * pQuestion)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		return FALSE;
	}

	if (pQuestion == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_Question;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pQuestion);
	m_nCursor++;

	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(FeedBoss * pFeedBoss)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_FeedBossPool().Free(pFeedBoss);
		return FALSE;
	}

	if (pFeedBoss == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_FeedBoss;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pFeedBoss);
	m_nCursor++;

	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(CScene * pScene)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_ScenePool().Free(pScene);
		return FALSE;
	}

	if (pScene == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_Scene;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pScene);
	m_nCursor++;

	return TRUE;
}
/*
BOOL CMemPoolFreeMgr::FreeObj(CCountDownTime * pDownTime)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_CountDownTimePool().Free(pDownTime);
		return FALSE;
	}

	if (pDownTime == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_DownTime;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pDownTime);
	m_nCursor++;

	return TRUE;
}
*/

BOOL CMemPoolFreeMgr::FreeObj(PACKET_COMMAND * pCommand)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_SendPacketPool().Free(pCommand);
		return FALSE;
	}

	if (pCommand == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_Command;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pCommand);
	m_nCursor++;

	return TRUE;
}

BOOL CMemPoolFreeMgr::FreeObj(CZoneMessageBuffer * pZoneMsg)
{
	if (m_nCursor >= FREE_POOL_MAX)
	{
		// TODO : Log
		//AssertMsg(0,"FREE_POOL_MAX too Small");
		g_ZoneMessagePool().Free(pZoneMsg);
		return FALSE;
	}

	if (pZoneMsg == NULL)
	{
		// TODO : Log
		return FALSE;
	}

	m_FreeList[m_nCursor].nType = MPT_GS_ZoneMessage;
	m_FreeList[m_nCursor].pAddr = static_cast<void*>(pZoneMsg);
	m_nCursor++;

	return TRUE;
}

#else
BOOL CMemPoolFreeMgr::_FreeEx(FreeElement & elem)
{
	return FALSE;
}
#endif
