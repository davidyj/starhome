////////////////////////////////////////
//   模块:  read_abi_carton.cpp
//   功能:  读取动画数据(第三部分) from artific.abi
//   作者:  jinsheng 
/////////////////////////////////////////
#include "stdafx.h"
#include "abi.h"

cbone_data::cbone_data(int in_move_lim, int in_circle_lim)
{
	move_count = circle_count = 0;
	move_lim = in_move_lim;
	circle_lim = in_circle_lim;
	
	move_i = new char [move_lim];
	move_d = new MoveData_s [move_lim];
	
	circle_i = new char [circle_lim];
	circle_d = new CircleData_s [circle_lim];
}

cbone_data::~cbone_data()
{
	SAFE_DELETE_ARRAY(move_i);
	SAFE_DELETE_ARRAY(move_d);
	SAFE_DELETE_ARRAY(circle_i);
	SAFE_DELETE_ARRAY(circle_d);
	
}
/*  动画动作 */


CartonData_S::~CartonData_S()
{
	delete bc_data;
	bc_data = NULL;
	bone_num = 0;
}


ccharacter_data::ccharacter_data()
{
	bone_data = NULL;
	bone_carton = NULL;
	carton_data = NULL;
}

ccharacter_data::~ccharacter_data()
{
	delete bone_data;
	delete [] bone_carton;
	delete [] carton_data;
}

//============================
//--Get_Boneindex_ofboneree   获得装备骨头的索引
//============================
int CAbi::Get_Boneindex_ofbonetree(const char * bone_str)
{
	

	bool bFound = false;

	for ( int i = 0; i <m_bonenum; i++)
	{
		if ( stricmp(nd[i].bone_name, bone_str) == 0) // 找到了
		{
			bFound = true;
			break;
		}
	}

	if (!bFound)
		return -1;

    return i;
}


void CAbi::character_release()
{
	SAFE_DELETE(m_character_data);
	
}

//mesh anim
BOOL CMeshAnim::Init()
{
	m_ppMeshAnimData = NULL;
	m_CartonName = NULL;
	m_max_frame = NULL;
	carton_num = 0;
	m_bOk = TRUE;
	return m_bOk;
}

void CMeshAnim::End()
{
	if (m_bOk)
	{
		if (carton_num > 0)
		{
			for ( int i = 0; i < carton_num; i++)
			{
				delete[]m_CartonName[i];
				for ( int j = 0; j < (m_max_frame[i] + 1); j++)
				{
				   delete[](m_ppMeshAnimData[j]); //FIXME
				}
			}
			delete []m_CartonName;
			delete []m_max_frame;
			delete []m_ppMeshAnimData;//FIXME
		}
		m_bOk = FALSE;
	}
}
