
//////////////////////////////////////////////////////////////////////////
//数据库参数表
enum Numerical
{
	//////////////////人物属性及装备参数////////////////////////////////////
	Num_Begin = 0,
	Num_Init_Waigong = 1,			//初始外功
	Num_Init_Shenfa,				//初始身法
	Num_Init_Neigong,				//初始内功
	Num_Init_Zhenqi,				//初始真气
	Num_Init_Jingu,					//初始筋骨
	Num_Init_Level,					//初始等级
	Num_Init_Exp,					//初始经验
	Num_Init_Hp,					//初始生命值
	Num_Init_Mp,					//初始魔法值
	Num_Init_Runspeed,				//初始移动速度
	Num_Init_HpRegen_ClassOne,		//生命恢复速度
	Num_Init_HpRegen_ClassTwo,
	Num_Init_HpRegen_ClassThree,
	Num_Init_HpRegen_ClassFour,
	Num_Init_MpRegen_ClassOne,		//魔法恢复速度
	Num_Init_MpRegen_ClassTwo,
	Num_Init_MpRegen_ClassThree,
	Num_Init_MpRegen_ClassFour,

	Num_LevelUp_Hp = 20,			//级别提升生命值
	Num_LevelUp_Mp,					//级别提升魔法值
	Num_LevelUp_AttribPoint,		//级别提升属性点
	Num_LevelUp_SkillPoint,			//级别提升技能点

	Num_AffectByWG_PhysicalDamage = 30,	//力量对物理伤害的提升
	Num_AffectByWG_SpellDamage,			//力量对魔法伤害的提升
	Num_AffectByWG_PhysicalArmor,		//力量对物理防御的提升
	Num_AffectByWG_SpellArmor,			//力量对魔法防御的提升
	Num_AffectByWG_Hp,					//力量对生命值的提升
	Num_AffectByWG_Mp,					//力量对魔法值的提升
	Num_AffectByWG_Crit,				//力量对暴击的提升
	Num_AffectBySF_PhysicalDamage,		//敏捷对物理伤害的提升
	Num_AffectBySF_SpellDamage,			//敏捷对魔法伤害的提升
	Num_AffectBySF_PhysicalArmor,		//敏捷对物理防御的提升    
	Num_AffectBySF_SpellArmor,			//敏捷对魔法防御的提升
	Num_AffectBySF_Hp,					//敏捷对生命值的提升
	Num_AffectBySF_Mp,					//敏捷对魔法值的提升
	Num_AffectBySF_Crit,				//敏捷对暴击的提升
	Num_AffectByNG_PhysicalDamage,		//智力对物理伤害的提升
	Num_AffectByNG_SpellDamage,			//智力对魔法伤害的提升
	Num_AffectByNG_PhysicalArmor,		//智力对物理防御的提升
	Num_AffectByNG_SpellArmor,			//智力对魔法防御的提升
	Num_AffectByNG_Hp,					//智力对生命值的提升
	Num_AffectByNG_Mp,					//智力对魔法值的提升
	Num_AffectByNG_Crit,				//智力对暴击的提升
	Num_AffectByZQ_PhysicalDamage,		//精神对物理伤害的提升
	Num_AffectByZQ_SpellDamage,			//精神对魔法伤害的提升
	Num_AffectByZQ_PhysicalArmor,		//精神对物理防御的提升
	Num_AffectByZQ_SpellArmor,			//精神对魔法防御的提升
	Num_AffectByZQ_Hp,					//精神对生命值的提升
	Num_AffectByZQ_Mp,					//精神对魔法值的提升
	Num_AffectByZQ_Crit,				//精神对暴击的提升
	Num_AffectByJG_PhysicalDamage,		//体质对物理伤害的提升
	Num_AffectByJG_SpellDamage,			//体质对魔法伤害的提升
	Num_AffectByJG_PhysicalArmor,		//体质对物理防御的提升
	Num_AffectByJG_SpellArmor,			//体质对魔法防御的提升
	Num_AffectByJG_Hp,					//体质对生命值的提升
	Num_AffectByJG_Mp,					//体质对魔法值的提升
	Num_AffectByJG_Crit,				//体质对暴击的提升
	Num_AffectByLevel_Damage,			//等级对攻击力的提升
	Num_AffectByLevel_Armor,			//等级对防御力的提升
	Num_Bind_Max_Money,					//绑定的最大金钱数
	Num_Not_Bind_Max_Money,				//非绑定的最大金钱数

	Num_Wave_Value = 70,				//取值浮动
	Num_Wave_Precent,					//取比例浮动
	NUM_DamageArea_Precent,				//群攻的百分比减少
	Num_Damage_Percent_Max,				//每次攻击对玩家的最大伤害百分比（和目标的血量最大值的百分比，用来做防秒参数）
	Num_Energy_Regen,					//活力值每日回复

	Num_PropAttrib_ClassOne = 80,		//装备向基础值选取系数
	Num_PropAttrib_ClassTwo,
	Num_PropAttrib_ClassThree,
	Num_PropAttrib_ClassFour,

	Num_Coefficient_DoubleHand = 90,	//装备位置的选取系数
	Num_Coefficient_SingleHand,
	Num_Coefficient_Shield,
	Num_Coefficient_Ring,
	Num_Coefficient_Necklack,
	Num_Coefficient_Helm,
	Num_Coefficient_Chest,
	Num_Coefficient_Belt,
	Num_Coefficient_Boot,
	Num_Coefficient_Bracer,

	Num_Coefficient_DoubleResist = 110,	//双防装属性系数

	Num_Coefficient_White = 120,		//装备品质的选取系数
	Num_Coefficient_Green,
	Num_Coefficient_Blue,
	Num_Coefficient_Purple,
	Num_Coefficient_Gold,
	Num_Coefficient_PerfectGold,
	Num_Coefficient_LegendGold,		    //传说金

	Num_PreName_Purple = 130,			//紫色和金色装备前缀名概率
	Num_PreName_Gold1,
	Num_PreName_Gold2,

	Num_Coefficient_BlueEffect_ClassOne = 140,		//蓝装效果
	Num_Coefficient_BlueEffect_ClassTwo,
	Num_Coefficient_BlueEffect_ClassThree,
	Num_Coefficient_BlueEffect_ClassFour,

	Num_Coefficient_GreenEffect = 150,	//装备效果提升比例
	Num_Coefficient_CyanEffect,
	Num_Coefficient_PurpleEffect,
	Num_Coefficient_ActiveEffect1,		
	Num_Coefficient_ActiveEffect2,
	Num_Coefficient_ActiveEffect3,
	Num_Coefficient_ZhanhunEffect,

	Num_PropRepeatBind_Attr1 = 160,		//重绑属性提升(4个参数)
	Num_PropRepeatBind_Attr2,			
	Num_PropRepeatBind_Attr3,			
	Num_PropRepeatBind_Attr4,			
	
	Num_PropSign_Attr = 170,			//签名属性提升
	Num_PropBind_Attr,					//绑定属性提升

	Num_PropStar_Attr1 = 200,			//打星属性提升
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

	Num_Repair_Cost = 250,				//每文银子可修理的耐久度
	Num_AutoRepairPropCost		= 252,	//自动修理装备花费银子

	Num_EquipEffect_RandomMax = 260,	// 装备产生随机品质位的最大值(0-400)
	Num_EquipEffect_White_Param,		// 各品质随机效果的品质系数
	Num_EquipEffect_Green_Param,
	Num_EquipEffect_Blue_Param,
	Num_EquipEffect_Purple_Param,
	Num_EquipEffect_Gold_Param,
	Num_EquipEffect_White_Range,		// 各品质取随机效果的区间低值
	Num_EquipEffect_Green_Range,
	Num_EquipEffect_Blue_Range,
	Num_EquipEffect_Purple_Range,
	Num_EquipEffect_Gold_Range,
	Num_EquipEffect_LegendGold_Param,	//传说金
	Num_EquipEffect_LegendGold_Range,

	Num_PropBind_Cost = 280,			//道具绑定原费用 
	Num_PropSign_Cost,					//道具签名原费用 
	Num_PropAddStar_Cost,				//装备打星原费用
	Num_PropCompose_Cost,				//装备合成原费用
	Num_MaterialCompose_Cost,			//材料合成原费用
	Num_PropAddHole_Cost,				//装备打孔原费用
	Num_PropAddGem_Cost,				//装备镶嵌原费用
	Num_PropUnGem_Cost,					//装备拆宝石费用
	Num_PropRepeatBind_Cost,			//装备重绑费用
	Num_PropUnAddStar_Cost,				//装备拆星费用
	Num_PropRepeatStar_Cost,			//装备附星费用
	Num_PropZhanHun_Cost,				//灵魂锁链修改费用
	Num_PropFiveElements_Cost,			//修改五行费用
	Num_PropUnGem_Fail,					//拆宝石失败率
	Num_PropUnAddStar_Fail,				//拆星失败率


	Num_Fellow_Grown_Radix = 300,		//成长基数
	Num_Fellow_Grown_RadixValue,		//成长基值
	Num_Fellow_Aptitude_Radix,			//资质基数
	Num_Fellow_Rebirth_Cost,			//重生花费参数
	Num_Fellow_Refinery_Exp,			//炼化经验基数
	Num_Fellow_Prop_Feed_Val,			//道具喂食兑换基数
	Num_Fellow_SkillID_Num,				//随机技能个数参数

	Num_Fellow_WhiteApt_Min,					//白色资质的最小概率
	Num_Fellow_WhiteApt_Max,					//白色资质的最大概率

	Num_Fellow_GreenApt_Min,					//绿色资质的最小概率
	Num_Fellow_GreenApt_Max,					//绿色资质的最大概率

	Num_Fellow_BlueApt_Min,						//蓝色资质的最小概率
	Num_Fellow_BlueApt_Max,						//蓝色资质的最大概率

	Num_Fellow_PurpleApt_Min,					//紫色资质的最小概率
	Num_Fellow_PurpleApt_Max,					//紫色资质的最大概率

	Num_Fellow_GoldApt_Min,						//金色资质的最小概率
	Num_Fellow_GoldApt_Max,						//金色资质的最大概率
	Num_Fellow_AddUseableAttribPoint,			//每次升级增加的属性点
	
	Num_Fellow_SkillFusion_Cost_Changeless,     //技能融合固定手续费
	Num_Fellow_SkillFusion_Cost_BindSkill,      //技能融合绑定技能手续费

	Num_Fellow_Evolution_BaseCost,				//珍兽强化原费用
	Num_Ride_Evolution_BaseCost,				//骑宠强化费用

	Num_Fellow_PhysicalDamage,					// 珍兽力量增加物理攻击量
	Num_Fellow_SpellDamage,						// 珍兽智力增加魔法攻击量
	Num_Fellow_PhysicalArmor,					// 珍兽敏捷增加物防防御量
	Num_Fellow_SpellArmor,						// 珍兽精神增加魔防防御量
	Num_Fellow_Hp,								// 珍兽体质增加生命值量
	Num_Fellow_Crit,							// 珍兽体质增加暴击等级量
	Num_Fellow_UpLevelExpIsMasterExp_Twentieth,	//珍兽升级经验为主人经验的二十分之一

	Num_Gem_Buff_Poison	= 400,					//宝石效果添加的中毒Buff（取出的值同样要除1000）
	Num_Gem_Buff_Ablepsia,						//宝石效果添加的失明Buff（取出的值同样要除1000）
	Num_Gem_Buff_Freeze,						//宝石效果添加的冰冻Buff（取出的值同样要除1000）
	Num_Gem_Buff_Burn,							//宝石效果添加的灼烧Buff（取出的值同样要除1000）
	Num_Gem_Buff_Stun,							//宝石效果添加的眩晕Buff（取出的值同样要除1000）
	Num_Gem_Buff_Slow,							//宝石效果添加的减速Buff（取出的值同样要除1000）
	Num_Gem_Buff_Immobilize,					//宝石效果添加的定身Buff（取出的值同样要除1000）
	Num_Gem_Buff_Confuse,						//宝石效果添加的混乱Buff（取出的值同样要除1000）
	Num_Gem_Buff_Slience,						//宝石效果添加的沉默Buff（取出的值同样要除1000）

	Nun_Suit_Level_1_Damage = 450,				//套件差值为第1档时，增加攻击力%
	Nun_Suit_Level_1_Armor,						//套件差值为第1档时，增加防御力%
	Nun_Suit_Level_1_DamageIncrease,			//套件差值为第1档时，增加伤害%

	Nun_Suit_Level_2_Damage = 460,				//套件差值为第2档时，增加攻击力%
	Nun_Suit_Level_2_Armor,						//套件差值为第2档时，增加防御力%
	Nun_Suit_Level_2_DamageIncrease,			//套件差值为第2档时，增加伤害%

	Num_PropStar_Success1 = 500,				//打星成功率
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
	
	Num_PropStar_Fail = 550,		//加星失败后星数掉落数
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

	Num_PropCompose_Success = 600, //装备合成 成功率

	Num_YearWineBox_BindParam = 700,
	Num_Data_End,

	//////////////////系统参数////////////////////////////////////
	//dbserver参数
	DB_Param_ID_Logic_Time_LoginQueue = 1000,	//排队逻辑时间
	DB_Param_ID_Logic_Time_UserMgr,				//UserMgr逻辑时间
	DB_Param_ID_Logic_Time_PlayerMgr,			//PlayerMgr逻辑时间
	DB_Param_ID_Logic_Time_FamilyMgr,			//家族管理器逻辑时间
	DB_Param_ID_Logic_Time_GangMgr,				//帮会管理器逻辑时间
	DB_Param_ID_Logic_Time_AuctionMgr,			//拍卖行逻辑时间
	DB_Param_ID_Logic_Time_ClearingMgr,			//金币交易所逻辑时间
	DB_Param_ID_Logic_Time_MailMgr,				//MailMgr逻辑时间
	DB_Param_ID_Logic_Time_PropMgr,				//PropMgr逻辑时间
	DB_Param_ID_Player_Quit_Time,				//DB保留玩家的时间	
	DB_Param_ID_Logic_Time_Player_Quest,
	DB_Param_ID_Logic_Time_Player_Private,
	DB_Param_ID_Logic_Time_SaveEventItem,		//SaveEventItem Logic Time
	DB_Param_ID_Logic_Time_LoadNumerical,		//读取数值表
	DB_Param_ID_Logic_Time_PlayerCampaign,		//玩家活动管理器逻辑时间
	DB_Param_End,

	//communityserver参数
	Community_Param_ID_Logic_Time_PlayerMgr	= 1100,			
	Community_Param_ID_Logic_Time_TeamMgr,
	Community_Param_ID_Logic_Time_FamilyMgr,
	Community_Param_ID_Player_SendPacket_Limit,
	Community_Param_End,

	//loginserver参数
	Login_Param_ID_Logic_Time_UserMgr = 1200,
	Login_Param_ID_Logic_Time_LoginQueue,
	Login_Param_End,

	//dataserver参数
	Data_Param_ID_Logic_Time_PlayerMgr = 1300,	//PlayerMgr逻辑时间
	Data_Param_ID_Logic_Time_FamilyMgr,			//家族管理器逻辑时间
	Data_Param_ID_Logic_Time_GangMgr,			//帮会管理器逻辑时间
	Data_Param_ID_Logic_Time_AuctionMgr,		//拍卖行逻辑时间
	Data_Param_ID_Logic_Time_ClearingMgr,		//金币交易所逻辑时间
	Data_Param_ID_Logic_Time_MailMgr,			//MailMgr逻辑时间
	Data_Param_ID_Logic_Time_PropMgr,			//PropMgr逻辑时间
	Data_Param_ID_Logic_Time_TeamMgr,			//TeamMgr 逻辑时间
	Data_Param_ID_Logic_Time_QuestMgr,			//任务逻辑时间
	Data_Param_ID_Logic_Time_QuestionMgr,		//答题逻辑时间
	Data_Param_ID_Logic_Time_God,				//God逻辑时间
	Data_Param_ID_Logic_Time_SceneMgr,			//SceneMgr 逻辑
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
	Data_Param_ID_Logic_Time_Player_Hp_Mp,		//玩家Hp Mp恢复速度
	Data_Param_ID_Logic_Time_Player_Campaign,	//活动管理器逻辑速度
	Data_Param_ID_Logic_Time_PlayerMgr_NPC,		//NPC的逻辑时间间隔
	Data_Param_ID_Logic_Time_Person_AI,			//Person AI逻辑
	Data_Param_ID_Logic_Time_Person_Status,
	Data_Param_ID_Logic_Time_Person_Buff,


	Data_Param_ID_Player_Count_Limit = 1400,	//服务器限制人数
	Data_Param_ID_Player_SendPacket_Limit,		//玩家发送缓存里Packet的数量限制,超过了就强行中断连接
	Data_Param_ID_Explorer_Player_Count_Max,	//同屏表的限制人数最大值
	Data_Param_ID_Team_Postion_Syncho,			//队伍成员位置同步频率
	Data_Param_ID_Prop_Disappear_Time,			//地上的道具消失的时间
	Data_Param_ID_Prop_Protect_Time,			//地上的道具受保护的时间
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


	//////////////////社会系统参数////////////////////////////////////
	Community_Param_LevelIncrease = 2000,	//社会系统级别提升比例

	//组队参数
	Community_Param_ExpAdd = 2100,			//经验值加成比例
	Community_Param_TeamPersonNum,			//队伍人数限制
	Community_Param_SpeDistribute,			//特殊分配比例

	//师徒参数
	Community_Param_MasterLevel = 2200,		//收徒级别
	Community_Param_ChildLevel,				//拜师级别
	Community_Param_GrowSync,				//同步成长
	Community_Param_ChildNum,				//级别收徒量
	Community_Param_ChildLevel_Max,			//出师级别（超过此级别不能拜师）

	//好友参数
	Community_Param_Friendliness = 2300,	//友好度
	Community_Param_FriednlinessIncrease,	//友好度提升速度

	//家族参数
	Community_Param_FamilyLevel = 2400,			//家族等级
	Community_Param_CreateFamilyLevel,			//家族创建级别
	Community_Param_FamilyNameCount,			//创建家族名字的长度
	Community_Param_AddFamilyLevel,				//加入级别限制
	Community_Param_CreateFamilyCost,			//家族创建资金
	Community_Param_ChangeFamilyMoney,			//转换为家族资金
	Community_Param_InitFamilyActive,			//家族繁荣度初始值
	Community_Param_FamilyActive,				//家族繁荣度比值
	Community_Param_FamilyMemberCount,			//家族人数比值
	Community_Param_FamilyLevelCost,			//家族升级花费家族资金的比值
	Community_Param_FamilySkillLevle,			//家族技能等级
	Community_Param_FamilySkillResearchCost,	//家族技能研究消耗家族资金比值
	Community_Param_FamliySkillLearnCost,		//家族技能学习消耗贡献度比值
	Community_Param_FamilyMoney1,				//家族捐款1
	Community_Param_FamilyMoney2,				//家族捐款2
	Community_Param_FamilyCredit1,				//家族捐款1获得贡献度
	Community_Param_FamilyCredit2,				//家族捐款2获得贡献度
	Community_Param_FamilyDownActive,			//家族降繁荣度比值
	Community_Param_FamilyUpdateActiveMember,	//繁荣度提升家族多少人在线
	Community_Param_FamilyUpdateActive,			//家族人数在线繁荣度提升多少
	Community_Param_FamilyIpdateActiveTime,		//几个小时提升一次繁荣度
	Community_Param_FamilyCar_MakeMoney,		//打造家族战车需要花费的个人资金
	Community_Param_FamilyCar_FixMoney,			//修理家族战车需要花费的家族资金（10：n）
	Community_Param_FamilyCar_BAIHU_ID,			//白虎车id
	Community_Param_FamilyCar_QINGLONG_ID,		//青龙车id
	Community_Param_FamilyCar_QILIN_ID,			//麒麟车id
	Community_Param_FamilyActive_Rate,			//家族繁荣度比率
	Community_Param_FamilyMemberCount_Rate,		//家族人数比率	
	Community_Param_FamilyLevelCost_Rate,		//家族升级花费家族资金的比率
	Community_Param_FamilySkillResearchCost_Rate,//家族研究技能消耗家族资金比率
	Community_Param_FamilySkillLearCost_Rate,	//家族学习技能消耗贡献度比率
	Community_Param_FamilyApplySceneMoney,		//申请家族庄园花费的家族资金
	//家族建筑相关数据--耐久度
	Community_Param_FamilyJuYiTingWear,			//家族聚义厅耐久度
	Community_Param_FamilyZhaiBaseWear,			//家族宅基地耐久度		
	Community_Param_FamilyCarHouseWear,			//家族战车坊耐久度				
	Community_Param_FamilyWuGuangWear,			//家族武馆耐久度
	Community_Param_FamilyYanJiuSuoWear,		//家族研究所耐久度
	Community_Param_FamilyGoldStorageWear,		//家族金库耐久度
	Community_Param_FamilyStorageWear,			//家族仓库耐久度
	Community_Param_FamilyYeLianFangWear,		//家族冶炼房耐久度
	Community_Param_FamilyJianTaWear,			//家族箭塔耐久度
	
	Community_Param_FamilyJuYiTingMaxHp,		//家族聚义厅最大血量
	Community_Param_FamilyZhaiBaseMaxHp,		//家族宅基地最大血量	
	Community_Param_FamilyCarHouseMaxHp,		//家族战车坊最大血量			
	Community_Param_FamilyWuGuangMaxHp,			//家族武馆最大血量
	Community_Param_FamilyYanJiuSuoMaxHp,		//家族研究所最大血量
	Community_Param_FamilyGoldStorageMaxHp,		//家族金库最大血量
	Community_Param_FamilyStorageMaxHp,			//家族仓库最大血量
	Community_Param_FamilyYeLianFangMaxHp,		//家族冶炼房最大血量
	Community_Param_FamilyJianTaMaxHp,			//家族箭塔最大血量

	Community_Param_FamilyBuildingWeiHuValue,			//家族维护费系数
	Community_Param_FamilyBuildingJianSheDuA,			//家族建设度A
	Community_Param_FamilyBuildingJianSheDuB,			//家族建设度B

	Community_Param_FamilyUpKeepCost,					//家族每日维护费基数
	Community_Param_FamilyBuildingUpgradeCostA,			//A建筑升级基础花费
	Community_Param_FamilyBuildingUpgradeCostB,			//B建筑升级基础花费

	Community_Param_FamilyJuYiTingMaxLevel,				//聚义厅最大等级
	Community_Param_FamilyGoldStorageMaxLevel,			//家族金库最大等级
	Community_Param_FamilyZhaiBaseMaxLevel,			//家族宅基地最大等级
	Community_Param_FamilyFightCarHouseMaxLevel,	//家族战车坊最大等级
	Community_Param_FamilyYanJiuSuoMaxLevel,		//研究所最大等级
	Community_Param_FamilyWuGuanMaxLevel,			//家族武馆最大等级
	Community_Param_FamilyStorageMaxLevel,			// 家族仓库最大等级
	Community_Param_FamilyYeLianFangMaxLevel,		//冶炼房最大等级
	Community_Param_FamilyJianTaMaxLevel,			//家族箭塔最大等级

	//帮会参数
	Community_Param_CreateGangPersonNum = 2500,		//帮会创建人数要求
	Community_Param_CreateGangCost,					//创建需求家族资金
	Community_Param_GangCreateCD,					//创建帮会需要cd
	Community_Param_GangMasterLeaveTime,			//帮主离会时间
	Community_Param_GangExitPunish,					//退会贡献度惩罚比
	Community_Param_GangExitCD,						//家族推出冷却时间
	Community_Param_GangActiveStandard,				//帮会标准繁荣度1
	Community_Param_GangActiveDecrease1,			//帮会繁荣度减少量1
	Community_Param_GangActiveDecrease2,			//帮会繁荣度减少量2
	Community_Param_GangActiveDecrease3,			//帮会繁荣度减少量3
	Community_Param_GangActiveDecrease4,			//帮会繁荣度减少量4
	Community_Param_GangActiveDecrease5,			//帮会繁荣度减少量5
	Community_Param_GangContributionPercent,		//贡献度的产出比例
	Community_Param_GangCapacity1,					//帮会容量1
	Community_Param_GangCapacity2,					//帮会容量2
	Community_Param_GangCapacity3,					//帮会容量3
	Community_Param_GangCapacity4,					//帮会容量4
	Community_Param_GangCapacity5,					//帮会容量5
	Community_Param_GangDismissTime,				//帮会解散时间
	Community_Param_GangSkillResearchCost,			//帮会技能研究消耗1
	Community_Param_GangSkillLearnCost,				//帮会技能学习消耗1
	Community_Param_GangUpdateLevelCost,			//帮会升级资金消耗1
	Community_Param_GangActiveInit,					//帮会初始繁荣度

	//////////////////功能参数////////////////////////////////////
	//邮件系统
	Mail_Param_Cost = 3000,							//邮件基础费用
	Mail_Param_PropCost,							//道具邮件费用
	Mail_Param_MaxNum,								//邮件存储量
	Mail_Param_Time,								//邮件存储时间
	Num_Exchange_Cost,								//玩家之间交易的手续费
	Num_Business_Discount,							//NPC交易时的卖价折扣

	Num_BindSilverCostLimitParam1 = 3010,					// 玩家每日银票消费上限计算公式参数1
	Num_BindSilverCostLimitParam2,							// 玩家每日银票消费上限计算公式参数2

	Num_BindSilverCarryLimitParam1 = 3015,					// 玩家银票携带上限计算公式参数1
	Num_BindSilverCarryLimitParam2,							// 玩家银票携带上限计算公式参数2
	Num_BindSilverCarryLimitParam3,							// 玩家银票携带上限计算公式参数2

	NUM_BINDSILVER_DAY_USEUPPERLIMIT = 3050,		//绑定银子每天使用上限
	NPC_BusinessTax,                                //NPC交易国家税参数
	NPC_BusinessTax_Add,                            //NPC交易国家税外加税（国家圣水为0时加税）


	//拍卖系统
	Auction_Param_Cost1 = 3100,						//拍卖费用8小时
	Auction_Param_Cost2,							//拍卖费用12小时
	Auction_Param_Cost3,							//拍卖费用24小时
	Auction_Param_Tax,								//拍卖税收比例

	//摆摊系统
	Stall_Param_Cost = 3200,						//摆摊费用

	//仓库系统
	Warehouse_Param_LatticeNum = 3300,				//仓库位置数提升
	Warehouse_Param_Cost,							//费用

	//pk系统
	PK_Param_Hunt1 = 3400,							//追捕1分钟
	PK_Param_Hunt2,									//追捕5分钟
	PK_Param_Hunt3,									//追捕10分钟

	//监狱系统
	Prison_Param_Percent = 3500,					//监狱概率
	Prison_Param_SinPercent,						//罪恶值比
	Prison_Param_SinValue,							//罪恶值/监禁时间
	Prison_Param_RedNameTime,						//红名时间/人
	Prison_Param_HonorsExchangSin,					//罪恶/荣誉（荣誉洗罪恶）
	Prison_Param_CommutationCost,					//花钱减刑期（钱/分钟）

	WHITE_NAME_DROP_NUMS = 3506,                    //白名死亡掉落道具个数
	WHITE_NAME_DROP_ODDS,                           //白名死亡掉落道具概率
	GRAY_NAME_DROP_NUMS,                            //灰名死亡掉落道具个数
	GRAY_NAME_DROP_ODDS,                            //灰名死亡掉落道具概率
	RED_NAME_DROP_NUMS,                             //红名死亡掉落道具个数
	RED_NAME_DROP_ODDS,                             //红名死亡掉落道具概率

	PK_Protected_Level	  = 3512,					//PK保护等级（策划在数据库中填写的此值）

	Num_Death_PropHp_Lost = 3550,                    //死亡掉落道具耐久值

	//活动参数
	Campaign_Dance_ExpSecond=3600,					//跳舞加经验的秒数
	Campaign_Dance_BaseExp,							//跳舞基础经验值奖励	
	Campaign_Dance_DecreaseEngegy,					//跳舞减少的精力值
	Campaign_Dance_AddPropSecond,					//跳舞增加道具的秒数
	Campaign_Dacne_UseCount,						//熟练度的秒数


	//////////////////其它参数////////////////////////////////////
	//同屏表
	Explorer_Param_Area = 4000,						//同屏表范围
	Explorer_Param_PersonNum,						//同屏表量

	Param_Quest_GetExpPercent = 4100,				//任务经验值获取比例
	Param_Monster_GetExpPercent,					//怪物经验值获取比例
	Param_Prestige_GetExpPercent,					//声望值获取比例
	Param_Money_GetPercent,							//金钱获得比例
	Param_Drop_GetPercent,							//掉落量比例
	Param_GainMoney_Percent,						//金钱收益系数

	Param_Quest_20Percent = 4110,					//20活动比
	Param_Quest_40Percent,							//40活动比
	Param_Quest_60Percent,							//60活动比
	Param_Quest_80Percent,							//80活动比
	Param_Quest_100Percent,							//100活动比
	Param_Quest_120Percent,							//120活动比
	Param_Quest_140Percent,							//140活动比
	Param_Quest_160Percent,							//160活动比

	//活动
	Family_Boss_CreatRand1 = 5001,					//随即初级boss
	Family_Boss_CreatRand2,							//中级boss
	Family_Boss_CreatRand3,							//高级boss
	Action_Family_Boss_Grace,						//功勋
	Action_Family_Boss_Scale,						//活动比例
	Action_Family_Boss_Weights,						//活动权值
	Family_Boss_Level1,								//boss的等级
	Family_Boss_Level2,						
	Family_Boss_Level3,
	Family_Boss_Level4,
	Family_Boss_Level5,
	Family_Boss_Grow1,								//boss的成长值
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
	Family_Boss_Feed_Credit ,						//喂养家族boss获取的家族贡献度
	FamilyBossLevelMultiple,						//家族boss等级倍率

	Campaign_Question_Base =5050,					//活动比例
	Campaign_Question_Power,						//活动权值
	Camapign_Question_WencaiBase,					//文采比例
	Campaign_Question_PointBase,					//得分比例

	Quest_Target_SafeTime=6000,						//防守目标被攻击后的恢复状态时间
	Quest_Target_ReHpTime,							//防守目标的回复时间
	Quest_Car_UnderAttackTime,						//镖车被攻击后，不动的秒数

	////////////////////////向客户端同步的参数/////////////////////////////////////
	Client_Gift_Time1 = 7000,						//时间礼包发送时间
	Client_Gift_Time2,								//时间礼包发送时间
	Client_Gift_Time3,								//时间礼包发送时间
	Client_Gift_Time4,								//时间礼包发送时间
	Client_Gift_Time5,								//时间礼包发送时间
	Client_Gift_Time6,								//时间礼包发送时间
	Client_Gift_Time7,								//时间礼包发送时间
	Client_Gift_Time8,								//时间礼包发送时间
	Client_Gift_Time9,								//时间礼包发送时间
	Client_Gift_Time10,								//时间礼包发送时间

	Client_Gift_PropID1,							//时间礼包发送道具
	Client_Gift_PropID2,							//时间礼包发送道具
	Client_Gift_PropID3,							//时间礼包发送道具
	Client_Gift_PropID4,							//时间礼包发送道具
	Client_Gift_PropID5,							//时间礼包发送道具
	Client_Gift_PropID6,							//时间礼包发送道具
	Client_Gift_PropID7,							//时间礼包发送道具
	Client_Gift_PropID8,							//时间礼包发送道具
	Client_Gift_PropID9,							//时间礼包发送道具
	Client_Gift_PropID10,							//时间礼包发送道具

	Client_Gift_PropID11,							//时间礼包发送道具
	Client_Gift_PropID12,							//时间礼包发送道具
	Client_Gift_PropID13,							//时间礼包发送道具
	Client_Gift_PropID14,							//时间礼包发送道具
	Client_Gift_PropID15,							//时间礼包发送道具
	Client_Gift_PropID16,							//时间礼包发送道具
	Client_Gift_PropID17,							//时间礼包发送道具
	Client_Gift_PropID18,							//时间礼包发送道具
	Client_Gift_PropID19,							//时间礼包发送道具
	Client_Gift_PropID20,							//时间礼包发送道具

	Client_Gift_PropID21,							//时间礼包发送道具
	Client_Gift_PropID22,							//时间礼包发送道具
	Client_Gift_PropID23,							//时间礼包发送道具
	Client_Gift_PropID24,							//时间礼包发送道具
	Client_Gift_PropID25,							//时间礼包发送道具
	Client_Gift_PropID26,							//时间礼包发送道具
	Client_Gift_PropID27,							//时间礼包发送道具
	Client_Gift_PropID28,							//时间礼包发送道具
	Client_Gift_PropID29,							//时间礼包发送道具
	Client_Gift_PropID30,							//时间礼包发送道具

	Client_Gift_PropID31,							//时间礼包发送道具
	Client_Gift_PropID32,							//时间礼包发送道具
	Client_Gift_PropID33,							//时间礼包发送道具
	Client_Gift_PropID34,							//时间礼包发送道具
	Client_Gift_PropID35,							//时间礼包发送道具
	Client_Gift_PropID36,							//时间礼包发送道具
	Client_Gift_PropID37,							//时间礼包发送道具
	Client_Gift_PropID38,							//时间礼包发送道具
	Client_Gift_PropID39,							//时间礼包发送道具
	Client_Gift_PropID40,							//时间礼包发送道具

	Client_Gift_PropID41,							//时间礼包发送道具
	Client_Gift_PropID42,							//时间礼包发送道具
	Client_Gift_PropID43,							//时间礼包发送道具
	Client_Gift_PropID44,							//时间礼包发送道具
	Client_Gift_PropID45,							//时间礼包发送道具
	Client_Gift_PropID46,							//时间礼包发送道具
	Client_Gift_PropID47,							//时间礼包发送道具
	Client_Gift_PropID48,							//时间礼包发送道具
	Client_Gift_PropID49,							//时间礼包发送道具
	Client_Gift_PropID50,							//时间礼包发送道具

	Client_Gift_PropID51,							//时间礼包发送道具
	Client_Gift_PropID52,							//时间礼包发送道具
	Client_Gift_PropID53,							//时间礼包发送道具
	Client_Gift_PropID54,							//时间礼包发送道具
	Client_Gift_PropID55,							//时间礼包发送道具
	Client_Gift_PropID56,							//时间礼包发送道具
	Client_Gift_PropID57,							//时间礼包发送道具
	Client_Gift_PropID58,							//时间礼包发送道具
	Client_Gift_PropID59,							//时间礼包发送道具
	Client_Gift_PropID60,							//时间礼包发送道具

	Client_Gift_PropID61,							//时间礼包发送道具
	Client_Gift_PropID62,							//时间礼包发送道具
	Client_Gift_PropID63,							//时间礼包发送道具
	Client_Gift_PropID64,							//时间礼包发送道具
	Client_Gift_PropID65,							//时间礼包发送道具
	Client_Gift_PropID66,							//时间礼包发送道具
	Client_Gift_PropID67,							//时间礼包发送道具
	Client_Gift_PropID68,							//时间礼包发送道具
	Client_Gift_PropID69,							//时间礼包发送道具
	Client_Gift_PropID70,							//时间礼包发送道具

	Client_Gift_PropID71,							//时间礼包发送道具
	Client_Gift_PropID72,							//时间礼包发送道具
	Client_Gift_PropID73,							//时间礼包发送道具
	Client_Gift_PropID74,							//时间礼包发送道具
	Client_Gift_PropID75,							//时间礼包发送道具
	Client_Gift_PropID76,							//时间礼包发送道具
	Client_Gift_PropID77,							//时间礼包发送道具
	Client_Gift_PropID78,							//时间礼包发送道具
	Client_Gift_PropID79,							//时间礼包发送道具
	Client_Gift_PropID80,							//时间礼包发送道具

	Client_Gift_PropID81,							//时间礼包发送道具
	Client_Gift_PropID82,							//时间礼包发送道具
	Client_Gift_PropID83,							//时间礼包发送道具
	Client_Gift_PropID84,							//时间礼包发送道具
	Client_Gift_PropID85,							//时间礼包发送道具
	Client_Gift_PropID86,							//时间礼包发送道具
	Client_Gift_PropID87,							//时间礼包发送道具
	Client_Gift_PropID88,							//时间礼包发送道具
	Client_Gift_PropID89,							//时间礼包发送道具
	Client_Gift_PropID90,							//时间礼包发送道具

	Client_Gift_PropID91,							//时间礼包发送道具
	Client_Gift_PropID92,							//时间礼包发送道具
	Client_Gift_PropID93,							//时间礼包发送道具
	Client_Gift_PropID94,							//时间礼包发送道具
	Client_Gift_PropID95,							//时间礼包发送道具
	Client_Gift_PropID96,							//时间礼包发送道具
	Client_Gift_PropID97,							//时间礼包发送道具
	Client_Gift_PropID98,							//时间礼包发送道具
	Client_Gift_PropID99,							//时间礼包发送道具
	Client_Gift_PropID100,							//时间礼包发送道具

	Client_Gift_PropCount,							//礼包总数量
	Client_Gift_TakeTimes,							//每天领取数量

	Client_Family_SkillLevel,						//家族技能等级
	Client_Family_ResearchSkill_Cost,				//家族技能研究消耗家族资金基值
	Client_Family_LearnSkill_Cost,					//家族技能学习消耗贡献度基值
	Client_Family_ResearchSkill_Rate,				//家族研究技能消耗家族资金比率
	Client_Family_LearnSkill_Rate,					//家族学习技能消耗贡献度比率
	Client_Family_Active,							//家族繁荣度基值
	Client_Family_Active_Rate,						//家族繁荣度比率

	Client_Gift_Max_Everyday,						//每天可领取的礼包数
	Client_Gift_Max_Times,							//总共可领取的包的数量

	Client_Revive_Cost_ToTown = 7201,				//安全复活所需的费用
	Client_Revive_Cost_InSitu,						//原地复活所需的费用
	Client_Revive_Cost_FullStatus,					//满状态复活所需的费用
	Client_Revive_Cost_Append,						//虚弱复活和满状态复活所需的附加费用

	//活跃度参数
	Vitality_Family_Wage = 7500,					//家族成员活跃度计算参数
	Vitality_Family_HuoDongDuN,						//家族转化比例的活动度参数
	Family_Wage_BaseValue,							//工资基础值

	//战斗功勋兑换所需要的功勋值
	CombatCredit_Sanlue = 7510,
	CombatCredit_LiuTao,
	CombatCredit_MengDeXinShu,
	CombatCredit_SunZiBingFa,
	CombatCredit_ExchangeNum,						//战斗功勋兑换次数 add by zhangjianli 2012-10-12

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
