#pragma once
#include "PacketDefine.h"
namespace _NS_PET
{

/********************************** ���� Start **************************************/

	#define		FELLOW_NAME_MAX					32			//�������ֵ���󳤶�
	#define		FELLOW_ATTRI_STRING_MAX			16			//���������ַ�������󳤶�
	#define		PROTECTOR_LIST_MAX				6			//�ڶӳ�Ա���������
	const int	FELLOW_LEARN_SKILL_ENHANCE		= 10;		//����ÿ��һ��ʱ��һ��ѧ���ܵİٷֱ�
	//���ʵȼ�
	enum APT_Level
	{
		AL_Invalid = -1,

		AL_White = 1,			//��
		AL_Green,			//��
		AL_Blue,				//��
		AL_Purple,			//��
		AL_Gold,			//��

		AL_Max,
	};

	enum APT_Type
	{
		AT_INVALID = -1,

		AT_Growth = 0,			//�ɳ�
		AT_UnderStand,		//����
		AT_STR,						//����
		AT_INT,					//����
		AT_AGI,						//����
		AT_SPI,						//����
		AT_STA,						//����

		AT_MAX,
	};

	/************************************************************************/
	/*										           ���������                          */
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
	//��������
	enum Const_Value
	{
		SEGMENT_MAX = 10,											//����ṹ���ֶ���
		SKILL_ID_MAX = 10,											//����ID���������
		BIRTH_SKILL_MAX = 10,										//���޳���ʱ��ѡ�ļ��������
	};
	struct sArea
	{
		sArea()
		{
			nMin = 0;
			nMax = 0;
		}

		int nMin;																	//����
		int nMax;																//����
	};
	//��������ṹ,���ڼ����ڼ���������ȡ���ֵ�Ľṹ��
	struct sRangeRandom_T
	{
		sRangeRandom_T()
		{
			bSegmentNum = 0;
			memset(bSegmentRate,0,sizeof(bSegmentRate));
			memset(nSegmentArea,0,sizeof(nSegmentArea));
		}

		sArea					nTotalArea;													//������ϣ�����
		int	 					bSegmentNum;												//�ֶ���
		int						bSegmentRate[SEGMENT_MAX];				//����ÿ����ռ�ı���
		sArea					nSegmentArea[SEGMENT_MAX];				//ÿ�ε��ϣ�����
	};
	//����ģ��
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
		//��������
		int						nTemplateID;									//ģ��ID
		int						nBreedTID;										//��ֳ���ģ��ID
		char					szName[MAX_ALIAS_NAME_LEN];										//����
		int						nModelID;										//����ID
		int						nModelSize;										//���δ�С
		int						nHeadID;										//ͷ��ID
		int						nRectHeadID;									//���ڽ�����ʾ�ķ���ͷ��ID
		int						nRunSpeed;										//�����ٶ�
		int						nWalkSpeed;										//�����ٶ�
		int						nDunt;											//�ػ�
		int						nCampID;										//��ӪID
		int						nTakeLevel;										//Я���ȼ�
		int						nDodgeRate;										//�رܼ���
		int						nChaseDist;										//׷������
		int						nLevel;											//��ʼ����
		int						nLevelLimit;									// �ȼ�����	dxt���2012/2/28
		int						nBornHp;										//��ʼHP
		int						nHappyValue;									//��ʼ����ֵ
		int						nLife;											//��ʼ����
		int						nBreedLevel;									//�״η�ֳ�ȼ�
		int						nBreedNum;										//�ɷ�ֳ����
		int						nFellowFlag;									//�����(���ޱ���,  ��������, �ɷ��ӡ	�ɷ����	�ɷ��ػ�	�ɷ�ֳ	�ɷ��ں�	�ɷ�����	�ɷ�ǿ��)
		int						nSkillID;										//��������ID
		sArea					nSkillRange_Init;								//��������ʱ�ļ�������
		sArea					nSkillRange_Learn;								//��������ʱ����ļ�������
		SkillID					nBirthSkill[BIRTH_SKILL_MAX];					//���޳���ʱҪѧ�ļ���
		SkillID					nSefeGuardSkillID;									//�ػ�����


		//////////////////////////////////////////////////////////////////////////
		//�ɳ�����
		sRangeRandom_T		STR_Aptitude;										//��������
		sRangeRandom_T		INT_Aptitude;										//��������
		sRangeRandom_T		AGI_Aptitude;										//��������
		sRangeRandom_T		SPI_Aptitude;										//��������
		sRangeRandom_T		STA_Aptitude;										//��������

		sRangeRandom_T		sGrow;												//�ɳ�����
		sRangeRandom_T		sUnderStand;										//��������
	};


	/************************************************************************/
	/*										           �������                            */
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
		FT_Baby,		//���ޱ���
		FT_Grown,		//��������
	};

	enum Fellow_Damage_Type
	{
		FDT_Invalid = -1,

		FDT_Physical,     //����ϵ����
		FDT_Magic,			//ħ��ϵ����
	};

	//���޻�����������
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

		int64					MasterPID;																													//���˵�PID
		TemplateID		TID;																																//ģ��ID
		int64					SceneID;																														//���ڳ���ID
		int						nState;																															//״̬
		int						nDir;																																//����
		int64					nBirthTime;																													//���볡����ʱ��
	};
	//����һ����������
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
		
		char						szName[ATTRIB_NAME_MAX];																				//����

		int						nLevel;																																//�ȼ�
		int64						nExp;																																//����
		int64						nMaxExp;																														//�����
		int						nHP;																																//HP
		int						nMaxHP[ParamPool_Size];																															//MaxHP
		//int						nAddMaxHPEnhance;																												//MaxHP�ٷֱȼӳ�

		int                       nBreedNum;																													//�ɷ�ֳ����
		int                       nBreedLevel;																													//�ɷ�ֳ�ȼ�
		int						nSex;																																//�Ա�(FS_Mate:�� FS_Femate:��)
		int						nType;																																//����(0:���ޱ��� 1:��������)
		int						nHappyDeg;																													//���ֶ�
		int						nMaxHappyDeg;																											//�����ֶ�
		int						nLife;																																//����
		int						nMaxLife;																														//�������
		int						nChaseDist;																													//׷������
		int						nStartLevel;																													//��ǰ�Ǽ�
		int						nTakeLevel;																													//Я���ȼ�
	};
	//���޶�����������
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
		int						nGrow;																															//�ɳ�
		int						nUnderStand;																												//����
		int                       nUnuseAttriPoint;																											//ʣ�����Ե�

		int						nAptitude_STR;																											//��������
		int						nAptitude_INT;																											//��������
		int						nAptitude_AGI;																											//��������
		int						nAptitude_SPI;																												//��������
		int						nAptitude_STA;																											//��������

		int						nSTR[ParamPool_Size];																																//����
		int						nINT[ParamPool_Size];																																//����
		int						nAGI[ParamPool_Size];																																//����
		int						nSPI[ParamPool_Size];																																//����
		int						nSTA[ParamPool_Size];																																//����

		int                       nAP[ParamPool_Size];																																	//�﹥
		int						nAC[ParamPool_Size];																																//���
		int                       nMAP[ParamPool_Size];																																//ħ��
		int						nMAC[ParamPool_Size];																																//ħ��

		int						nDunt;																																//�ػ�
		int						nJouk;																																//����

		int						nMaxApt_STR;																											//������������
		int						nMaxApt_INT;																											//������������
		int						nMaxApt_AGI;																											//������������
		int						nMaxApt_SPI;																											//������������
		int						nMaxApt_STA;																											//������������

		int						nGrowAptitude;																											//�ɳ�����
		int						nUnderStandAptitude;																								//��������

		int						nAddStr;																													//���ӵ���������
		int						nAddInt;																													//���ӵ���������
		int						nAddAgi;																													//���ӵ����ݵ���
		int						nAddSpi;																														//���ӵľ������
		int						nAddSta;																													//���ӵ����ʵ���

		//int						nAddAPEnhance;																											//���ӵ�������%
		//int						nAddACEnhance;																											//���ӵ��������%
		//int						nAddMAPEnhance;																											//���ӵ�ħ������%
		//int						nAddMACEnhance;																											//���ӵ�ħ������%
		//int						nAddDuntEnhance;																										//���ӵ��ػ�%
		//int						nAddJoukEnhance;																										//���ӵ�����%
	};

	//����ʱ����
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
		int				nRunSpeed[ParamPool_Size];					//���ٶ�
		int				nWalkSpeed;					//���ٶ�
		int				nNotMove;						//�����ƶ�
		int				nNotControl;					//���ܿ���
		int				nAutoDriveFlag;			//�Զ���ʻ���
		//Debuff����
		int				m_nChancetoDebuff[Debuff_TypeCounts];
		int				m_nReduceChanceofDebuff[Debuff_TypeCounts];
	};

	//��Щ���ݲ���Ҫ������key��Ӧ

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
		BOOL bBind; //�Ƿ�󶨣����ڼ����ں�
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
	/*										           ��Ϣ���                            */
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

	//�ڶӳ�Ա״̬
	enum ProtectorState
	{
		PS_Invalid = -1,
		PS_Common,
		PS_FarAway,
		PS_NotOnLine,
	};
	//�ڶӳ�Ա��Ϣ
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
		int nState; //��Ա״̬��0������ 1��Զ�� 2������
	};

	//�ڶӳ�Ա�б�
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
	//������Ϣ����Ľ��
	enum MSG_RESULT
	{
		MR_SUMMON_SUCCEED,		//�ٻ��ɹ�
		MR_CALLBACK_SUCCEED,     //�ٻسɹ�

		MR_SUCCEED_MODIFYNAME,		//�����ɹ�
		MR_SUCCEED_REBIRTH,       //�����ɹ�

		MR_SUCCEED_FEED,					//ιʳ�ɹ�
		MR_SUCCEED_BREED,					//��ֳ�ɹ�
		MR_SUCCEED_FUSION_APT,	//�������ϳɹ�
		MR_SUCCEED_ADD_SKILL,		//��Ӽ������

		MR_RET_EVOLUTION_RATE,    //����ǿ��ʱ���ɹ���
		MR_RET_EVOLUTION_FAILED,  //ǿ��ʧ��
		MR_RET_EVOLUTION_OK, //ǿ���ɹ�

		MR_RET_RIDE_ENHANCE_OK,  //���ǿ���ɹ�
		MR_RET_RIDE_SUMMON_SUCCEED,	// ����ٻ��ɹ�
		MR_RET_RIDE_CALLBACK_SUCCEED,	// ����ٻسɹ�

		MR_COMBATPET_SUMMON_OVER, //ս���ٻ����
	};

	/********************************** ���� End **************************************/
};


//����ս����CommonData�ļ��в������� PacketDefine.h �����������˴�
enum FamilyCarType
{
	FCT_Invalid = -1,
	FCT_Ordnance,				//������
	FCT_Life,						//������
	FCT_Speed,					//�ٶ���
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
	int						m_nFamilyID;																//����ID
	//int						m_nCarID;																	//ս������
	int						m_TID;																		//ս��ģ��
	int						m_HP;																			//����
	int						m_nMaxHP;																//�������
	int						m_nStatus;																	//����״̬ 0:���� 1:����
	__int64				m_LastUser;																//�ϴ�������PID
	__int64				m_CurrentUser;															//��ǰ������PID
	char						m_szCarName[MAX_ALIAS_NAME_LEN];			//ս������
	char						m_szLastUser[MAX_ALIAS_NAME_LEN];			//���һ��ʹ��������
	char						m_szCurrentUser[MAX_ALIAS_NAME_LEN];	//��ǰʹ��������

	int						m_FCarType;																//ս�����ͣ���ӦFamilyCarTypeö��ֵ
	int						m_nAP;
	int						m_nMAP;
	int						m_nAC;
	int						m_nMAC;
	int						m_nSpeed;
	int						m_nEffectID;															//ս������Ч��ID

	int						m_nQuality;																//ս��Ʒ��
};
