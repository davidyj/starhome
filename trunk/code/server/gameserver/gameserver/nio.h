#include "stdafx.h"
#include "gamenet.h"

class CNIO : public CGameNet
{
public:
	CNIO();
	~CNIO();

	static CNIO* getSingle()
	{
		static CNIO io;
		return io;
	}

public:
	virtual BOOL	Begin(int nPacketPoolSize,int nListenPort,int nConnectMax,int nQueueSize,int nRecvSize,int nSendSize,int nTimeout,int nAcceptCount=0);
	virtual int		recv(SOCKET s,char* buf,int nsize);
	virtual int		send(SOCKET s,char* buf,int nsize);

	virtual void	accept(SOCKET s);

	virtual void	break(SOCKET s);
	virtual void	shutdown(SOCKET s);
};