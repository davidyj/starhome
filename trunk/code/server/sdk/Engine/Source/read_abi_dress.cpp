////////////////////////////////////////
//   模块:  read_abi_dress.cpp
//   功能:  读取衣服数据(第二部分) from artific.abi
//   作者:  jinsheng 
/////////////////////////////////////////


#include "stdafx.h"
#include "abi.h"



ctexture_data::ctexture_data(int in_tc_lim, int in_vi_lim) 
{
	tc_lim = in_tc_lim;
	vi_lim = in_vi_lim;
	texture_cord = new TextureCord [tc_lim];
	vertex_index = new short [vi_lim];
	tc_count = 0;
	vi_count = 0;


}

ctexture_data::~ctexture_data()
{
	delete [] texture_cord;
    delete [] vertex_index;
}

/* end of ctexture_data */



cdress_data::cdress_data()
{
	flag = 0;
	dress_num = 0;
	bone_num = 0;

	nd = NULL;
	vertex_num = NULL;
	faces_num = NULL;
	vertex_data = NULL;
	tri_data = NULL;
	//vb_data = NULL;
	vbw_data = NULL;
	dress_name = NULL;
	texture_data = NULL;

}
cdress_data::~cdress_data()
{
	/*
	vertex_data = new VertexCord * [dress_num];
	tri_data = new TriangleData * [dress_num];
	vb_data = new Vindex * [dress_num];
	vbw_data = new vbone_weight * [dress_num];
	dress_name = new char * [dress_num];
	*/


	delete []nd;
	delete []vertex_num;
	delete []faces_num;

	int i,j;
	for ( i = 0; i < dress_num; i++)
	{
		delete [](vertex_data[i]);
		
		for ( j= 0; j < bone_num; j++) 
		{
		   if (vbw_data[i][j].BoneWeights)
		    	delete vbw_data[i][j].BoneWeights;
		}

		delete [](vbw_data[i]);
	    delete [](tri_data[i]);
//	    delete [](vb_data[i]);
	    delete [](dress_name[i]);
	}
	delete []vertex_data;
	delete []vbw_data;
	delete []tri_data;
//	delete []vb_data;
	delete []dress_name;

	delete texture_data;

}

void cdress_data::init()
{
	Assert(bone_num >0 && dress_num > 0);
	nd = new Nodedes[bone_num];
	
	vertex_num = new int[dress_num];
	faces_num = new int[dress_num];
	vertex_data = new VertexCord * [dress_num];
	tri_data = new TriangleData * [dress_num];
//	vb_data = new Vindex * [dress_num];
	vbw_data = new vbone_weight * [dress_num];
	dress_name = new char * [dress_num];

	//--暂时不考虑动态决定空间,先分配足够大的空间, 临时 //FIXME!
	//texture_data = new ctexture_data (0xDA8A,0xDA8A);
	texture_data = new ctexture_data (0x40000,0x40000);

}
// end of cdress_data 


int CAbi::get_nvertex (int dressi)
{
	return *(m_pDress->vertex_num + dressi);
}
int CAbi::get_totaldressnum()
{
	return m_pDress->dress_num;
}
int CAbi::get_facenum (int dressi)
{
	return *(m_pDress->faces_num + dressi);
}

void CAbi::dress_release(void)
{
	SAFE_DELETE(m_pDress);

}

void CMesh_data::End()
{
	if (m_bOk)
	{
		int i;
		for ( i = 0; i < dress_num; i++)
		{
			delete [](dress_name[i]);
		}
		delete []dress_name;
		dress_num = 0;
		SAFE_DELETE(texture_data);
		m_bOk = FALSE;
		delete tri_data;
	}

}
BOOL CMesh_data::Init()
{
	Assert(dress_num > 0);
	
	dress_name = new char * [dress_num];
	//--暂时不考虑动态决定空间,先分配足够大的空间, 临时 //FIXME!
	//texture_data = new ctexture_data (0xDA8A,0xDA8A);
	texture_data = new ctexture_data (0x40000,0x40000);
	m_bOk = TRUE;
	return TRUE;

}


