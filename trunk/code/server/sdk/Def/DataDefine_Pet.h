#pragma once
#include "PacketDefine.h"
namespace _NS_PET
{

/********************************** 玄兽 Start **************************************/

	#define		FELLOW_NAME_MAX					32			//玄兽名字的最大长度
	#define		FELLOW_ATTRI_STRING_MAX			16			//玄兽属性字符串的最大长度
	#define		PROTECTOR_LIST_MAX				6			//镖队成员的最大人数
	const int	FELLOW_LEARN_SKILL_ENHANCE		= 10;		//珍兽每升一级时会一个学技能的百分比
	//资质等级
	enum APT_Level
	{
		AL_Invalid = -1,

		AL_White = 1,			//白
		AL_Green,			//绿
		AL_Blue,				//蓝
		AL_Purple,			//紫
		AL_Gold,			//金

		AL_Max,
	};

	enum APT_Type
	{
		AT_INVALID = -1,

		AT_Growth = 0,			//成长
		AT_UnderStand,		//悟性
		AT_STR,						//力量
		AT_INT,					//智力
		AT_AGI,						//敏捷
		AT_SPI,						//精神
		AT_STA,						//体质

		AT_MAX,
	};

	/************************************************************************/
	/*										           读表器相关                          */
	/************************************************************************/

	//////////////////////////////////////////////////////////////////////////
	// BreedRule.csv

	struct sBreedRuleData_T
	{
		int nApt_Main;
		int nApt_Auxi;

		int nNum;

		int nApt_One;
		int nRate_One;
		int nApt_Two;
		int nRate_Two;
		int nApt_Three;
		int nRate_Three;
		int nApt_Four;
		int nRate_Four;
		int nApt_Five;
		int nRate_Five;
	};

	//////////////////////////////////////////////////////////////////////////
	// pettemplate.csv
	//常量定义
	enum Const_Value
	{
		SEGMENT_MAX = 10,											//随机结构最大分段数
		SKILL_ID_MAX = 10,											//技能ID的最大数量
		BIRTH_SKILL_MAX = 10,										//珍兽出生时可选的技能最大数
	};
	struct sArea
	{
		sArea()
		{
			nMin = 0;
			nMax = 0;
		}

		int nMin;																	//下限
		int nMax;																//上限
	};
	//区间随机结构,用于计算在几段区间内取随机值的结构体
	struct sRangeRandom_T
	{
		sRangeRandom_T()
		{
			bSegmentNum = 0;
			memset(bSegmentRate,0,sizeof(bSegmentRate));
			memset(nSegmentArea,0,sizeof(nSegmentArea));
		}

		sArea					nTotalArea;													//整体的上，下限
		int	 					bSegmentNum;												//分段数
		int						bSegmentRate[SEGMENT_MAX];				//保存每段所占的比例
		sArea					nSegmentArea[SEGMENT_MAX];				//每段的上，下限
	};
	//玄兽模板
	struct sFellowTemplate_T : public IBaseObj
	{
	public:
		sFellowTemplate_T()
		{
			nTemplateID = 0;
			nBreedTID = 8001;
			memset(szName,0,sizeof(szName));
			nModelID = 0;
			nModelSize = 0;
			nHeadID = 0;
			nRectHeadID = 0;
			nRunSpeed = 0;
			nWalkSpeed = 0;
			nDunt = 0;
			nCampID = 0;
			nTakeLevel = 0;
			nDodgeRate = 0;
			nChaseDist = 0;
			nLevel = 0;
			nLevelLimit = 0;
			nBornHp = 0;
			nHappyValue = 0;
			nLife = 0;
			nBreedLevel = 0;
			nBreedNum = 0;
			nFellowFlag = 0;
			nSkillID = INVALID_SKILLID;
			nSefeGuardSkillID = INVALID_SKILLID;
			memset(nBirthSkill,INVALID_SKILLID,sizeof(SkillID) * BIRTH_SKILL_MAX );
		}
	public:
		//////////////////////////////////////////////////////////////////////////
		//基本属性
		int						nTemplateID;									//模板ID
		int						nBreedTID;										//繁殖后的模板ID
		char					szName[MAX_ALIAS_NAME_LEN];										//姓名
		int						nModelID;										//外形ID
		int						nModelSize;										//外形大小
		int						nHeadID;										//头像ID
		int						nRectHeadID;									//用于界面显示的方形头像ID
		int						nRunSpeed;										//奔跑速度
		int						nWalkSpeed;										//行走速度
		int						nDunt;											//重击
		int						nCampID;										//阵营ID
		int						nTakeLevel;										//携带等级
		int						nDodgeRate;										//回避几率
		int						nChaseDist;										//追击距离
		int						nLevel;											//初始级别
		int						nLevelLimit;									// 等级上限	dxt添加2012/2/28
		int						nBornHp;										//初始HP
		int						nHappyValue;									//初始快乐值
		int						nLife;											//初始寿命
		int						nBreedLevel;									//首次繁殖等级
		int						nBreedNum;										//可繁殖次数
		int						nFellowFlag;									//标记组(玄兽宝宝,  成年玄兽, 可否封印	可否放生	可否守护	可否繁殖	可否融合	可否炼化	可否强化)
		int						nSkillID;										//基本技能ID
		sArea					nSkillRange_Init;								//创建宠物时的技能区间
		sArea					nSkillRange_Learn;								//宠物升级时领悟的技能区间
		SkillID					nBirthSkill[BIRTH_SKILL_MAX];					//珍兽出生时要学的技能
		SkillID					nSefeGuardSkillID;									//守护技能


		//////////////////////////////////////////////////////////////////////////
		//成长属性
		sRangeRandom_T		STR_Aptitude;										//力量资质
		sRangeRandom_T		INT_Aptitude;										//智力资质
		sRangeRandom_T		AGI_Aptitude;										//敏捷资质
		sRangeRandom_T		SPI_Aptitude;										//精神资质
		sRangeRandom_T		STA_Aptitude;										//体质资质

		sRangeRandom_T		sGrow;												//成长区间
		sRangeRandom_T		sUnderStand;										//悟性区间
	};


	/************************************************************************/
	/*										           属性相关                            */
	/************************************************************************/

	enum Fellow_Sex
	{
		FS_Invalid = -1,
		FS_Mate,
		FS_Femate,
	};

	enum Fellow_Type
	{
		FT_Invalid = -1,
		FT_Baby,		//玄兽宝宝
		FT_Grown,		//成年玄兽
	};

	enum Fellow_Damage_Type
	{
		FDT_Invalid = -1,

		FDT_Physical,     //物理系宝宝
		FDT_Magic,			//魔法系宝宝
	};

	//玄兽基本属性数据
	struct Fellow_Attri_Base
	{
		Fellow_Attri_Base()
		{
			ClearUp();
		}

		void ClearUp()
		{
			MasterPID = INVALID_PID;
			TID = INVALID_TEMPLATE;
			SceneID = INVALID_SCENEID;
			nState = -1;
			nDir = 0;
			nBirthTime = 0;
		}

		//void Write(PACKET_COMMAND & Msg)
		//{
		//	Msg.Add(&MasterPID);
		//	Msg.Add(&TID);
		//	Msg.Add(&SceneID);
		//	Msg.Add(&nState);
		//	Msg.Add(&nDir);
		//	Msg.Add(&nBirthTime);
		//}

		//void Read(PACKET_COMMAND & Msg)
		//{
		//	Msg.Get(&MasterPID);
		//	Msg.Get(&TID);
		//	Msg.Get(&SceneID);
		//	Msg.Get(&nState);
		//	Msg.Get(&nDir);
		//	Msg.Get(&nBirthTime);
		//}

		void ToString(char * pString,int nSize)
		{
			if (NULL == pString)
			{
				return;
			}

			Q_snprintf(pString,nSize,"%I64u_%d",MasterPID,TID);
		}

		void ToRevert(char * pString)
		{
			if (NULL == pString)
			{
				return;
			}
#ifdef WIN32
			sscanf(pString,"%I64u_%d",&MasterPID,&TID);
#else
            sscanf(pString,"%llu_%d",&MasterPID,&TID);
#endif

		}

		int64					MasterPID;																													//主人的PID
		TemplateID		TID;																																//模板ID
		int64					SceneID;																														//所在场景ID
		int						nState;																															//状态
		int						nDir;																																//朝向
		int64					nBirthTime;																													//进入场景的时间
	};
	//玄兽一级属性数据
	struct Fellow_Attri_OneLevel
	{
		Fellow_Attri_OneLevel()
		{
			ClearUp();
		}

		void ClearUp()
		{
			memset(szName,0,sizeof(szName));
			nLevel = 0;
			nExp = 0;
			nMaxExp = 0;
			nHP = 0;
			for ( int i = 0; i < ParamPool_Size; ++i )
				nMaxHP[i] = 0;

			nStartLevel = 0;
			nBreedNum = 0;
			nBreedLevel = 0;
			nSex = FS_Invalid;
			nType = FT_Invalid;
			nHappyDeg = 0;
			nMaxHappyDeg = 0;
			nLife = 0;
			nMaxLife = 0;
			nChaseDist = 0;
			nTakeLevel = 0;
		}

		//void Write(PACKET_COMMAND & Msg)
		//{
		//	Msg.AddString(szName);

		//	Msg.Add(&nLevel);
		//	Msg.Add(&nExp);
		//	Msg.Add(&nMaxExp);
		//	Msg.Add(&nHP);
		//	Msg.Add(&nMaxHP[0]);
		//	Msg.Add(&nMaxHP[1]);
		//	Msg.Add(&nMaxHP[2]);

		//	Msg.Add(&nStartLevel);
		//	Msg.Add(&nBreedNum);
		//	Msg.Add(&nBreedLevel);
		//	Msg.Add(&nSex);
		//	Msg.Add(&nType);
		//	Msg.Add(&nHappyDeg);
		//	Msg.Add(&nMaxHappyDeg);
		//	Msg.Add(&nLife);
		//	Msg.Add(&nMaxLife);
		//	Msg.Add(&nChaseDist);
		//	Msg.Add(&nTakeLevel);
		//}

		//void Read(PACKET_COMMAND & Msg)
		//{
		//	Msg.GetString(szName);

		//	Msg.Get(&nLevel);
		//	Msg.Get(&nExp);
		//	Msg.Get(&nMaxExp);
		//	Msg.Get(&nHP);
		//	Msg.Get(&nMaxHP[0]);
		//	Msg.Get(&nMaxHP[1]);
		//	Msg.Get(&nMaxHP[2]);

		//	Msg.Get(&nStartLevel);
		//	Msg.Get(&nBreedNum);
		//	Msg.Get(&nBreedLevel);
		//	Msg.Get(&nSex);
		//	Msg.Get(&nType);
		//	Msg.Get(&nHappyDeg);
		//	Msg.Get(&nMaxHappyDeg);
		//	Msg.Get(&nLife);
		//	Msg.Get(&nMaxLife);
		//	Msg.Get(&nChaseDist);
		//	Msg.Get(&nTakeLevel);
		//}		
		
		void ToString(char * pString,int nSize)
		{
			if (NULL == pString)
			{
				return;
			}

			_snprintf(pString,nSize,"%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%s",
				nLevel,(int)nExp,(int)nMaxExp,nHP,nMaxHP[0],nMaxHP[1],nMaxHP[2],
				nStartLevel,nBreedNum,nBreedLevel,nSex,nType,nHappyDeg,nMaxHappyDeg,nLife,nMaxLife,nChaseDist,nTakeLevel,szName);
		}

		void ToRevert(char * pString)
		{
			if (NULL == pString)
			{
				return;
			}
			sscanf(pString,"%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%s",&nLevel,&nExp,&nMaxExp,&nHP,
				&nMaxHP[0],&nMaxHP[1],&nMaxHP[2],
				&nStartLevel,&nBreedNum,&nBreedLevel,&nSex,&nType,&nHappyDeg,&nMaxHappyDeg,&nLife,&nMaxLife,&nChaseDist,&nTakeLevel,szName);
		}
		
		char						szName[ATTRIB_NAME_MAX];																				//姓名

		int						nLevel;																																//等级
		int64						nExp;																																//经验
		int64						nMaxExp;																														//最大经验
		int						nHP;																																//HP
		int						nMaxHP[ParamPool_Size];																															//MaxHP
		//int						nAddMaxHPEnhance;																												//MaxHP百分比加成

		int                       nBreedNum;																													//可繁殖次数
		int                       nBreedLevel;																													//可繁殖等级
		int						nSex;																																//性别(FS_Mate:雌 FS_Femate:雄)
		int						nType;																																//类型(0:玄兽宝宝 1:成年玄兽)
		int						nHappyDeg;																													//快乐度
		int						nMaxHappyDeg;																											//最大快乐度
		int						nLife;																																//寿命
		int						nMaxLife;																														//最大寿命
		int						nChaseDist;																													//追击距离
		int						nStartLevel;																													//当前星级
		int						nTakeLevel;																													//携带等级
	};
	//玄兽二级属性数据
	struct Fellow_Attri_TwoLevel
	{
		Fellow_Attri_TwoLevel()
		{
			ClearUp();
		}

		void ClearUp()
		{
			nGrow = 0;
			nUnderStand = 0;
			nUnuseAttriPoint = 0;

			nAptitude_STR = 0;
			nAptitude_INT = 0;
			nAptitude_AGI = 0;
			nAptitude_SPI = 0;
			nAptitude_STA = 0;
			for ( int i = 0; i < ParamPool_Size; ++i )
			{
				nSTR[i] = 0;
				nINT[i] = 0;
				nAGI[i] = 0;
				nSPI[i] = 0;
				nSTA[i] = 0;

				nAP[i] = 0;
				nAC[i] = 0;
				nMAP[i] = 0;
				nMAC[i] = 0;
			}

			nDunt = 0;
			nJouk = 0;

			nMaxApt_STR = 0;
			nMaxApt_INT = 0;
			nMaxApt_AGI = 0;
			nMaxApt_SPI = 0;
			nMaxApt_STA = 0;

			nGrowAptitude = 0;
			nUnderStandAptitude = 0;

			nAddStr = 0;
			nAddInt = 0;
			nAddAgi = 0;
			nAddSpi = 0;
			nAddSta = 0;

			//nAddAPEnhance	 = 0;
			//nAddACEnhance	 = 0;
			//nAddMAPEnhance	 = 0;
			//nAddMACEnhance	 = 0;
			//nAddDuntEnhance	 = 0;
			//nAddJoukEnhance	 = 0;

		}

		//void Write(PACKET_COMMAND & Msg)
		//{
		//	Msg.Add(&nGrow);
		//	Msg.Add(&nUnderStand);
		//	Msg.Add(&nUnuseAttriPoint);

		//	Msg.Add(&nAptitude_STR);
		//	Msg.Add(&nAptitude_INT);
		//	Msg.Add(&nAptitude_AGI);
		//	Msg.Add(&nAptitude_SPI);
		//	Msg.Add(&nAptitude_STA);

		//	Msg.Add(nSTR);
		//	Msg.Add(nINT);
		//	Msg.Add(nAGI);
		//	Msg.Add(nSPI);
		//	Msg.Add(nSTA);

		//	Msg.Add(nAP);
		//	Msg.Add(nAC);
		//	Msg.Add(nMAP);
		//	Msg.Add(nMAC);

		//	Msg.Add(&nDunt);
		//	Msg.Add(&nJouk);

		//	Msg.Add(&nMaxApt_STR);
		//	Msg.Add(&nMaxApt_INT);
		//	Msg.Add(&nMaxApt_AGI);
		//	Msg.Add(&nMaxApt_SPI);
		//	Msg.Add(&nMaxApt_STA);

		//	Msg.Add(&nGrowAptitude);
		//	Msg.Add(&nUnderStandAptitude);

		//	Msg.Add(&nAddStr);
		//	Msg.Add(&nAddInt);
		//	Msg.Add(&nAddAgi);
		//	Msg.Add(&nAddSpi);
		//	Msg.Add(&nAddSta);
		//}

		//void Read(PACKET_COMMAND & Msg)
		//{
		//	Msg.Get(&nGrow);
		//	Msg.Get(&nUnderStand);
		//	Msg.Get(&nUnuseAttriPoint);

		//	Msg.Get(&nAptitude_STR);
		//	Msg.Get(&nAptitude_INT);
		//	Msg.Get(&nAptitude_AGI);
		//	Msg.Get(&nAptitude_SPI);
		//	Msg.Get(&nAptitude_STA);

		//	Msg.Get(nSTR);
		//	Msg.Get(nINT);
		//	Msg.Get(nAGI);
		//	Msg.Get(nSPI);
		//	Msg.Get(nSTA);

		//	Msg.Get(nAP);
		//	Msg.Get(nAC);
		//	Msg.Get(nMAP);
		//	Msg.Get(nMAC);

		//	Msg.Get(&nDunt);
		//	Msg.Get(&nJouk);

		//	Msg.Get(&nMaxApt_STR);
		//	Msg.Get(&nMaxApt_INT);
		//	Msg.Get(&nMaxApt_AGI);
		//	Msg.Get(&nMaxApt_SPI);
		//	Msg.Get(&nMaxApt_STA);

		//	Msg.Get(&nGrowAptitude);
		//	Msg.Get(&nUnderStandAptitude);

		//	Msg.Get(&nAddStr);
		//	Msg.Get(&nAddInt);
		//	Msg.Get(&nAddAgi);
		//	Msg.Get(&nAddSpi);
		//	Msg.Get(&nAddSta);
		//}

		void ToString(char * pString,int nSize)
		{
			if (NULL == pString)
			{
				return;
			}

			_snprintf(pString,nSize,"%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d",
				nGrow,nUnderStand,nUnuseAttriPoint,
				nAptitude_STR,nAptitude_INT,nAptitude_AGI,nAptitude_SPI,nAptitude_STA,
				nSTR[0],nSTR[1],nSTR[2],
				nINT[0],nINT[1],nINT[2],
				nAGI[0],nAGI[1],nAGI[2],
				nSPI[0],nSPI[1],nSPI[2],
				nSTA[0],nSTA[1],nSTA[2],
				nAP[0],nAP[1],nAP[2],
				nAC[0],nAC[1],nAC[2],
				nMAP[0],nMAP[1],nMAP[2],
				nMAC[0],nMAC[1],nMAC[2],
				nDunt,nJouk,
				nMaxApt_STR,nMaxApt_INT,nMaxApt_AGI,nMaxApt_SPI,nMaxApt_STA,
				nGrowAptitude,nUnderStandAptitude,
				nAddStr,nAddInt,nAddAgi,nAddSpi,nAddSta);
		}

		void ToRevert(char * pString)
		{
			if (NULL == pString)
			{
				return;
			}
			sscanf(pString,"%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d",
				&nGrow,&nUnderStand,&nUnuseAttriPoint,
				&nAptitude_STR,&nAptitude_INT,&nAptitude_AGI,&nAptitude_SPI,&nAptitude_STA,
				&nSTR[0],&nSTR[1],&nSTR[2],
				&nINT[0],&nINT[1],&nINT[2],
				&nAGI[0],&nAGI[1],&nAGI[2],
				&nSPI[0],&nSPI[1],&nSPI[2],
				&nSTA[0],&nSTA[1],&nSTA[2],
				&nAP[0],&nAP[1],&nAP[2],
				&nAC[0],&nAC[1],&nAC[2],
				&nMAP[0],&nMAP[1],&nMAP[2],
				&nMAC[0],&nMAC[1],&nMAC[2],
				&nDunt,&nJouk,
				&nMaxApt_STR,&nMaxApt_INT,&nMaxApt_AGI,&nMaxApt_SPI,&nMaxApt_STA,
				&nGrowAptitude,&nUnderStandAptitude,
				&nAddStr,&nAddInt,&nAddAgi,&nAddSpi,&nAddSta);
		}
		int						nGrow;																															//成长
		int						nUnderStand;																												//悟性
		int                       nUnuseAttriPoint;																											//剩余属性点

		int						nAptitude_STR;																											//力量资质
		int						nAptitude_INT;																											//智力资质
		int						nAptitude_AGI;																											//敏捷资质
		int						nAptitude_SPI;																												//精神资质
		int						nAptitude_STA;																											//体质资质

		int						nSTR[ParamPool_Size];																																//力量
		int						nINT[ParamPool_Size];																																//智力
		int						nAGI[ParamPool_Size];																																//敏捷
		int						nSPI[ParamPool_Size];																																//精神
		int						nSTA[ParamPool_Size];																																//体质

		int                       nAP[ParamPool_Size];																																	//物攻
		int						nAC[ParamPool_Size];																																//物防
		int                       nMAP[ParamPool_Size];																																//魔攻
		int						nMAC[ParamPool_Size];																																//魔防

		int						nDunt;																																//重击
		int						nJouk;																																//闪避

		int						nMaxApt_STR;																											//力量资质上限
		int						nMaxApt_INT;																											//智力资质上限
		int						nMaxApt_AGI;																											//敏捷资质上限
		int						nMaxApt_SPI;																											//精神资质上限
		int						nMaxApt_STA;																											//体质资质上限

		int						nGrowAptitude;																											//成长资质
		int						nUnderStandAptitude;																								//悟性资质

		int						nAddStr;																													//增加的力量点数
		int						nAddInt;																													//增加的智力点数
		int						nAddAgi;																													//增加的敏捷点数
		int						nAddSpi;																														//增加的精神点数
		int						nAddSta;																													//增加的体质点数

		//int						nAddAPEnhance;																											//增加的物理攻击%
		//int						nAddACEnhance;																											//增加的物理防御%
		//int						nAddMAPEnhance;																											//增加的魔法攻击%
		//int						nAddMACEnhance;																											//增加的魔法防御%
		//int						nAddDuntEnhance;																										//增加的重击%
		//int						nAddJoukEnhance;																										//增加的闪避%
	};

	//运行时属性
	struct Fellow_Runtime_Attri
	{
		Fellow_Runtime_Attri() { ClearUp(); }
		void ClearUp()
		{
			for( int i = 0; i < ParamPool_Size; ++i )
				nRunSpeed[i] = 0;
			nWalkSpeed = 0;
			nNotMove = 0;
			nNotControl = 0;
			nAutoDriveFlag = 0;
			nPos = 0;
			for ( int i = 0; i < Debuff_TypeCounts; ++i )
			{
				m_nChancetoDebuff[i] = 0;
				m_nReduceChanceofDebuff[i] = 0;

			}
		}

		int				nPos;
		int				nRunSpeed[ParamPool_Size];					//跑速度
		int				nWalkSpeed;					//走速度
		int				nNotMove;						//不能移动
		int				nNotControl;					//不能控制
		int				nAutoDriveFlag;			//自动驾驶标记
		//Debuff几率
		int				m_nChancetoDebuff[Debuff_TypeCounts];
		int				m_nReduceChanceofDebuff[Debuff_TypeCounts];
	};

	//这些数据不需要有属性key对应

	struct SkillInfo_T
	{
		SkillInfo_T()
		{
			ClearUp();
		}

		void ClearUp()
		{
			nSkillID = INVALID_SKILLID;
			bBind = FALSE;
		}

		SkillID nSkillID;
		BOOL bBind; //是否绑定，用于技能融合
	};
	struct Fellow_SkillData
	{
		Fellow_SkillData() { ClearUp(); }
		void ClearUp()
		{
			nBaseSkillID = INVALID_SKILLID;
			for (int i = 0; i < SKILL_ID_MAX; i++)
			{
				nSkillInfo[i].ClearUp();
			}
		}

		//void Write(PACKET_COMMAND & Msg)
		//{
		//	Msg.Add(&nBaseSkillID);
		//	for (int i = 0; i < SKILL_ID_MAX; i++)
		//	{
		//		Msg.Add(&nSkillInfo[i].nSkillID);
		//		Msg.Add(&nSkillInfo[i].bBind);
		//	}
		//}

		//void Read(PACKET_COMMAND & Msg)
		//{
		//	Msg.Get(&nBaseSkillID);
		//	for (int i = 0; i < SKILL_ID_MAX; i++)
		//	{
		//		Msg.Get(&nSkillInfo[i].nSkillID);
		//		Msg.Get(&nSkillInfo[i].bBind);
		//	}
		//}

		bool IsExist(SkillID nID)
		{
			for (int i = 0; i < SKILL_ID_MAX; i++)
			{
				if (nID == nSkillInfo[i].nSkillID)
				{
					return true;
				}
			}
			return false;
		}
		int GetIndexBySkillID(SkillID nID)
		{
			for (int i = 0; i < SKILL_ID_MAX; i++)
			{
				if (nID == nSkillInfo[i].nSkillID)
				{
					return i;
				}
			}
			return INVALID_VALUE;
		}
		int FindValidIndex()
		{
			for (int i = 0; i < SKILL_ID_MAX; i++)
			{
				if (INVALID_SKILLID == nSkillInfo[i].nSkillID)
				{
					return i;
				}
			}
			return -1;
		}

		void ToString(char * pString,int nSize)
		{
			if (NULL == pString)
			{
				return;
			}

			_snprintf(pString,nSize,"%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d",
				nBaseSkillID,
				nSkillInfo[0].nSkillID,
				nSkillInfo[1].nSkillID,
				nSkillInfo[2].nSkillID,
				nSkillInfo[3].nSkillID,
				nSkillInfo[4].nSkillID,
				nSkillInfo[5].nSkillID,
				nSkillInfo[6].nSkillID,
				nSkillInfo[7].nSkillID,
				nSkillInfo[8].nSkillID,
				nSkillInfo[9].nSkillID);
		}
		void ToRevert(char * pString)
		{
			if (NULL == pString)
			{
				return;
			}
			sscanf(pString,"%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d",
				&nBaseSkillID,
				&nSkillInfo[0].nSkillID,
				&nSkillInfo[1].nSkillID,
				&nSkillInfo[2].nSkillID,
				&nSkillInfo[3].nSkillID,
				&nSkillInfo[4].nSkillID,
				&nSkillInfo[5].nSkillID,
				&nSkillInfo[6].nSkillID,
				&nSkillInfo[7].nSkillID,
				&nSkillInfo[8].nSkillID,
				&nSkillInfo[9].nSkillID);
		}
		SkillID			nBaseSkillID;
		SkillInfo_T	nSkillInfo[SKILL_ID_MAX];
	};
	/************************************************************************/
	/*										           消息相关                            */
	/************************************************************************/

	struct Msg_FullFellowData
	{
		Msg_FullFellowData()
		{
			ClearUp();
		}

		void ClearUp()
		{
			m_BaseAttri.ClearUp();
			m_OneLevelAttri.ClearUp();
			m_TwoLevelAttri.ClearUp();
			m_RuntimeAttri.ClearUp();
			m_SkillData.ClearUp();
		}

		//void Write(PACKET_COMMAND & Msg)
		//{
		//	m_BaseAttri.Write(Msg);
		//	m_OneLevelAttri.Write(Msg);
		//	m_TwoLevelAttri.Write(Msg);
		//	m_RuntimeAttri.Write(Msg);
		//	m_SkillData.Write(Msg);
		//}

		//void Read(PACKET_COMMAND & Msg)
		//{
		//	m_BaseAttri.Read(Msg);
		//	m_OneLevelAttri.Read(Msg);
		//	m_TwoLevelAttri.Read(Msg);
		//	m_RuntimeAttri.Read(Msg);
		//	m_SkillData.Read(Msg);
		//}

		Fellow_Attri_Base				m_BaseAttri;
		Fellow_Attri_OneLevel		m_OneLevelAttri;
		Fellow_Attri_TwoLevel		m_TwoLevelAttri;
		Fellow_Runtime_Attri			m_RuntimeAttri;
		Fellow_SkillData					m_SkillData;
	};

	struct Msg_RidePetData
	{
		Msg_RidePetData()
		{
			ClearUp();
		}

		void ClearUp()
		{
			PID = INVALID_PID;
			MasterPID = INVALID_PID;
			TID = INVALID_TEMPLATE;
			nAddHp = 0;
			nAddSpeed = 0;

			nAddSTR = 0;
			nAddINT = 0;
			nAddAGI = 0;
			nAddSPI = 0;
			nAddSTA = 0;

			nAddAp = 0;
			nAddAC = 0;
			nAddMAP = 0;
			nAddMAC = 0;
		}

		//void Write(PACKET_COMMAND & Msg)
		//{
		//	Msg.Add(&PID);
		//	Msg.Add(&MasterPID);
		//	Msg.Add(&TID);

		//	Msg.Add(&nAddHp);
		//	Msg.Add(&nAddSpeed);

		//	Msg.Add(&nAddSTR);
		//	Msg.Add(&nAddINT);
		//	Msg.Add(&nAddAGI);
		//	Msg.Add(&nAddSPI);
		//	Msg.Add(&nAddSTA);

		//	Msg.Add(&nAddAp);
		//	Msg.Add(&nAddAC);
		//	Msg.Add(&nAddMAP);
		//	Msg.Add(&nAddMAC);
		//}

		//void Read(PACKET_COMMAND & Msg)
		//{
		//	Msg.Get(&PID);
		//	Msg.Get(&MasterPID);
		//	Msg.Get(&TID);

		//	Msg.Get(&nAddHp);
		//	Msg.Get(&nAddSpeed);

		//	Msg.Get(&nAddSTR);
		//	Msg.Get(&nAddINT);
		//	Msg.Get(&nAddAGI);
		//	Msg.Get(&nAddSPI);
		//	Msg.Get(&nAddSTA);

		//	Msg.Get(&nAddAp);
		//	Msg.Get(&nAddAC);
		//	Msg.Get(&nAddMAP);
		//	Msg.Get(&nAddMAC);
		//}


		void ToString(char * pString,int nSize)
		{
			if (NULL == pString)
			{
				return;
			}

			_snprintf(pString,nSize,"%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d",
				nAddHp,nAddSpeed,
				nAddSTR,nAddINT,nAddAGI,nAddSPI,nAddSTA,
				nAddAp,nAddAC,nAddMAP,nAddMAC);
		}

		void ToRevert(char * pString)
		{
			if (NULL == pString)
			{
				return;
			}

			sscanf(pString,"%d_%d_%d_%d_%d_%d_%d_%d_%d_%d_%d",
				&nAddHp,&nAddSpeed,
				&nAddSTR,&nAddINT,&nAddAGI,&nAddSPI,&nAddSTA,
				&nAddAp,&nAddAC,&nAddMAP,&nAddMAC);
		}


		PersonID PID;
		PersonID MasterPID;
		TemplateID TID;

		int nAddHp;
		int nAddSpeed;

		int nAddSTR;
		int nAddINT;
		int nAddAGI;
		int nAddSPI;
		int nAddSTA;

		int nAddAp;
		int nAddAC;
		int nAddMAP;
		int nAddMAC;
	};

	//镖队成员状态
	enum ProtectorState
	{
		PS_Invalid = -1,
		PS_Common,
		PS_FarAway,
		PS_NotOnLine,
	};
	//镖队成员信息
	struct	sProtectorInfo_T
	{
		sProtectorInfo_T()
		{
			ClearUp();
		}

		void ClearUp()
		{
			PID = INVALID_PID;
			memset(szName,0,sizeof(szName));
			nState = PS_Invalid;
		}

		PersonID PID;
		char szName[MAX_ALIAS_NAME_LEN];
		int nState; //成员状态，0：正常 1：远离 2：下线
	};

	//镖队成员列表
	struct Msg_ProtectorList
	{
		Msg_ProtectorList()
		{
			ClearUp();
		}

		void ClearUp()
		{
			for (int i = 0; i < PROTECTOR_LIST_MAX; i++)
			{
				ProtectorList[i].ClearUp();
			}
		}

		//void Write(PACKET_COMMAND & Msg)
		//{
		//	for (int i = 0; i < PROTECTOR_LIST_MAX; i++)
		//	{
		//		Msg.Add(&ProtectorList[i].PID);
		//		Msg.AddString(ProtectorList[i].szName);
		//		Msg.Add(&ProtectorList[i].nState);
		//	}
		//}

		//void Read(PACKET_COMMAND & Msg)
		//{
		//	for (int i = 0; i < PROTECTOR_LIST_MAX; i++)
		//	{
		//		Msg.Get(&ProtectorList[i].PID);
		//		Msg.GetString(ProtectorList[i].szName);
		//		Msg.Get(&ProtectorList[i].nState);
		//	}
		//}

		sProtectorInfo_T  ProtectorList[PROTECTOR_LIST_MAX];
	};
	//定义消息处理的结果
	enum MSG_RESULT
	{
		MR_SUMMON_SUCCEED,		//召唤成攻
		MR_CALLBACK_SUCCEED,     //召回成攻

		MR_SUCCEED_MODIFYNAME,		//改名成攻
		MR_SUCCEED_REBIRTH,       //重生成攻

		MR_SUCCEED_FEED,					//喂食成功
		MR_SUCCEED_BREED,					//繁殖成功
		MR_SUCCEED_FUSION_APT,	//资质整合成功
		MR_SUCCEED_ADD_SKILL,		//添加技能完毕

		MR_RET_EVOLUTION_RATE,    //返回强化时，成功率
		MR_RET_EVOLUTION_FAILED,  //强化失败
		MR_RET_EVOLUTION_OK, //强化成功

		MR_RET_RIDE_ENHANCE_OK,  //骑宠强化成功
		MR_RET_RIDE_SUMMON_SUCCEED,	// 骑宠召唤成功
		MR_RET_RIDE_CALLBACK_SUCCEED,	// 骑宠召回成功

		MR_COMBATPET_SUMMON_OVER, //战宠召唤完毕
	};

	/********************************** 玄兽 End **************************************/
};


//家族战车，CommonData文件中不能引用 PacketDefine.h ，所以移至此处
enum FamilyCarType
{
	FCT_Invalid = -1,
	FCT_Ordnance,				//火炮型
	FCT_Life,						//生命型
	FCT_Speed,					//速度型
};

struct FamilyCarData
{
	FamilyCarData() { ClearUp(); }
	void ClearUp()
	{
		m_nPID = -1;
		m_nFamilyID	= -1;
		m_TID			= -1;
		m_HP				= 0;
		m_nStatus		= -1;

		m_FCarType = -1;
		m_nAP = -1;
		m_nMAP = -1;
		m_nAC = -1;
		m_nMAC = -1;
		m_nSpeed = -1;
		m_nEffectID = -1;

		m_LastUser	= INVALID_PID;
		m_CurrentUser = INVALID_PID;

		m_nQuality = -1;
		memset(m_szCarName,0,sizeof(m_szCarName));
		memset(m_szLastUser,0,sizeof(m_szLastUser));
		memset(m_szCurrentUser,0,sizeof(m_szCurrentUser));
	}

	//void Write(PACKET_COMMAND & Msg)
	//{
	//	Msg.Add(&m_nPID);
	//	Msg.Add(&m_nFamilyID);
	//	Msg.Add(&m_TID);
	//	Msg.Add(&m_HP);
	//	Msg.Add(&m_nMaxHP);
	//	Msg.Add(&m_nStatus);
	//	Msg.Add(&m_LastUser);
	//	Msg.Add(&m_CurrentUser);

	//	Msg.Add(&m_FCarType);
	//	Msg.Add(&m_nAP);
	//	Msg.Add(&m_nMAP);
	//	Msg.Add(&m_nAC);
	//	Msg.Add(&m_nMAC);
	//	Msg.Add(&m_nSpeed);
	//	Msg.Add(&m_nEffectID);
	//	Msg.Add(&m_nQuality);

	//	Msg.AddString(m_szCarName);
	//	Msg.AddString(m_szLastUser);
	//	Msg.AddString(m_szCurrentUser);
	//}

	//void Read(PACKET_COMMAND & Msg)
	//{
	//	Msg.Get(&m_nPID);
	//	Msg.Get(&m_nFamilyID);
	//	Msg.Get(&m_TID);
	//	Msg.Get(&m_HP);
	//	Msg.Get(&m_nMaxHP);
	//	Msg.Get(&m_nStatus);
	//	Msg.Get(&m_LastUser);
	//	Msg.Get(&m_CurrentUser);

	//	Msg.Get(&m_FCarType);
	//	Msg.Get(&m_nAP);
	//	Msg.Get(&m_nMAP);
	//	Msg.Get(&m_nAC);
	//	Msg.Get(&m_nMAC);
	//	Msg.Get(&m_nSpeed);
	//	Msg.Get(&m_nEffectID);
	//	Msg.Get(&m_nQuality);

	//	Msg.GetString(m_szCarName);
	//	Msg.GetString(m_szLastUser);
	//	Msg.GetString(m_szCurrentUser);
	//}

	__int64				m_nPID;
	int						m_nFamilyID;																//家族ID
	//int						m_nCarID;																	//战车索引
	int						m_TID;																		//战车模板
	int						m_HP;																			//生命
	int						m_nMaxHP;																//最大生命
	int						m_nStatus;																	//领用状态 0:闲置 1:领用
	__int64				m_LastUser;																//上次领用人PID
	__int64				m_CurrentUser;															//当前领用人PID
	char						m_szCarName[MAX_ALIAS_NAME_LEN];			//战车名字
	char						m_szLastUser[MAX_ALIAS_NAME_LEN];			//最后一个使用者名字
	char						m_szCurrentUser[MAX_ALIAS_NAME_LEN];	//当前使用者名字

	int						m_FCarType;																//战车类型，对应FamilyCarType枚举值
	int						m_nAP;
	int						m_nMAP;
	int						m_nAC;
	int						m_nMAC;
	int						m_nSpeed;
	int						m_nEffectID;															//战车辅助效果ID

	int						m_nQuality;																//战车品质
};
