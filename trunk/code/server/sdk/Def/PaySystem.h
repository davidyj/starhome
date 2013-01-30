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
// ֧��ϵͳ �������ע���� begin
#define	 ORDINARYDRIVER					"��ͨ����"
#define	 CROSS_BORDER_TRANSMISSION		"�������"
#define	 PETUPSTAR						"��������"
#define	 PETSKILL_METAMORPHOSIS			"���＼�ܻû�"
#define	 PET_REBIRTH					"��������"
#define	 MOUNTSTOSTRENGTHEN				"����ǿ��"
#define	 CREATEFAMILY					"���崴��"
#define	 RAMILY_DONATED					"�������"
#define	 MARRIAGECOSTS					"������"
#define  DIVORCECOSTS					"������"
#define	 WARCAR_BUILD					"ս������"
#define  WARCAR_REPAIR                  "ս������"
#define  SKILL_LEAN						"����ѧϰ"
#define  RELIVE_INSITU					"ԭ�ظ���"
#define	 RELIVE_FULLSTATUS				"��״̬����"
#define  WORLDCHAT						"��������"
#define  COLOR_WORLD_CHAT				"��������"
#define  FIX_POSTAGE					"�̶��ʷ�"
#define  GOLDCOIN_MAIL					"����ʼ�"
#define	 EQUIP_REPAIRCOSTS				"װ������"
#define	 EQUIP_SIGN						"װ��ǩ��"
#define	 EQUIP_BIND						"װ����"
#define	 EQUIP_REPEATEBIND				"װ�����°�"
#define	 EQUIP_ADDSTAR					"װ������"
#define  EQUIP_UNADDSTAR				"װ������"
#define  EQUIP_REPEATEADDSTAR			"װ������"
#define	 EQUIP_ADDHOLE					"װ�����"
#define	 EQUIP_UNADDGEM					"װ�������ʯ"
#define	 EQUIP_ADDGEM					"װ����Ƕ��ʯ"
#define	 EQUIP_CHANGE_ZHUANHUN			"װ���޸�ս��"
#define	 EQUIP_CHANGE_FIVEELEMENT		"װ���޸�����"
#define	 EQUIP_COMPOSE					"װ���ϳ�"
#define  MATERIAL_COMPOSE				"���Ϻϳ�"
#define  STATEPOWERSUMMON				"���ҹ�Ա�ٻ�"
#define  ADDAUCTION				        "���������Ϣ"
#define  BIDAUCTIONSUCC			        "���ĳɹ�"
#define  BANK_IN                        "��Ǯ"
#define  BANK_OUT                       "ȡǮ"
#define  SUMMON                         "�ٻ�"
#define  CHANGE_STATE					"����"
#define  TREATDRINK						"��ͺȾ�"
#define	 CHECKGOODSCARD					"�����Ʒ��"
#define	 USEGOODSCARD					"ʹ����Ʒ��"
#define  DRAGONCONVERT					"���Ҷһ�"
#define  NPCBUY							"NPC����"
#define  NPCSELL						"NPC����"
#define  USEPROP						"ʹ�õ���"
#define  QUESTGETPROP					"����������"
#define  GIFTGETPROP					"�����õ���"
#define  YEARWINEGETPROP				"��������õ���"
#define	 EFFECT_BEATTACKER_GETPROP		"Ч���������߻�õ���"
#define	 EFFECT_ATTACKER_GETPROP		"Ч�������߻�õ���"
#define  PLAYERLEVELGETMATERIAL			"��ҵȼ�����ò���"
#define  MAILCREATEPROP					"�ʼ���������"
#define  PRIVATEGETPROP					"���˹�ϵ��õ���"
#define  SPLITPROP						"��ֵ���"
#define  TOPGETPROP						"���а��õ���"
#define  DROPPROP						"�������"
#define  STALLBUYPROP					"��̯�������"

// ֧��ϵͳ �������ע���� end
/////////////////////////////////////////////////

#define  PAYSYSTEM_EXPSTR1_LEN		128
#define  PAYSYSTEM_EXPSTR2_LEN		256
#define  PAYSYSTEM_EXPSTR3_LEN		500
//////////////////////////////////////////////////////////////////////////
//�������Ͷ���
enum TrscOpt
{
	Opt_Invalid = -1,
	Opt_Buy		= 0,			//����
	Opt_Sell,					//����
	Opt_DragonConvertSilver,	//���Ҷһ�
	Opt_QueryDragonCoin,		//��ѯ����
	Opt_CostMoney,				//���Ľ�Ǯ
	Opt_DealCoin,               //��ҽ���
	Opt_DealCoinByUserName,     //ͨ���˺Ž�ҽ��ף�֧������ת��
	Opt_SaveCoin,				//��Ҵ洢
	Opt_TakeCoin,				//�Ӵ洢��֧ȡ���
	Opt_CostMoneyByUserName,	//ͨ���˺Ž�����ģ�֧����������
	Opt_UseProp,				//ʹ�õ���
	Opt_QrSaveCoin,             //��ѯ�洢����
	Opt_CheckGoodsCard,			//�����Ʒ��
	Opt_UseGoodsCard,			//ʹ����Ʒ��
};

//��������
enum TrscService
{
	Svic_Invalid = -1,	//��Чֵ
	Svic_Forever = 1,	//����
	Svic_Number,		//�ִ�
	Svic_Sharing,		//��̯
	Svic_Immediate		//��ʱ
};

//////////////////////////////////////////////////////////////////////////
//���ص�����ʹ�õ���չ����
struct Transac_CallBackParam
{
	Type_Money	m_Money;	//���Ľ�Ǯ
	Type_Money	m_RemainMoney;	//ʣ���Ǯ
	int			m_nNum;		//����
	int			m_nDay;		//��Ч����

	PersonID	m_Buyer;	//��
	PersonID	m_Seller;	//����
	
	int			m_Ext1;		//��չ����
	int			m_Ext2;		//��չ����
	int			m_Ext3;		//��չ����
	int			m_Ext4;		//��չ����
	int			m_Ext5;		//��չ����
	int64		m_Ext6;		//��չ����
	int64		m_Ext7;		//��չ����
	int			m_Ext8;		//��չ����
	int64		m_Ext9;		//��չ����
	int64		m_Ext10;	//��չ����
	int64		m_Ext11;	//��չ����
	int64		m_Ext12;	//��չ���� 

	char		m_ExpStr1[PAYSYSTEM_EXPSTR1_LEN];
	char		m_ExtStr2[PAYSYSTEM_EXPSTR1_LEN];

	char        m_ExpStr3[PAYSYSTEM_EXPSTR2_LEN];
	char        m_ExpStr4[PAYSYSTEM_EXPSTR2_LEN];

	char        m_ExpStr5[PAYSYSTEM_EXPSTR3_LEN];

	char        m_ExpStr6[PAYSYSTEM_EXPSTR2_LEN];


	char		m_UserName[PAYSYSTEM_EXPSTR1_LEN];

	BOOL        m_IsSetMoney;//��ȡ��Ǯʱ �Ƿ�֪ͨ��SetMoney

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
//֧��ϵͳ�ص��ӿ�
//--�ɹ�ʱ�ص�
typedef void (*TrscCallBackFunc)( Transac_CallBackParam &pTransac);
//--ʧ��ʱ�ص�
typedef void (*TrscFailedCallBackFunc)(Transac_CallBackParam &pTransac);

//֧�����״洢�ṹ
struct Transac
{
	TrscID		m_TrscID;	//ȫ��Ψһ��ˮ��
	TrscOpt		m_OptID;	//����ID
	TrscCallBackFunc	m_pTrscCallFn;				//֧��ϵͳ�ص��ӿ�
	TrscFailedCallBackFunc m_pTrscFailedCallFn;	
	
	TrscService	m_ServiceID;	//����ID
	char		m_strExtParam[128];		//�ַ�������

	Transac_CallBackParam m_Trsc_CBParam;
	TMV					  m_TrscTime;//����ʱ��
	int					  m_Money;//ʣ��Ǯ��
	int					  m_SendCount; // ���ʹ���

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
//֧��ϵͳȫ�ֹ�����
class CTrcsMgr
{
public:
	static CTrcsMgr& Instance() {
		static CTrcsMgr mgr;
		return mgr;
	}
#ifndef _DBSERVER

	BOOL	OnMsg(PACKET_COMMAND* pPacket);

	/* �����Ǯ����
	* ����1��Transac �ṹ��  */
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
		
		if( m_CurrentID >= MakePayID((serverid+1),worldid,0))//�������ֵ������
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
			Log("����PaySys��Ϣ��������ˮ����Ч(%I64d)\n", id);
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
	//����洢��֧ȡ����,add by lfy  2012.5.14
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
	BOOL	_ProcDealCoinByUserName(Transac* pTrsc);	//���˺������׽��,֧���������� add by lfy 2012.5.10
	BOOL	_ProcMoneyCostByUserName(Transac* pTrsc);	//���˺������Ľ��,֧���������� add by lfy 2012.5.10
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


// --- ��Ʒ���� ----
extern void	_G_CheckServer_CheckSuccess_P_PB_BN_BuyItem( Transac_CallBackParam &TrascCBParam );
extern void	_G_CheckServer_CheckFail_P_PB_BN_BuyItem( Transac_CallBackParam &TrascCBParam );
extern void	_G_CheckServer_CheckSuccess_P_PB_BN_RechargeWithFCoin( Transac_CallBackParam &TrascCBParam );

// --- ����ϳ� ----
extern void _G_Equip_SignBind_CallBackFun( Transac_CallBackParam &TrascCBParam );
extern void _G_Equip_EquipPropUpQuality_AddStar_CallBackFun( Transac_CallBackParam &TrascCBParam );
extern void _G_PropEnchanting( Transac_CallBackParam &TrascCBParam );

// --- װ������ ----
extern void _G_EquipRepairProp(Transac_CallBackParam &TrascCBParam);
extern void _G_EquipRepairAllProp(Transac_CallBackParam &TrascCBParam);

// --- ��̯���� ----
extern void _G_BuyPropFromStall(Transac_CallBackParam &TrascCBParam);

//--�ھ���Ӫ
extern void _G_SendSilverMail(Transac_CallBackParam &TrascCBParam);	//�����ʼ�
extern void _G_CallBack_StoreCoin(Transac_CallBackParam &TrascCBParam);	//������
extern void _G_CallBack_CostCoin(Transac_CallBackParam &TrascCBParam); //���Ľ��
extern void _G_CallBack_StorageExchange(Transac_CallBackParam &TrascCBParam);//���峤ʱ�����洢����
extern void _G_CallBack_SendEsortCompeteFailMoney(Transac_CallBackParam &TrascCBParam);//���;���ʧ������

//---  ���� -----
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_DoAuction(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_RequestBidAuction(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_BidFaildReturnMoney(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_BidSuccCostChargeMoney(Transac_CallBackParam &TrascCBParam);

//-- �ʼ� ---
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_GetMailMoney(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_SendMail(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_ReturnMailMoney(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_CostChargeMoney(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_TakeMoneySucc(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_CreatMailSuccTakeMoney(Transac_CallBackParam &TrascCBParam);
extern void _G_CheckServer_CheckSuccess_P_PB_BN_CheckSucc_RequestSendMoneymBySysteMail(Transac_CallBackParam &TrascCBParam);