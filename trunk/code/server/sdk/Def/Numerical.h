
//////////////////////////////////////////////////////////////////////////
//���ݿ������
enum Numerical
{
	//////////////////�������Լ�װ������////////////////////////////////////
	Num_Begin = 0,
	Num_Init_Waigong = 1,			//��ʼ�⹦
	Num_Init_Shenfa,				//��ʼ��
	Num_Init_Neigong,				//��ʼ�ڹ�
	Num_Init_Zhenqi,				//��ʼ����
	Num_Init_Jingu,					//��ʼ���
	Num_Init_Level,					//��ʼ�ȼ�
	Num_Init_Exp,					//��ʼ����
	Num_Init_Hp,					//��ʼ����ֵ
	Num_Init_Mp,					//��ʼħ��ֵ
	Num_Init_Runspeed,				//��ʼ�ƶ��ٶ�
	Num_Init_HpRegen_ClassOne,		//�����ָ��ٶ�
	Num_Init_HpRegen_ClassTwo,
	Num_Init_HpRegen_ClassThree,
	Num_Init_HpRegen_ClassFour,
	Num_Init_MpRegen_ClassOne,		//ħ���ָ��ٶ�
	Num_Init_MpRegen_ClassTwo,
	Num_Init_MpRegen_ClassThree,
	Num_Init_MpRegen_ClassFour,

	Num_LevelUp_Hp = 20,			//������������ֵ
	Num_LevelUp_Mp,					//��������ħ��ֵ
	Num_LevelUp_AttribPoint,		//�����������Ե�
	Num_LevelUp_SkillPoint,			//�����������ܵ�

	Num_AffectByWG_PhysicalDamage = 30,	//�����������˺�������
	Num_AffectByWG_SpellDamage,			//������ħ���˺�������
	Num_AffectByWG_PhysicalArmor,		//�������������������
	Num_AffectByWG_SpellArmor,			//������ħ������������
	Num_AffectByWG_Hp,					//����������ֵ������
	Num_AffectByWG_Mp,					//������ħ��ֵ������
	Num_AffectByWG_Crit,				//�����Ա���������
	Num_AffectBySF_PhysicalDamage,		//���ݶ������˺�������
	Num_AffectBySF_SpellDamage,			//���ݶ�ħ���˺�������
	Num_AffectBySF_PhysicalArmor,		//���ݶ��������������    
	Num_AffectBySF_SpellArmor,			//���ݶ�ħ������������
	Num_AffectBySF_Hp,					//���ݶ�����ֵ������
	Num_AffectBySF_Mp,					//���ݶ�ħ��ֵ������
	Num_AffectBySF_Crit,				//���ݶԱ���������
	Num_AffectByNG_PhysicalDamage,		//�����������˺�������
	Num_AffectByNG_SpellDamage,			//������ħ���˺�������
	Num_AffectByNG_PhysicalArmor,		//�������������������
	Num_AffectByNG_SpellArmor,			//������ħ������������
	Num_AffectByNG_Hp,					//����������ֵ������
	Num_AffectByNG_Mp,					//������ħ��ֵ������
	Num_AffectByNG_Crit,				//�����Ա���������
	Num_AffectByZQ_PhysicalDamage,		//����������˺�������
	Num_AffectByZQ_SpellDamage,			//�����ħ���˺�������
	Num_AffectByZQ_PhysicalArmor,		//������������������
	Num_AffectByZQ_SpellArmor,			//�����ħ������������
	Num_AffectByZQ_Hp,					//���������ֵ������
	Num_AffectByZQ_Mp,					//�����ħ��ֵ������
	Num_AffectByZQ_Crit,				//����Ա���������
	Num_AffectByJG_PhysicalDamage,		//���ʶ������˺�������
	Num_AffectByJG_SpellDamage,			//���ʶ�ħ���˺�������
	Num_AffectByJG_PhysicalArmor,		//���ʶ��������������
	Num_AffectByJG_SpellArmor,			//���ʶ�ħ������������
	Num_AffectByJG_Hp,					//���ʶ�����ֵ������
	Num_AffectByJG_Mp,					//���ʶ�ħ��ֵ������
	Num_AffectByJG_Crit,				//���ʶԱ���������
	Num_AffectByLevel_Damage,			//�ȼ��Թ�����������
	Num_AffectByLevel_Armor,			//�ȼ��Է�����������
	Num_Bind_Max_Money,					//�󶨵�����Ǯ��
	Num_Not_Bind_Max_Money,				//�ǰ󶨵�����Ǯ��

	Num_Wave_Value = 70,				//ȡֵ����
	Num_Wave_Precent,					//ȡ��������
	NUM_DamageArea_Precent,				//Ⱥ���İٷֱȼ���
	Num_Damage_Percent_Max,				//ÿ�ι�������ҵ�����˺��ٷֱȣ���Ŀ���Ѫ�����ֵ�İٷֱȣ����������������
	Num_Energy_Regen,					//����ֵÿ�ջظ�

	Num_PropAttrib_ClassOne = 80,		//װ�������ֵѡȡϵ��
	Num_PropAttrib_ClassTwo,
	Num_PropAttrib_ClassThree,
	Num_PropAttrib_ClassFour,

	Num_Coefficient_DoubleHand = 90,	//װ��λ�õ�ѡȡϵ��
	Num_Coefficient_SingleHand,
	Num_Coefficient_Shield,
	Num_Coefficient_Ring,
	Num_Coefficient_Necklack,
	Num_Coefficient_Helm,
	Num_Coefficient_Chest,
	Num_Coefficient_Belt,
	Num_Coefficient_Boot,
	Num_Coefficient_Bracer,

	Num_Coefficient_DoubleResist = 110,	//˫��װ����ϵ��

	Num_Coefficient_White = 120,		//װ��Ʒ�ʵ�ѡȡϵ��
	Num_Coefficient_Green,
	Num_Coefficient_Blue,
	Num_Coefficient_Purple,
	Num_Coefficient_Gold,
	Num_Coefficient_PerfectGold,
	Num_Coefficient_LegendGold,		    //��˵��

	Num_PreName_Purple = 130,			//��ɫ�ͽ�ɫװ��ǰ׺������
	Num_PreName_Gold1,
	Num_PreName_Gold2,

	Num_Coefficient_BlueEffect_ClassOne = 140,		//��װЧ��
	Num_Coefficient_BlueEffect_ClassTwo,
	Num_Coefficient_BlueEffect_ClassThree,
	Num_Coefficient_BlueEffect_ClassFour,

	Num_Coefficient_GreenEffect = 150,	//װ��Ч����������
	Num_Coefficient_CyanEffect,
	Num_Coefficient_PurpleEffect,
	Num_Coefficient_ActiveEffect1,		
	Num_Coefficient_ActiveEffect2,
	Num_Coefficient_ActiveEffect3,
	Num_Coefficient_ZhanhunEffect,

	Num_PropRepeatBind_Attr1 = 160,		//�ذ���������(4������)
	Num_PropRepeatBind_Attr2,			
	Num_PropRepeatBind_Attr3,			
	Num_PropRepeatBind_Attr4,			
	
	Num_PropSign_Attr = 170,			//ǩ����������
	Num_PropBind_Attr,					//����������

	Num_PropStar_Attr1 = 200,			//������������
	Num_PropStar_Attr2,
	Num_PropStar_Attr3,
	Num_PropStar_Attr4,
	Num_PropStar_Attr5,
	Num_PropStar_Attr6,
	Num_PropStar_Attr7,
	Num_PropStar_Attr8,
	Num_PropStar_Attr9,
	Num_PropStar_Attr10,
	Num_PropStar_Attr11,
	Num_PropStar_Attr12,
	Num_PropStar_Attr13,
	Num_PropStar_Attr14,
	Num_PropStar_Attr15,
	Num_PropStar_Attr16,
	Num_PropStar_Attr17,
	Num_PropStar_Attr18,
	Num_PropStar_Attr19,
	Num_PropStar_Attr20,
	Num_PropStar_Attr21,
	Num_PropStar_Attr22,
	Num_PropStar_Attr23,
	Num_PropStar_Attr24,
	Num_PropStar_Attr25,
	Num_PropStar_Attr26,
	Num_PropStar_Attr27,
	Num_PropStar_Attr28,
	Num_PropStar_Attr29,
	Num_PropStar_Attr30,

	Num_Repair_Cost = 250,				//ÿ�����ӿ�������;ö�
	Num_AutoRepairPropCost		= 252,	//�Զ�����װ����������

	Num_EquipEffect_RandomMax = 260,	// װ���������Ʒ��λ�����ֵ(0-400)
	Num_EquipEffect_White_Param,		// ��Ʒ�����Ч����Ʒ��ϵ��
	Num_EquipEffect_Green_Param,
	Num_EquipEffect_Blue_Param,
	Num_EquipEffect_Purple_Param,
	Num_EquipEffect_Gold_Param,
	Num_EquipEffect_White_Range,		// ��Ʒ��ȡ���Ч���������ֵ
	Num_EquipEffect_Green_Range,
	Num_EquipEffect_Blue_Range,
	Num_EquipEffect_Purple_Range,
	Num_EquipEffect_Gold_Range,
	Num_EquipEffect_LegendGold_Param,	//��˵��
	Num_EquipEffect_LegendGold_Range,

	Num_PropBind_Cost = 280,			//���߰�ԭ���� 
	Num_PropSign_Cost,					//����ǩ��ԭ���� 
	Num_PropAddStar_Cost,				//װ������ԭ����
	Num_PropCompose_Cost,				//װ���ϳ�ԭ����
	Num_MaterialCompose_Cost,			//���Ϻϳ�ԭ����
	Num_PropAddHole_Cost,				//װ�����ԭ����
	Num_PropAddGem_Cost,				//װ����Ƕԭ����
	Num_PropUnGem_Cost,					//װ����ʯ����
	Num_PropRepeatBind_Cost,			//װ���ذ����
	Num_PropUnAddStar_Cost,				//װ�����Ƿ���
	Num_PropRepeatStar_Cost,			//װ�����Ƿ���
	Num_PropZhanHun_Cost,				//��������޸ķ���
	Num_PropFiveElements_Cost,			//�޸����з���
	Num_PropUnGem_Fail,					//��ʯʧ����
	Num_PropUnAddStar_Fail,				//����ʧ����


	Num_Fellow_Grown_Radix = 300,		//�ɳ�����
	Num_Fellow_Grown_RadixValue,		//�ɳ���ֵ
	Num_Fellow_Aptitude_Radix,			//���ʻ���
	Num_Fellow_Rebirth_Cost,			//�������Ѳ���
	Num_Fellow_Refinery_Exp,			//�����������
	Num_Fellow_Prop_Feed_Val,			//����ιʳ�һ�����
	Num_Fellow_SkillID_Num,				//������ܸ�������

	Num_Fellow_WhiteApt_Min,					//��ɫ���ʵ���С����
	Num_Fellow_WhiteApt_Max,					//��ɫ���ʵ�������

	Num_Fellow_GreenApt_Min,					//��ɫ���ʵ���С����
	Num_Fellow_GreenApt_Max,					//��ɫ���ʵ�������

	Num_Fellow_BlueApt_Min,						//��ɫ���ʵ���С����
	Num_Fellow_BlueApt_Max,						//��ɫ���ʵ�������

	Num_Fellow_PurpleApt_Min,					//��ɫ���ʵ���С����
	Num_Fellow_PurpleApt_Max,					//��ɫ���ʵ�������

	Num_Fellow_GoldApt_Min,						//��ɫ���ʵ���С����
	Num_Fellow_GoldApt_Max,						//��ɫ���ʵ�������
	Num_Fellow_AddUseableAttribPoint,			//ÿ���������ӵ����Ե�
	
	Num_Fellow_SkillFusion_Cost_Changeless,     //�����ںϹ̶�������
	Num_Fellow_SkillFusion_Cost_BindSkill,      //�����ںϰ󶨼���������

	Num_Fellow_Evolution_BaseCost,				//����ǿ��ԭ����
	Num_Ride_Evolution_BaseCost,				//���ǿ������

	Num_Fellow_PhysicalDamage,					// ��������������������
	Num_Fellow_SpellDamage,						// ������������ħ��������
	Num_Fellow_PhysicalArmor,					// ���������������������
	Num_Fellow_SpellArmor,						// ���޾�������ħ��������
	Num_Fellow_Hp,								// ����������������ֵ��
	Num_Fellow_Crit,							// �����������ӱ����ȼ���
	Num_Fellow_UpLevelExpIsMasterExp_Twentieth,	//������������Ϊ���˾���Ķ�ʮ��֮һ

	Num_Gem_Buff_Poison	= 400,					//��ʯЧ����ӵ��ж�Buff��ȡ����ֵͬ��Ҫ��1000��
	Num_Gem_Buff_Ablepsia,						//��ʯЧ����ӵ�ʧ��Buff��ȡ����ֵͬ��Ҫ��1000��
	Num_Gem_Buff_Freeze,						//��ʯЧ����ӵı���Buff��ȡ����ֵͬ��Ҫ��1000��
	Num_Gem_Buff_Burn,							//��ʯЧ����ӵ�����Buff��ȡ����ֵͬ��Ҫ��1000��
	Num_Gem_Buff_Stun,							//��ʯЧ����ӵ�ѣ��Buff��ȡ����ֵͬ��Ҫ��1000��
	Num_Gem_Buff_Slow,							//��ʯЧ����ӵļ���Buff��ȡ����ֵͬ��Ҫ��1000��
	Num_Gem_Buff_Immobilize,					//��ʯЧ����ӵĶ���Buff��ȡ����ֵͬ��Ҫ��1000��
	Num_Gem_Buff_Confuse,						//��ʯЧ����ӵĻ���Buff��ȡ����ֵͬ��Ҫ��1000��
	Num_Gem_Buff_Slience,						//��ʯЧ����ӵĳ�ĬBuff��ȡ����ֵͬ��Ҫ��1000��

	Nun_Suit_Level_1_Damage = 450,				//�׼���ֵΪ��1��ʱ�����ӹ�����%
	Nun_Suit_Level_1_Armor,						//�׼���ֵΪ��1��ʱ�����ӷ�����%
	Nun_Suit_Level_1_DamageIncrease,			//�׼���ֵΪ��1��ʱ�������˺�%

	Nun_Suit_Level_2_Damage = 460,				//�׼���ֵΪ��2��ʱ�����ӹ�����%
	Nun_Suit_Level_2_Armor,						//�׼���ֵΪ��2��ʱ�����ӷ�����%
	Nun_Suit_Level_2_DamageIncrease,			//�׼���ֵΪ��2��ʱ�������˺�%

	Num_PropStar_Success1 = 500,				//���ǳɹ���
	Num_PropStar_Success2,				
	Num_PropStar_Success3,
	Num_PropStar_Success4,
	Num_PropStar_Success5,
	Num_PropStar_Success6,
	Num_PropStar_Success7,
	Num_PropStar_Success8,
	Num_PropStar_Success9,
	Num_PropStar_Success10,
	Num_PropStar_Success11,
	Num_PropStar_Success12,
	Num_PropStar_Success13,
	Num_PropStar_Success14,
	Num_PropStar_Success15,
	Num_PropStar_Success16,
	Num_PropStar_Success17,	
	Num_PropStar_Success18,
	Num_PropStar_Success19,
	Num_PropStar_Success20,
	Num_PropStar_Success21,
	Num_PropStar_Success22,
	Num_PropStar_Success23,
	Num_PropStar_Success24,
	Num_PropStar_Success25,
	Num_PropStar_Success26,
	Num_PropStar_Success27,
	Num_PropStar_Success28,
	Num_PropStar_Success29,
	Num_PropStar_Success30,
	
	Num_PropStar_Fail = 550,		//����ʧ�ܺ�����������
	Num_PropStar_Fail1,
	Num_PropStar_Fail2,
	Num_PropStar_Fail3,
	Num_PropStar_Fail4,
	Num_PropStar_Fail5,
	Num_PropStar_Fail6,
	Num_PropStar_Fail7,
	Num_PropStar_Fail8,
	Num_PropStar_Fail9,
	Num_PropStar_Fail10,
	Num_PropStar_Fail11,
	Num_PropStar_Fail12,
	Num_PropStar_Fail13,
	Num_PropStar_Fail14,
	Num_PropStar_Fail15,
	Num_PropStar_Fail16,
	Num_PropStar_Fail17,
	Num_PropStar_Fail18,
	Num_PropStar_Fail19,
	Num_PropStar_Fail20,
	Num_PropStar_Fail21,
	Num_PropStar_Fail22,
	Num_PropStar_Fail23,
	Num_PropStar_Fail24,
	Num_PropStar_Fail25,
	Num_PropStar_Fail26,
	Num_PropStar_Fail27,
	Num_PropStar_Fail28,
	Num_PropStar_Fail29,

	Num_PropCompose_Success = 600, //װ���ϳ� �ɹ���

	Num_YearWineBox_BindParam = 700,
	Num_Data_End,

	//////////////////ϵͳ����////////////////////////////////////
	//dbserver����
	DB_Param_ID_Logic_Time_LoginQueue = 1000,	//�Ŷ��߼�ʱ��
	DB_Param_ID_Logic_Time_UserMgr,				//UserMgr�߼�ʱ��
	DB_Param_ID_Logic_Time_PlayerMgr,			//PlayerMgr�߼�ʱ��
	DB_Param_ID_Logic_Time_FamilyMgr,			//����������߼�ʱ��
	DB_Param_ID_Logic_Time_GangMgr,				//���������߼�ʱ��
	DB_Param_ID_Logic_Time_AuctionMgr,			//�������߼�ʱ��
	DB_Param_ID_Logic_Time_ClearingMgr,			//��ҽ������߼�ʱ��
	DB_Param_ID_Logic_Time_MailMgr,				//MailMgr�߼�ʱ��
	DB_Param_ID_Logic_Time_PropMgr,				//PropMgr�߼�ʱ��
	DB_Param_ID_Player_Quit_Time,				//DB������ҵ�ʱ��	
	DB_Param_ID_Logic_Time_Player_Quest,
	DB_Param_ID_Logic_Time_Player_Private,
	DB_Param_ID_Logic_Time_SaveEventItem,		//SaveEventItem Logic Time
	DB_Param_ID_Logic_Time_LoadNumerical,		//��ȡ��ֵ��
	DB_Param_ID_Logic_Time_PlayerCampaign,		//��һ�������߼�ʱ��
	DB_Param_End,

	//communityserver����
	Community_Param_ID_Logic_Time_PlayerMgr	= 1100,			
	Community_Param_ID_Logic_Time_TeamMgr,
	Community_Param_ID_Logic_Time_FamilyMgr,
	Community_Param_ID_Player_SendPacket_Limit,
	Community_Param_End,

	//loginserver����
	Login_Param_ID_Logic_Time_UserMgr = 1200,
	Login_Param_ID_Logic_Time_LoginQueue,
	Login_Param_End,

	//dataserver����
	Data_Param_ID_Logic_Time_PlayerMgr = 1300,	//PlayerMgr�߼�ʱ��
	Data_Param_ID_Logic_Time_FamilyMgr,			//����������߼�ʱ��
	Data_Param_ID_Logic_Time_GangMgr,			//���������߼�ʱ��
	Data_Param_ID_Logic_Time_AuctionMgr,		//�������߼�ʱ��
	Data_Param_ID_Logic_Time_ClearingMgr,		//��ҽ������߼�ʱ��
	Data_Param_ID_Logic_Time_MailMgr,			//MailMgr�߼�ʱ��
	Data_Param_ID_Logic_Time_PropMgr,			//PropMgr�߼�ʱ��
	Data_Param_ID_Logic_Time_TeamMgr,			//TeamMgr �߼�ʱ��
	Data_Param_ID_Logic_Time_QuestMgr,			//�����߼�ʱ��
	Data_Param_ID_Logic_Time_QuestionMgr,		//�����߼�ʱ��
	Data_Param_ID_Logic_Time_God,				//God�߼�ʱ��
	Data_Param_ID_Logic_Time_SceneMgr,			//SceneMgr �߼�
	Data_Param_ID_Logic_Time_Player_Attrib,
	Data_Param_ID_Logic_Time_Player_Status,
	Data_Param_ID_Logic_Time_Player_Buff,
	Data_Param_ID_Logic_Time_Player_AI,
	Data_Param_ID_Logic_Time_Player_Quest,
	Data_Param_ID_Logic_Time_Player_PK,
	Data_Param_ID_Logic_Time_Player_Skill,
	Data_Param_ID_Logic_Time_Player_Bag,
	Data_Param_ID_Logic_Time_Player_Explorer,
	Data_Param_ID_Logic_Time_Player_Event,
	Data_Param_ID_Logic_Time_Player_Command,
	Data_Param_ID_Logic_Time_Player_Hp_Mp,		//���Hp Mp�ָ��ٶ�
	Data_Param_ID_Logic_Time_Player_Campaign,	//��������߼��ٶ�
	Data_Param_ID_Logic_Time_PlayerMgr_NPC,		//NPC���߼�ʱ����
	Data_Param_ID_Logic_Time_Person_AI,			//Person AI�߼�
	Data_Param_ID_Logic_Time_Person_Status,
	Data_Param_ID_Logic_Time_Person_Buff,


	Data_Param_ID_Player_Count_Limit = 1400,	//��������������
	Data_Param_ID_Player_SendPacket_Limit,		//��ҷ��ͻ�����Packet����������,�����˾�ǿ���ж�����
	Data_Param_ID_Explorer_Player_Count_Max,	//ͬ����������������ֵ
	Data_Param_ID_Team_Postion_Syncho,			//�����Աλ��ͬ��Ƶ��
	Data_Param_ID_Prop_Disappear_Time,			//���ϵĵ�����ʧ��ʱ��
	Data_Param_ID_Prop_Protect_Time,			//���ϵĵ����ܱ�����ʱ��
	Data_Param_End,


	Param_ID_Event_Item_1 = 1500,
	Param_ID_Event_Item_2,
	Param_ID_Event_Item_3,
	Param_ID_Event_Item_4,
	Param_ID_Event_Item_5,
	Param_ID_Event_Item_6,
	Param_ID_Event_Item_7,
	Param_ID_Event_Item_8,
	Param_ID_Event_Item_9,
	Param_ID_Event_Item_10,
	Param_ID_Event_Item_11,
	Param_ID_Event_Item_12,
	Param_ID_Event_Item_13,
	Param_ID_Event_Item_14,
	Param_ID_Event_Item_15,
	Param_ID_Event_Item_16,
	Param_ID_Event_Item_17,
	Param_ID_Event_Item_18,
	Param_ID_Event_Item_19,
	Param_ID_Event_Item_20,
	Param_ID_Event_Item_21,
	Param_ID_Event_Item_22,
	Param_ID_Event_Item_23,
	Param_ID_Event_Item_24,
	Param_ID_Event_Item_25,
	Param_ID_Event_Item_26,
	Param_ID_Event_Item_27,
	Param_ID_Event_Item_28,
	Param_ID_Event_Item_29,
	Param_ID_Event_Item_30,
	Param_ID_Event_Item_31,
	Param_ID_Event_Item_32,
	Param_ID_Event_Item_33,
	Param_ID_Event_Item_34,
	Param_ID_Event_Item_35,
	Param_ID_Event_Item_36,
	Param_ID_Event_Item_37,
	Param_ID_Event_Item_38,
	Param_ID_Event_Item_39,
	Param_ID_Event_Item_40,
	Param_ID_Event_Item_41,
	Param_ID_Event_Item_42,
	Param_ID_Event_Item_43,
	Param_ID_Event_Item_44,
	Param_ID_Event_Item_45,
	Param_ID_Event_Item_46,
	Param_ID_Event_Item_47,
	Param_ID_Event_Item_48,
	Param_ID_Event_Item_49,
	Param_ID_Event_Item_50,
	Param_ID_Event_End,


	//////////////////���ϵͳ����////////////////////////////////////
	Community_Param_LevelIncrease = 2000,	//���ϵͳ������������

	//��Ӳ���
	Community_Param_ExpAdd = 2100,			//����ֵ�ӳɱ���
	Community_Param_TeamPersonNum,			//������������
	Community_Param_SpeDistribute,			//����������

	//ʦͽ����
	Community_Param_MasterLevel = 2200,		//��ͽ����
	Community_Param_ChildLevel,				//��ʦ����
	Community_Param_GrowSync,				//ͬ���ɳ�
	Community_Param_ChildNum,				//������ͽ��
	Community_Param_ChildLevel_Max,			//��ʦ���𣨳����˼����ܰ�ʦ��

	//���Ѳ���
	Community_Param_Friendliness = 2300,	//�Ѻö�
	Community_Param_FriednlinessIncrease,	//�Ѻö������ٶ�

	//�������
	Community_Param_FamilyLevel = 2400,			//����ȼ�
	Community_Param_CreateFamilyLevel,			//���崴������
	Community_Param_FamilyNameCount,			//�����������ֵĳ���
	Community_Param_AddFamilyLevel,				//���뼶������
	Community_Param_CreateFamilyCost,			//���崴���ʽ�
	Community_Param_ChangeFamilyMoney,			//ת��Ϊ�����ʽ�
	Community_Param_InitFamilyActive,			//���己�ٶȳ�ʼֵ
	Community_Param_FamilyActive,				//���己�ٶȱ�ֵ
	Community_Param_FamilyMemberCount,			//����������ֵ
	Community_Param_FamilyLevelCost,			//�����������Ѽ����ʽ�ı�ֵ
	Community_Param_FamilySkillLevle,			//���弼�ܵȼ�
	Community_Param_FamilySkillResearchCost,	//���弼���о����ļ����ʽ��ֵ
	Community_Param_FamliySkillLearnCost,		//���弼��ѧϰ���Ĺ��׶ȱ�ֵ
	Community_Param_FamilyMoney1,				//������1
	Community_Param_FamilyMoney2,				//������2
	Community_Param_FamilyCredit1,				//������1��ù��׶�
	Community_Param_FamilyCredit2,				//������2��ù��׶�
	Community_Param_FamilyDownActive,			//���彵���ٶȱ�ֵ
	Community_Param_FamilyUpdateActiveMember,	//���ٶ������������������
	Community_Param_FamilyUpdateActive,			//�����������߷��ٶ���������
	Community_Param_FamilyIpdateActiveTime,		//����Сʱ����һ�η��ٶ�
	Community_Param_FamilyCar_MakeMoney,		//�������ս����Ҫ���ѵĸ����ʽ�
	Community_Param_FamilyCar_FixMoney,			//�������ս����Ҫ���ѵļ����ʽ�10��n��
	Community_Param_FamilyCar_BAIHU_ID,			//�׻���id
	Community_Param_FamilyCar_QINGLONG_ID,		//������id
	Community_Param_FamilyCar_QILIN_ID,			//���복id
	Community_Param_FamilyActive_Rate,			//���己�ٶȱ���
	Community_Param_FamilyMemberCount_Rate,		//������������	
	Community_Param_FamilyLevelCost_Rate,		//�����������Ѽ����ʽ�ı���
	Community_Param_FamilySkillResearchCost_Rate,//�����о��������ļ����ʽ����
	Community_Param_FamilySkillLearCost_Rate,	//����ѧϰ�������Ĺ��׶ȱ���
	Community_Param_FamilyApplySceneMoney,		//�������ׯ԰���ѵļ����ʽ�
	//���彨���������--�;ö�
	Community_Param_FamilyJuYiTingWear,			//����������;ö�
	Community_Param_FamilyZhaiBaseWear,			//����լ�����;ö�		
	Community_Param_FamilyCarHouseWear,			//����ս�����;ö�				
	Community_Param_FamilyWuGuangWear,			//��������;ö�
	Community_Param_FamilyYanJiuSuoWear,		//�����о����;ö�
	Community_Param_FamilyGoldStorageWear,		//�������;ö�
	Community_Param_FamilyStorageWear,			//����ֿ��;ö�
	Community_Param_FamilyYeLianFangWear,		//����ұ�����;ö�
	Community_Param_FamilyJianTaWear,			//��������;ö�
	
	Community_Param_FamilyJuYiTingMaxHp,		//������������Ѫ��
	Community_Param_FamilyZhaiBaseMaxHp,		//����լ�������Ѫ��	
	Community_Param_FamilyCarHouseMaxHp,		//����ս�������Ѫ��			
	Community_Param_FamilyWuGuangMaxHp,			//����������Ѫ��
	Community_Param_FamilyYanJiuSuoMaxHp,		//�����о������Ѫ��
	Community_Param_FamilyGoldStorageMaxHp,		//���������Ѫ��
	Community_Param_FamilyStorageMaxHp,			//����ֿ����Ѫ��
	Community_Param_FamilyYeLianFangMaxHp,		//����ұ�������Ѫ��
	Community_Param_FamilyJianTaMaxHp,			//����������Ѫ��

	Community_Param_FamilyBuildingWeiHuValue,			//����ά����ϵ��
	Community_Param_FamilyBuildingJianSheDuA,			//���彨���A
	Community_Param_FamilyBuildingJianSheDuB,			//���彨���B

	Community_Param_FamilyUpKeepCost,					//����ÿ��ά���ѻ���
	Community_Param_FamilyBuildingUpgradeCostA,			//A����������������
	Community_Param_FamilyBuildingUpgradeCostB,			//B����������������

	Community_Param_FamilyJuYiTingMaxLevel,				//���������ȼ�
	Community_Param_FamilyGoldStorageMaxLevel,			//���������ȼ�
	Community_Param_FamilyZhaiBaseMaxLevel,			//����լ�������ȼ�
	Community_Param_FamilyFightCarHouseMaxLevel,	//����ս�������ȼ�
	Community_Param_FamilyYanJiuSuoMaxLevel,		//�о������ȼ�
	Community_Param_FamilyWuGuanMaxLevel,			//����������ȼ�
	Community_Param_FamilyStorageMaxLevel,			// ����ֿ����ȼ�
	Community_Param_FamilyYeLianFangMaxLevel,		//ұ�������ȼ�
	Community_Param_FamilyJianTaMaxLevel,			//����������ȼ�

	//������
	Community_Param_CreateGangPersonNum = 2500,		//��ᴴ������Ҫ��
	Community_Param_CreateGangCost,					//������������ʽ�
	Community_Param_GangCreateCD,					//���������Ҫcd
	Community_Param_GangMasterLeaveTime,			//�������ʱ��
	Community_Param_GangExitPunish,					//�˻ṱ�׶ȳͷ���
	Community_Param_GangExitCD,						//�����Ƴ���ȴʱ��
	Community_Param_GangActiveStandard,				//����׼���ٶ�1
	Community_Param_GangActiveDecrease1,			//��ᷱ�ٶȼ�����1
	Community_Param_GangActiveDecrease2,			//��ᷱ�ٶȼ�����2
	Community_Param_GangActiveDecrease3,			//��ᷱ�ٶȼ�����3
	Community_Param_GangActiveDecrease4,			//��ᷱ�ٶȼ�����4
	Community_Param_GangActiveDecrease5,			//��ᷱ�ٶȼ�����5
	Community_Param_GangContributionPercent,		//���׶ȵĲ�������
	Community_Param_GangCapacity1,					//�������1
	Community_Param_GangCapacity2,					//�������2
	Community_Param_GangCapacity3,					//�������3
	Community_Param_GangCapacity4,					//�������4
	Community_Param_GangCapacity5,					//�������5
	Community_Param_GangDismissTime,				//����ɢʱ��
	Community_Param_GangSkillResearchCost,			//��Ἴ���о�����1
	Community_Param_GangSkillLearnCost,				//��Ἴ��ѧϰ����1
	Community_Param_GangUpdateLevelCost,			//��������ʽ�����1
	Community_Param_GangActiveInit,					//����ʼ���ٶ�

	//////////////////���ܲ���////////////////////////////////////
	//�ʼ�ϵͳ
	Mail_Param_Cost = 3000,							//�ʼ���������
	Mail_Param_PropCost,							//�����ʼ�����
	Mail_Param_MaxNum,								//�ʼ��洢��
	Mail_Param_Time,								//�ʼ��洢ʱ��
	Num_Exchange_Cost,								//���֮�佻�׵�������
	Num_Business_Discount,							//NPC����ʱ�������ۿ�

	Num_BindSilverCostLimitParam1 = 3010,					// ���ÿ����Ʊ�������޼��㹫ʽ����1
	Num_BindSilverCostLimitParam2,							// ���ÿ����Ʊ�������޼��㹫ʽ����2

	Num_BindSilverCarryLimitParam1 = 3015,					// �����ƱЯ�����޼��㹫ʽ����1
	Num_BindSilverCarryLimitParam2,							// �����ƱЯ�����޼��㹫ʽ����2
	Num_BindSilverCarryLimitParam3,							// �����ƱЯ�����޼��㹫ʽ����2

	NUM_BINDSILVER_DAY_USEUPPERLIMIT = 3050,		//������ÿ��ʹ������
	NPC_BusinessTax,                                //NPC���׹���˰����
	NPC_BusinessTax_Add,                            //NPC���׹���˰���˰������ʥˮΪ0ʱ��˰��


	//����ϵͳ
	Auction_Param_Cost1 = 3100,						//��������8Сʱ
	Auction_Param_Cost2,							//��������12Сʱ
	Auction_Param_Cost3,							//��������24Сʱ
	Auction_Param_Tax,								//����˰�ձ���

	//��̯ϵͳ
	Stall_Param_Cost = 3200,						//��̯����

	//�ֿ�ϵͳ
	Warehouse_Param_LatticeNum = 3300,				//�ֿ�λ��������
	Warehouse_Param_Cost,							//����

	//pkϵͳ
	PK_Param_Hunt1 = 3400,							//׷��1����
	PK_Param_Hunt2,									//׷��5����
	PK_Param_Hunt3,									//׷��10����

	//����ϵͳ
	Prison_Param_Percent = 3500,					//��������
	Prison_Param_SinPercent,						//���ֵ��
	Prison_Param_SinValue,							//���ֵ/���ʱ��
	Prison_Param_RedNameTime,						//����ʱ��/��
	Prison_Param_HonorsExchangSin,					//���/����������ϴ���
	Prison_Param_CommutationCost,					//��Ǯ�����ڣ�Ǯ/���ӣ�

	WHITE_NAME_DROP_NUMS = 3506,                    //��������������߸���
	WHITE_NAME_DROP_ODDS,                           //��������������߸���
	GRAY_NAME_DROP_NUMS,                            //��������������߸���
	GRAY_NAME_DROP_ODDS,                            //��������������߸���
	RED_NAME_DROP_NUMS,                             //��������������߸���
	RED_NAME_DROP_ODDS,                             //��������������߸���

	PK_Protected_Level	  = 3512,					//PK�����ȼ����߻������ݿ�����д�Ĵ�ֵ��

	Num_Death_PropHp_Lost = 3550,                    //������������;�ֵ

	//�����
	Campaign_Dance_ExpSecond=3600,					//����Ӿ��������
	Campaign_Dance_BaseExp,							//�����������ֵ����	
	Campaign_Dance_DecreaseEngegy,					//������ٵľ���ֵ
	Campaign_Dance_AddPropSecond,					//�������ӵ��ߵ�����
	Campaign_Dacne_UseCount,						//�����ȵ�����


	//////////////////��������////////////////////////////////////
	//ͬ����
	Explorer_Param_Area = 4000,						//ͬ����Χ
	Explorer_Param_PersonNum,						//ͬ������

	Param_Quest_GetExpPercent = 4100,				//������ֵ��ȡ����
	Param_Monster_GetExpPercent,					//���ﾭ��ֵ��ȡ����
	Param_Prestige_GetExpPercent,					//����ֵ��ȡ����
	Param_Money_GetPercent,							//��Ǯ��ñ���
	Param_Drop_GetPercent,							//����������
	Param_GainMoney_Percent,						//��Ǯ����ϵ��

	Param_Quest_20Percent = 4110,					//20���
	Param_Quest_40Percent,							//40���
	Param_Quest_60Percent,							//60���
	Param_Quest_80Percent,							//80���
	Param_Quest_100Percent,							//100���
	Param_Quest_120Percent,							//120���
	Param_Quest_140Percent,							//140���
	Param_Quest_160Percent,							//160���

	//�
	Family_Boss_CreatRand1 = 5001,					//�漴����boss
	Family_Boss_CreatRand2,							//�м�boss
	Family_Boss_CreatRand3,							//�߼�boss
	Action_Family_Boss_Grace,						//��ѫ
	Action_Family_Boss_Scale,						//�����
	Action_Family_Boss_Weights,						//�Ȩֵ
	Family_Boss_Level1,								//boss�ĵȼ�
	Family_Boss_Level2,						
	Family_Boss_Level3,
	Family_Boss_Level4,
	Family_Boss_Level5,
	Family_Boss_Grow1,								//boss�ĳɳ�ֵ
	Family_Boss_Grow2,
	Family_Boss_Grow3,
	Family_Boss_Grow4,
	Family_Boss_Grow5,
	FamilyBossID1,
	FamilyBossID2,
	FamilyBossID3,
	FamilyBossID4,
	FamilyBossID5,
	FamilyBossID6,
	Family_Boss_Feed_Credit ,						//ι������boss��ȡ�ļ��幱�׶�
	FamilyBossLevelMultiple,						//����boss�ȼ�����

	Campaign_Question_Base =5050,					//�����
	Campaign_Question_Power,						//�Ȩֵ
	Camapign_Question_WencaiBase,					//�Ĳɱ���
	Campaign_Question_PointBase,					//�÷ֱ���

	Quest_Target_SafeTime=6000,						//����Ŀ�걻������Ļָ�״̬ʱ��
	Quest_Target_ReHpTime,							//����Ŀ��Ļظ�ʱ��
	Quest_Car_UnderAttackTime,						//�ڳ��������󣬲���������

	////////////////////////��ͻ���ͬ���Ĳ���/////////////////////////////////////
	Client_Gift_Time1 = 7000,						//ʱ���������ʱ��
	Client_Gift_Time2,								//ʱ���������ʱ��
	Client_Gift_Time3,								//ʱ���������ʱ��
	Client_Gift_Time4,								//ʱ���������ʱ��
	Client_Gift_Time5,								//ʱ���������ʱ��
	Client_Gift_Time6,								//ʱ���������ʱ��
	Client_Gift_Time7,								//ʱ���������ʱ��
	Client_Gift_Time8,								//ʱ���������ʱ��
	Client_Gift_Time9,								//ʱ���������ʱ��
	Client_Gift_Time10,								//ʱ���������ʱ��

	Client_Gift_PropID1,							//ʱ��������͵���
	Client_Gift_PropID2,							//ʱ��������͵���
	Client_Gift_PropID3,							//ʱ��������͵���
	Client_Gift_PropID4,							//ʱ��������͵���
	Client_Gift_PropID5,							//ʱ��������͵���
	Client_Gift_PropID6,							//ʱ��������͵���
	Client_Gift_PropID7,							//ʱ��������͵���
	Client_Gift_PropID8,							//ʱ��������͵���
	Client_Gift_PropID9,							//ʱ��������͵���
	Client_Gift_PropID10,							//ʱ��������͵���

	Client_Gift_PropID11,							//ʱ��������͵���
	Client_Gift_PropID12,							//ʱ��������͵���
	Client_Gift_PropID13,							//ʱ��������͵���
	Client_Gift_PropID14,							//ʱ��������͵���
	Client_Gift_PropID15,							//ʱ��������͵���
	Client_Gift_PropID16,							//ʱ��������͵���
	Client_Gift_PropID17,							//ʱ��������͵���
	Client_Gift_PropID18,							//ʱ��������͵���
	Client_Gift_PropID19,							//ʱ��������͵���
	Client_Gift_PropID20,							//ʱ��������͵���

	Client_Gift_PropID21,							//ʱ��������͵���
	Client_Gift_PropID22,							//ʱ��������͵���
	Client_Gift_PropID23,							//ʱ��������͵���
	Client_Gift_PropID24,							//ʱ��������͵���
	Client_Gift_PropID25,							//ʱ��������͵���
	Client_Gift_PropID26,							//ʱ��������͵���
	Client_Gift_PropID27,							//ʱ��������͵���
	Client_Gift_PropID28,							//ʱ��������͵���
	Client_Gift_PropID29,							//ʱ��������͵���
	Client_Gift_PropID30,							//ʱ��������͵���

	Client_Gift_PropID31,							//ʱ��������͵���
	Client_Gift_PropID32,							//ʱ��������͵���
	Client_Gift_PropID33,							//ʱ��������͵���
	Client_Gift_PropID34,							//ʱ��������͵���
	Client_Gift_PropID35,							//ʱ��������͵���
	Client_Gift_PropID36,							//ʱ��������͵���
	Client_Gift_PropID37,							//ʱ��������͵���
	Client_Gift_PropID38,							//ʱ��������͵���
	Client_Gift_PropID39,							//ʱ��������͵���
	Client_Gift_PropID40,							//ʱ��������͵���

	Client_Gift_PropID41,							//ʱ��������͵���
	Client_Gift_PropID42,							//ʱ��������͵���
	Client_Gift_PropID43,							//ʱ��������͵���
	Client_Gift_PropID44,							//ʱ��������͵���
	Client_Gift_PropID45,							//ʱ��������͵���
	Client_Gift_PropID46,							//ʱ��������͵���
	Client_Gift_PropID47,							//ʱ��������͵���
	Client_Gift_PropID48,							//ʱ��������͵���
	Client_Gift_PropID49,							//ʱ��������͵���
	Client_Gift_PropID50,							//ʱ��������͵���

	Client_Gift_PropID51,							//ʱ��������͵���
	Client_Gift_PropID52,							//ʱ��������͵���
	Client_Gift_PropID53,							//ʱ��������͵���
	Client_Gift_PropID54,							//ʱ��������͵���
	Client_Gift_PropID55,							//ʱ��������͵���
	Client_Gift_PropID56,							//ʱ��������͵���
	Client_Gift_PropID57,							//ʱ��������͵���
	Client_Gift_PropID58,							//ʱ��������͵���
	Client_Gift_PropID59,							//ʱ��������͵���
	Client_Gift_PropID60,							//ʱ��������͵���

	Client_Gift_PropID61,							//ʱ��������͵���
	Client_Gift_PropID62,							//ʱ��������͵���
	Client_Gift_PropID63,							//ʱ��������͵���
	Client_Gift_PropID64,							//ʱ��������͵���
	Client_Gift_PropID65,							//ʱ��������͵���
	Client_Gift_PropID66,							//ʱ��������͵���
	Client_Gift_PropID67,							//ʱ��������͵���
	Client_Gift_PropID68,							//ʱ��������͵���
	Client_Gift_PropID69,							//ʱ��������͵���
	Client_Gift_PropID70,							//ʱ��������͵���

	Client_Gift_PropID71,							//ʱ��������͵���
	Client_Gift_PropID72,							//ʱ��������͵���
	Client_Gift_PropID73,							//ʱ��������͵���
	Client_Gift_PropID74,							//ʱ��������͵���
	Client_Gift_PropID75,							//ʱ��������͵���
	Client_Gift_PropID76,							//ʱ��������͵���
	Client_Gift_PropID77,							//ʱ��������͵���
	Client_Gift_PropID78,							//ʱ��������͵���
	Client_Gift_PropID79,							//ʱ��������͵���
	Client_Gift_PropID80,							//ʱ��������͵���

	Client_Gift_PropID81,							//ʱ��������͵���
	Client_Gift_PropID82,							//ʱ��������͵���
	Client_Gift_PropID83,							//ʱ��������͵���
	Client_Gift_PropID84,							//ʱ��������͵���
	Client_Gift_PropID85,							//ʱ��������͵���
	Client_Gift_PropID86,							//ʱ��������͵���
	Client_Gift_PropID87,							//ʱ��������͵���
	Client_Gift_PropID88,							//ʱ��������͵���
	Client_Gift_PropID89,							//ʱ��������͵���
	Client_Gift_PropID90,							//ʱ��������͵���

	Client_Gift_PropID91,							//ʱ��������͵���
	Client_Gift_PropID92,							//ʱ��������͵���
	Client_Gift_PropID93,							//ʱ��������͵���
	Client_Gift_PropID94,							//ʱ��������͵���
	Client_Gift_PropID95,							//ʱ��������͵���
	Client_Gift_PropID96,							//ʱ��������͵���
	Client_Gift_PropID97,							//ʱ��������͵���
	Client_Gift_PropID98,							//ʱ��������͵���
	Client_Gift_PropID99,							//ʱ��������͵���
	Client_Gift_PropID100,							//ʱ��������͵���

	Client_Gift_PropCount,							//���������
	Client_Gift_TakeTimes,							//ÿ����ȡ����

	Client_Family_SkillLevel,						//���弼�ܵȼ�
	Client_Family_ResearchSkill_Cost,				//���弼���о����ļ����ʽ��ֵ
	Client_Family_LearnSkill_Cost,					//���弼��ѧϰ���Ĺ��׶Ȼ�ֵ
	Client_Family_ResearchSkill_Rate,				//�����о��������ļ����ʽ����
	Client_Family_LearnSkill_Rate,					//����ѧϰ�������Ĺ��׶ȱ���
	Client_Family_Active,							//���己�ٶȻ�ֵ
	Client_Family_Active_Rate,						//���己�ٶȱ���

	Client_Gift_Max_Everyday,						//ÿ�����ȡ�������
	Client_Gift_Max_Times,							//�ܹ�����ȡ�İ�������

	Client_Revive_Cost_ToTown = 7201,				//��ȫ��������ķ���
	Client_Revive_Cost_InSitu,						//ԭ�ظ�������ķ���
	Client_Revive_Cost_FullStatus,					//��״̬��������ķ���
	Client_Revive_Cost_Append,						//�����������״̬��������ĸ��ӷ���

	//��Ծ�Ȳ���
	Vitality_Family_Wage = 7500,					//�����Ա��Ծ�ȼ������
	Vitality_Family_HuoDongDuN,						//����ת�������Ļ�Ȳ���
	Family_Wage_BaseValue,							//���ʻ���ֵ

	//ս����ѫ�һ�����Ҫ�Ĺ�ѫֵ
	CombatCredit_Sanlue = 7510,
	CombatCredit_LiuTao,
	CombatCredit_MengDeXinShu,
	CombatCredit_SunZiBingFa,
	CombatCredit_ExchangeNum,						//ս����ѫ�һ����� add by zhangjianli 2012-10-12

	Client_Param_End,
	//////////////////////////////////////////////////////////////////////////
	
	Num_End,
};

enum Affect_By_Attrib
{
	Affect_PhysicalDamage = 0,
	Affect_SpellDamage,
	Affect_PhysicalArmor,
	Affect_SpellArmor,
	Affect_Hp,
	Affect_Mp,
	Affect_Crit,
	Affect_End,
};
