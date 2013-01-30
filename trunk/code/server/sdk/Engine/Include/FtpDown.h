#pragma once
#if 0
#include <string>

#include "./FtpSocket.h"

#define		RES_CODE_SEGMENT	3
#define		SERVER_READY		220
#define		USER_OK				331
#define		PASS_OK				230
#define		DIR_OK				257
#define		CHDIR_OK			250
#define		DELDIR_OK			250
#define		MOVE_OK				350
#define		PORT_OK				200
#define		DATA_OK				150
#define		PASV_OK				227
#define		GET_OK				226
#define		SIZE_OK				350
#define		SESSION_OVER		221
#define		GET_SIZE			213

//#define		MOVE_DONE		350


#define		POS_HYPHEN		3
#define		CRLF			"\r\n"
#define		DIR_SEPERATOR	"/"
#define		BLANK			""
#define		MAX_BUFFER		256
#define		ZERO			0

#define		ASCII			"A"
#define		IMAGE			"I"

#define		ERR_SOCK_LOOKUP		5000
#define		ERR_SOCK_CREATE		5001
#define		ERR_SOCK_LISTEN		5002
#define		ERR_SOCK_PORT		5003
#define		ERR_SOCK_ACCEPT		5004
#define		ERR_SOCK_LOCFILE	5004

// 打开正在使用的文件
#define			ERROR_OPEN_USING	5005

class CFtpDown
{
public:
	CFtpDown(void);
	~CFtpDown(void);

	BOOL	ConnectToServer( std::string csServer, UINT unPort );

	BOOL	UserLogin(std::string csUserName, std::string csPassword ) ;


	BOOL	DisconnectFromServer();

	std::string GetStatusFromServer();

	/*
		fileLen 文件的长度，nDownLoads 还没有接受完的数据, curData 本次下载到的数据
	*/
	virtual void OnFileProcess( std::string sLocalFile, LONGLONG fileLen, LONGLONG nDownLoads, LONGLONG curData ){};


public:
	std::string GetHELP();
	std::string	GetWorkingDirectory( );
	BOOL	SetWorkingDirectory( std::string csDirectory ) ;

	BOOL	ChangeWorkingDirectory( std::string csDirectory ) ;

	BOOL	MakeDirectory( std::string csDirectory ) ;

	BOOL	RemoveDirectory( std::string csDirectory );


	// 文件内断点序传 downloadpos
	BOOL	GetFile( std::string csRemoteFile, std::string csLocalFile, LONGLONG downloadpos = 0 ) ;


	BOOL	PutFile( std::string csLocalFile, std::string csRemoteFile ) ;

	BOOL	MoveFile( std::string csSourcePath, std::string csDestPath ) ;

	BOOL	ChangeFileAttrib( std::string csFilePath, std::string csAttrib ) ;


	BOOL	ChangeUser( std::string csUserName, std::string csPassword ) ;


	BOOL	SetTransferModeAscii( ) ;


	BOOL	SetTransferModeImage( ) ;

	BOOL	SetPosision( LONGLONG pos );



	UINT	GetFileList( std::string csDirectory, std::string &csFileList ) ;

	LONGLONG GetFileLength( std::string fileName );


	int		GetErrorCode( ) ;


public:

	void	CloseChannel();
	BOOL	SendCommand( std::string csCommand ) ;


	std::string		GetResponse( ) ;

	void	SetErrorCode( int nErrorCode ) ;




	void	TraceErrorCode( int nErrorCode) ;

	BOOL AssertFailure();

private:

	std::string m_csStatusString;

	BOOL OpenDataChannel();


	std::string m_FileList;


	std::string m_csTransferMode;


	CFtpSocket		m_CtrlSock;


	std::string		m_csHost;


	BOOL		m_bSession;

	int			m_nLastError;

	std::string		m_csHelpString;

	CFtpSocket		m_DataSock;

};

#endif