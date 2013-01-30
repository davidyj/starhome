#ifndef _PAYSYSTEM_H_
#define _PAYSYSTEM_H_

#include "CommData.h"
#include "UtlMap.h"
#include "PacketDefineHead.h"
#include "MemoryPoolDef.h"
#ifdef _DATASERVER_
#include "DataServerMgr.h"
#endif

#define  PAYSYSTEM_EXPSTR1_LEN		128
#define  PAYSYSTEM_EXPSTR2_LEN		256
#define  PAYSYSTEM_EXPSTR3_LEN		500
//////////////////////////////////////////////////////////////////////////

/////////////////////////////////////
// 支付系统 购买服务备注名称 begin
#define	 ORDINARYDRIVER					"普通车夫"
#define	 CROSS_BORDER_TRANSMISSION		"跨国传送"
#define	 PETUPSTAR						"宠物升星"
#define	 PETSKILL_METAMORPHOSIS			"宠物技能幻化"
#define	 PET_REBIRTH					"宠物重生"
#define	 MOUNTSTOSTRENGTHEN				"坐骑强化"
#define	 CREATEFAMILY					"家族创建"
#define	 RAMILY_DONATED					"家族捐献"
#define	 MARRIAGECOSTS					"结婚费用"
#define  DIVORCECOSTS					"离婚费用"
#define	 WARCAR_BUILD					"战车打造"
#define  WARCAR_REPAIR                  "战车修理"
#define  SKILL_LEAN						"技能学习"
#define  RELIVE_INSITU					"原地复活"
#define	 RELIVE_FULLSTATUS				"满状态复活"
#define  WORLDCHAT						"世界聊天"
#define  COLOR_WORLD_CHAT				"彩世聊天"
#define  FIX_POSTAGE					"固定邮费"
#define  GOLDCOIN_MAIL					"金币邮件"
#define	 EQUIP_REPAIRCOSTS				"装备修理"
#define	 EQUIP_SIGN						"装备签名"
#define	 EQUIP_BIND						"装备绑定"
#define	 EQUIP_REPEATEBIND				"装备重新绑定"
#define	 EQUIP_ADDSTAR					"装备升星"
#define  EQUIP_UNADDSTAR				"装备拆星"
#define  EQUIP_REPEATEADDSTAR			"装备附星"
#define	 EQUIP_ADDHOLE					"装备打孔"
#define	 EQUIP_UNADDGEM					"装备拆除宝石"
#define	 EQUIP_ADDGEM					"装备镶嵌宝石"
#define	 EQUIP_CHANGE_ZHUANHUN			"装备修改战魂"
#define	 EQUIP_CHANGE_FIVEELEMENT		"装备修改五行"
#define	 EQUIP_COMPOSE					"装备合成"
#define  MATERIAL_COMPOSE				"材料合成"
#define  STATEPOWERSUMMON				"国家官员召唤"
#define  ADDAUCTION				        "添加拍卖信息"
#define  BIDAUCTIONSUCC			        "竞拍成功"
#define  BANK_IN                        "存钱"
#define  BANK_OUT                       "取钱"
#define  SUMMON                         "召唤"
#define  CHANGE_STATE					"移民"
#define  TREATDRINK						"请客喝酒"
#define	 CHECKGOODSCARD					"检查物品卡"
#define	 USEGOODSCARD					"使用物品卡"
#define  DRAGONCONVERT					"龙币兑换"
#define  NPCBUY							"NPC购买"
#define  NPCSELL						"NPC出售"
#define  USEPROP						"使用道具"
#define  QUESTGETPROP					"任务给予道具"
#define  GIFTGETPROP					"礼包获得道具"
#define  YEARWINEGETPROP				"百年陈酿获得道具"
#define	 EFFECT_BEATTACKER_GETPROP		"效果被攻击者获得道具"
#define	 EFFECT_ATTACKER_GETPROP		"效果攻击者获得道具"
#define  PLAYERLEVELGETMATERIAL			"玩家等级随机得材料"
#define  MAILCREATEPROP					"邮件创建道具"
#define  PRIVATEGETPROP					"个人关系获得道具"
#define  SPLITPROP						"拆分道具"
#define  TOPGETPROP						"排行榜获得道具"
#define  DROPPROP						"掉落道具"
#define  STALLBUYPROP					"摆摊购买道具"

// 支付系统 购买服务备注名称 end
/////////////////////////////////////////////////

#define  PAYSYSTEM_EXPSTR1_LEN		128
#define  PAYSYSTEM_EXPSTR2_LEN		256
#define  PAYSYSTEM_EXPSTR3_LEN		500
//////////////////////////////////////////////////////////////////////////
//操作类型定义
enum TrscOpt
{
	Opt_Invalid = -1,
	Opt_Buy		= 0,			//买东西
	Opt_Sell,					//出售
	Opt_DragonConvertSilver,	//龙币兑换
	Opt_QueryDragonCoin,		//查询龙币
	Opt_CostMoney,				//消耗金钱
	Opt_DealCoin,               //金币交易
	Opt_DealCoinByUserName,     //通过账号金币交易，支持离线转账
	Opt_SaveCoin,				//金币存储
	Opt_TakeCoin,				//从存储中支取金币
	Opt_CostMoneyByUserName,	//通过账号金币消耗，支持离线消耗
	Opt_UseProp,				//使用道具
	Opt_QrSaveCoin,             //查询存储银子
	Opt_CheckGoodsCard,			//检查物品卡
	Opt_UseGoodsCard,			//使用物品卡
};

//服务类型
enum TrscService
{
	Svic_Invalid = -1,	//无效值
	Svic_Forever = 1,	//永久
	Svic_Number,		//分次
	Svic_Sharing,		//分摊
	Svic_Immediate		//即时
};

//////////////////////////////////////////////////////////////////////////
//供回调参数使用的扩展参数
struct Transac_CallBackParam
{
	Type_Money	m_Money;	//消耗金钱
	Type_Money	m_RemainMoney;	//剩余金钱
	int			m_nNum;		//数量
	int			m_nDay;		//有效天数

	PersonID	m_Buyer;	//买方
	PersonID	m_Seller;	//卖方
	
	int			m_Ext1;		//扩展参数
	int			m_Ext2;		//扩展参数
	int			m_Ext3;		//扩展参数
	int			m_Ext4;		//扩展参数
	int			m_Ext5;		//扩展参数
	int64		m_Ext6;		//扩展参数
	int64		m_Ext7;		//扩展参数
	int			m_Ext8;		//扩展参数
	int64		m_Ext9;		//扩展参数
	int64		m_Ext10;	//扩展参数
	int64		m_Ext11;	//扩展参数
	int64		m_Ext12;	//扩展参数 

	char		m_ExpStr1[PAYSYSTEM_EXPSTR1_LEN];
	char		m_ExtStr2[PAYSYSTEM_EXPSTR1_LEN];

	char        m_ExpStr3[PAYSYSTEM_EXPSTR2_LEN];
	char        m_ExpStr4[PAYSYSTEM_EXPSTR2_LEN];

	char        m_ExpStr5[PAYSYSTEM_EXPSTR3_LEN];

	char        m_ExpStr6[PAYSYSTEM_EXPSTR2_LEN];


	char		m_UserName[PAYSYSTEM_EXPSTR1_LEN];

	BOOL        m_IsSetMoney;//提取金钱时 是否通知其SetMoney

	Transac_CallBackParam()
	{
		m_Money		= 0;
		m_RemainMoney = 0;
		m_nNum		= 1;
		m_nDay		= 0;

		m_Buyer		= INVALID_PID;
		m_Seller	= INVALID_PID;

		m_Ext1		= INVALID_VALUE;	
		m_Ext2		= INVALID_VALUE;	
		m_Ext3		= INVALID_VALUE;	
		m_Ext4		= INVALID_VALUE;	
		m_Ext5		= INVALID_VALUE;	
		m_Ext6		= INVALID_VALUE64;	
		m_Ext7		= INVALID_VALUE64;	
		m_Ext8		= INVALID_VALUE;	
		m_Ext9		= INVALID_VALUE64;	
		m_Ext10		= INVALID_VALUE64;
		m_Ext11		= INVALID_VALUE64;
		m_Ext12		= INVALID_VALUE64; 
		memset(m_ExpStr1, 0, sizeof(m_ExpStr1));
		memset(m_ExtStr2, 0, sizeof(m_ExtStr2));
		memset(m_UserName,0 ,sizeof(m_UserName));

		memset(m_ExpStr3, 0, sizeof(m_ExpStr3));
		memset(m_ExpStr4, 0, sizeof(m_ExpStr4));

		memset(m_ExpStr5, 0, sizeof(m_ExpStr5)); 
		memset(m_ExpStr6, 0, sizeof(m_ExpStr6));
		m_IsSetMoney = TRUE;
	}

	Transac_CallBackParam(Transac_CallBackParam &TransCBParamObj)
	{
		m_Money			= TransCBParamObj.m_Money;
		m_RemainMoney	= TransCBParamObj.m_RemainMoney;
		m_nNum			= TransCBParamObj.m_nNum;
		m_nDay			= TransCBParamObj.m_nDay;

		m_Buyer			= TransCBParamObj.m_Buyer;
		m_Seller		= TransCBParamObj.m_Seller;

		m_Ext1			= TransCBParamObj.m_Ext1;	
		m_Ext2		=  TransCBParamObj.m_Ext2;	
		m_Ext3		=  TransCBParamObj.m_Ext3;	
		m_Ext4		= TransCBParamObj.m_Ext4;	
		m_Ext5		=  TransCBParamObj.m_Ext5;
		m_Ext6		=  TransCBParamObj.m_Ext6;	
		m_Ext7		=  TransCBParamObj.m_Ext7;	
		m_Ext8		=  TransCBParamObj.m_Ext8;	
		m_Ext9		=  TransCBParamObj.m_Ext9;
		m_Ext10		=  TransCBParamObj.m_Ext10;
		m_Ext11		= TransCBParamObj.m_Ext11;
		m_Ext12		=  TransCBParamObj.m_Ext12;

		memcpy(m_ExpStr1,TransCBParamObj.m_ExpStr1, sizeof(char) * PAYSYSTEM_EXPSTR1_LEN);
		memcpy(m_ExtStr2,TransCBParamObj.m_ExtStr2, sizeof(char) * PAYSYSTEM_EXPSTR1_LEN);
		memcpy(m_UserName,TransCBParamObj.m_UserName, sizeof(char) * PAYSYSTEM_EXPSTR1_LEN);
		memcpy(m_ExpStr3,TransCBParamObj.m_ExpStr3, sizeof(char) * PAYSYSTEM_EXPSTR2_LEN);
		memcpy(m_ExpStr4,TransCBParamObj.m_ExpStr4, sizeof(char) * PAYSYSTEM_EXPSTR2_LEN);
		memcpy(m_ExpStr5,TransCBParamObj.m_ExpStr5, sizeof(char) * PAYSYSTEM_EXPSTR3_LEN);
		memcpy(m_ExpStr6,TransCBParamObj.m_ExpStr6, sizeof(char) * PAYSYSTEM_EXPSTR2_LEN);

		m_IsSetMoney = TransCBParamObj.m_IsSetMoney;
	}
		Transac_CallBackParam& operator=(Transac_CallBackParam &TransCBParamObj )
		{
			m_Money			= TransCBParamObj.m_Money;
			m_RemainMoney	= TransCBParamObj.m_RemainMoney;
			m_nNum			= TransCBParamObj.m_nNum;
			m_nDay			= TransCBParamObj.m_nDay;

			m_Buyer			= TransCBParamObj.m_Buyer;
			m_Seller		= TransCBParamObj.m_Seller;

			m_Ext1			= TransCBParamObj.m_Ext1;	
			m_Ext2		=  TransCBParamObj.m_Ext2;	
			m_Ext3		=  TransCBParamObj.m_Ext3;	
			m_Ext4		= TransCBParamObj.m_Ext4;	
			m_Ext5		=  TransCBParamObj.m_Ext5;
			m_Ext6		=  TransCBParamObj.m_Ext6;	
			m_Ext7		=  TransCBParamObj.m_Ext7;	
			m_Ext8		=  TransCBParamObj.m_Ext8;	
			m_Ext9		=  TransCBParamObj.m_Ext9;
			m_Ext10		=  TransCBParamObj.m_Ext10;
			m_Ext11		= TransCBParamObj.m_Ext11;
			m_Ext12		=  TransCBParamObj.m_Ext12;

			memcpy(m_ExpStr1,TransCBParamObj.m_ExpStr1, sizeof(char) * PAYSYSTEM_EXPSTR1_LEN);
			memcpy(m_ExtStr2,TransCBParamObj.m_ExtStr2, sizeof(char) * PAYSYSTEM_EXPSTR1_LEN);
			memcpy(m_UserName,TransCBParamObj.m_UserName, sizeof(char) * PAYSYSTEM_EXPSTR1_LEN);
			memcpy(m_ExpStr3,TransCBParamObj.m_ExpStr3, sizeof(char) * PAYSYSTEM_EXPSTR2_LEN);
			memcpy(m_ExpStr4,TransCBParamObj.m_ExpStr4, sizeof(char) * PAYSYSTEM_EXPSTR2_LEN);
			memcpy(m_ExpStr5,TransCBParamObj.m_ExpStr5, sizeof(char) * PAYSYSTEM_EXPSTR3_LEN);
			memcpy(m_ExpStr6,TransCBParamObj.m_ExpStr6, sizeof(char) * PAYSYSTEM_EXPSTR2_LEN);

			m_IsSetMoney = TransCBParamObj.m_IsSetMoney;
			return *this;

		}
	BOOL operator==(Transac_CallBackParam &_Transac );
	BOOL operator==(Transac_CallBackParam *_Transac );
};
//支付系统回调接口
//--成功时回调
typedef void (*TrscCallBackFunc)( Transac_CallBackParam &pTransac);
//--失败时回调
typedef void (*TrscFailedCallBackFunc)(Transac_CallBackParam &pTransac);

//支付交易存储结构
struct Transac
{
	TrscID		m_TrscID;	//全局唯一流水号
	TrscOpt		m_OptID;	//操作ID
	TrscCallBackFunc	m_pTrscCallFn;				//支付系统回调接口
	TrscFailedCallBackFunc m_pTrscFailedCallFn;	
	
	TrscService	m_ServiceID;	//服务ID
	char		m_strExtParam[128];		//字符串参数

	Transac_CallBackParam m_Trsc_CBParam;
	TMV					  m_TrscTime;//操作时间
	int					  m_Money;//剩余钱数
	int					  m_SendCount; // 发送次数

	Transac()
	{
		m_TrscID			= INVALID_VALUE64;
		m_OptID				= Opt_Invalid;
		m_pTrscCallFn		= NULL;
		m_ServiceID			= Svic_Invalid;
		m_pTrscFailedCallFn = NULL;
		m_TrscTime			= INVALID_TIME;
		m_Money			    = 0;
		m_SendCount			= 1;
		memset(m_strExtParam,0,sizeof(m_strExtParam));
		strcpy(m_strExtParam,"null");
	}
	
	Transac(Transac &TransacObj)
	{
		m_TrscID			= TransacObj.m_TrscID;
		m_OptID				= TransacObj.m_OptID;
		m_pTrscCallFn		= TransacObj.m_pTrscCallFn;
		m_ServiceID			= TransacObj.m_ServiceID;
		m_pTrscFailedCallFn = TransacObj.m_pTrscFailedCallFn;
		m_TrscTime			= TransacObj.m_TrscTime;
		m_Money			    = TransacObj.m_Money;

		m_Trsc_CBParam		= TransacObj.m_Trsc_CBParam;
		memcpy(m_strExtParam,TransacObj.m_strExtParam,sizeof(char) * 128);
	}
	BOOL operator==(Transac &_Transac );
	BOOL operator==(Transac *_Transac );

};



//////////////////////////////////////////////////////////////////////////
//支付系统全局管理器
class CTrcsMgr
{
public:
	static CTrcsMgr& Instance() {
		static CTrcsMgr mgr;
		return mgr;
	}
#ifndef _DBSERVER

	BOOL	OnMsg(PACKET_COMMAND* pPacket);

	/* 请求金钱交易
	* 参数1：Transac 结构体  */
	BOOL	RequestTransac( Transac &sTransac );
	void	LogicTrsc();
#endif
#ifdef _DBSERVER
	inline CUtlMap<int,TrscID>&	GetStateTrscIDMap() { return m_StateTrscIDMap;}

	inline BOOL	UpdateStateTrscID(int nServerID, TrscID nTrscID)
	{
		int nIndex = m_StateTrscIDMap.Find(nServerID);
		if(m_StateTrscIDMap.IsValidIndex(nIndex))
		{
			m_StateTrscIDMap.Element(nIndex) = nTrscID;
		}
		else
		{
			m_StateTrscIDMap.Insert(nServerID,nTrscID);
	}

		return TRUE;
	}

	inline TrscID GetStateTrscIDByServerID(int nServerID)
	{
		int nIndex = m_StateTrscIDMap.Find(nServerID);
		if(m_StateTrscIDMap.IsValidIndex(nIndex))
		{
			return m_StateTrscIDMap.Element(nIndex);
		}
		return INVALID_TRSCID;
	}
#endif

protected:
	CTrcsMgr();
	~CTrcsMgr();
#ifndef _DBSERVER
	BOOL	_ProcGameRequest(Transac* pTrsc);
	BOOL	_ProcPaysysResponse();

	void	_SendPaysysMsg(PACKET_COMMAND* pPacket, int nServerID);

	void   SetTrscID(TrscID id) {m_CurrentID = id;}

#ifdef _DATASERVER_
	inline TrscID	_GetCurrentTrscID()	
	{
		int serverid = DataServerMgr().m_MyServerID;
		int worldid = DataServerMgr().m_WorldID;
		
		if( m_CurrentID >= MakePayID((serverid+1),worldid,0))//超过最大值则重置
		{
			m_CurrentID = MakePayID((serverid),worldid,0);
			return m_CurrentID;
		}		
		return ++m_CurrentID;
	}
#endif



	inline Transac*	_GetTransac(TrscID id)
	{
		int index = m_TrscContainer.Find( id );
		if( !m_TrscContainer.IsValidIndex(index) )
		{
			Log("接收PaySys消息，交易流水号无效(%I64d)\n", id);
			return FALSE;
		}

		Transac* pTrsc = m_TrscContainer.Element( index );

		m_TrscContainer.RemoveAt( index );

		return pTrsc;
	}
	
#endif
protected:
#ifndef _DBSERVER
	BOOL	_Packet_BuyItem(PACKET_COMMAND* pPacket);
	BOOL	_Packet_SellItem(PACKET_COMMAND* pPacket);
	BOOL    _Packet_DragonConvertSilver(PACKET_COMMAND* pPacket);
	BOOL    _Packet_QueryDragonCoin(PACKET_COMMAND* pPacket);
	BOOL    _Packet_SetPayID(PACKET_COMMAND* pPacket);
	BOOL    _Packet_Common(PACKET_COMMAND* pPacket);
	BOOL    _Packet_DealCoin(PACKET_COMMAND* pPacket);
	BOOL    _Packet_UseProp(PACKET_COMMAND* pPacket);
	BOOL    _Packet_QrSaveCoin(PACKET_COMMAND* pPacket);
	
	BOOL	_Packet_CheckGoodsCard(PACKET_COMMAND* pPacket);
	BOOL	_Packet_UseGoodsCard(PACKET_COMMAND* pPacket);
public:
	//请求存储和支取银子,add by lfy  2012.5.14
	BOOL	Request_PlayerStoreCoin(PersonID PID,const char *szUserName,int nStoreType,Type_Money nMoney,const char *szComments);
	BOOL	Request_PlayerDrawCoin(PersonID PID,const char *szUserName,int nStoreType,Type_Money nMoney,const char *szComments);
	BOOL	Request_DealMoneyToPlayerByUserName(const char* strFromName, const char* strToUserName, Type_Money nMoney, Type_Money nShui, PersonID PID = INVALID_UINT64);

private:
	BOOL	_ProcBuyItem(Transac* pTrsc);
	BOOL	_ProcSellItem(Transac* pTrsc);
	BOOL	_ProcDragonConvertSilver(Transac* pTrsc);
	BOOL	_ProcQueryDragonCoin(Transac* pTrsc);
	BOOL	_ProcCostMoneySilver(Transac* pTrsc);
	BOOL    _procStoreCoin(Transac* pTrsc);
	BOOL    _ProcTakeCoin(Transac* pTrsc);
	BOOL    _ProcQrSaveCoin(Transac* pTrsc);
	BOOL    _ProcSendCoinMail(Transac* pTrsc);
	BOOL    _ProcRecCoinMail(Transac* pTrsc);
	BOOL    _ProcDealCoin(Transac* pTrsc);
	BOOL	_ProcDealCoinByUserName(Transac* pTrsc);	//按账号名交易金币,支持离线消耗 add by lfy 2012.5.10
	BOOL	_ProcMoneyCostByUserName(Transac* pTrsc);	//按账号名消耗金币,支持离线消耗 add by lfy 2012.5.10
	BOOL	_ProcUseProp( Transac* pTrsc );

	BOOL	_ProcCheckGoodsCard(Transac* pTrsc );
	BOOL	_ProcUseGoodsCard(Transac* pTrsc );
#endif
protected:
#ifndef _DBSERVER
	TrscID						m_CurrentID;
	CUtlMap<TrscID, Transac*>	m_TrscContainer;
	TMV							m_SendTime;
#endif
#ifdef _DBSERVER
	CUtlMap<int,TrscID>			m_StateTrscIDMap;						
#endif

};

#endif	//_PAYSYSTEM_H_

/////////////////////////////////////////////////////////////


// --- 物品购买 ----
extern void	_G_CheckServer_CheckSuccess_P_PB_BN_BuyItem( Transac_CallBackParam &TrascCBParam );
extern void	_G_CheckServer_CheckFail_P_PB_BN_BuyItem( Transac_CallBackParam &TrascCBParam );
extern void	_G_CheckServer_CheckSuccess_P_PB_BN_RechargeWithFCoin( Transac_CallBackParam &TrascCBParam );

// --- 打造合成 ----
extern void _G_Equip_SignBind_CallBackFun( Transac_CallBackParam &TrascCBParam );
extern void _G_Equip_EquipPropUpQuality_AddStar_CallBackFun( Transac_CallBackParam &TrascCBParam );
extern void _G_PropEnchanting( Transac_CallBackParam &TrascCBParam );

// --- 装备修理 ----
extern void _G_EquipRepairProp(Transac_CallBackParam &TrascCBParam);
extern void _G_EquipRepairAllProp(Transac_CallBackParam &TrascCBParam);

// --- 摆摊交易 ----
extern void _G_BuyPropFromStall(Transac_CallBackParam &TrascCBParam);

//--镖局运营
extern void _G_SendSilverMail(Transac_CallBackParam &TrascCBParam);	//发送邮件
extern void _G_CallBack_StoreCoin(Transac_CallBackParam &TrascCBParam);	//储存金币
extern void _G_CallBack_CostCoin(Transac_CallBackParam &TrascCBParam); //消耗金币
extern void _G_CallBack_StorageExchange(Transac_CallBackParam &TrascCBParam);//换族长时交换存储银子
extern void _G_CallBack_SendEsortCompeteFailMoney(Transac_CallBackParam &TrascCBParam);//发送竞标失败银子

//---  拍卖 -----
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_DoAuction(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_RequestBidAuction(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_BidFaildReturnMoney(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_BidSuccCostChargeMoney(Transac_CallBackParam &TrascCBParam);

//-- 邮件 ---
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_GetMailMoney(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_SendMail(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_ReturnMailMoney(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_CostChargeMoney(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_TakeMoneySucc(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_CreatMailSuccTakeMoney(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_RequestSendMoneymBySysteMail(Transac_CallBackParam &TrascCBParam);