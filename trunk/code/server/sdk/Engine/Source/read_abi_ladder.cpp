////////////////////////////////////////
//   模块:  read_abi_ladder.cpp
//   功能:  读取ladder's 动画数据文件(mesh_data.txt) 
//   作者:  jinsheng 
/////////////////////////////////////////
//#include <d3dutil.h>
#include "stdafx.h"
#include "abi.h"
#include "tgaloader.h"
#include "xmlparser.h"
#include "strtools.h"
//=======================================================
// func: LDfread_abi()
// desc:  读取ladder's abi文件
//=======================================================
BOOL CAbi::LDfread_abi(const char * szName, const char * szPathID, uint * pnLength)
{

	Init();

	//CAbi *pAbi = char_carton.m_pAbi;
	set_abiname(szName);

	IXMLParser AbiXML;
	// 加载abi文件
	if( AbiXML.Load( szName, szPathID ) )
	{
		IXMLParser AbiNode = AbiXML[L"AnimData"];
		if( wcscmp( AbiNode.GetName( ), L"AnimData" ) == 0 )
		{
			
			WCHAR szWAbiName[256];
		    AbiNode.GetAttribute( L"Name", szWAbiName, 256 );
			WideCharToChar(szWAbiName, m_abi_name, 100);
			

			int nAnimCount = 0;
			McbXMLElement * pAnimNode = NULL;
			while( pAnimNode = AbiNode[nAnimCount++] )
			{
				IXMLParser AnimNode= pAnimNode;
				if( wcscmp( AnimNode.GetName( ), L"BoneTree" ) == 0 )
				{
					GetBoneTree(AnimNode, szPathID);
					continue;
				}
				if( wcscmp( AnimNode.GetName( ), L"TgaData" ) == 0 )
				{
					GetTgaData(AnimNode, szPathID);
					continue;
				}

				if( wcscmp( AnimNode.GetName( ), L"MeshData" ) == 0 )
				{
					GetMeshData(AnimNode, szPathID);
					continue;
				}

				if( wcscmp( AnimNode.GetName( ), L"CartonData" ) == 0 )
				{
					GetCartonData(AnimNode, szPathID);
					continue;
				}

				



			}
		}

	}
	return TRUE;
}
void SetMatrixFromFloat(D3DXMATRIX &mat, float* m)
{
	
	mat._11 = m[0];
	mat._12 = m[1];
	mat._13 = m[2];
	mat._14 = m[3];
			
	mat._21 = m[4];
	mat._22 = m[5];
	mat._23 = m[6];
	mat._24 = m[7];
				
	mat._31 = m[8];
	mat._32 = m[9];
	mat._33 = m[10];
	mat._34 = m[11];
				
	mat._41 = m[12];
	mat._42 = m[13];
	mat._43 = m[14];
	mat._44 = m[15];

}




//====================================================
//  func: GetBoneTree()
//  desc:  读取骨骼树，应该只读一次(ONLY ONCE)
//====================================================
void CAbi::GetBoneTree(IXMLParser &BoneTreeXml, const char * szPathID)
{
	//bone
	//---骨骼父子关系表
	ULONG bone_num = 0;
	//fscanf(fbonetree, "%d\n", &bone_num);

	bone_num = BoneTreeXml.GetChildCount();
	Assert(bone_num >0);
	nd = new Nodedes[bone_num];
	ULONG i = 0;
	McbXMLElement * pUnitNode = NULL;
	while( pUnitNode = BoneTreeXml[i] )
	{
		IXMLParser UnitNode( pUnitNode );
					
        UnitNode.GetAttribute( L"Index", nd[i].bone_index );
		UnitNode.GetAttribute( L"ParentIndex", nd[i].parent_bone);

		WCHAR szBoneName[256];
		UnitNode.GetAttribute( L"Name", szBoneName, 256 );
		WideCharToChar(szBoneName, nd[i].bone_name, 100);
	 
		nd[i].centerx = nd[i].centery = nd[i].centerz = 0.0f;//FIXME
		i++;
		
	}

	m_bonenum  = bone_num;

}

//=======================================
//   func: GetTgaData
//   desc: 读取ladder's texture (tga) == fread_bmp()
//======================================
void CAbi::GetTgaData(IXMLParser &TgaDataXml, const char * szPathID)
{
	
	
	int bmp_count = TgaDataXml.GetChildCount();
	Assert(bmp_count >0);
	Assert (bmp_count < MAX_BMP_NUM);
	bmps_init(bmp_count); 
	cbmp_data** bmps_data = m_bmps_data;

	int bmp_index = 0;
	McbXMLElement * pUnitNode = NULL;
	while( pUnitNode = TgaDataXml[bmp_index] )
	{
		int i,j;
		IXMLParser UnitNode( pUnitNode );
	/*				
        UnitNode.GetAttribute( L"Index", nd[i].bone_index );
		UnitNode.GetAttribute( L"ParentIndex", nd[i].parent_bone);

		WCHAR szBoneName[256];
		UnitNode.GetAttribute( L"Name", szBoneName, 256 );
		WideCharToChar(szBoneName, nd[i].bone_name, 100);
	*/
		int len,wid;

		//tga data
	    IRect rec_img;
	    color32 * image_data = NULL; 
				
		char tga_name[100];
		WCHAR szBmpName[256];
		UnitNode.GetAttribute( L"Name", szBmpName, 256 );
		WideCharToChar(szBmpName, tga_name, 100);

		
        //--是256色带有调色板
		char tgafile_name[100];

		sprintf(tgafile_name,"%s/%s",m_abi_name,tga_name);
		Verify(tgaloader_32(tgafile_name, szPathID, rec_img, &image_data)); 
	
		len = rec_img.m_nCX;
		wid = rec_img.m_nCY;
		
		//tmp data pointer
		char *pixel_data = new char[wid * 256]; //--bpx 921DAE(0x343C4C0)
		memset(pixel_data,0,wid*256);
		
		//tmp data
		cpalette_data *  palette_data = new cpalette_data;       //--bpx 921DB9(0x020C2030)
		
		palette_data->init(0x100,1);      //--sub_0921DDD
		//fread(palette_data->palette_rawdata,1,0x300,fbmp); //--sub_921DF0
		extern unsigned char g_ColorMap[];//FIXME
		memcpy(palette_data->palette_rawdata, g_ColorMap, 0x300);
		
		//--始终是256X256图的左上角，需要优化! FIXME!!!
		for (i = 0; i < wid; i++) {
			//fread(pixel_data + j * 0x100, 1, len, fbmp);
			for ( j = 0; j < len; j++)
			{
				pixel_data[i * 256 + j] = image_data[i * wid + j].a;// 改了,256 tga 存放 palette index
			}

			
		}
		
		//--sub_921F08 -->非类
		//--最终bmp结果包括4部分:初始、bmp's name、pixel data、palette_data
		
		//--0 
		create_bmpdata(bmp_index,len,wid);
		

		//--1 
		//--copy bmp's name
		memcpy(bmps_data[bmp_index]->bmp_name, tga_name, 0x20);
		
		//--2 
		//--copy pixel data
		bmps_data[bmp_index]->pixel_data = new char[wid * 256];
		memcpy(bmps_data[bmp_index]->pixel_data,pixel_data, wid * 256);
		
		
		//--convert 24bit palette to 16bit
		palette_data->convert24to16_tga();
		
		
		//--3 copy converted palette_data
		bmps_data[bmp_index]->palette_data = new cpalette_data(*palette_data);
		
		//delete tmp data pointer
		delete []pixel_data;
		delete palette_data;

		delete []image_data;

		bmp_index++;
	}


	

}


void CAbi::GetMeshData(IXMLParser &MeshDataXml, const char * szPathID)
{

	int i,j;
	m_pDress =  new cdress_data;
	cdress_data * dress_data = m_pDress;

	
	//ladder 's bone_num 固定 FIXME
	dress_data->bone_num = m_bonenum;

	dress_data->dress_num = MeshDataXml.GetChildCount();
	Assert(dress_data->dress_num >0);

	dress_data->init(); //c2's ctexture 包含所有dress的顶点和面的数据
	
		

	int idress = 0;
	McbXMLElement * pUnitNode = NULL;
	while( pUnitNode = MeshDataXml[idress] )
	{
		int vertex_num;
	    int face_num;

		char * dress_name = new char [0x20];
		dress_data->dress_name [idress] = dress_name;


		IXMLParser UnitNode( pUnitNode );
		WCHAR szDressName[256];
		UnitNode.GetAttribute( L"Name", szDressName, 256 );
		dress_name[0] = 0;
		WideCharToChar(szDressName, dress_name, 0x20);

		char str_filemeshname[100];
		sprintf(str_filemeshname, "./anim/%s/%s", m_abi_name, dress_name);

		FILE * file_mesh = fopen(str_filemeshname, "rt");
		Assert(file_mesh);

		fscanf(file_mesh, "%d;\n",&vertex_num);
		dress_data->vertex_num[idress] = vertex_num;

				
		// vertex data
		VertexCord *vertex_data = new VertexCord[vertex_num];
		dress_data->vertex_data[idress] = vertex_data;

		
	//	Vindex * vb_data = new Vindex[dress_data->bone_num];
	//	dress_data->vb_data [idress] = vb_data;

		// by weight
		vbone_weight * vbw_data = new vbone_weight[dress_data->bone_num];
		dress_data->vbw_data[idress] = vbw_data;

		for ( i = 0; i <vertex_num; i++)
		{
			if ( i == (vertex_num - 1))
				fscanf(file_mesh, "%f;%f;%f;;\n", &(vertex_data[i].x), &(vertex_data[i].y), &(vertex_data[i].z));
			else
				fscanf(file_mesh, "%f;%f;%f;,\n", &(vertex_data[i].x), &(vertex_data[i].y), &(vertex_data[i].z));
			
		}

		// face data
		fscanf(file_mesh, "%d;\n",&face_num);
		dress_data->faces_num[idress] = face_num;

		TriangleData *tri_data = new TriangleData[face_num];
		dress_data->tri_data[idress] = tri_data;

		// 后面需要, 因为dress_data->texture_data->vi_index 被分拆操作
		int vi_startcount = dress_data->texture_data->vi_count;
		for ( i = 0; i <face_num; i++)
		{
			
			int t0, t1,t2; 
			int tt;
			TriangleData * td = &tri_data[i];

			if (i == (face_num - 1))
				fscanf(file_mesh, "%d;%d,%d,%d;;\n", &tt, &t0, &t1, &t2);
			else
				fscanf(file_mesh, "%d;%d,%d,%d;,\n", &tt, &t0, &t1, &t2);

			//C2 好象是倒序
			dress_data->texture_data->vertex_index[dress_data->texture_data->vi_count] = t0;
			dress_data->texture_data->vertex_index[dress_data->texture_data->vi_count + 1] = t1;
			dress_data->texture_data->vertex_index[dress_data->texture_data->vi_count + 2] = t2;
			
			td->side_num = tt; //==3
			td->vi = dress_data->texture_data->vi_count;
			dress_data->texture_data->vi_count += td->side_num;
		}

		// texture's data 与 c2 有区别; 基于顶点的-->基于面的
		
		fscanf(file_mesh, "%d;\n", &vertex_num);
		TextureCord  *tex_rawdata = new TextureCord[vertex_num]; //tmp new

		//未处理的 texture data
		for ( i = 0; i < vertex_num ; i++)
		{
			float tu,tv;
			if ( i == (vertex_num - 1))
				fscanf(file_mesh, "%f;%f;;\n", &tu,&tv);
			else
				fscanf(file_mesh, "%f;%f;,\n", &tu,&tv);

			tex_rawdata[i].u = tu;
			tex_rawdata[i].v = tv;

		}

		// material list
		int nMat = 0;
		fscanf(file_mesh,"%d\n", &nMat);
		Assert(nMat > 0 && nMat < MAX_BMP_NUM );

		char matName[MAX_BMP_NUM][100];
		char matOpName[MAX_BMP_NUM][100];

		for ( i = 0; i < nMat; i++)
		{
			char matName_tmp[100];
			fscanf(file_mesh, "%s\n", matName_tmp); // 含有目录

			// 清除 matName_tmp 中的目录
			Assert(strrchr(matName_tmp, '\\'));
			strcpy(matName[i], strrchr(matName_tmp, '\\')+1);

		}

		//
		int nOpMat = 0;
		fscanf(file_mesh,"%d\n", &nOpMat);
		Assert(nOpMat >= 0 && nOpMat < MAX_BMP_NUM );
		for ( i = 0; i < nOpMat; i++)
		{
			char matOpName_tmp[100];
			fscanf(file_mesh, "%s\n", matOpName_tmp); // 含有目录

			// 清除 matName_tmp 中的目录
			Assert(strrchr(matOpName_tmp, '\\'));
			strcpy(matOpName[i], strrchr(matOpName_tmp, '\\')+1);
		}

		// material info
		fscanf(file_mesh,"%d;\n", &nMat);
		fscanf(file_mesh,"%d;\n", &face_num);
		for ( i=0; i < face_num; i++)
		{
			TriangleData * td = &tri_data[i];
			int matid;

			if (i != (face_num - 1))
			   fscanf(file_mesh,"%d,\n", &matid);
			else
			   fscanf(file_mesh,"%d;\n", &matid);

			int bmp_index = Get_bmpindex(matName[matid]);
			Assert(bmp_index != -1);
			td->palette_index = bmp_index;
			td->opacity_index = -1;
			if (nOpMat > 0) //FIXME
			{
				int op_index = Get_bmpindex(matOpName[matid]);
				td->opacity_index = op_index;
			}
		}

		// 2004.4.5 add opacity material

		// 进一步处理 texture data
		for ( i = 0; i <face_num; i++)
		{
			TriangleData * td = &tri_data[i];
			int palette_index = td->palette_index;
			int tga_len = get_bmplen(palette_index);// tga len
			for ( j = 0; j <3; j++)
			{
				int t0_v, t0;
				t0_v = 0;
				t0 = dress_data->texture_data->vertex_index[vi_startcount + 3 * i + j];
				// FIXME: 可能有问题, texture cord 基于 顶点的,不是基于面的??
				float tu,tv;
				tu = tex_rawdata[t0].u;
				tv = tex_rawdata[t0].v;

				float t_1,t_2;
				tu = tu * 256.0f * 16.0f;
				tv = tv * 256.0f * 16.0f;
				t_2  = (float)((tga_len - 1) * 16);
				t_1  = 32768.0f;
				tu = tu * t_2 + t_1;
				tv = tv * t_2 + t_1;

				dress_data->texture_data->texture_cord[dress_data->texture_data->tc_count + j].u = tu;
			    dress_data->texture_data->texture_cord[dress_data->texture_data->tc_count + j].v = tv;
			}
			td->ti = dress_data->texture_data->tc_count;
			dress_data->texture_data->tc_count += td->side_num;
		}

		delete []tex_rawdata;
		tex_rawdata = NULL;

        //bone_weight  init & 
		int bone_num = dress_data->bone_num;

		char bone_name[20];
		int bone_index;
		int vertexcount;
		int vertex_index;
		float weight;

		//int skinweight_num = 24;
		//int skinweight_num;
		//fscanf(file_mesh,"%d\n", &skinweight_num);

		// init fixme
		for ( i = 0; i < bone_num; i++)
		{
			vbw_data[i].VertexCount = 0;
			vbw_data[i].BoneWeights = NULL;
		}

		//for ( i = 0; i < skinweight_num; i++)
		do
		{
			fscanf(file_mesh,"%s\n", bone_name);
			fscanf(file_mesh,"%d;\n",&vertexcount);
			bone_index= Get_Boneindex_ofbonetree(bone_name);
			if (bone_index == -1)
			{
				Assert(0);
				continue;
			}
			vbw_data[bone_index].VertexCount = vertexcount;
			vbw_data[bone_index].BoneWeights = new _BoneWeights[vertexcount];

			for ( j = 0; j < (vertexcount - 1); j++)
			{
				fscanf(file_mesh,"%d,\n",&vertex_index);
				vbw_data[bone_index].BoneWeights[j].Index = vertex_index;

			}
			fscanf(file_mesh,"%d;\n",&vertex_index);
			vbw_data[bone_index].BoneWeights[j].Index = vertex_index;

			for ( j = 0; j < (vertexcount - 1); j++)
			{
				fscanf(file_mesh,"%f,\n",&weight);
				vbw_data[bone_index].BoneWeights[j].Weight = weight;

			}
			fscanf(file_mesh,"%f;\n",&weight);
			vbw_data[bone_index].BoneWeights[j].Weight = weight;


			//skin matrix
			float m[16];

			for ( j =0; j < 15; j++)
			{
				fscanf(file_mesh,"%f,\n",&m[j]);

			}
			fscanf(file_mesh,"%f;;\n",&m[j]);

			SetMatrixFromFloat(vbw_data[bone_index].mat_skin, m);
		
		}while(!feof(file_mesh));

		fclose(file_mesh);
		file_mesh = NULL;
		//char_carton.m_data_vbwt = vbw_table;
		idress++;
	}  // every dress

	TextureCord * tc_total = new TextureCord [dress_data->texture_data->tc_count];
	short * vi_total = new short [dress_data->texture_data->vi_count];

	memcpy(tc_total,dress_data->texture_data->texture_cord,sizeof(TextureCord) * (dress_data->texture_data->tc_count));
	memcpy(vi_total,dress_data->texture_data->vertex_index,sizeof(short) *  (dress_data->texture_data->vi_count));

	delete []dress_data->texture_data->texture_cord;
	delete []dress_data->texture_data->vertex_index;

	dress_data->texture_data->texture_cord = tc_total;
	dress_data->texture_data->vertex_index = vi_total;

	for ( idress = 0; idress < dress_data->dress_num; idress++) 
	{
		for ( j = 0; j < dress_data->faces_num [idress]; j++) 
		{
			TriangleData *tri = dress_data->tri_data[idress] + j;
			tri->texture =(tri->ti + dress_data->texture_data->texture_cord);
			tri->vertexindex = (tri->vi + dress_data->texture_data->vertex_index);
		}
	}
/*
	for (i = 0; i < dress_data->bone_num; i++) 
	{

		fread(&((dress_data->nd + i)->parent_bone), 1,4, fdress);
		fread(&((dress_data->nd + i)->centerx), 1,0x4, fdress);
		fread(&((dress_data->nd + i)->centery), 1,0x4, fdress);
		fread(&((dress_data->nd + i)->centerz), 1,0x4, fdress);

		fread(&((dress_data->nd + i)->bone_name), 1,0x20, fdress);
		fread(&((dress_data->nd + i)->unknown), 1,4, fdress);

	}
*/
	//---?? 总dress
	memcpy(dress_data->nd, nd, sizeof(Nodedes) * dress_data->bone_num);
	m_pDress = dress_data;
		
}

void CAbi::set_abiname(const char * abi_name)
{
	strcpy(m_abi_name, abi_name);
}

void fread_framematrix(FILE * file_anim, 
					   CAbi * pAbi, 
					   BoneCarton_s * bc, 
					   int max_frame, 
					   int cartonbone_num,
					   int *BoneIndexData)
{
	//read frame matrix data
	int i,j,k;
	int anim_index;
	char bone_name[20];
	int bone_index;

	
 
	for ( k = 0; k < (max_frame + 1); k++) //FIXME
	{
		fscanf(file_anim,"%d\n", &anim_index);
		for (i = 0; i < cartonbone_num; i++)
		{
			float m[16];
			fscanf(file_anim,"%s\n", bone_name);
			bone_index= pAbi->Get_Boneindex_ofbonetree(bone_name);
			Assert(bone_index >= 0);
			
			int tick;
			int matrix_size;
			
			fscanf(file_anim,"%d;%d;", &tick, &matrix_size);
			for ( j = 0; j < 15; j++)
			{
				fscanf(file_anim, "%f,", &m[j]);
			}
			fscanf(file_anim, "%f;;,\n", &m[j]);
			SetMatrixFromFloat(bc[i].mat_data[k], &m[0]);
			BoneIndexData[i] = bone_index;
		}
	}
}

int compare_time(const void * t1, const void * t2)
{
	int c1 = *((int *) t1);
	int c2 = *((int *) t2);
	if (c1 < c2)
	{
		return -1;
	}
	else if (c1 > c2)
	{
		return 1;
	}
	else
		return 0;
}

//==============================================
// func: fileopen_animdata() 
// desc: ladder 的 movelen & cirlelen 完全一样
//==============================================
//void CAbi::fileopen_animdata(FILE * fanim)
void CAbi::GetCartonData(IXMLParser &CartonDataXml, const char * szPathID)
{
	
	int i,j;

	int max_frame;
	char bone_name[20];
	int bone_index;
	//int bonenum = 25;

	m_character_data = new ccharacter_data;
	ccharacter_data * character_data = m_character_data;

	int max_bonecarton_num = 1000; //FIXME
	//--暂时不考虑动态决定空间,先分配足够大的空间, 临时 FIXME
	
	character_data->bone_data = new cbone_data(0x20000, 0x80000);// 类似 all dress's Ctexturedata
	character_data->bone_carton = new BoneCarton_s [max_bonecarton_num];



	int bonecarton_count = 1;  // 必须>=1
	int carton_num = 0;


	carton_num = CartonDataXml.GetChildCount();
	Assert(carton_num >0);
	Assert(carton_num < max_bonecarton_num);

	character_data->carton_data = new CartonData_S [carton_num];
	character_data->carton_num = carton_num;

	int iCarton = 0;
	McbXMLElement * pUnitNode = NULL;
	while( pUnitNode = CartonDataXml[iCarton] )
	{

    //read bone carton data of all carton action
	//ONLY ONE 
	// max frame 

		// carton 数据
		char carton_name[100];


		IXMLParser UnitNode( pUnitNode );
		WCHAR szCartonName[256];
		UnitNode.GetAttribute( L"Name", szCartonName, 256 );
		WideCharToChar(szCartonName, carton_name, 60);
	
		strcpy(character_data->carton_data[iCarton].carton_name, carton_name);
		


		BoneCarton_s ** bc_data =  new BoneCarton_s* [m_bonenum];////FIXME : 所有动作目前必须有同样的骨胳
		character_data->carton_data[iCarton].bc_data = bc_data;
		memset (bc_data, 0, 4 * m_bonenum);


		char str_filename[100];
		sprintf(str_filename, "./anim/%s/%s.an3", m_abi_name, carton_name);

		FILE * file_anim = fopen(str_filename, "rt");
		Assert(file_anim);

		int cartonbone_num = 0;  // == 25
		fscanf(file_anim, "%d\n", &cartonbone_num);

	
		character_data->carton_data[iCarton].bone_num = cartonbone_num;//fixme

		// bonecarton 数据

		int start_frame, end_frame;
		fscanf(file_anim, "%d\n", &start_frame);
		fscanf(file_anim, "%d\n", &end_frame);

		max_frame = end_frame - start_frame;
		//max_frame = end_frame - start_frame + 1;

		// init bonecarton data
		for ( i = 0; i <cartonbone_num ; i++)
		{
			//g_bonecarton_data[i].mat_data = new D3DXMATRIX[max_frame];
		}

		//frame matrix data
		//temp 


		BoneCarton_s * bc_tmp = &character_data->bone_carton[bonecarton_count];
		for ( i = 0; i < cartonbone_num; i++)
		{
			bc_tmp[i].mat_data = new D3DXMATRIX[max_frame+1];
		}

		int BoneIndexData[100]; //FIXME 
		memset(BoneIndexData, 0, 100 * 4);
		fread_framematrix(file_anim,this,&character_data->bone_carton[bonecarton_count],max_frame,cartonbone_num,BoneIndexData);
		

		//read pos&rot data
		for (i = 0; i < cartonbone_num; i++)
		{
			//int * com_time_list = new int[max_frame * 3 + 3]; // 排序前
			//int * time_list  = new int[max_frame + 1]; //排序后
			//int * com_time_list = new int[1000]; // 排序前
			//int * time_list  = new int[1000]; //排序后

		//	fscanf(file_anim,"%s\n", bone_name);
		//	bone_index= Get_Boneindex_ofbonetree(bone_name);
		//	Assert(bone_index >= 0);

			//ladder move_len = circle_len
			int move_len = 0; 
			int circle_len = 0;

			//bone_index = BoneIndexData[i];
			////fix bug   2004.3.5  not i ; must bone_index;
			BoneCarton_s * bc = &character_data->bone_carton[bonecarton_count + i];

//---2004.6.2 完全不支持关键帧
#if 0
			/////fix bug 2004.4.15  start_frame maybe > 0 
			int bip_time_count = 0; 
			if (bone_index == 0 && strcmp("Bip01", bone_name) == 0)  // Bip01 特殊处理
			{
				int vlen,hlen,tlen; //vertical ,horizal, turn

				//vertical
				fscanf(file_anim, "%d;\n", &vlen);
				for (j = 0;  j <vlen; j++)
				{
					fscanf(file_anim, "%d\n", &com_time_list[bip_time_count]);
					/*

					if (com_time_list[bip_time_count] < start_frame)
						com_time_list[bip_time_count] = 0;
					else
						com_time_list[bip_time_count] -= start_frame;
					*/


					bip_time_count ++;

				}

				//horizal
				fscanf(file_anim, "%d;\n", &hlen);
				for (j = 0;  j <hlen; j++)
				{
					fscanf(file_anim, "%d\n", &com_time_list[bip_time_count]);
					/*
					if (com_time_list[bip_time_count] < start_frame)
						com_time_list[bip_time_count] = 0;
					else
						com_time_list[bip_time_count] -= start_frame;
                    */

					bip_time_count ++;

				}

				//turn
				fscanf(file_anim, "%d;\n", &tlen);
				for (j = 0;  j <tlen; j++)
				{
					fscanf(file_anim, "%d\n", &com_time_list[bip_time_count]);
					/*
					if (com_time_list[bip_time_count] < start_frame)
						com_time_list[bip_time_count] = 0;
					else
						com_time_list[bip_time_count] -= start_frame;
                    */

					bip_time_count ++;

				}

			}
			else
			{
				fscanf(file_anim,"%d;\n",&bip_time_count);
				for ( j = 0; j < bip_time_count; j++)
				{
					fscanf(file_anim, "%d\n", &com_time_list[j]);
					/*
					if (com_time_list[j] < start_frame)
						com_time_list[j] = 0;
					else
						com_time_list[j] -= start_frame;
					*/
				}
			}
			// 添加首尾
			com_time_list[bip_time_count] = start_frame;
			com_time_list[bip_time_count + 1] = end_frame;
			bip_time_count += 2;

			// 排序&排除重复&限制最大帧
			Assert(bip_time_count >= 2);
			qsort(com_time_list, bip_time_count, sizeof(int), compare_time);
			j = 0;
			time_list[0] = com_time_list[0];
			move_len = 1;
			for ( j = 1; j < bip_time_count; j++)
			{

				if (com_time_list[j] != com_time_list[j-1])
				{
					time_list[move_len] = com_time_list[j];
					if (time_list[move_len] == end_frame)  
					{
						move_len++;
						break;
					}
					move_len++;
				}

			}
			delete com_time_list;

			// 清除首帧位移
			for ( j = 0; j < move_len; j++)
			{
				time_list[j] -= start_frame;

			}


#endif

			//--2004.4.15 变成每帧都是关键帧
			move_len = max_frame + 1;
			for ( j = 0; j < move_len; j++) {
				char m1 = 0;
				short m2 = 0; short m3 = 0; short m4 = 0;


				float m2_f,m3_f,m4_f;
				//fscanf(file_anim,"%d;%f,%f,%f", &m1_i, &m2_f,&m3_f,&m4_f);
#define CARTON_MOVE_SCALE  256.0f
				//m1 = time_list[j];
				m1 = j; // every frame is key frame

				m2_f = bc->mat_data[m1]._41;
				m3_f = bc->mat_data[m1]._42;
				m4_f = bc->mat_data[m1]._43;

				m2 = (short)(m2_f * CARTON_MOVE_SCALE);
				m3 = (short)(m3_f * CARTON_MOVE_SCALE);
				m4 = (short)(m4_f * CARTON_MOVE_SCALE);

				character_data->bone_data->move_i[character_data->bone_data->move_count + j] = m1;
			    character_data->bone_data->move_d[character_data->bone_data->move_count + j].x = m2;
			    character_data->bone_data->move_d[character_data->bone_data->move_count + j].y = m3;
    		    character_data->bone_data->move_d[character_data->bone_data->move_count + j].z = m4;

			}
			bc->movelen = (short)move_len;
		    bc->movei_i = character_data->bone_data->move_count;
		    bc->moved_i = character_data->bone_data->move_count;
			character_data->bone_data->move_count += move_len;
            
			
#define CARTON_CIRCLE_SCALE  32768.0f	
			//fscanf(file_anim,"%d",&circle_len);
			// ladder 简化, circle == move_len
			circle_len = move_len;

			for ( int k = 0; k < circle_len; k++) {
				int m1 = 0;
				short m2 = 0; short m3 = 0; short m4 = 0; short m5 = 0;


				float m2_f,m3_f,m4_f,m5_f;

				//m1 = time_list[k];
				m1 = k; // every frame is key frame

				D3DXMATRIX mat_tmp;
				mat_tmp = bc->mat_data[m1];


				D3DXQUATERNION quat;
				D3DXQuaternionRotationMatrix(&quat, &mat_tmp);
				m2_f = quat.x;
				m3_f = quat.y;
				m4_f = quat.z;
				m5_f = quat.w;


				m2 = (short)(m2_f * CARTON_CIRCLE_SCALE);
				m3 = (short)(m3_f * CARTON_CIRCLE_SCALE);
				m4 = (short)(m4_f * CARTON_CIRCLE_SCALE);
				m5 = (short)(m5_f * CARTON_CIRCLE_SCALE);

				character_data->bone_data->circle_i[character_data->bone_data->circle_count + k] = m1;
				character_data->bone_data->circle_d[character_data->bone_data->circle_count + k].x = m2;
				character_data->bone_data->circle_d[character_data->bone_data->circle_count + k].y = m3;
				character_data->bone_data->circle_d[character_data->bone_data->circle_count + k].z = m4;
				character_data->bone_data->circle_d[character_data->bone_data->circle_count + k].w = m5;

			}

			bc->circlelen = (short)circle_len;
			bc->circlei_i = character_data->bone_data->circle_count;
			bc->circled_i = character_data->bone_data->circle_count;

			character_data->bone_data->circle_count += circle_len;

			//delete time_list;
			//time_list = NULL;
		} // end of fread bone_carton data 


		fclose(file_anim);
		file_anim = NULL;

		for ( i = 0; i < m_bonenum; i++)
		{
			bc_data[i] = NULL;
		}
		for (i = 0; i < cartonbone_num; i++) 
		{
			//fread (&li, 1,4,fcarton);
			//fread (&gi, 1,4,fcarton);

			bone_index = BoneIndexData[i];
			//			bc_data[bone_index] = &character_data->bone_carton[i + bonecarton_count];

			bc_data[bone_index] = (BoneCarton_s *)(i + bonecarton_count);
		}


		bonecarton_count += cartonbone_num;

		//free matrix data
		for ( i = 0; i < cartonbone_num; i++)
		{
			delete []bc_tmp[i].mat_data;
		}

		iCarton++;

	}//every carton

	// 倒腾骨胳动画数据
	char * movei_total = new char [character_data->bone_data->move_count];
	MoveData_s * moved_total = new MoveData_s [character_data->bone_data->move_count];

	char * circlei_total = new char [character_data->bone_data->circle_count];
	CircleData_s * circled_total = new CircleData_s [character_data->bone_data->circle_count];

	memcpy (movei_total, character_data->bone_data->move_i, sizeof(char) * character_data->bone_data->move_count); 
	memcpy (moved_total, character_data->bone_data->move_d, sizeof(MoveData_s) * character_data->bone_data->move_count); 

	memcpy (circlei_total, character_data->bone_data->circle_i, sizeof(char) * character_data->bone_data->circle_count); 
	memcpy (circled_total, character_data->bone_data->circle_d, sizeof(CircleData_s) * character_data->bone_data->circle_count); 


	delete []character_data->bone_data->move_i;
	delete []character_data->bone_data->move_d;
	delete []character_data->bone_data->circle_i;
	delete []character_data->bone_data->circle_d;

	character_data->bone_data->move_i = movei_total;
	character_data->bone_data->move_d = moved_total;
	character_data->bone_data->circle_i = circlei_total;
	character_data->bone_data->circle_d = circled_total;

	for (i = 0; i < bonecarton_count; i++) 
	{
		(character_data->bone_carton + i)->moveindex = (character_data->bone_carton + i)->movei_i + character_data->bone_data->move_i;
		(character_data->bone_carton + i)->movedata = (character_data->bone_carton + i)->moved_i + character_data->bone_data->move_d;
		(character_data->bone_carton + i)->circleindex = (character_data->bone_carton + i)->circlei_i + character_data->bone_data->circle_i;
		(character_data->bone_carton + i)->circledata = (character_data->bone_carton + i)->circled_i + character_data->bone_data->circle_d;
	}

	// 倒腾动画数据
	BoneCarton_s* bone_carton_tmp = new BoneCarton_s [bonecarton_count];
	memcpy(bone_carton_tmp, character_data->bone_carton, sizeof(BoneCarton_s) * bonecarton_count);
	delete []character_data->bone_carton;
	character_data->bone_carton = bone_carton_tmp;

	int bonecarton_count_tmp = 0;
	for (iCarton = 0; iCarton < carton_num; iCarton++)
	{
		int bone_num = character_data->carton_data[iCarton].bone_num;
		BoneCarton_s ** bc_data =  character_data->carton_data[iCarton].bc_data;
		for ( i = 0; i < m_bonenum; i++)  
		{
			if (!bc_data[i])
				continue;
			int bone_count = *((int *)(&(bc_data[i])));
			bc_data[i] = &bone_carton_tmp[bone_count];
			
		}
		bonecarton_count_tmp += bone_num;
	}



}

//--整合abi 操作
void CAbi::End()
{
	if (m_bOk)
	{
		release_abi();
		m_pDress = NULL;
		if (nd)
		{
			delete []nd;
			nd = NULL;
		}
	}
	m_bOk = FALSE;


}
bool CAbi::Init()
{
	End();
	m_pDress = NULL; 
	m_palettes = NULL; 
	m_bmps_data = NULL;  
	m_character_data = NULL;
	nd = NULL;

	m_bOk = TRUE;
	return m_bOk;
}
void CAbi::release_abi()
{
	bmps_release();
	dress_release();
	character_release();
}
//------------------------------------------
//    CMeshAbi
//------------------------------------------
void CMeshAbi::set_abiname(const char * abi_name)
{
	strcpy(m_abi_name, abi_name);
}

void CMeshAbi::End()
{

	if (m_bOk)
	{
		release_abi();
	}
	m_bOk = FALSE;
}

BOOL CMeshAbi::Init()
{
	End();
	m_pDress = NULL;
	m_palettes = NULL; 
	m_bmps_data = NULL;  
	m_bOk = TRUE;
	m_meshanim = NULL;
	return m_bOk;
}
void CMeshAbi::release_abi()
{
	bmps_release();
	dress_release();
	meshanim_release();
}

void CMeshAbi::bmps_release()
{
	if (m_bmps_data && m_palettes)
	{
		for (int i = 0; i < m_bmp_count; i++) {
			delete m_bmps_data[i];
			delete m_palettes[i];
		}
		delete []m_palettes;
		delete []m_bmps_data;

		m_palettes = NULL;
		m_bmps_data = NULL;

	}
}

void CMeshAbi::dress_release()
{
	SAFE_DELETE(m_pDress);
	
}
void CMeshAbi::meshanim_release()
{
	SAFE_DELETE(m_meshanim);
}

BOOL CMeshAbi::LDfread_abi(const char * szName, const char * szPathID, uint * pnLength)
{

	Init();

	//CAbi *pAbi = char_carton.m_pAbi;
	set_abiname(szName);

	IXMLParser AbiXML;
	// 加载abi文件
	if( AbiXML.Load( szName, szPathID ) )
	{
		IXMLParser AbiNode = AbiXML[L"AnimData"];
		if( wcscmp( AbiNode.GetName( ), L"AnimData" ) == 0 )
		{
			
			WCHAR szWAbiName[256];
		    AbiNode.GetAttribute( L"Name", szWAbiName, 256 );
			WideCharToChar(szWAbiName, m_abi_name, 100);
			

			int nAnimCount = 0;
			McbXMLElement * pAnimNode = NULL;
			while( pAnimNode = AbiNode[nAnimCount++] )
			{
				IXMLParser AnimNode= pAnimNode;
				if( wcscmp( AnimNode.GetName( ), L"TgaData" ) == 0 )
				{
					GetTgaData(AnimNode, szPathID);
					continue;
				}

				if( wcscmp( AnimNode.GetName( ), L"MeshData" ) == 0 )
				{
					GetMeshData(AnimNode, szPathID);
					continue;
				}

				if( wcscmp( AnimNode.GetName( ), L"CartonData" ) == 0 )
				{
					GetCartonData(AnimNode, szPathID);
					continue;
				}

				



			}
		}

	}
	return TRUE;
}

void CMeshAbi::GetTgaData(IXMLParser &TgaDataXml, const char * szPathID)
{
	
	
	int bmp_count = TgaDataXml.GetChildCount();
	Assert(bmp_count >0);
	Assert (bmp_count < MAX_BMP_NUM);
	bmps_init(bmp_count); 
	cbmp_data** bmps_data = m_bmps_data;

	int bmp_index = 0;
	McbXMLElement * pUnitNode = NULL;
	while( pUnitNode = TgaDataXml[bmp_index] )
	{
		int i,j;
		IXMLParser UnitNode( pUnitNode );
	/*				
        UnitNode.GetAttribute( L"Index", nd[i].bone_index );
		UnitNode.GetAttribute( L"ParentIndex", nd[i].parent_bone);

		WCHAR szBoneName[256];
		UnitNode.GetAttribute( L"Name", szBoneName, 256 );
		WideCharToChar(szBoneName, nd[i].bone_name, 100);
	*/
		int len,wid;

		//tga data
	    IRect rec_img;
	    color32 * image_data = NULL; 
				
		char tga_name[100];
		WCHAR szBmpName[256];
		UnitNode.GetAttribute( L"Name", szBmpName, 256 );
		WideCharToChar(szBmpName, tga_name, 100);

		
        //--是256色带有调色板
		char tgafile_name[100];

		sprintf(tgafile_name,"%s/%s",m_abi_name,tga_name);
		Verify(tgaloader_32(tgafile_name, szPathID, rec_img, &image_data)); 
	
		len = rec_img.m_nCX;
		wid = rec_img.m_nCY;
		
		//tmp data pointer
		char *pixel_data = new char[wid * 256]; //--bpx 921DAE(0x343C4C0)
		memset(pixel_data,0,wid*256);
		
		//tmp data
		cpalette_data *  palette_data = new cpalette_data;       //--bpx 921DB9(0x020C2030)
		
		palette_data->init(0x100,1);      //--sub_0921DDD
		//fread(palette_data->palette_rawdata,1,0x300,fbmp); //--sub_921DF0
		extern unsigned char g_ColorMap[];//FIXME
		memcpy(palette_data->palette_rawdata, g_ColorMap, 0x300);
		
		//--始终是256X256图的左上角，需要优化! FIXME!!!
		for (i = 0; i < wid; i++) {
			//fread(pixel_data + j * 0x100, 1, len, fbmp);
			for ( j = 0; j < len; j++)
			{
				pixel_data[i * 256 + j] = image_data[i * wid + j].a;
			}

			
		}
		
		//--sub_921F08 -->非类
		//--最终bmp结果包括4部分:初始、bmp's name、pixel data、palette_data
		
		//--0 
		create_bmpdata(bmp_index,len,wid);
		

		//--1 
		//--copy bmp's name
		memcpy(bmps_data[bmp_index]->bmp_name, tga_name, 0x20);
		
		//--2 
		//--copy pixel data
		bmps_data[bmp_index]->pixel_data = new char[wid * 256];
		memcpy(bmps_data[bmp_index]->pixel_data,pixel_data, wid * 256);
		
		
		//--convert 24bit palette to 16bit
		palette_data->convert24to16_tga();
		
		
		//--3 copy converted palette_data
		bmps_data[bmp_index]->palette_data = new cpalette_data(*palette_data);
		
		//delete tmp data pointer
		delete []pixel_data;
		delete palette_data;

		delete []image_data;

		bmp_index++;
	}


	

}



void CMeshAbi::GetMeshData(IXMLParser &MeshDataXml, const char * szPathID)
{

	
	int i,j;
	m_pDress =  new CMesh_data;
	CMesh_data * dress_data = m_pDress;

	
	

	dress_data->dress_num = MeshDataXml.GetChildCount();
	Assert(dress_data->dress_num >0);

	dress_data->Init(); //c2's ctexture 包含所有dress的顶点和面的数据
	
		

	int idress = 0;
	McbXMLElement * pUnitNode = NULL;
	while( pUnitNode = MeshDataXml[idress] )
	{
		int vertex_num;
	    int face_num;

		char * dress_name = new char [0x20];
		dress_data->dress_name [idress] = dress_name;

		IXMLParser UnitNode( pUnitNode );
		WCHAR szDressName[256];
		UnitNode.GetAttribute( L"Name", szDressName, 256 );
		WideCharToChar(szDressName, dress_name, 0x20);

		char str_filemeshname[100];
		sprintf(str_filemeshname, "./anim/%s/%s", m_abi_name, dress_name);

		FILE * file_mesh = fopen(str_filemeshname, "rt");
		Assert(file_mesh);

		fscanf(file_mesh, "%d;\n",&vertex_num);
						
		m_VertexNum = vertex_num;
		// vertex data: NOT USED

		VertexCord *vertex_data = new VertexCord[vertex_num];
		for ( i = 0; i <vertex_num; i++)
		{
			if ( i == (vertex_num - 1))
				fscanf(file_mesh, "%f;%f;%f;;\n", &(vertex_data[i].x), &(vertex_data[i].y), &(vertex_data[i].z));
			else
				fscanf(file_mesh, "%f;%f;%f;,\n", &(vertex_data[i].x), &(vertex_data[i].y), &(vertex_data[i].z));
			
		}

		delete []vertex_data;

		//==========================
		// face data
		//==========================
		fscanf(file_mesh, "%d;\n",&face_num);
		m_FacesNum = face_num;

		TriangleData *tri_data = new TriangleData[face_num];
		dress_data->tri_data = tri_data;

		// 后面需要, 因为dress_data->texture_data->vi_index 被分拆操作
		int vi_startcount = dress_data->texture_data->vi_count;
		for ( i = 0; i <face_num; i++)
		{
			
			int t0, t1,t2; 
			int tt;
			TriangleData * td = &tri_data[i];

			if (i == (face_num - 1))
				fscanf(file_mesh, "%d;%d,%d,%d;;\n", &tt, &t0, &t1, &t2);
			else
				fscanf(file_mesh, "%d;%d,%d,%d;,\n", &tt, &t0, &t1, &t2);

			//C2 好象是倒序
			dress_data->texture_data->vertex_index[dress_data->texture_data->vi_count] = t0;
			dress_data->texture_data->vertex_index[dress_data->texture_data->vi_count + 1] = t1;
			dress_data->texture_data->vertex_index[dress_data->texture_data->vi_count + 2] = t2;
			
			td->side_num = tt; //==3
			td->vi = dress_data->texture_data->vi_count;
			dress_data->texture_data->vi_count += td->side_num;
		}

		// texture's data 与 c2 有区别; 基于顶点的-->基于面的
		
		fscanf(file_mesh, "%d;\n", &vertex_num);
		TextureCord  *tex_rawdata = new TextureCord[vertex_num]; //tmp new

		//未处理的 texture data
		for ( i = 0; i < vertex_num ; i++)
		{
			float tu,tv;
			if ( i == (vertex_num - 1))
				fscanf(file_mesh, "%f;%f;;\n", &tu,&tv);
			else
				fscanf(file_mesh, "%f;%f;,\n", &tu,&tv);

			tex_rawdata[i].u = tu;
			tex_rawdata[i].v = tv;

		}

		// material list
		int nMat = 0;
		fscanf(file_mesh,"%d\n", &nMat);
		Assert(nMat > 0 && nMat < MAX_BMP_NUM );

		char matName[MAX_BMP_NUM][100];
		char matOpName[MAX_BMP_NUM][100];

		for ( i = 0; i < nMat; i++)
		{
			char matName_tmp[100];
			fscanf(file_mesh, "%s\n", matName_tmp); // 含有目录

			// 清除 matName_tmp 中的目录
			Assert(strrchr(matName_tmp, '\\'));
			strcpy(matName[i], strrchr(matName_tmp, '\\')+1);

		}

		//
		int nOpMat = 0;
		fscanf(file_mesh,"%d\n", &nOpMat);
		Assert(nOpMat >= 0 && nOpMat < MAX_BMP_NUM );
		for ( i = 0; i < nOpMat; i++)
		{
			char matOpName_tmp[100];
			fscanf(file_mesh, "%s\n", matOpName_tmp); // 含有目录

			// 清除 matName_tmp 中的目录
			Assert(strrchr(matOpName_tmp, '\\'));
			strcpy(matOpName[i], strrchr(matOpName_tmp, '\\')+1);
		}

		// material info
		fscanf(file_mesh,"%d;\n", &nMat);
		fscanf(file_mesh,"%d;\n", &face_num);
		for ( i=0; i < face_num; i++)
		{
			TriangleData * td = &tri_data[i];
			int matid;

			if (i != (face_num - 1))
			   fscanf(file_mesh,"%d,\n", &matid);
			else
			   fscanf(file_mesh,"%d;\n", &matid);

			int bmp_index = Get_bmpindex(matName[matid]);
			Assert(bmp_index != -1);
			td->palette_index = bmp_index;
			td->opacity_index = -1;
			if (nOpMat > 0) //FIXME
			{
				int op_index = Get_bmpindex(matOpName[matid]);
				td->opacity_index = op_index;
			}
		}

		// 2004.4.5 add opacity material

		// 进一步处理 texture data
		for ( i = 0; i <face_num; i++)
		{
			TriangleData * td = &tri_data[i];
			int palette_index = td->palette_index;
			int tga_len = get_bmplen(palette_index);// tga len
			for ( j = 0; j <3; j++)
			{
				int t0_v, t0;
				t0_v = 0;
				t0 = dress_data->texture_data->vertex_index[vi_startcount + 3 * i + j];
				// FIXME: 可能有问题, texture cord 基于 顶点的,不是基于面的??
				float tu,tv;
				tu = tex_rawdata[t0].u;
				tv = tex_rawdata[t0].v;

				float t_1,t_2;
				tu = tu * 256.0f * 16.0f;
				tv = tv * 256.0f * 16.0f;
				t_2  = (float)((tga_len - 1) * 16);
				t_1  = 32768.0f;
				tu = tu * t_2 + t_1;
				tv = tv * t_2 + t_1;

				dress_data->texture_data->texture_cord[dress_data->texture_data->tc_count + j].u = tu;
			    dress_data->texture_data->texture_cord[dress_data->texture_data->tc_count + j].v = tv;
			}
			td->ti = dress_data->texture_data->tc_count;
			dress_data->texture_data->tc_count += td->side_num;
		}

		delete []tex_rawdata;
		tex_rawdata = NULL;

		fclose(file_mesh);
		file_mesh = NULL;
		idress++;
	}

	TextureCord * tc_total = new TextureCord [dress_data->texture_data->tc_count];
	short * vi_total = new short [dress_data->texture_data->vi_count];

	memcpy(tc_total,dress_data->texture_data->texture_cord,sizeof(TextureCord) * (dress_data->texture_data->tc_count));
	memcpy(vi_total,dress_data->texture_data->vertex_index,sizeof(short) *  (dress_data->texture_data->vi_count));

	delete []dress_data->texture_data->texture_cord;
	delete []dress_data->texture_data->vertex_index;

	dress_data->texture_data->texture_cord = tc_total;
	dress_data->texture_data->vertex_index = vi_total;

	for ( idress = 0; idress < dress_data->dress_num; idress++) 
	{
		for ( j = 0; j < m_FacesNum; j++) 
		{
			TriangleData *tri = dress_data->tri_data + j;
			tri->texture =(tri->ti + dress_data->texture_data->texture_cord);
			tri->vertexindex = (tri->vi + dress_data->texture_data->vertex_index);
		}
	}
}


void CMeshAbi::GetCartonData(IXMLParser &CartonDataXml, const char * szPathID)
{
	
	int i,j;

	int max_frame;
	
	

	m_meshanim = new CMeshAnim;
	m_meshanim->Init();
	
	
	int carton_num = 0;

	carton_num = CartonDataXml.GetChildCount();
	Assert(carton_num >0);

	m_meshanim->carton_num = carton_num;
	m_meshanim->m_CartonName = new char *[carton_num];
	
	m_meshanim->m_max_frame = new int[carton_num];

	int iCarton = 0;
	McbXMLElement * pUnitNode = NULL;
	while( pUnitNode = CartonDataXml[iCarton] )
	{

		// carton 数据
		char carton_name[100];

		IXMLParser UnitNode( pUnitNode );
		WCHAR szCartonName[256];
		UnitNode.GetAttribute( L"Name", szCartonName, 256 );
		WideCharToChar(szCartonName, carton_name, 60);
	
		m_meshanim->m_CartonName[iCarton] = new char[100];
		strcpy(m_meshanim->m_CartonName[iCarton], carton_name);
		
		char str_filename[100];
		sprintf(str_filename, "./anim/%s/%s", m_abi_name, carton_name);

		FILE * file_anim = fopen(str_filename, "rt");
		Assert(file_anim);

		//frame
		int start_frame, end_frame;
		fscanf(file_anim, "%d\n", &start_frame);
		fscanf(file_anim, "%d\n", &end_frame);

		max_frame = end_frame - start_frame;
		m_meshanim->m_max_frame[iCarton] = max_frame;

		//FIXME:
		m_meshanim->m_ppMeshAnimData = new VertexCord *[max_frame+1];

		//every frame data
		int frame_index;
		for ( i = 0; i < (max_frame + 1); i++)
		{
			m_meshanim->m_ppMeshAnimData[i] = new VertexCord[max_frame + 1];
			fscanf(file_anim, "%d\n", &frame_index);

			for ( j = 0; j < m_VertexNum; j++)
			{
				fscanf(file_anim, "%f %f %f\n",&(m_meshanim->m_ppMeshAnimData[i][j].x), 
					&(m_meshanim->m_ppMeshAnimData[i][j].y),
					&(m_meshanim->m_ppMeshAnimData[i][j].z));

			}

		}




		fclose(file_anim);
		file_anim = NULL;

		iCarton++;
	}
}