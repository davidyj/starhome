#pragma	   once
/* Error ID 和 Text ID 是一一对应的 所以不能改变已有的 Error ID*/
enum GAME_WORLD_ERROR
{
	GAME_ERROR_FAIL = 0,
	GAME_ERROR_OK	= 1,
	PLAYER_NOT_ONLINE,										//对方不在线
	VERSION_ERROR,											//版本错误

	//用户
	USER_LOGIN_OK		= 10,
	USER_LOGIN_OK_ENABLE_CREATEPLAYERBTN,
	USER_NOT_FIND,											//玩家账户不存在
	USER_ERROR_PSW,											//密码不正确
	PLAYER_CREAET_MAX_LIMIT,								//无法创建角色已经到最大值
	PLAYER_CREATE_NAME_REPEAT,								//无法创建角色名字重复
	USER_NOT_DELETE_PLAYER_FAMILY,							//有家族职称不能删除角色
	USER_NOT_DELETE_PLAEYR_MAIL,							//有邮件不能删除
	USER_NOT_DELETE_LEVEL,									//不能删除高等级的角色
	USER_CHECK_OK,											//账号验证通过
	USER_CHECK_ERROR,										//账号验证失败
	USER_LOGIN_ERROR,										//账号登陆失败
	USER_LOGIN_ALREADY,										//账号已经登录
	USER_LOGIN_TARGETSERVERISFULL,						    //目标GameServer 已满
	PLAYER_CREATE_NAME_ERROR,								//名字非法
	PLAYER_LOGIN_DATASERVER_NOT_OPEN,							//服务器未开放
	PLAYER_LOGIN_SCENE_NOT_OPEN,								//场景未开放
	PLAYER_LOGIN_SUCESS,

	USER_CHECK_NOTACTIVE,                                   // 帐号未激活
	USER_CHECK_STOPTEST,                                    // 产品停止测试
	USER_LOAD_PLAYER_ERROR,									//加载角色信息失败
	PLAYER_BE_FREEZED,										//角色被冻结


	USER_DEFAULT_SHOWMSG = 40,
	//攻击
	PLAYER_UPDATE_EXP	= 50,								//经验变化
	PLAYER_UPDATE_LEVEL,									//等级变化
	PLAYER_UPDATE_HP,										//血值变化
	PLAYER_GET_HIT,											//被击中
	PLAYER_FIGHT_WIN,										//击败目标
	PLAYER_ADD_BUFF,										//添加buff
	PLAYER_REMOVE_BUFF,										//移除buff
	PLAYER_COMMON_CD,										//公共冷却时间未到
	PLAYER_SKILL_CD,										//技能冷却时间未到
	PLAYER_NOT_MP,											//没有Mp
	PLAYER_NOT_TARGET_ZONE,									//不是目标区域
	PLAYER_NOT_TARGET_TEMPLATE,								//不是目标模板
	PLAYER_NOT_TARGET,										//不是目标
	PLAYER_NOT_TARGET_STATUS,								//目标状态不正确
	ATTACK_NEED_TARGET,										//请选择工具目标
	ATTACK_WEAPEN_RESTICK,									//武器限制
	ATTACK_TARGET_NOT_EXIST,                                //攻击目标不存在
	ATTACK_NOT_ALL_FRIEND,                                  //全体和平阵营不能攻击
	ATTACK_NOT_STATE_FRIEND,                                //本国友好不能被攻击
	ATTACK_NOT_TEAM_FRIEND,                                 //组队友好不能攻击
	ATTACK_NOT_FAMILY_FRIEND,                               //家族友好不能攻击
	ATTACK_NOT_SAME_SCENE,                                  //不再同一个场景不能攻击
	ATTACK_NO,                                              //不能攻击
	ATTACK_TARGET_POINT_TO_FAR,								//目标点过远
	ATTACK_CANT_ATTACK,										//无法攻击
	PLAYER_NO_CONTROL,										//无法操作
	//PLAYER_EXP_ADDITION_TEAM,								//组队经验加成  --[060组队经验加成]%d，其中%d：经验值
	PLAYER_STORAGE_EXPERIENCE_TOPLIMIT,						//经验累积已到上限


	//背包
	BAG_IS_FULL	= 100,										//背包已满
	BAG_ADD_PROP,											//增加道具
	BAG_ADD_PROP_STACKABLE,									//增加可堆叠道具
	BAG_REMOVE_PROP,										//移除道具
	BAG_TARGET_IS_FULL,										//对方背包已满
	BAG_RID_PROP_BIND_CANT_MOVEBACK,                        //绑定宠物道具不能移回背包
	BAG_RETINUE_PROP_BIND_CANT_MOVEBACK,                    //绑定侍从道具不能移回背包
	BAG_PROP_WRONG_POSTION,                                 //道具不能装备到此位置
	BAG_ENSIGN_EXIST,                                       //已有军旗类道具装备在身上
	BAG_ENERGY_EXIST,										//已有精华类道具装备在身上
	BAG_HONOR_EXIST,										//已有荣誉类道具装备在身上
	BAG_POSITION_CAN_UNEQUIP,                               //此位置不能取下
	BAG_CANT_ADD_NO_CONTAINER,                              //非背包类的道具不能放背包里
	BAG_RID_BAG_CANT_ADD,                                   //非骑宠道具不能放在骑宠背包里
	BAG_RETINUE_BAG_CANT_ADD,                               //非侍从道具不能放在侍从背包里
	BAG_BINDPROP_ONLY_ADD_MASTER,                           //绑定道具不能添加给其他人的背包
	BAG_COUNT_MAX_LIMIT,                                    //达到添加背包的上限
	BAG_POSTION_HAS_PROP,                                   //此位置已有道具
	BAG_EXTERN_BAG_IS_NOT_EMPTY_CANT_DEL,                   //扩展背包不为空不能删除
	BAG_EXTERN_BAG_IS_NOT_EMPTY_CANT_EQUIP,                 //扩展背包不为空不能装备
	BAG_MOVE_FAILD,                                         //移动失败
	BAG_BEFORE_EQUIP_REMOVE_FAILD,                          //原有装备卸载失败
	BAG_STASH_EXTBAG_FULL,									//仓库背包数已满
	BAG_HAVE_NO_SPACE,										//背包剩余空间不足
    BAG_STASH_FULL,                                         //银行背包满
	BAG_FAMILY_FULL,                                        //家族银行满
	BAG_GANG_FULL,                                          //帮会银行满
	BAG_STASH_BUY_SUCCESS,                                 //购买仓库背包成功
	BAG_STASH_BUY_FAILD,
	BAG_NOMONEY,											//背包中的银子不足
	BAG_HAVEPROP_NOUNEQUIP,									//背包中有道具无法卸除
	BAG_PETEQUIP_EQUIPLEVELHIGHT,							//骑宠装备等级过高
	BAG_CANNOT_REPLACEBAG,									//无法替换背包
	BAG_IS_FULL_CATCH_FAIL,									//捕捉失败！没有空余背包空间


	//金钱
	MONEY_NOT_ENOUGH = 150,									//金钱不足
	CURRENCY_NOT_ALLOWABLE,									//货币类型不符
	PLAYER_ADD_MONEY,										//获得 金币
	PLAYER_REMOVE_MONEY,									//消耗 金币
	GONGXUN_NOT_ENOUGH,                                     //功勋值不足
	FAMILYWAGE_NOT_ENOUGH,                                  //工资不足
	ERROR_OTHER_BIND_MONEY_CMAX,							//消费上限
	HEROILANDCURRENCY_NOT_ENOUGH,							//点将台积分不足
	XUNZHANG_NOT_ENOUGH,

	//任务相关错误
	QUEST_NO_SELECT_PRIZE_PROP = 200,						//请选择一个任务道具
	QUEST_IS_COMPLETE,										//任务达到完成状态
	QUEST_IS_ACCEPT,										//接受任务
	QUEST_IS_FAILD,                                         //任务失败
	QUEST_IS_NO_ACCEPT,                                     //任务不能接受
	QUEST_IS_NO_COMPLETE,									//任务暂时不能完成
	QUEST_IS_NO_DELETE,                                     //任务不能删除
	QUEST_CAR_NO_ACCEPT,                                    //你已接了一个镖车或护送任务
	QUEST_CAR_NO_TRANS,                                     //你有镖车不能进行传送
	QUEST_IS_OUT_NUM,                                       //任务数量满了
	QUEST_TIMELIMIT_OUT,                                    //限时任务一次只能接一个
	QUEST_GAME_TIME_NO_SUIT,                                //活动时间未到
	QUEST_COUNT_IS_OUT,                                     //次数限制
	QUEST_LEVEL_LIMIT,                                      //等级限制
	QUEST_PRIZE_FAILED,                                     //任务奖励失败
	QUEST_PROP_ACCEPT_AGAIN,                                //道具触发任务已接
	QUEST_PREQUEST_NOT_COMPLETE,                            //前置任务没完成
	QUEST_CAMPAIGN_NOT_START,                               //活动还没开始
	QUEST_HAS_COMPLETED,                                    //已做过此任务，不能再做
	QUEST_HAS_ACCEPTED,                                     //此任务在身
	QUEST_COUT_LIMIT,                                       //已经超过次数限制
	QUEST_IS_OVER,                                          //任务完成
	QUEST_IS_EXCLUSIVE,                                     //任务排他
	QUEST_COMPLETE_FAILD,                                   //任务提交失败
	QUEST_IS_NOT_THIS_NPC,									//任务不在这个npc提交
	QUEST_IS_NEED_FRIEND,									//任务需要有一个好友
	QUEST_IS_NEED_MASTER,									//任务需要有师徒关系
	QUEST_IS_NEED_MARRY,									//任务需要结婚后才能接
	QUEST_IS_NEED_FAMILY,									//任务需要有家族
	QUEST_IS_NEED_GANG,										//任务需要有帮会
	QUEST_IS_NEED_WEEKSTAE,									//任务需要本国是弱国
	QUEST_IS_NEED_STRENTHSTATE,								//任务需要本国是强国
	QUEST_PRIZE_SLIVER,										//奖励金子
	QUEST_PRIZE_BINDSLIVER,									//奖励绑定银子
	QUEST_PRIZE_EXP,										//奖励经验
	QUEST_QUESTFOLLOW,										//跟随单位已有
    QUEST_NOT_COMMON_STATUS,								//玩家目前不是普通状态，是骑乘状态或者其它合体状态
	QUEST_PRIZE_SKILLPOINT,									//任务奖励技能点
	QUEST_PRIZE_PNEUMA,										//任务奖励元气值
	QUEST_PRIZE_PRACTISE,									//任务奖励历练功勋
	QUEST_IS_NEED_PROP,									    //任务需要道具
	QUEST_ABANDON,											//放弃任务
	QUEST_NO_NESESSARYQUEST,								//前提任务未接受

	//答题
	QUESTION_ERROR             = 250,                       //不能再接了
	QUESTION_OUT_TIME,                                      //不在答题活动期间
	QUESTION_LEVEL_LIMIT,									//答题等级限制
	QUESTION_DROP_OUT,										//提前退出


	//队伍
	TEAM_TYPE_DIFFERENT = 300,  							//组队方式不同
	TEAM_PLAEYR_BUSY,            							//组队的人正忙，不能组队
	TEAM_PLAYER_IN_SAMETEAM,                                //对方已经在队伍中
	TEAM_PERSON_IN_OTHERTEAM,      			    			//对方已在另一个队伍中
	TEAM_IS_FULL,                							//队伍人数已满
	TEAM_NOT_TEAMCAPTION_NO_POWER,         	    			//不是队长没有权利
	TEAM_NOT_TEAMCAPTION_NO_INVITE_POWER,  	    			//不是队长没有权利邀请
	TEAM_NOT_TEAMCAPTION_APPLICATE,   						//只能向队长申请组队
	TEAM_NOT_TEAM_HONOR_CONDITION,               			//不符合荣誉组队条件，队长必须60级以上，有荣誉之星
	TEAM_NOT_CHANGE_CAPTION_HONOR,                          //荣誉组队不能移交队长
	TEAM_DENY,												//拒绝组队申请
	TEAM_REMOVE_TEAM_MEMBER,								//移除队伍
	TEAM_ADD_TEAM_MEMBER,									//加入队伍
	TEAM_PLAYER_QUIT,                                       //退出队伍
	TEAM_PLAYER_NOT_ONLINE,             					//队员下线
	TEAM_PLAYER_ONLINE,                                     //队员上线
	TEAM_IS_DISBAND,                                        //队伍已解散
	TEAM_TEAMCAPTION_IS_REMOVE,                             //移交队长
	TEAM_TEAMWAY_IS_CHANGE,                                 //更改组队方式
	TEAM_TEAMWAY_IS_CHANGE_ORDINARY,                        //更改组队方式
	TEAM_PICKWAY_IS_FREEDOM,                                //更改拾取方式
	TEAM_PICKWAY_IS_ROTATION,                               //更改拾取方式
	TEAM_PICKWAY_IS_RANDOM,                                 //更改拾取方式
	TEAM_EXPWAY_IS_SPECIAL,                                 //更改经验分配方式
	TEAM_EXPWAY_IS_LEVEL,                                   //更改经验分配方式
	TEAM_LEAVE,                                             //自己离开队伍
	TEAM_JOIN,                                              //自己加入队伍
	TEAM_RECRUIT_IS_AUTO,									//更改招募方式为自动
	TEAM_RECRUIT_IS_MANUAL,									//更改招募方式为手动
	TEAM_PLAYER_NOT_EXIST,									//玩家不存在
	TEAM_CANT_FIND,											//找不到队伍
	TEAM_HONOR_MAX_NUM,										//荣誉组队人数上限
	TEAM_NOT_TEAM_HONOR_CONDITION_MEMBER_LEVEL,             //荣誉组队队员必须60级以下
	TEAM_WAITING_REQUEST_REPLY,
	TEAM_BECOME_CAPTION,									//XX成为了队长
	TEAM_CONNOT_WITH_SELF,									// 不能与自己组队
	TEAM_NOT_CHANGE_EXPWAY,									//荣誉组队不能更改经验分配方式
	TEAM_CHANGE_TEAMWAY,									//有队友等级超过60级，荣誉组队改变为普通组队
	TEAM_CAPTION_DENY_ADD,									//队伍队长拒绝添加你入队
	TEAM_CONNOT_WITH_ENEMY,									//不能与敌对组队
	TEAM_NO_ALLOW,											// 对方关闭了组队被邀请功能
	TEAM_MAP_NOT_ALLOW1,									//此地图不能组队
	TEAM_MAP_NOT_ALLOW2,									//此玩家当前所在的地图不允许组队

	//不明的错误信息
	BAG_FULL_PACKAGE = 500,           						//包裹已满
	MAP_CANNOT_USED,                						//此地图不能使用
	FEE_NOT_ENOUGH,                    						//手续费不足
	JUST_DIVORCE_CANNOT_REMARRY,    						//刚离婚的人不能马上再婚


	//地图
	MAP_POS_INVALID  = 600,									//坐标点无效

	//杂乱 ，fuck
	PRIVATE_NOT_ONLINE			   = 650,
	PRIVATE_IS_DEAD,
	//个人关系(谁也不许占用 哦)
	//好友
	PRIVATE_FRIEND_REQUEST_ADDSELF = 700,					//不能加自己为好友
	PRIVATE_FRIEND_TARGET_OFFLINE,							//对方不在线
	PRIVATE_FRIEND_HAD_INFRIENDLIST,						//XXX已在好友列表中
	PRIVATE_FRIEND_CLOSE_ADDFRIEND,							//XXX关闭了被申请添加好友功能
	PRIVATE_FRIEND_SELF_ISFULL,								//你的好友数量已达上限
	PRIVATE_FRIEND_TARGET_ISFULL,							//XXX的好友数量已达上限
	PRIVATE_FRIEND_TARGET_REFUSE,							//XXX拒绝了您的邀请
	PRIVATE_FRIEND_WAIT_TARGET,								//正在等待XXX接受邀请
	PRIVATE_FRIEND_INVITOR_OFFLINE,							//邀请者已经下线，无法添加好友

	PRIVATE_FRIEND_ADD_FRIEND,								//你与XXX结为好友
	PRIVATE_FRIEND_REMOVE_FRIEND,							//移出好友
	PRIVATE_FRIEND_LEAVE_WORLD,								//好友删号

	//黑名单
	PRIVATE_BLOCK_REQUEST_ADDSELF,							//不能把自己加入黑名单
	PRIVATE_BLOCK_SELF_ISFULL,								//你的黑名单数量已达上限
	PRIVATE_BLOCK_HAD_INBLOCKLIST,							//XXX已在您的黑名单中
	PRIVATE_BLOCK_ADD_BLOCK,								//将XXX加入黑名单
	PRIVATE_BLOCK_REMOVE_BLOCK,								//将XXX移出黑名单
	PRIVATE_BLOCK_TARGET_OFFLINE,							//对方不在线，不能加为黑名单

	//仇人
	PRIVATE_ENEMY_TARGET_INFRIENDLIST,						//对方是你的好友，添加仇人失败。
	PRIVATE_ENEMY_HAD_INENEMYLIST,							//对方已在您的仇人列表中，添加仇人失败。
	PRIVATE_ENEMY_SELF_ISFULL,								//仇人列表已达到上限，添加失败。

	PRIVATE_ENEMY_ADD_ENEMY,								//你被xxx击败！将xxx加入你的仇人列表。
	PRIVATE_ENEMY_REMOVE_ENEMY,								//你与xxx解除仇人。

	//深仇大恨
	PRIVATE_DEEPENEMY_TARGET_INFRIENDLIST,					//目标玩家为你的好友，添加深仇大恨失败 。
	PRIVATE_DEEPENEMY_HAD_DEEPINENEMYLIST,					//该玩家已为您的深仇大恨
	PRIVATE_DEEPENEMY_REQUEST_ADDSELF,						//不能将自己添加为深仇大恨。
	PRIVATE_DEEPENEMY_SELF_ISFULL,							//您的深仇大恨列表已经达到上限，添加失败 。

	PRIVATE_DEEPENEMY_ADD_DEEPENEMY,						//将目标玩家加入深仇大恨列表。
	PRIVATE_DEEPENEMY_REMOVE_DEEPENEMY,						//你与xxx解除深仇大恨。

	PRIVATE_DEEPENEMY_TARGET_OFFLINE,						//对方不在线，不能加为深仇大恨

	//夫妻
	PRIVATE_CONSORT_PLAYER_GIVEUP,							//XXX还未考虑好，结婚未完成
	PRIVATE_CONSORT_REMOVE_CONSORT,							//你与ＸＸＸ解除夫妻关系
	//结拜
	PRIVATE_SWORN_REMOVE_SWORN,								//471XXX（玩家名） 与你解除结拜

	//家族
	FAMILY_EXIT_CYCLE_CANNOT_CREATE = 800,					//退出家族一定时间内不能创建家族
	FAMILY_PLAEYR_BUSY,										//人正忙
	FAMILY_REPLY_DENY,										//拒绝加入家族
	FAMILY_ALREADY_JOIN_CANNOT_CREATE,     					//已加入家族无法继续创建家族
	FAMILY_BANKROLL_NOT_ENOUGH_CANNOT_CREATE,               //资金不足,不能创建家族
	FAMILY_BANKROLL_NOT_ENOUGH_CANNOT_APPLY,                //资金不足,不能申请家族庄园
	FAMILY_NOT_ACHIEVE_CREATE_LEVEL,       					//未达到创建家族所需等级
	FAMILY_BEYOND_WORD_LIMIT,                     			//超出字数限制
	FAMILY_BEYOND_PASSWORD_LIMIT,							//家族密码超过6位限制
	FAMILY_NAME_CONTAIN_ILLEGAL_CHAR,             			//家族名称包含非法字符
	FAMILY_NAME_AND_PASSWORD_CANNOT_NULL,                   //家族名称和密码不能为空
	FAMILY_NAME_REPEAT,                           			//家族名称重复
	FAMILY_NOT_INPUT_REQUIRE_REENTER,                       //不符合输入要求请重新输入
	FAMILY_LEVEL_NOT_ENOUGH_CANNOT_JOIN,					//等级不够不能加入家族
	FAMILY_NOT_SAME_STATE_PLAYER_CANNOT_INVITE,				//家族只能邀请同国玩家加入
	FAMILY_HAVE_BEEN,                     					//已有家族
	FAMILY_NOT_IN_GANG,										//家族不在此帮会中
	FAMILY_EXIT_CYCLE_CANNOT_JOIN,        					//退出家族一定时间内不能加入家族
	FAMILY_IS_FULL,                       					//家族人数已满
	FAMILYCAPTION_OFFLINE,                					//族长不在线
	FAMILY_NOT_FIND_PLAYER,                      			//找不到该玩家
	FAMILY_NOT_FIND_FAMILY,									//找不到该家族
	FAMILY_CANNOT_IMMEDIACY_FIRE_OFFICIAL,       			//不能直接开除官员
	FAMILY_NO_POWER,                             			//没有权限
	FAMILY_CAPTION_NO_SET_CAPTION,							//族长不能设置自己的权限
	FAMILY_ASSISTANT_NO_SET_SELFPOWER,						//副族长不能设置自己的权限
	FAMILY_ASSISTANT_NO_SET_CAPTION,						//副族长不能设置族长的权限
	FAMILY_ASSISTANT_NO_SET_CAPTION_TITLE,					//副族长不能设置族长的称号
	FAMILY_PWD_ERROR,                            			//密码错误
	FAMILY_POST_HAVE_MEMBER,                     			//职位已有成员担任
	FAMILY_CANNOT_REMOVE_AGAIN,                  			//不能再次移交
	FAMILY_NOT_ACHIEVE_UPGRADE_PROSPERITY,       			//未达到升级所需繁荣度
	FAMILY_FUND_NOT_ENOUGH,               					//家族资金不足
	FAMILY_CANNOT_LEARN_MORE_SKILL,       					//不能学习更多家族技能
	FAMILY_OFFER_NOT_ENOUGH,                     			//贡献度不足
	FAMILY_BANKROLL_NOT_REOUGH,								//资金不足
	FAMILY_FAMILYCAPTION_NOT_CANNOT_SUMMON,       			//只有族长才能召唤
	FAMILY_BEYOND_BY_UPPERLIMIT,                  			//超过乘坐上限
	FAMILY_NOT_HOLD_MORE_TANK,                    			//不能拥有更多战车
	FAMILY_NOT_ARM_USE_POWER,              					//没有家族装备使用权限
	FAMILY_AFTER_REPAIR_CONTINUE_USE,             			//修理后才能继续使用
	FAMILY_TANK_DAMAGE,                           			//战车已破损
	FAMILY_GOT_OFF,                               			//请先下车
	FAMILY_NOT_ACHIEVE_CAPTION_TIME,						//族长一天只能设置一次
	FAMILY_CREATE_SUCCESS,                                  //创建家族成功
	FAMILY_CREATE_FAILURE,                                  //创建家族失败
	FAMILY_NOT_IN_FAMILY,                                   //不在家族中
	FAMILY_MENMBER_IS_LEAVE,                                //离开家族
	FAMILY_ONLY_CAPTION_CAN_UPGRADE,                        //只有族长才能升级家族
	FAMILY_LEVEL_UP_SUCCESS,                                //升级家族成功
	FAMILY_LEVEL_UP_FAILURE,                                //升级家族失败
	FAMILY_EQUIPMENT_RETURN_SUCCESS,                        //归还装备成功
	FAMILY_EQUIPMENT_RETURN_FAILURE,                        //归还装备失败
	FAMILY_SKIll_LEARN_SUCCESS,                             //学习技能成功
	FAMILY_SKIll_LEARN_FAILURE,                             //学习技能失败
	FAMILY_SET_CAPTION_POWER_SUCCESS,                       //设置组长权限成功
	FAMILY_SET_CAPTION_POWER_FAILURE,                       //设置组长权限失败
	FAMILY_SET_ASSISTANT_POWER_SUCCESS,                     //设置副组长权限成功
	FAMILY_SET_ASSISTANT_POWER_FAILURE,                     //设置副组长权限失败
	FAMILY_SET_MEMBER_POWER_SUCCESS,                        //设置成员权限成功
	FAMILY_SET_MEMBER_POWER_FAILURE,                        //设置成员权限失败
	FAMILY_Title_GIVE_SUCCESS,                              //赋予称号成功
	FAMILY_Title_GIVE_FAILURE,                              //赋予称号失败
	FAMILY_YOU_HAVENOT_FAMILY,                              //您没有家族
	FAMILY_DONATINGMONEY_SUCCESS,                           //捐献家族资金成功
	FAMILY_DONATINGMONEY_FAILURE,                           //捐献家族资金失败
	FAMILY_PUBLIC_CONTAIN_ILLEGAL_CHAR,                     //家族公告含有非法字符
	FAMILY_JOIN_MEMBER_ACCEPT,							    //欢迎加入家族
	FAMILY_JOIN_PARIVATE_ACCEPT,							//加入家族成功
	FAMILY_REMOVE_MEMBER_NUMBER,							//族长每天只能移除3名成员
	FAMILY_CREATE_SCENE_FAILURE,							//没有权限申请家族庄园
	FAMILY_QUIT_ALL_MEMBER,									//向全部家族的人发送某人离开家族的信息
	FAMILY_APPLY_SCENE_FAILURE,								//申请过家族庄园
	FAMILY_APPLY_SCENE_ACCEPT,								//申请家族庄园成功
	FAMILY_NO_APPLY_SCENE,									//家族族长没有申请过家族庄园
	FAMILY_ONLY_GET_ONE_FAMILY_CAR,							//只能领取一辆家族战车
	FAMILY_GET_CAR,											//领取了家族战车
	FAMILY_BACK_CAR,										//归还了家族战车
	FAMILY_RESEARCH_SKILL_NOT_LEVEL,						//研究家族技能等级不够
	FAMILY_LEARN_SKILL_NOT_LEVLE,							//该等级技能家族还未研究出来
	FAMILY_RESEARCH_SKILL_NOT_CAPTION,						//不是家族族长没有权利研究家族技能
	FAMILY_LEAVE_SKILL_NOT_HAVA,							//该技能您没有学习过，遗忘技能失败
	FAMILY_RESEARCH_SKILL_ACCEPT,							//研究家族技能成功
	FAMILY_LEARN_SKILL_ACCEPT,								//学习家族技能成功
	FAMILY_LEAVE_SKILL_ACCEPT,								//遗忘家族技能成功
	FAMILY_MEMEBER_ADD_WRONG,                               //添加家族成员失败
	FAMILY_FIND_FAILD,                                      //找不到家族
	FAMILY_MONEY_NOT_ENOUGH,                                //家族资金不够
	FAMILY_CONSTRCT_NOT_ENOUGH,                             //家族贡献值不够
	FAMILY_MEMBER_NOT_EXIST,                                //家族成员不存在
	FAMILY_MEMBER_IS_DEAD,									//家族成员死亡，不能召唤
	FAMILY_CAPTION_IS_DEAD,                                 //族长死亡，不能召唤
	FAMILY_MONEY_NOT_LESSZERO,                              //捐献家族资金不能小于0
	FAMILY_CAR_HAS_PULL_SELF,                               //家族战车您已经领取
	FAMILY_CAR_HAS_PULL_ANOTHER,							//家族战车被别人领取了
	FAMILY_CAR_GET_ACCEPT,									//家族战车领取成功
	FAMILY_CAR_NOT_EXIST,                                   //家族战车不存在
	FAMILY_MEMBER_NOT_IN_SAME_FAMILY,                       //不是一个家族的成员
	FAMILY_CAR_MASTER_NOT_EXIST,							//找不到战车主人
	FAMILY_ACTIVE_VALUE_FAILD,                              //设置家族繁荣度失败
	FAMILY_SUMMON_CANT_HAVE_CAR,                            //不能召唤有镖车的家族成员
	FAMILY_SUMMON_ONLY_CAPTION,                             //只有族长才能召唤
	FAMILY_CREDIT_MAY_NOT_SAVE,								//家族贡献度没必要封存
	FAMILY_CAR_HP_NOT_USE,									//家族战车已坏不能使用
	FAMILY_SET_POWER_FAILD,									//对方等级不够，转让族长失败
	FAMILY_GANG_CAPTION_CHANGE,								//身为帮会帮主不能转让其族长权利
	FAMILY_BOSS_NOT_FEED,									//不是喂养boss的食物
	FAMILY_BOSS_NOT_CREATE,									//家族没有领养家族boss
	FAMILY_BOSS_FEED_TIME,									//一天只能喂养一次家族boss，请明天再来
	FAMILY_BOSS_WRITE,										//恭喜获得白boss
	FAMILY_BOSS_BLUE,										//恭喜获得蓝boss
	FAMILY_BOSS_GREEN,										//恭喜获得绿boss
	FAMILY_BOSS_BLACK,										//恭喜获得青boss
	FAMILY_DANCE_ACTION_START,								//家族舞狮活动开始
	FAMILY_DANCE_ACTION_END,								//家族舞狮活动结束
	FAMILY_DISS_STATE,										//当前家族进入解散流程，将于三天后正式解散
	FAMILY_BOSS_FEED_ACCEPT,								//喂食成功
	FAMILY_BOSS_ACCEPT,										//恭喜本家族挑战家族boss成功！
	FAMILY_BAG_NOT_HAVE_PROP,								//您背包里不存在家族勋章
	FAMILY_CAR_CHAGE_NAME_ACCEPT,							//战车更名成功
	FAMILY_CAR_UPDATE_ACCEPT,								//战车升级成功
	FAMILY_DAOCHANG_ACCEPT,									//活动发起成功
	FAMILY_CAR_BACK_ACCEPT,									//归还战车成功
	FAMILY_CAR_DOING,										//该战车正在被别的玩家使用
	FAMILY_CAR_REMOVE_ACCEPT,								//战车摧毁成功
	FAMILY_CAR_COMPOSE_SUCCES,								//战车打造成功
	FAMILY_CAR_NOT_NAME,									//设置战车名字过长
	FAMILY_ADD_CAR_PERSON_ACCEPT,							//加入战车队伍成功
	FAMILY_REMOVE_CAR_PERSON_ACCEPT,						//移除战车队伍成功
	FAMILY_CAPTION_REMOVE_CAR_PERSONG,						//被战车主移除战车队伍
	FAMILY_REMOVE_CAR_ACCEPT,								//离开战车队伍成功
	FAMILY_MAX_LEVEL,										//已经到达家族最高等级
	FAMILY_ADD_MEMBER_SUCCESS,								//家族加入新成员
	FAMILY_REMOVE_MEMBER_SUCCESS,							//家族成员退出
	FAMILY_EXIT_SUCCESS,									//退出家族成功
	FAMILY_TRANSFER_BOSS_FREQUENTLY,						//两次移交帮主时间不能少于24小时
	FAMILY_IS_REMOVED_BY_CAPTION,							//家族被从帮会中移除
	FAMILY_PLAYER_IN_CAR,
	FAMILY_ACQUIRE_FAMILY_SCENE,							//恭喜家族获得家族庄园
	FAMILY_BEAPPOINT_FOODER,								//族长任命xx为家族食神
	FAMILY_LEVEL_UP,										//恭喜家族升为X级家族
	FAMILY_PK_FAMILYTHIEF_FAILED,							//挑战超时，申请家族庄园失败
	FAMILY_REQUEST_PK_FEEDBOSS,								//家族领导发起对家族boss的挑战
	FAMILY_PK_BOSS_FAILED,									//家族boss挑战超时
	FAMILY_PK_THIEF_OVER,									//对庄园大盗的挑战已结束，你来晚了
	FAMILY_FEED_BOSS,										//%s 给家族Boss喂食了一块%s色的人参果


	FAMILY_CAR_REPAIR_SUCCESS,						//战车修理成功
	FAMILY_CAR_REPLACE_FAILED,								//替换战车失败
	FAMILY_CAR_CALLBACK_FAILED,							//收回战车失败
	FAMILY_COST_EVERYDAY,							//每日维护消耗家族资金
	FAMILY_CAR_USEING,								//战车正在使用中
	FAMILY_CAR_MAXNUM,								//战车已达到最大

	FAMILY_CAR_CARCARRY_STATUE,					//运镖或护镖状态不能上战车
	FAMILY_CAR_STATUE_NO_INVITE,	//不能被邀请上战车
	FAMILY_CAR_STATUE_NO_ENTER, //已在家族战车里，不能上另一辆战车
	FAMILY_CAR_BEKICKED,		//被踢出战车
	FAMILY_AUTO_DISMISS,
	//家族挑战赛
	FAMILY_WAR_FLAG_USEING, //旗使用中
	FAMILY_WAR_NO_FAMILY,
	FAMILY_APPLAY_SCENE_WARN,
	FAMILY_LEVEL_DEGREE,
	FAMILY_MONEY_UP,
	FAMILY_WAIT_JOIN,
	FAMILY_CAR_FAR_TO_CAR,		//远离战车，登录失败
	FAMILY_CAR_COMBINPET_NO_INVITE,							//与战宠合体状态，不能被邀请上战车 add by zhangjianli 2012-5-2
	FAMILY_BOSS_BE_DARED,
	FAMILY_CAR_STATUS_STALL_NO_GOUP,                        //摆摊状态下不允许上战车
	FAMILY_CAR_SUMMONFAIL_NO_FAMILYCAR,						//你当前还没有领取战车
	FAMILY_CAR_SUMMONFAIL_STATUS_STALL,                     //摆摊状态下，不能召唤战车
	FAMILY_CAR_SUMMONFAIL_STATUS_CHANGEMODEL,				//变身状态下，不能召唤战车
	FAMILY_CAR_SUMMONFAIL_STATUS_COMBINPET,					//合体状态下，不能召唤战车
	FAMILY_CAR_SUMMONFAIL_STATUS_BUFF_GUIDON,				//扛旗状态下，不能召唤战车
	FAMILY_CAR_SUMMONFAIL_SCENE_NOACCEPT,					//当前场景不能召唤战车
	FAMILY_CAR_SUMMONFAIL_STATUS_FAMILYCAR,					//当前已是战车状态
	FAMILY_CAR_ADD_SUCCESS,									//添加战车成功
	FAMILY_CAR_ADD_FAILED,									//添加战车失败

	//帮会
	GUILD_EXIT_CYCLE_CANNOT_CREATE = 1000, 					//退出帮会一定时间内不能创建帮会
	GUILD_CAPTION_NO_REMOVE_FAMILY_CAPTION,					//帮主不能不当族长
	GUILD_REPLY_DENY,										//拒绝加入帮会
	GUIlD_NO_RECRUIT_NOTFAMILY_CAPTION,						//帮主只能邀请族长加入
	GUILD_GANGCAPTION_NO_REMOVE_OWNFAMILY,					//帮主不能移除自己所在的家族
	GUILD_NOT_SAME_STATE,									//不是同一国家
	GUILD_ALREADY_JOIN_CANNOT_CREATE,     					//已加入帮会无法继续创建帮会
	GUILD_BANKROLL_NOT_ENOUGH,								//资金不足
	GUILD_FAMILY_NUM_NOT_ACHIEVE_BUILD_REQUIRE,				//家族人数未达到组建帮会要求
	GUILD_FAMILY_LEVEL_NOT_ACHIEVE_BUILD_REQUIRE,			//家族等级未达到组建帮会要求
	GUILD_NOT_LAND_PROVE,                        			//没有地产证明
	GUILD_BEYOND_WORD_LIMIT,                     			//超出字数限制
	GUILD_NAME_CONTAIN_ILLEGAL_CHAR,             			//名称包含非法字符
	GUILD_NAME_REPEAT,                           			//名称重复
	GUILD_NOT_INPUT_REQUIRE_REENTER,             			//不符合输入要求请重新输入
	GUILD_HAVE_BEEN,                       					//已有帮会
	GUILD_EXIT_CYCLE_CANNOT_JOIN_GUILD,    					//退出帮会一定时间内不能加入帮会
	GUILD_FAMILY_IS_FULL,                  					//帮会家族数已满
	GUILD_CAPTION_OFFLINE,                  				//帮主不在线
	GUILD_NOT_FAMILYCAPTION_CANNOT_INVITE_JOIN,				//只有族长才能申请加入帮会
	GUILD_NOT_FIND,                        					//找不到该帮会
	GUILD_CANNOT_IMMEDIACY_FIRE_OFFICIAL,        			//不能直接开除官员
	GUILD_ONLY_FIRE_FAMILY,                      			//只能开除家族
	GUILD_NO_POWER,                              			//没有权限
	GUILD_CAPTION_NO_SET_CAPTION,							//帮主不能设置自己的权利
	GUILD_ASSISTANT_NO_SET_CAPTION,                         //副帮主不能设置帮主的权限
	GUILD_ASSISTANT_NO_SET_SELFPOWER,                       //副帮主不能设置自己的权限
	GUILD_MAP_FORBID_USE_FUNCTION,               			//该地图禁止使用此功能
	GUILD_PWD_ERROR,                             			//密码错误
	GUILD_POST_HAVE_MEMBER,									//职位已有成员担任
	GUILD_ONLY_GUILDCAPTION_AND_AUXILIARY_SHOULDER,			//只有族长和本家族副族长才能担任
	GUILD_CANNOT_REMOVE_AGAIN,                   			//不能再次移交
	GUILD_NOT_ACHIEVE_UPGRADE_PROSPERITY,        			//未达到升级所需繁荣度
	GUILD_GUILD_FUND_NOT_ENOUGH,                 			//帮会资金不足
	GUILD_GUILD_CANNOT_LEARN_MORE_SKILL,         			//不能学习更多帮会技能
	GUILD_OFFER_NOT_ENOUGH,                      			//贡献度不足
	GUILD_CREATE_SUCCESS,                                   //创建帮会成功
	GUILD_CREATE_FAILURE,                                   //创建帮会失败
	GUILD_NOT_IN_GANG,                                      //不在帮会中
	GUILD_NAME_AND_PASSWORD_CANNOT_NULL,                    //帮会的名字不能为空
	GUILD_ADD_FAMILY_FAILD,									//帮会添加家族失败
	GUILD_ADD_FAILD,										//添加帮会失败
	GUILD_CAPTION_SET_FAILD,								//设置帮主失败
	GUILD_HAS_IN_GUILD,										//已经加入帮会
	GUILD_CANT_FIND,										//找不到帮会
	GUILD_ADDMEMBER_POWER_ONLY_TO_CAPTION,                   //只有帮主才能加新家族
	GUILD_BEYOND_PASSWORD_LIMIT,							//密码必须要为六位
	GUILD_PROP_FAMILY_DICHAN,								//背包里面没有地产证明
	GUILD_ADD_ACCEPT,										//添加家族成功
	GUILD_NOT_CAPTION_REASERCH_SKILL,						//不是帮主不能研究帮会技能
	GUILD_GANG_LEVEL_NOT_SKILL,								//帮会等级不够不能研究此技能
	GUILD_SKILL_NOT_HAVE,									//该技能不存在
	GUILD_REASECHER_SKILL_ACCEPT,							//帮会研究技能成功
	GUILD_REASECHER_SKILL_FAILD,							//帮会研究技能失败
	GUILD_LEARN_SKILL_ACCEPT,								//帮会学习技能成功
	GUILD_LEARN_SKILL_FAILD,								//帮会学习技能失败
	GUILD_LEAVE_SKILL_ACCEPT,								//帮会遗忘技能成功
	GUILD_LEAVE_SKILL_FAILD,								//帮会遗忘技能失败
	GUILD_NOT_REASECHER,									//该等级技能还未研究
	GUILD_NOT_CAPTION_UPDATE_LEAVE,							//不是帮主没有权利升级
	GUILD_UPDATE_ACCEPT,									//升级成功
	GUILD_UPDATE_FAILD,										//升级失败
	GUILD_PUBLIC_ERROR,										//家族公告不合法
	GUILD_PUBLIC_ACCEPT,									//更改家族公告成功
	GUILD_PUBLIC_FAILD,										//更改家族公告失败
	GUILD_REMOVE_FAMILY_ACCEPT,								//移除家族成功
	GUILD_REMOVE_FAMILY_FAILY,								//移除家族失败
	GUILD_SET_POWER_ACCEPT,									//设置权限成功
	GUILD_SET_POWER_FAILY,									//设置权限失败
	GUILD_SET_MONEY_ACCEPT,									//捐钱成功
	GUILD_SET_MONEY_FAILY,									//捐钱失败
	GUILD_APPLY_SCENE_ACCEPT,								//申请帮会庄园成功
	GUILD_APPLY_SCENE_FAILY,								//申请帮会庄园失败
	GUILD_HAVE_SCENE,										//已经申请过帮会庄园
	GUILD_NOT_APPLY_SCENE,									//只有帮主才有权申请帮会庄园
	GUILD_CAPTION_NOT_DISSFAMILY,							//帮会帮主不能解散家族
	GUILD_SUMMON_MEMBER_TIMES,								//每天只能召唤三次帮众
	GUILD_ASSISTANT_NO_REMOVE_OWNFAMILY,					//副帮主退出帮会前必须移交副帮主职位
	GUILD_DISS_STATE,										//当前帮会进入解散流程
	GUILD_WAIT_RECUIT_ACCEPT,								//等待对方接受邀请
	GUILD_BE_DISMISSED,
	GUILD_APPOINT_ASSISTANT,

	//国家
	STATE_BANKROLL_NOT_ENOUGH = 1200,						//资金不足
	STATE_MAP_CANNOT_USE_FUNCTION,                			//此地图不能该功能
	STATE_PLAYER_HAVE_POSITION,                   			//该玩家已有官职
	STATE_BEYOND_WORD_LIMIT,                      			//超出字数限制
	STATE_BEYONG_TIME_LIMIT,                      			//超过次数限制
	STATE_ALREADY_DRAW_TODAY,                     			//今天已经领取过一次
	STATE_LEAGUE_STATE_ALREADY,                         	//已经是同盟国
	STATE_NOT_LEAGUE_RELATION,                    			//不是同盟关系
	STATE_PERSON_IS_FULL,                         			//人数已满
	STATE_NOT_WAR_TIME_CANNOT_ENTER,              			//非战争时间不能进入
	STATE_ERROR_SELECT_OWN_ADD_UNION,						//不能选择自己做同盟国
	STATE_ERROR_SELECT_OWN_REMOVE_UNION,					//不能选择自己接触同盟国
	STATE_OWN_UNION_STATE_FULL,								//自己的同盟国已满
	STATE_TARGET_UNION_STATE_FULL,							//对方同盟国已满
	STATE_PLAYER_NOTONLINE,									//该玩家不在线或是不存在
	STATE_PLAYER_NOT_SAME_STATE,							//该玩家与你不在同一个国家
	STATE_PLAYER_HAVE_NOSPEAK,								//该玩家今天已经被你禁言一次了
	STATE_PLAYER_HAVE_PRISONER,								//该玩家今天已经被你关进监狱一次了
	STATE_IS_KING_NOSPEAK,									//您被本国国王禁言30小时
	STATE_IS_KING_PRISONER,									//您被本国国王关进监狱2个小时
	STATE_KING_NOSPEAK,										//玩家本您禁言成功
	STATE_KING_PRISONER,									//玩家被您关进监狱成功
	STATE_TARGET_NOT_KING,									//对方国家不存在国王，不能结盟
	STATE_TARGET_KING_NOTONLINE,							//对方国家国王不在线，不能结盟
	STATE_TARGET_STATE_NOT_OWN,								//对方的同盟国里面没有本国，解除盟约失败
	STATE_OWN_STATE_NOT_TARGET,								//自己的同盟国里面没有对方，解除盟约失败
	STATE_ADD_UNION_STATE_ACCPET,							//添加盟国成功
	STATE_REMOVE_UNION_STATE_FAIL,							//移除盟国成功
	STATE_CANT_FIND,										//找不到国家
	STATE_NOT_KING,											//不是国王
	STATE_POWER_FULL,										//现在有人正在担任该职位，请先将其罢免，再任命新的官员。
	STATE_WAITING_APPOINT_ACCPET,							//已经发出任命申请
	STATE_BE_PUSHTOPRISON,									//被关进监狱
	STATE_PUSHTOPRISON_SUCCESS,
	STATE_FREEPRISONER_SUCCESS,
	STATE_KING_RULE_DOWN,
	STATE_BE_INBREAK,										//国家遭到入侵 add by zhangjianli 2012-2-28

	//交易
	EVENT_EXCHANGE_REFUSE = 1300,							//对方拒绝交易
	EVENT_EXCHANGE_ADD_PROP_BIND,							//绑定道具不允许交易
	EVENT_EXCHANGE_ADD_PROP_FAILURE,						//添加交易道具失败
	EVENT_EXCHANGE_REMOVE_PROP_FAILURE,						//删除交易道具失败
	EVENT_EXCHANGE_FAILURE,									//交易失败
	EVENT_EXCHANGE_CANCEL,									//取消交易
	EVENT_EXCHANGE_SUCCESS,									//交易成功
	EVENT_EXCHANGE_BUSY,									//对方正在忙
	EVENT_EXCHANGE_COUNT_MAX,								//交易背包已满
	EVENT_EXCHANGE_NOT_EXPLORER,				    		//玩家不再同一屏幕内，
	EVENT_EXCHANGE_TARGET_UNALLOWEXCHANGE,					//对方不允许进行交易
	EVENT_EXCHANGE_SEND,                                    //已向对方发送交易请求
	EVENT_EXCHANGE_STALLSTAT_NOTEXCHANGE,                   //摆摊状态不能进行交易
	EVENT_EXCHANGE_TARGET_NOTEXCHANGE,                      //对方摆摊不能进行交易
	EVENT_EXCHANGE_NOT_STATE,                        		//不是相同国家不让交易
	EVENT_EXCHANGE_SUCCESS_GETMONEY,                 		//交易过程中获得的金钱数
	EVENT_EXCHANGE_SUCCESS_LOSTMONEY,                		//交易过程中失去的金钱数
	EVENT_EXCHANGE_SILVER1,                                 //自己的钱到上线了
	EVENT_EXCHANGE_SILVER2,                                 //对方的钱到上线了
	CANT_LILIANGONGXUN,                                     //历练功勋不足
	EVENT_EXCHANGEING,                                      //交易中不能進行其他操作
	EVENT_CAN_NOT_EXCHANGE,                                 //该道具不参与玩家之间交易
	CANT_LILIANGONGXUN_MAXNUM,								//本周兑换次数已达最大上限

	//服务器信息
	SERVER_GAMESERVER_BREAK = 1400,							//gameserver链接断开
	SERVER_GAMESERVER_CONNECT,								//gameserver链接成功
	SERVER_COMMUNITYSERVER_BREAK,							//communityserver链接终端
	SERVER_COMMUNITYSERVER_CONNECT,							//Communityser链接成功

	//技能
	SKILL_NOT_ENOUGH_MP		=1500,							//Mp不足
	SKILL_BEIN_COMMON_COOLDOWN,								//公共冷却时间未到
	SKILL_BEIN_SKILL_COOLDOWN,								//技能冷却时间未到
	SKILL_DISTACNE_TO_FAR,									//攻击目标太远
	SKILL_NOT_TARGET_TYPE,									//攻击目标无效
	SKILL_SELF_STATUS_RESTRICT_ERROR,						//自身状态限制错误
	SKILL_LEARN_NEED_BOOK,									//请先使用技能书学习该技能
	SKILL_LEARN_SUCCESS,									//技能学习成功（包括技能升级成功）
	SKILL_LEARN_USECOUNT,									//技能熟练度不够


	//技能树
	SKILLTREE_LEVEL_LIMIT	= 1600,							//学习技能任务等级限制
	SKILLTREE_PRESKILL_LIMIT,								//学习技能前置技能限制
	SKILLTREE_MUTEX_SKILL,									//互斥技能
	SKILLTREE_SYSTEM_SKILLPOINT,							//技能树的点数要求
	SKILLTREE_NOT_SKILL_POINT,								//技能点不足
	SKILLTREE_MAX_LEARN_POINT,                              //技能已经是最大值了
	SKILLTREE_SKILL_LEARNED,                                //技能已经学习了
	SKILLTREE_SKILL_LEARN_FAILD,                            //技能学习失败
	SKILLTREE_CLASS_POINT_LIMIT,							//本系所加技能点数限制
	SKILLTREE_SKILL_NOT_SELF_CLASS,							//技能不属于自己的职业
	SKILLTREE_SKILL_NOT_SELF_RAMIFY,						//技能不属于自己的职业分枝
	SKILLTREE_LEARN_SKILL_USE_BOOK,							//升级此技能需要相应技能书
	SKILLTREE_LEARN_SKILL_STRIDE_LEVEL,						//不能跨级学习技能 add by zhangjianli 2011-11-22





	//邮件
	MAIL_DELETE_FAILURE  =1700,								//删除邮件失败
	MAIL_DELETE_SUCCESS,									//删除邮件成功
	MAIL_DELETE_PROP_FAILURE,								//移除道具失败
	MAIL_DELETE_PROP_SUCCESS,								//移除道具成功
	MAIL_SEND_FAILURE,										//发送邮件失败
	MAIL_SEND_SUCCESS,										//发送邮件成功
	MAIL_GETPROP_FAILURE,									//提取道具失败
	MAIL_GETPROP_SUCCESS,									//提取道具成功
	MAIL_GETMONEY_FAILURE,									//提取金钱失败
	MAIL_GETMONEY_SUCCESS,									//提取金钱成功
	MAIL_MONEY_OVER_OWNERMONEY,								//邮件中的金钱大于现有金钱
	MAIL_OVER_MAX_COUNT,									//超过了所能接受邮件的最大数量
	MAIL_MONEY_NOT_ENOUGH,									//资金不足
	MAIL_MONEY_NOT_ENOUGH_NOCANTIQU,						//资金不足,无法提取
	MAIL_OVER_MAX_ACCEPT_COUNT,								//对方已经达到所能接受的最大限制
	MAIL_BAG_ADD_MONEY,										//得到金钱
	MAIL_TITLE_OVER_MAXLENGTH,								//邮件标题超过最大长度限制
	MAIL_CONTEXT_OVER_MAXLENGTH,							//邮件内容超过了最大长度限制
	MAIL_TITLE_CONTAIN_ILLEGAL_CHAR,						//邮件标题还有非法字符
	MAIL_CONTEXT_CONTAIN_ILLEGAL_CHAR,						//邮件内容还有非法字符
	MAIL_CANT_FIND,											//找不到邮件
	MAIL_CANT_FIND_PROP,									//没有找到邮件中的道具
	MAIL_MONEY_LESS_ZERO,									//邮件中金钱数小于0
	MAIL_STRING_IS_NULL,									//字符串为空指针
	MAIL_ERROR_NOT_DELTE_PROP_MAIL,							//邮件里有道具或者金币不能删除
    MAIL_NOT_SAME_STATE,									//不同国家不能发送邮件
    MAIL_NOBODY_SEND_FAILURE,                              //目标不存在发送邮件失败
	MAIL_GETMONEYFAILD,                                    //GetMailMoneyFaild:已超过银子携带最大上限
	MAIL_SEND_HIGHT_FREQUENCY,								//发送邮件太过频繁

	//拍卖
	AUCTION_BID_SUCCESS = 1800,                             //竞拍成功
	AUCTION_MONEY_NOT_ENOUGH,                				//金钱不足，无法买卖（摆摊单元也在使用）
	AUCTION_BID_BEGIN,                       				//开始竞拍
	AUCTION_PROP_NOT_EXIST,                  				//物品不存在
	AUCITON_BID_BEYOND,                      				//竞价被超过
	AUCTION_FAILURE,                         				//拍卖失败,您的金钱不足以支付管理费
	AUCTION_PROP_OVERDUE,                    				//拍卖物品已过期作废
	AUCTION_CANCEL,                          				//拍卖已取消
	AUCTION_SUCCESS,                         				//拍卖物品已售出
	AUCTION_BAND_NOT_SALE,                   				//绑定物品不能拍卖
	AUCTION_ADD_AUCTION_SUCCESS,							//添加拍卖信息成功
	AUCTION_DELETE_AUCTION_SUCCESS,							//删除拍卖信息成功
	AUCTION_CANNOT_BID_SELF_PROP,							//不能竞拍自己出售的物品
	AUCTION_MUST_SET_BID,									//必须设置起拍价格
	AUCTION_BUYOUT_LOW_BID,									//一口价低于了竞价
	AUCTION_PRICE_LOW_BID,									//设置价格低于竞标价
	AUCTION_PRICE_LOW_HIGHEST_BID,							//设置价格低于最高竞价
	AUCTION_SELF_HIGHEST_PRICE,								//自己已经是最高竞价
	AUCTION_SEND_SUCCESS_TO_OWNER,							//您的物品已经成功被拍卖
	AUCTION_MAKE_BID_SUCCESS,								//成功参与竞拍当前物品
    AUCTION_NO_BID,                                         //当前物品没有一口价，不能一口价购买！
	NOT_FIND_AUCTION_PROP,                                  //该拍卖信息已不存在
	NOCE_DOAUCTION_COUNT,                                   //一次最多只能放100条拍卖信息

	//打造合成
	COMPOSE_SIGN_SUCCESS = 1900,
	COMPOSE_SIGN_FAILTURE,
	COMPOSE_BIND_SUCCESS,				//绑定成功
	COMPOSE_BIND_FAILTURE,				//绑定失败
	COMPOSE_REPEATBIND_SUCCESS,			//重绑成功
	COMPOSE_REPEATBIND_FAILTURE,		//重绑失败
	COMPOSE_REPEATBIND_MATLESS,			//材料不足
	COMPOSE_REPEATBIND_PROPSIGNBIND,	//装备需绑定并签名
	COMPOSE_STAR_SUCCESS,
	COMPOSE_STAR_FAILTURE,
	COMPOSE_UNSTAR_SUCCESS,				//拆星成功
	COMPOSE_UNSTAR_FAILTURE,			//拆星失败
	COMPOSE_UNSTAR_PROPNOTSTAR,			//拆星失败,装备不带星
	COMPOSE_UNSTAR_STARDOWN,			//拆星失败, 获得了星数下降的封星石

	COMPOSE_REPEATSTAR_SUCCESS,			//附星成功
	COMPOSE_REPEATSTAR_FAILTURE,		//附星失败
	COMPOSE_REPEATSTAR_EQUIPSTAR,		//附星失败,装备带星,先拆星
	COMPOSE_HOLE_SUCCESS,
	COMPOSE_HOLE_FAILTURE,
	COMPOSE_ENCHANSE_SUCCESS,			//镶嵌宝石成功
	COMPOSE_ENCHANSE_FAILTURE,			//镶嵌宝石失败
	COMPOSE_UNENCHANSE_SUCCESS,			//拆除宝石成功
	COMPOSE_UNENCHANSE_FAILTURE,		//拆除宝石失败
	COMPOSE_CHANGEZHANHUN_SUCCESS,		//修改战魂成功
	COMPOSE_CHANGEZHANHUN_FAILTURE,		//修改战魂失败
	COMPOSE_CREATE_PROP_SUCCESS,
	COMPOSE_LEVEL_PROP_SUCCESS,
	COMPOSE_QUALITY_PROP_SUCCESS,
	COMPOSE_ATTR_PROP_SUCCESS,
	COMPOSE_CREATE_PROP_FAILTURE,
	COMPOSE_LEVEL_PROP_FAILTURE,
	COMPOSE_QUALITY_PROP_FAILTURE,
	COMPOSE_ATTR_PROP_FAILTURE,
	COMPOSE_PROP_UNSIGNABLE,								//该道具不可签名
	COMPOSE_PROP_UNADDSTAR,									//该道具不可加星
	COMPOSE_PROP_UNADDHOLE,									//该道具不可打孔
	COMPOSE_PROP_UNENCHASE,									//该道具不可镶嵌
	COMPOSE_PROP_UNUPGRADE,									//该道具不可升级
	COMPOSE_PROP_SIGNED,									//该道具已签名
	COMPOSE_PROP_BINDED,									//该道具已绑定
	COMPOSE_PROP_NOSIGNED,									//该道具未签名
	COMPOSE_PROP_NOBINDED,									//该道具未绑定
	COMPOSE_PROP_SIGNEDBYME,								//已经是自己的签名
	COMPOSE_PROP_NOHOLE,									//没有多余的位置可以镶嵌宝石
	COMPOSE_PROP_QUALITY_HIGHEST,							//该道具已为最高品质
	COMPOSE_MAT_TYPE,										//材料类型错误
	COMPOSE_MAT_CLASS,										//材料级别段错误
	COMPOSE_MAT_ERROR,                                      //请按顺序打孔
	COMPOSE_MAT_LOW,                                        //钻头级别太低
	COMPOSE_MAT_OVERFULL,									//材料数量过多
	COMPOSE_MAT_LACK,										//材料数量不足
	COMPOSE_MAT_STAR,										//请使用与星星对应位置的材料
	COMPOSE_MAT_NEEDSAME,									//请使用相同的材料进行合成
	COMPOSE_MAT_FAIL_GEMED,									//镶嵌过宝石孔无法在此打孔
	COMPOSE_INVALID_PROP,									//无效的合成道具
	COMPOSE_MATERIAL_IS_NOT_CHECK,							//材料不符
	COMPOSE_PROP_MARK_ZERO,									//道具分数为0
    COMPOSE_UPQUALITY_PROP_SUCCESS,							//装备升级成功 4旧 + 1 == 1新
	COMPOSE_UPQUALITY_PROP_FAILTURE,						//装备升级失败 4旧 + 1 == 1新
	COMPOSE_UPQUALITY_PROP_FAILTURE_LEVEL,					//装备升级失败,材料等级不符
	COMPOSE_ENCHANTING_PROP_SUCCESS,						//固定材料的合成成功  5 + 金钱 == 1
	COMPOSE_ENCHANTING_PROP_FAILTURE,						//固定材料的合成失败  5 + 金钱 == 1
	COMPOSE_PROP_LEVELLIMIT,								//装备道具等级不符
	COMPOSE_PROP_QUALIYLESS,								//装备品质过低
	COMPOSE_PROPMAT_QUALIYLESS,								//合成材料品质过低
	COMPOSE_PROPMAT_PROP_NOTAGREE,							//合成材料与装备等级不符
	COMPOSE_PROP_NOZHANHUN,									//装备不具备战魂属性
	COMPOSE_BAGSPACE_LESS,									//操作失败,背包剩余空间过少
	COMPOSE_PROP_ADDSTARFULL,                                //道具加星数已满
	COMPOSE_PROP_ADDSTARFULLBANNERMSG,						//加星满星的横幅信息
	COMPOSE_PROP_MATERIAL_EQUIP_FAIL,						//材料与装备类型不符
	COMPOSE_PROP_ADDGEM_COLORREPEATE,						//宝石镶嵌的颜色重复
	COMPOSE_PROP_ADDGEM_CURPOSNOADDGEM,						//此位置已有宝石,无法进行镶嵌
	COMPOSE_PROP_ADDGEM_ORDERBYERROR,						//镶嵌宝石请按顺序镶嵌
	COMPOSE_PROP_ADDGEM_HOLELEVELLOW,						//无法将高级宝石镶嵌在低级孔上
	COMPOSE_PROP_REPEATEBIND_NOTPPERCENTATTR,				//装备上没有百分比属性 改造失败

//---------
	COMPOSE_PROP_BIND_NEED_SOULJADE,						//绑定需要放入灵魂玉
	COMPOSE_PROP_REPEATEBIND_EQUIPLEVELOVERTEN,				//重新绑定的装备必须大于10级
	COMPOSE_PROP_REPEATEBIND_NEEDGOLDQUALITY,				//重新绑定需要金色以上品质装备
	COMPOSE_PROP_NEED_SILVERMATERIAL,						//需要银材料	--公共
	COMPOSE_PROP_NEED_LEATHERMATERIAL,						//需要熟皮材料	--公共
	COMPOSE_PROP_REPEATEBIND_NEEDSILVER,					//武器/项链/戒指/饰品需要使用材料银进行绑定或修改
	COMPOSE_PROP_REPEATEBIND_NEEDLEATHER,					//头盔/副手/衣服/护腕/腰带/鞋子使用材料皮进行绑定或修改
	COMPOSE_PROP_UNADDSTAR_EQUIPLEVELOVERTEN,				//摘星的装备必须大于10级
	COMPOSE_PROP_UNADDSTAR_EQUIPQUALITY_OVERPURPLE,			//摘星的装备品质必须是紫色或紫色一样
	COMPOSE_PROP_REPEATESTAR_EQUIPLEVEL_OVERTEN,			//附星的装备等级必须大于10级
	COMPOSE_PROP_REPEATESTAR_EQUIPQUALITY_OVERPURPLE,		//附星的装备品质必须是紫色或紫色一样
	COMPOSE_PROP_REPEATESTAR_EQUIPLEVELNOTINSOULSTONELEVELRANGE, //附星的装备与封星石使用范围不符
	COMPOSE_PROP_ADDHOLE_NEED_OPENSUNSTONE,					//必须使用开阳石进行打孔
	COMPOSE_PROP_ADDHOLE_MUSTUSEHIGHTLEVEL_OPENSUNSTONE,	//只能使用更高级别的开阳石修改已有孔
	COMPOSE_PROP_UNADDGEM_EQUIPLEVEL_OVERTEN,				//拆除宝石的装备等级必须大于10级
	COMPOSE_PROP_ADDGEM_NEEDSOULROCK,						//需要放入魂魄石进行镶嵌
	COMPOSE_PROP_CHANGEZHANHUN_EQUIPLEVEL_OVERTEN,			//战魂修改装备等级必须大于10级
	COMPOSE_PROP_CHANGEZHANHUN_EQUIPQUALITY_OVERGOLD,		//战魂修改装备品质是金色或金色以上
	COMPOSE_PROP_CHANGEZHANHUN_MATERIALLEVELLESSTHREE,		//战魂修改材料等级最低为三等材料

	COMPOSE_PROP_CHANGEFIVEELEMENT_EQUIPQUALITY_OVERGOLD,	//五行修改装备品质必须是金色或金色以上
	COMPOSE_PROP_NEEDTHREETOFIVE_MATERIALLEVEL,				//需要3~5等材料
	COMPOSE_PROP_NEEDFOURTOSIX_MATERIALLEVEL,				//需要4~6等材料

//---------
	//stall

	//PK和监狱
	PK_TYPE_WRONG  =2200,				//攻击模式不对
	PK_KILL_STATE_MAN,					//杀死本国玩家
	PK_SYSTEM_PUT_TO_PRISON,			//被系统抓进监狱
	PK_PLAYER_PUT_TO_PRISON,			//被玩家抓进监狱
	PK_PRISON_TIME_IS_NOT_OVER,			//监狱时间未到

	PK_STATUS_CHANGE_HERO,				//当前为英雄状态
	PK_STATUS_CHANGE_WELLDOER,			//当前为善人状态
	PK_STATUS_CHANGE_ORDINARY,			//当前为普通状态
	PK_STATUS_CHANGE_BADDIE,			//当前为恶人状态
	PK_STATUS_CHANGE_DEMON,				//当前为恶魔状态
	PK_STATUS_CHANGE_DEMON_HEAD,		//当前为魔头状态
	PK_STATUS_CHANGE_MALICIOUS,			//当前为恶意攻击状态
	PK_STATUS_CHANGE_CHANGE,			//当前为即将恢复普通状态

	PK_KILLER_IS_OFFLINE,				//凶犯不在线
	PK_KILLER_IS_INPRISON,				//凶犯已在监狱
	PK_KILLER_CATCH_SUCCESS,			//凶犯成功抓捕
	PK_ENEMY_WRONG,						//不是敌人
	PK_NOT_STATE_KILL,					//伤你的是敌国玩家，本国捕快毫无办法将其捉拿归案。
	PK_REDNAME_NOT_CATCH,				//红名不能抓捕凶犯

	PK_TYPE_CHANGE_ALL,					//切换为全体模式
	PK_TYPE_CHANGE_PEACE,				//切换为和平模式
	PK_TYPE_CHANGE_STATE,				//切换为国家模式
	PK_TYPE_CHANGE_UNION,				//切换为盟国模式
	PK_TYPE_CHANGE_GANG,				//切换为帮会模式
	PK_TYPE_CHANGE_FAMIY,				//切换为家族模式
	PK_TYPE_CHANGE_EVIL,				//切换为善恶模式
	PK_TYPE_CHANGE_ENEMY,				//切换为仇人模式
	PK_TYPE_CHANGE_CAMP,				//切换为阵营模式

	//摆摊
	STALL_NOT_REGIONAL	= 2300,
	STALL_PROP_BINDED,					//道具已绑定，不能出售
	STALL_PROP_NOPRICE,					//请设置道具的出售价格
	STALL_UIPOS_NOEMPTY,				//该位置以有道具
	STALL_PROP_NUM_NOENOUGH,			//道具数量错误
	STALL_PROP_SALE,
	STALL_PROP_SUCCESS,                 //道具买卖成功
	STALL_PROP_FAIL_SALED,				//道具已被出售,购买失败
    STALL_PROP_FAIL,                    //运镖过程中不可以摆摊
	STALL_PROP_RID_FAIL,                //骑马状态下不可以摆摊
	STALL_FAIL_EXCHANGE,				//交易状态不可摆摊
	STALL_FAIL_CHANGEMODEL,				//变身状态不可摆摊
	STALL_FAIL_DEAD,					//死亡状态不可摆摊
	STALL_FAIL_NUMNOTENOUGH,			//购买数量不足
	STALL_FAIL_LEAVEMESSAGE_FAIL_ONE,		//您已经留过一次言了，请勿重复留言
	STALL_FAIL_SILVER_NOTENOUGH,			//银子不足，无法购买
	STALL_FAIL_SELLNUMZERO,					//摆摊位不可为空
	STALL_FAIL_STATUS_FAMILYONCAR,          //召唤家族战车中不可摆摊
	STALL_ADD_STALLPROP_FALID,              //添加摆摊信息失败 该道具已在摆摊列表中
	STALL_IS_SUPERADDFLAG,									//对不起,该摊位正在追售中,请稍后再购买
	STALL_CANT_LEAVEMESSAGE,								//该摊位已收摊,不能添加留言信息
	//道具
	PROP_LEVEL_NOT_REACH = 2400,		//等级不足，无法使用该道具
	PROP_LEVEL_OVERTOP,					//等级过高，无法使用该道具
	PROP_NEED_TWO_HANDS,				//您需要两只手来拿这件武器
	PROP_LEFT_NO_HANDS,					//您没有多余的手来拿这件装备
	PROP_DURABILITY_IS_ZERO,            //道具磨损度为0
	PROP_HAS_BIND,                      //已经绑定了
	PROP_NOT_SAME_STATE_AND_NEUTRAL_CANNOT_USE,	//只能在本国和中立地区使用
	PROP_ADD_FAILD,                     //道具添加失败
	PROP_BIND_FAILD,                    //绑定失败
	PROP_SPLIT_FAILD,                   //拆分失败
	PROP_SPLIT_NUM_WRONG,               //拆分数量错误
	PROP_COMBINE_FAILD,                 //合并道具失败
	PROP_NOT_STACKABLE,                 //不是可堆叠道具
	PROP_NOT_SAME_PROP_CANT_COMBINE,    //不同道具不能堆叠
	PROP_COMBINE_MAX_LIMIT,             //超过最大堆叠数量
	PROP_DROP_PROTECT,                  //道具跌落保护
	PROP_EQUIP_PROP_CANT_USE_UNEQUIP,   //装备类型道具不能在非装备栏使用
	PROP_USE_FAILD,                     //道具使用失败
	PROP_ADD_EFFECT_FAILD,				//道具加效果失败
	PROP_CD_NOT_REACH,					//装备道具时间未到
	PROP_CANNOT_DESTROY,				//道具不能被销毁
	PROP_CANNOT_SALE,					//道具不能被出售
	PROP_MAN_USE,						//只有男性玩家可以使用
	PROP_FEMAN_USE,						//只有女性玩家可以使用
	PROP_CANNOT_USE_ONSTALL,			//您正处于摆摊状态
	PROP_CANNOT_USE_ONDEAD,				//您正处于死亡状态
	PROP_CANNOT_USE_ONGHOST,			//您正处于灵魂状态
	PROP_SALE_SUCCESS_USESILVER,         //道具卖给npc 成功 用未绑定的银子
    PROP_SALE_SUCCESS_USEBINDSILVER,    //道具卖给npc 成功，用绑定的银子
	PROP_BUY_SUCCESS,                    //买道具成功
	PROP_BIND_TYPE_ERROR,                //道具绑定类型不同，不可以堆叠
	PROP_QUALITY_ERROR,                  //道具品质不同，不可堆叠
	PROP_ADD_TO_BAG,                     //添加道具成功
	PROP_REPAIR_SUCCESS, 				 //道具修理成功
	PROP_REPAIR_ONEFAILE,				//此道具不需要修改
	PROP_REPAIR_ONECOSTM,				//单件道具修理扣钱
	PROP_LIMIT_OWN_COUNTRY_USE,			//此道具限制只能在本国使用
	PROP_LIMIT_NOCAN_FLY_THISMAP,		//当前地图无法使用传送功能
	PROP_NOT_EQUIPABLE, 				//此道具不能装备
	PROP_NOT_EQUIPMENT, 				//此道具不是装备
	PROP_CANNOT_INSERT_ACTBAR,			//当前物品不可使用，不必拖入快捷键区
	PROP_USECOUNT_FULL,					//道具使用次数已满
	PROP_ADD_FELLOW_EXP,					//使用珍兽经验丹成功
	PROP_UNABLE_TOPICK,					//你无权拾取此道具
	PROP_ADD_FELLOW_EXP_OVERFLOW,	 //经验溢出
	PROP_USEAFTER_SENDSYSTEMMSG,		//道具使用后发送系统消息
	PROP_CANNOT_USE_ONCHANGEMODEL,		//您正处于变身状态
	PROP_MOVE_CANNOTDRAG,					//道具处于移动状态不可拖拽
	PROP_CANNOT_USE_THIS_TARGET,			//道具无法对该目标使用
	PROP_CANNOT_USE_IN_FAMILYCAR,			//道具无法在战车中使用
	PROP_NOT_INBAGBAG,					    //该道具在储物箱里，不能使用
	PROP_NOTSELL_INBAGBAG,					//该道具不在主背包里，不能出售
	PROP_NO_PUT_ACTIVE_BAR,					// 该道具不允许放入快捷栏
	PROP_NO_INBAGBAG_NO_ACTIVE_BAR,			// 该道具不在背包里不能放入快捷栏
	PROP_ALREADY_IN_ACTIVE_BAR,				// 该道具已经在快捷栏  
	PROP_CANNOT_USE_ENERGY_NO_ACTIVE,		//你尚未激活活力值，无法使用此物品
	PROP_USE_ADD_ENERGY_SUCCESS,			//你使用了一个活力丹，恢复15点活力！
	PROP_CANNOT_USE_ENERGY_IS_MAX,			//活力值已满，物品不能使用
	PROP_OBSERVER_IS_DESTORY,				//当前观察物品不存在
	PROP_CANNOT_USE_ONCOMBINPET,			//处于变身状态，不可使用道具

	//技能使用
	SKILL_NOT_USE = 2500,				//技能不能使用
	SKILL_MAGIC_CUT,					//被禁魔
	SKILL_MP_NOT_ENOUGH,				//法术值不够
	SKILL_COMMON_CD,					//公共冷却时间未到
	SKILL_CD,							//冷却时间未到
	SKILL_NOT_TARGET_ZONE,				//不是技能指定区域
	SKILL_NOT_WEAPON,					//没有释放技能的武器
	SKILL_NOT_WAITERPET,				//侍从不能被攻击
	SKILL_NOT_BEATABLE,					//无敌状态不能被攻击
	SKILL_NOT_TARGET,					//目标不正确
	//SKILL_NOT_EP,						//没有精力值
	SKILL_NOT_SP,						//怒气值不够
	SKILL_DEAD_CANT_USE,                //死亡不能使用技能
	SKILL_NOT_LEARN,                    //技能没有学习，不能使用
	SKILL_PROP_NOT_ENOUGH,              //技能所需的道具不足够
	SKILL_PROP_TYPE_NOT_MATCH,          //技能所需武器类型不匹配
	SKILL_NOT_USE_MAGIC,                //被禁魔
	SKILL_NOT_SUIT_NPC_ZONE,            //目标区域不正确
	SKILL_NOT_USE_TO_DEADMAN,           //技能对死亡状态不能使用
	SKILL_NOT_USE_TO_GHOSTMAN,          //技能对灵魂状态不能使用
	SKILL_NOT_USE_TO_INVULNERABILITY,   //技能对无敌状态不能使用
	SKILL_TARGET_TYPE_WRONG,            //目标类型不正确
	SKILL_ADD_WRONG,                    //添加技能失败
	OPEN_CTRLZ,							//开启挂机
	CLOSE_CTRLZ,						//关闭挂机
	SKILL_STATUS_NOT_USE,				//此状态不能使用
	SKILL_STATUS_RIDE,                   //状态是骑乘技能不能使用
	SKILL_LOGICSTATUS_INGAME,            //状态是小游戏技能不能使用
	SKILL_NOT_IN_RIDE,                   //次技能不允许骑乘状态使用
	SKILL_NOT_IN_CAR,                   //次技能不允许战车状态使用
	SKILL_NOT_IN_COMBINEPET,             //次技能不允许站宠合体状态使用
	SKILL_NOT_IN_STALL,                   //次技能不可以摆摊状态时候用
	SKILL_PROP_TYPE_NOT_ASSISTANT_MATCH,	//技能所需副手武器类型不匹配
	SKILL_PROP_CD,							//道具技能未冷却
	SKILL_SINGING_BREAK,					//吟唱技能被打断	by zhaoguoze
	OPEN_AUTO_OPRATING,							// 开启辅助系统
	CLOSE_AUTO_OPRATING,						// 关闭辅助系统
	AUTO_ATTACK_BY_POS_CAN_NOT_MOVE,			// 定点打怪中，无法进行移动操作
	OPEN_AUTO_PICK,								// 开启自动拾取
	CLOSE_AUTO_PICK,							// 关闭自动拾取
	SKILL_NOT_COMBINEPET,						// 没有战宠，不能使用
	SKILL_NOT_FELLOWPET,						// 没有珍兽，不能使用
	ATTACK_IN_SECURE_REGION,					// 安全区内不能攻击
	ATTACK_CAN_NOT_ATTACK_CHILD,				// 不能攻击受保护的小号玩家
	SKILL_OBJ_DISTANCE_OUT,						// 目标距离过远
	SKILL_NOT_IN_SCENE,						// 不能在本地图使用
	SKILL_USE_EP,								// 消耗的活力值 add by zhangjianli  2011-11-30
	ATTACK_LEVEL_CAN_NOT_ATTACK,				// 小号玩家不能进行PK add by zhangjianli 2012-02-01
	OPEN_AUTO_PICK_FAIL,						// 骑乘状态无法自动采集 add by zhangjianli 2012-2-23
	SKILL_NO_COMBAT_CAN_NOT_USE,				// 没有战宠无法施放（道士的万法合一技能）add by zhangjianli 2012-3-9
	SKILL_CAN_NOT_USE_THIS_RANGE,				// 该区域无法使用 add by zhangjianli 2012-3-27
	NO_ATTACK_HOMELAND_AREA,					// 不能攻击此区域内的该国玩家
	CANT_ATTACK_PROTECTED_CAR,					// 该镖车处于保护状态，无法攻击！（王城运镖镖车在50级及以下的受保护）
	SKILL_CANT_USE_NO_TEAM,						// 无队伍不能使用该技能 add by zhangjianli 2012-6-9
	SKILL_CAN_USE_IN_MYSELFSTATE,				// 技能只能在本国使用 add by zhangjianli 2012-6-9

	SKILL_LIFE_STOP=2560,               //生活技能被打断，魏小波添加，解决0000106问题
	OPEN_CTRLC=2590,					//crtl+c开始



	//聊天
	CHAT_NO_LONG = 2600,				//聊天内容过长
	CHAT_NO_KONG,						//聊天内容不能为空
	CHAT_NO_SELECT_PLAYER,				//没有选中聊天对象
	CHAT_NO_WORLD_MESSAGE,				//不到六十级不能在世界频道聊天
	CHAT_NO_TEAM_MESSAGE,				//没有组队，不能在组队频道聊天
	CHAT_NO_FAMILY_MESSAGE,				//没有家族，不能再家族频道聊天
	CHAT_NO_GANG_MESSAGE,				//没有帮会，不能在帮会频道聊天
	CHAT_NO_FRIEND_MESSAGE,			//没有好友，不能在好友频道聊天
	CHAT_NO_STATE_MESSAGE,				//等级不到30级，不能再国家频道聊天
	CHAT_AREA_LEVEL_MESSAGE,			//区域聊天等级不够
	CHAT_NO_TIME,						//您聊天过于频繁
	CHAT_GROUP_NAME_NO_LONG,			//聊天群名字过长
	CHAT_GROUP_NAME_NO_KONG,			//聊天群名字不能为空
	CHAT_GROUP_NAME_CONTAIN_ILLEGAL_CHAR,//聊天群名称包含非法字符
	CHAT_GROUP_NAME_HAVE,				 //聊天群名字已存在
	CHAT_GROUP_CREATE_FAILURE,			 //聊天群创建失败
	CHAT_GROUP_ADD_MEMBER_FAILURE,		 //添加成员失败
	CHAT_GROUP_CREATE_ACCEPT,			 //创建群成功
	CHAT_GROUP_BE_ADD_ACCEPT,			 //被添加成功
	CHAT_GROUP_JOIN_HAVE_GROUP,			 //您已经在此群中
	CHAT_GROUP_ISFULL,					 //该聊天群人数已满
	CHAT_GROUP_CAPTION_NO_ONLINE,		 //群主不在线
	CHAT_GROUP_JOIN_DENY,				 //请求被拒绝
	CHAT_GROUP_NOT_CAPTION,				 //您不是群主
	CHAT_GROUP_HAVE_GROUP,				 //您已经创建过一个群了
	CHAT_GROUP_HAVE_GROUP_MAX,			 //每个人最多可以加入五个群
	CHAT_GROUP_TARGET_GROUP_MAX,		 //对方已经有五个群了
	CHAT_NO_COLORWORLD_MESSAGE,          //等级不到六十级，不能在彩世频道聊天
	CHAT_BE_SET_NOSPEAK,				 //被设置禁言

	//财产保护
	PROPERTY_PROTECT_APPLY_SUCCESS = 2700,	//申请财产保护成功
	PROPERTY_PROTECT,                       //财产保护提示信息

	//快捷栏
	ACTIVE_BAR_PASSIVESKILL_NOT_DRAG=2800,  //被动技能不能拖动
	ACTIVE_BAR_TYPE_WRONG,					//拖动类型错误
	ACTIVE_BAR_REPLACE_WRONG,				//原有快捷栏错误
	ACTIVE_BAR_NO_RROPORSKILL_NOREPALCE,	//非道具和技能不能替换
	ACTIVE_BAR_NO_PROP_SHORCUT,				//不是道具快捷图标
	ACTIVE_BAR_NO_HAVE_SKILL,               //没有该技能
	ACTIVE_BAR_REMOVE_WRONG,                //移除错误

	//玩家属性
	ATTRIB_POINT_ZERO               =2900,	//属性点已清零
	ATTRIB_POINT_NOT_ENOUGH,                //没有属性点可分配
	ATTRIB_POINT_NOT_ADD,                   //没有分配属性点
	ATTRIB_POINT_NOT_ZERO,                  //所加属性点不能为0
	ATTRIB_POINT_NOT_SO_MUCH,               //没有这么多属性点可分配


	//宠物
	PET_INVITE_RID_TARGET_NOT_COM   =3000,  //当前骑乘状态不是普通状态
	PET_NOT_EXIST,                          //找不到宠物
	PET_CANT_COMBINE,                       //不能合体
	PET_COMBINE_TARGET_NOT_EXIST,           //合体目标不存在
	PET_MASTER_TEMPLATE_NOT,                //主人模板找不到
	PET_NOT_RID,							//当前状态不能上宠物
	PET_COMBIN_DISTANCE_OUT,				//超出合体最大距离
	PET_TILI_LOW,							//体力值低于40点不能骑乘
	PET_FELLOW_MAX_COUNT,	//玄兽数量达到上限
	PET_FELLOW_SUMMON,		//玄兽已召唤
	PET_FELLOW_FIGHTING,		//玄兽正在出战
	PET_FELLOW_FULLSTAR,		// 珍兽不能再强化了(冲星已满)
	PET_FELLOW_GOLD_NO_ENOUGH, //金币不足
	PET_FELLOW_LIFE_NO_ENOUGH,//寿命不足
	PET_FELLOW_LIFE_MAX,//寿命达到上限
	PET_FELLOW_SEAL, //玄兽已封印
	PET_FELLOW_RELEASE,//玄兽已放生
	PET_FELLOW_CALLBACK, //玄兽已收回
	PET_FELLOW_HAPPY_LOW, //快乐度低于20%，无法出战
	PET_FELLOW_BREEDERR_LEVEL, //等级不够，不可繁殖
	PET_FELLOW_BREEDERR_SEX, //性别不同，不可繁殖
	PET_FELLOW_BREEDERR_GROWTH, //二代珍兽，不可繁殖
	PET_FELLOW_BREEDERR_LIFE, //寿命太低，不可繁殖
	PET_FELLOW_EVOLUTION_SUCCEED, //强化成功
	PET_FELLOW_EVOLUTION_FAILED, //强化失败
	PET_FELLOW_EVOLUTION_NOGEM, //在玩家背包里没找到强化用的宝石
	PET_FELLOW_FEED_LEVEL_LOW,	//喂养的道具等级太低
	PET_FELLOW_FEED_HAPPY_FULL,	//当前快乐度满，不需要喂养
	PET_FELLOW_BREED_TYPE_DIFF, //珍兽类型不同，不同繁殖
	PET_FELLOW_EVOLUTION_GEMNUM_ZERO, //宝石数量为0
	PET_FELLOW_LESSTHAN_TAKELEVEL, //小于可携带等级
	PET_FELLOW_EGG_LESS_TAKELEVEL, //使用蛋时，小于携带等级
	PET_FELLOW_MASTER_LESS_FELLOWLEVEL, //召唤时，主人等级小于珍兽等级
	PET_FELLOW_NO_QUEST, //没有任务
	PET_FELLOW_HAVE_QUEST, //有任务
	PET_FELLOW_LEVEL_ERROR,//被邀请人等级不符
	PET_FELLOW_QUEST_COUNT,//被邀请人今日护镖次数大于4
	PET_FELLOW_STATE_ERROR,//被邀请人现在处于运镖或护镖状态，不能再被邀请
	PET_FELLOW_REFUSEAPPLY, //拒绝加入镖队的申请
	PET_FELLOW_REFUSEINVITE, //拒绝加入镖队的邀请
	PET_CAR_STATEID_ERROR,	// 国家ID不相同
	PET_CAR_PLAYER_PRISON,	//玩家处于囚禁状态，不能申请加入镖队
	PET_CAR_PASS_STEP_ONE,	 //镖车已过第一阶段
	PET_CAR_WAIT_APPLY,//等待XXX接受你的申请
	PET_CAR_WAIT_INVITE,//已邀请XXX加入镖队
	PET_CAR_DELETE_QUEST,//找不到镖车，删除任务
	PET_CAR_NO_FLY,//有运镖/护镖任务，不能传送
	PET_CAR_EXIT_CARLIST, //退出镖队
	PET_CAR_PLAYER_NO_FLY,//正在运镖或护镖，不能传送
	PET_CAR_DISCARD_QUEST_MAIN, //放弃运镖任务
	PET_CAR_DISCARD_QUEST_AUXI, //放弃护镖任务
	PET_CAR_ENTER_TEAM, //进入镖队
	PET_FELLOW_KICKPLAYER, //将XXX踢出镖队
	PET_FELLOW_REMIND_OVER, //提醒消息成功
	PET_CAR_ADD_FRIENDPOINT, //增加好友度10点
	PET_CAR_QUEST_FAILED,
	PET_CAR_REPEAT_INVITE, //重复邀请
	PET_RIDE_NO_EXIST,	//当前没有骑宠
	PET_RIDE_DISMOUNT, //请下马后再强化
	PET_RIDE_GEM_ERROR, //强化宝石不正确
	PET_RIDE_LEVEL_LOW, //低级马不能替换高级马
	PET_RIDE_LEVEL_EQUAL, //同等级马不能替换
	PET_RIDE_STATE_RID, //骑乘状态，不能添加骑宠
	PET_RIDE_SCENE_NO_ALLOW,	//当前场景不允许骑马
	PET_CAR_BEINVITERPLAYER_OFFLINE,	// 被邀请的玩家不在线
	PET_COMBAT_ONDEAD, //战宠已死
	PET_REFINERY_MAXNUM,				//一天只能炼化10只珍兽


	//效果
	EFFECT_CURSOR_READY_USE_PROP=3100,      //已经进入使用道具状态
	EFFECT_CURSOR_READY_POETAL,				//入口已经打开
	EFFECT_TYPE_IS_CANT_CANCAL,				//buff为不可移除效果

	//股票
	CLEARING_ADD_SUCCESS=3200,				//添加股票信息成功
	CLEARING_HAVE_GOLD_NOT_ENOUGH,			//账户金子不足
	CLEARING_HAVE_SILVER_NOT_ENOUGH,		//账户银子不足
	CLEARING_HAVE_NOTFIT_SELL,				//没有符合条件的卖单
	CLEARING_HAVE_NOTFIT_BUY,				//没有符合条件的买单
	CLEARING_BUY_SILVER_NOT_ENOUGH,			//账户中没有足够的银子购买该数量的金子, 请充值
	CLEARING_NOT_BUY_ENOUGH,				//没有买够, 系统为剩余数量的购买手数生成买单
	CLEARING_BUY_SUCCESS,					//已经购买成功
	CLEARING_BUY_GOLD_NOT_ENOUGH,			//账户中拥有的金子不足以满足买单的需要, 请充值
	CLEARING_NOT_SELL_ENOUGH,				//没有卖完, 系统为剩余数量的买入手数生成卖单
	CLEARING_SELL_SUCCESS,					//卖出成功
	CLEARING_DELETE_SUCCESS,				//撤单成功
	CLEARING_SOLD_OUT,						//卖家卖出成功
	CLEARING_BUY_GET,						//买家买入成功

	//场景
	SCENE_UNGROUND_TEAM = 3300,				//您不在组队中，无法进入此副本
	SCENE_UNGROUND_FAMILY,					//您不在家族中，无法进入此副本
	SCENE_UNGROUND_GANG,					//您不在帮会中，无法进入此副本
	SCENE_CAN_NOT_DEPART_PRISON,			//无法离开监狱

	//鲜花
	ROSE_NOT_NUMBER,						//鲜花数量不足，赠送失败
	ROSE_NOT_FAIL,							//鲜花赠送失败
	ROSE_SUCCESS,							//鲜花赠送成功
	ROSE_BANNER,							//鲜花横幅
	ROSE_NOT_QIANZHIHE,						//千纸鹤数量不足
	ROSE_SEND_ONLYMAN,						//只有男玩家可以赠送玫瑰
	ROSE_SEND_ONLYWOMAN,					//只有女玩家可以赠送千纸鹤
	ROSE_SEND_FAIL_FORBID_TIME,				//每日23:55-00:05无法赠送鲜花
	QIANZHIHE_SEND_FAIL_FORBID_TIME,		//每日23:55-00:05无法赠送千纸鹤

	//传送
	FLY_LEVEL_LIMIT = 3500,					//等级不足
	SUMMON_ACCEPTFAIL_DEAD,					//死亡时不能响应召唤
	SUMMON_ACCEPTFAIL_PRISON,				//监狱中不能响应召唤
	SUMMON_ACCEPTFAIL_INCAR,				//战车中不能响应召唤
	SUMMON_ACCEPTFAIL_MAPLEVEL,				//不满足地图等级
	SUMMON_ACCEPTFAIL_ESCORT,				//运镖状态不能响应召唤
	SUMMON_ACCEPTFAIL_INVALID,				//召唤已失效
	SUMMON_ACCEPTFAIL_TOSOON,				//请勿频繁传送
	SUMMON_ACCEPTFAIL_SCENENOACCEPT,		//当前场景不可接受召唤
	SUMMON_SEND_SUCCESS,					//召唤发送成功
	SUMMON_ACCEPTFAIL_STALL,				//摆摊状态不响应召唤	add by zhangjianli 2012-2-23
	FLY_FAMILYCAR_NO_FLY,					//在战车中不能传送
	FLY_LEVEL_CAR_MEMBER_LIMIT,				//战车中有乘员等级不足

    // 五行
    SYSTEM_WUXING_JIN = 3900,                //系统提示获取金属性
    SYSTEM_WUXING_MU,                       //系统提示获取木属性
    SYSTEM_WUXING_SHUI,                     //系统提示获取水属性
    SYSTEM_WUXING_HUO,                      //系统提示获取火属性
    SYSTEM_WUXING_TU,                       //系统提示获取土属性

	//活动
	CAMPAIGN_COUT_OUT=4000,					//活动次数限制
	CAMPAIGN_SIGNUP_SUCCESS,				//活动报名成功
	CAMPAIGN_SIGNUP_ALREADY,				//已经报名
	CAMPAIGN_BAGFULL_SENDBYMAIL,			//背包已满，道具通过邮件发送

	//经验
	EXPERIENCE_NOT_ENOUGH = 4500,			//经验不足
	EXPERIENCE_STORE_ISFULL,				//存储经验已满

	//元气值
	PNEUMA_NOT_ENOUGH = 4550,				//元气值不足

	ERROR_FACE_INCAR=4600,						//战车状态下不适用特殊聊天表情的系统消息
	SPACE_DATA_SAVE,							//空间页签保存好资料后发送系统消息

	//其他错误
	ERROR_OTHER_EXP_IS_ZERO =10000,          //NPC经验值为0
	ERROR_OTHER_NPC_MAXLIFE_LESSZERO,        //NPC生命值小于0
	ERROR_OTHER_BAG_UIPOS_WRONG,             //背包UI位置错误
	ERROR_OTHER_MONEY_CHANGE_WRONG,         //设置金钱失败
	ERROR_OTHER_BIND_MONEY_FULL,			//绑定的金钱已到上限
	ERROR_OTHER_NOTBIND_MONEY_FULL,			//不绑定的金钱已到上限
	ERROR_OTHER_CANT_GET_SCENE,              //得不到场景
	ERROR_OTHER_PID_IS_WRONG,                //系统错误，PID不一致
	ERROR_OTHER_BIRTH_ZONE_CANT_FIND,		 //找不到出生区
	ERROR_OTHER_COMPOSE_CHANCE_ZERO,		 //合成几率为0
	ERROR_GIFT_NOT_TIME,					 //未到领取礼包时间
	ERROR_CAMPAIGN_BAGISFULL,				 //活动背包已满
	ERROR_GIFT_TAKE_SUCCESS,				//领取礼包成功
	ERROR_GIFT_TAKE_RESET,					//礼包被重置
	ERROR_BIND_MONEY_ENOUGH,				//绑定金钱不足
	ERROR_NOTBIND_MONEY_ENOUGH,				//非绑定钱不足
	ERROR_UNSEEEQUIP,						//对方不允许查看装备
	ERROR_YEARWINE_OPEN,					//已开启百年陈酿 (跟脚本补齐) by zlm  2012.8.16
	ERROR_CDKEY_CONVERT_ONLYONE,			// 兑换码只能兑换一次
	ERROR_EVERYDAY_SELLMONEY_LIMITUP,		//达到每天出售银子上限

	//debug
	SCRIPT_LOAD_FAILED = 11000,				 //加载脚本失败
	SCRIPT_DEBUG_STR,						 //脚本调试字符串
	//通用类型
	ERROR_COMMON_STRING = 12000,

	//GM
	ERROR_GM_STRING = 13000,                // GM 喊话
	//元神相关
	ERROR_DiHunLevel_UpTo_MingHun = 30000,
	Soul_Error_SwitchToSame,
	Soul_Error_WaitForTime,
	Soul_Error_NotOpenDiHun,
	//封印相关
	ERROR_INSEAL_STATE = 30100,
	//排行榜
	ERROR_TOP_NOTRIGHTTIME = 30200,
	ERROR_TOP_REWARDED,
	ERROR_TOP_GAINREWARDBYMAIN,
	ERROR_TOP_GETMONEYBYBAGFULL,
	ERROR_TOP_GAINRMONEY,

	PRIVATE_ADDCHOUREN,

	ERROR_BORDER_TRANS_TIME,
	ERROR_BORDER_TRANS_STATUS,
	ERROR_BORDER_TRANS_FCAR,
	
	//--系统开关--
	SYSTEM_SWITCH_UNOPENED	= 30300,		//该功能暂未开放
	SYSTEM_SWITCH_CANNOT_USE,				//该功能无法使用
	SYSTEM_SWITCH_CLOSED,					//该功能已经关闭
};

enum	MessageBox_Type
{
	MessageBox_Type_Confirm						=1,			//确认提示框
	MessageBox_Type_Choose,									//确认取消提示框
	MessageBox_Type_Input,									//输入确认框

	//登录界面
	MessageBox_Type_USER_CHECK_FAIL				= 10,		//账户或密码错误
	MessageBox_Type_USER_LOGON_FAIL,						//账号登陆出现意外错误
	MessageBox_Type_USER_PSW_BLANK,							//密码不能为空
	MessageBox_Type_Player_Create_Count_Limit,				//无法创建角色已经到最大值
	MessageBox_Type_Player_Create_Name_Repeat,				//角色名已存在
	MessageBox_Type_Not_Find_Server,						//没有找到角色所在的服务器
	MessageBox_Type_Not_Delete_Player_FamilyPower,			//有家族职务 不能删除
	MessageBox_Type_Not_Delete_Player_Mail,					//有邮件不能删除
	MessageBox_Type_Server_Not_Open,						//服务器未开放
	MessageBox_Type_Cant_Delete_HighLev_Player,				//不能删除高级玩家
	MessageBox_Type_DeleteSelRole,							//是否删除选定角色
	MessageBox_Type_NotRole,								//此帐号不存在角色
	MessageBox_Type_Cant_Delete_HaveFamily,		//不能删除有家族职务的角色
	MessageBox_Type_Cant_Delete_HaveMail_Player,			//不能删除有邮件的角色
	MessageBox_Type_User_Already_Logon,						//账号已登录
	MessageBox_Type_Disconnect_Server,						//已与服务器断开连接
	MessageBox_Type_Player_Create_Name_Error,				//名字非法
	MessageBox_Type_Version_Error,						    //版本错误提示
	MessageBox_Type_User_Check_NotActive,                   //帐号未激活
	MessageBox_Type_User_Check_StopTest,                    //产品停止测试
	MessageBox_Type_User_NOT_REG,                    //账号未注册
	MessageBox_Type_Connect_World_Error,				//连接游戏世界失败
	MessageBox_Type_Load_Player_Error,				//加载角色信息失败
	MessageBox_Type_Connect_Success,					//连接成功
	MessageBox_Type_Loading_Player,						//正在加载角色数据
	MessageBox_Type_Login_Connect_Error,			//连接服务器失败
	MessageBox_Type_PropertyProtect,                //财产保护
	MessageBox_Type_Cant_Delete_HaveGay,		    //不能删除结拜的角色
	MessageBox_Type_Cant_Delete_HaveConsort,		//不能删除夫妻的角色
	MessageBox_Type_Cant_Delete_StatePower_Player,	//不能删除国家官职的角色
	MessageBox_Type_Player_Login_DataServer_Not_Open,		//没dataserver
	MessageBox_Type_Player_Login_Scene_Not_Open,	//没场景
	MessageBox_Type_Player_Login_Role_Be_Freezed,	//角色被冻结
	MessageBox_Type_Delete_TwoTwice_Player,			//无其他
	MessageBox_Type_Player_Login_Sucess,


	//交易
	MessageBox_Type_Exchange_Player			    = 50,		//玩家交易
	MessageBox_Type_Delte_Prop,								//销毁道具
	MessageBox_Type_Splite_Prop,							//拆分道具
	MessageBox_Type_Bind_Prop,								//绑定道具
	MessageBox_Type_Exchange_Choose,						//接受或拒绝交易的窗口
	MessageBox_Type_Exchange_Start,							//开始交易
	MessageBox_Type_StallCheck_Start,						//打开其他玩家摊位信息

	//以前在个人关系中嵌套的杂七杂八
	MessageBox_Type_Confirmation_Code_Valid	  =80,
	MessageBox_Type_Confirmation_Input,
	MessageBox_Tpye_NotOnLine,
	MessageBox_Type_Storage_Experience_Toplimit,
	MessageBox_Type_Fellow_Storage_Exp_Toplimit,			// 珍兽经验储存到达上限 add by zhangjianli 2012-1-3
	MessageBox_Type_Confirmation_Code_Valid_1,              // 您已经兑换过该类的激活码
	MessageBox_Type_CDkeyAward,								// 兑换码中奖 ---> 恭喜您领到5Q币,谢谢您的参与签到领到大奖活动!
	MessageBox_Type_CDKNotAward,							// 兑换码没中奖---> 很遗憾您没有领到外星人,谢谢您的参与签到领到大奖活动!

	//个人关系
	//好友
	MessageBox_Type_Request_AddFriend			= 100,		//请求添加好友
	//黑名单
	MessageBox_Type_Request_AddFriendToBlock,				//不能将好友加入黑名单。
	//夫妻
	MessageBox_Type_Request_AddConsort,						//你确定要与XXX结为夫妻，百年好合么？
	MessageBox_Type_Request_RemoveConsort,					//离婚需消耗银子500两，确定与XXXXX（配偶名字）劳燕分飞吗？
	MessageBox_Type_Remove_Consort,							//你与XXX（配偶名字）劳燕分飞。
	MessageBox_Type_Consort_BeRemoveConsort,				//XXX（配偶名字）选择与你劳燕分飞。
	MessageBox_Type_Consort_WaitWoman,						//请耐心等待新娘接受你的请求……
	MessageBox_Type_Consort_SelfRefuse,						//你拒绝了对方的求婚。
	MessageBox_Type_Consort_SelfRefused,					//对方拒绝了你的求婚。
	MessageBox_Type_Consort_TeamChange,						//组队人员变化，结婚失败。
	MessageBox_Type_Consort_StateIDDifferent,				//新郎新娘必须国籍相同。
	MessageBox_Type_Consort_MoneyLess500,					//新郎背包中的银子不足。
	MessageBox_Type_Consort_TeamMemberNotOnLine,			//队内成员必须全部在线。
	MessageBox_Type_Consort_NotInExplorer,					//队内成员全部在月老周围
	MessageBox_Type_Consort_HadConsort,						//两个玩家必须全部未婚。
	MessageBox_Type_Self_MoneyLess500,						//你的银子不足
	MessageBox_Type_Consort_TeamDismiss,					//队伍解散，结婚失败
	MessageBox_Type_Consort_NotInTeam,						//请与心仪的对象组队并在同屏内
	//结拜
	MessageBox_Type_Request_AddSworn,						//你确定和队伍中的朋友义结金兰吗？
	MessageBox_Type_Sworn_RemoveSworn,						//朋友一时，兄弟一世，你确定要和兄弟/姐妹解除结拜吗？
	MessageBox_Type_Sworn_SomebodyCancel,					//有兄弟/姐妹还未考虑好，结拜未能完成！
	MessageBox_Type_Sworn_WaitOther,						//正在等待其他兄弟/姐妹确定……
	MessageBox_Type_Sworn_WaitCaption,						//队长正为咱们取个响亮的名头，请稍后…
	MessageBox_Type_Sworn_NoKeyworld,						//你有兄弟/姐妹“X”人，你的结拜称号中需包含“X”字。
	MessageBox_Type_Sworn_MoreKeyworld,						//称号中只能有一个“X”字。
	MessageBox_Type_Sworn_LengthError,						//称号必须在3-5个字之间。
	MessageBox_Type_Sworn_TitleError,						//称号不合法。
	MessageBox_Type_Sworn_TitleUsed,						//与已有结拜称号重复
	MessageBox_Type_Sworn_TeamInfoChange,					//队伍信息发生变化，结拜失败
	MessageBox_Type_Sworn_TeamMemberNotOnLine,				//队内成员必须全部在线。
	MessageBox_Type_Sworn_NotInExplorer,					//队内有玩家不在同屏列表中，结拜失败。
	MessageBox_Type_Sworn_TeamDismiss,						//队伍解散，结拜失败
	MessageBox_Type_Sworn_StateChange,						//队内有玩家不是本国国籍，结拜失败。

	//组队
	MessageBox_Type_Add_Team					= 150,		//邀请组队的申请
	MessageBox_Type_Caption_Add,							//
	MessageBox_Type_ApplyJoinTeam,
	//骑宠
	MessageBox_Type_Horse_Replace		= 160, //马匹替换
	//家族
	MessageBox_Type_Add_Family					= 200,		//添加族员
	MessageBox_Type_By_Invert_To_Family,       				//被家族邀请
	MessageBox_Type_Invert_To_Family,						//申请加入家族
	MessageBox_Type_Delete_Family,             				//确认移除族员
	MessageBox_Type_Title_Change_To_Family,    				//家族权限变更
	MessageBox_Type_Teleport_To_Family,        				//传送至族员处
	MessageBox_Type_Summon_From_Family,        				//召唤族员
	MessageBox_Type_Summon_All_From_Fmaily,    				//召唤全体族员
	MessageBox_Type_By_Summon_To_Family, 					//被召唤确认
	MessageBox_Type_Quit_Family,         					//退出家族
	MessageBox_Type_Change_Nick_Name_For_Family,			//改变称号
	MessageBox_Type_Modify_Notice_For_Family,				//家族公告修改
	MessageBox_Type_Destory_Family,							//解散家族
	MessageBox_Type_Apply_Family_Scene,						//申请家族庄园扣银子
	MessageBox_Type_Create_Family,      					//创建家族时所需名称与密码
	MessageBox_Type_Delete_Arm,        						//确认删除家族装备
	MessageBox_Type_Delete_Family_Skill,   					//确认遗忘家族技能
	MessageBox_Type_ReturnFamilyCredit_Choose,				//返还家族贡献度
	MessageBox_Type_BagNoSpace,								//背包中空位不足
	MessageBox_Type_ReturnFamilyCredit_Success,				//家族贡献度返还成功
	MessageBox_Type_FamilyCaptionRequestPKBoss,				//族长申请一起PK庄园Boss
	MessageBox_Type_FamilyAddMoney,							//增加家族资金
	MessageBox_Type_InputMoneyIsZero,						//输入金额为0
	MessageBox_Type_BagNoMoney,								//背包中银子不足
	MessageBox_Type_FamilyAddMoneySuccess,					//成功捐献家族资金
	MessageBox_Type_RequestFamilySceneSuccess,				//恭喜你申请家族地图成功
	MessageBox_Type_FamilyNameRepeat,						//名称与现有家族名称重复，请尝试其它名称
	MessageBox_Type_CreateFamilySuccess,					//恭喜您创建家族成功
	MessageBox_Type_NoPowerRecruitMember,					//只有族长和副族长有权招收族员
	MessageBox_Type_OnlySameStateCanInFamily,				//只能邀请本国玩家加入家族
	MessageBox_Type_NotEnoughLevel,							//对方等级不到20级
	MessageBox_Type_AlreadyInFamily,						//对方已有家族
	MessageBox_Type_IsFull,									//本家族人数已满
	MessageBox_Type_NotEnoughTime,							//24小时后才能再次加入家族
	MessageBox_Tpye_BeFireOut,								//你被族长开除出族
	MessageBox_Tpye_FireMemberSuccess,						//你已将XX开除出族
	MessageBox_Tpye_CaptionQuitFamily,						//族长退出家族将导致家族永久解散，确认要退出当前家族吗?
	MessageBox_Tpye_BeAppointAssitant,						//族长将你任命为家族副族长
	MessageBox_Type_OfflineDismissFamily,					//x日x点x时,族长解散了您所在的家族
	MessageBox_Type_OfflineBecomeCaption,					//将家族职位转移给你
	MessageBox_Tpye_FreeZhiwu,								//族长解除了您的职务
	MessageBox_Tpye_AppointFood,							//族长将您任命为食神
	MessageBox_Tpye_ChangeCaptionSuccess,					//移交族长成功
	MessageBox_Type_FamilyAlreadyDismiss,					//此家族已解散
	MessageBox_Type_FamilyAlreadyHasAssistant,				//一个家族只能有一个副族长，请先解除现任副族长
	MessageBox_Type_FamilyAlreadyHasHeadship,				//选中玩家当前已有其他官职，请先解除其现任职位
	MessageBox_Type_FamilyNameError,						//家族名称不合法
	MessageBox_Type_ExitFamilySuccess,						//退出家族成功，24小时后才可再次加入家族
	MessageBox_Type_AppointSuccess,							//任命成功

	//家族战车
	MessageBox_Type_InviteToFCar,								//邀请进入战车

	//帮会
	MessageBox_Type_Add_Family_To_Guild			= 250,		//添加家族
	MessageBox_Type_Apply_Gang_Scene,						//申请帮会庄园
	MessageBox_Type_By_Invert_To_Guild,      				//被帮会邀请提示
	MessageBox_Type_Delete_Family_To_Guild,  				//移除家族
	MessageBox_Type_Title_Change_To_Guild,   				//帮会权限变更
	MessageBox_Type_Teleport_To_Guild,       				//传送至帮众处
	MessageBox_Type_Summon_From_Guild,       				//召唤帮众
	MessageBox_Type_Summon_All_From_Guild,   				//召唤全体族长
	MessageBox_Type_By_Summon_To_Guild,      				//被召唤确认
	MessageBox_Type_Quit_Guild,              				//退出帮会
	MessageBox_Type_Change_Nick_Name_For_Guild,				//改变称号
	MessageBox_Type_Modify_Notice_For_Guild,   				//帮会公告修改
	MessageBox_Type_Destory_Guild,             				//解散帮会
	MessageBox_Type_Create_Guild,         					//创建帮会时所需名称与密码
	MessageBox_Type_Modify_Notice_For_Country,				//国家公告修改
	MessageBox_Type_Title_Change_To_Country,  				//职务任命
	MessageBox_Type_GangNameError,							//帮会名称不合法
	MessageBox_Type_GangNameRepeat,							//名称与现有帮会名称重复，请尝试其他名称。
	MessageBox_Type_BagNoHeroJuYiLin,						//背包中没有英雄聚义令
	MessageBox_Type_CreateGangSuccess,						//恭喜你创建帮会成功
	MessageBox_Type_NotFamilyCaption,						//不是家族族长
	MessageBox_Type_GangNotSameState,						//只能邀请本国玩家加入帮会
	MessageBox_Type_GangNoRecuritPower,						//只有帮主或副帮主有权招收族员
	MessageBox_Type_AlreadyInGang,							//该玩家已有帮会
	MessageBox_Type_GangIsFull,								//本帮会人数已满
	MessageBox_Type_LeaveGangTimeLime,						//24小时后才能再次加入帮会
	MessageBox_Type_FamilyNotExist,							//该家族不存在
	MessageBox_Type_FamilyCaptionNotOnline,					//该家族族长不在线
	MessageBox_Type_GangNotCommonMember,					//该玩家已有其他帮会职务
	MessageBox_Type_GangSetCaptionTimeLimit,				//帮主24小时内只能转让一次
	MessageBox_Type_GangCaptionNotFamilyCaption,			//该玩家不是族长，帮主只能凡族长担任
	MessageBox_Type_SureSetGangCaption,						//确认转让帮主
	MessageBox_Type_SetGangCaptionSuccess,					//移交族长成功
	MessageBox_Type_BecomeGangCaption,						//“XXXX（转移者名称）已将帮主职位转移给你。该消息发布于XX时XX分。
	MessageBox_Type_GangAlreadyHasAssistant,				//一个帮会只能有一个副帮主，请先解除现任副帮主
	MessageBox_Type_NotCommonGangMember,					//该玩家当前已有其他帮会官职，请先解除其现任职位。
	MessageBox_Type_GangAssistantNotFamilyCaption,			//该玩家不是族长，副帮主只能由族长担任。
	MessageBox_Type_BecomeGangAssistant,					//帮主已任命你为帮会副帮主。该消息发布于XX时XX分
	MessageBox_Type_SetToCommonMemberSuccess,				//解除任命成功
	MessageBox_Type_BecomeCangCommonMember,					//帮主解除了你的帮会职务，该消息发布于..
	MessageBox_Type_NoGangZhiWu,							//该玩家没有帮会职位
	MessageBox_Type_GangHasDismissed,						//帮主解散了你所在的帮会，24小时后你可重新加入帮会。\n该消息发布于XX时XX分
	MessageBox_Type_CaptionFireFamily,						//帮主已将XXXX家族开除出帮
	MessageBox_Type_GangRemoveFamily,						//你的家族被帮主开除出帮。该消息发布于XX时XX分
	MessageBox_Type_SetupNoAllowAddToGang,					//该玩家“允许加入帮会”设置未开启
	MessageBox_Type_GangNameTooLong,
	MessageBox_Type_GangNameLessThen4,
	MessageBox_Type_GangMemberDismissFamily,
	MessageBox_Type_GangNotFind,
	MessageBox_Type_YouHasAlreadyInGang,
	//国家
	MessageBox_Type_State_Summon				= 300,		//国家召唤
	MessageBox_Type_State_King_NoSpeak,						//国王禁言
	MessageBox_Type_State_King_Prisoner,					//国王监狱
	MessageBox_Type_State_Add_UnionState,					//添加盟国
	MessageBox_Type_State_Remove_UnionState,				//解除盟国
	MessageBox_Type_State_Request_AddUnionState,			//响应添加盟国
	MessageBox_Type_State_Request_RemoveUnionState,			//响应移除盟国
	MessageBox_Type_SetOfficalNext,							//国家大臣添加从属官
	MessageBox_Type_AcceptSetOfficalNext,
	MessageBox_Type_NotEnoughLevelToPower,					//该玩家等级不足60级，无法担任重要职位！
	MessageBox_Type_AlreadyHasPower,						//该玩家已有其它职位了
	MessageBox_Type_AppointRequest,
	MessageBox_Type_AppointFailedPowerExist,				//任命失败，已经有人担任此官职了！
	MessageBox_Type_DenyAppointPower,						//xxxx拒绝就任该职位
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
	//邮件
	MessageBox_Type_Add_Mail					= 350,      //有新的邮件
	MessageBox_Type_User_Not_Find_Mail,						//收件人不存在
	//Auction
	MessageBox_Type_User_Not_Find_Auction,                  //该拍卖信息已不存在
	MessageBox_Type_User_Not_Bid_Auction,

	//任务
	MessageBox_Type_Quest_No_Select_Prize_Prop  = 400,		//没有选择任务奖励道具
	MessageBox_Type_Quest_NumisOut,							//任务数量限制
	MessageBox_Type_Car_LessMoney,							//接镖金钱不够
	MessageBox_Type_Quest_Delete,							//确认删除任务
	MessageBox_Type_Quest_Accept,							//获得任务
	MessageBox_Type_Quest_Finish,							//活动结算
	MessageBox_Type_TYJY_Hint,								//桃园结义提示
	MessageBox_Type_Map_FamilyChallenge,					//已在家族争夺战地图中
	MessageBox_Type_Map_GangFight,							//已在帮会夺城战地图中

	//战斗系统
	MessageBox_Type_Riding_Together				= 450,      //邀请共乘坐骑
	MessageBox_Type_Not_Enough_Time_Releasa_Prison,			//还没到出狱时间

	//活动
	MessageBox_Type_Campaign_Invite				= 500,      //参加活动
	MessageBox_Type_Question_Invite,						//参加答题
	MessageBox_Type_Question_HadMiss,                       //答题已错过
	MessageBox_Type_Question_HadOver,                       //答题已结束 Add by ChenXY
	MessageBox_Type_Question_WiseOver,						//智者答题结算
	MessageBox_Type_Question_CompeOver,						//答题竞赛结算
	MessageBox_Type_JunShi_Action,							//军事活动
	MessageBox_Type_Action_Summon,							//活动召唤
	MessageBox_Type_Action_FamilyJuYiStart,					//发起家族聚义
	MessageBox_Type_Action_Drink_1,							//请客喝酒（新丰酒）
	MessageBox_Type_Action_Drink_2,							//请客喝酒（状元红）
	MessageBox_Type_Action_Drink_3,							//请客喝酒（杜康）
	MessageBox_Type_Invite_CarList,							//邀请加入镖队
	MessageBox_Type_Apply_CarList,								//申请加入镖队
	MessageBox_Type_Warning_FarFrom_Car,				//警告，远离镖车  (废弃)
	MessageBox_Type_BeKick_ProtectorList,				//被踢出镖队
	MessageBox_Type_Exit_ProtectorList,					//退出镖队
	MessageBox_Type_ProtectorList_Full,						//镖队人数满
	MessageBox_Type_MsgBox_FarFrom_Car,				//远离镖车，弹出MsgBox
	MessageBox_Type_ExchangeGoodsAndGold,				// 王城运镖 兑换金条和货物
	MessageBox_Type_GoodsExchangedInform,				// 王城运镖 货物被兑换通知
	MessageBox_Type_GoldExchangedInform,				// 王城运镖 金条被兑换通知
	MessageBox_Type_EscortError,				// 王城运镖 金条被兑换通知
	MessageBox_Type_TaoYuanJieYiMain,
	MessageBox_Type_TaoYuanJieYiVice,
	MessageBox_Type_TaoYuanJieYiProp,
	MessageBox_Type_InCar_Area,             // 在镖车范围内
	MessageBox_Type_CarryCar_Over_Step,     // 运镖完成其中一步
	MessageBox_Type_CarryCar_Over_Final,    // 运镖最终完成
	MessageBox_Type_CarryCar_Over_Final2,   //护镖最终完成
	MessageBox_Type_CarryCar_Over_Final3,
	MessageBox_Type_Quest_WrongAswer,		//答题任务答案错误
	MessageBox_Type_WorldQuestion_HadJoin,  //已经参加过
	MessageBox_Type_BuyPresentSuccess, //购买国战礼包成功
	//聊天
	MessageBox_Type_Invert_To_Group				= 550,		//申请加入群
	MessageBox_Type_Apply_Add_Group,
	MessageBox_Type_EWorldMsg_Choose,
	MessageBox_Tpye_EColorfulWorld_Chose,

	//家族补充
	MessageBox_Type_AlreadyHasFooder            = 600,		//一个家族只能有一个食神，请先解除现任食神
	MessageBox_Type_FamilyBecomeCaption,					//族长xx已将家族族长职位转移给你
	MessageBox_Type_PkFamilyBigThiefFailed,					//挑战“庄园大盗”超时，申请家族庄园失败
	MessageBox_Type_PKBossRequest,							//PK家族Boss请求
	MessageBox_Type_NoHeadship,								//该玩家没有官职
	MessageBox_Type_CannotFireSelf,							//不能开除自己出族
	MessageBox_Type_ChangeCaptionTimeLimit,					//家族族长24小时内只能转让一次
	MessageBox_Type_FamilyHaveBeen,							//你目前已有家族
	MessageBox_Type_CanOnlyJoinSameStateFamily,				//只能加入本国家族
	MessageBox_Tpye_OfflineBeFireOut,						// 离线被开除出族
	MessageBox_Tpye_OfflineFreeZhiwu,						//离线解除职务
	MessageBox_Tpye_OfflineBeAppointAssitant,				//离线任命副族长
	MessageBox_Tpye_OfflineAppointFood,						//离线任命食神
	MessageBox_Type_JoinFamilyNotEnoughLevel,					//20级才可加入家族
	MessageBox_Type_JoinFamilyNumLimitOnce,					//同一时间只能申请10个家族
	MessageBox_Type_JoinFamilyAlredy,						//你已经有家族了，不可再申请
	MessageBox_Type_JoinFamilyWait,							//你向此家族提交的申请正在等待处理
	MessageBox_Type_TargetFamilyIsFull,						//目标家族人数已满
	MessageBox_Type_TargetFamilyApplyJoinRecordFull,		//	目标家族待批准队列已达上限
	MessageBox_Type_NotOnlineJoinFamilyFaild,				//目标玩家不在线，添加失败
	MessageBox_Type_NotSameStateJoinFamilyFaild,			//只能邀请本国玩家加入家族，添加失败
	MessageBox_Type_JoinFamilyTimeLimit,					//对方在x小时x分后才能再次加入家族，添加失败
	MessageBox_Type_FamilyIsFullJoinFamilyFaild,			//本家族人数已满，添加失败
	MessageBox_Type_ApplyJoinFamilyTimeLimit,				//你据上次退出家族时间未超过24个小时，请在X小时X分后再申请
	MessageBox_Type_TargetHasFamilyJoinFamilyFaild,			//对方已有家族，添加失败
	MessageBox_Type_UpgradeFamilyBuildNotCaption,			//只有族长可以升级家族建
	MessageBox_Type_CannotUpgradeMoreBuidingSameTime,		//同一时只能升级一座家族建筑
	MessageBox_Type_QiantiBuildingLevelNotEnough,			//前提建筑等级不足
	MessageBox_Type_NotEnoughMoneyInFamily,					//家族资金不足
	MessageBox_Type_AddOverFamilyMaxMoney,
	MessageBox_Type_QueryFamilyBuilding,
	MessageBox_Type_SummonFamilyMemberTimeLimit,
	MessageBox_Type_FamilyNameLessThen4,					//家族名称长度不得少于2个汉字(或4个字母)
	MessageBox_Type_FamilyAutoDismiss,
	MessageBox_Type_NoUpgradeFamilyBuilding,
	MessageBox_Tpye_JoinListNotVoid,						//待批准进入家族的玩家列表非空
	MessageBox_Type_OnlyCaptionSetRecruit,					//只有族长才能设置家族招募方式
	MessageBox_Type_RecruitIsOperate,						//当前家族招募方式已为手动招募
	MessageBox_Type_RecruitIsRobotize,						//当前家族招募方式已为自动招募
	MessageBox_Type_RecruitSetSucceed,						//招募方式设置成功
	MessageBox_Type_CreateFamilyFailedAsBagFull,			//你的背包已满，无法获得奖励，请清理背包后再尝试创建家族

	//献花
	MessageBox_Type_SendFlowerToFriend			= 650,
	MessageBox_Type_SendFlower,
	MessageBox_Type_AnonymousSendFlower,
	//换服 提示
	MessageBox_Type_TargetServerIsFull          = 700,      //目标GameServer满员
	//防沉迷
	MessageBox_Type_WallowStatePre60			= 750,      //防沉迷1 小时
	MessageBox_Type_WallowStatePre120,					    //防沉迷2 小时
	MessageBox_Type_WallowStatePre170,						//防沉迷3 小时
	MessageBox_Type_WallowLoginMsg,						    //防沉迷

	MessageBox_Type_Map_Pos_Invalid				= 790,		//传送坐标无效 add by zhangjianli 2012-2-29
	MessageBox_Type_Map_TianChiLing_Trans,					//天池领传送师 add by zhangjianli 2012-7-16


	MessageBox_Type_MoneyNoEnough = 800,					//金币不足
	MessageBox_Type_LevelNotEnough,
	MessageBox_Type_ExitGangSuccess,
	MessageBox_Type_KingCannotDismissGang,
	MessageBox_Type_ChangeFamilyCreditSuccess,
	MessageBox_Type_PropCanOnlyUseInSelfState,

	MessageBox_Type_HonourChangeExp,

	//帮会补充
	MessageBox_Type_Gang_FamilyNotSameState		= 850,		//只能邀请本国家族加入帮会
	MessageBox_Type_Gang_NotOnline,							//目标玩家不在线

	MessageBox_Type_Null,
	MessageBox_Type_InviterOffline,

	//开关对话框
	MessageBox_Type_Switch					= 900,			//--开关提示--

	MessageBox_Type_Prop_Add_Energy			= 910,			//--使用活力丹增加活力值--
};

enum Dialog_Switch_Content		// 开关对话框内容
{
	DIALOG_SWITCH_UNOPENED,		//该功能尚未开放
	DIALOG_SWITCH_CANNOT_USE,	//该功能无法使用
	DIALOG_SWITCH_CLOSED,		//该功能已经关闭
};

enum RollNewCommunity_Type
{
	RollNewCommunity_Type_Invalid				=-1,
	RollNewCommunity_Type_Person				=0,	//个人
	RollNewCommunity_Type_Team,						//队伍
	RollNewCommunity_Type_Family,					//家族
	RollNewCommunity_Type_Gang,						//帮会
	RollNewCommunity_Type_State,					//国家
	RollNewCommunity_Type_World,					//世界
	RollNewCommunity_Type_Scene,					//场景
	RollNewCommunity_Type_StateOffical,				//国家所有官员
};

enum RollNew_Type
{
	//任务相关
	RollNew_Type_Queset_Accept					=1,				//接受任务
	RollNew_Type_Queset_TargetCount,							//任务计数
	RollNew_Type_Queset_CompleteTarget,							//任务达成
	RollNew_Type_Queset_CompleteQuest,							//提交任务
	RollNew_Type_Queset_QuestCountOut,							//任务列表已满
	RollNew_Type_Queset_ProtectedOver,							//护送目标过远
	RollNew_Type_Queset_QuestFaild,								//任务失败
	RollNew_Type_Queset_TimeOver,								//任务时间到
	RollNew_Type_Queset_ShengWanglimit,							//声望不足
	RollNew_Type_Queset_Abandon,								//放弃任务
	RollNew_Type_Queset_PrizeRage,								//任务奖励忠义值
	//系统相关
	RollNew_Type_ChangeScene					=1000,			//换场景
	RollNew_Type_InZone,										//进入区域
	RollNew_Type_LevelLimit,									//等级不足
	RollNew_Type_MoneyLimit,									//金钱不足

	//活动用
	RollNew_Type_Campaign						=2000,			//活动电视
	RollNew_Type_CarAlarm,										//镖车警戒
	RollNew_Type_InCarAlarm,									//进入警戒
	RollNew_Type_OutCarAlarm,									//出警戒
	RollNew_Type_TickOutByAlarm,								//镖车在警戒状态中，不能进入


};

enum Dialog
{
	Dialog_CarMessage				=1,				//同意救镖后的界面
	Dialog_CarQuestion,								//运镖奇遇答题感叹号界面
	Dialog_ZhadanrenSkill,							//炸弹人技能打开界面
	Dialog_LionBag,									//舞狮背包界面
	Dialog_CarBag,									//运镖背包界面
};


enum ImportMsgID
{
	IM_Invalid = -1,
	//大名府运镖
	IM_Start_YunBiao,   // 好友 [315"..name.."] 正在进行运镖，赶快去加入!
	IM_Warning_Far,      // 远离镖车
	IM_Invite_Player_To_CarPet, //邀请玩家加入护镖
	IM_FarFrom_CarPet, //离目标过远
	IM_StateLeaderBeAttacked,   //国家官职被攻击
	IM_StateRuleDown,			//国王统冶力下降
};

const int PayServerErrorID		= - 1000;

//计费系统 返回标识  由于 数量过多 先添加这么多, 碰到了在加 by zlm 2012.4.11
enum EPayServerReturnFlag
{
	PayServer_ReturnResult_OK			= 1000,				//执行成功
	PayServer_ReturnResult_Fail,							//执行失败
	PayServer_ReturnResult_ParamError,						//参数错误
	
	PayServer_ReturnResult_AccountNumberExist = 1101,				//帐号在会员库中已存在
	PayServer_ReturnResult_AccountNumberNoExist,			//帐号在会员库中不存在
	PayServer_ReturnResult_AccountNumber_ProductExits,		//帐号在产品库中已存在
	PayServer_ReturnResult_AccountNumber_ProductNoExits,	//帐号在产品库中已存在

	PayServer_ReturnResult_AccountIntegral_NotEnough = 1401,// 帐号积分不足
	PayServer_ReturnResult_AccountIntegral_Enough,			// 帐号积分充足
	PayServer_ReturnResult_AccountRemaining_NotEnough,		// 帐号余额不足
	PayServer_ReturnResult_AccountRemaining_Enough,			// 帐号余额充足
	PayServer_ReturnResult_AccountExtPoint_NotEnough,		// 帐号扩展点不足
	PayServer_ReturnResult_AccountExtPoint_Enough,			// 帐号扩展点充足
	PayServer_ReturnResult_AccountDragonCoin_NotEnough,		// 帐号龙币不足
	PayServer_ReturnResult_AccountDragonCoin_Enough,		// 帐号龙币充足

	PayServer_ReturnResult_OrderIDRepeate	= 1501,			//订单号(流水号重复,  用于Log输出)
	
	PayServer_ReturnResult_GoodsCardNotExist = 1601,		// 物品卡不存在
	PayServer_ReturnResult_GoodsCardOutOfDate = 1602,		// 物品卡已过期
	PayServer_ReturnResult_GoodsCardUsed = 1603,			// 物品卡已使用
};