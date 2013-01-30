////////////////////////////////////////
//   模块:  read_abi_bmp.cpp
//   功能:  动画数据读取的第一部分(bmp) from artific.abi
//   作者:  jinsheng 
/////////////////////////////////////////

#include "stdafx.h"
#include "abi.h"

cpalette_data::cpalette_data(const cpalette_data&pt)
{
	flag = 0;
	count = 0;
    palette_rawdata = new char[pt.count * 3];
	Assert(pt.flag == 1);
    palette_data = new USHORT[pt.count * pt.flag ];
	unknown1 = NULL;
	
	memcpy(palette_rawdata,pt.palette_rawdata,pt.count * 3);
	memcpy(palette_data,pt.palette_data,pt.count * pt.flag * sizeof(USHORT));
}

cpalette_data::cpalette_data()
{
	flag = 0;
	count = 0;
	palette_rawdata = NULL;
	palette_data = NULL;
	unknown1 = NULL;
}


cpalette_data::~cpalette_data()
{
    delete []palette_rawdata;
	delete []palette_data;
	if (unknown1)
	  delete []unknown1;
		
}

int cpalette_data::init( int in_count,int in_flag )
{
  if (in_count == 0)
	  return 1;
  palette_rawdata = new char[in_count * 3]; //24 bit 色

  Assert(palette_rawdata);
  if (palette_rawdata == NULL)
	  return 1;

  Assert(in_flag == 1);
  palette_data = new USHORT[in_count * in_flag];
  unknown1 = new char[in_flag * 4];

  count = in_count;
  flag = in_flag;
// unknown2 = &s_B58DF0;

  memset (palette_rawdata, 0, in_count * 3);
  memset (palette_data, 0, in_count * sizeof(USHORT));
  memset (unknown1, 0, in_flag * 4);

  return 0;
  
}
void cpalette_data::convert24to16_tga()
{
	unsigned short pixel = 0;
	unsigned short red,green,blue;
	
	for (int i = 0; i < 256; i++) {
		red = green = blue = 0;
		pixel = 0;
		red = (unsigned short)palette_rawdata[i*3+0] &0x00ff; //--小技巧
		green= (unsigned short)palette_rawdata[i*3+1]&0x00ff;
		blue = (unsigned short)palette_rawdata[i*3+2]&0x00ff;

		red = red >> 3;
		red = red << 0;

		green = green >> 2;
		green = green << 5;

		blue = blue >> 3;
		blue = blue << 0xB;

		pixel = red|green|blue;

		*(palette_data + i) = pixel;

	}
}

void cpalette_data::convert24to16()
{
	unsigned short pixel = 0;
	unsigned short red,green,blue;
	
	for (int i = 0; i < 256; i++) {
		red = green = blue = 0;
		pixel = 0;
		blue = (unsigned short)palette_rawdata[i*3+2] &0x00ff; //--小技巧
		green= (unsigned short)palette_rawdata[i*3+1]&0x00ff;
		red = (unsigned short)palette_rawdata[i*3]&0x00ff;

		blue = blue >> 3;
		blue = blue << 0;

		green = green >> 2;
		green = green << 5;

		red = red >> 3;
		red = red << 0xB;

		pixel = red|green|blue;

		*(palette_data + i) = pixel;

	}
}

/*****************bmp data of class ***********/

cbmp_data::cbmp_data()
{
	palette_data = NULL;
	pixel_data = NULL;
	m_rawpixeldata = NULL;
	bmp_name[0x20] = 0;

}

cbmp_data::~cbmp_data()
{
	delete palette_data;
	delete []pixel_data;
}

/*  自定义数据 */


void CAbi::create_bmpdata(int bmp_i, int len, int wid)
{ 
	Assert(bmp_i < m_bmp_count);

	m_bmps_data[bmp_i] = new cbmp_data;
	m_palettes [bmp_i] = new cpalette_data;

	m_bmps_data[bmp_i]->len = len;
	m_bmps_data[bmp_i]->wid = wid;
	m_bmps_data[bmp_i]->palette_data = m_palettes[bmp_i];
}

void CAbi::bmps_init(int bmp_count)
{
	 m_bmp_count = bmp_count;
	 m_palettes = new cpalette_data *[m_bmp_count];
	 m_bmps_data = new cbmp_data*[m_bmp_count];	

	 for (int i = 0; i < m_bmp_count; i++) {
		 m_bmps_data[i] = NULL;
		 m_palettes[i] = NULL;
	 }

}

void CAbi::bmps_release()
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


char * CAbi::get_pixel (int bmp_i)
{
   return m_bmps_data[bmp_i]->pixel_data ;
	
}
USHORT * CAbi::get_palette (int bmp_i)
{

   return m_bmps_data[bmp_i]->palette_data->palette_data ;

}
char * CAbi::get_opacity_source (int bmp_i)
{
	if (bmp_i < 0)
	{
		return NULL;
	}
	else
	{
	   return m_bmps_data[bmp_i]->pixel_data;
	}
}

USHORT * CAbi::get_opacity_palette (int bmp_i)
{
	if (bmp_i < 0)
	{
		return NULL;
	}
	else
	{
       return m_bmps_data[bmp_i]->palette_data->palette_data ;
	}

}


int CAbi::get_bmplen (int bmp_i)
{
	
	return m_bmps_data[bmp_i]->len;
}

//==================================================
//  func: Get_bmpindex()
//  desc: 根据 bmp's name 获得 bmp index
//        error: -1
//==================================================
int CAbi::Get_bmpindex(const char * bmp_str)
{
	cbmp_data  ** bmp_data = m_bmps_data;
	int bmpi = 0;
	char * bmp_strtmp = NULL;
	while(1)
	{
		bmp_strtmp = bmp_data[bmpi]->bmp_name;
		if (stricmp(bmp_strtmp, bmp_str) == 0)
			break;
		
		if (bmpi >= (m_bmp_count - 1))
		{
			bmpi = -1;
			break;
		}
		bmpi++;
		
	}
	
	return bmpi;

}
//===============================================
//CMeshAbi
//===============================================



char * CMeshAbi::get_pixel (int bmp_i)
{
   return m_bmps_data[bmp_i]->pixel_data ;
	
}
USHORT * CMeshAbi::get_palette (int bmp_i)
{

   return m_bmps_data[bmp_i]->palette_data->palette_data ;

}
char * CMeshAbi::get_opacity_source (int bmp_i)
{
	if (bmp_i < 0)
	{
		return NULL;
	}
	else
	{
	   return m_bmps_data[bmp_i]->pixel_data;
	}
}

USHORT * CMeshAbi::get_opacity_palette (int bmp_i)
{
	if (bmp_i < 0)
	{
		return NULL;
	}
	else
	{
       return m_bmps_data[bmp_i]->palette_data->palette_data ;
	}

}


int CMeshAbi::get_bmplen (int bmp_i)
{
	
	return m_bmps_data[bmp_i]->len;
}

//==================================================
//  func: Get_bmpindex()
//  desc: 根据 bmp's name 获得 bmp index
//        error: -1
//==================================================
int CMeshAbi::Get_bmpindex(const char * bmp_str)
{
	cbmp_data  ** bmp_data = m_bmps_data;
	int bmpi = 0;
	char * bmp_strtmp = NULL;
	while(1)
	{
		bmp_strtmp = bmp_data[bmpi]->bmp_name;
		if (stricmp(bmp_strtmp, bmp_str) == 0)
			break;
		
		if (bmpi >= (m_bmp_count - 1))
		{
			bmpi = -1;
			break;
		}
		bmpi++;
		
	}
	
	return bmpi;

}








void CMeshAbi::create_bmpdata(int bmp_i, int len, int wid)
{ 
		Assert(bmp_i < m_bmp_count);

	m_bmps_data[bmp_i] = new cbmp_data;
	m_palettes [bmp_i] = new cpalette_data;

	m_bmps_data[bmp_i]->len = len;
	m_bmps_data[bmp_i]->wid = wid;
	m_bmps_data[bmp_i]->palette_data = m_palettes[bmp_i];

}


void CMeshAbi::bmps_init(int bmp_count)
{
		 m_bmp_count = bmp_count;
	 m_palettes = new cpalette_data *[m_bmp_count];
	 m_bmps_data = new cbmp_data*[m_bmp_count];	

	 for (int i = 0; i < m_bmp_count; i++) {
		 m_bmps_data[i] = NULL;
		 m_palettes[i] = NULL;
	 }

}




