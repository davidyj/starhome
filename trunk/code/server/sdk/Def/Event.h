#pragma	  once
#include "CommData.h"
#include "utllinkedlist.h"
#include "PacketDefine.h"

//////////////////////////////////////////////////////////////////////////
//
enum Event_ID
{
	Event_INVALID			= 0,			// ��Ч�¼�
	Event_NULL,								// ���¼�
	Event_Logic_Time		= 2,			// �߼���
	Event_System_Message,					// ϵͳ��Ϣ
	Event_Create_Role,						//������ɫ
	Event_Delete_Role,						//ɾ����ɫ	
	

	//Combat
	Event_Combat_Skill_Hit	= 10,			//0:PID, 1:SkillID, 2:Damage, 3:School
	Event_Combat_Skill_Crit,				//����
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

	Event_Combat_TargetOutofRange = 26 ,	// �뿪������Χ

	Event_Combat_Kill			= 27,		// A ɱ�� B �� C�ļ���   ����˳��: B 
	Event_Combat_beKilled,					// A �� B ɱ�� ��C����	 ����˳��: B 	
	Event_Combat_Revive,					// ����
	Event_Combat_RecvDamage,				// �ܵ��˺�
	Event_Combat_Attack,
	Event_Combat_UnderAttack,
	Event_Combat_GameKill,                 //��Ϸ��ɱ
	Event_Combat_BeGameKill,               //����Ϸ��ɱ������������������ֻ�ǵ��أ�
	

	Event_Combat_Effect_UnSet	= 50,		// ж��Ч��
	Event_Combat_Effect_OnSet,				// ����Ч������

	Event_Combat_Skill_HolyStrike= 80,		// ����һ��
	Event_Combat_Skill_GetHolyStrike,

	Event_Combat_Effect_HolyStrike,
	Event_Combat_Effect_GetHolyStrike,
	Event_Combat_Effect_HpHadLittle,      //Ѫ�����ٵ�һ��ֵʱ


	//Prop
	Event_Prop_Use				= 100,		//ʹ�õ���
	Event_Prop_Get,							//�õ�����
	Event_Prop_Lost,						//�ӵ���
	Event_Prop_Equip,						//װ������
	Event_Prop_UnEquip,						//ж�ص���
	Event_Prop_Split,						//��ֵ���
	Event_Prop_Attrib_Change,               //�������Ըı�
	Event_Prop_AddGem,                      //������Ƕ
	Event_Prop_UseSkill,					//ʹ�õ��߼���
	Event_Prop_AddHole,						//���
	Event_Prop_AddStar,						//����
	Event_Prop_Move,						//�ƶ����� 
	Event_Prop_Bind,						//װ����
	Event_Prop_ByFromNPC,					//��NPC����װ��
	Event_Prop_Compose,						//�ϳɵ��ߣ������ϳɲ��Ϻͺϳ�װ��
	Event_Prop_Rebind,						//�ذ�
	Event_Prop_ReFiveElement,				//�޸�����	
	Event_Prop_Destory,						//�ݻٵ���(����DB ɾ�������Ե�)
	//Quest
	Event_Quest_Accept			= 200,		// Param1:QuestID	Param2:Player PID
	Event_Quest_Update,						
	Event_Quest_Abandon,
	Event_Quest_Complete,					// Param1:QuestID	Param2:Player PID
	Event_Quest_Start,						// ����ʼ
	Event_Quest_Stop,						// ����ֹͣ
	Event_Quest_ChildInquirer,          	// ����������
	Event_Quest_Inquirer,               	// ���Ի�����
	Event_Quest_FindNpc,
	Event_Quest_AddFriend,
	Event_Quest_AddTeam,
	Event_Quest_AddAttribute,
	Event_Quest_AddSkill,
	Event_Quest_GameStart,              	//���ʼ
	Event_Quest_GameOver,               	//�����
	Event_Quest_QuestTimeStart,
	Event_Quest_QuestTimeOver,          	//��ʱ����ʱ�䵽
	Event_Quest_MonsterGoHome,          	//����GoHome
	Event_Quest_ReadMail,					//����
	Event_Quest_AskQuestionOver,        	//�������
	Event_Quest_AskWrong,               	//�������
	Event_Quest_DragCutShort,				//�϶������
	Event_Quest_TitleAccept,				//�����������������
	Event_Quest_TitleNoComplete,			//������������δ���
	Evetn_Quest_TitleComplete,				//���������������
	Event_Quest_KillMonstlevel,				//ɱ�涨�ȼ��Ĺ�
	Event_Quest_InAutoZone,					//�������񴥷�����
	Event_Quest_CatchPet,					//����׽����
	Event_Quest_GetMidNPC,					//���񲶻��м䵥λ
	Event_Quest_LostMidNPC,					//����ʧȥ�м䵥λ
	Event_Quest_Failed,						//����ʧ��
    Event_Quest_RemoveBuff,                 // �Ƴ�buff����ʧ���¼�
	Event_Quest_KillOverlevel,				//ɱָ���ȼ����ϵĹ֣���һ������Ϊָ���ĵȼ�
	Event_Quest_KillManyMonster,			//������ɱ���ֹ֣��ĸ�����Ϊ����ID	
	Event_Quest_MiddleTalk,               	//�����м�Ի�
	Event_Quest_KillHigherMonster,          //��ɱ����������ȼ��Ĺ���
	Event_Quest_Load,						//��������
	Event_Quest_NULL,						//���¼������ڽű�����Ŀ�����
	Event_Quest_Clear,						//��������¼� add by lfy 2012.6.1
	Event_Quest_Complete_ByID,				//��������¼�������֪ͨ����������������״̬ add by lfy 2012.6.14

	//�ͻ��������������¼�
	Event_Quest_ClientOperation		= 250,		//�ͻ��˽�������¼�

	//Action
	Event_Action_Move			= 300,		//�ƶ�
	Event_Action_Stop,						//ֹͣ
	Event_Action_Arrive,					//����
	Event_Action_Blocked,					//�赲
	Event_Action_RequestMove,				//�����ƶ�
	Event_Reply_Summon,						//��Ӧ�ٻ�

	//Inquirer
	Event_Inquirer				= 400,		//��NPC�Ի� 0:NPC PID 1:InquirerID
	Event_BeInquirer,						//��Player�Ի� 0:Player PID  1:Inquirer Type 2:Inquirer ID
	Event_BeChildInquirer,              	//��Player�ӶԻ�
	Event_InquirerOver,						//�Ի������¼�
	

	//Scene
	Event_Scene_Create			= 500,		//
	Event_Scene_Delete,						//

	Event_AutoNPC_Create			= 600,		//�Զ���ʻNPC����

	Event_Player_Scene_Exit     = 700,  	//����˳�����
	Event_Player_Scene_Enter,           	//��ҽ��볡��

	Event_Add_Combat_Pet		= 800,		//����ս����
	Event_Remove_Combat_Pet,				//ɾ��ս����
	Event_CombineWithCombatPet,				//��ս�����
	Event_UnCombineWithCombatPet,			//��ս��������

	Event_Add_WaitPet			= 810,		//�ٻ��̳�



	// Login / Exit	
	Event_Player_Login			= 1001,
	Event_Player_Exit,						//����뿪��Ϸ
	Event_Player_FirstLogin,				//��ҳ��ε�½

	//Explorer
	Event_Explorer_Add			= 1100,		//����ͬ����
	Event_Explorer_Remvoe,					//�Ƴ�ͬ����

	//pet
	Event_Explorer_AddProp		= 1200,		//���߽���ͬ����
	Event_Explorer_RemoveProp,				//�����뿪ͬ����
	Event_Owner_Attack,						//�������˹�����    ����PID   ��������PID
	Event_Owner_DesAttack,					//���ﱻ����		����PID    �����˵� PID
	Event_Pet_Dead,							//����������ֻ������ս�裩 ����PID  ���������PID
	Event_Pet_Evolution,					//ǿ������
	Event_Pet_LevelUp,						//��������
	Event_Pet_AttribPoint,					//�������Ե�ı�
	Event_Pet_Refinery,						//���������¼�
	Enent_Pet_CreateFellow,					//���޴���					
	Event_Pet_Illusion,						//���޻û�
	Event_Pet_Release,						//���޷���
	Event_Pet_SealFellow,					//���޻���
	Event_Pet_Destory_SealEgg,				//�������޷�ӡ��

	//pk & prison
	Event_Change_RednameType	= 1300,		//�ı����״̬

	//Family
	Event_Family_Money			= 1400,		//�����ʽ�仯
	Event_Family_Action_Complete,			//�������
	Event_FamilyPower,						//����ְλ�仯
	Event_Family_Level,						//����ȼ��仯
	Event_Create_Family,					//��������
	Event_Change_Family,					//������˳�����
	Event_Remove_Family,					//��ɢ����
	Event_Make_Tank,						//ʹ��ս��
	Event_Return_Tank,						//�黹ս��

	//Gang
	Event_Gang_Action_Complete	= 1500,		//������
	Event_Gang_Money,						//����ʽ�仯
	Event_GangPower,						//���ְλ�仯
	Event_Gang_Level,						//���ȼ��仯
	Event_Create_Gang,						//�������
	Event_Change_Gang,						//������˳����
	Event_Remove_Gang,						//��ɢ���

	//State
	Event_State_Action_Complete	 = 1600,	//���һ���
	Event_StatePower,						//����ְλ�仯
	Event_Create_King,						//��������
	Event_Remove_King,						//������̨
	Event_NoSpeak,							//����
	Event_Prisoner,							//�ؼ���
	Event_Gantry,							//�����仯
	Event_BOSS_Update,						//BOSS����or��ʩ����
	Event_kill_BOSS,						//��ɱBOSS
	Event_Attack_State_Goal,				//����������ҪĿ��or������ҪĿ�걻����
	Event_Destroy_State_Goal,				//�ݻ��������Ĺ�����ҪĿ��or������ҪĿ�걻�ݻ�
	Event_Kill_Player,						//ɱ���й���orɱ��������

	//Team
	Event_Add_Team = 1650,
	Event_Remove_Team,

	//Private
	Event_Private_Flag			= 1700,		//���or���
	Event_Bind_Box_Top,						//�������ӵ�һ��
	Event_NotBind_Box_Top,					//���ǰ����ӵ�һ��
	Event_Private_All_Power_Top,			//�����ۺ�ʵ����һ��
	Event_Get_Cat,							//�쵽����
	Event_Flowers,							//�׻�
	Event_Make_Prop,						//����װ��
	Event_Change_Color_Name,				//���ֱ�ɫ
	Event_Add_Private_Friend,

	Event_Public				= 1800,		//ѭ������
	Event_Ad,								//ѭ�����
	Event_Open_Box,							//�����ӻ�ø߼���Ʒ
	Event_Enter_Scene,						//����ĳһ������������
	Event_Create_Kaiser,					//��Ϊ�ʵ�
	
	//�
	Event_Campaign_Start        = 1900,     //���ʼ
	Event_Campaign_Over,					//�����
	Event_Campaign_Signup,					//������ɹ�
	Event_Campaign_5MinPre,                 //������ʼǰ��ʱ
	Event_Campaign_3MinPre,                 //������ʼǰ��ʱ
	Event_Campaign_1MinPre,                 //������ʼǰ��ʱ


	//�Ʋ�����
	Event_Warehouse_Open		= 2000,		//�򿪲ֿ����
	Event_Mail_Open,						//���ʼ�����
	Event_Auction_Open,						//�������н���
	Event_Clearing_Open,					//�򿪽���������

	//����������ܣ�
	Event_Remove_ShortCutObj	=2100,		//�Ƴ�������ļ���

	//�⻷
	Event_Aura_Create			= 2200,		//�����⻷
	Event_Aura_Remove,						//�Ƴ��⻷
	//buff
	Event_Add_Buff				= 2250,		//����buff
	Event_Remove_Buff,						//�Ƴ�buff	
//����
	Event_Cast_Complete		=2300,		//��������
	Event_Cast_Break,

	//messageobx�¼�
	Event_Messagebox_Accept		= 2400,		//���ܰ�ť
	Event_Messagebox_Refuse,				//�ܾ���ť
	Event_InputBox_Accpet,					//��������
	Event_InputBox_Refuse,					//�����ܾ�

	Event_Player_Attack			= 2500,		//ս�������ķ���		A-ID	B-ID	ֵ	ʱ��	skillID
	Event_Player_Damage,					//ս���˺��ķ���		A-ID	B-ID	ֵ	ʱ��	skillID
	Event_Player_UseSkill,					//ս�����ܵ�ʹ��		A-ID	B-ID	ID	ʱ��	skillID
	

	// Player �¼�
	Event_Player_LevelUp		= 2600,			//��ɫ�ȼ��ı�
	Event_Player_ChangeJob,						//��ɫְҵ�ı�
	Event_Player_LeaveFamily,					//����뿪����
	Event_Player_LeaveGang,						//����뿪���
	Event_Player_ChangeTeam,					//��Ҹı����
	
	// Money �¼�
	Event_BindSilver_CreateCost		= 2999,			// ��Ʊ�Ĳ���������

	////////////////////////////////////////////
	//�����ڿͻ�����ʾtip���¼�,���ڽ����д�����ʹ��
	////////////////////////////////////////////

	Event_HelpTip_FindNPC       = 3000,     //��npc�б�
	Event_HelpTip_OpenMap,                  //�򿪵�ͼ
	Event_HelpTip_Repair,                   //�������
	Event_HelpTip_LvUp,                     //����
	Event_HelpTip_Sit,                      //����
	Event_HelpTip_FiveAttrib,               //5��
	Event_HelpTip_StallButton_Click,        //����ͷ���Ҽ����°�̯��
	Event_HelpTip_MakeProp,                 //����
	Event_HelpTip_BindProp,                 //��
	Event_HelpTip_FollowMagic,              //��ħ
	Event_HelpTip_ActionButton_Click,       //���������
	Event_HelpTip_AcceptCredit,             //�������
	Event_HelpTip_HonorTeam,                //�������
	Event_HelpTip_Marriage,                 //���
	Event_HelpTip_Master,                   //ʦͽ
	Event_HelpTip_DuryZero,					//ĥ��Ϊ0
	Event_HelpTip_SwitchPK,					//�л�pkģʽ
	Event_HelpTip_PickProp,					//ʰȡ����
	

	///////////////////////
	//���ڿͻ��˽����¼�
	///////////////////////
	Event_Clint_Contrl_Click=4000,			//�ؼ�������	
	Event_Drag_Prop_Cut_Start,				//������ק��ʼ
	Event_Drag_Skill_Cut_Start,				//������ק��ʼ
	Event_Dialog_Open,						//�����
	Event_Drag_Cut_End,						//��ק����������
	Event_Drag_Prop_Cut_Reback,				//��ק��;���µ��߻ر���
	Event_Bag_PropPet_Use,					//�ڱ������Ҽ�ʹ�ó������	
	Event_Role_Prop_MainEquip,				//��������װ��
	Event_DragDown_Prop,					//���µ��߿��
	Event_DragDown_Skill,					//���¼��ܿ��
	Event_Hp_DownByPer,						//��Ѫ���ڰٷֱ�
	Event_Newman_Add_Skill,					//��Ӽ���
	Event_Notice_TimeOut,					//����ر�������ʾ֪ͨ
	Event_Notice_GiftOnTime,				//�������ﵹ��ʱ�¼�
	Event_Drag_Pet_Cut_Start,				//������ק��ʼ
	Event_Notice_AddFriend,					//��Ӻ���
	Event_Notice_AddTeam,					//�������
	Event_Notice_AddFamily,					//�������
	Event_Notice_AddGang,					//������
	Event_Hp_DownByFel,                     //���޵�Ѫ�ٷֱ�
	Event_Put_Prop_Inter_NewStar,           //���¹ⱦ��װ������ҳǩ�м���߿�������
	Event_Put_Prop_Inter_NewBind,           //���¹ⱦ��װ����ҳǩ�м���߿�������
	Event_Put_Prop_TopR_NewBind,            //���¹ⱦ�а�װ��ҳǩ���Ͻǵ��߿�������
	Event_Quest_AchiveTarget,				//������
	Event_Newman_UseSkill,					//ʹ�ü���
	Event_Newman_ExpTopLimit,				//��ǰ�ȼ���������
	Event_Newman_PetLevelUp,				//���������¼�
	Event_Newman_NewStarPutStone,			//�¹ⱦ���з��뱦ʯ
	Event_Newman_PetSummon,					//�����ٻ��¼�
	Event_Newman_QuestTrackClick,			//����׷�����ӵ���¼�
	Event_Newman_QuestLogClick,				//������־���ӵ���¼�
	Event_Newman_AttribAdd,				    //�����Ե��¼�
	Event_Newman_OnRide,					//�����¼�
	Event_Newman_EnergyAvailable,			//���������¼�
	Event_Newman_PutEquipCombine_Center,	//���ϻ�м���ӷ���װ��		
	Event_Newman_PutEquipCombine_Around,	//���ϻ��Χ���ӷ���װ��
	Event_PetUI_Strenthen_PutPet,			//����ǿ�������������
	Event_PetUI_Strenthen_PutStone,			//����ǿ�������������
	Event_Pet_LowHappy,						//���޿��ֶȵ��ڰٷֱ�
	Event_EarthSoulButton_Click,			//Ԫ������ɷ��ť����¼�
	Event_Newman_BattleCredit,				//ս����ѫ�����¼�
	Event_Newman_RageMax,					//����ֵ���¼�
	Event_Dialog_Release,					//����ر��¼�
	Event_Newman_Wage,						//��ü��幤���¼�
	Event_Newman_MaterialInput,				//���ϻ�������
	Event_Newman_FamilyCredit,				//��ü��幱���¼�
	Event_Newman_OpenBag,				    //�򿪱���
	// ����
	Event_Exchange_Success = 5000,					//���׳ɹ�
	Event_Exchange_Prop,					//���֮�佻��
	//��̯
	Event_Stall_Begin = 5500,				//��ʼ��̯
	Event_Stall_Exchange_Count,				//��̯������ɴ���

	//װ������ϳ�
	Event_ExecuteAddStar = 5800,			//���д���
	Event_ExecuteMatrialCompose,			//���в��Ϻϳ�
	Event_ExecuteEquipCompose,				//����װ���ϳ�

	//��Ǯ
	Event_BindSilver = 6000,				//��Ǯ�䶯
	Event_Silver,					//�ǰ�Ǯ�䶯

	Event_Drag_FacePicture_Start = 6100,		//  ͼƬ��ק��ʼ

	//Mail
	Event_Quest_SendMail = 6500,			//�������ʼ�
	Event_Quest_Deletemail,                 //����ɾ���ʼ�  
	Event_Quest_GetMail_Accessories,        //������ȡ�ʼ�����

	Event_Succeed_SendMail,                 //�����ʼ��ɹ�
	Event_Succeed_Deletemail,               //ɾ���ʼ��ɹ�  
	Event_Succeed_GetMail_Accessories,      //��ȡ�ʼ������ɹ�

	//Monitor�¼�
	Event_Monitor_CreateProp,				// ���Ӵ��������¼�
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
	PersonID	m_nPID;					// �����¼�����
	SCENEID		m_nSceneID;				// 	
	int64		m_nParam[6];
	char		m_szParam[SHORT_STRING_LEN];			//
	BOOL		m_bUpdateDB;
	BOOL		m_bIsUsing;				//--���ڴ��Ƿ����ڱ�ʹ��--
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
