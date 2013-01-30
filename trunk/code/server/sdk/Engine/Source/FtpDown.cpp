#include "../stdafx.h"
#if 0
#include "FtpDown.h"
#include <assert.h>


CFtpDown::CFtpDown(void)
{
	m_csTransferMode = IMAGE;
}

CFtpDown::~CFtpDown(void)
{
	CloseChannel();
}
BOOL CFtpDown::ConnectToServer( std::string csServer, UINT unPort )
{
	assert( INVALID_SOCKET == m_CtrlSock.getSock() );
	assert( csServer.length() > 0 );

	m_CtrlSock.init();

	m_bSession = m_CtrlSock.connectTo( csServer.c_str(), unPort );
	if( !m_bSession )
		return FALSE;

	int nErrorCode = GetLastError();
	TraceErrorCode( nErrorCode );

	std::string csWelcome = GetResponse();
	if( GetErrorCode() != SERVER_READY ) 
		m_bSession = FALSE;

	return m_bSession;
}
void CFtpDown::TraceErrorCode( int nErrorCode) 
{
	if (0 != nErrorCode)   
	{      
		switch( nErrorCode )      
		{
		case WSAEADDRINUSE: 
			::OutputDebugString(("\nCode Message - The specified address is already in use. \r\n") );
			break;         
		case WSAEADDRNOTAVAIL: 
			OutputDebugString(("\nCode Message - The specified address is not available from the local machine. \r\n") );            
			break;
		case WSAEAFNOSUPPORT: 
			OutputDebugString(("\nCode Message - Addresses in the specified family cannot be used with this socket. \r\n") );            
			break;
		case WSAECONNREFUSED: 
			OutputDebugString(("\nCode Message - The attempt to connect was forcefully rejected. \r\n") );            
			break;         
		case WSAEDESTADDRREQ: 
			OutputDebugString(("\nCode Message - A destination address is required. \r\n") );
			break;         
		case WSAEFAULT: 
			OutputDebugString(("\nCode Message - The lpSockAddrLen argument is incorrect. \r\n") );
			break;         
		case WSAEINVAL: 
			OutputDebugString(("\nCode Message - The socket is already bound to an address. \r\n") );            
			break;         
		case WSAEISCONN: 
			OutputDebugString(("\nCode Message - The socket is already connected. \r\n") );
			break;         
		case WSAEMFILE: 
			OutputDebugString(("\nCode Message - No more file descriptors are available. \r\n") );
			break;         
		case WSAENETUNREACH: 
			OutputDebugString(("\nCode Message - The network cannot be reached from this host at this time. \r\n") );            
			break;         
		case WSAENOBUFS: 
			OutputDebugString(("\nCode Message - No buffer space is available. The socket cannot be connected. \r\n") );            
			break;
		case WSAENOTCONN: 
			OutputDebugString(("\nCode Message - The socket is not connected. \r\n") );            
			break;
		case WSAENOTSOCK: 
			OutputDebugString(("\nCode Message - The descriptor is a file, not a socket. \r\n") );
			break;         
		case WSAETIMEDOUT: 
			OutputDebugString(("\nCode Message - The attempt to connect timed out without establishing a connection. \r\n") );            
			break;
		case WSAECONNABORTED: 
			OutputDebugString(("\nCode Message - The virtual circuit was aborted due to timeout or other failure. \r\n") );            
			break;
		default:            
			TCHAR szError[256];
			sprintf(szError, "Code Message - Connect error: %d", nErrorCode);
			OutputDebugString(szError);            
			break;      
		}
	}
	else
		OutputDebugString(("\nCode Message - Connect attempt Successful") );
}
std::string CFtpDown::GetResponse( ) 
{
	assert ( INVALID_SOCKET != m_CtrlSock.getSock() );
	assert ( m_bSession );
	if( ! m_bSession )
	{
		OutputDebugString(("\nCode Message - No Session Established"));
		return "";
	}

	std::string csResp = "";

	std::string csCompleteString = ("");

	char ch;

	BOOL bCheckMultiLine = TRUE;

	while(bCheckMultiLine)
	{
		size_t len = csResp.length();
		size_t firstPos; //= len - 2;
		if( len < 2 )
			firstPos = 0;
		else
			firstPos = len - 2;
		while( ( csResp.substr(  firstPos, 2 ) != CRLF ) )
		{
			int nRead = m_CtrlSock.recvData( &ch, 1 );
			csResp += ch;


			len = csResp.length();
			if( len < 2 )
				firstPos = 0;
			else
				firstPos = len - 2;
		}

		csCompleteString += csResp;

		if( csResp[POS_HYPHEN] == ' ' )
			bCheckMultiLine = FALSE;
		csResp = ("");
	}		

	std::string csTemp = csCompleteString.substr( 0, RES_CODE_SEGMENT );

	size_t nLen = csTemp.length();

	SetErrorCode( atoi( csTemp.c_str() ) );
	csTemp.clear();

	return m_csStatusString = csCompleteString;
}
void CFtpDown::SetErrorCode( int nErrorCode )
{
	m_nLastError = nErrorCode;
}

BOOL CFtpDown::UserLogin(std::string csUserName, std::string csPassword )
{
	std::string csCommand = "USER " + csUserName;

	BOOL bRetVal = SendCommand( csCommand );
	GetResponse();

	if( !bRetVal || GetErrorCode( ) != USER_OK )
	{
		OutputDebugString(("\nServer Message - User access not allowed. \r\n"));
		return FALSE;
	}

	csCommand = "PASS " + csPassword;

	bRetVal = SendCommand( csCommand );
	GetResponse();
	if( ! bRetVal || GetErrorCode( ) != PASS_OK )
	{
		OutputDebugString(("\nServer Message - User access not allowed. \r\n"));
		return FALSE;
	}

	OutputDebugString(("\nServer Message - User logged in. \r\n"));

	return TRUE;
}
BOOL CFtpDown::SendCommand( std::string csCommand )
{
	assert ( INVALID_SOCKET != m_CtrlSock.getSock() );

	assert( m_bSession );
	if( ! m_bSession )
	{
		OutputDebugString(("\nCode Message - No Session Established"));
		return TRUE;
	}

	if( csCommand.empty() )
		return FALSE;

	size_t len = csCommand.length();
	size_t firstPos;
	if( len < 2 )
		firstPos = 0;
	else
		firstPos = len - 2;
	if( csCommand.substr( firstPos, 2) != CRLF )
		csCommand += CRLF;

	size_t nLen = csCommand.length();

	char *pBuffer = new char[ nLen + 1 ];
	UINT nSent = 0;
	do
	{
		nSent += m_CtrlSock.sendData( csCommand._Myptr(), nLen );
		if( nSent == 0 )
		{
			if( pBuffer != NULL )
			{
				delete [] pBuffer;
				pBuffer = NULL;
			}
			return FALSE;
		}
	}while ( nSent < nLen );

	csCommand.clear();

	if( pBuffer != NULL )
	{
		delete [] pBuffer;
		pBuffer = NULL;
	}

	return TRUE;
}
BOOL CFtpDown::DisconnectFromServer()
{
	assert( INVALID_SOCKET !=  m_CtrlSock.getSock() );

	assert( m_bSession );

	if( ! m_bSession )
	{
		OutputDebugString(("\nCode Message - No Session Established"));
		return TRUE;
	}


	BOOL bRetVal = SendCommand( "QUIT" );
	GetResponse();

	if( !bRetVal || GetErrorCode( ) != SESSION_OVER )
	{
		OutputDebugString("\nServer Message - Could not disconnect session from server \r\n");
		return FALSE;
	}

	CloseChannel();

	return TRUE;
}
void CFtpDown::CloseChannel()
{
	if( INVALID_SOCKET != m_CtrlSock.getSock() )
	{
		m_CtrlSock.closeSocket();
	}
}
std::string CFtpDown::GetStatusFromServer()
{
	return m_csStatusString;
}
std::string CFtpDown::GetHELP()
{
	SendCommand( "HELP" );
	m_csHelpString = GetResponse();
	return m_csHelpString;
}
std::string	CFtpDown::GetWorkingDirectory( )
{

	return BLANK;
}
BOOL CFtpDown::SetWorkingDirectory( std::string csDirectory )
{
	assert( !csDirectory.empty() );
	if( csDirectory.empty() )
		return FALSE;

	std::string csCommand = "CWD " + csDirectory;

	BOOL bRetVal = SendCommand( csCommand );

	GetResponse();

	if( !bRetVal && GetErrorCode() != CHDIR_OK )
		return FALSE;
	return TRUE;
}
BOOL CFtpDown::ChangeWorkingDirectory( std::string csDirectory ) 
{
	return SetWorkingDirectory( csDirectory );
}

BOOL CFtpDown::MakeDirectory( std::string csDirectory )
{


	return FALSE;
}

BOOL CFtpDown::RemoveDirectory( std::string csDirectory )
{


	return FALSE;
}
BOOL CFtpDown::GetFile( std::string csRemoteFile, std::string csLocalFile, LONGLONG downloadpos )
{
	bool		bMiddle = false;

	if( 0 == downloadpos )
	{
		// 不用断点续传
		bMiddle = false;
	}
	else
	{
		// 断点续传
		bMiddle = true;
	}
	FILE * cfDataFile = NULL; // = fopen( csLocalFile.c_str(), "ab" );
	if( bMiddle )
		cfDataFile = fopen( csLocalFile.c_str(), "r+b" );
	else
		cfDataFile = fopen( csLocalFile.c_str(), "wb" );

	//cfDataFile = fopen( csLocalFile.c_str(), "ab" );


	if( NULL == cfDataFile )
	{
		if( ERROR_SHARING_VIOLATION == GetLastError() )
		{
			SetErrorCode( ERROR_OPEN_USING );
		}
		return FALSE;
	}
	if( !OpenDataChannel() )
	{
		m_DataSock.closeSocket();
		return FALSE;
	}

	// 得到文件的总长度
	LONGLONG fileLen = GetFileLength( csRemoteFile );
	// 备份文件

	if( bMiddle )
	{
		if( !SetPosision( downloadpos ) )
		{
			m_DataSock.closeSocket();
			return FALSE;
		}
	}

	std::string csCommand = "RETR " + csRemoteFile;
	BOOL bRetVal = SendCommand( csCommand );
	GetResponse();
	if( !bRetVal || GetErrorCode() != DATA_OK )
	{
		m_DataSock.closeSocket();
		return FALSE;
	}


	char szBuffer[ MAX_BUFFER ];
	LONGLONG datalen = 0;
	LONGLONG nRecvDataLen = 0;
	if( bMiddle )
	{
		nRecvDataLen = downloadpos;
	}
	else
	{
		nRecvDataLen = 0;
	}
	fseek( cfDataFile, nRecvDataLen, SEEK_SET );

	LONGLONG	nNoRecvDataLen = 0; // 没有下载的资源总数
	nNoRecvDataLen = fileLen - nRecvDataLen;

	while ( TRUE )
	{
		// 下面的语句不知道为什么
		memset( szBuffer, '\0', MAX_BUFFER );

		datalen = m_DataSock.recvData( szBuffer, MAX_BUFFER - 1 );

		if( ! datalen || datalen == SOCKET_ERROR ) 
			break; // ( EOF || network error )

		fwrite( szBuffer, datalen, 1, cfDataFile );
		fflush( cfDataFile );
		nRecvDataLen += datalen;
		OnFileProcess( csLocalFile, fileLen, nNoRecvDataLen, datalen );
	}


	m_DataSock.closeSocket();

	fclose( cfDataFile );


	GetResponse();

	if( GetErrorCode() != GET_OK )
	{
		return FALSE;
	}
	return TRUE;


}
BOOL CFtpDown::OpenDataChannel()
{
	m_DataSock.init();
	std::string csCommand = "PASV";
	BOOL bRetVal = SendCommand( csCommand );
	std::string res =  GetResponse();
	if( !bRetVal || GetErrorCode() != PASV_OK )
	{
		m_DataSock.closeSocket();
		return FALSE;
	}
	size_t pos = res.find( '(' );
	res = res.substr( pos + 1, res.length() - pos - 2 );
	int ip1,ip2,ip3,ip4,port1, port2;
	sscanf( res._Myptr(), "%d,%d,%d,%d,%d,%d", &ip1,&ip2,&ip3, &ip4,&port1,&port2 );
	char sIp[20] = {0};
	sprintf( sIp, "%d.%d.%d.%d", ip1, ip2, ip3,ip4 ) ;
	unsigned short port = port1 * 256 + port2;

	if( !m_DataSock.connectTo(  sIp, port ) )
	{
		return FALSE;
	}

	return TRUE;
}
BOOL CFtpDown::PutFile( std::string csLocalFile, std::string csRemoteFile )
{
	
	return FALSE;
}
BOOL CFtpDown::MoveFile( std::string csSourcePath, std::string csDestPath )
{
	return FALSE;
}

BOOL CFtpDown::ChangeFileAttrib( std::string csFilePath, std::string csAttrib )
{
	return FALSE;
}

BOOL CFtpDown::ChangeUser( std::string csUserName, std::string csPassword )
{
	return FALSE;
}

BOOL CFtpDown::SetTransferModeAscii( )
{
	m_csTransferMode = ASCII;
	return TRUE;
}

BOOL CFtpDown::SetTransferModeImage( )
{
	m_csTransferMode = IMAGE;
	return TRUE;
}
BOOL CFtpDown::SetPosision( LONGLONG pos )
{
	std::string csCommand;
	char buff[MAX_BUFFER];
	sprintf( buff, "REST %I64d", pos );
	// 发送文件的位置
	csCommand = buff;
	BOOL bRetVal = SendCommand( csCommand );
	GetResponse();
	if( !bRetVal || GetErrorCode() != SIZE_OK )
	{
		return FALSE;
	}
	return TRUE;
}
UINT CFtpDown::GetFileList( std::string csDirectory, std::string &csFileList )
{
	return 10;
}
int CFtpDown::GetErrorCode( )
{
	return m_nLastError;
}
LONGLONG CFtpDown::GetFileLength( std::string fileName )
{
	std::string csCommand;
	char buff[MAX_BUFFER];
	sprintf( buff, "SIZE %s", fileName.c_str() );
	// 发送文件的位置
	csCommand = buff;
	BOOL bRetVal = SendCommand( csCommand );
	std::string res = GetResponse();
	if( !bRetVal || GetErrorCode() != GET_SIZE )
	{
		return -1;
	}
	std::string sFileSize = res.substr( RES_CODE_SEGMENT + 1, res.length() );
	LONGLONG nFileSize = -1;
	sscanf( sFileSize.c_str(), "%I64d", &nFileSize );
	return nFileSize;
}

#endif