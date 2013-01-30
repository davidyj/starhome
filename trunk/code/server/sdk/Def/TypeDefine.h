#pragma	  once


#define GetLeftSingle(n)	(n/100000000)
#define GetLeftTwo(n)		(n/1000000)
#define GetLeftThree(n)		(n/10000)
#define GetLeftFour(n)		(n/100)	
#define GetLeftFive(n)		(n/1)


const int OBJTYPE_INVALID									= -1;			//��Ч��obj����
const int OBJTYPE_USER										= 1;			//User
const int OBJTYPE_MAPOBJ									= 100000;		
const int OBJTYPE_MAPOBJ_MPW								= 101000;		//mpw
const int OBJTYPE_MAPOBJ_NPC								= 102000;		//editor Npc
const int OBJTYPE_MAPOBJ_CPOINT								= 103000;		//���ɵ�
																			
const int OBJTYPE_ROLE										= 100000000;	//����
const int OBJTYPE_ROLE_PLAYER								= 101000000;	//���					
const int OBJTYPE_ROLE_NPC									= 102000000;	//�����
const int OBJTYPE_ROLE_NPC_NAMENPC							= 102010000;	//Name NPC & Boss	
//const int OBJTYPE_ROLE_NPC_NAMENPC_STALL					= 102010100;	//��̯��				//--����-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_MOB								= 102020000;	//��ͨС��			
const int OBJTYPE_ROLE_NPC_MOB_COMMON						= 102020100;	//��ͨ��
const int OBJTYPE_ROLE_NPC_MOB_SPECIAL						= 102020200;	//��Ӣ��
const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Normal_L				= 102020201;	//��ͨ��Ӣ��1-90
const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Normal_H				= 102020202;	//��ͨ��Ӣ��90-160
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_F_N			= 102020203;	//ǰ��С��			//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_B_N			= 102020204;	//��С��			//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_F_P			= 102020205;	//ǰ��Ѳ�߹�		//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_B_P			= 102020206;	//��Ѳ�߹�		//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_F_G			= 102020207;	//ǰ������			//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_B_G			= 102020208;	//������			//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MOB_SPECIAL_Area_A_Fun			= 102020209;	//���ܾ�Ӣ��	//--����-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_MOB_SPECIAL2						= 102020300;	//�߼���
const int OBJTYPE_ROLE_NPC_MOB_FELLOW						= 102020400;	//���޹֣�������׽����׽���Ϊ���ޣ�
const int OBJTYPE_ROLE_BOSS									= 102050000;	//BOSS
const int OBJ_ROLE_BOSS_FUBEN								= 102050100;	//����Boss
const int OBJ_ROLE_BOSS_FUBEN_Single						= 102050101;	//��ͨBOSS
//const int OBJ_ROLE_BOSS_FUBEN_Compose						= 102050102;	//���BOSS		
//const int OBJ_ROLE_BOSS_FUBEN_BOX							= 102050103;	//BOSS����		
//const int OBJ_ROLE_BOSS_FUBEN_N_BOX						= 102050104;	//��������		
const int OBJ_ROLE_BOSS_FUBEN_Call							= 102050105;	//BOSS�ٻ���		
//const int OBJ_ROLE_BOSS_FUBEN_Quest						= 102050106;	//����boss		//--������ֻ��һ������BOSS-- del by zhaoguoze 2011-09-19
const int OBJ_ROLE_BOSS_UNDERCITY							= 102050200;	//���³�Boss
const int OBJ_ROLE_BOSS_UNDERCITY_A							= 102050201;	//���³�BossA
const int OBJ_ROLE_BOSS_UNDERCITY_B							= 102050202;	//���³�BossB
const int OBJ_ROLE_BOSS_WORLD								= 102050300;	//����Boss
const int OBJ_ROLE_BOSS_WORLD_A								= 102050301;	//����BossA
const int OBJ_ROLE_BOSS_WORLD_B								= 102050302;	//����BossB
const int OBJ_ROLE_BOSS_QUEST								= 102050400;	//����boss		
const int OBJ_ROLE_BOSS_WILD								= 102050500;	//Ұ��boss
const int OBJ_ROLE_BOSS_WILD_A								= 102050501;	//Ұ��bossA
const int OBJ_ROLE_BOSS_WILD_B								= 102050502;	//Ұ��bossB
const int OBJTYPE_ROLE_AURA									= 102060000;	//�⻷
const int OBJTYPE_ROLE_NPC_ZONE								= 102070000;	//����������
const int OBJTYPE_ROLE_NPC_TRAP								= 102070100;	//����
//const int OBJTYPE_ROLE_NPC_PORTAL							= 102070200;	//������				//--����-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_LAND								= 102070300;	//����
//const int OBJTYPE_ROLE_NPC_LAND_FALSE						= 102070301;	//�ٵ���			//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_TRIGGERPROP					= 102070400;	//��������ߵ���		//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_TRIGGERPROP_MULTI				=102070500;		//����Ⱥ�������	//--����-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_PET								= 102080000;	//��������
																			
const int OBJTYPE_ROLE_NPC_PET_ZUOQI						= 102080200;	//����
const int OBJTYPE_ROLE_NPC_PET_ZUOQI_COMMONHORSE			= 102080201;	//�������ͣ���ͨ��change by zhangjianli 2011-12-07
const int OBJTYPE_ROLE_NPC_PET_ZUOQI_COMMONBIRD				= 102080202;	//�������ͣ���ͨ��change by zhangjianli 2011-12-07
const int OBJTYPE_ROLE_NPC_PET_ZUOQI_COMBATHORSE			= 102080203;	//�������ͣ�ս��  add by zhangjianli 2011-12-07
const int OBJTYPE_ROLE_NPC_PET_ZUOQI_COMBATBIRD				= 102080204;	//�������ͣ�ս��  add by zhangjianli 2011-12-07

const int OBJTYPE_ROLE_NPC_PET_Combat						= 102080300;	//ս��
const int OBJTYPE_ROLE_NPC_PET_ShootCombat_Beast			= 102080301;	//�����ٻ�ս�裨֮ǰ��Ұ�����ͣ�
//const int OBJTYPE_ROLE_NPC_PET_ShootCombat_SpiritBeast	= 102080302;	//����	//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_PET_ShootCombat_SaintBeast		= 102080303;	//ʥ��		//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_PET_MonsterCombat_Ghost		= 102080311;	//����	//--����-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_PET_MonsterCombat_AquaSpirit		= 102080312;	//��ʿ�ٻ�ս�裨֮ǰ��ˮ�����ͣ�
//const int OBJTYPE_ROLE_NPC_PET_MonsterCombat_FireSpirit	= 102080313;	//����		//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_PET_MonsterCombat_DarkSpirit	= 102080314;	//����		//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_PET_MonsterCombat_WindSpirit	= 102080315;	//����		//--����-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_CAT								= 102090000;	//ս��
const int OBJTYPE_ROLE_NPC_PRIVATE_CAT						= 102090100;	//�����ڳ�
const int OBJTYPE_ROLE_NPC_FAMILY_CAT						= 102090200;	//����ս��
const int OBJTYPE_ROLE_NPC_FAMILY_PRIVATECAT				= 102090400;	//�����ڳ�
//const int OBJTYPE_ROLE_NPC_FAMILY_COMMON_CAT				= 102090201;	//������ͨս��		//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_FAMILY_DRAGON_CAT				= 102090202;	//������ս��		//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_FAMILY_TIGER_CAT				= 102090203;	//���廢ս��	//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_FAMILY_COLLECT_CAT				= 102090204;	//����ɼ���	//--����-- del by zhaoguoze 2011-09-19
//const int OBJTYPE_ROLE_NPC_MARRY_CAT						= 102090300;	//�鳵		//--����-- del by zhaoguoze 2011-09-19
const int OBJTYPE_ROLE_NPC_SPIRIT							= 102100000;	//������
																			
const int OBJTYPE_ROLE_NPC_BOAT								= 102200000;	//��ˮ�������ߵĴ���
																			
const int OBJTYPE_ROLE_NPC_PET_FELLOW						= 103000000;	//--���ޣ���ҿ�Я�����--
																			
const int OBJTYPE_ROLE_GOD									= 104000000;	//�ϵ�		
const int OBJTYPE_ROLE_ANIMAL								= 105000000;	//С����
																			
const int OBJTYPE_PROP										= 200000000;	//����
const int OBJTYPE_PROP_EQUIPMENT							= 201000000;	//װ��
const int OBJTYPE_PROP_EQUIPMENT_WEAPEN						= 201010000;	//����
const int OBJTYPE_PROP_EQUIPMENT_WEAPEN_PHYSICAL			= 201010100;	//��ʦ
const int OBJTYPE_PROP_EQUIPMENT_WEAPEN_MAGIC				= 201010200;	//��ʿ
const int OBJTYPE_PROP_EQUIPMENT_WEAPEN_TOXOPHILY			= 201010300;	//����
const int OBJTYPE_PROP_EQUIPMENT_WEAPEN_BLACKART			= 201010400;	//����
const int OBJTYPE_PROP_EQUIPMENT_WEAPEN_THEURGY				= 201010500;	//ҩʦ
const int OBJTYPE_PROP_EQUIPMENT_ARMOR						= 201020000;	//װ��������
const int OBJTYPE_PROP_EQUIPMENT_ARMOR_HEAD					= 201020100;	//ͷ��
const int OBJTYPE_PROP_EQUIPMENT_ARMOR_CHEST				= 201020200;	//�·�
const int OBJTYPE_PROP_EQUIPMENT_ARMOR_WAIST				= 201020300;	//����
const int OBJTYPE_PROP_EQUIPMENT_ARMOR_HANDS				= 201020400;	//����
const int OBJTYPE_PROP_EQUIPMENT_ARMOR_FEETS				= 201020500;	//ѥ��
const int OBJTYPE_PROP_EQUIPMENT_JEWELRY					= 201030000;	//��Ʒ
const int OBJTYPE_PROP_EQUIPMENT_JEWELRY_NECKLACE			= 201030100;	//����
const int OBJTYPE_PROP_EQUIPMENT_JEWELRY_RINGS				= 201030200;	//��ָ
const int OBJTYPE_PROP_EQUIPMENT_JEWELRY_SHIPIN				= 201030300;	//��Ʒ
const int OBJTYPE_PROP_EQUIPMENT_PET						= 201040000;	//����װ��
const int OBJTYPE_PROP_EQUIPMENT_PET_SADDLE					= 201040100;	//��
const int OBJTYPE_PROP_EQUIPMENT_PET_HORSEWHIP				= 201040200;	//���
const int OBJTYPE_PROP_EQUIPMENT_PET_WESKIT					= 201040300;	//���
const int OBJTYPE_PROP_EQUIPMENT_PET_SPUR					= 201040400;	//���		
const int OBJTYPE_PROP_EQUIPMENT_PET_FASHION				= 201040500;	//��ƥʱװ
const int OBJTYPE_PROP_EQUIPMENT_SPECIAL					= 201050000;	//����װ��
const int OBJTYPE_PROP_EQUIPMENT_SPECIAL_FASHION			= 201050100;	//ʱװ
const int OBJTYPE_PROP_EQUIPMENT_SPECIAL_MANTLE				= 201050200;	//����
const int OBJTYPE_PROP_EQUIPMENT_SPECIAL_ENSIGN				= 201050300;	//����
const int OBJTYPE_PROP_EQUIPMENT_ASSWEAP					= 201060000;	//����
const int OBJTYPE_PROP_EQUIPMENT_ASSWEAP_PHYSICAL			= 201060100;	//��ʦ
const int OBJTYPE_PROP_EQUIPMENT_ASSWEAP_MAGIC				= 201060200;	//��ʿ
const int OBJTYPE_PROP_EQUIPMENT_ASSWEAP_TOXOPHILY			= 201060300;	//����
const int OBJTYPE_PROP_EQUIPMENT_ASSWEAP_BLACKART			= 201060400;	//����
const int OBJTYPE_PROP_EQUIPMENT_ASSWEAP_THEURGY			= 201060500;	//ҩʦ
																			
const int OBJTYPE_PROP_STUFF								= 202000000;	//����	
const int OBJTYPE_PROP_STUFF_COMPOSE						= 202010000;	//�������
const int OBJTYPE_PROP_STUFF_COMPOSE_WOOD					= 202010100;	//ľ��
const int OBJTYPE_PROP_STUFF_COMPOSE_METAL					= 202010200;	//����
const int OBJTYPE_PROP_STUFF_COMPOSE_LEATHER				= 202010300;	//Ƥ��
const int OBJTYPE_PROP_STUFF_COMPOSE_PIECE					= 202010400;	//��ƥ
const int OBJTYPE_PROP_STUFF_COMPOSE_STONE					= 202010500;	//ʯͷ
const int OBJTYPE_PROP_STUFF_ADDSTAR						= 202020000;	//���ǲ���
const int OBJTYPE_PROP_STUFF_ADDSTAR_YOUSHI					= 202020100;	//��ʯ
const int OBJTYPE_PROP_STUFF_PETADDSTAR_YOUSHI				= 202020200;	//����ǿ��ʯͷ
const int OBJTYPE_PROP_STUFF_SEALSTONE						= 202020300;	//����ʯͷ
const int OBJTYPE_PROP_STUFF_SIGN							= 202030000;	//ǩ������
const int OBJTYPE_PROP_STUFF_SIGN_YINZHANG					= 202030100;	//ӡ��
const int OBJTYPE_PROP_STUFF_BIND							= 202040000;	//�󶨲���
const int OBJTYPE_PROP_STUFF_BIND_FUWEN						= 202040100;	//����
const int OBJTYPE_PROP_STUFF_ADDHOLE						= 202050000;	//��ײ��� �ݻٱ�ʯ����
const int OBJTYPE_PROP_STUFF_ADDHOLE_ZUANTOU				= 202050100;	//��ͷ
const int OBJTYPE_PROP_STUFF_ENCHASE						= 202060000;	//��Ƕ����
const int OBJTYPE_PROP_STUFF_ENCHASE_GEM					= 202060100;	//��ʯ
																			
const int OBJTYPE_PROP_MEDICAMENT							= 203000000;	//ҩ��
const int OBJTYPE_PROP_MEDICAMENT_COMMON					= 203010000;	//��ͨҩ��
const int OBJTYPE_PROP_MEDICAMENT_COMMON_HP					= 203010100;	//����
const int OBJTYPE_PROP_MEDICAMENT_COMMON_MP					= 203010200;	//����
const int OBJTYPE_PROP_MEDICAMENT_ENERGY					= 203020000;	//����
const int OBJTYPE_PROP_MEDICAMENT_ENERGY_HP					= 203020100;	//��������
const int OBJTYPE_PROP_MEDICAMENT_ENERGY_MP					= 203020200;	//��������
const int OBJTYPE_PROP_MEDICAMENT_SPEC						= 203030000;	//����ҩ��
const int OBJTYPE_PROP_MEDICAMENT_SPEC_ATTR					= 203030100;	//��������
const int OBJTYPE_PROP_MEDICAMENT_SPEC_FUNC					= 203030200;	//���⹦��
																			
const int OBJTYPE_PROP_BOOK									= 204000000;	//������
const int OBJTYPE_PROP_BOOK_PHYSICAL						= 204010000;	//����ϵ
const int OBJTYPE_PROP_BOOK_MAGIC							= 204020000;	//����ϵ
const int OBJTYPE_PROP_BOOK_TOXOPHILY						= 204030000;	//����ϵ
const int OBJTYPE_PROP_BOOK_BLACKART						= 204040000;	//����ϵ
const int OBJTYPE_PROP_BOOK_THEURGY							= 204050000;	//����ϵ
const int OBJTYPE_PROP_BOOK_PET								= 204060000;	//���＼����
																			
const int OBJTYPE_PROP_SPECIALITY							= 206000000;	//�ز�
																			
const int OBJTYPE_PROP_FUMO									= 207000000;	//��ħ
const int OBJTYPE_PROP_FUMO_METHOD							= 207010000;	//��ħ�䷽
const int OBJTYPE_PROP_FUMO_MATERIAL						= 207020000;	//��ħ����
const int OBJTYPE_PROP_FUMO_CHARM							= 207030000;	//��ħ���
																			
const int OBJTYPE_PROP_FUNCTION								= 208000000;	//������
const int OBJTYPE_PROP_FUNCTION_REEL						= 208010000;	//���;���
const int OBJTYPE_PROP_FUNCTION_CONTAINER					= 208040000;	//����

const int OBJTYPE_PROP_FUNCTION_OTHER	                    = 208050000;     //--����

const int OBJTYPE_PROP_FUNCTION_BOOTH						= 208060000;	//��̯��
const int OBJTYPE_PROP_FUNCTION_HONOR						= 208070000;	//��������
const int OBJTYPE_PROP_CAR									= 208080000;	//ս��
const int OBJTYPE_PROP_CAR_FAMILY							= 208080100;	//����ս��
const int OBJTYPE_PROP_HEALTH_CAR_FAMILY					= 208080101;	//����������ս��
const int OBJTYPE_PROP_DAMAGE_CAR_FAMILY					= 208080102;	//���幥����ս��
const int OBJTYPE_PROP_DEFENCE_CAR_FAMILY					= 208080103;	//���������ս��
const int OBJTYPE_PROP_CAR_FAMILY_COLLECT					= 208080104;	//����ɼ���
//const int OBJTYPE_PROP_CAR_GANG							= 208080200;	//���ս��
const int OBJTYPE_PROP_FUNCTION_FAMILY						= 208090000;	//�����Ṧ�ܵ���
const int OBJTYPE_PROP_FUNCTION_FAMILY_DICHAN				= 208090100;	//�ز�֤��
const int OBJTYPE_PROP_FUNCTION_FAMILY_MAGICBOX				= 208090200;	//��������
const int OBJTYPE_PROP_FUNCTION_FAMILY_FOOD					= 208090300;	//bossʳ��
const int OBJTYPE_PROP_FUNCTION_FAMILY_QUEST				= 208090400;	//�������
const int OBJTYPE_PROP_FUNCTION_FEEDS						= 208100000;	//����
const int OBJTYPE_PROP_FUNCTION_FEEDS_PET					= 208100100;	//�̴�����
const int OBJTYPE_PROP_FUNCTION_FEEDS_RIDE					= 208100200;	//��������
																			
const int OBJTYPE_PROP_PET									= 209000000;	//����
const int OBJTYPE_PROP_PET_EGG								= 209010000;	//���ﵰ
const int OBJTYPE_PROP_PET_ZUOQI							= 209020000;	//����
const int OBJTYPE_RPOP_PET_COMBAT							= 209030000;	//ս��
																			
const int OBJTYPE_PROP_MISSION								= 210000000;		//�������
const int OBJTYPE_PROP_MISSION_BOOK							= 210010000;	//����
const int OBJTYPE_PROP_MISSION_USED							= 210020000;	//ʹ��
const int OBJTYPE_PROP_MISSION_EQUIP						= 210030000;	//����װ��
																			
const int OBJTYPE_PROP_GUOCE								= 211000000;	//����
const int OBJTYPE_PROP_HUFU									= 212000000;	//����
const int OBJTYPE_PROP_SHENGWANG							= 213000000;	//����
const int OBJTYPE_PROP_ZHANHUN								= 214000000;	//ս��ʯ
																			
const int OBJTYPE_SKILL										= 300000000;	//����	
const int OBJTYPE_SKILL_COMMON								= 301000000;	//��ͨ����

const int OBJTYPE_SKILL_TREESKILL							= 302000000;	//���＼��					
const int OBJTYPE_SKILL_TREESKILL_PHYSICAL					= 302010000;	//����ϵ����
const int OBJTYPE_SKILL_TREESKILL_MAGIC						= 302020000;	//����ϵ����
const int OBJTYPE_SKILL_TREESKILL_TOXOPHILY					= 302030000;	//����ϵ����
const int OBJTYPE_SKILL_TREESKILL_BLACKART					= 302040000;	//����ϵ����
const int OBJTYPE_SKILL_TREESKILL_THEURGY					= 302050000;	//����ϵ����
const int OBJTYPE_SKILL_LIFESKILL							= 303000000;	//�����
const int OBJTYPE_SKILL_NPCSKILL							= 304000000;	//NPC����
const int OBJTYPE_SKILL_PROPSKILL							= 305000000;	//���߼���
const int OBJTYPE_SKILL_PROP_ENCHANTING						= 305010000;	//��ħ����
const int OBJTYPE_SKILL_PROP_FUNCTION						= 305020000;	//���߹��ܼ��ܣ�װ�������Զ����ʹ�ü��ܵ�������
const int OBJTYPE_SKILL_PETSKILL							= 306000000;	//���＼��
const int OBJTYPE_SKILL_PETSKILL_SELF						= 306010000;	//��������������
const int OBJTYPE_SKILL_PETSKILL_PLAYER						= 306020000;	//������弼��
const int OBJTYPE_SKILL_PETSKILL_SAFEGUARD					= 306030000;	//�����ػ�����
const int OBJTYPE_SKILL_AddSkill							= 307000000;	//���Ӽ���
const int OBJTYPE_SKILL_SOCIETYSKILL						= 308000000;	//��Ἴ��
const int OBJTYPE_SKILL_SOCIETYSKILL_FAMILY					= 308010000;	//���弼��
const int OBJTYPE_SKILL_SOCIETYSKILL_TEAM					= 308020000;	//���鼼��
const int OBJTYPE_SKILL_SOCIETYSKILL_BANG					= 308030000;	//��Ἴ��
const int OBJTYPE_SKILL_TALENT								= 309000000;	//�츳���ܣ��Զ�ѧϰ��
const int OBJTYPE_SKILL_RAGE								= 310000000;	//ŭ������
const int OBJTYPE_SKILL_XINFA								= 311000000;	//�ķ�����
																			
const int OBJTYPE_SCENE										= 400000000;	//����
const int OBJTYPE_SCENE_CITY								= 401000000;	//��ͨ����
const int OBJTYPE_SCENE_UNDERGROUD_CITY						= 402000000;	//��������
const int OBJTYPE_SCENE_FAMILY_CITY							= 402010000;	//���帱��
const int OBJTYPE_SCENE_GANG_CITY							= 402020000;	//��ḱ��
const int OBJTYPE_SCENE_TEAM_CITY							= 402030000;	//���鸱��
const int OBJTYPE_SCENE_PRIVATE_CITY						= 402040000;	//���˸���
const int OBJTYPE_SCENE_CAMPAIGN_CITY						= 402050000;	//�����
															
const int OBJTYPE_SERVER									= 500000000;	//����������
const int OBJTYPE_SERVER_SUPER								= 501000000;	//Super Server
const int OBJTYPE_SERVER_DB									= 502000000;	//DB Server
const int OBJTYPE_SERVER_GAME								= 503000000;	//��Ϸ������
const int OBJTYPE_SERVER_GAME_COMMAND						= 203010000;	//��ͨ����
const int OBJTYPE_SERVER_GAME_UNDERGROUP					= 203020000;	//�������������
const int OBJTYPE_SERVER_LOGIN								= 504000000;	//Login Server
//const int OBJTYPE_SERVER_CHECKUSER						= 514000000;	//Login Server  Check User
const int OBJTYPE_SERVER_COMMUNIT							= 505000000;	//����ϵ������
const int OBJTYPE_SERVER_MAIL								= 506000000;	//�ʼ�����������
const int OBJTYPE_SERVER_BACKUP								= 507000000;	//���ݷ�����
const int OBJTYPE_SERVER_MONITOR							= 508000000;	//���ӷ�����
const int OBJTYPE_SERVER_GATEWAY							= 509000000;	//GateWay ������
const int OBJTYPE_SERVER_DNS								= 510000000;	//DNS ������
const int OBJTYPE_SERVER_CHECK								= 511000000;	//�Ʒ�&��֤������
const int OBJTYPE_SERVER_TOP								= 512000000;	//����������
const int OBJTYPE_SERVER_GM									= 513000000;	//GM������
const int OBJTYPE_SERVER_GMC								= 514000000;	//��άGMC������
const int OBJTYPE_SERVER_GMTOOL								= 515000000;	//GM����
const int OBJTYPE_SERVER_NAME								= 516000000;	//NAME ������
																			
																			
const int OBJTYPE_QUEST										= 600000000;	//����
const int OBJTYPE_QUEST_COMMON								= 601000000;	//��������
const int OBJTYPE_QUEST_COMMON_FRIEND						= 601010000;	//��������
const int OBJTYPE_QUEST_COMMON_MASTER						= 601020000;	//ͽ������
const int OBJTYPE_QUEST_COMMON_MARRY						= 601030000;	//��������
const int OBJTYPE_QUEST_COMMON_FAMILY						= 601040000;	//��������
const int OBJTYPE_QUEST_COMMON_GANG							= 601050000;	//�������
const int OBJTYPE_QUEST_COMMON_WEEKSTATE					= 601060000;	//��������
const int OBJTYPE_QUEST_COMMON_STRENTHSTATE					= 601070000;	//ǿ������
const int OBJTYPE_QUEST_GREEN								= 602000000;	//��װ����
const int OBJTYPE_QUEST_CREDIT								= 603000000;	//��������		
const int OBJTYPE_QUEST_CAMPAIGN							= 604000000;	//�����
const int OBJTYPE_QUEST_CAMPAIGN_PRIVATE					= 604010000;	//���˻
const int OBJTYPE_QUEST_CAMPAIGN_FAMILY						= 604020000;	//����
const int OBJTYPE_QUEST_CAMPAIGN_GANG						= 604030000;	//���
const int OBJTYPE_QUEST_CAMPAIGN_STATE						= 604040000;	//���һ
const int OBJTYPE_QUEST_QUEST								= 605000000;	//����
const int OBJTYPE_QUEST_UNDERCITY							= 606000000;	//��������
const int OBJTYPE_QUEST_HELP								= 607000000;	//��������
const int OBJTYPE_QUEST_THREAD								= 608000000;	//֧������
const int OBJTYPE_QUEST_RANDOM								= 608010000;	//�������
const int OBJTYPE_QUEST_STORY								= 609000000;	//��������
const int OBJTYPE_QUEST_TREASURE							= 610000000;	//��Ʒ����
const int OBJTYPE_QUEST_SKILLPOINT							= 611000000;	//���ܵ�����
												
const int OBJTYPE_MAIL										= 700000000;	//�ʼ�	
const int OBJTYPE_BUFF										= 800000000;	//buff
const int OBJTYPE_BUFF_ROLE									= 801000000;	//���buff
const int OBJTYPE_BUFF_PROP									= 802000000;	//����buff
const int OBJTYPE_STATE										= 900000000;	//��������

inline bool g_IsUser(int nType)				{return nType == OBJTYPE_USER;}
inline bool g_IsRole(int nType)				{return GetLeftSingle(nType) == GetLeftSingle(OBJTYPE_ROLE);}
inline bool g_IsPlayer(int nType)			{return GetLeftTwo(nType)	== GetLeftTwo(OBJTYPE_ROLE_PLAYER) ;}
inline bool g_IsNPC(int nType)				{return GetLeftTwo(nType)	== GetLeftTwo(OBJTYPE_ROLE_NPC);}	
inline bool g_IsNameNPC(int nType)			{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_ROLE_NPC_NAMENPC);}
inline bool g_IsMonster(int nType)			{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_ROLE_NPC_MOB);}
inline bool g_IsCommonMonster(int nType)	{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_MOB_COMMON);}
inline bool g_IsSpecialMonster(int nType)	{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_MOB_SPECIAL);}
inline bool g_IsSpecialMonster2(int nType)	{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_MOB_SPECIAL2);}
inline bool g_IsNpcMobFellow(int nType)		{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_MOB_FELLOW);}			//--���޹֣�������׽����׽���Ϊ����)--
inline bool g_IsPet(int nType)				{return GetLeftThree(nType)	== GetLeftThree(OBJTYPE_ROLE_NPC_PET);}
inline bool g_IsFellow(int nType)			{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_PET_FELLOW);}			//--���ޣ���ҿ�Я�����--
inline bool g_IsCombatPet(int nType)		{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_PET_Combat);}

inline bool g_IsRidPet(int nType)			{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_PET_ZUOQI);}				//--����--
inline bool g_IsRidPetCommonHorse(int nType){return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ZUOQI_COMMONHORSE);}	//--�������ͣ���ͨ��--change by zhangjianli 2011-12-07
inline bool g_IsRidPetCommonBird(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ZUOQI_COMMONBIRD);}	//--�������ͣ���ͨ��--change by zhangjianli 2011-12-07
inline bool g_IsRidPetCombatHorse(int nType){return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ZUOQI_COMBATHORSE);} //--�������ͣ�ս��--add by zhangjianli 2011-12-07
inline bool g_IsRidPetCombatBird(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ZUOQI_COMBATBIRD);}	//--�������ͣ�ս��--add by zhangjianli 2011-12-07
inline bool g_IsRidPetHorse(int nType)		{return (g_IsRidPetCommonHorse(nType)||g_IsRidPetCombatHorse(nType));}				//--�������ͣ���������ͨ���ս��--add by zhangjianli 2011-12-07
inline bool g_IsRidPetBird(int nType)		{return (g_IsRidPetCommonBird(nType)||g_IsRidPetCombatBird(nType));}				//--�������ͣ��񣺰�����ͨ���ս��--add by zhangjianli 2011-12-07
inline bool g_IsRidPetCombat(int nType)		{return (g_IsRidPetCombatHorse(nType)||g_IsRidPetCombatBird(nType));}				//--�������ͣ���ս�����--add by zhangjianli 2011-12-07
inline bool g_IsRidPetCommon(int nType)		{return (g_IsRidPetCommonHorse(nType)||g_IsRidPetCommonBird(nType));}				//--�������ͣ���ͨ����-����ս����--add by zhangjianli 2011-12-07

inline bool	g_IsBeastPet(int nType)			{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ShootCombat_Beast);}	//--����ս��--
//inline bool	 g_IsSpiritBeastPet(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ShootCombat_SpiritBeast);}	//--����-- del by zhaoguoze 2011-09-19
//inline bool	 g_IsSaintBeastPet(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_ShootCombat_SaintBeast);}	//--����-- del by zhaoguoze 2011-09-19
//inline bool	 g_IsGhostPet(int nType)		{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_MonsterCombat_Ghost);}		//--����-- del by zhaoguoze 2011-09-19
inline bool	 g_IsAquaSpiritPet(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_MonsterCombat_AquaSpirit);}//--��ʿս��--
//inline bool	 g_IsFireSpiritPet(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_MonsterCombat_FireSpirit);}	//--����-- del by zhaoguoze 2011-09-19
//inline bool	 g_IsDarkSpiritPet(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_MonsterCombat_DarkSpirit);}	//--����-- del by zhaoguoze 2011-09-19
//inline bool	 g_IsWindSpiritPet(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_PET_MonsterCombat_WindSpirit);}	//--����-- del by zhaoguoze 2011-09-19
inline bool  g_IsCar(int nType)				{return GetLeftThree(nType)	== GetLeftThree(OBJTYPE_ROLE_NPC_CAT);}	
inline bool	 g_IsPrivateCar(int nType)		{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_PRIVATE_CAT);}
inline bool  g_IsFamilyCar(int nType)		{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_FAMILY_CAT);}
inline bool  g_IsPrivateFamilyCar(int nType){return GetLeftFour(nType) == GetLeftFour(OBJTYPE_ROLE_NPC_FAMILY_PRIVATECAT);}
//inline bool  g_IsFamilyCommonCar(int nType) {return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_FAMILY_COMMON_CAT);}				//--����-- del by zhaoguoze 2011-09-19
//inline bool  g_IsFamilyDragonCar(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_FAMILY_DRAGON_CAT);}				//--����-- del by zhaoguoze 2011-09-19
//inline bool  g_IsFamilyTigerCar(int nType)	{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_ROLE_NPC_FAMILY_TIGER_CAT);}				//--����-- del by zhaoguoze 2011-09-19
//inline bool  g_IsMarryCar(int nType)		{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_ROLE_NPC_MARRY_CAT);}						//--����-- del by zhaoguoze 2011-09-19
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
//edit by youxl 2011.7.18//ȡ��mpwnpc�����⴦��
inline bool  g_IsMpwPerson( int nType)		{return (nType >= 7000 && nType <= 7999 )?true:false;}
//-end
inline bool	 g_IsLand(int nType)			{return GetLeftFour(nType)	== GetLeftFour(OBJTYPE_ROLE_NPC_LAND);}
//inline bool  g_IsFalseLand(int nType)		{return GetLeftFive(nType)  == GetLeftFive(OBJTYPE_ROLE_NPC_LAND_FALSE);}		//--����-- del by zhaoguoze 2011-09-19
//inline bool	 g_IsTriggerProp(int nType)		{return GetLeftFour(nType)	== GetLeftFour(OBJTYPE_ROLE_NPC_TRIGGERPROP);}	//--����-- del by zhaoguoze 2011-09-19
//inline bool	 g_IsTriggerMultiProp(int nType){return GetLeftFour(nType)  == GetLeftFour(OBJTYPE_ROLE_NPC_TRIGGERPROP_MULTI);}//--����-- del by zhaoguoze 2011-09-19

//Prop
inline bool g_IsProp(int nType)								{return GetLeftSingle(nType) == GetLeftSingle(OBJTYPE_PROP);}							//����
inline bool g_IsEquip(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_EQUIPMENT);}						//װ��

inline bool g_IsEquipWeapen(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_EQUIPMENT_WEAPEN);}			//����
inline bool g_IsPhysicalWeapen(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_WEAPEN_PHYSICAL);}		//����ϵ
inline bool g_IsMagicWeapen(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_WEAPEN_MAGIC);}		//����ϵ
inline bool g_IsToxophilyWeapen(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_WEAPEN_TOXOPHILY);}	//����ϵ
inline bool g_IsBlackartWeapen(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_WEAPEN_BLACKART);}		//����ϵ
inline bool g_IsTheurgyWeapen(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_WEAPEN_THEURGY);}		//����ϵ

inline bool g_IsEquipAssWeapen(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_EQUIPMENT_ASSWEAP);}			//����
inline bool g_IsAssPhysicalWeapen(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ASSWEAP_PHYSICAL);}	//����ϵ
inline bool g_IsAssMagicWeapen(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ASSWEAP_MAGIC);}		//����ϵ
inline bool g_IsAssToxophilyWeapen(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ASSWEAP_TOXOPHILY);}	//����ϵ
inline bool g_IsAssBlackartWeapen(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ASSWEAP_BLACKART);}	//����ϵ
inline bool g_IsAssTheurgyWeapen(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ASSWEAP_THEURGY);}		//����ϵ

inline bool g_IsEquipArmor(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_EQUIPMENT_ARMOR);}			//������װ��
inline bool g_IsEquipArmorHead(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ARMOR_HEAD);}		//ͷ��
inline bool g_IsEquipArmorChest(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ARMOR_CHEST);}		//����
inline bool g_IsEquipArmorWaist(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ARMOR_WAIST);}		//����
inline bool g_IsEquipArmorHands(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ARMOR_HANDS);}		//����
inline bool g_IsEquipArmorFeets(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_ARMOR_FEETS);}		//ѥ��

inline bool g_IsEquipJewelry(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_EQUIPMENT_JEWELRY);}			//�����Ʒ
inline bool g_IsEquipJewelryNecklace(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_JEWELRY_NECKLACE);}	//����
inline bool g_IsEquipJewelryRings(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_JEWELRY_RINGS);}		//��ָ
inline bool g_IsEquipJewelryShipin(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_JEWELRY_SHIPIN);}		//��Ʒ

inline bool g_IsEquipPet(int nType)							{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_EQUIPMENT_PET);}			//����װ��
inline bool g_IsEquipPetSaddle(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_PET_SADDLE);}		//��
inline bool g_IsEquipPetHorsewhip(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_PET_HORSEWHIP);}	//���
inline bool g_IsEquipPetWeskit(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_PET_WESKIT);}		//���
inline bool g_IsEquipPetSpur(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_PET_SPUR);}		//���
inline bool g_IsEquipPetFashion(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_PET_FASHION);}		//��ƥʱװ

inline bool g_IsEquipSpecial(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_EQUIPMENT_SPECIAL);}		//����װ��
inline bool g_IsEquipSpecialFashion(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_SPECIAL_FASHION);}	//ʱװ
inline bool g_IsEquipSpecialMantle(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_SPECIAL_MANTLE);}	//����
inline bool g_IsEquipSpecialEnsign(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_EQUIPMENT_SPECIAL_ENSIGN);}	//����

inline bool g_IsStuff(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_STUFF);}	//����

inline bool g_IsStuffCompose(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_STUFF_COMPOSE);}	//�������
inline bool g_IsComposeWood(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_COMPOSE_WOOD);}	//ľ��
inline bool g_IsComposeMetal(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_COMPOSE_METAL);}	//����
inline bool g_IsComposePiece(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_COMPOSE_PIECE);}	//��ƥ
inline bool g_IsComposeStone(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_COMPOSE_STONE);}	//ʯͷ
inline bool g_IsComposeLeather(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_COMPOSE_LEATHER);}	//Ƥ��

inline bool g_IsStuffStone(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_STUFF_ADDSTAR);}	//����
inline bool g_IsStarYu(int nType)							{return nType == OBJTYPE_PROP_STUFF_ADDSTAR_YOUSHI;}
inline bool g_IsPetStarYu(int nType)						{return nType == OBJTYPE_PROP_STUFF_PETADDSTAR_YOUSHI;}
inline bool	g_IsSealStone(int nType)						{return nType == OBJTYPE_PROP_STUFF_SEALSTONE; }	//����ʯ

inline bool g_IsStuffSign(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_STUFF_SIGN);}	//ǩ��
inline bool g_IsSignYin(int nType)							{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_SIGN_YINZHANG);}

inline bool g_IsStuffBind(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_STUFF_BIND);}	//��
inline bool g_IsBindFu(int nType)							{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_BIND_FUWEN);}

inline bool g_IsStuffHole(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_STUFF_ADDHOLE);}	//���
inline bool g_IsHoleZuan(int nType)							{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_ADDHOLE_ZUANTOU);}

inline bool g_IsStuffEnchase(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_STUFF_ENCHASE);}	//��Ƕ
inline bool g_IsEnchaseGem(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_STUFF_ENCHASE_GEM);}

inline bool g_IsMedicament(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_MEDICAMENT);}	//ҩ��
inline bool g_IsMedicamentCommon(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_MEDICAMENT_COMMON);}	//��ͨҩ��
inline bool g_IsMedicamentCommonHP(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_MEDICAMENT_COMMON_HP);}	//����
inline bool g_IsMedicamentCommonMP(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_MEDICAMENT_COMMON_MP);}	//����
inline bool g_IsMedicamentSpec(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_MEDICAMENT_SPEC);}		//����ҩ��
inline bool g_IsMedicamentSpecAttr(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_MEDICAMENT_SPEC_ATTR);}	//
inline bool g_IsMedicamentSpecFunc(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_MEDICAMENT_SPEC_FUNC);}	//
inline bool g_IsMedicamentEnergy(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_MEDICAMENT_ENERGY);}	//��������
inline bool g_IsMedicamentEnergyHP(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_MEDICAMENT_ENERGY_HP);}	//����
inline bool g_IsMedicamentEnergyMP(int nType)				{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_MEDICAMENT_ENERGY_MP);}	//����

inline bool g_IsBook(int nType)								{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_BOOK);}	//��
inline bool g_IsBookPhysical(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_BOOK_PHYSICAL);}	//����ϵ
inline bool g_IsBookMagic(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_BOOK_MAGIC);}	//����ϵ
inline bool g_IsBookToxophily(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_BOOK_TOXOPHILY);}	//����ϵ
inline bool g_IsBookBlackart(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_BOOK_BLACKART);}	//����ϵ
inline bool g_IsBooktheurgy(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_BOOK_THEURGY);}	//����ϵ
inline bool g_IsBookPet(int nType)							{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_BOOK_PET);}	//����

inline bool g_IsPropPet(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_PET);}				//������
inline bool g_IsPropPetEgg(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_PET_EGG);}		//���ﵰ
inline bool g_IsPropPetRid(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_PET_ZUOQI);}	//����
inline bool g_IsPropPetCombat(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_RPOP_PET_COMBAT);}	//ս��

inline bool g_IsPropSpeciality(int nType)					{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_SPECIALITY);}	//�ز�

inline bool g_IsPropFumo(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_FUMO);}	//��ħ
inline bool g_IsPropFumoMethod(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUMO_METHOD);} //��ħ�䷽
inline bool g_IsPropFumoMaterial(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUMO_MATERIAL);} //��ħ����
inline bool g_IsPropFumoCharm(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUMO_CHARM);} //��ħ���

inline bool g_IsPropFunction(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_FUNCTION);}	//����
inline bool g_IsPropFunctionReel(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_REEL);} //����
inline bool g_IsPropFunctionBooth(int nType)				{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_BOOTH);} //��̯��
inline bool g_IsPropFunctionHonor(int nType)				{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_HONOR);} //��������
inline bool g_IsContainerProp(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_CONTAINER);} //����

inline bool g_IsFunctionOther(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_OTHER);} //����

inline bool g_IsPropCar(int nType)							{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_CAR);} //ս��
inline bool g_IsPropCarFamily(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_CAR_FAMILY);} //����ս��
inline bool g_IsPropCarHealth(int nType)					{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_PROP_HEALTH_CAR_FAMILY);} //
inline bool g_IsPropCarDamage(int nType)					{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_PROP_DAMAGE_CAR_FAMILY);} //
inline bool g_IsPropCarDefence(int nType)					{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_PROP_DEFENCE_CAR_FAMILY);} //
inline bool g_IsPropCarCollect(int nType)					{return GetLeftFive(nType) == GetLeftFive(OBJTYPE_PROP_CAR_FAMILY_COLLECT);} //
//inline bool g_IsPropCarGang(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_CAR_GANG);} //���ս��

inline bool g_IsPropFamilyFunc(int nType)					{return GetLeftFour(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_FAMILY);} //�����Ṧ�ܵ���
inline bool g_IsPropFamilyDiChan(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_FUNCTION_FAMILY_DICHAN);} //�ز�֤��
inline bool g_IsPropMagicBox(int nType)						{return GetLeftFour(nType)== GetLeftFour(OBJTYPE_PROP_FUNCTION_FAMILY_MAGICBOX);} 
inline bool g_IsPropBossFood(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_FUNCTION_FAMILY_FOOD);}
inline bool g_IsPropFamilyQuest(int nType)					{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_FUNCTION_FAMILY_QUEST);}

inline bool g_IsFeeds(int nType)							{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_FUNCTION_FEEDS);}	//����
inline bool g_IsFeedsPet(int nType)							{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_FUNCTION_FEEDS_PET);}	
inline bool g_IsFeedsRide(int nType)						{return GetLeftFour(nType) == GetLeftFour(OBJTYPE_PROP_FUNCTION_FEEDS_RIDE);}	

inline bool g_IsPropMission(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_MISSION);}	//�������
inline bool g_IsPropMissionBook(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_MISSION_BOOK);}	//����
inline bool g_IsPropMissionUsed(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_MISSION_USED);}	//ʹ��
inline bool g_IsPropMissionEquip(int nType)					{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_PROP_MISSION_EQUIP);}	//װ��

inline bool g_IsGuoce(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_GUOCE);}	//����
inline bool g_IsHufu(int nType)								{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_HUFU);}	//����
inline bool g_IsShengWang(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_SHENGWANG);}//����
inline bool g_IsZhanhun(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_PROP_ZHANHUN);}	//ս��ʯ

//Skill
inline bool g_IsSkill(int nType)							{return GetLeftSingle(nType) == GetLeftSingle(OBJTYPE_SKILL);}			//����
inline bool g_IsCommonSkill(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_COMMON);}			//��ͨ����
inline bool g_IsRageSkill(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_RAGE);}		//ŭ������
inline bool g_IsXinFaSkill(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_XINFA);}		//�ķ�����
inline bool g_IsTreeSkill(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_TREESKILL);}		//���＼����
inline bool g_IsLiftSkill(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_LIFESKILL);}		//�����
inline bool g_IsNPCSkill(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_NPCSKILL);}		//npc����
inline bool g_IsPropSkill(int nType)						{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_PROPSKILL);}		//���߼���
inline bool g_IsEnchanting(int nType)						{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_SKILL_PROP_ENCHANTING);}	//��ħ����
inline bool g_IsPetSkill(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_PETSKILL);}		//���＼��
inline bool g_IsAddSkill(int nType)							{return GetLeftTwo(nType) == GetLeftTwo(OBJTYPE_SKILL_AddSkill);}
inline bool g_IsPetSafeGuardSkill(int nType)				{return GetLeftThree(nType) == GetLeftThree(OBJTYPE_SKILL_PETSKILL_SAFEGUARD);}		//�����ػ�����

//Server
inline bool g_IsServer(int nType)							{return GetLeftSingle(nType) == GetLeftSingle(OBJTYPE_SERVER); }	// ������Obj
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

