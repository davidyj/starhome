#ifndef IMPL_SELECT_IO_H
#define IMPL_SELECT_IO_H

#include "../../../Port/config.h"
#include "../../Def/GlobalConst.h"
#include "../../Engine/Include/utllinkedlist.h"
#include "../../Engine/Include/GLock.h"
#include "Gamenetcommondefine.h"
#include "SocketHashTable.h"
#include "NetBuffer.h"
#include "Net.h"

class CGameNet;

#define LISTEN_BACKLOG 100

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
		m_nNetID		= 0;
		m_sock			= INVALID_SOCKET;
		m_nRecvBufSize	= nRecvBufSize;
		m_nSendBufSize	= nSendBufSize;
		m_IP[0]			='\0';
	}

	inline void Release()
	{
		Log("IOKEY release by sock:%d",m_sock);
		m_bFree		= true;
		m_bClosed	= false;
		m_nNetID	= 0;
		m_sock		= INVALID_SOCKET;
		m_IP[0]		= '\0';

//		if(m_RecvBuff)
//			Plat_Free(m_RecvBuff);

		m_WriteBufferQueue.Release();
	}

	inline void SetIP(const char* szIP)
	{
		if(szIP && strlen(szIP))
			strcpy(m_IP,szIP);
	}

	inline void SetClosed()	{m_bClosed = true;}
	//inline bool IsClosed()	{return m_bClosed;}

public:
	int				m_nNetID;
	bool			m_bClosed;
	bool			m_bFree;				//true : ����״̬ false:��ʹ��
	SOCKET			m_sock;
	CGLock			m_WriteLock;
	char			m_IP[25];
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
	virtual SOCKET	Connect( const char *szIP,ULONG lPort );
	virtual int		Recv( SOCKET sock,char *szBuf,int nSize );
//	virtual int		Send( SOCKET sock,PACKET_COMMAND* pPacket);
	virtual int     Send( SOCKET sock, char *szBuf, int nSize );
	virtual void	Break( SOCKET sock );
	virtual char*	IP(SOCKET sock);

	static void* RecvThread(void *pParam);
	static void* SendThread(void *pParam);
	static void* CloseThread(void *pParam);

	IOKEY*	GetFreeKey();
	void	SetKey( SOCKET sock,IOKEY* pKey );
	IOKEY*	GetKey( SOCKET sock);
	void	RemoveKey(SOCKET sock);

protected:
	virtual BOOL	Close(SOCKET sock);								//�����ڹ����̹߳ر�һ��socket, ���߼����ɵ��ô˺���
	int		SetSockOpt(SOCKET sock, int nRecv, int nSend, int dtime, int idle, int intv, int cnt);	//����socket����

private:
	void		AcceptAllConnections();

protected:
	BOOL		m_StarFlag;
	CGEvent		m_Event;
	SOCKET		m_nListenSocket;			//����socket
	int			m_nConnectMax;				//����������
	IOKEY*		m_IOKeyTable;
	LONG		m_IOKeyTableIndex;
	int			m_nRecvBuffSize;			//�������ݵĻ�������С
	int			m_nSendBuffSize;			//�������ݵĻ�������С
	int			m_nWorkSocketCount;			//������IOkey�ĸ���
	int			m_nPacketPoolSize;			//��Ϣ�ش�С
	CGLock		m_RecvLock,m_SendLock;		//
	CSocketHashTable m_IOKeyMap;

private:
	CGameNet*	m_pGameNet;
};
#endif
