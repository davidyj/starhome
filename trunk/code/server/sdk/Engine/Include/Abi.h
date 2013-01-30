/////////////////////////////////////////
//   模块:  abi.h
//   功能:  abi动画文件的定义
//   作者:  jinsheng 
/////////////////////////////////////////
#pragma once
#include "EngineDefine.h"
#include "dbg.h"
#include "vector.h"
#include "xmlparser.h"
//#include "d3dutil.h"

//--bmp&palette
class cpalette_data {
public:
  cpalette_data();
  ~cpalette_data();
  cpalette_data(const cpalette_data&pt);

  int init(int in_count = 0x100, int in_flag = 1);  
  void convert24to16();

  void convert24to16_tga();
 // cpalette_data& operator=(const cpalette_data&);

  int flag;
  int count; 
  char * palette_rawdata;   //--0x020C3040
  USHORT * palette_data;      //--0x020C3A10 //short *-->ushort *
  char * unknown1;         //--0x020C2020
  int * unknown2;
};


class cbmp_data{
public:
	int flag;
	int flag1; //--把所有像素索引值相加和??000A64A7
	cpalette_data *  palette_data;
	char *pixel_data;
	char * opacity_data;       // new ladder
	int len,wid;
	char bmp_name[0x20+1];
	
	char *m_rawpixeldata; // my own ,3d 特有

    //--似乎还有wid&len's float 
	cbmp_data();
	cbmp_data::~cbmp_data();
    //cbmp_data(char *in_pixel_data, cpalette_data * in_palette_data, int in_len, int in_wid);
	
};

#define MAX_BMP_NUM  0xf0  //abi文件中最大的纹理图数目  


//---忠实原文
struct TextureCord
{
  float u;
  float v;
};

/*********
衣服的每一个三角形的数据集合, 与CTexture_data配合使用;前者是索引,后者是数据区
**********/
struct TriangleData
{
	union {
		short *	vertexindex;     //--3个
		int vi;
	};
	union {
		TextureCord *texture;  //--3个
		int ti;
	};
	USHORT side_num;	
	USHORT palette_index;
	short opacity_index;      //FIXME 半透
};
//-- 与 cbone_data 类似,都有count
//  准确说应该是 cface_data,与triangle_data 的区别, triangle_data 是索引;  ctexture_data 是数据区
class ctexture_data {
public:
	TextureCord * texture_cord;
	short * vertex_index;
	int tc_count;
	int vi_count;
	int tc_lim;
	int vi_lim;
	
	ctexture_data(int in_tc_lim, int in_vi_lim);
    ~ctexture_data();
};


struct Nodedes
{
 //float nd[0x34>>2];  // 前三个float 是骨骼中心点(x,y,z);->10是父节点序号
 float centerx, centery,centerz;
 int parent_bone;
 char bone_name[0x20];
 int unknown;
 int bone_index;
 
};

// 权重结构
struct _BoneWeights
{
	unsigned int Index;
	float Weight;
};


struct vbone_weight
{
 //--skin modifier 数据，每个模型对应一种
    int VertexCount;
   _BoneWeights* BoneWeights;	//vertex influenced by this bone
   D3DXMATRIX mat_skin;

};



class cdress_data {
public:
	int flag;
	int dress_num,bone_num;
	
	Nodedes * nd;   //--父子关系表
	int * vertex_num;
	int * faces_num;
	VertexCord ** vertex_data;
	TriangleData ** tri_data;
	//Vindex ** vb_data;   //--骨骼顶点对应表
	vbone_weight ** vbw_data; // --骨骼顶点权重对应表
    char ** dress_name;
	ctexture_data * texture_data;
	
	cdress_data();
	~cdress_data();
	
	void init();
	
};

class CMesh_data
{
public:
	int dress_num;

	int m_faces_num;
	TriangleData * tri_data;

	char ** dress_name;
	
	ctexture_data * texture_data;
	
private:
	bool m_bOk;
public:	
	CMesh_data(): m_bOk(false)  {}
     ~CMesh_data()                { End(); }
	BOOL Init();
    void End();

};





struct MoveData_s
{
	short x, y, z;
};


struct CircleData_s
{
	short x, y, z, w;
};


struct BoneCarton_s
{
	short          movelen;
	short          circlelen;
	union {
	    char        *moveindex;
		int        movei_i;
	};
	union {
		char         *circleindex;
		int         circlei_i;
	};
	union {
		MoveData_s   *movedata;
		int          moved_i;
	};
	union {
		CircleData_s *circledata;
		int           circled_i;
	};
	
	//D3DXMATRIX  mat_data[50];   // ladder 的 movelen & cirlelen 完全一样
	D3DXMATRIX *mat_data;   //
};

//--注意:可能会内存泄漏
class CartonData_S {
public:
	int bone_num;   //??? what bone num
	BoneCarton_s ** bc_data;
	char carton_name[0x3C];
	CartonData_S() {bone_num = 0; bc_data = NULL;};
	~CartonData_S();
};



/* 动画骨骼 */
class cbone_data {
public:
	int move_count;
	int move_lim;
	char * move_i;
	MoveData_s * move_d;
	
	int circle_count;
	int circle_lim;
	char * circle_i;
	CircleData_s * circle_d;
	
	cbone_data(int in_move_lim, int in_circle_lim);
	~cbone_data();
};



/* 角色动画数据 */
class ccharacter_data 
{
public:
	cbone_data * bone_data; 
	BoneCarton_s * bone_carton;
	CartonData_S * carton_data;
    int carton_num;
	ccharacter_data();
    ~ccharacter_data();
};

// 顶点动画数据
class CMeshAnim
{
private:
	bool m_bOk;
public:	
	CMeshAnim(): m_bOk(FALSE)  {}
     ~CMeshAnim()                { End(); }
	BOOL Init();
	void End();


    VertexCord ** m_ppMeshAnimData;  //FIXME;仅仅支持一个动画
	char ** m_CartonName;
	int *m_max_frame;
	int carton_num;
	

};

class ENGINE_CLASS CMeshAbi  
{
public:
	int m_VertexNum;
	int m_FacesNum;
	CMesh_data * m_pDress;

	cpalette_data** m_palettes;
	cbmp_data** m_bmps_data;	
	int m_bmp_count;

	CMeshAnim *  m_meshanim;

private:
	bool m_bOk;
public:	
	CMeshAbi(): m_bOk(false)  {}
     ~CMeshAbi()                { End(); }
	BOOL Init();
	void End();

	BOOL LDfread_abi(const char * szName, const char * szPathID, uint * pnLength);
	void bmps_init(int bmp_count); // defined in read_abi_bmp.cpp
	void create_bmpdata(int bmp_i, int len, int wid);
	void set_abiname(const char * abi_name);

	void GetTgaData(IXMLParser &TgaDataXml, const char * szPathID);
	void GetMeshData(IXMLParser &MeshDataXml, const char * szPathID);
	void GetCartonData(IXMLParser &CartonDataXml, const char * szPathID);



	char * get_pixel (int bmp_i);
    USHORT * get_palette (int bmp_i);
	char * get_opacity_source (int bmp_i);
	USHORT * get_opacity_palette (int bmp_i);
	

    int get_bmplen(int bmp_i);
    int Get_bmpindex(const char * bmp_str);


	void release_abi();

	char m_abi_name[100];
	void bmps_release();
	void dress_release();
	void meshanim_release();


};

class ENGINE_CLASS CAbi  
{
public:
	cdress_data*  m_pDress;  

	cpalette_data** m_palettes;
	cbmp_data** m_bmps_data;	
	int m_bmp_count;

	int m_bonenum;  // ladder 特有,所有服装共有一个bonetree
	Nodedes * nd; 

	ccharacter_data * m_character_data;
private:
	bool m_bOk;
public:	
	CAbi(): m_bOk(false)  {}
     ~CAbi()                { End(); }
	bool Init();
	void End();

	// fread data
	BOOL LDfread_abi(const char * szName, const char * szPathID, uint * pnLength);
	void bmps_init(int bmp_count); // defined in read_abi_bmp.cpp
	void create_bmpdata(int bmp_i, int len, int wid);

	//ladder
	void GetBoneTree(IXMLParser & BoneTreeXml, const char * szPathID);
	void GetTgaData(IXMLParser &TgaDataXml, const char * szPathID);
	void GetMeshData(IXMLParser &MeshDataXml, const char * szPathID);
	void GetCartonData(IXMLParser &CartonDataXml, const char * szPathID);
	
	char * get_pixel (int bmp_i);
    USHORT * get_palette (int bmp_i);
	char * get_opacity_source (int bmp_i);
	USHORT * get_opacity_palette (int bmp_i);
	

    int get_bmplen(int bmp_i);
    int Get_bmpindex(const char * bmp_str);
	int Get_Boneindex_ofbonetree(const char * bone_str);

	int get_facenum (int dress_i);
	int get_nvertex (int dressi);
	int get_totaldressnum();
	void release_abi();

	void set_abiname(const char * abi_name);
	char * GetResPath() { return m_abi_name;} 

private:
	char m_abi_name[100];
	void bmps_release();
	void character_release();
	void dress_release();
	
};

