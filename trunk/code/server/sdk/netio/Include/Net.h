#pragma once
#include "../../Port/config.h"
#include "NetBuffer.h"

//struct PACKET_COMMAND;

typedef void (*ConnectCallBackFunc)( SOCKET s );

class CNet
{
public:
	CNet(){};

	virtual ~CNet(){};

	virtual BOOL	Begin(int nPort){return TRUE;}
	virtual BOOL	Begin(int nPort,int nPacketPoolSize,int nConnectMax,int nRecvBuffSize,int nSendBuffSize,int nTimeout)					{return TRUE;}
	virtual BOOL	Begin(int nPort,int nPacketPoolSize,int nConnectMax,int nRecvBuffSize,int nSendBuffSize,int nTimeout, int nAcceptCount)	{return TRUE;}
	virtual void	End(){}
	
	virtual void	Accept( SOCKET sock){};
	virtual void	Break( SOCKET sock ){};
	virtual void	ShutDown( SOCKET sock ){};
//	virtual int		Send( SOCKET sock,PACKET_COMMAND* pPacket){return 0;}
	virtual int		Send( SOCKET sock, char *szBuf, int nSize ){return 0;}
	virtual int		Recv( int nThreadID,SOCKET sock,char*	buf,DWORD nSize ){return 0;}
	virtual SOCKET	Connect( const char *szIp,ULONG nPort ){return INVALID_SOCKET;}
	virtual SOCKET		ConnectAsync( const char *szIp,ULONG nPort,ConnectCallBackFunc pfn=NULL ){return INVALID_SOCKET;}
	virtual BOOL	Close( SOCKET sock ){return TRUE;}
	virtual char*	IP(SOCKET sock)
	{
#ifdef WIN32		
		return "";
#else		
		return NULL;		
#endif		
	}
	virtual	int		GetSendBufferUsage( SOCKET sock ){return 0;}
public:
//	virtual void	InitCompleteWait(){};
};


