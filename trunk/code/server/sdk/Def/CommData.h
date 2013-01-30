//
//
//			commdata.h
//
//					�����õù�����ͷ�ļ������м�¼��һЩ������
//			�ṹ�壬��һЩ����� ���������� ��Щ�������ǲ߻���
//			����Ҫʹ�õò��֡�
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


//����ʹ�õĹ�ϣ�ṹ��
#define _CLXHLIST_
//#define _UTLHASH_
//#define _UTLMAP_

#ifndef PAYSERVER_OPENCLOSE_STATE
#define PAYSERVER_OPENCLOSE_STATE	TRUE	//֧��ϵͳ����
#endif

#ifndef PAY_SYNCH_MODE
#define PAY_SYNCH_MODE	FALSE	//֧��ϵͳ----> ͬ���첽���ƿ���
#endif

#ifndef	_NEWACTIVECODEGIFT_
#define _NEWACTIVECODEGIFT_		TRUE						// �µļ����������ʽ
#define _OLDACTIVECODEGIFT_		!_NEWACTIVECODEGIFT_		// �ɵļ����������ʽ (���»���)
#endif

#ifndef _USEUTF8_
#define _USEUTF8_	FALSE		//Ĭ�ϲ�����,
#endif

#define Bag_Max Bag_UI_End
//Ĭ��ϵͳ����
#define DEFAULT_SYSTEMSET 398715391

const int  MAX_OPENNUM  = 8;			// ���������������
const int  MAX_YEARWINESELECTCOUNT = 6;	// ����������ѡ������

const int QUEST_ID_MAX = 2000;				//������������

const int REPAIRTIPLOWNUM = 200;		// װ���;� ��� ��ʾֵ

const int  UTL_NO_GROW_TYPE = -1;
const int  UTL_DEFAULT_SIZE =100;

const int SKILL_SUMMON_FAMILYCAR = 608046;	//�ٻ�ս������ID add by zhangjianli 2012-10-5
const int Skill_Enter_FCar = 608070;		//����ս��ʱ��ʹ�õĶ�������
//
extern UINT g_GameTimer;
extern UINT g_Circles;
extern UINT GAME_FPS;

const UINT SERVER_TIMER_FREQUENCY = 25;
const UINT SERVER_TIMER_PERIOD = 1000 / SERVER_TIMER_FREQUENCY;

const int EVERYONE_ESELECT_MAILMAX = 100; //��ʱÿ������������ʼ�100��


typedef UINT64	PersonID;						// ��ҽ�ɫ��ID	-1 Ϊ��Чֵ
typedef UINT64  PropID;							// ����ID
typedef UINT64	SCENEID;						// ����ID
typedef UINT64	UserID;							// �ʻ�ID
typedef INT		NETID;							// ����ID		-1 Ϊ��Чֵ
typedef INT		SkillID;						// ����ID
typedef UINT    TABLEID;						// TableID
typedef INT		QuestID;						// ����ID
typedef UINT	ServerID;						// ������ID
typedef UINT    StateID;						// ����ID
typedef INT     TemplateID;						// Scene NPC,PROPģ��ID
typedef INT     ChatID;							// ����ID
typedef INT		UIPos;							// ���ߵ�UIλ��  ʮ���� aabbb�� aa��ʾ����������bbb��ʾ�����ڵ�λ��
typedef INT     TargetID;						// Ŀ��ID
typedef UINT64  EffectID;						// Ч��ID
typedef INT		BuffID;							// ״̬ID
typedef UINT64	TMV;							// ʱ������
typedef UINT64	RegTM;							// ע��ʱ������
typedef __int64	StatusFlag;						// ״̬ID
typedef UINT64	StatusFlagGroup;				// ״̬��
typedef UINT64  MailID;							// �ʼ�ID
typedef UINT64	PetID;							// ����ID
typedef INT     QuestionID;						// ��ĿID
typedef UINT64	AuctionID;						// ����ID
typedef UINT64  BuyID;                          // ��ID
typedef UINT64  BidID;                          // ����ID
typedef UINT64  BuyID;                          // ��ID
typedef UINT64	ClearingID;						// ������ID
typedef UINT64  CampaignID;                     // �ID
typedef UINT64	DialyMissionID;					// �ID
typedef UINT64	TrscID;							// ��Ǯ����ID
typedef INT64   Type_Money;                     // ��Ǯ��λ����


#define CURRENT_VERSION_ID			0			//add by mayanling 2010-3-23 ��ǰ�汾��

#ifdef _CLIENT_
#define USER_COUNT_MAX				1			// User������
#define NPC_COUNT_MAX				1000		// ��Ϸ����npc��
#define PLAYER_COUNT_MAX			500			// ��Ϸ����ʱ��ҵ������
#define EVENT_COUNT_MAX				200			// �¼������ֵ
#define PROP_COUNT_MAX				1000			// ��������
#define SCENE_COUNT_MAX				2			// �����������
#define FAMILY_COUNT_MAX			50			// ��������
#define ACTION_COUNT_MAX			100			//
#define CLEARING_COUNT_MAX			100			//
#define GANG_COUNT_MAX				100
#define MAIL_COUNT_MAX				100
#define SINGUP_COUNT_MAX			100			//�����
#define STORAGE_ROCK_COUNT_MAX		200			//
#define TEAM_COUNT_MAX				5			//������������
#define TOP_COUNT_MAX				200			//�������������
#define TIME_OBJ_COUNT_MAX			20			//ע��ʱ���obj
#define COUNTDOWN_TIME_COUNT_MAX	10			//���������
#define QUEST_QUESTION_COUNT_MAX	200
#define QUESION_TOP_COUNT_MAX		100			//����������������
#endif

const int EXPLORER_PLAYER_NUM_MAX	= 100;		//--ͬ���������������--




//��Чֵ����
#define INT_NULLITY					-1						// ���͵���Чֵ
#define	INVALIDSET					-1					// ��Ч��ֵ
#define INVALID_TIME				0xFFFFFFFFFFFFFFFFULL			// ��Ч��ʱ��
#define INVALID_VALUE				-1								// ��Ч��ֵ
#define INVALID_VALUE64				(int64)0xFFFFFFFFFFFFFFFFULL			//
#define INVALID_UINT64				0xFFFFFFFFFFFFFFFFULL			//
#define INVALID_POSITION			-1					// x,y����Чλ�õ�
#define INVALID_TEMPLATE			-1						// ��Ч��ģ��ID
#define INVALID_TABLEID				-1						// ��Ч��TableID
#define INVALID_PID					0xFFFFFFFFFFFFFFFFULL			// ��Ч��PID
#define INVALID_UID					0xFFFFFFFFFFFFFFFFULL			// ��Ч��UID
#define INVALID_SCENEID				0xFFFFFFFFFFFFFFFFULL			// ��Ч��SceneID
#define INVALID_SKILLID				-1
#define INVALID_QUESTID				-1						// ��Ч��QuestID
#define INVALID_INQUIRERID			-1						// ��Ч��InquirerID
#define INVALID_PROPID				0xFFFFFFFFFFFFFFFFULL			// ��Ч��PropID
#define INVALID_PETID				0xFFFFFFFFFFFFFFFFULL			//��Ч��PetID
#define INVALID_MAILID				0xFFFFFFFFFFFFFFFFULL			//��Ч��MailID
#define INVALID_UIPOS				-1					// ��Ч��UIλ��
#define INVALID_EFFECTID			0xFFFFFFFFFFFFFFFFULL			// ��Ч��Ч��ID
#define INVALID_BUFFID				-1
#define INVALID_TEAMID      		-1					//��Ч��TeamID
#define INVALID_QUESTIONID  		-1						//��Ч������ID
#define	INVALID_AUCID				0xFFFFFFFFFFFFFFFFULL			//��Ч������ID
#define	INVALID_BUYID				0xFFFFFFFFFFFFFFFFULL			//��Ч����ID
#define INVALID_CLEARINGID			0xFFFFFFFFFFFFFFFFULL			//��Ч�Ľ�����ID
#define INVALID_CAMPAIGN			0xFFFFFFFFFFFFFFFFULL			//��Ч�ĻID
#define INVALID_FAMILYID    		-1
#define FAIL						0								// ʧ��
#define OK							1								// �ɹ�
#define INVALID_ATTRIB_VALUE		-1
#define INVALID_TRSCID				0xFFFFFFFFFFFFFFFFULL			//��Ч�Ľ�ҽ���ID

//��������
#define GAME_WORLD_ROLE_COUNTS		10			// ��Ϸ���������ǵ�����
#define TRANSMIT_NUM_MAX            15          //��ͼ���ͱ������
#define MAX_ALIAS_NAME_LEN  		128
#define MAX_IP_ADD					30			// IP��ַ�ĳ���
#define MAX_FUN_LEN					256			// ��������
#define MAX_INQ_LEN					256			// �Ի�����
#define MAX_PATH_LEN				256			// ·������
#define MAX_LEVEL1_MEM				5			// ���������
#define MAX_LEAGUE_MEM				200			// �л���������
#define MSG_INFO_MAX				1024		// ��Ϣ���������
#define NAME_INFO_MAX				256			// ������������
#define PARM_TEMP_MAX				256			// ������������
#define STR_MUN_MAX					256			// ��ֵת�����ַ�����С
#define STR_LMUN_MAX				256			// ������ֵת�����ַ�����С
#define ATTRIB_NAME_MAX				256			// �������ǵ��ַ�����С
#define	MAX_ID_NUMBER				512
#define MAX_PROP_PROP				200			// ÿ�������Ͽ������ĵ��߸���
#define MAX_PROP_SKILL				5			// ÿ�������Ͽ������ļ�����
#define MAX_OBJ_ATTRIB_SIZE			1024		// GameObj�����Գ���
#define MAX_SCENE_COUNTS			10000		// ÿ�������Ͽ������ĵ��߸���
#define MAX_SCENE_CREATE_POSTS		100			// һ�������еĳ�������������
#define MAX_SCENE_SKILL				8000		// �����д�ŵ�skill�����ֵ
#define MAX_SCENE_CREATE_ID			50			// �����г�������������
#define MAX_SCENE_MAX_CREATE_POST	500			// һ�����������ĳ�����
#define ATTRIB_INVALID				-1000
#define PERCENT_RATE				100.00	    //�����аٷֱ����͵�����ʵ�ʴ洢��ֵ�ı���
#define MAX_PLAYER_NUM				100000		// ��ҵ�������
#define MAX_ROLEATTRIB_NUM			1000		// ��ǰ���������� ���Ϊ1000
#define MAX_PARTS					5			// װ��������
#define MAX_ROLE_PROP				1000		// ÿ�������Ͽ������ĵ��߸���
#define MAX_ROLE_SKILL				200			// ÿ�������Ͽ��еļ��ܸ���
#define MAX_ROLE_ATTRIB_STR			2000		// role��֯�������ַ�������󳤶�
#define MAX_MERCHANT_PROP			200			//����
#define MAX_SCENE_NUM				500			// ������������
#define EFFECT_PARAM_MAX			6			// һ�����õ�������
#define PERSON_SKILL_COUNT			500			//��¼���ӵ�еļ�������
#define GAME_SERVER_MAX_PLAYE		2000		//GameServer��ҵ���������
#define GM_CMD_MAX				50		// gm�������󳤶�
#define GM_CMD_VALUE_MAX				10		// gm������ֵ����󳤶�
#define ALLOWABLE_DELAY_TIME_MAX	100			//���������ӳ�ʱ�䣨ms��
const UINT PROP_TEMPPARAMCOUNT	=		4;		//������ʱ���ݴ洢����

#define FOLLOW_FLY_DIS		12				//�������ʱ�������˵ľ���

#define MAX_SINGNAME_LEN			400			//����ǩ��
#define DESIGNATION_COUNT			64			//������ϳƺ�����
#define ROUND_PERSON_FLOWER			200			//�ʻ�Χ��
#define SET_HEADEFFECT_SEAT			 20			//��λ
const int NUM_HOTKEYTEACH				=36;			//��ݼ���ѧ����

const int	MAX_BOSS_POINT_COUNT		= 10;			// ˢ��BOSS��������������    add by zhangjianli 2011-10-20
const int	MAX_BOSS_POINT_SCRIBE_LEN	= 64;			// ˢ��BOSS������λ��������󳤶�   add by zhangjianli 2011-10-20
const int	MAX_BOSS_DROP_RORP_NAME		= 256;			// ����BOSS������Ʒ������󳤶�	add by zhangjianli 2012-02-08
const int	GLOBAL_BOSS_COUNT_MAX		= 300;			// ȫ��BOSS������� add by zhangjianli 2011-10-21
#define  KING_RIDEPET_MODEL	8105 //����ר������ģ��ID
// ��ɫ���
const BYTE ROLE_COUNT_MAX			= 1;					// ��ɫ��������
const BYTE USER_NAME_LEN_MAX		= MAX_ALIAS_NAME_LEN;	// �ʻ�����󳤶�
const BYTE ROlE_NAME_LEN_MAX		= 25;					// ��ɫ����󳤶�
const BYTE PASSWORD_LEN_MAX			= 35;					// �������󳤶�
const int  CONFIRMATION_CODE_NUM_MAX				= 1;	//--������������--	Ŀǰ���ô˷�������ֵ��С�� change by zhaoguoze 2011-07-23
const UINT CONFIRMATION_CODE_LEN					= 20;	//--�����볤��--
const UINT CONFIRMATION_CODE_LEN_1					= 10;	//--�����볤��--
const int  CONFIRMATION_CODE_USED_TIMES_MAX		    = 1;	//--һ����������õĴ���--

#define PLAYER_COMMON_ATTACKID		1			//Ĭ�ϵ���ͨ����������
#define PLAYER_COMMON_DROWSKILLID	2			//��ͨԶ�̹���
#define PLAYER_COMMON_PICKUPSKILL	13			//Ĭ��ʰȡ����
#define PLAYER_COMMON_CAR_ATTACKID	14			//Ĭ�ϵ���ս����ʹ�õļ���
#define PLAYER_LEVEL_UP_SKILL		10			//������������
#define FELLOW_LEVEL_UP_SKILL		17			//������������

#define SECURITY_PERSON_LEVEL		30			// �Ʋ�����Ҫ������Ｖ��
#define SECURITY_PERSON_PWD_LEN		10			// �Ʋ��������볤��
#define PLAYER_DEFAULT_MODELCOLOR   514			//��ɫĬ�ϵ�������ɫ
// ��������ص�����
#define TASKNAMELEN	50
#define TASKNOTELEN	256
#define MAXLEAGUECOUNTS				5000		// һ����Ϸ���������������
#define MAXLEAGUEMEMBER				5000		// һ�������е�����Ա������
#define MAXLEAGUENAMELEG			256			// �������ֵ���󳤶�
#define MAXLEAGUEINFOLEG			1024		// ���˽�����Ϣ����󳤶�
#define MAX_GAMEWORLD_TEAM			5000		// ��Ϸ�е���������
#define NAMELENGTH					50	    	// ע�����ĳ���
#define IDTABLECOULD				5
#define DATADEBUGLEN				4096		// ���ݷ�������̬����ʾ�������ַ�������
#define	PUBLIC_SCENE_ID				5000		// ����������id

#define BUFF_GUIDON 2027

#define CAR_FARAWAY_DIST 20
#define GET_ARRAY_ITEMNUM(array)	(sizeof(array)/sizeof(*array))

#define AUTOSKILL_MAX_COUNT		5   //�Զ��ͷŵļ��������

#define SELFSHOP_GOOD_GROUP 72 // ��Ӧ goodsgroup.csv ���� "44  72	����	12	71	0	0" ��¼���������72�ı䣬��ֵҪ��Ӧ�޸�
struct AutoSkill
{
	int nSkillID;
	int nInterval;

};


// About of Mail
#define MAX_MAIL_TITLE_SIZE		50				// the size of title
#define MAX_MAIL_NOTE_SIZE		1024			// the size of mail note
#define PROPATTRIBCOUNTS		12				// ���߱��еĸı����Ե�����

#define  STSTE_NUM				500				// ״̬����
#define  Flag_MOD				1000			// ��ʾϵ��
#define MAX_SKILL_NUM			20000			// ���ļ��ܸ���
#define FACE_FLAGINDEX			1000			//������Ч���������

#define RED_FLOWERID            10467			//��õ��
#define WHITE_FLOWERID          10468			//��õ��
#define QIANZHIHEID				10469			//ǧֽ��

#define NUM_9_FLOWER			9				//9��					
#define NUM_99_FLOWER			99				//99��
#define NUM_365_FLOWER			365				//365
#define NUM_999_FLOWER			999				//999��

// װ����
// װ������
#define PROP_EQUIT_HD		10			// װ�� ͷ
#define PROP_EQUIT_TK		11			// װ�� �·�
#define PROP_EQUIT_GL		12			// װ�� ��
#define PROP_EQUIT_CR		13			// װ�� ����
#define PROP_EQUIT_FT		14			// װ�� Ь��

#define	EQUITECOUNTS		5
#define EQUITSTRLEN			32

#define MAX_STATE_COUNT		8			//���Ĺ�����


#define  PASSENGER_NUMBER	5			//��������

//AI���
const int	AUTO_MOVE_POINT_COUNT_MAX	= 20;	//�Զ�Ѱ·npc�����Ѱ··����

const int	COMBIN_DISTANCE =4 ;          //�����������

//����
#define  ZONE_TRANS_SCENE		0		 //�����͵ĵ�ͼid
#define  ZONE_AREA_X			1		 //�����͵�x����
#define  ZONE_AREA_Y			2		 //�����͵�y����
#define  ZONE_CAMPAIGN_INDEX	3        //��Ϸ������ʹ�õĲ������к�,��Ӧ�id
#define  ZONE_START_INDEX		4		 //��Ϸ����������Ӧ�������

#define	 BOMB_TYPE_TRUE			1
#define  BOMB_TYPE_FALSE		2

const int USER_EXT_POINT = 8;			 //�˺Ź�����չ������

//////////////////////////////////////////////////////////////////////////
//��ɫ��¼��ʽ
enum EPlayerLoginFlag
{
	CHANGE_SERVER,		//�������
	LOGIN_SERVER,		//��½
};

//��ɫ�ǳ���ʽ
enum EPlayerLogoutFlag
{
	LOGOUT_FLAG_CHANGE_SERVER,		//�������
	LOGOUT_FLAG_LOGOUT_SERVER,		//�˳���Ϸ
};

//////////////////////////////////////////////////////////////////////////
// ��׼NPCģ�嶨��
const int NPC_TEMPLATE_NEW_BIRTH		= 70;	//���ֳ�����
const int NPC_TEMPLATE_PEOPLE_REBIRTH	= 71;	//����������
//const int NPC_TEMPLATE_ANAMY_REBIRTH	= 52;	//���������	(����)
const int NPC_TEMPLATE_SAFE				= 53;	//���԰�ȫ��
const int NPC_TEMPLATE_FISH				= 54;	//������
const int NPC_TEMPLATE_GATHER			= 55;	//�ɼ���
const int NPC_TEMPLATE_MINING			= 56;	//�ɿ���
const int NPC_TEMPLATE_ELEMENT			= 57;	//Ԫ����
const int NPC_TEMPLATE_CULTURE			= 58;	//��ֳ��
const int NPC_TEMPLATE_FELLING			= 59;	//��ľ��
const int NPC_TEMPLATE_DANCE			= 60;	//������
const int NPC_TEMPLATE_WUSHU			= 61;   //������
const int NPC_TEMPLATE_STALL			= 62;	//��̯��
const int NPC_TEMPLATE_XIUXING			= 63;	//������
const int NPC_TEMPLATE_DAZUO			= 69;	//������
//const int NPC_TEMPLATE_UNGROUND_REBIRTH = 72;	//����������
//const int NPC_TEMPLATE_UNGROUND_BIRTH   = 76;	//����������
//const int NPC_TEMPLATE_GAME_REBIRTH		= 99;	//��Ϸ������


//////////////////////////////////////////////////////////////////////////
//--������--

//--���������--
enum TEAMTYPE
{
	TEAMTYPE_NONE			= 0,		//--��--
	TEAMTYPE_COMMON,					//--��ͨ���--
	TEAMTYPE_HONOR,						//--�������--
};

//--�����о������ģʽ--
enum TEAM_EXP_TYPE
{
	TEAM_EXP_NONE			= 0,		//--��--
	TEAM_EXP_SPECIAL,					//--�������--
	TEAM_EXP_LEVEL,						//--���ȼ�����--
};

//--�����е�ʰȡģʽ--
enum TEAM_ITEM_TYPE
{
	TEAM_ITEM_NONE			= 0,		//--��--
	TEAM_ITEM_FREE,						//--����ʰȡ--
	TEAM_ITEM_TURN,						//--����ʰȡ--
	TEAM_ITEM_RANDOM,					//--���ʰȡ--
};

//--�������ļģʽ--
enum TEAM_RECRUIT_TYPE
{
	TEAM_RECRUIT_NONE		= 0,		//--��--
	TEAM_RECRUIT_AUTO,					//--�Զ���ļ--
	TEAM_RECRUIT_MANUAL,				//--�ֶ���ļ--
};


const int	Team_Count_Max					= 6;	//--�����������--

const int	TEAMCAPTION_ICON				= 1001;	//--�ӳ�ͼ�꣬������ʾ--

const int	HONOR_STARE_ICON				= 2;	//--����֮��ͼ�꣬������ʾ--

const int	TEAM_HONOR_LEVEL_LIMITE			= 60;	//--������ӵĵȼ�����--

const int	TEAMBUFFERID_NUM				= 15;	//--buffer�ĸ���--

const int	TEAM_SET_POS_TIME				= 5;	//--5sͬ��һ�ض���λ��--

const float TEAM_EXP_ADDITION_BY_SPECIAL	= 0.1;	//--�������ʱ���龭��ӳɣ������о������ģʽ����������ʱ����������ѷֵľ���--

const float TEAM_EXP_ADDITION_BY_LEVEL		= 0.1;	//--�ȼ�����ʱ���龭��ӳɣ������о������ģʽ�ǵȼ������ʱ���ܾ���ӳ�--

const int	TEAM_CALL						= 1;	//--�������--
const int	TEAM_CALLED						= 2;	//--��ӱ���--
//////////////////////////////////////////////////////////////////////////
// ����ת��
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
//�Զ��һ�
enum AI_AUTO
{
	AI_AUTO_NO			= 0,			//δ�����Զ��һ�
	AI_AUTO_SKILL		= 1,			//����ʹ�ü����߼�
	AI_AUTO_Z			= 2,			//Ctrl+Z�һ�
	AI_AUTO_WAITERPET	= 3,			//����һ�
	AI_AUTO_LEFT		= 4,			//����Զ�����
	AI_AUTO_Z_PAUSE		,				//Ctrl+Z��ͣ
	AI_AUTO_WAITERPET_PAUSE,			//����һ� ��ͣ

	AI_AUTO_COLLECT     = 10,			//����ɼ��һ�  by zhao
	AI_AUTO_COLLECT_PAUSE,				//����ɼ��һ���ͣ	
};

enum AI_TYPE
{
	AI_TYPE_PLAYER	= 0,						//���

	AI_TYPE_NPC_FRIENDLY =1,					//�Ѻ�NPC
	AI_TYPE_MONSTER_ACTIVE = 3,					//������
	AI_TYPE_MONSTER_PASSIVE = 4,				//������
	AI_TYPE_MONSTER_NO_FIGHT,					//ɵ�Ϲ�
	AI_TYPE_NPC_CAT_AUTO,						//�Զ�Ѱ·�ڳ�
	AI_TYPE_NPC_CAT_FLOOW,						//�������
	AI_TYPE_PET_FELLOW,							//����
	AI_TYPE_PET_COMBAT,							//ս��
	AI_TYPE_PET_RID,							//����
	AI_TYPE_PET_ZONE,							//����
	AI_TYPE_SET_STALL,							//��̯��
	AI_TYPE_TRAP,								//����
	AI_TYPE_AURA,								//�⻷
	AI_TYPE_MONSTER_QUEST_TARGET_FIRST,         //����ˢ�¹�Ŀ������
	AI_TYPE_PORTAL,								//������
	AI_TYPE_NPC_FRIENDLY_CANATTACK,             //�ܵ��������ܻ������Ѻ�NPC
	AI_TYPE_SKILL_ZONE,							//�����ܵ�����
	AI_TYPE_MARRY_CARRIAGE,						//�鳵�߼�
	AI_TYPE_LANDMINE,							//����
	AI_TYPE_SPIRIT,								//�����߼�
	AI_TYPE_BOSS,								//BOSS AI
	AI_TYPE_CHANGE_AI_GROUP,                    //ת����ӪNPC AI
	AI_TYPE_SOLDIER,							//����
	AI_TYPE_CHARIOT,							//����ս��
	AI_TYPE_MONSTER_QUEST_PLAYER_FIRST,			//����ˢ�¹ֹ����������
	AI_TYPE_CHANGE_SCENE,						//������������
	AI_TYPE_TRIGGER_NPC_PROP,					//��Ϸ�еĴ��������npc
	AI_TYPE_TRIGGER_NPC_PROP_MULTI,				//��Ϸ�еĴ��������npc��Ⱥ��
	AI_TYPE_LANDMINE_FALSE,						//�ٵ���
	AI_TYPE_PROTECTED_TARGET,					//��������Ŀ��npc
	AI_TYPE_QUEST_AUTOZONE,						//�����Զ���������
	AI_TYPE_AUTODRIVE,							//�Զ���ʻ�Ĺ۹�AI
	AI_TYPE_SCRIPT,								//�ű�npc
	AI_TYPE_QUESTFOLLOW,						//������浥λ
	AI_TYPE_MONSTER_ACTIVE_PLACE,				//����������
	AI_TYPE_CAR_CAMPAIGN_PERSON,				//������ڳ�
	AI_TYPE_CAR_CAMPAIGN_FAMILY,				//������ڳ�
	AI_TYPE_CAR_NPC,							//�ڳ�����npc
	AI_TYPE_PROP_QUEST_NPC,						//��������ˢ�¹�
	AI_TYPE_GOD		= 100,						//�ϵ�

};


//////////////////////////////////////////////////////////////////////////////
//PK
//--ע��Ҫ����ҵ�PK״̬��enum PK_STATUS�����ֿ�--
enum PK_TYPE
{
	PK_TYPE_ALL			= 0, //ȫ��ģʽ
	PK_TYPE_PEACE,			//��ƽģʽ
	PK_TYPE_STATE,			//����ģʽ
	PK_TYPE_UNION,			//�˹�ģʽ
	PK_TYPE_GANG,			//���ģʽ
	PK_TYPE_FAMIY,			//����ģʽ
	PK_TYPE_EVIL,			//�ƶ�ģʽ
	PK_TYPE_ENEMY,			//����ģʽ		���ѷ�����
	PK_TYPE_CAMP,			//��Ӫģʽ
	PK_TYPE_STATEWAR,		//��սģʽ	add by zhangjianli 2012-02-17
	PK_TYPE_GANG_CANOT_SWITCH,	//ǿ�ư��ģʽ(�����ֶ��л�)
	PK_TYPE_FAMILY_CANOT_SWITCH,//ǿ�Ƽ���ģʽ(�����ֶ��л�)
	PK_TYPE_PROTECTED,			//����ģʽ�������ֶ��л���
};

//--PK״̬-- add by zhaoguoze 2011-03-16
//--������ʾ������ϵ�PK״̬����Ϊ����PK�ͷ��ͽ���������--
//--ע��Ҫ��PKģʽ��enum PK_TYPE�����ֿ�--
enum PK_STATUS
{
	PK_STATUS_ORDINARY						= 0,	//��ͨ					������
	PK_STATUS_HERO,									//Ӣ��					������(����)
	PK_STATUS_WELLDOER,								//����					������
	PK_STATUS_BADDIE,								//����					���ٺ�
	PK_STATUS_DEMON,								//��ħ					������
	PK_STATUS_DEMON_HEAD,							//ħͷ					�����
	PK_STATUS_MALICIOUS,							//���⹥��				������
	PK_STATUS_CHANGE,								//�����ָ�����ͨ״̬	����˸
};

//--PK��Ӫ��PKģʽΪ��Ӫģʽʱ������Ӧ����Ӫ��--
//--�������Ӫ����ֻ��Ϊ�˰���Ӫ���ֿ���û����������--
enum PK_CAMP
{
	PK_CAMP_INVALID = -1,	//--��Ч��PK��Ӫ--
	PK_CAMP_A = 0,			//--��ӪA--
	PK_CAMP_B,				//--��ӪB--
	PK_CAMP_C,				//--��ӪC--
};

//�ڳ�Ͷ����־
enum Car_TouBao_Flag
{
	CTF_Invalid = -1,
	CTF_Gold,
	CTF_Purple,
};

//�������״̬ add by zhangjianli 2012-9-17
enum Player_Stealth
{
	PLAYER_UNSTEALTH = 0,	//û������
	PLAYER_STEALTH,			//����
};

//֧��ϵͳ���Ӵ洢����
enum Storage_SilverType
{
	Storage_SilverType_PersonCar = 5,	//��������Ѻ��
	Storage_SilverType_FamilyCar	,	//�����ڳ�Ѻ��
	Storage_SilverType_EscortSignUp ,	//�ھ־���
	Storage_SilverType_EscortRunning ,	//�ھ���Ӫ�ʽ�
	Storage_SilverType_SealQuest     ,	//��ӡ����
	Storage_SilverType_Mail,  //�ʼ���Ҵ洢
    Storage_SilverType_Bank,  //���Ŵ洢
    Storage_SilverType_Sell, //���д洢
	Storage_SilverType_End,		//��Ҵ洢��������Ӷ������ڴ���֮ǰ
};


//#define     RED_NAME_DROP_ODDS  30					//����������߼���  ��Ϊ���� by fan
const int   PUSH_PRISON_BASE_ODDS			= 3;	//ɱ�˽�������������(�ٷֱ�)

const int	PRISON_TRANS_ID					= 1501;	//����������id
const int	PRISON_REALEASE_AREA_ID			= 1101;	//�ͷ�������id

const int	PK_VALUE_MAX					= 240;	//--PKֵ����-- change by zhangjianli 2012-01-05

const int	PK_VALUE_TYPE_HERO				= 240;	//--Ӣ��״̬�ٽ�ֵ�����ֵ����ΪӢ��״̬��������ֵ--
const int	PK_VALUE_TYPE_WELLDOER			= 100;	//--����״̬�ٽ�ֵ�����ֵ����Ϊ����״̬��������ֵ--
const int	PK_VALUE_TYPE_ORDINARY			= 0;	//--��ͨ״̬�ٽ�ֵ�����ֵ����Ϊһ��״̬��������ֵ--
const int	PK_VALUE_TYPE_BADDIE			= -50;	//--����״̬�ٽ�ֵ�����ֵ����Ϊ����״̬����������ֵ--
const int	PK_VALUE_TYPE_DEMON				= -100;	//--��ħ״̬�ٽ�ֵ�����ֵ����Ϊ��ħ״̬����������ֵ��һ�µ�Ϊħͷ״̬��������ֵ--
const int	PK_VALUE_TYPE_CHANGE			= -1;	//--�����ָ�����ͨ״̬�ٽ�ֵ�����ֵ����Ϊһ��״̬��������ֵ--
const int	PK_VALUE_TYPE_MALICIOUS			= 0;	//--���⹥��״ֵ̬--

const int	PK_VALUE_TO_PRISON				= -100;	//--PKֵС�ڴ�ֵǿ���ͽ�����--

const int	PK_VALUE_PLAYER					= 10;	//--����ɱһ���ˣ�PKֵ��Ĭ�ϳͷ�ֵ--
const int	PK_VALUE_PRIVATE_CAT			= 20;	//--�����һ�������ڳ���PKֵ��Ĭ�ϳͷ�ֵ--

const int	PK_PUNISH_TIMES					= 2;	//--����ɱ��Ӣ�ۣ�����������PK״̬����ң����ܵ��ӱ��ͷ�--

//--ÿ��һ��ʱ��ʱ�䣨�룩��һ��PKֵ--
//--��λ����--
const int	PK_ADD_VALUE_TIME				= 720;	//--ÿ������PKֵʱ������720s��1Сʱ�ָ�5�㣩-- change by zhangjianli 2012-7-21

//--ÿ�����ӵ�PKֵ������--
//--ע����ֵ���ܴ��ڸ���״̬�ٽ�ֵ�����Լ��--
const int	PK_VALUE_ONCE_ADD_NUM			= 1;

//--���⹥��״̬����ʱ��--
//--��λ����--
//--ע	�����⹥��״̬ʱ�䲻�����̴��������ʱ�������ߣ��򻻷����������߻����¼�ʱ�����Դ�ʱ�䲻�˹���--
const int	PK_TIME_MALICIOUS_STATUE		= 120;

const int	COMMON_GAME_OVER_CD_TIME		= 300;	//--��ͨ���������Զ���ȫ�����ʱ�䣨�룩--

const int	ROLE_REVIVE_TIMES_MAX			= 10;	//ԭ�غ���״̬������ӽ�Ǯ�������� add by zhangjianli 2011-10-12

const int	PK_CAR_PROTECTED_LEVEL			= 50;	//--�������ڵ��ڳ������ȼ�--

const int	ACTIVE_ENERGY_TASKID			= 4706;	//--�������ֵ����ID�������жϻ���ֵ�Ƿ񼤻�������ֵ�й�ϵ�Ĺ���-- add by zhangjianli 2012-7-5
const int	FELLOWREFINERY_DAYTIMES			= 10;	//--���ÿ������������޵��������-- add by zhangjianli 2012-7-13

enum Campaign_PK_TYPE
{
	Campaign_PUNISH_HORTATION				=0,		//�pk�ͷ�������
	Campaign_NO_PUNISH_NO_HORTATION,				//�pk���ͷ���������
	Campaign_NO_PUNISH_HORTATION,					//�pk���ͷ�������
	Campaign_PUNISH_NO_HORTATION,					//�pk�ͷ�������
};


//--��ɫ��������-- by zhaoguoze 2011-01-13
enum RELIVE_TYPE
{
	RELIVE_TYPE_TOTOWN						= 0,	//--��ȫ����--
	RELIVE_TYPE_INSITU,								//--ԭ�ظ���--
	RELIVE_TYPE_FULLSTATUS,							//--��״̬����--
};

//--�������������--
enum GAME_OVER_DLG_TYPE
{
	GAME_OVER_DLG_TYPE_COMMON = 0,					//--��ͨ--
	GAME_OVER_DLG_TYPE_FAMILY_CHALLENGE,			//--������ս��--
	GAME_OVER_DLG_TYPE_GUO_CE,						//--����--
	GAME_OVER_DLG_TYPE_CANNOT_INSITU,				//--��ֹԭ�ظ���--
};


//�ٻ���ض���
enum SummonRange   //�ٻ���Χ
{
	SummonRange_Person = 0, //�ٻ�����
	SummonRange_Team,		//�ٻ�����
	SummonRange_Family,		//�ٻ�����
	SummonRange_Gang,		//�ٻ����
	SummonRange_State,		//�����ٻ�
	SummonRange_King,		//�����ٻ�����
	SummonRange_Brothers,	//����ٻ�
	SummonRange_World,		//����
};

enum SummonType						//�ͻ������ͱ��
{
	SummonType_Common = 0,			//��ͨ�ٻ�
	SummonType_Quest,				//�����ٻ�
	SummonType_UnderGround,			//�����ٻ�
	SummonType_Teammate,			//�����ٻ�
	SummonType_Border,				//�߾��ٻ�

	SummonType_Special = 100,			// �����ٻ���ʼλ 
	SummonType_Special_Escort,			//�����ھ��ٻ�
	SummonType_Special_GangFight,		//�����ս�ٻ�
	SummonType_Special_FamilyChallenge,	//������ս���ٻ�
	SummonType_Special_EscortRunning,	//�����ھַ�������
	SummonType_Special_StateWarAttack,	//��ս�������ٻ�
	SummonType_Special_StateWarDefence,	//��ս���ط��ٻ�
	SummonType_Special_StateWarDanger,	//��ս��Ԫ˧����Σ���ٻ�
	SummonType_Special_ServerShutDown,	//ͣ��֪ͨ
	SummonType_Special_FamilyJuYi,		//�����ٻ�
	SummonType_Special_FamilyBoss,		//����BOSS�ٻ�
	SummonType_Special_FamilyEscort,	//��������
	SummonType_Special_ApplyFamilyScene,//�������ׯ԰���ѣ���ʱ���嵹��ʱ
};

//--���͵������ͣ��سǾ����������--add by zhangjianli 2012-3-1
enum TransPropType
{
	TransProp_HuiCheng_Single = 0,			//--����سǾ�--
	TransProp_Huicheng_Colony,				//--Ⱥ��سǾ�--
	TransProp_ShunYi_Single,				//--����˲�ƾ��ᣨ���޵�ͼ�������--
	TransProp_ShunYi_Colony,				//--Ⱥ��˲�ƾ���--
	TransProp_ShunYi_Map,					//--����˲�ƾ������Ч�����ޱ����������
	TransProp_JiYi,							//--�������--
	TransProp_ShiKong,						//--ʱ��ͨ��--
};

//--�����ӳ����������--
struct SSkillDelayInfo
{
public:
	SSkillDelayInfo(){Init();}
	//--skill		������ID--
	//--target		��Ŀ��ID--
	//--prop		������ID--
	//--AttackPoint	���Ե㹥����λ��--
	//--TriggerTime	�����ܿ�ʼ�ͷŵ�ʱ�䣨���룩--
	//--DelayTime	��������ʽ�ӳ�ʱ�䣨���룩--
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
	SkillID				m_nSkillID;			//--����ID--
	PersonID			m_nTargetID;		//--Ŀ��ID--
	PropID				m_nPropID;			//--����ID--
	POINT				m_ptAttackPoint;	//--������λ��--
	TMV					m_nSkillTriggerTime;//--���ܿ�ʼʱ�䣨���룩--
	TMV					m_nSkillDelayTime;	//--�����ӳ�ʱ�䣨���룩--
};

////////////////////////////////////////////////////////////////////////////////////


enum MOVING_TYPE
{
	MOVING_TYPE_RUN 						=0,		//�ܲ�
	MOVING_TYPE_WALK,								//��·
	MOVING_TYPE_FORCE_WALK,							//ǿ����
	MOVING_TYPE_FORCE_RUN,							//ǿ����
};

enum CASTING_STOP_TYPE
{
	CASTING_STOP_TYPE_FINISH				= 0,	// ���ʩ����������Ȼ������
	CASTING_STOP_TYPE_IDLE,							// վ��ʹʩ��״̬��������ϣ�
	CASTING_STOP_TYPE_MOVE,							// �ƶ�ʹʩ��״̬��������ϣ�
};

//--������������--
const int	SINGING_SKILL_TYPE_COMMON		= 1 << 0;// ��ͨ����ӦActionStatus_Casting״̬������һ��ʰȡ�����������������ְҵ���ܶ�����
const int	SINGING_SKILL_TYPE_STEAL		= 1 << 1;// ͵ש����ӦStealStatus_Steal״̬����״̬��ʹ���������ܣ�����͵ש������Ĥ�ݶ�������������ȣ�
const int	SINGING_SKILL_TYPE_GETONCAR		= 1 << 2;// ��ս������ӦComplexStatus_GetOnCar״̬����״̬��ʹ���������ܣ�������ս��������


const int	ROLE_RAGE_NUM_MAX				= 1000;	//--��ɫ��ŭ��ֵ����--
const int	RAGE_ONCE_NUM_ADD				= 2;	//--ɱһ�������õ�ŭ��ֵ--

const int	PLAYER_AUTO_UP_LEVEL			= 50;	//--����Զ������ļ������ޣ�������������Ҫ�ֶ�ѡ��������--

const int	PLAYER_EXP_TOPLIMIT_TIMES		= 3;	//--�������ۻ�����ֵ�������뵱ǰ�����µ�����������ȣ�--

//////////////////////////////////////////////////////////////////////////
//����
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
	AI_CURRENT_ATTACKALL = 1,					//ȫ�幥��
	AI_CURRENT_ATTACK = 2,						//����
	AI_CURRENT_DEFEND = 3,						//����
	AI_CURRENT_ATTACKSELECT = 4,				//ѡ�񹥻�
	AI_CURRENT_REST	= 5,						//��Ϣ
	AI_CURRENT_STAY = 6,						//ͣ��
};

//�����
#define CAMPAIGN_COUNT 10

#define FAMILY_PASSENGER_NUM 6

//����Ⱥ����
#define GROUP_COUNT		5

//ʱ�䶨��
const UINT TIME_1Min   = 60;			//1����
const UINT TIME_2Min   = 120;			//2����
const UINT TIME_5Min   = 300;			//5����
const UINT TIME_10Min  = 600;			//10����
const UINT TIME_1Hour  = 3600;			//1Сʱ
const UINT TIME_24Hour = 86400;			//24Сʱ
const UINT TIME_48Hour = 172800;		//48Сʱ����ʱ��
const UINT TIME_3Day   = 259200;        //3��
const UINT TIME_7Day   = 604800;        //7��

//����ʱ��
const int CAR_VENTURE_MIN				= 30;
const int CAR_VENTURE_MAX				= 120;

const int CONMMON_CD_TIME				= 1200; //����cd��ʱ�䣨���룩


//����Ŀͻ����������λ��ƫ�� tile
const int POSITION_VERIFY				= 5;


//--NPC����ʱ�Ĵ���ʱ�䣨�ܵ�����ʱ�ĵ�һ�η�����׷������Һ�ĵ�һ�ι�����Ҫ�д���ʱ�䣩--
const int WANT_ATTACK_TIME				= 500;	//��������ʱ�䣨���룩

//--NPC׷��ʱ�Ĵ���ʱ�䣨����Ŀ��ʱ��Ҫ����һ���Ĵ���ʱ�䣩--
const int WANT_CHASE_TIME				= 300;	//׷������ʱ�䣨���룩

const TMV INVALID_WANT_TIME				= 0;	//��Ч�Ĵ���ʱ��ֵ

const int RADIUS_NPC_CREATE_POS_RANDOM	= 2;	//--NPCˢ�µ������뾶--

const int NPC_AUTO_MOVE_RANGE			= 3;	//--NPC�Զ��ƶ��ķ�Χ--

//--��ͨNPC�����׷����Χ��NPCˢ�µ���Ŀ��ľ��룩--
//--ע�����Ŀ����NPCˢ�µ�ľ�����ڴ�ֵ������Ϊͬ�������ͣ�NPC����׷�����������߼�Idle״̬��
//		������͵ľ���С�����ֵ��NPC���ᳬĿ�귽��׷ȥ���������������Ե�׷����ΧʱGoHome
const int CHASE_RANGE_MAX				= 50;


const int VALUE_ENLARGE_TIMES			= 1000;
const int PROP_CLASS_NUM				= 4;	//���߼���θ���
const int PROP_STAR_NUM					= 15;	//װ�����Ǹ���

const int ROLE_RECOVER_TIME_INTERVAL	= 10;	//--��ɫ�ָ��߼�ʱ�������룩-- add by zhaoguoze 2011-05-21

const int EFFECT_HP_HAD_LITTLE_LIMIT	= 30;	//--����Ч��(Event_Combat_Effect_HpHadLittle)�������ٷֱ�--

const int RADIUS_PLAYER_RELIVE_POS_RAND = 4;	//--��ҳ����������뾶--

const int EFFECT_ADD_PRACTISEGESTE_RADIX = 10000;//Ч��������������ѫ�Ļ��� add by zhangjianli 2012-7-30

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
// ID���ɹ��� �����ӿ�

#define ROLE_ID_WORLD		10000000000000000ULL			//World
#define ROLE_ID_SERVER		100000000000000ULL				//Server
#define ROLE_ID_TYPE		10000000000000ULL
#define ROLE_ID_TEMPLATE	10000000ULL
#define FELLOW_ID_HEAD		1000000LL
#define ROLE_ID_FAMILY_GANG	1000000							//FamilyID GangIDΪint��

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

//ʹ�ô���Key
inline int64 MakeUseCountKeys(int nTemplateID, int nType, int nTimeType)
{
	return nTemplateID * 10000000000 + nType * 10000 + nTimeType;
}

//////////////////////////////////////////////////////////////////////////
// ����ID

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

//����PID
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
// AuctionID���Ϸ���������
inline AuctionID MakeAuctionID(int64 nServerID, int64 nIndex)
{
	return (nServerID * 1000000000000000LL + nIndex);
}
// BuyID ��ID���Ϸ���������
inline BuyID MakeBuyID(int64 nServerID, int64 nIndex)
{
	return (nServerID * 1000000000000000LL + nIndex);
}
//TeamID�������̣�
inline int MakeTeamID(int nServerID,int nIndex)
{
	return (nServerID * 1000000 + nIndex);
}
//////////////////////////////////////////////////////////////////////////
////��ݵ�ID�����ã�������del by zhangjianli 2012-9-27
//inline int MakeGayID(int nServerID,int nIndex)
//{
//	return (nServerID * 1000000 + nIndex);
//}
//���������ýӿ� del by zhangjianli 2012-9-27
//inline ClearingID MakeClearingID(int64 nServerID, int64 nIndex)
//{
//	return (nServerID * 1000000000000000LL + nIndex);
//}

/*
//�
inline CampaignID MakeCampaignID(int64 nCampaignTemplate, int64 nIndex)
{
return (nCampaignTemplate * 1000000000000000ULL + nIndex);
}
*/
//����ʱID����
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
//	����ID ���ɹ���
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
	//����nIndex���16λ
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
#define		ZONETILEX_SIZE		20					//ÿ��Zone X�����tile����
#define		ZONETILEY_SIZE		20  	            //ÿ��Zone y�����tile����
#define		EXPLORER_IN_DIST	(ZONETILEX_SIZE + (ZONETILEX_SIZE / 2))

enum PLAYERJOB				//����ְҵ����
{
	PLAYERJOB_NOLIMIT	=-1 ,			//������
	PLAYERJOB_NONE		=0	,			//��ְҵ		
	PLAYERJOB_WUSHI			,			//��ʦ
	PLAYERJOB_SHUSHI		,			//��ʿ
	PLAYERJOB_SHESHOU		,			//����
	PLAYERJOB_DAOSHI		,			//��ʿ
	PLAYERJOB_YISHI			,			//ҩʦ
};

///////////////////////////////////////////////////////////////////////////////////////////
// Skill

//--SkillIDվλ��ͼ--
//-------------------
//	1  1  01  01
//	|  |  |   |
//	|  |  | Level
//	|  | Mode
//  | Ramify(����ְҵ��֧��ŭ�����ķ�)
// Class
//-------------------

const int SKILL_NUM_PLACE_CLASS		= 100000;	//--����ID����ϵ��ʶλ��վһλ
const int SKILL_NUM_PLACE_RAMIFY	= 10000;	//--����ID�з�֦��ʶλ��վһλ
const int SKILL_NUM_PLACE_MODE		= 100;		//--����ID������ʶλ��վ��λ
const int SKILL_NUM_PLACE_LEVEL		= 1;		//--����ID�м����ʶλ��վ��λ


//--���ܷ�֦λ��ʶ--
enum SKILL_NUM_RAMIFY_FLAG
{
	SKILL_NUM_RAMIFY_FLAG_NONE			= 0,		//--��--
	SKILL_NUM_RAMIFY_FLAG_1				= 1,		//--��һ��֦--
	SKILL_NUM_RAMIFY_FLAG_2				= 2,		//--�ڶ���֦--
	SKILL_NUM_RAMIFY_FLAG_RAGE			= 5,		//--ŭ�����ܱ�ʶ--
	SKILL_NUM_RAMIFY_FLAG_XINFA			= 6,		//--�ķ����ܱ�ʶ--
};

//--���ݼ���ID�ж��ǲ���ְҵ����--
inline BOOL G_CheckIsTreeSkillByID( SkillID nSkillID )
{
	return ( (nSkillID / SKILL_NUM_PLACE_CLASS <= 5) && (nSkillID / SKILL_NUM_PLACE_CLASS > 0) );
}

//--�ж��ǲ���ŭ������--change by zhangjianli 2011-11-08
inline BOOL G_IsRageSkill( SkillID nSkillID )
{
	//return ( (nSkillID % SKILL_NUM_PLACE_CLASS / SKILL_NUM_PLACE_RAMIFY) == SKILL_NUM_RAMIFY_FLAG_RAGE );
	int nClass = nSkillID / SKILL_NUM_PLACE_CLASS;
	int nRamify = nSkillID % SKILL_NUM_PLACE_CLASS / SKILL_NUM_PLACE_RAMIFY;
	return ( (nClass == 0) && (nRamify == SKILL_NUM_RAMIFY_FLAG_RAGE) );
}

//--�ж��ǲ����ķ�����--change by zhangjianli 2011-11-08
inline BOOL G_IsXinFaSkill( SkillID nSkillID )
{
	//return ( (nSkillID % SKILL_NUM_PLACE_CLASS / SKILL_NUM_PLACE_RAMIFY) == SKILL_NUM_RAMIFY_FLAG_XINFA );
	int nClass = nSkillID / SKILL_NUM_PLACE_CLASS;
	int nRamify = nSkillID % SKILL_NUM_PLACE_CLASS / SKILL_NUM_PLACE_RAMIFY;
	return ( (nClass == 0) && (nRamify == SKILL_NUM_RAMIFY_FLAG_XINFA) );
}

//--�õ����ܵ�Level--
inline int G_MakeLevelBySkillID(SkillID nSkillID)
{
	return nSkillID % SKILL_NUM_PLACE_MODE / SKILL_NUM_PLACE_LEVEL;
}

//--�õ�����ģ��,�����������ܵȼ�����Ϣ--
inline int G_MakeModeBySkillID(SkillID nSkillID)
{
	return (nSkillID / SKILL_NUM_PLACE_MODE) * SKILL_NUM_PLACE_MODE;
}

//--�õ����ܵ���ϵ--
inline int G_MakeClassBySkillID(SkillID nSkillID)
{
	return nSkillID / SKILL_NUM_PLACE_CLASS;
}

//--�õ����ܵķ�֦-- change by zhangjianli 2011-11-08
inline int G_MakeRamifyBySkillID(SkillID nSkillID)
{
	//int nRamify = nSkillID % SKILL_NUM_PLACE_CLASS / SKILL_NUM_PLACE_RAMIFY;
	//return (( nRamify == SKILL_NUM_RAMIFY_FLAG_RAGE || nRamify == SKILL_NUM_RAMIFY_FLAG_XINFA ) ? SKILL_NUM_RAMIFY_FLAG_NONE : nRamify);	//--�����֦λ��ŭ�����ķ���ʶ���򷵻��� -- add by zhaoguoze 2011-03-23
	
	// �����ְҵ���ܣ��ŷ��ط�֧�����Ǿͷ�����
	if ( G_CheckIsTreeSkillByID(nSkillID) )				
		return nSkillID % SKILL_NUM_PLACE_CLASS / SKILL_NUM_PLACE_RAMIFY;
	else
		return SKILL_NUM_RAMIFY_FLAG_NONE;
}

//--ȡSkillID���м���λ--
inline int G_MakeSkillNode(SkillID nSkillID)
{
	return nSkillID % SKILL_NUM_PLACE_RAMIFY / SKILL_NUM_PLACE_MODE;
}


//--����һ������ID--
//--nClass	����ϵ--
//--nRamify	����֦ enum SKILL_NUM_RAMIFY_FLAG--
//--nMode	�����--
//--nLevel	���ȼ�--
inline int G_MakeSkillID( int nClass, int nRamify, int nMode, int nLevel )
{
	return ( nClass * SKILL_NUM_PLACE_CLASS + nRamify * SKILL_NUM_PLACE_RAMIFY + nMode * SKILL_NUM_PLACE_MODE + nLevel * SKILL_NUM_PLACE_LEVEL );
}

//--����һ������ID�����ı�ID����ϵλ--
//--nSkillID��Ҫ�ı�ļ���ID--
//--nClass	����ϵ--
inline int G_MakeSkillIDByClass( SkillID nSkillID ,int nClass )
{
	return ( nClass * SKILL_NUM_PLACE_CLASS + nSkillID % SKILL_NUM_PLACE_CLASS );
}

//--����һ������ID�����ı�ID�ķ�֦λ--
//--nSkillID��Ҫ�ı�ļ���ID--
//--nRamify	����֦ enum SKILL_NUM_RAMIFY_FLAG--
inline int G_MakeSkillIDByRamify( SkillID nSkillID ,int nRamify )
{
	return ( nSkillID / SKILL_NUM_PLACE_CLASS * SKILL_NUM_PLACE_CLASS + nRamify * SKILL_NUM_PLACE_RAMIFY + nSkillID % SKILL_NUM_PLACE_RAMIFY );
}

//--����һ������ID�����ı�ID�����λ--
//--nSkillID��Ҫ�ı�ļ���ID--
//--nMode	�����--
inline int G_MakeSkillIDByMode( SkillID nSkillID ,int nMode )
{
	return ( nSkillID / SKILL_NUM_PLACE_RAMIFY * SKILL_NUM_PLACE_RAMIFY + nMode * SKILL_NUM_PLACE_MODE + nSkillID % SKILL_NUM_PLACE_MODE );
}

//--����һ������ID�����ı�ID�ĵȼ�λ--
//--nSkillID��Ҫ�ı�ļ���ID--
//--nLevel	���ȼ�--
inline int G_MakeSkillIDByLevel( SkillID nSkillID ,int nLevel )
{
	return ( nSkillID / SKILL_NUM_PLACE_MODE * SKILL_NUM_PLACE_MODE + nLevel * SKILL_NUM_PLACE_LEVEL + nSkillID % SKILL_NUM_PLACE_LEVEL );
}

const int SKILL_EFFECT_MAX			= 10;
const int SKILL_EFFECT_INTIME		= 5;//--�輰ʱ�����Effect��վEffect����ĺ�5��--
const int SKILL_BUFF_MAX			= 5;
const int SKILL_TARGET_MAX          = 5;

const int SKILL_LEVEL_TREE_MAX		= 14;										//--ְҵ�������ȼ�--change by zhangjianli 2011-12-08
const int SKILL_LEVEL_XINFA_MAX		= 71;										//--�ľ��������ȼ�--add by zhangjianli 2011-12-08
const int PRESKILL_LEVEL1			= 5;
const int PRESKILL_LEVEL2			= 6;

const int SKILLTREE_COUNT_MAX		= 5;										//--�����������--
const int SKILLMODE_COUNT_MAX		= 50;										//--һ����ϵ�ļ����������--
//#define SKILLNOTE_COUNT_MAX			(SKILLMODE_COUNT_MAX * SKILL_LEVEL_TREE_MAX)//--Node�����ֵ�漼������ͼ��ܼ�������ֵ�ı䣬NodeMax = ModeMax * SKILL_MAX_LEVEL--  ��ʱû�ã�ע�͵� change by zhangjianli 2011-12-08

const int ATTACK_TARGER_NUM_MAX		= 100;	//--Ⱥ���ɹ������������--

//////////////////////////////////////////////////////////////////////////
//
//����ȱ��
enum Mission_Status
{
	Mission_Status_Null = 0,		//δ��ʼδ����
	Mission_Status_Regist,			//������
	Mission_Status_WaitForStart,	//��������δ��ʼ
	Mission_Status_Doing,			//������
	Mission_Status_Over,			//�ѽ���
};

//�����������
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
//�µ�EffectID��������	By David 2009-2-16
#define EFFECT_VALUE					1000000ULL							//Ч��������ֵ
#define EFFECT_OBJ_TYPE					1000000000ULL						//Ч����ִ��������	 ��Ӧֵ��enum ENUM_EFFECT_OBJ_TYPE
#define EFFECT_RANDOM					10000000000ULL						//Ч���ĸ���
#define	EFFECT_KEY						10000000000000ULL					//Ч��Key
#define EFFECT_FLAG						1000000000000000000ULL				//+/-���		 0:+	1:-
#define EFFECT_ACTIVE_FLAG				10000000000000000000ULL				//�Ƿ񼤻�ı�־ 0:���� 1:�Ǽ���

//--OnEffect����ִ�з���ֵ--
enum EffectReturn
{
	Effect_False	= 0,	//--����--
	Effect_Succeed,			//--Ч��ִ�гɹ�--
	Effect_RandFail,		//--���ʧ��--
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

//--��ȡЧ��ִ��������--
//--���أ�Ч��ִ���� enum ENUM_EFFECT_OBJ_TYPE--
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
// Ч����Ķ���
// 10000����Ϊ�Ա�������ֵ�ĸı� ( ���ö���Ϊĸ���� )
// 10000����Ϊ���Լ�����ֵ�ĸı� ( ���ö���Ϊʹ���� )
#define EFFECT_LIMIT		10000

// �������
const int EQUIP_EFFECT_MAX		= 15;	//���ߵ�Ч��
const int ZHANHUN_EFFECT_MAX	= 5;	//ս����Ч��
const int LIANCHENG_EFFECT_MAX	= 5;	//���Ǿ�Ч��
const int ACTIVE_EFFECT_MAX		= 5;	//����Ч���ĸ���
const int BIND_EFFECT_MAX		= 1;	//�ذ�Ч������
//const int PROP_SKILL_MAX		= 5;	//
const int EQUIP_POS_MAX			= 10;	//��������װ��λ������

// �������
#define QUEST_TYPE_MAX  6				// ��ѡ����Ʒ������Ŀ���������ֵ
#define QUEST_TYPE_MAX_PROP 10		//���߽��������ֵ
//������ص�
inline int GetBagByUIPost(UIPos post){return post/1000;}
inline int GetIndexInBagByUIPost(UIPos post){return post%1000;}
inline int GetUIPost(int CBag,int Post){return (CBag*1000 + Post);}

//��̯���
const int STALL_PROP_NUM = 48;		//̯λ��������
const int STALL_NAME_LEN = 64;		//̯λ���Ƴ���
const int STALL_NOTE_LEN = 128;		//̯λ��������


//��������UI����
enum Prop_UIPos_Type
{
	Prop_UIPos_Null = 0,
	Prop_UIPos_Bag  = 1,			//����
	Prop_UIPos_Equip= 2,			//װ����
	Prop_UIPos_Compose = 3,			//����ϳ�
	Prop_UIPos_Exchange = 4,		//����
	Prop_UIPos_Stall = 5,			//��̯
	Prop_UIPos_Mail = 6,			//�ʼ�
	Prop_UIPos_AUCTION = 7,			//����
	Prop_UIPos_FamilyBoss = 8,		//����boss
};

const int NPC_FALL_MONEY = 10;	//NPC�����Ǯ����
const int64 WORDCHAT      = 50000;   //�����������
const int64 COLORWORDCHAT = 250000;  //�����������


//��������
enum Currency_Type
{
	Currency_Gold = 0,			//����
	Currency_GoldBind,			//�󶨽�
	Currency_Silver,			//����
	Currency_SilverBind,		//����
	Currency_StashGold,			//���ý���
	Currency_StashGoldBind,		//�����ý���
	Currency_StashSilver,		//��������(�����������幤�ʻ���)
	Currency_StashSilverBind,	//����������(��������ÿ����������)
	Currency_Prop,				//���ﻻ��
	Currency_GongXun,			//��ѫ����-������ѫ
	Currency_HeroIsland,		//�㽫̨����
};

enum CostType
{
	COST_INVALID = -1,
	COST_PLAYERBUSINESS = 0,                //����
	COST_NPCBUSINESS,						//NPC����
	COST_SALE,								//����
	COST_MAIL,								//�ʼ�
	COST_REFORM,							//װ������
	COST_SYSTEM,							//ϵͳ����
	COST_AUCTION,							//����
	COST_BUY,								//��
	COST_BANK,								//Ʊ��
	COST_STALL,								//��̯
	COST_ORDINARYDRIVER,                    //��ͨ����
	COST_CROSS_BORDER_TRANSMISSION,         //�������
	COST_RELIVE_INSITU,                     //ԭ�ظ���
	COST_RELIVE_FULLSTATUS,                 //��״̬����
	COST_SKILL_LEAN,                        //ѧϰ����
	COST_CHAT,                              //����/��������
	COST_FAMILY,                            //����
	COST_MARRIAGE,                          //���
	COST_USEPROP,                           //ʹ�õ���
	COST_SUMMON,                            //�ٻ�
	COST_Dragon,                            //���Ҷһ�
	COST_HEROTOP,                           //����Ӣ�����а�
	COST_WAGE,                              //����
	COST_SIGNUP,                           //����
	COST_TREATDRINK,						//����ʳ����ͺȾ�
	COST_COLORCHAT,							//���к���
	COST_WORLDCHAT,							//���纰��
	COST_EQUIPCOMPOSE,						//����ϳ�
	COST_WARCARREPAIR,						//ս������
	COST_WARCARBUILD,						//ս������
	COST_EQUIP_REQAIR,						//װ������
	COST_CHANGE_STATE,						//����
	COST_MOUNTSTOSTRENGTHEN,				//����ǿ��
	COST_PETSKILL_METAMORPHOSIS,			//���＼�ܻû�
	COST_PETUPSTAR,							//��������
	COST_PET_REBIRTH,						//��������
};

enum CostInOrOut
{
	COST_IN = 0,				//���
	COST_OUT,					//ʹ��
};

enum MonitorItem_Type
{
	eMonitorItem_Invalid = -1,
	eMonitorItem_Prop,				// ����
	eMonitorItem_End,
};

enum MonitorItem_OprType
{
	eMonitorItem_OperInvalid = -1,
	eMonitorItem_OperAdd,	//���
	eMonitorItem_OperSub,	//��
	eMonitorItem_OperClear,	//��
	eMonitorItem_OperEnd,
};
//�����
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

//�Ʋ�����
const int PROTECT_EQUIP         = 1;	   //�Ѱ���ɫװ������ɫװ���ͽ�ɫ
const int PROTECT_STORAGE       = 1<<1;    //�ڶ������ֿ�
const int PROTECT_BANK          = 1<<2;	   //Ʊ���˻�
const int PROTECT_GIFT          = 1<<3;    //Ǯׯ�ϰ崦��ȡ��Ʒ
const int PROTECT_MAILANDSALE   = 1<<4;	   //���ס��ʼ�������
const int PROTECT_PET           = 1<<5;    //���ޱ���
const int PROTECT_FAMILYANDGANG = 1<<6;	   //��ɢ�����ת���峤����ɢ����ת�ð���
const int PROTECT_MEMBER        = 1<<7;    //�����޳���Ա������޳�����

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
#define 		COLOR_BLACK			L"00";	//��
#define 		COLOR_CARMINE		L"01"	//���ɫ
#define 		COLOR_GREEN			L"02"	//��ɫ
#define 		COLOR_OLIVE			L"03"	//���ɫ
#define 		COLOR_NAVY			L"04"	//����ɫ
#define 		COLOR_PURPLE		L"05"	//��
#define 		COLOR_CYAN			L"06"	//��
#define 		COLOR_GRAY			L"07"	//��
#define 		COLOR_ARGENTINE		L"08"	//��
#define 		COLOR_RED			L"09"	//��
#define 		COLOR_POTENTIAL		L"10"	//ǳ��
#define 		COLOR_YELLOW		L"11"	//��
#define 		COLOR_BLUE			L"12"	//��
#define 		COLOR_MAUVE			L"13"	//�Ϻ�
#define 		COLOR_AZURY			L"14"	//ǳ��
#define 		COLOR_WHITE			L"15"	//��
#define 		COLOR_SKY_BLUE		L"16"	//����
#define 		COLOR_SKY_YELLOW	L"17"	//����
#define 		COLOR_PEA_GREEN		L"18"	//����

//////////////////////////////////////////////////////////////////////////
// Inquirer
//////////////////////////////////////////////////////////////////////////

//NPC ����ɫ
#define		NPC_WHITE	2
#define		NPC_GREEN	3
#define		NPC_BLUE	4
#define		NPC_ZI		5
#define		NPC_GOLD	6

//����ֱ�Ӵ򿪽���
enum Dialog_Type
{
	Dialog_Invalid		= 0,			//��Ч����
	Dialog_Mail,						//�ʼ�
	Dialog_Auction,						//������
	Dialog_Stall,						//��̯
	Dialog_PropMake,					//װ������
	Dialog_PropUpgrade,					//װ������
	Dialog_PropCompose,					//װ���ϳ�
	Dialog_Clearing,					//Ʊ�ݽ���
	Dialog_Business,					//��������
	Dialog_ChangeCountry,		        // ������
	Dialog_CreateFamily,                //��������
	Dialog_EnterFamilyScene,            //�������ׯ԰
	Dialog_BuildFamilyScene,            //��������ׯ԰
	Dialog_FamilyTankMager,             //�������ս��
	Dialog_QueryFamilyCredit,           //�鿴���幱�׶�
	Dialog_SetFamilyMoney,              //���׼����ʽ�
	Dialog_PublicFamilyQuest,           //�������幫��
	Dialog_SummonFamilyBoss,            //�ٻ�����Boss
	Dialog_UpdateFamilyLevel,           //��������
	Dialog_UpdateFamilyReadMe,          //������������
	Dialog_LearnFamilySkill,            //ѧϰ���弼��
	Dialog_StudyFamilySkill,            //�о����弼��
	Dialog_GetFamilyTank,               //���ü���ս��
	Dialog_FamilyTankPermission,        // ���ü���ս��ʹ��Ȩ��
	Dialog_CreateFamilyTank,            //�������ս��
	Dialog_CreateGang,                  //�������
	Dialog_EnterGangScene,              //������ׯ԰
	Dialog_BuildGangScene,              //������ׯ԰
	Dialog_GangTankMager,               //������ս��
	Dialog_QueryGangCredit,             //�쿴��ṱ�׶�
	Dialog_SetGangMoney,                //���װ���ʽ�
	Dialog_PublicGangQuest,             //������ṫ��
	Dialog_SummonGangBoss,              //�ٻ����Boss
	Dialog_UpdateGangLevel,             //�������
	Dialog_UpdateGangReadMe,            //�����������
	Dialog_LearnGangSkill,              //ѧϰ��Ἴ��
	Dialog_StudyGangSkill,              //�о���Ἴ��
	Dialog_GetGangTank,                 //���ð��ս��
	Dialog_GangTankPermission,          //���ð��ս��ʹ��Ȩ��
	Dialog_CreateGangTank,              //������ս��
	Dialog_Warehouse,					//�򿪲ֿ����
	Dialog_Wikipedia,                   //�򿪰ٿƽ��� ���� ƴ�� nText (xxxx)
	Dialog_FamilyBuilding,				//�򿪼��彨���б�
	Dialog_Bank,					    //��Ʊ�ţ����У�����
	Dialog_LookingForFamily,			//����������
	Dialog_AppointStatePower,			//������ҹ�ְ
	//Dialog_DiceCommon,				//������ 
	Dialog_FamilyWage1,                 //��Ա�������
	Dialog_FamilyWage2,                 //�峤���乤��
	Dialog_FamilyShop,                  //�����̵�
	Dialog_WarCar_Bulid,				//ս������
	Dialog_JieBai_Notice,				//��ݹ���Ԥ��
	Dialog_Shengshui_Bang,				//��ʥˮ���а�
	Dialog_Quest_Track,					//����׷�ٽ���
	Dialog_Sworn,						//���
	Dialog_SwornEnter,					//��ݳƺ�����
	Dialog_AcceptPropQuest,				//��Ʒ�������
        Dialog_Buy,                         //���н���
	Dialog_DragonConvertSilver,			//���Ҷһ�����
	Dialog_ChangeState,					//����
};

enum INQUIRER_TYPE
{
	INQUIRER_TYPE_INVALID = -1,						// ��Ч������
	INQUIRER_TYPE_ISSUE_QUEST = 0,					// ��������
	INQUIRER_TYPE_COMPLETE_QUEST,					// �������
	INQUIRER_TYPE_COMPLETE_QUEST_LUA,   			// �ű��������
	INQUIRER_TYPE_NOCOMPLETE_QUEST,					// ���������
	INQUIRER_TYPE_FUNC,								// ���ܶԻ�
	INQUIRER_TYPE_CHAT,								// ���ĶԻ�
	INQUIRER_TYPE_EVENT,							// �����¼��Ի�
	INQUIRER_TYPE_MERCHANT,							// ��Ʒ����
	INQUIRER_TYPE_CHANGECOUNTRY,					// ������
	INQUIRER_TYPE_MAKE_PROP,						// װ������
	INQUIRER_TYPE_ENHANCE_PROP,						// װ������
	INQUIRER_TYPE_COMPOSE_PROP,						// װ���ϳ�
	INQUIRER_TYPE_EPLISTLE,							// ����
	INQUIRER_TYPE_ENTERN_FAMILY_SCENE,				// �������ׯ԰
	INQUIRER_TYPE_BUILD_FAMILY,						// ��������
	INQUIRER_TYPE_BUILD_FAMILY_SCENE,				// ��������ׯ԰
	INQUIRER_TYPE_FAMILY_TANK_MAGER,				// �������ս��
	INQUIRER_TYPE_QUERY_FAMILY_CREDIT,				// ��ѯ���幱�׶�
	INQUIRER_TYPE_SET_FAMILY_MONEY,					// ���׼����ʽ�
	INQUIRER_TYPE_SET_FAMILY_MONEY_5,				// 5��
	INQUIRER_TYPE_SET_FAMILY_MONEY_10,				// 10��
	INQUIRER_TYPE_PUBLIC_FAMILY_QUEST,				// ������������
	INQUIRER_TYPE_SUMMON_FAMILY_BOSS,				// �ٻ�����boss
	INQUIRER_TYPE_UPDATE_FAMILY,					// ��������
	INQUIRER_TYPE_UPDATE_FAMILY_README,				// ������������
	INQUIRER_TYPE_LEARN_FAMILY_SKILL,				// ѧϰ���弼��
	INQUIRER_TYPE_STUDY_FAMILY_SKILL,				// �о����弼��
	INQUIRER_TYPE_FAMILY_TANK_GET,      			//���ü���ս��
	INQUIRER_TYPE_FAMILY_TANK_PERMISSION,			//���ü���ս��ʹ��Ȩ��
	INQUIRER_TYPE_FAMILY_TANK_CREATE,   			//�������ս��
	INQUIRER_TYPE_TRANS,							//����
	INQUIRER_TYPE_SKILLLOG,             			//����ѡ��

	//2010-6-3 by ma
	INQUIRER_TYPE_ISSUE_CHILD_DIALOG,				//��������ǰ�ӶԻ�
	INQUIRER_TYPE_COMPLETE_CHILD_DIALOG,			//�������ǰ�ӶԻ�

	//�������� INQUIRER_TYPE
	INQUIRER_TYPE_CHOISE_JOB_WUSHU,     			//����ϵ
	INQUIRER_TYPE_CHOISE_JOB_FASHU,     			//����ϵ
	INQUIRER_TYPE_CHOISE_JOB_SHESHU,    			//����ϵ
	INQUIRER_TYPE_CHOISE_JOB_YAOSHU,    			//����ϵ
	INQUIRER_TYPE_CHOISE_JOB_XIANSHU,   			//����ϵ

	INQUIRER_TYPE_WISEMAM,							//���ߴ���
	INQUIRER_TYPE_COMPETITION,						//�����
	INQUIRER_TYPE_STALL,							//��̯
	INQUIRER_TYPE_MAIL,								//�ʼ�
	INQUIRER_TYPE_BUILD_GANG,						//�������,
	INQUIRER_TYPE_AUCTION,							//����
	INQUIRER_TYPE_LOOK_PRISON_TIME,                 //����ʱ��
	INQUIRER_TYPE_LEARN_SELECT,						//ѧϰ�ɼ�
	INQUIRER_TYPE_LEARN_MINING,						//ѧϰ�ɿ�
	INQUIRER_TYPE_LEARN_BREED,						//ѧϰ��ֳ
	INQUIRER_TYPE_LEARN_CUT,						//ѧϰ��ľ
	INQUIRER_TYPE_LEARN_ELEMENTS,					//ѧϰԪ������
	INQUIRER_TYPE_LEARN_FUN,						//����
	INQUIRER_TYPE_LEARN_HUNT,						//����
	INQUIRER_TYPE_LEARN_PRACTICE,					//����
	INQUIRER_TYPE_LEARN_FISH,						//����
	INQUIRER_TYPE_TRANSREEL,						//���;���
	INQUIRER_TYPE_CAR_INFOR,                        //�ڳ���Ϣ
	INQUIRER_TYPE_GET_FAMILY_VALUE,					//��ȡ���幱�׶�
	INQUIRER_TYPE_GET_STATE_NUMBER,					//��ȡ������������
	INQUIRER_TYPE_GET_GANG_VALUE,					//��ȡ��ṱ�׶�
	INQUIRER_TYPE_GET_STATE_POWER,					//��ѯ����ͳ����
	INQUIRER_TYPE_GET_PLAYER_DOUBLETIME,			//��ѯ��ǰʣ��˫��ʱ��
	INQUIRER_TYPE_Middle_DIALOG,					//����м�Ի�
	INQUIRER_TYPE_NocompleteChild_DIALOG,			//δ�������ʱ�ӶԻ�
	INQUIRER_TYPE_Middle_DIALOG_Main,				//�м�Ի����Ի�


	INQUIRER_TYPE_QUEST_COMMIT,						//�ύ�����ӶԻ�		//add by lfy 2012.9.1
	INQUIRER_TYPE_QUEST_ACCEPT,						//���������ӶԻ�
	INQUIRER_TYPE_OPENDIALOG,						//�򿪽���			

	//�����ı�
	INQUIRER_TYPE_QUEST_MAIN_INQUIRER=200,			//������
	INQUIRER_TYPE_QUEST_CHILD_INQUIRER,				//������
	INQUIRER_TYPE_CUSTOM_INQUIRER,					//�Զ����ı�����
	INQUIRER_TYPE_LEVEL_LIMIT,						//����ȼ�δ��
	INQUIRER_TYPE_CONTINUEQUESTION,					//��������

	INQUIRER_TYPE_CAMPAIGNQUEST_ISSUE,				//����񷢲�
	INQUIRER_TYPE_CAMPAIGNQUEST_COMPLETED,			//��������
	INQUIRER_TYPE_ACTIVITY_NPCTALK,					//�����Ի�����
	//�򿪴���
	INQUIRER_TYPE_OPEN_DIALOG=210,					//ͳһ�Ĵ򿪴���

	//������
	INQUIRER_TYPE_BORDER_DIALOG = 230,					//�߾�������
	INQUIRER_TYPE_BORDER_CHILD,						//�߾��������ӶԻ�
	INQUIRER_TYPE_BORDER_CARCHILD,					//�߾�������ս���ӶԻ�

	INQUIRER_TYPE_GONGXUN_EXP=1000,					//��ѫ������

};
/**************************************************************************
**							����
***************************************************************************/
enum QST_TYPE
{
	QST_TYPE_INVALID  =0,
	QST_TYPE_QUEST,					//�������
	QST_TYPE_COMPETITION,			//���������
};
#define  QUESTION_STAR_NUM         3     //�̶�����������
#define  QUESTION_STAR_MAX         5     //�������������
#define  QUESTION_STAR_PRIZE       2     //��������������
#define  QUESTION_ACTIVE_SEC	   5    //��Чʱ��



#define  QUESTION_BEFORE_TIME      30    //������ʼǰ�ȴ�ʱ��
#define  QUESTION_ASK_TIME_SEC     15    //����ʱ��
#define  QUESTION_READ_TIME_SEC    10    //����ʱ��

#define  QUESTION_ASK_TIME_WAIT    5     //�𰸹����Դ��ˢ��ʱ��
#define  QUESTIONTOP 20					 //����
#define  QUESTION_TOP_ADD			1
#define  QUESTION_TOP_POINT			2
#define  QUESTION_TOP_SORT			3
#define  QUESTION_TOP_SEND			4

//////////////////////////////////////////////////////////////////////////
// State Define
//////////////////////////////////////////////////////////////////////////
#define STATEID_PROPUPDATEQUALITY_COUNT  5		//��������Ʒ��ʱ,ʹ�õĹ���ID�����Դ�1-7�ĳ�1-5. by zhupf 2011.1.28
enum STATEID_DEFINE
{
	STATEID_ZHONG	= 0,		//����
	STATEID_SHU,				//¥��
	STATEID_HAN,				//��
	STATEID_TANG,				//����
	STATEID_JIN,				//��
	STATEID_ZHOU,				//����
	STATE_COUNT_MAX,
};

//-----------------------------------------------------------------------------------
#define STATE_COUNT_MAX				5			//���������С
#define STATE_NAME_MAX_LEN			64

//////////////////////////////////////////////////////////////////////////
// Scene Define
//////////////////////////////////////////////////////////////////////////
enum Scene_TemplateID
{
	Scene_DaMingFu		= 1201,				//������
	Scene_YeYunDu		= 1202,				//Ұ�ƶ�
	Scene_CuiPingShan	= 1203,				//����ɽ
	Scene_ChiSongLin	= 1204,				//������
	Scene_LongHuShan	= 1205,				//����ɽ
	Scene_CuiPingMiLin	= 1206,				//��������
	Scene_FamilyScene	= 2201,				//�����ͼ
};

//////////////////////////////////////////////////////////////////////////
//AIGroup //  [4/13/2010] ��aigroup������Ӫ���ж�����Ҫ�ǿɷ񹥻��ͶԻ����ж���
//////////////////////////////////////////////////////////////////////////
enum AIGroupType
{
	AIGroup_Type_State_Friend			= 1,		//�������Ѻ�NPC,�ɶԻ�
	AIGroup_Type_Team_Friend			= 2,		//�������Ѻ�NPC
	AIGroup_Type_Family_Friend			= 3,		//�������Ѻ�NPC
	AIGroup_Type_Gang_Friend			= 4,		//������Ѻ�NPC
	AIGroup_Type_All_Friend				= 5,		//���������Ѻã��ɶԻ�
	AIGroup_Type_Master_Friend			= 6,		//�����˻��ٻ����Ѻ�
	AIGroup_Type_Function_NPC			= 7,        //����npc�����ܶԻ�
	AIGroup_Type_UState_Friend			= 8,		//�������˹��Ѻ��Ѻ�NPC
	AIGroup_Type_UFunction_NPC			= 9,		//����npc�����ܶԻ�(ֻ���˹��ͱ����Ѻ�)
	AIGroup_Type_All_Friend_StateTalk	= 10,		//ֻ�뱾���Ի������������Ѻ�
	AIGroup_Type_All_Friend_UStateTalk	= 11,		//ֻ�뱾�����˹��Ի������������Ѻ�
	AIGroup_Type_All_Friend_UnTalk		= 12,		//���������Ѻã����ɶԻ�
	AIGroup_Type_State_Friend_UnTalk	= 13,		//�������Ѻ�NPC,���ɶԻ�
	AIGroup_Type_Monster				= 1000,		//����
	AIGroup_Type_Player					= 10000,	//���
};


//////////////////////////////////////////////////////////////////////////
//	����ϵFlag    �ѷ��� 
//////////////////////////////////////////////////////////////////////////
enum RELATION_FLAG_BIT
{
	RELATION_FLAG_BIT_SELF		= (1<<0),			//�Լ�
	RELATION_FLAG_BIT_FRIEND	= (1<<1),			//����
	RELATION_FLAG_BIT_SPOUSE	= (1<<2),			//��ż
	RELATION_FLAG_BIT_ENEMY		= (1<<3),			//����
	RELATION_FLAG_BIT_PARTY		= (1<<4),			//����
	RELATION_FLAG_BIT_MASTER	= (1<<5),			//ʦ��
	RELATION_FLAG_BIT_PRENTICE	= (1<<6),			//ͽ��
	RELATION_FLAG_BIT_PET		= (1<<7),			//����

	RELATION_FLAG_BIT_KIN		= (1<<8),			//����
	RELATION_FLAG_BIT_FACTION	= (1<<9),			//����
	RELATION_FLAG_BIT_STATE		= (1<<10),			//����
	RELATION_FLAG_BIT_FOREIGN	= (1<<11),			//���


	RELATION_FLAG_BIT_HOSTILE	= (1<<20),			//�ж�

};

//////////////////////////////////////////////////////////////////////////
// ����ָ��
//////////////////////////////////////////////////////////////////////////

enum OfflineCmdType
{
	//���˹�ϵ���
	OFFLINE_CMD_NULL = 0,
	OFFLINE_CMD_PRIVATE_DELETE_FRIENDLEVEL,		//����ɾ������  ����֪ͨ���Ѽ��� 
	OFFLINE_CMD_DELETEROLE_PRIVATE_FRIENDLEVEL,	//ɾ����ɫ      ����֪ͨ���Ѽ���
	
	//�������
	OFFLINE_CMD_FAMILY_DISMISS,				//��ɢ����
	OFFLINE_CMD_FAMILY_AUTO_DISMISS,		//�����Զ���ɢ
	OFFLINE_CMD_FAMILY_POWER_APPOINT,		//����
	OFFLINE_CMD_FAMILY_POWER_FIRE,			//���
	OFFLINE_CMD_FAMILY_BEFIREOUT,
	OFFLINE_CMD_FAMILY_PAYOFF,				//������

	//������
	OFFLINE_CMD_GANG_POWER_APPOINT,
	OFFLINE_CMD_GANG_POWER_FIRE,
	OFFLINE_CMD_GANG_DISMISS,				//��ᱻ��ɢ
	OFFLINE_CMD_GANG_REMOVEFAMILY,			//��������

	//�������
	OFFLINE_CMD_STATE_POWER_APPOINT,
	OFFLINE_CMD_STATE_POWER_FIRE,
	OFFLINE_CMD_KINGDOWN_AS_RULE,			//ͳ������Ϊ0������̨

};

#define INT64_PARAM_COUNT	3
#define INT_PARAM_COUNT		3

//////////////////////////////////////////////////////////////////////////
// ����Ƶ��
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
// ����������������
//////////////////////////////////////////////////////////////////////////
enum SKILL_WEAPEN_RESTRICT
{
	SKILL_WEAPEN_RESTRICT_SWORD			= (1<<0),		//��	//˫��
	SKILL_WEAPEN_RESTRICT_AX			= (1<<1),		//��	//����
	SKILL_WEAPEN_RESTRICT_BOWN			= (1<<2),		//��	//��
	SKILL_WEAPEN_RESTRICT_CROSS			= (1<<3),		//��	//����
	SKILL_WEAPEN_RESTRICT_FUCHEN		= (1<<4),		//����	//˫��
	SKILL_WEAPEN_RESTRICT_MAGIC			= (1<<5),		//����
	SKILL_WEAPEN_RESTRICT_SHIELD		= (1<<6),		//����
	SKILL_WEAPEN_RESTRICT_ARROW			= (1<<7),		//��
	SKILL_WEAPEN_RESTRICT_CHARM			= (1<<8),		//����
	SKILL_WEAPEN_RESTRICT_SWORD_DOUBLE	= (1<<9),		//˫�ֵ�
	SKILL_WEAPEN_RESTRICT_HAMMER_DOUBLE	=(1<<10),		//˫�ִ�
	SKILL_WEAPEN_RESTRICT_MAGIC_STAFF	= (1<<11),		//����
	SKILL_WEAPEN_RESTRICT_MAGIC_ORB		= (1<<12),		//����
	SKILL_WEAPEN_RESTRICT_FAN			= (1<<13),		//��
	SKILL_WEAPEN_RESTRICT_RUYI			= (1<<14),		//����
	SKILL_WEAPEN_RESTRICT_AX_DOUBLE		= (1<<15),		//˫�ָ�
	SKILL_WEAPEN_RESTRICT_JI_DOUBLE		= (1<<16),		//˫���
	SKILL_WEAPEN_RESTRICT_GLOVE			= (1<<17),		//��������
	SKILL_WEAPEN_RESTRICT_FISH			= (1<<18),		//���

};

//////////////////////////////////////////////////////////////////////////
// Lua_Type
//////////////////////////////////////////////////////////////////////////
enum
{
	Lua_Type_NPC	 = 0,			//NPC
	Lua_Type_Scene,					//����
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
	Drag_Type_Template	= 3,	//����ģ��
	Drag_Type_Shortcut	= 4,	//�����
	Drag_Type_Pet		= 5,			//����
	Drag_Type_Face		= 6,		//ͼƬ
};

//////////////////////////////////////////////////////////////////////////
//	Prop
//////////////////////////////////////////////////////////////////////////
enum Prop_Quality
{
	Prop_Quality_White = 0,	//Ʒ�ʶ�Ӧ����   ChenXY   �����ע ����ʱ�� ��ø�������  2011/6/21
	Prop_Quality_Green = 1,			  //�� 
	Prop_Quality_Blue,				  //��
	Prop_Quality_Purple,			  // ��			// ö����������������,��Ʒ���Ѿ���Ӧ  by zlm 2011.9.5
	Prop_Quality_Gold,				  //��
	Prop_Quality_PerfectGold,		  //������
	Prop_Quality_LegendGold,		  //��˵��
};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Target
//////////////////////////////////////////////////////////////////////////
enum Target_Group
{
	Target_Hostile,				// �ж�Ŀ��
	Target_Friendly,			// �ѷ�Ŀ��
	Target_State,				// �����ѷ�
	Target_Faction,				// ����
	Target_Kin,					// ����
	Target_Party,				// ����

	Target_Couple,				// ����
	Target_Master,				// ʦ��
	Target_Prentice,			// ͽ��

	Target_Pet,					// ����
	Target_Self,				// �Լ�
	Target_ExecptSelf,			// ���Լ��ѷ�

	Target_All,					// ȫ��
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
	Trigger_Type_Immediate	= 0,	//��������
	Trigger_Type_Use,				//ʹ�ô���
	Trigger_Type_Equip,				//װ������
	Trigger_Type_Event,				//�¼�����
};



const UINT	BagSlot_Size			=	10;		// ��װ����������
const UINT  EquipBag_Size			=	300;	// װ��������λ����
const UINT  DefaultBag_Size			=	48;		// Ĭ�ϱ����Ĵ�С
const UINT  DefaultBank_Size 		=	48;		//��ʼ���д�С
const UINT  LionBag_Size 			=	2;		//��ʼ��ʨ������С
const UINT  CarBag_Size 			=	3;		//��ʼ�ڳ����߱�����С
const UINT 	DeityBoxBag_Size 		=	20;		//��ʼ�����ϻ������С
const UINT  SkyBoxBag_Size 			=	20;		//��ʼ�����ϻ������С
const UINT  EquipReformBag_Size 	=	4;		//��ʼ��װ�����챳����С
const UINT  RidPetBag_Size 			=	5;		//���װ��������С
const UINT  EquipBagTianHun_Size	=	48;		// ��걳���Ĵ�С
const UINT  EquipBagDiHun_Size		=	48;		// �ػ걳���Ĵ�С
const UINT  FellowEvoBag_Size 		=	4;		//����ǿ�����汳����С
const UINT	FellowEvolutionFullStar_Size = 20;		// ����ǿ�������ǵ��Ǽ���(dxt 2012/3/17)
enum Bag_UI_Index
{
	Bag_InvalidIndex	= -1,
	EquipBag_Index		=0,		// װ����������   //Ĭ��Ϊ���� �� 
	DefaultBag_Index,			// Ĭ�ϱ���������

	ExtBag1_Index,				// ��չ����1
	ExtBag2_Index,
	ExtBag3_Index,
	ExtBag4_Index,
	ExtBag5_Index,
	ExtBag6_Index,

	Stash_Index			=10,	// ���вֿ�
	StashExt1_Index,			// ���вֿ���չ����1
	StashExt2_Index,			//
	StashExt3_Index,
	StashExt4_Index,
	StashExt5_Index,
	StashExt6_Index,

	KinStash_Index,				// ����ֿ�
	KinStashExt1_Index,			// ����ֿ���չ����1
	KinStashExt2_Index,
	KinStashExt3_Index,
	KinStashExt4_Index,

	FactionStash_Index,			// ���ֿ�
	FactionStashExt1_Index,		// ���ֿ���չ����1
	FactionStashExt2_Index,
	FactionStashExt3_Index,
	FactionStashExt4_Index,

	ActionBar1_Index	= 30,	// ������1 //�������ڵĴ�����Ʊ�ʾΪ��������   ChenXY  2011/9/28
	ActionBar2_Index,			//		   //�������ڵĴ�����Ʊ�ʾΪ�ػ�����   ChenXY  2011/9/28
	ActionBar3_Index,                      //�������ڵĴ�����Ʊ�ʾΪ�������   ChenXY  2011/9/28
	ActionBar4_Index,

	FaceActionBar1_Index = 35,
	FaceActionBar2_Index,
	FaceActionBar3_Index,

	Campaign_Lion_Index =40,	//���ʨ���� by zhao
	Campaign_Car_Index,			//������ڳ����߱���

	EquipBag_Pet = 50,
	DeityBoxBag_Index = 60,		//���ϻ����
	SkyBoxBag_Index,			//���ϻ����
	EquipReformBag_Index,       //װ�����챳��
	EquipBagTianHun_Index,      //���װ������
	EquipBagDiHun_Index,        //�ػ�װ������
	FellowEvolutionBag_Index,			//����ǿ�����汳��
	Bag_UI_End,

};

// ����װ��
enum Equip_UI_Index
{
	Equip_Helm,					// ͷ��
	Equip_Chest,				// �ؼ�
	Equip_Belt,					// ����
	Equip_Bracer1,				// ����1
	Equip_Bracer2,				// ����2
	Equip_Boot,					// Ь��
	Equip_MainWeap,				// ��������
	Equip_OffWeap,				// ��������
	Equip_Necklace,				// ����
	Equip_Ring1,				// ��ָ1
	Equip_Ring2,				// ��ָ2
	Equip_Fashion,				// ʱװ
	Equip_Cloak,				// ����
	//Equip_Banner,				// ����
	Equip_Shipin,				// ��Ʒ

	//װ�����
	Equip_Rides1 = 50,			// ���1
	Equip_Rides2,				// ���2
	Equip_Rides3,				// ���3
	Equip_Rides4,				// ���4
	Equip_Rides5,				// ���5
	Equip_Rides6,				// ���6

	//װ���̴�
	Equip_Retinue1 = 60,		// �̴�1
	Equip_Retinue2,				// �̴�2
	Equip_Retinue3,				// �̴�3
	Equip_Retinue4,				// �̴�4
	Equip_Retinue5,				// �̴�5
	Equip_Retinue6,				// �̴�6

	Equip_System1  = 100,		// ϵͳװ��1 ����
	Equip_System2,				// ϵͳװ��2 ����
	Equip_System3,				// ϵͳװ��3 ����
	Equip_System4,				// ϵͳװ��4 ����
	Equip_SuitEffect,			// ��װЧ��λ��

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

	Equip_Pet_Saddle = 50000,		// ��
	Equip_Pet_HorseWhip,		// ���
	Equip_Pet_Weskit,			// ���
	Equip_Pet_Spur,				// ���
	Equip_Pet_Fashion,			//ʱװ

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

// ʹ�ü�������
enum EUseCount_Type
{
	EUseCount_Invalid = -1,
	EUseCount_Prop,			//����ʹ������	
	EUseCount_BuyProp,		//���߹�������
	EUseCount_HuoDong,		//�����
	EUseCount_Quest,		//��������
	EUseCount_Exchange,		//�һ�����
	EUseCount_LiBao1,       //���1����ʹ�ã�
	EUseCount_LiBao2,       //���2��δʹ�ã�
	EUseCount_LiBao3,       //���3��δʹ�ã�
	EUseCount_ExpTaken,     //��ȡ����
	EUseCount_SellMoney,	//���۽�Ǯ����
	EUseCount_Num,		//��ֵʼ��Ϊ��� �����ڴ˺���� by zlm 2012.2.6
};

// ʹ�ü����� ʱ������
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
	EUseCount_Time_Num,		//��ֵʼ��Ϊ��� �����ڴ˺���� by zlm 2012.2.6
};
enum EUseCount_Template
{
	EUseCount_Template_1 = 100000, //ѫ�¶һ�����
	EUseCount_Template_2,					 //ѫ�¶һ����
};
// Ц��UI Pose 
// by ping 2011��11��8��
enum Face_UI_Index
{
	Face_UI_Index_1 = 0,		//��Ӧ Alt + Q
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
//	//����װ������
//	Equip_Pet_Saddle = 50000,		// ��
//	Equip_Pet_HorseWhip,		// ���
//	Equip_Pet_Weskit,			// ���
//	Equip_Pet_Spur,				// ���
//	Equip_Pet_Fashion,			//ʱװ
//};

//��װЧ��
enum SuitEffect
{
	Effect_Liancheng = 1,		//���Ǿ�Ч��
	Effect_Sign,				//ǩ��Ч��
	Effect_Star,				//����Ч��
};

// �͵�����ص�����
const UINT MAIL_PROP_UIPOS		= 610001;						//�ʼ���UIλ��
const UINT AUCTION_PROP_UIPOS	= 620001;						//������UIλ��
const UINT DRAG_PROP_UIPOS		= 620100;						//�����קUIλ��

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
// ��Ҫ��������������
////���ó��﹥��ģʽ��nPetType ��1.ս�裬2.���ޣ�
//void SetAttackType(int nType,int nPetType);
//int GetAttackType( int nPetType );
const int COMBAT_PET = 1;	//ս������
const int FELLOW_PET = 2;	// ��������

//////////////////////////////////////////////////////////////////////////
//ս�����
const int COMBAT_PET_FLAG_ATTACK		= 1;		//����		����������Ŀ�ֻ꣬�������˵�ǰ����Ŀ�ꣻ�������л�����Ŀ���Ҳ��֮�л�����Ŀ��
const int COMBAT_PET_FLAG_DEFANCE		= 2;		//����		���������ڹ������˵�Ŀ�꣬����ж��Ŀ��ͬʱ�������ˣ����ѡ����������һ��Ŀ����й���
const int COMBAT_PET_FLAG_STOP			= 3;		//ͣ��		��ͣ����ĳ�ص㲻���ƶ����Թ���(��ȫ�幥��Ψһ�����ǲ����ƶ�)
const int COMBAT_PET_FLAG_SELECT_ATTACK = 4;		//ѡ�񹥻�	��ѡ��˰�ť֮�������ɿ���ѡ��Ŀ���״̬�����ĳ��Ŀ��֮�󣬳������������ָ��Ŀ�꣬������û�з�����������֮ǰ�����ｫ�����������ез���λ
const int COMBAT_PET_FLAG_ALL_ATTACK	= 5;		//��		��ֻҪ�еж�Ŀ���������Ұ�����ｫ��������ǰ���������ͬʱ�ж��Ŀ���������Ұ�����ｫ����ѡ�������һ��Ŀ����й���
const int COMBAT_PET_FLAG_IDEL			= 6;		//��Ϣ		���������ˣ��������κι��������Ա�������������
#define BUY_SUCCESS_CHARGE      5
//���۵������
//////////////////////////////////////////////////////////////////////////
#define STORAGE_NUM_MAX			200		//ÿ��npc�����۵ĵ���
#define AUCTION_ADD_CHARGE	    15		//��������ɹ���1.5%������
#define AUCTION_BIDSUC_CHARGE	 1		//������Ϣ���ĳɹ���ȡ1%������
#define AUCTION_SUCCESS_CHARGE	25		//�����ɹ���ȡ25%������
#define AUCTION_MANAGE_TIMT     43200   //�����Ĺ���ʱ��  12h

//���۵�������
enum PropType_ForSale
{
	FORSALE_TYPE_INVALID		= 0,
	FORSALE_CHANDLERY_COMMON,			//�ӻ�
	FORSALE_CHANDLERY_HIGH,				//�߼��ӻ�
	FORSALE_PROP_MAGIC,					//ħ����Ʒ
	FORSALE_SKILL_WUSHU,				//����ϵ����
	FORSALE_SKILL_SHESHU,				//����ϵ����
	FORSALE_SKILL_FASHU,				//����ϵ����
	FORSALE_SKILL_YAOSHU,				//����ϵ����
	FORSALE_SKILL_XIANSHU,				//����ϵ����
	FORSALE_AMMO,						//��ҩ
	FORSALE_MATERIAL_COMMON,			//����
	FORSALE_MATERIAL_HIGH,				//�߼�����
	FORSALE_TOOL,						//����
	FORSALE_WEAPON,						//����
	FORSALE_ARMOR,						//����
	FORSALE_ORNAMENT,					//��Ʒ
	FORSALE_FORSALE_VEHICLE,			//ʱװ
	FORSALE_INQUEIR_PROP,				//������Ʒ
	FORSALE_VEHICLE,					//����
	FORASLE_MEDICA,						//ҩƷ
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
	signed int m_GoodsGroupID;			//��ID
	signed int m_PropTemplateID;		//����ĵ���ģ��ID
	signed int m_Num;					//��������
	Type_Money m_Price;					//�۸�
	signed int m_TypeForSale;			//��Ʒ����Ʒ��ģ��ID(�� ���ĵĵ���ģ��ID)
	signed int m_ItemOrder;				//����˳��
	signed int m_UseSex;				//ʹ���Ա�
	signed int m_MinLevel;				//��С�ȼ�
	signed int m_MaxLevel;				//���ȼ�
	signed int m_Seal;					//��ӡ

	signed int m_BuyCount_TimeType;		// �������ʱ������
	signed int m_BuyCount_Num;			// �ڹ涨ʱ���ڹ������
	signed int m_BuyCount_KeyWorlds;	// �ؼ���
};
//////////////////////////////////////////////////////////////////////////

#define MAX_DIALY_JOINER    4

#define	MAX_STR_LENGTH		32
#define	MAX_CHAR_NUMBER		64

enum Skill_Main_Pos
{
	SKILL_PROP_1		= 0,	// ����1
	SKILL_PROP_2,
	SKILL_PROP_3,
	SKILL_PROP_4,

	SKILL_ASSI_1,				// ����1
	SKILL_ASSI_2,

	SKILL_MAX_1,				// ��ɱ1
	SKILL_MAX_2,				// ��ɱ2

	SKILL_POS_END,
};
//enum Desigation_Type
//{
//	Designation_King = 0,
//};

enum Loing_State
{
	Loing_State_ReSetName = 0,			// ͬ����Ҫ����(CreateRole)
	Loing_State_Ok = 1,					// �������˳ɹ�
	Loing_State_Max = 10,				// �Ѿ������������6��
	Loing_State_Select_Login_OK = 11,	// ѡ�˵�¼�ɹ���Select Role��
	Login_State_Select_player_Being =13,// ѡ�е����Ѿ�����Ϸ�Select Role��
	Login_State_Create_Ignore = 15,		// ��������ʱ���໰
};

//
#define MAX_NETGRID_CX		1000
#define MAX_NETGRID_CY		1000
#define SCENE_OBJ_MAX		10000		// һ����������NPC����
#define PROP_ID_NORM		10000		// ���ߴ���table�еĻ�׼ֵ
#define ROLE_MAX_SKILL		500			// һ��

enum	DAMAGE_SCHOOL
{
	//2009.11.20 һ������û����Ϸ�߼���˳�����ҵ�
	DAMAGE_SCHOOL_PHYSICAL_M =0,	//��ս		//2009.1.17 ���ֵ���˫�֣�ֻ�ֽ���Զ��
	DAMAGE_SCHOOL_PHYSICAL_R,		//Զ��
	DAMAGE_SCHOOL_FIRE,				//���˺�
	DAMAGE_SCHOOL_COLD,				//���˺�
	DAMAGE_SCHOOL_SPELL,			//ħ���˺�
	DAMAGE_SCHOOL_POISON,			//���˺�
	DAMAGE_SCHOOL_HEALING,			//����ϵ
	DAMAGE_SCHOOL_DIRECT,			//ֱ���˺�
	DAMAGE_SCHOOL_KIN,				//����ս���˺�
	DAMAGE_SCHOOL_FACTION,			//���ս���˺�
	DAMAGE_SCHOOL_BURN,				//�����˺�
	DAMAGE_SCHOOL_DRUG,				//�ж��˺�
	DAMAGE_SCHOOL_FUZHOU,			//���乥��
	DAMAGE_SCHOOL_FAMILY1,			//�����˺�1
	DAMAGE_SCHOOL_FAMILY2,			//�����˺�2
	DAMAGE_SCHOOL_FAMILY3,			//�����˺�3
	DAMAGE_SCHOOL_LIGHTNING,		//���˺�
	DAMAGE_SCHOOL_PHYSICAL,			//�����˺�ϵ
	DAMAGE_SCHOOL_WUSHU,			//����
	DAMAGE_SCHOOL_SHESHU,			//����
	DAMAGE_SCHOOL_FASHU,			//����
	DAMAGE_SCHOOL_YAOSHU,			//����
	DAMAGE_SCHOOL_XIANSHU,			//����

	//DAMAGE_SCHOOL_PHYSICAL=50,			//����˺�ϵ��ר����ս��������Ч��
	//DAMAGE_SCHOOL_SPELL,
	//DAMAGE_SCHOOL_NULL,
	//DAMAGE_SCHOOL_ALL,

	DAMAGE_SCHOOL_HOT_EFFECT=100,		//����Ч��
	DAMAGE_SCHOOL_DOT_EFFECT,			//����Ч��
};


enum Skill_Class
{
	Skill_Class_Special,
	Skill_Class_Martial,
};

enum Debuff_Type
{
	Debuff_Poison,			//�ж�
	Debuff_Ablepsia,		//ʧ��
	Debuff_Freeze,			//����
	Debuff_Burn,			//����
	Debuff_Stun,			//ѣ��
	Debuff_Slow,			//����
	Debuff_Immobilize,		//����
	Debuff_Confuse,			//����
	Debuff_Slience,			//��Ĭ

	Debuff_TypeCounts,
};


//--ð������--
enum Attack_Result
{
	// ��ͨ
	Attack_Hit = 0,				// ����
	Attack_Hit_Player,          // ������
	Attack_Crit,				// ����
	Attack_Crit_Player,         // ������
	Attack_HolyStrike,			// ����һ��
	Attack_HolyStrike_Player,   // ������һ��
	Attack_Hit_Blood,			// ��Ѫ
	Attack_Crit_Blood,          // ��Ѫ����
	Attack_HolyStrike_Blood,    // ����Ѫ����
	Add_Exp,					// ���Ӿ���

	Valid_Result,				// ��ֵ���ϣ�������ֵ��Ϊ��Ҫ��ʾ��ð������

	Attack_MP,					// ����
	Pet_Hit,					// ���﹥��
	Pet_Crit,					// ���ﱩ��

	// �����⴦�� ��ʱû��
	Attack_Dodge,			    // ����
	Attack_Miss,				// δ����
	Attack_Invincible,			// ����

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
	Prop_School_Nothing = 0,		// ������
	Prop_School_Damage,				// �����˺�
	Prop_School_Spell,				// ħ���˺�
	Prop_School_Armor,				// �������
	Prop_School_SpellResist,		// ħ������
	Prop_School_DoubleResist,		// ˫��װ
	Prop_School_HpEquip,			// ����װ
	Prop_School_RidePet_Damage,		// ��װ �����˺�
	Prop_School_RidePet_Spell,		// ��װ ħ���˺�
	Prop_School_RidePet_Armor,		// ��װ �������
	Prop_School_RidePet_SpellResist,// ��װ ħ������

};
enum ESoulSysType
{
	ESoulSys_Invalid = -1,
	ESoulSys_MingHun,     //����
	ESoulSys_DiHun,       //�ػ�
	ESoulSys_TianHun,     //��� 
	ESoulSys_End,
};

/*// DB ��־
const int DB_FLAG_CREATE = (1<<1);		//����
const int DB_FLAG_DELETE = (1<<2);		//ɾ��
const int DB_FLAG_UPDATE = (1<<3);		//����*/

// Obj��־
const int OBJ_FLAG_NORMAL = 0;			//����
const int OBJ_FLAG_OFFLINE= 1;			//����
const int OBJ_FLAG_DELETE = 2;			//ɾ��
const int OBJ_FLAG_CREATE = 3;			//����
const int OBJ_FLAG_UPDATE = 4;			//����

// �������Ч��
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

// 16 ��ֹת���� 10����
// cp:ȥ��"0x"��ͷ�Ĳ���
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
//���ݼ���ȼ��ͻ���ģ��ID������ȡ��BOSS��ģ��ID
#define GETWHITEID(ID,Familylevel)     (ID + (Familylevel-1)*5)		//bossƷ�� (��)
#define GETGREENID(ID,Familylevel)	((ID + (Familylevel-1)*5)+1)	//bossƷ�� (��)
#define GETBLUEID(ID,Familylevel)		((ID + (Familylevel-1)*5)+2)	//bossƷ�� (��)
#define GETBLACKID(ID,Familylevel)	((ID + (Familylevel-1)*5)+3)	//bossƷ�� (��)
#define GETGOLDID(ID,Familylevel)		((ID + (Familylevel-1)*5)+4)	//bossƷ�� (��)

#define FEEDBOSSTIMES	5

enum FamilyBuilding				//���彨����
{
	Family_JuYiTing = 0,		//������
	Family_ZhaiJiDi,			//լ����
	Family_FightCarHouse,		//ս����
	Family_WuGuan,				//���
	Family_YanJiuSuo,			//�о���
	Family_Strorage,			//�ֿ�
	Family_GoldStrorage,		//���
	Family_YeLianFang,			//ұ����
	Family_JianTa,				//����
	Family_Building_End,
};

//������������루�����CS�Ͻ��м������ʧ��ʱ����Ҫ����������dataserverʱʹ�ã�
enum  FAMILY_OPERATE_ERRORID
{
	CREATEFAMILY_FAILED = 0,	// --��������ʧ��
	CREATEFAMILY_SUCCESS,		//��������ɹ�
	ADDFAMILYMONEY_SUCCESS,      //��Ǯ�ɹ�
	ADDFAMILYMONEY_FAILED,		//��Ǯʧ��
	SENDWORLDMSG_SUCCESS,		//����������Ϣ�ɹ�
	SENDWORLDMSG_FAILED,		//����������Ϣʧ��
	SENDCOLORWORLDMSG_SUCCESS,	//���Ͳ����ɹ�
	SENDCOLORWORLDMSG_FAILED,	//���Ͳ���ʧ��
};


enum FamilyBuildingAttrib
{
	FamilyBuilding_Attrib_Level = 0,		//��ǰ�ȼ�
	FamilyBuilding_Attrib_Hp,				//��ǰѪ��
	FamilyBuilding_Attrib_Wear,				//��ǰ�;ö�
	FamilyBuilding_Attrib_Progress,			//��ǰ����

	FamilyBuilding_Attrib_MaxProgress,		//������
	FamilyBuilding_Attrib_MaxLevel,			//���ȼ�
	FamilyBuilding_Attrib_MaxHp,			//���Ѫ��
	FamilyBuilding_Attrib_MaxWear,			//����;ö�
	FamilyBuilding_Attrib_UpgradeCost,		//��������
	FamilyBuilding_Attrib_UpkeepCost,		//ά������
	FamilyBuilding_Attrib_Type,				//����
	FamilyBuilding_Attrib_FamilyID,			//����ID
};

#define APPLY_JOIN_FAMILY_MAX		20
#define FAMILY_NOTICE_LENGTH_MAX    401


enum Attrib
{
	//////////////////////////////////////////////////
	///������������ & �������԰ٷֱ�����
	//////////////////////////////////////////////////

	Role_Attrib_Waigong	=	1,			//�⹦
	Role_Attrib_Neigong,				//�ڹ�
	Role_Attrib_Shenfa,					//��
	Role_Attrib_Zhenqi,					//����
	Role_Attrib_Jingu,					//���

	Role_Attrib_BaseWaigong,			//�����⹦
	Role_Attrib_BaseNeigong,			//�����ڹ�
	Role_Attrib_BaseShenfa,				//������
	Role_Attrib_BaseZhenqi,				//��������
	Role_Attrib_BaseJingu,				//�������

	Role_Attrib_WaigongEnhance = 11,	//%�⹦
	Role_Attrib_NeigongEnhance,			//%�ڹ�
	Role_Attrib_ShenfaEnhance,			//%��
	Role_Attrib_ZhenqiEnhance,			//%����
	Role_Attrib_JinguEnhance,			//%���



	//////////////////////////////////////////////////
	///״̬����ֵ
	//////////////////////////////////////////////////

	Role_Attrib_Hp  =  21,				//����
	Role_Attrib_MaxHp,					//�������
	Role_Attrib_HpRegen,				//�����ָ�
	Role_Attrib_MaxHpEnhance,			//�������%
	Role_Attrib_BaseHp,					//��������
	Role_Attrib_HpEnhance,				//�����ٷֱȸı�
	Role_Attrib_HpRegenEnhance,			//ÿ���Ѫ%

	Role_Attrib_Mp  = 31,				//����
	Role_Attrib_MaxMp,					//�����
	Role_Attrib_MpRegen,				//�����ָ�
	Role_Attrib_MaxMpEnhance,			//�����%
	Role_Attrib_BaseMp,					//��������
	Role_Attrib_MpEnhance,				//�����ٷֱȸı�
	Role_Attrib_MpRegenEnhance,			//ÿ�����%

	Role_Attrib_NormalEnergy = 41,		//������û�ã�//���������ֵ��ͻ��������û�øĳ�NormalEnergy(��������) change by zhangjianli 2012-7-12
	Role_Attrib_MaxEnergy,
	Role_Attrib_EnergyRegen,
	Role_Attrib_MaxEnergyEnhance,

	Role_Attrib_Rage  = 51,				// ��ǰŭ��
	Role_Attrib_MaxRage,				// ���ŭ������Ϊŭ�����ֵ���䣬�����ڳ�����д�����������ڳ�ʼ��ʱ��ֵ ROLE_RAGE_NUM_MAX��
	Role_Attrib_RageRegen,				// ŭ���ظ���û�ã�
	Role_Attrib_MaxRageEnhance,			// ŭ���ظ��ٷֱȣ�û�ã�


	//////////////////////////////////////////////////
	///����
	//////////////////////////////////////////////////
	Role_Attrib_MinDamageMelee  = 101,			//��С����(����)
	Role_Attrib_MaxDamageMelee,					//��󹥻�
	Role_Attrib_DamageMelee,					//����
	Role_Attrib_DamageMeleeEnhance,				//������ǿ%

	Role_Attrib_MinDamageRange  = 106,			//��С����(Զ��)
	Role_Attrib_MaxDamageRange,					//��󹥻�
	Role_Attrib_DamageRange,					//����
	Role_Attrib_DamageRangeEnhance,				//������ǿ

	Role_Attrib_MinDamagePhysical = 111,		//��С����(����)`
	Role_Attrib_MaxDamagePhysical,				//��󹥻�
	Role_Attrib_DamagePhysical,					//����
	Role_Attrib_DamagePhysicalEnhance,			//������ǿ%

	Role_Attrib_MinDamageFire   = 116,			//��С���湥��
	Role_Attrib_MaxDamageFire,					//�����湥��
	Role_Attrib_DamageFire,						//���湥��
	Role_Attrib_DamageFireEnhance,				//���湥��%

	Role_Attirb_MinDamageCold   = 121,			//����ͬ�ϣ�
	Role_Attirb_MaxDamageCold,
	Role_Attrib_DamageCold,
	Role_Attrib_DamageColdEnhance,

	Role_Attrib_MinDamageLightning = 126,		//�磨ͬ�ϣ�
	Role_Attrib_MaxDamageLightning,
	Role_Attrib_DamageLightning,
	Role_Attrib_DamageLightningEnhance,

	Role_Attrib_MinDamagePoison = 131,			//����ͬ�ϣ�
	Role_Attrib_MaxDamagePoison,
	Role_Attrib_DamagePoison,
	Role_Attrib_DamagePoisonEnhance,

	Role_Attrib_MinHealing = 136,				//���ƣ�ͬ�ϣ�
	Role_Attrib_MaxHealing,
	Role_Attrib_Healing,
	Role_Attrib_HealingEnhance,

	Role_Attrib_MinDamageFamily1 =	146,		//�����˺�1
	Role_Attrib_MaxDamageFamily1,
	Role_Attrib_DamageFamily1,
	Role_Attrib_DamageFamily1Enhance,

	Role_Attrib_MinDamageFamily2 =	151,		//�����˺�2
	Role_Attrib_MaxDamageFamily2,
	Role_Attrib_DamageFamily2,
	Role_Attrib_DamageFamily2Enhance,

	Role_Attrib_MinDamageFamily3 =	156,		//�����˺�3
	Role_Attrib_MaxDamageFamily3,
	Role_Attrib_DamageFamily3,
	Role_Attrib_DamageFamily3Enhance,

	Role_Attrib_MinDamageSpell = 166,				//��С��������
	Role_Attrib_MaxDamageSpell,						//���������
	Role_Attrib_DamageSpell,						//��������
	Role_Attrib_DamageSpellEnhance,					//��������%

	Role_Attrib_MinDirectDamage = 171,				//��Сֱ�ӹ���
	Role_Attrib_MaxDirectDamage,					//���ֱ�ӹ���
	Role_Attrib_DirectDamage,						//ֱ�ӹ���
	Role_Attrib_DirectDamageEnhance,				//ֱ�ӹ���%

	Role_Attrib_AllDamage = 175,			//���й���
	Role_Attrib_AllDamageEnhance,					//���й����ӳ�%

	Role_Attrib_MinBurn		 = 181,					//���չ�����Сֵ
	Role_Attrib_MaxBurn,							//���չ������ֵ
	Role_Attrib_Burn,								//���չ���
	Role_Attrib_BurnEnhance,						//���չ����ӳ�%

	Role_Attrib_MinPosionBuf	= 186,				//�ж�������Сֵ
	Role_Attrib_MaxPosionBuf,						//�ж��������ֵ
	Role_Attrib_PosionBuf,							//�ж�����
	Role_Attrib_PosionBufEnhance,					//�ж�������ǿ%

	Role_Attrib_MinFuZhou		= 191,				//��С���乥��
	Role_Attrib_MaxFuZhou,							//�����乥��
	Role_Attrib_FuZhou,								//���乥��
	Role_Attrib_FuZhouEnhance,						//���乥��%

	Role_Attrib_WuShu,								//�������Թ���
	Role_Attrib_WuShuEnhance,						//�������Թ����ӳ�%

	Role_Attrib_FaShu,								//�������Թ���
	Role_Attrib_FaShuEnhance,						//�������Թ����ӳ�%

	Role_Attrib_SheShu,								//�������Թ���
	Role_Attrib_SheShuEnhance,						//�������Թ����ӳ�%

	Role_Attrib_YaoShu,								//�������Թ���
	Role_Attrib_YaoShuEnhance,						//�������Թ����ӳ�%

	Role_Attrib_XianShu,							//�������Թ���
	Role_Attrib_XianShuEnhance,						//�������Թ����ӳ�%

	//////////////////////////////////////////////////
	///�˺�
	//////////////////////////////////////////////////
	// 	Role_Attrib_MinAttackPowerMelee = 201,			//
	// 	Role_Attrib_MaxAttackPowerMelee,				//
	// 	Role_Attrib_AttackPowerMelee,					//����������(����)
	// 	Role_Attrib_AttackPowerMeleeEnhance,			//����������%
	//
	// 	Role_Attrib_MinAttackPowerRange = 206,			//
	// 	Role_Attrib_MaxAttackPowerRange,
	// 	Role_Attrib_AttackPowerRange,					//����������(Զ��)
	// 	Role_Attrib_AttackPowerRangeEnhance,			//����������%
	//
	//
	// 	Role_Attrib_MinAttackPower = 211,				//��С��������
	// 	Role_Attrib_MaxAttackPower,						//��󹥻�����
	// 	Role_Attrib_AttackPower,						//��������
	// 	Role_Attrib_AttackPowerEnhance,					//��������%
	//
	// 	Role_Attrib_MinSpellPowerFire = 216,			//��С���湥������
	// 	Role_Attrib_MaxSpellPowerFire,
	// 	Role_Attrib_SpellPowerFire,
	// 	Role_Attrib_SpellPowerFireEnhance,
	//
	// 	Role_Attrib_MinSpellPowerCold= 221,				//��
	// 	Role_Attrib_MaxSpellPowerCold,
	// 	Role_Attrib_SpellPowerCold,
	// 	Role_Attrib_SpellPowerColdEnhance,
	//
	// 	Role_Attrib_MinSpellPowerLightning = 226,		//��
	// 	Role_Attrib_MaxSpellPowerLightning,
	// 	Role_Attrib_SpellPowerLightning,
	// 	Role_Attrib_SpellPowerLightningEnhance,
	//
	// 	Role_Attrib_MinSpellPowerPoison = 231,			//��
	// 	Role_Attrib_MaxSpellPowerPoison,
	// 	Role_Attrib_SpellPowerPoison,
	// 	Role_Attrib_SpellPowerPoisonEnhance,
	//
	// 	Role_Attrib_MinHealingPower =	236,			//����
	// 	Role_Attrib_MaxHealingPower,
	// 	Role_Attrib_HealingPower,
	// 	Role_Attrib_HealingPowerEnhance,
	//
	// 	Role_Attrib_MinSpellPower = 266,				//������С����
	// 	Role_Attrib_MaxSpellPower,						//������󹥻�
	// 	Role_Attrib_SpellPower,							//��������
	// 	Role_Attrib_SpellPowerEnhance,					//��������%

	//////////////////////////////////////////////////////////////////////////
	//�˺��ӳɣ�2009.11.20 �˺��ӳɺ��˺����ⲻ��Ӧ�����Ų�ˬ���пոģ�
	//////////////////////////////////////////////////////////////////////////

	Role_Attrib_IncreaseAllResultValue = 276,		//�����˺�����ֵ
	Role_Attrib_IncreaseAllResult = 277,			//�����˺�%
	Role_Attrib_DamageMellIncrease,					//���������˺�����
	Role_Attrib_DamageRangeIncrease,				//Զ�������˺�����
	Role_Attrib_DamageColdIncrease,					//���˺�����
	Role_Attrib_DamgeFireIncrease,					//���˺�����
	Role_Attrib_DamageLightIncrease,				//���˺�����
	Role_Attrib_DamagePosionIncrease,				//���˺�����
	Role_Attrib_DamageHealIncrease,					//��������
	Role_Attrib_DamagePhysicalIncrease,				//�����˺�����
	Role_Attrib_DamageSpellIncrease,				//ħ���˺�����
	Role_Attrib_DamageBurnIncrease,					//�����˺�����
	Role_Attrib_DamageFuZhouIncrease,				//�����˺��ӳ�
	Role_Attrib_DamageWuShuIncrease,				//�����˺��ӳ�
	Role_Attrib_DamageFaShuIncrease,				//�����˺��ӳ�
	Role_Attrib_DamageSheShuIncrease,				//�����˺��ӳ�
	Role_Attrib_DamageYaoShuIncrease,				//�����˺��ӳ�
	Role_Attrib_DamageXianShuIncrease,				//�����˺��ӳ�
	//////////////////////////////////////////////////
	///��������
	//////////////////////////////////////////////////
	Role_Attrib_MinArmorMeleeOH = 301,				//��С�����������
	Role_Attrib_MaxArmorMeleeOH,					//�������������
	Role_Attrib_ArmorMeleeOH,						//�����������
	Role_Attrib_ArmorMeleeEnhanceOH,				//�����������%

	Role_Attrib_MinArmorRange = 307,				//��СԶ���������
	Role_Attrib_MaxArmorRange,						//���Զ���������
	Role_Attrib_ArmorRange,							//Զ���������
	Role_Attrib_ArmorRangeEnhance,					//Զ���������%

	Role_Attrib_MinArmor = 311,						//��С�������
	Role_Attrib_MaxArmor,							//����������
	Role_Attrib_Armor,								//�������
	Role_Attrib_ArmorEnhance,						//�������%

	Role_Attrib_MinFireResist = 316,				//�������
	Role_Attrib_MaxFireResist,
	Role_Attrib_FireResist,
	Role_Attrib_FireResistEnhance,

	Role_Attrib_MinColdResist = 321,				//������
	Role_Attrib_MaxColdResist,
	Role_Attrib_ColdResist,
	Role_Attrib_ColdResistEnhance,

	Role_Attrib_MinLightningResist = 326,			//�����
	Role_Attrib_MaxLightningResist,
	Role_Attrib_LightningResist,
	Role_Attrib_LightningResistEnhance,

	Role_Attrib_MinPoisonResist = 331,				//������
	Role_Attrib_MaxPoisonResist,
	Role_Attrib_PoisonResist,
	Role_Attrib_PoisonResistEnhance,

	Role_Attrib_MinHealingResist = 336,				//���Ʒ���
	Role_Attrib_MaxHealingResist,
	Role_Attrib_HealingResist,
	Role_Attrib_HealingResistEnhance,


	Role_Attrib_MinArmorFamily1 =	346,				//����������
	Role_Attrib_MaxArmorFamily1,						//���������С
	Role_Attrib_ArmorFamily1,							//�������1
	Role_Attrib_ArmorEnhanceFamily1,					//�������1%

	Role_Attrib_MinArmorFamily2 =	351,				//�������2���
	Role_Attrib_MaxArmorFamily2,						//�������2��С
	Role_Attrib_ArmorFamily2,							//�������2
	Role_Attrib_ArmorEnhanceFamily2,					//�������2%

	Role_Attrib_MinArmorFamily3 =	356,				//�������3���
	Role_Attrib_MaxArmorFamily3,						//�������3��С
	Role_Attrib_ArmorFamily3,							//�������3
	Role_Attrib_ArmorEnhanceFamily3,					//�������3%


	Role_Attrib_MinSpellResist = 366,				//������������ָ���У�
	Role_Attrib_MaxSpellResist,
	Role_Attrib_SpellResist,
	Role_Attrib_SpellResistEnhance,

	Role_Attrib_MinDirectDamageArmor = 371,			//ֱ���˺�
	Role_Attrib_MaxDirectDamageArmor,
	Role_Attrib_DirectDamageArmor,
	Role_Attrib_DirectDamageArmorEnhance,

	Role_Attrib_AllArmor = 376,						//���з���
	Role_Attrib_AllArmorEnhance,					//���з�������%


	Role_Attrib_WuShuResist,						//��������
	Role_Attrib_FaShuResist,						//��������
	Role_Attrib_SheShuResist,						//��������
	Role_Attrib_YaoShuResist,						//��������
	Role_Attrib_XianShuResist,						//��������

	//Role_Attrib_MinFuZhouResist	= 381,				//������С����
	//Role_Attrib_MaxFuZhouResist,					//����������
	//Role_Attrib_FuZhouResist,						//�������
	//Role_Attrib_FuZhouResistEnhance,				//�������%

	//////////////////////////////////////////////////
	///�˺�����
	//////////////////////////////////////////////////

	Role_Attrib_MinMeleeDamageReduce = 401,			//������С�˺�����%
	Role_Attrib_MaxMeleeDamageReduce,				//��������˺�����%
	Role_Attrib_MeleeDamageReduce,					//�����˺�����%

	Role_Attrib_MinRangeDamageReduce = 406,			//Զ����С�˺�����%
	Role_Attrib_MaxRangeDamageReduce,				//Զ������˺�����%
	Role_Attrib_RangeDamageReduce,					//Զ���˺�����%

	Role_Attrib_MinPhysicDamageReduce = 411,		//������С�˺�����%
	Role_Attrib_MaxPhysicDamageReduce,				//��������˺�����%
	Role_Attrib_PhysicDamageReduce,					//�����˺�����%

	Role_Attrib_MinFireDamageReduce = 416,			//�����
	Role_Attrib_MaxFireDamageReduce,
	Role_Attrib_FireDamageReduce,

	Role_Attrib_MinColdDamageReduce = 421,			//��
	Role_Attrib_MaxColdDamageReduce,
	Role_Attrib_ColdDamageReduce,

	Role_Attrib_MinLightningDamageReduce = 426,		//��
	Role_Attrib_MaxLightningDamageReduce,
	Role_Attrib_LightningDamageReduce,

	Role_Attrib_MinPoisonDamageReduce = 431,		//��
	Role_Attrib_MaxPoisonDamageReduce,
	Role_Attrib_PoisonDamageReduce,

	Role_Attrib_MinHealingReduce = 436,				//����
	Role_Attrib_MaxHealingReduce,
	Role_Attrib_HealingReduce,

	Role_Attrib_FuZhouDamageReduce = 440,			//����
	Role_Attrib_BurnDamageReduce,					//����

	Role_Attrib_MinSpellDamageReduce = 466,			//ħ���˺���С����
	Role_Attrib_MaxSpellDamageReduce,				//ħ���˺�������
	Role_Attrib_SpellDamageReduce,					//ħ���˺�����

	Role_Attrib_AllDamageReduce = 471,				//�����˺�����
	Role_Attrib_AllDamageReduceEnhance,				//�����˺�����%

	Role_Attrib_DamageReduceDong,					//�˺�����Ļ���

	Role_Attrib_WuShuDamageReduce,					//����
	Role_Attrib_FaShuDamageReduce,					//����
	Role_Attrib_SheShuDamageReduce,					//����
	Role_Attrib_YaoShuDamageReduce,					//����
	Role_Attrib_XianShuDamageReduce,				//����

	/////////////////////////////////////
	//���У�Accuracy����&Parry�м�&Dodge����&Block��&CrushingBlow��ѹ&Glanceƫб ��ϵ��
	//Resilience ���Եȼ��������ܵ������ļ���
	//�����쳣��HolyStrike��ʥ�����Ը�Ϊ����
	////////////////////////////////////
	Role_Attrib_MeleeAccuracy = 501,				//��ս������%
	Role_Attrib_MeleeParry,							//��ս�м���%
	Role_Attrib_MeleeDodge,							//��չ�����
	Role_Attrib_MeleeBlock,							//��ս����
	Role_Attrib_MeleeCrit,							//��ս������%
	Role_Attrib_MeleeCritLevel,						//���̱����ȼ�
	Role_Attrib_MeleeCrushingBlow,					//��ս��ѹ��%
	Role_Attrib_MeleeGlance,						//��սƫб��%
	Role_Attrib_MeleeBlockMultiplier =  514,		//��ս���˺�%
	Role_Attrib_MeleeCritMultiplier,				//��ս�����˺�%
	Role_Attrib_MeleeCrushingBlowMultiplier,		//��ս��ѹ�˺�%
	Role_Attrib_MeleeGlanceMultipiler,				//��սƫб�˺�%

	Role_Attrib_RangeAccuracy = 521,				//Զ��������%
	Role_Attrib_RangeParry,							//Զ���м���%
	Role_Attrib_RangeDodge,							//Զ�̶����%
	Role_Attrib_RangeBlock,							//Զ�̸���%
	Role_Attrib_RangeCrit,							//Զ�̱�����%
	Role_Attrib_RangeCritLevel,						//Զ�̱����ȼ�
	Role_Attrib_RangeCrushingBlow,					//Զ����ѹ��%
	Role_Attrib_RangeGlance,						//Զ��ƫб��%
	Role_Attrib_RangeBlockMultiplier =  534,		//Զ�̸��˺�%
	Role_Attrib_RangeCritMultiplier,				//Զ�̱����˺�%
	Role_Attrib_RangeCrushingBlowMultiplier,		//Զ����ѹ�˺�%
	Role_Attrib_RangeGlanceMultipiler,				//Զ��ƫб�˺�%

	Role_Attrib_Accuracy = 541,						//����������%
	Role_Attrib_Parry,								//�����м���%
	Role_Attrib_Dodge,								//���������%
	Role_Attrib_Block,								//��������%
	Role_Attrib_Crit,								//����������%
	Role_Attrib_CritLevel,							//���������ȼ�
	Role_Attrib_CrushingBlow,						//������ѹ��%
	Role_Attrib_Glance,								//����ƫб��%
	Role_Attrib_CritLevelEnhance,					//���������ȼ�%

	Role_Attrib_CritResilience = 550,				//���ٱ�������(����)
	Role_Attrib_HolyStrikeResilience,				//��������һ������

	Role_Attrib_BlockMultiplier =  554,				//�������˺�%
	Role_Attrib_CritMultiplier,						//���������˺�%
	Role_Attrib_CrushingBlowMultiplier,				//������ѹ�˺�%
	Role_Attrib_GlanceMultipiler,					//����ƫб�˺�%

	Role_Attrib_FireAccuracy = 561,					//��ϵ������%
	Role_Attrib_FireDodge,							//��ϵ������%
	Role_Attrib_FireBlock,							//��ϵ����%
	Role_Attrib_FireCrit,							//��ϵ������%
	Role_Attrib_FireCritLevel,						//��ϵ�����ȼ�
	Role_Attrib_FireBlockMultiplier = 573,			//��ϵ���˺�ϵ��%
	Role_Attrib_FireCritMulitipiler,				//��ϵ�����˺�%

	Role_Attrib_ColdAccuracy = 581,					//��ϵ������%
	Role_Attrib_ColdDodge,							//��ϵ������%
	Role_Attrib_ColdBlock,							//��ϵ����%
	Role_Attrib_ColdCrit,							//��ϵ������%
	Role_Attrib_ColdCritLevel,						//��ϵ�����ȼ�
	Role_Attrib_ColdBlockMultiplier = 593,			//��ϵ��ϵ��%
	Role_Attrib_ColdCritMulitipiler,				//��ϵ�����˺�%

	Role_Attrib_LightningAccuracy = 601,			//��ϵ������%
	Role_Attrib_LightningDodge,						//��ϵ������%
	Role_Attrib_LightningBlock,						//��ϵ����%
	Role_Attrib_LightningCrit,						//��ϵ������%
	Role_Attrib_LightningCritLevel,					//��ϵ�����ȼ�
	Role_Attrib_LightningBlockMultiplier = 613, 	//��ϵ��ϵ��%
	Role_Attrib_LightningCritMulitipiler,	    	//��ϵ�����˺�%


	Role_Attrib_PoisonAccuracy = 621,				//��ϵ������%
	Role_Attrib_PoisonDodge,						//��ϵ������%
	Role_Attrib_PoisonBlock,						//��ϵ����%
	Role_Attrib_PoisonCrit,							//��ϵ������%
	Role_Attrib_PoisonCritLevel,					//��ϵ�����ȼ�
	Role_Attrib_PoisonBlockMultiplier = 633,		//��ϵ��ϵ����%
	Role_Attrib_PoisonCritMulitipiler,				//��ϵ�����˺�%


	Role_Attrib_HealingAccuracy = 641,				//����ϵ������%
	Role_Attrib_HealingDodge,						//����ϵ������%
	Role_Attrib_HealingBlock,						//����ϵ����%
	Role_Attrib_HealingCrit,						//����ϵ������%
	Role_Attrib_HealingCritLevel,					//����ϵ�����ȼ�
	Role_Attrib_HealingBlockMultiplier = 653,		//����ϵ��ϵ��%
	Role_Attrib_HealingCritMulitipiler,				//����ϵ�����˺�%

	Role_Attrib_PhysicalAccuracy = 661,				//����������%
	Role_Attrib_PhysicalParry,						//�������%
	Role_Attrib_PhysicalDodge,						//���������%
	Role_Attrib_PhysicalBlock,						//�������%
	Role_Attrib_PhysicalCrit,						//��������%
	Role_Attrib_PhysicalCritLevel,					//�������ȼ�
	Role_Attrib_PhysicalCrushingBlow,				//������ѹϵ��
	Role_Attrib_PhysicalGlance,						//����ƫб��
	Role_Attrib_PhysicalBlockMultiplier =  674,		//�����%
	Role_Attrib_PhysicalCritMultiplier,				//�������˺�%
	Role_Attrib_PhysicalCrushingBlowMultiplier,		//������ѹ�˺�%
	Role_Attrib_PhysicalGlanceMultipiler,			//����ƫб�˺�%

	Role_Attrib_SpellAccuracy = 761,				//ħ��������%
	Role_Attrib_SpellDodge,							//ħ��������%
	Role_Attrib_SpellBlock,							//ħ������%
	Role_Attrib_SpellCrit,							//ħ��������%
	Role_Attrib_SpellCritLevel,						//ħ�������ȼ�
	Role_Attrib_SpellBlockMultiplier = 773,			//ħ����ϵ��%
	Role_Attrib_SpellCritMultiplier,				//ħ�������˺�%

	Role_Attrib_FuZhouAccuracy = 781,				//����������%
	//Role_Attrib_FuZhouDodge,						//��������%
	//Role_Attrib_FuZhouBlock,						//�������%
	Role_Attrib_FuZhouCrit,							//���䱩����%
	Role_Attrib_FuZhouCritLevel,					//���䱬���ȼ�
	Role_Attrib_FuZhouBlockMultiplier,				//�����ϵ��%
	Role_Attrib_FuZhouMultipiler,					//�����˺�ϵ��%

	Role_Attrib_WuShuCrit,							//����������%
	Role_Attrib_WuShuCritLevel,						//���������ȼ�
	Role_Attrib_WuShuMultipiler,					//�����˺�ϵ��%

	Role_Attrib_FaShuCrit,							//����������%
	Role_Attrib_FaShuCritLevel,						//���������ȼ�
	Role_Attrib_FaShuMultipiler,					//�����˺�ϵ��%

	Role_Attrib_SheShuCrit,							//����������%
	Role_Attrib_SheShuCritLevel,					//���������ȼ�
	Role_Attrib_SheShuMultipiler,					//�����˺�ϵ��%

	Role_Attrib_YaoShuCrit,							//����������%
	Role_Attrib_YaoShuCritLevel,					//���������ȼ�
	Role_Attrib_YaoShuMultipiler,					//�����˺�ϵ��%

	Role_Attrib_XianShuCrit,						//����������%
	Role_Attrib_XianShuCritLevel,					//���������ȼ�
	Role_Attrib_XianShuMultipiler,					//�����˺�ϵ��%
	////////////////////////////////////
	////�˺����շ���   Absorb������    Rebound������
	/////////////////////////////////////
	Role_Attrib_MeleeDamageAbsorb = 801,
	Role_Attrib_MeleeDamageAbsorbRate,
	Role_Attrib_MeleeDamageRebound,					//�����˺�����
	Role_Attrib_MeleeDamageReboundRate,				//�����˺�������%

	Role_Attrib_RangeDamageAbsorb = 806,
	Role_Attrib_RangeDamageAbsorbRate,
	Role_Attrib_RangeDamageRebound,
	Role_Attrib_RangeDamageReboundRate,

	Role_Attrib_DamageAbsorb = 811,
	Role_Attrib_DamageAbsorbRate,
	Role_Attrib_DamageRebound,						//�����˺�����
	Role_Attrib_DamageReboundRate,					//�����˺�������

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

	Role_Attrib_HealingAbsorb = 836,    //������
	Role_Attrib_HealingAbsorbRate,		//������
	Role_Attrib_HealingRebound,
	Role_Attrib_HealingReboundRate,

	Role_Attrib_SpellDamageAbsorb =	866,
	Role_Attrib_SpellDamageAbsorbRate,
	Role_Attrib_SpellDamageRebound,				//ħ���˺�����
	Role_Attrib_SpellDamageReboundRate,			//ħ���˺�������%

	Role_Attrib_AllDamageAbsorb = 871,			//�����˺�����ֵ
	Role_Attrib_AllDamageAbsorbRate,			//�����˺�������%
	Role_Attrib_AllDamageRebound,				//�����˺�����ֵ
	Role_Attrib_AllDamageReboundRate,			//�����˺�������%

	Role_Attrib_HpDrain = 881,
	Role_Attrib_HpDrainRate,
	Role_Attrib_HpDrainRateMax,

	Role_Attrib_MpDrain = 886,
	Role_Attrib_MpDrainRate,
	Role_Attrib_MpDrainRateMax,

	//////////////////////////////////////
	/////�ٶ�
	//////////////////////////////////////
	Role_Attrib_AttackSpeed = 901,
	Role_Attrib_CastRate,
	Role_Attrib_RunSpeed,
	Role_Attrib_BaseRunSpeed,
	Role_Attrib_MovingForm,
	Role_Attrib_WalkSpeed,

	Role_Attrib_FastAttackSpeed = 911,
	Role_Attrib_FastCastRate,
	Role_Attrib_FastRunWalk,					//�ƶ��ٶ�%

	Role_Attrib_DamageToMana = 921,				//�˺�ת�Ƹ�����
	Role_Attrib_DamageToManaRate,				//�˺��ٷֱ�ת�Ƹ����� 


	Role_Attrib_SkillLevel	= 931,				//��߼��ܵȼ�
	Role_Attrib_IgnoreTargetDefence,			//����Ŀ�����з���%
	Role_Attrib_IgnoreTargetDefenceRating,		//���ӵ��˷���% ��������
	Role_Attrib_BetterChanceofItemFind,			//��ߵ�������
	Role_Attrib_IncreaseAllAttribute,			//�����������
	Role_Attrib_IncreaseAllAttributeEnhance,	//����������԰ٷֱ�

	Role_Attrib_LearnNewSkill = 941,
	Role_Attrib_AddNewSkill = 946,

	Role_Attrib_SummonCombatPet = 951,				//�ٻ�ս��
	Role_Attrib_EnhanceSkill,					//ǿ������


	Role_Attrib_IncreaseCommonAttackArea = 961, //�ı���ͨ�����Ĺ�����Χ
	Role_Attrib_IncreaseAllArea,

	Role_Attrib_SoulAttrib_HpEnhance     = 971,   //Ԫ�����Լӳ�      Hp						   Ѫֵ
	Role_Attrib_SoulAttrib_DamagePhysicalEnhance, //Ԫ�����Լӳ�     //Role_Attrib_DamagePhysical  �﹦
	Role_Attrib_SoulAttrib_DamageSpellEnhance,    //Ԫ�����Լӳ�     //Role_Attrib_DamageSpell     ħ��
	Role_Attrib_SoulAttrib_ArmorEnhance,		  //Ԫ�����Լӳ�     //Role_Attrib_Armor           ���  
	Role_Attrib_SoulAttrib_SpellResistEnhance,    //Ԫ�����Լӳ�     // Role_Attrib_SpellResist    ħ��

	/////////////////////////////////////////
	////
	/////////////////////////////////////////
	Role_Attrib_Level = 1001,					// �ȼ�
	Role_Attrib_Experience,						// ����
	Role_Attrib_MaxExperience,
	Role_Attrib_ExperienceGained,				//��ǰ����ӳ�
	Role_Attrib_Type,							//Type
	Role_Attrib_CurrentSuit,
	Role_Attrib_PictureID,						//ͷ��ID
	Role_Attrib_Hair,
	Role_Attrib_AIType,
	Role_Attrib_Gold,							//����
	Role_Attrib_GoldBind,						//�󶨽���
	Role_Attrib_Silver,							//����
	Role_Attrib_SilverBind,						//������
	Role_Attrib_StashGold,						//
	Role_Attrib_StashGoldBind,
	Role_Attrib_StashSilver,					//�������ӣ������������幤�ʣ�
	Role_Attrib_StashSilverBind,				//����������(��������ÿ����������)
	Role_Attrib_Credit,							//��ѫֵ
	Role_Attrib_AttributePoints,
	Role_Attrib_SkillPoints,
	Role_Attrib_Invulnerability,
	Role_Attrib_Invisibility,
	Role_Attrib_ChanceOfRebound,				//�˺�����
	Role_Attrib_Inventorys,
	Role_Attrib_Stashes,
	Role_Attrib_UIPos,
	Role_Attrib_AIGroup,
	Role_Attrib_HolyStrike,						// ����һ��%
	Role_Attrib_SceneID,						// ��ɫ��ǰ����ID
	Role_Attrib_Postion_x,						// ��ҵ�ǰ������ x
	Role_Attrib_Postion_y,						// ��ҵ�ǰ������ y
	Role_Attrib_Postion_z,						// ��ҵ�ǰ������ z
	Role_Attrib_StateID,						// ����ID
	Role_Attrib_DangID,							// ���ID
	Role_Attrib_FamilyID,						// ����ID
	Role_Attrib_TitleID,						// �ƺ�ID
	Role_Attrib_LeaveFamilyTime,				// �뿪����ʱ��
	Role_Attrib_HonorStar,						// ����֮��
	Role_Attrib_Wencai,                         // �Ĳ�
	Role_Attrib_QuestionPoint,					// ����÷�
	Role_Attrib_ExplorerRange,					// ͬ����Χ
	Role_Attrib_TeamID,							// ����ID
	Role_Attrib_CatID,							// �ڳ�ID
	Role_Attrib_Online_Time,					// ��ɫ����ʱ��
	Role_Attrib_Job,							// ��ɫְҵ
	Role_Attrib_JobRamify,						// ��ɫְҵ��֦
	Role_Attrib_CombineID,						// ���������Ч��ID
	Role_Attrib_LuaID,		                    // �ű�AI
	Role_Attrib_ClearingHouse_Gold,				// �������洢����
	Role_Attrib_ClearingHouse_Silver,			// �������洢����
	Role_Attrib_Visish,							// �Ƿ����صı�ʶ	//--�޸�ע�ͣ��ѡ��Ƿ�Draw�ı�ʶ����Ϊ���Ƿ����صı�ʶ��
	Role_Attrib_MasterPID,						// ���˵�PID
	Role_Attrib_UseGold,						// Ĭ��ѡ��ʹ�õĻ���
	Role_Attrib_UseSilver,						// Ĭ��ѡ��ʹ�õĻ���
	Role_Attrib_DamageTurnPID,					// �˺�ת�Ƶ���һ��������
	Role_Attrib_DamageTurnPer,					// �˺�ת�Ƶ���һ�������ϵı���
	Role_Attrib_CampaignID,						// �ID
	Role_Attrib_ServerID,						// ������ID
	Role_Attrib_PetProp,						// ����Ŀ��ٻ�����
	Role_Attrib_QuestID,						// ֻ����ָ��������ܱ�����
	Role_Attrib_Dead_Drop_Type,					// ������������
	Role_Attrib_Dead_Drop_Num,					// �������������
	Role_Attrib_Dead_Drop_Money,				// ��������Ľ�Ǯ
	Role_Attrib_Current_RidID,					// ��ǰ���ID
	Role_Attrib_Color,							// ��ɫ
	Role_Attrib_UpdateTime,						// ˢ��ʱ��
	Role_Attrib_WuXing,							// ��������
	Role_Attrib_Birth_Time,						// ����ʱ��
	Role_Attrib_State_Stone,					// �����Ĺ��Ҿ�ʯ ����+��ɫ
	Role_Attrib_Honor,							// ����ֵ
	Role_Attrib_Today_Honor,					// ��������ֵ
	Role_Attrib_Murderer,						// ����
	Role_Attrib_Anonymous,						// ����
	Role_Attrib_Energy,							// ����ֵ��Ŀǰ������¼����ֵ��
	Role_Attrib_Jump_StateFlag,					// ��ת���ҵı��
	Role_Attrib_Position,						// λ����Ϣ
	Role_Attrib_UnreadMailCount,				// δ���ʼ�����
	Role_Attrib_FamilyCarTID,					// ����ս������
	Role_Attrib_FamilyCarPID,					// ����ս��PID, ��ҵ�ǰ�ѵ��ϵ�ս��PID
	Role_Attrib_FamilyCarDriver,			//�Ƿ��Ǽ���ս��˾��
	Role_Attrib_PlayerSwitch,                   // ��ҿ���
	Role_Attrib_FollowPID,						// �����PID
	Role_Attrib_Stall_TID,						// ��Ұ�̯����TID
	Role_Attrib_Stall_PID,						// ��Ұ�̯����PID
	Role_Attrib_Stall_Name,						// ��̯������
	Role_Attrib_Stall_Note,						// ��̯������
	Role_Attrib_Stall_Type,						// ��̯����
	Role_Attrib_KillDust,						// ��ɱ�Ķ���
    Role_Attrib_EffectValue,                    // ��ɫ�������е�Ч��������buff��Ч��
	Role_Attrib_Change_TID,						// �ı�Model TID
	Role_Attrib_Change_ClientID,				// �ı�Model TID
	Role_Attrib_Combit_Pet_TID,					// �ͳ������ʱ�����TID
	Role_Attrib_Combit_Pet_ClientID,			// �ͳ���������ģ�͵�ClientID
	Role_Attrib_Dead_Time,						// ����ʱ��
	Role_Attrib_Dead_Scene,						// �����ĳ���
	Role_Attrib_Wait_LoadScene,					// �ȴ����س���
	Role_Attrib_Pneuma,							// Ԫ��ֵ
	Role_Attrib_ClothStyle,						// �·�����
	Role_Attrib_PractiseGeste,					// ������ѫ
	Role_Attrib_Talented,						// �Ĳ�							//����  ChenXY 2011/11/25  
	Role_Attrib_Clone,							// ���ο�¡PID
	Role_Attrib_PreSceneID,						// �ϴ����ڳ���ID
	Role_Attrib_ThisWeekCredit,					// ���ܹ�ѫ
	Role_Attrib_HeadEffect,						// ͷ����Ч
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
	Role_Attrib_BodyEffect,						//�ʻ�Χ����Ч	  add by����Ƽ 2011-12-16
	Role_Attrib_SaveSilver,                     // Ʊ������
	Role_Attrib_Name,
	Role_Attrib_NPCTitle,
	Role_Attrib_NPCCamp,
	Role_Attrib_CarPosition,					// �ڳ�λ��   add by lfy 2011.9.7
	Role_Attrib_CarSceneID,						// �ڳ�����ʵ��ID add by lfy 2011.9.7
	Role_Attrib_PropertyProtect,                // �Ʋ�����
	Role_Attrib_ProtectOverTime,                // �Ʋ�����-��¼ȡ���Ʋ���������ʱ�� 
	Role_Attrib_ProtectEquipOverTime,			// �Ʋ�����-��¼ȡ��װ���Ʋ�����ʱ�� 
	Role_Attrib_SoulType,                       // ��ɫԪ������
	Role_Attrib_SafetyTime,                     // ��ȫʱ��
	Role_Attrib_SafetyTimeOverTime,             // ��ȫʱ��-��¼�޸İ�ȫʱ��ʱ��
	Role_Attrib_OpenSoulState,                  // ��ɫԪ�꿪��״̬
	Role_Attrib_CombatCredit,					// ս����ѫ
	Role_Attrib_SafetyTimeTemp,                 // �µ���ȫʱ��ʱ��
	Role_Attrib_ForbidSpeakTime,				// ����ʱ��
	Role_Attrib_IsInSealState,                  //�Ƿ��ڷ�ӡ״̬
	Role_Attrib_SealOverTime,                   //��ӡ����ʱ��
	Role_Attrib_PKCamp,						    //PK��Ӫ enum PK_CAMP
	Role_Attrib_SefeGuardFellowID,				// �ػ�����ID�����ݴ�ֵ���ж��ػ��Ŀ���״̬������ЧʱΪû�п����ػ�״̬
	Role_Attrib_HistoryCombatCredit,		    //��ʷս����ѫ
	Role_Attrib_HeroWinTimes,					//�������ʤ������
	Role_Attrib_AutoReLiveTime,					//����������Զ���ȫ�����ʱ��
	Role_Attrib_TopRewardFlag,					//�������Top��ȡ������־
	Role_Attrib_TopWeekRewardFlag,				//�������Top��ȡ������־
	Role_Attrib_Clone_TemplateID,				// ���ο�¡��ɫģ��ID
	Role_Attrib_Clone_Hair,						// ���ο�¡��ɫ����
	Role_Attrib_Clone_ClothStyle,				// ���ο�¡��ɫ���
	Role_Attrib_Clone_EquipOne,					// ���ο�¡��ɫװ��������
	Role_Attrib_Clone_EquipTwo,					// ���ο�¡��ɫװ�����·�
	Role_Attrib_TopWorldLevelRanking,           // �������ȼ�����
	Role_Attrib_TopStateLevelRanking,           // ��ҹ��ҵȼ�����
	Role_Attrib_CurrentBodyFlower,				//��ǰ�����ʻ�Χ����Ч add by ����Ƽ 2011-12-16
	Role_Attrib_PKType,							// PK����enum PK_TYPE��ע������enum PK_STATUS add by zhangjianli 2012-01-13
	Role_Attrib_HeroIslandPoints_1,				// �㽫̨1���ջ���
	Role_Attrib_HeroIslandPoints_2,				// �㽫̨2���ջ���
	Role_Attrib_HeroIslandPoints_3,				// �㽫̨3���ջ���
	Role_Attrib_HeroIslandCurrency,				// �㽫̨�һ�����
	Role_Attrib_ProtectLinShiQuXiao,			// �Ʋ�������ʱȡ��
	Role_Attrib_SystemSet,						// ϵͳ����
	Role_Attrib_FreezeFreeTime,					//�������ʱ��
	Role_Attrib_HeadString,						//ͷ������
	Role_Attrib_StateWarKillCount,				//��ս��ɱ����
	Role_Attrib_DragonCoin,						//��������
	Role_Attrib_TempNPCChar,					//NPC��ʱ�ַ�������
	Role_Attrib_PlayerCreateTime,				//��ɫ����ʱ��
	Role_Attrib_PreChangeStateTime,				//��һ�λ���ʱ��
	Role_Attrib_GMLevel,						//ִ��GMָ������GM�ȼ�
	Role_Attrib_LeaveFamilyCredit,				//ʣ����幱��
	Role_Attrib_FloodEnergy,                    //�����ֵ
	Role_Attrib_FamilyName,			
	Role_Attrib_GangName,	
	Role_Attrib_PID,
	Role_Attrib_OnlineFlag,						//���߱��
	Role_Attrib_CombatCredit_ExchangeNum,		//ս����ѫ�һ����� add by zhangjianli 2012-10-12
	Role_Attrib_CallHeroLandRanking,			//�㽫̨��ǰ����

	Role_Attrib_ExchangePos	= 1300,				// ����λ��
	Role_Attrib_ReturnTown,						// ��һ��ʹ�ü�¼λ��,�ڶ��δ��ͻؼ�¼λ�á�
	Role_Attrib_ClearTime,						// �����ʱ��
	//Role_Attrib_RedNameTime,                    // ������ɫ����ʱ��			//--��¼����ʱ���Ϊ��¼PKֵ-- change by zhaoguoze 2011-03-15
	Role_Attrib_PKValue,	                    //--PKֵ	 ע������PKֵ��ʱ����õ���CPKMgr::SetPKValue(int nValue)����--
	//Role_Attrib_PrisonTime,                     // ���γ���ʱ��	//--��Ϊ[�������ؽ�������ʣ��ʱ��]-- change by zhaoguoze 2011-11-01
	Role_Attrib_PrisonTimeByKing,               //�������ؽ�������ʣ��ʱ�䣨�룩
	//Role_Attrib_RedNameFlag,                    // ������ɫϵͳ���				//--�޸�ΪPK״̬��ǣ�����������ֺ��ֶ�--
	Role_Attrib_PKStatus,						//--PK״̬���  enum PK_STATUS--
	Role_Attrib_NotInquiry,						// ���ܺ�NPC�Ի�
	Role_Attrib_CombinCombatPet_Damage = 1309,	// ������˺�����
	Role_Attrib_LifeTime,						// ������
	Role_Attrib_GangContribute,                 // ��ṱ�׶�
	Role_Attrib_ModelID,						// ģ��ID
	Role_Attrib_Exit_Time,						// ����ʱ��
	Role_Attrib_Login_Time,						// ����ʱ��
	Role_Attrib_AttckID,						// ��ͨ����
	Role_Attrib_PropertyLock,					// �Ʋ�����״̬
	Role_Attrib_PropertyPwd,					// �Ʋ���������
	Role_Attrib_NotUseSpell,					// ����ħ
	Role_Attrib_NotControl,						// ���ܿ���
	Role_Attrib_NotMove,						// �����ƶ�
	Role_Attrib_Stealth,						//����(0�Ƿ񣬡�0������
	Role_Attrib_DisableStealth,					//������
	Role_Attrib_PhysicsInvincible,				//��������
	Role_Attrib_SpellInvincible,				//ħ������
	Role_Attrib_Reflection,						//�����˺�
	Role_Attrib_ExtBagNum,						//�ֿ��й��򱳰�λ�õ�����
	Role_Attrib_CreatePID,						//�����ߵ�PID
	Role_Attrib_MonsterExpAdd,					//ɱ�־���ӳ�
	Role_Attrib_FirInvincible,					//������
	Role_Attrib_ColdInvincible,					//������
	Role_Attrib_LightningInvincible,			//������
	Role_Attrib_PosionInvincible,				//������
	Role_Attrib_BurnInvincible,					//��������
	Role_Attrib_HealingInvincible,				//��������
	Role_Attrib_SlienceInvincible,				//��Ĭ���ߣ�2009.11.2ĿǰΨһ�Ķ�״̬���ߵ����ԣ�һ����boss�ã�
	Role_Attrib_FuZhouInvincible,				//��������
	Role_Attrib_CorpseTime,						//ʬ�屣��ʱ��
	Role_Attrib_CurrentWaitPID,					//��ǰ�̴�
	Role_Attrib_CurrentCombatPID,				//��ǰս��
	Role_Attrib_CurrentCombatName,			//ս������
	Role_Attrib_UnBeatable,						//�޵�״̬
	Role_Attrib_LockUI,							//��������״̬
	Role_Attrib_CurrentCastingSkillID,			//��ǰ��casting����ID	��������casting����ID������״̬���У�
	Role_Attrib_CurrentLifeSkillID,				//��ǰ�����id
	Role_Attrib_Question_HeroTop,				//��Ҵ��⾺�����Լ�������
	Role_Attrib_AutoDriveFlag,			    	//�Զ���ʻ�ı��
	Role_Attrib_Version,						//�汾��Ϣ add by mayanling 2010-3-23
	Role_Attrib_Hidden,							//����״̬
	Role_Attrib_NoEnemy,						//����¼�����б�
	Role_Attrib_QuestFollow,					//������浥λ
	Role_Attrib_Angle,							//��ɫ����ĽǶ�
	Role_Attrib_CastingPropID,					//�����������ܵĵ��ߣ��������������ܵĵ��߱�����״̬���У�
	Role_Attrib_LastChangeHonor,				//�ϴ������һ�ʱ��
	Role_Attrib_GetGiftIndex,					//��ȡ�������
	Role_Attrib_GetGiftToday,			//������ȡ�����
	Role_Attrib_ChaseDistance,					//׷�����루Ĭ��ֵΪ-1��׷��������
	Role_Attrib_WuShuInvincible,				//��������
	Role_Attrib_FaShuInvincible,				//��������
	Role_Attrib_SheShuInvincible,				//��������
	Role_Attrib_YaoShuInvincible,				//��������
	Role_Attrib_XianShuInvincible,				//��������
	Role_Attrib_Client_Vision,					//����Լ����õ������������
	Role_Attrib_First_Login,						//��һ�ε�¼ʱ��
	Role_Attrib_PrayIndex,						//������ǩ����
	Role_Attrib_PreReqSelfStateFtoTime,			//�ϴ����󱾹��������а�ʱ��
	Role_Attrib_PreReqWorldFtoTime,				//�ϴ���������������а�ʱ��
	Role_Attrib_IsAllowSeeEquip,				//�Ƿ�����Է��鿴����װ��
	Role_Attrib_WorldQuestion_JoinState,		//�����״̬
	Role_Attrib_IsAblepsia,						//�Ƿ�ʧ��
	Role_Attrib_ConvoyState,					//����״̬
	Role_Attrib_GetDayGiftIndex,                //ÿ����ȡ���������,��ȡ�������

	Role_Attrib_Current_Campaign_ID=1380,		//��ǰ�����
	Role_Attrib_Stone_Num,						//��ʯ����
	Role_Attrib_Stone_Flag,						//͵��ʯ����
	Role_Attrib_SHENGXIANG_Dead_Num,			//��ʥ�����
	Role_Attrib_QI_Num,							//�������
	Role_Attrib_Get_LaoLong_Num,				//��ȡ��������
	Role_Attrib_Action_Huangshiweiji,			//����Σ�������
	Role_Attrib_FlowerWhite_History_Num,		//��ʷ��õ�廨����
	Role_Attrib_FlowerWhite_Today_Num,			//���հ�õ�廨����
	Role_Attrib_FlowerRed_History_Num,			//��ʷ��õ�廨����
	Role_Attrib_FlowerRed_Today_Num,			//���պ�õ�廨����





	Role_Attrib_Open_Box_Count	= 1400,			//�����Ӵ���
	Role_Attrib_Kill_Enemy,						//ɱ������
	Role_Attrib_Kill_Minister,					//ɱ�󳼵�����
	Role_Attrib_Rose_Number,					//��õ������
	Role_Attrib_History_Rose_Number,			//�ۼ�õ������
	Role_Attrib_Kill_Other_Country_Minister,	//��ɱ�������
	Role_Attrib_DoubleExp_Time,					//��ȡ˫������ʱ��
	Role_Attrib_DoubleExp_Count,				//��ȡ˫���������
	Role_Attrib_Honor_ExchangeNum,				//����ֵ�һ�����
	Role_Attrib_Campaign_PK,					//�ʱ��pk����


	Role_Attrib_Status_Craft_Type =1500,		//	�����״̬����
	Role_Attrib_Status_Dance_Type,				//	���м���״̬����
	Role_Attrib_Status_Express_Type,			//  ����״̬����
	Role_Attrib_Status_Bomb_Type,				//   Я��ը��״̬����
	Role_Attrib_Status_LionDance_Time,			//	��ʨͬ�����ͻ��˵�ʣ��ʱ��
	Role_Attrib_Question_JoinNum,				//  ���˴������
	Role_Attrib_LuckyStarNum,					//	����������

	Role_Attrib_NPC_CurrentTime=1600,			//	npc��ǰʱ��
	Role_Attrib_NPC_CartoonFlag,				// npc���������
	Role_Attrib_NPC_TargetPID,					// npcĿ���PID
	Role_Attrib_NPC_CampainStart,				//npc����Ļ�Ƿ��ڿ�ʼ״̬
	Role_Attrib_Car_PolicyHolder ,				// Ͷ�����ڳ�����ң��������ڳ���

	Role_Attrib_ExtInt32_1 = 1700,				//npc��չ����
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

	Role_Attrib_Player_ExtInt64_1 = 1800,		//player��չ����
	Role_Attrib_Player_ExtInt64_2,              //��԰����  ����Ƿ���� ��ֲ����
	Role_Attrib_Player_ExtInt64_3,
	Role_Attrib_Player_ExtInt64_4,
	Role_Attrib_Player_ExtInt64_5,
	Role_Attrib_Player_ExtInt64_6,
	Role_Attrib_Player_ExtInt64_7,
	Role_Attrib_Player_ExtInt64_8,
	Role_Attrib_Player_ExtInt64_9,
	Role_Attrib_Player_ExtInt64_10,


	Role_Attrib_CarPostionX		=1900,			//�ڳ�����λ��X
	Role_Attrib_CarPostionY,					//�ڳ�����λ��Y
	Role_Attrib_CarSceneTID,					//�ڳ����ڳ���TID
	Role_Attrib_CarTemplateID,					//�ڳ�ģ��id�����ڿ糡��Ѱ·
	Role_Attrib_CarAlarmPosX,					//��¼���ڵĵ�ǰλ��x
	Role_Attrib_CarAlarmPosY,					//��¼���ڵĵ�ǰλ��y
	Role_Attrib_AlarmCarPID,					//��Ҫ���ڵ��ڳ�PID
	Role_Attrib_AlarmReturnSenceID,				//����ǰ�ĳ���id
	Role_Attrib_CarMoney,						//�۳����ڳ��ϵ��ڽ�
	Role_Attrib_AdventureTime,					//����ʱ��
	Role_Attrib_AttackCarPlayerID,				//�����ڳ������
	Role_Attrib_QuestMaster,					//�ܿ����Լ����������
	Role_Attrib_DailyRefreshTime,				//ÿ������ˢ��ʱ��


	Role_Attrib_Status = 2001,
	Role_Attrib_IncreaseChanceOfPoison,			//����ж�����
	Role_Attrib_IncreaseChanceOfAblepsia,		//���ʧ������
	Role_Attrib_IncreaseChanceOfFreeze,			//��߱�������
	Role_Attrib_IncreaseChanceOfBurn,			//������ո���
	Role_Attrib_IncreaseChanceOfStun,			//���ѣ�θ���
	Role_Attrib_IncreaseChanceOfSlow,			//��߼��ٸ���
	Role_Attrib_IncreaseChanceOfImmobilize,		//��߶������
	Role_Attrib_IncreaseChanceOfConfuse,		//��߻��Ҹ���
	Role_Attrib_IncreaseChanceOfSlience,		//��߳�Ĭ����

	Role_Attrib_ReduceChanceOfPoison,			//�����ж�����
	Role_Attrib_ReduceChanceOfAblepsia,			//����ʧ������
	Role_Attrib_ReduceChanceOfFreeze,			//���ͱ�������
	Role_Attrib_ReduceChanceOfBurn,				//�������ո���
	Role_Attrib_ReduceChanceOfStun,				//����ѣ�θ���
	Role_Attrib_ReduceChanceOfSlow,				//���ͼ��ٸ���
	Role_Attrib_ReduceChanceOfImmobilize,		//���Ͷ������
	Role_Attrib_ReduceChanceOfConfuse,			//���ͻ��Ҹ���
	Role_Attrib_ReduceChanceOfSlience,			//���ͳ�Ĭ����

	Role_Attrib_Pet_Ghost_PhysicalDamageEnchance = 2050,	//����������%
	Role_Attrib_Pet_Aqua_PhysicalDamageEnchance,			//ˮ��������%
	Role_Attrib_Pet_Fire_PhysicalDamageEnchance,			//����������%
	Role_Attrib_Pet_Dark_PhysicalDamageEnchance,			//����������%
	Role_Attrib_Pet_Wind_PhysicalDamageEnchance,			//����������%

	Role_Attrib_Pet_Ghost_ArmorEnchance = 2060,	//�����������%
	Role_Attrib_Pet_Aqua_ArmorEnchance,			//ˮ���������%
	Role_Attrib_Pet_Fire_ArmorEnchance,			//�����������%
	Role_Attrib_Pet_Dark_ArmorEnchance,			//�����������%
	Role_Attrib_Pet_Wind_ArmorEnchance,			//�����������%

	Role_Attrib_Pet_Ghost_SpellEnchance = 2070,	//����ħ������%
	Role_Attrib_Pet_Aqua_SpellEnchance,			//ˮ��ħ������%
	Role_Attrib_Pet_Fire_SpellEnchance,			//����ħ������%
	Role_Attrib_Pet_Dark_SpellEnchance,			//����ħ������%
	Role_Attrib_Pet_Wind_SpellEnchance,			//����ħ������%

	Role_Attrib_Campaign1				= 2080, //��ҽ��ܵĻ
	Role_Attrib_Campaign2,
	Role_Attrib_Campaign3,
	Role_Attrib_Campaign4,
	Role_Attrib_Campaign5,
	Role_Attrib_Campaign6,
	Role_Attrib_Campaign7,
	Role_Attrib_Campaign8,
	Role_Attrib_Campaign9,
	Role_Attrib_Campaign10,

	Role_Attrib_ChatGroup1			  = 2090,	//Ⱥ��
	Role_Attrib_ChatGroup2,
	Role_Attrib_ChatGroup3,
	Role_Attrib_ChatGroup4,
	Role_Attrib_ChatGroup5,

	//////////////////////////////////////////////////////////////////////////
	//��personai �Ƴ����� ���������Զ�Ӧ���Ƴ�(��Щû�ӵ�����)
	//playerai
	Role_Attrib_ProgressTime		   = 2100,	//������ʱ��
	Role_Attrib_Spyable,						//�������
	Role_Attrib_AutoRelive,						//�Զ�������
	Role_Attrib_FriendNPCTID,					//�Ѻ�NPC��ģ��
	Role_Attrib_AutoAttackType,					//�Զ�������־
	Role_Attrib_RecoverTime,					//�ָ�ʱ��
	Role_Attrib_IsSendAttack,					//�Ƿ��͹�����ָ��

	//personai
	//Role_Attrib_Invulnerability,				// �Ƿ��޵�(�����������)
	//Role_Attrib_Invisibility,					// �Ƿ�����(�����������)
	Role_Attrib_HoldTime,						//����ʱ��

	//SkillZoneAI
	//ZoneAI
	//PortalAI

	//ridai

	//waiterai
	Role_Attrib_BaseIntervalTime,

	//CCarriageAI
	Role_Attrib_CarriageLoseTime,					//����뿪�ڳ�һ��ʱ�������ʧ��ʱ�䣬��(Carriage)
	Role_Attrib_CarriageQID,						//�洢����id	(Carriage)

	//AutoMoveAI
	Role_Attrib_AutoMoveLoseTime,					//����뿪�ڳ�һ��ʱ�������ʧ��ʱ�䣬��(AutoMove)

	Role_Attrib_ReviveInsituTimes,					//��Ұ�ȫ�������  add by zhangjianli 2011-10-12
	Role_Attrib_ReviveFullStatusTimes,				//�����״̬�������
	Role_Attrib_FellowRefinery_DayTimes,			//���һ���������޵Ĵ��� add by zhangjianli 2012-7-13

	Role_Attrib_Space_Age            =2200,          //����ռ���������               
	Role_Attrib_Space_City,							//����ռ��������
	Role_Attrib_Space_Area,							//����ռ��������
	Role_Attrib_Space_SignName,						//����ռ�ǩ������
	Role_Attrib_Space_Sex,							//����ռ��Ա�����
	Role_Attrib_Current_Designation,				//�������Խ��浱ǰ�ƺ�
	Role_Attrib_DesinationExtraText,
	Role_Attrib_DesinationExtraJieBai,				//�����������⴦��
	Role_Attrib_Effect_Designation,					//��Ч�ƺ�

	Role_Attrib_RGBColor			=2500,			//RGB��ɫ
	Role_Attrib_ModelColor,							//�����ɫ����

	//�˺Ź�����չ��
	Role_Attrib_UserExtPoint1		= 2900,			
	Role_Attrib_UserExtPoint2,						//	�ڶ���չ�� ʹ���ڼ��������(��ռ) by zlm 2012.7.16
	Role_Attrib_UserExtPoint3,						//	������չ�� ʹ���ڶһ������(��ռ) by zlm 2012.7.16
	Role_Attrib_UserExtPoint4,
	Role_Attrib_UserExtPoint5,
	Role_Attrib_UserExtPoint6,
	Role_Attrib_UserExtPoint7,
	Role_Attrib_UserExtPoint8,

	//Prop Attribute
	Prop_Attrib_Damage					= 3001,	//�����˺�
	Prop_Attrib_DamageEnhance,					//�����˺��ӳ�
	Prop_Attrib_BaseDamage,						//���߻����˺�

	Prop_Attrib_Spell,							//ħ������
	Prop_Attrib_SpellEnhance,					//ħ���˺��ӳ�
	Prop_Attrib_BaseSpell,						//����ħ���˺�

	Prop_Attrib_Armor,
	Prop_Attrib_ArmorEnhance,
	Prop_Attrib_BaseArmor,						//�����������

	Prop_Attrib_SpellResist,
	Prop_Attrib_SpellResistEnhance,
	Prop_Attrib_BaseSpellResist,				//����ħ���ֿ�

	Prop_Attrib_HealthPoint,
	Prop_Attrib_HealthPointEnhance,
	Prop_Attrib_BaseHealthPoint,				//��������ֵ

	Prop_Attrib_DoubleArmor,					//����˫��ֵ
	Prop_Attrib_DoubleArmorEnhance,				//����˫��ֵ�ӳ�

	Prop_Attrib_BasePoint,						//����ģ������ο�����
	Prop_Attrib_Level = 3031,					//���ߵȼ�
	Prop_Attrib_SchoolType,						//���ߵ��˺�ϵ
	Prop_Attrib_Type,							//��������
	Prop_Attrib_BindType,						//������
	Prop_Attrib_Quality,						//����Ʒ��
	Prop_Attrib_StackSize,						//���ߵĶѵ���
	Prop_Attrib_MaxStackSize,					//�������ѵ���
	Prop_Attrib_Durability,						//�;ö�
	Prop_Attrib_MaxDurability,					//����;ö�
	Prop_Attrib_StallPrice,						//��̯���ۼ۸�
	Prop_Attrib_Gold,							//�ƽ�۸�
	Prop_Attrib_Silver,							//���Ҽ۸�
	Prop_Attrib_GoldBind,						//�󶨽�Ҽ۸�
	Prop_Attrib_SilverBind,						//�����Ҽ۸�
	Prop_Attrib_Name,
	Prop_Attrib_NameBase,						//���ߵ���������
	Prop_Attrib_NameMid,						//�м���
	Prop_Attrib_NamePre,						//ǰ׺��
	Prop_Attrib_Star,							//
	Prop_Attrib_Hole,							//�����
	Prop_Attrib_PictureID,						//
	Prop_Attrib_Class,							//�ȼ���
	Prop_Attrib_UIPost,							//���ߵ�λ��
	Prop_Attrib_Sign,							//ǩ��
	Prop_Attrib_BindPID,						//�󶨶���
	Prop_Attrib_HoleColor,						//����ɫ
	Prop_Attrib_HoleGem,						//����Ƕ�ı�ʯ
	Prop_Attrib_HoleEffect,						//��ʯЧ��
	Prop_Attrib_HoleActive,						//�׼���
	Prop_Attrib_ActiveUIPos,					//�����λ��
	Prop_Attrib_FloorModel,						//�������ģ��ID
	Prop_Attrib_StatID,							//����
	Prop_Attrib_Flag,							//���壬ְҵ���ϳɣ���ֵȸ�������
	Prop_Attrib_Note_TextID,					//���ߵ�˵������ID����������ţ��������ŵ����ݣ�
	Prop_Attrib_Parent_PID,						//������PID
	Prop_Attrib_ZhanhunTemplateID,				//����ս����Ŀ��λ�õĵ���ģ��ID
	Prop_Attrib_ZhanhunStatID,					//����ս����Ŀ��λ�õĵ��߹���ID
	Prop_Attrib_TemplateID,
	Prop_Attrib_UseNum,							//���ߵ�ʹ�ô���
	Prop_Attrib_PetPID,							//�͵��߰󶨵ĳ���PID
	Prop_Attrib_CustomName,						//�����Զ�������
	Prop_Attrib_SignName,						//ǩ����ҵ�����
	Prop_Attrib_TransSceneID,					//��������¼�Ĵ���λ��
	Prop_Attrib_TransPosX,						//��������¼�Ĵ���λ��
	Prop_Attrib_TransPosY,						//��������¼�Ĵ���λ��
	Prop_Attrib_SplitNum,						//���߲������
	Prop_Attrib_LifeTime,						//ʹ��ʱ��
	Prop_Attrib_EquipLifeTime,					//װ��ʱ��
	Prop_Attrib_SkillID,						//���߼���ID
	Prop_Attrib_PortalPosX,
	Prop_Attrib_PortalPosY,
	Prop_Attrib_PortalScene,
	Prop_Attrib_FamilyMedal,
	Prop_Attrib_LevelMax,						//��ߵȼ�
	Prop_Attrib_GainTime,						//��õ��ߵ�ʱ��
	Prop_Attrib_BeginEquipTime,					//��ʼװ����ʱ��
	Prop_Attrib_SceneID,						//���䳡��ID
	Prop_Attrib_TimeInScene,					//���볡��ʱ��
	Prop_Attrib_QuestID,						//����ID
	Prop_Attrib_QuestMonster,					//��������npc
	Prop_Attrib_DamageSchool,					//���߼����˺�ϵ
	Prop_Attrib_MusicID,						//������Ч
	Prop_Attrib_LuaID,							//����LuaID
	Prop_Attrib_UseCount_Time,					//���ߵ�ʹ�ô��� ʱ������
	Prop_Attrib_UseCount_Num,					//�����ڹ涨ʱ���ڵ�ʹ�ô���
	Prop_Attrib_UseCount_KeyWords,				//����ʹ�ô����� �ؼ���

	//Skill
	Skill_Attrib_NameID = 4001,			// skill �� ����
	Skill_Attrib_DamageSchool,			//�˺�����
	Skill_Attrib_DamageArea,			//�˺���Χ
	Skill_Attrib_MpCast,				//��������
	Skill_Attrib_Flag,
	Skill_Attrib_AAIType,
	Skill_Attrib_TTargetID,				// Ŀ������
	Skill_Attrib_TargetNum,
	Skill_Attrib_MinLevel,				// ��С���Ƶȼ�
	Skill_Attrib_StatusRestrict,		// ״̬����
	Skill_Attrib_WeapenRestrict,		// ��������
	Skill_Attrib_WeapenAssistant,		// ������������
	Skill_Attrib_IntervalTime,			// ÿ��n���˺�damageֵ
	Skill_Attrib_DamageDistanc,			// �˺�����
	Skill_Attrib_DamageValue,			// �˺�ֵ
	Skill_Attrib_CoolDown,				// ��ȴʱ��
	Skill_Attrib_CastTime,				// ʩ��ʱ��
	Skill_Attrib_Distance,				// ʩ������
	Skill_Attrib_CostMp,				// ħ������
	Skill_Attrib_Duration,				// ���ܳ���ʱ��
	Skill_Attrib_TriggerMode,			// ������ʽ
	Skill_Attrib_TargetType,			// ����Ŀ������
	Skill_Attrib_InterruptType,			// �������
	Skill_Attrib_PropCostID,			// ���ĵĵ���ID
	Skill_Attrib_PropCostNum,			// ���ĵĵ�������
	Skill_Attrib_PropCostPos,			// ���ĵ���λ��
	Skill_Attrib_PropCostPosNum,		// ����ָ��λ�õ�������
	Skill_Attrib_MethodDelayTime,		// ������ʽЧ���ӳ�ʱ��
	Skill_Attrib_BeAttackMethod,		// ��������ʽID
	Skill_Attrib_PictureID,				// ͼƬID
	Skill_Attrib_ReadmeID,				// ����˵��ID
	Skill_Attrib_MusicID,
	Skill_Attrib_SpecialllyEffect,
	Skill_Attrib_ExtraCrit,				// ���ܶ��ⱬ������
	Skill_Attrib_DamageEnhance,			// ��߼����˺�%
	Skill_Attrib_CDGroup,				// CD��
	Skill_Attrib_CDGroupValue,			// CDGroup Value
	Skill_Attrib_CostSp,				// ����ŭ��
	//Skill_Attrib_CostEp,				// ���ľ���
	Skill_Attrib_LifeCount,				// ����ʹ�ô���
	Skill_Attrib_LifeLevel,				// �������������ȼ�
	Skill_Attrib_SceneTemplateID,		// ����ģ��ID

	//Effect
	Effect_Attrib_TemplateID		= 5000,
	Effect_Attrib_Property,			    // �������� 0: ���� 1: �к�
	Effect_Attrib_EventID,				// �¼�ID
	Effect_Attrib_School,				// ״̬���� ħ��Ч�� ����Ч�� �ж�Ч��
	Effect_Attrib_ETargetID,			// Ŀ������
	Effect_Attrib_TriggerType,			// ��������
	Effect_Attrib_TriggerRandom,		// Ч�������ļ���
	Effect_Attrib_Key,					// Ҫ�ı������ֵ
	Effect_Attrib_Value,				// �ı������ֵ��С
	Effect_Attrib_NameID,				// Ч��������

	//Buff
	Buff_Attirb_ClassPriority		= 5500,  // buff����������ȼ�  ��3��ʮ����λ��ʾͬ���������ȼ��ĸߵͣ�ǰ���ʾ����
	Buff_Attirb_Interval,					 // ���ʱ�䣬�����0��ʾ��buff��������Ч�ģ���������ı�ʾ��dot�����Ƕ�ʱ������Ч���ļ��ʱ��
	Buff_Attirb_Period,						 // buff�ĳ���ʱ��
	Buff_Attirb_Timer,
	Buff_Attirb_ReadmeID,					 // ״̬˵��ID
	Buff_Attirb_PictureID,					 // ͼƬID
	Buff_Attirb_BuffType,					 // ״̬����
	Buff_Attirb_CasterID,					 // ʩ����ID
	Buff_Attirb_KeyTable,		             // ������Ч������buff ID�ˣ�һ��buff���Դ�������Ч������buff

	//Pet
	Role_Attrib_IncreasePetHp		= 6001,
	Role_Attrib_EnhancePetHp,
	Role_Attrib_PetHpBaseOnLevel,

	Role_Attrib_IncreasePetMp		= 6011,
	Role_Attrib_EnhancePetMp,
	Role_Attrib_PetMpBaseOnLevel,

	Role_Attrib_IncreasePetDamage  = 6021,  // ����ս����������
	Role_Attrib_EnhancePetDamage,			// ����ս����������%
	Role_Attrib_IncreasePetSpellDamage,		// ����ս��ħ��������
	Role_Attrib_EnhancePetSpellDamage,		// ����ս��ħ��������%

	Role_Attrib_IncreasePetArmor	= 6031,	// ����ս���������
	Role_Attrib_EnhancePetArmor,			// ����ս�����������%
	Role_Attrib_IncreasePetResist,			// ����ս��ħ��
	Role_Attrib_EnhancePetResist,			// ����ս��ħ��������%

	Role_Attrib_IncreasePetCritLevel= 6041,	// ����ս�豩���ȼ�
	Role_Attrib_IncreasePetCritEnchance,	// ����ս�豩����%
	Role_Attrib_PetDamageReduce,			// ����ս���˺�����
	Role_Attrib_PetDamageReduceEnchance,	// ����ս���˺�����%

	Role_Attrib_IncreasePetDodge	= 6051,	// ����ս������
	Role_Attrib_PetRunSpeed			= 6201,	// �����ƶ��ٶ�

	Role_Attrib_PetShareDamageRate	= 6231, // ����ֵ��˺�����
	Role_Attrib_PetShareDamage,				// ����ֵ��˺���ֵ

	Role_Attrib_PetEquip1			= 6251,	// ����װ��1
	Role_Attrib_PetEquip2,					// ����װ��2
	Role_Attrib_PetEquip3,					// ����װ��3
	Role_Attrib_PetEquip4,					// ����װ��4

	Role_Attrib_TeamMemberShareDamageRate = 6261,	//���ѷֵ��˺��ٷֱ� add by zhangjianli 2012-9-12
	Role_Attrib_TeamMemberShareDamage,				//���ѷֵ��˺�

	//�ڳ�
	Role_Attrib_CarTouBaoFlag = 6270, //�ڳ�Ͷ�����

	//Family
	Family_Attrib_FamilyID			= 7000,	// ����ID
	Family_Attrib_CaptionID,				// �����峤ID
	Family_Attrib_AssistantID,				// ���帱�峤ID
	Family_Attrib_FireMemberID,				// �������ID ������ʳ��    2011-3-3
	Family_Attrib_StateID,					// ����ID
	Family_Attrib_Level,					// ����ȼ�
	Family_Attrib_Active,					// ���ٶ�
	Family_Attrib_Money,					// �����ʲ�
	Family_Attrib_GangID,					// ���ID
	Family_Attrib_DismissTime,				// ���ɢ���廹���ʱ����
	Family_Attrib_LeaveGangTime,			// �뿪����ʱ��
	Family_Attrib_SetCaptionTime,			// �����峤��ʱ��
	Family_Attrib_SetFlag,					// ���ü�����λ
	Family_Attrib_Skill_Count,				// ���ü�����ѧ��������
	Family_Attrib_Name,						// ��������
	Family_Attrib_PSW,						// ��������
	Family_Attrib_Public,					// ���幫��
	Family_Attrib_Boss_Level,				// ����boss�ȼ�
	Family_Attrib_Boss_Exp,					// ����boss����
	Family_Attrib_Boss_Time,				// boss������ʱ��
	Family_Attrib_Dance_Flag,				// ���������ļ��彨��
	Family_Attrib_Dance_StartTime,			// ������ʨ����ʱ��
	Family_Attrib_DaoChang_Flag,			// ���嵽�������������߲����ĳ���
	Family_Attrib_DaoChang_Time,			// ��������ʱ��
	Family_Attrib_SelectCar_Count,			// ��ȡ����ɼ����Ĵ���
	Family_Attrib_UseSelectCar_Count,		// ʹ�òɼ����Ĵ���
	Family_Attrib_YunBiao_Coun,				// ��ȡ�����ڳ��Ĵ���
	Family_Attrib_YunBiao_Time,				// ��ȡ�����ڳ���ʱ��
	Family_Attrib_JuYi_Count,				// ���������������ݿ�����������ͺ���һ���ֶ� = ���� * 10 + ���ͣ�
	Family_Attrib_JuYi_TreatType,			// �������������ͣ����ݿ���������������һ���ֶ� = ���� * 10 + ���ͣ�
	Family_Attrib_JuYi_StartTime,			// ������忪ʼʱ��
	Family_Attrib_Zhadanren_Number,			// ը���˻���
	Family_Attrib_Zhadanren_TarFamilyID,	// ���Լ��жԹ���ը���˵ļ���id
	Family_Attrib_Zhadanren_TarFamilyNumber,// ���Լ��жԹ���ը���˵ļ������
	Family_Attrib_SelectCar_Flag,			// ����ɼ�״̬���
	Family_Attrib_ApplySpeciality,			// �����Ͻ��ز�
	Family_Attrib_Tiaozhan_Flag,			// ������ս��������ǣ�ÿ��0�����ã�-1Ϊδ������1Ϊ����ͨ������2Ϊ�Ѹ��ѱ�����3Ϊ�Ѿ����䣩
	Family_Attrib_Tiaozhan_TarFamilyID,		// ������ս��Ŀ�����ID,ÿ��0������
	Family_Attrib_Tiaozhan_FlagNumber,		// ������ս������÷֣�ÿ��0����0
	Family_Attrib_Tiaozhan_PkNumber,		// ������ս��PK�÷֣�ÿ��0����0
	Family_Attrib_Tiaozhan_TarPkNumber,		// ������ս��Ŀ�����PK�÷֣�ÿ��0����0
	Family_Attrib_Tiaozhan_TarFlagNumber,	// ������ս��Ŀ��������÷֣�ÿ��0����0
	Family_Attrib_CurrentMemberCount,		// ��ǰ�����Ա����
	Family_Attrib_BossTemplateID,			// ����Boss��ģ��ID
	Family_Attrib_BossModelID,				// ����Boss��ģ��ID	
	Family_Attrib_PkThiefFlag,				// pk�����ʶ
	Family_Attrib_BossID,					// ����boss   ID
	Family_Attrib_BossDareFlag,				// ����boss ��ս���
	Family_Attrib_AddMoneyFlag,				// �Ƿ����Ӽ����ʽ�
	Family_Attrib_PkBossFlag,	
	Family_Attrib_FamilyCurrWeekWages,      // ���屾�ܹ��ʻ�����
	Family_Attrib_FamilyCurrWeekSYWages,    // ���屾��ʣ�๤��
	Family_Attrib_FamilyPastWeekVitality,   // �������ܻ�Ծ��
	Family_Attrib_IsFamilyPayoff,			// �峤�Ƿ��ѷ�������ܹ���
	Family_Attrib_FamliyJinEFanWei,         // ��������������ķ�Χ(��)
	Family_Attrib_FamliyBaiFenBi,           // ���������������İٷֱȣ��ϣ�
	Family_Attrib_TechnologicalPower,		// ����Ƽ�ʵ��
	Family_Attrib_SummonTime,				// �ٻ�ʱ��
	Family_Attrib_ChatPublic,				// �������칫��
	Family_Attrib_CreateTime,				// ���崴��ʱ��
	Family_Attrib_IsBiaoTou,				// �����Ƿ�����ͷ
	Family_Attrib_MaxMemberCount,			// �����Ա�������
	Family_Attrib_IsAllocWage,              // �Ƿ����ڷ��乤��
	Family_Attrib_CaptionUseFamilyTokenTimes,	//�����峤ʹ�ü������ƴ���
	Family_Attrib_AssistantUseFamilyTokenTimes,	//���帱�峤ʹ�ü������ƴ���
	Family_Attrib_CaptionUserName,				//�����峤�û���
	Family_Attrib_Recruit,					// ������ļ��ʽ
	Family_Attrib_IsLoadOver,				//�Ƿ�򿪹�������棬���Ƿ���ع�����
	
	//Family Member
	Family_Member_Attrib_PID		= 7200, // ��ԱPID
	Family_Member_Attrib_Level,				// ��Ա�ȼ�
	Family_Member_Attrib_FamilyID,			// ����ID
	Family_Member_Attrib_FamilyPower,		// ����ְλ
	Family_Member_Attrib_FamilyCredit,		// ���幱�׶�
	Family_Member_Attrib_GangPower,			// ���ְλ
	Family_Member_Attrib_GangCredit,		// ��ṱ�׶�
	Family_Member_Attrib_OnlineFlag,		// ���߱�ʶ
	Family_Member_Attrib_TitleID,			// ����ƺ�ID
	Family_Member_Attrib_FeedBossFlag,		// ι������boss���
	Family_Member_Attrib_FamilyCarID,		// ���ϴ��ڼ���ս��id
	Family_Member_Attrib_PictureID,			// �����Աͷ��ID
	Family_Member_Attrib_Gender,			// �����Ա�Ա�
	Family_Member_Attrib_CreditMoney,		// ���幱���ʽ�
	Family_Member_Attrib_LeaveCredit,		// ʣ����ù��׶�
	Family_Member_Attrib_GongXianWages,     // �����Ա���׹���
	Family_Member_Attrib_GetWagesFlage,		// �����Ա��ȡ���ʱ��
	Family_Member_Attrib_PastWeekWages,		// �����Ա������ȡ�Ĺ���
	Family_Member_Attrib_CurrWeekWages,		// �����Ա����ʵ���Ĺ���

	//Gang
	Gang_Attrib_GangID				= 7400,	// ���ID
	Gang_Attrib_CaptionID,					// ����ID
	Gang_Attrib_AssistantID,				// ������ID
	Gang_Attrib_StateID,					// ����ID
	Gang_Attrib_Level,						// ���ȼ�
	Gang_Attrib_Active,						// ��ᷱ�ٶ�
	Gang_Attrib_Money,						// ����ʽ�
	Gang_Attrib_Status,						// ���״̬
	Gang_Attrib_Sculpture_Level,			// ����ȼ�
	Gang_Attrib_Open_Flag,					// ��ļ������־
	Gang_Attrib_Down_Begin_Time,			// ��ή����ʼʱ��
	Gang_Attrib_SetCaptionTime,				// ����������ʱ��
	Gang_Attrib_DepriveKingTime,			// �������ʱ��
	Gang_Attrib_DissmissTime,				// ��ɢ���ʱ��
	Gang_Attrib_Name,						// �������
	Gang_Attrib_PSW,						// �������
	Gang_Attrib_Public,						// ��ṫ��
	Gang_Attrib_SetFlag,					// ���ð����λ
	Gang_Attrib_Skill_Count,				// ��Ἴ�ܸ���
	Gang_Attrib_CityInspectionFlag,			// ����Ѳ�鿪�����
	Gang_Attrib_CityInspectionTime,			// ����Ѳ�鿪��ʱ��
	Gang_Attrib_CityInspectionNum,			// ����Ѳ��μ�����
	Gang_Attrib_Action_Build,				// ��Ὠ������ʱ��
	Gang_Attrib_CengZhanling_City,			// �����ռ�����
	Gang_Attrib_YiZhanling_City1,			// ����Ѿ�ռ�����1
	Gang_Attrib_YiZhanling_City2,			// ����Ѿ�ռ�����2
	Gang_Attrib_ZhengduoCity_BaomingFlag,	// ��������ս�������
	Gang_Attrib_Speciality_Qi,				// ����ز�
	Gang_Attrib_Speciality_Chu,				// ����ز�
	Gang_Attrib_Speciality_Yan,				// ����ز�
	Gang_Attrib_Speciality_Han,				// ����ز�
	Gang_Attrib_Speciality_Zhao,			// ����ز�
	Gang_Attrib_Speciality_Wei,				// ����ز�
	Gang_Attrib_Speciality_Qin,				// ����ز�
	Gang_Attrib_ChatPublic,					//�������Ⱥ����
	Gang_Attrib_KingAutoDownTime,			//�����Զ���̨ʱ��
	Gang_Attrib_GangFight_KillCount,		//�����ս��ɱ��
	Gang_Attrib_IsLoadOver,					//�Ƿ�򿪹������棬���Ƿ���ع�����

	//State
	State_Attrib_StateID           = 7600,	// ����ID
	State_Attrib_ServerID,					// ����ServerID
	State_Attrib_Produce,					// ������
	State_Attrib_Build,						// �����
	State_Attrib_Militry,					// ����
	State_Attrib_Active,					// ���ٶ�
	State_Attrib_Food,						// ����
	State_Attrib_Power,						// ����
	State_Attrib_Rule,						// ͳ����
	State_Attrib_KingPID,					// ����PID
	State_Attrib_DaYuanShuaiPID,			// ��Ԫ˧
	State_Attrib_DaXueShiPID,				// ��ѧʿ
	State_Attrib_JianJunPID,				// ����
	State_Attrib_ChengXiangPID,				// ة��
	State_Attrib_SetProduceMasterTime,		// ����������ʱ��
	State_Attrib_SetBuildMasterTime,		// ����������ʱ��
	State_Attrib_SetMilityMasterTime,		// �������´�ʱ��
	State_Attrib_GetMoneyTime,				// ����칤��ʱ��
	State_Attrib_UnionStateOne,				// ��һ��ͬ�˹�id
	State_Attrib_UnionStateTwo,				// �ڶ���ͬ�˹�id
	State_Attrib_Public,					// ���ҹ���
	State_Attrib_Stone,						// ���Ҿ�ʯ
	State_Attrib_KingName,					// ��������
	State_Attrib_ProduceName,				// ����������
	State_Attrib_BuildName,					// ���������
	State_Attrib_MilityName,				// ���´�����
	State_Attrib_GuardName,					// �����ӳ�����
	State_Attrib_ProduceNextID1,			// ����������1ID
	State_Attrib_ProduceNextID2,			// ����������2ID
	State_Attrib_ProduceNextID3,			// ����������3ID
	State_Attrib_ProduceNextName1,			// ����������1����
	State_Attrib_ProduceNextName2,			// ����������2����
	State_Attrib_ProduceNextName3,			// ����������3����
	State_Attrib_BuildNextID1,				// ���������1ID
	State_Attrib_BuildNextID2,				// ���������2ID
	State_Attrib_BuildNextID3,				// ���������3ID
	State_Attrib_BuildNextName1,			// ���������1����
	State_Attrib_BuildNextName2,			// ���������2����
	State_Attrib_BuildNextName3,			// ���������3����
	State_Attrib_MilitryNextID1,			// ���´�����1ID
	State_Attrib_MilitryNextID2,			// ���´�����2ID
	State_Attrib_MilitryNextID3,			// ���´�����3ID
	State_Attrib_MilitryNextName1,			// ���´�����1����
	State_Attrib_MilitryNextName2,			// ���´�����2����
	State_Attrib_MilitryNextName3,			// ���´�����3����
	State_Attrib_GuardNextID1,				// �����ӳ�����1ID
	State_Attrib_GuardNextID2,				// �����ӳ�����2ID
	State_Attrib_GuardNextID3,				// �����ӳ�����3ID
	State_Attrib_GuardNextName1,			// �����ӳ�����1����
	State_Attrib_GuardNextName2,			// �����ӳ�����2����
	State_Attrib_GuardNextName3,			// �����ӳ�����3����
	State_Attrib_GUOYUNaction,				// ���˻���
	State_Attrib_GUOYUNtime,				// ���˻��ʼʱ��
	State_Attrib_GUOTANaction,				// ��̽����
	State_Attrib_GUOTANtime,				// ��̽���ʼʱ��
	State_Attrib_GONGFENGaction,			// �����������
	State_Attrib_GONGFENGtime,				// �������ʼʱ��
	State_Attrib_CITANstate,				// ��̽����
	State_Attrib_GONGFENGstate,				// �����������
	State_Attrib_JUNSHIaction,				// ���»�ı��
	State_Attrib_JUNSHIstate,				// ���»�Ĺ���
	State_Attrib_JingBaoFlag,				// ��ɱ����󳼵ľ���״̬
	State_Attrib_StateFlag,					// ���һ״̬
	State_Attrib_WuWangGuoChiFlag,			// ��������״̬���
	State_Attrib_WangCheng_Gang,			// ռ�����ǵİ��
	State_Attrib_MingYueCheng_Gang,			// ռ�����³ǵİ��
	State_Attrib_ZiZhuZhen_Gang,			// ռ��������İ��
	State_Attrib_XianChaLing_Gang,			// ռ���ɲ���İ��
	State_Attrib_FuRongZhai_Gang,			// ռ��ܽ��կ�İ��
	State_Attrib_IsGoodKing,				// �Ƿ����������
	State_Attrib_IsKaiser,					// �Ƿ��ǻʵ�
	State_Attrib_NoSpeakTimes,				// ���Ա���
	State_Attrib_SetPrisonerTimes,			// ������Ҵ���
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

	State_Attrib_StateWarFlag,						// ��ս���
	State_Attrib_StateWarEnemyState,				// ��ս�жԹ�ID
	State_Attrib_StateWarAttackTime,				// ��ս��սʱ��
	State_Attrib_StateWarDefenceTime,				// ��ս����սʱ��
	State_Attrib_EscortFamily1 ,					// �ھ�1����ID�� int���ͣ���ʼֵΪ-1
	State_Attrib_EscortFamily2 ,					// �ھ�2����ID�� int���ͣ���ʼֵΪ-1
	State_Attrib_EscortMoney1  ,					// �ھ�1�ʽ�int���ͣ���ʼֵΪ0
	State_Attrib_EscortMoney2  ,					// �ھ�1�ʽ�int���ͣ���ʼֵΪ0
	State_Attrib_PreGainWCProtectMoneyTime,         // �����ϴ���ȡ����ռ���ʽ��ʱ��
	State_Attrib_Name,								// ����
	State_Attrib_StateWarAttackFlag,
	State_Attrib_WarAttackCount,
	State_Attrib_WarDefendCount,
	State_Attrib_StatePowerRanking,					//�����ۺ�ʵ������
	

	PrivateMember_Attrib_PID			=7800,		//PID
	PrivateMember_Attrib_Name,						//Name
	PrivateMember_Attrib_StateID,					//����ID
	PrivateMember_Attrib_Level,						//�ȼ�
	PrivateMember_Attrib_Flag,						//��ϵ��־
	PrivateMember_Attrib_PictureID,					//ͷ��ID
	PrivateMember_Attrib_Gender,					//�Ա�
	PrivateMember_Attrib_JoinTime,					//��ϵ����ʱ��
	PrivateMember_Attrib_Online,					//���߱��
	PrivateMember_Attrib_FriendCloseValue,			//���ѹ�ϵ��
	PrivateMember_Attrib_ConsortCloseValue,			//���޹�ϵ��
	PrivateMember_Attrib_SwornCloseValue,			//��ݹ�ϵ��
	PrivateMember_Attrib_MasterPupilCloseValue,		//ʦͽ��ϵ��
	PrivateMember_Attrib_SwornPos,					//�����λ
	PrivateMember_Attrib_Pos,						//����λ����Ϣ


	Private_Attrib_PID					=7900,		//PID
	Private_Attrib_ConsortPID,						//��żPID						
	Private_Attrib_SwornTitleType,					//��ݳƺ�����
	Private_Attrib_PrefixTitle,						//��ݳƺ�ǰ׺
	Private_Attrib_PostfixTitle,					//��ݳƺź�׺
	Private_Attrib_FriendCount,						//���Ѹ���
	Private_Attrib_ConsortCount,					//���޸���
	Private_Attrib_BlockCount,						//����������
	Private_Attrib_EnemyCount,						//���˸���
	Private_Attrib_DeepEnemyCount,					//������
	Private_Attrib_MasterCount,						//ʦ������
	Private_Attrib_PupilCount,						//ͽ�ܸ���
	Private_Attrib_SwornCount,						//��ݸ���
	

	
	Group_Attrib_GroupID			= 8000,	//ȺID
	Group_Attrib_Type,
	Group_Attrib_CaptionID,
	Group_Attrib_Name,
	Group_Attrib_Public,

	Group_Member_Attrib_PID			= 8100,	// ��ԱPID
	Group_Member_Attrib_GroupID,
	Group_Member_Attrib_OnlineFlag,			// ���߱�ʶ
	Group_Member_Attrib_ShieldFlag,			// ���α��
	Group_Member_Attrib_Name,				// ��Ա����

	FamilyCar_Attrib_FamilyID				= 8200,	//����ս��
	FamilyCar_Attrib_PID,
	//FamilyCar_Attrib_ID,							//����ս��������λ��
	FamilyCar_Attrib_TemplateID,					//����ս����ģ��ID
	FamilyCar_Attrib_CurrentPID,					//��ǰ��ȡ���PID
	FamilyCar_Attrib_LastPID,						//���һ����ȡ���PID
	FamilyCar_Attrib_Hp_FEIQI,					//����ս����Hp					 (����)
	FamilyCar_Attrib_MaxHp_FEIQI,		//����ս����MaxHp			(����)
	FamilyCar_Attrib_Name,							//����ս������
	FamilyCar_Attrib_LastUserName,					//�ϴ�ʹ��������
	FamilyCar_Attrib_CurUserName,					//��ǰʹ��������
	FamilyCar_Attrib_Status,							//ս��״̬

	FamilyCar_Attrib_FCarType,
	FamilyCar_Attrib_AP,
	FamilyCar_Attrib_MAP,
	FamilyCar_Attrib_AC,
	FamilyCar_Attrib_MAC,
	FamilyCar_Attrib_Speed,
	FamilyCar_Attrib_EffectID,
	FamilyCar_Attrib_Quality,

	//���
	Ride_Attrib_PID						= 8300,	//PID
	Ride_Attrib_Template,						//ģ��ID
	Ride_Attrib_AddHP,							//���ӵ�HP
	Ride_Attrib_AddSpeed,						//���ӵ��ƶ��ٶ�

	Ride_Attrib_AddSTR,
	Ride_Attrib_AddINT,
	Ride_Attrib_AddAGI,
	Ride_Attrib_AddSPI,
	Ride_Attrib_AddSTA,

	Ride_Attrib_AddAP,							//���ӵ�AP
	Ride_Attrib_AddAC,							//���ӵ�AP
	Ride_Attrib_AddMAP,							//���ӵ�MAP
	Ride_Attrib_AddMAC,							//���ӵ�AP

	//PetItem_Attrib_Level,							//����ȼ�
	//PetItem_Attrib_Exp,								//���ﾭ��
	//PetItem_Attrib_WaiGong,							//�����⹦
	//PetItem_Attrib_NeiGong,
	//PetItem_Attrib_ShenFa,
	//PetItem_Attrib_ZhenQi,
	//PetItem_Attrib_JinGu,
	//PetItem_Attrib_AddWaiGong,						//�����⹦�ɳ���
	//PetItem_Attrib_AddNeiGong,
	//PetItem_Attrib_AddShenFa,
	//PetItem_Attrib_AddZhenQi,
	//PetItem_Attrib_AddJinGu,
	//PetItem_Attrib_Equip1,							//����װ��1
	//PetItem_Attrib_Equip2,
	//PetItem_Attrib_Equip3,
	//PetItem_Attrib_Equip4,
	//PetItem_Attrib_Name,							//��������
	//PetItem_Attrib_Grow_WaiGong,					//�⹦�ɳ�ֵ
	//PetItem_Attrib_Grow_NeiGong,					//�ڹ��ɳ�ֵ
	//PetItem_Attrib_Grow_ShenFa,						//���ɳ�ֵ
	//PetItem_Attrib_Grow_ZhenQi,						//�����ɳ�ֵ
	//PetItem_Attrib_Grow_JinGu,						//��ǳɳ�ֵ
	//PetItem_Attrib_WuXing,							//����
	//PetItem_Attrib_AddWuXing,						//��������ֵ
	//PetItem_Attrib_TiLi,							//����
	//PetItem_Attrib_Angry,							//ŭ��

	//����
	Scene_Attrib_ID							= 8400, //����ID
	Scene_Attrib_OwnerID,							//ӵ����ID
	Scene_Attrib_TemplateID,						//����ģ��ID
	Scene_Attrib_Type,								//��������
	Scene_Attrib_AIType,							//����AI����
	Scene_Attrib_LivingTime,						//���ʱ��
	Scene_Attrib_CreateTime,						//����ʱ��
	Scene_Attrib_ManCity,							//��Ӧ����ID
	Scene_Attrib_ServerID,							//���ڷ�����ID
	Scene_Attrib_PlayerNum,							//�������
	Scene_Attrib_Progress,							//��������
	Scene_Attrib_CreatorID,							//������ID
	Scene_Attrib_CampaignID,						//�ID
	Scene_Attrib_StateID,							//����ID
	Scene_Attrib_CloseTime,							//���ùر�ʱ��

	//����ֵ
	Vitality_Attrib_Value1					= 8600,	// �����ۺϻ�Ծ��
	Vitality_Attrib_Value2,							// �����ۺϻ�Ծ��
	Vitality_Attrib_Value3,							// ʱ���Ծ�� 2-8
	Vitality_Attrib_Value4,							// ʱ���Ծ�� 8-14
	Vitality_Attrib_Value5,							// ʱ���Ծ�� 14-20
	Vitality_Attrib_Value6,							// ʱ���Ծ�� 20-2
	Vitality_Attrib_Value7,							// ���Ծ��
	Vitality_Attrib_Value8,							// ��Ϊ��Ծ��

	//�
	Campaign_Attrib_ID						=8900,  //�id
	Campaign_Attrib_Flag,							//����
	Campaign_Attrib_UnitFlag,						//���λ
	Campaign_Attrib_LuaID,							//��ű�id
	Campaign_Attrib_Name,							//�����
	Campaign_Attrib_GameTime,						//���ʱ��
	Campaign_Attrib_StartTime,						//��ʼʱ���(�������п������ͻ��Ч)
	Campaign_Attrib_BeforeStartTime,				//���ʼǰʱ��(�������п������ͻ�п���������ʼ��ʱ��)
	Campaign_Attrib_SignUpTime,						//����ʱ���(���������п������Ϳ��Կ�����)
	Campaign_Attrib_EndSignUpTime,					//������ֹʱ��(���������п������Ϳ��Կ�����ֹʱ��)
	Campaign_Attrib_MinLimitNum,					//��С��������
	Campaign_Attrib_UnitMax,						//��λ�������
	Campaign_Attrib_MatchNum,						//��λƥ������
	Campaign_Attrib_Type,							//�����
	Campaign_Attrib_ServerID,						//����ڷ�����id
	Campaign_Attrib_Week,							//���������
	Campaign_Attrib_SceneTID1,						//�����ģ��1
	Campaign_Attrib_SceneTID2,						//�����ģ��2
	Campaign_Attrib_SceneTID3,						//�����ģ��3
	Campaign_Attrib_SceneTID4,						//�����ģ��4
	Campaign_Attrib_SceneTID5,						//�����ģ��5
	Campaign_Attrib_SceneTID6,						//�����ģ��6
	Campaign_Attrib_SceneTID7,						//�����ģ��7
	Campaign_Attrib_SceneTID8,						//�����ģ��8
	Campaign_Attrib_SceneTID9,						//�����ģ��9
	Campaign_Attrib_SceneTID10,						//�����ģ��10

	Campaign_Attrib_SignUpFlag,						//������ʼ���
	Campaign_Attrib_StartFlag,						//���ʼ���

	CommunityCampaign_Attrib_FamilyID,					//����id
	CommunityCampaign_Attrib_GangID,					//���id
	CommunityCampaign_Attrib_StateID,					//����id
	CommunityCampaign_Attrib_CommunityFlag,				//�����
	CommunityCampaign_Attrib_CompleteFlag,				//����ȱ��
	CommunityCampaign_Attrib_StartTime,					//���ʼʱ��
	CommunityCampaign_Attrib_StartSceneID,				//���ʼ����
	CommunityCampaign_Attrib_SceneID1,					//�����1
	CommunityCampaign_Attrib_SceneID2,					//�����2
	CommunityCampaign_Attrib_SceneID3,					//�����3
	CommunityCampaign_Attrib_SceneID4,					//�����4
	CommunityCampaign_Attrib_SceneID5,					//�����5
	CommunityCampaign_Attrib_SceneID6,					//�����6
	CommunityCampaign_Attrib_SceneID7,					//�����7
	CommunityCampaign_Attrib_SceneID8,					//�����8
	CommunityCampaign_Attrib_SceneID9,					//�����9
	CommunityCampaign_Attrib_SceneID10,					//�����10
	CommunityCampaign_Attrib_ZoneX,						//��������X ����
	CommunityCampaign_Attrib_ZoneY,						//��������Y ����
	CommunityCampaign_Attrib_Param1,					//�����1
	CommunityCampaign_Attrib_Param2,					//�����2
	CommunityCampaign_Attrib_Param3,					//�����3
	CommunityCampaign_Attrib_Param4,					//�����4
	CommunityCampaign_Attrib_Param5,					//�����5




	//�������͵�����
	Effect_ReadMail					= 10000,//
	Effect_HpMaxLVEhance,					//����������޺�Level�ļӳ�
	Effect_MpMaxLVEhance,					//����������޺�Level�ļӳ�
	Effect_Add_Target_Buff,					//��Ŀ���Buff
	Effect_Remove_All_Dot,					//������м���Buf
	Effect_Mp_Enhance,						//�ı䵱ǰMp %
	Effect_Weapen_Mell_Expore,				//��������������������%�����˺�
	Effect_Set_AIType,						//�ı�NPC��AIType
	Effect_Add_Prop,						//���ӵ��ߣ��������ߵõ�����
	Effect_Add_Quest,						//��������
	Effect_Summon_Booth,					//�ٻ���̯��
	Effect_Summon_NPC,						//�ٻ�NPC
	Effect_Transmission_Player,				//����
	Effect_Status_Posion,					//�����ж�״̬
	Effect_Status_OpenWound,				//����ʧ��״̬
	Effect_Status_Freeze,					//�������״̬
	Effect_Status_Burn,						//��������״̬
	Effect_Status_Stun,						//����ѣ��״̬
	Effect_Status_Slow,						//�������״̬
	Effect_Status_Immobilize,				//���붨��״̬
	Effect_Status_Confuse,					//�������״̬
	Effect_Status_Slience,					//�����Ĭ״̬
	Effect_Add_Self_Buff,					//���Լ�����Buff
	Effect_Make_Burn_Damage,				//��������˺�
	Effect_Make_Posion_Damage,				//����ж��˺�
	Effect_Revive,							//�������
	Effect_Catch,							//��׽
	Effect_Add_Summon_Pet_Buff,				//��ս�����buff����������Effect_Add_CombatPet_Buff�ظ���
	Effect_Add_Summon_Pet_Hp,				//��ս�����Hp
	Effect_CombineWithCombatPet,			//��ս�����
	Effect_Set_Trap,						//������
	Effect_Set_Spy,							//���
	Effect_Explorer_FlyTo,					//ͬ��˲���ƶ�
	Effect_CreateAura_Self,					//��������⻷
	Effect_Sit_With_Pet,					//��Pet��λ��
	Effect_Set_Aque_Buff,					//��ˮ�����Buff��������ͳһ��Effect_Add_CombatPet_Buff��
	Effect_Add_CombatPet_Buff,				//��ս���Buff
	Effect_Combin_With_Ghost,				//�͹��Ⱥ���	��������ͳһ����Effect_CombineWithCombatPet��
	Effect_Absorb_CombatPet_Attack_Invalid,	//����ս�蹥����%����������ʱ��Effect_Absorb_CombatPet_AttackEnchance��
	Effect_Absorb_CombatPet_Armor_Invalid,	//����ս�������%����������ʱ��Effect_Absorb_CombatPet_ArmorEnhchance��
	Effect_Combin_With_Aqua,				//��ˮ�����	��������ͳһ����Effect_CombineWithCombatPet��
	Effect_Combin_With_Fire,				//�ͻ������	��������ͳһ����Effect_CombineWithCombatPet��
	Effect_Combin_With_Drak,				//�Ͱ������	��������ͳһ����Effect_CombineWithCombatPet��
	Effect_Combin_With_Wind,				//�ͷ������	��������ͳһ����Effect_CombineWithCombatPet��
	Effect_Add_Explorer_Team_Buff,			//��ͬ���������buff
	Effect_Set_Hp_By_MaxHp,					//����MaxHp����Hp%
	Effect_Set_Mp_By_MaxMp,					//����MaxMp����Mp%
	Effect_Mp_Turn_Damage,					//Mpת�����˺�%
	Effect_Use_Skill,						//��Ŀ��ʹ�ü���
	Effect_ResetSkillPoints,				//���ü��ܵ�
	Effect_ResetAttributePoints,			//�������Ե�
	Effect_Transport,						//���͵�ָ���ص�
	Effect_Set_DamageTurn_Per,				//��Ŀ��ֵ��˺�%
	Effect_Auto_ReLive,						//�Զ�������
	Effect_Status_Funk,						//����־�״̬
	Effect_Add_Prop_Buff,					//��������buff
	Effect_Add_Damage,						//�����˺�
	Effect_Hp_Energy,						//��������
	Effect_Mp_Energy,						//��������
	Effect_Percent_Mp_Turn_Damage,			//���հٷֱȼ�������MP����ת����hp���˺�
	Effect_Prop_HuiCheng_Single,			//����سǾ������Ч�����سǷ���
	Effect_Prop_HuiCheng_Colony,			//Ⱥ��سǾ������Ч��
	Effect_Prop_ShunYi_Single,				//����˲�ƾ������Ч�������޵�ͼ�������
	Effect_Prop_ShunYi_Colony,				//Ⱥ��˲�ƾ������Ч��
	Effect_Prop_JiYi,						//����������Ч��
	Effect_Prop_ShiKong,					//ʱ��ͨ�����Ч��
	Effect_Prop_ZiYou,						//�������Ƶ���Ч��
	Effect_Prop_WangZhe,					//�����������Ƶ���Ч��
	Effect_Prop_Stealth,					//����Ч��
	Effect_Prop_DisableStealth,				//����Ч��
	Effect_Add_Player_CombatePet_Buff,		//���Ѿ��ٻ���ս����˼�buff
	Effect_Catch_Pet,						//��׽����
	Effect_Add_Skill_To_Pet,				//���������Ӽ���
	Effect_Set_Friend_NPC_TID,				//�����Ѻ�NPC��ģ��
	Effect_Set_RoleModel,					//���ý�ɫģ��
	Effect_Set_UnBeatable,					//�޵�״̬
	Effect_Set_Fight_Off,					//����
	Effect_Kill,							//ɱ���Է�
	Effect_FlyTo_Consort,					//���͵����޴�
	Effect_Add_Exp_BySelf,					//�����Լ������MaxExp���Ӿ���
	Effect_Add_Material_By_Level,			//������ҵȼ���������
	Effect_Remove_All_Hot,					//�����������Buf
	Effect_Add_Spell_Dong,					//�����˺�����
	Effect_Add_HpMaxEnhance,				//�ָ��������ްٷֱȵ�����ֵ
	Effect_Get_Prop,                        //͵ȡ�õ����ߣ�ʩ���ߵõ�����
	Effect_Set_Hp,							//���õ�ǰѪֵ
	Effect_Family_Medal,					//����ѫ��
	Effect_Add_Family_Car,					//��Ӽ���ս��
	Effect_Game_Kill,                       //��Ϸ��ɱ
	Effect_Radom_SetNPC,                    //�����npc
	Effect_Change_Hp_Enhance,				//��%�ı䵱ǰѪֵ����ҪðѪ
	Effect_CreateAura_Target,				//��ָ��λ�ô���⻷
	Effect_Set_Crafts_Status,				//���������״̬
	Effect_Set_Express_Status,				//�������״̬
	Effect_Status_Add_Prop,					//״̬��õ���
	Effect_Magic_Box_Get_Prop,				//������Ч��
	Effect_Add_Poison_Buff,					//�����ж�buff
	Effect_Add_Freeze_Buff,					//���ӱ���buff
	Effect_Add_Burn_Buff,					//��������buff
	Effect_Add_Stun_Buff,					//ѣ��buff
	Effect_Add_Slow_Buff,					//����buff
	Effect_Add_Immobilize_Buff,				//����buff
	Effect_Add_Confuse_Buff,				//����buff
	Effect_Add_Slience_Buff,				//��Ĭbuff
	Effect_In_ChangeModel_Status,			//����ı�ģ��״̬
	Effect_ResetWaigongPoint,				//�����⹦���Ե�
	Effect_ResetNeigongPoint,				//�����ڹ����Ե�
	Effect_ResetShenfaPoint,				//���������Ե�
	Effect_ResetZhenqiPoint,				//�����������Ե�
	Effect_ResetJinguPoint,					//���ý�����Ե�
	Effect_Add_Ride_Pet,					//����һ�����
	Effect_Charge_Target,					//��棬�嵽��Ŀ���������˲�ƣ�
	Effect_Combin_With_RidPet,				//��������
	Effect_SilverBind,						//��ð�����(��)
	Effect_SetCommonSill,					//������ͨ����
	Effect_CatchQuestNPC,					//��������npc
	Effect_OpenQuestComplete,				//�������ύ
	Effect_Add_Car_Buff,					//���Լ����ڳ���buff
	Effect_Summon_MyNPC,					//�ٻ�maseter���Լ���NPC
	Effect_INC_RidPet_Exp,					//������辭��
	Effect_Fellow_HuanHun,					//���޻���
	Effect_Spell_Turn_Damage,				//ħ��ת�˺�
	Effect_UseSkill_To_Myself,				//���Լ�ʹ�ü���
	Effect_Script_Call,						//�ű�����
	Effect_Prop_ShunYi_Map,					//����˲�ƾ������Ч�����ޱ����������
	Effect_Fly_To_Map,						//���͵�ĳ��ͼ
	Effect_Prop_To_Flight,					//ʹ�õ��߽������״̬
	Effect_Quest_SummonMonster,				//�ٻ�һ���������
	Effect_Quest_SummonProtectNPC,			//�ٻ�һ������������NPC
	Effect_Summon_BelongSelfNPC,			//�ٻ�����Ϊ�Լ���NPC
	Effect_Control_Car_Attack,				//����ս������Ŀ��
	Effect_Gang_SummonAllMember,			//�ٻ�����Ա
	Effect_Jump,							//��Ծ
	Effect_Family_Car_Summon,				//���������ٻ�ս��
	Effect_Add_Head_Effect,					//���ͷ����Ч
	Effect_Summon_Teammate,					//�ٻ�����
	Effect_Add_Buff_To_Master,				//���������BUFF
	Effect_Add_CombineBuff,					//���ս�����Buff
	Effect_Absorb_CombatPet_AttackEnchance,	//����ս�蹥����%
	Effect_Absorb_CombatPet_ArmorEnhchance, //����ս�������%
	Effect_Absorb_CombatPet_MaxHpEnhchance, //����ս����������%
	Effect_Absorb_CombatPet_CritEnhchance,	//����ս�豩����%
	Effect_Add_ExperienceByW,				//����Ϊ��λ�����Ӿ���
	Effect_Damage_TargetBySelfMaxHp,		//��Ŀ���˺��������Լ����Ѫֵ%��
	Effect_Damage_SelfBySelfMaxHp,			//���Լ��˺��������Լ����Ѫֵ%��
	Effect_Set_ModelColor,					//����ģ������
	Effect_Family_Car_Enter,				//�������󣬽���ս��
	Effect_Clear_SkillCD,					//����ĳ����CD
	Effect_Target_CallBackRide,				//��Ŀ������
	Effect_Auto_Stop,						//�Զ�ֹͣ
	Effect_Auto_Drive,						//�Զ���ʻ
	Effect_Absorb_CombatPet_DamageReduceEnchance,//����ս���˺�����%

	Effect_Set_Dance_Status			=10201,	//������������״̬
	Effect_Set_Bomb_Status,					//����Я��ը��״̬���ѷ�����
	Effect_Set_Game_Status,					//������Ϸ״̬

	Effect_RondomModel				=10300, //�����һ��ģ��
	Effect_EreaseKill,						//��NPC��ʧ��ˢ��ʱ�䵽��Ḵ��
	Effect_SummonCarGod,					//�ٻ��ڳ�����npc
	Effect_Summon_PropQuestNPC,				//�����ٻ�����������Npc

	Effect_Use_Baby_Egg				= 10350,		//��ͨ��������ʹ��Ч��
	Effect_Use_Seal_Egg,							//��ӡ������޵���ʹ��Ч��(���)
	Effect_Use_Breed_Egg,							//��ֳ��ĳ������޵���ʹ��Ч��
	Effect_Use_Prop_CatchFellow,					//���޵��ߵ�ʹ��Ч��
	Effect_Use_ChangeSoulTypeToDiHun,				//�л����ػ�
	Effect_Use_ChangeSoulTypeToMingHun,				//�л�������
	Effect_Use_ChangeSoulTypeToTianHun,				//�л������
	Effect_Remove_Target_Buff,						//�Ƴ�Ŀ��BUFF add by zhangjianli 2012-3-2
	Effect_Add_PractiseGeste,						//����������ѫ add by zhangjianli 2012-7-30
	Effect_Set_PKType_Protect,							//����PK���� add by zhangjianli 2012-9-6

	//������Ч
	Effect_Set_Cursor_Cast			= 20000,//�������Ϊʩ��״̬
	Effect_Set_Cursor_Repair,				//�������Ϊ����״̬
	Effect_Open_Inquiry,					//��һ���Ի�
	Effect_Open_Stall,						//�򿪰�̯��
	Effect_Set_Use_Prop_Skill,				//���븽ħ״̬
	Effect_Open_Portal,						//�򿪴��ͽ���
	Effect_Prop_JiYiPos,					//��������
	Effect_Progress_Bar,					//���ý�����״̬
	Effect_Ready_Use_Prop,					//����ʹ�õ���״̬
	Effect_Set_Cursor_Choice,				//����ѡ��Ŀ��״̬�������Ŀ��Ͳ��л�״̬��
	Effect_Open_PropCompose,				//�򿪴������



	//�����������
	//ע�Ͳ����������õ������ԣ��ⲿ��������ǰ�涨��
	//Role_Attrib_Fellow = 21000,											
	//Fellow_Attri_TID,																//TID
	//Role_Attrib_MasterPID,
	//Role_Attrib_SceneID,
	//Role_Attrib_StateID,
	//Role_Attrib_Birth_Time,
	//Role_Attrib_Angle,

	//һ������
	//Fellow_Attri_Name,																//Name
	//Role_Attrib_Level,
	//Role_Attrib_Experience
	//Role_Attrib_MaxExperience
	//Role_Attrib_Hp
	//Role_Attrib_MaxHp
	//Role_Attrib_ChaseDistance

	Role_Attrib_BreedNum = 21000,														//��ֳ����
	Role_Attrib_Sex,																//�Ա�	--������Ϊ����ʹ�ã������--
	Role_Attrib_FellowType,																//���� enum Fellow_Type   //lqp �Ѷ�����ͬ����
	Role_Attrib_Happy,															//���ֶ�
	Role_Attrib_MaxHappy,													//�����ֶ�
	Role_Attrib_Life,																//����
	Role_Attrib_MaxLife,														//�������

	//��������
	Role_Attrib_Grow,																//�ɳ�
	Role_Attrib_UnderStand,													//����
	//Fellow_Attri_UnuseAttriPoint,											//δʹ�õ����Ե�		//--�ϲ���ͳһ��Role������Role_Attrib_AttributePoints-- change by zhaoguoze 2011-08-31

	Role_Attrib_Aptitude_STR,												//��������
	Role_Attrib_Aptitude_INT,												//��������
	Role_Attrib_Aptitude_AGI,												//��������
	Role_Attrib_Aptitude_SPI,												//��������
	Role_Attrib_Aptitude_STA,												//��������

	//Fellow_Attri_STR,																//����	//--�ϲ���ͳһ��Role������Role_Attrib_Waigong-- change by zhaoguoze 2011-08-31
	//Fellow_Attri_INT,																//����	//--�ϲ���ͳһ��Role������Role_Attrib_Neigong-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_AGI,																//����	//--�ϲ���ͳһ��Role������Role_Attrib_Shenfa-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_SPI,																//����	//--�ϲ���ͳһ��Role������Role_Attrib_Zhenqi-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_STA,																//����	//--�ϲ���ͳһ��Role������Role_Attrib_Jingu-- change by zhaoguoze 2011-09-01

	//Fellow_Attri_AP,																//������	//--�ϲ���ͳһ��Role������Role_Attrib_DamagePhysical-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_AC,																//�������	//--�ϲ���ͳһ��Role������Role_Attrib_Armor-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_MAP,																//ħ������	//--�ϲ���ͳһ��Role������Role_Attrib_DamageSpell-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_MAC,																//ħ������	//--�ϲ���ͳһ��Role������Role_Attrib_SpellResist-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_Dunt,																//�ػ�	//--�ϲ���ͳһ��Role������Role_Attrib_Crit-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_Jouk,																//����	//--�ϲ���ͳһ��Role������Role_Attrib_Dodge-- change by zhaoguoze 2011-09-01

	Role_Attrib_Max_Aptitude_STR,												//������������
	Role_Attrib_Max_Aptitude_INT,												//������������
	Role_Attrib_Max_Aptitude_AGI,												//������������
	Role_Attrib_Max_Aptitude_SPI,												//������������
	Role_Attrib_Max_Aptitude_STA,												//������������

	Role_Attrib_Aptitude_Grow,											//�ɳ�����
	Role_Attrib_Aptitude_UnderStand,								//��������

	Role_Attrib_Breed_Level,													//��ֳ�ȼ�

	//�������ϵļӳ�ֵ������ֶ�����Щ���Լӵĵ���
	Role_Attrib_Add_STR,																//���ӵ�����
	Role_Attrib_Add_INT,																//���ӵ�����
	Role_Attrib_Add_AGI,																//���ӵ�����
	Role_Attrib_Add_SPI,																//���ӵľ���
	Role_Attrib_Add_STA,																//���ӵ�����

	//Fellow_Attri_Add_AP_Enhance,														//���ӵ�������%	//--�ϲ���ͳһ��Role������Role_Attrib_WaigongEnhance-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_Add_AC_Enhance,														//���ӵ��������%	//--�ϲ���ͳһ��Role������Role_Attrib_ArmorEnhance-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_Add_MAP_Enhance,														//���ӵ�ħ������%	//--�ϲ���ͳһ��Role������Role_Attrib_NeigongEnhance-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_Add_MAC_Enhance,														//���ӵ�ħ������%	//--�ϲ���ͳһ��Role������Role_Attrib_SpellResistEnhance-- change by zhaoguoze 2011-09-01
	//Fellow_Attri_Add_Dunt_Enhance,														//���ӵ��ػ�%	��������
	//Fellow_Attri_Add_Jouk_Enhance,														//���ӵ�����%	��������

	Role_Attrib_StarLevel,															//ǿ������ǵȼ� (1 - 30)
	Role_Attrib_TakeLevel,															//Я���ȼ�
	//--����Ч��--
	Effect_UnderStand_SelfPhysicalAttackEnhance = 21300,					//��������������������%
	Effect_UnderStand_SelfMagicAttackPEnhance,								//������������ħ��������%
	Effect_UnderStand_SelfPhysicalDefenseEnhance,							//���������������������%
	Effect_UnderStand_SelfMagicDefenseEnhance,								//������������ħ��������%
	Effect_UnderStand_SelfCritEnhance,										//�����������ޱ�����%
	Effect_UnderStand_SelfMaxHpEnhance,										//��������������������%

	Effect_UnderStand_MasterPhysicalAttackEnhance = 21400,					//���˸�������������ȡ�﹥%
	Effect_UnderStand_MasterMagicAttackPEnhance,							//���˸�������������ȡħ��%
	Effect_UnderStand_MasterPhysicalDefenseEnhance,							//���˸�������������ȡ���%
	Effect_UnderStand_MasterMagicDefenseEnhance,							//���˸�������������ȡħ��%
	Effect_UnderStand_MasterCritEnhance,									//���˸�������������ȡ������%
	Effect_UnderStand_MasterMaxHpEnhance,									//���˸�������������ȡ��������%

	Effect_Convert_MasterPhysicalAttackEnhance = 21500,						//������ȡ�����﹥%
	Effect_Convert_MasterMagicAttackPEnhance,								//������ȡ����ħ��%
	Effect_Convert_MasterPhysicalDefenseEnhance,							//������ȡ�������%
	Effect_Convert_MasterMagicDefenseEnhance,								//������ȡ����ħ��%
	Effect_Convert_MasterMaxHpEnhance,										//������ȡ�����������%

	//�������
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
	StateOfficer_AttribInt_YunBiaoHoldTimesPerDay,	//ÿ���������˴���
	StateOfficer_AttribInt64_AppointerTime,			//����ʱ��

};

const int HELPNOTICE_FLAGCOUNTS = 15;		//���������еĴ��̱������ 
enum CAMPAIGN_DATA_INDEX
{
	CamPaignData_Gifts		=   0,				//��ʱ���
	CampaignData_PlayerPointsActive,			//��¼�����ʾ��ǰ�Ƿ񼤻�
	CamPaignData_HelpNoticeFlag_Begin,			//��ͷ�����������̱�ǿ�ʼλ		add by lfy 2012.3.1
	CamPaignData_HelpNoticeFlag_End = CamPaignData_HelpNoticeFlag_Begin +HELPNOTICE_FLAGCOUNTS-1 ,			//��ͷ�����������̱�ǽ���λ
	CamPaignData_MaxID,							//��������ֵ������ӻʱ���ڴ���ǰ��� add by lfy 2011.7.2
};

enum FlashBox_ButtonType
{
	FlashBox_ButtonType_Individual		=	-1	,			//Ĭ��
	FlashBox_ButtonType_Common					,			//ͨ����ʾ
	FlashBox_ButtonType_ExpTip					,			//������ʾ
	FlashBox_ButtonType_PlayerPoint				,			//�����ʾ
	FlashBox_ButtonType_SeverDown				,			//�������ر���ʾ
	FlashBox_ButtonType_EquipProtect            ,           //ȡ��װ������
	FlashBox_ButtonType_PropertyProtect         ,           //ȡ���Ʋ���������
	FlashBox_ButtonType_SafetyTimeDown          ,           //�µ���ȫʱ��
	FlashBox_ButtonType_LevelSeal				,			//��ӡ����
	FlashBox_ButtonType_SealMonster				,			//ʮ���·�ӡ����

	FlashBox_ButtonType_JoinCompetition = 50,	//�_����
	FlashBox_ButtonType_EscortTeam,				//�_����
	FlashBox_ButtonType_FamilyCarOpt,			//����ս��
	FlashBox_ButtonType_ApplyJoinFamily,		//��������������
	FlashBox_ButtonType_EscortDangerCar,		//�ھ�Σ���ڳ��б�
	FlashBox_ButtonType_FamiyEscort,			//�������ڻ����
	FlashBox_ButtonType_FamilyAppointAssiatant,	//�������帱�峤
	FlashBox_ButtonType_FamilyAppointFooder,	//��������ʳ��
	FlashBox_ButtonType_FamilyFirePower,		//��������ְ
	FlashBox_ButtonType_GangAppointAssistant,	//������ḱ����
	FlashBox_ButtonType_GangFirePower,			//������ְ��
	FlashBox_ButtonType_ALT_F,					//AltF��������
	FlashBox_ButtonType_StatePower_BeFire,		//���ҹ�ְ������
	FlashBox_ButtonType_KingDownAsRule,			//ͳ�����½�������̨
	FlashBox_ButtonType_FamilyPayoff,			//�峤�ѷ��䱾�ܼ��幤�ʣ�֪ͨ��Ա��ȡ
	FlashBox_ButtonType_FamilyNotPayoff,		//�峤��û�з��䱾�ܹ��ʣ�֪ͨ�峤����
	FlashBox_ButtonType_StateWarAlarm,			//��ս��������
	FlashBox_ButtonType_RideBird,				//��ɫ�����ɺ׺���ʾ:�Ҽ�ͷ���·�������ͼ���ȡ�����״̬

	FlashBox_ButtonType_Chat_Private	=	100	,			//��������
	FlashBox_ButtonType_Chat_Family				,			//��������
	FlashBox_ButtonType_Chat_Gang				,			//�������
	FlashBox_ButtonType_Chat_Group				,			//Ⱥ������
	
	FlashBox_ButtonType_Notice_LevelUp	=	200	,			//������ʾ
	FlashBox_ButtonType_Notice_LevelUp_AddPoints,			//�����ӵ���ʾ
	FlashBox_ButtonType_Notice_NewCapability	,			//�¹���Ԥ��
	FlashBox_ButtonType_Notice_AvailableGames	,			//�ɽӻ
	
};

struct ATTRIB_MAP
{
	Attrib	ID;
	char	Name[50];
};

//��ҿ��ع���
//����ֵ��0����أ�1����
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 .........
// |
// |
// |
// |
//����ֵ

//λ�����ص�����
//(ע�����64����С1)
enum PLAYER_SWITCH
{
	PLAYER_SWITCH_AVAILABLEQUEST = 61	,	//��ʾȫ���ɽ�����Ĭ�ϲ���ʾ
	PLAYER_SWITCH_QUESTTRACK=62,
	PLAYER_SWITCH_HELPTIP=63,      //��63λ���Ƿ���ʾtip�����Ŀ���
};

//���ؿ��ص�ֵ
inline   BOOL     IsPlayerSwitchOpen(uint64 nSwitch,int n)
{
	return  (((uint64)1<<(n-1)) & nSwitch)!=(uint64)0;
}

//���ÿ���
inline   uint64    SetPlayerSwitch(uint64 nSwitch,int n,BOOL Flag)
{
	uint64 tempSwitch;
	if(Flag)
		tempSwitch= ((uint64)1<<(n-1)) | nSwitch;
	else
		tempSwitch= ~((uint64)1<<(n-1)) & nSwitch;
	return tempSwitch;
}


//����CUtlMap������һЩ�꣬by zhao
//////////////////////////////////

//����
#define FIND_MAP_VALID(mapname,mapkey)\
	int nIndex = mapname.Find( mapkey );\
	if(mapname.IsValidIndex(nIndex))\
	return mapname.Element(nIndex);\
	return NULL;
//ɾ��
#define DEL_MAP_VALID(mapname,mapkey)\
	int nIndex = mapname.Find( mapkey );\
	if( mapname.IsValidIndex( nIndex ) )\
	mapname.Remove(mapkey);\
	else\
	return FALSE;
//����
#define INSERT_MAP_VALID(mapname,mapelement,mapkey)\
	int index=mapname.Find(mapkey);\
	if(mapname.IsValidIndex(index))\
	return FALSE;\
	mapname.Insert(mapkey,mapelement);

#define FOR_EACH_LIST(listname,index)\
	for(int index=listname.Head();listname.IsValidIndex(index);index=listname.Next(index))



const int g_OpenDiHun_QuestID = 6701;     //�����ػ�Ĵ������� 

//////////////////////////////////////////////////////////////////////////
// �� ��ֵ�Դ洢��Blob ��֧��    ��DB ʹ�� 
//////////////////////////////////////////////////////////////////////////
enum EBlobStoreType
{
	EBST_Int = 1,
	EBST_Int64,
	EBST_String,
};

//////////////////////////////////////////////////////////////////////////
// ����̵Ļ��� (Type,Key,Value)										//
// Type�� ��ʾVuale ������  (1 ��ʾint  2 ��ʾint64  3 ��ʾ str)   short//
// Key��  ����key  ֵ ���� Player���� ���� �������Ե� Enum ֵ      int  //
// Value���洢ֵ                                     int or int64 or str//
// ע�⣺ Ŀǰֻ֧�� int int64  str  �����������ͣ��������ع���		//
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
//������� buffer ��ģ�庯�� �� MySql ��Ӧ Blob �洢��ʽ                 //
//ʹ��ʱע�⣺                                                           //
//			ʵ����ʱ typeClass �������SetAttribInt��SetAttribInt64      //
//			SetAttribStr ����                                            //
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
				//--Ϊ��֤����Դͳһ��Ҫɾ��Buff�еĵȼ����ԣ��ֲ��������ݿ⣬����3.0�汾�Ժ��ع��˷�������Ӱ汾��-- del by zgz 2012-3-21
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
		default: assert(0);   //������������ͣ��벹��������
		}
	}
}

//--���ݱ������ͷ�������Ӧ������Ԫ������--
//--nIndex���������� enum Bag_UI_Index--
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

//--��������Ԫ�����ͷ�������Ӧ�ı�������--
//--nSoulType��Ԫ������ enum ESoulSysType--
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


//ϵͳ����ѡ��
enum SYSTEMSET_OPTION
{
	//Ԥ��5��Ƶ��������  1-14λΪ��������
	CHAT_EXPLORERCHANNEL = 1 << 0,
	CHAT_AREACHANNEL     = 1 << 1,
	CHAT_WORLDCHANNEL    = 1 << 2,
	CHAT_STATECHANNEL    = 1 << 3,
	CHAT_GANGCHANNEL     = 1 << 4,
	CHAT_FAMILYCHANNEL   = 1 << 5,
	CHAT_TEAMCHANNEL     = 1 << 6,
	CHAT_FRIENDCHANNEL   = 1 << 7,
	CHAT_PVPCHANNEL		 = 1 << 8,

	//Ԥ��3��λ�ø�����  15-25Ϊ��������
	FUNCTION_ALLOWTEAM			 = 1 << 11,
	FUNCTION_AUTOTEAM			 = 1 << 12,
	FUNCTION_ALLOWBUSINESS       = 1 << 13,
	FUNCTION_ADDFRIEND           = 1 << 14,
	FUNCTION_ALLOWJOIN_GANG      = 1 << 15,
	FUNCTION_ALLOWJOINFAMILY     = 1 << 16,
	FUNCTION_ALLOWSEEEQUIP       = 1 << 17,
	FUNCTION_EXTENDSKILL		 = 1 << 18,

	//��ʾ
	SHOW_EFFICT		    = 1 << 21,		
	SHOW_ROLENAME       = 1 << 22,		//�Ƿ���ʾ�������
	SHOW_MinMap		    = 1 << 23,		//�Ƿ���ʾС��ͼ
	SHOW_HEADTOPEXP     = 1 << 24,		//�Ƿ���ʾͷ������
	SHOW_GROUNDPROPNAME = 1 << 25,		//�Ƿ���ʾ������Ʒ����
	SHOW_CHATPAOPAO     = 1 << 26,		//�Ƿ���ʾ������������
	SHOW_CENTERNOTIFY   = 1 << 27,		//�Ƿ���ʾ��Ļ���빫��
	SHOW_AUTOPICK		= 1 << 28,		//�Ƿ��Զ�ʰȡ
};



enum	TEAM_ERROR_CODE
{
	MAPNOTALLOW = 0 , //����ҵ�ǰ���ڵĵ�ͼ���������
};

enum GameTVType
{
	GTV_Invalid = -1,
	GTV_Common,							//��ͨ
	GTV_KillBoss,								//��ɱBOSS
	GTV_KillEnemy,              //����ɱ��
	GTV_PeachGarden,           //��԰����
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
	int m_nPower;	//��ְ
	int nFamilyID;
	int nTeamID;
	char m_szName[MAX_ALIAS_NAME_LEN];
};

//����ս����ѫ�һ��̵����Ʒ
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

//ע�⣺ʹ������꣬����Ҫ��֤Dest��һ�� char [] ��������һ�� char *
#define _STRNCPY_F(Dest,Src) \
		strncpy(Dest,Src,sizeof(Dest) - 1); \
		Dest[sizeof(Dest) - 1] = '\0';



//--����ս����ɫ�ֱ��ǣ���ͨ���ף����̣������ϣ���
const int	COLOR_FAMILYCAR_MODEL_COMMON = 49;
const int	COLOR_FAMILYCAR_MODEL_GREEN = 806;
const int	COLOR_FAMILYCAR_MODEL_BLUE = 807;
const int	COLOR_FAMILYCAR_MODEL_PURPLE = 808;
const int	COLOR_FAMILYCAR_MODEL_GOLD = 809;

//Ѱ·��ɫ
const int	COLOR_FAMILYCAR_FINDWAY = 533;		


#define  Car_Stop_Dist 20 



// �ַ���IP ת int64 ����
inline int64 StrIpToInt64(char* strIP)
{
	if(!strIP || strlen(strIP) <= 0)
		return 2885681153LL;		//��IP ��Чʱ ���� "172.0.0.1" �� 64λ��

	std::string sIp = strIP;

	CToken token;
	token.setToken(".");
	token.parseString(sIp);

	int64 iRsult = 0;
	for( int nIndex = 0; nIndex< 4; nIndex++)
		iRsult |= token.getInt64(nIndex) << 8 * (3 - nIndex);

	return iRsult;
}	

// ��װ����
enum ESuit_Type
{
	ESuit_Type_Quality = 1,		//Ʒ����װ
	ESuit_Type_Star,			//����װ
};

//�ݲ߻����󣬸�Ϊ�Ƿ�����۲�ϵͳ��Ϣ��ʾ
enum ESeeEquip
{
	ESE_AllowSee 	= 1,
	ESE_UnAllowSee 	= 2,
};

const int SUIT_EFFECT_TYPECOUNT		 = 2;				//��װ��������(����װ, Ʒ����װ)
const UINT	QUALITYSUIT_EFFECT_EQUIP_MINCOUNT = 8;		//Ʒ����װЧ�����8��
const UINT	STARSUIT_EFFECT_EQUIP_MINCOUNT = 12;		//����װЧ�����12��
const UINT	STARSUIT_EFFECT_STAR_MINCOUNT	= 6;		//����װ���6��(3������)

const UINT	SUIT_EFFECT_GROUPMAXNUM =	ESoulSys_End + 1;	//��װ����( ����, ��ɷ, ��ɷ ) + 1 (����)
const UINT	SUIT_EFFECT_RIDEPETINDEX =	ESoulSys_End;		//1 (����) ����

const int SUIT_EFFECT_EQUIP_MINCOUNT = 8;
const int SUIT_EFFECT_EQUIP_MAXCOUNT = 12;
const int EQUIP_MAXCOUNT = 14;							//��װЧ��װ������

					
//////////////////////////////////////////////////////////////////////////
const int EQUIPCOMPOSELEVELRANGE = 20;				// װ���ϳɷ�Χ	
//////////////////////////////////////////////////////////////////////////

const int PROP_STARSTONESEALLEVELUP = 20;	// �������ʯ�ĵȼ� ��װ���ȼ����в�ֵ

//////////////////////////////////////////////////////////////////////////
const Type_Money MONEY_RADIX		= 1000;						// ��Ǯ���ƣ�(%)ȡģ��
const Type_Money MONEY_WEN_RADIX	= 1;						// ��Ǯ�����ĵĽ��ƣ�(/ *)�˳���
const Type_Money MONEY_LIANG_RADIX = MONEY_RADIX;				// ��Ǯ�������Ľ��ƣ�(/ *)�˳���
const Type_Money MONEY_DING_RADIX	= MONEY_RADIX*MONEY_RADIX;	// ��Ǯ���㶧�Ľ��ƣ�(/ *)�˳���
const Type_Money MONEY_ONEDING		= 1000000;					// ��Ǯһ��



// ��Ǯת��
// GetMoneyNum ���ݶ����Ļ�ȡ��Ǯ��
inline Type_Money GetMoneyNum(int d,int l,int w) { return(Type_Money)((d*MONEY_DING_RADIX) + (l*MONEY_LIANG_RADIX) + w); }
// GetMoneyWen GetMoneyLiang GetMoneyDing����Ǯ����ֳ�3�ֵ�λ������,���� 1002003 ������� 1��2��3��
inline Type_Money GetMoneyWen(Type_Money t) { return(t%MONEY_RADIX); }
inline Type_Money GetMoneyLiang(Type_Money t) { return((t/MONEY_LIANG_RADIX)%MONEY_RADIX); }
inline Type_Money GetMoneyDing(Type_Money t) { return(t/MONEY_DING_RADIX); }
// GetMoneyDLW����Ǯ����ֳ�3�ֵ�λ������,һ�δ���3����λ,���� 1002003 ������� 1��2��3��
inline void GetMoneyDLW(Type_Money t,int& d,int& l,int& w) { d = (t/MONEY_DING_RADIX); l = ((t/MONEY_LIANG_RADIX)%MONEY_RADIX); w = (t%MONEY_RADIX); }
// ChangeToWen ChangeToLiang ChangeToDing���ݶ����ķֱ�ת���ɸ�����λ������,���� 1002003 ������� 1������1002������1002003��
inline Type_Money ChangeToWen(int d,int l,int w) { return(GetMoneyNum(d,l,w)); }
inline Type_Money ChangeToLiang(int d,int l,int w) { return(GetMoneyNum(d,l,w)/MONEY_LIANG_RADIX); }
inline int ChangeToDing(int d,int l,int w) { return(GetMoneyNum(d,l,w)/MONEY_DING_RADIX); }


//--ϵͳ���ܿ���--
enum ESystemSwitch
{
	SWITCH_FLAG_MATERIAL_COMPOSE				= 0,	//���Ϻϳ�
	SWITCH_FLAG_YEARWINE,								//�������
	SWITCH_FLAG_NPC_DROP,								//�������
	SWITCH_FLAG_EQUIP_COMPOSE,							//װ���ϳ�
	SWITCH_FLAG_EQUIP_SIGNBIND,							//ǩ����
	SWITCH_FLAG_EQUIP_ADDSTAR,							//װ������
	SWITCH_FLAG_EQUIP_ADDHOLE,							//װ�����
	SWITCH_FLAG_EQUIP_ADDGEM,							//װ����Ƕ��ʯ
	SWITCH_FLAG_EQUIP_REMOVEGEM,						//װ��ժ����ʯ
	SWITCH_FLAG_EQUIP_REMOVESTAR,						//װ��ժ������
	SWITCH_FLAG_EQUIP_APPENDSTAR,						//װ����������
	SWITCH_FLAG_EQUIP_REBIND,							//װ�����°�
	SWITCH_FLAG_EQUIP_CHANGE_FIVEELEMENT,				//װ���޸�����
	SWITCH_FLAG_EQUIP_CHANGE_SOULCHAIN,					//װ���޸��������
	SWITCH_FLAG_EQUIP_SUIT,								//װ����װ


	SWITCH_FLAG_PLAYER_BUSINESS,						//��ҽ���
	SWITCH_FLAG_STALL_BUSINESS,							//��̯����
	SWITCH_FLAG_STORAGE,								//�ֿ�
	SWITCH_FLAG_MAIL,									//�ʼ�
	SWITCH_FLAG_AUCTION,								//������
	SWITCH_FLAG_DRAGONCONVERTSILVER,					//���Ҷһ�����
	SWITCH_FLAG_BANK_STORE_SILVER,						//���Ŵ������
	SWITCH_FLAG_BANK_TAKEOUT_SILVER,					//����ȡ������
	SWITCH_FLAG_BEG_BUY,								//����


	SWITCH_FLAG_FELLOW_FREEDOM,							//�������
	SWITCH_FLAG_FELLOW_REFINE,							//��������
	SWITCH_FLAG_FELLOW_GIVEBACK_SOUL,					//���޻���
	SWITCH_FLAG_FELLOW_FEED,							//����ι��
	SWITCH_FLAG_FELLOW_STRENGTHEN,						//����ǿ��
	SWITCH_FLAG_FELLOW_BREED,							//���޷�ֳ
	SWITCH_FLAG_FELLOW_REBIRTH,							//��������
	SWITCH_FLAG_FELLOW_HUANHUA,							//���޻û�
	SWITCH_FLAG_FELLOW_PROTECT,							//�����ػ�
	SWITCH_FLAG_HORSE_RIDE,								//��ƥ���
	SWITCH_FLAG_HORSE_EQUIP,							//��ƥװ������
	SWITCH_FLAG_HORSE_STRENGTHEN,						//��ƥǿ��


	SWITCH_FLAG_CHANGE_EQUIP,							//�һ�װ��
	SWITCH_FLAG_CASTE_HELP,								//����ϵ����
	SWITCH_FLAG_FULMINIC_DROP,							//��������
	SWITCH_FLAG_SPECIFIC,								//��Ч
	SWITCH_FLAG_VOICE,									//��Ч
	SWITCH_FLAG_CHANGE_SOUL_TO_DISHA,					//�����л�����ɷ
	SWITCH_FLAG_CHANGE_TITLE,							//�ƺ��л�
	SWITCH_FLAG_AUTO_ATTACK,							//�Զ����
	SWITCH_FLAG_AUTO_COLLECT,							//�Զ��ɼ�
	SWITCH_FLAG_AUTO_OPRATINGUNIT,						//����ϵͳ
	SWITCH_FLAG_PKTYPE_PEACE,							//�л���ƽģʽ
	SWITCH_FLAG_PKTYPE_ALL,								//�л�ȫ��ģʽ
	SWITCH_FLAG_PKTYPE_STATE,							//�л�����ģʽ
	SWITCH_FLAG_PKTYPE_UNION,							//�л��˹�ģʽ
	SWITCH_FLAG_PKTYPE_FAMILY,							//�л�����ģʽ
	SWITCH_FLAG_PKTYPE_GANG,							//�л����ģʽ
	SWITCH_FLAG_PKTYPE_EVIL,							//�л��ƶ�ģʽ
	SWITCH_FLAG_PKTYPE_STATEWAR,						//�л���սģʽ
	SWITCH_FLAG_FELLOW_AUTO_OPRATINGUNIT,				//���︨��ϵͳ
	SWITCH_FLAG_SEND_ROSE,								//����õ��
	SWITCH_FLAG_SEND_QIANZHIHE,							//����ǧֽ��
	SWITCH_FLAG_SILVER_PROTECTED,						//�Ʋ�����
	SWITCH_FLAG_SAFETY_TIMELIMIT,						//��ȫʱ��
	SWITCH_FLAG_CHANGE_REDNAME,							//�ı����
	SWITCH_FLAG_SYSTEM_SET_CHAT,						//ϵͳ����-����
	SWITCH_FLAG_SYSTEM_SET_FUNCTION,					//ϵͳ����-����
	SWITCH_FLAG_SYSTEM_SET_OTHER,						//ϵͳ����-����
	SWITCH_FLAG_RESET_JOB,								//ϴְҵ
	SWITCH_FLAG_RESET_ATTRIB_POINT,						//ϴ���Ե�
	SWITCH_FLAG_LEARNSKILL,								//����ѧϰ
	SWITCH_FLAG_REVIVE,									//ԭ�ظ���
	SWITCH_FLAG_REVIVE_FUNSTATUS,						//��״̬����
	SWITCH_FLAG_OPEN_BIAOJU,							//�����ھ�
	SWITCH_FLAG_BIAOJU_COMPETE,							//�ھ־���
	SWITCH_FLAG_REFRESH_TOP,							//ˢ�����а�
	SWITCH_FLAG_GAIN_TOPHERO_HORTATION,					//��ȡ����Ӣ�����а���
	SWITCH_FLAG_ATTACK_EXPLOIT,							//ս����ѫ�����/�һ����飩
	SWITCH_FLAG_PRACTISE_EXPLOIT,						//������ѫ�����/�һ����飩
	SWITCH_FLAG_STATEWAR_BADGE,							//��ս���£����/�һ����飩
	SWITCH_FLAG_CLOSE_NAME_SHIELDCHAR,					//�ر����������ֿ�
	SWITCH_FLAG_CLOSE_CHAT_SHIELDCHAR,					//�ر����������ֿ�
	SWITCH_FLAG_LEVELUP_BUTTON,							//������ť


	SWITCH_FLAG_ACCEDETO_FAMILY,						//�������
	SWITCH_FLAG_LEAVE_FAMILY,							//�뿪����
	SWITCH_FLAG_DEDUCT_FAMILYMANOR_UPKEEP_COST,			//ÿ��0��۳�����ׯ԰����
	SWITCH_FLAG_RETURN_FAMILYCREDIT,					//���幱�׶ȷ���
	SWITCH_FLAG_FAMILYBUILDING_LEVELUP,					//�����������彨��
	SWITCH_FLAG_BALANCEINHAND_WAGE,						//���㹤��
	SWITCH_FLAG_WEEK_BALANCEINHAND_WAGE,				//ÿ��1����㹤��
	SWITCH_FLAG_ALLOW_ADD_ENEMY,						//����������
	SWITCH_FLAG_ALLOW_ADD_BLACKLIST,					//������������
	SWITCH_FLAG_ALLOW_SWORN_BROTHER,					//������
	SWITCH_FLAG_ALLOW_MARRIAGE,							//������
	SWITCH_FLAG_ALLOW_UNMARRY,							//�������
	SWITCH_FLAG_ALLOW_ADD_FRIEND,						//�����Ϊ����
	SWITCH_FLAG_ALLOW_EMIGRATION,						//��������
	SWITCH_FLAG_ALLOW_ABDICATION,						//������λ-����
	SWITCH_FLAG_ALLOW_DEMISSION,						//�����ְ-����
	SWITCH_FLAG_ALLOW_APPOINT,							//��������-����
	SWITCH_FLAG_ALLOW_OPEN_WAGE,						//�򿪹���
	SWITCH_FLAG_ALLOW_CHANGE_ACTIVITYPOINT,				//����ı��Ծ��
	SWITCH_FLAG_CREATE_GANG,							//�������
	SWITCH_FLAG_ADD_GANG,								//������
	SWITCH_FLAG_LEAVE_GANG,								//�뿪���
	SWITCH_FLAG_TRANSFER_GANGLEADER,					//ת�ư���
	SWITCH_FLAG_ALLOW_USE_GANGTOKEN,					//����ʹ�ð������
	SWITCH_FLAG_ALLOW_FIREPOWER,						//�������-����
	SWITCH_FLAG_ALLOW_FORBID_SPEAK,						//�������-����
	SWITCH_FLAG_ALLOW_SETPRISONER,						//��������-����
	SWITCH_FLAG_ALLOW_RELEASEPROSONER,					//�����ͷ�����-����
	SWITCH_FLAG_ALLOW_USE_KINGTOKEN,					//����ʹ�ù�������
	SWITCH_FLAG_ALLOW_USE_KINGJADE,						//����ʹ����������
	SWITCH_FLAG_ALLOW_ATTACK_ZAIXIANG,					//����������
	SWITCH_FLAG_ALLOW_SEE_STATEPAGE,					//����鿴����ҳǩ
	SWITCH_FLAG_ALLOW_CREATE_FAMILYTANK,				//�������ս��
	SWITCH_FLAG_ALLOW_ADD_FAMILYTANK,					//�������ս��
	SWITCH_FLAG_ALLOW_TAKE_FAMILYTANK,					//������ȡս��


	SWITCH_FLAG_TAOYUAN_ASSOCIATION,					//��԰����
	SWITCH_FLAG_COLOR_DEER,								//�����¹
	SWITCH_FLAG_CATCH_TOKEN,							//������
	SWITCH_FLAG_GET_TOGETHER,							//����
	SWITCH_FLAG_KEJU_EXAM,								//�ƾٿ���
	SWITCH_FLAG_XINGXIAZHANGYI,							//��������
	SWITCH_FLAG_FAMILY_BUIDING,							//���彨��
	SWITCH_FLAG_FAMILY_BOSS,							//����BOSS
	SWITCH_FLAG_FAMILY_GET_TOGETHER,					//�������
	SWITCH_FLAG_DAMINGFU_ESCORT,						//����������
	SWITCH_FLAG_FAMILY_CHALLENGE,						//������ս��
	SWITCH_FLAG_YUANZHENG_STATE,						//���Զ��
	SWITCH_FLAG_HEROISLAND,								//�㽫̨
	SWITCH_FLAG_WANGCHENG_ESCORT,						//��������
	SWITCH_FLAG_FAMILY_ESCORT,							//��������
	SWITCH_FLAG_COUNTERESPIONAGE,						//�߷�
	SWITCH_FLAG_STATE_WATER,							//����ʥˮ
	SWITCH_FLAG_FAMILY_CARNIVAL,						//������껪
	SWITCH_FLAG_CITY_BARBECUE,							//���йһ�
	SWITCH_FLAG_GANG_SEIZEPOWER_WAR,					//�����ս
	SWITCH_FLAG_GUOYUN_ACTION,							//����
	SWITCH_FLAG_GUOCE_ACTION,							//����
	SWITCH_FLAG_SMALLHELP,								//С����
	SWITCH_FLAG_DAY_ACTIVITY_LIST,						//ÿ�ջ�б�
	SWITCH_FLAG_GANG_SEIZEPOER_DRAW_OCCUPYBANKROLL,		//�����ս-��ȡÿ������ռ���ʽ�
	SWITCH_FLAG_STATEWAR,								//��ս
	SWITCH_FLAG_WORSHIP,								//Ĥ��

	SWITCH_FLAG_GAIN_TOP_FLOWER_HORTATION,				//��ȡ�ʻ��������а���
	SWITCH_FLAG_GAIN_TOP_EXPLOIT_HORTATION,				//��ȡ��ѫֵ���а���
	SWITCH_FLAG_COMBINEWITHCOMBATPET,					//��ս�����
	SWITCH_FLAG_ALL_BOSS,								//BOSSˢ���ܿ���
	SWITCH_FLAG_FIXED_BOSS,								//�̶�BOSSˢ�¿���
	SWITCH_FLAG_RAND_BOSS,								//���BOSSˢ�¿���
	SWITCH_FLAG_SUPER_BOSS,								//����BOSSˢ�¿���
	SWITCH_FLAG_CHANGE_SOUL_TO_MINGHUN,					//�����л�����Ԫ

	SWITCH_FLAG_END,

};
const int SYSTEMSWITCH_ARRAY			= 256;			//���ش�С

#define EXECUTE_GMCODE_LEVEL			1


// --GMָ��ִ�а�ȫ����
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


//��Ч�ƺ�
enum EffectDesignation
{
	Effect_Designation_Begin = 20,
	Effect_Designation_MGXZ,		//õ������
	Effect_Designation_XZYM,		//������ò
	Effect_Designation_GSTX,		//��ɫ����
	Effect_Designation_JDTJ,		//�����콾
	Effect_Designation_TXDY,		//���µ�һ
	Effect_Designation_End,
};

//ͷ������ add by lfy 2012.10.7
enum HeadString_ID
{
	HeadString_StateWar = 0,		//��ս
	HeadString_FamilyChallengeA,	//������ս��A
	HeadString_FamilyChallengeB,	//������ս��B
	HeadString_GangFightAttack,		//�����ս��
	HeadString_GangFightDefence,	//�����ս��
};

//GM���߷��ؽ��
enum GMTOOL_LOGINRETURNTYPE
{
	GMTOOL_LOGINRETURNTYPE_SUCCESS  = 1,//��¼�ɹ�
	GMTOOL_LOGINRETURNTYPE_FAIL		,   //��֤ʧ��
	GMTOOL_LOGINRETURNTYPE_LOGED  ,		//GM�˺��ѵ�½
};

//DB���ظ�gm���ߵĴ�����Ϣ
enum GMTOOL_DBErrorID
{
	GMTOOL_DBError_Mail_Success = 1,	//�����ʼ��ɹ�
	GMTOOL_DBError_Mail_NoPlayer ,		//�����ʼ�ʧ��-δ�ҵ����
	GMTOOL_DBError_Mail_CreateError,	//�����ʼ�ʧ��
	GMTOOL_DBError_Radio_CreateError,	//��������ʧ��
	GMTOOL_DBError_Radio_CreateSuccess,	//��������ɹ�
	GMTOOL_DBError_ForbidSpeak_Success,	//���Գɹ�
	GMTOOL_DBError_ForbidSpeak_Error,	//����ʧ��
	GMTOOL_DBError_UnForbidSpeak_Success,	//������Գɹ�
	GMTOOL_DBError_UnForbidSpeak_Error,	//�������ʧ��
	GMTOOL_DBError_SetSystemSwitch_Success,	//�޸�ϵͳ���سɹ�
	GMTOOL_DBError_SetSystemSwitch_Error,	//�޸�ϵͳ����ʧ��
	GMTOOL_DBError_LoadScript_Success	,	//���ؽű��ɹ�
	GMTOOL_DBError_LoadScript_Error		,	//���ؽű�ʧ��
	GMTOOL_DBError_ReloadNumerical_Success		,	//�������ݱ�ɹ�
	GMTOOL_DBError_ReloadNumerical_Error		,	//�������ݱ�ʧ��
	GMTOOL_DBError_SynchRoleByUID_Sucess		,	//��UIDͬ����ɫ�ɹ�
	GMTOOL_DBError_SynchRoleByUID_Error		,	//��UIDͬ����ɫʧ��
	GMTOOL_DBError_ReviveRole_Sucess		,	//�ָ���ɫ�ɹ�
	GMTOOL_DBError_ReviveRole_Error		,	//�ָ���ɫʧ��
};

//GM����Ȩ��
enum GMTOOL_RIGHTLEVEL
{
	GMTOOL_RIGHTLEVEL_INVALID = -1,		//��Ч
	GMTOOL_RIGHTLEVEL_QUERRYLIMIT = 1,	//���ֲ�ѯȨ��
	GMTOOL_RIGHTLEVEL_QUERRYALL ,		//ȫ����ѯȨ��
	GMTOOL_RIGHTLEVEL_ALTERLIMIT ,		//�����޸�Ȩ��
	GMTOOL_RIGHTLEVEL_ALTERALL ,		//ȫ���޸�Ȩ��
	GMTOOL_RIGHTLEVEL_TOP ,				//���Ȩ��
};

//GM������������
enum GMRequireType
{
	GMRequireType_INVALID	= -1,	//��Ч
	GMRequireType_Player = 0,	//�����������
	GMRequireType_State,		//����
	GMRequireType_Gang,			//���
	GMRequireType_Family,
};

#ifdef _DATASERVER_
// �������� ת�� ��������
int G_PropAttribKeyConvertPlayerAttribKey( int nKey );
#endif

// GBK Convert UTF8		GBK ת UTF8	����ֵ�� �ַ�������
int ConvertGBKToUTF8(char* strGBK, char* strDestUTF8, int nMaxSize );
// UTF8 Convert GBK		UTF8 ת GBK	����ֵ�� �ַ�������
int ConvertUTF8ToGBK(char* strUTF8, char* strDestGBK, int nMaxSize);

//--�������룬Ĭ������
static int	g_DefaultRef =0;
