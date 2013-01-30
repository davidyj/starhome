#include "../stdafx.h"
#include "FtpSocket.h"
#include <assert.h>

static char CS_TITLE[20] = "error";
int CFtpSocket::m_count = 0;

CFtpSocket::CFtpSocket(void)
{
	memset( &m_InternetAddr, 0, sizeof(SOCKADDR_IN) );
	m_Sock = INVALID_SOCKET;
}

CFtpSocket::~CFtpSocket(void)
{
	uninit();
}

bool CFtpSocket::init()
{
	memset( &m_InternetAddr, 0, sizeof(SOCKADDR_IN) );
	if( INVALID_SOCKET != m_Sock  )
	{
		closesocket( m_Sock );
		m_Sock = INVALID_SOCKET;
	}

	// ��ʼ��WINSOCK
	if( 0 == m_count )
	{

		WSADATA wsaData;
		int err;
		err = WSAStartup( MAKEWORD(2,2), &wsaData );
		if( err != 0 )
		{
			/* Tell the user that we could not find a usable */
			/* WinSock DLL.                                  */
			MessageBox( NULL, ("�Բ����Ҳ������õ�WinSock DLL��"),
				CS_TITLE, MB_OK );
			return false;
		}

		/* Confirm that the WinSock DLL supports 2.2.*/
		/* Note that if the DLL supports versions greater    */
		/* than 2.2 in addition to 2.2, it will still return */
		/* 2.2 in wVersion since that is the version we      */
		/* requested.                                        */
		if ( LOBYTE( wsaData.wVersion ) != 2 ||
			HIBYTE( wsaData.wVersion ) != 2 ) 
		{
			/* Tell the user that we could not find a usable */
			/* WinSock DLL.                                  */
			MessageBox( NULL, ("�Բ����Ҳ������õ�WinSock DLL��"),
				CS_TITLE, MB_OK );
			WSACleanup();
			return false; 
		}
	}
	return true;
}
void CFtpSocket::uninit()
{
	if( INVALID_SOCKET != m_Sock )
	{
		closesocket( m_Sock );
		m_Sock = INVALID_SOCKET;
	}
	--m_count;
	if( 0 == m_count )
		WSACleanup();
}

bool CFtpSocket::create( unsigned short port, char* ip )
{
	assert( m_Sock == INVALID_SOCKET );
	// �����׽���
	m_Sock = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP,
		NULL, 0, WSA_FLAG_OVERLAPPED );
	if( INVALID_SOCKET == m_Sock )
	{
		//CLogger::getInst()<<_T("���������˿�ʧ�ܣ�����ţ�")
		//	<< WSAGetLastError()<<_T("\n");
		uninit();
		return false;
	}

	m_InternetAddr.sin_family	= AF_INET;
	m_InternetAddr.sin_port		= htons( port );
	if( (ip != NULL) && (ip[0] != 0 )  )
		m_InternetAddr.sin_addr.s_addr	= inet_addr( ip );
	else
		m_InternetAddr.sin_addr.s_addr	= htonl( INADDR_ANY );

	// �󶨶˿�

	int ret;
	ret = bind( m_Sock, (const sockaddr*)&m_InternetAddr, sizeof( m_InternetAddr ) );
	if( SOCKET_ERROR == ret )
	{
		//CLogger::getInst()<<_T("�������˿�ʧ�ܣ�����ţ�")
		//	<< WSAGetLastError()<<_T(" \n");
		uninit();
		return false;
	}

	int opt = 1;
	setsockopt( m_Sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(int) );
	// ��ʼ����
	ret = listen( m_Sock, 5 );
	if( SOCKET_ERROR == ret )
	{
		//CLogger::getInst()<<_T("�����˿�ʧ�ܣ�����ţ�")
		//	<< WSAGetLastError()<<_T(" \n");
		uninit();
		return false;
	}
	return true;
}
bool CFtpSocket::connectTo( const char* serverAddr, int serverPort )
{
	assert( m_Sock == INVALID_SOCKET );

	m_Sock = WSASocket( AF_INET, SOCK_STREAM, IPPROTO_TCP,
		NULL, 0, WSA_FLAG_OVERLAPPED );
	if( INVALID_SOCKET == m_Sock )
	{
		//CLogger::getInst()<<_T("���������˿�ʧ�ܣ�����ţ�")
		//	<< WSAGetLastError()<<_T("\n");
		uninit();
		return false;
	}

	memset( &m_InternetAddr, 0, sizeof( sockaddr_in ) );

	m_InternetAddr.sin_family			= AF_INET;
	m_InternetAddr.sin_addr.s_addr	= inet_addr( serverAddr );
	m_InternetAddr.sin_port			= htons( serverPort );

	//CLogger::getInst()<<_T("���ӷ�����...\n");

	if( m_InternetAddr.sin_addr.s_addr == INADDR_NONE )
	{
		//CLogger::getInst()<<_T("����DNS����...\n");
		LPHOSTENT lpHostent = gethostbyname( serverAddr );
		if( NULL == lpHostent )
		{
			//CLogger::getInst()<<_T("�޷�������������ַ��")<< "�����:" << WSAGetLastError() << "\n";
			return false;
		}
		else
		{
			m_InternetAddr.sin_addr.s_addr = ((in_addr*)lpHostent->h_addr)->s_addr;
			//char* IP = inet_ntoa(*((in_addr*)lpHostent->h_addr));
			//CLogger::getInst()<<_T("���������")<<IP<<std::endl;
		}

	}

	int err;
	err = connect( m_Sock, (const sockaddr*)&m_InternetAddr,
		sizeof(sockaddr_in) );
	if( SOCKET_ERROR == err )
	{
		//CLogger::getInst()<<_T("�޷����ӵ���������")<< "�����:" << WSAGetLastError() << "\n";
		//int nn = WSAGetLastError();
		return false;
	}

	//CLogger::getInst()<<_T("���ӷ�������[")<<serverAddr<<_T(":")\
	//	<<serverPort<<_T("]�ɹ���\n");

	return true;
}

bool CFtpSocket::acceptSock( CFtpSocket& ftpSocket )
{
	SOCKADDR_IN		Address;
	int				nLen = sizeof( SOCKADDR_IN );
	SOCKET clientSock = WSAAccept( m_Sock, (sockaddr*)&Address, &nLen, NULL, 0 );
	if( INVALID_SOCKET == clientSock )
		return false;
	ftpSocket.setSock( clientSock );
	ftpSocket.setInternetAddr( (SOCKADDR_IN*)&Address );
	return true;
}

int CFtpSocket::recvData( char* data, int len )
{
	return recv( m_Sock, data, len, 0 );
}

int CFtpSocket::sendData( char* data, int len )
{
	return send( m_Sock, data, len, 0 );
}

void CFtpSocket::closeSocket()
{
	if( INVALID_SOCKET != m_Sock )
	{
		closesocket( m_Sock );
		m_Sock = INVALID_SOCKET;
	}
	uninit();
}

std::string CFtpSocket::getSelfIp()
{
	char name[100];
	if(  SOCKET_ERROR == ::gethostname( name, 100 ) )
		return "";

	LPHOSTENT lpHostent = gethostbyname( name );

	if( NULL == lpHostent )
	{
		return "";
	}
	else
	{
		m_InternetAddr.sin_addr.s_addr = ((in_addr*)lpHostent->h_addr)->s_addr;
		char* IP = inet_ntoa(*((in_addr*)lpHostent->h_addr));
		return IP;
	}

}
