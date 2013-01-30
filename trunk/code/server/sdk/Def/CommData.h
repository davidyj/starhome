//
//
//			commdata.h
//
//					程序用得公共得头文件，其中记录了一些基本得
//			结构体，和一些补充得 函数，其中 这些函数都是策划不
//			不需要使用得部分。
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////
#pragma warning(disable:4244)
#pragma warning(disable:4146)

#pragma once

#include "BaseObj.h"
#include "strtools.h"
#include "XMLParser.h"
#include "MemoryPoolDef.h"

#include "utlbuffer.h"
#include "Token.h"


//定义使用的哈希结构库
#define _CLXHLIST_
//#define _UTLHASH_
//#define _UTLMAP_

#ifndef PAYSERVER_OPENCLOSE_STATE
#define PAYSERVER_OPENCLOSE_STATE	TRUE	//支付系统开关
#endif

#ifndef PAY_SYNCH_MODE
#define PAY_SYNCH_MODE	FALSE	//支付系统----> 同步异步机制开关
#endif

#ifndef	_NEWACTIVECODEGIFT_
#define _NEWACTIVECODEGIFT_		TRUE						// 新的激活码礼包方式
#define _OLDACTIVECODEGIFT_		!_NEWACTIVECODEGIFT_		// 旧的激活码礼包方式 (与新互斥)
#endif

#ifndef _USEUTF8_
#define _USEUTF8_	FALSE		//默认不开启,
#endif

#define Bag_Max Bag_UI_End
//默认系统设置
#define DEFAULT_SYSTEMSET 398715391

const int  MAX_OPENNUM  = 8;			// 百年陈酿最大道具数
const int  MAX_YEARWINESELECTCOUNT = 6;	// 百年陈酿最大选择数量

const int QUEST_ID_MAX = 2000;				//任务的最大数量

const int REPAIRTIPLOWNUM = 200;		// 装备耐久 最低 提示值

const int  UTL_NO_GROW_TYPE = -1;
const int  UTL_DEFAULT_SIZE =100;

const int SKILL_SUMMON_FAMILYCAR = 608046;	//召唤战车技能ID add by zhangjianli 2012-10-5
const int Skill_Enter_FCar = 608070;		//进入战车时，使用的读条技能
//
extern UINT g_GameTimer;
extern UINT g_Circles;
extern UINT GAME_FPS;

const UINT SERVER_TIMER_FREQUENCY = 25;
const UINT SERVER_TIMER_PERIOD = 1000 / SERVER_TIMER_FREQUENCY;

const int EVERYONE_ESELECT_MAILMAX = 100; //暂时每个玩家最多加载邮件100封


typedef UINT64	PersonID;						// 玩家角色的ID	-1 为无效值
typedef UINT64  PropID;							// 道具ID
typedef UINT64	SCENEID;						// 场景ID
typedef UINT64	UserID;							// 帐户ID
typedef INT		NETID;							// 网络ID		-1 为无效值
typedef INT		SkillID;						// 技能ID
typedef UINT    TABLEID;						// TableID
typedef INT		QuestID;						// 任务ID
typedef UINT	ServerID;						// 服务器ID
typedef UINT    StateID;						// 国家ID
typedef INT     TemplateID;						// Scene NPC,PROP模板ID
typedef INT     ChatID;							// 闲聊ID
typedef INT		UIPos;							// 道具的UI位置  十进制 aabbb， aa表示背包索引，bbb表示背包内的位置
typedef INT     TargetID;						// 目标ID
typedef UINT64  EffectID;						// 效果ID
typedef INT		BuffID;							// 状态ID
typedef UINT64	TMV;							// 时间类型
typedef UINT64	RegTM;							// 注册时间类型
typedef __int64	StatusFlag;						// 状态ID
typedef UINT64	StatusFlagGroup;				// 状态组
typedef UINT64  MailID;							// 邮件ID
typedef UINT64	PetID;							// 宠物ID
typedef INT     QuestionID;						// 题目ID
typedef UINT64	AuctionID;						// 拍卖ID
typedef UINT64  BuyID;                          // 求购ID
typedef UINT64  BidID;                          // 竞拍ID
typedef UINT64  BuyID;                          // 求购ID
typedef UINT64	ClearingID;						// 交易所ID
typedef UINT64  CampaignID;                     // 活动ID
typedef UINT64	DialyMissionID;					// 活动ID
typedef UINT64	TrscID;							// 金钱交易ID
typedef INT64   Type_Money;                     // 金钱单位类型


#define CURRENT_VERSION_ID			0			//add by mayanling 2010-3-23 当前版本号

#ifdef _CLIENT_
#define USER_COUNT_MAX				1			// User的数量
#define NPC_COUNT_MAX				1000		// 游戏最大的npc数
#define PLAYER_COUNT_MAX			500			// 游戏运行时玩家的最大数
#define EVENT_COUNT_MAX				200			// 事件的最大值
#define PROP_COUNT_MAX				1000			// 道具数量
#define SCENE_COUNT_MAX				2			// 场景的最大数
#define FAMILY_COUNT_MAX			50			// 家族数量
#define ACTION_COUNT_MAX			100			//
#define CLEARING_COUNT_MAX			100			//
#define GANG_COUNT_MAX				100
#define MAIL_COUNT_MAX				100
#define SINGUP_COUNT_MAX			100			//活动报名
#define STORAGE_ROCK_COUNT_MAX		200			//
#define TEAM_COUNT_MAX				5			//队伍的最大数量
#define TOP_COUNT_MAX				200			//排名的最大数量
#define TIME_OBJ_COUNT_MAX			20			//注册时间的obj
#define COUNTDOWN_TIME_COUNT_MAX	10			//和人数相关
#define QUEST_QUESTION_COUNT_MAX	200
#define QUESION_TOP_COUNT_MAX		100			//参与答题排名的玩家
#endif

const int EXPLORER_PLAYER_NUM_MAX	= 100;		//--同屏表人数最大限制--




//无效值定义
#define INT_NULLITY					-1						// 整型的无效值
#define	INVALIDSET					-1					// 无效的值
#define INVALID_TIME				0xFFFFFFFFFFFFFFFFULL			// 无效的时间
#define INVALID_VALUE				-1								// 无效的值
#define INVALID_VALUE64				(int64)0xFFFFFFFFFFFFFFFFULL			//
#define INVALID_UINT64				0xFFFFFFFFFFFFFFFFULL			//
#define INVALID_POSITION			-1					// x,y的无效位置点
#define INVALID_TEMPLATE			-1						// 无效的模板ID
#define INVALID_TABLEID				-1						// 无效的TableID
#define INVALID_PID					0xFFFFFFFFFFFFFFFFULL			// 无效的PID
#define INVALID_UID					0xFFFFFFFFFFFFFFFFULL			// 无效的UID
#define INVALID_SCENEID				0xFFFFFFFFFFFFFFFFULL			// 无效的SceneID
#define INVALID_SKILLID				-1
#define INVALID_QUESTID				-1						// 无效的QuestID
#define INVALID_INQUIRERID			-1						// 无效的InquirerID
#define INVALID_PROPID				0xFFFFFFFFFFFFFFFFULL			// 无效的PropID
#define INVALID_PETID				0xFFFFFFFFFFFFFFFFULL			//无效的PetID
#define INVALID_MAILID				0xFFFFFFFFFFFFFFFFULL			//无效的MailID
#define INVALID_UIPOS				-1					// 无效的UI位置
#define INVALID_EFFECTID			0xFFFFFFFFFFFFFFFFULL			// 无效的效果ID
#define INVALID_BUFFID				-1
#define INVALID_TEAMID      		-1					//无效的TeamID
#define INVALID_QUESTIONID  		-1						//无效的问题ID
#define	INVALID_AUCID				0xFFFFFFFFFFFFFFFFULL			//无效的拍卖ID
#define	INVALID_BUYID				0xFFFFFFFFFFFFFFFFULL			//无效的求购ID
#define INVALID_CLEARINGID			0xFFFFFFFFFFFFFFFFULL			//无效的交易所ID
#define INVALID_CAMPAIGN			0xFFFFFFFFFFFFFFFFULL			//无效的活动ID
#define INVALID_FAMILYID    		-1
#define FAIL						0								// 失败
#define OK							1								// 成功
#define INVALID_ATTRIB_VALUE		-1
#define INVALID_TRSCID				0xFFFFFFFFFFFFFFFFULL			//无效的金币交易ID

//参数定义
#define GAME_WORLD_ROLE_COUNTS		10			// 游戏世界种主角的总数
#define TRANSMIT_NUM_MAX            15          //地图传送标记数量
#define MAX_ALIAS_NAME_LEN  		128
#define MAX_IP_ADD					30			// IP地址的长度
#define MAX_FUN_LEN					256			// 函数长度
#define MAX_INQ_LEN					256			// 对话长度
#define MAX_PATH_LEN				256			// 路径长度
#define MAX_LEVEL1_MEM				5			// 最大副盟主数
#define MAX_LEAGUE_MEM				200			// 行会的最大人数
#define MSG_INFO_MAX				1024		// 消息的最大字数
#define NAME_INFO_MAX				256			// 名称最大的最数
#define PARM_TEMP_MAX				256			// 参数最大的最数
#define STR_MUN_MAX					256			// 数值转换的字符串大小
#define STR_LMUN_MAX				256			// 超大数值转换的字符串大小
#define ATTRIB_NAME_MAX				256			// 属性名城的字符串大小
#define	MAX_ID_NUMBER				512
#define MAX_PROP_PROP				200			// 每个对象上可有做的道具个数
#define MAX_PROP_SKILL				5			// 每个对象上可有最大的技能数
#define MAX_OBJ_ATTRIB_SIZE			1024		// GameObj的属性长度
#define MAX_SCENE_COUNTS			10000		// 每个对象上可有做的道具个数
#define MAX_SCENE_CREATE_POSTS		100			// 一个场景中的出生点的最大数量
#define MAX_SCENE_SKILL				8000		// 场景中存放的skill的最大值
#define MAX_SCENE_CREATE_ID			50			// 场景中出生点的最大数量
#define MAX_SCENE_MAX_CREATE_POST	500			// 一个场景中最多的出生点
#define ATTRIB_INVALID				-1000
#define PERCENT_RATE				100.00	    //属性中百分比类型的属性实际存储数值的倍率
#define MAX_PLAYER_NUM				100000		// 玩家的最大个数
#define MAX_ROLEATTRIB_NUM			1000		// 以前个人物属性 最大为1000
#define MAX_PARTS					5			// 装备部件数
#define MAX_ROLE_PROP				1000		// 每个对象上可有做的道具个数
#define MAX_ROLE_SKILL				200			// 每个对象上可有的技能个数
#define MAX_ROLE_ATTRIB_STR			2000		// role组织的属性字符串的最大长度
#define MAX_MERCHANT_PROP			200			//商人
#define MAX_SCENE_NUM				500			// 场景的最大个数
#define EFFECT_PARAM_MAX			6			// 一个作用的最大参数
#define PERSON_SKILL_COUNT			500			//记录玩家拥有的技能数量
#define GAME_SERVER_MAX_PLAYE		2000		//GameServer玩家的人数上限
#define GM_CMD_MAX				50		// gm命令的最大长度
#define GM_CMD_VALUE_MAX				10		// gm命令中值的最大长度
#define ALLOWABLE_DELAY_TIME_MAX	100			//允许的最大延迟时间（ms）
const UINT PROP_TEMPPARAMCOUNT	=		4;		//道具临时数据存储个数

#define FOLLOW_FLY_DIS		12				//宠物跟随时距离主人的距离

#define MAX_SINGNAME_LEN			400			//个人签名
#define DESIGNATION_COUNT			64			//玩家身上称号数量
#define ROUND_PERSON_FLOWER			200			//鲜花围绕
#define SET_HEADEFFECT_SEAT			 20			//序位
const int NUM_HOTKEYTEACH				=36;			//快捷键教学数量

const int	MAX_BOSS_POINT_COUNT		= 10;			// 刷新BOSS的随机坐标最大数    add by zhangjianli 2011-10-20
const int	MAX_BOSS_POINT_SCRIBE_LEN	= 64;			// 刷出BOSS的所在位置名称最大长度   add by zhangjianli 2011-10-20
const int	MAX_BOSS_DROP_RORP_NAME		= 256;			// 超级BOSS掉落物品名称最大长度	add by zhangjianli 2012-02-08
const int	GLOBAL_BOSS_COUNT_MAX		= 300;			// 全局BOSS最大数量 add by zhangjianli 2011-10-21
#define  KING_RIDEPET_MODEL	8105 //国王专属坐骑模型ID
// 角色相关
const BYTE ROLE_COUNT_MAX			= 1;					// 角色的最大个数
const BYTE USER_NAME_LEN_MAX		= MAX_ALIAS_NAME_LEN;	// 帐户名最大长度
const BYTE ROlE_NAME_LEN_MAX		= 25;					// 角色名最大长度
const BYTE PASSWORD_LEN_MAX			= 35;					// 密码的最大长度
const int  CONFIRMATION_CODE_NUM_MAX				= 1;	//--激活码最大个数--	目前不用此方法，把值调小了 change by zhaoguoze 2011-07-23
const UINT CONFIRMATION_CODE_LEN					= 20;	//--激活码长度--
const UINT CONFIRMATION_CODE_LEN_1					= 10;	//--激活码长度--
const int  CONFIRMATION_CODE_USED_TIMES_MAX		    = 1;	//--一个激活码可用的次数--

#define PLAYER_COMMON_ATTACKID		1			//默认的普通近程物理攻击
#define PLAYER_COMMON_DROWSKILLID	2			//普通远程攻击
#define PLAYER_COMMON_PICKUPSKILL	13			//默认拾取技能
#define PLAYER_COMMON_CAR_ATTACKID	14			//默认的在战车上使用的技能
#define PLAYER_LEVEL_UP_SKILL		10			//人物升级技能
#define FELLOW_LEVEL_UP_SKILL		17			//宠物升级技能

#define SECURITY_PERSON_LEVEL		30			// 财产保护要求的人物级别
#define SECURITY_PERSON_PWD_LEN		10			// 财产保护密码长度
#define PLAYER_DEFAULT_MODELCOLOR   514			//角色默认的遮罩颜色
// 和任务相关的数据
#define TASKNAMELEN	50
#define TASKNOTELEN	256
#define MAXLEAGUECOUNTS				5000		// 一个游戏世界的最多个联盟数
#define MAXLEAGUEMEMBER				5000		// 一个联盟中的最大成员的数量
#define MAXLEAGUENAMELEG			256			// 联盟名字的最大长度
#define MAXLEAGUEINFOLEG			1024		// 联盟介绍信息的最大长度
#define MAX_GAMEWORLD_TEAM			5000		// 游戏中的最大队伍数
#define NAMELENGTH					50	    	// 注册名的长度
#define IDTABLECOULD				5
#define DATADEBUGLEN				4096		// 数据服务器静态框显示的最大的字符的数量
#define	PUBLIC_SCENE_ID				5000		// 公共场景的id

#define BUFF_GUIDON 2027

#define CAR_FARAWAY_DIST 20
#define GET_ARRAY_ITEMNUM(array)	(sizeof(array)/sizeof(*array))

#define AUTOSKILL_MAX_COUNT		5   //自动释放的技能最大数

#define SELFSHOP_GOOD_GROUP 72 // 对应 goodsgroup.csv 表中 "44  72	购买	12	71	0	0" 记录，如果其中72改变，该值要对应修改
struct AutoSkill
{
	int nSkillID;
	int nInterval;

};


// About of Mail
#define MAX_MAIL_TITLE_SIZE		50				// the size of title
#define MAX_MAIL_NOTE_SIZE		1024			// the size of mail note
#define PROPATTRIBCOUNTS		12				// 道具表中的改变属性的数量

#define  STSTE_NUM				500				// 状态数量
#define  Flag_MOD				1000			// 标示系数
#define MAX_SKILL_NUM			20000			// 最打的技能个数
#define FACE_FLAGINDEX			1000			//聊天特效快捷栏索引

#define RED_FLOWERID            10467			//红玫瑰
#define WHITE_FLOWERID          10468			//白玫瑰
#define QIANZHIHEID				10469			//千纸鹤

#define NUM_9_FLOWER			9				//9朵					
#define NUM_99_FLOWER			99				//99朵
#define NUM_365_FLOWER			365				//365
#define NUM_999_FLOWER			999				//999朵

// 装备串
// 装备类型
#define PROP_EQUIT_HD		10			// 装备 头
#define PROP_EQUIT_TK		11			// 装备 衣服
#define PROP_EQUIT_GL		12			// 装备 手
#define PROP_EQUIT_CR		13			// 装备 裤子
#define PROP_EQUIT_FT		14			// 装备 鞋子

#define	EQUITECOUNTS		5
#define EQUITSTRLEN			32

#define MAX_STATE_COUNT		8			//最大的国家数


#define  PASSENGER_NUMBER	5			//最大骑乘数

//AI相关
const int	AUTO_MOVE_POINT_COUNT_MAX	= 20;	//自动寻路npc的最大寻路路点数

const int	COMBIN_DISTANCE =4 ;          //合体的最大距离

//活动相关
#define  ZONE_TRANS_SCENE		0		 //区域传送的地图id
#define  ZONE_AREA_X			1		 //区域传送的x坐标
#define  ZONE_AREA_Y			2		 //区域传送的y坐标
#define  ZONE_CAMPAIGN_INDEX	3        //游戏出生区使用的参数序列号,对应活动id
#define  ZONE_START_INDEX		4		 //游戏出生区，对应活动出生点

#define	 BOMB_TYPE_TRUE			1
#define  BOMB_TYPE_FALSE		2

const int USER_EXT_POINT = 8;			 //账号功能扩展点数量

//////////////////////////////////////////////////////////////////////////
//角色登录方式
enum EPlayerLoginFlag
{
	CHANGE_SERVER,		//跨服传送
	LOGIN_SERVER,		//登陆
};

//角色登出方式
enum EPlayerLogoutFlag
{
	LOGOUT_FLAG_CHANGE_SERVER,		//跨服传送
	LOGOUT_FLAG_LOGOUT_SERVER,		//退出游戏
};

//////////////////////////////////////////////////////////////////////////
// 标准NPC模板定义
const int NPC_TEMPLATE_NEW_BIRTH		= 70;	//新手出生区
const int NPC_TEMPLATE_PEOPLE_REBIRTH	= 71;	//本国重生区
//const int NPC_TEMPLATE_ANAMY_REBIRTH	= 52;	//异国重生区	(废弃)
const int NPC_TEMPLATE_SAFE				= 53;	//绝对安全区
const int NPC_TEMPLATE_FISH				= 54;	//钓鱼区
const int NPC_TEMPLATE_GATHER			= 55;	//采集区
const int NPC_TEMPLATE_MINING			= 56;	//采矿区
const int NPC_TEMPLATE_ELEMENT			= 57;	//元素区
const int NPC_TEMPLATE_CULTURE			= 58;	//养殖区
const int NPC_TEMPLATE_FELLING			= 59;	//伐木区
const int NPC_TEMPLATE_DANCE			= 60;	//跳舞区
const int NPC_TEMPLATE_WUSHU			= 61;   //武术区
const int NPC_TEMPLATE_STALL			= 62;	//摆摊区
const int NPC_TEMPLATE_XIUXING			= 63;	//修行区
const int NPC_TEMPLATE_DAZUO			= 69;	//打坐区
//const int NPC_TEMPLATE_UNGROUND_REBIRTH = 72;	//副本复活区
//const int NPC_TEMPLATE_UNGROUND_BIRTH   = 76;	//副本出生区
//const int NPC_TEMPLATE_GAME_REBIRTH		= 99;	//游戏出生区


//////////////////////////////////////////////////////////////////////////
//--组队相关--

//--队伍的类型--
enum TEAMTYPE
{
	TEAMTYPE_NONE			= 0,		//--无--
	TEAMTYPE_COMMON,					//--普通组队--
	TEAMTYPE_HONOR,						//--荣誉组队--
};

//--队伍中经验分配模式--
enum TEAM_EXP_TYPE
{
	TEAM_EXP_NONE			= 0,		//--无--
	TEAM_EXP_SPECIAL,					//--特殊分配--
	TEAM_EXP_LEVEL,						//--按等级分配--
};

//--队伍中的拾取模式--
enum TEAM_ITEM_TYPE
{
	TEAM_ITEM_NONE			= 0,		//--无--
	TEAM_ITEM_FREE,						//--自由拾取--
	TEAM_ITEM_TURN,						//--轮流拾取--
	TEAM_ITEM_RANDOM,					//--随机拾取--
};

//--队伍的招募模式--
enum TEAM_RECRUIT_TYPE
{
	TEAM_RECRUIT_NONE		= 0,		//--无--
	TEAM_RECRUIT_AUTO,					//--自动招募--
	TEAM_RECRUIT_MANUAL,				//--手动招募--
};


const int	Team_Count_Max					= 6;	//--队伍最大人数--

const int	TEAMCAPTION_ICON				= 1001;	//--队长图标，用于显示--

const int	HONOR_STARE_ICON				= 2;	//--荣誉之星图标，用于显示--

const int	TEAM_HONOR_LEVEL_LIMITE			= 60;	//--荣誉组队的等级限制--

const int	TEAMBUFFERID_NUM				= 15;	//--buffer的个数--

const int	TEAM_SET_POS_TIME				= 5;	//--5s同步一回队友位置--

const float TEAM_EXP_ADDITION_BY_SPECIAL	= 0.1;	//--特殊分配时队伍经验加成，队伍中经验分配模式是特殊分配的时候给其他队友分的经验--

const float TEAM_EXP_ADDITION_BY_LEVEL		= 0.1;	//--等级分配时队伍经验加成，队伍中经验分配模式是等级分配的时候总经验加成--

const int	TEAM_CALL						= 1;	//--组队主叫--
const int	TEAM_CALLED						= 2;	//--组队被叫--
//////////////////////////////////////////////////////////////////////////
// 类型转换
#define MAKESCENE(p)		((CScene*)p)
#define MAKEROLE(p)			((CPlayer*)p)
#define MAKEPROP(p)			((CProp*)p)
#define MAKESKILL(p)		((CSkill*)p)
#define MAKEPLAYER(p)		((CPlayer*)p)
#define MAKENPC(p)			((CSGameNPC*)p)
#define MAKEFELLOW(p)		((CFellowNPC*)p)
#define MAKEBUFF(p)			((CBuffEffect*)p)
#define MAKEBAG(p)			((CBagObj*)p)
#define MAKEPET(p)			((CPet*)p)


//////////////////////////////////////////////////////////////////////////
//自动挂机
enum AI_AUTO
{
	AI_AUTO_NO			= 0,			//未设置自动挂机
	AI_AUTO_SKILL		= 1,			//持续使用技能逻辑
	AI_AUTO_Z			= 2,			//Ctrl+Z挂机
	AI_AUTO_WAITERPET	= 3,			//宠物挂机
	AI_AUTO_LEFT		= 4,			//左键自动攻击
	AI_AUTO_Z_PAUSE		,				//Ctrl+Z暂停
	AI_AUTO_WAITERPET_PAUSE,			//宠物挂机 暂停

	AI_AUTO_COLLECT     = 10,			//精灵采集挂机  by zhao
	AI_AUTO_COLLECT_PAUSE,				//精灵采集挂机暂停	
};

enum AI_TYPE
{
	AI_TYPE_PLAYER	= 0,						//玩家

	AI_TYPE_NPC_FRIENDLY =1,					//友好NPC
	AI_TYPE_MONSTER_ACTIVE = 3,					//主动怪
	AI_TYPE_MONSTER_PASSIVE = 4,				//被动怪
	AI_TYPE_MONSTER_NO_FIGHT,					//傻瓜怪
	AI_TYPE_NPC_CAT_AUTO,						//自动寻路镖车
	AI_TYPE_NPC_CAT_FLOOW,						//跟随玩家
	AI_TYPE_PET_FELLOW,							//玄兽
	AI_TYPE_PET_COMBAT,							//战宠
	AI_TYPE_PET_RID,							//坐骑
	AI_TYPE_PET_ZONE,							//区域
	AI_TYPE_SET_STALL,							//摆摊车
	AI_TYPE_TRAP,								//陷阱
	AI_TYPE_AURA,								//光环
	AI_TYPE_MONSTER_QUEST_TARGET_FIRST,         //任务刷新怪目标优先
	AI_TYPE_PORTAL,								//传送门
	AI_TYPE_NPC_FRIENDLY_CANATTACK,             //受到攻击后能还击的友好NPC
	AI_TYPE_SKILL_ZONE,							//带技能的区域
	AI_TYPE_MARRY_CARRIAGE,						//婚车逻辑
	AI_TYPE_LANDMINE,							//地雷
	AI_TYPE_SPIRIT,								//精灵逻辑
	AI_TYPE_BOSS,								//BOSS AI
	AI_TYPE_CHANGE_AI_GROUP,                    //转换阵营NPC AI
	AI_TYPE_SOLDIER,							//守卫
	AI_TYPE_CHARIOT,							//家族战车
	AI_TYPE_MONSTER_QUEST_PLAYER_FIRST,			//任务刷新怪攻击玩家优先
	AI_TYPE_CHANGE_SCENE,						//换场景触发器
	AI_TYPE_TRIGGER_NPC_PROP,					//游戏中的触发类道具npc
	AI_TYPE_TRIGGER_NPC_PROP_MULTI,				//游戏中的触发类道具npc，群体
	AI_TYPE_LANDMINE_FALSE,						//假地雷
	AI_TYPE_PROTECTED_TARGET,					//防御类型目标npc
	AI_TYPE_QUEST_AUTOZONE,						//任务自动触发区域
	AI_TYPE_AUTODRIVE,							//自动驾驶的观光AI
	AI_TYPE_SCRIPT,								//脚本npc
	AI_TYPE_QUESTFOLLOW,						//任务跟随单位
	AI_TYPE_MONSTER_ACTIVE_PLACE,				//定点主动怪
	AI_TYPE_CAR_CAMPAIGN_PERSON,				//活动个人镖车
	AI_TYPE_CAR_CAMPAIGN_FAMILY,				//活动家族镖车
	AI_TYPE_CAR_NPC,							//镖车所属npc
	AI_TYPE_PROP_QUEST_NPC,						//道具任务刷新怪
	AI_TYPE_GOD		= 100,						//上帝

};


//////////////////////////////////////////////////////////////////////////////
//PK
//--注：要和玩家的PK状态（enum PK_STATUS）区分开--
enum PK_TYPE
{
	PK_TYPE_ALL			= 0, //全体模式
	PK_TYPE_PEACE,			//和平模式
	PK_TYPE_STATE,			//国家模式
	PK_TYPE_UNION,			//盟国模式
	PK_TYPE_GANG,			//帮会模式
	PK_TYPE_FAMIY,			//家族模式
	PK_TYPE_EVIL,			//善恶模式
	PK_TYPE_ENEMY,			//仇人模式		（已废弃）
	PK_TYPE_CAMP,			//阵营模式
	PK_TYPE_STATEWAR,		//国战模式	add by zhangjianli 2012-02-17
	PK_TYPE_GANG_CANOT_SWITCH,	//强制帮会模式(不可手动切换)
	PK_TYPE_FAMILY_CANOT_SWITCH,//强制家族模式(不可手动切换)
	PK_TYPE_PROTECTED,			//保护模式（不可手动切换）
};

//--PK状态-- add by zhaoguoze 2011-03-16
//--用来标示玩家身上的PK状态，作为计算PK惩罚和奖励的依据--
//--注：要和PK模式（enum PK_TYPE）区分开--
enum PK_STATUS
{
	PK_STATUS_ORDINARY						= 0,	//普通					：白名
	PK_STATUS_HERO,									//英雄					：绿名(保护)
	PK_STATUS_WELLDOER,								//善人					：白名
	PK_STATUS_BADDIE,								//恶人					：橘红
	PK_STATUS_DEMON,								//恶魔					：红名
	PK_STATUS_DEMON_HEAD,							//魔头					：深红
	PK_STATUS_MALICIOUS,							//恶意攻击				：灰名
	PK_STATUS_CHANGE,								//即将恢复到普通状态	：闪烁
};

//--PK阵营（PK模式为阵营模式时，所对应的阵营）--
//--具体的阵营类型只是为了把阵营区分开，没有其他含义--
enum PK_CAMP
{
	PK_CAMP_INVALID = -1,	//--无效的PK阵营--
	PK_CAMP_A = 0,			//--阵营A--
	PK_CAMP_B,				//--阵营B--
	PK_CAMP_C,				//--阵营C--
};

//镖车投保标志
enum Car_TouBao_Flag
{
	CTF_Invalid = -1,
	CTF_Gold,
	CTF_Purple,
};

//玩家隐身状态 add by zhangjianli 2012-9-17
enum Player_Stealth
{
	PLAYER_UNSTEALTH = 0,	//没有隐身
	PLAYER_STEALTH,			//隐身
};

//支付系统银子存储类型
enum Storage_SilverType
{
	Storage_SilverType_PersonCar = 5,	//王城运镖押金
	Storage_SilverType_FamilyCar	,	//家族镖车押金
	Storage_SilverType_EscortSignUp ,	//镖局竞标
	Storage_SilverType_EscortRunning ,	//镖局运营资金
	Storage_SilverType_SealQuest     ,	//封印任务
	Storage_SilverType_Mail,  //邮件金币存储
    Storage_SilverType_Bank,  //银号存储
    Storage_SilverType_Sell, //求购行存储
	Storage_SilverType_End,		//金币存储结束，添加定义请在此项之前
};


//#define     RED_NAME_DROP_ODDS  30					//红名掉落道具几率  改为读表 by fan
const int   PUSH_PRISON_BASE_ODDS			= 3;	//杀人进监狱基础几率(百分比)

const int	PRISON_TRANS_ID					= 1501;	//监狱区传送id
const int	PRISON_REALEASE_AREA_ID			= 1101;	//释放区传送id

const int	PK_VALUE_MAX					= 240;	//--PK值上线-- change by zhangjianli 2012-01-05

const int	PK_VALUE_TYPE_HERO				= 240;	//--英雄状态临界值，这个值以上为英雄状态，包含此值--
const int	PK_VALUE_TYPE_WELLDOER			= 100;	//--善人状态临界值，这个值以上为善人状态，包含此值--
const int	PK_VALUE_TYPE_ORDINARY			= 0;	//--普通状态临界值，这个值以上为一般状态，包含此值--
const int	PK_VALUE_TYPE_BADDIE			= -50;	//--恶人状态临界值，这个值以上为恶人状态，不包含此值--
const int	PK_VALUE_TYPE_DEMON				= -100;	//--恶魔状态临界值，这个值以上为恶魔状态，不包含此值；一下的为魔头状态，包含此值--
const int	PK_VALUE_TYPE_CHANGE			= -1;	//--即将恢复到普通状态临界值，这个值以上为一般状态，包含此值--
const int	PK_VALUE_TYPE_MALICIOUS			= 0;	//--恶意攻击状态值--

const int	PK_VALUE_TO_PRISON				= -100;	//--PK值小于此值强制送进监狱--

const int	PK_VALUE_PLAYER					= 10;	//--恶意杀一个人，PK值的默认惩罚值--
const int	PK_VALUE_PRIVATE_CAT			= 20;	//--恶意借一辆个人镖车，PK值的默认惩罚值--

const int	PK_PUNISH_TIMES					= 2;	//--恶意杀害英雄（绿名）以上PK状态的玩家，将受到加倍惩罚--

//--每过一定时间时间（秒）加一次PK值--
//--单位：秒--
const int	PK_ADD_VALUE_TIME				= 720;	//--每次增加PK值时间间隔由720s（1小时恢复5点）-- change by zhangjianli 2012-7-21

//--每次增加的PK值的数量--
//--注：此值不能大于各个状态临界值的最大公约数--
const int	PK_VALUE_ONCE_ADD_NUM			= 1;

//--恶意攻击状态持续时间--
//--单位：秒--
//--注	：恶意攻击状态时间不做存盘处理，在这段时间内下线（或换服），再上线会重新计时，所以此时间不宜过长--
const int	PK_TIME_MALICIOUS_STATUE		= 120;

const int	COMMON_GAME_OVER_CD_TIME		= 300;	//--普通死亡界面自动安全复活的时间（秒）--

const int	ROLE_REVIVE_TIMES_MAX			= 10;	//原地和满状态复活不增加金钱的最大次数 add by zhangjianli 2011-10-12

const int	PK_CAR_PROTECTED_LEVEL			= 50;	//--王城运镖的镖车保护等级--

const int	ACTIVE_ENERGY_TASKID			= 4706;	//--激活活力值任务ID，用于判断活力值是否激活等与活力值有关系的功能-- add by zhangjianli 2012-7-5
const int	FELLOWREFINERY_DAYTIMES			= 10;	//--玩家每天可以炼化珍兽的最大数量-- add by zhangjianli 2012-7-13

enum Campaign_PK_TYPE
{
	Campaign_PUNISH_HORTATION				=0,		//活动pk惩罚，奖励
	Campaign_NO_PUNISH_NO_HORTATION,				//活动pk不惩罚，不奖励
	Campaign_NO_PUNISH_HORTATION,					//活动pk不惩罚，奖励
	Campaign_PUNISH_NO_HORTATION,					//活动pk惩罚不奖励
};


//--角色复活类型-- by zhaoguoze 2011-01-13
enum RELIVE_TYPE
{
	RELIVE_TYPE_TOTOWN						= 0,	//--安全复活--
	RELIVE_TYPE_INSITU,								//--原地复活--
	RELIVE_TYPE_FULLSTATUS,							//--满状态复活--
};

//--死亡界面的类型--
enum GAME_OVER_DLG_TYPE
{
	GAME_OVER_DLG_TYPE_COMMON = 0,					//--普通--
	GAME_OVER_DLG_TYPE_FAMILY_CHALLENGE,			//--家族挑战赛--
	GAME_OVER_DLG_TYPE_GUO_CE,						//--国策--
	GAME_OVER_DLG_TYPE_CANNOT_INSITU,				//--禁止原地复活--
};


//召唤相关定义
enum SummonRange   //召唤范围
{
	SummonRange_Person = 0, //召唤个人
	SummonRange_Team,		//召唤队伍
	SummonRange_Family,		//召唤家族
	SummonRange_Gang,		//召唤帮会
	SummonRange_State,		//国家召唤
	SummonRange_King,		//国王召唤帮主
	SummonRange_Brothers,	//结拜召唤
	SummonRange_World,		//世界
};

enum SummonType						//客户端类型标记
{
	SummonType_Common = 0,			//普通召唤
	SummonType_Quest,				//任务召唤
	SummonType_UnderGround,			//副本召唤
	SummonType_Teammate,			//队友召唤
	SummonType_Border,				//边境召唤

	SummonType_Special = 100,			// 特殊召唤起始位 
	SummonType_Special_Escort,			//家族镖局召唤
	SummonType_Special_GangFight,		//帮会夺城战召唤
	SummonType_Special_FamilyChallenge,	//家族挑战赛召唤
	SummonType_Special_EscortRunning,	//家族镖局发送闪框
	SummonType_Special_StateWarAttack,	//国战进攻方召唤
	SummonType_Special_StateWarDefence,	//国战防守方召唤
	SummonType_Special_StateWarDanger,	//国战大元帅生命危急召唤
	SummonType_Special_ServerShutDown,	//停服通知
	SummonType_Special_FamilyJuYi,		//聚义召唤
	SummonType_Special_FamilyBoss,		//家族BOSS召唤
	SummonType_Special_FamilyEscort,	//家族运镖
	SummonType_Special_ApplyFamilyScene,//申请家族庄园提醒，临时家族倒计时
};

//--传送道具类型（回城卷、随机符、）--add by zhangjianli 2012-3-1
enum TransPropType
{
	TransProp_HuiCheng_Single = 0,			//--单体回城卷--
	TransProp_Huicheng_Colony,				//--群体回城卷--
	TransProp_ShunYi_Single,				//--单体瞬移卷轴（不限地图随机符）--
	TransProp_ShunYi_Colony,				//--群体瞬移卷轴--
	TransProp_ShunYi_Map,					//--单体瞬移卷轴道具效果（限本国随机符）
	TransProp_JiYi,							//--记忆卷轴--
	TransProp_ShiKong,						//--时空通令--
};

//--技能延迟所需的数据--
struct SSkillDelayInfo
{
public:
	SSkillDelayInfo(){Init();}
	//--skill		：技能ID--
	//--target		：目标ID--
	//--prop		：道具ID--
	//--AttackPoint	：对点攻击的位置--
	//--TriggerTime	：技能开始释放的时间（毫秒）--
	//--DelayTime	：技能招式延迟时间（毫秒）--
	SSkillDelayInfo( SkillID skill, PersonID target, const POINT& AttackPoint, PropID prop, TMV TriggerTime, TMV DelayTime )
	{
		m_nSkillID			 = skill;
		m_nTargetID			 = target;
		m_nPropID			 = prop;
		m_ptAttackPoint.x	 = AttackPoint.x;
		m_ptAttackPoint.y	 = AttackPoint.y;
		m_nSkillTriggerTime	 = TriggerTime;
		m_nSkillDelayTime	 = DelayTime;
	}
	void Init()
	{
		m_nSkillID			 = INVALID_SKILLID;
		m_nTargetID			 = INVALID_PID;
		m_nPropID			 = INVALID_PROPID;
		m_ptAttackPoint.x	 = INVALID_VALUE;
		m_ptAttackPoint.y	 = INVALID_VALUE;
		m_nSkillTriggerTime	 = INVALID_TIME;
		m_nSkillDelayTime	 = INVALID_TIME;
	}
	inline SSkillDelayInfo& operator = (const SSkillDelayInfo& M)
	{
		m_nSkillID			 = M.m_nSkillID;
		m_nTargetID			 = M.m_nTargetID;
		m_nPropID			 = M.m_nPropID;
		m_ptAttackPoint.x	 = M.m_ptAttackPoint.x;
		m_ptAttackPoint.y	 = M.m_ptAttackPoint.y;
		m_nSkillTriggerTime	 = M.m_nSkillTriggerTime;
		m_nSkillDelayTime	 = M.m_nSkillDelayTime;
		return *this;
	}
public:
	SkillID				m_nSkillID;			//--技能ID--
	PersonID			m_nTargetID;		//--目标ID--
	PropID				m_nPropID;			//--道具ID--
	POINT				m_ptAttackPoint;	//--攻击的位置--
	TMV					m_nSkillTriggerTime;//--技能开始时间（毫秒）--
	TMV					m_nSkillDelayTime;	//--技能延迟时间（毫秒）--
};

////////////////////////////////////////////////////////////////////////////////////


enum MOVING_TYPE
{
	MOVING_TYPE_RUN 						=0,		//跑步
	MOVING_TYPE_WALK,								//走路
	MOVING_TYPE_FORCE_WALK,							//强制走
	MOVING_TYPE_FORCE_RUN,							//强制跑
};

enum CASTING_STOP_TYPE
{
	CASTING_STOP_TYPE_FINISH				= 0,	// 完成施法结束（自然结束）
	CASTING_STOP_TYPE_IDLE,							// 站立使施法状态结束（打断）
	CASTING_STOP_TYPE_MOVE,							// 移动使施法状态结束（打断）
};

//--吟唱技能类型--
const int	SINGING_SKILL_TYPE_COMMON		= 1 << 0;// 普通（对应ActionStatus_Casting状态，用于一般拾取读条，开礼包读条，职业技能读条）
const int	SINGING_SKILL_TYPE_STEAL		= 1 << 1;// 偷砖（对应StealStatus_Steal状态，该状态可使用其他技能，用于偷砖读条，膜拜读条，插旗读条等）
const int	SINGING_SKILL_TYPE_GETONCAR		= 1 << 2;// 上战车（对应ComplexStatus_GetOnCar状态，该状态可使用其他技能，用于上战车读条）


const int	ROLE_RAGE_NUM_MAX				= 1000;	//--角色的怒气值上线--
const int	RAGE_ONCE_NUM_ADD				= 2;	//--杀一个怪所得的怒气值--

const int	PLAYER_AUTO_UP_LEVEL			= 50;	//--玩家自动升级的级别上限（过了这个级别就要手动选择升级）--

const int	PLAYER_EXP_TOPLIMIT_TIMES		= 3;	//--玩家最大累积经验值倍数（与当前级别下的升级经验相比）--

//////////////////////////////////////////////////////////////////////////
//五行
enum WuXing_Type
{
	WuXing_Type_Jin     = 1,
	WuXing_Type_Mu,
	WuXing_Type_Shui,
	WuXing_Type_Huo,
	WuXing_Type_Tu,
};

enum AI_CURRENT_STATUS
{
	AI_CURRENT_ATTACKALL = 1,					//全体攻击
	AI_CURRENT_ATTACK = 2,						//攻击
	AI_CURRENT_DEFEND = 3,						//防守
	AI_CURRENT_ATTACKSELECT = 4,				//选择攻击
	AI_CURRENT_REST	= 5,						//休息
	AI_CURRENT_STAY = 6,						//停留
};

//活动数量
#define CAMPAIGN_COUNT 10

#define FAMILY_PASSENGER_NUM 6

//聊天群数量
#define GROUP_COUNT		5

//时间定义
const UINT TIME_1Min   = 60;			//1分钟
const UINT TIME_2Min   = 120;			//2分钟
const UINT TIME_5Min   = 300;			//5分钟
const UINT TIME_10Min  = 600;			//10分钟
const UINT TIME_1Hour  = 3600;			//1小时
const UINT TIME_24Hour = 86400;			//24小时
const UINT TIME_48Hour = 172800;		//48小时保护时间
const UINT TIME_3Day   = 259200;        //3天
const UINT TIME_7Day   = 604800;        //7天

//奇遇时间
const int CAR_VENTURE_MIN				= 30;
const int CAR_VENTURE_MAX				= 120;

const int CONMMON_CD_TIME				= 1200; //公共cd的时间（毫秒）


//允许的客户端与服务器位置偏差 tile
const int POSITION_VERIFY				= 5;


//--NPC攻击时的呆滞时间（受到攻击时的第一次反击和追击到玩家后的第一次攻击需要有呆滞时间）--
const int WANT_ATTACK_TIME				= 500;	//攻击呆滞时间（毫秒）

//--NPC追击时的呆滞时间（发现目标时需要有有一定的呆滞时间）--
const int WANT_CHASE_TIME				= 300;	//追击呆滞时间（毫秒）

const TMV INVALID_WANT_TIME				= 0;	//无效的呆滞时间值

const int RADIUS_NPC_CREATE_POS_RANDOM	= 2;	//--NPC刷新点的随机半径--

const int NPC_AUTO_MOVE_RANGE			= 3;	//--NPC自动移动的范围--

//--普通NPC的最大追击范围（NPC刷新点与目标的距离）--
//--注：如果目标与NPC刷新点的距离大于此值，则视为同场景传送，NPC不再追击，并处于逻辑Idle状态；
//		如果传送的距离小于这个值，NPC还会超目标方向追去，当大于自身属性的追击范围时GoHome
const int CHASE_RANGE_MAX				= 50;


const int VALUE_ENLARGE_TIMES			= 1000;
const int PROP_CLASS_NUM				= 4;	//道具级别段个数
const int PROP_STAR_NUM					= 15;	//装备打星个数

const int ROLE_RECOVER_TIME_INTERVAL	= 10;	//--角色恢复逻辑时间间隔（秒）-- add by zhaoguoze 2011-05-21

const int EFFECT_HP_HAD_LITTLE_LIMIT	= 30;	//--触发效果(Event_Combat_Effect_HpHadLittle)的生命百分比--

const int RADIUS_PLAYER_RELIVE_POS_RAND = 4;	//--玩家出生点的随机半径--

const int EFFECT_ADD_PRACTISEGESTE_RADIX = 10000;//效果中增加历练功勋的基数 add by zhangjianli 2012-7-30

//////////////////////////////////////////////////////////////////////////
// TemplateID Rule
// 0 0 0 0 0000 0000 0000
// | | |
// | | |
// | | +-
// | +-
// +-0: NPC 1:Prop
//////////////////////////////////////////////////////////////////////////
inline bool IsPropByTemplateID(TemplateID ID)	{return( ID & 0x8000 ) == 0x8000; }
inline bool IsNPCByTemplateID(TemplateID ID)	{return( ID & 0x8000 ) == 0x0000; }

//////////////////////////////////////////////////////////////////////////
// ID生成规则 函数接口

#define ROLE_ID_WORLD		10000000000000000ULL			//World
#define ROLE_ID_SERVER		100000000000000ULL				//Server
#define ROLE_ID_TYPE		10000000000000ULL
#define ROLE_ID_TEMPLATE	10000000ULL
#define FELLOW_ID_HEAD		1000000LL
#define ROLE_ID_FAMILY_GANG	1000000							//FamilyID GangID为int型

inline PersonID MakeNPCPID(TemplateID TID,int nServerID,int nIndex)
{
	return nServerID * ROLE_ID_SERVER + 1 * ROLE_ID_TYPE + TID * ROLE_ID_TEMPLATE + nIndex;
}

inline PersonID MakeGodPID()
{
	return 3 * ROLE_ID_TYPE;
}

inline TemplateID GetNPCTemplate(PersonID PID)
{
	return PID % ROLE_ID_TYPE / ROLE_ID_TEMPLATE;
}

inline UINT GetNPCIndex(PersonID PID/*,TemplateID TID*/)
{
	return PID % ROLE_ID_TEMPLATE;
}

//使用次数Key
inline int64 MakeUseCountKeys(int nTemplateID, int nType, int nTimeType)
{
	return nTemplateID * 10000000000 + nType * 10000 + nTimeType;
}

//////////////////////////////////////////////////////////////////////////
// 存盘ID

//PlayerPID
inline PersonID MakePlayerPID (int nWorldID, int nIndex = 0)
{
	return nWorldID * ROLE_ID_WORLD + nIndex;
}
//FamilyCarPID
inline PersonID MakeFamilyCarPID(int nWorldID, TemplateID nTID, int nIndex = 0)
{
	return nWorldID * ROLE_ID_WORLD + 2 * ROLE_ID_TYPE + nTID * ROLE_ID_TEMPLATE + nIndex;
}

inline UINT GetFamilyCarIndex(PersonID nFamilyCarID)
{
	return nFamilyCarID % ROLE_ID_TEMPLATE;
}

//玄兽PID
inline PersonID MakeFellowPID(int nWorldID, int nServerID ,int nIndex = 0)
{
	return nWorldID * ROLE_ID_WORLD + 2 * ROLE_ID_TYPE  + nServerID * ROLE_ID_SERVER + nIndex;
}
//PropID
inline PropID MakePropID(int nWorldID, int nServerID ,int nIndex = 0)
{
	return nWorldID * ROLE_ID_WORLD + nServerID * ROLE_ID_SERVER + nIndex;
}
//MailID
inline MailID MakeMailID(int nWorldID, int nIndex = 0)
{
	return nWorldID * ROLE_ID_WORLD + nIndex;
}
// FamilyID
inline int	MakeFamilyID(int nWorldID,int nIndex = 0)
{
	return nWorldID * ROLE_ID_FAMILY_GANG + nIndex;
}
//////////////////////////////////////////////////////////////////////////
//GangID
inline int MakeGangID(int nWorldID,int nIndex = 0)
{
	return nWorldID * ROLE_ID_FAMILY_GANG + nIndex;
}
// PayID
inline TrscID MakePayID(int64 nServerID ,int64 nWorldID,int64 nIndex)
{
	return (nServerID * 1000000000000LL + nWorldID * 10000000000LL +nIndex);
}
// AuctionID（合服不保留）
inline AuctionID MakeAuctionID(int64 nServerID, int64 nIndex)
{
	return (nServerID * 1000000000000000LL + nIndex);
}
// BuyID 求购ID（合服不保留）
inline BuyID MakeBuyID(int64 nServerID, int64 nIndex)
{
	return (nServerID * 1000000000000000LL + nIndex);
}
//TeamID（不存盘）
inline int MakeTeamID(int nServerID,int nIndex)
{
	return (nServerID * 1000000 + nIndex);
}
//////////////////////////////////////////////////////////////////////////
////结拜的ID（无用，废弃）del by zhangjianli 2012-9-27
//inline int MakeGayID(int nServerID,int nIndex)
//{
//	return (nServerID * 1000000 + nIndex);
//}
//废弃，无用接口 del by zhangjianli 2012-9-27
//inline ClearingID MakeClearingID(int64 nServerID, int64 nIndex)
//{
//	return (nServerID * 1000000000000000LL + nIndex);
//}

/*
//活动
inline CampaignID MakeCampaignID(int64 nCampaignTemplate, int64 nIndex)
{
return (nCampaignTemplate * 1000000000000000ULL + nIndex);
}
*/
//倒计时ID计算
inline int64 MakeQuestCountDownID(uint nQuestID)
{
	return nQuestID * 100000ULL;
}

inline int64 MakeCampaignCountDownID(uint nCampaignID,uint index)
{
	return nCampaignID * 1000  + index; 
}

//////////////////////////////////////////////////////////////////////////
//Position
inline unsigned int MakePosition(unsigned int x,unsigned int y)
{
	return (x|(y<<16));
}

inline unsigned int GetPosX(unsigned int Position)
{
	return  (0x0000ffff & Position) ;
}

inline unsigned int GetPosY(unsigned int Position)
{
	return (Position>>16);
}

//////////////////////////////////////////////////////////////////////////
//	场景ID 生成规则
//////////////////////////////////////////////////////////////////////////

#define SceneIDServerIndex		100000LL
#define SceneIDTemplateIndex	100000000LL
#define SceneIDStateIndex		10000000000000LL

inline SCENEID MakeSceneID(int nStateID, int nTemplateID, int nServerID, int index)
{
	return (int64)(nStateID * SceneIDStateIndex + nTemplateID * SceneIDTemplateIndex + nServerID * SceneIDServerIndex + index);
}

inline int GetStateBySceneID(SCENEID id)
{
	return id / SceneIDStateIndex;
}

inline int GetTemplateBySceneID(SCENEID id)
{
	return (id % SceneIDStateIndex) / SceneIDTemplateIndex;
}

inline int GetServerBySceneID(SCENEID id)
{
	return (id % SceneIDTemplateIndex) / SceneIDServerIndex;
}

/*
//Scene
inline SCENEID MakeSceneID(int64 nSceneTemplateID,int nServerID, int64 nIndex)
{
	//忽略nIndex最高16位
	return  nSceneTemplateID * SceneIDBase + nServerID * SceneIDServerIndex + nIndex;
}

inline int	GetTemplateIDFromSceneID(SCENEID ID)
{
	return ID / SceneIDBase;
}

inline int  GetStateIDFromSceneID(SCENEID ID)
{
	return (GetTemplateIDFromSceneID(ID))/1000;
}

inline int GetServerIDFromSceneID(SCENEID ID)
{
	return (ID % SceneIDBase) / SceneIDServerIndex;
}

inline int GetStateIDFromSceneTemplate(TemplateID nSceneTemplateID)
{
	return (nSceneTemplateID/1000);
}

inline int	GetSceneTemplateBySceneTemplate(TemplateID nSceneTemplateID)
{
	return (nSceneTemplateID%1000);
}

inline int	SetSceneTemplateByServer(TemplateID nSceneTemplateID, int nServerID)
{
	return nSceneTemplateID%1000 + nServerID*1000;
}

inline int GetCountryIDByServerID(int ID)
{
	return (ID/10);
}*/

//////////////////////////////////////////////////////////////////////////////////////////
// scene & explorer
#define		ZONETILEX_SIZE		20					//每个Zone X方向的tile个数
#define		ZONETILEY_SIZE		20  	            //每个Zone y方向的tile个数
#define		EXPLORER_IN_DIST	(ZONETILEX_SIZE + (ZONETILEX_SIZE / 2))

enum PLAYERJOB				//任务职业限制
{
	PLAYERJOB_NOLIMIT	=-1 ,			//无限制
	PLAYERJOB_NONE		=0	,			//无职业		
	PLAYERJOB_WUSHI			,			//武师
	PLAYERJOB_SHUSHI		,			//术士
	PLAYERJOB_SHESHOU		,			//射手
	PLAYERJOB_DAOSHI		,			//道士
	PLAYERJOB_YISHI			,			//药师
};

///////////////////////////////////////////////////////////////////////////////////////////
// Skill

//--SkillID站位简图--
//-------------------
//	1  1  01  01
//	|  |  |   |
//	|  |  | Level
//	|  | Mode
//  | Ramify(包括职业分支，怒气，心法)
// Class
//-------------------

const int SKILL_NUM_PLACE_CLASS		= 100000;	//--技能ID中派系标识位，站一位
const int SKILL_NUM_PLACE_RAMIFY	= 10000;	//--技能ID中分枝标识位，站一位
const int SKILL_NUM_PLACE_MODE		= 100;		//--技能ID中类别标识位，站两位
const int SKILL_NUM_PLACE_LEVEL		= 1;		//--技能ID中级别标识位，站两位


//--技能分枝位标识--
enum SKILL_NUM_RAMIFY_FLAG
{
	SKILL_NUM_RAMIFY_FLAG_NONE			= 0,		//--无--
	SKILL_NUM_RAMIFY_FLAG_1				= 1,		//--第一分枝--
	SKILL_NUM_RAMIFY_FLAG_2				= 2,		//--第二分枝--
	SKILL_NUM_RAMIFY_FLAG_RAGE			= 5,		//--怒气技能标识--
	SKILL_NUM_RAMIFY_FLAG_XINFA			= 6,		//--心法技能标识--
};

//--根据技能ID判断是不是职业技能--
inline BOOL G_CheckIsTreeSkillByID( SkillID nSkillID )
{
	return ( (nSkillID / SKILL_NUM_PLACE_CLASS <= 5) && (nSkillID / SKILL_NUM_PLACE_CLASS > 0) );
}

//--判断是不是怒气技能--change by zhangjianli 2011-11-08
inline BOOL G_IsRageSkill( SkillID nSkillID )
{
	//return ( (nSkillID % SKILL_NUM_PLACE_CLASS / SKILL_NUM_PLACE_RAMIFY) == SKILL_NUM_RAMIFY_FLAG_RAGE );
	int nClass = nSkillID / SKILL_NUM_PLACE_CLASS;
	int nRamify = nSkillID % SKILL_NUM_PLACE_CLASS / SKILL_NUM_PLACE_RAMIFY;
	return ( (nClass == 0) && (nRamify == SKILL_NUM_RAMIFY_FLAG_RAGE) );
}

//--判断是不是心法技能--change by zhangjianli 2011-11-08
inline BOOL G_IsXinFaSkill( SkillID nSkillID )
{
	//return ( (nSkillID % SKILL_NUM_PLACE_CLASS / SKILL_NUM_PLACE_RAMIFY) == SKILL_NUM_RAMIFY_FLAG_XINFA );
	int nClass = nSkillID / SKILL_NUM_PLACE_CLASS;
	int nRamify = nSkillID % SKILL_NUM_PLACE_CLASS / SKILL_NUM_PLACE_RAMIFY;
	return ( (nClass == 0) && (nRamify == SKILL_NUM_RAMIFY_FLAG_XINFA) );
}

//--得到技能的Level--
inline int G_MakeLevelBySkillID(SkillID nSkillID)
{
	return nSkillID % SKILL_NUM_PLACE_MODE / SKILL_NUM_PLACE_LEVEL;
}

//--得到技能模板,及不包含技能等级的信息--
inline int G_MakeModeBySkillID(SkillID nSkillID)
{
	return (nSkillID / SKILL_NUM_PLACE_MODE) * SKILL_NUM_PLACE_MODE;
}

//--得到技能的派系--
inline int G_MakeClassBySkillID(SkillID nSkillID)
{
	return nSkillID / SKILL_NUM_PLACE_CLASS;
}

//--得到技能的分枝-- change by zhangjianli 2011-11-08
inline int G_MakeRamifyBySkillID(SkillID nSkillID)
{
	//int nRamify = nSkillID % SKILL_NUM_PLACE_CLASS / SKILL_NUM_PLACE_RAMIFY;
	//return (( nRamify == SKILL_NUM_RAMIFY_FLAG_RAGE || nRamify == SKILL_NUM_RAMIFY_FLAG_XINFA ) ? SKILL_NUM_RAMIFY_FLAG_NONE : nRamify);	//--如果分枝位是怒气或心法标识，则返回无 -- add by zhaoguoze 2011-03-23
	
	// 如果是职业技能，才返回分支，不是就返回无
	if ( G_CheckIsTreeSkillByID(nSkillID) )				
		return nSkillID % SKILL_NUM_PLACE_CLASS / SKILL_NUM_PLACE_RAMIFY;
	else
		return SKILL_NUM_RAMIFY_FLAG_NONE;
}

//--取SkillID的中间两位--
inline int G_MakeSkillNode(SkillID nSkillID)
{
	return nSkillID % SKILL_NUM_PLACE_RAMIFY / SKILL_NUM_PLACE_MODE;
}


//--构造一个技能ID--
//--nClass	：派系--
//--nRamify	：分枝 enum SKILL_NUM_RAMIFY_FLAG--
//--nMode	：类别--
//--nLevel	：等级--
inline int G_MakeSkillID( int nClass, int nRamify, int nMode, int nLevel )
{
	return ( nClass * SKILL_NUM_PLACE_CLASS + nRamify * SKILL_NUM_PLACE_RAMIFY + nMode * SKILL_NUM_PLACE_MODE + nLevel * SKILL_NUM_PLACE_LEVEL );
}

//--构造一个技能ID，仅改变ID的派系位--
//--nSkillID：要改变的技能ID--
//--nClass	：派系--
inline int G_MakeSkillIDByClass( SkillID nSkillID ,int nClass )
{
	return ( nClass * SKILL_NUM_PLACE_CLASS + nSkillID % SKILL_NUM_PLACE_CLASS );
}

//--构造一个技能ID，仅改变ID的分枝位--
//--nSkillID：要改变的技能ID--
//--nRamify	：分枝 enum SKILL_NUM_RAMIFY_FLAG--
inline int G_MakeSkillIDByRamify( SkillID nSkillID ,int nRamify )
{
	return ( nSkillID / SKILL_NUM_PLACE_CLASS * SKILL_NUM_PLACE_CLASS + nRamify * SKILL_NUM_PLACE_RAMIFY + nSkillID % SKILL_NUM_PLACE_RAMIFY );
}

//--构造一个技能ID，仅改变ID的类别位--
//--nSkillID：要改变的技能ID--
//--nMode	：类别--
inline int G_MakeSkillIDByMode( SkillID nSkillID ,int nMode )
{
	return ( nSkillID / SKILL_NUM_PLACE_RAMIFY * SKILL_NUM_PLACE_RAMIFY + nMode * SKILL_NUM_PLACE_MODE + nSkillID % SKILL_NUM_PLACE_MODE );
}

//--构造一个技能ID，仅改变ID的等级位--
//--nSkillID：要改变的技能ID--
//--nLevel	：等级--
inline int G_MakeSkillIDByLevel( SkillID nSkillID ,int nLevel )
{
	return ( nSkillID / SKILL_NUM_PLACE_MODE * SKILL_NUM_PLACE_MODE + nLevel * SKILL_NUM_PLACE_LEVEL + nSkillID % SKILL_NUM_PLACE_LEVEL );
}

const int SKILL_EFFECT_MAX			= 10;
const int SKILL_EFFECT_INTIME		= 5;//--需及时处理的Effect，站Effect数组的后5个--
const int SKILL_BUFF_MAX			= 5;
const int SKILL_TARGET_MAX          = 5;

const int SKILL_LEVEL_TREE_MAX		= 14;										//--职业技能最大等级--change by zhangjianli 2011-12-08
const int SKILL_LEVEL_XINFA_MAX		= 71;										//--心决技能最大等级--add by zhangjianli 2011-12-08
const int PRESKILL_LEVEL1			= 5;
const int PRESKILL_LEVEL2			= 6;

const int SKILLTREE_COUNT_MAX		= 5;										//--最大技能树数量--
const int SKILLMODE_COUNT_MAX		= 50;										//--一个派系的技能最大种类--
//#define SKILLNOTE_COUNT_MAX			(SKILLMODE_COUNT_MAX * SKILL_LEVEL_TREE_MAX)//--Node的最大值随技能种类和技能级别的最大值改变，NodeMax = ModeMax * SKILL_MAX_LEVEL--  暂时没用，注释掉 change by zhangjianli 2011-12-08

const int ATTACK_TARGER_NUM_MAX		= 100;	//--群攻可攻击的最大人数--

//////////////////////////////////////////////////////////////////////////
//
//活动进度标记
enum Mission_Status
{
	Mission_Status_Null = 0,		//未开始未报名
	Mission_Status_Regist,			//报名中
	Mission_Status_WaitForStart,	//报名结束未开始
	Mission_Status_Doing,			//进行中
	Mission_Status_Over,			//已结束
};

//活动参与者类型
enum Mission_Joiner
{
	Mission_Joiner_Null = 0,
	Mission_Joiner_Player,
	Mission_Joiner_Team,
	Mission_Joiner_Family,
	Mission_Joiner_Gang,
	Mission_Joiner_Country,
};
//////////////////////////////////////////////////////////////////////////
//
//新的EffectID操作函数	By David 2009-2-16
#define EFFECT_VALUE					1000000ULL							//效果的属性值
#define EFFECT_OBJ_TYPE					1000000000ULL						//效果的执行者类型	 对应值：enum ENUM_EFFECT_OBJ_TYPE
#define EFFECT_RANDOM					10000000000ULL						//效果的概率
#define	EFFECT_KEY						10000000000000ULL					//效果Key
#define EFFECT_FLAG						1000000000000000000ULL				//+/-标记		 0:+	1:-
#define EFFECT_ACTIVE_FLAG				10000000000000000000ULL				//是否激活的标志 0:激活 1:非激活

//--OnEffect函数执行返回值--
enum EffectReturn
{
	Effect_False	= 0,	//--错误--
	Effect_Succeed,			//--效果执行成功--
	Effect_RandFail,		//--随机失败--
};

inline int GetEffectValue(EffectID nEffectID)
{
	nEffectID = nEffectID % EFFECT_ACTIVE_FLAG;
	if(nEffectID/EFFECT_FLAG)
		return -(nEffectID % EFFECT_VALUE);
	else
		return nEffectID % EFFECT_VALUE;
}

inline int GetEffectRandom(EffectID nEffectID)
{
	return ((nEffectID % EFFECT_ACTIVE_FLAG) / EFFECT_RANDOM) % 1000;
}

inline int GetEffectKey(EffectID nEffectID)
{
	return ((nEffectID % EFFECT_ACTIVE_FLAG) % EFFECT_FLAG) / EFFECT_KEY;
}

//--获取效果执行者类型--
//--返回：效果执行者 enum ENUM_EFFECT_OBJ_TYPE--
inline int GetEffectObjType(EffectID nEffectID)
{
	return nEffectID % EFFECT_RANDOM / EFFECT_OBJ_TYPE;
}

inline EffectID SetEffectID(int nKey,int nRandom,int nValue,int active=0,int object = 0)
{
	EffectID nEffectID;
	if(nValue>0)
		nEffectID = (nKey * EFFECT_KEY ) + (nRandom * EFFECT_RANDOM ) + nValue;
	else
		nEffectID = (1 * EFFECT_FLAG) + (nKey * EFFECT_KEY ) + (nRandom * EFFECT_RANDOM ) + nValue;
	if(active == 1)
		nEffectID = EFFECT_ACTIVE_FLAG + nEffectID;
	if ( object > 0 )
		nEffectID = object * EFFECT_OBJ_TYPE + nEffectID;
	return nEffectID;
}

inline BOOL IsActiveEffect(EffectID nEffectID)
{
	return !(nEffectID / EFFECT_ACTIVE_FLAG);
}

inline EffectID SetActiveEffect(EffectID nEffectID)
{
	if(IsActiveEffect(nEffectID))
		return nEffectID;
	if( nEffectID / EFFECT_ACTIVE_FLAG )
		nEffectID -= EFFECT_ACTIVE_FLAG;
	return nEffectID;
}

inline EffectID UnsetActiveEffect(EffectID nEffectID)
{
	if(!IsActiveEffect(nEffectID))
		return nEffectID;
	if(!(nEffectID / EFFECT_ACTIVE_FLAG))
		nEffectID += EFFECT_ACTIVE_FLAG;
	return nEffectID;
}


//////////////////////////////////////////////////////////////////////////
// 效果项的定义
// 10000以上为对别人属性值的改变 ( 作用对象为母标着 )
// 10000以下为对自己属性值的改变 ( 作用对象为使用者 )
#define EFFECT_LIMIT		10000

// 道具相关
const int EQUIP_EFFECT_MAX		= 15;	//道具的效果
const int ZHANHUN_EFFECT_MAX	= 5;	//战魂链效果
const int LIANCHENG_EFFECT_MAX	= 5;	//连城诀效果
const int ACTIVE_EFFECT_MAX		= 5;	//激活效果的个数
const int BIND_EFFECT_MAX		= 1;	//重绑效果个数
//const int PROP_SKILL_MAX		= 5;	//
const int EQUIP_POS_MAX			= 10;	//单个道具装备位置数量

// 任务相关
#define QUEST_TYPE_MAX  6				// 可选择物品与任务目标数的最大值
#define QUEST_TYPE_MAX_PROP 10		//道具奖励的最大值
//背包相关的
inline int GetBagByUIPost(UIPos post){return post/1000;}
inline int GetIndexInBagByUIPost(UIPos post){return post%1000;}
inline int GetUIPost(int CBag,int Post){return (CBag*1000 + Post);}

//摆摊相关
const int STALL_PROP_NUM = 48;		//摊位最大道具数
const int STALL_NAME_LEN = 64;		//摊位名称长度
const int STALL_NOTE_LEN = 128;		//摊位喊话长度


//道具所在UI界面
enum Prop_UIPos_Type
{
	Prop_UIPos_Null = 0,
	Prop_UIPos_Bag  = 1,			//背包
	Prop_UIPos_Equip= 2,			//装备栏
	Prop_UIPos_Compose = 3,			//打造合成
	Prop_UIPos_Exchange = 4,		//交换
	Prop_UIPos_Stall = 5,			//摆摊
	Prop_UIPos_Mail = 6,			//邮件
	Prop_UIPos_AUCTION = 7,			//拍卖
	Prop_UIPos_FamilyBoss = 8,		//家族boss
};

const int NPC_FALL_MONEY = 10;	//NPC掉落金钱概率
const int64 WORDCHAT      = 50000;   //世界聊天费用
const int64 COLORWORDCHAT = 250000;  //彩世聊天费用


//货币类型
enum Currency_Type
{
	Currency_Gold = 0,			//金子
	Currency_GoldBind,			//绑定金
	Currency_Silver,			//银子
	Currency_SilverBind,		//绑定银
	Currency_StashGold,			//信用金子
	Currency_StashGoldBind,		//绑定信用金子
	Currency_StashSilver,		//信用银子(现在用作家族工资货币)
	Currency_StashSilverBind,	//绑定信用银子(现在用作每日消费上限)
	Currency_Prop,				//以物换物
	Currency_GongXun,			//功勋货币-历练功勋
	Currency_HeroIsland,		//点将台积分
};

enum CostType
{
	COST_INVALID = -1,
	COST_PLAYERBUSINESS = 0,                //交易
	COST_NPCBUSINESS,						//NPC交易
	COST_SALE,								//拍卖
	COST_MAIL,								//邮件
	COST_REFORM,							//装备改造
	COST_SYSTEM,							//系统消费
	COST_AUCTION,							//竞拍
	COST_BUY,								//求购
	COST_BANK,								//票号
	COST_STALL,								//摆摊
	COST_ORDINARYDRIVER,                    //普通车夫
	COST_CROSS_BORDER_TRANSMISSION,         //跨国传送
	COST_RELIVE_INSITU,                     //原地复活
	COST_RELIVE_FULLSTATUS,                 //满状态复活
	COST_SKILL_LEAN,                        //学习技能
	COST_CHAT,                              //世界/彩世聊天
	COST_FAMILY,                            //家族
	COST_MARRIAGE,                          //结婚
	COST_USEPROP,                           //使用道具
	COST_SUMMON,                            //召唤
	COST_Dragon,                            //龙币兑换
	COST_HEROTOP,                           //国家英雄排行榜
	COST_WAGE,                              //工资
	COST_SIGNUP,                           //报名
	COST_TREATDRINK,						//家族食神请客喝酒
	COST_COLORCHAT,							//彩市喊话
	COST_WORLDCHAT,							//世界喊话
	COST_EQUIPCOMPOSE,						//打造合成
	COST_WARCARREPAIR,						//战车修理
	COST_WARCARBUILD,						//战车打造
	COST_EQUIP_REQAIR,						//装备修理
	COST_CHANGE_STATE,						//移民
	COST_MOUNTSTOSTRENGTHEN,				//坐骑强化
	COST_PETSKILL_METAMORPHOSIS,			//宠物技能幻化
	COST_PETUPSTAR,							//宠物升星
	COST_PET_REBIRTH,						//宠物重生
};

enum CostInOrOut
{
	COST_IN = 0,				//获得
	COST_OUT,					//使用
};

enum MonitorItem_Type
{
	eMonitorItem_Invalid = -1,
	eMonitorItem_Prop,				// 道具
	eMonitorItem_End,
};

enum MonitorItem_OprType
{
	eMonitorItem_OperInvalid = -1,
	eMonitorItem_OperAdd,	//添加
	eMonitorItem_OperSub,	//减
	eMonitorItem_OperClear,	//清
	eMonitorItem_OperEnd,
};
//级别段
enum Level_Class
{
	Level_Class_One = 1,		//1-90
	Level_Class_Two,			//90-120
	Level_Class_Three,			//120-140
	Level_Class_Four,			//140-160
};

inline int GetLevelClass(int level)
{
	if(level <= 90)
		return Level_Class_One;
	else if(level <= 120)
		return Level_Class_Two;
	else if(level <= 140)
		return Level_Class_Three;
	else if(level <= 160)
		return Level_Class_Four;
	return INVALID_VALUE;
}

//财产保护
const int PROTECT_EQUIP         = 1;	   //已绑定紫色装备、金色装备和角色
const int PROTECT_STORAGE       = 1<<1;    //第二、三仓库
const int PROTECT_BANK          = 1<<2;	   //票号账户
const int PROTECT_GIFT          = 1<<3;    //钱庄老板处领取礼品
const int PROTECT_MAILANDSALE   = 1<<4;	   //交易、邮件和拍卖
const int PROTECT_PET           = 1<<5;    //珍兽保护
const int PROTECT_FAMILYANDGANG = 1<<6;	   //解散家族或转让族长、解散帮会或转让帮主
const int PROTECT_MEMBER        = 1<<7;    //家族剔除族员、帮会剔除家族

inline bool IsProtectEquip(const int value)				{return ( value & PROTECT_EQUIP )		  == PROTECT_EQUIP;}
inline bool IsProtectStorage(const int value)			{return ( value & PROTECT_STORAGE )		  == PROTECT_STORAGE;}
inline bool IsProtectBank(const int value)			    {return ( value & PROTECT_BANK )		  == PROTECT_BANK;}
inline bool IsProtectGift(const int value)			    {return ( value & PROTECT_GIFT )		  == PROTECT_GIFT;}
inline bool IsProtectMailAndSale(const int value)		{return ( value & PROTECT_MAILANDSALE )   == PROTECT_MAILANDSALE;}
inline bool IsProtectPet(const int value)				{return ( value & PROTECT_PET )			  == PROTECT_PET;}
inline bool IsProtectFamilyAndGang(const int value)     {return ( value & PROTECT_FAMILYANDGANG ) == PROTECT_FAMILYANDGANG;}
inline bool IsProtectMember(const int value)			{return ( value & PROTECT_MEMBER )		  == PROTECT_MEMBER;}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
#define 		COLOR_BLACK			L"00";	//黑
#define 		COLOR_CARMINE		L"01"	//深红色
#define 		COLOR_GREEN			L"02"	//绿色
#define 		COLOR_OLIVE			L"03"	//橄榄色
#define 		COLOR_NAVY			L"04"	//藏青色
#define 		COLOR_PURPLE		L"05"	//紫
#define 		COLOR_CYAN			L"06"	//青
#define 		COLOR_GRAY			L"07"	//灰
#define 		COLOR_ARGENTINE		L"08"	//银
#define 		COLOR_RED			L"09"	//红
#define 		COLOR_POTENTIAL		L"10"	//浅绿
#define 		COLOR_YELLOW		L"11"	//黄
#define 		COLOR_BLUE			L"12"	//兰
#define 		COLOR_MAUVE			L"13"	//紫红
#define 		COLOR_AZURY			L"14"	//浅蓝
#define 		COLOR_WHITE			L"15"	//白
#define 		COLOR_SKY_BLUE		L"16"	//淡蓝
#define 		COLOR_SKY_YELLOW	L"17"	//淡黄
#define 		COLOR_PEA_GREEN		L"18"	//淡绿

//////////////////////////////////////////////////////////////////////////
// Inquirer
//////////////////////////////////////////////////////////////////////////

//NPC 的颜色
#define		NPC_WHITE	2
#define		NPC_GREEN	3
#define		NPC_BLUE	4
#define		NPC_ZI		5
#define		NPC_GOLD	6

//用于直接打开界面
enum Dialog_Type
{
	Dialog_Invalid		= 0,			//无效类型
	Dialog_Mail,						//邮件
	Dialog_Auction,						//拍卖行
	Dialog_Stall,						//摆摊
	Dialog_PropMake,					//装备制造
	Dialog_PropUpgrade,					//装备升级
	Dialog_PropCompose,					//装备合成
	Dialog_Clearing,					//票据交易
	Dialog_Business,					//道具买卖
	Dialog_ChangeCountry,		        // 换国家
	Dialog_CreateFamily,                //创建家族
	Dialog_EnterFamilyScene,            //进入家族庄园
	Dialog_BuildFamilyScene,            //建立家族庄园
	Dialog_FamilyTankMager,             //管理家族战车
	Dialog_QueryFamilyCredit,           //查看家族贡献度
	Dialog_SetFamilyMoney,              //捐献家族资金
	Dialog_PublicFamilyQuest,           //发布家族公告
	Dialog_SummonFamilyBoss,            //召唤家族Boss
	Dialog_UpdateFamilyLevel,           //家族升级
	Dialog_UpdateFamilyReadMe,          //家族升级公告
	Dialog_LearnFamilySkill,            //学习家族技能
	Dialog_StudyFamilySkill,            //研究家族技能
	Dialog_GetFamilyTank,               //领用家族战车
	Dialog_FamilyTankPermission,        // 设置家族战车使用权限
	Dialog_CreateFamilyTank,            //打造家族战车
	Dialog_CreateGang,                  //创建帮会
	Dialog_EnterGangScene,              //进入帮会庄园
	Dialog_BuildGangScene,              //家里帮会庄园
	Dialog_GangTankMager,               //管理帮会战车
	Dialog_QueryGangCredit,             //察看帮会贡献度
	Dialog_SetGangMoney,                //捐献帮会资金
	Dialog_PublicGangQuest,             //发布帮会公告
	Dialog_SummonGangBoss,              //召唤帮会Boss
	Dialog_UpdateGangLevel,             //帮会升级
	Dialog_UpdateGangReadMe,            //帮会升级公告
	Dialog_LearnGangSkill,              //学习帮会技能
	Dialog_StudyGangSkill,              //研究帮会技能
	Dialog_GetGangTank,                 //领用帮会战车
	Dialog_GangTankPermission,          //设置帮会战车使用权限
	Dialog_CreateGangTank,              //打造帮会战车
	Dialog_Warehouse,					//打开仓库界面
	Dialog_Wikipedia,                   //打开百科界面 参数 拼在 nText (xxxx)
	Dialog_FamilyBuilding,				//打开家族建筑列表
	Dialog_Bank,					    //打开票号（银行）界面
	Dialog_LookingForFamily,			//申请加入家族
	Dialog_AppointStatePower,			//任务国家官职
	//Dialog_DiceCommon,				//打开骰子 
	Dialog_FamilyWage1,                 //族员工资情况
	Dialog_FamilyWage2,                 //族长分配工资
	Dialog_FamilyShop,                  //家族商店
	Dialog_WarCar_Bulid,				//战车打造
	Dialog_JieBai_Notice,				//结拜功能预告
	Dialog_Shengshui_Bang,				//打开圣水排行榜
	Dialog_Quest_Track,					//任务追踪界面
	Dialog_Sworn,						//结拜
	Dialog_SwornEnter,					//结拜称号输入
	Dialog_AcceptPropQuest,				//物品任务界面
        Dialog_Buy,                         //求购行界面
	Dialog_DragonConvertSilver,			//龙币兑换界面
	Dialog_ChangeState,					//移民
};

enum INQUIRER_TYPE
{
	INQUIRER_TYPE_INVALID = -1,						// 无效的类型
	INQUIRER_TYPE_ISSUE_QUEST = 0,					// 发布任务
	INQUIRER_TYPE_COMPLETE_QUEST,					// 完成任务
	INQUIRER_TYPE_COMPLETE_QUEST_LUA,   			// 脚本完成任务
	INQUIRER_TYPE_NOCOMPLETE_QUEST,					// 完成任务中
	INQUIRER_TYPE_FUNC,								// 功能对话
	INQUIRER_TYPE_CHAT,								// 闲聊对话
	INQUIRER_TYPE_EVENT,							// 触发事件对话
	INQUIRER_TYPE_MERCHANT,							// 商品交易
	INQUIRER_TYPE_CHANGECOUNTRY,					// 换国家
	INQUIRER_TYPE_MAKE_PROP,						// 装备制造
	INQUIRER_TYPE_ENHANCE_PROP,						// 装备提升
	INQUIRER_TYPE_COMPOSE_PROP,						// 装备合成
	INQUIRER_TYPE_EPLISTLE,							// 读信
	INQUIRER_TYPE_ENTERN_FAMILY_SCENE,				// 进入家族庄园
	INQUIRER_TYPE_BUILD_FAMILY,						// 建立家族
	INQUIRER_TYPE_BUILD_FAMILY_SCENE,				// 建立家族庄园
	INQUIRER_TYPE_FAMILY_TANK_MAGER,				// 管理家族战车
	INQUIRER_TYPE_QUERY_FAMILY_CREDIT,				// 查询家族贡献度
	INQUIRER_TYPE_SET_FAMILY_MONEY,					// 捐献家族资金
	INQUIRER_TYPE_SET_FAMILY_MONEY_5,				// 5锭
	INQUIRER_TYPE_SET_FAMILY_MONEY_10,				// 10锭
	INQUIRER_TYPE_PUBLIC_FAMILY_QUEST,				// 发布家族任务
	INQUIRER_TYPE_SUMMON_FAMILY_BOSS,				// 召唤家族boss
	INQUIRER_TYPE_UPDATE_FAMILY,					// 家族升级
	INQUIRER_TYPE_UPDATE_FAMILY_README,				// 家族升级介绍
	INQUIRER_TYPE_LEARN_FAMILY_SKILL,				// 学习家族技能
	INQUIRER_TYPE_STUDY_FAMILY_SKILL,				// 研究家族技能
	INQUIRER_TYPE_FAMILY_TANK_GET,      			//领用家族战车
	INQUIRER_TYPE_FAMILY_TANK_PERMISSION,			//设置家族战车使用权限
	INQUIRER_TYPE_FAMILY_TANK_CREATE,   			//打造家族战车
	INQUIRER_TYPE_TRANS,							//传送
	INQUIRER_TYPE_SKILLLOG,             			//技能选择

	//2010-6-3 by ma
	INQUIRER_TYPE_ISSUE_CHILD_DIALOG,				//接受任务前子对话
	INQUIRER_TYPE_COMPLETE_CHILD_DIALOG,			//完成任务前子对话

	//新手任务 INQUIRER_TYPE
	INQUIRER_TYPE_CHOISE_JOB_WUSHU,     			//武术系
	INQUIRER_TYPE_CHOISE_JOB_FASHU,     			//法术系
	INQUIRER_TYPE_CHOISE_JOB_SHESHU,    			//射术系
	INQUIRER_TYPE_CHOISE_JOB_YAOSHU,    			//妖术系
	INQUIRER_TYPE_CHOISE_JOB_XIANSHU,   			//仙术系

	INQUIRER_TYPE_WISEMAM,							//智者答题
	INQUIRER_TYPE_COMPETITION,						//活动答题
	INQUIRER_TYPE_STALL,							//摆摊
	INQUIRER_TYPE_MAIL,								//邮件
	INQUIRER_TYPE_BUILD_GANG,						//建立帮会,
	INQUIRER_TYPE_AUCTION,							//拍卖
	INQUIRER_TYPE_LOOK_PRISON_TIME,                 //监狱时间
	INQUIRER_TYPE_LEARN_SELECT,						//学习采集
	INQUIRER_TYPE_LEARN_MINING,						//学习采矿
	INQUIRER_TYPE_LEARN_BREED,						//学习养殖
	INQUIRER_TYPE_LEARN_CUT,						//学习伐木
	INQUIRER_TYPE_LEARN_ELEMENTS,					//学习元素提炼
	INQUIRER_TYPE_LEARN_FUN,						//鼓乐
	INQUIRER_TYPE_LEARN_HUNT,						//狩猎
	INQUIRER_TYPE_LEARN_PRACTICE,					//修行
	INQUIRER_TYPE_LEARN_FISH,						//钓鱼
	INQUIRER_TYPE_TRANSREEL,						//传送卷轴
	INQUIRER_TYPE_CAR_INFOR,                        //镖车信息
	INQUIRER_TYPE_GET_FAMILY_VALUE,					//获取家族贡献度
	INQUIRER_TYPE_GET_STATE_NUMBER,					//获取国家在线人数
	INQUIRER_TYPE_GET_GANG_VALUE,					//获取帮会贡献度
	INQUIRER_TYPE_GET_STATE_POWER,					//查询国王统治力
	INQUIRER_TYPE_GET_PLAYER_DOUBLETIME,			//查询当前剩余双倍时间
	INQUIRER_TYPE_Middle_DIALOG,					//完成中间对话
	INQUIRER_TYPE_NocompleteChild_DIALOG,			//未完成任务时子对话
	INQUIRER_TYPE_Middle_DIALOG_Main,				//中间对话主对话


	INQUIRER_TYPE_QUEST_COMMIT,						//提交任务子对话		//add by lfy 2012.9.1
	INQUIRER_TYPE_QUEST_ACCEPT,						//接受任务子对话
	INQUIRER_TYPE_OPENDIALOG,						//打开界面			

	//任务文本
	INQUIRER_TYPE_QUEST_MAIN_INQUIRER=200,			//主请求
	INQUIRER_TYPE_QUEST_CHILD_INQUIRER,				//子请求
	INQUIRER_TYPE_CUSTOM_INQUIRER,					//自定义文本请求
	INQUIRER_TYPE_LEVEL_LIMIT,						//任务等级未到
	INQUIRER_TYPE_CONTINUEQUESTION,					//继续答题

	INQUIRER_TYPE_CAMPAIGNQUEST_ISSUE,				//活动任务发布
	INQUIRER_TYPE_CAMPAIGNQUEST_COMPLETED,			//活动任务完成
	INQUIRER_TYPE_ACTIVITY_NPCTALK,					//活动竖版对话界面
	//打开窗口
	INQUIRER_TYPE_OPEN_DIALOG=210,					//统一的打开窗口

	//传送柱
	INQUIRER_TYPE_BORDER_DIALOG = 230,					//边境传送柱
	INQUIRER_TYPE_BORDER_CHILD,						//边境传送柱子对话
	INQUIRER_TYPE_BORDER_CARCHILD,					//边境传送柱战车子对话

	INQUIRER_TYPE_GONGXUN_EXP=1000,					//功勋换经验

};
/**************************************************************************
**							答题
***************************************************************************/
enum QST_TYPE
{
	QST_TYPE_INVALID  =0,
	QST_TYPE_QUEST,					//任务答题
	QST_TYPE_COMPETITION,			//活动竞赛答题
};
#define  QUESTION_STAR_NUM         3     //固定幸运星数量
#define  QUESTION_STAR_MAX         5     //最大幸运星数量
#define  QUESTION_STAR_PRIZE       2     //奖励幸运星数量
#define  QUESTION_ACTIVE_SEC	   5    //特效时间



#define  QUESTION_BEFORE_TIME      30    //答题活动开始前等待时间
#define  QUESTION_ASK_TIME_SEC     15    //答题时间
#define  QUESTION_READ_TIME_SEC    10    //读题时间

#define  QUESTION_ASK_TIME_WAIT    5     //答案公布对错和刷新时间
#define  QUESTIONTOP 20					 //名次
#define  QUESTION_TOP_ADD			1
#define  QUESTION_TOP_POINT			2
#define  QUESTION_TOP_SORT			3
#define  QUESTION_TOP_SEND			4

//////////////////////////////////////////////////////////////////////////
// State Define
//////////////////////////////////////////////////////////////////////////
#define STATEID_PROPUPDATEQUALITY_COUNT  5		//道具提升品质时,使用的国家ID可能性从1-7改成1-5. by zhupf 2011.1.28
enum STATEID_DEFINE
{
	STATEID_ZHONG	= 0,		//中立
	STATEID_SHU,				//楼兰
	STATEID_HAN,				//辽
	STATEID_TANG,				//西夏
	STATEID_JIN,				//金
	STATEID_ZHOU,				//大理
	STATE_COUNT_MAX,
};

//-----------------------------------------------------------------------------------
#define STATE_COUNT_MAX				5			//国家数组大小
#define STATE_NAME_MAX_LEN			64

//////////////////////////////////////////////////////////////////////////
// Scene Define
//////////////////////////////////////////////////////////////////////////
enum Scene_TemplateID
{
	Scene_DaMingFu		= 1201,				//大名府
	Scene_YeYunDu		= 1202,				//野云渡
	Scene_CuiPingShan	= 1203,				//翠屏山
	Scene_ChiSongLin	= 1204,				//赤松林
	Scene_LongHuShan	= 1205,				//龙虎山
	Scene_CuiPingMiLin	= 1206,				//翠屏密林
	Scene_FamilyScene	= 2201,				//家族地图
};

//////////////////////////////////////////////////////////////////////////
//AIGroup //  [4/13/2010] 此aigroup用于阵营的判定（主要是可否攻击和对话的判定）
//////////////////////////////////////////////////////////////////////////
enum AIGroupType
{
	AIGroup_Type_State_Friend			= 1,		//本国家友好NPC,可对话
	AIGroup_Type_Team_Friend			= 2,		//本队伍友好NPC
	AIGroup_Type_Family_Friend			= 3,		//本家族友好NPC
	AIGroup_Type_Gang_Friend			= 4,		//本帮会友好NPC
	AIGroup_Type_All_Friend				= 5,		//对所有人友好，可对话
	AIGroup_Type_Master_Friend			= 6,		//对主人或召唤者友好
	AIGroup_Type_Function_NPC			= 7,        //功能npc，不能对话
	AIGroup_Type_UState_Friend			= 8,		//本国及盟国友好友好NPC
	AIGroup_Type_UFunction_NPC			= 9,		//功能npc，不能对话(只对盟国和本国友好)
	AIGroup_Type_All_Friend_StateTalk	= 10,		//只与本国对话，对所有人友好
	AIGroup_Type_All_Friend_UStateTalk	= 11,		//只与本国、盟国对话，对所有人友好
	AIGroup_Type_All_Friend_UnTalk		= 12,		//对所有人友好，不可对话
	AIGroup_Type_State_Friend_UnTalk	= 13,		//本国家友好NPC,不可对话
	AIGroup_Type_Monster				= 1000,		//敌人
	AIGroup_Type_Player					= 10000,	//玩家
};


//////////////////////////////////////////////////////////////////////////
//	社会关系Flag    已废弃 
//////////////////////////////////////////////////////////////////////////
enum RELATION_FLAG_BIT
{
	RELATION_FLAG_BIT_SELF		= (1<<0),			//自己
	RELATION_FLAG_BIT_FRIEND	= (1<<1),			//朋友
	RELATION_FLAG_BIT_SPOUSE	= (1<<2),			//配偶
	RELATION_FLAG_BIT_ENEMY		= (1<<3),			//仇人
	RELATION_FLAG_BIT_PARTY		= (1<<4),			//队友
	RELATION_FLAG_BIT_MASTER	= (1<<5),			//师傅
	RELATION_FLAG_BIT_PRENTICE	= (1<<6),			//徒弟
	RELATION_FLAG_BIT_PET		= (1<<7),			//宠物

	RELATION_FLAG_BIT_KIN		= (1<<8),			//家族
	RELATION_FLAG_BIT_FACTION	= (1<<9),			//公会
	RELATION_FLAG_BIT_STATE		= (1<<10),			//国家
	RELATION_FLAG_BIT_FOREIGN	= (1<<11),			//异国


	RELATION_FLAG_BIT_HOSTILE	= (1<<20),			//敌对

};

//////////////////////////////////////////////////////////////////////////
// 离线指令
//////////////////////////////////////////////////////////////////////////

enum OfflineCmdType
{
	//个人关系相关
	OFFLINE_CMD_NULL = 0,
	OFFLINE_CMD_PRIVATE_DELETE_FRIENDLEVEL,		//在线删除好友  离线通知好友级别 
	OFFLINE_CMD_DELETEROLE_PRIVATE_FRIENDLEVEL,	//删除角色      离线通知好友级别
	
	//家族相关
	OFFLINE_CMD_FAMILY_DISMISS,				//解散家族
	OFFLINE_CMD_FAMILY_AUTO_DISMISS,		//家族自动解散
	OFFLINE_CMD_FAMILY_POWER_APPOINT,		//任命
	OFFLINE_CMD_FAMILY_POWER_FIRE,			//解除
	OFFLINE_CMD_FAMILY_BEFIREOUT,
	OFFLINE_CMD_FAMILY_PAYOFF,				//发工资

	//帮会相关
	OFFLINE_CMD_GANG_POWER_APPOINT,
	OFFLINE_CMD_GANG_POWER_FIRE,
	OFFLINE_CMD_GANG_DISMISS,				//帮会被解散
	OFFLINE_CMD_GANG_REMOVEFAMILY,			//开除出帮

	//国家相关
	OFFLINE_CMD_STATE_POWER_APPOINT,
	OFFLINE_CMD_STATE_POWER_FIRE,
	OFFLINE_CMD_KINGDOWN_AS_RULE,			//统治力降为0国王下台

};

#define INT64_PARAM_COUNT	3
#define INT_PARAM_COUNT		3

//////////////////////////////////////////////////////////////////////////
// 聊天频道
//////////////////////////////////////////////////////////////////////////
enum EChannel
{
	ESYSTEMMsg = 0,
	EFriendMsg=1,
	EGangMsg=2,
	EFamilyMsg=3,
	EProvinceMsg=4,
	ECityMsg=5,
	EWorldMsg = 6,
	EStateMsg = 7,
	EAreaMsg=8,
	ETeamMsg = 9,
	EExplorerMsg=10,
	EPVPMsg = 11,
	EColorWorldMsg =12,
};

//////////////////////////////////////////////////////////////////////////
// 技能武器限制类型
//////////////////////////////////////////////////////////////////////////
enum SKILL_WEAPEN_RESTRICT
{
	SKILL_WEAPEN_RESTRICT_SWORD			= (1<<0),		//刀	//双刀
	SKILL_WEAPEN_RESTRICT_AX			= (1<<1),		//斧	//法杖
	SKILL_WEAPEN_RESTRICT_BOWN			= (1<<2),		//弓	//弓
	SKILL_WEAPEN_RESTRICT_CROSS			= (1<<3),		//弩	//法剑
	SKILL_WEAPEN_RESTRICT_FUCHEN		= (1<<4),		//拂尘	//双扇
	SKILL_WEAPEN_RESTRICT_MAGIC			= (1<<5),		//法器
	SKILL_WEAPEN_RESTRICT_SHIELD		= (1<<6),		//盾牌
	SKILL_WEAPEN_RESTRICT_ARROW			= (1<<7),		//箭
	SKILL_WEAPEN_RESTRICT_CHARM			= (1<<8),		//符咒
	SKILL_WEAPEN_RESTRICT_SWORD_DOUBLE	= (1<<9),		//双手刀
	SKILL_WEAPEN_RESTRICT_HAMMER_DOUBLE	=(1<<10),		//双手锤
	SKILL_WEAPEN_RESTRICT_MAGIC_STAFF	= (1<<11),		//法杖
	SKILL_WEAPEN_RESTRICT_MAGIC_ORB		= (1<<12),		//宝珠
	SKILL_WEAPEN_RESTRICT_FAN			= (1<<13),		//扇
	SKILL_WEAPEN_RESTRICT_RUYI			= (1<<14),		//如意
	SKILL_WEAPEN_RESTRICT_AX_DOUBLE		= (1<<15),		//双手斧
	SKILL_WEAPEN_RESTRICT_JI_DOUBLE		= (1<<16),		//双手戬
	SKILL_WEAPEN_RESTRICT_GLOVE			= (1<<17),		//万能手套
	SKILL_WEAPEN_RESTRICT_FISH			= (1<<18),		//鱼竿

};

//////////////////////////////////////////////////////////////////////////
// Lua_Type
//////////////////////////////////////////////////////////////////////////
enum
{
	Lua_Type_NPC	 = 0,			//NPC
	Lua_Type_Scene,					//场景
	Lua_Type_Skill,					//Skill
	Lua_Type_Prop,
	Lua_Type_Effect,
	Lua_Type_Buffer,
	Lua_Type_Quest,
};
//////////////////////////////////////////////////////////////////////////
//  Drag_Type
//////////////////////////////////////////////////////////////////////////
enum Drag_Type
{
	Drag_Type_Null		= 0,
	Drag_Type_Prop		= 1,
	Drag_Type_Skill		= 2,
	Drag_Type_Template	= 3,	//道具模板
	Drag_Type_Shortcut	= 4,	//快捷栏
	Drag_Type_Pet		= 5,			//宠物
	Drag_Type_Face		= 6,		//图片
};

//////////////////////////////////////////////////////////////////////////
//	Prop
//////////////////////////////////////////////////////////////////////////
enum Prop_Quality
{
	Prop_Quality_White = 0,	//品质对应：白   ChenXY   添加批注 。有时间 最好更改命名  2011/6/21
	Prop_Quality_Green = 1,			  //绿 
	Prop_Quality_Blue,				  //蓝
	Prop_Quality_Purple,			  // 紫			// 枚举名称已重新命名,与品质已经对应  by zlm 2011.9.5
	Prop_Quality_Gold,				  //金
	Prop_Quality_PerfectGold,		  //完美金
	Prop_Quality_LegendGold,		  //传说金
};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Target
//////////////////////////////////////////////////////////////////////////
enum Target_Group
{
	Target_Hostile,				// 敌对目标
	Target_Friendly,			// 友方目标
	Target_State,				// 本国友方
	Target_Faction,				// 帮派
	Target_Kin,					// 家族
	Target_Party,				// 队伍

	Target_Couple,				// 夫妻
	Target_Master,				// 师傅
	Target_Prentice,			// 徒弟

	Target_Pet,					// 宠物
	Target_Self,				// 自己
	Target_ExecptSelf,			// 非自己友方

	Target_All,					// 全部
};

//////////////////////////////////////////////////////////////////////////
// ServerInfo
class  CServerInfo
{
public:
	CServerInfo(){};
	~CServerInfo(){};

	inline void SetID(int nID){m_nID = nID;}
	inline void SetType(int nType){m_nType = nType;}
	inline void SetPort(int nPort){m_nPort = nPort;}
	inline void SetIP(char* szIP){if(szIP){strcpy(m_szIP, szIP);}}

	inline int ID(){return m_nID;}
	inline int Type(){return m_nType;}
	inline int Port(){return m_nPort;}
	inline char* IP(){return m_szIP;}

protected:
	int		m_nID;
	int		m_nType;
	int		m_nPort;
	char	m_szIP[25];
};
//////////////////////////////////////////////////////////////////////////
enum Trigger_Type
{
	Trigger_Type_Immediate	= 0,	//立即触发
	Trigger_Type_Use,				//使用触发
	Trigger_Type_Equip,				//装备触发
	Trigger_Type_Event,				//事件触发
};



const UINT	BagSlot_Size			=	10;		// 可装备背包数量
const UINT  EquipBag_Size			=	300;	// 装备栏的总位置数
const UINT  DefaultBag_Size			=	48;		// 默认背包的大小
const UINT  DefaultBank_Size 		=	48;		//初始银行大小
const UINT  LionBag_Size 			=	2;		//初始舞狮背包大小
const UINT  CarBag_Size 			=	3;		//初始镖车道具背包大小
const UINT 	DeityBoxBag_Size 		=	20;		//初始化神机匣背包大小
const UINT  SkyBoxBag_Size 			=	20;		//初始化天机匣背包大小
const UINT  EquipReformBag_Size 	=	4;		//初始化装备改造背包大小
const UINT  RidPetBag_Size 			=	5;		//骑宠装备背包大小
const UINT  EquipBagTianHun_Size	=	48;		// 天魂背包的大小
const UINT  EquipBagDiHun_Size		=	48;		// 地魂背包的大小
const UINT  FellowEvoBag_Size 		=	4;		//珍兽强化界面背包大小
const UINT	FellowEvolutionFullStar_Size = 20;		// 珍兽强化到满星的星级别(dxt 2012/3/17)
enum Bag_UI_Index
{
	Bag_InvalidIndex	= -1,
	EquipBag_Index		=0,		// 装备栏的索引   //默认为命魂 的 
	DefaultBag_Index,			// 默认背包的索引

	ExtBag1_Index,				// 扩展背包1
	ExtBag2_Index,
	ExtBag3_Index,
	ExtBag4_Index,
	ExtBag5_Index,
	ExtBag6_Index,

	Stash_Index			=10,	// 银行仓库
	StashExt1_Index,			// 银行仓库扩展背包1
	StashExt2_Index,			//
	StashExt3_Index,
	StashExt4_Index,
	StashExt5_Index,
	StashExt6_Index,

	KinStash_Index,				// 家族仓库
	KinStashExt1_Index,			// 家族仓库扩展背包1
	KinStashExt2_Index,
	KinStashExt3_Index,
	KinStashExt4_Index,

	FactionStash_Index,			// 帮会仓库
	FactionStashExt1_Index,		// 帮会仓库扩展背包1
	FactionStashExt2_Index,
	FactionStashExt3_Index,
	FactionStashExt4_Index,

	ActionBar1_Index	= 30,	// 动作条1 //按照现在的代码机制表示为命魂快捷栏   ChenXY  2011/9/28
	ActionBar2_Index,			//		   //按照现在的代码机制表示为地魂快捷栏   ChenXY  2011/9/28
	ActionBar3_Index,                      //按照现在的代码机制表示为天魂快捷栏   ChenXY  2011/9/28
	ActionBar4_Index,

	FaceActionBar1_Index = 35,
	FaceActionBar2_Index,
	FaceActionBar3_Index,

	Campaign_Lion_Index =40,	//活动舞狮背包 by zhao
	Campaign_Car_Index,			//活动个人镖车道具背包

	EquipBag_Pet = 50,
	DeityBoxBag_Index = 60,		//神机匣背包
	SkyBoxBag_Index,			//天机匣背包
	EquipReformBag_Index,       //装备改造背包
	EquipBagTianHun_Index,      //天魂装备背包
	EquipBagDiHun_Index,        //地魂装备背包
	FellowEvolutionBag_Index,			//珍兽强化界面背包
	Bag_UI_End,

};

// 道具装备
enum Equip_UI_Index
{
	Equip_Helm,					// 头盔
	Equip_Chest,				// 胸甲
	Equip_Belt,					// 腰带
	Equip_Bracer1,				// 手套1
	Equip_Bracer2,				// 手套2
	Equip_Boot,					// 鞋子
	Equip_MainWeap,				// 主手武器
	Equip_OffWeap,				// 副手武器
	Equip_Necklace,				// 项链
	Equip_Ring1,				// 戒指1
	Equip_Ring2,				// 戒指2
	Equip_Fashion,				// 时装
	Equip_Cloak,				// 披风
	//Equip_Banner,				// 军旗
	Equip_Shipin,				// 饰品

	//装备骑宠
	Equip_Rides1 = 50,			// 骑宠1
	Equip_Rides2,				// 骑宠2
	Equip_Rides3,				// 骑宠3
	Equip_Rides4,				// 骑宠4
	Equip_Rides5,				// 骑宠5
	Equip_Rides6,				// 骑宠6

	//装备侍从
	Equip_Retinue1 = 60,		// 侍从1
	Equip_Retinue2,				// 侍从2
	Equip_Retinue3,				// 侍从3
	Equip_Retinue4,				// 侍从4
	Equip_Retinue5,				// 侍从5
	Equip_Retinue6,				// 侍从6

	Equip_System1  = 100,		// 系统装备1 腰兜
	Equip_System2,				// 系统装备2 腰兜
	Equip_System3,				// 系统装备3 锦囊
	Equip_System4,				// 系统装备4 锦囊
	Equip_SuitEffect,			// 套装效果位置

	Equip_Bag1 = 202,			//
	Equip_Bag2,
	Equip_Bag3,
	Equip_Bag4,
	Equip_Bag5,
	Equip_Bag6,

	Equip_Stash = 210,
	Equip_StashExt1,
	Equip_StashExt2,
	Equip_StashExt3,
	Equip_StashExt4,
	Equip_StashExt5,
	Equip_StashExt6,

	Equip_KinStash,
	Equip_KinStashExt1,
	Equip_KinStashExt2,
	Equip_KinStashExt3,
	Equip_KinStashExt4,

	Equip_FactionStash,
	Equip_FactionStashExt1,
	Equip_FactionStashExt2,
	Equip_FactionStashExt3,
	Equip_FactionStashExt4,

	Equip_Saddle,
	Equip_Horsewhip,
	Equip_Weskit,
	Equip_Spur,

	Equip_Pet_Saddle = 50000,		// 马鞍
	Equip_Pet_HorseWhip,		// 马鞭
	Equip_Pet_Weskit,			// 马甲
	Equip_Pet_Spur,				// 马刺
	Equip_Pet_Fashion,			//时装

};

enum BoxCompose_UIPos
{
	BoxCompose_InvailPos = -1,
	BoxCompose_MaterialPos1 = 0,
	BoxCompose_MaterialPos2,
	BoxCompose_MaterialPos3,
	BoxCompose_MaterialPos4,
	BoxCompose_MaterialPos5,

	BoxCompose_EquipComposePos1,
	BoxCompose_EquipComposePos2,
	BoxCompose_EquipComposePos3,
	BoxCompose_EquipComposePos4,
	BoxCompose_EquipComposePos5,

	BoxCompose_SignBindPos1,
	BoxCompose_SignBindPos2,
	BoxCompose_SignBindPos3,
	BoxCompose_SignBindPos4,
	BoxCompose_SignBindPos5,

	BoxCompose_EquipStarPos1,
	BoxCompose_EquipStarPos2,
	BoxCompose_EquipStarPos3,
	BoxCompose_EquipStarPos4,
	BoxCompose_EquipStarPos5,
};

// 使用计数种类
enum EUseCount_Type
{
	EUseCount_Invalid = -1,
	EUseCount_Prop,			//道具使用类型	
	EUseCount_BuyProp,		//道具购买类型
	EUseCount_HuoDong,		//活动类型
	EUseCount_Quest,		//任务类型
	EUseCount_Exchange,		//兑换类型
	EUseCount_LiBao1,       //礼包1（已使用）
	EUseCount_LiBao2,       //礼包2（未使用）
	EUseCount_LiBao3,       //礼包3（未使用）
	EUseCount_ExpTaken,     //获取经验
	EUseCount_SellMoney,	//出售金钱类型
	EUseCount_Num,		//此值始终为最后 请勿在此后添加 by zlm 2012.2.6
};

// 使用计数的 时间限制
enum EUseCount_TimeType
{
	EUseCount_Time_Invalid = -1,
	EUseCount_Time_Minute,
	EUseCount_Time_Hour,
	EUseCount_Time_Day,
	EUseCount_Time_Week,
	EUseCount_Time_Month,
	EUseCount_Time_Year,
	EUseCount_Time_NoTime,
	EUseCount_Time_Num,		//此值始终为最后 请勿在此后添加 by zlm 2012.2.6
};
enum EUseCount_Template
{
	EUseCount_Template_1 = 100000, //勋章兑换经验
	EUseCount_Template_2,					 //勋章兑换礼包
};
// 笑脸UI Pose 
// by ping 2011年11月8日
enum Face_UI_Index
{
	Face_UI_Index_1 = 0,		//对应 Alt + Q
	Face_UI_Index_2,			//Alt + W
	Face_UI_Index_3,
	Face_UI_Index_4,
	Face_UI_Index_5,
	Face_UI_index_6,
	Face_UI_index_7,
	Face_UI_index_8,
	Face_UI_index_9,
	Face_UI_index_10,
};

enum Reform_Auction_Bag
{
    ERA_Reform_UIPos = EquipReformBag_Index * 1000 ,
    ERA_Auction_UIPos,
    ERA_BUY_UIPos,
    ERA_MAIL_Pos,
};
//enum EquipPet_UI_Index
//{
//	//宠物装备索引
//	Equip_Pet_Saddle = 50000,		// 马鞍
//	Equip_Pet_HorseWhip,		// 马鞭
//	Equip_Pet_Weskit,			// 马甲
//	Equip_Pet_Spur,				// 马刺
//	Equip_Pet_Fashion,			//时装
//};

//套装效果
enum SuitEffect
{
	Effect_Liancheng = 1,		//连城诀效果
	Effect_Sign,				//签名效果
	Effect_Star,				//打星效果
};

// 和道具相关的数据
const UINT MAIL_PROP_UIPOS		= 610001;						//邮件的UI位置
const UINT AUCTION_PROP_UIPOS	= 620001;						//拍卖的UI位置
const UINT DRAG_PROP_UIPOS		= 620100;						//鼠标拖拽UI位置

#define GetBagIndex(m) (Bag_UI_Index)((m)/1000)
#define GetInsideIndex(m) ((m)%1000)
#define SetUIPos(m,n)		(UIPos)((m*1000)+n)
#define GetBagIndexByEquipPos(m) (Bag_UI_Index)((m)%100)

inline bool IsEquipByUIPos(UIPos Pos)		{ return (GetBagIndex(Pos) == EquipBag_Index) || (GetBagIndex(Pos) == EquipBagTianHun_Index) || (GetBagIndex(Pos) == EquipBagDiHun_Index); }
inline bool IsBagByUIPos(UIPos Pos)			{ return ((GetBagIndex(Pos) >= DefaultBag_Index) && (GetBagIndex(Pos) <= ExtBag6_Index));}
inline bool IsExtBagUIPos(UIPos Pos)		{ return ((GetBagIndex(Pos) >= ExtBag1_Index) && (GetBagIndex(Pos) <= ExtBag6_Index)); }
inline bool IsBankByUIPos(UIPos Pos)		{ return ((GetBagIndex(Pos) >= Stash_Index) && (GetBagIndex(Pos) <= StashExt6_Index));}
inline bool IsPetEquipIndex(UIPos Pos)		{ return ((Pos >= Equip_Pet_Saddle) && (Pos <= Equip_Pet_Fashion));}

//////////////////////////////////////////////////////////////////////////
// 主要用于这两个函数
////设置宠物攻击模式（nPetType ：1.战宠，2.玄兽）
//void SetAttackType(int nType,int nPetType);
//int GetAttackType( int nPetType );
const int COMBAT_PET = 1;	//战宠类型
const int FELLOW_PET = 2;	// 珍兽类型

//////////////////////////////////////////////////////////////////////////
//战宠相关
const int COMBAT_PET_FLAG_ATTACK		= 1;		//攻击		：无视其他目标，只攻击主人当前攻击目标；当主人切换攻击目标后，也随之切换攻击目标
const int COMBAT_PET_FLAG_DEFANCE		= 2;		//防守		：攻击正在攻击主人的目标，如果有多个目标同时攻击主人，则会选择距离最近的一个目标进行攻击
const int COMBAT_PET_FLAG_STOP			= 3;		//停留		：停留在某地点不作移动可以攻击(与全体攻击唯一区别是不能移动)
const int COMBAT_PET_FLAG_SELECT_ATTACK = 4;		//选择攻击	：选择此按钮之后，鼠标会变成可以选择目标的状态，点击某个目标之后，宠物会立即攻击指定目标，在主人没有发出其他命令之前，宠物将无视其他所有敌方单位
const int COMBAT_PET_FLAG_ALL_ATTACK	= 5;		//狂暴		：只要有敌对目标出现在视野，宠物将会立即上前攻击。如果同时有多个目标出现在视野，宠物将优先选择最近的一个目标进行攻击
const int COMBAT_PET_FLAG_IDEL			= 6;		//休息		：跟随主人，不进行任何攻击。可以被攻击，不还击
#define BUY_SUCCESS_CHARGE      5
//出售道具相关
//////////////////////////////////////////////////////////////////////////
#define STORAGE_NUM_MAX			200		//每个npc最多出售的道具
#define AUCTION_ADD_CHARGE	    15		//添加拍卖成功收1.5%手续费
#define AUCTION_BIDSUC_CHARGE	 1		//拍卖信息竞拍成功收取1%手续费
#define AUCTION_SUCCESS_CHARGE	25		//拍卖成功收取25%手续费
#define AUCTION_MANAGE_TIMT     43200   //拍卖的管理时间  12h

//出售道具类型
enum PropType_ForSale
{
	FORSALE_TYPE_INVALID		= 0,
	FORSALE_CHANDLERY_COMMON,			//杂货
	FORSALE_CHANDLERY_HIGH,				//高级杂货
	FORSALE_PROP_MAGIC,					//魔幻物品
	FORSALE_SKILL_WUSHU,				//武术系技能
	FORSALE_SKILL_SHESHU,				//射术系技能
	FORSALE_SKILL_FASHU,				//法术系技能
	FORSALE_SKILL_YAOSHU,				//妖术系技能
	FORSALE_SKILL_XIANSHU,				//仙术系技能
	FORSALE_AMMO,						//弹药
	FORSALE_MATERIAL_COMMON,			//材料
	FORSALE_MATERIAL_HIGH,				//高级材料
	FORSALE_TOOL,						//工具
	FORSALE_WEAPON,						//武器
	FORSALE_ARMOR,						//防具
	FORSALE_ORNAMENT,					//饰品
	FORSALE_FORSALE_VEHICLE,			//时装
	FORSALE_INQUEIR_PROP,				//任务物品
	FORSALE_VEHICLE,					//坐骑
	FORASLE_MEDICA,						//药品
};
struct Goods
{
	int m_TemplateID;
	int m_Num;
	int m_Price;
	PropType_ForSale m_SaleType;
};

struct Commodity
{
	signed int m_GoodsGroupID;			//组ID
	signed int m_PropTemplateID;		//购买的道具模版ID
	signed int m_Num;					//购买数量
	Type_Money m_Price;					//价格
	signed int m_TypeForSale;			//物品换物品的模版ID(即 消耗的道具模版ID)
	signed int m_ItemOrder;				//排列顺序
	signed int m_UseSex;				//使用性别
	signed int m_MinLevel;				//最小等级
	signed int m_MaxLevel;				//最大等级
	signed int m_Seal;					//封印

	signed int m_BuyCount_TimeType;		// 购买计数时间类型
	signed int m_BuyCount_Num;			// 在规定时间内购买次数
	signed int m_BuyCount_KeyWorlds;	// 关键字
};
//////////////////////////////////////////////////////////////////////////

#define MAX_DIALY_JOINER    4

#define	MAX_STR_LENGTH		32
#define	MAX_CHAR_NUMBER		64

enum Skill_Main_Pos
{
	SKILL_PROP_1		= 0,	// 道具1
	SKILL_PROP_2,
	SKILL_PROP_3,
	SKILL_PROP_4,

	SKILL_ASSI_1,				// 辅助1
	SKILL_ASSI_2,

	SKILL_MAX_1,				// 必杀1
	SKILL_MAX_2,				// 必杀2

	SKILL_POS_END,
};
//enum Desigation_Type
//{
//	Designation_King = 0,
//};

enum Loing_State
{
	Loing_State_ReSetName = 0,			// 同名需要改名(CreateRole)
	Loing_State_Ok = 1,					// 创建新人成功
	Loing_State_Max = 10,				// 已经创建最大人数6个
	Loing_State_Select_Login_OK = 11,	// 选人登录成功（Select Role）
	Login_State_Select_player_Being =13,// 选中的人已经在游戏里（Select Role）
	Login_State_Create_Ignore = 15,		// 创建人名时有脏话
};

//
#define MAX_NETGRID_CX		1000
#define MAX_NETGRID_CY		1000
#define SCENE_OBJ_MAX		10000		// 一个场景最多的NPC个数
#define PROP_ID_NORM		10000		// 道具存入table中的基准值
#define ROLE_MAX_SKILL		500			// 一个

enum	DAMAGE_SCHOOL
{
	//2009.11.20 一下排列没有游戏逻辑的顺序，是乱的
	DAMAGE_SCHOOL_PHYSICAL_M =0,	//近战		//2009.1.17 不分单手双手，只分近程远程
	DAMAGE_SCHOOL_PHYSICAL_R,		//远程
	DAMAGE_SCHOOL_FIRE,				//火伤害
	DAMAGE_SCHOOL_COLD,				//冰伤害
	DAMAGE_SCHOOL_SPELL,			//魔法伤害
	DAMAGE_SCHOOL_POISON,			//毒伤害
	DAMAGE_SCHOOL_HEALING,			//治疗系
	DAMAGE_SCHOOL_DIRECT,			//直接伤害
	DAMAGE_SCHOOL_KIN,				//家族战车伤害
	DAMAGE_SCHOOL_FACTION,			//帮会战车伤害
	DAMAGE_SCHOOL_BURN,				//灼烧伤害
	DAMAGE_SCHOOL_DRUG,				//中毒伤害
	DAMAGE_SCHOOL_FUZHOU,			//符咒攻击
	DAMAGE_SCHOOL_FAMILY1,			//家族伤害1
	DAMAGE_SCHOOL_FAMILY2,			//家族伤害2
	DAMAGE_SCHOOL_FAMILY3,			//家族伤害3
	DAMAGE_SCHOOL_LIGHTNING,		//电伤害
	DAMAGE_SCHOOL_PHYSICAL,			//物理伤害系
	DAMAGE_SCHOOL_WUSHU,			//武术
	DAMAGE_SCHOOL_SHESHU,			//射术
	DAMAGE_SCHOOL_FASHU,			//法术
	DAMAGE_SCHOOL_YAOSHU,			//妖术
	DAMAGE_SCHOOL_XIANSHU,			//仙术

	//DAMAGE_SCHOOL_PHYSICAL=50,			//组合伤害系，专用于战斗触发的效果
	//DAMAGE_SCHOOL_SPELL,
	//DAMAGE_SCHOOL_NULL,
	//DAMAGE_SCHOOL_ALL,

	DAMAGE_SCHOOL_HOT_EFFECT=100,		//增益效果
	DAMAGE_SCHOOL_DOT_EFFECT,			//减溢效果
};


enum Skill_Class
{
	Skill_Class_Special,
	Skill_Class_Martial,
};

enum Debuff_Type
{
	Debuff_Poison,			//中毒
	Debuff_Ablepsia,		//失明
	Debuff_Freeze,			//冰冻
	Debuff_Burn,			//灼烧
	Debuff_Stun,			//眩晕
	Debuff_Slow,			//减速
	Debuff_Immobilize,		//定身
	Debuff_Confuse,			//混乱
	Debuff_Slience,			//沉默

	Debuff_TypeCounts,
};


//--冒字类型--
enum Attack_Result
{
	// 普通
	Attack_Hit = 0,				// 命中
	Attack_Hit_Player,          // 被命中
	Attack_Crit,				// 爆击
	Attack_Crit_Player,         // 被暴击
	Attack_HolyStrike,			// 致命一击
	Attack_HolyStrike_Player,   // 被致命一击
	Attack_Hit_Blood,			// 加血
	Attack_Crit_Blood,          // 加血暴击
	Attack_HolyStrike_Blood,    // 被加血暴击
	Add_Exp,					// 增加经验

	Valid_Result,				// 此值以上（不含此值）为需要显示的冒字类型

	Attack_MP,					// 抽蓝
	Pet_Hit,					// 宠物攻击
	Pet_Crit,					// 宠物暴击

	// 需特殊处理 暂时没有
	Attack_Dodge,			    // 闪避
	Attack_Miss,				// 未击中
	Attack_Invincible,			// 免役

};

enum Attrib_Param_Pool
{
	Param_Value,
	Param_Addend,
	Param_Multiplier,

	ParamPool_Size,
};

enum Equip_School
{
	Prop_School_Nothing = 0,		// 无类型
	Prop_School_Damage,				// 物理伤害
	Prop_School_Spell,				// 魔法伤害
	Prop_School_Armor,				// 物理防御
	Prop_School_SpellResist,		// 魔法防御
	Prop_School_DoubleResist,		// 双防装
	Prop_School_HpEquip,			// 生命装
	Prop_School_RidePet_Damage,		// 马装 物理伤害
	Prop_School_RidePet_Spell,		// 马装 魔法伤害
	Prop_School_RidePet_Armor,		// 马装 物理防御
	Prop_School_RidePet_SpellResist,// 马装 魔法防御

};
enum ESoulSysType
{
	ESoulSys_Invalid = -1,
	ESoulSys_MingHun,     //命魂
	ESoulSys_DiHun,       //地魂
	ESoulSys_TianHun,     //天魂 
	ESoulSys_End,
};

/*// DB 标志
const int DB_FLAG_CREATE = (1<<1);		//创建
const int DB_FLAG_DELETE = (1<<2);		//删除
const int DB_FLAG_UPDATE = (1<<3);		//更新*/

// Obj标志
const int OBJ_FLAG_NORMAL = 0;			//正常
const int OBJ_FLAG_OFFLINE= 1;			//下线
const int OBJ_FLAG_DELETE = 2;			//删除
const int OBJ_FLAG_CREATE = 3;			//创建
const int OBJ_FLAG_UPDATE = 4;			//更新

// 道具随机效果
struct Effect_Value
{
	EffectID	m_EffectID;
	BYTE		m_Random;
	//int			m_Value;
	int			m_MinValue;
	int			m_MaxValue;
};

//const char* GetAttribName(int nAttribID);
//const wchar_t* GetAttribNameW(int nAttribID);

// 16 禁止转换成 10进制
// cp:去掉"0x"开头的部分
// inline int xatoi(char* cp)
// {
// 	if(cp[0] == '0' && (cp[1]='x' || cp[1]=='X'))
// 		cp=cp+2;
//
// 	int   val=0;
// 	val   =   0;
// 	while(*cp)
// 	{
// 		if(*cp >='a'   &&   *cp<= 'f')
// 			val   =   val   *   16   +   *cp   -   'a'   +   10;
// 		else   if(*cp   >=   'A'   &&   *cp   <=   'F')
// 			val   =   val   *   16   +   *cp   -   'A'   +   10;
// 		else   if(*cp   >=   '0'   &&   *cp   <=   '9')
// 			val = val   *   16   +   *cp   -   '0';
// 		else
// 			break;
// 		cp++;
// 	}
// 	return   val;
// }

// inline int64 xatoi64(char* str)
// {
// 	if(str[0] == '0' && (str[1]='x' || str[1]=='X'))
// 		str=str+2;
//
// 	int64 Val=0;
// 	size_t len = strlen(str);
// 	for(UINT i = 0;i < len-1 ;i++)
// 	{
// 		int nDecNum;
// 		switch(str[i])
// 		{
// 		case 'a':
// 		case 'A':
// 			nDecNum = 10;
// 			break;
// 		case 'b':
// 		case 'B':
// 			nDecNum = 11;
// 			break;
// 		case 'c':
// 		case 'C':
// 			nDecNum = 12;
// 			break;
// 		case 'd':
// 		case 'D':
// 			nDecNum = 13;
// 			break;
// 		case 'e':
// 		case 'E':
// 			nDecNum = 14;
// 			break;
// 		case 'f':
// 		case 'F':
// 			nDecNum = 15;
// 			break;
// 		case '0':
// 		case '1':
// 		case '2':
// 		case '3':
// 		case '4':
// 		case '5':
// 		case '6':
// 		case '7':
// 		case '8':
// 		case '9':
// 			nDecNum = str[i] - '0';
// 			break;
// 		default:
// 			return 0;
// 		}
// 		Val = (Val | nDecNum) << 4;
// 	}
//
// 	return   Val;
// }

// inline UINT64 xatoui64(char* str)
// {
// 	if(str[0] == '0' && (str[1]='x' || str[1]=='X'))
// 		str=str+2;
//
// 	UINT64 Val=0;
// 	UINT len = strlen(str);
// 	for(UINT i = 0;i < len ;i++)
// 	{
// 		int nDecNum;
// 		switch(str[i])
// 		{
// 		case 'a':
// 		case 'A':
// 			nDecNum = 10;
// 			break;
// 		case 'b':
// 		case 'B':
// 			nDecNum = 11;
// 			break;
// 		case 'c':
// 		case 'C':
// 			nDecNum = 12;
// 			break;
// 		case 'd':
// 		case 'D':
// 			nDecNum = 13;
// 			break;
// 		case 'e':
// 		case 'E':
// 			nDecNum = 14;
// 			break;
// 		case 'f':
// 		case 'F':
// 			nDecNum = 15;
// 			break;
// 		case '0':
// 		case '1':
// 		case '2':
// 		case '3':
// 		case '4':
// 		case '5':
// 		case '6':
// 		case '7':
// 		case '8':
// 		case '9':
// 			nDecNum = str[i] - '0';
// 			break;
// 		default:
// 			return 0;
// 		}
// 		Val = (Val<<4 | nDecNum) ;
// 	}
//
// 	return   Val;
// }
//根据家族等级和基础模板ID决定领取的BOSS的模板ID
#define GETWHITEID(ID,Familylevel)     (ID + (Familylevel-1)*5)		//boss品质 (白)
#define GETGREENID(ID,Familylevel)	((ID + (Familylevel-1)*5)+1)	//boss品质 (绿)
#define GETBLUEID(ID,Familylevel)		((ID + (Familylevel-1)*5)+2)	//boss品质 (蓝)
#define GETBLACKID(ID,Familylevel)	((ID + (Familylevel-1)*5)+3)	//boss品质 (紫)
#define GETGOLDID(ID,Familylevel)		((ID + (Familylevel-1)*5)+4)	//boss品质 (金)

#define FEEDBOSSTIMES	5

enum FamilyBuilding				//家族建筑物
{
	Family_JuYiTing = 0,		//聚义厅
	Family_ZhaiJiDi,			//宅基地
	Family_FightCarHouse,		//战车坊
	Family_WuGuan,				//武馆
	Family_YanJiuSuo,			//研究所
	Family_Strorage,			//仓库
	Family_GoldStrorage,		//金库
	Family_YeLianFang,			//冶炼房
	Family_JianTa,				//箭塔
	Family_Building_End,
};

//家族操作错误码（玩家在CS上进行家族操作失败时，需要反馈给所在dataserver时使用）
enum  FAMILY_OPERATE_ERRORID
{
	CREATEFAMILY_FAILED = 0,	// --创建家族失败
	CREATEFAMILY_SUCCESS,		//创建家族成功
	ADDFAMILYMONEY_SUCCESS,      //捐钱成功
	ADDFAMILYMONEY_FAILED,		//捐钱失败
	SENDWORLDMSG_SUCCESS,		//发送世界消息成功
	SENDWORLDMSG_FAILED,		//发送世界消息失败
	SENDCOLORWORLDMSG_SUCCESS,	//发送彩世成功
	SENDCOLORWORLDMSG_FAILED,	//发送彩世失败
};


enum FamilyBuildingAttrib
{
	FamilyBuilding_Attrib_Level = 0,		//当前等级
	FamilyBuilding_Attrib_Hp,				//当前血量
	FamilyBuilding_Attrib_Wear,				//当前耐久度
	FamilyBuilding_Attrib_Progress,			//当前进度

	FamilyBuilding_Attrib_MaxProgress,		//最大建设度
	FamilyBuilding_Attrib_MaxLevel,			//最大等级
	FamilyBuilding_Attrib_MaxHp,			//最大血量
	FamilyBuilding_Attrib_MaxWear,			//最大耐久度
	FamilyBuilding_Attrib_UpgradeCost,		//升级费用
	FamilyBuilding_Attrib_UpkeepCost,		//维护费用
	FamilyBuilding_Attrib_Type,				//类型
	FamilyBuilding_Attrib_FamilyID,			//家族ID
};

#define APPLY_JOIN_FAMILY_MAX		20
#define FAMILY_NOTICE_LENGTH_MAX    401


enum Attrib
{
	//////////////////////////////////////////////////
	///基础属性增加 & 基础属性百分比增加
	//////////////////////////////////////////////////

	Role_Attrib_Waigong	=	1,			//外功
	Role_Attrib_Neigong,				//内功
	Role_Attrib_Shenfa,					//身法
	Role_Attrib_Zhenqi,					//真气
	Role_Attrib_Jingu,					//筋骨

	Role_Attrib_BaseWaigong,			//基础外功
	Role_Attrib_BaseNeigong,			//基础内功
	Role_Attrib_BaseShenfa,				//基础身法
	Role_Attrib_BaseZhenqi,				//基础真气
	Role_Attrib_BaseJingu,				//基础筋骨

	Role_Attrib_WaigongEnhance = 11,	//%外功
	Role_Attrib_NeigongEnhance,			//%内功
	Role_Attrib_ShenfaEnhance,			//%身法
	Role_Attrib_ZhenqiEnhance,			//%真气
	Role_Attrib_JinguEnhance,			//%筋骨



	//////////////////////////////////////////////////
	///状态条数值
	//////////////////////////////////////////////////

	Role_Attrib_Hp  =  21,				//生命
	Role_Attrib_MaxHp,					//最大生命
	Role_Attrib_HpRegen,				//生命恢复
	Role_Attrib_MaxHpEnhance,			//最大生命%
	Role_Attrib_BaseHp,					//基础生命
	Role_Attrib_HpEnhance,				//生命百分比改变
	Role_Attrib_HpRegenEnhance,			//每秒回血%

	Role_Attrib_Mp  = 31,				//法力
	Role_Attrib_MaxMp,					//最大法力
	Role_Attrib_MpRegen,				//法力恢复
	Role_Attrib_MaxMpEnhance,			//最大法力%
	Role_Attrib_BaseMp,					//基础法力
	Role_Attrib_MpEnhance,				//法力百分比改变
	Role_Attrib_MpRegenEnhance,			//每秒回蓝%

	Role_Attrib_NormalEnergy = 41,		//能量（没用）//名字与活力值冲突，此属性没用改成NormalEnergy(正常能量) change by zhangjianli 2012-7-12
	Role_Attrib_MaxEnergy,
	Role_Attrib_EnergyRegen,
	Role_Attrib_MaxEnergyEnhance,

	Role_Attrib_Rage  = 51,				// 当前怒气
	Role_Attrib_MaxRage,				// 最大怒气（因为怒气最大值不变，所以在程序中写死，不读表，在初始化时赋值 ROLE_RAGE_NUM_MAX）
	Role_Attrib_RageRegen,				// 怒气回复（没用）
	Role_Attrib_MaxRageEnhance,			// 怒气回复百分比（没用）


	//////////////////////////////////////////////////
	///攻击
	//////////////////////////////////////////////////
	Role_Attrib_MinDamageMelee  = 101,			//最小攻击(近程)
	Role_Attrib_MaxDamageMelee,					//最大攻击
	Role_Attrib_DamageMelee,					//攻击
	Role_Attrib_DamageMeleeEnhance,				//攻击加强%

	Role_Attrib_MinDamageRange  = 106,			//最小攻击(远程)
	Role_Attrib_MaxDamageRange,					//最大攻击
	Role_Attrib_DamageRange,					//攻击
	Role_Attrib_DamageRangeEnhance,				//攻击加强

	Role_Attrib_MinDamagePhysical = 111,		//最小攻击(物理)`
	Role_Attrib_MaxDamagePhysical,				//最大攻击
	Role_Attrib_DamagePhysical,					//攻击
	Role_Attrib_DamagePhysicalEnhance,			//攻击加强%

	Role_Attrib_MinDamageFire   = 116,			//最小火焰攻击
	Role_Attrib_MaxDamageFire,					//最大火焰攻击
	Role_Attrib_DamageFire,						//火焰攻击
	Role_Attrib_DamageFireEnhance,				//火焰攻击%

	Role_Attirb_MinDamageCold   = 121,			//冰（同上）
	Role_Attirb_MaxDamageCold,
	Role_Attrib_DamageCold,
	Role_Attrib_DamageColdEnhance,

	Role_Attrib_MinDamageLightning = 126,		//电（同上）
	Role_Attrib_MaxDamageLightning,
	Role_Attrib_DamageLightning,
	Role_Attrib_DamageLightningEnhance,

	Role_Attrib_MinDamagePoison = 131,			//毒（同上）
	Role_Attrib_MaxDamagePoison,
	Role_Attrib_DamagePoison,
	Role_Attrib_DamagePoisonEnhance,

	Role_Attrib_MinHealing = 136,				//治疗（同上）
	Role_Attrib_MaxHealing,
	Role_Attrib_Healing,
	Role_Attrib_HealingEnhance,

	Role_Attrib_MinDamageFamily1 =	146,		//家族伤害1
	Role_Attrib_MaxDamageFamily1,
	Role_Attrib_DamageFamily1,
	Role_Attrib_DamageFamily1Enhance,

	Role_Attrib_MinDamageFamily2 =	151,		//家族伤害2
	Role_Attrib_MaxDamageFamily2,
	Role_Attrib_DamageFamily2,
	Role_Attrib_DamageFamily2Enhance,

	Role_Attrib_MinDamageFamily3 =	156,		//家族伤害3
	Role_Attrib_MaxDamageFamily3,
	Role_Attrib_DamageFamily3,
	Role_Attrib_DamageFamily3Enhance,

	Role_Attrib_MinDamageSpell = 166,				//最小法术攻击
	Role_Attrib_MaxDamageSpell,						//最大法术攻击
	Role_Attrib_DamageSpell,						//法术攻击
	Role_Attrib_DamageSpellEnhance,					//法术攻击%

	Role_Attrib_MinDirectDamage = 171,				//最小直接攻击
	Role_Attrib_MaxDirectDamage,					//最大直接攻击
	Role_Attrib_DirectDamage,						//直接攻击
	Role_Attrib_DirectDamageEnhance,				//直接攻击%

	Role_Attrib_AllDamage = 175,			//所有攻击
	Role_Attrib_AllDamageEnhance,					//所有攻击加成%

	Role_Attrib_MinBurn		 = 181,					//灼烧攻击最小值
	Role_Attrib_MaxBurn,							//灼烧攻击最大值
	Role_Attrib_Burn,								//灼烧攻击
	Role_Attrib_BurnEnhance,						//灼烧攻击加成%

	Role_Attrib_MinPosionBuf	= 186,				//中毒攻击最小值
	Role_Attrib_MaxPosionBuf,						//中毒攻击最大值
	Role_Attrib_PosionBuf,							//中毒攻击
	Role_Attrib_PosionBufEnhance,					//中毒攻击加强%

	Role_Attrib_MinFuZhou		= 191,				//最小符咒攻击
	Role_Attrib_MaxFuZhou,							//最大符咒攻击
	Role_Attrib_FuZhou,								//符咒攻击
	Role_Attrib_FuZhouEnhance,						//符咒攻击%

	Role_Attrib_WuShu,								//武术属性攻击
	Role_Attrib_WuShuEnhance,						//武术属性攻击加成%

	Role_Attrib_FaShu,								//法术属性攻击
	Role_Attrib_FaShuEnhance,						//法术属性攻击加成%

	Role_Attrib_SheShu,								//射术属性攻击
	Role_Attrib_SheShuEnhance,						//射术属性攻击加成%

	Role_Attrib_YaoShu,								//妖术属性攻击
	Role_Attrib_YaoShuEnhance,						//妖术属性攻击加成%

	Role_Attrib_XianShu,							//法术属性攻击
	Role_Attrib_XianShuEnhance,						//法术属性攻击加成%

	//////////////////////////////////////////////////
	///伤害
	//////////////////////////////////////////////////
	// 	Role_Attrib_MinAttackPowerMelee = 201,			//
	// 	Role_Attrib_MaxAttackPowerMelee,				//
	// 	Role_Attrib_AttackPowerMelee,					//物理攻击能量(近程)
	// 	Role_Attrib_AttackPowerMeleeEnhance,			//物理攻击能量%
	//
	// 	Role_Attrib_MinAttackPowerRange = 206,			//
	// 	Role_Attrib_MaxAttackPowerRange,
	// 	Role_Attrib_AttackPowerRange,					//物理攻击能量(远程)
	// 	Role_Attrib_AttackPowerRangeEnhance,			//物理攻击能量%
	//
	//
	// 	Role_Attrib_MinAttackPower = 211,				//最小攻击增加
	// 	Role_Attrib_MaxAttackPower,						//最大攻击增加
	// 	Role_Attrib_AttackPower,						//攻击增加
	// 	Role_Attrib_AttackPowerEnhance,					//攻击增加%
	//
	// 	Role_Attrib_MinSpellPowerFire = 216,			//最小火焰攻击增加
	// 	Role_Attrib_MaxSpellPowerFire,
	// 	Role_Attrib_SpellPowerFire,
	// 	Role_Attrib_SpellPowerFireEnhance,
	//
	// 	Role_Attrib_MinSpellPowerCold= 221,				//冰
	// 	Role_Attrib_MaxSpellPowerCold,
	// 	Role_Attrib_SpellPowerCold,
	// 	Role_Attrib_SpellPowerColdEnhance,
	//
	// 	Role_Attrib_MinSpellPowerLightning = 226,		//电
	// 	Role_Attrib_MaxSpellPowerLightning,
	// 	Role_Attrib_SpellPowerLightning,
	// 	Role_Attrib_SpellPowerLightningEnhance,
	//
	// 	Role_Attrib_MinSpellPowerPoison = 231,			//毒
	// 	Role_Attrib_MaxSpellPowerPoison,
	// 	Role_Attrib_SpellPowerPoison,
	// 	Role_Attrib_SpellPowerPoisonEnhance,
	//
	// 	Role_Attrib_MinHealingPower =	236,			//治疗
	// 	Role_Attrib_MaxHealingPower,
	// 	Role_Attrib_HealingPower,
	// 	Role_Attrib_HealingPowerEnhance,
	//
	// 	Role_Attrib_MinSpellPower = 266,				//法术最小攻击
	// 	Role_Attrib_MaxSpellPower,						//法术最大攻击
	// 	Role_Attrib_SpellPower,							//法术攻击
	// 	Role_Attrib_SpellPowerEnhance,					//法术攻击%

	//////////////////////////////////////////////////////////////////////////
	//伤害加成（2009.11.20 伤害加成和伤害减免不对应，看着不爽，有空改）
	//////////////////////////////////////////////////////////////////////////

	Role_Attrib_IncreaseAllResultValue = 276,		//所有伤害增加值
	Role_Attrib_IncreaseAllResult = 277,			//所有伤害%
	Role_Attrib_DamageMellIncrease,					//近程物理伤害增加
	Role_Attrib_DamageRangeIncrease,				//远程物理伤害增加
	Role_Attrib_DamageColdIncrease,					//冰伤害增加
	Role_Attrib_DamgeFireIncrease,					//火伤害增加
	Role_Attrib_DamageLightIncrease,				//电伤害增加
	Role_Attrib_DamagePosionIncrease,				//毒伤害增加
	Role_Attrib_DamageHealIncrease,					//治疗增加
	Role_Attrib_DamagePhysicalIncrease,				//物理伤害增加
	Role_Attrib_DamageSpellIncrease,				//魔法伤害增加
	Role_Attrib_DamageBurnIncrease,					//灼烧伤害增加
	Role_Attrib_DamageFuZhouIncrease,				//符咒伤害加成
	Role_Attrib_DamageWuShuIncrease,				//武术伤害加成
	Role_Attrib_DamageFaShuIncrease,				//法术伤害加成
	Role_Attrib_DamageSheShuIncrease,				//射术伤害加成
	Role_Attrib_DamageYaoShuIncrease,				//妖术伤害加成
	Role_Attrib_DamageXianShuIncrease,				//仙术伤害加成
	//////////////////////////////////////////////////
	///攻击防御
	//////////////////////////////////////////////////
	Role_Attrib_MinArmorMeleeOH = 301,				//最小近程物理防御
	Role_Attrib_MaxArmorMeleeOH,					//最大近程物理防御
	Role_Attrib_ArmorMeleeOH,						//近程物理防御
	Role_Attrib_ArmorMeleeEnhanceOH,				//近程物理防御%

	Role_Attrib_MinArmorRange = 307,				//最小远程物理防御
	Role_Attrib_MaxArmorRange,						//最大远程物理防御
	Role_Attrib_ArmorRange,							//远程物理防御
	Role_Attrib_ArmorRangeEnhance,					//远程物理防御%

	Role_Attrib_MinArmor = 311,						//最小物理防御
	Role_Attrib_MaxArmor,							//最大物理防御
	Role_Attrib_Armor,								//物理防御
	Role_Attrib_ArmorEnhance,						//物理防御%

	Role_Attrib_MinFireResist = 316,				//火焰防御
	Role_Attrib_MaxFireResist,
	Role_Attrib_FireResist,
	Role_Attrib_FireResistEnhance,

	Role_Attrib_MinColdResist = 321,				//冰防御
	Role_Attrib_MaxColdResist,
	Role_Attrib_ColdResist,
	Role_Attrib_ColdResistEnhance,

	Role_Attrib_MinLightningResist = 326,			//电防御
	Role_Attrib_MaxLightningResist,
	Role_Attrib_LightningResist,
	Role_Attrib_LightningResistEnhance,

	Role_Attrib_MinPoisonResist = 331,				//毒防御
	Role_Attrib_MaxPoisonResist,
	Role_Attrib_PoisonResist,
	Role_Attrib_PoisonResistEnhance,

	Role_Attrib_MinHealingResist = 336,				//治疗防御
	Role_Attrib_MaxHealingResist,
	Role_Attrib_HealingResist,
	Role_Attrib_HealingResistEnhance,


	Role_Attrib_MinArmorFamily1 =	346,				//家族防御最大
	Role_Attrib_MaxArmorFamily1,						//家族防御最小
	Role_Attrib_ArmorFamily1,							//家族防御1
	Role_Attrib_ArmorEnhanceFamily1,					//家族防御1%

	Role_Attrib_MinArmorFamily2 =	351,				//家族防御2最大
	Role_Attrib_MaxArmorFamily2,						//家族防御2最小
	Role_Attrib_ArmorFamily2,							//家族防御2
	Role_Attrib_ArmorEnhanceFamily2,					//家族防御2%

	Role_Attrib_MinArmorFamily3 =	356,				//家族防御3最大
	Role_Attrib_MaxArmorFamily3,						//家族防御3最小
	Role_Attrib_ArmorFamily3,							//家族防御3
	Role_Attrib_ArmorEnhanceFamily3,					//家族防御3%


	Role_Attrib_MinSpellResist = 366,				//法术防御（泛指所有）
	Role_Attrib_MaxSpellResist,
	Role_Attrib_SpellResist,
	Role_Attrib_SpellResistEnhance,

	Role_Attrib_MinDirectDamageArmor = 371,			//直接伤害
	Role_Attrib_MaxDirectDamageArmor,
	Role_Attrib_DirectDamageArmor,
	Role_Attrib_DirectDamageArmorEnhance,

	Role_Attrib_AllArmor = 376,						//所有防御
	Role_Attrib_AllArmorEnhance,					//所有防御增加%


	Role_Attrib_WuShuResist,						//武术抗性
	Role_Attrib_FaShuResist,						//法术抗性
	Role_Attrib_SheShuResist,						//射术抗性
	Role_Attrib_YaoShuResist,						//妖术抗性
	Role_Attrib_XianShuResist,						//仙术抗性

	//Role_Attrib_MinFuZhouResist	= 381,				//符咒最小防御
	//Role_Attrib_MaxFuZhouResist,					//符咒最大防御
	//Role_Attrib_FuZhouResist,						//符咒防御
	//Role_Attrib_FuZhouResistEnhance,				//符咒防御%

	//////////////////////////////////////////////////
	///伤害减免
	//////////////////////////////////////////////////

	Role_Attrib_MinMeleeDamageReduce = 401,			//近程最小伤害减免%
	Role_Attrib_MaxMeleeDamageReduce,				//近程最大伤害减免%
	Role_Attrib_MeleeDamageReduce,					//近程伤害减免%

	Role_Attrib_MinRangeDamageReduce = 406,			//远程最小伤害减免%
	Role_Attrib_MaxRangeDamageReduce,				//远程最大伤害减免%
	Role_Attrib_RangeDamageReduce,					//远程伤害减免%

	Role_Attrib_MinPhysicDamageReduce = 411,		//物理最小伤害减免%
	Role_Attrib_MaxPhysicDamageReduce,				//物理最大伤害减免%
	Role_Attrib_PhysicDamageReduce,					//物理伤害减免%

	Role_Attrib_MinFireDamageReduce = 416,			//火焰的
	Role_Attrib_MaxFireDamageReduce,
	Role_Attrib_FireDamageReduce,

	Role_Attrib_MinColdDamageReduce = 421,			//冰
	Role_Attrib_MaxColdDamageReduce,
	Role_Attrib_ColdDamageReduce,

	Role_Attrib_MinLightningDamageReduce = 426,		//电
	Role_Attrib_MaxLightningDamageReduce,
	Role_Attrib_LightningDamageReduce,

	Role_Attrib_MinPoisonDamageReduce = 431,		//毒
	Role_Attrib_MaxPoisonDamageReduce,
	Role_Attrib_PoisonDamageReduce,

	Role_Attrib_MinHealingReduce = 436,				//治疗
	Role_Attrib_MaxHealingReduce,
	Role_Attrib_HealingReduce,

	Role_Attrib_FuZhouDamageReduce = 440,			//符咒
	Role_Attrib_BurnDamageReduce,					//灼烧

	Role_Attrib_MinSpellDamageReduce = 466,			//魔法伤害最小减免
	Role_Attrib_MaxSpellDamageReduce,				//魔法伤害最大减免
	Role_Attrib_SpellDamageReduce,					//魔法伤害减免

	Role_Attrib_AllDamageReduce = 471,				//所有伤害减免
	Role_Attrib_AllDamageReduceEnhance,				//所有伤害减免%

	Role_Attrib_DamageReduceDong,					//伤害减免的护盾

	Role_Attrib_WuShuDamageReduce,					//武术
	Role_Attrib_FaShuDamageReduce,					//法术
	Role_Attrib_SheShuDamageReduce,					//射术
	Role_Attrib_YaoShuDamageReduce,					//妖术
	Role_Attrib_XianShuDamageReduce,				//仙术

	/////////////////////////////////////
	//现有：Accuracy命中&Parry招架&Dodge闪避&Block格挡&CrushingBlow碾压&Glance偏斜 及系数
	//Resilience 韧性等级，减少受到爆击的几率
	//名称异常：HolyStrike神圣攻击以改为致命
	////////////////////////////////////
	Role_Attrib_MeleeAccuracy = 501,				//近战命中率%
	Role_Attrib_MeleeParry,							//近战招架率%
	Role_Attrib_MeleeDodge,							//进展躲避率
	Role_Attrib_MeleeBlock,							//近战格挡率
	Role_Attrib_MeleeCrit,							//近战爆击率%
	Role_Attrib_MeleeCritLevel,						//近程暴击等级
	Role_Attrib_MeleeCrushingBlow,					//近战碾压率%
	Role_Attrib_MeleeGlance,						//近战偏斜率%
	Role_Attrib_MeleeBlockMultiplier =  514,		//近战格挡伤害%
	Role_Attrib_MeleeCritMultiplier,				//近战爆击伤害%
	Role_Attrib_MeleeCrushingBlowMultiplier,		//近战碾压伤害%
	Role_Attrib_MeleeGlanceMultipiler,				//近战偏斜伤害%

	Role_Attrib_RangeAccuracy = 521,				//远程命中率%
	Role_Attrib_RangeParry,							//远程招架率%
	Role_Attrib_RangeDodge,							//远程躲避率%
	Role_Attrib_RangeBlock,							//远程格挡率%
	Role_Attrib_RangeCrit,							//远程爆击率%
	Role_Attrib_RangeCritLevel,						//远程暴击等级
	Role_Attrib_RangeCrushingBlow,					//远程碾压率%
	Role_Attrib_RangeGlance,						//远程偏斜率%
	Role_Attrib_RangeBlockMultiplier =  534,		//远程格挡伤害%
	Role_Attrib_RangeCritMultiplier,				//远程爆击伤害%
	Role_Attrib_RangeCrushingBlowMultiplier,		//远程碾压伤害%
	Role_Attrib_RangeGlanceMultipiler,				//远程偏斜伤害%

	Role_Attrib_Accuracy = 541,						//基础命中率%
	Role_Attrib_Parry,								//基础招架率%
	Role_Attrib_Dodge,								//基础躲避率%
	Role_Attrib_Block,								//基础格挡率%
	Role_Attrib_Crit,								//基础暴击率%
	Role_Attrib_CritLevel,							//基础暴击等级
	Role_Attrib_CrushingBlow,						//基础碾压率%
	Role_Attrib_Glance,								//基础偏斜率%
	Role_Attrib_CritLevelEnhance,					//基础暴击等级%

	Role_Attrib_CritResilience = 550,				//减少爆击概率(任性)
	Role_Attrib_HolyStrikeResilience,				//减少致命一击概率

	Role_Attrib_BlockMultiplier =  554,				//基础格挡伤害%
	Role_Attrib_CritMultiplier,						//基础爆击伤害%
	Role_Attrib_CrushingBlowMultiplier,				//基础碾压伤害%
	Role_Attrib_GlanceMultipiler,					//基础偏斜伤害%

	Role_Attrib_FireAccuracy = 561,					//火系命中率%
	Role_Attrib_FireDodge,							//火系躲闪率%
	Role_Attrib_FireBlock,							//火系格挡率%
	Role_Attrib_FireCrit,							//火系爆击率%
	Role_Attrib_FireCritLevel,						//火系暴击等级
	Role_Attrib_FireBlockMultiplier = 573,			//火系格挡伤害系数%
	Role_Attrib_FireCritMulitipiler,				//火系爆击伤害%

	Role_Attrib_ColdAccuracy = 581,					//冰系命中率%
	Role_Attrib_ColdDodge,							//冰系躲闪率%
	Role_Attrib_ColdBlock,							//冰系格挡率%
	Role_Attrib_ColdCrit,							//冰系暴击率%
	Role_Attrib_ColdCritLevel,						//冰系暴击等级
	Role_Attrib_ColdBlockMultiplier = 593,			//冰系格挡系数%
	Role_Attrib_ColdCritMulitipiler,				//冰系爆击伤害%

	Role_Attrib_LightningAccuracy = 601,			//电系命中率%
	Role_Attrib_LightningDodge,						//电系躲闪率%
	Role_Attrib_LightningBlock,						//电系格挡率%
	Role_Attrib_LightningCrit,						//电系暴击率%
	Role_Attrib_LightningCritLevel,					//电系暴击等级
	Role_Attrib_LightningBlockMultiplier = 613, 	//电系格挡系数%
	Role_Attrib_LightningCritMulitipiler,	    	//电系爆击伤害%


	Role_Attrib_PoisonAccuracy = 621,				//毒系命中率%
	Role_Attrib_PoisonDodge,						//毒系躲闪率%
	Role_Attrib_PoisonBlock,						//毒系格挡率%
	Role_Attrib_PoisonCrit,							//毒系暴击率%
	Role_Attrib_PoisonCritLevel,					//毒系暴击等级
	Role_Attrib_PoisonBlockMultiplier = 633,		//毒系格挡系数率%
	Role_Attrib_PoisonCritMulitipiler,				//毒系爆击伤害%


	Role_Attrib_HealingAccuracy = 641,				//治疗系命中率%
	Role_Attrib_HealingDodge,						//治疗系躲闪率%
	Role_Attrib_HealingBlock,						//治疗系格挡率%
	Role_Attrib_HealingCrit,						//治疗系暴击率%
	Role_Attrib_HealingCritLevel,					//治疗系暴击等级
	Role_Attrib_HealingBlockMultiplier = 653,		//治疗系格挡系数%
	Role_Attrib_HealingCritMulitipiler,				//治疗系爆击伤害%

	Role_Attrib_PhysicalAccuracy = 661,				//物理命中率%
	Role_Attrib_PhysicalParry,						//物理格挡率%
	Role_Attrib_PhysicalDodge,						//物理躲闪率%
	Role_Attrib_PhysicalBlock,						//物理格挡率%
	Role_Attrib_PhysicalCrit,						//物理暴击率%
	Role_Attrib_PhysicalCritLevel,					//物理暴击等级
	Role_Attrib_PhysicalCrushingBlow,				//物理碾压系数
	Role_Attrib_PhysicalGlance,						//物理偏斜率
	Role_Attrib_PhysicalBlockMultiplier =  674,		//物理格挡%
	Role_Attrib_PhysicalCritMultiplier,				//物理爆击伤害%
	Role_Attrib_PhysicalCrushingBlowMultiplier,		//物理碾压伤害%
	Role_Attrib_PhysicalGlanceMultipiler,			//物理偏斜伤害%

	Role_Attrib_SpellAccuracy = 761,				//魔法命中率%
	Role_Attrib_SpellDodge,							//魔法躲闪率%
	Role_Attrib_SpellBlock,							//魔法格挡率%
	Role_Attrib_SpellCrit,							//魔法暴击率%
	Role_Attrib_SpellCritLevel,						//魔法暴击等级
	Role_Attrib_SpellBlockMultiplier = 773,			//魔法格挡系数%
	Role_Attrib_SpellCritMultiplier,				//魔法爆击伤害%

	Role_Attrib_FuZhouAccuracy = 781,				//符咒命中率%
	//Role_Attrib_FuZhouDodge,						//符咒躲避率%
	//Role_Attrib_FuZhouBlock,						//符咒格挡率%
	Role_Attrib_FuZhouCrit,							//符咒暴击率%
	Role_Attrib_FuZhouCritLevel,					//符咒爆击等级
	Role_Attrib_FuZhouBlockMultiplier,				//符咒格挡系数%
	Role_Attrib_FuZhouMultipiler,					//符咒伤害系数%

	Role_Attrib_WuShuCrit,							//武术暴击率%
	Role_Attrib_WuShuCritLevel,						//武术爆击等级
	Role_Attrib_WuShuMultipiler,					//武术伤害系数%

	Role_Attrib_FaShuCrit,							//法术暴击率%
	Role_Attrib_FaShuCritLevel,						//法术爆击等级
	Role_Attrib_FaShuMultipiler,					//法术伤害系数%

	Role_Attrib_SheShuCrit,							//射术暴击率%
	Role_Attrib_SheShuCritLevel,					//射术爆击等级
	Role_Attrib_SheShuMultipiler,					//射术伤害系数%

	Role_Attrib_YaoShuCrit,							//妖术暴击率%
	Role_Attrib_YaoShuCritLevel,					//妖术爆击等级
	Role_Attrib_YaoShuMultipiler,					//妖术伤害系数%

	Role_Attrib_XianShuCrit,						//仙术暴击率%
	Role_Attrib_XianShuCritLevel,					//仙术爆击等级
	Role_Attrib_XianShuMultipiler,					//仙术伤害系数%
	////////////////////////////////////
	////伤害吸收反射   Absorb：吸收    Rebound：反射
	/////////////////////////////////////
	Role_Attrib_MeleeDamageAbsorb = 801,
	Role_Attrib_MeleeDamageAbsorbRate,
	Role_Attrib_MeleeDamageRebound,					//近程伤害反射
	Role_Attrib_MeleeDamageReboundRate,				//近程伤害反射率%

	Role_Attrib_RangeDamageAbsorb = 806,
	Role_Attrib_RangeDamageAbsorbRate,
	Role_Attrib_RangeDamageRebound,
	Role_Attrib_RangeDamageReboundRate,

	Role_Attrib_DamageAbsorb = 811,
	Role_Attrib_DamageAbsorbRate,
	Role_Attrib_DamageRebound,						//物理伤害反射
	Role_Attrib_DamageReboundRate,					//物理伤害反射率

	Role_Attrib_FireDamageAbsorb = 816,
	Role_Attrib_FireDamageAbsorbRate,
	Role_Attrib_FireDamageRebound,
	Role_Attrib_FireDamageReboundRate,

	Role_Attrib_ColdDamageAbsorb = 821,
	Role_Attrib_ColdDamageAbsorbRate,
	Role_Attrib_ColdDamageRebound,
	Role_Attrib_ColdDamageReboundRate,

	Role_Attrib_LightningDamageAbsorb = 826,
	Role_Attrib_LightningDamageAbsorbRate,
	Role_Attrib_LightningDamageRebound,
	Role_Attrib_LightningDamageReboundRate,

	Role_Attrib_PoisonDamageAbsorb = 831,
	Role_Attrib_PoisonDamageAbsorbRate,
	Role_Attrib_PoisonDamageRebound,
	Role_Attrib_PoisonDamageReboundRate,

	Role_Attrib_HealingAbsorb = 836,    //无意义
	Role_Attrib_HealingAbsorbRate,		//无意义
	Role_Attrib_HealingRebound,
	Role_Attrib_HealingReboundRate,

	Role_Attrib_SpellDamageAbsorb =	866,
	Role_Attrib_SpellDamageAbsorbRate,
	Role_Attrib_SpellDamageRebound,				//魔法伤害反射
	Role_Attrib_SpellDamageReboundRate,			//魔法伤害反射率%

	Role_Attrib_AllDamageAbsorb = 871,			//所有伤害吸收值
	Role_Attrib_AllDamageAbsorbRate,			//所有伤害吸收率%
	Role_Attrib_AllDamageRebound,				//所有伤害反射值
	Role_Attrib_AllDamageReboundRate,			//所有伤害反射率%

	Role_Attrib_HpDrain = 881,
	Role_Attrib_HpDrainRate,
	Role_Attrib_HpDrainRateMax,

	Role_Attrib_MpDrain = 886,
	Role_Attrib_MpDrainRate,
	Role_Attrib_MpDrainRateMax,

	//////////////////////////////////////
	/////速度
	//////////////////////////////////////
	Role_Attrib_AttackSpeed = 901,
	Role_Attrib_CastRate,
	Role_Attrib_RunSpeed,
	Role_Attrib_BaseRunSpeed,
	Role_Attrib_MovingForm,
	Role_Attrib_WalkSpeed,

	Role_Attrib_FastAttackSpeed = 911,
	Role_Attrib_FastCastRate,
	Role_Attrib_FastRunWalk,					//移动速度%

	Role_Attrib_DamageToMana = 921,				//伤害转移给法力
	Role_Attrib_DamageToManaRate,				//伤害百分比转移给发力 


	Role_Attrib_SkillLevel	= 931,				//提高技能等级
	Role_Attrib_IgnoreTargetDefence,			//无视目标所有防御%
	Role_Attrib_IgnoreTargetDefenceRating,		//忽视敌人防御% （废弃）
	Role_Attrib_BetterChanceofItemFind,			//提高掉宝几率
	Role_Attrib_IncreaseAllAttribute,			//提高所有属性
	Role_Attrib_IncreaseAllAttributeEnhance,	//提高所有属性百分比

	Role_Attrib_LearnNewSkill = 941,
	Role_Attrib_AddNewSkill = 946,

	Role_Attrib_SummonCombatPet = 951,				//召唤战宠
	Role_Attrib_EnhanceSkill,					//强化技能


	Role_Attrib_IncreaseCommonAttackArea = 961, //改变普通攻击的攻击范围
	Role_Attrib_IncreaseAllArea,

	Role_Attrib_SoulAttrib_HpEnhance     = 971,   //元神属性加成      Hp						   血值
	Role_Attrib_SoulAttrib_DamagePhysicalEnhance, //元神属性加成     //Role_Attrib_DamagePhysical  物功
	Role_Attrib_SoulAttrib_DamageSpellEnhance,    //元神属性加成     //Role_Attrib_DamageSpell     魔功
	Role_Attrib_SoulAttrib_ArmorEnhance,		  //元神属性加成     //Role_Attrib_Armor           物防  
	Role_Attrib_SoulAttrib_SpellResistEnhance,    //元神属性加成     // Role_Attrib_SpellResist    魔防

	/////////////////////////////////////////
	////
	/////////////////////////////////////////
	Role_Attrib_Level = 1001,					// 等级
	Role_Attrib_Experience,						// 经验
	Role_Attrib_MaxExperience,
	Role_Attrib_ExperienceGained,				//当前经验加成
	Role_Attrib_Type,							//Type
	Role_Attrib_CurrentSuit,
	Role_Attrib_PictureID,						//头像ID
	Role_Attrib_Hair,
	Role_Attrib_AIType,
	Role_Attrib_Gold,							//金子
	Role_Attrib_GoldBind,						//绑定金子
	Role_Attrib_Silver,							//银子
	Role_Attrib_SilverBind,						//绑定银子
	Role_Attrib_StashGold,						//
	Role_Attrib_StashGoldBind,
	Role_Attrib_StashSilver,					//信用银子（现在用作家族工资）
	Role_Attrib_StashSilverBind,				//绑定信用银子(现在用作每日消费上限)
	Role_Attrib_Credit,							//功勋值
	Role_Attrib_AttributePoints,
	Role_Attrib_SkillPoints,
	Role_Attrib_Invulnerability,
	Role_Attrib_Invisibility,
	Role_Attrib_ChanceOfRebound,				//伤害减免
	Role_Attrib_Inventorys,
	Role_Attrib_Stashes,
	Role_Attrib_UIPos,
	Role_Attrib_AIGroup,
	Role_Attrib_HolyStrike,						// 致命一击%
	Role_Attrib_SceneID,						// 角色当前场景ID
	Role_Attrib_Postion_x,						// 玩家当前的坐标 x
	Role_Attrib_Postion_y,						// 玩家当前的坐标 y
	Role_Attrib_Postion_z,						// 玩家当前的坐标 z
	Role_Attrib_StateID,						// 国家ID
	Role_Attrib_DangID,							// 帮会ID
	Role_Attrib_FamilyID,						// 家族ID
	Role_Attrib_TitleID,						// 称号ID
	Role_Attrib_LeaveFamilyTime,				// 离开家族时间
	Role_Attrib_HonorStar,						// 荣誉之星
	Role_Attrib_Wencai,                         // 文采
	Role_Attrib_QuestionPoint,					// 答题得分
	Role_Attrib_ExplorerRange,					// 同屏表范围
	Role_Attrib_TeamID,							// 队伍ID
	Role_Attrib_CatID,							// 镖车ID
	Role_Attrib_Online_Time,					// 角色在线时间
	Role_Attrib_Job,							// 角色职业
	Role_Attrib_JobRamify,						// 角色职业分枝
	Role_Attrib_CombineID,						// 人物合体后的效果ID
	Role_Attrib_LuaID,		                    // 脚本AI
	Role_Attrib_ClearingHouse_Gold,				// 交易所存储金子
	Role_Attrib_ClearingHouse_Silver,			// 交易所存储银子
	Role_Attrib_Visish,							// 是否隐藏的标识	//--修改注释，把“是否Draw的标识”改为“是否隐藏的标识”
	Role_Attrib_MasterPID,						// 主人的PID
	Role_Attrib_UseGold,						// 默认选择使用的货币
	Role_Attrib_UseSilver,						// 默认选择使用的货币
	Role_Attrib_DamageTurnPID,					// 伤害转移到另一个人身上
	Role_Attrib_DamageTurnPer,					// 伤害转移到另一个人身上的比例
	Role_Attrib_CampaignID,						// 活动ID
	Role_Attrib_ServerID,						// 服务器ID
	Role_Attrib_PetProp,						// 掉落的可召唤道具
	Role_Attrib_QuestID,						// 只能有指定任务才能被攻击
	Role_Attrib_Dead_Drop_Type,					// 死亡掉落类型
	Role_Attrib_Dead_Drop_Num,					// 死亡掉落的数量
	Role_Attrib_Dead_Drop_Money,				// 死亡掉落的金钱
	Role_Attrib_Current_RidID,					// 当前骑乘ID
	Role_Attrib_Color,							// 颜色
	Role_Attrib_UpdateTime,						// 刷新时间
	Role_Attrib_WuXing,							// 五行属性
	Role_Attrib_Birth_Time,						// 出生时间
	Role_Attrib_State_Stone,					// 所抢的国家晶石 国家+颜色
	Role_Attrib_Honor,							// 荣誉值
	Role_Attrib_Today_Honor,					// 今日荣誉值
	Role_Attrib_Murderer,						// 凶手
	Role_Attrib_Anonymous,						// 匿名
	Role_Attrib_Energy,							// 精力值（目前用作记录活力值）
	Role_Attrib_Jump_StateFlag,					// 跳转国家的标记
	Role_Attrib_Position,						// 位置信息
	Role_Attrib_UnreadMailCount,				// 未读邮件数量
	Role_Attrib_FamilyCarTID,					// 家族战车索引
	Role_Attrib_FamilyCarPID,					// 家族战车PID, 玩家当前已登上的战车PID
	Role_Attrib_FamilyCarDriver,			//是否是家族战车司机
	Role_Attrib_PlayerSwitch,                   // 玩家开关
	Role_Attrib_FollowPID,						// 跟随的PID
	Role_Attrib_Stall_TID,						// 玩家摆摊车的TID
	Role_Attrib_Stall_PID,						// 玩家摆摊车的PID
	Role_Attrib_Stall_Name,						// 摆摊车名字
	Role_Attrib_Stall_Note,						// 摆摊车内容
	Role_Attrib_Stall_Type,						// 摆摊类型
	Role_Attrib_KillDust,						// 所杀的对象
    Role_Attrib_EffectValue,                    // 角色身上所中的效果，比如buff的效果
	Role_Attrib_Change_TID,						// 改变Model TID
	Role_Attrib_Change_ClientID,				// 改变Model TID
	Role_Attrib_Combit_Pet_TID,					// 和宠物合体时宠物的TID
	Role_Attrib_Combit_Pet_ClientID,			// 和宠物合体后新模型的ClientID
	Role_Attrib_Dead_Time,						// 死亡时间
	Role_Attrib_Dead_Scene,						// 死亡的场景
	Role_Attrib_Wait_LoadScene,					// 等待加载场景
	Role_Attrib_Pneuma,							// 元气值
	Role_Attrib_ClothStyle,						// 衣服类型
	Role_Attrib_PractiseGeste,					// 历练功勋
	Role_Attrib_Talented,						// 文采							//废弃  ChenXY 2011/11/25  
	Role_Attrib_Clone,							// 外形克隆PID
	Role_Attrib_PreSceneID,						// 上次所在场景ID
	Role_Attrib_ThisWeekCredit,					// 本周功勋
	Role_Attrib_HeadEffect,						// 头顶特效
	Role_Attrib_FlowerEffect,					
	Role_Attrib_CiTanEffect,			
	Role_Attrib_BaoZangEffect,
	Role_Attrib_ShaoKaoEffect,
	Role_Attrib_RedFlowerEffectL,
	Role_Attrib_RedFlowerEffectM,
	Role_Attrib_RedFlowerEffectH,
	Role_Attrib_WhiteFlowerEffectL,
	Role_Attrib_WhiteFlowerEffectM,
	Role_Attrib_WhiteFlowerEffectH,
	Role_Attrib_BodyEffect,						//鲜花围绕特效	  add by李秋萍 2011-12-16
	Role_Attrib_SaveSilver,                     // 票号银子
	Role_Attrib_Name,
	Role_Attrib_NPCTitle,
	Role_Attrib_NPCCamp,
	Role_Attrib_CarPosition,					// 镖车位置   add by lfy 2011.9.7
	Role_Attrib_CarSceneID,						// 镖车场景实体ID add by lfy 2011.9.7
	Role_Attrib_PropertyProtect,                // 财产保护
	Role_Attrib_ProtectOverTime,                // 财产保护-记录取消财产保护密码时间 
	Role_Attrib_ProtectEquipOverTime,			// 财产保护-记录取消装备财产保护时间 
	Role_Attrib_SoulType,                       // 角色元魂类型
	Role_Attrib_SafetyTime,                     // 安全时限
	Role_Attrib_SafetyTimeOverTime,             // 安全时限-记录修改安全时限时间
	Role_Attrib_OpenSoulState,                  // 角色元魂开启状态
	Role_Attrib_CombatCredit,					// 战斗功勋
	Role_Attrib_SafetyTimeTemp,                 // 下调安全时限时间
	Role_Attrib_ForbidSpeakTime,				// 禁言时间
	Role_Attrib_IsInSealState,                  //是否处于封印状态
	Role_Attrib_SealOverTime,                   //封印结束时间
	Role_Attrib_PKCamp,						    //PK阵营 enum PK_CAMP
	Role_Attrib_SefeGuardFellowID,				// 守护珍兽ID，根据此值来判断守护的开启状态，当无效时为没有开启守护状态
	Role_Attrib_HistoryCombatCredit,		    //历史战斗功勋
	Role_Attrib_HeroWinTimes,					//今日玩家胜利次数
	Role_Attrib_AutoReLiveTime,					//玩家死亡后自动安全复活的时间
	Role_Attrib_TopRewardFlag,					//玩家昨日Top领取奖励标志
	Role_Attrib_TopWeekRewardFlag,				//玩家上周Top领取奖励标志
	Role_Attrib_Clone_TemplateID,				// 外形克隆角色模板ID
	Role_Attrib_Clone_Hair,						// 外形克隆角色发型
	Role_Attrib_Clone_ClothStyle,				// 外形克隆角色风格
	Role_Attrib_Clone_EquipOne,					// 外形克隆角色装备：武器
	Role_Attrib_Clone_EquipTwo,					// 外形克隆角色装备：衣服
	Role_Attrib_TopWorldLevelRanking,           // 玩家世界等级排名
	Role_Attrib_TopStateLevelRanking,           // 玩家国家等级排名
	Role_Attrib_CurrentBodyFlower,				//当前身上鲜花围绕特效 add by 李秋萍 2011-12-16
	Role_Attrib_PKType,							// PK类型enum PK_TYPE，注意区分enum PK_STATUS add by zhangjianli 2012-01-13
	Role_Attrib_HeroIslandPoints_1,				// 点将台1当日积分
	Role_Attrib_HeroIslandPoints_2,				// 点将台2当日积分
	Role_Attrib_HeroIslandPoints_3,				// 点将台3当日积分
	Role_Attrib_HeroIslandCurrency,				// 点将台兑换积分
	Role_Attrib_ProtectLinShiQuXiao,			// 财产保护临时取消
	Role_Attrib_SystemSet,						// 系统设置
	Role_Attrib_FreezeFreeTime,					//解除冻结时间
	Role_Attrib_HeadString,						//头顶文字
	Role_Attrib_StateWarKillCount,				//国战击杀数量
	Role_Attrib_DragonCoin,						//龙币数量
	Role_Attrib_TempNPCChar,					//NPC临时字符串属性
	Role_Attrib_PlayerCreateTime,				//角色创建时间
	Role_Attrib_PreChangeStateTime,				//上一次换国时间
	Role_Attrib_GMLevel,						//执行GM指令所需GM等级
	Role_Attrib_LeaveFamilyCredit,				//剩余家族贡献
	Role_Attrib_FloodEnergy,                    //溢出活值
	Role_Attrib_FamilyName,			
	Role_Attrib_GangName,	
	Role_Attrib_PID,
	Role_Attrib_OnlineFlag,						//在线标记
	Role_Attrib_CombatCredit_ExchangeNum,		//战斗功勋兑换次数 add by zhangjianli 2012-10-12
	Role_Attrib_CallHeroLandRanking,			//点将台当前排名

	Role_Attrib_ExchangePos	= 1300,				// 交换位置
	Role_Attrib_ReturnTown,						// 第一次使用记录位置,第二次传送回记录位置。
	Role_Attrib_ClearTime,						// 清零的时间
	//Role_Attrib_RedNameTime,                    // 名字颜色持续时间			//--记录红名时间改为记录PK值-- change by zhaoguoze 2011-03-15
	Role_Attrib_PKValue,	                    //--PK值	 注：设置PK值的时候最好调用CPKMgr::SetPKValue(int nValue)方法--
	//Role_Attrib_PrisonTime,                     // 坐牢持续时间	//--改为[被国王关进监狱的剩余时间]-- change by zhaoguoze 2011-11-01
	Role_Attrib_PrisonTimeByKing,               //被国王关进监狱的剩余时间（秒）
	//Role_Attrib_RedNameFlag,                    // 红名颜色系统标记				//--修改为PK状态标记，还用这个名字和字段--
	Role_Attrib_PKStatus,						//--PK状态标记  enum PK_STATUS--
	Role_Attrib_NotInquiry,						// 不能和NPC对话
	Role_Attrib_CombinCombatPet_Damage = 1309,	// 合体后伤害增加
	Role_Attrib_LifeTime,						// 生命期
	Role_Attrib_GangContribute,                 // 帮会贡献度
	Role_Attrib_ModelID,						// 模型ID
	Role_Attrib_Exit_Time,						// 下线时间
	Role_Attrib_Login_Time,						// 上线时间
	Role_Attrib_AttckID,						// 普通攻击
	Role_Attrib_PropertyLock,					// 财产锁定状态
	Role_Attrib_PropertyPwd,					// 财产保护密码
	Role_Attrib_NotUseSpell,					// 被禁魔
	Role_Attrib_NotControl,						// 不能控制
	Role_Attrib_NotMove,						// 不能移动
	Role_Attrib_Stealth,						//隐形(0是否，》0是隐身）
	Role_Attrib_DisableStealth,					//反隐形
	Role_Attrib_PhysicsInvincible,				//物理免疫
	Role_Attrib_SpellInvincible,				//魔法免疫
	Role_Attrib_Reflection,						//反射伤害
	Role_Attrib_ExtBagNum,						//仓库中购买背包位置的数量
	Role_Attrib_CreatePID,						//创建者的PID
	Role_Attrib_MonsterExpAdd,					//杀怪经验加成
	Role_Attrib_FirInvincible,					//火免疫
	Role_Attrib_ColdInvincible,					//冰免疫
	Role_Attrib_LightningInvincible,			//电免疫
	Role_Attrib_PosionInvincible,				//毒免疫
	Role_Attrib_BurnInvincible,					//灼烧免疫
	Role_Attrib_HealingInvincible,				//治疗免疫
	Role_Attrib_SlienceInvincible,				//沉默免疫（2009.11.2目前唯一的对状态免疫的属性，一般是boss用）
	Role_Attrib_FuZhouInvincible,				//符咒免疫
	Role_Attrib_CorpseTime,						//尸体保留时间
	Role_Attrib_CurrentWaitPID,					//当前侍从
	Role_Attrib_CurrentCombatPID,				//当前战宠
	Role_Attrib_CurrentCombatName,			//战宠名字
	Role_Attrib_UnBeatable,						//无敌状态
	Role_Attrib_LockUI,							//锁定界面状态
	Role_Attrib_CurrentCastingSkillID,			//当前的casting技能ID	（废弃，casting技能ID保存在状态机中）
	Role_Attrib_CurrentLifeSkillID,				//当前生活技能id
	Role_Attrib_Question_HeroTop,				//玩家答题竞赛中自己的排名
	Role_Attrib_AutoDriveFlag,			    	//自动驾驶的标记
	Role_Attrib_Version,						//版本信息 add by mayanling 2010-3-23
	Role_Attrib_Hidden,							//蒙面状态
	Role_Attrib_NoEnemy,						//不记录愁人列表
	Role_Attrib_QuestFollow,					//任务跟随单位
	Role_Attrib_Angle,							//角色面向的角度
	Role_Attrib_CastingPropID,					//道具吟唱技能的道具（废弃，吟唱技能的道具保存在状态机中）
	Role_Attrib_LastChangeHonor,				//上次荣誉兑换时间
	Role_Attrib_GetGiftIndex,					//领取的礼包数
	Role_Attrib_GetGiftToday,			//当天领取礼包数
	Role_Attrib_ChaseDistance,					//追击距离（默认值为-1，追击到死）
	Role_Attrib_WuShuInvincible,				//武术免疫
	Role_Attrib_FaShuInvincible,				//法术免疫
	Role_Attrib_SheShuInvincible,				//射术免疫
	Role_Attrib_YaoShuInvincible,				//妖术免疫
	Role_Attrib_XianShuInvincible,				//仙术免疫
	Role_Attrib_Client_Vision,					//玩家自己设置的屏蔽其他玩家
	Role_Attrib_First_Login,						//第一次登录时间
	Role_Attrib_PrayIndex,						//当天求签次数
	Role_Attrib_PreReqSelfStateFtoTime,			//上次请求本国家族排行榜时间
	Role_Attrib_PreReqWorldFtoTime,				//上次请求世界家族排行榜时间
	Role_Attrib_IsAllowSeeEquip,				//是否允许对方查看自身装备
	Role_Attrib_WorldQuestion_JoinState,		//答题的状态
	Role_Attrib_IsAblepsia,						//是否失明
	Role_Attrib_ConvoyState,					//护送状态
	Role_Attrib_GetDayGiftIndex,                //每日领取礼包界面中,领取的礼包数

	Role_Attrib_Current_Campaign_ID=1380,		//当前活动类型
	Role_Attrib_Stone_Num,						//天石数量
	Role_Attrib_Stone_Flag,						//偷天石次数
	Role_Attrib_SHENGXIANG_Dead_Num,			//砍圣像次数
	Role_Attrib_QI_Num,							//砍旗次数
	Role_Attrib_Get_LaoLong_Num,				//获取牢笼次数
	Role_Attrib_Action_Huangshiweiji,			//皇室危机活动次数
	Role_Attrib_FlowerWhite_History_Num,		//历史白玫瑰花数量
	Role_Attrib_FlowerWhite_Today_Num,			//今日白玫瑰花数量
	Role_Attrib_FlowerRed_History_Num,			//历史红玫瑰花数量
	Role_Attrib_FlowerRed_Today_Num,			//今日红玫瑰花数量





	Role_Attrib_Open_Box_Count	= 1400,			//开箱子次数
	Role_Attrib_Kill_Enemy,						//杀敌人数
	Role_Attrib_Kill_Minister,					//杀大臣的数量
	Role_Attrib_Rose_Number,					//日玫瑰数量
	Role_Attrib_History_Rose_Number,			//累计玫瑰数量
	Role_Attrib_Kill_Other_Country_Minister,	//击杀别国大臣数
	Role_Attrib_DoubleExp_Time,					//领取双倍经验时间
	Role_Attrib_DoubleExp_Count,				//领取双倍经验次数
	Role_Attrib_Honor_ExchangeNum,				//荣誉值兑换数量
	Role_Attrib_Campaign_PK,					//活动时的pk规则


	Role_Attrib_Status_Craft_Type =1500,		//	生活技能状态类型
	Role_Attrib_Status_Dance_Type,				//	休闲技能状态类型
	Role_Attrib_Status_Express_Type,			//  表情状态类型
	Role_Attrib_Status_Bomb_Type,				//   携带炸弹状态类型
	Role_Attrib_Status_LionDance_Time,			//	舞狮同步给客户端的剩余时间
	Role_Attrib_Question_JoinNum,				//  个人答题次数
	Role_Attrib_LuckyStarNum,					//	幸运星数量

	Role_Attrib_NPC_CurrentTime=1600,			//	npc当前时间
	Role_Attrib_NPC_CartoonFlag,				// npc批动画标记
	Role_Attrib_NPC_TargetPID,					// npc目标的PID
	Role_Attrib_NPC_CampainStart,				//npc管理的活动是否处于开始状态
	Role_Attrib_Car_PolicyHolder ,				// 投保本镖车的玩家（仅用于镖车）

	Role_Attrib_ExtInt32_1 = 1700,				//npc扩展参数
	Role_Attrib_ExtInt32_2,
	Role_Attrib_ExtInt32_3,
	Role_Attrib_ExtInt32_4,
	Role_Attrib_ExtInt32_5,
	Role_Attrib_ExtInt32_6,
	Role_Attrib_ExtInt32_7,
	Role_Attrib_ExtInt32_8,
	Role_Attrib_ExtInt32_9,
	Role_Attrib_ExtInt32_10,
	Role_Attrib_ExtInt64_1,
	Role_Attrib_ExtInt64_2,
	Role_Attrib_ExtInt64_3,
	Role_Attrib_ExtInt64_4,
	Role_Attrib_ExtInt64_5,
	Role_Attrib_ExtInt64_6,
	Role_Attrib_ExtInt64_7,
	Role_Attrib_ExtInt64_8,
	Role_Attrib_ExtInt64_9,
	Role_Attrib_ExtInt64_10,

	Role_Attrib_Player_ExtInt64_1 = 1800,		//player扩展背包
	Role_Attrib_Player_ExtInt64_2,              //桃园结义  标记是否进入 种植区域
	Role_Attrib_Player_ExtInt64_3,
	Role_Attrib_Player_ExtInt64_4,
	Role_Attrib_Player_ExtInt64_5,
	Role_Attrib_Player_ExtInt64_6,
	Role_Attrib_Player_ExtInt64_7,
	Role_Attrib_Player_ExtInt64_8,
	Role_Attrib_Player_ExtInt64_9,
	Role_Attrib_Player_ExtInt64_10,


	Role_Attrib_CarPostionX		=1900,			//镖车所在位置X
	Role_Attrib_CarPostionY,					//镖车所在位置Y
	Role_Attrib_CarSceneTID,					//镖车所在场景TID
	Role_Attrib_CarTemplateID,					//镖车模板id，用于跨场景寻路
	Role_Attrib_CarAlarmPosX,					//记录救镖的当前位置x
	Role_Attrib_CarAlarmPosY,					//记录救镖的当前位置y
	Role_Attrib_AlarmCarPID,					//需要救镖的镖车PID
	Role_Attrib_AlarmReturnSenceID,				//救镖前的场景id
	Role_Attrib_CarMoney,						//扣除在镖车上的镖金
	Role_Attrib_AdventureTime,					//奇遇时间
	Role_Attrib_AttackCarPlayerID,				//攻击镖车的玩家
	Role_Attrib_QuestMaster,					//能看见自己的任务玩家
	Role_Attrib_DailyRefreshTime,				//每日任务刷新时间


	Role_Attrib_Status = 2001,
	Role_Attrib_IncreaseChanceOfPoison,			//提高中毒概率
	Role_Attrib_IncreaseChanceOfAblepsia,		//提高失明概率
	Role_Attrib_IncreaseChanceOfFreeze,			//提高冰冻概率
	Role_Attrib_IncreaseChanceOfBurn,			//提高灼烧概率
	Role_Attrib_IncreaseChanceOfStun,			//提高眩晕概率
	Role_Attrib_IncreaseChanceOfSlow,			//提高减速概率
	Role_Attrib_IncreaseChanceOfImmobilize,		//提高定身概率
	Role_Attrib_IncreaseChanceOfConfuse,		//提高混乱概率
	Role_Attrib_IncreaseChanceOfSlience,		//提高沉默概率

	Role_Attrib_ReduceChanceOfPoison,			//降低中毒概率
	Role_Attrib_ReduceChanceOfAblepsia,			//降低失明概率
	Role_Attrib_ReduceChanceOfFreeze,			//降低冰冻概率
	Role_Attrib_ReduceChanceOfBurn,				//降低灼烧概率
	Role_Attrib_ReduceChanceOfStun,				//降低眩晕概率
	Role_Attrib_ReduceChanceOfSlow,				//降低减速概率
	Role_Attrib_ReduceChanceOfImmobilize,		//降低定身概率
	Role_Attrib_ReduceChanceOfConfuse,			//降低混乱概率
	Role_Attrib_ReduceChanceOfSlience,			//降低沉默概率

	Role_Attrib_Pet_Ghost_PhysicalDamageEnchance = 2050,	//鬼魅物理攻击%
	Role_Attrib_Pet_Aqua_PhysicalDamageEnchance,			//水灵物理攻击%
	Role_Attrib_Pet_Fire_PhysicalDamageEnchance,			//火灵物理攻击%
	Role_Attrib_Pet_Dark_PhysicalDamageEnchance,			//暗灵物理攻击%
	Role_Attrib_Pet_Wind_PhysicalDamageEnchance,			//风灵物理攻击%

	Role_Attrib_Pet_Ghost_ArmorEnchance = 2060,	//鬼魅物理防御%
	Role_Attrib_Pet_Aqua_ArmorEnchance,			//水灵物理防御%
	Role_Attrib_Pet_Fire_ArmorEnchance,			//火灵物理防御%
	Role_Attrib_Pet_Dark_ArmorEnchance,			//暗灵物理防御%
	Role_Attrib_Pet_Wind_ArmorEnchance,			//风灵物理防御%

	Role_Attrib_Pet_Ghost_SpellEnchance = 2070,	//鬼魅魔法攻击%
	Role_Attrib_Pet_Aqua_SpellEnchance,			//水灵魔法攻击%
	Role_Attrib_Pet_Fire_SpellEnchance,			//火灵魔法攻击%
	Role_Attrib_Pet_Dark_SpellEnchance,			//暗灵魔法攻击%
	Role_Attrib_Pet_Wind_SpellEnchance,			//风灵魔法攻击%

	Role_Attrib_Campaign1				= 2080, //玩家接受的活动
	Role_Attrib_Campaign2,
	Role_Attrib_Campaign3,
	Role_Attrib_Campaign4,
	Role_Attrib_Campaign5,
	Role_Attrib_Campaign6,
	Role_Attrib_Campaign7,
	Role_Attrib_Campaign8,
	Role_Attrib_Campaign9,
	Role_Attrib_Campaign10,

	Role_Attrib_ChatGroup1			  = 2090,	//群聊
	Role_Attrib_ChatGroup2,
	Role_Attrib_ChatGroup3,
	Role_Attrib_ChatGroup4,
	Role_Attrib_ChatGroup5,

	//////////////////////////////////////////////////////////////////////////
	//从personai 移出来的 变量与属性对应的移出(有些没加到这里)
	//playerai
	Role_Attrib_ProgressTime		   = 2100,	//进度条时间
	Role_Attrib_Spyable,						//侦查能力
	Role_Attrib_AutoRelive,						//自动复活标记
	Role_Attrib_FriendNPCTID,					//友好NPC的模板
	Role_Attrib_AutoAttackType,					//自动攻击标志
	Role_Attrib_RecoverTime,					//恢复时间
	Role_Attrib_IsSendAttack,					//是否发送过攻击指令

	//personai
	//Role_Attrib_Invulnerability,				// 是否无敌(这个属性重了)
	//Role_Attrib_Invisibility,					// 是否隐身(这个属性重了)
	Role_Attrib_HoldTime,						//保留时间

	//SkillZoneAI
	//ZoneAI
	//PortalAI

	//ridai

	//waiterai
	Role_Attrib_BaseIntervalTime,

	//CCarriageAI
	Role_Attrib_CarriageLoseTime,					//玩家离开镖车一屏时，任务的失败时间，秒(Carriage)
	Role_Attrib_CarriageQID,						//存储任务id	(Carriage)

	//AutoMoveAI
	Role_Attrib_AutoMoveLoseTime,					//玩家离开镖车一屏时，任务的失败时间，秒(AutoMove)

	Role_Attrib_ReviveInsituTimes,					//玩家安全复活次数  add by zhangjianli 2011-10-12
	Role_Attrib_ReviveFullStatusTimes,				//玩家满状态复活次数
	Role_Attrib_FellowRefinery_DayTimes,			//玩家一天炼化珍兽的次数 add by zhangjianli 2012-7-13

	Role_Attrib_Space_Age            =2200,          //人物空间年龄属性               
	Role_Attrib_Space_City,							//人物空间城市属性
	Role_Attrib_Space_Area,							//人物空间地区属性
	Role_Attrib_Space_SignName,						//人物空间签名属性
	Role_Attrib_Space_Sex,							//人物空间性别属性
	Role_Attrib_Current_Designation,				//人物属性界面当前称号
	Role_Attrib_DesinationExtraText,
	Role_Attrib_DesinationExtraJieBai,				//特殊文字特殊处理
	Role_Attrib_Effect_Designation,					//特效称号

	Role_Attrib_RGBColor			=2500,			//RGB颜色
	Role_Attrib_ModelColor,							//玩家颜色遮罩

	//账号功能扩展点
	Role_Attrib_UserExtPoint1		= 2900,			
	Role_Attrib_UserExtPoint2,						//	第二扩展点 使用于激活码礼包(被占) by zlm 2012.7.16
	Role_Attrib_UserExtPoint3,						//	第三扩展点 使用于兑换码礼包(被占) by zlm 2012.7.16
	Role_Attrib_UserExtPoint4,
	Role_Attrib_UserExtPoint5,
	Role_Attrib_UserExtPoint6,
	Role_Attrib_UserExtPoint7,
	Role_Attrib_UserExtPoint8,

	//Prop Attribute
	Prop_Attrib_Damage					= 3001,	//道具伤害
	Prop_Attrib_DamageEnhance,					//道具伤害加成
	Prop_Attrib_BaseDamage,						//道具基础伤害

	Prop_Attrib_Spell,							//魔法攻击
	Prop_Attrib_SpellEnhance,					//魔法伤害加成
	Prop_Attrib_BaseSpell,						//基础魔法伤害

	Prop_Attrib_Armor,
	Prop_Attrib_ArmorEnhance,
	Prop_Attrib_BaseArmor,						//基础物理防护

	Prop_Attrib_SpellResist,
	Prop_Attrib_SpellResistEnhance,
	Prop_Attrib_BaseSpellResist,				//基础魔法抵抗

	Prop_Attrib_HealthPoint,
	Prop_Attrib_HealthPointEnhance,
	Prop_Attrib_BaseHealthPoint,				//基础生命值

	Prop_Attrib_DoubleArmor,					//道具双防值
	Prop_Attrib_DoubleArmorEnhance,				//道具双防值加成

	Prop_Attrib_BasePoint,						//道具模版基础参考点数
	Prop_Attrib_Level = 3031,					//道具等级
	Prop_Attrib_SchoolType,						//道具的伤害系
	Prop_Attrib_Type,							//道具类型
	Prop_Attrib_BindType,						//绑定类型
	Prop_Attrib_Quality,						//道具品质
	Prop_Attrib_StackSize,						//道具的堆叠数
	Prop_Attrib_MaxStackSize,					//道具最大堆叠数
	Prop_Attrib_Durability,						//耐久度
	Prop_Attrib_MaxDurability,					//最大耐久度
	Prop_Attrib_StallPrice,						//摆摊出售价格
	Prop_Attrib_Gold,							//黄金价格
	Prop_Attrib_Silver,							//银币价格
	Prop_Attrib_GoldBind,						//绑定金币价格
	Prop_Attrib_SilverBind,						//绑定银币价格
	Prop_Attrib_Name,
	Prop_Attrib_NameBase,						//道具的类型名称
	Prop_Attrib_NameMid,						//中间名
	Prop_Attrib_NamePre,						//前缀名
	Prop_Attrib_Star,							//
	Prop_Attrib_Hole,							//打孔数
	Prop_Attrib_PictureID,						//
	Prop_Attrib_Class,							//等级段
	Prop_Attrib_UIPost,							//道具的位置
	Prop_Attrib_Sign,							//签名
	Prop_Attrib_BindPID,						//绑定对象
	Prop_Attrib_HoleColor,						//孔颜色
	Prop_Attrib_HoleGem,						//孔镶嵌的宝石
	Prop_Attrib_HoleEffect,						//宝石效果
	Prop_Attrib_HoleActive,						//孔激活
	Prop_Attrib_ActiveUIPos,					//快捷栏位置
	Prop_Attrib_FloorModel,						//掉落地面模型ID
	Prop_Attrib_StatID,							//国家
	Prop_Attrib_Flag,							//种族，职业，合成，拆分等各种限制
	Prop_Attrib_Note_TextID,					//道具的说明文字ID（如果是书信，就是书信的内容）
	Prop_Attrib_Parent_PID,						//父物体PID
	Prop_Attrib_ZhanhunTemplateID,				//激活战魂链目标位置的道具模板ID
	Prop_Attrib_ZhanhunStatID,					//激活战魂链目标位置的道具国家ID
	Prop_Attrib_TemplateID,
	Prop_Attrib_UseNum,							//道具的使用次数
	Prop_Attrib_PetPID,							//和道具绑定的宠物PID
	Prop_Attrib_CustomName,						//道具自定义名称
	Prop_Attrib_SignName,						//签名玩家的名字
	Prop_Attrib_TransSceneID,					//记忆卷轴记录的传送位置
	Prop_Attrib_TransPosX,						//记忆卷轴记录的传送位置
	Prop_Attrib_TransPosY,						//记忆卷轴记录的传送位置
	Prop_Attrib_SplitNum,						//道具拆分数量
	Prop_Attrib_LifeTime,						//使用时限
	Prop_Attrib_EquipLifeTime,					//装备时限
	Prop_Attrib_SkillID,						//道具技能ID
	Prop_Attrib_PortalPosX,
	Prop_Attrib_PortalPosY,
	Prop_Attrib_PortalScene,
	Prop_Attrib_FamilyMedal,
	Prop_Attrib_LevelMax,						//最高等级
	Prop_Attrib_GainTime,						//获得道具的时间
	Prop_Attrib_BeginEquipTime,					//开始装备的时间
	Prop_Attrib_SceneID,						//掉落场景ID
	Prop_Attrib_TimeInScene,					//进入场景时间
	Prop_Attrib_QuestID,						//任务ID
	Prop_Attrib_QuestMonster,					//任务宿主npc
	Prop_Attrib_DamageSchool,					//道具技能伤害系
	Prop_Attrib_MusicID,						//道具音效
	Prop_Attrib_LuaID,							//道具LuaID
	Prop_Attrib_UseCount_Time,					//道具的使用次数 时间类型
	Prop_Attrib_UseCount_Num,					//道具在规定时间内的使用次数
	Prop_Attrib_UseCount_KeyWords,				//道具使用次数的 关键字

	//Skill
	Skill_Attrib_NameID = 4001,			// skill 的 名称
	Skill_Attrib_DamageSchool,			//伤害类型
	Skill_Attrib_DamageArea,			//伤害范围
	Skill_Attrib_MpCast,				//能量消耗
	Skill_Attrib_Flag,
	Skill_Attrib_AAIType,
	Skill_Attrib_TTargetID,				// 目标类型
	Skill_Attrib_TargetNum,
	Skill_Attrib_MinLevel,				// 最小限制等级
	Skill_Attrib_StatusRestrict,		// 状态限制
	Skill_Attrib_WeapenRestrict,		// 武器限制
	Skill_Attrib_WeapenAssistant,		// 副手武器限制
	Skill_Attrib_IntervalTime,			// 每隔n秒伤害damage值
	Skill_Attrib_DamageDistanc,			// 伤害距离
	Skill_Attrib_DamageValue,			// 伤害值
	Skill_Attrib_CoolDown,				// 冷却时间
	Skill_Attrib_CastTime,				// 施法时间
	Skill_Attrib_Distance,				// 施法距离
	Skill_Attrib_CostMp,				// 魔法消耗
	Skill_Attrib_Duration,				// 技能持续时间
	Skill_Attrib_TriggerMode,			// 触发方式
	Skill_Attrib_TargetType,			// 触发目标类型
	Skill_Attrib_InterruptType,			// 打断类型
	Skill_Attrib_PropCostID,			// 消耗的道具ID
	Skill_Attrib_PropCostNum,			// 消耗的道具数量
	Skill_Attrib_PropCostPos,			// 消耗道具位置
	Skill_Attrib_PropCostPosNum,		// 消耗指定位置道具数量
	Skill_Attrib_MethodDelayTime,		// 技能招式效果延迟时间
	Skill_Attrib_BeAttackMethod,		// 被攻击招式ID
	Skill_Attrib_PictureID,				// 图片ID
	Skill_Attrib_ReadmeID,				// 技能说明ID
	Skill_Attrib_MusicID,
	Skill_Attrib_SpecialllyEffect,
	Skill_Attrib_ExtraCrit,				// 技能额外爆击几率
	Skill_Attrib_DamageEnhance,			// 提高技能伤害%
	Skill_Attrib_CDGroup,				// CD组
	Skill_Attrib_CDGroupValue,			// CDGroup Value
	Skill_Attrib_CostSp,				// 消耗怒气
	//Skill_Attrib_CostEp,				// 消耗精力
	Skill_Attrib_LifeCount,				// 生活使用次数
	Skill_Attrib_LifeLevel,				// 生活技能升级所需等级
	Skill_Attrib_SceneTemplateID,		// 场景模板ID

	//Effect
	Effect_Attrib_TemplateID		= 5000,
	Effect_Attrib_Property,			    // 属性类型 0: 有益 1: 有害
	Effect_Attrib_EventID,				// 事件ID
	Effect_Attrib_School,				// 状态类型 魔法效果 诅咒效果 中毒效果
	Effect_Attrib_ETargetID,			// 目标类型
	Effect_Attrib_TriggerType,			// 触发类型
	Effect_Attrib_TriggerRandom,		// 效果触发的几率
	Effect_Attrib_Key,					// 要改变的属性值
	Effect_Attrib_Value,				// 改变的属性值大小
	Effect_Attrib_NameID,				// 效果的名称

	//Buff
	Buff_Attirb_ClassPriority		= 5500,  // buff的种类和优先级  后3个十进制位表示同种类中优先级的高低，前面表示种类
	Buff_Attirb_Interval,					 // 间隔时间，如果是0表示是buff，立刻生效的，如果是正的表示是dot或者是定时触发的效果的间隔时间
	Buff_Attirb_Period,						 // buff的持续时间
	Buff_Attirb_Timer,
	Buff_Attirb_ReadmeID,					 // 状态说明ID
	Buff_Attirb_PictureID,					 // 图片ID
	Buff_Attirb_BuffType,					 // 状态类型
	Buff_Attirb_CasterID,					 // 施法者ID
	Buff_Attirb_KeyTable,		             // 现在是效果或者buff ID了，一个buff可以带几个子效果或者buff

	//Pet
	Role_Attrib_IncreasePetHp		= 6001,
	Role_Attrib_EnhancePetHp,
	Role_Attrib_PetHpBaseOnLevel,

	Role_Attrib_IncreasePetMp		= 6011,
	Role_Attrib_EnhancePetMp,
	Role_Attrib_PetMpBaseOnLevel,

	Role_Attrib_IncreasePetDamage  = 6021,  // 增加战宠物理攻击力
	Role_Attrib_EnhancePetDamage,			// 增加战宠物理攻击力%
	Role_Attrib_IncreasePetSpellDamage,		// 增加战宠魔法攻击力
	Role_Attrib_EnhancePetSpellDamage,		// 增加战宠魔法攻击力%

	Role_Attrib_IncreasePetArmor	= 6031,	// 增加战宠物理防御
	Role_Attrib_EnhancePetArmor,			// 增加战宠物理防御力%
	Role_Attrib_IncreasePetResist,			// 增加战宠魔防
	Role_Attrib_EnhancePetResist,			// 增加战宠魔法防御力%

	Role_Attrib_IncreasePetCritLevel= 6041,	// 增加战宠暴击等级
	Role_Attrib_IncreasePetCritEnchance,	// 增加战宠暴击率%
	Role_Attrib_PetDamageReduce,			// 增加战宠伤害减免
	Role_Attrib_PetDamageReduceEnchance,	// 增加战宠伤害减免%

	Role_Attrib_IncreasePetDodge	= 6051,	// 增加战宠躲避率
	Role_Attrib_PetRunSpeed			= 6201,	// 宠物移动速度

	Role_Attrib_PetShareDamageRate	= 6231, // 宠物分担伤害比率
	Role_Attrib_PetShareDamage,				// 宠物分担伤害数值

	Role_Attrib_PetEquip1			= 6251,	// 宠物装备1
	Role_Attrib_PetEquip2,					// 宠物装备2
	Role_Attrib_PetEquip3,					// 宠物装备3
	Role_Attrib_PetEquip4,					// 宠物装备4

	Role_Attrib_TeamMemberShareDamageRate = 6261,	//队友分担伤害百分比 add by zhangjianli 2012-9-12
	Role_Attrib_TeamMemberShareDamage,				//队友分担伤害

	//镖车
	Role_Attrib_CarTouBaoFlag = 6270, //镖车投保标记

	//Family
	Family_Attrib_FamilyID			= 7000,	// 家族ID
	Family_Attrib_CaptionID,				// 家族族长ID
	Family_Attrib_AssistantID,				// 家族副族长ID
	Family_Attrib_FireMemberID,				// 家族火神ID （用于食神）    2011-3-3
	Family_Attrib_StateID,					// 国家ID
	Family_Attrib_Level,					// 家族等级
	Family_Attrib_Active,					// 繁荣度
	Family_Attrib_Money,					// 家族资产
	Family_Attrib_GangID,					// 帮会ID
	Family_Attrib_DismissTime,				// 离解散家族还差的时间数
	Family_Attrib_LeaveGangTime,			// 离开帮会的时间
	Family_Attrib_SetCaptionTime,			// 设置族长的时间
	Family_Attrib_SetFlag,					// 设置家族标记位
	Family_Attrib_Skill_Count,				// 设置家族已学技能总数
	Family_Attrib_Name,						// 家族名称
	Family_Attrib_PSW,						// 家族秘密
	Family_Attrib_Public,					// 家族公告
	Family_Attrib_Boss_Level,				// 家族boss等级
	Family_Attrib_Boss_Exp,					// 家族boss经验
	Family_Attrib_Boss_Time,				// boss死亡的时间
	Family_Attrib_Dance_Flag,				// 正在升级的家族建筑
	Family_Attrib_Dance_StartTime,			// 家族舞狮开启时间
	Family_Attrib_DaoChang_Flag,			// 家族到达的试练到场最高层数的场景
	Family_Attrib_DaoChang_Time,			// 试练道场时间
	Family_Attrib_SelectCar_Count,			// 领取家族采集车的次数
	Family_Attrib_UseSelectCar_Count,		// 使用采集车的次数
	Family_Attrib_YunBiao_Coun,				// 领取家族镖车的次数
	Family_Attrib_YunBiao_Time,				// 领取家族镖车的时间
	Family_Attrib_JuYi_Count,				// 家族聚义次数（数据库中与请客类型合用一个字段 = 次数 * 10 + 类型）
	Family_Attrib_JuYi_TreatType,			// 家族聚义请客类型（数据库中与聚义次数合用一个字段 = 次数 * 10 + 类型）
	Family_Attrib_JuYi_StartTime,			// 家族聚义开始时间
	Family_Attrib_Zhadanren_Number,			// 炸弹人积分
	Family_Attrib_Zhadanren_TarFamilyID,	// 与自己敌对攻打炸弹人的家族id
	Family_Attrib_Zhadanren_TarFamilyNumber,// 与自己敌对攻打炸弹人的家族积分
	Family_Attrib_SelectCar_Flag,			// 家族采集状态标记
	Family_Attrib_ApplySpeciality,			// 家族上交特产
	Family_Attrib_Tiaozhan_Flag,			// 家族挑战赛报名标记，每天0点重置（-1为未报名，1为已普通报名，2为已付费报名，3为已经认输）
	Family_Attrib_Tiaozhan_TarFamilyID,		// 家族挑战赛目标家族ID,每天0点重置
	Family_Attrib_Tiaozhan_FlagNumber,		// 家族挑战赛夺旗得分，每天0点置0
	Family_Attrib_Tiaozhan_PkNumber,		// 家族挑战赛PK得分，每天0点置0
	Family_Attrib_Tiaozhan_TarPkNumber,		// 家族挑战赛目标家族PK得分，每天0点置0
	Family_Attrib_Tiaozhan_TarFlagNumber,	// 家族挑战赛目标家族夺旗得分，每天0点置0
	Family_Attrib_CurrentMemberCount,		// 当前家族成员数量
	Family_Attrib_BossTemplateID,			// 家族Boss的模板ID
	Family_Attrib_BossModelID,				// 家族Boss的模型ID	
	Family_Attrib_PkThiefFlag,				// pk大盗标识
	Family_Attrib_BossID,					// 家族boss   ID
	Family_Attrib_BossDareFlag,				// 家族boss 挑战标记
	Family_Attrib_AddMoneyFlag,				// 是否增加家族资金
	Family_Attrib_PkBossFlag,	
	Family_Attrib_FamilyCurrWeekWages,      // 家族本周工资基础额
	Family_Attrib_FamilyCurrWeekSYWages,    // 家族本周剩余工资
	Family_Attrib_FamilyPastWeekVitality,   // 家族上周活跃度
	Family_Attrib_IsFamilyPayoff,			// 族长是否已分配过本周工资
	Family_Attrib_FamliyJinEFanWei,         // 按金额批量调整的范围(废)
	Family_Attrib_FamliyBaiFenBi,           // 按比例批量调整的百分比（废）
	Family_Attrib_TechnologicalPower,		// 家族科技实力
	Family_Attrib_SummonTime,				// 召唤时间
	Family_Attrib_ChatPublic,				// 家族聊天公告
	Family_Attrib_CreateTime,				// 家族创建时间
	Family_Attrib_IsBiaoTou,				// 家族是否是镖头
	Family_Attrib_MaxMemberCount,			// 家族成员最大数量
	Family_Attrib_IsAllocWage,              // 是否正在分配工资
	Family_Attrib_CaptionUseFamilyTokenTimes,	//家族族长使用家族令牌次数
	Family_Attrib_AssistantUseFamilyTokenTimes,	//家族副族长使用家族令牌次数
	Family_Attrib_CaptionUserName,				//家族族长用户名
	Family_Attrib_Recruit,					// 家族招募方式
	Family_Attrib_IsLoadOver,				//是否打开过家族界面，即是否加载过数据
	
	//Family Member
	Family_Member_Attrib_PID		= 7200, // 成员PID
	Family_Member_Attrib_Level,				// 成员等级
	Family_Member_Attrib_FamilyID,			// 家族ID
	Family_Member_Attrib_FamilyPower,		// 家族职位
	Family_Member_Attrib_FamilyCredit,		// 家族贡献度
	Family_Member_Attrib_GangPower,			// 帮会职位
	Family_Member_Attrib_GangCredit,		// 帮会贡献度
	Family_Member_Attrib_OnlineFlag,		// 在线标识
	Family_Member_Attrib_TitleID,			// 家族称号ID
	Family_Member_Attrib_FeedBossFlag,		// 喂养家族boss标记
	Family_Member_Attrib_FamilyCarID,		// 身上存在家族战车id
	Family_Member_Attrib_PictureID,			// 家族成员头像ID
	Family_Member_Attrib_Gender,			// 家族成员性别
	Family_Member_Attrib_CreditMoney,		// 家族贡献资金
	Family_Member_Attrib_LeaveCredit,		// 剩余可用贡献度
	Family_Member_Attrib_GongXianWages,     // 家族成员贡献工资
	Family_Member_Attrib_GetWagesFlage,		// 家族成员领取工资标记
	Family_Member_Attrib_PastWeekWages,		// 家族成员上周领取的工资
	Family_Member_Attrib_CurrWeekWages,		// 家族成员本周实发的工资

	//Gang
	Gang_Attrib_GangID				= 7400,	// 帮会ID
	Gang_Attrib_CaptionID,					// 帮主ID
	Gang_Attrib_AssistantID,				// 副帮主ID
	Gang_Attrib_StateID,					// 国家ID
	Gang_Attrib_Level,						// 帮会等级
	Gang_Attrib_Active,						// 帮会繁荣度
	Gang_Attrib_Money,						// 帮会资金
	Gang_Attrib_Status,						// 帮会状态
	Gang_Attrib_Sculpture_Level,			// 雕像等级
	Gang_Attrib_Open_Flag,					// 招募开启标志
	Gang_Attrib_Down_Begin_Time,			// 帮会降级开始时间
	Gang_Attrib_SetCaptionTime,				// 任命副帮主时间
	Gang_Attrib_DepriveKingTime,			// 剥夺国王时间
	Gang_Attrib_DissmissTime,				// 解散帮会时间
	Gang_Attrib_Name,						// 帮会名字
	Gang_Attrib_PSW,						// 帮会密码
	Gang_Attrib_Public,						// 帮会公告
	Gang_Attrib_SetFlag,					// 设置帮会标记位
	Gang_Attrib_Skill_Count,				// 帮会技能个数
	Gang_Attrib_CityInspectionFlag,			// 城市巡查开启标记
	Gang_Attrib_CityInspectionTime,			// 城市巡查开启时间
	Gang_Attrib_CityInspectionNum,			// 城市巡查参加人数
	Gang_Attrib_Action_Build,				// 帮会建设活动开启时间
	Gang_Attrib_CengZhanling_City,			// 帮会曾占领城市
	Gang_Attrib_YiZhanling_City1,			// 帮会已经占领城市1
	Gang_Attrib_YiZhanling_City2,			// 帮会已经占领城市2
	Gang_Attrib_ZhengduoCity_BaomingFlag,	// 城市争夺战报名标记
	Gang_Attrib_Speciality_Qi,				// 帮会特产
	Gang_Attrib_Speciality_Chu,				// 帮会特产
	Gang_Attrib_Speciality_Yan,				// 帮会特产
	Gang_Attrib_Speciality_Han,				// 帮会特产
	Gang_Attrib_Speciality_Zhao,			// 帮会特产
	Gang_Attrib_Speciality_Wei,				// 帮会特产
	Gang_Attrib_Speciality_Qin,				// 帮会特产
	Gang_Attrib_ChatPublic,					//帮会聊天群公告
	Gang_Attrib_KingAutoDownTime,			//国王自动下台时间
	Gang_Attrib_GangFight_KillCount,		//帮会夺城战击杀数
	Gang_Attrib_IsLoadOver,					//是否打开过帮会界面，即是否加载过数据

	//State
	State_Attrib_StateID           = 7600,	// 国家ID
	State_Attrib_ServerID,					// 国家ServerID
	State_Attrib_Produce,					// 生产力
	State_Attrib_Build,						// 建设度
	State_Attrib_Militry,					// 军力
	State_Attrib_Active,					// 繁荣度
	State_Attrib_Food,						// 军粮
	State_Attrib_Power,						// 国力
	State_Attrib_Rule,						// 统治力
	State_Attrib_KingPID,					// 国王PID
	State_Attrib_DaYuanShuaiPID,			// 大元帅
	State_Attrib_DaXueShiPID,				// 大学士
	State_Attrib_JianJunPID,				// 将军
	State_Attrib_ChengXiangPID,				// 丞相
	State_Attrib_SetProduceMasterTime,		// 任命生产大臣时间
	State_Attrib_SetBuildMasterTime,		// 任命建筑大臣时间
	State_Attrib_SetMilityMasterTime,		// 任命军事大臣时间
	State_Attrib_GetMoneyTime,				// 玩家领工资时间
	State_Attrib_UnionStateOne,				// 第一个同盟国id
	State_Attrib_UnionStateTwo,				// 第二个同盟国id
	State_Attrib_Public,					// 国家公告
	State_Attrib_Stone,						// 国家晶石
	State_Attrib_KingName,					// 国王名字
	State_Attrib_ProduceName,				// 生产大臣名字
	State_Attrib_BuildName,					// 建设大臣名字
	State_Attrib_MilityName,				// 军事大臣名字
	State_Attrib_GuardName,					// 警卫队长名字
	State_Attrib_ProduceNextID1,			// 生产大臣手下1ID
	State_Attrib_ProduceNextID2,			// 生产大臣手下2ID
	State_Attrib_ProduceNextID3,			// 生产大臣手下3ID
	State_Attrib_ProduceNextName1,			// 生产大臣手下1名字
	State_Attrib_ProduceNextName2,			// 生产大臣手下2名字
	State_Attrib_ProduceNextName3,			// 生产大臣手下3名字
	State_Attrib_BuildNextID1,				// 建设大臣手下1ID
	State_Attrib_BuildNextID2,				// 建设大臣手下2ID
	State_Attrib_BuildNextID3,				// 建设大臣手下3ID
	State_Attrib_BuildNextName1,			// 建设大臣手下1名字
	State_Attrib_BuildNextName2,			// 建设大臣手下2名字
	State_Attrib_BuildNextName3,			// 建设大臣手下3名字
	State_Attrib_MilitryNextID1,			// 军事大臣手下1ID
	State_Attrib_MilitryNextID2,			// 军事大臣手下2ID
	State_Attrib_MilitryNextID3,			// 军事大臣手下3ID
	State_Attrib_MilitryNextName1,			// 军事大臣手下1名字
	State_Attrib_MilitryNextName2,			// 军事大臣手下2名字
	State_Attrib_MilitryNextName3,			// 军事大臣手下3名字
	State_Attrib_GuardNextID1,				// 警卫队长手下1ID
	State_Attrib_GuardNextID2,				// 警卫队长手下2ID
	State_Attrib_GuardNextID3,				// 警卫队长手下3ID
	State_Attrib_GuardNextName1,			// 警卫队长手下1名字
	State_Attrib_GuardNextName2,			// 警卫队长手下2名字
	State_Attrib_GuardNextName3,			// 警卫队长手下3名字
	State_Attrib_GUOYUNaction,				// 国运活动标记
	State_Attrib_GUOYUNtime,				// 国运活动开始时间
	State_Attrib_GUOTANaction,				// 国探活动标记
	State_Attrib_GUOTANtime,				// 国探活动开始时间
	State_Attrib_GONGFENGaction,			// 王朝供奉活动标记
	State_Attrib_GONGFENGtime,				// 王朝供奉开始时间
	State_Attrib_CITANstate,				// 刺探国家
	State_Attrib_GONGFENGstate,				// 王朝供奉国家
	State_Attrib_JUNSHIaction,				// 军事活动的标记
	State_Attrib_JUNSHIstate,				// 军事活动的国家
	State_Attrib_JingBaoFlag,				// 刺杀国务大臣的警报状态
	State_Attrib_StateFlag,					// 国家活动状态
	State_Attrib_WuWangGuoChiFlag,			// 勿忘国耻状态标记
	State_Attrib_WangCheng_Gang,			// 占领王城的帮会
	State_Attrib_MingYueCheng_Gang,			// 占领明月城的帮会
	State_Attrib_ZiZhuZhen_Gang,			// 占领紫竹镇的帮会
	State_Attrib_XianChaLing_Gang,			// 占领仙茶岭的帮会
	State_Attrib_FuRongZhai_Gang,			// 占领芙蓉寨的帮会
	State_Attrib_IsGoodKing,				// 是否是优秀国王
	State_Attrib_IsKaiser,					// 是否是皇帝
	State_Attrib_NoSpeakTimes,				// 禁言标数
	State_Attrib_SetPrisonerTimes,			// 囚禁玩家次数
	State_Attrib_FreePrisonerTimes,
	State_Attrib_KingTokenUseTimes,
	State_Attrib_SummonTimes,
	State_Attrib_ShenshuiTime,
	State_Attrib_ShenshuiCount,
	State_Attrib_CheFanTime,
	State_Attrib_EnemyState,
	State_Attrib_YuanZhengState,
	State_Attrib_StateLockTime,
	State_Attrib_StateLockFlag,
	State_Attrib_ShenshuiCountBeThievedBySHU,
	State_Attrib_ShenshuiCountBeThievedByHAN,
	State_Attrib_ShenshuiCountBeThievedByTANG,
	State_Attrib_ShenshuiCountBeThievedByJIN,
	State_Attrib_ShenshuiCountBeThievedByZHOU,

	State_Attrib_StateWarFlag,						// 国战标记
	State_Attrib_StateWarEnemyState,				// 国战敌对国ID
	State_Attrib_StateWarAttackTime,				// 国战宣战时间
	State_Attrib_StateWarDefenceTime,				// 国战被宣战时间
	State_Attrib_EscortFamily1 ,					// 镖局1家族ID， int类型，初始值为-1
	State_Attrib_EscortFamily2 ,					// 镖局2家族ID， int类型，初始值为-1
	State_Attrib_EscortMoney1  ,					// 镖局1资金，int类型，初始值为0
	State_Attrib_EscortMoney2  ,					// 镖局1资金，int类型，初始值为0
	State_Attrib_PreGainWCProtectMoneyTime,         // 本国上次领取王城占领资金的时间
	State_Attrib_Name,								// 国名
	State_Attrib_StateWarAttackFlag,
	State_Attrib_WarAttackCount,
	State_Attrib_WarDefendCount,
	State_Attrib_StatePowerRanking,					//国家综合实力排名
	

	PrivateMember_Attrib_PID			=7800,		//PID
	PrivateMember_Attrib_Name,						//Name
	PrivateMember_Attrib_StateID,					//国家ID
	PrivateMember_Attrib_Level,						//等级
	PrivateMember_Attrib_Flag,						//关系标志
	PrivateMember_Attrib_PictureID,					//头像ID
	PrivateMember_Attrib_Gender,					//性别
	PrivateMember_Attrib_JoinTime,					//关系开启时间
	PrivateMember_Attrib_Online,					//在线标记
	PrivateMember_Attrib_FriendCloseValue,			//好友关系度
	PrivateMember_Attrib_ConsortCloseValue,			//夫妻关系度
	PrivateMember_Attrib_SwornCloseValue,			//结拜关系度
	PrivateMember_Attrib_MasterPupilCloseValue,		//师徒关系度
	PrivateMember_Attrib_SwornPos,					//结拜排位
	PrivateMember_Attrib_Pos,						//好友位置信息


	Private_Attrib_PID					=7900,		//PID
	Private_Attrib_ConsortPID,						//配偶PID						
	Private_Attrib_SwornTitleType,					//结拜称号类型
	Private_Attrib_PrefixTitle,						//结拜称号前缀
	Private_Attrib_PostfixTitle,					//结拜称号后缀
	Private_Attrib_FriendCount,						//朋友个数
	Private_Attrib_ConsortCount,					//夫妻个数
	Private_Attrib_BlockCount,						//黑名单个数
	Private_Attrib_EnemyCount,						//仇人个数
	Private_Attrib_DeepEnemyCount,					//深仇个数
	Private_Attrib_MasterCount,						//师傅个数
	Private_Attrib_PupilCount,						//徒弟个数
	Private_Attrib_SwornCount,						//结拜个数
	

	
	Group_Attrib_GroupID			= 8000,	//群ID
	Group_Attrib_Type,
	Group_Attrib_CaptionID,
	Group_Attrib_Name,
	Group_Attrib_Public,

	Group_Member_Attrib_PID			= 8100,	// 成员PID
	Group_Member_Attrib_GroupID,
	Group_Member_Attrib_OnlineFlag,			// 在线标识
	Group_Member_Attrib_ShieldFlag,			// 屏蔽标记
	Group_Member_Attrib_Name,				// 成员名字

	FamilyCar_Attrib_FamilyID				= 8200,	//家族战车
	FamilyCar_Attrib_PID,
	//FamilyCar_Attrib_ID,							//家族战车的索引位置
	FamilyCar_Attrib_TemplateID,					//家族战车的模板ID
	FamilyCar_Attrib_CurrentPID,					//当前领取玩家PID
	FamilyCar_Attrib_LastPID,						//最后一次领取玩家PID
	FamilyCar_Attrib_Hp_FEIQI,					//家族战车的Hp					 (废弃)
	FamilyCar_Attrib_MaxHp_FEIQI,		//家族战车的MaxHp			(废弃)
	FamilyCar_Attrib_Name,							//家族战车名字
	FamilyCar_Attrib_LastUserName,					//上次使用者名字
	FamilyCar_Attrib_CurUserName,					//当前使用者名字
	FamilyCar_Attrib_Status,							//战车状态

	FamilyCar_Attrib_FCarType,
	FamilyCar_Attrib_AP,
	FamilyCar_Attrib_MAP,
	FamilyCar_Attrib_AC,
	FamilyCar_Attrib_MAC,
	FamilyCar_Attrib_Speed,
	FamilyCar_Attrib_EffectID,
	FamilyCar_Attrib_Quality,

	//骑宠
	Ride_Attrib_PID						= 8300,	//PID
	Ride_Attrib_Template,						//模板ID
	Ride_Attrib_AddHP,							//增加的HP
	Ride_Attrib_AddSpeed,						//增加的移动速度

	Ride_Attrib_AddSTR,
	Ride_Attrib_AddINT,
	Ride_Attrib_AddAGI,
	Ride_Attrib_AddSPI,
	Ride_Attrib_AddSTA,

	Ride_Attrib_AddAP,							//增加的AP
	Ride_Attrib_AddAC,							//增加的AP
	Ride_Attrib_AddMAP,							//增加的MAP
	Ride_Attrib_AddMAC,							//增加的AP

	//PetItem_Attrib_Level,							//宠物等级
	//PetItem_Attrib_Exp,								//宠物经验
	//PetItem_Attrib_WaiGong,							//宠物外功
	//PetItem_Attrib_NeiGong,
	//PetItem_Attrib_ShenFa,
	//PetItem_Attrib_ZhenQi,
	//PetItem_Attrib_JinGu,
	//PetItem_Attrib_AddWaiGong,						//宠物外功成长率
	//PetItem_Attrib_AddNeiGong,
	//PetItem_Attrib_AddShenFa,
	//PetItem_Attrib_AddZhenQi,
	//PetItem_Attrib_AddJinGu,
	//PetItem_Attrib_Equip1,							//宠物装备1
	//PetItem_Attrib_Equip2,
	//PetItem_Attrib_Equip3,
	//PetItem_Attrib_Equip4,
	//PetItem_Attrib_Name,							//宠物名字
	//PetItem_Attrib_Grow_WaiGong,					//外功成长值
	//PetItem_Attrib_Grow_NeiGong,					//内功成长值
	//PetItem_Attrib_Grow_ShenFa,						//身法成长值
	//PetItem_Attrib_Grow_ZhenQi,						//真气成长值
	//PetItem_Attrib_Grow_JinGu,						//筋骨成长值
	//PetItem_Attrib_WuXing,							//悟性
	//PetItem_Attrib_AddWuXing,						//悟性增长值
	//PetItem_Attrib_TiLi,							//体力
	//PetItem_Attrib_Angry,							//怒气

	//场景
	Scene_Attrib_ID							= 8400, //场景ID
	Scene_Attrib_OwnerID,							//拥有者ID
	Scene_Attrib_TemplateID,						//场景模板ID
	Scene_Attrib_Type,								//场景类型
	Scene_Attrib_AIType,							//场景AI类型
	Scene_Attrib_LivingTime,						//存活时间
	Scene_Attrib_CreateTime,						//创建时间
	Scene_Attrib_ManCity,							//对应主城ID
	Scene_Attrib_ServerID,							//所在服务器ID
	Scene_Attrib_PlayerNum,							//玩家数量
	Scene_Attrib_Progress,							//副本进度
	Scene_Attrib_CreatorID,							//创建者ID
	Scene_Attrib_CampaignID,						//活动ID
	Scene_Attrib_StateID,							//国家ID
	Scene_Attrib_CloseTime,							//空置关闭时间

	//活力值
	Vitality_Attrib_Value1					= 8600,	// 上周综合活跃度
	Vitality_Attrib_Value2,							// 本周综合活跃度
	Vitality_Attrib_Value3,							// 时间活跃度 2-8
	Vitality_Attrib_Value4,							// 时间活跃度 8-14
	Vitality_Attrib_Value5,							// 时间活跃度 14-20
	Vitality_Attrib_Value6,							// 时间活跃度 20-2
	Vitality_Attrib_Value7,							// 活动活跃度
	Vitality_Attrib_Value8,							// 行为活跃度

	//活动
	Campaign_Attrib_ID						=8900,  //活动id
	Campaign_Attrib_Flag,							//活动标记
	Campaign_Attrib_UnitFlag,						//活动单位
	Campaign_Attrib_LuaID,							//活动脚本id
	Campaign_Attrib_Name,							//活动名称
	Campaign_Attrib_GameTime,						//活动总时间
	Campaign_Attrib_StartTime,						//开始时间点(或者自行开启类型活动无效)
	Campaign_Attrib_BeforeStartTime,				//活动开始前时间(或者自行开启类型活动中开启后离活动开始的时间)
	Campaign_Attrib_SignUpTime,						//报名时间点(或者是自行开启类型可以开启点)
	Campaign_Attrib_EndSignUpTime,					//报名截止时间(或者是自行开启类型可以开启截止时间)
	Campaign_Attrib_MinLimitNum,					//最小限制人数
	Campaign_Attrib_UnitMax,						//单位最大限制
	Campaign_Attrib_MatchNum,						//单位匹配数量
	Campaign_Attrib_Type,							//活动类型
	Campaign_Attrib_ServerID,						//活动所在服务器id
	Campaign_Attrib_Week,							//活动所开星期
	Campaign_Attrib_SceneTID1,						//活动场景模板1
	Campaign_Attrib_SceneTID2,						//活动场景模板2
	Campaign_Attrib_SceneTID3,						//活动场景模板3
	Campaign_Attrib_SceneTID4,						//活动场景模板4
	Campaign_Attrib_SceneTID5,						//活动场景模板5
	Campaign_Attrib_SceneTID6,						//活动场景模板6
	Campaign_Attrib_SceneTID7,						//活动场景模板7
	Campaign_Attrib_SceneTID8,						//活动场景模板8
	Campaign_Attrib_SceneTID9,						//活动场景模板9
	Campaign_Attrib_SceneTID10,						//活动场景模板10

	Campaign_Attrib_SignUpFlag,						//报名开始标记
	Campaign_Attrib_StartFlag,						//活动开始标记

	CommunityCampaign_Attrib_FamilyID,					//家族id
	CommunityCampaign_Attrib_GangID,					//帮会id
	CommunityCampaign_Attrib_StateID,					//国家id
	CommunityCampaign_Attrib_CommunityFlag,				//社会标记
	CommunityCampaign_Attrib_CompleteFlag,				//活动进度标记
	CommunityCampaign_Attrib_StartTime,					//活动开始时间
	CommunityCampaign_Attrib_StartSceneID,				//活动开始场景
	CommunityCampaign_Attrib_SceneID1,					//活动场景1
	CommunityCampaign_Attrib_SceneID2,					//活动场景2
	CommunityCampaign_Attrib_SceneID3,					//活动场景3
	CommunityCampaign_Attrib_SceneID4,					//活动场景4
	CommunityCampaign_Attrib_SceneID5,					//活动场景5
	CommunityCampaign_Attrib_SceneID6,					//活动场景6
	CommunityCampaign_Attrib_SceneID7,					//活动场景7
	CommunityCampaign_Attrib_SceneID8,					//活动场景8
	CommunityCampaign_Attrib_SceneID9,					//活动场景9
	CommunityCampaign_Attrib_SceneID10,					//活动场景10
	CommunityCampaign_Attrib_ZoneX,						//出生区域X 坐标
	CommunityCampaign_Attrib_ZoneY,						//出生区域Y 坐标
	CommunityCampaign_Attrib_Param1,					//活动数据1
	CommunityCampaign_Attrib_Param2,					//活动数据2
	CommunityCampaign_Attrib_Param3,					//活动数据3
	CommunityCampaign_Attrib_Param4,					//活动数据4
	CommunityCampaign_Attrib_Param5,					//活动数据5




	//特殊类型的属性
	Effect_ReadMail					= 10000,//
	Effect_HpMaxLVEhance,					//生命最大上限和Level的加成
	Effect_MpMaxLVEhance,					//能量最大上限和Level的加成
	Effect_Add_Target_Buff,					//给目标加Buff
	Effect_Remove_All_Dot,					//清楚所有减益Buf
	Effect_Mp_Enhance,						//改变当前Mp %
	Effect_Weapen_Mell_Expore,				//根据主手武器的物理攻击%计算伤害
	Effect_Set_AIType,						//改变NPC的AIType
	Effect_Add_Prop,						//增加道具，被攻击者得到道具
	Effect_Add_Quest,						//增加任务
	Effect_Summon_Booth,					//召唤摆摊车
	Effect_Summon_NPC,						//召唤NPC
	Effect_Transmission_Player,				//传送
	Effect_Status_Posion,					//进入中毒状态
	Effect_Status_OpenWound,				//进入失明状态
	Effect_Status_Freeze,					//进入冰冻状态
	Effect_Status_Burn,						//进入灼烧状态
	Effect_Status_Stun,						//进入眩晕状态
	Effect_Status_Slow,						//进入减速状态
	Effect_Status_Immobilize,				//进入定身状态
	Effect_Status_Confuse,					//进入混乱状态
	Effect_Status_Slience,					//进入沉默状态
	Effect_Add_Self_Buff,					//给自己增加Buff
	Effect_Make_Burn_Damage,				//造成灼烧伤害
	Effect_Make_Posion_Damage,				//造成中毒伤害
	Effect_Revive,							//复活玩家
	Effect_Catch,							//捕捉
	Effect_Add_Summon_Pet_Buff,				//向战宠添加buff（废弃，跟Effect_Add_CombatPet_Buff重复）
	Effect_Add_Summon_Pet_Hp,				//向战宠添加Hp
	Effect_CombineWithCombatPet,			//与战宠合体
	Effect_Set_Trap,						//种陷阱
	Effect_Set_Spy,							//侦查
	Effect_Explorer_FlyTo,					//同屏瞬间移动
	Effect_CreateAura_Self,					//创造自身光环
	Effect_Sit_With_Pet,					//和Pet换位置
	Effect_Set_Aque_Buff,					//给水灵添加Buff（废弃，统一用Effect_Add_CombatPet_Buff）
	Effect_Add_CombatPet_Buff,				//给战宠加Buff
	Effect_Combin_With_Ghost,				//和鬼魅合体	（废弃，统一改用Effect_CombineWithCombatPet）
	Effect_Absorb_CombatPet_Attack_Invalid,	//吸收战宠攻击力%（废弃，暂时用Effect_Absorb_CombatPet_AttackEnchance）
	Effect_Absorb_CombatPet_Armor_Invalid,	//吸收战宠防御力%（废弃，暂时用Effect_Absorb_CombatPet_ArmorEnhchance）
	Effect_Combin_With_Aqua,				//和水灵合体	（废弃，统一改用Effect_CombineWithCombatPet）
	Effect_Combin_With_Fire,				//和火灵合体	（废弃，统一改用Effect_CombineWithCombatPet）
	Effect_Combin_With_Drak,				//和暗鬼合体	（废弃，统一改用Effect_CombineWithCombatPet）
	Effect_Combin_With_Wind,				//和风灵合体	（废弃，统一改用Effect_CombineWithCombatPet）
	Effect_Add_Explorer_Team_Buff,			//向同屏队友添加buff
	Effect_Set_Hp_By_MaxHp,					//根据MaxHp设置Hp%
	Effect_Set_Mp_By_MaxMp,					//根据MaxMp设置Mp%
	Effect_Mp_Turn_Damage,					//Mp转换成伤害%
	Effect_Use_Skill,						//对目标使用技能
	Effect_ResetSkillPoints,				//重置技能点
	Effect_ResetAttributePoints,			//重置属性点
	Effect_Transport,						//传送到指定地点
	Effect_Set_DamageTurn_Per,				//替目标分担伤害%
	Effect_Auto_ReLive,						//自动复活标记
	Effect_Status_Funk,						//进入恐惧状态
	Effect_Add_Prop_Buff,					//向道具添加buff
	Effect_Add_Damage,						//附加伤害
	Effect_Hp_Energy,						//生命精华
	Effect_Mp_Energy,						//能量精华
	Effect_Percent_Mp_Turn_Damage,			//按照百分比减掉现有MP，再转换成hp的伤害
	Effect_Prop_HuiCheng_Single,			//单体回城卷轴道具效果（回城符）
	Effect_Prop_HuiCheng_Colony,			//群体回城卷轴道具效果
	Effect_Prop_ShunYi_Single,				//单体瞬移卷轴道具效果（不限地图随机符）
	Effect_Prop_ShunYi_Colony,				//群体瞬移卷轴道具效果
	Effect_Prop_JiYi,						//记忆卷轴道具效果
	Effect_Prop_ShiKong,					//时空通令道具效果
	Effect_Prop_ZiYou,						//自由令牌道具效果
	Effect_Prop_WangZhe,					//自由王者令牌道具效果
	Effect_Prop_Stealth,					//隐身效果
	Effect_Prop_DisableStealth,				//反隐效果
	Effect_Add_Player_CombatePet_Buff,		//给已经召唤出战宠的人加buff
	Effect_Catch_Pet,						//捕捉宠物
	Effect_Add_Skill_To_Pet,				//给宠物增加技能
	Effect_Set_Friend_NPC_TID,				//设置友好NPC的模板
	Effect_Set_RoleModel,					//设置角色模型
	Effect_Set_UnBeatable,					//无敌状态
	Effect_Set_Fight_Off,					//击退
	Effect_Kill,							//杀死对方
	Effect_FlyTo_Consort,					//传送到夫妻处
	Effect_Add_Exp_BySelf,					//按照自己的最大MaxExp增加经验
	Effect_Add_Material_By_Level,			//根据玩家等级产出材料
	Effect_Remove_All_Hot,					//清楚所有增益Buf
	Effect_Add_Spell_Dong,					//抵消伤害护盾
	Effect_Add_HpMaxEnhance,				//恢复生命上限百分比的生命值
	Effect_Get_Prop,                        //偷取得到道具，施法者得到道具
	Effect_Set_Hp,							//设置当前血值
	Effect_Family_Medal,					//家族勋章
	Effect_Add_Family_Car,					//添加家族战车
	Effect_Game_Kill,                       //游戏击杀
	Effect_Radom_SetNPC,                    //随机种npc
	Effect_Change_Hp_Enhance,				//按%改变当前血值，需要冒血
	Effect_CreateAura_Target,				//在指定位置创造光环
	Effect_Set_Crafts_Status,				//进入生活技能状态
	Effect_Set_Express_Status,				//进入表情状态
	Effect_Status_Add_Prop,					//状态获得道具
	Effect_Magic_Box_Get_Prop,				//开箱子效果
	Effect_Add_Poison_Buff,					//增加中毒buff
	Effect_Add_Freeze_Buff,					//增加冰冻buff
	Effect_Add_Burn_Buff,					//增加灼烧buff
	Effect_Add_Stun_Buff,					//眩晕buff
	Effect_Add_Slow_Buff,					//减速buff
	Effect_Add_Immobilize_Buff,				//定身buff
	Effect_Add_Confuse_Buff,				//混乱buff
	Effect_Add_Slience_Buff,				//沉默buff
	Effect_In_ChangeModel_Status,			//进入改变模型状态
	Effect_ResetWaigongPoint,				//重置外功属性点
	Effect_ResetNeigongPoint,				//重置内功属性点
	Effect_ResetShenfaPoint,				//重置身法属性点
	Effect_ResetZhenqiPoint,				//重置真气属性点
	Effect_ResetJinguPoint,					//重置筋骨属性点
	Effect_Add_Ride_Pet,					//增加一个骑宠
	Effect_Charge_Target,					//冲锋，冲到离目标最近处（瞬移）
	Effect_Combin_With_RidPet,				//和骑宠合体
	Effect_SilverBind,						//获得绑定银子(文)
	Effect_SetCommonSill,					//设置普通技能
	Effect_CatchQuestNPC,					//捕获任务npc
	Effect_OpenQuestComplete,				//打开任务提交
	Effect_Add_Car_Buff,					//给自己的镖车加buff
	Effect_Summon_MyNPC,					//召唤maseter是自己的NPC
	Effect_INC_RidPet_Exp,					//提升骑宠经验
	Effect_Fellow_HuanHun,					//珍兽还魂
	Effect_Spell_Turn_Damage,				//魔攻转伤害
	Effect_UseSkill_To_Myself,				//对自己使用技能
	Effect_Script_Call,						//脚本调用
	Effect_Prop_ShunYi_Map,					//单体瞬移卷轴道具效果（限本国随机符）
	Effect_Fly_To_Map,						//传送到某地图
	Effect_Prop_To_Flight,					//使用道具进入飞行状态
	Effect_Quest_SummonMonster,				//召唤一个任务怪物
	Effect_Quest_SummonProtectNPC,			//召唤一个护送类任务NPC
	Effect_Summon_BelongSelfNPC,			//召唤所属为自己的NPC
	Effect_Control_Car_Attack,				//控制战车攻击目标
	Effect_Gang_SummonAllMember,			//召唤帮会成员
	Effect_Jump,							//跳跃
	Effect_Family_Car_Summon,				//读完条后，召唤战车
	Effect_Add_Head_Effect,					//添加头顶特效
	Effect_Summon_Teammate,					//召唤队友
	Effect_Add_Buff_To_Master,				//给主人添加BUFF
	Effect_Add_CombineBuff,					//添加战宠合体Buff
	Effect_Absorb_CombatPet_AttackEnchance,	//吸收战宠攻击力%
	Effect_Absorb_CombatPet_ArmorEnhchance, //吸收战宠防御力%
	Effect_Absorb_CombatPet_MaxHpEnhchance, //吸收战宠生命上限%
	Effect_Absorb_CombatPet_CritEnhchance,	//吸收战宠暴击率%
	Effect_Add_ExperienceByW,				//以万为单位来增加经验
	Effect_Damage_TargetBySelfMaxHp,		//给目标伤害（根据自己最大血值%）
	Effect_Damage_SelfBySelfMaxHp,			//给自己伤害（根据自己最大血值%）
	Effect_Set_ModelColor,					//设置模型遮罩
	Effect_Family_Car_Enter,				//读完条后，进入战车
	Effect_Clear_SkillCD,					//重置某技能CD
	Effect_Target_CallBackRide,				//令目标下马
	Effect_Auto_Stop,						//自动停止
	Effect_Auto_Drive,						//自动驾驶
	Effect_Absorb_CombatPet_DamageReduceEnchance,//吸收战宠伤害减免%

	Effect_Set_Dance_Status			=10201,	//进入跳舞休闲状态
	Effect_Set_Bomb_Status,					//进入携带炸弹状态（已废弃）
	Effect_Set_Game_Status,					//进入游戏状态

	Effect_RondomModel				=10300, //随机变一个模型
	Effect_EreaseKill,						//让NPC消失，刷新时间到后会复活
	Effect_SummonCarGod,					//召唤镖车所属npc
	Effect_Summon_PropQuestNPC,				//道具召唤出来的任务Npc

	Effect_Use_Baby_Egg				= 10350,		//普通宝宝蛋的使用效果
	Effect_Use_Seal_Egg,							//封印后的玄兽蛋的使用效果(解封)
	Effect_Use_Breed_Egg,							//繁殖后的成年玄兽蛋的使用效果
	Effect_Use_Prop_CatchFellow,					//捕兽道具的使用效果
	Effect_Use_ChangeSoulTypeToDiHun,				//切换到地魂
	Effect_Use_ChangeSoulTypeToMingHun,				//切换到命魂
	Effect_Use_ChangeSoulTypeToTianHun,				//切换到天魂
	Effect_Remove_Target_Buff,						//移除目标BUFF add by zhangjianli 2012-3-2
	Effect_Add_PractiseGeste,						//增加历练功勋 add by zhangjianli 2012-7-30
	Effect_Set_PKType_Protect,							//设置PK保护 add by zhangjianli 2012-9-6

	//界面特效
	Effect_Set_Cursor_Cast			= 20000,//设置鼠标为施法状态
	Effect_Set_Cursor_Repair,				//设置鼠标为修理状态
	Effect_Open_Inquiry,					//打开一个对话
	Effect_Open_Stall,						//打开摆摊车
	Effect_Set_Use_Prop_Skill,				//进入附魔状态
	Effect_Open_Portal,						//打开传送界面
	Effect_Prop_JiYiPos,					//记忆坐标
	Effect_Progress_Bar,					//设置进度条状态
	Effect_Ready_Use_Prop,					//进入使用道具状态
	Effect_Set_Cursor_Choice,				//进入选择目标状态（如果有目标就不切换状态）
	Effect_Open_PropCompose,				//打开打造界面



	//玄兽相关属性
	//注释部分是玄兽用到的属性，这部分属性在前面定义
	//Role_Attrib_Fellow = 21000,											
	//Fellow_Attri_TID,																//TID
	//Role_Attrib_MasterPID,
	//Role_Attrib_SceneID,
	//Role_Attrib_StateID,
	//Role_Attrib_Birth_Time,
	//Role_Attrib_Angle,

	//一级属性
	//Fellow_Attri_Name,																//Name
	//Role_Attrib_Level,
	//Role_Attrib_Experience
	//Role_Attrib_MaxExperience
	//Role_Attrib_Hp
	//Role_Attrib_MaxHp
	//Role_Attrib_ChaseDistance

	Role_Attrib_BreedNum = 21000,														//繁殖次数
	Role_Attrib_Sex,																//性别	--此属性为珍兽使用，非玩家--
	Role_Attrib_FellowType,																//类型 enum Fellow_Type   //lqp 已定义相同类型
	Role_Attrib_Happy,															//快乐度
	Role_Attrib_MaxHappy,													//最大快乐度
	Role_Attrib_Life,																//寿命
	Role_Attrib_MaxLife,														//最大寿命

	//二级属性
	Role_Attrib_Grow,																//成长
	Role_Attrib_UnderStand,													//悟性
	//Fellow_Attri_UnuseAttriPoint,											//未使用的属性点		//--合并，统一用Role的属性Role_Attrib_AttributePoints-- change by zhaoguoze 2011-08-31

	Role_Attrib_Aptitude_STR,												//力量资质
	Role_Attrib_Aptitude_INT,												//智力资质
	Role_Attrib_Aptitude_AGI,												//敏捷资质
	Role_Attrib_Aptitude_SPI,												//精神资质
	Role_Attrib_Aptitude_STA,												//体质资质

	//Fellow_Attri_STR,																//力量	//--合并，统一用Role的属性Role_Attrib_Waigong-- change by zhaoguoze 2011-08-31
	//Fellow_Attri_INT,																//智力	//--合并，统一用Role的属性Role_Attrib_Neigong-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_AGI,																//敏捷	//--合并，统一用Role的属性Role_Attrib_Shenfa-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_SPI,																//精神	//--合并，统一用Role的属性Role_Attrib_Zhenqi-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_STA,																//体质	//--合并，统一用Role的属性Role_Attrib_Jingu-- change by zhaoguoze 2011-09-01

	//Fellow_Attri_AP,																//物理攻击	//--合并，统一用Role的属性Role_Attrib_DamagePhysical-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_AC,																//物理防御	//--合并，统一用Role的属性Role_Attrib_Armor-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_MAP,																//魔法攻击	//--合并，统一用Role的属性Role_Attrib_DamageSpell-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_MAC,																//魔法防御	//--合并，统一用Role的属性Role_Attrib_SpellResist-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_Dunt,																//重击	//--合并，统一用Role的属性Role_Attrib_Crit-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_Jouk,																//闪避	//--合并，统一用Role的属性Role_Attrib_Dodge-- change by zhaoguoze 2011-09-01

	Role_Attrib_Max_Aptitude_STR,												//力量资质上限
	Role_Attrib_Max_Aptitude_INT,												//智力资质上限
	Role_Attrib_Max_Aptitude_AGI,												//敏捷资质上限
	Role_Attrib_Max_Aptitude_SPI,												//精神资质上限
	Role_Attrib_Max_Aptitude_STA,												//体质资质上限

	Role_Attrib_Aptitude_Grow,											//成长资质
	Role_Attrib_Aptitude_UnderStand,								//悟性资质

	Role_Attrib_Breed_Level,													//繁殖等级

	//各属性上的加成值，玩家手动给这些属性加的点数
	Role_Attrib_Add_STR,																//增加的力量
	Role_Attrib_Add_INT,																//增加的智力
	Role_Attrib_Add_AGI,																//增加的敏捷
	Role_Attrib_Add_SPI,																//增加的精神
	Role_Attrib_Add_STA,																//增加的体质

	//Fellow_Attri_Add_AP_Enhance,														//增加的物理攻击%	//--合并，统一用Role的属性Role_Attrib_WaigongEnhance-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_Add_AC_Enhance,														//增加的物理防御%	//--合并，统一用Role的属性Role_Attrib_ArmorEnhance-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_Add_MAP_Enhance,														//增加的魔法攻击%	//--合并，统一用Role的属性Role_Attrib_NeigongEnhance-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_Add_MAC_Enhance,														//增加的魔法防御%	//--合并，统一用Role的属性Role_Attrib_SpellResistEnhance-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_Add_Dunt_Enhance,														//增加的重击%	（废弃）
	//Fellow_Attri_Add_Jouk_Enhance,														//增加的闪避%	（废弃）

	Role_Attrib_StarLevel,															//强化后的星等级 (1 - 30)
	Role_Attrib_TakeLevel,															//携带等级
	//--珍兽效果--
	Effect_UnderStand_SelfPhysicalAttackEnhance = 21300,					//悟性提升珍兽物理攻击力%
	Effect_UnderStand_SelfMagicAttackPEnhance,								//悟性提升珍兽魔法攻击力%
	Effect_UnderStand_SelfPhysicalDefenseEnhance,							//悟性提升珍兽物理防御力%
	Effect_UnderStand_SelfMagicDefenseEnhance,								//悟性提升珍兽魔法防御力%
	Effect_UnderStand_SelfCritEnhance,										//悟性提升珍兽暴击率%
	Effect_UnderStand_SelfMaxHpEnhance,										//悟性提升珍兽生命上限%

	Effect_UnderStand_MasterPhysicalAttackEnhance = 21400,					//主人根据珍兽悟性提取物攻%
	Effect_UnderStand_MasterMagicAttackPEnhance,							//主人根据珍兽悟性提取魔攻%
	Effect_UnderStand_MasterPhysicalDefenseEnhance,							//主人根据珍兽悟性提取物防%
	Effect_UnderStand_MasterMagicDefenseEnhance,							//主人根据珍兽悟性提取魔防%
	Effect_UnderStand_MasterCritEnhance,									//主人根据珍兽悟性提取暴击率%
	Effect_UnderStand_MasterMaxHpEnhance,									//主人根据珍兽悟性提取生命上限%

	Effect_Convert_MasterPhysicalAttackEnhance = 21500,						//主人提取珍兽物攻%
	Effect_Convert_MasterMagicAttackPEnhance,								//主人提取珍兽魔攻%
	Effect_Convert_MasterPhysicalDefenseEnhance,							//主人提取珍兽物防%
	Effect_Convert_MasterMagicDefenseEnhance,								//主人提取珍兽魔防%
	Effect_Convert_MasterMaxHpEnhance,										//主人提取珍兽最大生命%

	//组队属性
	TeamMember_Attrib_TeamID				  = 21600,	
	TeamMember_Attrib_PID,
	TeamMember_Attrib_Name,
	TeamMember_Attrib_OfflineTime,
	TeamMember_Attrib_Hp,
	TeamMember_Attrib_MaxHp,
	TeamMember_Attrib_Mp,
	TeamMember_Attrib_MaxMp,
	TeamMember_Attrib_PictureID,
	TeamMember_Attrib_Gender,
	TeamMember_Attrib_Level,
	TeamMember_Attrib_StateID,
	TeamMember_Attrib_SceneID,
	TeamMember_Attrib_OnlineFlag,
	TeamMember_Attrib_Position,

	StateOfficer_AttribInt64_PID			= 21650,
	StateOfficer_AttribStr_Name,
	StateOfficer_AttribInt_Power,
	StateOfficer_AttribInt_AppointerPower,
	StateOfficer_AttribInt_TokenUseTimesToday,
	StateOfficer_AttribInt_TokenUseTimesHistory,
	StateOfficer_AttribInt_StateID,
	StateOfficer_AttribInt_YunBiaoHoldTimesPerDay,	//每日运镖托运次数
	StateOfficer_AttribInt64_AppointerTime,			//上任时间

};

const int HELPNOTICE_FLAGCOUNTS = 15;		//新手引导中的存盘标记数量 
enum CAMPAIGN_DATA_INDEX
{
	CamPaignData_Gifts		=   0,				//临时礼包
	CampaignData_PlayerPointsActive,			//记录玩点提示当前是否激活
	CamPaignData_HelpNoticeFlag_Begin,			//箭头文字引导存盘标记开始位		add by lfy 2012.3.1
	CamPaignData_HelpNoticeFlag_End = CamPaignData_HelpNoticeFlag_Begin +HELPNOTICE_FLAGCOUNTS-1 ,			//箭头文字引导存盘标记结束位
	CamPaignData_MaxID,							//活动数据最大值，新添加活动时请在此项前添加 add by lfy 2011.7.2
};

enum FlashBox_ButtonType
{
	FlashBox_ButtonType_Individual		=	-1	,			//默认
	FlashBox_ButtonType_Common					,			//通用提示
	FlashBox_ButtonType_ExpTip					,			//经验提示
	FlashBox_ButtonType_PlayerPoint				,			//玩点提示
	FlashBox_ButtonType_SeverDown				,			//服务器关闭提示
	FlashBox_ButtonType_EquipProtect            ,           //取消装备保护
	FlashBox_ButtonType_PropertyProtect         ,           //取消财产保护密码
	FlashBox_ButtonType_SafetyTimeDown          ,           //下调安全时限
	FlashBox_ButtonType_LevelSeal				,			//封印闪框
	FlashBox_ButtonType_SealMonster				,			//十字坡封印怪物

	FlashBox_ButtonType_JoinCompetition = 50,	//活动_答题
	FlashBox_ButtonType_EscortTeam,				//活动_运镖
	FlashBox_ButtonType_FamilyCarOpt,			//家族战车
	FlashBox_ButtonType_ApplyJoinFamily,		//有人申请加入家族
	FlashBox_ButtonType_EscortDangerCar,		//镖局危险镖车列表
	FlashBox_ButtonType_FamiyEscort,			//家族运镖活动界面
	FlashBox_ButtonType_FamilyAppointAssiatant,	//任命家族副族长
	FlashBox_ButtonType_FamilyAppointFooder,	//任命家族食神
	FlashBox_ButtonType_FamilyFirePower,		//罢免家族官职
	FlashBox_ButtonType_GangAppointAssistant,	//任命帮会副帮主
	FlashBox_ButtonType_GangFirePower,			//罢免帮会职务
	FlashBox_ButtonType_ALT_F,					//AltF新手引导
	FlashBox_ButtonType_StatePower_BeFire,		//国家官职被罢免
	FlashBox_ButtonType_KingDownAsRule,			//统治力下降国王下台
	FlashBox_ButtonType_FamilyPayoff,			//族长已分配本周家族工资，通知族员领取
	FlashBox_ButtonType_FamilyNotPayoff,		//族长还没有分配本周工资，通知族长分配
	FlashBox_ButtonType_StateWarAlarm,			//国战即将来临
	FlashBox_ButtonType_RideBird,				//角色骑上仙鹤后提示:右键头像下方的御行图标可取消骑乘状态

	FlashBox_ButtonType_Chat_Private	=	100	,			//个人聊天
	FlashBox_ButtonType_Chat_Family				,			//家族聊天
	FlashBox_ButtonType_Chat_Gang				,			//帮会聊天
	FlashBox_ButtonType_Chat_Group				,			//群组聊天
	
	FlashBox_ButtonType_Notice_LevelUp	=	200	,			//升级提示
	FlashBox_ButtonType_Notice_LevelUp_AddPoints,			//升级加点提示
	FlashBox_ButtonType_Notice_NewCapability	,			//新功能预告
	FlashBox_ButtonType_Notice_AvailableGames	,			//可接活动
	
};

struct ATTRIB_MAP
{
	Attrib	ID;
	char	Name[50];
};

//玩家开关规则
//开关值：0代表关，1代表开
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 .........
// |
// |
// |
// |
//开关值

//位数开关的意义
//(注意最大64，最小1)
enum PLAYER_SWITCH
{
	PLAYER_SWITCH_AVAILABLEQUEST = 61	,	//显示全部可接任务，默认不显示
	PLAYER_SWITCH_QUESTTRACK=62,
	PLAYER_SWITCH_HELPTIP=63,      //第63位：是否显示tip帮助的开关
};

//返回开关的值
inline   BOOL     IsPlayerSwitchOpen(uint64 nSwitch,int n)
{
	return  (((uint64)1<<(n-1)) & nSwitch)!=(uint64)0;
}

//设置开关
inline   uint64    SetPlayerSwitch(uint64 nSwitch,int n,BOOL Flag)
{
	uint64 tempSwitch;
	if(Flag)
		tempSwitch= ((uint64)1<<(n-1)) | nSwitch;
	else
		tempSwitch= ~((uint64)1<<(n-1)) & nSwitch;
	return tempSwitch;
}


//方便CUtlMap操作的一些宏，by zhao
//////////////////////////////////

//查找
#define FIND_MAP_VALID(mapname,mapkey)\
	int nIndex = mapname.Find( mapkey );\
	if(mapname.IsValidIndex(nIndex))\
	return mapname.Element(nIndex);\
	return NULL;
//删除
#define DEL_MAP_VALID(mapname,mapkey)\
	int nIndex = mapname.Find( mapkey );\
	if( mapname.IsValidIndex( nIndex ) )\
	mapname.Remove(mapkey);\
	else\
	return FALSE;
//插入
#define INSERT_MAP_VALID(mapname,mapelement,mapkey)\
	int index=mapname.Find(mapkey);\
	if(mapname.IsValidIndex(index))\
	return FALSE;\
	mapname.Insert(mapkey,mapelement);

#define FOR_EACH_LIST(listname,index)\
	for(int index=listname.Head();listname.IsValidIndex(index);index=listname.Next(index))



const int g_OpenDiHun_QuestID = 6701;     //开启地魂的触发任务 

//////////////////////////////////////////////////////////////////////////
// 对 键值对存储成Blob 的支持    在DB 使用 
//////////////////////////////////////////////////////////////////////////
enum EBlobStoreType
{
	EBST_Int = 1,
	EBST_Int64,
	EBST_String,
};

//////////////////////////////////////////////////////////////////////////
// 存读盘的机制 (Type,Key,Value)										//
// Type： 表示Vuale 的类型  (1 表示int  2 表示int64  3 表示 str)   short//
// Key：  属性key  值 ，像 Player属性 或者 道具属性的 Enum 值      int  //
// Value：存储值                                     int or int64 or str//
// 注意： 目前只支持 int int64  str  如有其他类型，请添加相关功能		//
//                 ChenXY   2011/9/15                                   //
//////////////////////////////////////////////////////////////////////////
inline void  g_Blob_SerialInt(CUtlBuffer& buffer,short sType,int nKey, int nValue)
{
	buffer.PutShort( EBST_Int );
	buffer.PutInt( nKey );
	buffer.PutInt( nValue );
}
inline void  g_Blob_SerialInt64(CUtlBuffer& buffer,short sType,int nKey, int64 i64Value)
{
	buffer.PutShort( EBST_Int64 );
	buffer.PutInt( nKey );
	buffer.PutInt64( i64Value );
}

inline void  g_Blob_SerialStr(CUtlBuffer& buffer,short sType,int nKey, char const* pString)
{
	buffer.PutShort( EBST_String );
	buffer.PutInt( nKey );
	buffer.PutString( pString );
}

inline void  g_Blob_DerialInt(CUtlBuffer& buffer,int &nKey, int &nValue)
{
	nKey = buffer.GetInt();
	nValue = buffer.GetInt();
}
inline void  g_Blob_DerialInt64(CUtlBuffer& buffer,int &nKey, int64 &i64Value)
{
	nKey = buffer.GetInt();
	i64Value = buffer.GetInt64();
}

inline void  g_Blob_DerialStr(CUtlBuffer& buffer,int &nKey, char* pString)
{
	nKey = buffer.GetInt();
	buffer.GetString(pString,MAX_ALIAS_NAME_LEN);
}

///////////////////////////////////////////////////////////////////////////
//负责解析 buffer 的模板函数 在 MySql 对应 Blob 存储方式                 //
//使用时注意：                                                           //
//			实例化时 typeClass 必须包含SetAttribInt，SetAttribInt64      //
//			SetAttribStr 函数                                            //
//      ChenXY         2011/9/15                                         //
///////////////////////////////////////////////////////////////////////////
template<typename T>
inline void g_Template_Blob_Derial(CUtlBuffer & buffer, T & typeClass)
{
	while(buffer.TellGet()< buffer.TellPut())
	{
		int nkey = INVALID_VALUE;
		int nValue = INVALID_VALUE;
		int64 i64Value= INVALID_VALUE64;
		char  szString[MAX_ALIAS_NAME_LEN] = {0};

		short sType = buffer.GetShort();
		switch (sType)
		{
		case EBST_Int:   //int
			{ 
				g_Blob_DerialInt(buffer,nkey,nValue);
				//--为保证数据源统一，要删掉Buff中的等级属性，又不能清数据库，建议3.0版本以后重构此方法，添加版本号-- del by zgz 2012-3-21
				if ( nkey != Role_Attrib_Level )
				{
					typeClass.SetAttribInt(nkey,nValue);
				}
				break;
			}
		case EBST_Int64:   // int64
			{
				g_Blob_DerialInt64(buffer,nkey,i64Value);
				typeClass.SetAttribInt64(nkey,nValue);
				break;
			}
		case EBST_String:   // str
			{
				g_Blob_DerialStr(buffer,nkey,szString);
				typeClass.SetAttribStr(nkey,szString);
				break;
			}
		default: assert(0);   //如果有其他类型，请补充完整。
		}
	}
}

//--根据背包类型返回所对应的人物元神类型--
//--nIndex：背包类型 enum Bag_UI_Index--
inline ESoulSysType GetSoulTypeByBagIndex( int nIndex )
{
	switch(nIndex)
	{
	case EquipBag_Index:
		return ESoulSys_MingHun;
		break;
	case EquipBagDiHun_Index: 
		return ESoulSys_DiHun;
		break;
	case EquipBagTianHun_Index:
		return ESoulSys_TianHun;
		break;
	default: assert(0);
	}
	return ESoulSys_Invalid;
}

//--根据人物元神类型返回所对应的背包类型--
//--nSoulType：元魂类型 enum ESoulSysType--
inline Bag_UI_Index GetBagIndexBySoulType( int nSoulType )
{
	switch(nSoulType)
	{
	case ESoulSys_MingHun:
		return EquipBag_Index;
		break;
	case ESoulSys_DiHun: 
		return EquipBagDiHun_Index;
		break;
	case ESoulSys_TianHun:
		return EquipBagTianHun_Index;
		break;
	default: assert(0);
	}
	return EquipBag_Index;
}


//系统设置选项
enum SYSTEMSET_OPTION
{
	//预留5个频道给聊天  1-14位为聊天设置
	CHAT_EXPLORERCHANNEL = 1 << 0,
	CHAT_AREACHANNEL     = 1 << 1,
	CHAT_WORLDCHANNEL    = 1 << 2,
	CHAT_STATECHANNEL    = 1 << 3,
	CHAT_GANGCHANNEL     = 1 << 4,
	CHAT_FAMILYCHANNEL   = 1 << 5,
	CHAT_TEAMCHANNEL     = 1 << 6,
	CHAT_FRIENDCHANNEL   = 1 << 7,
	CHAT_PVPCHANNEL		 = 1 << 8,

	//预留3个位置给功能  15-25为功能设置
	FUNCTION_ALLOWTEAM			 = 1 << 11,
	FUNCTION_AUTOTEAM			 = 1 << 12,
	FUNCTION_ALLOWBUSINESS       = 1 << 13,
	FUNCTION_ADDFRIEND           = 1 << 14,
	FUNCTION_ALLOWJOIN_GANG      = 1 << 15,
	FUNCTION_ALLOWJOINFAMILY     = 1 << 16,
	FUNCTION_ALLOWSEEEQUIP       = 1 << 17,
	FUNCTION_EXTENDSKILL		 = 1 << 18,

	//显示
	SHOW_EFFICT		    = 1 << 21,		
	SHOW_ROLENAME       = 1 << 22,		//是否显示玩家名称
	SHOW_MinMap		    = 1 << 23,		//是否显示小地图
	SHOW_HEADTOPEXP     = 1 << 24,		//是否显示头顶经验
	SHOW_GROUNDPROPNAME = 1 << 25,		//是否显示地面物品名称
	SHOW_CHATPAOPAO     = 1 << 26,		//是否显示队伍聊天泡泡
	SHOW_CENTERNOTIFY   = 1 << 27,		//是否显示屏幕中央公告
	SHOW_AUTOPICK		= 1 << 28,		//是否自动拾取
};



enum	TEAM_ERROR_CODE
{
	MAPNOTALLOW = 0 , //此玩家当前所在的地图不允许组队
};

enum GameTVType
{
	GTV_Invalid = -1,
	GTV_Common,							//普通
	GTV_KillBoss,								//击杀BOSS
	GTV_KillEnemy,              //国内杀敌
	GTV_PeachGarden,           //桃园结义
};

struct sPeopleData_T
{
	sPeopleData_T()
	{
		m_PID = INVALID_PID;
		m_nPower = -1;
		m_nPos = 0;
		nFamilyID = -1;
		nTeamID = -1;
		memset(m_szName,0,sizeof(m_szName));
	}
	PersonID m_PID;
	int m_nPos;
	int m_nPower;	//官职
	int nFamilyID;
	int nTeamID;
	char m_szName[MAX_ALIAS_NAME_LEN];
};

//定义战斗功勋兑换商店的商品
enum CombatCredit_ProductExChangeType
{
	ESANLUE = 1,
	ELIUTAO,
	MENGDEXINSHU,
	SUNZIBINGFA,
};

struct sTVMsgParam_T
{
	sTVMsgParam_T()
	{
		PID_One = INVALID_PID;
		PID_Two = INVALID_PID;
		nIndex_One = INVALID_VALUE;
		nIndex_Two = INVALID_VALUE;
		nIndex_Three = INVALID_VALUE;
		nType = INVALID_VALUE;
		memset(szName_One,0,sizeof(szName_One));
		memset(szName_Two,0,sizeof(szName_Two));
		memset(szName_Three,0,sizeof(szName_Three));
		memset(szName_Four,0,sizeof(szName_Four));
		nTvMsgType = INVALID_VALUE;
	}

	PersonID	PID_One;
	PersonID	PID_Two;
	int				nIndex_One;
	int				nIndex_Two;
	int				nIndex_Three;
	int				nType; // enum TV_Type	
	char				szName_One[ROlE_NAME_LEN_MAX]	;
	char				szName_Two[ROlE_NAME_LEN_MAX];
	char				szName_Three[ROlE_NAME_LEN_MAX];
	char				szName_Four[ROlE_NAME_LEN_MAX];
	int				nTvMsgType;
};

//注意：使用这个宏，必须要保证Dest是一个 char [] ，而不是一个 char *
#define _STRNCPY_F(Dest,Src) \
		strncpy(Dest,Src,sizeof(Dest) - 1); \
		Dest[sizeof(Dest) - 1] = '\0';



//--家族战车颜色分别是：普通（白），绿，蓝，紫，金
const int	COLOR_FAMILYCAR_MODEL_COMMON = 49;
const int	COLOR_FAMILYCAR_MODEL_GREEN = 806;
const int	COLOR_FAMILYCAR_MODEL_BLUE = 807;
const int	COLOR_FAMILYCAR_MODEL_PURPLE = 808;
const int	COLOR_FAMILYCAR_MODEL_GOLD = 809;

//寻路颜色
const int	COLOR_FAMILYCAR_FINDWAY = 533;		


#define  Car_Stop_Dist 20 



// 字符串IP 转 int64 类型
inline int64 StrIpToInt64(char* strIP)
{
	if(!strIP || strlen(strIP) <= 0)
		return 2885681153LL;		//当IP 无效时 返回 "172.0.0.1" 的 64位数

	std::string sIp = strIP;

	CToken token;
	token.setToken(".");
	token.parseString(sIp);

	int64 iRsult = 0;
	for( int nIndex = 0; nIndex< 4; nIndex++)
		iRsult |= token.getInt64(nIndex) << 8 * (3 - nIndex);

	return iRsult;
}	

// 套装类型
enum ESuit_Type
{
	ESuit_Type_Quality = 1,		//品质套装
	ESuit_Type_Star,			//星套装
};

//据策划需求，改为是否允许观察系统消息提示
enum ESeeEquip
{
	ESE_AllowSee 	= 1,
	ESE_UnAllowSee 	= 2,
};

const int SUIT_EFFECT_TYPECOUNT		 = 2;				//套装类型数量(星套装, 品质套装)
const UINT	QUALITYSUIT_EFFECT_EQUIP_MINCOUNT = 8;		//品质套装效果最低8件
const UINT	STARSUIT_EFFECT_EQUIP_MINCOUNT = 12;		//星套装效果最低12件
const UINT	STARSUIT_EFFECT_STAR_MINCOUNT	= 6;		//星套装最低6星(3颗整星)

const UINT	SUIT_EFFECT_GROUPMAXNUM =	ESoulSys_End + 1;	//套装组数( 命魂, 地煞, 天煞 ) + 1 (坐骑)
const UINT	SUIT_EFFECT_RIDEPETINDEX =	ESoulSys_End;		//1 (坐骑) 索引

const int SUIT_EFFECT_EQUIP_MINCOUNT = 8;
const int SUIT_EFFECT_EQUIP_MAXCOUNT = 12;
const int EQUIP_MAXCOUNT = 14;							//套装效果装备件数

					
//////////////////////////////////////////////////////////////////////////
const int EQUIPCOMPOSELEVELRANGE = 20;				// 装备合成范围	
//////////////////////////////////////////////////////////////////////////

const int PROP_STARSTONESEALLEVELUP = 20;	// 拆除封星石的等级 与装备等级上行差值

//////////////////////////////////////////////////////////////////////////
const Type_Money MONEY_RADIX		= 1000;						// 金钱进制，(%)取模用
const Type_Money MONEY_WEN_RADIX	= 1;						// 金钱计算文的进制，(/ *)乘除用
const Type_Money MONEY_LIANG_RADIX = MONEY_RADIX;				// 金钱计算两的进制，(/ *)乘除用
const Type_Money MONEY_DING_RADIX	= MONEY_RADIX*MONEY_RADIX;	// 金钱计算锭的进制，(/ *)乘除用
const Type_Money MONEY_ONEDING		= 1000000;					// 金钱一定



// 金钱转换
// GetMoneyNum 根据锭两文获取总钱数
inline Type_Money GetMoneyNum(int d,int l,int w) { return(Type_Money)((d*MONEY_DING_RADIX) + (l*MONEY_LIANG_RADIX) + w); }
// GetMoneyWen GetMoneyLiang GetMoneyDing将总钱数拆分成3种单位的数量,例如 1002003 算出来是 1锭2两3文
inline Type_Money GetMoneyWen(Type_Money t) { return(t%MONEY_RADIX); }
inline Type_Money GetMoneyLiang(Type_Money t) { return((t/MONEY_LIANG_RADIX)%MONEY_RADIX); }
inline Type_Money GetMoneyDing(Type_Money t) { return(t/MONEY_DING_RADIX); }
// GetMoneyDLW将总钱数拆分成3种单位的数量,一次处理3个单位,例如 1002003 算出来是 1锭2两3文
inline void GetMoneyDLW(Type_Money t,int& d,int& l,int& w) { d = (t/MONEY_DING_RADIX); l = ((t/MONEY_LIANG_RADIX)%MONEY_RADIX); w = (t%MONEY_RADIX); }
// ChangeToWen ChangeToLiang ChangeToDing根据锭两文分别转换成各个单位的数量,例如 1002003 算出来是 1锭或者1002两或者1002003文
inline Type_Money ChangeToWen(int d,int l,int w) { return(GetMoneyNum(d,l,w)); }
inline Type_Money ChangeToLiang(int d,int l,int w) { return(GetMoneyNum(d,l,w)/MONEY_LIANG_RADIX); }
inline int ChangeToDing(int d,int l,int w) { return(GetMoneyNum(d,l,w)/MONEY_DING_RADIX); }


//--系统功能开关--
enum ESystemSwitch
{
	SWITCH_FLAG_MATERIAL_COMPOSE				= 0,	//材料合成
	SWITCH_FLAG_YEARWINE,								//百年陈酿
	SWITCH_FLAG_NPC_DROP,								//怪物掉落
	SWITCH_FLAG_EQUIP_COMPOSE,							//装备合成
	SWITCH_FLAG_EQUIP_SIGNBIND,							//签名绑定
	SWITCH_FLAG_EQUIP_ADDSTAR,							//装备升星
	SWITCH_FLAG_EQUIP_ADDHOLE,							//装备打孔
	SWITCH_FLAG_EQUIP_ADDGEM,							//装备镶嵌宝石
	SWITCH_FLAG_EQUIP_REMOVEGEM,						//装备摘除宝石
	SWITCH_FLAG_EQUIP_REMOVESTAR,						//装备摘除星星
	SWITCH_FLAG_EQUIP_APPENDSTAR,						//装备附加星星
	SWITCH_FLAG_EQUIP_REBIND,							//装备重新绑定
	SWITCH_FLAG_EQUIP_CHANGE_FIVEELEMENT,				//装备修改五行
	SWITCH_FLAG_EQUIP_CHANGE_SOULCHAIN,					//装备修改灵魂锁链
	SWITCH_FLAG_EQUIP_SUIT,								//装备套装


	SWITCH_FLAG_PLAYER_BUSINESS,						//玩家交易
	SWITCH_FLAG_STALL_BUSINESS,							//摆摊交易
	SWITCH_FLAG_STORAGE,								//仓库
	SWITCH_FLAG_MAIL,									//邮件
	SWITCH_FLAG_AUCTION,								//拍卖行
	SWITCH_FLAG_DRAGONCONVERTSILVER,					//龙币兑换银子
	SWITCH_FLAG_BANK_STORE_SILVER,						//银号存放银子
	SWITCH_FLAG_BANK_TAKEOUT_SILVER,					//银号取出银子
	SWITCH_FLAG_BEG_BUY,								//求购行


	SWITCH_FLAG_FELLOW_FREEDOM,							//宠物放生
	SWITCH_FLAG_FELLOW_REFINE,							//宠物炼化
	SWITCH_FLAG_FELLOW_GIVEBACK_SOUL,					//珍兽还魂
	SWITCH_FLAG_FELLOW_FEED,							//珍兽喂养
	SWITCH_FLAG_FELLOW_STRENGTHEN,						//珍兽强化
	SWITCH_FLAG_FELLOW_BREED,							//珍兽繁殖
	SWITCH_FLAG_FELLOW_REBIRTH,							//珍兽重生
	SWITCH_FLAG_FELLOW_HUANHUA,							//珍兽幻化
	SWITCH_FLAG_FELLOW_PROTECT,							//珍兽守护
	SWITCH_FLAG_HORSE_RIDE,								//马匹骑乘
	SWITCH_FLAG_HORSE_EQUIP,							//马匹装备穿着
	SWITCH_FLAG_HORSE_STRENGTHEN,						//马匹强化


	SWITCH_FLAG_CHANGE_EQUIP,							//兑换装备
	SWITCH_FLAG_CASTE_HELP,								//社会关系呼救
	SWITCH_FLAG_FULMINIC_DROP,							//爆出掉落
	SWITCH_FLAG_SPECIFIC,								//特效
	SWITCH_FLAG_VOICE,									//音效
	SWITCH_FLAG_CHANGE_SOUL_TO_DISHA,					//星宿切换至地煞
	SWITCH_FLAG_CHANGE_TITLE,							//称号切换
	SWITCH_FLAG_AUTO_ATTACK,							//自动打怪
	SWITCH_FLAG_AUTO_COLLECT,							//自动采集
	SWITCH_FLAG_AUTO_OPRATINGUNIT,						//辅助系统
	SWITCH_FLAG_PKTYPE_PEACE,							//切换和平模式
	SWITCH_FLAG_PKTYPE_ALL,								//切换全体模式
	SWITCH_FLAG_PKTYPE_STATE,							//切换国家模式
	SWITCH_FLAG_PKTYPE_UNION,							//切换盟国模式
	SWITCH_FLAG_PKTYPE_FAMILY,							//切换家族模式
	SWITCH_FLAG_PKTYPE_GANG,							//切换帮会模式
	SWITCH_FLAG_PKTYPE_EVIL,							//切换善恶模式
	SWITCH_FLAG_PKTYPE_STATEWAR,						//切换国战模式
	SWITCH_FLAG_FELLOW_AUTO_OPRATINGUNIT,				//宠物辅助系统
	SWITCH_FLAG_SEND_ROSE,								//赠送玫瑰
	SWITCH_FLAG_SEND_QIANZHIHE,							//赠送千纸鹤
	SWITCH_FLAG_SILVER_PROTECTED,						//财产保护
	SWITCH_FLAG_SAFETY_TIMELIMIT,						//安全时限
	SWITCH_FLAG_CHANGE_REDNAME,							//改变红名
	SWITCH_FLAG_SYSTEM_SET_CHAT,						//系统设置-聊天
	SWITCH_FLAG_SYSTEM_SET_FUNCTION,					//系统设置-功能
	SWITCH_FLAG_SYSTEM_SET_OTHER,						//系统设置-其它
	SWITCH_FLAG_RESET_JOB,								//洗职业
	SWITCH_FLAG_RESET_ATTRIB_POINT,						//洗属性点
	SWITCH_FLAG_LEARNSKILL,								//技能学习
	SWITCH_FLAG_REVIVE,									//原地复活
	SWITCH_FLAG_REVIVE_FUNSTATUS,						//满状态复活
	SWITCH_FLAG_OPEN_BIAOJU,							//开启镖局
	SWITCH_FLAG_BIAOJU_COMPETE,							//镖局竞标
	SWITCH_FLAG_REFRESH_TOP,							//刷新排行榜
	SWITCH_FLAG_GAIN_TOPHERO_HORTATION,					//获取国家英雄排行榜奖励
	SWITCH_FLAG_ATTACK_EXPLOIT,							//战斗功勋（获得/兑换经验）
	SWITCH_FLAG_PRACTISE_EXPLOIT,						//历练功勋（获得/兑换经验）
	SWITCH_FLAG_STATEWAR_BADGE,							//国战徽章（获得/兑换经验）
	SWITCH_FLAG_CLOSE_NAME_SHIELDCHAR,					//关闭名称屏蔽字库
	SWITCH_FLAG_CLOSE_CHAT_SHIELDCHAR,					//关闭料条屏蔽字库
	SWITCH_FLAG_LEVELUP_BUTTON,							//升级按钮


	SWITCH_FLAG_ACCEDETO_FAMILY,						//进入家族
	SWITCH_FLAG_LEAVE_FAMILY,							//离开家族
	SWITCH_FLAG_DEDUCT_FAMILYMANOR_UPKEEP_COST,			//每天0点扣除家族庄园费用
	SWITCH_FLAG_RETURN_FAMILYCREDIT,					//家族贡献度返还
	SWITCH_FLAG_FAMILYBUILDING_LEVELUP,					//家族升级家族建筑
	SWITCH_FLAG_BALANCEINHAND_WAGE,						//结算工资
	SWITCH_FLAG_WEEK_BALANCEINHAND_WAGE,				//每周1点结算工资
	SWITCH_FLAG_ALLOW_ADD_ENEMY,						//允许加入仇人
	SWITCH_FLAG_ALLOW_ADD_BLACKLIST,					//允许加入黑名单
	SWITCH_FLAG_ALLOW_SWORN_BROTHER,					//允许结拜
	SWITCH_FLAG_ALLOW_MARRIAGE,							//允许结婚
	SWITCH_FLAG_ALLOW_UNMARRY,							//允许离婚
	SWITCH_FLAG_ALLOW_ADD_FRIEND,						//允许加为好友
	SWITCH_FLAG_ALLOW_EMIGRATION,						//允许移民
	SWITCH_FLAG_ALLOW_ABDICATION,						//允许退位-国家
	SWITCH_FLAG_ALLOW_DEMISSION,						//允许辞职-国家
	SWITCH_FLAG_ALLOW_APPOINT,							//允许任命-国家
	SWITCH_FLAG_ALLOW_OPEN_WAGE,						//打开工资
	SWITCH_FLAG_ALLOW_CHANGE_ACTIVITYPOINT,				//允许改变活跃度
	SWITCH_FLAG_CREATE_GANG,							//创建帮会
	SWITCH_FLAG_ADD_GANG,								//加入帮会
	SWITCH_FLAG_LEAVE_GANG,								//离开帮会
	SWITCH_FLAG_TRANSFER_GANGLEADER,					//转移帮主
	SWITCH_FLAG_ALLOW_USE_GANGTOKEN,					//允许使用帮会令牌
	SWITCH_FLAG_ALLOW_FIREPOWER,						//允许罢免-国家
	SWITCH_FLAG_ALLOW_FORBID_SPEAK,						//允许禁言-国家
	SWITCH_FLAG_ALLOW_SETPRISONER,						//允许囚禁-国家
	SWITCH_FLAG_ALLOW_RELEASEPROSONER,					//允许释放囚犯-国家
	SWITCH_FLAG_ALLOW_USE_KINGTOKEN,					//允许使用国王令牌
	SWITCH_FLAG_ALLOW_USE_KINGJADE,						//允许使用王者令牌
	SWITCH_FLAG_ALLOW_ATTACK_ZAIXIANG,					//允许攻击宰相
	SWITCH_FLAG_ALLOW_SEE_STATEPAGE,					//允许查看国家页签
	SWITCH_FLAG_ALLOW_CREATE_FAMILYTANK,				//允许打造战车
	SWITCH_FLAG_ALLOW_ADD_FAMILYTANK,					//允许添加战车
	SWITCH_FLAG_ALLOW_TAKE_FAMILYTANK,					//允许领取战车


	SWITCH_FLAG_TAOYUAN_ASSOCIATION,					//桃园结义
	SWITCH_FLAG_COLOR_DEER,								//五彩仙鹿
	SWITCH_FLAG_CATCH_TOKEN,							//逮捕令
	SWITCH_FLAG_GET_TOGETHER,							//聚义
	SWITCH_FLAG_KEJU_EXAM,								//科举考试
	SWITCH_FLAG_XINGXIAZHANGYI,							//行侠仗义
	SWITCH_FLAG_FAMILY_BUIDING,							//家族建设
	SWITCH_FLAG_FAMILY_BOSS,							//家族BOSS
	SWITCH_FLAG_FAMILY_GET_TOGETHER,					//家族聚义
	SWITCH_FLAG_DAMINGFU_ESCORT,						//大名府运镖
	SWITCH_FLAG_FAMILY_CHALLENGE,						//家族挑战赛
	SWITCH_FLAG_YUANZHENG_STATE,						//跨国远征
	SWITCH_FLAG_HEROISLAND,								//点将台
	SWITCH_FLAG_WANGCHENG_ESCORT,						//王城运镖
	SWITCH_FLAG_FAMILY_ESCORT,							//家族运镖
	SWITCH_FLAG_COUNTERESPIONAGE,						//策反
	SWITCH_FLAG_STATE_WATER,							//国家圣水
	SWITCH_FLAG_FAMILY_CARNIVAL,						//家族嘉年华
	SWITCH_FLAG_CITY_BARBECUE,							//城市挂机
	SWITCH_FLAG_GANG_SEIZEPOWER_WAR,					//帮会夺城战
	SWITCH_FLAG_GUOYUN_ACTION,							//国运
	SWITCH_FLAG_GUOCE_ACTION,							//国策
	SWITCH_FLAG_SMALLHELP,								//小帮手
	SWITCH_FLAG_DAY_ACTIVITY_LIST,						//每日活动列表
	SWITCH_FLAG_GANG_SEIZEPOER_DRAW_OCCUPYBANKROLL,		//帮会夺城战-领取每日王城占领资金
	SWITCH_FLAG_STATEWAR,								//国战
	SWITCH_FLAG_WORSHIP,								//膜拜

	SWITCH_FLAG_GAIN_TOP_FLOWER_HORTATION,				//获取鲜花宝贝排行榜奖励
	SWITCH_FLAG_GAIN_TOP_EXPLOIT_HORTATION,				//获取功勋值排行榜奖励
	SWITCH_FLAG_COMBINEWITHCOMBATPET,					//与战宠合体
	SWITCH_FLAG_ALL_BOSS,								//BOSS刷新总开关
	SWITCH_FLAG_FIXED_BOSS,								//固定BOSS刷新开关
	SWITCH_FLAG_RAND_BOSS,								//随机BOSS刷新开关
	SWITCH_FLAG_SUPER_BOSS,								//超级BOSS刷新开关
	SWITCH_FLAG_CHANGE_SOUL_TO_MINGHUN,					//星宿切换至本元

	SWITCH_FLAG_END,

};
const int SYSTEMSWITCH_ARRAY			= 256;			//开关大小

#define EXECUTE_GMCODE_LEVEL			1


// --GM指令执行安全检查宏
#define CHECK_EXECUTE_GMCODE_RETURNBOOL(p)\
	if(!p) return FALSE;\
	CPlayer* pGamePlayer = dynamic_cast<CPlayer*>(p);\
	if (pGamePlayer)\
	{\
		if (FALSE == pGamePlayer->IsCanExecuteGMcode()) return FALSE;\
	}\
	else{ return FALSE;}

#define CHECK_EXECUTE_GMCODE_RETURNVOID(p)\
	if(!p) return;\
	CPlayer* pGamePlayer = dynamic_cast<CPlayer*>(p);\
	if (pGamePlayer)\
	{\
		if (FALSE == pGamePlayer->IsCanExecuteGMcode()) return;\
	}\
	else{ return;}


//特效称号
enum EffectDesignation
{
	Effect_Designation_Begin = 20,
	Effect_Designation_MGXZ,		//玫瑰仙子
	Effect_Designation_XZYM,		//仙姿玉貌
	Effect_Designation_GSTX,		//国色天香
	Effect_Designation_JDTJ,		//绝代天骄
	Effect_Designation_TXDY,		//天下第一
	Effect_Designation_End,
};

//头顶文字 add by lfy 2012.10.7
enum HeadString_ID
{
	HeadString_StateWar = 0,		//国战
	HeadString_FamilyChallengeA,	//家族挑战赛A
	HeadString_FamilyChallengeB,	//家族挑战赛B
	HeadString_GangFightAttack,		//帮会夺城战攻
	HeadString_GangFightDefence,	//帮会夺城战守
};

//GM工具返回结果
enum GMTOOL_LOGINRETURNTYPE
{
	GMTOOL_LOGINRETURNTYPE_SUCCESS  = 1,//登录成功
	GMTOOL_LOGINRETURNTYPE_FAIL		,   //验证失败
	GMTOOL_LOGINRETURNTYPE_LOGED  ,		//GM账号已登陆
};

//DB返回给gm工具的错误消息
enum GMTOOL_DBErrorID
{
	GMTOOL_DBError_Mail_Success = 1,	//创建邮件成功
	GMTOOL_DBError_Mail_NoPlayer ,		//创建邮件失败-未找到玩家
	GMTOOL_DBError_Mail_CreateError,	//创建邮件失败
	GMTOOL_DBError_Radio_CreateError,	//创建公告失败
	GMTOOL_DBError_Radio_CreateSuccess,	//创建公告成功
	GMTOOL_DBError_ForbidSpeak_Success,	//禁言成功
	GMTOOL_DBError_ForbidSpeak_Error,	//禁言失败
	GMTOOL_DBError_UnForbidSpeak_Success,	//解除禁言成功
	GMTOOL_DBError_UnForbidSpeak_Error,	//解除禁言失败
	GMTOOL_DBError_SetSystemSwitch_Success,	//修改系统开关成功
	GMTOOL_DBError_SetSystemSwitch_Error,	//修改系统开关失败
	GMTOOL_DBError_LoadScript_Success	,	//加载脚本成功
	GMTOOL_DBError_LoadScript_Error		,	//加载脚本失败
	GMTOOL_DBError_ReloadNumerical_Success		,	//重载数据表成功
	GMTOOL_DBError_ReloadNumerical_Error		,	//重载数据表失败
	GMTOOL_DBError_SynchRoleByUID_Sucess		,	//按UID同步角色成功
	GMTOOL_DBError_SynchRoleByUID_Error		,	//按UID同步角色失败
	GMTOOL_DBError_ReviveRole_Sucess		,	//恢复角色成功
	GMTOOL_DBError_ReviveRole_Error		,	//恢复角色失败
};

//GM工具权限
enum GMTOOL_RIGHTLEVEL
{
	GMTOOL_RIGHTLEVEL_INVALID = -1,		//无效
	GMTOOL_RIGHTLEVEL_QUERRYLIMIT = 1,	//部分查询权限
	GMTOOL_RIGHTLEVEL_QUERRYALL ,		//全部查询权限
	GMTOOL_RIGHTLEVEL_ALTERLIMIT ,		//部分修改权限
	GMTOOL_RIGHTLEVEL_ALTERALL ,		//全部修改权限
	GMTOOL_RIGHTLEVEL_TOP ,				//最高权限
};

//GM工具请求类型
enum GMRequireType
{
	GMRequireType_INVALID	= -1,	//无效
	GMRequireType_Player = 0,	//请求玩家属性
	GMRequireType_State,		//国家
	GMRequireType_Gang,			//帮会
	GMRequireType_Family,
};

#ifdef _DATASERVER_
// 道具属性 转换 人物属性
int G_PropAttribKeyConvertPlayerAttribKey( int nKey );
#endif

// GBK Convert UTF8		GBK 转 UTF8	返回值： 字符串长度
int ConvertGBKToUTF8(char* strGBK, char* strDestUTF8, int nMaxSize );
// UTF8 Convert GBK		UTF8 转 GBK	返回值： 字符串长度
int ConvertUTF8ToGBK(char* strUTF8, char* strDestGBK, int nMaxSize);

//--仅供编译，默认引用
static int	g_DefaultRef =0;
