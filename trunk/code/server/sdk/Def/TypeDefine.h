#pragma	  once


#define GetLeftSingle(n)	(n/100000000)
#define GetLeftTwo(n)		(n/1000000)
#define GetLeftThree(n)		(n/10000)
#define GetLeftFour(n)		(n/100)	
#define GetLeftFive(n)		(n/1)


const int OBJTYPE_INVALID									= -1;			//无效的obj类型
const int OBJTYPE_USER										= 1;			//User
const int OBJTYPE_MAPOBJ									= 100000;		
const int OBJTYPE_MAPOBJ_MPW								= 101000;		//mpw
const int OBJTYPE_MAPOBJ_NPC								= 102000;		//editor Npc
const int OBJTYPE_MAPOBJ_CPOINT								= 103000;		//生成点
																			
const int OBJTYPE_ROLE										= 100000000;	//人物
const int OBJTYPE_ROLE_PLAYER								= 101000000;	//玩家					
const int OBJTYPE_ROLE_NPC									= 102000000;	//非玩家
const int OBJTYPE_ROLE_NPC_NAMENPC							= 102010000;	//Name NPC & Boss	
//const int OBJTYPE_ROLE_NPC_NAMENPC_STALL					= 102010100;	//摆摊车				//--废弃-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_MOB								= 102020000;	//普通小怪			
const int OBJTYPE_ROLE_NPC_MOB_COMMON						= 102020100;	//普通怪
const int OBJTYPE_ROLE_NPC_MOB_SPECIAL						= 102020200;	//精英怪
const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Normal_L				= 102020201;	//普通精英怪1-90
const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Normal_H				= 102020202;	//普通精英怪90-160
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_F_N			= 102020203;	//前场小怪			//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_B_N			= 102020204;	//后场小怪			//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_F_P			= 102020205;	//前场巡逻怪		//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_B_P			= 102020206;	//后场巡逻怪		//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_F_G			= 102020207;	//前场门神			//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_B_G			= 102020208;	//后场门神			//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_A_Fun			= 102020209;	//功能精英怪	//--废弃-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_MOB_SPECIAL2						= 102020300;	//高级怪
const int OBJTYPE_ROLE_NPC_MOB_FELLOW						= 102020400;	//珍兽怪（用来捕捉，捕捉后成为珍兽）
const int OBJTYPE_ROLE_BOSS									= 102050000;	//BOSS
const int OBJ_ROLE_BOSS_FUBEN								= 102050100;	//副本Boss
const int OBJ_ROLE_BOSS_FUBEN_Single						= 102050101;	//普通BOSS
//const int OBJ_ROLE_BOSS_FUBEN_Compose						= 102050102;	//组合BOSS		
//const int OBJ_ROLE_BOSS_FUBEN_BOX							= 102050103;	//BOSS宝箱		
//const int OBJ_ROLE_BOSS_FUBEN_N_BOX						= 102050104;	//副本宝箱		
const int OBJ_ROLE_BOSS_FUBEN_Call							= 102050105;	//BOSS召唤怪		
//const int OBJ_ROLE_BOSS_FUBEN_Quest						= 102050106;	//任务boss		//--废弃，只留一个任务BOSS-- del by zhaoguoze 2011-09-19
const int OBJ_ROLE_BOSS_UNDERCITY							= 102050200;	//地下城Boss
const int OBJ_ROLE_BOSS_UNDERCITY_A							= 102050201;	//地下城BossA
const int OBJ_ROLE_BOSS_UNDERCITY_B							= 102050202;	//地下城BossB
const int OBJ_ROLE_BOSS_WORLD								= 102050300;	//世界Boss
const int OBJ_ROLE_BOSS_WORLD_A								= 102050301;	//世界BossA
const int OBJ_ROLE_BOSS_WORLD_B								= 102050302;	//世界BossB
const int OBJ_ROLE_BOSS_QUEST								= 102050400;	//任务boss		
const int OBJ_ROLE_BOSS_WILD								= 102050500;	//野外boss
const int OBJ_ROLE_BOSS_WILD_A								= 102050501;	//野外bossA
const int OBJ_ROLE_BOSS_WILD_B								= 102050502;	//野外bossB
const int OBJTYPE_ROLE_AURA									= 102060000;	//光环
const int OBJTYPE_ROLE_NPC_ZONE								= 102070000;	//触发器类型
const int OBJTYPE_ROLE_NPC_TRAP								= 102070100;	//陷阱
//const int OBJTYPE_ROLE_NPC_PORTAL							= 102070200;	//传送门				//--废弃-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_LAND								= 102070300;	//地雷
//const int OBJTYPE_ROLE_NPC_LAND_FALSE						= 102070301;	//假地雷			//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_TRIGGERPROP					= 102070400;	//触发类道具单体		//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_TRIGGERPROP_MULTI				=102070500;		//触发群体类道具	//--废弃-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_PET								= 102080000;	//宠物类型
																			
const int OBJTYPE_ROLE_NPC_PET_ZUOQI						= 102080200;	//坐骑
const int OBJTYPE_ROLE_NPC_PET_ZUOQI_COMMONHORSE			= 102080201;	//坐骑类型（普通马）change by zhangjianli 2011-12-07
const int OBJTYPE_ROLE_NPC_PET_ZUOQI_COMMONBIRD				= 102080202;	//坐骑类型（普通鸟）change by zhangjianli 2011-12-07
const int OBJTYPE_ROLE_NPC_PET_ZUOQI_COMBATHORSE			= 102080203;	//坐骑类型（战马）  add by zhangjianli 2011-12-07
const int OBJTYPE_ROLE_NPC_PET_ZUOQI_COMBATBIRD				= 102080204;	//坐骑类型（战鸟）  add by zhangjianli 2011-12-07

const int OBJTYPE_ROLE_NPC_PET_Combat						= 102080300;	//战宠
const int OBJTYPE_ROLE_NPC_PET_ShootCombat_Beast			= 102080301;	//射手召唤战宠（之前的野兽类型）
//const int OBJTYPE_ROLE_NPC_PET_ShootCombat_SpiritBeast	= 102080302;	//灵兽	//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_PET_ShootCombat_SaintBeast		= 102080303;	//圣兽		//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_PET_MonsterCombat_Ghost		= 102080311;	//鬼魅	//--废弃-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_PET_MonsterCombat_AquaSpirit		= 102080312;	//道士召唤战宠（之前的水灵类型）
//const int OBJTYPE_ROLE_NPC_PET_MonsterCombat_FireSpirit	= 102080313;	//火灵		//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_PET_MonsterCombat_DarkSpirit	= 102080314;	//暗鬼		//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_PET_MonsterCombat_WindSpirit	= 102080315;	//风灵		//--废弃-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_CAT								= 102090000;	//战车
const int OBJTYPE_ROLE_NPC_PRIVATE_CAT						= 102090100;	//个人镖车
const int OBJTYPE_ROLE_NPC_FAMILY_CAT						= 102090200;	//家族战车
const int OBJTYPE_ROLE_NPC_FAMILY_PRIVATECAT				= 102090400;	//家族镖车
//const int OBJTYPE_ROLE_NPC_FAMILY_COMMON_CAT				= 102090201;	//家族普通战车		//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_FAMILY_DRAGON_CAT				= 102090202;	//家族龙战车		//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_FAMILY_TIGER_CAT				= 102090203;	//家族虎战车	//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_FAMILY_COLLECT_CAT				= 102090204;	//家族采集车	//--废弃-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MARRY_CAT						= 102090300;	//婚车		//--废弃-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_SPIRIT							= 102100000;	//精灵类
																			
const int OBJTYPE_ROLE_NPC_BOAT								= 102200000;	//在水中能行走的船类
																			
const int OBJTYPE_ROLE_NPC_PET_FELLOW						= 103000000;	//--珍兽（玩家可携带宠物）--
																			
const int OBJTYPE_ROLE_GOD									= 104000000;	//上帝		
const int OBJTYPE_ROLE_ANIMAL								= 105000000;	//小动物
																			
const int OBJTYPE_PROP										= 200000000;	//道具
const int OBJTYPE_PROP_EQUIPMENT							= 201000000;	//装备
const int OBJTYPE_PROP_EQUIPMENT_WEAPEN						= 201010000;	//武器
const int OBJTYPE_PROP_EQUIPMENT_WEAPEN_PHYSICAL			= 201010100;	//武师
const int OBJTYPE_PROP_EQUIPMENT_WEAPEN_MAGIC				= 201010200;	//术士
const int OBJTYPE_PROP_EQUIPMENT_WEAPEN_TOXOPHILY			= 201010300;	//射手
const int OBJTYPE_PROP_EQUIPMENT_WEAPEN_BLACKART			= 201010400;	//道术
const int OBJTYPE_PROP_EQUIPMENT_WEAPEN_THEURGY				= 201010500;	//药师
const int OBJTYPE_PROP_EQUIPMENT_ARMOR						= 201020000;	//装备防具类
const int OBJTYPE_PROP_EQUIPMENT_ARMOR_HEAD					= 201020100;	//头盔
const int OBJTYPE_PROP_EQUIPMENT_ARMOR_CHEST				= 201020200;	//衣服
const int OBJTYPE_PROP_EQUIPMENT_ARMOR_WAIST				= 201020300;	//腰带
const int OBJTYPE_PROP_EQUIPMENT_ARMOR_HANDS				= 201020400;	//护腕
const int OBJTYPE_PROP_EQUIPMENT_ARMOR_FEETS				= 201020500;	//靴子
const int OBJTYPE_PROP_EQUIPMENT_JEWELRY					= 201030000;	//饰品
const int OBJTYPE_PROP_EQUIPMENT_JEWELRY_NECKLACE			= 201030100;	//项链
const int OBJTYPE_PROP_EQUIPMENT_JEWELRY_RINGS				= 201030200;	//戒指
const int OBJTYPE_PROP_EQUIPMENT_JEWELRY_SHIPIN				= 201030300;	//饰品
const int OBJTYPE_PROP_EQUIPMENT_PET						= 201040000;	//宠物装备
const int OBJTYPE_PROP_EQUIPMENT_PET_SADDLE					= 201040100;	//马鞍
const int OBJTYPE_PROP_EQUIPMENT_PET_HORSEWHIP				= 201040200;	//马鞭
const int OBJTYPE_PROP_EQUIPMENT_PET_WESKIT					= 201040300;	//马甲
const int OBJTYPE_PROP_EQUIPMENT_PET_SPUR					= 201040400;	//马刺		
const int OBJTYPE_PROP_EQUIPMENT_PET_FASHION				= 201040500;	//马匹时装
const int OBJTYPE_PROP_EQUIPMENT_SPECIAL					= 201050000;	//特殊装备
const int OBJTYPE_PROP_EQUIPMENT_SPECIAL_FASHION			= 201050100;	//时装
const int OBJTYPE_PROP_EQUIPMENT_SPECIAL_MANTLE				= 201050200;	//披风
const int OBJTYPE_PROP_EQUIPMENT_SPECIAL_ENSIGN				= 201050300;	//军旗
const int OBJTYPE_PROP_EQUIPMENT_ASSWEAP					= 201060000;	//副手
const int OBJTYPE_PROP_EQUIPMENT_ASSWEAP_PHYSICAL			= 201060100;	//武师
const int OBJTYPE_PROP_EQUIPMENT_ASSWEAP_MAGIC				= 201060200;	//术士
const int OBJTYPE_PROP_EQUIPMENT_ASSWEAP_TOXOPHILY			= 201060300;	//射手
const int OBJTYPE_PROP_EQUIPMENT_ASSWEAP_BLACKART			= 201060400;	//道术
const int OBJTYPE_PROP_EQUIPMENT_ASSWEAP_THEURGY			= 201060500;	//药师
																			
const int OBJTYPE_PROP_STUFF								= 202000000;	//材料	
const int OBJTYPE_PROP_STUFF_COMPOSE						= 202010000;	//打造材料
const int OBJTYPE_PROP_STUFF_COMPOSE_WOOD					= 202010100;	//木材
const int OBJTYPE_PROP_STUFF_COMPOSE_METAL					= 202010200;	//金属
const int OBJTYPE_PROP_STUFF_COMPOSE_LEATHER				= 202010300;	//皮革
const int OBJTYPE_PROP_STUFF_COMPOSE_PIECE					= 202010400;	//布匹
const int OBJTYPE_PROP_STUFF_COMPOSE_STONE					= 202010500;	//石头
const int OBJTYPE_PROP_STUFF_ADDSTAR						= 202020000;	//加星材料
const int OBJTYPE_PROP_STUFF_ADDSTAR_YOUSHI					= 202020100;	//玉石
const int OBJTYPE_PROP_STUFF_PETADDSTAR_YOUSHI				= 202020200;	//珍兽强化石头
const int OBJTYPE_PROP_STUFF_SEALSTONE						= 202020300;	//封星石头
const int OBJTYPE_PROP_STUFF_SIGN							= 202030000;	//签名材料
const int OBJTYPE_PROP_STUFF_SIGN_YINZHANG					= 202030100;	//印章
const int OBJTYPE_PROP_STUFF_BIND							= 202040000;	//绑定材料
const int OBJTYPE_PROP_STUFF_BIND_FUWEN						= 202040100;	//符文
const int OBJTYPE_PROP_STUFF_ADDHOLE						= 202050000;	//打孔材料 摧毁宝石材料
const int OBJTYPE_PROP_STUFF_ADDHOLE_ZUANTOU				= 202050100;	//钻头
const int OBJTYPE_PROP_STUFF_ENCHASE						= 202060000;	//镶嵌材料
const int OBJTYPE_PROP_STUFF_ENCHASE_GEM					= 202060100;	//宝石
																			
const int OBJTYPE_PROP_MEDICAMENT							= 203000000;	//药剂
const int OBJTYPE_PROP_MEDICAMENT_COMMON					= 203010000;	//普通药剂
const int OBJTYPE_PROP_MEDICAMENT_COMMON_HP					= 203010100;	//生命
const int OBJTYPE_PROP_MEDICAMENT_COMMON_MP					= 203010200;	//法力
const int OBJTYPE_PROP_MEDICAMENT_ENERGY					= 203020000;	//精化
const int OBJTYPE_PROP_MEDICAMENT_ENERGY_HP					= 203020100;	//生命精化
const int OBJTYPE_PROP_MEDICAMENT_ENERGY_MP					= 203020200;	//法力精化
const int OBJTYPE_PROP_MEDICAMENT_SPEC						= 203030000;	//特殊药剂
const int OBJTYPE_PROP_MEDICAMENT_SPEC_ATTR					= 203030100;	//特殊属性
const int OBJTYPE_PROP_MEDICAMENT_SPEC_FUNC					= 203030200;	//特殊功能
																			
const int OBJTYPE_PROP_BOOK									= 204000000;	//技能书
const int OBJTYPE_PROP_BOOK_PHYSICAL						= 204010000;	//武术系
const int OBJTYPE_PROP_BOOK_MAGIC							= 204020000;	//法术系
const int OBJTYPE_PROP_BOOK_TOXOPHILY						= 204030000;	//射术系
const int OBJTYPE_PROP_BOOK_BLACKART						= 204040000;	//妖术系
const int OBJTYPE_PROP_BOOK_THEURGY							= 204050000;	//仙术系
const int OBJTYPE_PROP_BOOK_PET								= 204060000;	//宠物技能书
																			
const int OBJTYPE_PROP_SPECIALITY							= 206000000;	//特产
																			
const int OBJTYPE_PROP_FUMO									= 207000000;	//附魔
const int OBJTYPE_PROP_FUMO_METHOD							= 207010000;	//附魔配方
const int OBJTYPE_PROP_FUMO_MATERIAL						= 207020000;	//附魔材料
const int OBJTYPE_PROP_FUMO_CHARM							= 207030000;	//附魔咒符
																			
const int OBJTYPE_PROP_FUNCTION								= 208000000;	//功能类
const int OBJTYPE_PROP_FUNCTION_REEL						= 208010000;	//传送卷轴
const int OBJTYPE_PROP_FUNCTION_CONTAINER					= 208040000;	//背包

const int OBJTYPE_PROP_FUNCTION_OTHER	                    = 208050000;     //--其它

const int OBJTYPE_PROP_FUNCTION_BOOTH						= 208060000;	//摆摊车
const int OBJTYPE_PROP_FUNCTION_HONOR						= 208070000;	//荣誉道具
const int OBJTYPE_PROP_CAR									= 208080000;	//战车
const int OBJTYPE_PROP_CAR_FAMILY							= 208080100;	//家族战车
const int OBJTYPE_PROP_HEALTH_CAR_FAMILY					= 208080101;	//家族生命型战车
const int OBJTYPE_PROP_DAMAGE_CAR_FAMILY					= 208080102;	//家族攻击型战车
const int OBJTYPE_PROP_DEFENCE_CAR_FAMILY					= 208080103;	//家族防御型战车
const int OBJTYPE_PROP_CAR_FAMILY_COLLECT					= 208080104;	//家族采集车
//const int OBJTYPE_PROP_CAR_GANG							= 208080200;	//帮会战车
const int OBJTYPE_PROP_FUNCTION_FAMILY						= 208090000;	//家族帮会功能道具
const int OBJTYPE_PROP_FUNCTION_FAMILY_DICHAN				= 208090100;	//地产证明
const int OBJTYPE_PROP_FUNCTION_FAMILY_MAGICBOX				= 208090200;	//家族箱子
const int OBJTYPE_PROP_FUNCTION_FAMILY_FOOD					= 208090300;	//boss食物
const int OBJTYPE_PROP_FUNCTION_FAMILY_QUEST				= 208090400;	//随机道具
const int OBJTYPE_PROP_FUNCTION_FEEDS						= 208100000;	//饲料
const int OBJTYPE_PROP_FUNCTION_FEEDS_PET					= 208100100;	//侍从饲料
const int OBJTYPE_PROP_FUNCTION_FEEDS_RIDE					= 208100200;	//坐骑饲料
																			
const int OBJTYPE_PROP_PET									= 209000000;	//宠物
const int OBJTYPE_PROP_PET_EGG								= 209010000;	//宠物蛋
const int OBJTYPE_PROP_PET_ZUOQI							= 209020000;	//坐骑
const int OBJTYPE_RPOP_PET_COMBAT							= 209030000;	//战宠
																			
const int OBJTYPE_PROP_MISSION								= 210000000;		//任务道具
const int OBJTYPE_PROP_MISSION_BOOK							= 210010000;	//书信
const int OBJTYPE_PROP_MISSION_USED							= 210020000;	//使用
const int OBJTYPE_PROP_MISSION_EQUIP						= 210030000;	//任务装备
																			
const int OBJTYPE_PROP_GUOCE								= 211000000;	//国策
const int OBJTYPE_PROP_HUFU									= 212000000;	//虎符
const int OBJTYPE_PROP_SHENGWANG							= 213000000;	//声望
const int OBJTYPE_PROP_ZHANHUN								= 214000000;	//战魂石
																			
const int OBJTYPE_SKILL										= 300000000;	//技能	
const int OBJTYPE_SKILL_COMMON								= 301000000;	//普通攻击

const int OBJTYPE_SKILL_TREESKILL							= 302000000;	//人物技能					
const int OBJTYPE_SKILL_TREESKILL_PHYSICAL					= 302010000;	//武术系技能
const int OBJTYPE_SKILL_TREESKILL_MAGIC						= 302020000;	//法术系技能
const int OBJTYPE_SKILL_TREESKILL_TOXOPHILY					= 302030000;	//射术系技能
const int OBJTYPE_SKILL_TREESKILL_BLACKART					= 302040000;	//妖术系技能
const int OBJTYPE_SKILL_TREESKILL_THEURGY					= 302050000;	//仙术系技能
const int OBJTYPE_SKILL_LIFESKILL							= 303000000;	//生活技能
const int OBJTYPE_SKILL_NPCSKILL							= 304000000;	//NPC技能
const int OBJTYPE_SKILL_PROPSKILL							= 305000000;	//道具技能
const int OBJTYPE_SKILL_PROP_ENCHANTING						= 305010000;	//附魔技能
const int OBJTYPE_SKILL_PROP_FUNCTION						= 305020000;	//道具功能技能（装备道具自动获得使用技能的能力）
const int OBJTYPE_SKILL_PETSKILL							= 306000000;	//宠物技能
const int OBJTYPE_SKILL_PETSKILL_SELF						= 306010000;	//宠物自身攻击技能
const int OBJTYPE_SKILL_PETSKILL_PLAYER						= 306020000;	//宠物合体技能
const int OBJTYPE_SKILL_PETSKILL_SAFEGUARD					= 306030000;	//宠物守护技能
const int OBJTYPE_SKILL_AddSkill							= 307000000;	//附加技能
const int OBJTYPE_SKILL_SOCIETYSKILL						= 308000000;	//社会技能
const int OBJTYPE_SKILL_SOCIETYSKILL_FAMILY					= 308010000;	//家族技能
const int OBJTYPE_SKILL_SOCIETYSKILL_TEAM					= 308020000;	//队伍技能
const int OBJTYPE_SKILL_SOCIETYSKILL_BANG					= 308030000;	//帮会技能
const int OBJTYPE_SKILL_TALENT								= 309000000;	//天赋技能（自动学习）
const int OBJTYPE_SKILL_RAGE								= 310000000;	//怒气技能
const int OBJTYPE_SKILL_XINFA								= 311000000;	//心法技能
																			
const int OBJTYPE_SCENE										= 400000000;	//场景
const int OBJTYPE_SCENE_CITY								= 401000000;	//普通场景
const int OBJTYPE_SCENE_UNDERGROUD_CITY						= 402000000;	//单开场景
const int OBJTYPE_SCENE_FAMILY_CITY							= 402010000;	//家族副本
const int OBJTYPE_SCENE_GANG_CITY							= 402020000;	//帮会副本
const int OBJTYPE_SCENE_TEAM_CITY							= 402030000;	//队伍副本
const int OBJTYPE_SCENE_PRIVATE_CITY						= 402040000;	//个人副本
const int OBJTYPE_SCENE_CAMPAIGN_CITY						= 402050000;	//活动副本
															
const int OBJTYPE_SERVER									= 500000000;	//服务器类型
const int OBJTYPE_SERVER_SUPER								= 501000000;	//Super Server
const int OBJTYPE_SERVER_DB									= 502000000;	//DB Server
const int OBJTYPE_SERVER_GAME								= 503000000;	//游戏服务器
const int OBJTYPE_SERVER_GAME_COMMAND						= 203010000;	//普通场景
const int OBJTYPE_SERVER_GAME_UNDERGROUP					= 203020000;	//单开房间服务器
const int OBJTYPE_SERVER_LOGIN								= 504000000;	//Login Server
//const int OBJTYPE_SERVER_CHECKUSER						= 514000000;	//Login Server  Check User
const int OBJTYPE_SERVER_COMMUNIT							= 505000000;	//社会关系服务器
const int OBJTYPE_SERVER_MAIL								= 506000000;	//邮件拍卖服务器
const int OBJTYPE_SERVER_BACKUP								= 507000000;	//备份服务器
const int OBJTYPE_SERVER_MONITOR							= 508000000;	//监视服务器
const int OBJTYPE_SERVER_GATEWAY							= 509000000;	//GateWay 服务器
const int OBJTYPE_SERVER_DNS								= 510000000;	//DNS 服务器
const int OBJTYPE_SERVER_CHECK								= 511000000;	//计费&验证服务器
const int OBJTYPE_SERVER_TOP								= 512000000;	//排名服务器
const int OBJTYPE_SERVER_GM									= 513000000;	//GM服务器
const int OBJTYPE_SERVER_GMC								= 514000000;	//运维GMC服务器
const int OBJTYPE_SERVER_GMTOOL								= 515000000;	//GM工具
const int OBJTYPE_SERVER_NAME								= 516000000;	//NAME 服务器
																			
																			
const int OBJTYPE_QUEST										= 600000000;	//任务
const int OBJTYPE_QUEST_COMMON								= 601000000;	//主线任务
const int OBJTYPE_QUEST_COMMON_FRIEND						= 601010000;	//好友任务
const int OBJTYPE_QUEST_COMMON_MASTER						= 601020000;	//徒弟任务
const int OBJTYPE_QUEST_COMMON_MARRY						= 601030000;	//夫妻任务
const int OBJTYPE_QUEST_COMMON_FAMILY						= 601040000;	//家族任务
const int OBJTYPE_QUEST_COMMON_GANG							= 601050000;	//帮会任务
const int OBJTYPE_QUEST_COMMON_WEEKSTATE					= 601060000;	//弱国任务
const int OBJTYPE_QUEST_COMMON_STRENTHSTATE					= 601070000;	//强国任务
const int OBJTYPE_QUEST_GREEN								= 602000000;	//绿装任务
const int OBJTYPE_QUEST_CREDIT								= 603000000;	//声望任务		
const int OBJTYPE_QUEST_CAMPAIGN							= 604000000;	//活动任务
const int OBJTYPE_QUEST_CAMPAIGN_PRIVATE					= 604010000;	//个人活动
const int OBJTYPE_QUEST_CAMPAIGN_FAMILY						= 604020000;	//家族活动
const int OBJTYPE_QUEST_CAMPAIGN_GANG						= 604030000;	//帮会活动
const int OBJTYPE_QUEST_CAMPAIGN_STATE						= 604040000;	//国家活动
const int OBJTYPE_QUEST_QUEST								= 605000000;	//答题活动
const int OBJTYPE_QUEST_UNDERCITY							= 606000000;	//副本任务
const int OBJTYPE_QUEST_HELP								= 607000000;	//帮助任务
const int OBJTYPE_QUEST_THREAD								= 608000000;	//支线任务
const int OBJTYPE_QUEST_RANDOM								= 608010000;	//随机任务
const int OBJTYPE_QUEST_STORY								= 609000000;	//剧情任务
const int OBJTYPE_QUEST_TREASURE							= 610000000;	//珍品任务
const int OBJTYPE_QUEST_SKILLPOINT							= 611000000;	//技能点任务
												
const int OBJTYPE_MAIL										= 700000000;	//邮件	
const int OBJTYPE_BUFF										= 800000000;	//buff
const int OBJTYPE_BUFF_ROLE									= 801000000;	//玩家buff
const int OBJTYPE_BUFF_PROP									= 802000000;	//道具buff
const int OBJTYPE_STATE										= 900000000;	//国家类型

inline bool g_IsUser(int nType)				{return nType == OBJTYPE_USER;}
inline bool g_IsRole(int nType)				{return GetLeftSingle(nType) == GetLeftSingle(OBJTYPE_ROLE);}
inline bool g_IsPlayer(int nType)			{return GetLeftTwo(nType)	== GetLeftTwo(OBJTYPE_ROLE_PLAYER) ;}
inline bool g_IsNPC(int nType)				{return GetLeftTwo(nType)	== GetLeftTwo(OBJTYPE_ROLE_NPC);}	
inline bool g_IsNameNPC(int nType)			{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_ROLE_NPC_NAMENPC);}
inline bool g_IsMonster(int nType)			{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_ROLE_NPC_MOB);}
inline bool g_IsCommonMonster(int nType)	{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_MOB_COMMON);}
inline bool g_IsSpecialMonster(int nType)	{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_MOB_SPECIAL);}
inline bool g_IsSpecialMonster2(int nType)	{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_MOB_SPECIAL2);}
inline bool g_IsNpcMobFellow(int nType)		{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_MOB_FELLOW);}			//--珍兽怪（用来捕捉，捕捉后成为珍兽)--
inline bool g_IsPet(int nType)				{return GetLeftThree(nType)	== GetLeftThree(OBJTYPE_ROLE_NPC_PET);}
inline bool g_IsFellow(int nType)			{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_PET_FELLOW);}			//--珍兽（玩家可携带宠物）--
inline bool g_IsCombatPet(int nType)		{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_PET_Combat);}

inline bool g_IsRidPet(int nType)			{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_PET_ZUOQI);}				//--坐骑--
inline bool g_IsRidPetCommonHorse(int nType){return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ZUOQI_COMMONHORSE);}	//--坐骑类型（普通马）--change by zhangjianli 2011-12-07
inline bool g_IsRidPetCommonBird(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ZUOQI_COMMONBIRD);}	//--坐骑类型（普通鸟）--change by zhangjianli 2011-12-07
inline bool g_IsRidPetCombatHorse(int nType){return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ZUOQI_COMBATHORSE);} //--坐骑类型（战马）--add by zhangjianli 2011-12-07
inline bool g_IsRidPetCombatBird(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ZUOQI_COMBATBIRD);}	//--坐骑类型（战鸟）--add by zhangjianli 2011-12-07
inline bool g_IsRidPetHorse(int nType)		{return (g_IsRidPetCommonHorse(nType)||g_IsRidPetCombatHorse(nType));}				//--坐骑类型（马：包括普通马和战马）--add by zhangjianli 2011-12-07
inline bool g_IsRidPetBird(int nType)		{return (g_IsRidPetCommonBird(nType)||g_IsRidPetCombatBird(nType));}				//--坐骑类型（鸟：包括普通鸟和战鸟）--add by zhangjianli 2011-12-07
inline bool g_IsRidPetCombat(int nType)		{return (g_IsRidPetCombatHorse(nType)||g_IsRidPetCombatBird(nType));}				//--坐骑类型（可战斗坐骑）--add by zhangjianli 2011-12-07
inline bool g_IsRidPetCommon(int nType)		{return (g_IsRidPetCommonHorse(nType)||g_IsRidPetCommonBird(nType));}				//--坐骑类型（普通坐骑-不可战斗）--add by zhangjianli 2011-12-07

inline bool	g_IsBeastPet(int nType)			{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ShootCombat_Beast);}	//--射手战宠--
//inline bool	 g_IsSpiritBeastPet(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ShootCombat_SpiritBeast);}	//--废弃-- del by zhaoguoze 2011-09-19
//inline bool	 g_IsSaintBeastPet(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ShootCombat_SaintBeast);}	//--废弃-- del by zhaoguoze 2011-09-19
//inline bool	 g_IsGhostPet(int nType)		{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_MonsterCombat_Ghost);}		//--废弃-- del by zhaoguoze 2011-09-19
inline bool	 g_IsAquaSpiritPet(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_MonsterCombat_AquaSpirit);}//--道士战宠--
//inline bool	 g_IsFireSpiritPet(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_MonsterCombat_FireSpirit);}	//--废弃-- del by zhaoguoze 2011-09-19
//inline bool	 g_IsDarkSpiritPet(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_MonsterCombat_DarkSpirit);}	//--废弃-- del by zhaoguoze 2011-09-19
//inline bool	 g_IsWindSpiritPet(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_MonsterCombat_WindSpirit);}	//--废弃-- del by zhaoguoze 2011-09-19
inline bool  g_IsCar(int nType)				{return GetLeftThree(nType)	== GetLeftThree(OBJTYPE_ROLE_NPC_CAT);}	
inline bool	 g_IsPrivateCar(int nType)		{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_PRIVATE_CAT);}
inline bool  g_IsFamilyCar(int nType)		{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_FAMILY_CAT);}
inline bool  g_IsPrivateFamilyCar(int nType){return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_FAMILY_PRIVATECAT);}
//inline bool  g_IsFamilyCommonCar(int nType) {return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_FAMILY_COMMON_CAT);}				//--废弃-- del by zhaoguoze 2011-09-19
//inline bool  g_IsFamilyDragonCar(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_FAMILY_DRAGON_CAT);}				//--废弃-- del by zhaoguoze 2011-09-19
//inline bool  g_IsFamilyTigerCar(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_FAMILY_TIGER_CAT);}				//--废弃-- del by zhaoguoze 2011-09-19
//inline bool  g_IsMarryCar(int nType)		{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_ROLE_NPC_MARRY_CAT);}						//--废弃-- del by zhaoguoze 2011-09-19
inline bool  g_IsZone(int nType)			{return GetLeftThree(nType)	== GetLeftThree(OBJTYPE_ROLE_NPC_ZONE);}
inline bool  g_IsTrap(int nType)			{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_TRAP);}
inline bool  g_IsAura(int nType)			{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_ROLE_AURA);}
inline bool  g_IsGod(int nType)				{return GetLeftTwo(nType)	== GetLeftTwo(OBJTYPE_ROLE_GOD);}
inline bool  g_IsAnimal(int nType)			{return GetLeftTwo(nType)	== GetLeftTwo(OBJTYPE_ROLE_ANIMAL);}
inline bool  g_IsBoss(int nType)			{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_ROLE_BOSS);}
inline bool  g_IsFuBenBoss(int nType)		{return GetLeftFour(nType) == GetLeftFour(OBJ_ROLE_BOSS_FUBEN);}
inline bool  g_IsUnDercityBoss(int nType)	{return GetLeftFour(nType) == GetLeftFour(OBJ_ROLE_BOSS_UNDERCITY);}
inline bool  g_IsWorldBoss(int nType)		{return GetLeftFour(nType) == GetLeftFour(OBJ_ROLE_BOSS_WORLD);}
inline bool  g_IsQuestBoss(int nType)		{return GetLeftFour(nType) == GetLeftFour(OBJ_ROLE_BOSS_QUEST);}

inline bool  g_IsSpirit(int nType)			{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_ROLE_NPC_SPIRIT);}
inline bool  g_IsBoat(int nType)			{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_ROLE_NPC_BOAT);}
//edit by youxl 2011.7.18//取消mpwnpc的特殊处理
inline bool  g_IsMpwPerson( int nType)		{return (nType >= 7000 && nType <= 7999 )?true:false;}
//-end
inline bool	 g_IsLand(int nType)			{return GetLeftFour(nType)	== GetLeftFour(OBJTYPE_ROLE_NPC_LAND);}
//inline bool  g_IsFalseLand(int nType)		{return GetLeftFive(nType)  == GetLeftFive(OBJTYPE_ROLE_NPC_LAND_FALSE);}		//--废弃-- del by zhaoguoze 2011-09-19
//inline bool	 g_IsTriggerProp(int nType)		{return GetLeftFour(nType)	== GetLeftFour(OBJTYPE_ROLE_NPC_TRIGGERPROP);}	//--废弃-- del by zhaoguoze 2011-09-19
//inline bool	 g_IsTriggerMultiProp(int nType){return GetLeftFour(nType)  == GetLeftFour(OBJTYPE_ROLE_NPC_TRIGGERPROP_MULTI);}//--废弃-- del by zhaoguoze 2011-09-19

//Prop
inline bool g_IsProp(int nType)								{return GetLeftSingle(nType) == GetLeftSingle(OBJTYPE_PROP);}							//道具
inline bool g_IsEquip(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_EQUIPMENT);}						//装备

inline bool g_IsEquipWeapen(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_EQUIPMENT_WEAPEN);}			//武器
inline bool g_IsPhysicalWeapen(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_WEAPEN_PHYSICAL);}		//物理系
inline bool g_IsMagicWeapen(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_WEAPEN_MAGIC);}		//法术系
inline bool g_IsToxophilyWeapen(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_WEAPEN_TOXOPHILY);}	//射术系
inline bool g_IsBlackartWeapen(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_WEAPEN_BLACKART);}		//妖术系
inline bool g_IsTheurgyWeapen(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_WEAPEN_THEURGY);}		//仙术系

inline bool g_IsEquipAssWeapen(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_EQUIPMENT_ASSWEAP);}			//武器
inline bool g_IsAssPhysicalWeapen(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ASSWEAP_PHYSICAL);}	//物理系
inline bool g_IsAssMagicWeapen(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ASSWEAP_MAGIC);}		//法术系
inline bool g_IsAssToxophilyWeapen(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ASSWEAP_TOXOPHILY);}	//射术系
inline bool g_IsAssBlackartWeapen(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ASSWEAP_BLACKART);}	//妖术系
inline bool g_IsAssTheurgyWeapen(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ASSWEAP_THEURGY);}		//仙术系

inline bool g_IsEquipArmor(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_EQUIPMENT_ARMOR);}			//防具类装备
inline bool g_IsEquipArmorHead(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ARMOR_HEAD);}		//头盔
inline bool g_IsEquipArmorChest(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ARMOR_CHEST);}		//盔甲
inline bool g_IsEquipArmorWaist(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ARMOR_WAIST);}		//腰带
inline bool g_IsEquipArmorHands(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ARMOR_HANDS);}		//手套
inline bool g_IsEquipArmorFeets(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ARMOR_FEETS);}		//靴子

inline bool g_IsEquipJewelry(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_EQUIPMENT_JEWELRY);}			//佩戴饰品
inline bool g_IsEquipJewelryNecklace(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_JEWELRY_NECKLACE);}	//项链
inline bool g_IsEquipJewelryRings(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_JEWELRY_RINGS);}		//戒指
inline bool g_IsEquipJewelryShipin(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_JEWELRY_SHIPIN);}		//饰品

inline bool g_IsEquipPet(int nType)							{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_EQUIPMENT_PET);}			//宠物装备
inline bool g_IsEquipPetSaddle(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_PET_SADDLE);}		//马鞍
inline bool g_IsEquipPetHorsewhip(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_PET_HORSEWHIP);}	//马鞭
inline bool g_IsEquipPetWeskit(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_PET_WESKIT);}		//马甲
inline bool g_IsEquipPetSpur(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_PET_SPUR);}		//马刺
inline bool g_IsEquipPetFashion(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_PET_FASHION);}		//马匹时装

inline bool g_IsEquipSpecial(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_EQUIPMENT_SPECIAL);}		//特殊装备
inline bool g_IsEquipSpecialFashion(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_SPECIAL_FASHION);}	//时装
inline bool g_IsEquipSpecialMantle(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_SPECIAL_MANTLE);}	//披风
inline bool g_IsEquipSpecialEnsign(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_SPECIAL_ENSIGN);}	//军旗

inline bool g_IsStuff(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_STUFF);}	//材料

inline bool g_IsStuffCompose(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_STUFF_COMPOSE);}	//打造材料
inline bool g_IsComposeWood(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_COMPOSE_WOOD);}	//木材
inline bool g_IsComposeMetal(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_COMPOSE_METAL);}	//金属
inline bool g_IsComposePiece(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_COMPOSE_PIECE);}	//布匹
inline bool g_IsComposeStone(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_COMPOSE_STONE);}	//石头
inline bool g_IsComposeLeather(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_COMPOSE_LEATHER);}	//皮革

inline bool g_IsStuffStone(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_STUFF_ADDSTAR);}	//加星
inline bool g_IsStarYu(int nType)							{return nType == OBJTYPE_PROP_STUFF_ADDSTAR_YOUSHI;}
inline bool g_IsPetStarYu(int nType)						{return nType == OBJTYPE_PROP_STUFF_PETADDSTAR_YOUSHI;}
inline bool	g_IsSealStone(int nType)						{return nType == OBJTYPE_PROP_STUFF_SEALSTONE; }	//封星石

inline bool g_IsStuffSign(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_STUFF_SIGN);}	//签名
inline bool g_IsSignYin(int nType)							{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_SIGN_YINZHANG);}

inline bool g_IsStuffBind(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_STUFF_BIND);}	//绑定
inline bool g_IsBindFu(int nType)							{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_BIND_FUWEN);}

inline bool g_IsStuffHole(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_STUFF_ADDHOLE);}	//打孔
inline bool g_IsHoleZuan(int nType)							{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_ADDHOLE_ZUANTOU);}

inline bool g_IsStuffEnchase(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_STUFF_ENCHASE);}	//镶嵌
inline bool g_IsEnchaseGem(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_ENCHASE_GEM);}

inline bool g_IsMedicament(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_MEDICAMENT);}	//药剂
inline bool g_IsMedicamentCommon(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_MEDICAMENT_COMMON);}	//普通药剂
inline bool g_IsMedicamentCommonHP(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_MEDICAMENT_COMMON_HP);}	//生命
inline bool g_IsMedicamentCommonMP(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_MEDICAMENT_COMMON_MP);}	//法力
inline bool g_IsMedicamentSpec(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_MEDICAMENT_SPEC);}		//特殊药剂
inline bool g_IsMedicamentSpecAttr(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_MEDICAMENT_SPEC_ATTR);}	//
inline bool g_IsMedicamentSpecFunc(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_MEDICAMENT_SPEC_FUNC);}	//
inline bool g_IsMedicamentEnergy(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_MEDICAMENT_ENERGY);}	//能量精化
inline bool g_IsMedicamentEnergyHP(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_MEDICAMENT_ENERGY_HP);}	//生命
inline bool g_IsMedicamentEnergyMP(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_MEDICAMENT_ENERGY_MP);}	//法力

inline bool g_IsBook(int nType)								{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_BOOK);}	//书
inline bool g_IsBookPhysical(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_BOOK_PHYSICAL);}	//武术系
inline bool g_IsBookMagic(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_BOOK_MAGIC);}	//法术系
inline bool g_IsBookToxophily(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_BOOK_TOXOPHILY);}	//射术系
inline bool g_IsBookBlackart(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_BOOK_BLACKART);}	//妖术系
inline bool g_IsBooktheurgy(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_BOOK_THEURGY);}	//仙术系
inline bool g_IsBookPet(int nType)							{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_BOOK_PET);}	//宠物

inline bool g_IsPropPet(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_PET);}				//宠物类
inline bool g_IsPropPetEgg(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_PET_EGG);}		//宠物蛋
inline bool g_IsPropPetRid(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_PET_ZUOQI);}	//坐骑
inline bool g_IsPropPetCombat(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_RPOP_PET_COMBAT);}	//战宠

inline bool g_IsPropSpeciality(int nType)					{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_SPECIALITY);}	//特产

inline bool g_IsPropFumo(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_FUMO);}	//附魔
inline bool g_IsPropFumoMethod(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUMO_METHOD);} //附魔配方
inline bool g_IsPropFumoMaterial(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUMO_MATERIAL);} //附魔材料
inline bool g_IsPropFumoCharm(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUMO_CHARM);} //附魔咒符

inline bool g_IsPropFunction(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_FUNCTION);}	//功能
inline bool g_IsPropFunctionReel(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_REEL);} //卷轴
inline bool g_IsPropFunctionBooth(int nType)				{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_BOOTH);} //摆摊车
inline bool g_IsPropFunctionHonor(int nType)				{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_HONOR);} //荣誉道具
inline bool g_IsContainerProp(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_CONTAINER);} //背包

inline bool g_IsFunctionOther(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_OTHER);} //其他

inline bool g_IsPropCar(int nType)							{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_CAR);} //战车
inline bool g_IsPropCarFamily(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_CAR_FAMILY);} //家族战车
inline bool g_IsPropCarHealth(int nType)					{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_PROP_HEALTH_CAR_FAMILY);} //
inline bool g_IsPropCarDamage(int nType)					{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_PROP_DAMAGE_CAR_FAMILY);} //
inline bool g_IsPropCarDefence(int nType)					{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_PROP_DEFENCE_CAR_FAMILY);} //
inline bool g_IsPropCarCollect(int nType)					{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_PROP_CAR_FAMILY_COLLECT);} //
//inline bool g_IsPropCarGang(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_CAR_GANG);} //帮会战车

inline bool g_IsPropFamilyFunc(int nType)					{return GetLeftFour(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_FAMILY);} //家族帮会功能道具
inline bool g_IsPropFamilyDiChan(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_FUNCTION_FAMILY_DICHAN);} //地产证明
inline bool g_IsPropMagicBox(int nType)						{return GetLeftFour(nType)== GetLeftFour(OBJTYPE_PROP_FUNCTION_FAMILY_MAGICBOX);} 
inline bool g_IsPropBossFood(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_FUNCTION_FAMILY_FOOD);}
inline bool g_IsPropFamilyQuest(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_FUNCTION_FAMILY_QUEST);}

inline bool g_IsFeeds(int nType)							{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_FEEDS);}	//饲料
inline bool g_IsFeedsPet(int nType)							{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_FUNCTION_FEEDS_PET);}	
inline bool g_IsFeedsRide(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_FUNCTION_FEEDS_RIDE);}	

inline bool g_IsPropMission(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_MISSION);}	//任务道具
inline bool g_IsPropMissionBook(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_MISSION_BOOK);}	//书信
inline bool g_IsPropMissionUsed(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_MISSION_USED);}	//使用
inline bool g_IsPropMissionEquip(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_MISSION_EQUIP);}	//装备

inline bool g_IsGuoce(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_GUOCE);}	//国策
inline bool g_IsHufu(int nType)								{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_HUFU);}	//虎符
inline bool g_IsShengWang(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_SHENGWANG);}//声望
inline bool g_IsZhanhun(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_ZHANHUN);}	//战魂石

//Skill
inline bool g_IsSkill(int nType)							{return GetLeftSingle(nType) == GetLeftSingle(OBJTYPE_SKILL);}			//技能
inline bool g_IsCommonSkill(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_COMMON);}			//普通攻击
inline bool g_IsRageSkill(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_RAGE);}		//怒气技能
inline bool g_IsXinFaSkill(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_XINFA);}		//心法技能
inline bool g_IsTreeSkill(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_TREESKILL);}		//人物技能数
inline bool g_IsLiftSkill(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_LIFESKILL);}		//生活技能
inline bool g_IsNPCSkill(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_NPCSKILL);}		//npc技能
inline bool g_IsPropSkill(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_PROPSKILL);}		//道具技能
inline bool g_IsEnchanting(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_SKILL_PROP_ENCHANTING);}	//附魔技能
inline bool g_IsPetSkill(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_PETSKILL);}		//宠物技能
inline bool g_IsAddSkill(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_AddSkill);}
inline bool g_IsPetSafeGuardSkill(int nType)				{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_SKILL_PETSKILL_SAFEGUARD);}		//宠物守护技能

//Server
inline bool g_IsServer(int nType)							{return GetLeftSingle(nType) == GetLeftSingle(OBJTYPE_SERVER); }	// 服务器Obj
inline bool g_IsSuperServer(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_SUPER);}		// SuperServer
inline bool g_IsCheckServer(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_CHECK);}		// SuperServer
inline bool g_IsDBServer(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_DB);}		// DBServer
inline bool g_IsDataServer(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_GAME);}		// DataServer
inline bool g_IsLoginServer(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_LOGIN);}		// LoginServer
inline bool g_IsDNSServer(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_DNS);}		// DNSServer
inline bool g_IsCommunityServer(int nType)					{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_COMMUNIT);}// community
inline bool g_IsMailServer(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_MAIL);}		// MailServer
inline bool g_IsMonitorServer(int nType)					{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_MONITOR);}	// MonitorServer
inline bool g_IsBackupServer(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_BACKUP);}	// BackupServer
inline bool g_IsGateWayServer(int nType)					{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_GATEWAY);}	// BackupServer
inline bool g_IsTopServer(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_TOP);}	// BackupServer
inline bool g_IsGMServer(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_GM);}		// CGMServer
inline bool g_IsGMCServer(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_GMC);}		// CGMCServer
inline bool g_IsGMTool(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_GMTOOL);}	// GMTool
inline bool g_IsNameServer(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SERVER_NAME);}		// CNameServer



//Scene
inline bool g_IsScene(int nType)							{return GetLeftSingle(nType) == GetLeftSingle(OBJTYPE_SCENE);}
inline bool g_IsCity(int nType)								{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SCENE_CITY);}
inline bool	g_IsUnderGroundCity(int nType)					{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SCENE_UNDERGROUD_CITY);}
inline bool g_IsFamilyCity(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_SCENE_FAMILY_CITY);}
inline bool g_IsGangCity(int nType)							{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_SCENE_GANG_CITY);}
inline bool g_IsTeamCity(int nType)							{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_SCENE_TEAM_CITY);}
inline bool g_IsPrivateCity(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_SCENE_PRIVATE_CITY);}
inline bool g_IsCampaignCity(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_SCENE_CAMPAIGN_CITY);}


//buff
inline bool g_IsBuff(int nType)								{return GetLeftSingle(nType) == GetLeftSingle(OBJTYPE_BUFF);}
inline bool g_IsRoleBuff(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_BUFF_ROLE);}
inline bool g_IsPropBuff(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_BUFF_PROP);}

//Quest
inline bool g_IsQuest(int nType)							{return GetLeftSingle(nType) == GetLeftSingle(OBJTYPE_QUEST);}
inline bool g_IsCommonQuest(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_QUEST_COMMON);}
inline bool g_IsGreenQuest(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_QUEST_GREEN);}
inline bool g_IsCreditQuest(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_QUEST_CREDIT);}
inline bool g_IsThreadQuest(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_QUEST_THREAD);}
inline bool g_IsRandomQuest(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_QUEST_RANDOM);}
inline bool g_IsStoryQuest(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_QUEST_STORY);}
inline bool g_IsTreasureQuest(int nType)					{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_QUEST_TREASURE);}
inline bool g_IsSkillPointQuest(int nType)					{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_QUEST_SKILLPOINT);}

inline bool g_IsFriendQuest(int nType)						{return GetLeftThree(nType)==GetLeftThree(OBJTYPE_QUEST_COMMON_FRIEND);}
inline bool g_IsMasterQuest(int nType)						{return GetLeftThree(nType)==GetLeftThree(OBJTYPE_QUEST_COMMON_MASTER);}
inline bool g_IsMarryQuest(int nType)						{return GetLeftThree(nType)==GetLeftThree(OBJTYPE_QUEST_COMMON_MARRY);}
inline bool g_IsFamilyQuest(int nType)						{return GetLeftThree(nType)==GetLeftThree(OBJTYPE_QUEST_COMMON_FAMILY);}
inline bool g_IsGangQuest(int nType)						{return GetLeftThree(nType)==GetLeftThree(OBJTYPE_QUEST_COMMON_GANG);}
inline bool g_IsWeekStateQuest(int nType)					{return GetLeftThree(nType)==GetLeftThree(OBJTYPE_QUEST_COMMON_WEEKSTATE);}
inline bool g_IsStrenthStateQuest(int nType)				{return GetLeftThree(nType)==GetLeftThree(OBJTYPE_QUEST_COMMON_STRENTHSTATE);}


inline bool g_IsUnderCityQuest(int nType)					{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_QUEST_UNDERCITY);}
inline bool g_IsHelpQuest(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_QUEST_HELP);}
inline bool g_IsQuestQuest(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_QUEST_QUEST);}
inline bool g_IsCampaignQuest(int nType)					{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_QUEST_CAMPAIGN);}
inline bool g_IsCampaignPrivateQuest(int nType)				{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_QUEST_CAMPAIGN_PRIVATE);}
inline bool g_IsCampaignFamilyQuest(int nType)				{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_QUEST_CAMPAIGN_FAMILY);}
inline bool g_IsCampaignGangQuest(int nType)				{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_QUEST_CAMPAIGN_GANG);}
inline bool g_IsCampaignStateQuest(int nType)				{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_QUEST_CAMPAIGN_STATE);}

//Mail
inline bool g_IsMail(int nType)								{ return GetLeftSingle(nType) == GetLeftSingle(OBJTYPE_MAIL);}	

