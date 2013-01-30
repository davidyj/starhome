#pragma	   once

#include "memorypool.h"

//client
class CommodityGroup;
//login
class PlayerLoginInfo;
//class CUserSession;

//dataserver
class CProp;
class CPlayer;
class CSGameNPC;
class CBag;
class CBuff;
class CPrivate;
class CPrivateMember;

class CPlayerQuest;
class Event;
class CTeam;
class CFamily;
class CFellowNPC;
class CQuestionTop;
class FeedBoss;
class CPetItem;
//class CCountDownTime;
class CScene;
struct Timer_Obj;
struct PACKET_COMMAND;
class CZoneMessageBuffer;
class Send2Player;
class CGlobalBoss;			//add by zhangjianli 2011-10-21
class CUseCountObj;			//add by zlm 2012.2.6
struct EventRegistry;
class CRobotAIUnit;

//dbserver
class CUser;
class CFamily;
class COfflineCmd;
class CCreatePlayerInfo;
class CPlayerQuest;
class CShortCutObj;
//class CSignUpObj;
class CMail;
class CGang;
class CGroup;
class CAuction;
//class CQuestionTop;
class sql_var;
//class CPlayerSummon;
class CSqlRetObj;
class CSqlObj;
class CVitality;
struct LogUsr;
class CampaignSignUp;
class CTop_MemObj;
class CTopObj;
//CCommunityServer
struct CPrisoner;
class SummonUnit;
class CFamilyMember;
class CTeamSession;
struct SystemMsg_t;
class CTeamMember;
struct Transac;
struct stPayInfo;
class CStallBuyPropInfo;
//全局内存池定义
//client
extern CObjectMemoryPool<CommodityGroup>&	g_CommodityGroupPool();
extern CObjectMemoryPool<CTop_MemObj>&		g_TopMemObjPool();	
extern CObjectMemoryPool<CTopObj>&    		g_TopObjPool();	
//login
CObjectMemoryPool<PlayerLoginInfo>&			g_PlayerLoginPool() ;
extern CObjectMemoryPool<stPayInfo>&			g_PayPool();
//CObjectMemoryPool<CUserSession>&			g_UserSessionPool();
//dataserver
extern CObjectMemoryPool<CProp>&			g_PropPool();
extern CObjectMemoryPool<CPlayer>&			g_PlayerPool();
extern CObjectMemoryPool<CSGameNPC>&		g_NpcPool();
extern CObjectMemoryPool<CFellowNPC>&		g_FellowPool();
extern CObjectMemoryPool<CBag>&				g_BagPool();
extern CObjectMemoryPool<CBuff>&			g_BuffPool();
extern CObjectMemoryPool<CPrivate>&			g_PrivatePool();
extern CObjectMemoryPool<CPrivateMember>&	g_PrivateMemberPool();
extern CObjectMemoryPool<Transac>&			g_TransacPool();
extern CObjectMemoryPool<CPlayerQuest>&		g_PlayerQuestPool();
extern CObjectMemoryPool<Event>&			g_EventPool();
extern CObjectMemoryPool<CTeam>&			g_TeamPool();
extern CObjectMemoryPool<CFamily>&			g_FamilyPool();
extern CObjectMemoryPool<FeedBoss>&			g_FeedBossPool();
extern CObjectMemoryPool<CPetItem>&			g_PetItemPool();
extern CObjectMemoryPool<Timer_Obj>&		g_TimerPool();
extern CObjectMemoryPool<CScene>&			g_ScenePool();
extern CObjectMemoryPool<Send2Player>&		g_Send2PlayerPool();
//extern CObjectMemoryPool<CCountDownTime>&	g_CountDownTimePool();
//extern CObjectMemoryPool<PACKET_COMMAND>&	g_PacketPool();
extern CObjectMemoryPool<PACKET_COMMAND>&	g_SendPacketPool();
extern CObjectMemoryPool<CZoneMessageBuffer>&		g_ZoneMessagePool();
extern CObjectMemoryPool<CUseCountObj>&		g_UseCountPool();
extern CObjectMemoryPool<EventRegistry>&	g_EventRegistryPool();
extern CObjectMemoryPool<CRobotAIUnit>&	g_RobotAIUnitPool();

//dbserver
extern CObjectMemoryPool<CUser>&			g_UserPool();
//extern CObjectMemoryPool<CProp>&			g_PropPool();
extern CObjectMemoryPool<CFamily>&			g_FamilyPool();
extern CObjectMemoryPool<LogUsr>&			g_LogUsrPool();
//extern CObjectMemoryPool<CSignUpObj>&		g_SignUpPool();
extern CObjectMemoryPool<CMail>&			g_MailPool();
extern CObjectMemoryPool<CGang>&			g_GangPool();
extern CObjectMemoryPool<CGroup>&			g_GroupPool();
extern CObjectMemoryPool<CSqlObj>&			g_UpdateSqlPool();
extern CObjectMemoryPool<CSqlObj>&			g_SelectSqlPool();
extern CObjectMemoryPool<sql_var>&			g_SqlVarPool();
extern CObjectMemoryPool<CSqlRetObj>&		g_SqlRetPool();
extern CObjectMemoryPool<CAuction>&			g_AuctionPool();
extern CObjectMemoryPool<COfflineCmd>&		g_OfflineCmdPool();
extern CObjectMemoryPool<CCreatePlayerInfo>&		g_CrtPlayerInfoPool();
extern CObjectMemoryPool<CVitality>&		g_VitalityPool();
extern CObjectMemoryPool<CampaignSignUp>&	g_SignUpPool();	
extern CObjectMemoryPool<CTop_MemObj>&		g_TopMemObjPool();	
extern CObjectMemoryPool<CTopObj>&    		g_TopObjPool();	
extern CObjectMemoryPool<CShortCutObj>&		g_ShuortCutPool();				//快捷栏内存池 add by david 2011-11-21

//communityserver
extern CObjectMemoryPool<SummonUnit>&		g_SummonPool();
extern CObjectMemoryPool<CGlobalBoss>&		g_GlobalBossPool();				//全局BOSS add by zhangjianli 2011-10-21

extern CObjectMemoryPool<CPrisoner>&	    g_PrisonerPool();
extern CObjectMemoryPool<CGang>&			g_GangPool();
extern CObjectMemoryPool<CQuestionTop>&		g_QuestionTopPool();
extern CObjectMemoryPool<CFamilyMember>&    g_FamilyMemberPool();
extern CObjectMemoryPool<CTeamSession>&		g_TeamSessionPool();
extern CObjectMemoryPool<SystemMsg_t>&		g_SystemMsgPool();
extern CObjectMemoryPool<CTeamMember>&		g_TeamMemberPool();
extern CObjectMemoryPool<CStallBuyPropInfo>&   g_StallBuyPropInfoPool();

//////////////////////////////////////////////////////////////////////////
//  CMemoryPoolFreeMgr 内存池释放管理器
//////////////////////////////////////////////////////////////////////////
//#ifdef _DATASERVER_
#define FREE_POOL_MAX 2000
class CMemPoolFreeMgr
{
public:
	enum MemPoolType
	{
		// GS：内存池是在GameServer上用的
		MPT_GS_Begin = -1,

		MPT_GS_Prop,
		MPT_GS_Player,
		MPT_GS_Npc,
		MPT_GS_Fellow,
		MPT_GS_Bag,
		MPT_GS_Buff,
		MPT_GS_Private,
		MPT_GS_PrivateMember,
		MPT_GS_PlayerQuest,
		MPT_GS_Event,
		MPT_GS_Team,
		MPT_GS_Family,
		MPT_GS_TopObj,
		MPT_GS_Question,
		MPT_GS_FeedBoss,
		MPT_GS_TimerObj,
		MPT_GS_Scene,
		MPT_GS_DownTime,
		MPT_GS_Command,
		MPT_GS_ZoneMessage,

		MPT_GS_End,
	};

	struct FreeElement
	{
		MemPoolType nType;
		void * pAddr;

		void ClearUp()
		{
			nType = MPT_GS_Begin;
			pAddr = NULL;
		}
	};
public:
	CMemPoolFreeMgr();
	~CMemPoolFreeMgr();
	static CMemPoolFreeMgr & GetFreeMgr();

	BOOL Logic();

	BOOL FreeObj(CProp * pProp);
	BOOL FreeObj(CPlayer * pPlayer);
	BOOL FreeObj(CSGameNPC * pNpc);
	BOOL FreeObj(CFellowNPC * pFellow);
	BOOL FreeObj(CBag * pBag);
	BOOL FreeObj(CBuff * pBuff);
	BOOL FreeObj(CPrivate * pPrivate);
	BOOL FreeObj(CPrivateMember *pPrivateMember);
	BOOL FreeObj(CTeamSession *pTeamSession);
	BOOL FreeObj(CPlayerQuest * pPlayerQuest);
	BOOL FreeObj(Event * pEvent);
	BOOL FreeObj(CTeam * pTeam);
	BOOL FreeObj(CFamily * pFamily);
	BOOL FreeObj(CQuestionTop * pQuestion);
	BOOL FreeObj(FeedBoss * pFeedBoss);
	BOOL FreeObj(Timer_Obj * pTimerObj);
	BOOL FreeObj(CScene * pScene);
//	BOOL FreeObj(CCountDownTime * pDownTime);
	BOOL FreeObj(PACKET_COMMAND * pCommand);
	BOOL FreeObj(CZoneMessageBuffer * pZoneMsg);

private:
	BOOL _Free(FreeElement & elem);
	BOOL _FreeEx(FreeElement & elem);

private:
	FreeElement m_FreeList[FREE_POOL_MAX];
	int m_nCursor;
	static CMemPoolFreeMgr m_FreeMgr;
};

//#endif
