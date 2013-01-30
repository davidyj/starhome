#ifndef UNIXDOMSVR
#define UNIXDOMSVR

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <signal.h> // raise
#include <string>

#include "ThreadLib.h"
#include "package.h"
//#include "platform.h"

namespace udsvr
{

extern int client_sockfd;
extern bool recvflag;
extern ThreadLib::ThreadID g_hThreadRecv;
extern bool isconn;

typedef void (*CmdFunc)(char);
extern CmdFunc CmdExec;

bool IsConn();
void StartMoniterServer( CmdFunc pfunc, const char* sspath );

/////////////////////////////////////////////////
namespace tomoniter
{
	void SendToMoniter( int nLine, const char* pdata );
	void SendToMoniter( const char* pdata );
	void SendToMoniterBanner( const char* pdata );
	void SendToMoniterState( const char* pdata );
}

}
#endif
