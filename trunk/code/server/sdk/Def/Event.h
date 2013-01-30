#pragma	  once
#include "CommData.h"
#include "utllinkedlist.h"
#include "PacketDefine.h"

//////////////////////////////////////////////////////////////////////////
//
enum Event_ID
{
	Event_INVALID			= 0,			// 无效事件
	Event_NULL,								// 空事件
	Event_Logic_Time		= 2,			// 逻辑秒
	Event_System_Message,					// 系统信息
	Event_Create_Role,						//创建角色
	Event_Delete_Role,						//删除角色	
	

	//Combat
	Event_Combat_Skill_Hit	= 10,			//0:PID, 1:SkillID, 2:Damage, 3:School
	Event_Combat_Skill_Crit,				//暴击
	Event_Combat_Skill_Miss,
	Event_Combat_Skill_Dodge,	

	Event_Combat_Skill_GetHit = 14,
	Event_Combat_Skill_GetCrit,
	Event_Combat_Skill_GetMiss,	
	Event_Combat_Skill_GetDodge,	



// 	Event_Combat_Effect_Hit,
// 	Event_Combat_Effect_Crit,
// 	Event_Combat_Effect_Miss,
// 	Event_Combat_Effect_Dodge,	
// 
// 	Event_Combat_Effect_GetHit,
// 	Event_Combat_Effect_GetCrit,
// 	Event_Combat_Effect_GetMiss,
// 	Event_Combat_Effect_GetDodge,	

	Event_Combat_TargetOutofRange = 26 ,	// 离开攻击范围

	Event_Combat_Kill			= 27,		// A 杀死 B 用 C的技能   参数顺序: B 
	Event_Combat_beKilled,					// A 被 B 杀死 用C技能	 参数顺序: B 	
	Event_Combat_Revive,					// 复活
	Event_Combat_RecvDamage,				// 受到伤害
	Event_Combat_Attack,
	Event_Combat_UnderAttack,
	Event_Combat_GameKill,                 //游戏击杀
	Event_Combat_BeGameKill,               //被游戏击杀（不是真正的死亡，只是倒地）
	

	Event_Combat_Effect_UnSet	= 50,		// 卸载效果
	Event_Combat_Effect_OnSet,				// 加载效果作用

	Event_Combat_Skill_HolyStrike= 80,		// 致命一击
	Event_Combat_Skill_GetHolyStrike,

	Event_Combat_Effect_HolyStrike,
	Event_Combat_Effect_GetHolyStrike,
	Event_Combat_Effect_HpHadLittle,      //血量减少到一定值时


	//Prop
	Event_Prop_Use				= 100,		//使用道具
	Event_Prop_Get,							//得到道具
	Event_Prop_Lost,						//扔道具
	Event_Prop_Equip,						//装备道具
	Event_Prop_UnEquip,						//卸载道具
	Event_Prop_Split,						//拆分道具
	Event_Prop_Attrib_Change,               //道具属性改变
	Event_Prop_AddGem,                      //道具镶嵌
	Event_Prop_UseSkill,					//使用道具技能
	Event_Prop_AddHole,						//打孔
	Event_Prop_AddStar,						//加星
	Event_Prop_Move,						//移动道具 
	Event_Prop_Bind,						//装备绑定
	Event_Prop_ByFromNPC,					//从NPC购买装备
	Event_Prop_Compose,						//合成道具，包括合成材料和合成装备
	Event_Prop_Rebind,						//重绑定
	Event_Prop_ReFiveElement,				//修改五行	
	Event_Prop_Destory,						//摧毁道具(包括DB 删除彻底性的)
	//Quest
	Event_Quest_Accept			= 200,		// Param1:QuestID	Param2:Player PID
	Event_Quest_Update,						
	Event_Quest_Abandon,
	Event_Quest_Complete,					// Param1:QuestID	Param2:Player PID
	Event_Quest_Start,						// 任务开始
	Event_Quest_Stop,						// 任务停止
	Event_Quest_ChildInquirer,          	// 任务子请求
	Event_Quest_Inquirer,               	// 主对话请求
	Event_Quest_FindNpc,
	Event_Quest_AddFriend,
	Event_Quest_AddTeam,
	Event_Quest_AddAttribute,
	Event_Quest_AddSkill,
	Event_Quest_GameStart,              	//活动开始
	Event_Quest_GameOver,               	//活动结束
	Event_Quest_QuestTimeStart,
	Event_Quest_QuestTimeOver,          	//计时任务时间到
	Event_Quest_MonsterGoHome,          	//怪物GoHome
	Event_Quest_ReadMail,					//读信
	Event_Quest_AskQuestionOver,        	//答题完毕
	Event_Quest_AskWrong,               	//答题错误
	Event_Quest_DragCutShort,				//拖动快捷栏
	Event_Quest_TitleAccept,				//任务名称子请求接受
	Event_Quest_TitleNoComplete,			//任务名称请求未完成
	Evetn_Quest_TitleComplete,				//任务名称请求完成
	Event_Quest_KillMonstlevel,				//杀规定等级的怪
	Event_Quest_InAutoZone,					//进入任务触发区域
	Event_Quest_CatchPet,					//任务捕捉宠物
	Event_Quest_GetMidNPC,					//任务捕获中间单位
	Event_Quest_LostMidNPC,					//任务失去中间单位
	Event_Quest_Failed,						//任务失败
    Event_Quest_RemoveBuff,                 // 移除buff任务失败事件
	Event_Quest_KillOverlevel,				//杀指定等级以上的怪，第一个参数为指定的等级
	Event_Quest_KillManyMonster,			//任务中杀多种怪，四个参数为怪物ID	
	Event_Quest_MiddleTalk,               	//任务中间对话
	Event_Quest_KillHigherMonster,          //击杀不低于自身等级的怪物
	Event_Quest_Load,						//加载任务
	Event_Quest_NULL,						//空事件，用于脚本任务目标计数
	Event_Quest_Clear,						//清除任务事件 add by lfy 2012.6.1
	Event_Quest_Complete_ByID,				//完成任务事件，用于通知其他任务本任务的完成状态 add by lfy 2012.6.14

	//客户端任务界面操作事件
	Event_Quest_ClientOperation		= 250,		//客户端界面操作事件

	//Action
	Event_Action_Move			= 300,		//移动
	Event_Action_Stop,						//停止
	Event_Action_Arrive,					//到达
	Event_Action_Blocked,					//阻挡
	Event_Action_RequestMove,				//请求移动
	Event_Reply_Summon,						//响应召唤

	//Inquirer
	Event_Inquirer				= 400,		//和NPC对话 0:NPC PID 1:InquirerID
	Event_BeInquirer,						//被Player对话 0:Player PID  1:Inquirer Type 2:Inquirer ID
	Event_BeChildInquirer,              	//被Player子对话
	Event_InquirerOver,						//对话结束事件
	

	//Scene
	Event_Scene_Create			= 500,		//
	Event_Scene_Delete,						//

	Event_AutoNPC_Create			= 600,		//自动驾驶NPC创建

	Event_Player_Scene_Exit     = 700,  	//玩家退出场景
	Event_Player_Scene_Enter,           	//玩家进入场景

	Event_Add_Combat_Pet		= 800,		//增加战斗宠
	Event_Remove_Combat_Pet,				//删除战斗宠
	Event_CombineWithCombatPet,				//与战宠合体
	Event_UnCombineWithCombatPet,			//与战宠合体结束

	Event_Add_WaitPet			= 810,		//召唤侍宠



	// Login / Exit	
	Event_Player_Login			= 1001,
	Event_Player_Exit,						//玩家离开游戏
	Event_Player_FirstLogin,				//玩家初次登陆

	//Explorer
	Event_Explorer_Add			= 1100,		//进入同屏表
	Event_Explorer_Remvoe,					//移除同屏表

	//pet
	Event_Explorer_AddProp		= 1200,		//道具进入同屏表
	Event_Explorer_RemoveProp,				//道具离开同屏表
	Event_Owner_Attack,						//宠物主人攻击人    主人PID   被攻击者PID
	Event_Owner_DesAttack,					//宠物被攻击		主人PID    打主人的 PID
	Event_Pet_Dead,							//宠物死亡（只是骑宠和战宠） 主人PID  死亡宠物的PID
	Event_Pet_Evolution,					//强化珍兽
	Event_Pet_LevelUp,						//珍兽升级
	Event_Pet_AttribPoint,					//珍兽属性点改变
	Event_Pet_Refinery,						//珍兽炼化事件
	Enent_Pet_CreateFellow,					//珍兽创建					
	Event_Pet_Illusion,						//珍兽幻化
	Event_Pet_Release,						//珍兽放生
	Event_Pet_SealFellow,					//珍兽还魂
	Event_Pet_Destory_SealEgg,				//丢弃珍兽封印蛋

	//pk & prison
	Event_Change_RednameType	= 1300,		//改变红名状态

	//Family
	Event_Family_Money			= 1400,		//家族资金变化
	Event_Family_Action_Complete,			//家族活动完成
	Event_FamilyPower,						//家族职位变化
	Event_Family_Level,						//家族等级变化
	Event_Create_Family,					//建立家族
	Event_Change_Family,					//加入或退出家族
	Event_Remove_Family,					//解散家族
	Event_Make_Tank,						//使用战车
	Event_Return_Tank,						//归还战车

	//Gang
	Event_Gang_Action_Complete	= 1500,		//帮会活动完成
	Event_Gang_Money,						//帮会资金变化
	Event_GangPower,						//帮会职位变化
	Event_Gang_Level,						//帮会等级变化
	Event_Create_Gang,						//建立帮会
	Event_Change_Gang,						//加入或退出帮会
	Event_Remove_Gang,						//解散帮会

	//State
	Event_State_Action_Complete	 = 1600,	//国家活动完成
	Event_StatePower,						//国家职位变化
	Event_Create_King,						//建立国王
	Event_Remove_King,						//国王下台
	Event_NoSpeak,							//禁言
	Event_Prisoner,							//关监狱
	Event_Gantry,							//龙脉变化
	Event_BOSS_Update,						//BOSS更新or设施更新
	Event_kill_BOSS,						//击杀BOSS
	Event_Attack_State_Goal,				//攻击他国重要目标or国家重要目标被攻击
	Event_Destroy_State_Goal,				//摧毁了他国的国家重要目标or国家重要目标被摧毁
	Event_Kill_Player,						//杀死敌国人or杀死本国人

	//Team
	Event_Add_Team = 1650,
	Event_Remove_Team,

	//Private
	Event_Private_Flag			= 1700,		//结婚or离婚
	Event_Bind_Box_Top,						//开绑定箱子第一名
	Event_NotBind_Box_Top,					//开非绑定箱子第一名
	Event_Private_All_Power_Top,			//个人综合实力第一名
	Event_Get_Cat,							//领到金镖
	Event_Flowers,							//献花
	Event_Make_Prop,						//打造装备
	Event_Change_Color_Name,				//名字变色
	Event_Add_Private_Friend,

	Event_Public				= 1800,		//循环公告
	Event_Ad,								//循环广告
	Event_Open_Box,							//开箱子获得高级物品
	Event_Enter_Scene,						//进入某一场景或是区域
	Event_Create_Kaiser,					//成为皇帝
	
	//活动
	Event_Campaign_Start        = 1900,     //活动开始
	Event_Campaign_Over,					//活动结束
	Event_Campaign_Signup,					//活动报名成功
	Event_Campaign_5MinPre,                 //答题活动开始前报时
	Event_Campaign_3MinPre,                 //答题活动开始前报时
	Event_Campaign_1MinPre,                 //答题活动开始前报时


	//财产保护
	Event_Warehouse_Open		= 2000,		//打开仓库界面
	Event_Mail_Open,						//打开邮件界面
	Event_Auction_Open,						//打开拍卖行界面
	Event_Clearing_Open,					//打开交易所界面

	//快捷栏（技能）
	Event_Remove_ShortCutObj	=2100,		//移除快捷栏的技能

	//光环
	Event_Aura_Create			= 2200,		//创建光环
	Event_Aura_Remove,						//移除光环
	//buff
	Event_Add_Buff				= 2250,		//增加buff
	Event_Remove_Buff,						//移除buff	
//生活
	Event_Cast_Complete		=2300,		//生活技能完成
	Event_Cast_Break,

	//messageobx事件
	Event_Messagebox_Accept		= 2400,		//接受按钮
	Event_Messagebox_Refuse,				//拒绝按钮
	Event_InputBox_Accpet,					//输入框接受
	Event_InputBox_Refuse,					//输入框拒绝

	Event_Player_Attack			= 2500,		//战斗攻击的发出		A-ID	B-ID	值	时间	skillID
	Event_Player_Damage,					//战斗伤害的发出		A-ID	B-ID	值	时间	skillID
	Event_Player_UseSkill,					//战斗技能的使用		A-ID	B-ID	ID	时间	skillID
	

	// Player 事件
	Event_Player_LevelUp		= 2600,			//角色等级改变
	Event_Player_ChangeJob,						//角色职业改变
	Event_Player_LeaveFamily,					//玩家离开家族
	Event_Player_LeaveGang,						//玩家离开帮会
	Event_Player_ChangeTeam,					//玩家改变队伍
	
	// Money 事件
	Event_BindSilver_CreateCost		= 2999,			// 银票的产出与消耗

	////////////////////////////////////////////
	//仅用于客户端显示tip的事件,仅在界面中触发和使用
	////////////////////////////////////////////

	Event_HelpTip_FindNPC       = 3000,     //打开npc列表
	Event_HelpTip_OpenMap,                  //打开地图
	Event_HelpTip_Repair,                   //修理道具
	Event_HelpTip_LvUp,                     //升级
	Event_HelpTip_Sit,                      //打坐
	Event_HelpTip_FiveAttrib,               //5行
	Event_HelpTip_StallButton_Click,        //人物头像右键按下摆摊健
	Event_HelpTip_MakeProp,                 //打造
	Event_HelpTip_BindProp,                 //绑定
	Event_HelpTip_FollowMagic,              //附魔
	Event_HelpTip_ActionButton_Click,       //点击拍卖行
	Event_HelpTip_AcceptCredit,             //获得声望
	Event_HelpTip_HonorTeam,                //荣誉组队
	Event_HelpTip_Marriage,                 //结婚
	Event_HelpTip_Master,                   //师徒
	Event_HelpTip_DuryZero,					//磨损为0
	Event_HelpTip_SwitchPK,					//切换pk模式
	Event_HelpTip_PickProp,					//拾取道具
	

	///////////////////////
	//用于客户端界面事件
	///////////////////////
	Event_Clint_Contrl_Click=4000,			//控件被按下	
	Event_Drag_Prop_Cut_Start,				//道具拖拽开始
	Event_Drag_Skill_Cut_Start,				//技能拖拽开始
	Event_Dialog_Open,						//界面打开
	Event_Drag_Cut_End,						//拖拽到快捷栏完毕
	Event_Drag_Prop_Cut_Reback,				//拖拽中途放下道具回背包
	Event_Bag_PropPet_Use,					//在背包中右键使用宠物道具	
	Event_Role_Prop_MainEquip,				//主手武器装备
	Event_DragDown_Prop,					//放下道具快捷
	Event_DragDown_Skill,					//放下技能快捷
	Event_Hp_DownByPer,						//掉血低于百分比
	Event_Newman_Add_Skill,					//添加技能
	Event_Notice_TimeOut,					//界面关闭新手提示通知
	Event_Notice_GiftOnTime,				//新手礼物倒计时事件
	Event_Drag_Pet_Cut_Start,				//宠物拖拽开始
	Event_Notice_AddFriend,					//添加好友
	Event_Notice_AddTeam,					//加入队伍
	Event_Notice_AddFamily,					//加入家族
	Event_Notice_AddGang,					//加入帮会
	Event_Hp_DownByFel,                     //玄兽掉血百分比
	Event_Put_Prop_Inter_NewStar,           //在新光宝盒装备升星页签中间道具框放入道具
	Event_Put_Prop_Inter_NewBind,           //在新光宝盒装备绑定页签中间道具框放入道具
	Event_Put_Prop_TopR_NewBind,            //在新光宝盒绑定装备页签右上角道具框放入道具
	Event_Quest_AchiveTarget,				//任务达成
	Event_Newman_UseSkill,					//使用技能
	Event_Newman_ExpTopLimit,				//当前等级经验已满
	Event_Newman_PetLevelUp,				//玄兽升级事件
	Event_Newman_NewStarPutStone,			//月光宝盒中放入宝石
	Event_Newman_PetSummon,					//玄兽召唤事件
	Event_Newman_QuestTrackClick,			//任务追踪链接点击事件
	Event_Newman_QuestLogClick,				//任务日志链接点击事件
	Event_Newman_AttribAdd,				    //加属性点事件
	Event_Newman_OnRide,					//上马事件
	Event_Newman_EnergyAvailable,			//活力激活事件
	Event_Newman_PutEquipCombine_Center,	//神机匣中间格子放入装备		
	Event_Newman_PutEquipCombine_Around,	//神机匣周围格子放入装备
	Event_PetUI_Strenthen_PutPet,			//珍兽强化界面放入珍兽
	Event_PetUI_Strenthen_PutStone,			//珍兽强化界面放入珍兽
	Event_Pet_LowHappy,						//珍兽快乐度低于百分比
	Event_EarthSoulButton_Click,			//元魂界面地煞按钮点击事件
	Event_Newman_BattleCredit,				//战斗功勋增加事件
	Event_Newman_RageMax,					//忠义值满事件
	Event_Dialog_Release,					//界面关闭事件
	Event_Newman_Wage,						//获得家族工资事件
	Event_Newman_MaterialInput,				//神机匣放入道具
	Event_Newman_FamilyCredit,				//获得家族贡献事件
	Event_Newman_OpenBag,				    //打开背包
	// 交易
	Event_Exchange_Success = 5000,					//交易成功
	Event_Exchange_Prop,					//玩家之间交易
	//摆摊
	Event_Stall_Begin = 5500,				//开始摆摊
	Event_Stall_Exchange_Count,				//摆摊交易完成次数

	//装备打造合成
	Event_ExecuteAddStar = 5800,			//进行打星
	Event_ExecuteMatrialCompose,			//进行材料合成
	Event_ExecuteEquipCompose,				//进行装备合成

	//金钱
	Event_BindSilver = 6000,				//绑定钱变动
	Event_Silver,					//非绑定钱变动

	Event_Drag_FacePicture_Start = 6100,		//  图片拖拽开始

	//Mail
	Event_Quest_SendMail = 6500,			//请求发送邮件
	Event_Quest_Deletemail,                 //请求删除邮件  
	Event_Quest_GetMail_Accessories,        //请求提取邮件附件

	Event_Succeed_SendMail,                 //发送邮件成功
	Event_Succeed_Deletemail,               //删除邮件成功  
	Event_Succeed_GetMail_Accessories,      //提取邮件附件成功

	//Monitor事件
	Event_Monitor_CreateProp,				// 监视创建道具事件
};

//////////////////////////////////////////////////////////////////////////

class Event : public IBaseObj
{
public:
	Event();
	~Event();

	inline Event_ID EventID()					{ return m_nEventID;}
	inline void SetEventID(Event_ID EventID)	{ m_nEventID = EventID; }

	inline void Create(Event_ID nEventID,PersonID PID,SCENEID SID,int64 nParam1 = INVALID_VALUE, int64 nParam2 = INVALID_VALUE, int64 nParam3 = INVALID_VALUE, int64 nParam4 = INVALID_VALUE,int64 nParam5 = INVALID_VALUE,int64 nParam6=INVALID_VALUE,char* szParam1=NULL,BOOL bUpdateDB = FALSE)
	{
		m_nPID = PID;
		m_nSceneID = SID;
		m_nEventID = nEventID;
		m_nParam[0] = nParam1;
		m_nParam[1] = nParam2;
		m_nParam[2] = nParam3;
		m_nParam[3] = nParam4;		
		m_nParam[4] = nParam5;
		m_nParam[5] = nParam6;
		if(szParam1)
			strncpy(m_szParam,szParam1,SHORT_STRING_LEN);
		m_bUpdateDB = bUpdateDB;
		m_bIsUsing = TRUE;
	}

	inline BOOL operator == (const Event& event)
	{
		return ((m_nEventID == event.m_nEventID) &&
			   (m_nPID == event.m_nPID) &&
			   (m_bIsUsing == event.m_bIsUsing) &&
			   (m_nSceneID == event.m_nSceneID ) &&
			   (m_nParam[0] == event.m_nParam[0])&&
			   (m_nParam[1] == event.m_nParam[1])&&
			   (m_nParam[2] == event.m_nParam[2])&&
			   (m_nParam[3] == event.m_nParam[3])&&
			   (m_nParam[4] == event.m_nParam[4])&&
			   (m_nParam[5] == event.m_nParam[5]));
	}
	inline Event& operator = (const Event& event)
	{
		m_nPID	= event.m_nPID;
		m_nSceneID = event.m_nSceneID;
		m_nEventID = event.m_nEventID;
		m_bIsUsing	= event.m_bIsUsing;
		m_nParam[0] = event.m_nParam[0];
		m_nParam[1] = event.m_nParam[1];
		m_nParam[2] = event.m_nParam[2];
		m_nParam[3] = event.m_nParam[3];
		m_nParam[4] = event.m_nParam[4];
		m_nParam[5] = event.m_nParam[5];
		strncpy(m_szParam,event.m_szParam,SHORT_STRING_LEN);
		return *this;
	}

public:
	Event_ID	m_nEventID;
	PersonID	m_nPID;					// 产生事件的人
	SCENEID		m_nSceneID;				// 	
	int64		m_nParam[6];
	char		m_szParam[SHORT_STRING_LEN];			//
	BOOL		m_bUpdateDB;
	BOOL		m_bIsUsing;				//--该内存是否正在被使用--
};

Event*	MakeEvent(Event_ID nEventID,PersonID PID=INVALID_PID,SCENEID SID = INVALID_SCENEID,int64 nParam1 =INVALID_VALUE, int64 nParam2 = INVALID_VALUE, int64 nParam3 = INVALID_VALUE, int64 nParam4 = INVALID_VALUE,int64 nParam5=INVALID_VALUE,int64 nParam6=INVALID_VALUE,char* szParam1=NULL,BOOL bUpdateDB = FALSE);
Event*	MakeEvent(Event* pEvent);

//Event*	g_AllocEvent();
//void	g_FreeEvent(Event* pEvent);
//int		g_GetEventAllocCount();

typedef CUtlLinkedList<Event*,int>		EventList;

//////////////////////////////////////////////////////////////////////////
//
class CEventPool
{
public:
	CEventPool();
	~CEventPool();

	virtual bool Create(int nPoolSize);
	virtual void Release();

	Event*		Alloc();
	inline void	Free(Event* pEvent){}

protected:
	int			m_EventPoolSize;
	ULONG		m_EventTableIndex;
	Event*		m_EventTable;
};

CEventPool& EventPool();
