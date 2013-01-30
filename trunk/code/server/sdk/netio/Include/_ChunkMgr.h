#pragma  once
#include "../../Common/GlobalConst.h"
#include "dbg.h"
#include "Gamenetcommondefine.h"

GAMENETCOMMON_GLOBAL	int	g_GetChunkAllocIndex();
//////////////////////////////////////////////////////////////////////////
//
struct PACKET_CHUNK
{
	SOCKET	m_Socket;
	UINT	m_Size;						// ���յ����ݴ�С
	char	m_Chunk[CHUNK_BUFFER_SIZE];	// ���յ����ݿ� f�̶���С����ȷ���ǲ��ǻᳬ�������С��

	PACKET_CHUNK() 
	{
		m_Size = 0;
		m_Socket = INVALID_SOCKET;
	}

	inline UINT Write(const char* pData, int nSize)
	{		
		if( nSize > CHUNK_BUFFER_SIZE)
		{
			Assert(0);
			return 0;
		}
		memcpy(m_Chunk, pData, nSize);
		m_Size = nSize;
		return nSize;
	}

	inline BOOL Release()
	{
		m_Size = 0;
		m_Socket = INVALID_SOCKET;
		return TRUE;
	}
};

//
class CChunkQueue
{
public:
	CChunkQueue()
	{
		m_Read	= 0;
		m_Write = 0;
		for(int i=0;i<CHUNK_COUNT_MAX;i++)
		{
			m_Table[i] = NULL;
		}
	}
	~CChunkQueue()
	{

	}
public:
	inline void Release()
	{
		m_Read	= 0;
		m_Write = 0;
		for(int i=0;i<CHUNK_COUNT_MAX;i++)
		{
			m_Table[i] = NULL;
		}
	}

	inline bool Write(PACKET_CHUNK* p)
	{
		LONG idx = InterlockedExchangeAdd(&m_Write,1);				
		InterlockedCompareExchange(&m_Write,0,CHUNK_COUNT_MAX);
		m_Table[idx] = p;

		return true;
	}

	inline PACKET_CHUNK* Read()
	{
		return m_Table[m_Read];
	}

	//	read������һ��ʹ�ã�������ҪNext��ȷ��read�ɹ��Ĳ���
	inline void	Next()	
	{
		//����ǰ�����ó�NULL
		m_Table[m_Read] = NULL;

		//�����Զ��ص���ʼ��λ��
		InterlockedIncrement(&m_Read);
		InterlockedCompareExchange(&m_Read,0,CHUNK_COUNT_MAX);
	}

	inline	bool	IsDataWaiting()	{	return (m_Table[m_Read] != NULL);	}

protected:
	PACKET_CHUNK*		m_Table[CHUNK_COUNT_MAX];
	long				m_Read,m_Write;

};
//
class CChunkMgr
{
public:
	CChunkMgr()
	{
		m_AllocIndex = 0;
	}
	~CChunkMgr(){}

	inline PACKET_CHUNK*	Alloc()
	{
		LONG idx =  InterlockedExchangeAdd(&m_AllocIndex,1);				
		InterlockedCompareExchange(&m_AllocIndex,0,CHUNK_COUNT_MAX);		
		return &ChunkTable[idx];		
	}

	inline void	Free(PACKET_CHUNK* pPacket){;}
	inline int  AllocIndex()		{return m_AllocIndex;}
protected:
	LONG			m_AllocIndex;					//Ҫ�����ָ��
	PACKET_CHUNK	ChunkTable[CHUNK_COUNT_MAX];
};

CChunkMgr& ChunkMgr();