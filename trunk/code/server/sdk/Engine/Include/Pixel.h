#pragma once

#pragma warning(disable:4201)

//#include "gfxdefine.h" // int64
#include "dbg.h"

enum PIXEL_FORMAT
{
	PF_24			=   20,
	PF_32A			=   21,		// for D3DFMT_A8R8G8B8
	PF_32			=   22,		// for D3DFMT_X8R8G8B8
	PF_16			=   23,		// for D3DFMT_R5G6B5
	PF_15			=   24,		// for D3DFMT_X1R5G5B5
	PF_15A			=   25,		// for D3DFMT_A1R5G5B5
    PF_8			=	41,		// for D3DFMT_P8

	PF_UNKNOW,
};

struct RGB24
{
	BYTE R;
	BYTE G;
	BYTE B;
	RGB24( BYTE r, BYTE g, BYTE b )
	{
		R = r;
		G = g;
		B = b;
	}
	RGB24( int nPixel )
	{
		R = BYTE( nPixel & 0xff );
		G = BYTE( ( nPixel >> 8 ) & 0xff );
		B = BYTE( ( nPixel >> 16 ) & 0xff );
	}
	RGB24()
	{
		R = G = B = 0;
	}
};

union RGB16
{
	WORD Color;
	struct {
		WORD R : 5;
		WORD G : 6;
		WORD B : 5;
	};
};

union RGB15
{
	WORD Color;
	struct {
		BYTE t : 1;
		BYTE R : 5;
		BYTE G : 5;
		BYTE B : 5;
	};
};


const int64	PF15_RMASK_64 = 0X7C007C007C007C00;
const int64	PF16_RMASK_64 = 0XF800F800F800F800;

const int64	PF15_GMASK_64 = 0X03E003E003E003E0;
const int64	PF16_GMASK_64 = 0X07E007E007E007E0;
	
const int64	PF15_BMASK_64 = 0X001F001F001F001F;
const int64	PF16_BMASK_64 = 0X001F001F001F001F;

const int64	PF15_RBMASK_64 = 0X7C1F7C1F7C1F7C1F;
const int64	PF16_RBMASK_64 = 0XF81FF81FF81FF81F;


#define		PF15_RMASK  	0x7c00
#define		PF16_RMASK		0xf800

#define		PF15_GMASK  	0x3e0
#define		PF16_GMASK		0x7e0
	
#define		PF15_BMASK  	0x1f
#define		PF16_BMASK		0x1f

//// 
#define		PF15_RBMASK		PF15_RMASK|PF15_BMASK
#define		PF16_RBMASK		PF16_RMASK|PF16_BMASK

#define		PF15_GBMASK		PF15_GMASK|PF15_BMASK
#define		PF16_GBMASK		PF16_GMASK|PF16_BMASK

#define		PF15_RGMASK		PF15_RMASK|PF15_GMASK
#define		PF16_RGMASK		PF16_RMASK|PF16_GMASK

/***************************************************************************/
inline WORD	MakePixel15BitsBy16Bits( WORD wSour )
{
		WORD wDest = 0;

		WORD wR,wG,wB;
		wB = wSour & PF16_BMASK;

		wG = wSour & PF16_GMASK;
		wG >>= 1;
		wG = wG & PF15_GMASK;
		
		wR = wSour & PF16_RMASK;
		wR >>= 1;

		wDest = wB | wG | wR;

		return wDest;
}

inline WORD	MakePixel16BitsBy15Bits( WORD wSour )
{
		WORD wDest = 0;
		
		WORD wR,wG,wB;
		wB = wSour & PF15_BMASK;

		wG = wSour & PF15_GMASK;
		wG <<= 1;
		
		wR = wSour & PF15_RMASK;
		wR <<= 1;

		wDest = wB | wG | wR;

		return wDest;

}

inline WORD	MakePixel16BitsBy15BitsSpecial( WORD wSour )
{
	WORD wDest = 0;
	
	WORD wR,wG,wB;
	wB = wSour & PF15_BMASK;
	
	wG = wSour & PF15_GMASK;
	wG <<= 1;
	wG += (0x1 << 5); // special
	
	wR = wSour & PF15_RMASK;
	wR <<= 1;
	
	wDest = wB | wG | wR;
	
	return wDest;
	
}

inline WORD	MakePixel16BitsBy15BitsEx( WORD wSour )
{
	WORD wDest = 0;
	
	WORD wR,wG,wB;
	wB = wSour & PF15_BMASK;
	
	wG = wSour & PF15_GMASK;
	wG <<= 1;
	wG	+= 0x20;
	
	wR = wSour & PF15_RMASK;
	wR <<= 1;
	
	wDest = wB | wG | wR;
	
	return wDest;
	
}

inline WORD MakePixel15BitBy24Bit( BYTE r, BYTE g, BYTE b )
{
//	WORD rr = ( r * 32 ) / 256;
//	WORD gg = ( g * 32 ) / 256;
//	WORD bb = ( b * 32 ) / 256;
	WORD rr = ( r << 5 ) >> 8;
	WORD gg = ( g << 5 ) >> 8;
	WORD bb = ( b << 5 ) >> 8;

	return bb + ( gg << 5 ) + ( rr << 10 );
}

inline WORD MakePixel15BitBy32Bit( BYTE r, BYTE g, BYTE b, BYTE a )
{
//	WORD rr = ( r * 32 ) / 256;
//	WORD gg = ( g * 32 ) / 256;
//	WORD bb = ( b * 32 ) / 256;
	WORD rr = ( r << 5 ) >> 8;
	WORD gg = ( g << 5 ) >> 8;
	WORD bb = ( b << 5 ) >> 8;

	return bb + ( gg << 5 ) + ( rr << 10 ) + ( a > 0x80 ? 0x8000 : 0 );
}

inline WORD MakePixel16BitBy24Bit( BYTE r, BYTE g, BYTE b )
{
//	WORD rr = ( r * 32 ) / 256;
//	WORD gg = ( g * 64 ) / 256;
//	WORD bb = ( b * 32 ) / 256;
	WORD rr = ( r << 5 ) >> 8;
	WORD gg = ( g << 6 ) >> 8;
	WORD bb = ( b << 5 ) >> 8;

	return bb + ( gg << 5 ) + ( rr << 11 );
}

inline int MakePixel32BitBy24Bit( int r, int g, int b )
{
	return b + ( g << 8 ) + ( r << 16 );
}

inline int MakePixel( int destPF, int sourPF, int r, int g, int b )
{
	switch( destPF )
	{
	case PF_15:
		switch( sourPF )
		{
		case PF_24: 
			return MakePixel15BitBy24Bit( (BYTE)r, (BYTE)g, (BYTE)b );
			break;  
		default:
			Assert( FALSE );
		}
		break;
	case PF_16:
		switch( sourPF )
		{
		case PF_24  : 
			return MakePixel16BitBy24Bit( (BYTE)r, (BYTE)g, (BYTE)b );
			break;  
		default:
			Assert( FALSE );
		}
		break;
	case PF_32:
		switch( sourPF )
		{
		case PF_24: 
			return MakePixel32BitBy24Bit( r, g, b );
			break;  
		default:
			Assert( FALSE );
		}
		break;
	default:
		Assert( FALSE );
	}

	return -1;
}

/***************************************************************************/
inline void Pixel15BitGetRgb( WORD * p, int& r, int& g, int& b )
{
	r = ( *p >> 10 ) & 0x1f;
	g = ( *p >>  5 ) & 0x1f;
	b = ( *p       ) & 0x1f;
}

inline void Pixel16BitGetRgb( WORD * p, int& r, int& g, int& b )
{
	r = ( *p >> 11 ) & 0x1f;
	g = ( *p >>  5 ) & 0x3f;
	b = ( *p       ) & 0x1f;
}

inline void Pixel32BitGetRgb( BYTE * p, int& r, int& g, int& b )
{
	r = p[2];
	g = p[1];
	b = p[0];
}

inline void GetPixelRgb( void * p, PIXEL_FORMAT eFormat, int& r, int& g, int& b, int& alpha )
{
	switch( eFormat )
	{
	case PF_15:
		Pixel15BitGetRgb( (WORD*)p, r, g, b );
		break;
	case PF_16:
		Pixel16BitGetRgb( (WORD*)p, r, g, b ); 
		break;
	case PF_24:
	case PF_32:
		Pixel32BitGetRgb( (BYTE*)p, r, g, b ); 
		break;
	default:
		Assert( FALSE );
	}
}

/***************************************************************************/
inline int GetPixelByte( PIXEL_FORMAT eFormat )
{
	switch( eFormat )
	{
	case PF_8:
		return 1;
	case PF_15:
	case PF_16:
		return 2;
	case PF_24:
		return 3;
	case PF_32:   
		return 4;
	default: 
		Assert( FALSE );
	}
	return 0;
}

inline int GetPixelValue( void * p, PIXEL_FORMAT eFormat )
{
	switch( eFormat )
	{
	case PF_8:
		return *(BYTE*)p;
	case PF_15:
	case PF_16:
		return *(WORD*)p;
	case PF_24:
		{
			int val = 0;
			((BYTE*)&val)[0]  = ((BYTE*)p)[0];
			((BYTE*)&val)[1]  = ((BYTE*)p)[1];
			((BYTE*)&val)[2]  = ((BYTE*)p)[2];
			return val;
		}
		break;
	case PF_32:
		return *(int*)p;
	default:
		Assert( FALSE );
	}

	return  0;
}

/***************************************************************************/
inline WORD Pixel16BitAlphaBlend( int fg, int bg, BYTE alpha )
{
	WORD    bFg = (WORD)fg & 0x1f;
	WORD    bBg = (WORD)bg & 0x1f;
	WORD    b   = (WORD)(bFg * alpha) / 255 + (WORD)(bBg * (255 - alpha)) / 255;

	WORD    gFg = (WORD)(fg >> 5) & 0x3f;
	WORD    gBg = (WORD)(bg >> 5) & 0x3f;
	WORD    g   = (WORD)(gFg * alpha) / 255 + (gBg * (255 - alpha)) / 255;

	WORD    rFg = (WORD)(fg >> 11) & 0x1f;
	WORD    rBg = (WORD)(bg >> 11) & 0x1f;
	WORD    r   = (WORD)(rFg * alpha) / 255 + (rBg * (255 - alpha)) / 255;

	return b + (g << 5) + (r << 11);
}

inline WORD Pixel15BitAlphaBlend( int fg, int bg, BYTE alpha )
{
	WORD    bFg = (WORD)fg & 0x1f;
	WORD    bBg = (WORD)bg & 0x1f;
	WORD    b   = (WORD)(bFg * alpha) / 255 + (WORD)(bBg * (255 - alpha)) / 255;

	WORD    gFg = (WORD)(fg >> 5) & 0x1f;
	WORD    gBg = (WORD)(bg >> 5) & 0x1f;
	WORD    g   = (WORD)(gFg * alpha) / 255 + (WORD)(gBg * (255 - alpha)) / 255;

	WORD    rFg = (WORD)(fg >> 10) & 0x1f;
	WORD    rBg = (WORD)(bg >> 10) & 0x1f;
	WORD    r   = (WORD)(rFg * alpha) / 255 + (WORD)(rBg * (255 - alpha)) / 255;

	return b + (g << 5) + (r << 10);
}

inline int Pixel32BitAlphaBlend( int fg, int bg, BYTE alpha )
{
	WORD    bFg = (WORD)fg & 0xff;
	WORD    bBg = (WORD)bg & 0xff;
	WORD    b   = (WORD)(bFg * alpha) / 255 + (WORD)(bBg * (255 - alpha)) / 255;

	WORD    gFg = (WORD)(fg >> 8) & 0xff;
	WORD    gBg = (WORD)(bg >> 8) & 0xff;
	WORD    g   = (WORD)(gFg * alpha) / 255 + (WORD)(gBg * (255 - alpha)) / 255;

	WORD    rFg = (WORD)(fg >> 16) & 0xff;
	WORD    rBg = (WORD)(bg >> 16) & 0xff;
	WORD    r   = (WORD)(rFg * alpha) / 255 + (WORD)(rBg * (255 - alpha)) / 255;

	return b + (g << 8) + (r << 16);
}

inline int PixelAlphaBlend( PIXEL_FORMAT ePixelFormat, int fg, int bg, BYTE alpha )
{
	int nPixel;

	switch ( ePixelFormat )
	{
	case PF_15:   
		nPixel = Pixel15BitAlphaBlend( fg, bg, alpha );
		break;
	case PF_16:   
		nPixel = Pixel16BitAlphaBlend( fg, bg, alpha );
		break;
	case PF_32:   
		nPixel = Pixel32BitAlphaBlend( fg, bg, alpha );
		break;
	default:
		Assert( FALSE );
	}

	return  nPixel;
}

/***************************************************************************/
inline int Pixel32BitBlur( int origin, int left, int right, int up, int down )
{
	int newR = ((BYTE*)(&left))[2] + ((BYTE*)(&right))[2] + ((BYTE*)(&up))[2] + ((BYTE*)(&down))[2];
	int newG = ((BYTE*)(&left))[1] + ((BYTE*)(&right))[1] + ((BYTE*)(&up))[1] + ((BYTE*)(&down))[1];
	int newB = ((BYTE*)(&left))[0] + ((BYTE*)(&right))[0] + ((BYTE*)(&up))[0] + ((BYTE*)(&down))[0];

	return MakePixel32BitBy24Bit( newR, newG, newB );
}

//---------------------------- color key define --------------------------//
// the color key in Gfx always is purple !
const DWORD COLORKEY32		= 0xFF0F;
const DWORD COLORKEY565		= 0xF81F;
const DWORD COLORKEY555		= 0x7C1F;
const DWORD COLORKEYA555	= 0xFC1F;

inline DWORD GetColorKey( PIXEL_FORMAT ePixelFormat )
{
	switch( ePixelFormat )
	{
	case PF_32:
	case PF_32A:
		return COLORKEY32;
	case PF_16:
		return COLORKEY565;
	case PF_15:
		return COLORKEY555;
	case PF_15A:
		return COLORKEYA555;
	case PF_UNKNOW:
	default:
		return 0;
	}
}

#define RGBA(r,g,b,a)    ((DWORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))
#define ARGB(a,r,g,b)    RGBA(r,g,b,a)
