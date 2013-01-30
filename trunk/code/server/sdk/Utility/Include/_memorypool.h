//
//	CObjectMemroyPool:
//==========================================================================================================================
//	�޸�1��2011-04-22 13:23  by david
//		1.�����˶Զ��̵߳�֧�֣����Զ����߳�ͬʱAlloc�ڴ治�����bug������
//	ע�⣺
//		1.ɾ��ʱδ�����������ܴ���һ�������������ڻ�����ʲô���⣬���ϲ��ʹ��
//			�йء���Ҳ��û�������ף�������
//
//==========================================================================================================================
//	�޸�2��	2011-04-23	15:11   by David
//		1.�����˶Ե�������֧��
//		2.������һ��������������ĺ꣬�������ڴ�й©�����
//
//==========================================================================================================================
//	�޸�3��	2011-05-28	        by li9chuan
//		1.Free֧�ֶ��߳��ͷţ��ظ��ͷ�ͬһ���ڴ治�����
//
//		2.����windows atomicʹ��LONG���޸��ڴ��Ƿ�ʹ�õı��ΪLONG��                  #define USEFLAGLEN	sizeof(ULONG)
//			UNIX�¿��Զ�byte��������ֲ���ʹ��1byte��ʾ��
//
//		3.Alloc()������, ����_InterlockedCompareExchange( (volatile LONG *)&(m_pPool[index]), 1, 0 ) )�滻Ϊ�ֲ��Ĳ�����
//			��˳�����ʱ��Alloc()������Լ10%��Ч�ʣ�����Ƕ��̵߳��û���ߡ�
//			���ڻ�����Ԫ�ظ�������ʱ�����ж���߳�ͬʱ����if�����������ϴ�ʱ�ɿ��Ƿֲ���
//
//==========================================================================================================================
//	�޸�4��	2011-05-28	        by li9chuan
//		1.֧���Զ�������
//==========================================================================================================================

#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H
#include "platform.h"
#include "vprof.h"
#include "ThreadLibFunctions.h"
#include "atomic.h"
#include "CommDef.h"
//-----------------------------------------------------------------------------
// Wrapper macro to make an allocator that returns particular typed allocations
// and construction and destruction of objects.
//-----------------------------------------------------------------------------
#define FOR_EACH_POOL( poolName, iteratorName ) \
	for( int iteratorName=poolName.Head(); iteratorName != poolName.End(); iteratorName = poolName.Next( iteratorName ) )

#define USEFLAGLEN	sizeof(ULONG)
#define NAMELEN		64

template<class T ,class I = ULONG>
class CObjectMemoryPool
{
public:
	CObjectMemoryPool();
	~CObjectMemoryPool();

	inline bool	Init(const char* szName,uint nSize,uint nGrow=1024);
	inline T*	Alloc();
	inline void	Free( T *pMem );
	inline void	FreeAll();
	inline void Purge( void );
	inline void	Report(int line);
	inline void	MemLog();

	inline I Head(){return 0;}
	inline I Next(I i){return ++i;}
	inline I End(){return m_max;}

	inline T* Element(I i);
	inline T* operator[](I i);

private:
	char		m_szName[NAMELEN];		//	�ڴ�صı�ʶ
	ULONG		m_max;				//	�ڴ�ص����ֵ
	ULONG		m_used;				//	�ڴ�صĵ�ǰʹ����
	ULONG		m_current;			//	�ڴ�صĵ�ǰָ��
	UCHAR*		m_pPool;			//
private:
	CGLock		m_growlock;
	uint		m_growSize;
	CObjectMemoryPool<T>*	m_growBlock;
};

template<class T ,class I>
CObjectMemoryPool<T,I>::CObjectMemoryPool()
{
	memset(m_szName,0,NAMELEN);
	m_pPool = NULL;
	m_max = 0;
	m_used = 0;
	m_current = 0;
	m_growSize = 0;
	m_growBlock = NULL;
}

template<class T,class I>
CObjectMemoryPool<T,I>::~CObjectMemoryPool()
{
	Purge();
}

template<class T ,class I>
inline bool CObjectMemoryPool<T,I>::Init(const char* szName,uint nSize,uint nGrow)
{
	strcpy(m_szName,szName);
	m_max = nSize;
	m_growSize= nGrow;

	if( m_pPool )
	{
		m_pPool = (byte*)Plat_Realloc( m_pPool, (sizeof(T) + USEFLAGLEN )* m_max );
	}
	else
	{
		m_pPool = (byte*)Plat_Alloc( (sizeof(T) + USEFLAGLEN )* m_max );
	}

	if(!m_pPool)
	{
		Plat_BlockLog("%s alloc failed��\n", m_szName);
		return false;
	}
	//memset(m_pPool,0,(sizeof(T) + sizeof(bool) )* nSize);
	memset(m_pPool,0,(sizeof(T) + USEFLAGLEN )* m_max);

	return true;
}

// temp,index ÿ���̵߳ĵ�ַ���᲻ͬ�����Բ���������
template<class T ,class I>
inline T* CObjectMemoryPool<T,I>::Alloc()
{
	I temp  =0;
	I index = 0;
	for( I i=0; i<m_max; i++ )
	{
		temp = ThreadLib::LocketAdd((volatile LONG *)&m_current,1);
		index = (temp%m_max) * ( USEFLAGLEN + sizeof(T) );

		if( LockedCompareExchange( (volatile LONG *)&(m_pPool[index]), 1, 0 ) )
//		if( m_pPool[index] == 0 )
		{
//			m_pPool[index] = 1;
			ThreadLib::LockedIncrement((volatile LONG *)&m_used);
			//T *pRet = (T*)(&m_pPool[index]+1);
			T *pRet = (T*)(&m_pPool[index]+USEFLAGLEN);
			if ( pRet ){
				Construct( pRet );
			}
			return pRet;
		}
	}

	m_growlock.LOCK();
	if( !m_growBlock )
	{
		Plat_BlockLog("%s�ڴ��������\n", m_szName);
		m_growBlock = new CObjectMemoryPool<T>;
		char szName[NAMELEN];
		sprintf( szName, "%s_%d", m_szName, m_growSize );

		if( m_growBlock->Init( szName, m_growSize, m_growSize*2 ) )
		{
			Plat_BlockLog("���� %s��\n", szName);
		}
		else
		{
			m_growlock.UNLOCK();
			return NULL;
		}
	}
	m_growlock.UNLOCK();

	return m_growBlock->Alloc();
}

// ע�⣺
// �ڵ���Free��ʱ��һ��Ҫ��֤��ͬһ���̡߳�
// �������� �Ⱥ���õĿ��ܣ����bug
// ����ÿ��obj��freeһ���ڸ��Ե��߼������
//				2011-04-22 14:20 David
template<class T ,class I>
inline void CObjectMemoryPool<T,I>::Free(T *pMem)
{
	if( pMem )
	{
		if( LockedCompareExchange( (volatile LONG *)((byte*)pMem - USEFLAGLEN), 0, 1 ) )
		{
			Destruct( pMem );
			ThreadLib::LockedDecrement((volatile LONG*)&m_used);
		}
	}
}

template<class T ,class I>
inline void CObjectMemoryPool<T,I>::FreeAll()
{
	m_growlock.LOCK();
	if( m_growBlock )  { m_growBlock->FreeAll(); }
	memset(m_pPool,0,(sizeof(T) + USEFLAGLEN )* m_max);
	m_used		= 0;
	m_current	= 0;
	m_growlock.UNLOCK();
}

template<class T ,class I>
inline void CObjectMemoryPool<T,I>::Purge()
{
	m_growlock.LOCK();
	if( m_growBlock )  { m_growBlock->~CObjectMemoryPool();  m_growBlock = NULL; }
	m_used		= 0;
	m_current	= 0;
	m_max		= 0;
	m_szName[0] = '\0';
	Plat_Free(m_pPool);
	m_pPool = NULL;
	m_growlock.LOCK();
}

template<class T,class I>
inline T* CObjectMemoryPool<T,I>::Element(I i)
{
	if(i>=0 && i<m_max)
	{
		int temp = i * ( sizeof(T) + USEFLAGLEN );
		return (T*)( &m_pPool[temp] + USEFLAGLEN );
	}
	else if( i>=0 && m_growBlock )
	{
		return m_growBlock->Element( i - m_max );
	}
	return NULL;
}

template<class T,class I>
inline T* CObjectMemoryPool<T,I>::operator [](I i)
{
	return Element(i);
}

template<class T,class I>
inline void CObjectMemoryPool<T,I>::Report(int line)
{
	Print(line++,"%s	%10.3f K / %10.3f K	   <<%10.3f K \n",m_szName,(float)m_used * (float)sizeof(T)/1024.0, (float)m_max * (float)sizeof(T)/1024.0, (float)sizeof(T)/1024.0);
	if( m_growBlock )   { m_growBlock->Report(line); }
}

template<class T,class I>
inline void CObjectMemoryPool<T,I>::MemLog()
{
	Log("MemoryPool::%s	%d / %d << %10.3f K",m_szName,m_used, m_max, (float)sizeof(T)/1024.0);
	if( m_growBlock )   { m_growBlock->MemLog(); }
}
#endif
