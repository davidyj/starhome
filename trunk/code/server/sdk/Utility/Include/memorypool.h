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
//	重写：	2011-09-27	        by li9chuan
//		1.DoubleStack管理空闲空间。
//		2.支持自动增长。
//		3.支持两种内存分配模式。
//			(a)OBJ模式，对象内存池，调用Init初始化。 
//			(b)MEM模式，一些固定大小的内存块，调用InitMem初始化。
//		4.增加对池中对象的预处理和后处理。
//==========================================================================================================================

#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H
#include "platform.h"
#include "vprof.h"
#include "ThreadLibFunctions.h"
#include "atomic.h"
#include "CommDef.h"

#define USEFLAGLEN	sizeof(ULONG)
#define NAMELEN		( 256 * sizeof(char) )

class CSqlRetObj;
class CSqlObj;
struct _DefaultFunc	//	默认的预处理和后处理
{
	inline bool operator()( void* const data ) const 
	{
		return true;
	}
};

template<class T,typename PreFunc=_DefaultFunc,typename AfterFunc=_DefaultFunc>
class CObjectMemoryPool
{
public:
	CObjectMemoryPool();
	~CObjectMemoryPool();

	inline bool	Init( const char* szName, uint nCount, uint nGrow=2048 );
	inline bool	InitMem( const char* szName, uint nSize, uint nCount, uint nGrow );
	inline T*	Alloc();
	inline bool	Free( T *pMem );
	inline void	FreeAll();
	inline void Purge( void );
	inline void	Report(int& line);
	inline void	MemLog();

private:
	char			m_szName[NAMELEN];		//	内存池的标识
	uint			m_size;
	uint			m_count;				//	内存池的Obj个数
	volatile LONG	m_used;					//	内存池的当前使用数
	UCHAR*			m_pPool;				//
	void*			m_pPoolTail;

	inline bool     PublicInitialization(const char* szName,uint nCount,uint nGrow);	//
private:
	CGLock		m_growlock;
	uint		m_growSize;
	CObjectMemoryPool<T,PreFunc,AfterFunc>*	m_growBlock;

private:
	PreFunc			pre_func;
	AfterFunc		after_func;

private:

	enum _MODE
	{
		OBJ,
		MEM,
		UN_INIT
	};
	_MODE		m_mode;

	class _DoubleStack
	{
	private:
		struct	_Stack
		{
			inline bool	Init( uint nSize )
			{
				if(nSize == 0)
					return false;			

				m_lock.LOCK();
				if( m_stack )
				{
					m_stack = (T**)Plat_Realloc( m_stack, sizeof(T*)*nSize );
				}
				else
				{
					m_stack = (T**)Plat_Alloc( sizeof(T*)*nSize );
				}

				if(!m_stack)
				{
					Plat_BlockLog("m_stack alloc failed！\n");
					m_lock.UNLOCK();
					return false;
				}
				memset( m_stack, 0, sizeof(T*)*nSize );
				m_top = 0;
				m_lock.UNLOCK();
				return true;
			}

			inline void	Push( T* mem )
			{
				m_lock.LOCK();
				if( m_stack )
				{
					m_stack[m_top++] = mem;
				}
				m_lock.UNLOCK();
			}

			inline T*	Pop( void )
			{
				T* res = NULL;
				m_lock.LOCK();
				if( m_stack && m_top > 0 )
				{
					res = m_stack[--m_top];	
				}
				m_lock.UNLOCK();
				return res;
			}

			_Stack()
			{
				m_stack	=	NULL;
				m_top	=	0;
			}

			~_Stack()
			{
				Purge();
			}

			inline void Purge()
			{
				m_lock.LOCK();
				m_top	=	0;
				Plat_Free(m_stack);
				m_stack = NULL;
				m_lock.UNLOCK();
			}

			inline void Clear()
			{
				m_lock.LOCK();
				m_top	=	0;
				m_lock.UNLOCK();
			}

			T**				m_stack;
			volatile uint	m_top;
			CGLock			m_lock;
		};

	public:
		_DoubleStack()
		{
			m_pStackFree = &m_stack1;
			m_pStackAlloc = &m_stack2;
		}

		inline bool	Init( uint nSize )
		{
			if ( m_stack1.Init( nSize ) )
			{
				if( m_stack2.Init( nSize ) )
				{
					return true;
				}
			}
			return false;
		}

		inline void	Push( T* mem )
		{
			m_pStackFree->Push( mem );
		}

		inline T*	Pop( void )
		{
			T* res = m_pStackAlloc->Pop();

			if( res == NULL )
			{
				m_lock.LOCK();
				res = m_pStackAlloc->Pop();
				if( res == NULL )
				{
#				ifdef WIN32
					m_pStackAlloc = (_Stack*)InterlockedExchangePointer((void**)&m_pStackFree,(void*)m_pStackAlloc);
#				else
					_Stack* pStack = m_pStackFree;
					atomic_store_rel_ptr((uintptr_t *)&m_pStackFree,(uintptr_t)m_pStackAlloc);
					atomic_store_rel_ptr((uintptr_t *)&m_pStackAlloc,(uintptr_t)pStack);
#				endif
					res = m_pStackAlloc->Pop();
				}
				m_lock.UNLOCK();
			}
			return res;
		}

		inline void Clear()
		{
			m_stack1.Clear();
			m_stack2.Clear();
		}

	private:
		_Stack* m_pStackAlloc;
		_Stack* m_pStackFree;
		_Stack	m_stack1;
		_Stack	m_stack2;
		CGLock	m_lock;
	};

	_DoubleStack	m_dstack;
};

template<class T,typename PreFunc,typename AfterFunc>
CObjectMemoryPool<T,PreFunc,AfterFunc>::CObjectMemoryPool()
{
	memset( m_szName, 0, NAMELEN );
	m_pPool = NULL;
	m_pPoolTail = NULL;
	m_size	= 0;
	m_count	= 0;
	m_used	= 0;
	m_growSize	= 0;
	m_growBlock = NULL;
	m_mode		= UN_INIT;
}

template<class T,typename PreFunc,typename AfterFunc>
CObjectMemoryPool<T,PreFunc,AfterFunc>::~CObjectMemoryPool()
{
	Purge();
}

template<class T,typename PreFunc,typename AfterFunc>
inline bool CObjectMemoryPool<T,PreFunc,AfterFunc>::PublicInitialization(const char* szName,uint nCount,uint nGrow)
{
	m_szName[0] = '\0';
	strncat(m_szName,szName,NAMELEN-1);
	m_count	    = nCount;
	m_growSize  = nGrow;

	const uint64 memsize = ( m_size + USEFLAGLEN ) * m_count;

	if( m_pPool )
	{
		FreeAll();
		m_pPool = (byte*)Plat_Realloc( m_pPool, memsize );
	}
	else
	{
		m_pPool = (byte*)Plat_Alloc( memsize );
	}

	if(!m_pPool)
	{
		Plat_BlockLog( "%s alloc failed！\n", m_szName );
		return false;
	}

	memset( m_pPool, 0, memsize );
	m_pPoolTail = (void*)( m_pPool + memsize ) ;

	if ( !m_dstack.Init( m_count ) )
	{
		Plat_Free(m_pPool);
		m_pPool     = NULL;
		m_pPoolTail = NULL;
		Plat_BlockLog( "%s m_dstack.Init() failed！\n", m_szName );
		return false;
	}

	for( uint i=0; i<m_count; i++ )
	{
		uint64 index = i * ( USEFLAGLEN + m_size );
		m_dstack.Push( (T*)(&m_pPool[index]+USEFLAGLEN) );
	}

	return true;
}

template<class T,typename PreFunc,typename AfterFunc>
inline bool CObjectMemoryPool<T,PreFunc,AfterFunc>::Init(const char* szName,uint nCount,uint nGrow)
{
	m_size	    = sizeof(T);
	if( !PublicInitialization(szName,nCount,nGrow) )	{	return	false;	}

	for( uint i=0; i<m_count; i++ )
	{
		uint64 index = i * ( USEFLAGLEN + sizeof(T) );
		T* pMem = (T*)(&m_pPool[index]+USEFLAGLEN);
		Construct( pMem );
		pre_func ( pMem );
		Destruct ( pMem );
	}

	m_mode		= OBJ;
	return true;
}

template<class T,typename PreFunc,typename AfterFunc>
inline bool CObjectMemoryPool<T,PreFunc,AfterFunc>::InitMem(const char* szName,uint nSize,uint nCount,uint nGrow)
{
	m_size	    = sizeof(T)*nSize;
	if( !PublicInitialization(szName,nCount,nGrow) )	{	return	false;	}
	m_mode		= MEM;
	return true;
}

template<class T,typename PreFunc,typename AfterFunc>
inline T* CObjectMemoryPool<T,PreFunc,AfterFunc>::Alloc()
{
	T* res = m_dstack.Pop();
	if( res != NULL )
	{
		ThreadLib::LocketSet( (volatile LONG *)((byte*)res - USEFLAGLEN) , 1 );
		ThreadLib::LockedIncrement(&m_used);
		if( m_mode == OBJ )
		{
			Construct( res );
		}
		return res;
	}

	if( m_growSize == 0 )
	{
		Plat_BlockLog("%s设置不自动增长，内存分配失败！\n", m_szName);
		return NULL;
	}

	m_growlock.LOCK();
	if( !m_growBlock )
	{
		Plat_BlockLog("%s内存池已满！\n", m_szName);
		m_growBlock = new CObjectMemoryPool<T,PreFunc,AfterFunc>;
		char szName[NAMELEN];
		sprintf( szName, "%s_%d", m_szName, m_growSize );

		bool bgrow = false;

		switch( m_mode )
		{
		case OBJ:
			bgrow = m_growBlock->Init( szName, m_growSize, m_growSize*2 );
			break;
		case MEM:
			bgrow = m_growBlock->InitMem( szName, m_size, m_growSize, m_growSize*2 );
			break;
		default:
			Assert( FALSE );
			return NULL;
		}

		if( bgrow )
		{
			Plat_BlockLog("增长 %s！\n", szName);
		}
		else
		{
			Plat_BlockLog("增长失败 %s！\n", szName);
			delete m_growBlock;
			m_growBlock		= NULL;
			m_growlock.UNLOCK();
			return NULL;
		}
	}
	m_growlock.UNLOCK();
	
	return m_growBlock->Alloc();
}

template<class T,typename PreFunc,typename AfterFunc>
inline bool CObjectMemoryPool<T,PreFunc,AfterFunc>::Free(T *pMem)
{
	if( (void*)pMem>=(void*)m_pPool && (void*)pMem<m_pPoolTail )
	{
		if( LockedCompareExchange( (volatile LONG *)((byte*)pMem - USEFLAGLEN), 0, 1 ) )
		{
			if( m_mode == OBJ )
			{
				Destruct( pMem );
			}
			m_dstack.Push(pMem);
			ThreadLib::LockedDecrement(&m_used);
		}
		else
		{
			Plat_BlockLog("%s:内存重复释放！！！\n", m_szName);
			assert(0);
			return false;
		}
	}
	else if( m_growBlock )
	{
		m_growBlock->Free(pMem);
	}
	else
	{
//		Plat_BlockLog("%s:释放的内存不属于该内存池！！！\n", m_szName);
		return false;
	}
	return true;
}

template<class T,typename PreFunc,typename AfterFunc>
inline void CObjectMemoryPool<T,PreFunc,AfterFunc>::FreeAll()
{
	if( m_mode == UN_INIT )	{	return;	}
	m_growlock.LOCK();
	if( m_growBlock )  { m_growBlock->FreeAll(); }

	for( uint i=0; i<m_count; i++ )
	{
		uint64 index = (i) * ( USEFLAGLEN + m_size );
		T *pMem = (T*)(&m_pPool[index]+USEFLAGLEN);
		if( LockedCompareExchange( (volatile LONG *)((byte*)pMem - USEFLAGLEN), 0, 1 ) )
		{
			if( m_mode == OBJ )
			{
				Destruct( pMem );
			}
			m_dstack.Push(pMem);
			ThreadLib::LockedDecrement(&m_used);
		}
	}

	if( m_used != 0 )
	{
		Plat_BlockLog( "CObjectMemoryPool::FreeAll()释放错误!" );
		assert(0);
	}
	m_growlock.UNLOCK();
}

//fixed by david 
template<class T,typename PreFunc,typename AfterFunc>
inline void CObjectMemoryPool<T,PreFunc,AfterFunc>::Purge()
{
	if( m_mode == UN_INIT )	{	return;	}
	//FreeAll();				//	FreeAll与下面的操作不是同步的
	m_growlock.LOCK();
	if( m_growBlock )  
	{
		m_growBlock->~CObjectMemoryPool();  
		m_growBlock = NULL; 
	}
	//if( m_mode == OBJ )
	{
		//for( uint i=0; i<m_count; i++ )
		{
			//uint64 index = (i++) * ( USEFLAGLEN + sizeof(T) );
			//T* pMem = (T*)(&m_pPool[index]+USEFLAGLEN);
			//Construct ( pMem );
			//after_func( pMem );
			//Destruct  ( pMem );
		}
	}
	m_used		= 0;
	m_size		= 0;
	m_count		= 0;
	m_szName[0] = '\0';
	Plat_Free(m_pPool);
	m_pPool		= NULL;
	m_pPoolTail	= NULL;
	m_mode		= UN_INIT;
	m_growlock.UNLOCK();
}

template<class T,typename PreFunc,typename AfterFunc>
inline void CObjectMemoryPool<T,PreFunc,AfterFunc>::Report(int& line)
{
	Print(line++,"%s	%10.3f K / %10.3f K	   <<%10.3f K \n",m_szName,(float)m_used * (float)m_size/1024.0, (float)m_count * (float)m_size/1024.0, (float)m_size/1024.0);
	if( m_growBlock )   { m_growBlock->Report(line); }
}

template<class T,typename PreFunc,typename AfterFunc>
inline void CObjectMemoryPool<T,PreFunc,AfterFunc>::MemLog()
{
	Log("MemoryPool::%s	%d / %d << %10.3f K",m_szName,m_used, m_count, (float)m_size/1024.0);
	if( m_growBlock )   { m_growBlock->MemLog(); }
}

#endif
