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
		Log("�ַ�ת�� new ʧ��");
		return 0;
	}
	memset(wszUtf8, 0, sizeof(WCHAR) * (nMaxSize + 1));
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strGBK, -1, wszUtf8, nMaxSize);

	len = WideCharToMultiByte(CP_UTF8, 0, wszUtf8, -1, NULL, 0, NULL, NULL);
	char *szUtf8 = new char[nMaxSize + 1];
	if(!szUtf8)
	{
		assert(0);
		Log("�ַ�ת�� new ʧ��");
		return 0;
	}
	memset(szUtf8, 0, sizeof(char) * (nMaxSize + 1));
	WideCharToMultiByte (CP_UTF8, 0, wszUtf8, -1, szUtf8, nMaxSize, NULL,NULL);
	if((len-1) <= nMaxSize)	// len -1 ��ʾ ȥ�����һ��\0 nMaxSize  ����\0
	{
		memcpy(strDestUTF8,szUtf8,nMaxSize);
	}
	else
	{
		assert(0);
		Log("ת��Ŀ��洢�ڴ������С");
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
		Log("�ַ�ת�� new ʧ��");
		return 0;
	}
	memset(wszGBK, 0, sizeof(WCHAR) * (nMaxSize + 1));
	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)strUtf8, -1, wszGBK, nMaxSize);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[nMaxSize + 1];
	if(!szGBK)
	{
		assert(0);
		Log("�ַ�ת�� new ʧ��");
		return 0;
	}
	memset(szGBK, 0, sizeof(char) * (nMaxSize + 1));
	len = WideCharToMultiByte (CP_ACP, 0, wszGBK, -1, szGBK, nMaxSize, NULL,NULL);
	
	if((len-1) <= nMaxSize)		// len -1 ��ʾ ȥ�����һ��\0 nMaxSize  ����\0
	{
		memcpy(strDestGBK,szGBK,nMaxSize);
	}
	else
	{
		assert(0);
		Log("ת��Ŀ��洢�ڴ������С");
		strDestGBK[0] = '\0';
	}

	SAFE_DELETE(wszGBK);
	SAFE_DELETE(szGBK);
	return strlen(strDestGBK);
}

//////////////////////////////////
// �Ƿ�������ʹ����
// nEffectID		: ���õ�ID
BOOL IsSrcEffect( int nEffectID )
{
	if( nEffectID < EFFECT_LIMIT )
		return TRUE;
	return FALSE;
}
//////////////////////////////
// �Ƿ�������Ŀ����
// nEffectID		: ���õ�ID
BOOL IsDestEffect( int nEffectID )
{
	if( nEffectID > EFFECT_LIMIT )
		return TRUE;
	return FALSE;
}

ATTRIB_MAP AttribTabble[]=
{
	//////////////////////////////////////////////////
	///������������ 
	//////////////////////////////////////////////////	
	{ Role_Attrib_Hp,							"��ǰ����"},
	{ Role_Attrib_MaxHp,						"��������"},
	{ Role_Attrib_HpRegen,						"�����ظ��ٶ�"},

	{ Role_Attrib_Mp	,						"��ǰ����"},
	{ Role_Attrib_MaxMp,						"��������"},
	{ Role_Attrib_MpRegen,						"�����ظ��ٶ�"},

	//{ Role_Attirb_Energy,						"��ǰ����"},
	//{ Role_Attrib_MaxEnergy,					"��������"},
	//{ Role_Attrib_EnergyRegen,				"�����ظ��ٶ�"},

	//{ Role_Attrib_Rage,						"��ǰŭ��"},
	//{ Role_Attrib_MaxRage,					"ŭ������"},
	//{ Role_Attrib_RageRegen,					"ŭ���ظ��ٶ�"},

	{ Role_Attrib_Waigong,						"�⹦"},
	{ Role_Attrib_Neigong,						"�ڹ�"},
	{ Role_Attrib_Shenfa,						"��"},	
	{ Role_Attrib_Zhenqi,						"����"},	
	{ Role_Attrib_Jingu,						"���"},	


	//////////////////////////////////////////////////
	///�������԰ٷֱ�����
	//////////////////////////////////////////////////	
	{ Role_Attrib_MaxHpEnhance,					"��������% "},	
	{ Role_Attrib_MaxMpEnhance,					"��������% "},
	

	{ Role_Attrib_WaigongEnhance,				"�⹦% "},
	{ Role_Attrib_NeigongEnhance,				"�ڹ�% "},
	{ Role_Attrib_ShenfaEnhance,				"��% "},
	{ Role_Attrib_ZhenqiEnhance,				"����% "},
	{ Role_Attrib_JinguEnhance,					"���% "},	



	//////////////////////////////////////////////////
	///�˺��ӳ�
	//////////////////////////////////////////////////	
	{ Role_Attrib_DamageMelee,					"��ս�˺�"},
	{ Role_Attrib_DamageRange,					"Զ���˺�"},

	{ Role_Attrib_DamageFire,					"�����˺�"},
	{ Role_Attrib_DamageCold,					"�����˺�"},
	{ Role_Attrib_DamageLightning,				"�����˺�"},
	{ Role_Attrib_DamagePoison,					"�����˺�"},
	{ Role_Attrib_Healing,						"����"},

//	{ Role_Attrib_DamageKin,					"����ս���˺�"},
//	{ Role_Attrib_DamageFaction,				"���ս���˺�"},

	{ Role_Attrib_DirectDamage,					"ֱ���˺�"},
	/////////////////////////////////////////
	//// �˺��ӳ�%
	////////////////////////////////////////
	{ Role_Attrib_DamageMeleeEnhance,			"��ս�˺���ǿ%"},
	{ Role_Attrib_DamageRangeEnhance,			"Զ���˺���ǿ%"},
	{ Role_Attrib_DamagePhysicalEnhance,		"�����˺���ǿ%"},

	{ Role_Attrib_DamageFireEnhance,			"�����˺���ǿ%"},
	{ Role_Attrib_DamageColdEnhance,			"�����˺���ǿ%"},
	{ Role_Attrib_DamageLightningEnhance,		"�����˺���ǿ%"},
	{ Role_Attrib_DamagePoisonEnhance,			"�����˺���ǿ%"},
	{ Role_Attrib_HealingEnhance,				"���ưٷּ�ǿ%"},
	{ Role_Attrib_DamageSpellEnhance,			"ħ���˺���ǿ%"},

	{ Role_Attrib_AllDamageEnhance,				"�����˺���ǿ%"},

	///////////////////////////////////////////////
	////�����ӳ�
	//////////////////////////////////////////////
// 	{ Role_Attrib_AttackPowerMelee,				"��ս����ǿ��"},
// 	{ Role_Attrib_AttackPowerRange,				"Զ�̹���ǿ��"},
// 	{ Role_Attrib_AttackPower,					"������ǿ��"},

// 	{ Role_Attrib_SpellPowerFire,				"��������"},
// 	{ Role_Attrib_SpellPowerCold,				"��������"},
// 	{ Role_Attrib_SpellPowerLightning,			"��������"},
// 	{ Role_Attrib_SpellPowerPoison,				"��������"},
// 	{ Role_Attrib_HealingPower,					"��������"},
// 	{ Role_Attrib_SpellPower,					"ħ������"},


	/////////////////////////////////////////////////
	////�����ӳ�%
	/////////////////////////////////////////////////
// 	{ Role_Attrib_AttackPowerMeleeEnhance,		"��ս����ǿ��%"},
// 	{ Role_Attrib_AttackPowerRangeEnhance,		"Զ�̹���ǿ��%"},
// 	{ Role_Attrib_AttackPowerEnhance,			"������ǿ��%"},
// 
// 	{ Role_Attrib_SpellPowerFireEnhance,		"��������%"},
// 	{ Role_Attrib_SpellPowerColdEnhance,		"��������%"},
// 	{ Role_Attrib_SpellPowerLightningEnhance,	"��������%"},
// 	{ Role_Attrib_SpellPowerPoisonEnhance,		"��������%"},
// 	{ Role_Attrib_HealingPowerEnhance,			"��������%"},
// 	{ Role_Attrib_SpellPowerEnhance,			"ħ������%"},

	///////////////////////////////////////////
	//// ����(��ֵ����)
	///////////////////////////////////////////
	{ Role_Attrib_Armor,						"����"},
	{ Role_Attrib_SpellResist,					"�����˺���ֵ����"},
	{ Role_Attrib_HealingResist,				"������ֵ����"},

//	{ Role_Attrib_ArmorKin,						"����ս���˺���ֵ����"},
//	{ Role_Attrib_ArmorFaction,					"���ս���˺���ֵ����"},
	///////////////////////////////////////////
	//// ����%
	///////////////////////////////////////////
	{ Role_Attrib_ArmorEnhance,					"���װٷֱ�����"},	
	{ Role_Attrib_SpellResistEnhance,			"�������԰ٷֱ�����"},
	{ Role_Attrib_HealingResistEnhance,			"���Ƽ���%"},
	/////////////////////////////////////////
	//// �˺�����%
	/////////////////////////////////////////
	{ Role_Attrib_PhysicDamageReduce,			"�����˺��ٷֱȼ���"},
	{ Role_Attrib_HealingReduce,				"���ưٷֱȼ���"},
	{ Role_Attrib_SpellDamageReduce,			"ħ���˺��ٷֱȼ���"},
	{ Role_Attrib_AllDamageReduceEnhance,		"�����˺��ٷֱȼ���"},
	/////////////////////////////////////
	////ս������
	////////////////////////////////////
	{ Role_Attrib_MeleeCrit,					"��ս������"},
	{ Role_Attrib_MeleeCritMultiplier,			"��ս�����˺�ϵ��"},

//	{ Role_Attrib_MeleeDHCrit,					"��ս˫�ֱ�����"},
//	{ Role_Attrib_MeleeDHCritMultiplier,		"��ս˫�ֱ����˺�ϵ��"},

	{ Role_Attrib_RangeCrit,					"Զ�̱�����"},
	{ Role_Attrib_RangeCritMultiplier,			"Զ�������˺�ϵ��"},	

	{ Role_Attrib_FireCrit,						"���汩����"},
	{ Role_Attrib_FireCritMulitipiler,			"���汩���˺�ϵ��"},

	{ Role_Attrib_ColdCrit,						"���䱩����"},
	{ Role_Attrib_ColdCritMulitipiler,			"���䱩���˺�ϵ��"},

	{ Role_Attrib_LightningCrit,				"����������"},
	{ Role_Attrib_LightningCritMulitipiler,		"���������˺�ϵ��"},

	{ Role_Attrib_PoisonCrit,					"���ر�����"},
	{ Role_Attrib_PoisonCritMulitipiler,		"���ر����˺�ϵ��"},

	{ Role_Attrib_HealingCrit,					"���Ʊ�����"},
	{ Role_Attrib_HealingCritMulitipiler,		"���Ʊ���Ч��ϵ��"},

	{ Role_Attrib_SpellCrit,					"ħ��������"},
	{ Role_Attrib_SpellCritMultiplier,			"ħ�������˺�ϵ��"},

	{ Role_Attrib_Crit,							"��������"},
	{ Role_Attrib_CritMultiplier,				"���������˺�ϵ��"},

	{ Role_Attrib_Dodge,						"�رܼ���"},
	{ Role_Attrib_CritResilience,				"����"},
	{ Role_Attrib_HolyStrike,					"��ʥһ���ļ���"},
	{ Role_Attrib_ChanceOfRebound,				"��ȫ��������"},
	{ Role_Attrib_HolyStrikeResilience,			"������ʥһ������"},	
	///////////////////////////////////////
	//// ʩ��״̬����
	///////////////////////////////////////
	{ Role_Attrib_IncreaseChanceOfPoison,		"���ʩ�Ŷ�����"},
	{ Role_Attrib_IncreaseChanceOfAblepsia,	"���ʩ��ʧ������"},
	{ Role_Attrib_IncreaseChanceOfFreeze,		"���ʩ�ű�������"},
	{ Role_Attrib_IncreaseChanceOfBurn,			"���ʩ�����ռ���"},
	{ Role_Attrib_IncreaseChanceOfStun,			"���ʩ��ѣ�μ���"},
	{ Role_Attrib_IncreaseChanceOfSlow,			"���ʩ�ż��ټ���"},
	{ Role_Attrib_IncreaseChanceOfImmobilize,	"���ʩ�Ŷ�����"},
	{ Role_Attrib_IncreaseChanceOfConfuse,		"���ʩ�Ż��Ҽ���"},
	{ Role_Attrib_IncreaseChanceOfSlience,		"���ʩ�ų�Ĭ����"},


	{ Role_Attrib_ReduceChanceOfPoison,			"�����ж�����"},
	{ Role_Attrib_ReduceChanceOfAblepsia,		"�����ܵ�ʧ������"},
	{ Role_Attrib_ReduceChanceOfFreeze,			"���ٱ������ļ���"},
	{ Role_Attrib_ReduceChanceOfBurn,			"���ٱ����յļ���"},
	{ Role_Attrib_ReduceChanceOfStun,			"���ٱ�ѣ�εļ���"},
	{ Role_Attrib_ReduceChanceOfSlow,			"���ٱ����ٵļ���"},
	{ Role_Attrib_ReduceChanceOfImmobilize,		"���ٱ�����ļ���"},
	{ Role_Attrib_ReduceChanceOfConfuse,		"���ٱ����ҵļ���"},
	{ Role_Attrib_ReduceChanceOfSlience,		"���ٱ���Ĭ�ļ���"},
	/////////////////////////////////////
	//// ��������
	////////////////////////////////////
	{ Role_Attrib_FastRunWalk,					"�ƶ�����"},
	{ Role_Attrib_DamageToManaRate,				"�˺��ٷֱ�ת�Ƹ�����"},
	{ Role_Attrib_AttributePoints,				"���Ե���"},
	{ Role_Attrib_ExperienceGained,				"����ֵ��ȡ"},

	{ Role_Attrib_SkillLevel,					"��߼��ܵȼ�"},
	{ Role_Attrib_IgnoreTargetDefence,			"���ӵ��˷���"},
	{ Role_Attrib_IgnoreTargetDefenceRating,	"���ӵ��˷���%"},

	{ Role_Attrib_BetterChanceofItemFind,		"��ߵ�������"},

	//{ Role_Attrib_MaxEnergyEnhance,		"�������ްٷֱ�����"},
	//{ Role_Attrib_MaxRageEnhance,			"ŭ�����ްٷֱ�����"},
	//{ Role_Attrib_Level,						"�ȼ�"},
	//{ Role_Attrib_Experience,				"����"},
	//{ Role_Attrib_Type,						"����"},
	//{ Role_Attrib_CurrentSuit,				"��ǰװ��Ϊ�ڼ���"},
	//{ Role_Attrib_Hair,						"ͷ����ɫ"},
	//{ Role_Attrib_AIType,					"AI����"},
	//{ Role_Attrib_Gold,						"����"},
	//{ Role_Attrib_GoldBind,					"�󶨵Ľ���"},
	//{ Role_Attrib_Silver,					"����"},
	//{ Role_Attrib_SilverBind,				"�󶨵�����"},
	//{ Role_Attrib_StashGold,					"������Ľ���"},
	//{ Role_Attrib_StashGoldBind,				"������󶨵Ľ���"},
	//{ Role_Attrib_StashSilver,				"�����������"},
	//{ Role_Attrib_StashSilverBind,			"������󶨵�����"},	
	//{ Role_Attrib_SkillPoints,				"���ܵ���"},
	//{ Role_Attrib_Invulnerability,			"�Ƿ��޵�"},
	//{ Role_Attrib_Invisibility,				"�Ƿ�����"},
	//{ Role_Attrib_Inventorys,				"��������"},
	//{ Role_Attrib_Stashes,					"���Ӹ���"},
	//{ Role_Attrib_UIPos,						"����������UI�е�λ��"}



	//{Role_Attrib_MeleeOHAccuracy,				"��ս������"},
	//{Role_Attrib_MeleeOHParry,					"��ս�м���"},
	//{Role_Attrib_MeleeOHDodge,					"��ս������"},
	//{Role_Attrib_MeleeOHBlock,					"��ս����"},
	//{Role_Attrib_MeleeOHCrushingBlow,			"��ս��ѹ��"},
	//{Role_Attrib_MeleeOHGlance,					"��սƫб��"},

	//{Role_Attrib_MeleeOHBlockMultiplier,		"��ս���˺�ϵ��"},
	//{Role_Attrib_MeleeOHCrushingBlowMultiplier,	"��ս��ѹ�˺�ϵ��"},
	//{Role_Attrib_MeleeOHGlanceMultipiler,		"��սƫб�˺�ϵ��"},

	//{Role_Attrib_MeleeDHAccuracy,				"��ս˫��������"},
	//{Role_Attrib_MeleeDHParry,					"��ս�м���"},
	//{Role_Attrib_MeleeDHDodge,					"��ս������"},
	//{Role_Attrib_MeleeDHBlock,					"��ս����"},
	//{Role_Attrib_MeleeDHCrushingBlow,			"��ս��ѹ��"},
	//{Role_Attrib_MeleeDHGlance,					"��սƫб��"},

	//{Role_Attrib_MeleeDHBlockMultiplier,		"��ս���˺�ϵ��"},
	//{Role_Attrib_MeleeDHCrushingBlowMultiplier,	"��ս��ѹ�˺�ϵ��"},
	//{Role_Attrib_MeleeDHGlanceMultipiler,		"��սƫб�˺�ϵ��"},


	//{Role_Attrib_RangeAccuracy,				"Զ��������"},
	//{Role_Attrib_RangeParry,				"Զ���м���"},
	//{Role_Attrib_RangeDodge,				"Զ�̶�����"},
	//{Role_Attrib_RangeBlock,				"Զ�̸���"},
	//{Role_Attrib_RangeCrushingBlow,			"Զ����ѹ��"},
	//{Role_Attrib_RangeGlance,				"Զ��ƫб��"},

	//{Role_Attrib_RangeBlockMultiplier,		"Զ�̸��˺�ϵ��"},
	//{Role_Attrib_RangeCrushingBlowMultiplier,"Զ����ѹ�˺�ϵ��"},
	//{Role_Attrib_RangeGlanceMultipiler,		"Զ��ƫб�˺�ϵ��"},

	//{Role_Attrib_Accuracy,					"������"},
	//{Role_Attrib_Parry,						"�м���"},
	//{Role_Attrib_Dodge,						"������"},
	//{Role_Attrib_Block,						"����"},
	//{Role_Attrib_CrushingBlow,				"��ѹ��"},
	//{Role_Attrib_Glance,					"ƫб��"},

	//{Role_Attrib_BlockMultiplier,			"���˺�ϵ��"},
	//{Role_Attrib_CrushingBlowMultiplier,	"��ѹ�˺�ϵ��"},
	//{Role_Attrib_GlanceMultipiler,			"ƫб�˺�ϵ��"},

	//{Role_Attrib_FireAccuracy,				"���淨��������"},
	//{Role_Attrib_FireDodge,					"���淨��������"},
	//{Role_Attrib_FireBlock,					"���淨������"},


	//{Role_Attrib_FireBlockMultiplier,		"���淨�����˺�ϵ��"},
	

	//{Role_Attrib_ColdAccuracy,				"���䷨��������"},
	//{Role_Attrib_ColdDodge,					"���䷨��������"},
	//{Role_Attrib_ColdBlock,					"���䷨������"},

	//{Role_Attrib_ColdBlockMultiplier,		"���䷨�����˺�ϵ��"},

	//{Role_Attrib_LightningAccuracy,			"���編��������"},
	//{Role_Attrib_LightningDodge,			"���編��������"},
	//{Role_Attrib_LightningBlock,			"���編������"},

	//{Role_Attrib_LightningBlockMultiplier,	"���編�����˺�ϵ��"},


	//{Role_Attrib_PoisonAccuracy,			"���ط���������"},
	//{Role_Attrib_PoisonDodge,				"���ط���������"},
	//{Role_Attrib_PoisonBlock,				"���ط�������"},

	//{Role_Attrib_PoisonBlockMultiplier,		"���ط������˺�ϵ��"},


	//{Role_Attrib_HealingAccuracy,			"���Ʒ���������"},
	//{Role_Attrib_HealingDodge,				"���Ʒ���������"},
	//{Role_Attrib_HealingBlock,				"���Ʒ�������"},

	//{Role_Attrib_HealingBlockMultiplier,	"���Ʒ�����Ч��ϵ��"},


	//{Role_Attrib_SpellAccuracy,				"����������"},
	//{Role_Attrib_SpellDodge,				"����������"},
	//{Role_Attrib_SpellBlock,				"��������"},

	//{Role_Attrib_SpellBlockMultiplier,		"�������˺�ϵ��"},



	//{Role_Attrib_MeleeDamageAbsorb,			"��ս�˺�����"},
	//{Role_Attrib_MeleeDamageAbsorbRate,		"��ս�˺��ٷֱ�����"},
	//{Role_Attrib_MeleeDamageRebound,		"��ս�˺�����"},
	//{Role_Attrib_MeleeDamageReboundRate,	"��ս�˺��ٷֱȷ���"},

	//{Role_Attrib_RangeDamageAbsorb,			"Զ���˺�����"},
	//{Role_Attrib_RangeDamageAbsorbRate,		"Զ���˺��ٷֱ�����"},
	//{Role_Attrib_RangeDamageRebound,		"Զ���˺�����"},
	//{Role_Attrib_RangeDamageReboundRate,	"Զ���˺��ٷֱȷ���"},

	//{Role_Attrib_DamageAbsorb,				"�˺�����"},
	//{Role_Attrib_DamageAbsorbRate,			"�˺��ٷֱ�����"},
	//{Role_Attrib_DamageRebound,				"�˺�����"},
	//{Role_Attrib_DamageReboundRate,			"�˺��ٷֱȷ���"},

	//{Role_Attrib_FireDamageAbsorb,			"�����˺�����"},
	//{Role_Attrib_FireDamageAbsorbRate,		"�����˺��ٷֱ�����"},
	//{Role_Attrib_FireDamageRebound,			"�����˺�����"},
	//{Role_Attrib_FireDamageReboundRate,		"�����˺��ٷֱȷ���"},

	//{Role_Attrib_ColdDamageAbsorb,			"�����˺�����"},
	//{Role_Attrib_ColdDamageAbsorbRate,		"�����˺��ٷֱ�����"},
	//{Role_Attrib_ColdDamageRebound,			"�����˺�����"},
	//{Role_Attrib_ColdDamageReboundRate,		"�����˺��ٷֱȷ���"},

	//{Role_Attrib_LightningDamageAbsorb,		"�����˺�����"},
	//{Role_Attrib_LightningDamageAbsorbRate,	"�����˺��ٷֱ�����"},
	//{Role_Attrib_LightningDamageRebound,	"�����˺�����"},
	//{Role_Attrib_LightningDamageReboundRate,"�����˺��ٷֱȷ���"},

	//{Role_Attrib_PoisonDamageAbsorb,		"�����˺�����"},
	//{Role_Attrib_PoisonDamageAbsorbRate,	"�����˺��ٷֱ�����"},
	//{Role_Attrib_PoisonDamageRebound,		"�����˺�����"},
	//{Role_Attrib_PoisonDamageReboundRate,	"�����˺��ٷֱȷ���"},

	//{Role_Attrib_HealingAbsorb,   			"����Ч������"}, //������		
	//{Role_Attrib_HealingAbsorbRate,			"����Ч���ٷֱ�����"},//������	
	//{Role_Attrib_HealingRebound,			"����Ч������"},
	//{Role_Attrib_HealingReboundRate,		"����Ч���ٷֱȷ���"},


	//{Role_Attrib_SpellDamageAbsorb,			"�����˺�����"},
	//{Role_Attrib_SpellDamageAbsorbRate,		"�����˺��ٷֱ�����"},
	//{Role_Attrib_SpellDamageRebound,		"�����˺�����"},
	//{Role_Attrib_SpellDamageReboundRate,	"�����˺��ٷֱȷ���"},

	//{Role_Attrib_AllDamageAbsorb,			"�����˺�����"},
	//{Role_Attrib_AllDamageAbsorbRate,		"�����˺��ٷֱ�����"},
	//{Role_Attrib_AllDamageRebound,			"�����˺�����"},
	//{Role_Attrib_AllDamageReboundRate,		"�����˺��ٷֱȷ���"},



	//{Role_Attrib_AttackSpeed,				"�����ٶ�"},
	//{Role_Attrib_CastRate,					"ʩ���ٶ�"},
	//{Role_Attrib_RunSpeed,					"�ƶ��ٶ�"},

	//{Role_Attrib_FastAttackSpeed,			"��������"},
	//{Role_Attrib_FastCastRate,				"ʩ������"},

	{Role_Attrib_DamageToMana,				"�˺�ת�Ƹ�����"},


	//{Role_Attrib_MinMeleeDamageReduce,		"��С��ս�˺��ٷֱȼ���"},
	//{Role_Attrib_MaxMeleeDamageReduce,		"����ս�˺��ٷֱȼ���"},
	//{Role_Attrib_MeleeDamageReduce,			"��ս�˺��ٷֱȼ���"},

	//{Role_Attrib_MinRangeDamageReduce,		"��СԶ���˺��ٷֱȼ���"},
	//{Role_Attrib_MaxRangeDamageReduce,		"���Զ���˺��ٷֱȼ���"},
	//{Role_Attrib_RangeDamageReduce,			"Զ���˺��ٷֱȼ���"},

	//{Role_Attrib_MinPhysicDamageReduce,			"��С�˺��ٷֱȼ���"},
	//{Role_Attrib_MaxPhysicDamageReduce,			"����˺��ٷֱȼ���"},
	

	//{Role_Attrib_MinFireDamageReduce,		"��С�����˺��ٷֱȼ���"},
	//{Role_Attrib_MaxFireDamageReduce,		"�������˺��ٷֱȼ���"},
	//{Role_Attrib_FireDamageReduce,			"�����˺��ٷֱȼ���"},

	//{Role_Attrib_MinColdDamageReduce,		"��С�����˺��ٷֱȼ���"},
	//{Role_Attrib_MaxColdDamageReduce,		"�������˺��ٷֱȼ���"},
	//{Role_Attrib_ColdDamageReduce,			"�����˺��ٷֱȼ���"},

	//{Role_Attrib_MinLightningDamageReduce,	"��С�����˺��ٷֱȼ���"},
	//{Role_Attrib_MaxLightningDamageReduce,	"��������˺��ٷֱȼ���"},
	//{Role_Attrib_LightningDamageReduce,		"�����˺��ٷֱȼ���"},

	//{Role_Attrib_MinPoisonDamageReduce,		"��С�����˺��ٷֱȼ���"},
	//{Role_Attrib_MaxPoisonDamageReduce,		"������˺��ٷֱȼ���"},
	//{Role_Attrib_PoisonDamageReduce,		"�����˺��ٷֱȼ���"},

	//{Role_Attrib_MinHealingReduce,			"��С���ưٷֱȼ���"},
	//{Role_Attrib_MaxHealingReduce,			"������ưٷֱȼ���"},

	//	441,

	//	446,

	//	451,

	//	456,

	//	461,	

	//{Role_Attrib_MinSpellDamageReduce,		"��С�����˺��ٷֱȼ���"},
	//{Role_Attrib_MaxSpellDamageReduce,		"������˺��ٷֱȼ���"},

	

	//{ Role_Attrib_MinDamageMeleeOH,			"��ս������С�˺�"},
	//{ Role_Attrib_MaxDamageMeleeOH,			"��ս��������˺�"},	

	//{ Role_Attrib_MinDamageRange,			"Զ����С�˺�"},
	//{ Role_Attrib_MaxDamageRange,			"Զ������˺�"},


	//{ Role_Attrib_MinDamagePhysical,		"������С�˺�"},
	//{ Role_Attrib_MaxDamagePhysical,		"��������˺�"},
	//{ Role_Attrib_DamagePhysical,			"�����˺�"},
	//{ Role_Attrib_DamagePhysicalEnhance,	"�����˺��ٷֱ�����"},

	//{ Role_Attrib_MinDamageFire,			"������С�˺�"},
	//{ Role_Attrib_MaxDamageFire,			"��������˺�"},

	//{ Role_Attirb_MinDamageCold,			"������С�˺�"},
	//{ Role_Attirb_MaxDamageCold,			"��������˺�"},

	//{ Role_Attrib_MinDamageLightning,		"������С�˺�"},
	//{ Role_Attrib_MaxDamageLightning,		"��������˺�"},

	//{ Role_Attrib_MinDamagePoison,			"������С�˺�"},
	//{ Role_Attrib_MaxDamagePoison,			"��������˺�"},

	//{ Role_Attrib_MinHealing,				"��С����"},
	//{ Role_Attrib_MaxHealing,				"�������"},



		//	141,

		//	146,

		//	151,

		//	156,

		//	161,

	//{ Role_Attrib_MinDamageSpell,			"������С�˺�"},
	//{ Role_Attrib_MaxDamageSpell,			"��������˺�"},
	//{ Role_Attrib_DamageSpell,				"�����˺�"},
	//{ Role_Attrib_DamageSpellEnhance,		"�����˺��ٷֱ�����"},


		//////////////////////////////////////////////////
		///������ǿ�� & �������� & ��������
		//////////////////////////////////////////////////	

	//{ Role_Attrib_MinAttackPowerMeleeOH,		"��ս��С����ǿ��"},
	//{ Role_Attrib_MaxAttackPowerMeleeOH,		"��ս��󹥻�ǿ��"},


	//{ Role_Attrib_AttackPowerMeleeEnhanceOH,	"��ս����ǿ�Ȱٷֱ�����"},



	//{ Role_Attrib_MinAttackPowerRange,		"Զ����С����ǿ��"},
	//{ Role_Attrib_MaxAttackPowerRange,		"Զ����󹥻�ǿ��"},
	//{ Role_Attrib_AttackPowerRangeEnhance,	"Զ�̹���ǿ�Ȱٷֱ�����"},


	//{ Role_Attrib_MinAttackPower,			"��С����ǿ��"},
	//{ Role_Attrib_MaxAttackPower,			"��󹥻�ǿ��"},
	//{ Role_Attrib_AttackPowerEnhance,		"����ǿ�Ȱٷֱ�����"},

	//{ Role_Attrib_MinSpellPowerFire,		"��С���淨������"},
	//{ Role_Attrib_MaxSpellPowerFire,		"�����淨������"},
	//{ Role_Attrib_SpellPowerFireEnhance,	"���淨�������ٷֱ�����"},

	//{ Role_Attrib_MinSpellPowerCold,		"��С���䷨������"},
	//{ Role_Attrib_MaxSpellPowerCold,		"�����䷨������"},
	//{ Role_Attrib_SpellPowerColdEnhance,	"���䷨�������ٷֱ�����"},

	//{ Role_Attrib_MinSpellPowerLightning,	"��С���編������"},
	//{ Role_Attrib_MaxSpellPowerLightning,	"������編������"},
	//{ Role_Attrib_SpellPowerLightningEnhance,"���編�������ٷֱ�����"},

	//{ Role_Attrib_MinSpellPowerPoison,		"��С���ط�������"},
	//{ Role_Attrib_MaxSpellPowerPoison,		"����ط�������"},
	//{ Role_Attrib_SpellPowerPoisonEnhance,	"���ط��������ٷֱ�����"},

	//{ Role_Attrib_MinHealingPower,			"��С��������"},
	//{ Role_Attrib_MaxHealingPower,			"�����������"},
	//{ Role_Attrib_HealingPowerEnhance,		"���������ٷֱ�����"},

		//	241,

		//	246,

		//	251,

		//	256,

		//	261,

	//{ Role_Attrib_MinSpellPower,			"��С��������"},
	//{ Role_Attrib_MaxSpellPower,			"���������"},
	//{ Role_Attrib_SpellPowerEnhance,		"���������ٷֱ�����"},

	//{ Role_Attrib_IncreaseAllDamage,		"�����˺�����"},
	//{ Role_Attrib_EnhanceAllDamage,			"�����˺��ٷֱ�����"},

	//{Role_Attrib_IncreaseAllResult,			"����Ч������"},
	//{Role_Attrib_EnhanceAllResult,			"����Ч���ٷֱ�����"},


		//////////////////////////////////////////////////
		///���� & ���� �˺���ֵ����
		//////////////////////////////////////////////////	
	//{ Role_Attrib_MinArmorMeleeOH,			"��С��ս����-����"},  
	//{ Role_Attrib_MaxArmorMeleeOH,			"����ս����-����"},
	//{ Role_Attrib_ArmorMeleeOH,				"��ս����-����"},
	//{ Role_Attrib_ArmorMeleeEnhanceOH,		"��ս���װٷֱ�����"},

	//{ Role_Attrib_MinArmorRange,			"��СԶ�̻���"},
	//{Role_Attrib_MaxArmorRange,				"���Զ�̻���"},
	//{Role_Attrib_ArmorRange,				"Զ�̻���"},
	//{Role_Attrib_ArmorRangeEnhance,			"Զ�̻��װٷֱ�����"},

	//{Role_Attrib_MinArmor,					"��С����"},
	//{Role_Attrib_MaxArmor,					"��󻤼�"},


	//{Role_Attrib_MinFireResist,				"��С���濹��"},
	//{Role_Attrib_MaxFireResist,				"�����濹��"},
	//{Role_Attrib_FireResist,				"���濹��"},
	//{Role_Attrib_FireResistEnhance,			"���濹�԰ٷֱ�����"},

	//{Role_Attrib_MinColdResist,				"��С���俹��"},
	//{Role_Attrib_MaxColdResist,				"�����俹��"},
	//{Role_Attrib_ColdResist,				"���俹��"},
	//{Role_Attrib_ColdResistEnhance,			"���俹�԰ٷֱ�����"},

	//{Role_Attrib_MinLightningResist,		"��С���翹��"},
	//{Role_Attrib_MaxLightningResist,		"������翹��"},
	//{Role_Attrib_LightningResist,			"���翹��"},
	//{Role_Attrib_LightningResistEnhance,	"���翹�԰ٷֱ�����"},

	//{Role_Attrib_MinPoisonResist,			"��С���ؿ���"},
	//{Role_Attrib_MaxPoisonResist,			"����ؿ���"},
	//{Role_Attrib_PoisonResist,				"���ؿ���"},
	//{Role_Attrib_PoisonResistEnhance,		"���ؿ��԰ٷֱ�����"},

	//{Role_Attrib_MinHealingResist,			"��С���ƿ���"},
	//{Role_Attrib_MaxHealingResist,			"������ƿ���"},
	//{Role_Attrib_HealingResist,				"���ƿ���"},
	//{Role_Attrib_HealingResistEnhance,		"���ƿ��԰ٷֱ�����"},

	//	341,

	//	346,

	//	351,

	//	356,

	//	361,


	//{Role_Attrib_MinSpellResist,			"��С��������"},
	//{Role_Attrib_MaxSpellResist,			"���������"},


	//{Role_Attrib_AllArmor,					"�����˺�����"},


	//////////////////////////////////////////////////
	///���� & ���� �˺��ٷֱȼ���
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
