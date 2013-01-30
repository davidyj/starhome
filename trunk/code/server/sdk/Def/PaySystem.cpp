#include "PaySystem.h"
#include "PlayerMgr.h"
#include "PlayerObj.h"
#ifdef _DATASERVER_
#include "DataServerMgr.h"
#endif

#include "ErrorID.h"

BOOL Transac_CallBackParam::operator==(Transac_CallBackParam &Transac_CBP )
{
	return *this == &Transac_CBP;
}

BOOL Transac_CallBackParam::operator==(Transac_CallBackParam *Transac_CBP )
{
	bool nFlag = true;
	nFlag	&=		m_Money			== Transac_CBP->m_Money;
	nFlag	&=		m_RemainMoney	== Transac_CBP->m_RemainMoney;
	nFlag	&=		m_nNum			== Transac_CBP->m_nNum;
	nFlag	&=		m_nDay			== Transac_CBP->m_nDay;

	nFlag	&=		m_Buyer			== Transac_CBP->m_Buyer;
	nFlag	&=		m_Seller		== Transac_CBP->m_Seller;

	nFlag	&=		m_Ext1			== Transac_CBP->m_Ext1;	
	nFlag	&=		m_Ext2			== Transac_CBP->m_Ext2;	
	nFlag	&=		m_Ext3			== Transac_CBP->m_Ext3;	
	nFlag	&=		m_Ext4			== Transac_CBP->m_Ext4;	
	nFlag	&=		m_Ext5			== Transac_CBP->m_Ext5;	
	nFlag	&=		m_Ext6			== Transac_CBP->m_Ext6;	
	nFlag	&=		m_Ext7			== Transac_CBP->m_Ext7;	
	nFlag	&=		m_Ext8			== Transac_CBP->m_Ext8;	
	nFlag	&=		m_Ext9			== Transac_CBP->m_Ext9;	
	nFlag	&=		m_Ext10			== Transac_CBP->m_Ext10;
	nFlag	&=		m_Ext11			== Transac_CBP->m_Ext11;
	nFlag	&=		m_Ext12			== Transac_CBP->m_Ext12; 
	nFlag	&=		m_IsSetMoney	== Transac_CBP->m_IsSetMoney;

	nFlag	&= !strcmp(m_ExpStr1,Transac_CBP->m_ExpStr1);
	nFlag	&= !strcmp(m_ExtStr2,Transac_CBP->m_ExtStr2);
	nFlag	&= !strcmp(m_ExpStr3,Transac_CBP->m_ExpStr3);
	nFlag	&= !strcmp(m_ExpStr4,Transac_CBP->m_ExpStr4);
	nFlag	&= !strcmp(m_ExpStr5,Transac_CBP->m_ExpStr5);
	nFlag	&= !strcmp(m_ExpStr6,Transac_CBP->m_ExpStr6);
	nFlag	&= !strcmp(m_UserName,Transac_CBP->m_UserName);
	
	return nFlag;
}

BOOL Transac::operator==(Transac &_Transac )
{
	return *this == &_Transac;
}
BOOL Transac::operator==(Transac *_Transac )
{
	BOOL nFlag = TRUE;
	nFlag	&=		m_OptID				== _Transac->m_OptID;
	nFlag	&=		m_pTrscCallFn		== _Transac->m_pTrscCallFn;
	nFlag	&=		m_ServiceID			== _Transac->m_ServiceID;
	nFlag	&=		m_pTrscFailedCallFn == _Transac->m_pTrscFailedCallFn;
	nFlag	&=		m_Money			    == _Transac->m_Money;
	
	nFlag	&= !strcmp(m_strExtParam,_Transac->m_strExtParam);

	nFlag	&= m_Trsc_CBParam == _Transac->m_Trsc_CBParam;
	return nFlag;
}


CTrcsMgr::CTrcsMgr()
{
#ifndef _DBSERVER
	m_CurrentID = 0;
	m_SendTime = 0;
	SetDefLessFunc(m_TrscContainer);
#endif
#ifdef _DBSERVER
	SetDefLessFunc(m_StateTrscIDMap);
	m_StateTrscIDMap.RemoveAll();
#endif

}

CTrcsMgr::~CTrcsMgr()
{
}
#ifndef _DBSERVER
BOOL CTrcsMgr::OnMsg(PACKET_COMMAND* pPacket)
{
	if( !pPacket )
		return FALSE;

	switch( pPacket->Type() )
	{
	case DBSERVER_SET_PAYID:
		_Packet_SetPayID(pPacket);
		break;
	case CHECKSERVER_RESPONSE_BUYITEM:
		_Packet_BuyItem( pPacket );
		break;
	case CHECKSERVER_RESPONSE_RECHARGEWITHFCOIN:
		_Packet_SellItem(pPacket);
		break;
	case CHECKSERVER_RESPONSE_RECHARGEWITSCOIN:
		_Packet_DragonConvertSilver(pPacket);
		break;
	case CHECKSERVER_RESPONSE_QUERYDRAGONCOIN:
		_Packet_QueryDragonCoin(pPacket);
		break;
	case CHECKSERVER_RESPONSE_STORECOIN:
		_Packet_Common(pPacket);
		break;
	case CHECKSERVER_RESPONSE_TAKECOIN:
		_Packet_Common(pPacket);
		break;
	case CHECKSERVER_RESPONSE_QRSAVECOIN:
		_Packet_QrSaveCoin(pPacket);
		break;
	case CHECKSERVER_RESPONSE_RECCOINMAIL:
		_Packet_Common(pPacket);
		break;
	case CHECKSERVER_RESPONSE_SENDCOINMAIL:
		_Packet_Common(pPacket);
		break;
	case CHECKSERVER_RESPONSE_DEALCOIN_LOCALZONE:
		_Packet_DealCoin(pPacket);
		break;
	case CHECKSERVER_RESPONSE_CHECKGOODSCARD:
		_Packet_CheckGoodsCard(pPacket);
		break;
	case CHECKSERVER_RESPONSE_USEGOODSCARD:
		_Packet_UseGoodsCard(pPacket);
		break;
	default:
		break;
	}

	return TRUE;
}



BOOL CTrcsMgr::RequestTransac( Transac &sTransac )
{
	Transac* pTrsc = g_TransacPool().Alloc();
	if( !pTrsc )
		return FALSE;

	pTrsc->m_TrscID				= _GetCurrentTrscID();
	pTrsc->m_OptID				= sTransac.m_OptID;
	pTrsc->m_pTrscCallFn		= sTransac.m_pTrscCallFn;
	pTrsc->m_pTrscFailedCallFn  = sTransac.m_pTrscFailedCallFn;
	pTrsc->m_ServiceID			= sTransac.m_ServiceID;

	pTrsc->m_Trsc_CBParam.m_Money	= sTransac.m_Trsc_CBParam.m_Money;
	pTrsc->m_Trsc_CBParam.m_nNum	= sTransac.m_Trsc_CBParam.m_nNum;
	pTrsc->m_Trsc_CBParam.m_nDay	= sTransac.m_Trsc_CBParam.m_nDay;
	pTrsc->m_Trsc_CBParam.m_Buyer	= sTransac.m_Trsc_CBParam.m_Buyer;
	pTrsc->m_Trsc_CBParam.m_Seller	= sTransac.m_Trsc_CBParam.m_Seller;
	pTrsc->m_Trsc_CBParam.m_Ext1	= sTransac.m_Trsc_CBParam.m_Ext1;
	pTrsc->m_Trsc_CBParam.m_Ext2	= sTransac.m_Trsc_CBParam.m_Ext2;
	pTrsc->m_Trsc_CBParam.m_Ext3	= sTransac.m_Trsc_CBParam.m_Ext3;
	pTrsc->m_Trsc_CBParam.m_Ext4	= sTransac.m_Trsc_CBParam.m_Ext4;
	pTrsc->m_Trsc_CBParam.m_Ext5	= sTransac.m_Trsc_CBParam.m_Ext5;
	pTrsc->m_Trsc_CBParam.m_Ext6	= sTransac.m_Trsc_CBParam.m_Ext6;
	pTrsc->m_Trsc_CBParam.m_Ext7	= sTransac.m_Trsc_CBParam.m_Ext7;
	pTrsc->m_Trsc_CBParam.m_Ext8	= sTransac.m_Trsc_CBParam.m_Ext8;
	pTrsc->m_Trsc_CBParam.m_Ext9	= sTransac.m_Trsc_CBParam.m_Ext9;
	pTrsc->m_Trsc_CBParam.m_Ext10	= sTransac.m_Trsc_CBParam.m_Ext10;
	pTrsc->m_Trsc_CBParam.m_Ext11	= sTransac.m_Trsc_CBParam.m_Ext11;
	pTrsc->m_Trsc_CBParam.m_Ext12	= sTransac.m_Trsc_CBParam.m_Ext12; 
	pTrsc->m_Trsc_CBParam.m_IsSetMoney  = sTransac.m_Trsc_CBParam.m_IsSetMoney;

	if(sTransac.m_strExtParam != NULL)
		Q_strlcpy(pTrsc->m_strExtParam,sizeof(pTrsc->m_strExtParam),sTransac.m_strExtParam);
		//strcpy(pTrsc->m_strExtParam,sTransac.m_strExtParam);

	if (sTransac.m_Trsc_CBParam.m_ExpStr1 && strlen(sTransac.m_Trsc_CBParam.m_ExpStr1) < PAYSYSTEM_EXPSTR1_LEN)
	{
		//strcpy(pTrsc->m_Trsc_CBParam.m_ExpStr1, sTransac.m_Trsc_CBParam.m_ExpStr1);
		Q_strlcpy(pTrsc->m_Trsc_CBParam.m_ExpStr1,sizeof(pTrsc->m_Trsc_CBParam.m_ExpStr1), sTransac.m_Trsc_CBParam.m_ExpStr1);
	}
	if (sTransac.m_Trsc_CBParam.m_ExtStr2 && strlen(sTransac.m_Trsc_CBParam.m_ExtStr2) < PAYSYSTEM_EXPSTR1_LEN)
	{
		//strcpy(pTrsc->m_Trsc_CBParam.m_ExtStr2, sTransac.m_Trsc_CBParam.m_ExtStr2);
		Q_strlcpy(pTrsc->m_Trsc_CBParam.m_ExtStr2,sizeof(pTrsc->m_Trsc_CBParam.m_ExtStr2), sTransac.m_Trsc_CBParam.m_ExtStr2);
	}

	if (sTransac.m_Trsc_CBParam.m_UserName && strlen(sTransac.m_Trsc_CBParam.m_UserName) < PAYSYSTEM_EXPSTR1_LEN)
	{
		//strcpy(pTrsc->m_Trsc_CBParam.m_UserName, sTransac.m_Trsc_CBParam.m_UserName);
		Q_strlcpy(pTrsc->m_Trsc_CBParam.m_UserName,sizeof(pTrsc->m_Trsc_CBParam.m_UserName), sTransac.m_Trsc_CBParam.m_UserName);
	}

	if (sTransac.m_Trsc_CBParam.m_ExpStr3 && strlen(sTransac.m_Trsc_CBParam.m_ExpStr3) < PAYSYSTEM_EXPSTR2_LEN)
	{
		//strcpy(pTrsc->m_Trsc_CBParam.m_ExpStr3, sTransac.m_Trsc_CBParam.m_ExpStr3);
		Q_strlcpy(pTrsc->m_Trsc_CBParam.m_ExpStr3,sizeof(pTrsc->m_Trsc_CBParam.m_ExpStr3), sTransac.m_Trsc_CBParam.m_ExpStr3);
	}
	if (sTransac.m_Trsc_CBParam.m_ExpStr4 && strlen(sTransac.m_Trsc_CBParam.m_ExpStr4) < PAYSYSTEM_EXPSTR2_LEN)
	{
		//strcpy(pTrsc->m_Trsc_CBParam.m_ExpStr4, sTransac.m_Trsc_CBParam.m_ExpStr4);
		Q_strlcpy(pTrsc->m_Trsc_CBParam.m_ExpStr4,sizeof(pTrsc->m_Trsc_CBParam.m_ExpStr4), sTransac.m_Trsc_CBParam.m_ExpStr4);
	}
	if (sTransac.m_Trsc_CBParam.m_ExpStr5 && strlen(sTransac.m_Trsc_CBParam.m_ExpStr5) < PAYSYSTEM_EXPSTR3_LEN)
	{
		//strcpy(pTrsc->m_Trsc_CBParam.m_ExpStr5, sTransac.m_Trsc_CBParam.m_ExpStr5);
		Q_strlcpy(pTrsc->m_Trsc_CBParam.m_ExpStr5,sizeof(pTrsc->m_Trsc_CBParam.m_ExpStr5), sTransac.m_Trsc_CBParam.m_ExpStr5);
	}
	if (sTransac.m_Trsc_CBParam.m_ExpStr6 && strlen(sTransac.m_Trsc_CBParam.m_ExpStr6) < PAYSYSTEM_EXPSTR2_LEN)
	{
		//strcpy(pTrsc->m_Trsc_CBParam.m_ExpStr6, sTransac.m_Trsc_CBParam.m_ExpStr6);
		Q_strlcpy(pTrsc->m_Trsc_CBParam.m_ExpStr6,sizeof(pTrsc->m_Trsc_CBParam.m_ExpStr6), sTransac.m_Trsc_CBParam.m_ExpStr6);
	}

	int index = m_TrscContainer.Find( pTrsc->m_TrscID );
	if( m_TrscContainer.IsValidIndex( index ) )
	{
		Log("创建金钱交易时出现严重错误：流水号重复！");
		return FALSE;
	}

	CPlayer* pPlayer = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Buyer );
	if( pPlayer )
	{
		pTrsc->m_Money = pPlayer->GetMoney(Currency_Silver);
		//Log("支付请求 账号: %s , 玩家: %s,操作:%d, 请求金币:%s , 剩余金币: %d",pPlayer->GetUserName(), pPlayer->GetName(),pTrsc->m_OptID,pTrsc->m_Trsc_CBParam.m_Money,pTrsc->m_Money );
	}
	else
	{
		CPlayer* pSellPlayer = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Seller );
		if( pSellPlayer )
		{
			pTrsc->m_Money = pSellPlayer->GetMoney(Currency_Silver);
			//Log("支付请求 账号: %s , 玩家: %s,操作:%d, 请求金币:%s , 剩余金币: %d",pSellPlayer->GetUserName(), pSellPlayer->GetName(),pTrsc->m_OptID,pTrsc->m_Trsc_CBParam.m_Money,pTrsc->m_Money );
		}
	}

	pTrsc->m_TrscTime = Time().GetCurrentTime();
	//Log("\n 支付系统 支付单号: %I64d, 初始化时间 %I64d\n",	pTrsc->m_TrscID,pTrsc->m_TrscTime);

	m_TrscContainer.Insert( pTrsc->m_TrscID, pTrsc );
	//这里发给DB让其存流水号
	PACKET_COMMAND pack;
	pack.SetParam( DBSERVER_SET_PAYID,GetCmdFormat(DBSERVER_SET_PAYID),pTrsc->m_TrscID);
	DataServerMgr().SendDBMsg(&pack);

	return _ProcGameRequest(pTrsc);
	
}

BOOL CTrcsMgr::_ProcGameRequest(Transac* pTrsc)
{
	if( !pTrsc )
		return FALSE;

	switch( pTrsc->m_OptID )
	{
	case Opt_Buy:
		return _ProcBuyItem( pTrsc );
	case Opt_Sell:
		return _ProcSellItem( pTrsc );
	case Opt_DragonConvertSilver:
		return _ProcDragonConvertSilver( pTrsc );
	case Opt_QueryDragonCoin:
		_ProcQueryDragonCoin( pTrsc );
		break;
	case Opt_CostMoney:
		return _ProcCostMoneySilver(pTrsc);		
	case Opt_DealCoin:
		return _ProcDealCoin(pTrsc);
	case Opt_SaveCoin:
		return _procStoreCoin(pTrsc);		
	case Opt_TakeCoin:
		return _ProcTakeCoin(pTrsc);
	case Opt_DealCoinByUserName:
		return _ProcDealCoinByUserName(pTrsc);
	case Opt_CostMoneyByUserName:
		return _ProcMoneyCostByUserName(pTrsc);
	case Opt_UseProp:
		return _ProcUseProp( pTrsc );
	case Opt_QrSaveCoin:
		return _ProcQrSaveCoin(pTrsc);
	case Opt_CheckGoodsCard:
		return _ProcCheckGoodsCard(pTrsc);
	case Opt_UseGoodsCard:
		return _ProcUseGoodsCard(pTrsc);
	default:
		break;
	}

	return FALSE;
}

BOOL CTrcsMgr::_ProcPaysysResponse()
{
	return TRUE;
}

void	CTrcsMgr::LogicTrsc()
{
	
	TMV  CurTime = Time().GetCurrentTime();
	FOR_EACH_MAP( m_TrscContainer,index)
	{
		Transac* pTran=m_TrscContainer.Element(index);
		if(pTran)
		{
			if( (CurTime - pTran->m_TrscTime) > TIME_5Min )//五分钟还没有返回消息是有问题的
			{

				int nIndex = m_TrscContainer.Find( pTran->m_TrscID );\
					if( m_TrscContainer.IsValidIndex( nIndex ) )
					{
						if(++pTran->m_SendCount <= 3)
						{
							Log("没有收到此单号 %I64u 的回复, 试图重复第%d次发送,  玩家ID：%I64u,操作：%d,剩余金币：%I64d, 备注: %s\n",
								pTran->m_TrscID,pTran->m_SendCount,pTran->m_Trsc_CBParam.m_Buyer,pTran->m_OptID,pTran->m_Trsc_CBParam.m_Money,pTran->m_strExtParam);
							pTran->m_TrscTime = Time().GetCurrentTime();
							_ProcGameRequest(pTran);
							break;
						}
						else
						{
							Log("有问题的单号(试图发送3次失败, 已干掉)：%I64u 玩家ID：%I64u,操作：%d,剩余金币：%I64d, 备注: %s\n",
								pTran->m_TrscID,pTran->m_Trsc_CBParam.m_Buyer,pTran->m_OptID,pTran->m_Trsc_CBParam.m_Money,pTran->m_strExtParam);
							m_TrscContainer.RemoveAt(nIndex);
							g_TransacPool().Free( pTran );
							break;
						}
					}
			}
		}	
	}
}

///////////////////////////////////////////////////////////////////////////////
//
void CTrcsMgr::_SendPaysysMsg(PACKET_COMMAND* pPacket, int nServerID)
{
	if( !pPacket )
		return;

	CSNetGameObj* pServer = DataServerMgr().GetServerByServerID(nServerID);
	if( !pServer )
		return;

	pServer->SendMsg( pPacket );
}

BOOL CTrcsMgr::_ProcBuyItem(Transac* pTrsc)
{
	if( !pTrsc )
		return FALSE;

	CPlayer* pPlayer = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Buyer );
	if( !pPlayer )
		return FALSE;

	PACKET_COMMAND pack;
	//GUID，道具ID（不能重复），道具名称，道具类型，（1：永久类，2：分次类，3：分摊类, 4: 即时），数量, 用户名，网关ID，有效天数，（永久类道具：传0；其他：传实际可用天数），价格
	pack.SetParam( CHECKSERVER_REQUEST_BUYITEM, GetCmdFormat(CHECKSERVER_REQUEST_BUYITEM),
		pTrsc->m_TrscID, pTrsc->m_TrscID, pTrsc->m_strExtParam, pTrsc->m_ServiceID,
		pTrsc->m_Trsc_CBParam.m_Ext2,pPlayer->GetUserName(), DataServerMgr().m_WorldID,
		pTrsc->m_Trsc_CBParam.m_nDay,pTrsc->m_Trsc_CBParam.m_Money );

	pPlayer->SendMsg(&pack);
	return TRUE;
}

BOOL CTrcsMgr::_ProcSellItem(Transac* pTrsc)
{
	if( !pTrsc )
		return FALSE;

	CPlayer* pPlayer = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Seller );
	if( !pPlayer )
		return FALSE;
	//GUID(流水号), 帐号名, 网关ID, 充值金币数, IP地址, 备注(char256 允许NULL)
	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_RECHARGEWITHFCOIN, GetCmdFormat(CHECKSERVER_REQUEST_RECHARGEWITHFCOIN),
		pTrsc->m_TrscID, pTrsc->m_TrscID,pPlayer->GetUserName(),DataServerMgr().m_WorldID, pTrsc->m_Trsc_CBParam.m_Money,INVALID_VALUE64,pTrsc->m_strExtParam );
	pPlayer->SendMsg(&pack);

	return TRUE;
}
BOOL CTrcsMgr::_ProcDragonConvertSilver(Transac* pTrsc)
{
	if( !pTrsc )
		return FALSE;

	CPlayer* pPlayer = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Buyer );
	if( !pPlayer )
		return FALSE;
	//GUID(流水号), 帐号名, 网关ID, 充值金币数, IP地址, 密保卡坐标(char256 允许NULL), 密保卡密匙(char256 允许NULL), 备注(char256 允许NULL)
	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_RECHARGEWITHSCOIN, GetCmdFormat(CHECKSERVER_REQUEST_RECHARGEWITHSCOIN),
		pTrsc->m_TrscID,pTrsc->m_TrscID, pPlayer->GetUserName(),DataServerMgr().m_WorldID, pTrsc->m_Trsc_CBParam.m_Money,INVALID_VALUE64,"null","null","null" );
	pPlayer->SendMsg(&pack);
	//Log("请求兑换龙币：兑换金额为 %I64d 玩家 %s ",pTrsc->m_Trsc_CBParam.m_Money,pPlayer->GetName());

	return TRUE;
}
BOOL CTrcsMgr::_ProcQueryDragonCoin(Transac* pTrsc)
{
	if( !pTrsc )
		return FALSE;

	CPlayer* pPlayer = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Buyer );
	if( !pPlayer )
		return FALSE;
	//GUID(流水号), 帐号名
	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_QUERYDRAGONCOIN, GetCmdFormat(CHECKSERVER_REQUEST_QUERYDRAGONCOIN),
		pTrsc->m_TrscID, pPlayer->GetUserName() );
	pPlayer->SendMsg(&pack);
	return TRUE;
}

BOOL    CTrcsMgr::_ProcRecCoinMail(Transac* pTrsc)
{
	if( !pTrsc )
		return FALSE;

	CPlayer* pPlayer = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Buyer );
	if( !pPlayer )
		return FALSE;
	///GUID(流水号),GUID(流水号),邮件所附带金币单号, 账号名, 备注
	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_RECCOINMAIL, GetCmdFormat(CHECKSERVER_REQUEST_RECCOINMAIL),
		pTrsc->m_TrscID, pTrsc->m_TrscID, pTrsc->m_Trsc_CBParam.m_Ext6, pPlayer->GetUserName() ,pTrsc->m_Trsc_CBParam.m_ExpStr1);
	pPlayer->SendMsg(&pack);
	return TRUE;

}

BOOL    CTrcsMgr::_ProcSendCoinMail(Transac* pTrsc)
{
	
	if( !pTrsc )
		return FALSE;

	CPlayer* pPlayer = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Buyer );
	if( !pPlayer )
		return FALSE;
	//GUID(流水号),GUID(流水号), 账号名, 网关，发送金币数，税费金额，备注
	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_SENDCOINMAIL, GetCmdFormat(CHECKSERVER_REQUEST_SENDCOINMAIL),
		pTrsc->m_TrscID, pTrsc->m_TrscID,pPlayer->GetUserName() , DataServerMgr().m_WorldID, pTrsc->m_Trsc_CBParam.m_Ext6,pTrsc->m_Trsc_CBParam.m_Ext7 ,pTrsc->m_Trsc_CBParam.m_ExpStr1);
	pPlayer->SendMsg(&pack);
	return TRUE;
}

BOOL    CTrcsMgr::_procStoreCoin(Transac* pTrsc)
{
	if( !pTrsc )
		return FALSE;

	//CPlayer* pPlayer = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Buyer );
	//if( !pPlayer )
	//	return FALSE;
	if(strlen(pTrsc->m_Trsc_CBParam.m_UserName) == 0)
		return FALSE;

	//GUID(流水号), 帐号名,网关id，存储金币数，存储类型，备注
	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_STORECOIN, GetCmdFormat(CHECKSERVER_REQUEST_STORECOIN),
		pTrsc->m_TrscID, pTrsc->m_TrscID,pTrsc->m_Trsc_CBParam.m_UserName , DataServerMgr().m_WorldID, pTrsc->m_Trsc_CBParam.m_Ext6,pTrsc->m_Trsc_CBParam.m_Ext1 ,pTrsc->m_strExtParam);
	//pPlayer->SendMsg(&pack);
	DataServerMgr().SendMsgToLoginServer(&pack);
	return TRUE;
}

BOOL    CTrcsMgr::_ProcTakeCoin(Transac* pTrsc)
{
	if( !pTrsc )
		return FALSE;

// 	CPlayer* pPlayer = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Buyer );
// 	if( !pPlayer )
// 		return FALSE;

	//GUID(流水号), 帐号名,网关id，存储金币数，存储类型，备注
	if(strlen(pTrsc->m_Trsc_CBParam.m_UserName) == 0)
	{
		Log("提取金钱失败! 提取者UserName: %s",pTrsc->m_Trsc_CBParam.m_UserName);
		return FALSE;
	}

	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_TAKECOIN, GetCmdFormat(CHECKSERVER_REQUEST_TAKECOIN),
		pTrsc->m_TrscID, pTrsc->m_TrscID,pTrsc->m_Trsc_CBParam.m_UserName , DataServerMgr().m_WorldID, pTrsc->m_Trsc_CBParam.m_Ext6,pTrsc->m_Trsc_CBParam.m_Ext1 ,pTrsc->m_strExtParam);
	//pPlayer->SendMsg(&pack);
	return DataServerMgr().SendMsgToLoginServer(&pack);

}

BOOL    CTrcsMgr::_ProcQrSaveCoin(Transac* pTrsc)
{
	if( !pTrsc )
		return FALSE;

// 	CPlayer* pPlayer = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Buyer );
// 	if( !pPlayer )
// 		return FALSE;

	if(strlen( pTrsc->m_Trsc_CBParam.m_UserName) == 0)
		return FALSE;
	//GUID(流水号), 帐号名,网关id，存储类型
	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_QRSAVECOIN, GetCmdFormat(CHECKSERVER_REQUEST_QRSAVECOIN),
		pTrsc->m_TrscID, pTrsc->m_Trsc_CBParam.m_UserName , DataServerMgr().m_WorldID,pTrsc->m_Trsc_CBParam.m_Ext1);

	//pPlayer->SendMsg(&pack);
	return DataServerMgr().SendMsgToLoginServer(&pack);
}

BOOL CTrcsMgr::_ProcDealCoin(Transac* pTrsc)
{
	if( !pTrsc)
		return FALSE;

	//CPlayer* pPlayerB = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Buyer );
	//CPlayer* pPlayerS = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Seller );
	//if( !pPlayerB || !pPlayerS)
	//	return FALSE;
	//GUID(流水号),金币转出人，金币接收人，金币缴税人，网关ID，金币数量（交易），金币数量（税费）
	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_DEALCOIN_LOCALZONE, GetCmdFormat(CHECKSERVER_REQUEST_DEALCOIN_LOCALZONE),
		pTrsc->m_TrscID, pTrsc->m_TrscID, pTrsc->m_Trsc_CBParam.m_ExpStr1, pTrsc->m_Trsc_CBParam.m_ExtStr2,pTrsc->m_Trsc_CBParam.m_ExpStr1,
		DataServerMgr().m_WorldID, pTrsc->m_Trsc_CBParam.m_Money, pTrsc->m_Trsc_CBParam.m_Ext7,pTrsc->m_strExtParam);

	DataServerMgr().SendMsgToLoginServer(&pack);
	//pPlayerB->SendMsg(&pack);
	return TRUE;
}

BOOL CTrcsMgr::_ProcDealCoinByUserName(Transac* pTrsc)
{
	if( !pTrsc)
		return FALSE;

	if(strlen(pTrsc->m_Trsc_CBParam.m_ExpStr1) == 0 || strlen(pTrsc->m_Trsc_CBParam.m_ExtStr2) == 0 )
		return FALSE;

	//GUID(流水号),金币转出人，金币接收人，金币缴税人，网关ID，金币数量（交易），金币数量（税费）
	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_DEALCOIN_LOCALZONE, GetCmdFormat(CHECKSERVER_REQUEST_DEALCOIN_LOCALZONE),
		pTrsc->m_TrscID, pTrsc->m_TrscID, pTrsc->m_Trsc_CBParam.m_ExpStr1, pTrsc->m_Trsc_CBParam.m_ExtStr2,pTrsc->m_Trsc_CBParam.m_ExpStr1,
		DataServerMgr().m_WorldID, pTrsc->m_Trsc_CBParam.m_Money, pTrsc->m_Trsc_CBParam.m_Ext7,pTrsc->m_strExtParam);

	DataServerMgr().SendMsgToLoginServer(&pack);
	return TRUE;
}

BOOL CTrcsMgr::_ProcCostMoneySilver(Transac* pTrsc)
{
	if( !pTrsc )
		return FALSE;

	CPlayer* pPlayer = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Buyer );
	if( !pPlayer )
		return FALSE;
	//游戏币消耗 使用道具购买接口, 在消耗金币时,没有道具ID 使用流水号替代
	//GUID，流水号，道具名称，道具类型 ->即时（1：永久类，2：分次类，3：分摊类 4: 即时），数量,用户名，网关ID，有效天数，
	//                       （永久类和 即时类：传0；其他：传实际可用天数），价格
	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_BUYITEM, GetCmdFormat(CHECKSERVER_REQUEST_BUYITEM),
		pTrsc->m_TrscID, pTrsc->m_TrscID, pTrsc->m_strExtParam, pTrsc->m_ServiceID,pTrsc->m_Trsc_CBParam.m_nNum,
		pPlayer->GetUserName(), DataServerMgr().m_WorldID,pTrsc->m_Trsc_CBParam.m_nDay,pTrsc->m_Trsc_CBParam.m_Money );

	pPlayer->SendMsg(&pack);
	return TRUE;
}

BOOL CTrcsMgr::_ProcMoneyCostByUserName(Transac* pTrsc)
{
	if( !pTrsc )
		return FALSE;	
	if(strlen(pTrsc->m_Trsc_CBParam.m_UserName) == 0)
		return FALSE;
	CPlayer *pPlayer = PlayerMgr().GetPlayerByPID(pTrsc->m_Trsc_CBParam.m_Buyer);

	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_BUYITEM_OFFLINE, GetCmdFormat(CHECKSERVER_REQUEST_BUYITEM_OFFLINE),
		pTrsc->m_TrscID, pTrsc->m_TrscID, pTrsc->m_strExtParam, pTrsc->m_ServiceID,pTrsc->m_Trsc_CBParam.m_nNum,
		pTrsc->m_Trsc_CBParam.m_UserName, DataServerMgr().m_WorldID,pTrsc->m_Trsc_CBParam.m_nDay,pTrsc->m_Trsc_CBParam.m_Money );
	
	if(pPlayer)
		pPlayer->SendMsg(&pack);
	else
		DataServerMgr().SendMsgToLoginServer(&pack);
	return TRUE;

}

BOOL CTrcsMgr::_ProcUseProp( Transac* pTrsc )
{
	if( !pTrsc )
		return FALSE;	
	
	CPlayer *pPlayer = PlayerMgr().GetPlayerByPID(pTrsc->m_Trsc_CBParam.m_Buyer);

	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_USEITEM, GetCmdFormat(CHECKSERVER_REQUEST_USEITEM),
		pTrsc->m_TrscID, pTrsc->m_Trsc_CBParam.m_Ext6, pTrsc->m_Trsc_CBParam.m_UserName);

	if(pPlayer)
		pPlayer->SendMsg(&pack);
	else
		DataServerMgr().SendMsgToLoginServer(&pack);
	return TRUE;
}
//  检查物品卡
BOOL	CTrcsMgr::_ProcCheckGoodsCard(Transac* pTrsc )
{
	if( !pTrsc )
		return FALSE;	

	CPlayer *pPlayer = PlayerMgr().GetPlayerByPID(pTrsc->m_Trsc_CBParam.m_Buyer);

	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_CHECKGOODSCARD, GetCmdFormat(CHECKSERVER_REQUEST_CHECKGOODSCARD),
		pTrsc->m_TrscID, pTrsc->m_Trsc_CBParam.m_ExpStr1, pTrsc->m_Trsc_CBParam.m_UserName, DataServerMgr().m_WorldID);

	if(pPlayer)
		pPlayer->SendMsg(&pack);
	else
		DataServerMgr().SendMsgToLoginServer(&pack);
	return TRUE;
}

BOOL	CTrcsMgr::_ProcUseGoodsCard(Transac* pTrsc )
{
	if( !pTrsc )
		return FALSE;	

	CPlayer *pPlayer = PlayerMgr().GetPlayerByPID(pTrsc->m_Trsc_CBParam.m_Buyer);

	PACKET_COMMAND pack;
	pack.SetParam( CHECKSERVER_REQUEST_USEGOODSCARD, GetCmdFormat(CHECKSERVER_REQUEST_USEGOODSCARD),
		pTrsc->m_TrscID, pTrsc->m_Trsc_CBParam.m_ExpStr1, pTrsc->m_Trsc_CBParam.m_UserName, pTrsc->m_Trsc_CBParam.m_ExpStr3);

	if(pPlayer)
		pPlayer->SendMsg(&pack);
	else
		DataServerMgr().SendMsgToLoginServer(&pack);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

BOOL    CTrcsMgr::_Packet_SetPayID(PACKET_COMMAND* pPacket)
{
	if( !pPacket )
		return FALSE;
	TrscID	nTrscID;
	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&nTrscID);
	if(nTrscID <=0 )
		return FALSE;
	Log("GameServer 最终接收到DB 的流水号为 %I64d",nTrscID);
	SetTrscID(nTrscID);
	return TRUE;

}

BOOL CTrcsMgr::_Packet_BuyItem(PACKET_COMMAND* pPacket)
{
	if( !pPacket )
		return FALSE;

	TrscID	nTrscID = INVALID_TRSCID;
	int     nResult = INVALID_VALUE;
	int64	nMoney = 0;

	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&nTrscID,&nResult,&nMoney);

	Transac* pTrsc = _GetTransac( nTrscID );
	if( pTrsc )
	{
		CPlayer * pPlayer = PlayerMgr().GetPlayerByPID(pTrsc->m_Trsc_CBParam.m_Buyer);
 			if(nResult != PayServer_ReturnResult_OK && nResult != PayServer_ReturnResult_OrderIDRepeate)
 			{
				if (pTrsc->m_pTrscFailedCallFn)
				{
					pTrsc->m_pTrscFailedCallFn(pTrsc->m_Trsc_CBParam);
					if(pPlayer)
					{
						pPlayer->SendPayServerErrorMsg(nResult);
						Log("接收支付消息(购买 or 即时消耗) 失败：类型 %d, 流水号：%I64u 操作：%d 玩家姓名：%s 玩家账号：%s 返回结果: %d 剩余金额: %I64d ,备注:%s" , 
							pTrsc->m_OptID,pTrsc->m_TrscID,pTrsc->m_OptID, pPlayer->GetName(),pPlayer->GetUserName(),nResult,nMoney,pTrsc->m_strExtParam);
					}
				}
 				g_TransacPool().Free( pTrsc );
				
 				return FALSE;
 			}
			
			if( pTrsc->m_pTrscCallFn )
				pTrsc->m_pTrscCallFn( pTrsc->m_Trsc_CBParam );

			if(nResult == PayServer_ReturnResult_OrderIDRepeate)
			{
				Log("接收支付消息(成功) 第 %d 次：操作类型: %d, 流水号：%I64u 操作：%d,返回结果: %d ,备注: %s\n" , 
					pTrsc->m_SendCount,pTrsc->m_OptID, pTrsc->m_TrscID,pTrsc->m_OptID,nResult,pTrsc->m_strExtParam);
			}
			else
			{
				if(pTrsc->m_Trsc_CBParam.m_IsSetMoney == TRUE)
				{
					if(pPlayer)
						pPlayer->SetRemainMoney(nMoney);
				}
			}

		g_TransacPool().Free( pTrsc );
	}

	return TRUE;
}

BOOL CTrcsMgr::_Packet_SellItem(PACKET_COMMAND* pPacket)
{
	if(!pPacket)
		return FALSE;

	TrscID	nTrscID;
	int		nResult;
	int64	nMoney;
	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&nTrscID,&nResult,&nMoney);

	Transac* pTrsc = _GetTransac( nTrscID );
	if( pTrsc )
	{
		CPlayer * pPlayer = PlayerMgr().GetPlayerByPID(pTrsc->m_Trsc_CBParam.m_Seller);
		if(nResult != PayServer_ReturnResult_OK && nResult != PayServer_ReturnResult_OrderIDRepeate)
		{
			if(pPlayer)
			{
				pPlayer->SendPayServerErrorMsg(nResult);
				Log("接收支付消息：流水号：%I64u 操作：%d 玩家姓名：%s 玩家账号：%s 返回结果%d" ,
					pTrsc->m_TrscID,pTrsc->m_OptID, pPlayer->GetName(),pPlayer->GetUserName(),nResult);
			}
	
			g_TransacPool().Free( pTrsc );
			return FALSE;
		}

		if(pTrsc->m_pTrscCallFn)
			pTrsc->m_pTrscCallFn( pTrsc->m_Trsc_CBParam );

		if(nResult == PayServer_ReturnResult_OrderIDRepeate)
		{
			Log("接收支付消息(成功) 第 %d 次：操作类型: %d, 流水号：%I64u 操作：%d,返回结果: %d ,备注: %s\n" , 
				pTrsc->m_SendCount,pTrsc->m_OptID, pTrsc->m_TrscID,pTrsc->m_OptID,nResult,pTrsc->m_strExtParam);
		}
		else
		{
			if(pTrsc->m_Trsc_CBParam.m_IsSetMoney == TRUE)
			{
				if(pPlayer)
				{
					pPlayer->SetRemainMoney(nMoney);
				}
			}
		}

		g_TransacPool().Free( pTrsc );
	}

	return TRUE;
}

BOOL CTrcsMgr::_Packet_DragonConvertSilver(PACKET_COMMAND* pPacket)
{
	if(!pPacket)
		return FALSE;

	TrscID			nTrscID;
	int				nResult;
	Type_Money		nMoney;
	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&nTrscID,&nResult,&nMoney);

	Transac* pTrsc = _GetTransac( nTrscID );
	if( pTrsc )
	{
		CPlayer * pPlayer = PlayerMgr().GetPlayerByPID(pTrsc->m_Trsc_CBParam.m_Buyer);
		if(pPlayer)
		{
			if(nResult != PayServer_ReturnResult_OK && nResult != PayServer_ReturnResult_OrderIDRepeate)
			{
				pPlayer->SendPayServerErrorMsg(nResult);
				Log("龙币兑换返回失败 接收支付消息：流水号：%I64u 操作：%d 玩家姓名：%s 玩家账号：%s 返回结果%d" , 
					pTrsc->m_TrscID,pTrsc->m_OptID, pPlayer->GetName(),pPlayer->GetUserName(),nResult);
				g_TransacPool().Free( pTrsc );
				return FALSE;
			}
			

			if( pTrsc->m_pTrscCallFn)
				pTrsc->m_pTrscCallFn( pTrsc->m_Trsc_CBParam ); 
			
			pPlayer->SendPayServerErrorMsg(nResult);

			if(nResult == PayServer_ReturnResult_OrderIDRepeate)
			{
				Log("接收支付消息(成功) 第 %d 次：操作类型: %d, 流水号：%I64u 操作：%d,返回结果: %d ,备注: %s\n" , 
					pTrsc->m_SendCount,pTrsc->m_OptID, pTrsc->m_TrscID,pTrsc->m_OptID,nResult,pTrsc->m_strExtParam);
			}
			else
			{
				if(pTrsc->m_Trsc_CBParam.m_IsSetMoney == TRUE)
				{
					pPlayer->SetRemainMoney(nMoney);
				}
			}
			pPlayer->RequestGetDragonCoin();

			
			// Log("接收支付消息：流水号：%I64u 操作：%d 玩家姓名：%s 玩家账号：%s 返回结果%d" , pTrsc->m_TrscID,pTrsc->m_OptID, pPlayer->GetName(),pPlayer->GetUserName(),nResult);
		}
		
		g_TransacPool().Free( pTrsc );
	}

	return TRUE;
}


BOOL CTrcsMgr::_Packet_QueryDragonCoin(PACKET_COMMAND* pPacket)
{
	if(!pPacket)
		return FALSE;

	TrscID	nTrscID;
	int		nResult;
	Type_Money		nMoney;
	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&nTrscID,&nResult,&nMoney);

	Transac* pTrsc = _GetTransac( nTrscID );
	if( pTrsc )
	{
		CPlayer * pPlayer = PlayerMgr().GetPlayerByPID(pTrsc->m_Trsc_CBParam.m_Buyer);
		if(pPlayer)
		{
			if(nResult != PayServer_ReturnResult_OK && nResult != PayServer_ReturnResult_OrderIDRepeate)
			{
				pPlayer->SendPayServerErrorMsg(nResult);
				g_TransacPool().Free( pTrsc );
				return FALSE;
			}

			if(nResult == PayServer_ReturnResult_OrderIDRepeate)
			{
				Log("接收支付消息(成功) 第 %d 次：操作类型: %d, 流水号：%I64u 操作：%d,返回结果: %d ,备注: %s\n" , 
					pTrsc->m_SendCount,pTrsc->m_OptID, pTrsc->m_TrscID,pTrsc->m_OptID,nResult,pTrsc->m_strExtParam);
			}

			if( pTrsc->m_pTrscCallFn )
			{
				pTrsc->m_Trsc_CBParam.m_Ext1 = nMoney;
				pTrsc->m_pTrscCallFn( pTrsc->m_Trsc_CBParam );
			}
		}

		g_TransacPool().Free( pTrsc );
	}

	return TRUE;
}

BOOL    CTrcsMgr::_Packet_Common(PACKET_COMMAND* pPacket)
{
	if(!pPacket)
		return FALSE;

	TrscID	   nTrscID;
	int		   nResult;
	Type_Money nMoney;
	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&nTrscID,&nResult,&nMoney);

	Transac* pTrsc = _GetTransac( nTrscID );
	if( pTrsc )
	{
			if(nResult != PayServer_ReturnResult_OK && nResult != PayServer_ReturnResult_OrderIDRepeate)
			{
				Log("接收支付消息(返回失败)：操作类型: %d, 流水号：%I64u 操作：%d,返回结果: %d ,备注: %s\n" , 
						pTrsc->m_OptID, pTrsc->m_TrscID,pTrsc->m_OptID,nResult,pTrsc->m_strExtParam);
				g_TransacPool().Free( pTrsc );
				return FALSE;
			}
			if(nResult == PayServer_ReturnResult_OrderIDRepeate)
			{
				Log("接收支付消息(成功) 第 %d 次：操作类型: %d, 流水号：%I64u 操作：%d,返回结果: %d ,备注: %s\n" , 
					pTrsc->m_SendCount,pTrsc->m_OptID, pTrsc->m_TrscID,pTrsc->m_OptID,nResult,pTrsc->m_strExtParam);
			}
			if( pTrsc->m_pTrscCallFn )
			{
				pTrsc->m_Trsc_CBParam.m_RemainMoney = nMoney;
				pTrsc->m_pTrscCallFn( pTrsc->m_Trsc_CBParam );
			}
			
			//Log("玩家: %s 操作之后账号余额:  %I64u 返回结果: %d %s",pPlayer->GetUserName(), nMoney,nResult,pTrsc->m_strExtParam);
			//	Log("接收支付消息：流水号：%I64u 操作：%d 玩家姓名：%s 玩家账号：%s 返回结果%d" , pTrsc->m_TrscID,pTrsc->m_OptID, pPlayer->GetName(),pPlayer->GetUserName(),nResult);

		g_TransacPool().Free( pTrsc );
	}

	return TRUE;

}

BOOL    CTrcsMgr::_Packet_QrSaveCoin(PACKET_COMMAND* pPacket)
{
	if(!pPacket)
		return FALSE;

	TrscID	nTrscID;
	int		nResult;
	int64	nMoney;
	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&nTrscID,&nResult,&nMoney);

	Transac* pTrsc = _GetTransac( nTrscID );
	if( pTrsc )
	{
		CPlayer * pPlayer = PlayerMgr().GetPlayerByPID(pTrsc->m_Trsc_CBParam.m_Buyer);
		if(nResult != PayServer_ReturnResult_OK && nResult != PayServer_ReturnResult_OrderIDRepeate)
		{
			if(pPlayer)
			{
				pPlayer->SendPayServerErrorMsg(nResult);
				Log("接收支付消息 (查询存储金币失败)：流水号：%I64u 操作：%d 玩家姓名：%s 玩家账号：%s 返回结果%d" , 
					pTrsc->m_TrscID,pTrsc->m_OptID, pPlayer->GetName(),pPlayer->GetUserName(),nResult);
			}
			g_TransacPool().Free( pTrsc );
			return FALSE;
		}

		if(nResult == PayServer_ReturnResult_OrderIDRepeate)
		{
			Log("接收支付消息(成功) 第 %d 次：操作类型: %d, 流水号：%I64u 操作：%d,返回结果: %d ,备注: %s\n" , 
				pTrsc->m_SendCount,pTrsc->m_OptID, pTrsc->m_TrscID,pTrsc->m_OptID,nResult,pTrsc->m_strExtParam);
		}

		if( pTrsc->m_pTrscCallFn )
		{
			pTrsc->m_Trsc_CBParam.m_Ext6 = nMoney;
			pTrsc->m_pTrscCallFn( pTrsc->m_Trsc_CBParam );
		}
		//	Log("接收支付消息：流水号：%I64u 操作：%d 玩家姓名：%s 玩家账号：%s 返回结果%d" , pTrsc->m_TrscID,pTrsc->m_OptID, pPlayer->GetName(),pPlayer->GetUserName(),nResult);

		g_TransacPool().Free( pTrsc );
	}

	return TRUE;
}

BOOL	CTrcsMgr::_Packet_UseProp(PACKET_COMMAND* pPacket)
{
	if(!pPacket)
		return FALSE;

	TrscID nTrscID;
	int nResult;

	pPacket->GetParam(GetCmdFormat(pPacket->Type()), &nTrscID, &nResult);

	Transac* pTrsc = _GetTransac( nTrscID );
	if( pTrsc )
	{
		CPlayer* pPlayer = PlayerMgr().GetPlayerByPID( pTrsc->m_Trsc_CBParam.m_Buyer);
		if(pPlayer)
		{
			if( nResult != PayServer_ReturnResult_OK && nResult != PayServer_ReturnResult_OrderIDRepeate)
			{
				if( pTrsc->m_pTrscFailedCallFn )
					pTrsc->m_pTrscFailedCallFn(pTrsc->m_Trsc_CBParam);
				// Log("接收支付消息：流水号：%I64u 操作：%d 玩家姓名：%s 玩家账号：%s 返回结果%d" , pTrsc->m_TrscID,pTrsc->m_OptID, pPlayer->GetName(),pPlayer->GetUserName(),nResult);
				g_TransacPool().Free( pTrsc );
				return FALSE;
			}

			if(nResult == PayServer_ReturnResult_OrderIDRepeate)
			{
				Log("接收支付消息(成功) 第 %d 次：操作类型: %d, 流水号：%I64u 操作：%d,返回结果: %d ,备注: %s\n" , 
					pTrsc->m_SendCount,pTrsc->m_OptID, pTrsc->m_TrscID,pTrsc->m_OptID,nResult,pTrsc->m_strExtParam);
			}

			if( pTrsc->m_pTrscCallFn )
			{
				pTrsc->m_pTrscCallFn( pTrsc->m_Trsc_CBParam );
			}
			// Log("接收支付消息：流水号：%I64u 操作：%d 玩家姓名：%s 玩家账号：%s 返回结果%d" , pTrsc->m_TrscID,pTrsc->m_OptID, pPlayer->GetName(),pPlayer->GetUserName(),nResult);
		}
		g_TransacPool().Free( pTrsc );
	}
	return TRUE;
}

BOOL	CTrcsMgr::_Packet_DealCoin(PACKET_COMMAND* pPacket)
{
	if(!pPacket)
		return FALSE;

	TrscID			nTrscID;
	int				nResult;
	Type_Money		nMoneyB;
	Type_Money		nMoneyS;
	Type_Money		nMoneyC;
	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&nTrscID,&nResult,&nMoneyB,&nMoneyS,&nMoneyC);

	Transac* pTrsc = _GetTransac( nTrscID );
	if( pTrsc )
	{
		CPlayer * pPlayerB = PlayerMgr().GetPlayerByPID(pTrsc->m_Trsc_CBParam.m_Buyer);
		CPlayer * pPlayerS = PlayerMgr().GetPlayerByPID(pTrsc->m_Trsc_CBParam.m_Seller);
		if(nResult != PayServer_ReturnResult_OK && nResult != PayServer_ReturnResult_OrderIDRepeate)
		{
			if(pTrsc->m_pTrscFailedCallFn)
				pTrsc->m_pTrscFailedCallFn(pTrsc->m_Trsc_CBParam);

			if(pPlayerB)
			{
				pPlayerB->SendPayServerErrorMsg(nResult);
				Log("接收支付消息(交易返回失败)：玩家(B): %s,PID: %I64d, 流水号：%I64u 操作：%d 返回结果%d" , pPlayerB->GetName(),pPlayerB->GetPID(),pTrsc->m_TrscID,pTrsc->m_OptID,nResult);
			}
			if(pPlayerS)
			{
				pPlayerS->SendPayServerErrorMsg(nResult);
				Log("接收支付消息(交易返回失败)：玩家(S): %s,PID: %I64d, 流水号：%I64u 操作：%d 返回结果%d" , pPlayerS->GetName(),pPlayerS->GetPID(),pTrsc->m_TrscID,pTrsc->m_OptID,nResult);
			}

				g_TransacPool().Free( pTrsc );
				return FALSE;
		}
		else
		{
			if( pTrsc->m_pTrscCallFn )
			{
				pTrsc->m_pTrscCallFn( pTrsc->m_Trsc_CBParam );
			}

			if(nResult == PayServer_ReturnResult_OrderIDRepeate)
			{
				Log("接收支付消息(成功) 第 %d 次：操作类型: %d, 流水号：%I64u 操作：%d,返回结果: %d ,备注: %s\n" , 
					pTrsc->m_SendCount,pTrsc->m_OptID, pTrsc->m_TrscID,pTrsc->m_OptID,nResult,pTrsc->m_strExtParam);
			}
			else
			{
				if(pTrsc->m_Trsc_CBParam.m_IsSetMoney == TRUE)
				{
					if(pPlayerB)
						pPlayerB->SetRemainMoney(nMoneyB);
					if(pPlayerS)
						pPlayerS->SetRemainMoney(nMoneyS);
				}
			}
		}
		g_TransacPool().Free( pTrsc );
	}
	return TRUE;
}

BOOL	CTrcsMgr::_Packet_CheckGoodsCard(PACKET_COMMAND* pPacket)
{
	if(!pPacket)
		return FALSE;

	TrscID			nTrscID;
	int				nResult,nTemplateID;
	int64			iExtPoint[8] = {0};

	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&nTrscID,
		&nResult,&nTemplateID,&iExtPoint[0],&iExtPoint[1],&iExtPoint[2],&iExtPoint[3],&iExtPoint[4],&iExtPoint[5],&iExtPoint[6],&iExtPoint[7]);

	Transac* pTrsc = _GetTransac( nTrscID );
	if( pTrsc )
	{
		CPlayer * pPlayer = PlayerMgr().GetPlayerByPID(pTrsc->m_Trsc_CBParam.m_Buyer);
		if(nResult != PayServer_ReturnResult_OK && nResult != PayServer_ReturnResult_OrderIDRepeate)
		{
			if(pTrsc->m_pTrscFailedCallFn)
				pTrsc->m_pTrscFailedCallFn(pTrsc->m_Trsc_CBParam);

			if(pPlayer)
				pPlayer->SendPayServerErrorMsg(nResult);
			Log("接收支付消息（检查物品卡失败）：流水号：%I64u 操作：%d 玩家姓名：%s 玩家账号：%s 返回结果%d" , 
				pTrsc->m_TrscID,pTrsc->m_OptID, pPlayer->GetName(),pPlayer->GetUserName(),nResult);

			g_TransacPool().Free( pTrsc );
			return FALSE;
		}
		else
		{
			if(nResult == PayServer_ReturnResult_OrderIDRepeate)
			{
				Log("接收支付消息(成功) 第 %d 次：操作类型: %d, 流水号：%I64u 操作：%d,返回结果: %d ,备注: %s\n" , 
					pTrsc->m_SendCount,pTrsc->m_OptID, pTrsc->m_TrscID,pTrsc->m_OptID,nResult,pTrsc->m_strExtParam);
			}

			if( pTrsc->m_pTrscCallFn )
			{
				for( int i =0; i< 8; i++)
				{
					pPlayer->GetAttribMgr()->SetAttribInt64(Role_Attrib_UserExtPoint1 + i, iExtPoint[i]);
				}
				pTrsc->m_Trsc_CBParam.m_Ext1 = nTemplateID;
				pTrsc->m_pTrscCallFn( pTrsc->m_Trsc_CBParam );
			}
		}
		g_TransacPool().Free( pTrsc );
	}
	return TRUE;
}
BOOL	CTrcsMgr::_Packet_UseGoodsCard(PACKET_COMMAND* pPacket)
{
	if(!pPacket)
		return FALSE;

	TrscID			nTrscID;
	int				nResult;
	int				nGoodsCardType;

	pPacket->GetParam(GetCmdFormat(pPacket->Type()),&nTrscID,&nResult,&nGoodsCardType);

	Transac* pTrsc = _GetTransac( nTrscID );
	if( pTrsc )
	{
		CPlayer * pPlayer = PlayerMgr().GetPlayerByPID(pTrsc->m_Trsc_CBParam.m_Buyer);
		if(nResult != PayServer_ReturnResult_OK && nResult != PayServer_ReturnResult_OrderIDRepeate)
		{
			if(pTrsc->m_pTrscFailedCallFn)
				pTrsc->m_pTrscFailedCallFn(pTrsc->m_Trsc_CBParam);

			if(pPlayer)
				pPlayer->SendPayServerErrorMsg(nResult);
			Log("接收支付消息（使用物品卡失败）：流水号：%I64u 操作：%d 玩家姓名：%s 玩家账号：%s 返回结果%d" ,
				pTrsc->m_TrscID,pTrsc->m_OptID, pPlayer->GetName(),pPlayer->GetUserName(),nResult);

			g_TransacPool().Free( pTrsc );
			return FALSE;
		}
		else
		{
			if(nResult == PayServer_ReturnResult_OrderIDRepeate)
			{
				Log("接收支付消息(成功) 第 %d 次：操作类型: %d, 流水号：%I64u 操作：%d,返回结果: %d ,备注: %s\n" , 
					pTrsc->m_SendCount,pTrsc->m_OptID, pTrsc->m_TrscID,pTrsc->m_OptID,nResult,pTrsc->m_strExtParam);
			}

			if( pTrsc->m_pTrscCallFn )
			{
				pTrsc->m_Trsc_CBParam.m_Ext1 = nGoodsCardType;
				pTrsc->m_pTrscCallFn( pTrsc->m_Trsc_CBParam );
			}
		}
		g_TransacPool().Free( pTrsc );
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

BOOL CTrcsMgr::Request_PlayerStoreCoin(PersonID PID,const char *szUserName,int nStoreType,Type_Money nMoney,const char *szComments)
{

	if(nStoreType < Storage_SilverType_PersonCar || nStoreType > Storage_SilverType_End)
		return FALSE;

	if(nMoney <= 0 )
		return FALSE;

	Transac pTransac;
	//strcpy(pTransac.m_strExtParam,szComments);
	Q_strlcpy(pTransac.m_strExtParam,sizeof(pTransac.m_strExtParam),szComments);
	CPlayer *pPlayer = PlayerMgr().GetPlayerByPID(PID);
	if(pPlayer)
	{
		Q_strlcpy(pTransac.m_Trsc_CBParam.m_UserName,sizeof(pTransac.m_Trsc_CBParam.m_UserName),pPlayer->GetUserName());
		//strcpy(pTransac.m_Trsc_CBParam.m_UserName,pPlayer->GetUserName());
	}
	else
	{
		Q_strlcpy(pTransac.m_Trsc_CBParam.m_UserName,sizeof(pTransac.m_Trsc_CBParam.m_UserName),szUserName);
		//strcpy(pTransac.m_Trsc_CBParam.m_UserName,szUserName);
	}

	if(strlen(pTransac.m_Trsc_CBParam.m_UserName) == 0)
		return FALSE;
	
	pTransac.m_OptID = Opt_SaveCoin;
	pTransac.m_Trsc_CBParam.m_Buyer = PID;
	pTransac.m_Trsc_CBParam.m_Ext1 = nStoreType;
	pTransac.m_Trsc_CBParam.m_Ext6 = nMoney;
	return CTrcsMgr::Instance().RequestTransac(pTransac);

}

BOOL CTrcsMgr::Request_PlayerDrawCoin(PersonID PID,const char *szUserName,int nStoreType,Type_Money nMoney,const char *szComments)
{

	if(nStoreType < Storage_SilverType_PersonCar || nStoreType > Storage_SilverType_End)
		return FALSE;

	if(nMoney <= 0 )
		return FALSE;

	Transac pTransac;
	//strcpy(pTransac.m_strExtParam,szComments);
	Q_strlcpy(pTransac.m_strExtParam,sizeof(pTransac.m_strExtParam),szComments);
	CPlayer *pPlayer = PlayerMgr().GetPlayerByPID(PID);
	if(pPlayer)
	{
		Q_strlcpy(pTransac.m_Trsc_CBParam.m_UserName,sizeof(pTransac.m_Trsc_CBParam.m_UserName),pPlayer->GetUserName())
		//strcpy(pTransac.m_Trsc_CBParam.m_UserName,pPlayer->GetUserName());
	}
	else
	{
		Q_strlcpy(pTransac.m_Trsc_CBParam.m_UserName,sizeof(pTransac.m_Trsc_CBParam.m_UserName),szUserName)
		//strcpy(pTransac.m_Trsc_CBParam.m_UserName,szUserName);
	}

	if(strlen(pTransac.m_Trsc_CBParam.m_UserName) == 0)
		return FALSE;
	pTransac.m_OptID = Opt_TakeCoin;
	pTransac.m_Trsc_CBParam.m_Buyer = PID;
	pTransac.m_Trsc_CBParam.m_Ext1 = nStoreType;
	pTransac.m_Trsc_CBParam.m_Ext6 = nMoney;
	return CTrcsMgr::Instance().RequestTransac(pTransac);
}


BOOL CTrcsMgr::Request_DealMoneyToPlayerByUserName( const char* strFromname, const char* strToUserName, Type_Money nMoney, Type_Money nShui, PersonID PID)
{
	if( !strToUserName || strlen(strToUserName) <= 0 )
		return FALSE;

	Transac sTransac;
	sTransac.m_OptID = Opt_DealCoinByUserName;
	sTransac.m_Trsc_CBParam.m_Money = _abs64(nMoney);
	sTransac.m_Trsc_CBParam.m_Buyer = PID;
	sTransac.m_Trsc_CBParam.m_Ext7 = nShui;

	/*strcpy(sTransac.m_Trsc_CBParam.m_ExpStr1, strFromname);
	strcpy(sTransac.m_Trsc_CBParam.m_ExtStr2, strToUserName);*/

	Q_strlcpy(sTransac.m_Trsc_CBParam.m_ExpStr1,sizeof(sTransac.m_Trsc_CBParam.m_ExpStr1), strFromname);
	Q_strlcpy(sTransac.m_Trsc_CBParam.m_ExtStr2,sizeof(sTransac.m_Trsc_CBParam.m_ExtStr2), strToUserName);

	return CTrcsMgr::Instance().RequestTransac( sTransac );
}

extern void _G_SendSilverMail(Transac_CallBackParam &TrascCBParam)	//发送邮件
{	
	RequestSendSystemMail_PropID(TrascCBParam.m_Ext9,"",TrascCBParam.m_ExpStr1,INVALID_PROPID,TrascCBParam.m_Ext10,1,FALSE,TrascCBParam.m_ExtStr2);
}

extern void _G_CallBack_StoreCoin(Transac_CallBackParam &TrascCBParam)
{
	Transac pTransac;
	/*strcpy(pTransac.m_strExtParam,TrascCBParam.m_ExpStr5);
	strcpy(pTransac.m_Trsc_CBParam.m_UserName,TrascCBParam.m_ExpStr6);*/
	
	Q_strlcpy(pTransac.m_strExtParam,sizeof(pTransac.m_strExtParam),TrascCBParam.m_ExpStr5);
	Q_strlcpy(pTransac.m_Trsc_CBParam.m_UserName,sizeof(pTransac.m_Trsc_CBParam.m_UserName),TrascCBParam.m_ExpStr6);

	if(strlen(pTransac.m_Trsc_CBParam.m_UserName) == 0)
		return;
	
	pTransac.m_OptID = Opt_SaveCoin;
	pTransac.m_Trsc_CBParam.m_Buyer = INVALID_VALUE64;
	pTransac.m_Trsc_CBParam.m_Ext1 = TrascCBParam.m_Ext2;
	pTransac.m_Trsc_CBParam.m_Ext6 = TrascCBParam.m_Ext3;
    CTrcsMgr::Instance().RequestTransac(pTransac);	

}

extern void _G_CallBack_CostCoin(Transac_CallBackParam &TrascCBParam) //消耗金币
{
	Transac pTransac;
	/*strcpy(pTransac.m_strExtParam,TrascCBParam.m_ExpStr5);
	strcpy(pTransac.m_Trsc_CBParam.m_UserName,TrascCBParam.m_ExpStr6);*/
	
	Q_strlcpy(pTransac.m_strExtParam,sizeof(pTransac.m_strExtParam),TrascCBParam.m_ExpStr5);
	Q_strlcpy(pTransac.m_Trsc_CBParam.m_UserName,sizeof(pTransac.m_Trsc_CBParam.m_UserName),TrascCBParam.m_ExpStr6);

	if(strlen(pTransac.m_Trsc_CBParam.m_UserName) == 0)
		return;
	
	pTransac.m_OptID = Opt_CostMoneyByUserName;
	pTransac.m_Trsc_CBParam.m_Buyer = INVALID_VALUE64;
	pTransac.m_ServiceID = Svic_Immediate;
	pTransac.m_Trsc_CBParam.m_nNum = 1;
//	pTransac.m_Trsc_CBParam.m_Buyer = PID;
	pTransac.m_Trsc_CBParam.m_Money = TrascCBParam.m_Ext9;
	pTransac.m_Trsc_CBParam.m_nDay = 0;		
    CTrcsMgr::Instance().RequestTransac(pTransac);	
	
}

extern void _G_CallBack_StorageExchange(Transac_CallBackParam &TrascCBParam)//换族长时交换存储银子
{
	Transac sTransac;
	sTransac.m_OptID = Opt_DealCoinByUserName;
	sTransac.m_Trsc_CBParam.m_Money = TrascCBParam.m_Ext9;
	sTransac.m_Trsc_CBParam.m_Ext7 = 0;
	/*strcpy(sTransac.m_Trsc_CBParam.m_ExpStr1, TrascCBParam.m_ExpStr1);
	strcpy(sTransac.m_Trsc_CBParam.m_ExtStr2, TrascCBParam.m_ExtStr2);
	strcpy(sTransac.m_strExtParam, "更换族长时交换家族镖局资金");*/
	
	Q_strlcpy(sTransac.m_Trsc_CBParam.m_ExpStr1,sizeof(sTransac.m_Trsc_CBParam.m_ExpStr1), TrascCBParam.m_ExpStr1);
	Q_strlcpy(sTransac.m_Trsc_CBParam.m_ExtStr2,sizeof(sTransac.m_Trsc_CBParam.m_ExtStr2), TrascCBParam.m_ExtStr2);
	Q_strlcpy(sTransac.m_strExtParam,sizeof(sTransac.m_strExtParam), "更换族长时交换家族镖局资金");


	sTransac.m_pTrscCallFn = _G_CallBack_StoreCoin;
	sTransac.m_Trsc_CBParam.m_Ext2 = Storage_SilverType_EscortRunning;
	sTransac.m_Trsc_CBParam.m_Ext3 = TrascCBParam.m_Ext9;
	/*strcpy(sTransac.m_Trsc_CBParam.m_ExpStr6,TrascCBParam.m_ExtStr2);
	strcpy(sTransac.m_Trsc_CBParam.m_ExpStr5, "镖局运营资金存入");*/

	Q_strlcpy(sTransac.m_Trsc_CBParam.m_ExpStr6,sizeof(sTransac.m_Trsc_CBParam.m_ExpStr6),TrascCBParam.m_ExtStr2);
	Q_strlcpy(sTransac.m_Trsc_CBParam.m_ExpStr5,sizeof(sTransac.m_Trsc_CBParam.m_ExpStr5), "镖局运营资金存入");

	CTrcsMgr::Instance().RequestTransac( sTransac );
}

extern void _G_CallBack_SendEsortCompeteFailMoney(Transac_CallBackParam &TrascCBParam)   //返还竞标失败银子
{
	Transac sTransac;
	sTransac.m_OptID = Opt_CostMoneyByUserName;
	sTransac.m_ServiceID = Svic_Immediate;	
	sTransac.m_Trsc_CBParam.m_nNum = 1;
	sTransac.m_Trsc_CBParam.m_Money = TrascCBParam.m_Ext11;
	sTransac.m_Trsc_CBParam.m_Buyer = INVALID_PID;
	sTransac.m_Trsc_CBParam.m_nDay = 0;
	Q_strlcpy(sTransac.m_Trsc_CBParam.m_UserName,sizeof(sTransac.m_Trsc_CBParam.m_UserName),TrascCBParam.m_UserName);
	Q_strlcpy(sTransac.m_strExtParam,sizeof(sTransac.m_strExtParam),"家族竞标失败扣除手续费");

	sTransac.m_pTrscCallFn = _G_SendSilverMail;
	sTransac.m_Trsc_CBParam.m_Ext9  = TrascCBParam.m_Ext9; //收邮件的PID
	sTransac.m_Trsc_CBParam.m_Ext10 = TrascCBParam.m_Ext10;  //邮件附加的金钱
	Q_strlcpy(sTransac.m_Trsc_CBParam.m_ExpStr1,sizeof(sTransac.m_Trsc_CBParam.m_ExpStr1),"家族镖局竞标失败，返还家族镖局竞标资金。\n为防止恶意行为，返还金额相当于竞标投入金额的99%。");		//邮件文字
	Q_strlcpy(sTransac.m_Trsc_CBParam.m_ExtStr2,sizeof(sTransac.m_Trsc_CBParam.m_ExtStr2),TrascCBParam.m_UserName);	//邮件资金支付账号
	sTransac.m_Trsc_CBParam.m_IsSetMoney = FALSE;

	CTrcsMgr::Instance().RequestTransac(sTransac);
}
#endif
