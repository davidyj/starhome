#pragma once
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

class CFtpSocket
{
public:
	CFtpSocket(void);
	~CFtpSocket(void);

	bool init();
	void uninit();

	void setSock( SOCKET sock )
	{
		m_Sock = sock;
	}
	SOCKET getSock(){
		return m_Sock;
	};

	bool create( unsigned short port, char* ip = "" );
	bool connectTo( const char* serverAddr, int serverPort );
	bool acceptSock( CFtpSocket& ftpSocket );

	int recvData( char* data, int len );
	int sendData( char* data, int len );

	void closeSocket();

	char* getIp()
	{
		return inet_ntoa( ( (sockaddr_in*)&m_InternetAddr)->sin_addr);
	}
	unsigned short getPort()
	{
		return ntohs( ( (sockaddr_in*)&m_InternetAddr)->sin_port );
	}
	void setInternetAddr( SOCKADDR_IN* addr )
	{
		memcpy( &m_InternetAddr, addr, sizeof(SOCKADDR_IN) );
	}

	std::string getSelfIp();

private:
	SOCKET m_Sock;
	SOCKADDR_IN		m_InternetAddr;

	// 控制注册的网络数量
	static int m_count;
};
