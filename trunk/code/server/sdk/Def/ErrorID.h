#pragma	   once
/* Error ID �� Text ID ��һһ��Ӧ�� ���Բ��ܸı����е� Error ID*/
enum GAME_WORLD_ERROR
{
	GAME_ERROR_FAIL = 0,
	GAME_ERROR_OK	= 1,
	PLAYER_NOT_ONLINE,										//�Է�������
	VERSION_ERROR,											//�汾����

	//�û�
	USER_LOGIN_OK		= 10,
	USER_LOGIN_OK_ENABLE_CREATEPLAYERBTN,
	USER_NOT_FIND,											//����˻�������
	USER_ERROR_PSW,											//���벻��ȷ
	PLAYER_CREAET_MAX_LIMIT,								//�޷�������ɫ�Ѿ������ֵ
	PLAYER_CREATE_NAME_REPEAT,								//�޷�������ɫ�����ظ�
	USER_NOT_DELETE_PLAYER_FAMILY,							//�м���ְ�Ʋ���ɾ����ɫ
	USER_NOT_DELETE_PLAEYR_MAIL,							//���ʼ�����ɾ��
	USER_NOT_DELETE_LEVEL,									//����ɾ���ߵȼ��Ľ�ɫ
	USER_CHECK_OK,											//�˺���֤ͨ��
	USER_CHECK_ERROR,										//�˺���֤ʧ��
	USER_LOGIN_ERROR,										//�˺ŵ�½ʧ��
	USER_LOGIN_ALREADY,										//�˺��Ѿ���¼
	USER_LOGIN_TARGETSERVERISFULL,						    //Ŀ��GameServer ����
	PLAYER_CREATE_NAME_ERROR,								//���ַǷ�
	PLAYER_LOGIN_DATASERVER_NOT_OPEN,							//������δ����
	PLAYER_LOGIN_SCENE_NOT_OPEN,								//����δ����
	PLAYER_LOGIN_SUCESS,

	USER_CHECK_NOTACTIVE,                                   // �ʺ�δ����
	USER_CHECK_STOPTEST,                                    // ��Ʒֹͣ����
	USER_LOAD_PLAYER_ERROR,									//���ؽ�ɫ��Ϣʧ��
	PLAYER_BE_FREEZED,										//��ɫ������


	USER_DEFAULT_SHOWMSG = 40,
	//����
	PLAYER_UPDATE_EXP	= 50,								//����仯
	PLAYER_UPDATE_LEVEL,									//�ȼ��仯
	PLAYER_UPDATE_HP,										//Ѫֵ�仯
	PLAYER_GET_HIT,											//������
	PLAYER_FIGHT_WIN,										//����Ŀ��
	PLAYER_ADD_BUFF,										//���buff
	PLAYER_REMOVE_BUFF,										//�Ƴ�buff
	PLAYER_COMMON_CD,										//������ȴʱ��δ��
	PLAYER_SKILL_CD,										//������ȴʱ��δ��
	PLAYER_NOT_MP,											//û��Mp
	PLAYER_NOT_TARGET_ZONE,									//����Ŀ������
	PLAYER_NOT_TARGET_TEMPLATE,								//����Ŀ��ģ��
	PLAYER_NOT_TARGET,										//����Ŀ��
	PLAYER_NOT_TARGET_STATUS,								//Ŀ��״̬����ȷ
	ATTACK_NEED_TARGET,										//��ѡ�񹤾�Ŀ��
	ATTACK_WEAPEN_RESTICK,									//��������
	ATTACK_TARGET_NOT_EXIST,                                //����Ŀ�겻����
	ATTACK_NOT_ALL_FRIEND,                                  //ȫ���ƽ��Ӫ���ܹ���
	ATTACK_NOT_STATE_FRIEND,                                //�����Ѻò��ܱ�����
	ATTACK_NOT_TEAM_FRIEND,                                 //����Ѻò��ܹ���
	ATTACK_NOT_FAMILY_FRIEND,                               //�����Ѻò��ܹ���
	ATTACK_NOT_SAME_SCENE,                                  //����ͬһ���������ܹ���
	ATTACK_NO,                                              //���ܹ���
	ATTACK_TARGET_POINT_TO_FAR,								//Ŀ����Զ
	ATTACK_CANT_ATTACK,										//�޷�����
	PLAYER_NO_CONTROL,										//�޷�����
	//PLAYER_EXP_ADDITION_TEAM,								//��Ӿ���ӳ�  --[060��Ӿ���ӳ�]%d������%d������ֵ
	PLAYER_STORAGE_EXPERIENCE_TOPLIMIT,						//�����ۻ��ѵ�����


	//����
	BAG_IS_FULL	= 100,										//��������
	BAG_ADD_PROP,											//���ӵ���
	BAG_ADD_PROP_STACKABLE,									//���ӿɶѵ�����
	BAG_REMOVE_PROP,										//�Ƴ�����
	BAG_TARGET_IS_FULL,										//�Է���������
	BAG_RID_PROP_BIND_CANT_MOVEBACK,                        //�󶨳�����߲����ƻر���
	BAG_RETINUE_PROP_BIND_CANT_MOVEBACK,                    //���̴ӵ��߲����ƻر���
	BAG_PROP_WRONG_POSTION,                                 //���߲���װ������λ��
	BAG_ENSIGN_EXIST,                                       //���о��������װ��������
	BAG_ENERGY_EXIST,										//���о��������װ��������
	BAG_HONOR_EXIST,										//�������������װ��������
	BAG_POSITION_CAN_UNEQUIP,                               //��λ�ò���ȡ��
	BAG_CANT_ADD_NO_CONTAINER,                              //�Ǳ�����ĵ��߲��ܷű�����
	BAG_RID_BAG_CANT_ADD,                                   //�������߲��ܷ�����豳����
	BAG_RETINUE_BAG_CANT_ADD,                               //���̴ӵ��߲��ܷ����̴ӱ�����
	BAG_BINDPROP_ONLY_ADD_MASTER,                           //�󶨵��߲�����Ӹ������˵ı���
	BAG_COUNT_MAX_LIMIT,                                    //�ﵽ��ӱ���������
	BAG_POSTION_HAS_PROP,                                   //��λ�����е���
	BAG_EXTERN_BAG_IS_NOT_EMPTY_CANT_DEL,                   //��չ������Ϊ�ղ���ɾ��
	BAG_EXTERN_BAG_IS_NOT_EMPTY_CANT_EQUIP,                 //��չ������Ϊ�ղ���װ��
	BAG_MOVE_FAILD,                                         //�ƶ�ʧ��
	BAG_BEFORE_EQUIP_REMOVE_FAILD,                          //ԭ��װ��ж��ʧ��
	BAG_STASH_EXTBAG_FULL,									//�ֿⱳ��������
	BAG_HAVE_NO_SPACE,										//����ʣ��ռ䲻��
    BAG_STASH_FULL,                                         //���б�����
	BAG_FAMILY_FULL,                                        //����������
	BAG_GANG_FULL,                                          //���������
	BAG_STASH_BUY_SUCCESS,                                 //����ֿⱳ���ɹ�
	BAG_STASH_BUY_FAILD,
	BAG_NOMONEY,											//�����е����Ӳ���
	BAG_HAVEPROP_NOUNEQUIP,									//�������е����޷�ж��
	BAG_PETEQUIP_EQUIPLEVELHIGHT,							//���װ���ȼ�����
	BAG_CANNOT_REPLACEBAG,									//�޷��滻����
	BAG_IS_FULL_CATCH_FAIL,									//��׽ʧ�ܣ�û�п��౳���ռ�


	//��Ǯ
	MONEY_NOT_ENOUGH = 150,									//��Ǯ����
	CURRENCY_NOT_ALLOWABLE,									//�������Ͳ���
	PLAYER_ADD_MONEY,										//��� ���
	PLAYER_REMOVE_MONEY,									//���� ���
	GONGXUN_NOT_ENOUGH,                                     //��ѫֵ����
	FAMILYWAGE_NOT_ENOUGH,                                  //���ʲ���
	ERROR_OTHER_BIND_MONEY_CMAX,							//��������
	HEROILANDCURRENCY_NOT_ENOUGH,							//�㽫̨���ֲ���
	XUNZHANG_NOT_ENOUGH,

	//������ش���
	QUEST_NO_SELECT_PRIZE_PROP = 200,						//��ѡ��һ���������
	QUEST_IS_COMPLETE,										//����ﵽ���״̬
	QUEST_IS_ACCEPT,										//��������
	QUEST_IS_FAILD,                                         //����ʧ��
	QUEST_IS_NO_ACCEPT,                                     //�����ܽ���
	QUEST_IS_NO_COMPLETE,									//������ʱ�������
	QUEST_IS_NO_DELETE,                                     //������ɾ��
	QUEST_CAR_NO_ACCEPT,                                    //���ѽ���һ���ڳ���������
	QUEST_CAR_NO_TRANS,                                     //�����ڳ����ܽ��д���
	QUEST_IS_OUT_NUM,                                       //������������
	QUEST_TIMELIMIT_OUT,                                    //��ʱ����һ��ֻ�ܽ�һ��
	QUEST_GAME_TIME_NO_SUIT,                                //�ʱ��δ��
	QUEST_COUNT_IS_OUT,                                     //��������
	QUEST_LEVEL_LIMIT,                                      //�ȼ�����
	QUEST_PRIZE_FAILED,                                     //������ʧ��
	QUEST_PROP_ACCEPT_AGAIN,                                //���ߴ��������ѽ�
	QUEST_PREQUEST_NOT_COMPLETE,                            //ǰ������û���
	QUEST_CAMPAIGN_NOT_START,                               //���û��ʼ
	QUEST_HAS_COMPLETED,                                    //�����������񣬲�������
	QUEST_HAS_ACCEPTED,                                     //����������
	QUEST_COUT_LIMIT,                                       //�Ѿ�������������
	QUEST_IS_OVER,                                          //�������
	QUEST_IS_EXCLUSIVE,                                     //��������
	QUEST_COMPLETE_FAILD,                                   //�����ύʧ��
	QUEST_IS_NOT_THIS_NPC,									//���������npc�ύ
	QUEST_IS_NEED_FRIEND,									//������Ҫ��һ������
	QUEST_IS_NEED_MASTER,									//������Ҫ��ʦͽ��ϵ
	QUEST_IS_NEED_MARRY,									//������Ҫ������ܽ�
	QUEST_IS_NEED_FAMILY,									//������Ҫ�м���
	QUEST_IS_NEED_GANG,										//������Ҫ�а��
	QUEST_IS_NEED_WEEKSTAE,									//������Ҫ����������
	QUEST_IS_NEED_STRENTHSTATE,								//������Ҫ������ǿ��
	QUEST_PRIZE_SLIVER,										//��������
	QUEST_PRIZE_BINDSLIVER,									//����������
	QUEST_PRIZE_EXP,										//��������
	QUEST_QUESTFOLLOW,										//���浥λ����
    QUEST_NOT_COMMON_STATUS,								//���Ŀǰ������ͨ״̬�������״̬������������״̬
	QUEST_PRIZE_SKILLPOINT,									//���������ܵ�
	QUEST_PRIZE_PNEUMA,										//������Ԫ��ֵ
	QUEST_PRIZE_PRACTISE,									//������������ѫ
	QUEST_IS_NEED_PROP,									    //������Ҫ����
	QUEST_ABANDON,											//��������
	QUEST_NO_NESESSARYQUEST,								//ǰ������δ����

	//����
	QUESTION_ERROR             = 250,                       //�����ٽ���
	QUESTION_OUT_TIME,                                      //���ڴ����ڼ�
	QUESTION_LEVEL_LIMIT,									//����ȼ�����
	QUESTION_DROP_OUT,										//��ǰ�˳�


	//����
	TEAM_TYPE_DIFFERENT = 300,  							//��ӷ�ʽ��ͬ
	TEAM_PLAEYR_BUSY,            							//��ӵ�����æ���������
	TEAM_PLAYER_IN_SAMETEAM,                                //�Է��Ѿ��ڶ�����
	TEAM_PERSON_IN_OTHERTEAM,      			    			//�Է�������һ��������
	TEAM_IS_FULL,                							//������������
	TEAM_NOT_TEAMCAPTION_NO_POWER,         	    			//���Ƕӳ�û��Ȩ��
	TEAM_NOT_TEAMCAPTION_NO_INVITE_POWER,  	    			//���Ƕӳ�û��Ȩ������
	TEAM_NOT_TEAMCAPTION_APPLICATE,   						//ֻ����ӳ��������
	TEAM_NOT_TEAM_HONOR_CONDITION,               			//��������������������ӳ�����60�����ϣ�������֮��
	TEAM_NOT_CHANGE_CAPTION_HONOR,                          //������Ӳ����ƽ��ӳ�
	TEAM_DENY,												//�ܾ��������
	TEAM_REMOVE_TEAM_MEMBER,								//�Ƴ�����
	TEAM_ADD_TEAM_MEMBER,									//�������
	TEAM_PLAYER_QUIT,                                       //�˳�����
	TEAM_PLAYER_NOT_ONLINE,             					//��Ա����
	TEAM_PLAYER_ONLINE,                                     //��Ա����
	TEAM_IS_DISBAND,                                        //�����ѽ�ɢ
	TEAM_TEAMCAPTION_IS_REMOVE,                             //�ƽ��ӳ�
	TEAM_TEAMWAY_IS_CHANGE,                                 //������ӷ�ʽ
	TEAM_TEAMWAY_IS_CHANGE_ORDINARY,                        //������ӷ�ʽ
	TEAM_PICKWAY_IS_FREEDOM,                                //����ʰȡ��ʽ
	TEAM_PICKWAY_IS_ROTATION,                               //����ʰȡ��ʽ
	TEAM_PICKWAY_IS_RANDOM,                                 //����ʰȡ��ʽ
	TEAM_EXPWAY_IS_SPECIAL,                                 //���ľ�����䷽ʽ
	TEAM_EXPWAY_IS_LEVEL,                                   //���ľ�����䷽ʽ
	TEAM_LEAVE,                                             //�Լ��뿪����
	TEAM_JOIN,                                              //�Լ��������
	TEAM_RECRUIT_IS_AUTO,									//������ļ��ʽΪ�Զ�
	TEAM_RECRUIT_IS_MANUAL,									//������ļ��ʽΪ�ֶ�
	TEAM_PLAYER_NOT_EXIST,									//��Ҳ�����
	TEAM_CANT_FIND,											//�Ҳ�������
	TEAM_HONOR_MAX_NUM,										//���������������
	TEAM_NOT_TEAM_HONOR_CONDITION_MEMBER_LEVEL,             //������Ӷ�Ա����60������
	TEAM_WAITING_REQUEST_REPLY,
	TEAM_BECOME_CAPTION,									//XX��Ϊ�˶ӳ�
	TEAM_CONNOT_WITH_SELF,									// �������Լ����
	TEAM_NOT_CHANGE_EXPWAY,									//������Ӳ��ܸ��ľ�����䷽ʽ
	TEAM_CHANGE_TEAMWAY,									//�ж��ѵȼ�����60����������Ӹı�Ϊ��ͨ���
	TEAM_CAPTION_DENY_ADD,									//����ӳ��ܾ���������
	TEAM_CONNOT_WITH_ENEMY,									//������ж����
	TEAM_NO_ALLOW,											// �Է��ر�����ӱ����빦��
	TEAM_MAP_NOT_ALLOW1,									//�˵�ͼ�������
	TEAM_MAP_NOT_ALLOW2,									//����ҵ�ǰ���ڵĵ�ͼ���������

	//�����Ĵ�����Ϣ
	BAG_FULL_PACKAGE = 500,           						//��������
	MAP_CANNOT_USED,                						//�˵�ͼ����ʹ��
	FEE_NOT_ENOUGH,                    						//�����Ѳ���
	JUST_DIVORCE_CANNOT_REMARRY,    						//�������˲��������ٻ�


	//��ͼ
	MAP_POS_INVALID  = 600,									//�������Ч

	//���� ��fuck
	PRIVATE_NOT_ONLINE			   = 650,
	PRIVATE_IS_DEAD,
	//���˹�ϵ(˭Ҳ����ռ�� Ŷ)
	//����
	PRIVATE_FRIEND_REQUEST_ADDSELF = 700,					//���ܼ��Լ�Ϊ����
	PRIVATE_FRIEND_TARGET_OFFLINE,							//�Է�������
	PRIVATE_FRIEND_HAD_INFRIENDLIST,						//XXX���ں����б���
	PRIVATE_FRIEND_CLOSE_ADDFRIEND,							//XXX�ر��˱�������Ӻ��ѹ���
	PRIVATE_FRIEND_SELF_ISFULL,								//��ĺ��������Ѵ�����
	PRIVATE_FRIEND_TARGET_ISFULL,							//XXX�ĺ��������Ѵ�����
	PRIVATE_FRIEND_TARGET_REFUSE,							//XXX�ܾ�����������
	PRIVATE_FRIEND_WAIT_TARGET,								//���ڵȴ�XXX��������
	PRIVATE_FRIEND_INVITOR_OFFLINE,							//�������Ѿ����ߣ��޷���Ӻ���

	PRIVATE_FRIEND_ADD_FRIEND,								//����XXX��Ϊ����
	PRIVATE_FRIEND_REMOVE_FRIEND,							//�Ƴ�����
	PRIVATE_FRIEND_LEAVE_WORLD,								//����ɾ��

	//������
	PRIVATE_BLOCK_REQUEST_ADDSELF,							//���ܰ��Լ����������
	PRIVATE_BLOCK_SELF_ISFULL,								//��ĺ����������Ѵ�����
	PRIVATE_BLOCK_HAD_INBLOCKLIST,							//XXX�������ĺ�������
	PRIVATE_BLOCK_ADD_BLOCK,								//��XXX���������
	PRIVATE_BLOCK_REMOVE_BLOCK,								//��XXX�Ƴ�������
	PRIVATE_BLOCK_TARGET_OFFLINE,							//�Է������ߣ����ܼ�Ϊ������

	//����
	PRIVATE_ENEMY_TARGET_INFRIENDLIST,						//�Է�����ĺ��ѣ���ӳ���ʧ�ܡ�
	PRIVATE_ENEMY_HAD_INENEMYLIST,							//�Է��������ĳ����б��У���ӳ���ʧ�ܡ�
	PRIVATE_ENEMY_SELF_ISFULL,								//�����б��Ѵﵽ���ޣ����ʧ�ܡ�

	PRIVATE_ENEMY_ADD_ENEMY,								//�㱻xxx���ܣ���xxx������ĳ����б�
	PRIVATE_ENEMY_REMOVE_ENEMY,								//����xxx������ˡ�

	//�����
	PRIVATE_DEEPENEMY_TARGET_INFRIENDLIST,					//Ŀ�����Ϊ��ĺ��ѣ���������ʧ�� ��
	PRIVATE_DEEPENEMY_HAD_DEEPINENEMYLIST,					//�������Ϊ���������
	PRIVATE_DEEPENEMY_REQUEST_ADDSELF,						//���ܽ��Լ����Ϊ����ޡ�
	PRIVATE_DEEPENEMY_SELF_ISFULL,							//����������б��Ѿ��ﵽ���ޣ����ʧ�� ��

	PRIVATE_DEEPENEMY_ADD_DEEPENEMY,						//��Ŀ����Ҽ���������б�
	PRIVATE_DEEPENEMY_REMOVE_DEEPENEMY,						//����xxx�������ޡ�

	PRIVATE_DEEPENEMY_TARGET_OFFLINE,						//�Է������ߣ����ܼ�Ϊ�����

	//����
	PRIVATE_CONSORT_PLAYER_GIVEUP,							//XXX��δ���Ǻã����δ���
	PRIVATE_CONSORT_REMOVE_CONSORT,							//����أأؽ�����޹�ϵ
	//���
	PRIVATE_SWORN_REMOVE_SWORN,								//471XXX��������� ���������

	//����
	FAMILY_EXIT_CYCLE_CANNOT_CREATE = 800,					//�˳�����һ��ʱ���ڲ��ܴ�������
	FAMILY_PLAEYR_BUSY,										//����æ
	FAMILY_REPLY_DENY,										//�ܾ��������
	FAMILY_ALREADY_JOIN_CANNOT_CREATE,     					//�Ѽ�������޷�������������
	FAMILY_BANKROLL_NOT_ENOUGH_CANNOT_CREATE,               //�ʽ���,���ܴ�������
	FAMILY_BANKROLL_NOT_ENOUGH_CANNOT_APPLY,                //�ʽ���,�����������ׯ԰
	FAMILY_NOT_ACHIEVE_CREATE_LEVEL,       					//δ�ﵽ������������ȼ�
	FAMILY_BEYOND_WORD_LIMIT,                     			//������������
	FAMILY_BEYOND_PASSWORD_LIMIT,							//�������볬��6λ����
	FAMILY_NAME_CONTAIN_ILLEGAL_CHAR,             			//�������ư����Ƿ��ַ�
	FAMILY_NAME_AND_PASSWORD_CANNOT_NULL,                   //�������ƺ����벻��Ϊ��
	FAMILY_NAME_REPEAT,                           			//���������ظ�
	FAMILY_NOT_INPUT_REQUIRE_REENTER,                       //����������Ҫ������������
	FAMILY_LEVEL_NOT_ENOUGH_CANNOT_JOIN,					//�ȼ��������ܼ������
	FAMILY_NOT_SAME_STATE_PLAYER_CANNOT_INVITE,				//����ֻ������ͬ����Ҽ���
	FAMILY_HAVE_BEEN,                     					//���м���
	FAMILY_NOT_IN_GANG,										//���岻�ڴ˰����
	FAMILY_EXIT_CYCLE_CANNOT_JOIN,        					//�˳�����һ��ʱ���ڲ��ܼ������
	FAMILY_IS_FULL,                       					//������������
	FAMILYCAPTION_OFFLINE,                					//�峤������
	FAMILY_NOT_FIND_PLAYER,                      			//�Ҳ��������
	FAMILY_NOT_FIND_FAMILY,									//�Ҳ����ü���
	FAMILY_CANNOT_IMMEDIACY_FIRE_OFFICIAL,       			//����ֱ�ӿ�����Ա
	FAMILY_NO_POWER,                             			//û��Ȩ��
	FAMILY_CAPTION_NO_SET_CAPTION,							//�峤���������Լ���Ȩ��
	FAMILY_ASSISTANT_NO_SET_SELFPOWER,						//���峤���������Լ���Ȩ��
	FAMILY_ASSISTANT_NO_SET_CAPTION,						//���峤���������峤��Ȩ��
	FAMILY_ASSISTANT_NO_SET_CAPTION_TITLE,					//���峤���������峤�ĳƺ�
	FAMILY_PWD_ERROR,                            			//�������
	FAMILY_POST_HAVE_MEMBER,                     			//ְλ���г�Ա����
	FAMILY_CANNOT_REMOVE_AGAIN,                  			//�����ٴ��ƽ�
	FAMILY_NOT_ACHIEVE_UPGRADE_PROSPERITY,       			//δ�ﵽ�������跱�ٶ�
	FAMILY_FUND_NOT_ENOUGH,               					//�����ʽ���
	FAMILY_CANNOT_LEARN_MORE_SKILL,       					//����ѧϰ������弼��
	FAMILY_OFFER_NOT_ENOUGH,                     			//���׶Ȳ���
	FAMILY_BANKROLL_NOT_REOUGH,								//�ʽ���
	FAMILY_FAMILYCAPTION_NOT_CANNOT_SUMMON,       			//ֻ���峤�����ٻ�
	FAMILY_BEYOND_BY_UPPERLIMIT,                  			//������������
	FAMILY_NOT_HOLD_MORE_TANK,                    			//����ӵ�и���ս��
	FAMILY_NOT_ARM_USE_POWER,              					//û�м���װ��ʹ��Ȩ��
	FAMILY_AFTER_REPAIR_CONTINUE_USE,             			//�������ܼ���ʹ��
	FAMILY_TANK_DAMAGE,                           			//ս��������
	FAMILY_GOT_OFF,                               			//�����³�
	FAMILY_NOT_ACHIEVE_CAPTION_TIME,						//�峤һ��ֻ������һ��
	FAMILY_CREATE_SUCCESS,                                  //��������ɹ�
	FAMILY_CREATE_FAILURE,                                  //��������ʧ��
	FAMILY_NOT_IN_FAMILY,                                   //���ڼ�����
	FAMILY_MENMBER_IS_LEAVE,                                //�뿪����
	FAMILY_ONLY_CAPTION_CAN_UPGRADE,                        //ֻ���峤������������
	FAMILY_LEVEL_UP_SUCCESS,                                //��������ɹ�
	FAMILY_LEVEL_UP_FAILURE,                                //��������ʧ��
	FAMILY_EQUIPMENT_RETURN_SUCCESS,                        //�黹װ���ɹ�
	FAMILY_EQUIPMENT_RETURN_FAILURE,                        //�黹װ��ʧ��
	FAMILY_SKIll_LEARN_SUCCESS,                             //ѧϰ���ܳɹ�
	FAMILY_SKIll_LEARN_FAILURE,                             //ѧϰ����ʧ��
	FAMILY_SET_CAPTION_POWER_SUCCESS,                       //�����鳤Ȩ�޳ɹ�
	FAMILY_SET_CAPTION_POWER_FAILURE,                       //�����鳤Ȩ��ʧ��
	FAMILY_SET_ASSISTANT_POWER_SUCCESS,                     //���ø��鳤Ȩ�޳ɹ�
	FAMILY_SET_ASSISTANT_POWER_FAILURE,                     //���ø��鳤Ȩ��ʧ��
	FAMILY_SET_MEMBER_POWER_SUCCESS,                        //���ó�ԱȨ�޳ɹ�
	FAMILY_SET_MEMBER_POWER_FAILURE,                        //���ó�ԱȨ��ʧ��
	FAMILY_Title_GIVE_SUCCESS,                              //����ƺųɹ�
	FAMILY_Title_GIVE_FAILURE,                              //����ƺ�ʧ��
	FAMILY_YOU_HAVENOT_FAMILY,                              //��û�м���
	FAMILY_DONATINGMONEY_SUCCESS,                           //���׼����ʽ�ɹ�
	FAMILY_DONATINGMONEY_FAILURE,                           //���׼����ʽ�ʧ��
	FAMILY_PUBLIC_CONTAIN_ILLEGAL_CHAR,                     //���幫�溬�зǷ��ַ�
	FAMILY_JOIN_MEMBER_ACCEPT,							    //��ӭ�������
	FAMILY_JOIN_PARIVATE_ACCEPT,							//�������ɹ�
	FAMILY_REMOVE_MEMBER_NUMBER,							//�峤ÿ��ֻ���Ƴ�3����Ա
	FAMILY_CREATE_SCENE_FAILURE,							//û��Ȩ���������ׯ԰
	FAMILY_QUIT_ALL_MEMBER,									//��ȫ��������˷���ĳ���뿪�������Ϣ
	FAMILY_APPLY_SCENE_FAILURE,								//���������ׯ԰
	FAMILY_APPLY_SCENE_ACCEPT,								//�������ׯ԰�ɹ�
	FAMILY_NO_APPLY_SCENE,									//�����峤û�����������ׯ԰
	FAMILY_ONLY_GET_ONE_FAMILY_CAR,							//ֻ����ȡһ������ս��
	FAMILY_GET_CAR,											//��ȡ�˼���ս��
	FAMILY_BACK_CAR,										//�黹�˼���ս��
	FAMILY_RESEARCH_SKILL_NOT_LEVEL,						//�о����弼�ܵȼ�����
	FAMILY_LEARN_SKILL_NOT_LEVLE,							//�õȼ����ܼ��廹δ�о�����
	FAMILY_RESEARCH_SKILL_NOT_CAPTION,						//���Ǽ����峤û��Ȩ���о����弼��
	FAMILY_LEAVE_SKILL_NOT_HAVA,							//�ü�����û��ѧϰ������������ʧ��
	FAMILY_RESEARCH_SKILL_ACCEPT,							//�о����弼�ܳɹ�
	FAMILY_LEARN_SKILL_ACCEPT,								//ѧϰ���弼�ܳɹ�
	FAMILY_LEAVE_SKILL_ACCEPT,								//�������弼�ܳɹ�
	FAMILY_MEMEBER_ADD_WRONG,                               //��Ӽ����Աʧ��
	FAMILY_FIND_FAILD,                                      //�Ҳ�������
	FAMILY_MONEY_NOT_ENOUGH,                                //�����ʽ𲻹�
	FAMILY_CONSTRCT_NOT_ENOUGH,                             //���幱��ֵ����
	FAMILY_MEMBER_NOT_EXIST,                                //�����Ա������
	FAMILY_MEMBER_IS_DEAD,									//�����Ա�����������ٻ�
	FAMILY_CAPTION_IS_DEAD,                                 //�峤�����������ٻ�
	FAMILY_MONEY_NOT_LESSZERO,                              //���׼����ʽ���С��0
	FAMILY_CAR_HAS_PULL_SELF,                               //����ս�����Ѿ���ȡ
	FAMILY_CAR_HAS_PULL_ANOTHER,							//����ս����������ȡ��
	FAMILY_CAR_GET_ACCEPT,									//����ս����ȡ�ɹ�
	FAMILY_CAR_NOT_EXIST,                                   //����ս��������
	FAMILY_MEMBER_NOT_IN_SAME_FAMILY,                       //����һ������ĳ�Ա
	FAMILY_CAR_MASTER_NOT_EXIST,							//�Ҳ���ս������
	FAMILY_ACTIVE_VALUE_FAILD,                              //���ü��己�ٶ�ʧ��
	FAMILY_SUMMON_CANT_HAVE_CAR,                            //�����ٻ����ڳ��ļ����Ա
	FAMILY_SUMMON_ONLY_CAPTION,                             //ֻ���峤�����ٻ�
	FAMILY_CREDIT_MAY_NOT_SAVE,								//���幱�׶�û��Ҫ���
	FAMILY_CAR_HP_NOT_USE,									//����ս���ѻ�����ʹ��
	FAMILY_SET_POWER_FAILD,									//�Է��ȼ�������ת���峤ʧ��
	FAMILY_GANG_CAPTION_CHANGE,								//��Ϊ����������ת�����峤Ȩ��
	FAMILY_BOSS_NOT_FEED,									//����ι��boss��ʳ��
	FAMILY_BOSS_NOT_CREATE,									//����û����������boss
	FAMILY_BOSS_FEED_TIME,									//һ��ֻ��ι��һ�μ���boss������������
	FAMILY_BOSS_WRITE,										//��ϲ��ð�boss
	FAMILY_BOSS_BLUE,										//��ϲ�����boss
	FAMILY_BOSS_GREEN,										//��ϲ�����boss
	FAMILY_BOSS_BLACK,										//��ϲ�����boss
	FAMILY_DANCE_ACTION_START,								//������ʨ���ʼ
	FAMILY_DANCE_ACTION_END,								//������ʨ�����
	FAMILY_DISS_STATE,										//��ǰ��������ɢ���̣������������ʽ��ɢ
	FAMILY_BOSS_FEED_ACCEPT,								//ιʳ�ɹ�
	FAMILY_BOSS_ACCEPT,										//��ϲ��������ս����boss�ɹ���
	FAMILY_BAG_NOT_HAVE_PROP,								//�������ﲻ���ڼ���ѫ��
	FAMILY_CAR_CHAGE_NAME_ACCEPT,							//ս�������ɹ�
	FAMILY_CAR_UPDATE_ACCEPT,								//ս�������ɹ�
	FAMILY_DAOCHANG_ACCEPT,									//�����ɹ�
	FAMILY_CAR_BACK_ACCEPT,									//�黹ս���ɹ�
	FAMILY_CAR_DOING,										//��ս�����ڱ�������ʹ��
	FAMILY_CAR_REMOVE_ACCEPT,								//ս���ݻٳɹ�
	FAMILY_CAR_COMPOSE_SUCCES,								//ս������ɹ�
	FAMILY_CAR_NOT_NAME,									//����ս�����ֹ���
	FAMILY_ADD_CAR_PERSON_ACCEPT,							//����ս������ɹ�
	FAMILY_REMOVE_CAR_PERSON_ACCEPT,						//�Ƴ�ս������ɹ�
	FAMILY_CAPTION_REMOVE_CAR_PERSONG,						//��ս�����Ƴ�ս������
	FAMILY_REMOVE_CAR_ACCEPT,								//�뿪ս������ɹ�
	FAMILY_MAX_LEVEL,										//�Ѿ����������ߵȼ�
	FAMILY_ADD_MEMBER_SUCCESS,								//��������³�Ա
	FAMILY_REMOVE_MEMBER_SUCCESS,							//�����Ա�˳�
	FAMILY_EXIT_SUCCESS,									//�˳�����ɹ�
	FAMILY_TRANSFER_BOSS_FREQUENTLY,						//�����ƽ�����ʱ�䲻������24Сʱ
	FAMILY_IS_REMOVED_BY_CAPTION,							//���屻�Ӱ�����Ƴ�
	FAMILY_PLAYER_IN_CAR,
	FAMILY_ACQUIRE_FAMILY_SCENE,							//��ϲ�����ü���ׯ԰
	FAMILY_BEAPPOINT_FOODER,								//�峤����xxΪ����ʳ��
	FAMILY_LEVEL_UP,										//��ϲ������ΪX������
	FAMILY_PK_FAMILYTHIEF_FAILED,							//��ս��ʱ���������ׯ԰ʧ��
	FAMILY_REQUEST_PK_FEEDBOSS,								//�����쵼����Լ���boss����ս
	FAMILY_PK_BOSS_FAILED,									//����boss��ս��ʱ
	FAMILY_PK_THIEF_OVER,									//��ׯ԰�������ս�ѽ�������������
	FAMILY_FEED_BOSS,										//%s ������Bossιʳ��һ��%sɫ���˲ι�


	FAMILY_CAR_REPAIR_SUCCESS,						//ս������ɹ�
	FAMILY_CAR_REPLACE_FAILED,								//�滻ս��ʧ��
	FAMILY_CAR_CALLBACK_FAILED,							//�ջ�ս��ʧ��
	FAMILY_COST_EVERYDAY,							//ÿ��ά�����ļ����ʽ�
	FAMILY_CAR_USEING,								//ս������ʹ����
	FAMILY_CAR_MAXNUM,								//ս���Ѵﵽ���

	FAMILY_CAR_CARCARRY_STATUE,					//���ڻ���״̬������ս��
	FAMILY_CAR_STATUE_NO_INVITE,	//���ܱ�������ս��
	FAMILY_CAR_STATUE_NO_ENTER, //���ڼ���ս�����������һ��ս��
	FAMILY_CAR_BEKICKED,		//���߳�ս��
	FAMILY_AUTO_DISMISS,
	//������ս��
	FAMILY_WAR_FLAG_USEING, //��ʹ����
	FAMILY_WAR_NO_FAMILY,
	FAMILY_APPLAY_SCENE_WARN,
	FAMILY_LEVEL_DEGREE,
	FAMILY_MONEY_UP,
	FAMILY_WAIT_JOIN,
	FAMILY_CAR_FAR_TO_CAR,		//Զ��ս������¼ʧ��
	FAMILY_CAR_COMBINPET_NO_INVITE,							//��ս�����״̬�����ܱ�������ս�� add by zhangjianli 2012-5-2
	FAMILY_BOSS_BE_DARED,
	FAMILY_CAR_STATUS_STALL_NO_GOUP,                        //��̯״̬�²�������ս��
	FAMILY_CAR_SUMMONFAIL_NO_FAMILYCAR,						//�㵱ǰ��û����ȡս��
	FAMILY_CAR_SUMMONFAIL_STATUS_STALL,                     //��̯״̬�£������ٻ�ս��
	FAMILY_CAR_SUMMONFAIL_STATUS_CHANGEMODEL,				//����״̬�£������ٻ�ս��
	FAMILY_CAR_SUMMONFAIL_STATUS_COMBINPET,					//����״̬�£������ٻ�ս��
	FAMILY_CAR_SUMMONFAIL_STATUS_BUFF_GUIDON,				//����״̬�£������ٻ�ս��
	FAMILY_CAR_SUMMONFAIL_SCENE_NOACCEPT,					//��ǰ���������ٻ�ս��
	FAMILY_CAR_SUMMONFAIL_STATUS_FAMILYCAR,					//��ǰ����ս��״̬
	FAMILY_CAR_ADD_SUCCESS,									//���ս���ɹ�
	FAMILY_CAR_ADD_FAILED,									//���ս��ʧ��

	//���
	GUILD_EXIT_CYCLE_CANNOT_CREATE = 1000, 					//�˳����һ��ʱ���ڲ��ܴ������
	GUILD_CAPTION_NO_REMOVE_FAMILY_CAPTION,					//�������ܲ����峤
	GUILD_REPLY_DENY,										//�ܾ�������
	GUIlD_NO_RECRUIT_NOTFAMILY_CAPTION,						//����ֻ�������峤����
	GUILD_GANGCAPTION_NO_REMOVE_OWNFAMILY,					//���������Ƴ��Լ����ڵļ���
	GUILD_NOT_SAME_STATE,									//����ͬһ����
	GUILD_ALREADY_JOIN_CANNOT_CREATE,     					//�Ѽ������޷������������
	GUILD_BANKROLL_NOT_ENOUGH,								//�ʽ���
	GUILD_FAMILY_NUM_NOT_ACHIEVE_BUILD_REQUIRE,				//��������δ�ﵽ�齨���Ҫ��
	GUILD_FAMILY_LEVEL_NOT_ACHIEVE_BUILD_REQUIRE,			//����ȼ�δ�ﵽ�齨���Ҫ��
	GUILD_NOT_LAND_PROVE,                        			//û�еز�֤��
	GUILD_BEYOND_WORD_LIMIT,                     			//������������
	GUILD_NAME_CONTAIN_ILLEGAL_CHAR,             			//���ư����Ƿ��ַ�
	GUILD_NAME_REPEAT,                           			//�����ظ�
	GUILD_NOT_INPUT_REQUIRE_REENTER,             			//����������Ҫ������������
	GUILD_HAVE_BEEN,                       					//���а��
	GUILD_EXIT_CYCLE_CANNOT_JOIN_GUILD,    					//�˳����һ��ʱ���ڲ��ܼ�����
	GUILD_FAMILY_IS_FULL,                  					//������������
	GUILD_CAPTION_OFFLINE,                  				//����������
	GUILD_NOT_FAMILYCAPTION_CANNOT_INVITE_JOIN,				//ֻ���峤�������������
	GUILD_NOT_FIND,                        					//�Ҳ����ð��
	GUILD_CANNOT_IMMEDIACY_FIRE_OFFICIAL,        			//����ֱ�ӿ�����Ա
	GUILD_ONLY_FIRE_FAMILY,                      			//ֻ�ܿ�������
	GUILD_NO_POWER,                              			//û��Ȩ��
	GUILD_CAPTION_NO_SET_CAPTION,							//�������������Լ���Ȩ��
	GUILD_ASSISTANT_NO_SET_CAPTION,                         //�������������ð�����Ȩ��
	GUILD_ASSISTANT_NO_SET_SELFPOWER,                       //���������������Լ���Ȩ��
	GUILD_MAP_FORBID_USE_FUNCTION,               			//�õ�ͼ��ֹʹ�ô˹���
	GUILD_PWD_ERROR,                             			//�������
	GUILD_POST_HAVE_MEMBER,									//ְλ���г�Ա����
	GUILD_ONLY_GUILDCAPTION_AND_AUXILIARY_SHOULDER,			//ֻ���峤�ͱ����帱�峤���ܵ���
	GUILD_CANNOT_REMOVE_AGAIN,                   			//�����ٴ��ƽ�
	GUILD_NOT_ACHIEVE_UPGRADE_PROSPERITY,        			//δ�ﵽ�������跱�ٶ�
	GUILD_GUILD_FUND_NOT_ENOUGH,                 			//����ʽ���
	GUILD_GUILD_CANNOT_LEARN_MORE_SKILL,         			//����ѧϰ�����Ἴ��
	GUILD_OFFER_NOT_ENOUGH,                      			//���׶Ȳ���
	GUILD_CREATE_SUCCESS,                                   //�������ɹ�
	GUILD_CREATE_FAILURE,                                   //�������ʧ��
	GUILD_NOT_IN_GANG,                                      //���ڰ����
	GUILD_NAME_AND_PASSWORD_CANNOT_NULL,                    //�������ֲ���Ϊ��
	GUILD_ADD_FAMILY_FAILD,									//�����Ӽ���ʧ��
	GUILD_ADD_FAILD,										//��Ӱ��ʧ��
	GUILD_CAPTION_SET_FAILD,								//���ð���ʧ��
	GUILD_HAS_IN_GUILD,										//�Ѿ�������
	GUILD_CANT_FIND,										//�Ҳ������
	GUILD_ADDMEMBER_POWER_ONLY_TO_CAPTION,                   //ֻ�а������ܼ��¼���
	GUILD_BEYOND_PASSWORD_LIMIT,							//�������ҪΪ��λ
	GUILD_PROP_FAMILY_DICHAN,								//��������û�еز�֤��
	GUILD_ADD_ACCEPT,										//��Ӽ���ɹ�
	GUILD_NOT_CAPTION_REASERCH_SKILL,						//���ǰ��������о���Ἴ��
	GUILD_GANG_LEVEL_NOT_SKILL,								//���ȼ����������о��˼���
	GUILD_SKILL_NOT_HAVE,									//�ü��ܲ�����
	GUILD_REASECHER_SKILL_ACCEPT,							//����о����ܳɹ�
	GUILD_REASECHER_SKILL_FAILD,							//����о�����ʧ��
	GUILD_LEARN_SKILL_ACCEPT,								//���ѧϰ���ܳɹ�
	GUILD_LEARN_SKILL_FAILD,								//���ѧϰ����ʧ��
	GUILD_LEAVE_SKILL_ACCEPT,								//����������ܳɹ�
	GUILD_LEAVE_SKILL_FAILD,								//�����������ʧ��
	GUILD_NOT_REASECHER,									//�õȼ����ܻ�δ�о�
	GUILD_NOT_CAPTION_UPDATE_LEAVE,							//���ǰ���û��Ȩ������
	GUILD_UPDATE_ACCEPT,									//�����ɹ�
	GUILD_UPDATE_FAILD,										//����ʧ��
	GUILD_PUBLIC_ERROR,										//���幫�治�Ϸ�
	GUILD_PUBLIC_ACCEPT,									//���ļ��幫��ɹ�
	GUILD_PUBLIC_FAILD,										//���ļ��幫��ʧ��
	GUILD_REMOVE_FAMILY_ACCEPT,								//�Ƴ�����ɹ�
	GUILD_REMOVE_FAMILY_FAILY,								//�Ƴ�����ʧ��
	GUILD_SET_POWER_ACCEPT,									//����Ȩ�޳ɹ�
	GUILD_SET_POWER_FAILY,									//����Ȩ��ʧ��
	GUILD_SET_MONEY_ACCEPT,									//��Ǯ�ɹ�
	GUILD_SET_MONEY_FAILY,									//��Ǯʧ��
	GUILD_APPLY_SCENE_ACCEPT,								//������ׯ԰�ɹ�
	GUILD_APPLY_SCENE_FAILY,								//������ׯ԰ʧ��
	GUILD_HAVE_SCENE,										//�Ѿ���������ׯ԰
	GUILD_NOT_APPLY_SCENE,									//ֻ�а�������Ȩ������ׯ԰
	GUILD_CAPTION_NOT_DISSFAMILY,							//���������ܽ�ɢ����
	GUILD_SUMMON_MEMBER_TIMES,								//ÿ��ֻ���ٻ����ΰ���
	GUILD_ASSISTANT_NO_REMOVE_OWNFAMILY,					//�������˳����ǰ�����ƽ�������ְλ
	GUILD_DISS_STATE,										//��ǰ�������ɢ����
	GUILD_WAIT_RECUIT_ACCEPT,								//�ȴ��Է���������
	GUILD_BE_DISMISSED,
	GUILD_APPOINT_ASSISTANT,

	//����
	STATE_BANKROLL_NOT_ENOUGH = 1200,						//�ʽ���
	STATE_MAP_CANNOT_USE_FUNCTION,                			//�˵�ͼ���ܸù���
	STATE_PLAYER_HAVE_POSITION,                   			//��������й�ְ
	STATE_BEYOND_WORD_LIMIT,                      			//������������
	STATE_BEYONG_TIME_LIMIT,                      			//������������
	STATE_ALREADY_DRAW_TODAY,                     			//�����Ѿ���ȡ��һ��
	STATE_LEAGUE_STATE_ALREADY,                         	//�Ѿ���ͬ�˹�
	STATE_NOT_LEAGUE_RELATION,                    			//����ͬ�˹�ϵ
	STATE_PERSON_IS_FULL,                         			//��������
	STATE_NOT_WAR_TIME_CANNOT_ENTER,              			//��ս��ʱ�䲻�ܽ���
	STATE_ERROR_SELECT_OWN_ADD_UNION,						//����ѡ���Լ���ͬ�˹�
	STATE_ERROR_SELECT_OWN_REMOVE_UNION,					//����ѡ���Լ��Ӵ�ͬ�˹�
	STATE_OWN_UNION_STATE_FULL,								//�Լ���ͬ�˹�����
	STATE_TARGET_UNION_STATE_FULL,							//�Է�ͬ�˹�����
	STATE_PLAYER_NOTONLINE,									//����Ҳ����߻��ǲ�����
	STATE_PLAYER_NOT_SAME_STATE,							//��������㲻��ͬһ������
	STATE_PLAYER_HAVE_NOSPEAK,								//����ҽ����Ѿ��������һ����
	STATE_PLAYER_HAVE_PRISONER,								//����ҽ����Ѿ�����ؽ�����һ����
	STATE_IS_KING_NOSPEAK,									//����������������30Сʱ
	STATE_IS_KING_PRISONER,									//�������������ؽ�����2��Сʱ
	STATE_KING_NOSPEAK,										//��ұ������Գɹ�
	STATE_KING_PRISONER,									//��ұ����ؽ������ɹ�
	STATE_TARGET_NOT_KING,									//�Է����Ҳ����ڹ��������ܽ���
	STATE_TARGET_KING_NOTONLINE,							//�Է����ҹ��������ߣ����ܽ���
	STATE_TARGET_STATE_NOT_OWN,								//�Է���ͬ�˹�����û�б����������Լʧ��
	STATE_OWN_STATE_NOT_TARGET,								//�Լ���ͬ�˹�����û�жԷ��������Լʧ��
	STATE_ADD_UNION_STATE_ACCPET,							//����˹��ɹ�
	STATE_REMOVE_UNION_STATE_FAIL,							//�Ƴ��˹��ɹ�
	STATE_CANT_FIND,										//�Ҳ�������
	STATE_NOT_KING,											//���ǹ���
	STATE_POWER_FULL,										//�����������ڵ��θ�ְλ�����Ƚ�����⣬�������µĹ�Ա��
	STATE_WAITING_APPOINT_ACCPET,							//�Ѿ�������������
	STATE_BE_PUSHTOPRISON,									//���ؽ�����
	STATE_PUSHTOPRISON_SUCCESS,
	STATE_FREEPRISONER_SUCCESS,
	STATE_KING_RULE_DOWN,
	STATE_BE_INBREAK,										//�����⵽���� add by zhangjianli 2012-2-28

	//����
	EVENT_EXCHANGE_REFUSE = 1300,							//�Է��ܾ�����
	EVENT_EXCHANGE_ADD_PROP_BIND,							//�󶨵��߲�������
	EVENT_EXCHANGE_ADD_PROP_FAILURE,						//��ӽ��׵���ʧ��
	EVENT_EXCHANGE_REMOVE_PROP_FAILURE,						//ɾ�����׵���ʧ��
	EVENT_EXCHANGE_FAILURE,									//����ʧ��
	EVENT_EXCHANGE_CANCEL,									//ȡ������
	EVENT_EXCHANGE_SUCCESS,									//���׳ɹ�
	EVENT_EXCHANGE_BUSY,									//�Է�����æ
	EVENT_EXCHANGE_COUNT_MAX,								//���ױ�������
	EVENT_EXCHANGE_NOT_EXPLORER,				    		//��Ҳ���ͬһ��Ļ�ڣ�
	EVENT_EXCHANGE_TARGET_UNALLOWEXCHANGE,					//�Է���������н���
	EVENT_EXCHANGE_SEND,                                    //����Է����ͽ�������
	EVENT_EXCHANGE_STALLSTAT_NOTEXCHANGE,                   //��̯״̬���ܽ��н���
	EVENT_EXCHANGE_TARGET_NOTEXCHANGE,                      //�Է���̯���ܽ��н���
	EVENT_EXCHANGE_NOT_STATE,                        		//������ͬ���Ҳ��ý���
	EVENT_EXCHANGE_SUCCESS_GETMONEY,                 		//���׹����л�õĽ�Ǯ��
	EVENT_EXCHANGE_SUCCESS_LOSTMONEY,                		//���׹�����ʧȥ�Ľ�Ǯ��
	EVENT_EXCHANGE_SILVER1,                                 //�Լ���Ǯ��������
	EVENT_EXCHANGE_SILVER2,                                 //�Է���Ǯ��������
	CANT_LILIANGONGXUN,                                     //������ѫ����
	EVENT_EXCHANGEING,                                      //�����в����M����������
	EVENT_CAN_NOT_EXCHANGE,                                 //�õ��߲��������֮�佻��
	CANT_LILIANGONGXUN_MAXNUM,								//���ܶһ������Ѵ��������

	//��������Ϣ
	SERVER_GAMESERVER_BREAK = 1400,							//gameserver���ӶϿ�
	SERVER_GAMESERVER_CONNECT,								//gameserver���ӳɹ�
	SERVER_COMMUNITYSERVER_BREAK,							//communityserver�����ն�
	SERVER_COMMUNITYSERVER_CONNECT,							//Communityser���ӳɹ�

	//����
	SKILL_NOT_ENOUGH_MP		=1500,							//Mp����
	SKILL_BEIN_COMMON_COOLDOWN,								//������ȴʱ��δ��
	SKILL_BEIN_SKILL_COOLDOWN,								//������ȴʱ��δ��
	SKILL_DISTACNE_TO_FAR,									//����Ŀ��̫Զ
	SKILL_NOT_TARGET_TYPE,									//����Ŀ����Ч
	SKILL_SELF_STATUS_RESTRICT_ERROR,						//����״̬���ƴ���
	SKILL_LEARN_NEED_BOOK,									//����ʹ�ü�����ѧϰ�ü���
	SKILL_LEARN_SUCCESS,									//����ѧϰ�ɹ����������������ɹ���
	SKILL_LEARN_USECOUNT,									//���������Ȳ���


	//������
	SKILLTREE_LEVEL_LIMIT	= 1600,							//ѧϰ��������ȼ�����
	SKILLTREE_PRESKILL_LIMIT,								//ѧϰ����ǰ�ü�������
	SKILLTREE_MUTEX_SKILL,									//���⼼��
	SKILLTREE_SYSTEM_SKILLPOINT,							//�������ĵ���Ҫ��
	SKILLTREE_NOT_SKILL_POINT,								//���ܵ㲻��
	SKILLTREE_MAX_LEARN_POINT,                              //�����Ѿ������ֵ��
	SKILLTREE_SKILL_LEARNED,                                //�����Ѿ�ѧϰ��
	SKILLTREE_SKILL_LEARN_FAILD,                            //����ѧϰʧ��
	SKILLTREE_CLASS_POINT_LIMIT,							//��ϵ���Ӽ��ܵ�������
	SKILLTREE_SKILL_NOT_SELF_CLASS,							//���ܲ������Լ���ְҵ
	SKILLTREE_SKILL_NOT_SELF_RAMIFY,						//���ܲ������Լ���ְҵ��֦
	SKILLTREE_LEARN_SKILL_USE_BOOK,							//�����˼�����Ҫ��Ӧ������
	SKILLTREE_LEARN_SKILL_STRIDE_LEVEL,						//���ܿ缶ѧϰ���� add by zhangjianli 2011-11-22





	//�ʼ�
	MAIL_DELETE_FAILURE  =1700,								//ɾ���ʼ�ʧ��
	MAIL_DELETE_SUCCESS,									//ɾ���ʼ��ɹ�
	MAIL_DELETE_PROP_FAILURE,								//�Ƴ�����ʧ��
	MAIL_DELETE_PROP_SUCCESS,								//�Ƴ����߳ɹ�
	MAIL_SEND_FAILURE,										//�����ʼ�ʧ��
	MAIL_SEND_SUCCESS,										//�����ʼ��ɹ�
	MAIL_GETPROP_FAILURE,									//��ȡ����ʧ��
	MAIL_GETPROP_SUCCESS,									//��ȡ���߳ɹ�
	MAIL_GETMONEY_FAILURE,									//��ȡ��Ǯʧ��
	MAIL_GETMONEY_SUCCESS,									//��ȡ��Ǯ�ɹ�
	MAIL_MONEY_OVER_OWNERMONEY,								//�ʼ��еĽ�Ǯ�������н�Ǯ
	MAIL_OVER_MAX_COUNT,									//���������ܽ����ʼ����������
	MAIL_MONEY_NOT_ENOUGH,									//�ʽ���
	MAIL_MONEY_NOT_ENOUGH_NOCANTIQU,						//�ʽ���,�޷���ȡ
	MAIL_OVER_MAX_ACCEPT_COUNT,								//�Է��Ѿ��ﵽ���ܽ��ܵ��������
	MAIL_BAG_ADD_MONEY,										//�õ���Ǯ
	MAIL_TITLE_OVER_MAXLENGTH,								//�ʼ����ⳬ����󳤶�����
	MAIL_CONTEXT_OVER_MAXLENGTH,							//�ʼ����ݳ�������󳤶�����
	MAIL_TITLE_CONTAIN_ILLEGAL_CHAR,						//�ʼ����⻹�зǷ��ַ�
	MAIL_CONTEXT_CONTAIN_ILLEGAL_CHAR,						//�ʼ����ݻ��зǷ��ַ�
	MAIL_CANT_FIND,											//�Ҳ����ʼ�
	MAIL_CANT_FIND_PROP,									//û���ҵ��ʼ��еĵ���
	MAIL_MONEY_LESS_ZERO,									//�ʼ��н�Ǯ��С��0
	MAIL_STRING_IS_NULL,									//�ַ���Ϊ��ָ��
	MAIL_ERROR_NOT_DELTE_PROP_MAIL,							//�ʼ����е��߻��߽�Ҳ���ɾ��
    MAIL_NOT_SAME_STATE,									//��ͬ���Ҳ��ܷ����ʼ�
    MAIL_NOBODY_SEND_FAILURE,                              //Ŀ�겻���ڷ����ʼ�ʧ��
	MAIL_GETMONEYFAILD,                                    //GetMailMoneyFaild:�ѳ�������Я���������
	MAIL_SEND_HIGHT_FREQUENCY,								//�����ʼ�̫��Ƶ��

	//����
	AUCTION_BID_SUCCESS = 1800,                             //���ĳɹ�
	AUCTION_MONEY_NOT_ENOUGH,                				//��Ǯ���㣬�޷���������̯��ԪҲ��ʹ�ã�
	AUCTION_BID_BEGIN,                       				//��ʼ����
	AUCTION_PROP_NOT_EXIST,                  				//��Ʒ������
	AUCITON_BID_BEYOND,                      				//���۱�����
	AUCTION_FAILURE,                         				//����ʧ��,���Ľ�Ǯ������֧�������
	AUCTION_PROP_OVERDUE,                    				//������Ʒ�ѹ�������
	AUCTION_CANCEL,                          				//������ȡ��
	AUCTION_SUCCESS,                         				//������Ʒ���۳�
	AUCTION_BAND_NOT_SALE,                   				//����Ʒ��������
	AUCTION_ADD_AUCTION_SUCCESS,							//���������Ϣ�ɹ�
	AUCTION_DELETE_AUCTION_SUCCESS,							//ɾ��������Ϣ�ɹ�
	AUCTION_CANNOT_BID_SELF_PROP,							//���ܾ����Լ����۵���Ʒ
	AUCTION_MUST_SET_BID,									//�����������ļ۸�
	AUCTION_BUYOUT_LOW_BID,									//һ�ڼ۵����˾���
	AUCTION_PRICE_LOW_BID,									//���ü۸���ھ����
	AUCTION_PRICE_LOW_HIGHEST_BID,							//���ü۸������߾���
	AUCTION_SELF_HIGHEST_PRICE,								//�Լ��Ѿ�����߾���
	AUCTION_SEND_SUCCESS_TO_OWNER,							//������Ʒ�Ѿ��ɹ�������
	AUCTION_MAKE_BID_SUCCESS,								//�ɹ����뾺�ĵ�ǰ��Ʒ
    AUCTION_NO_BID,                                         //��ǰ��Ʒû��һ�ڼۣ�����һ�ڼ۹���
	NOT_FIND_AUCTION_PROP,                                  //��������Ϣ�Ѳ�����
	NOCE_DOAUCTION_COUNT,                                   //һ�����ֻ�ܷ�100��������Ϣ

	//����ϳ�
	COMPOSE_SIGN_SUCCESS = 1900,
	COMPOSE_SIGN_FAILTURE,
	COMPOSE_BIND_SUCCESS,				//�󶨳ɹ�
	COMPOSE_BIND_FAILTURE,				//��ʧ��
	COMPOSE_REPEATBIND_SUCCESS,			//�ذ�ɹ�
	COMPOSE_REPEATBIND_FAILTURE,		//�ذ�ʧ��
	COMPOSE_REPEATBIND_MATLESS,			//���ϲ���
	COMPOSE_REPEATBIND_PROPSIGNBIND,	//װ����󶨲�ǩ��
	COMPOSE_STAR_SUCCESS,
	COMPOSE_STAR_FAILTURE,
	COMPOSE_UNSTAR_SUCCESS,				//���ǳɹ�
	COMPOSE_UNSTAR_FAILTURE,			//����ʧ��
	COMPOSE_UNSTAR_PROPNOTSTAR,			//����ʧ��,װ��������
	COMPOSE_UNSTAR_STARDOWN,			//����ʧ��, ����������½��ķ���ʯ

	COMPOSE_REPEATSTAR_SUCCESS,			//���ǳɹ�
	COMPOSE_REPEATSTAR_FAILTURE,		//����ʧ��
	COMPOSE_REPEATSTAR_EQUIPSTAR,		//����ʧ��,װ������,�Ȳ���
	COMPOSE_HOLE_SUCCESS,
	COMPOSE_HOLE_FAILTURE,
	COMPOSE_ENCHANSE_SUCCESS,			//��Ƕ��ʯ�ɹ�
	COMPOSE_ENCHANSE_FAILTURE,			//��Ƕ��ʯʧ��
	COMPOSE_UNENCHANSE_SUCCESS,			//�����ʯ�ɹ�
	COMPOSE_UNENCHANSE_FAILTURE,		//�����ʯʧ��
	COMPOSE_CHANGEZHANHUN_SUCCESS,		//�޸�ս��ɹ�
	COMPOSE_CHANGEZHANHUN_FAILTURE,		//�޸�ս��ʧ��
	COMPOSE_CREATE_PROP_SUCCESS,
	COMPOSE_LEVEL_PROP_SUCCESS,
	COMPOSE_QUALITY_PROP_SUCCESS,
	COMPOSE_ATTR_PROP_SUCCESS,
	COMPOSE_CREATE_PROP_FAILTURE,
	COMPOSE_LEVEL_PROP_FAILTURE,
	COMPOSE_QUALITY_PROP_FAILTURE,
	COMPOSE_ATTR_PROP_FAILTURE,
	COMPOSE_PROP_UNSIGNABLE,								//�õ��߲���ǩ��
	COMPOSE_PROP_UNADDSTAR,									//�õ��߲��ɼ���
	COMPOSE_PROP_UNADDHOLE,									//�õ��߲��ɴ��
	COMPOSE_PROP_UNENCHASE,									//�õ��߲�����Ƕ
	COMPOSE_PROP_UNUPGRADE,									//�õ��߲�������
	COMPOSE_PROP_SIGNED,									//�õ�����ǩ��
	COMPOSE_PROP_BINDED,									//�õ����Ѱ�
	COMPOSE_PROP_NOSIGNED,									//�õ���δǩ��
	COMPOSE_PROP_NOBINDED,									//�õ���δ��
	COMPOSE_PROP_SIGNEDBYME,								//�Ѿ����Լ���ǩ��
	COMPOSE_PROP_NOHOLE,									//û�ж����λ�ÿ�����Ƕ��ʯ
	COMPOSE_PROP_QUALITY_HIGHEST,							//�õ�����Ϊ���Ʒ��
	COMPOSE_MAT_TYPE,										//�������ʹ���
	COMPOSE_MAT_CLASS,										//���ϼ���δ���
	COMPOSE_MAT_ERROR,                                      //�밴˳����
	COMPOSE_MAT_LOW,                                        //��ͷ����̫��
	COMPOSE_MAT_OVERFULL,									//������������
	COMPOSE_MAT_LACK,										//������������
	COMPOSE_MAT_STAR,										//��ʹ�������Ƕ�Ӧλ�õĲ���
	COMPOSE_MAT_NEEDSAME,									//��ʹ����ͬ�Ĳ��Ͻ��кϳ�
	COMPOSE_MAT_FAIL_GEMED,									//��Ƕ����ʯ���޷��ڴ˴��
	COMPOSE_INVALID_PROP,									//��Ч�ĺϳɵ���
	COMPOSE_MATERIAL_IS_NOT_CHECK,							//���ϲ���
	COMPOSE_PROP_MARK_ZERO,									//���߷���Ϊ0
    COMPOSE_UPQUALITY_PROP_SUCCESS,							//װ�������ɹ� 4�� + 1 == 1��
	COMPOSE_UPQUALITY_PROP_FAILTURE,						//װ������ʧ�� 4�� + 1 == 1��
	COMPOSE_UPQUALITY_PROP_FAILTURE_LEVEL,					//װ������ʧ��,���ϵȼ�����
	COMPOSE_ENCHANTING_PROP_SUCCESS,						//�̶����ϵĺϳɳɹ�  5 + ��Ǯ == 1
	COMPOSE_ENCHANTING_PROP_FAILTURE,						//�̶����ϵĺϳ�ʧ��  5 + ��Ǯ == 1
	COMPOSE_PROP_LEVELLIMIT,								//װ�����ߵȼ�����
	COMPOSE_PROP_QUALIYLESS,								//װ��Ʒ�ʹ���
	COMPOSE_PROPMAT_QUALIYLESS,								//�ϳɲ���Ʒ�ʹ���
	COMPOSE_PROPMAT_PROP_NOTAGREE,							//�ϳɲ�����װ���ȼ�����
	COMPOSE_PROP_NOZHANHUN,									//װ�����߱�ս������
	COMPOSE_BAGSPACE_LESS,									//����ʧ��,����ʣ��ռ����
	COMPOSE_PROP_ADDSTARFULL,                                //���߼���������
	COMPOSE_PROP_ADDSTARFULLBANNERMSG,						//�������ǵĺ����Ϣ
	COMPOSE_PROP_MATERIAL_EQUIP_FAIL,						//������װ�����Ͳ���
	COMPOSE_PROP_ADDGEM_COLORREPEATE,						//��ʯ��Ƕ����ɫ�ظ�
	COMPOSE_PROP_ADDGEM_CURPOSNOADDGEM,						//��λ�����б�ʯ,�޷�������Ƕ
	COMPOSE_PROP_ADDGEM_ORDERBYERROR,						//��Ƕ��ʯ�밴˳����Ƕ
	COMPOSE_PROP_ADDGEM_HOLELEVELLOW,						//�޷����߼���ʯ��Ƕ�ڵͼ�����
	COMPOSE_PROP_REPEATEBIND_NOTPPERCENTATTR,				//װ����û�аٷֱ����� ����ʧ��

//---------
	COMPOSE_PROP_BIND_NEED_SOULJADE,						//����Ҫ���������
	COMPOSE_PROP_REPEATEBIND_EQUIPLEVELOVERTEN,				//���°󶨵�װ���������10��
	COMPOSE_PROP_REPEATEBIND_NEEDGOLDQUALITY,				//���°���Ҫ��ɫ����Ʒ��װ��
	COMPOSE_PROP_NEED_SILVERMATERIAL,						//��Ҫ������	--����
	COMPOSE_PROP_NEED_LEATHERMATERIAL,						//��Ҫ��Ƥ����	--����
	COMPOSE_PROP_REPEATEBIND_NEEDSILVER,					//����/����/��ָ/��Ʒ��Ҫʹ�ò��������а󶨻��޸�
	COMPOSE_PROP_REPEATEBIND_NEEDLEATHER,					//ͷ��/����/�·�/����/����/Ь��ʹ�ò���Ƥ���а󶨻��޸�
	COMPOSE_PROP_UNADDSTAR_EQUIPLEVELOVERTEN,				//ժ�ǵ�װ���������10��
	COMPOSE_PROP_UNADDSTAR_EQUIPQUALITY_OVERPURPLE,			//ժ�ǵ�װ��Ʒ�ʱ�������ɫ����ɫһ��
	COMPOSE_PROP_REPEATESTAR_EQUIPLEVEL_OVERTEN,			//���ǵ�װ���ȼ��������10��
	COMPOSE_PROP_REPEATESTAR_EQUIPQUALITY_OVERPURPLE,		//���ǵ�װ��Ʒ�ʱ�������ɫ����ɫһ��
	COMPOSE_PROP_REPEATESTAR_EQUIPLEVELNOTINSOULSTONELEVELRANGE, //���ǵ�װ�������ʯʹ�÷�Χ����
	COMPOSE_PROP_ADDHOLE_NEED_OPENSUNSTONE,					//����ʹ�ÿ���ʯ���д��
	COMPOSE_PROP_ADDHOLE_MUSTUSEHIGHTLEVEL_OPENSUNSTONE,	//ֻ��ʹ�ø��߼���Ŀ���ʯ�޸����п�
	COMPOSE_PROP_UNADDGEM_EQUIPLEVEL_OVERTEN,				//�����ʯ��װ���ȼ��������10��
	COMPOSE_PROP_ADDGEM_NEEDSOULROCK,						//��Ҫ�������ʯ������Ƕ
	COMPOSE_PROP_CHANGEZHANHUN_EQUIPLEVEL_OVERTEN,			//ս���޸�װ���ȼ��������10��
	COMPOSE_PROP_CHANGEZHANHUN_EQUIPQUALITY_OVERGOLD,		//ս���޸�װ��Ʒ���ǽ�ɫ���ɫ����
	COMPOSE_PROP_CHANGEZHANHUN_MATERIALLEVELLESSTHREE,		//ս���޸Ĳ��ϵȼ����Ϊ���Ȳ���

	COMPOSE_PROP_CHANGEFIVEELEMENT_EQUIPQUALITY_OVERGOLD,	//�����޸�װ��Ʒ�ʱ����ǽ�ɫ���ɫ����
	COMPOSE_PROP_NEEDTHREETOFIVE_MATERIALLEVEL,				//��Ҫ3~5�Ȳ���
	COMPOSE_PROP_NEEDFOURTOSIX_MATERIALLEVEL,				//��Ҫ4~6�Ȳ���

//---------
	//stall

	//PK�ͼ���
	PK_TYPE_WRONG  =2200,				//����ģʽ����
	PK_KILL_STATE_MAN,					//ɱ���������
	PK_SYSTEM_PUT_TO_PRISON,			//��ϵͳץ������
	PK_PLAYER_PUT_TO_PRISON,			//�����ץ������
	PK_PRISON_TIME_IS_NOT_OVER,			//����ʱ��δ��

	PK_STATUS_CHANGE_HERO,				//��ǰΪӢ��״̬
	PK_STATUS_CHANGE_WELLDOER,			//��ǰΪ����״̬
	PK_STATUS_CHANGE_ORDINARY,			//��ǰΪ��ͨ״̬
	PK_STATUS_CHANGE_BADDIE,			//��ǰΪ����״̬
	PK_STATUS_CHANGE_DEMON,				//��ǰΪ��ħ״̬
	PK_STATUS_CHANGE_DEMON_HEAD,		//��ǰΪħͷ״̬
	PK_STATUS_CHANGE_MALICIOUS,			//��ǰΪ���⹥��״̬
	PK_STATUS_CHANGE_CHANGE,			//��ǰΪ�����ָ���ͨ״̬

	PK_KILLER_IS_OFFLINE,				//�׷�������
	PK_KILLER_IS_INPRISON,				//�׷����ڼ���
	PK_KILLER_CATCH_SUCCESS,			//�׷��ɹ�ץ��
	PK_ENEMY_WRONG,						//���ǵ���
	PK_NOT_STATE_KILL,					//������ǵй���ң�����������ް취����׽�ù鰸��
	PK_REDNAME_NOT_CATCH,				//��������ץ���׷�

	PK_TYPE_CHANGE_ALL,					//�л�Ϊȫ��ģʽ
	PK_TYPE_CHANGE_PEACE,				//�л�Ϊ��ƽģʽ
	PK_TYPE_CHANGE_STATE,				//�л�Ϊ����ģʽ
	PK_TYPE_CHANGE_UNION,				//�л�Ϊ�˹�ģʽ
	PK_TYPE_CHANGE_GANG,				//�л�Ϊ���ģʽ
	PK_TYPE_CHANGE_FAMIY,				//�л�Ϊ����ģʽ
	PK_TYPE_CHANGE_EVIL,				//�л�Ϊ�ƶ�ģʽ
	PK_TYPE_CHANGE_ENEMY,				//�л�Ϊ����ģʽ
	PK_TYPE_CHANGE_CAMP,				//�л�Ϊ��Ӫģʽ

	//��̯
	STALL_NOT_REGIONAL	= 2300,
	STALL_PROP_BINDED,					//�����Ѱ󶨣����ܳ���
	STALL_PROP_NOPRICE,					//�����õ��ߵĳ��ۼ۸�
	STALL_UIPOS_NOEMPTY,				//��λ�����е���
	STALL_PROP_NUM_NOENOUGH,			//������������
	STALL_PROP_SALE,
	STALL_PROP_SUCCESS,                 //���������ɹ�
	STALL_PROP_FAIL_SALED,				//�����ѱ�����,����ʧ��
    STALL_PROP_FAIL,                    //���ڹ����в����԰�̯
	STALL_PROP_RID_FAIL,                //����״̬�²����԰�̯
	STALL_FAIL_EXCHANGE,				//����״̬���ɰ�̯
	STALL_FAIL_CHANGEMODEL,				//����״̬���ɰ�̯
	STALL_FAIL_DEAD,					//����״̬���ɰ�̯
	STALL_FAIL_NUMNOTENOUGH,			//������������
	STALL_FAIL_LEAVEMESSAGE_FAIL_ONE,		//���Ѿ�����һ�����ˣ������ظ�����
	STALL_FAIL_SILVER_NOTENOUGH,			//���Ӳ��㣬�޷�����
	STALL_FAIL_SELLNUMZERO,					//��̯λ����Ϊ��
	STALL_FAIL_STATUS_FAMILYONCAR,          //�ٻ�����ս���в��ɰ�̯
	STALL_ADD_STALLPROP_FALID,              //��Ӱ�̯��Ϣʧ�� �õ������ڰ�̯�б���
	STALL_IS_SUPERADDFLAG,									//�Բ���,��̯λ����׷����,���Ժ��ٹ���
	STALL_CANT_LEAVEMESSAGE,								//��̯λ����̯,�������������Ϣ
	//����
	PROP_LEVEL_NOT_REACH = 2400,		//�ȼ����㣬�޷�ʹ�øõ���
	PROP_LEVEL_OVERTOP,					//�ȼ����ߣ��޷�ʹ�øõ���
	PROP_NEED_TWO_HANDS,				//����Ҫ��ֻ�������������
	PROP_LEFT_NO_HANDS,					//��û�ж�������������װ��
	PROP_DURABILITY_IS_ZERO,            //����ĥ���Ϊ0
	PROP_HAS_BIND,                      //�Ѿ�����
	PROP_NOT_SAME_STATE_AND_NEUTRAL_CANNOT_USE,	//ֻ���ڱ�������������ʹ��
	PROP_ADD_FAILD,                     //�������ʧ��
	PROP_BIND_FAILD,                    //��ʧ��
	PROP_SPLIT_FAILD,                   //���ʧ��
	PROP_SPLIT_NUM_WRONG,               //�����������
	PROP_COMBINE_FAILD,                 //�ϲ�����ʧ��
	PROP_NOT_STACKABLE,                 //���ǿɶѵ�����
	PROP_NOT_SAME_PROP_CANT_COMBINE,    //��ͬ���߲��ܶѵ�
	PROP_COMBINE_MAX_LIMIT,             //�������ѵ�����
	PROP_DROP_PROTECT,                  //���ߵ��䱣��
	PROP_EQUIP_PROP_CANT_USE_UNEQUIP,   //װ�����͵��߲����ڷ�װ����ʹ��
	PROP_USE_FAILD,                     //����ʹ��ʧ��
	PROP_ADD_EFFECT_FAILD,				//���߼�Ч��ʧ��
	PROP_CD_NOT_REACH,					//װ������ʱ��δ��
	PROP_CANNOT_DESTROY,				//���߲��ܱ�����
	PROP_CANNOT_SALE,					//���߲��ܱ�����
	PROP_MAN_USE,						//ֻ��������ҿ���ʹ��
	PROP_FEMAN_USE,						//ֻ��Ů����ҿ���ʹ��
	PROP_CANNOT_USE_ONSTALL,			//�������ڰ�̯״̬
	PROP_CANNOT_USE_ONDEAD,				//������������״̬
	PROP_CANNOT_USE_ONGHOST,			//�����������״̬
	PROP_SALE_SUCCESS_USESILVER,         //��������npc �ɹ� ��δ�󶨵�����
    PROP_SALE_SUCCESS_USEBINDSILVER,    //��������npc �ɹ����ð󶨵�����
	PROP_BUY_SUCCESS,                    //����߳ɹ�
	PROP_BIND_TYPE_ERROR,                //���߰����Ͳ�ͬ�������Զѵ�
	PROP_QUALITY_ERROR,                  //����Ʒ�ʲ�ͬ�����ɶѵ�
	PROP_ADD_TO_BAG,                     //��ӵ��߳ɹ�
	PROP_REPAIR_SUCCESS, 				 //��������ɹ�
	PROP_REPAIR_ONEFAILE,				//�˵��߲���Ҫ�޸�
	PROP_REPAIR_ONECOSTM,				//�������������Ǯ
	PROP_LIMIT_OWN_COUNTRY_USE,			//�˵�������ֻ���ڱ���ʹ��
	PROP_LIMIT_NOCAN_FLY_THISMAP,		//��ǰ��ͼ�޷�ʹ�ô��͹���
	PROP_NOT_EQUIPABLE, 				//�˵��߲���װ��
	PROP_NOT_EQUIPMENT, 				//�˵��߲���װ��
	PROP_CANNOT_INSERT_ACTBAR,			//��ǰ��Ʒ����ʹ�ã����������ݼ���
	PROP_USECOUNT_FULL,					//����ʹ�ô�������
	PROP_ADD_FELLOW_EXP,					//ʹ�����޾��鵤�ɹ�
	PROP_UNABLE_TOPICK,					//����Ȩʰȡ�˵���
	PROP_ADD_FELLOW_EXP_OVERFLOW,	 //�������
	PROP_USEAFTER_SENDSYSTEMMSG,		//����ʹ�ú���ϵͳ��Ϣ
	PROP_CANNOT_USE_ONCHANGEMODEL,		//�������ڱ���״̬
	PROP_MOVE_CANNOTDRAG,					//���ߴ����ƶ�״̬������ק
	PROP_CANNOT_USE_THIS_TARGET,			//�����޷��Ը�Ŀ��ʹ��
	PROP_CANNOT_USE_IN_FAMILYCAR,			//�����޷���ս����ʹ��
	PROP_NOT_INBAGBAG,					    //�õ����ڴ����������ʹ��
	PROP_NOTSELL_INBAGBAG,					//�õ��߲�������������ܳ���
	PROP_NO_PUT_ACTIVE_BAR,					// �õ��߲������������
	PROP_NO_INBAGBAG_NO_ACTIVE_BAR,			// �õ��߲��ڱ����ﲻ�ܷ�������
	PROP_ALREADY_IN_ACTIVE_BAR,				// �õ����Ѿ��ڿ����  
	PROP_CANNOT_USE_ENERGY_NO_ACTIVE,		//����δ�������ֵ���޷�ʹ�ô���Ʒ
	PROP_USE_ADD_ENERGY_SUCCESS,			//��ʹ����һ�����������ָ�15�������
	PROP_CANNOT_USE_ENERGY_IS_MAX,			//����ֵ��������Ʒ����ʹ��
	PROP_OBSERVER_IS_DESTORY,				//��ǰ�۲���Ʒ������
	PROP_CANNOT_USE_ONCOMBINPET,			//���ڱ���״̬������ʹ�õ���

	//����ʹ��
	SKILL_NOT_USE = 2500,				//���ܲ���ʹ��
	SKILL_MAGIC_CUT,					//����ħ
	SKILL_MP_NOT_ENOUGH,				//����ֵ����
	SKILL_COMMON_CD,					//������ȴʱ��δ��
	SKILL_CD,							//��ȴʱ��δ��
	SKILL_NOT_TARGET_ZONE,				//���Ǽ���ָ������
	SKILL_NOT_WEAPON,					//û���ͷż��ܵ�����
	SKILL_NOT_WAITERPET,				//�̴Ӳ��ܱ�����
	SKILL_NOT_BEATABLE,					//�޵�״̬���ܱ�����
	SKILL_NOT_TARGET,					//Ŀ�겻��ȷ
	//SKILL_NOT_EP,						//û�о���ֵ
	SKILL_NOT_SP,						//ŭ��ֵ����
	SKILL_DEAD_CANT_USE,                //��������ʹ�ü���
	SKILL_NOT_LEARN,                    //����û��ѧϰ������ʹ��
	SKILL_PROP_NOT_ENOUGH,              //��������ĵ��߲��㹻
	SKILL_PROP_TYPE_NOT_MATCH,          //���������������Ͳ�ƥ��
	SKILL_NOT_USE_MAGIC,                //����ħ
	SKILL_NOT_SUIT_NPC_ZONE,            //Ŀ��������ȷ
	SKILL_NOT_USE_TO_DEADMAN,           //���ܶ�����״̬����ʹ��
	SKILL_NOT_USE_TO_GHOSTMAN,          //���ܶ����״̬����ʹ��
	SKILL_NOT_USE_TO_INVULNERABILITY,   //���ܶ��޵�״̬����ʹ��
	SKILL_TARGET_TYPE_WRONG,            //Ŀ�����Ͳ���ȷ
	SKILL_ADD_WRONG,                    //��Ӽ���ʧ��
	OPEN_CTRLZ,							//�����һ�
	CLOSE_CTRLZ,						//�رչһ�
	SKILL_STATUS_NOT_USE,				//��״̬����ʹ��
	SKILL_STATUS_RIDE,                   //״̬����˼��ܲ���ʹ��
	SKILL_LOGICSTATUS_INGAME,            //״̬��С��Ϸ���ܲ���ʹ��
	SKILL_NOT_IN_RIDE,                   //�μ��ܲ��������״̬ʹ��
	SKILL_NOT_IN_CAR,                   //�μ��ܲ�����ս��״̬ʹ��
	SKILL_NOT_IN_COMBINEPET,             //�μ��ܲ�����վ�����״̬ʹ��
	SKILL_NOT_IN_STALL,                   //�μ��ܲ����԰�̯״̬ʱ����
	SKILL_PROP_TYPE_NOT_ASSISTANT_MATCH,	//�������踱���������Ͳ�ƥ��
	SKILL_PROP_CD,							//���߼���δ��ȴ
	SKILL_SINGING_BREAK,					//�������ܱ����	by zhaoguoze
	OPEN_AUTO_OPRATING,							// ��������ϵͳ
	CLOSE_AUTO_OPRATING,						// �رո���ϵͳ
	AUTO_ATTACK_BY_POS_CAN_NOT_MOVE,			// �������У��޷������ƶ�����
	OPEN_AUTO_PICK,								// �����Զ�ʰȡ
	CLOSE_AUTO_PICK,							// �ر��Զ�ʰȡ
	SKILL_NOT_COMBINEPET,						// û��ս�裬����ʹ��
	SKILL_NOT_FELLOWPET,						// û�����ޣ�����ʹ��
	ATTACK_IN_SECURE_REGION,					// ��ȫ���ڲ��ܹ���
	ATTACK_CAN_NOT_ATTACK_CHILD,				// ���ܹ����ܱ�����С�����
	SKILL_OBJ_DISTANCE_OUT,						// Ŀ������Զ
	SKILL_NOT_IN_SCENE,						// �����ڱ���ͼʹ��
	SKILL_USE_EP,								// ���ĵĻ���ֵ add by zhangjianli  2011-11-30
	ATTACK_LEVEL_CAN_NOT_ATTACK,				// С����Ҳ��ܽ���PK add by zhangjianli 2012-02-01
	OPEN_AUTO_PICK_FAIL,						// ���״̬�޷��Զ��ɼ� add by zhangjianli 2012-2-23
	SKILL_NO_COMBAT_CAN_NOT_USE,				// û��ս���޷�ʩ�ţ���ʿ���򷨺�һ���ܣ�add by zhangjianli 2012-3-9
	SKILL_CAN_NOT_USE_THIS_RANGE,				// �������޷�ʹ�� add by zhangjianli 2012-3-27
	NO_ATTACK_HOMELAND_AREA,					// ���ܹ����������ڵĸù����
	CANT_ATTACK_PROTECTED_CAR,					// ���ڳ����ڱ���״̬���޷������������������ڳ���50�������µ��ܱ�����
	SKILL_CANT_USE_NO_TEAM,						// �޶��鲻��ʹ�øü��� add by zhangjianli 2012-6-9
	SKILL_CAN_USE_IN_MYSELFSTATE,				// ����ֻ���ڱ���ʹ�� add by zhangjianli 2012-6-9

	SKILL_LIFE_STOP=2560,               //����ܱ���ϣ�κС����ӣ����0000106����
	OPEN_CTRLC=2590,					//crtl+c��ʼ



	//����
	CHAT_NO_LONG = 2600,				//�������ݹ���
	CHAT_NO_KONG,						//�������ݲ���Ϊ��
	CHAT_NO_SELECT_PLAYER,				//û��ѡ���������
	CHAT_NO_WORLD_MESSAGE,				//������ʮ������������Ƶ������
	CHAT_NO_TEAM_MESSAGE,				//û����ӣ����������Ƶ������
	CHAT_NO_FAMILY_MESSAGE,				//û�м��壬�����ټ���Ƶ������
	CHAT_NO_GANG_MESSAGE,				//û�а�ᣬ�����ڰ��Ƶ������
	CHAT_NO_FRIEND_MESSAGE,			//û�к��ѣ������ں���Ƶ������
	CHAT_NO_STATE_MESSAGE,				//�ȼ�����30���������ٹ���Ƶ������
	CHAT_AREA_LEVEL_MESSAGE,			//��������ȼ�����
	CHAT_NO_TIME,						//���������Ƶ��
	CHAT_GROUP_NAME_NO_LONG,			//����Ⱥ���ֹ���
	CHAT_GROUP_NAME_NO_KONG,			//����Ⱥ���ֲ���Ϊ��
	CHAT_GROUP_NAME_CONTAIN_ILLEGAL_CHAR,//����Ⱥ���ư����Ƿ��ַ�
	CHAT_GROUP_NAME_HAVE,				 //����Ⱥ�����Ѵ���
	CHAT_GROUP_CREATE_FAILURE,			 //����Ⱥ����ʧ��
	CHAT_GROUP_ADD_MEMBER_FAILURE,		 //��ӳ�Աʧ��
	CHAT_GROUP_CREATE_ACCEPT,			 //����Ⱥ�ɹ�
	CHAT_GROUP_BE_ADD_ACCEPT,			 //����ӳɹ�
	CHAT_GROUP_JOIN_HAVE_GROUP,			 //���Ѿ��ڴ�Ⱥ��
	CHAT_GROUP_ISFULL,					 //������Ⱥ��������
	CHAT_GROUP_CAPTION_NO_ONLINE,		 //Ⱥ��������
	CHAT_GROUP_JOIN_DENY,				 //���󱻾ܾ�
	CHAT_GROUP_NOT_CAPTION,				 //������Ⱥ��
	CHAT_GROUP_HAVE_GROUP,				 //���Ѿ�������һ��Ⱥ��
	CHAT_GROUP_HAVE_GROUP_MAX,			 //ÿ���������Լ������Ⱥ
	CHAT_GROUP_TARGET_GROUP_MAX,		 //�Է��Ѿ������Ⱥ��
	CHAT_NO_COLORWORLD_MESSAGE,          //�ȼ�������ʮ���������ڲ���Ƶ������
	CHAT_BE_SET_NOSPEAK,				 //�����ý���

	//�Ʋ�����
	PROPERTY_PROTECT_APPLY_SUCCESS = 2700,	//����Ʋ������ɹ�
	PROPERTY_PROTECT,                       //�Ʋ�������ʾ��Ϣ

	//�����
	ACTIVE_BAR_PASSIVESKILL_NOT_DRAG=2800,  //�������ܲ����϶�
	ACTIVE_BAR_TYPE_WRONG,					//�϶����ʹ���
	ACTIVE_BAR_REPLACE_WRONG,				//ԭ�п��������
	ACTIVE_BAR_NO_RROPORSKILL_NOREPALCE,	//�ǵ��ߺͼ��ܲ����滻
	ACTIVE_BAR_NO_PROP_SHORCUT,				//���ǵ��߿��ͼ��
	ACTIVE_BAR_NO_HAVE_SKILL,               //û�иü���
	ACTIVE_BAR_REMOVE_WRONG,                //�Ƴ�����

	//�������
	ATTRIB_POINT_ZERO               =2900,	//���Ե�������
	ATTRIB_POINT_NOT_ENOUGH,                //û�����Ե�ɷ���
	ATTRIB_POINT_NOT_ADD,                   //û�з������Ե�
	ATTRIB_POINT_NOT_ZERO,                  //�������Ե㲻��Ϊ0
	ATTRIB_POINT_NOT_SO_MUCH,               //û����ô�����Ե�ɷ���


	//����
	PET_INVITE_RID_TARGET_NOT_COM   =3000,  //��ǰ���״̬������ͨ״̬
	PET_NOT_EXIST,                          //�Ҳ�������
	PET_CANT_COMBINE,                       //���ܺ���
	PET_COMBINE_TARGET_NOT_EXIST,           //����Ŀ�겻����
	PET_MASTER_TEMPLATE_NOT,                //����ģ���Ҳ���
	PET_NOT_RID,							//��ǰ״̬�����ϳ���
	PET_COMBIN_DISTANCE_OUT,				//��������������
	PET_TILI_LOW,							//����ֵ����40�㲻�����
	PET_FELLOW_MAX_COUNT,	//���������ﵽ����
	PET_FELLOW_SUMMON,		//�������ٻ�
	PET_FELLOW_FIGHTING,		//�������ڳ�ս
	PET_FELLOW_FULLSTAR,		// ���޲�����ǿ����(��������)
	PET_FELLOW_GOLD_NO_ENOUGH, //��Ҳ���
	PET_FELLOW_LIFE_NO_ENOUGH,//��������
	PET_FELLOW_LIFE_MAX,//�����ﵽ����
	PET_FELLOW_SEAL, //�����ѷ�ӡ
	PET_FELLOW_RELEASE,//�����ѷ���
	PET_FELLOW_CALLBACK, //�������ջ�
	PET_FELLOW_HAPPY_LOW, //���ֶȵ���20%���޷���ս
	PET_FELLOW_BREEDERR_LEVEL, //�ȼ����������ɷ�ֳ
	PET_FELLOW_BREEDERR_SEX, //�Ա�ͬ�����ɷ�ֳ
	PET_FELLOW_BREEDERR_GROWTH, //�������ޣ����ɷ�ֳ
	PET_FELLOW_BREEDERR_LIFE, //����̫�ͣ����ɷ�ֳ
	PET_FELLOW_EVOLUTION_SUCCEED, //ǿ���ɹ�
	PET_FELLOW_EVOLUTION_FAILED, //ǿ��ʧ��
	PET_FELLOW_EVOLUTION_NOGEM, //����ұ�����û�ҵ�ǿ���õı�ʯ
	PET_FELLOW_FEED_LEVEL_LOW,	//ι���ĵ��ߵȼ�̫��
	PET_FELLOW_FEED_HAPPY_FULL,	//��ǰ���ֶ���������Ҫι��
	PET_FELLOW_BREED_TYPE_DIFF, //�������Ͳ�ͬ����ͬ��ֳ
	PET_FELLOW_EVOLUTION_GEMNUM_ZERO, //��ʯ����Ϊ0
	PET_FELLOW_LESSTHAN_TAKELEVEL, //С�ڿ�Я���ȼ�
	PET_FELLOW_EGG_LESS_TAKELEVEL, //ʹ�õ�ʱ��С��Я���ȼ�
	PET_FELLOW_MASTER_LESS_FELLOWLEVEL, //�ٻ�ʱ�����˵ȼ�С�����޵ȼ�
	PET_FELLOW_NO_QUEST, //û������
	PET_FELLOW_HAVE_QUEST, //������
	PET_FELLOW_LEVEL_ERROR,//�������˵ȼ�����
	PET_FELLOW_QUEST_COUNT,//�������˽��ջ��ڴ�������4
	PET_FELLOW_STATE_ERROR,//�����������ڴ������ڻ���״̬�������ٱ�����
	PET_FELLOW_REFUSEAPPLY, //�ܾ������ڶӵ�����
	PET_FELLOW_REFUSEINVITE, //�ܾ������ڶӵ�����
	PET_CAR_STATEID_ERROR,	// ����ID����ͬ
	PET_CAR_PLAYER_PRISON,	//��Ҵ�������״̬��������������ڶ�
	PET_CAR_PASS_STEP_ONE,	 //�ڳ��ѹ���һ�׶�
	PET_CAR_WAIT_APPLY,//�ȴ�XXX�����������
	PET_CAR_WAIT_INVITE,//������XXX�����ڶ�
	PET_CAR_DELETE_QUEST,//�Ҳ����ڳ���ɾ������
	PET_CAR_NO_FLY,//������/�������񣬲��ܴ���
	PET_CAR_EXIT_CARLIST, //�˳��ڶ�
	PET_CAR_PLAYER_NO_FLY,//�������ڻ��ڣ����ܴ���
	PET_CAR_DISCARD_QUEST_MAIN, //������������
	PET_CAR_DISCARD_QUEST_AUXI, //������������
	PET_CAR_ENTER_TEAM, //�����ڶ�
	PET_FELLOW_KICKPLAYER, //��XXX�߳��ڶ�
	PET_FELLOW_REMIND_OVER, //������Ϣ�ɹ�
	PET_CAR_ADD_FRIENDPOINT, //���Ӻ��Ѷ�10��
	PET_CAR_QUEST_FAILED,
	PET_CAR_REPEAT_INVITE, //�ظ�����
	PET_RIDE_NO_EXIST,	//��ǰû�����
	PET_RIDE_DISMOUNT, //���������ǿ��
	PET_RIDE_GEM_ERROR, //ǿ����ʯ����ȷ
	PET_RIDE_LEVEL_LOW, //�ͼ������滻�߼���
	PET_RIDE_LEVEL_EQUAL, //ͬ�ȼ������滻
	PET_RIDE_STATE_RID, //���״̬������������
	PET_RIDE_SCENE_NO_ALLOW,	//��ǰ��������������
	PET_CAR_BEINVITERPLAYER_OFFLINE,	// ���������Ҳ�����
	PET_COMBAT_ONDEAD, //ս������
	PET_REFINERY_MAXNUM,				//һ��ֻ������10ֻ����


	//Ч��
	EFFECT_CURSOR_READY_USE_PROP=3100,      //�Ѿ�����ʹ�õ���״̬
	EFFECT_CURSOR_READY_POETAL,				//����Ѿ���
	EFFECT_TYPE_IS_CANT_CANCAL,				//buffΪ�����Ƴ�Ч��

	//��Ʊ
	CLEARING_ADD_SUCCESS=3200,				//��ӹ�Ʊ��Ϣ�ɹ�
	CLEARING_HAVE_GOLD_NOT_ENOUGH,			//�˻����Ӳ���
	CLEARING_HAVE_SILVER_NOT_ENOUGH,		//�˻����Ӳ���
	CLEARING_HAVE_NOTFIT_SELL,				//û�з�������������
	CLEARING_HAVE_NOTFIT_BUY,				//û�з�����������
	CLEARING_BUY_SILVER_NOT_ENOUGH,			//�˻���û���㹻�����ӹ���������Ľ���, ���ֵ
	CLEARING_NOT_BUY_ENOUGH,				//û����, ϵͳΪʣ�������Ĺ�������������
	CLEARING_BUY_SUCCESS,					//�Ѿ�����ɹ�
	CLEARING_BUY_GOLD_NOT_ENOUGH,			//�˻���ӵ�еĽ��Ӳ����������򵥵���Ҫ, ���ֵ
	CLEARING_NOT_SELL_ENOUGH,				//û������, ϵͳΪʣ������������������������
	CLEARING_SELL_SUCCESS,					//�����ɹ�
	CLEARING_DELETE_SUCCESS,				//�����ɹ�
	CLEARING_SOLD_OUT,						//���������ɹ�
	CLEARING_BUY_GET,						//�������ɹ�

	//����
	SCENE_UNGROUND_TEAM = 3300,				//����������У��޷�����˸���
	SCENE_UNGROUND_FAMILY,					//�����ڼ����У��޷�����˸���
	SCENE_UNGROUND_GANG,					//�����ڰ���У��޷�����˸���
	SCENE_CAN_NOT_DEPART_PRISON,			//�޷��뿪����

	//�ʻ�
	ROSE_NOT_NUMBER,						//�ʻ��������㣬����ʧ��
	ROSE_NOT_FAIL,							//�ʻ�����ʧ��
	ROSE_SUCCESS,							//�ʻ����ͳɹ�
	ROSE_BANNER,							//�ʻ����
	ROSE_NOT_QIANZHIHE,						//ǧֽ����������
	ROSE_SEND_ONLYMAN,						//ֻ������ҿ�������õ��
	ROSE_SEND_ONLYWOMAN,					//ֻ��Ů��ҿ�������ǧֽ��
	ROSE_SEND_FAIL_FORBID_TIME,				//ÿ��23:55-00:05�޷������ʻ�
	QIANZHIHE_SEND_FAIL_FORBID_TIME,		//ÿ��23:55-00:05�޷�����ǧֽ��

	//����
	FLY_LEVEL_LIMIT = 3500,					//�ȼ�����
	SUMMON_ACCEPTFAIL_DEAD,					//����ʱ������Ӧ�ٻ�
	SUMMON_ACCEPTFAIL_PRISON,				//�����в�����Ӧ�ٻ�
	SUMMON_ACCEPTFAIL_INCAR,				//ս���в�����Ӧ�ٻ�
	SUMMON_ACCEPTFAIL_MAPLEVEL,				//�������ͼ�ȼ�
	SUMMON_ACCEPTFAIL_ESCORT,				//����״̬������Ӧ�ٻ�
	SUMMON_ACCEPTFAIL_INVALID,				//�ٻ���ʧЧ
	SUMMON_ACCEPTFAIL_TOSOON,				//����Ƶ������
	SUMMON_ACCEPTFAIL_SCENENOACCEPT,		//��ǰ�������ɽ����ٻ�
	SUMMON_SEND_SUCCESS,					//�ٻ����ͳɹ�
	SUMMON_ACCEPTFAIL_STALL,				//��̯״̬����Ӧ�ٻ�	add by zhangjianli 2012-2-23
	FLY_FAMILYCAR_NO_FLY,					//��ս���в��ܴ���
	FLY_LEVEL_CAR_MEMBER_LIMIT,				//ս�����г�Ա�ȼ�����

    // ����
    SYSTEM_WUXING_JIN = 3900,                //ϵͳ��ʾ��ȡ������
    SYSTEM_WUXING_MU,                       //ϵͳ��ʾ��ȡľ����
    SYSTEM_WUXING_SHUI,                     //ϵͳ��ʾ��ȡˮ����
    SYSTEM_WUXING_HUO,                      //ϵͳ��ʾ��ȡ������
    SYSTEM_WUXING_TU,                       //ϵͳ��ʾ��ȡ������

	//�
	CAMPAIGN_COUT_OUT=4000,					//���������
	CAMPAIGN_SIGNUP_SUCCESS,				//������ɹ�
	CAMPAIGN_SIGNUP_ALREADY,				//�Ѿ�����
	CAMPAIGN_BAGFULL_SENDBYMAIL,			//��������������ͨ���ʼ�����

	//����
	EXPERIENCE_NOT_ENOUGH = 4500,			//���鲻��
	EXPERIENCE_STORE_ISFULL,				//�洢��������

	//Ԫ��ֵ
	PNEUMA_NOT_ENOUGH = 4550,				//Ԫ��ֵ����

	ERROR_FACE_INCAR=4600,						//ս��״̬�²�����������������ϵͳ��Ϣ
	SPACE_DATA_SAVE,							//�ռ�ҳǩ��������Ϻ���ϵͳ��Ϣ

	//��������
	ERROR_OTHER_EXP_IS_ZERO =10000,          //NPC����ֵΪ0
	ERROR_OTHER_NPC_MAXLIFE_LESSZERO,        //NPC����ֵС��0
	ERROR_OTHER_BAG_UIPOS_WRONG,             //����UIλ�ô���
	ERROR_OTHER_MONEY_CHANGE_WRONG,         //���ý�Ǯʧ��
	ERROR_OTHER_BIND_MONEY_FULL,			//�󶨵Ľ�Ǯ�ѵ�����
	ERROR_OTHER_NOTBIND_MONEY_FULL,			//���󶨵Ľ�Ǯ�ѵ�����
	ERROR_OTHER_CANT_GET_SCENE,              //�ò�������
	ERROR_OTHER_PID_IS_WRONG,                //ϵͳ����PID��һ��
	ERROR_OTHER_BIRTH_ZONE_CANT_FIND,		 //�Ҳ���������
	ERROR_OTHER_COMPOSE_CHANCE_ZERO,		 //�ϳɼ���Ϊ0
	ERROR_GIFT_NOT_TIME,					 //δ����ȡ���ʱ��
	ERROR_CAMPAIGN_BAGISFULL,				 //���������
	ERROR_GIFT_TAKE_SUCCESS,				//��ȡ����ɹ�
	ERROR_GIFT_TAKE_RESET,					//���������
	ERROR_BIND_MONEY_ENOUGH,				//�󶨽�Ǯ����
	ERROR_NOTBIND_MONEY_ENOUGH,				//�ǰ�Ǯ����
	ERROR_UNSEEEQUIP,						//�Է�������鿴װ��
	ERROR_YEARWINE_OPEN,					//�ѿ���������� (���ű�����) by zlm  2012.8.16
	ERROR_CDKEY_CONVERT_ONLYONE,			// �һ���ֻ�ܶһ�һ��
	ERROR_EVERYDAY_SELLMONEY_LIMITUP,		//�ﵽÿ�������������

	//debug
	SCRIPT_LOAD_FAILED = 11000,				 //���ؽű�ʧ��
	SCRIPT_DEBUG_STR,						 //�ű������ַ���
	//ͨ������
	ERROR_COMMON_STRING = 12000,

	//GM
	ERROR_GM_STRING = 13000,                // GM ����
	//Ԫ�����
	ERROR_DiHunLevel_UpTo_MingHun = 30000,
	Soul_Error_SwitchToSame,
	Soul_Error_WaitForTime,
	Soul_Error_NotOpenDiHun,
	//��ӡ���
	ERROR_INSEAL_STATE = 30100,
	//���а�
	ERROR_TOP_NOTRIGHTTIME = 30200,
	ERROR_TOP_REWARDED,
	ERROR_TOP_GAINREWARDBYMAIN,
	ERROR_TOP_GETMONEYBYBAGFULL,
	ERROR_TOP_GAINRMONEY,

	PRIVATE_ADDCHOUREN,

	ERROR_BORDER_TRANS_TIME,
	ERROR_BORDER_TRANS_STATUS,
	ERROR_BORDER_TRANS_FCAR,
	
	//--ϵͳ����--
	SYSTEM_SWITCH_UNOPENED	= 30300,		//�ù�����δ����
	SYSTEM_SWITCH_CANNOT_USE,				//�ù����޷�ʹ��
	SYSTEM_SWITCH_CLOSED,					//�ù����Ѿ��ر�
};

enum	MessageBox_Type
{
	MessageBox_Type_Confirm						=1,			//ȷ����ʾ��
	MessageBox_Type_Choose,									//ȷ��ȡ����ʾ��
	MessageBox_Type_Input,									//����ȷ�Ͽ�

	//��¼����
	MessageBox_Type_USER_CHECK_FAIL				= 10,		//�˻����������
	MessageBox_Type_USER_LOGON_FAIL,						//�˺ŵ�½�����������
	MessageBox_Type_USER_PSW_BLANK,							//���벻��Ϊ��
	MessageBox_Type_Player_Create_Count_Limit,				//�޷�������ɫ�Ѿ������ֵ
	MessageBox_Type_Player_Create_Name_Repeat,				//��ɫ���Ѵ���
	MessageBox_Type_Not_Find_Server,						//û���ҵ���ɫ���ڵķ�����
	MessageBox_Type_Not_Delete_Player_FamilyPower,			//�м���ְ�� ����ɾ��
	MessageBox_Type_Not_Delete_Player_Mail,					//���ʼ�����ɾ��
	MessageBox_Type_Server_Not_Open,						//������δ����
	MessageBox_Type_Cant_Delete_HighLev_Player,				//����ɾ���߼����
	MessageBox_Type_DeleteSelRole,							//�Ƿ�ɾ��ѡ����ɫ
	MessageBox_Type_NotRole,								//���ʺŲ����ڽ�ɫ
	MessageBox_Type_Cant_Delete_HaveFamily,		//����ɾ���м���ְ��Ľ�ɫ
	MessageBox_Type_Cant_Delete_HaveMail_Player,			//����ɾ�����ʼ��Ľ�ɫ
	MessageBox_Type_User_Already_Logon,						//�˺��ѵ�¼
	MessageBox_Type_Disconnect_Server,						//����������Ͽ�����
	MessageBox_Type_Player_Create_Name_Error,				//���ַǷ�
	MessageBox_Type_Version_Error,						    //�汾������ʾ
	MessageBox_Type_User_Check_NotActive,                   //�ʺ�δ����
	MessageBox_Type_User_Check_StopTest,                    //��Ʒֹͣ����
	MessageBox_Type_User_NOT_REG,                    //�˺�δע��
	MessageBox_Type_Connect_World_Error,				//������Ϸ����ʧ��
	MessageBox_Type_Load_Player_Error,				//���ؽ�ɫ��Ϣʧ��
	MessageBox_Type_Connect_Success,					//���ӳɹ�
	MessageBox_Type_Loading_Player,						//���ڼ��ؽ�ɫ����
	MessageBox_Type_Login_Connect_Error,			//���ӷ�����ʧ��
	MessageBox_Type_PropertyProtect,                //�Ʋ�����
	MessageBox_Type_Cant_Delete_HaveGay,		    //����ɾ����ݵĽ�ɫ
	MessageBox_Type_Cant_Delete_HaveConsort,		//����ɾ�����޵Ľ�ɫ
	MessageBox_Type_Cant_Delete_StatePower_Player,	//����ɾ�����ҹ�ְ�Ľ�ɫ
	MessageBox_Type_Player_Login_DataServer_Not_Open,		//ûdataserver
	MessageBox_Type_Player_Login_Scene_Not_Open,	//û����
	MessageBox_Type_Player_Login_Role_Be_Freezed,	//��ɫ������
	MessageBox_Type_Delete_TwoTwice_Player,			//������
	MessageBox_Type_Player_Login_Sucess,


	//����
	MessageBox_Type_Exchange_Player			    = 50,		//��ҽ���
	MessageBox_Type_Delte_Prop,								//���ٵ���
	MessageBox_Type_Splite_Prop,							//��ֵ���
	MessageBox_Type_Bind_Prop,								//�󶨵���
	MessageBox_Type_Exchange_Choose,						//���ܻ�ܾ����׵Ĵ���
	MessageBox_Type_Exchange_Start,							//��ʼ����
	MessageBox_Type_StallCheck_Start,						//���������̯λ��Ϣ

	//��ǰ�ڸ��˹�ϵ��Ƕ�׵������Ӱ�
	MessageBox_Type_Confirmation_Code_Valid	  =80,
	MessageBox_Type_Confirmation_Input,
	MessageBox_Tpye_NotOnLine,
	MessageBox_Type_Storage_Experience_Toplimit,
	MessageBox_Type_Fellow_Storage_Exp_Toplimit,			// ���޾��鴢�浽������ add by zhangjianli 2012-1-3
	MessageBox_Type_Confirmation_Code_Valid_1,              // ���Ѿ��һ�������ļ�����
	MessageBox_Type_CDkeyAward,								// �һ����н� ---> ��ϲ���쵽5Q��,лл���Ĳ���ǩ���쵽�󽱻!
	MessageBox_Type_CDKNotAward,							// �һ���û�н�---> ���ź���û���쵽������,лл���Ĳ���ǩ���쵽�󽱻!

	//���˹�ϵ
	//����
	MessageBox_Type_Request_AddFriend			= 100,		//������Ӻ���
	//������
	MessageBox_Type_Request_AddFriendToBlock,				//���ܽ����Ѽ����������
	//����
	MessageBox_Type_Request_AddConsort,						//��ȷ��Ҫ��XXX��Ϊ���ޣ�����ú�ô��
	MessageBox_Type_Request_RemoveConsort,					//�������������500����ȷ����XXXXX����ż���֣�����ַ���
	MessageBox_Type_Remove_Consort,							//����XXX����ż���֣�����ַɡ�
	MessageBox_Type_Consort_BeRemoveConsort,				//XXX����ż���֣�ѡ����������ַɡ�
	MessageBox_Type_Consort_WaitWoman,						//�����ĵȴ��������������󡭡�
	MessageBox_Type_Consort_SelfRefuse,						//��ܾ��˶Է�����顣
	MessageBox_Type_Consort_SelfRefused,					//�Է��ܾ��������顣
	MessageBox_Type_Consort_TeamChange,						//�����Ա�仯�����ʧ�ܡ�
	MessageBox_Type_Consort_StateIDDifferent,				//����������������ͬ��
	MessageBox_Type_Consort_MoneyLess500,					//���ɱ����е����Ӳ��㡣
	MessageBox_Type_Consort_TeamMemberNotOnLine,			//���ڳ�Ա����ȫ�����ߡ�
	MessageBox_Type_Consort_NotInExplorer,					//���ڳ�Աȫ����������Χ
	MessageBox_Type_Consort_HadConsort,						//������ұ���ȫ��δ�顣
	MessageBox_Type_Self_MoneyLess500,						//������Ӳ���
	MessageBox_Type_Consort_TeamDismiss,					//�����ɢ�����ʧ��
	MessageBox_Type_Consort_NotInTeam,						//�������ǵĶ�����Ӳ���ͬ����
	//���
	MessageBox_Type_Request_AddSworn,						//��ȷ���Ͷ����е�������������
	MessageBox_Type_Sworn_RemoveSworn,						//����һʱ���ֵ�һ������ȷ��Ҫ���ֵ�/���ý�������
	MessageBox_Type_Sworn_SomebodyCancel,					//���ֵ�/���û�δ���Ǻã����δ����ɣ�
	MessageBox_Type_Sworn_WaitOther,						//���ڵȴ������ֵ�/����ȷ������
	MessageBox_Type_Sworn_WaitCaption,						//�ӳ���Ϊ����ȡ����������ͷ�����Ժ�
	MessageBox_Type_Sworn_NoKeyworld,						//�����ֵ�/���á�X���ˣ���Ľ�ݳƺ����������X���֡�
	MessageBox_Type_Sworn_MoreKeyworld,						//�ƺ���ֻ����һ����X���֡�
	MessageBox_Type_Sworn_LengthError,						//�ƺű�����3-5����֮�䡣
	MessageBox_Type_Sworn_TitleError,						//�ƺŲ��Ϸ���
	MessageBox_Type_Sworn_TitleUsed,						//�����н�ݳƺ��ظ�
	MessageBox_Type_Sworn_TeamInfoChange,					//������Ϣ�����仯�����ʧ��
	MessageBox_Type_Sworn_TeamMemberNotOnLine,				//���ڳ�Ա����ȫ�����ߡ�
	MessageBox_Type_Sworn_NotInExplorer,					//��������Ҳ���ͬ���б��У����ʧ�ܡ�
	MessageBox_Type_Sworn_TeamDismiss,						//�����ɢ�����ʧ��
	MessageBox_Type_Sworn_StateChange,						//��������Ҳ��Ǳ������������ʧ�ܡ�

	//���
	MessageBox_Type_Add_Team					= 150,		//������ӵ�����
	MessageBox_Type_Caption_Add,							//
	MessageBox_Type_ApplyJoinTeam,
	//���
	MessageBox_Type_Horse_Replace		= 160, //��ƥ�滻
	//����
	MessageBox_Type_Add_Family					= 200,		//�����Ա
	MessageBox_Type_By_Invert_To_Family,       				//����������
	MessageBox_Type_Invert_To_Family,						//����������
	MessageBox_Type_Delete_Family,             				//ȷ���Ƴ���Ա
	MessageBox_Type_Title_Change_To_Family,    				//����Ȩ�ޱ��
	MessageBox_Type_Teleport_To_Family,        				//��������Ա��
	MessageBox_Type_Summon_From_Family,        				//�ٻ���Ա
	MessageBox_Type_Summon_All_From_Fmaily,    				//�ٻ�ȫ����Ա
	MessageBox_Type_By_Summon_To_Family, 					//���ٻ�ȷ��
	MessageBox_Type_Quit_Family,         					//�˳�����
	MessageBox_Type_Change_Nick_Name_For_Family,			//�ı�ƺ�
	MessageBox_Type_Modify_Notice_For_Family,				//���幫���޸�
	MessageBox_Type_Destory_Family,							//��ɢ����
	MessageBox_Type_Apply_Family_Scene,						//�������ׯ԰������
	MessageBox_Type_Create_Family,      					//��������ʱ��������������
	MessageBox_Type_Delete_Arm,        						//ȷ��ɾ������װ��
	MessageBox_Type_Delete_Family_Skill,   					//ȷ���������弼��
	MessageBox_Type_ReturnFamilyCredit_Choose,				//�������幱�׶�
	MessageBox_Type_BagNoSpace,								//�����п�λ����
	MessageBox_Type_ReturnFamilyCredit_Success,				//���幱�׶ȷ����ɹ�
	MessageBox_Type_FamilyCaptionRequestPKBoss,				//�峤����һ��PKׯ԰Boss
	MessageBox_Type_FamilyAddMoney,							//���Ӽ����ʽ�
	MessageBox_Type_InputMoneyIsZero,						//������Ϊ0
	MessageBox_Type_BagNoMoney,								//���������Ӳ���
	MessageBox_Type_FamilyAddMoneySuccess,					//�ɹ����׼����ʽ�
	MessageBox_Type_RequestFamilySceneSuccess,				//��ϲ����������ͼ�ɹ�
	MessageBox_Type_FamilyNameRepeat,						//���������м��������ظ����볢����������
	MessageBox_Type_CreateFamilySuccess,					//��ϲ����������ɹ�
	MessageBox_Type_NoPowerRecruitMember,					//ֻ���峤�͸��峤��Ȩ������Ա
	MessageBox_Type_OnlySameStateCanInFamily,				//ֻ�����뱾����Ҽ������
	MessageBox_Type_NotEnoughLevel,							//�Է��ȼ�����20��
	MessageBox_Type_AlreadyInFamily,						//�Է����м���
	MessageBox_Type_IsFull,									//��������������
	MessageBox_Type_NotEnoughTime,							//24Сʱ������ٴμ������
	MessageBox_Tpye_BeFireOut,								//�㱻�峤��������
	MessageBox_Tpye_FireMemberSuccess,						//���ѽ�XX��������
	MessageBox_Tpye_CaptionQuitFamily,						//�峤�˳����彫���¼������ý�ɢ��ȷ��Ҫ�˳���ǰ������?
	MessageBox_Tpye_BeAppointAssitant,						//�峤��������Ϊ���帱�峤
	MessageBox_Type_OfflineDismissFamily,					//x��x��xʱ,�峤��ɢ�������ڵļ���
	MessageBox_Type_OfflineBecomeCaption,					//������ְλת�Ƹ���
	MessageBox_Tpye_FreeZhiwu,								//�峤���������ְ��
	MessageBox_Tpye_AppointFood,							//�峤��������Ϊʳ��
	MessageBox_Tpye_ChangeCaptionSuccess,					//�ƽ��峤�ɹ�
	MessageBox_Type_FamilyAlreadyDismiss,					//�˼����ѽ�ɢ
	MessageBox_Type_FamilyAlreadyHasAssistant,				//һ������ֻ����һ�����峤�����Ƚ�����θ��峤
	MessageBox_Type_FamilyAlreadyHasHeadship,				//ѡ����ҵ�ǰ����������ְ�����Ƚ��������ְλ
	MessageBox_Type_FamilyNameError,						//�������Ʋ��Ϸ�
	MessageBox_Type_ExitFamilySuccess,						//�˳�����ɹ���24Сʱ��ſ��ٴμ������
	MessageBox_Type_AppointSuccess,							//�����ɹ�

	//����ս��
	MessageBox_Type_InviteToFCar,								//�������ս��

	//���
	MessageBox_Type_Add_Family_To_Guild			= 250,		//��Ӽ���
	MessageBox_Type_Apply_Gang_Scene,						//������ׯ԰
	MessageBox_Type_By_Invert_To_Guild,      				//�����������ʾ
	MessageBox_Type_Delete_Family_To_Guild,  				//�Ƴ�����
	MessageBox_Type_Title_Change_To_Guild,   				//���Ȩ�ޱ��
	MessageBox_Type_Teleport_To_Guild,       				//���������ڴ�
	MessageBox_Type_Summon_From_Guild,       				//�ٻ�����
	MessageBox_Type_Summon_All_From_Guild,   				//�ٻ�ȫ���峤
	MessageBox_Type_By_Summon_To_Guild,      				//���ٻ�ȷ��
	MessageBox_Type_Quit_Guild,              				//�˳����
	MessageBox_Type_Change_Nick_Name_For_Guild,				//�ı�ƺ�
	MessageBox_Type_Modify_Notice_For_Guild,   				//��ṫ���޸�
	MessageBox_Type_Destory_Guild,             				//��ɢ���
	MessageBox_Type_Create_Guild,         					//�������ʱ��������������
	MessageBox_Type_Modify_Notice_For_Country,				//���ҹ����޸�
	MessageBox_Type_Title_Change_To_Country,  				//ְ������
	MessageBox_Type_GangNameError,							//������Ʋ��Ϸ�
	MessageBox_Type_GangNameRepeat,							//���������а�������ظ����볢���������ơ�
	MessageBox_Type_BagNoHeroJuYiLin,						//������û��Ӣ�۾�����
	MessageBox_Type_CreateGangSuccess,						//��ϲ�㴴�����ɹ�
	MessageBox_Type_NotFamilyCaption,						//���Ǽ����峤
	MessageBox_Type_GangNotSameState,						//ֻ�����뱾����Ҽ�����
	MessageBox_Type_GangNoRecuritPower,						//ֻ�а����򸱰�����Ȩ������Ա
	MessageBox_Type_AlreadyInGang,							//��������а��
	MessageBox_Type_GangIsFull,								//�������������
	MessageBox_Type_LeaveGangTimeLime,						//24Сʱ������ٴμ�����
	MessageBox_Type_FamilyNotExist,							//�ü��岻����
	MessageBox_Type_FamilyCaptionNotOnline,					//�ü����峤������
	MessageBox_Type_GangNotCommonMember,					//����������������ְ��
	MessageBox_Type_GangSetCaptionTimeLimit,				//����24Сʱ��ֻ��ת��һ��
	MessageBox_Type_GangCaptionNotFamilyCaption,			//����Ҳ����峤������ֻ�ܷ��峤����
	MessageBox_Type_SureSetGangCaption,						//ȷ��ת�ð���
	MessageBox_Type_SetGangCaptionSuccess,					//�ƽ��峤�ɹ�
	MessageBox_Type_BecomeGangCaption,						//��XXXX��ת�������ƣ��ѽ�����ְλת�Ƹ��㡣����Ϣ������XXʱXX�֡�
	MessageBox_Type_GangAlreadyHasAssistant,				//һ�����ֻ����һ�������������Ƚ�����θ�����
	MessageBox_Type_NotCommonGangMember,					//����ҵ�ǰ������������ְ�����Ƚ��������ְλ��
	MessageBox_Type_GangAssistantNotFamilyCaption,			//����Ҳ����峤��������ֻ�����峤���Ρ�
	MessageBox_Type_BecomeGangAssistant,					//������������Ϊ��ḱ����������Ϣ������XXʱXX��
	MessageBox_Type_SetToCommonMemberSuccess,				//��������ɹ�
	MessageBox_Type_BecomeCangCommonMember,					//�����������İ��ְ�񣬸���Ϣ������..
	MessageBox_Type_NoGangZhiWu,							//�����û�а��ְλ
	MessageBox_Type_GangHasDismissed,						//������ɢ�������ڵİ�ᣬ24Сʱ��������¼����ᡣ\n����Ϣ������XXʱXX��
	MessageBox_Type_CaptionFireFamily,						//�����ѽ�XXXX���忪������
	MessageBox_Type_GangRemoveFamily,						//��ļ��屻���������������Ϣ������XXʱXX��
	MessageBox_Type_SetupNoAllowAddToGang,					//����ҡ���������ᡱ����δ����
	MessageBox_Type_GangNameTooLong,
	MessageBox_Type_GangNameLessThen4,
	MessageBox_Type_GangMemberDismissFamily,
	MessageBox_Type_GangNotFind,
	MessageBox_Type_YouHasAlreadyInGang,
	//����
	MessageBox_Type_State_Summon				= 300,		//�����ٻ�
	MessageBox_Type_State_King_NoSpeak,						//��������
	MessageBox_Type_State_King_Prisoner,					//��������
	MessageBox_Type_State_Add_UnionState,					//����˹�
	MessageBox_Type_State_Remove_UnionState,				//����˹�
	MessageBox_Type_State_Request_AddUnionState,			//��Ӧ����˹�
	MessageBox_Type_State_Request_RemoveUnionState,			//��Ӧ�Ƴ��˹�
	MessageBox_Type_SetOfficalNext,							//���Ҵ���Ӵ�����
	MessageBox_Type_AcceptSetOfficalNext,
	MessageBox_Type_NotEnoughLevelToPower,					//����ҵȼ�����60�����޷�������Ҫְλ��
	MessageBox_Type_AlreadyHasPower,						//�������������ְλ��
	MessageBox_Type_AppointRequest,
	MessageBox_Type_AppointFailedPowerExist,				//����ʧ�ܣ��Ѿ����˵��δ˹�ְ�ˣ�
	MessageBox_Type_DenyAppointPower,						//xxxx�ܾ����θ�ְλ
	MessageBox_Type_SureGiveupStatePower,
	MessageBox_Type_AddNoSpeakPlayer,
	MessageBox_Type_NoSpeakNotSameState,
	MessageBox_Type_NoSpeakTimesFull,
	MessageBox_Type_BeSetNoSpeak,
	MessageBox_Type_SetNoSeakSuccess,
	MessageBox_Type_StateSetPrisoner,
	MessageBox_Type_OnlyKingHaveSetPrisonerPower,
	MessageBox_Type_FreeFrisonerTimesFull,
	MessageBox_Type_BeFreedFromFrisonerByKing,
	MessageBox_Type_QueryKingRulePower,
	MessageBox_Type_KingToPrisonAsZaiXiangBeKilled,
	MessageBox_Type_TransferKingSuccess,
	MessageBox_Type_BeTransferedKing,
	MessageBox_Type_KingMustIsGangCaption,
	MessageBox_Type_AppointFailedNotSameState,
	MessageBox_Type_KingDownAsFamilyDismiss,
	MessageBox_Type_NotEnoughLevelBecomeKing,
	MessageBox_Type_NotEnoughLevelTopBecomeKing,
	MessageBox_Type_KingDownSuccess,
	MessageBox_Type_KingDownAsRuleLow,
	MessageBox_Type_FamilyAndGangCaiChanBaoHu,
	MessageBox_Type_KingRuleDown,
	MessageBox_Type_ContextNonStandard,
	MessageBox_Type_CannotChangeStateWhileStateWar1,
	MessageBox_Type_CannotChangeStateWhileStateWar2,
	//�ʼ�
	MessageBox_Type_Add_Mail					= 350,      //���µ��ʼ�
	MessageBox_Type_User_Not_Find_Mail,						//�ռ��˲�����
	//Auction
	MessageBox_Type_User_Not_Find_Auction,                  //��������Ϣ�Ѳ�����
	MessageBox_Type_User_Not_Bid_Auction,

	//����
	MessageBox_Type_Quest_No_Select_Prize_Prop  = 400,		//û��ѡ������������
	MessageBox_Type_Quest_NumisOut,							//������������
	MessageBox_Type_Car_LessMoney,							//���ڽ�Ǯ����
	MessageBox_Type_Quest_Delete,							//ȷ��ɾ������
	MessageBox_Type_Quest_Accept,							//�������
	MessageBox_Type_Quest_Finish,							//�����
	MessageBox_Type_TYJY_Hint,								//��԰������ʾ
	MessageBox_Type_Map_FamilyChallenge,					//���ڼ�������ս��ͼ��
	MessageBox_Type_Map_GangFight,							//���ڰ����ս��ͼ��

	//ս��ϵͳ
	MessageBox_Type_Riding_Together				= 450,      //���빲������
	MessageBox_Type_Not_Enough_Time_Releasa_Prison,			//��û������ʱ��

	//�
	MessageBox_Type_Campaign_Invite				= 500,      //�μӻ
	MessageBox_Type_Question_Invite,						//�μӴ���
	MessageBox_Type_Question_HadMiss,                       //�����Ѵ��
	MessageBox_Type_Question_HadOver,                       //�����ѽ��� Add by ChenXY
	MessageBox_Type_Question_WiseOver,						//���ߴ������
	MessageBox_Type_Question_CompeOver,						//���⾺������
	MessageBox_Type_JunShi_Action,							//���»
	MessageBox_Type_Action_Summon,							//��ٻ�
	MessageBox_Type_Action_FamilyJuYiStart,					//����������
	MessageBox_Type_Action_Drink_1,							//��ͺȾƣ��·�ƣ�
	MessageBox_Type_Action_Drink_2,							//��ͺȾƣ�״Ԫ�죩
	MessageBox_Type_Action_Drink_3,							//��ͺȾƣ��ſ���
	MessageBox_Type_Invite_CarList,							//��������ڶ�
	MessageBox_Type_Apply_CarList,								//��������ڶ�
	MessageBox_Type_Warning_FarFrom_Car,				//���棬Զ���ڳ�  (����)
	MessageBox_Type_BeKick_ProtectorList,				//���߳��ڶ�
	MessageBox_Type_Exit_ProtectorList,					//�˳��ڶ�
	MessageBox_Type_ProtectorList_Full,						//�ڶ�������
	MessageBox_Type_MsgBox_FarFrom_Car,				//Զ���ڳ�������MsgBox
	MessageBox_Type_ExchangeGoodsAndGold,				// �������� �һ������ͻ���
	MessageBox_Type_GoodsExchangedInform,				// �������� ���ﱻ�һ�֪ͨ
	MessageBox_Type_GoldExchangedInform,				// �������� �������һ�֪ͨ
	MessageBox_Type_EscortError,				// �������� �������һ�֪ͨ
	MessageBox_Type_TaoYuanJieYiMain,
	MessageBox_Type_TaoYuanJieYiVice,
	MessageBox_Type_TaoYuanJieYiProp,
	MessageBox_Type_InCar_Area,             // ���ڳ���Χ��
	MessageBox_Type_CarryCar_Over_Step,     // �����������һ��
	MessageBox_Type_CarryCar_Over_Final,    // �����������
	MessageBox_Type_CarryCar_Over_Final2,   //�����������
	MessageBox_Type_CarryCar_Over_Final3,
	MessageBox_Type_Quest_WrongAswer,		//��������𰸴���
	MessageBox_Type_WorldQuestion_HadJoin,  //�Ѿ��μӹ�
	MessageBox_Type_BuyPresentSuccess, //�����ս����ɹ�
	//����
	MessageBox_Type_Invert_To_Group				= 550,		//�������Ⱥ
	MessageBox_Type_Apply_Add_Group,
	MessageBox_Type_EWorldMsg_Choose,
	MessageBox_Tpye_EColorfulWorld_Chose,

	//���岹��
	MessageBox_Type_AlreadyHasFooder            = 600,		//һ������ֻ����һ��ʳ�����Ƚ������ʳ��
	MessageBox_Type_FamilyBecomeCaption,					//�峤xx�ѽ������峤ְλת�Ƹ���
	MessageBox_Type_PkFamilyBigThiefFailed,					//��ս��ׯ԰�������ʱ���������ׯ԰ʧ��
	MessageBox_Type_PKBossRequest,							//PK����Boss����
	MessageBox_Type_NoHeadship,								//�����û�й�ְ
	MessageBox_Type_CannotFireSelf,							//���ܿ����Լ�����
	MessageBox_Type_ChangeCaptionTimeLimit,					//�����峤24Сʱ��ֻ��ת��һ��
	MessageBox_Type_FamilyHaveBeen,							//��Ŀǰ���м���
	MessageBox_Type_CanOnlyJoinSameStateFamily,				//ֻ�ܼ��뱾������
	MessageBox_Tpye_OfflineBeFireOut,						// ���߱���������
	MessageBox_Tpye_OfflineFreeZhiwu,						//���߽��ְ��
	MessageBox_Tpye_OfflineBeAppointAssitant,				//�����������峤
	MessageBox_Tpye_OfflineAppointFood,						//��������ʳ��
	MessageBox_Type_JoinFamilyNotEnoughLevel,					//20���ſɼ������
	MessageBox_Type_JoinFamilyNumLimitOnce,					//ͬһʱ��ֻ������10������
	MessageBox_Type_JoinFamilyAlredy,						//���Ѿ��м����ˣ�����������
	MessageBox_Type_JoinFamilyWait,							//����˼����ύ���������ڵȴ�����
	MessageBox_Type_TargetFamilyIsFull,						//Ŀ�������������
	MessageBox_Type_TargetFamilyApplyJoinRecordFull,		//	Ŀ��������׼�����Ѵ�����
	MessageBox_Type_NotOnlineJoinFamilyFaild,				//Ŀ����Ҳ����ߣ����ʧ��
	MessageBox_Type_NotSameStateJoinFamilyFaild,			//ֻ�����뱾����Ҽ�����壬���ʧ��
	MessageBox_Type_JoinFamilyTimeLimit,					//�Է���xСʱx�ֺ�����ٴμ�����壬���ʧ��
	MessageBox_Type_FamilyIsFullJoinFamilyFaild,			//�������������������ʧ��
	MessageBox_Type_ApplyJoinFamilyTimeLimit,				//����ϴ��˳�����ʱ��δ����24��Сʱ������XСʱX�ֺ�������
	MessageBox_Type_TargetHasFamilyJoinFamilyFaild,			//�Է����м��壬���ʧ��
	MessageBox_Type_UpgradeFamilyBuildNotCaption,			//ֻ���峤�����������彨
	MessageBox_Type_CannotUpgradeMoreBuidingSameTime,		//ͬһʱֻ������һ�����彨��
	MessageBox_Type_QiantiBuildingLevelNotEnough,			//ǰ�Ὠ���ȼ�����
	MessageBox_Type_NotEnoughMoneyInFamily,					//�����ʽ���
	MessageBox_Type_AddOverFamilyMaxMoney,
	MessageBox_Type_QueryFamilyBuilding,
	MessageBox_Type_SummonFamilyMemberTimeLimit,
	MessageBox_Type_FamilyNameLessThen4,					//�������Ƴ��Ȳ�������2������(��4����ĸ)
	MessageBox_Type_FamilyAutoDismiss,
	MessageBox_Type_NoUpgradeFamilyBuilding,
	MessageBox_Tpye_JoinListNotVoid,						//����׼������������б�ǿ�
	MessageBox_Type_OnlyCaptionSetRecruit,					//ֻ���峤�������ü�����ļ��ʽ
	MessageBox_Type_RecruitIsOperate,						//��ǰ������ļ��ʽ��Ϊ�ֶ���ļ
	MessageBox_Type_RecruitIsRobotize,						//��ǰ������ļ��ʽ��Ϊ�Զ���ļ
	MessageBox_Type_RecruitSetSucceed,						//��ļ��ʽ���óɹ�
	MessageBox_Type_CreateFamilyFailedAsBagFull,			//��ı����������޷���ý����������������ٳ��Դ�������

	//�׻�
	MessageBox_Type_SendFlowerToFriend			= 650,
	MessageBox_Type_SendFlower,
	MessageBox_Type_AnonymousSendFlower,
	//���� ��ʾ
	MessageBox_Type_TargetServerIsFull          = 700,      //Ŀ��GameServer��Ա
	//������
	MessageBox_Type_WallowStatePre60			= 750,      //������1 Сʱ
	MessageBox_Type_WallowStatePre120,					    //������2 Сʱ
	MessageBox_Type_WallowStatePre170,						//������3 Сʱ
	MessageBox_Type_WallowLoginMsg,						    //������

	MessageBox_Type_Map_Pos_Invalid				= 790,		//����������Ч add by zhangjianli 2012-2-29
	MessageBox_Type_Map_TianChiLing_Trans,					//����촫��ʦ add by zhangjianli 2012-7-16


	MessageBox_Type_MoneyNoEnough = 800,					//��Ҳ���
	MessageBox_Type_LevelNotEnough,
	MessageBox_Type_ExitGangSuccess,
	MessageBox_Type_KingCannotDismissGang,
	MessageBox_Type_ChangeFamilyCreditSuccess,
	MessageBox_Type_PropCanOnlyUseInSelfState,

	MessageBox_Type_HonourChangeExp,

	//��Ჹ��
	MessageBox_Type_Gang_FamilyNotSameState		= 850,		//ֻ�����뱾�����������
	MessageBox_Type_Gang_NotOnline,							//Ŀ����Ҳ�����

	MessageBox_Type_Null,
	MessageBox_Type_InviterOffline,

	//���ضԻ���
	MessageBox_Type_Switch					= 900,			//--������ʾ--

	MessageBox_Type_Prop_Add_Energy			= 910,			//--ʹ�û��������ӻ���ֵ--
};

enum Dialog_Switch_Content		// ���ضԻ�������
{
	DIALOG_SWITCH_UNOPENED,		//�ù�����δ����
	DIALOG_SWITCH_CANNOT_USE,	//�ù����޷�ʹ��
	DIALOG_SWITCH_CLOSED,		//�ù����Ѿ��ر�
};

enum RollNewCommunity_Type
{
	RollNewCommunity_Type_Invalid				=-1,
	RollNewCommunity_Type_Person				=0,	//����
	RollNewCommunity_Type_Team,						//����
	RollNewCommunity_Type_Family,					//����
	RollNewCommunity_Type_Gang,						//���
	RollNewCommunity_Type_State,					//����
	RollNewCommunity_Type_World,					//����
	RollNewCommunity_Type_Scene,					//����
	RollNewCommunity_Type_StateOffical,				//�������й�Ա
};

enum RollNew_Type
{
	//�������
	RollNew_Type_Queset_Accept					=1,				//��������
	RollNew_Type_Queset_TargetCount,							//�������
	RollNew_Type_Queset_CompleteTarget,							//������
	RollNew_Type_Queset_CompleteQuest,							//�ύ����
	RollNew_Type_Queset_QuestCountOut,							//�����б�����
	RollNew_Type_Queset_ProtectedOver,							//����Ŀ���Զ
	RollNew_Type_Queset_QuestFaild,								//����ʧ��
	RollNew_Type_Queset_TimeOver,								//����ʱ�䵽
	RollNew_Type_Queset_ShengWanglimit,							//��������
	RollNew_Type_Queset_Abandon,								//��������
	RollNew_Type_Queset_PrizeRage,								//����������ֵ
	//ϵͳ���
	RollNew_Type_ChangeScene					=1000,			//������
	RollNew_Type_InZone,										//��������
	RollNew_Type_LevelLimit,									//�ȼ�����
	RollNew_Type_MoneyLimit,									//��Ǯ����

	//���
	RollNew_Type_Campaign						=2000,			//�����
	RollNew_Type_CarAlarm,										//�ڳ�����
	RollNew_Type_InCarAlarm,									//���뾯��
	RollNew_Type_OutCarAlarm,									//������
	RollNew_Type_TickOutByAlarm,								//�ڳ��ھ���״̬�У����ܽ���


};

enum Dialog
{
	Dialog_CarMessage				=1,				//ͬ����ں�Ľ���
	Dialog_CarQuestion,								//�������������̾�Ž���
	Dialog_ZhadanrenSkill,							//ը���˼��ܴ򿪽���
	Dialog_LionBag,									//��ʨ��������
	Dialog_CarBag,									//���ڱ�������
};


enum ImportMsgID
{
	IM_Invalid = -1,
	//����������
	IM_Start_YunBiao,   // ���� [315"..name.."] ���ڽ������ڣ��Ͽ�ȥ����!
	IM_Warning_Far,      // Զ���ڳ�
	IM_Invite_Player_To_CarPet, //������Ҽ��뻤��
	IM_FarFrom_CarPet, //��Ŀ���Զ
	IM_StateLeaderBeAttacked,   //���ҹ�ְ������
	IM_StateRuleDown,			//����ͳұ���½�
};

const int PayServerErrorID		= - 1000;

//�Ʒ�ϵͳ ���ر�ʶ  ���� �������� �������ô��, �������ڼ� by zlm 2012.4.11
enum EPayServerReturnFlag
{
	PayServer_ReturnResult_OK			= 1000,				//ִ�гɹ�
	PayServer_ReturnResult_Fail,							//ִ��ʧ��
	PayServer_ReturnResult_ParamError,						//��������
	
	PayServer_ReturnResult_AccountNumberExist = 1101,				//�ʺ��ڻ�Ա�����Ѵ���
	PayServer_ReturnResult_AccountNumberNoExist,			//�ʺ��ڻ�Ա���в�����
	PayServer_ReturnResult_AccountNumber_ProductExits,		//�ʺ��ڲ�Ʒ�����Ѵ���
	PayServer_ReturnResult_AccountNumber_ProductNoExits,	//�ʺ��ڲ�Ʒ�����Ѵ���

	PayServer_ReturnResult_AccountIntegral_NotEnough = 1401,// �ʺŻ��ֲ���
	PayServer_ReturnResult_AccountIntegral_Enough,			// �ʺŻ��ֳ���
	PayServer_ReturnResult_AccountRemaining_NotEnough,		// �ʺ�����
	PayServer_ReturnResult_AccountRemaining_Enough,			// �ʺ�������
	PayServer_ReturnResult_AccountExtPoint_NotEnough,		// �ʺ���չ�㲻��
	PayServer_ReturnResult_AccountExtPoint_Enough,			// �ʺ���չ�����
	PayServer_ReturnResult_AccountDragonCoin_NotEnough,		// �ʺ����Ҳ���
	PayServer_ReturnResult_AccountDragonCoin_Enough,		// �ʺ����ҳ���

	PayServer_ReturnResult_OrderIDRepeate	= 1501,			//������(��ˮ���ظ�,  ����Log���)
	
	PayServer_ReturnResult_GoodsCardNotExist = 1601,		// ��Ʒ��������
	PayServer_ReturnResult_GoodsCardOutOfDate = 1602,		// ��Ʒ���ѹ���
	PayServer_ReturnResult_GoodsCardUsed = 1603,			// ��Ʒ����ʹ��
};