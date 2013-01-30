//
//	CObjectMemroyPool:
//==========================================================================================================================
//	修改1：2011-04-22 13:23  by david
//		1.增加了对多线程的支持；可以多条线程同时Alloc内存不会产生bug。但是
//	注意：
//		1.删除时未作保护，可能存在一定的隐患。至于会引起什么问题，和上层的使用
//			有关。我也还没有想明白，待考察
//
//==========================================================================================================================
//	修改2：	2011-04-23	15:11   by David
//		1.增加了对迭代器的支持
//		2.增加了一个便与遍历操作的宏，方便检查内存泄漏的情况
//
//==========================================================================================================================
//	修改3：	2011-05-28	        by li9chuan
//		1.Free支持多线程释放，重复释放同一块内存不会出错。
//
//		2.由于windows atomic使用LONG，修改内存是否使用的标记为LONG。                  #define USEFLAGLEN	sizeof(ULONG)
//			UNIX下可以对byte操作，移植后可使用1byte表示。
//
//		3.Alloc()函数中, 若将_InterlockedCompareExchange( (volatile LONG *)&(m_pPool[index]), 1, 0 ) )替换为分步的操作，
//			在顺序分配时，Alloc()可提升约10%的效率，如果是多线程调用会更高。
//			但在缓冲区元素个数较少时可能有多个线程同时进入if，缓冲区都较大时可考虑分步。
//
//==========================================================================================================================
//	修改4：	2011-05-28	        by li9chuan
//		1.支持自动增长。
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
	char		m_szName[NAMELEN];		//	内存池的标识
	ULONG		m_max;				//	内存池的最大值
	ULONG		m_used;				//	内存池的当前使用数
	ULONG		m_current;			//	内存池的当前指针
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
		Plat_BlockLog("%s alloc failed！\n", m_szName);
		return false;
	}
	//memset(m_pPool,0,(sizeof(T) + sizeof(bool) )* nSize);
	memset(m_pPool,0,(sizeof(T) + USEFLAGLEN )* m_max);

	return true;
}

// temp,index 每个线程的地址都会不同，所以不会有问题
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
		Plat_BlockLog("%s内存池已满！\n", m_szName);
		m_growBlock = new CObjectMemoryPool<T>;
		char szName[NAMELEN];
		sprintf( szName, "%s_%d", m_szName, m_growSize );

		if( m_growBlock->Init( szName, m_growSize, m_growSize*2 ) )
		{
			Plat_BlockLog("增长 %s！\n", szName);
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

// 注意：
// 在调用Free的时候，一定要保证是同一个线程。
// 否则会出现 先后调用的可能，造成bug
// 所以每个obj的free一定在各自的逻辑里进行
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
