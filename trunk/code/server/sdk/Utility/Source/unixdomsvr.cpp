#include "unixdomsvr.h"
#include <pwd.h>
#include <unistd.h>

namespace udsvr
{
int client_sockfd=0;
bool recvflag = true;
ThreadLib::ThreadID g_hThreadRecv = NULL;
bool isconn = false;
CmdFunc CmdExec = NULL;

inline bool IsConn()
{
//	printf("isconn = %s +++ \n",isconn?"true":"false");
	return isconn;
}

void ThreadRecv( void* pArguments )
{
	int ret = 0;
	fd_set fdread;
	timeval t = {1,0};
	while( recvflag )
	{
		FD_ZERO( &fdread );
		FD_SET( client_sockfd, &fdread );
		ret = select( client_sockfd+1, &fdread, NULL, NULL, &t );
		if( ret > 0 )
		{
		    char recvdata[510];
		    memset(recvdata,0,510);
		    int bytes = 0;

		    if ((bytes = read (client_sockfd, recvdata, 510)) == -1)
		    {
		    	close( client_sockfd );
		    	recvflag = false;
		    	printf( "Read Error.\n" );
		    }

		    if( bytes == 0 )
		    {
		    	isconn = false;
		    	close( client_sockfd );
		    	recvflag = false;
		    	printf( "Connection closed.\n" );
		    }
		    else
		    {
		    	switch( moniter::PACKET_COMMAND::PacketType( recvdata ) )
				{
					case moniter::CLOSESERVER:
						CmdExec( 27 );
						printf("Recv moniter::CLOSESERVER\n");
						break;
					case moniter::M_KEY_F1:		//	F1
						CmdExec( 59 );
						printf("Recv moniter::F1\n");
						break;
					case moniter::M_KEY_F2:		//	F2
						CmdExec( 60 );
						printf("Recv moniter::F2\n");
						break;
					case moniter::M_KEY_F3:		//	F3
						CmdExec( 61 );
						printf("Recv moniter::F3\n");
						break;
					case moniter::M_KEY_F4:		//	F4
						CmdExec( 62 );
						printf("Recv moniter::F4\n");
						break;
					case moniter::M_KEY_F5:		//	F5
						CmdExec( 63 );
						printf("Recv moniter::F5\n");
						break;
					case moniter::M_KEY_F6:		//	F6
						CmdExec( 64 );
						printf("Recv moniter::F6\n");
						break;
					case moniter::M_KEY_F7:		//	F7
						CmdExec( 65 );
						printf("Recv moniter::F7\n");
						break;
					case moniter::M_KEY_F8:		//	F8
						CmdExec( 66 );
						printf("Recv moniter::F8\n");
						break;
					case moniter::M_KEY_F9:		//	F9
						CmdExec( 67 );
						printf("Recv moniter::F9\n");
						break;
					case moniter::M_KEY_F10:		//	F10
						CmdExec( 68 );
						printf("Recv moniter::F10\n");
						break;
					case moniter::M_KEY_F11:		//	F11
						CmdExec( 69 );
						printf("Recv moniter::F11\n");
						break;
					case moniter::M_KEY_F12:		//	F12
						CmdExec( 70 );
						printf("Recv moniter::F12\n");
						break;
					default:
						printf("Recv ? = %s\n", recvdata);
				}
		    }
		}
	}
}

int Send( moniter::PACKET_COMMAND& pmd )
{
//	printf( "want send %d => %s\n",pmd.Size(),pmd.Data() );
	if( !IsConn() )
	{
		printf("Not connected!\n");
		return 0;
	}

	int bytes = write( client_sockfd, pmd.pParam, pmd.Size() );
//	printf( "send bytes => %d\n",bytes );

	if ( bytes == -1) {
		printf ("moniter disconnect.\n");
		recvflag = false;
		ThreadLib::WaitForFinish(g_hThreadRecv);
		isconn = false;
		close(client_sockfd);
		client_sockfd = NULL;
		return -1;
	}
	return bytes;
}

void acceptsvr( void* pArguments )
{
    std::string sspath = getpwuid(getuid())->pw_dir;
    sspath += (char*)pArguments;
//	std::string sspath = (char*)pArguments;
    printf( "acceptsvr:%s\n", sspath.c_str() );


	int server_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;      /*UNIX*/
	struct sockaddr_un client_address;
	int bytes;

	unlink( sspath.c_str() );       /*server_socket*/

	/* socket, AF_UNIX, SOCK_STREAM SOCK_DGRAM*/
	server_sockfd = socket (AF_UNIX, SOCK_STREAM, 0);
	server_address.sun_family = AF_UNIX;

	strcpy( server_address.sun_path, sspath.c_str() );
	server_len = sizeof (server_address);

	bind( server_sockfd, (struct sockaddr *)&server_address, server_len);
	listen(server_sockfd, 5);

	printf("Server is waiting for client connect...\n");

	client_len = sizeof(client_address);

	while(1)
	{
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&server_address, (socklen_t *)&client_len);
		if(client_sockfd == -1) {
			printf("client_sockfd = accept error\n");
			continue;
		}

		isconn = true;
		recvflag = true;

		g_hThreadRecv = ThreadLib::Create( ThreadRecv, NULL );

		signal(SIGPIPE,SIG_IGN);

		moniter::PACKET_COMMAND pmd;
		pmd.SetPacketType( moniter::DISPSTATE );
		pmd.SetData( "Connection Sucess!" );
		bytes = Send( pmd );

		if( bytes == -1) {
			printf("moniter disconnect.\n");
			recvflag = false;
			ThreadLib::WaitForFinish(g_hThreadRecv);
			isconn = false;
			close(client_sockfd);
			client_sockfd = NULL;
			break;
		}
		sleep(1);
	}

	if(client_sockfd)
	{
		close(client_sockfd);
	}
	unlink ( sspath.c_str() );
}

void StartMoniterServer( CmdFunc pfunc, const char* sspath )
{
	CmdExec = pfunc;
	ThreadLib::Create( acceptsvr, (void*)sspath );
}

/////////////////////////////////////////////////
namespace tomoniter
{
void SendToMoniter( int nLine, const char* pdata )
{
	if( IsConn() )
	{
		moniter::PACKET_COMMAND pmd;
		pmd.SetPacketType( moniter::DISPLINE );
		pmd.SetLine( nLine+1 );
		pmd.SetData( pdata );
		Send( pmd );
	}
}

void SendToMoniter( const char* pdata )
{
	if( IsConn() )
	{
		moniter::PACKET_COMMAND pmd;
		pmd.SetPacketType( moniter::DISPAUTO );
		pmd.SetData( pdata );
		Send( pmd );
	}
}

void SendToMoniterBanner( const char* pdata )
{
	if( IsConn() )
	{
		moniter::PACKET_COMMAND pmd;
		pmd.SetPacketType( moniter::DISPBANNER );
		pmd.SetData( pdata );
		Send( pmd );
	}
}

void SendToMoniterState( const char* pdata )
{
	if( IsConn() )
	{
		moniter::PACKET_COMMAND pmd;
		pmd.SetPacketType( moniter::DISPSTATE );
		pmd.SetData( pdata );
		Send( pmd );
	}
}

}
}
