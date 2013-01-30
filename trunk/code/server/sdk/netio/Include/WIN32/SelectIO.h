#ifndef IMPL_SELECT_IO_H
#define IMPL_SELECT_IO_H

#include "config.h"
#include "GLock.h"
#include "SocketHashTable.h"
#include "NetBuffer.h"
#include "Net.h"

class CGameNet;

class IOKEY
{
public:
	IOKEY(){}
	~IOKEY(){}

	//���ƹ��캯��,��������ռ�
	// nRecvBufSize : �������ݻ�������С
	// nSendBufSize	: ������Ϣ���ڴ��С	
	inline void Construct(int nRecvBufSize,int nSendBufSize,int nTimeout)
	{
		m_RecvBuff = (char*)Plat_Alloc(nRecvBufSize);
		m_WriteBufferQueue.Create(nSendBufSize,nTimeout);	

		m_bClosed		= false;
		m_bFree			= true;
		m_sock			= INVALID_SOCKET;
		m_nRecvBufSize	= nRecvBufSize;
		m_nSendBufSize	= nSendBufSize;
		m_IP[0]			='\0';		
		m_Port			= 0;
	}

	inline void Release()
	{
		m_bFree		= true;
		m_bClosed	= false;
		m_sock		= INVALID_SOCKET;
		m_IP[0]		= '\0';
		m_Port			= 0;

		m_WriteBufferQueue.Release();
	}

	inline void SetPort(ULONG port)			{ m_Port=port; }
	inline void SetIP(const char* szIP)		{ if(szIP && strlen(szIP)) strcpy(m_IP,szIP); }

	inline void SetClosed()	{m_bClosed = true;}

public:
	bool			m_bClosed;
	bool			m_bFree;				//true : ����״̬ false:��ʹ��
	SOCKET			m_sock;
	char			m_IP[25];
	ULONG			m_Port;
	int				m_nRecvBufSize;			//�������ݵĻ�������С
	int				m_nSendBufSize;			//�������ݵĻ�������С
	char*			m_RecvBuff;				//�������ݵĻ�����
	CWDoubleBuff	m_WriteBufferQueue;
};

class CSelectIO : public CNet
{
public:
	CSelectIO(CGameNet* pGameNet);	
	virtual ~CSelectIO();

public:
	virtual BOOL	Begin(int nPort,int nPacketPoolSize,int nConnecMax,int nRecvBuffSize,int nSendBuffSize,int nTimeout);
	virtual void	End();	
	
	//virtual void	Accept( SOCKET sock);
	virtual SOCKET	Connect( const char *szIP, ULONG lPort );									//��������
	virtual SOCKET	ConnectAsync( const char *szIP, ULONG lPort, ConnectCallBackFunc pfn=NULL );//����������
	virtual int		Recv( SOCKET sock, char *szBuf, int nSize );
	virtual int		Send( SOCKET sock, char *szBuf, int nSize );
	virtual void	Break( SOCKET sock );		
	virtual BOOL	Close( SOCKET sock );	

	static DWORD WINAPI ConnThread(PVOID pParam);			//���������ӷ�ʽ�Ĵ����߳�
	static DWORD WINAPI RecvThread(PVOID pParam);
	static DWORD WINAPI SendThread(PVOID pParam);
	static DWORD WINAPI	CloseThread(PVOID pParam);
	
	IOKEY*			GetFreeKey();
	inline void		SetKey( SOCKET sock,IOKEY* pKey )	{ m_IOKeyMap.Insert(sock,pKey); }
	inline IOKEY*	GetKey( SOCKET sock)	{ return (IOKEY*)m_IOKeyMap.Find(sock); }
	inline void		RemoveKey(SOCKET sock)	{ m_IOKeyMap.Remove(sock); }

	inline int		GetSendBufferUsage( SOCKET sock )	
	{ 
		IOKEY* IO = GetKey(sock); 
		if( IO && !m_nSendBuffSize )
			return IO->m_WriteBufferQueue.m_nWriteSize * 100 / m_nSendBuffSize;
		return -1;
	}

protected:
	int			SetSockOpt(SOCKET sock, int nRecv, int nSend, int dtime, int idle, int intv);	//����socket����
	void		AcceptAllConnections();

protected:
	BOOL		m_StarFlag;
	CGEvent		m_Event;
	SOCKET		m_nListenSocket;			//����socket
	int			m_nConnectMax;				//����������
	IOKEY*		m_IOKeyTable;
	int			m_nRecvBuffSize;			//�������ݵĻ�������С
	int			m_nSendBuffSize;			//�������ݵĻ�������С
	int			m_nWorkSocketCount;			//������IOkey�ĸ���
	CGLock		m_RecvLock,m_SendLock;		//
	CSocketHashTable m_IOKeyMap;

	//�ͻ���ʹ�õ�
	BOOL		m_ConnectFlag;				//�����ӷ�������ʾ
	SOCKET		m_nConnectSocket;		//�ͻ�������socket
	ConnectCallBackFunc	m_pCallFnConnAsync;
	
private:
	CGameNet*	m_pGameNet;	

};
#endif
