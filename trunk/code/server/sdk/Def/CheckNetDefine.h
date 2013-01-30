#pragma	  once

#define		CN_SUCCESS					1000	//执行成功
#define		CN_FAIL						1001	//执行失败
#define		CN_ARGS_ERROR				1002	//输入参数错误
	//
#define		CN_ACCOUNT_EXISTS			1101	//账号在会员库中已存在
#define		CN_ACCOUNT_NOT_EXISTS		1102	//账号在会员库中不存在
//#define		CN_NODEFINE					1103	//账号在产品库中已存在
//#define		CN_NODEFINE		1104	//账号在产品库中不存在
#define		CN_ACCOUNT_FREEZE		    1105	//账号已冻结（产品库）  //暂作为游戏停测
//#define		CN_NODEFINE		1106	//账号未冻结（产品库）
//#define		CN_NODEFINE		1107	//账号已纳入防沉迷（产品库）
//#define		CN_NODEFINE		1108	//账号未纳入防沉迷（产品库）
//#define		CN_NODEFINE		1109	//账号已激活（产品库）
#define     CN_ACCOUNT_NOT_ACTIVE       1110	//账号未激活（产品库）
#define			CN_ONLINE		1111	//账号在线（产品库）
//#define		CN_NODEFINE		1112	//账号离线（产品库）
//#define		CN_NODEFINE		1113	//防沉迷信息只能补充一次
//#define		CN_NODEFINE		1114	//账号未绑定身份证信息

#define		   CN_AP_NOT_MATCH	1201	//账号密码不匹配
//#define		CN_NODEFINE		1202	//账号密码匹配正确
//#define		CN_NODEFINE		1203	//账号密保不匹配
//#define		CN_NODEFINE		1204	//账号密保匹配正确
//#define		CN_NODEFINE		1205	//账号已绑定密保
//#define		CN_NODEFINE		1206	//账号未绑定密保卡
//#define		CN_NODEFINE		1207	//账号未绑定任何密保
//#define		CN_NODEFINE		1208	//密保卡已冻结
//	//
//#define		CN_NODEFINE		1301	//账号不能激活当前产品
//#define		CN_NODEFINE		1302	//账号允许激活当前产品
//#define		CN_NODEFINE		1303	//账号不允许登录当前产品（18禁）
//#define		CN_NODEFINE		1304	//账号允许登录当前产品（18禁）
//#define		CN_NODEFINE		1305	//账号不能充值当前产品
//#define		CN_NODEFINE		1306	//区服信息不正确
//#define		CN_NODEFINE		1307	//当前在线人数达到设定上限（禁止登陆）
//	//
//#define		CN_NODEFINE		1401	//积分不足
//#define		CN_NODEFINE		1402	//积分充足
//#define		CN_NODEFINE		1403	//余额不足
//#define		CN_NODEFINE		1404	//余额充足
//#define		CN_NODEFINE		1405	//扩展点不足
//#define		CN_NODEFINE		1406	//扩展点充足
//#define		CN_NODEFINE		1407	//龙币不足
//#define		CN_NODEFINE		1408	//龙币充足
//	//
//#define		CN_NODEFINE		1501	//订单号已存在（充值/道具/金币交易）
//#define		CN_NODEFINE		1502	//道具已购买
//#define		CN_NODEFINE		1503	//道具已使用
//#define		CN_NODEFINE		1504	//道具已过期
//#define		CN_NODEFINE		1505	//道具类型错误
//#define		CN_NODEFINE		1506	//道具不存在
//#define		CN_NODEFINE		1507	//订单号不存在
//#define		CN_NODEFINE		1508	//订单号已冻结
//	//
//#define		CN_NODEFINE		1601	//物品卡不存在
//#define		CN_NODEFINE		1602	//物品卡已过期
//#define		CN_NODEFINE		1603	//物品卡已使用
//	//
//#define		CN_NODEFINE		1701	//激活码不存在
//#define		CN_NODEFINE		1702	//激活码已使用
//#define		CN_NODEFINE		1703	//激活码已过期
//	//
//#define		CN_NODEFINE		1801	//金币订单不存在
//#define		CN_NODEFINE		1802	//金币订单已撤销
//#define		CN_NODEFINE		1803	//金币订单已交易
//#define		CN_NODEFINE		1804	//金币订单已冻结
//#define		CN_NODEFINE		1805	//金币订单状态错误
//#define		CN_NODEFINE		1806	//交易支付方账号被冻结
//#define		CN_NODEFINE		1807	//交易获取方账号被冻结
//#define		CN_NODEFINE		1808	//交易支付方账号不存在
//#define		CN_NODEFINE		1809	//交易获取方账号不存在
