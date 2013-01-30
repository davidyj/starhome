#ifndef UNIXDOM_PACKAGE
#define UNIXDOM_PACKAGE

#include <string.h>
//#include "CommDef.h"

namespace moniter
{

#define PACKET_BUFFER_SIZE (1024-sizeof(int))

#define WORD  unsigned short
typedef unsigned char BYTE;

enum PACKET_TYPE
{
//	PACKET_TYPE_COMMAND_REGISTER_SERVER				= 1,				//

//	server ->	client
	DISPBANNER		=	20,
	DISPLINE,
	DISPAUTO,
	DISPSTATE,

//	client	->	server
	VIEWREFRESH,
	VIEWFRAME,
	VIEWSTATA,
	CLOSESERVER,

//	Fn
	M_KEY_F0		=	58,
	M_KEY_F1,
	M_KEY_F2,
	M_KEY_F3,
	M_KEY_F4,
	M_KEY_F5,
	M_KEY_F6,
	M_KEY_F7,
	M_KEY_F8,
	M_KEY_F9,
	M_KEY_F10,
	M_KEY_F11,
	M_KEY_F12,


	INVALID_TYPE
};

struct PACKET_COMMAND
{
private:

	static const BYTE HEAD_PSIZE = 0;
	static const BYTE HEAD_TYPE  = 2;
	static const BYTE HEAD_LINE	 = 4;		//
	static const BYTE DATA_PARAM = 6;

	inline static WORD	HeadSize()			{ return DATA_PARAM - HEAD_PSIZE;}
	inline void			SetSize(WORD wSize) { *(WORD*)(pParam + HEAD_PSIZE) = wSize;}

public:

	BYTE pParam[PACKET_BUFFER_SIZE];

	PACKET_COMMAND( )
	{
		Init();
	}

	inline void	Init()
	{
		memset( pParam, 0, PACKET_BUFFER_SIZE );
		SetSize( HeadSize() );
		SetLine(0xFFFF);
		SetPacketType(0xFFFF);
	}

	inline WORD			Size()				{ return *(WORD*)(pParam + HEAD_PSIZE);	}
	inline int			DataSize( )			{ return Size() - HeadSize(); }
	inline BYTE*		Data()				{ return pParam + DATA_PARAM;}
	inline WORD			PacketType()		{ return *(WORD*)(pParam + HEAD_TYPE); }
	inline WORD			PacketLine()		{ return *(WORD*)(pParam + HEAD_LINE); }

	inline static WORD		Size( char* pData )				{ return *(WORD*)(pData + HEAD_PSIZE);	}
	inline static char*		Data( char* pData )				{ return pData + DATA_PARAM;}
	inline static WORD		PacketType( char* pData )		{ return *(WORD*)(pData + HEAD_TYPE); }
	inline static WORD		PacketLine( char* pData )		{ return *(WORD*)(pData + HEAD_LINE); }

	inline void			SetLine(WORD wLine) { *(WORD*)(pParam + HEAD_LINE) = wLine;}
	inline void			SetPacketType(WORD wType)		{*(WORD*)(pParam + HEAD_TYPE) = wType;}

	void	SetData( const char* pData )
	{
		WORD nSize = strlen(pData);
		if( nSize > PACKET_BUFFER_SIZE-DATA_PARAM )
		{
			printf( "override...\n" );
			SetSize( HeadSize() );
			return;
		}
		memcpy( (void*)(pParam + DATA_PARAM), (void*)pData, nSize );
		SetSize( nSize + HeadSize() );
	}

	void ReplaceCtlToBlank( char* buffer, unsigned int length)
	{
		if (PACKET_BUFFER_SIZE < length)
			return ;

		memcpy( (void*)pParam, (void*)buffer, length );

		for( unsigned int i=HeadSize(); i<length-1; i++ )
		{
			if( buffer[i] < 0x20 && buffer[i] != '\0' )
			{
				pParam[i] = ' ';
			}
		}
	}

};

}

#endif
