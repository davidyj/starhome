#include "StdAfx.h"
#include "CommData.h"
#include "utlvector.h"
#include "random.h"
#include "memdbgon.h"

int ConvertGBKToUTF8(char* strGBK, char* strDestUTF8, int nMaxSize )
{
	int len=MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, NULL,0);
	WCHAR  *wszUtf8 = new WCHAR[nMaxSize + 1];
	if(!wszUtf8)
	{
		assert(0);
		Log("字符转换 new 失败");
		return 0;
	}
	memset(wszUtf8, 0, sizeof(WCHAR) * (nMaxSize + 1));
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, wszUtf8, nMaxSize);

	len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = new char[nMaxSize + 1];
	if(!szUtf8)
	{
		assert(0);
		Log("字符转换 new 失败");
		return 0;
	}
	memset(szUtf8, 0, sizeof(char) * (nMaxSize + 1));
	WideCharToMultiByte (CP_UTF8, 0, wszUtf8, -1, szUtf8, nMaxSize, NULL,NULL);
	if((len-1) <= nMaxSize)	// len -1 表示 去掉最后一个\0 nMaxSize  不带\0
	{
		memcpy(strDestUTF8,szUtf8,nMaxSize);
	}
	else
	{
		assert(0);
		Log("转换目标存储内存数组过小");
		strDestUTF8[0] = '\0';
	}

	SAFE_DELETE(wszUtf8);
	SAFE_DELETE(szUtf8);
	return strlen(strDestUTF8);
} 

int ConvertUTF8ToGBK(char* strUtf8, char* strDestGBK, int nMaxSize )
{
	int len=MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, NULL,0);
	WCHAR *wszGBK = new WCHAR[nMaxSize + 1];
	if(!wszGBK)
	{
		assert(0);
		Log("字符转换 new 失败");
		return 0;
	}
	memset(wszGBK, 0, sizeof(WCHAR) * (nMaxSize + 1));
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, wszGBK, nMaxSize);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[nMaxSize + 1];
	if(!szGBK)
	{
		assert(0);
		Log("字符转换 new 失败");
		return 0;
	}
	memset(szGBK, 0, sizeof(char) * (nMaxSize + 1));
	len = WideCharToMultiByte (CP_ACP, 0, wszGBK, -1, szGBK, nMaxSize, NULL,NULL);
	
	if((len-1) <= nMaxSize)		// len -1 表示 去掉最后一个\0 nMaxSize  不带\0
	{
		memcpy(strDestGBK,szGBK,nMaxSize);
	}
	else
	{
		assert(0);
		Log("转换目标存储内存数组过小");
		strDestGBK[0] = '\0';
	}

	SAFE_DELETE(wszGBK);
	SAFE_DELETE(szGBK);
	return strlen(strDestGBK);
}

//////////////////////////////////
// 是否作用于使用者
// nEffectID		: 作用的ID
BOOL IsSrcEffect( int nEffectID )
{
	if( nEffectID < EFFECT_LIMIT )
		return TRUE;
	return FALSE;
}
//////////////////////////////
// 是否作用于目的者
// nEffectID		: 作用的ID
BOOL IsDestEffect( int nEffectID )
{
	if( nEffectID > EFFECT_LIMIT )
		return TRUE;
	return FALSE;
}

ATTRIB_MAP AttribTabble[]=
{
	//////////////////////////////////////////////////
	///基础属性增加 
	//////////////////////////////////////////////////	
	{ Role_Attrib_Hp,							"当前生命"},
	{ Role_Attrib_MaxHp,						"生命上限"},
	{ Role_Attrib_HpRegen,						"生命回复速度"},

	{ Role_Attrib_Mp	,						"当前法力"},
	{ Role_Attrib_MaxMp,						"法力上限"},
	{ Role_Attrib_MpRegen,						"法力回复速度"},

	//{ Role_Attirb_Energy,						"当前能量"},
	//{ Role_Attrib_MaxEnergy,					"能量上限"},
	//{ Role_Attrib_EnergyRegen,				"能量回复速度"},

	//{ Role_Attrib_Rage,						"当前怒气"},
	//{ Role_Attrib_MaxRage,					"怒气上限"},
	//{ Role_Attrib_RageRegen,					"怒气回复速度"},

	{ Role_Attrib_Waigong,						"外功"},
	{ Role_Attrib_Neigong,						"内功"},
	{ Role_Attrib_Shenfa,						"身法"},	
	{ Role_Attrib_Zhenqi,						"真气"},	
	{ Role_Attrib_Jingu,						"筋骨"},	


	//////////////////////////////////////////////////
	///基础属性百分比增加
	//////////////////////////////////////////////////	
	{ Role_Attrib_MaxHpEnhance,					"生命上限% "},	
	{ Role_Attrib_MaxMpEnhance,					"法力上限% "},
	

	{ Role_Attrib_WaigongEnhance,				"外功% "},
	{ Role_Attrib_NeigongEnhance,				"内功% "},
	{ Role_Attrib_ShenfaEnhance,				"身法% "},
	{ Role_Attrib_ZhenqiEnhance,				"真气% "},
	{ Role_Attrib_JinguEnhance,					"筋骨% "},	



	//////////////////////////////////////////////////
	///伤害加成
	//////////////////////////////////////////////////	
	{ Role_Attrib_DamageMelee,					"近战伤害"},
	{ Role_Attrib_DamageRange,					"远程伤害"},

	{ Role_Attrib_DamageFire,					"火焰伤害"},
	{ Role_Attrib_DamageCold,					"冰冷伤害"},
	{ Role_Attrib_DamageLightning,				"法术伤害"},
	{ Role_Attrib_DamagePoison,					"毒素伤害"},
	{ Role_Attrib_Healing,						"治疗"},

//	{ Role_Attrib_DamageKin,					"家族战车伤害"},
//	{ Role_Attrib_DamageFaction,				"帮会战车伤害"},

	{ Role_Attrib_DirectDamage,					"直接伤害"},
	/////////////////////////////////////////
	//// 伤害加成%
	////////////////////////////////////////
	{ Role_Attrib_DamageMeleeEnhance,			"近战伤害加强%"},
	{ Role_Attrib_DamageRangeEnhance,			"远程伤害加强%"},
	{ Role_Attrib_DamagePhysicalEnhance,		"物理伤害加强%"},

	{ Role_Attrib_DamageFireEnhance,			"火焰伤害加强%"},
	{ Role_Attrib_DamageColdEnhance,			"冰冷伤害加强%"},
	{ Role_Attrib_DamageLightningEnhance,		"闪电伤害加强%"},
	{ Role_Attrib_DamagePoisonEnhance,			"毒素伤害加强%"},
	{ Role_Attrib_HealingEnhance,				"治疗百分加强%"},
	{ Role_Attrib_DamageSpellEnhance,			"魔法伤害加强%"},

	{ Role_Attrib_AllDamageEnhance,				"所有伤害加强%"},

	///////////////////////////////////////////////
	////攻击加成
	//////////////////////////////////////////////
// 	{ Role_Attrib_AttackPowerMelee,				"近战攻击强度"},
// 	{ Role_Attrib_AttackPowerRange,				"远程攻击强度"},
// 	{ Role_Attrib_AttackPower,					"物理攻击强度"},

// 	{ Role_Attrib_SpellPowerFire,				"火焰能量"},
// 	{ Role_Attrib_SpellPowerCold,				"冰冷能量"},
// 	{ Role_Attrib_SpellPowerLightning,			"法术能量"},
// 	{ Role_Attrib_SpellPowerPoison,				"毒素能量"},
// 	{ Role_Attrib_HealingPower,					"治疗能量"},
// 	{ Role_Attrib_SpellPower,					"魔法能量"},


	/////////////////////////////////////////////////
	////攻击加成%
	/////////////////////////////////////////////////
// 	{ Role_Attrib_AttackPowerMeleeEnhance,		"近战攻击强度%"},
// 	{ Role_Attrib_AttackPowerRangeEnhance,		"远程攻击强度%"},
// 	{ Role_Attrib_AttackPowerEnhance,			"物理攻击强度%"},
// 
// 	{ Role_Attrib_SpellPowerFireEnhance,		"火焰能量%"},
// 	{ Role_Attrib_SpellPowerColdEnhance,		"冰冷能量%"},
// 	{ Role_Attrib_SpellPowerLightningEnhance,	"法术能量%"},
// 	{ Role_Attrib_SpellPowerPoisonEnhance,		"毒素能量%"},
// 	{ Role_Attrib_HealingPowerEnhance,			"治疗能量%"},
// 	{ Role_Attrib_SpellPowerEnhance,			"魔法能量%"},

	///////////////////////////////////////////
	//// 防御(数值减免)
	///////////////////////////////////////////
	{ Role_Attrib_Armor,						"护甲"},
	{ Role_Attrib_SpellResist,					"法术伤害数值减少"},
	{ Role_Attrib_HealingResist,				"治疗数值减少"},

//	{ Role_Attrib_ArmorKin,						"家族战车伤害数值减免"},
//	{ Role_Attrib_ArmorFaction,					"帮会战车伤害数值减免"},
	///////////////////////////////////////////
	//// 防御%
	///////////////////////////////////////////
	{ Role_Attrib_ArmorEnhance,					"护甲百分比增加"},	
	{ Role_Attrib_SpellResistEnhance,			"法术抗性百分比增加"},
	{ Role_Attrib_HealingResistEnhance,			"治疗减少%"},
	/////////////////////////////////////////
	//// 伤害减免%
	/////////////////////////////////////////
	{ Role_Attrib_PhysicDamageReduce,			"物理伤害百分比减免"},
	{ Role_Attrib_HealingReduce,				"治疗百分比减免"},
	{ Role_Attrib_SpellDamageReduce,			"魔法伤害百分比减免"},
	{ Role_Attrib_AllDamageReduceEnhance,		"所有伤害百分比减免"},
	/////////////////////////////////////
	////战斗几率
	////////////////////////////////////
	{ Role_Attrib_MeleeCrit,					"近战暴击率"},
	{ Role_Attrib_MeleeCritMultiplier,			"近战暴击伤害系数"},

//	{ Role_Attrib_MeleeDHCrit,					"近战双手暴击率"},
//	{ Role_Attrib_MeleeDHCritMultiplier,		"近战双手暴击伤害系数"},

	{ Role_Attrib_RangeCrit,					"远程暴击率"},
	{ Role_Attrib_RangeCritMultiplier,			"远程致命伤害系数"},	

	{ Role_Attrib_FireCrit,						"火焰暴击率"},
	{ Role_Attrib_FireCritMulitipiler,			"火焰暴击伤害系数"},

	{ Role_Attrib_ColdCrit,						"冰冷暴击率"},
	{ Role_Attrib_ColdCritMulitipiler,			"冰冷暴击伤害系数"},

	{ Role_Attrib_LightningCrit,				"法术暴击率"},
	{ Role_Attrib_LightningCritMulitipiler,		"法术暴击伤害系数"},

	{ Role_Attrib_PoisonCrit,					"毒素暴击率"},
	{ Role_Attrib_PoisonCritMulitipiler,		"毒素暴击伤害系数"},

	{ Role_Attrib_HealingCrit,					"治疗暴击率"},
	{ Role_Attrib_HealingCritMulitipiler,		"治疗暴击效果系数"},

	{ Role_Attrib_SpellCrit,					"魔法暴击率"},
	{ Role_Attrib_SpellCritMultiplier,			"魔法暴击伤害系数"},

	{ Role_Attrib_Crit,							"物理暴击率"},
	{ Role_Attrib_CritMultiplier,				"物理致命伤害系数"},

	{ Role_Attrib_Dodge,						"回避几率"},
	{ Role_Attrib_CritResilience,				"韧性"},
	{ Role_Attrib_HolyStrike,					"神圣一击的几率"},
	{ Role_Attrib_ChanceOfRebound,				"完全反弹几率"},
	{ Role_Attrib_HolyStrikeResilience,			"减少神圣一击几率"},	
	///////////////////////////////////////
	//// 施加状态几率
	///////////////////////////////////////
	{ Role_Attrib_IncreaseChanceOfPoison,		"提高施放毒几率"},
	{ Role_Attrib_IncreaseChanceOfAblepsia,	"提高施放失明几率"},
	{ Role_Attrib_IncreaseChanceOfFreeze,		"提高施放冰冻几率"},
	{ Role_Attrib_IncreaseChanceOfBurn,			"提高施放灼烧几率"},
	{ Role_Attrib_IncreaseChanceOfStun,			"提高施放眩晕几率"},
	{ Role_Attrib_IncreaseChanceOfSlow,			"提高施放减速几率"},
	{ Role_Attrib_IncreaseChanceOfImmobilize,	"提高施放定身几率"},
	{ Role_Attrib_IncreaseChanceOfConfuse,		"提高施放混乱几率"},
	{ Role_Attrib_IncreaseChanceOfSlience,		"提高施放沉默几率"},


	{ Role_Attrib_ReduceChanceOfPoison,			"减少中毒几率"},
	{ Role_Attrib_ReduceChanceOfAblepsia,		"减少受到失明几率"},
	{ Role_Attrib_ReduceChanceOfFreeze,			"减少被冰冻的几率"},
	{ Role_Attrib_ReduceChanceOfBurn,			"减少被灼烧的几率"},
	{ Role_Attrib_ReduceChanceOfStun,			"减少被眩晕的几率"},
	{ Role_Attrib_ReduceChanceOfSlow,			"减少被减速的几率"},
	{ Role_Attrib_ReduceChanceOfImmobilize,		"减少被定身的几率"},
	{ Role_Attrib_ReduceChanceOfConfuse,		"减少被混乱的几率"},
	{ Role_Attrib_ReduceChanceOfSlience,		"减少被沉默的几率"},
	/////////////////////////////////////
	//// 其他属性
	////////////////////////////////////
	{ Role_Attrib_FastRunWalk,					"移动加速"},
	{ Role_Attrib_DamageToManaRate,				"伤害百分比转移给发力"},
	{ Role_Attrib_AttributePoints,				"属性点数"},
	{ Role_Attrib_ExperienceGained,				"经验值获取"},

	{ Role_Attrib_SkillLevel,					"提高技能等级"},
	{ Role_Attrib_IgnoreTargetDefence,			"忽视敌人防御"},
	{ Role_Attrib_IgnoreTargetDefenceRating,	"忽视敌人防御%"},

	{ Role_Attrib_BetterChanceofItemFind,		"提高掉宝几率"},

	//{ Role_Attrib_MaxEnergyEnhance,		"能量上限百分比增加"},
	//{ Role_Attrib_MaxRageEnhance,			"怒气上限百分比增加"},
	//{ Role_Attrib_Level,						"等级"},
	//{ Role_Attrib_Experience,				"经验"},
	//{ Role_Attrib_Type,						"类型"},
	//{ Role_Attrib_CurrentSuit,				"当前装备为第几套"},
	//{ Role_Attrib_Hair,						"头发颜色"},
	//{ Role_Attrib_AIType,					"AI类型"},
	//{ Role_Attrib_Gold,						"金子"},
	//{ Role_Attrib_GoldBind,					"绑定的金子"},
	//{ Role_Attrib_Silver,					"银子"},
	//{ Role_Attrib_SilverBind,				"绑定的银子"},
	//{ Role_Attrib_StashGold,					"箱子里的金子"},
	//{ Role_Attrib_StashGoldBind,				"箱子里绑定的金子"},
	//{ Role_Attrib_StashSilver,				"箱子里的银子"},
	//{ Role_Attrib_StashSilverBind,			"箱子里绑定的银子"},	
	//{ Role_Attrib_SkillPoints,				"技能点数"},
	//{ Role_Attrib_Invulnerability,			"是否无敌"},
	//{ Role_Attrib_Invisibility,				"是否隐身"},
	//{ Role_Attrib_Inventorys,				"背包个数"},
	//{ Role_Attrib_Stashes,					"箱子个数"},
	//{ Role_Attrib_UIPos,						"在人物身上UI中的位置"}



	//{Role_Attrib_MeleeOHAccuracy,				"近战命中率"},
	//{Role_Attrib_MeleeOHParry,					"近战招架率"},
	//{Role_Attrib_MeleeOHDodge,					"近战躲闪率"},
	//{Role_Attrib_MeleeOHBlock,					"近战格挡率"},
	//{Role_Attrib_MeleeOHCrushingBlow,			"近战碾压率"},
	//{Role_Attrib_MeleeOHGlance,					"近战偏斜率"},

	//{Role_Attrib_MeleeOHBlockMultiplier,		"近战格挡伤害系数"},
	//{Role_Attrib_MeleeOHCrushingBlowMultiplier,	"近战碾压伤害系数"},
	//{Role_Attrib_MeleeOHGlanceMultipiler,		"近战偏斜伤害系数"},

	//{Role_Attrib_MeleeDHAccuracy,				"近战双手命中率"},
	//{Role_Attrib_MeleeDHParry,					"近战招架率"},
	//{Role_Attrib_MeleeDHDodge,					"近战躲闪率"},
	//{Role_Attrib_MeleeDHBlock,					"近战格挡率"},
	//{Role_Attrib_MeleeDHCrushingBlow,			"近战碾压率"},
	//{Role_Attrib_MeleeDHGlance,					"近战偏斜率"},

	//{Role_Attrib_MeleeDHBlockMultiplier,		"近战格挡伤害系数"},
	//{Role_Attrib_MeleeDHCrushingBlowMultiplier,	"近战碾压伤害系数"},
	//{Role_Attrib_MeleeDHGlanceMultipiler,		"近战偏斜伤害系数"},


	//{Role_Attrib_RangeAccuracy,				"远程命中率"},
	//{Role_Attrib_RangeParry,				"远程招架率"},
	//{Role_Attrib_RangeDodge,				"远程躲闪率"},
	//{Role_Attrib_RangeBlock,				"远程格挡率"},
	//{Role_Attrib_RangeCrushingBlow,			"远程碾压率"},
	//{Role_Attrib_RangeGlance,				"远程偏斜率"},

	//{Role_Attrib_RangeBlockMultiplier,		"远程格挡伤害系数"},
	//{Role_Attrib_RangeCrushingBlowMultiplier,"远程碾压伤害系数"},
	//{Role_Attrib_RangeGlanceMultipiler,		"远程偏斜伤害系数"},

	//{Role_Attrib_Accuracy,					"命中率"},
	//{Role_Attrib_Parry,						"招架率"},
	//{Role_Attrib_Dodge,						"躲闪率"},
	//{Role_Attrib_Block,						"格挡率"},
	//{Role_Attrib_CrushingBlow,				"碾压率"},
	//{Role_Attrib_Glance,					"偏斜率"},

	//{Role_Attrib_BlockMultiplier,			"格挡伤害系数"},
	//{Role_Attrib_CrushingBlowMultiplier,	"碾压伤害系数"},
	//{Role_Attrib_GlanceMultipiler,			"偏斜伤害系数"},

	//{Role_Attrib_FireAccuracy,				"火焰法术命中率"},
	//{Role_Attrib_FireDodge,					"火焰法术躲闪率"},
	//{Role_Attrib_FireBlock,					"火焰法术格挡率"},


	//{Role_Attrib_FireBlockMultiplier,		"火焰法术格挡伤害系数"},
	

	//{Role_Attrib_ColdAccuracy,				"冰冷法术命中率"},
	//{Role_Attrib_ColdDodge,					"冰冷法术躲闪率"},
	//{Role_Attrib_ColdBlock,					"冰冷法术格挡率"},

	//{Role_Attrib_ColdBlockMultiplier,		"冰冷法术格挡伤害系数"},

	//{Role_Attrib_LightningAccuracy,			"闪电法术命中率"},
	//{Role_Attrib_LightningDodge,			"闪电法术躲闪率"},
	//{Role_Attrib_LightningBlock,			"闪电法术格挡率"},

	//{Role_Attrib_LightningBlockMultiplier,	"闪电法术格挡伤害系数"},


	//{Role_Attrib_PoisonAccuracy,			"毒素法术命中率"},
	//{Role_Attrib_PoisonDodge,				"毒素法术躲闪率"},
	//{Role_Attrib_PoisonBlock,				"毒素法术格挡率"},

	//{Role_Attrib_PoisonBlockMultiplier,		"毒素法术格挡伤害系数"},


	//{Role_Attrib_HealingAccuracy,			"治疗法术命中率"},
	//{Role_Attrib_HealingDodge,				"治疗法术躲闪率"},
	//{Role_Attrib_HealingBlock,				"治疗法术格挡率"},

	//{Role_Attrib_HealingBlockMultiplier,	"治疗法术格挡效果系数"},


	//{Role_Attrib_SpellAccuracy,				"法术命中率"},
	//{Role_Attrib_SpellDodge,				"法术躲闪率"},
	//{Role_Attrib_SpellBlock,				"法术格挡率"},

	//{Role_Attrib_SpellBlockMultiplier,		"法术格挡伤害系数"},



	//{Role_Attrib_MeleeDamageAbsorb,			"近战伤害吸收"},
	//{Role_Attrib_MeleeDamageAbsorbRate,		"近战伤害百分比吸收"},
	//{Role_Attrib_MeleeDamageRebound,		"近战伤害反弹"},
	//{Role_Attrib_MeleeDamageReboundRate,	"近战伤害百分比反弹"},

	//{Role_Attrib_RangeDamageAbsorb,			"远程伤害吸收"},
	//{Role_Attrib_RangeDamageAbsorbRate,		"远程伤害百分比吸收"},
	//{Role_Attrib_RangeDamageRebound,		"远程伤害反弹"},
	//{Role_Attrib_RangeDamageReboundRate,	"远程伤害百分比反弹"},

	//{Role_Attrib_DamageAbsorb,				"伤害吸收"},
	//{Role_Attrib_DamageAbsorbRate,			"伤害百分比吸收"},
	//{Role_Attrib_DamageRebound,				"伤害反弹"},
	//{Role_Attrib_DamageReboundRate,			"伤害百分比反弹"},

	//{Role_Attrib_FireDamageAbsorb,			"火焰伤害吸收"},
	//{Role_Attrib_FireDamageAbsorbRate,		"火焰伤害百分比吸收"},
	//{Role_Attrib_FireDamageRebound,			"火焰伤害反弹"},
	//{Role_Attrib_FireDamageReboundRate,		"火焰伤害百分比反弹"},

	//{Role_Attrib_ColdDamageAbsorb,			"冰冷伤害吸收"},
	//{Role_Attrib_ColdDamageAbsorbRate,		"冰冷伤害百分比吸收"},
	//{Role_Attrib_ColdDamageRebound,			"冰冷伤害反弹"},
	//{Role_Attrib_ColdDamageReboundRate,		"冰冷伤害百分比反弹"},

	//{Role_Attrib_LightningDamageAbsorb,		"闪电伤害吸收"},
	//{Role_Attrib_LightningDamageAbsorbRate,	"闪电伤害百分比吸收"},
	//{Role_Attrib_LightningDamageRebound,	"闪电伤害反弹"},
	//{Role_Attrib_LightningDamageReboundRate,"闪电伤害百分比反弹"},

	//{Role_Attrib_PoisonDamageAbsorb,		"毒素伤害吸收"},
	//{Role_Attrib_PoisonDamageAbsorbRate,	"毒素伤害百分比吸收"},
	//{Role_Attrib_PoisonDamageRebound,		"毒素伤害反弹"},
	//{Role_Attrib_PoisonDamageReboundRate,	"毒素伤害百分比反弹"},

	//{Role_Attrib_HealingAbsorb,   			"治疗效果吸收"}, //无意义		
	//{Role_Attrib_HealingAbsorbRate,			"治疗效果百分比吸收"},//无意义	
	//{Role_Attrib_HealingRebound,			"治疗效果反弹"},
	//{Role_Attrib_HealingReboundRate,		"治疗效果百分比反弹"},


	//{Role_Attrib_SpellDamageAbsorb,			"法术伤害吸收"},
	//{Role_Attrib_SpellDamageAbsorbRate,		"法术伤害百分比吸收"},
	//{Role_Attrib_SpellDamageRebound,		"法术伤害反弹"},
	//{Role_Attrib_SpellDamageReboundRate,	"法术伤害百分比反弹"},

	//{Role_Attrib_AllDamageAbsorb,			"所有伤害吸收"},
	//{Role_Attrib_AllDamageAbsorbRate,		"所有伤害百分比吸收"},
	//{Role_Attrib_AllDamageRebound,			"所有伤害反弹"},
	//{Role_Attrib_AllDamageReboundRate,		"所有伤害百分比反弹"},



	//{Role_Attrib_AttackSpeed,				"攻击速度"},
	//{Role_Attrib_CastRate,					"施法速度"},
	//{Role_Attrib_RunSpeed,					"移动速度"},

	//{Role_Attrib_FastAttackSpeed,			"攻击加速"},
	//{Role_Attrib_FastCastRate,				"施法加速"},

	{Role_Attrib_DamageToMana,				"伤害转移给法力"},


	//{Role_Attrib_MinMeleeDamageReduce,		"最小近战伤害百分比减免"},
	//{Role_Attrib_MaxMeleeDamageReduce,		"最大近战伤害百分比减免"},
	//{Role_Attrib_MeleeDamageReduce,			"近战伤害百分比减免"},

	//{Role_Attrib_MinRangeDamageReduce,		"最小远程伤害百分比减免"},
	//{Role_Attrib_MaxRangeDamageReduce,		"最大远程伤害百分比减免"},
	//{Role_Attrib_RangeDamageReduce,			"远程伤害百分比减免"},

	//{Role_Attrib_MinPhysicDamageReduce,			"最小伤害百分比减免"},
	//{Role_Attrib_MaxPhysicDamageReduce,			"最大伤害百分比减免"},
	

	//{Role_Attrib_MinFireDamageReduce,		"最小火焰伤害百分比减免"},
	//{Role_Attrib_MaxFireDamageReduce,		"最大火焰伤害百分比减免"},
	//{Role_Attrib_FireDamageReduce,			"火焰伤害百分比减免"},

	//{Role_Attrib_MinColdDamageReduce,		"最小冰冷伤害百分比减免"},
	//{Role_Attrib_MaxColdDamageReduce,		"最大冰冷伤害百分比减免"},
	//{Role_Attrib_ColdDamageReduce,			"冰冷伤害百分比减免"},

	//{Role_Attrib_MinLightningDamageReduce,	"最小闪电伤害百分比减免"},
	//{Role_Attrib_MaxLightningDamageReduce,	"最大闪电伤害百分比减免"},
	//{Role_Attrib_LightningDamageReduce,		"闪电伤害百分比减免"},

	//{Role_Attrib_MinPoisonDamageReduce,		"最小毒素伤害百分比减免"},
	//{Role_Attrib_MaxPoisonDamageReduce,		"最大毒素伤害百分比减免"},
	//{Role_Attrib_PoisonDamageReduce,		"毒素伤害百分比减免"},

	//{Role_Attrib_MinHealingReduce,			"最小治疗百分比减免"},
	//{Role_Attrib_MaxHealingReduce,			"最大治疗百分比减免"},

	//	441,

	//	446,

	//	451,

	//	456,

	//	461,	

	//{Role_Attrib_MinSpellDamageReduce,		"最小法术伤害百分比减免"},
	//{Role_Attrib_MaxSpellDamageReduce,		"最大法术伤害百分比减免"},

	

	//{ Role_Attrib_MinDamageMeleeOH,			"近战单手最小伤害"},
	//{ Role_Attrib_MaxDamageMeleeOH,			"近战单手最大伤害"},	

	//{ Role_Attrib_MinDamageRange,			"远程最小伤害"},
	//{ Role_Attrib_MaxDamageRange,			"远程最大伤害"},


	//{ Role_Attrib_MinDamagePhysical,		"物理最小伤害"},
	//{ Role_Attrib_MaxDamagePhysical,		"物理最大伤害"},
	//{ Role_Attrib_DamagePhysical,			"物理伤害"},
	//{ Role_Attrib_DamagePhysicalEnhance,	"物理伤害百分比增加"},

	//{ Role_Attrib_MinDamageFire,			"火焰最小伤害"},
	//{ Role_Attrib_MaxDamageFire,			"火焰最大伤害"},

	//{ Role_Attirb_MinDamageCold,			"冰冷最小伤害"},
	//{ Role_Attirb_MaxDamageCold,			"冰冷最大伤害"},

	//{ Role_Attrib_MinDamageLightning,		"闪电最小伤害"},
	//{ Role_Attrib_MaxDamageLightning,		"闪电最大伤害"},

	//{ Role_Attrib_MinDamagePoison,			"毒素最小伤害"},
	//{ Role_Attrib_MaxDamagePoison,			"毒素最大伤害"},

	//{ Role_Attrib_MinHealing,				"最小治疗"},
	//{ Role_Attrib_MaxHealing,				"最大治疗"},



		//	141,

		//	146,

		//	151,

		//	156,

		//	161,

	//{ Role_Attrib_MinDamageSpell,			"法术最小伤害"},
	//{ Role_Attrib_MaxDamageSpell,			"法术最大伤害"},
	//{ Role_Attrib_DamageSpell,				"法术伤害"},
	//{ Role_Attrib_DamageSpellEnhance,		"法术伤害百分比增加"},


		//////////////////////////////////////////////////
		///物理攻击强度 & 法术能量 & 治疗能量
		//////////////////////////////////////////////////	

	//{ Role_Attrib_MinAttackPowerMeleeOH,		"近战最小攻击强度"},
	//{ Role_Attrib_MaxAttackPowerMeleeOH,		"近战最大攻击强度"},


	//{ Role_Attrib_AttackPowerMeleeEnhanceOH,	"近战攻击强度百分比增加"},



	//{ Role_Attrib_MinAttackPowerRange,		"远程最小攻击强度"},
	//{ Role_Attrib_MaxAttackPowerRange,		"远程最大攻击强度"},
	//{ Role_Attrib_AttackPowerRangeEnhance,	"远程攻击强度百分比增加"},


	//{ Role_Attrib_MinAttackPower,			"最小攻击强度"},
	//{ Role_Attrib_MaxAttackPower,			"最大攻击强度"},
	//{ Role_Attrib_AttackPowerEnhance,		"攻击强度百分比增加"},

	//{ Role_Attrib_MinSpellPowerFire,		"最小火焰法术能量"},
	//{ Role_Attrib_MaxSpellPowerFire,		"最大火焰法术能量"},
	//{ Role_Attrib_SpellPowerFireEnhance,	"火焰法术能量百分比增加"},

	//{ Role_Attrib_MinSpellPowerCold,		"最小冰冷法术能量"},
	//{ Role_Attrib_MaxSpellPowerCold,		"最大冰冷法术能量"},
	//{ Role_Attrib_SpellPowerColdEnhance,	"冰冷法术能量百分比增加"},

	//{ Role_Attrib_MinSpellPowerLightning,	"最小闪电法术能量"},
	//{ Role_Attrib_MaxSpellPowerLightning,	"最大闪电法术能量"},
	//{ Role_Attrib_SpellPowerLightningEnhance,"闪电法术能量百分比增加"},

	//{ Role_Attrib_MinSpellPowerPoison,		"最小毒素法术能量"},
	//{ Role_Attrib_MaxSpellPowerPoison,		"最大毒素法术能量"},
	//{ Role_Attrib_SpellPowerPoisonEnhance,	"毒素法术能量百分比增加"},

	//{ Role_Attrib_MinHealingPower,			"最小治疗能量"},
	//{ Role_Attrib_MaxHealingPower,			"最大治疗能量"},
	//{ Role_Attrib_HealingPowerEnhance,		"治疗能量百分比增加"},

		//	241,

		//	246,

		//	251,

		//	256,

		//	261,

	//{ Role_Attrib_MinSpellPower,			"最小法术能量"},
	//{ Role_Attrib_MaxSpellPower,			"最大法术能量"},
	//{ Role_Attrib_SpellPowerEnhance,		"法术能量百分比增加"},

	//{ Role_Attrib_IncreaseAllDamage,		"所有伤害增加"},
	//{ Role_Attrib_EnhanceAllDamage,			"所有伤害百分比增加"},

	//{Role_Attrib_IncreaseAllResult,			"所有效果增加"},
	//{Role_Attrib_EnhanceAllResult,			"所有效果百分比增加"},


		//////////////////////////////////////////////////
		///物理 & 法术 伤害数值减免
		//////////////////////////////////////////////////	
	//{ Role_Attrib_MinArmorMeleeOH,			"最小近战护甲-单手"},  
	//{ Role_Attrib_MaxArmorMeleeOH,			"最大近战护甲-单手"},
	//{ Role_Attrib_ArmorMeleeOH,				"近战护甲-单手"},
	//{ Role_Attrib_ArmorMeleeEnhanceOH,		"近战护甲百分比增加"},

	//{ Role_Attrib_MinArmorRange,			"最小远程护甲"},
	//{Role_Attrib_MaxArmorRange,				"最大远程护甲"},
	//{Role_Attrib_ArmorRange,				"远程护甲"},
	//{Role_Attrib_ArmorRangeEnhance,			"远程护甲百分比增加"},

	//{Role_Attrib_MinArmor,					"最小护甲"},
	//{Role_Attrib_MaxArmor,					"最大护甲"},


	//{Role_Attrib_MinFireResist,				"最小火焰抗性"},
	//{Role_Attrib_MaxFireResist,				"最大火焰抗性"},
	//{Role_Attrib_FireResist,				"火焰抗性"},
	//{Role_Attrib_FireResistEnhance,			"火焰抗性百分比增加"},

	//{Role_Attrib_MinColdResist,				"最小冰冷抗性"},
	//{Role_Attrib_MaxColdResist,				"最大冰冷抗性"},
	//{Role_Attrib_ColdResist,				"冰冷抗性"},
	//{Role_Attrib_ColdResistEnhance,			"冰冷抗性百分比增加"},

	//{Role_Attrib_MinLightningResist,		"最小闪电抗性"},
	//{Role_Attrib_MaxLightningResist,		"最大闪电抗性"},
	//{Role_Attrib_LightningResist,			"闪电抗性"},
	//{Role_Attrib_LightningResistEnhance,	"闪电抗性百分比增加"},

	//{Role_Attrib_MinPoisonResist,			"最小毒素抗性"},
	//{Role_Attrib_MaxPoisonResist,			"最大毒素抗性"},
	//{Role_Attrib_PoisonResist,				"毒素抗性"},
	//{Role_Attrib_PoisonResistEnhance,		"毒素抗性百分比增加"},

	//{Role_Attrib_MinHealingResist,			"最小治疗抗性"},
	//{Role_Attrib_MaxHealingResist,			"最大治疗抗性"},
	//{Role_Attrib_HealingResist,				"治疗抗性"},
	//{Role_Attrib_HealingResistEnhance,		"治疗抗性百分比增加"},

	//	341,

	//	346,

	//	351,

	//	356,

	//	361,


	//{Role_Attrib_MinSpellResist,			"最小法术抗性"},
	//{Role_Attrib_MaxSpellResist,			"最大法术抗性"},


	//{Role_Attrib_AllArmor,					"所有伤害抗性"},


	//////////////////////////////////////////////////
	///物理 & 法术 伤害百分比减免
	//////////////////////////////////////////////////	


	
};
//
//const char* GetAttribName(int nAttribID)
//{
//	int nSize = sizeof(AttribTabble)/sizeof(ATTRIB_MAP);
//	for(int i=0;i<nSize;i++)
//	{
//		if(AttribTabble[i].ID == nAttribID )
//		{
//			return &AttribTabble[i].Name[0];
//		}
//	}
//	return NULL;
//}
//
//const wchar_t* GetAttribNameW(int nAttribID)
//{
//	const char* szName = GetAttribName(nAttribID);
//	if(!szName)
//		return NULL;
//	wchar_t wcsName[50]={0};
//	CharToWideChar(szName,wcsName,50);
//	return wcsName;
//}
//
