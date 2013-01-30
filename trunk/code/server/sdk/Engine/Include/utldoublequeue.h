#pragma once

#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif

#include "platform.h"

template<class T>
class CDoubleQueue
{
private:
	struct	_Queue
	{
		inline bool	Init( uint nSize )
		{
			if(nSize == 0)
				return false;			

			m_lock.LOCK();
			if( m_queue )
			{
				m_queue = (T**)Plat_Realloc( m_queue, sizeof(T*)*nSize );
			}
			else
			{
				m_queue = (T**)Plat_Alloc( sizeof(T*)*nSize );
			}

			if(!m_queue)
			{
				Plat_BlockLog("m_queue alloc failed£¡\n");
				m_lock.UNLOCK();
				return false;
			}
			memset( m_queue, 0, sizeof(T*)*nSize );
			m_top = 0;
			m_curr = 0;
			m_max = nSize;
			m_lock.UNLOCK();
			return true;
		}

		inline bool	Push( T* mem )
		{
			bool res = false;
			m_lock.LOCK();
			if( m_queue && (m_top+1<m_max) )
			{
				m_queue[m_top++] = mem;
				res = true;
			}
			m_lock.UNLOCK();
			return res;
		}

		inline T*	Pop( void )
		{
			T* res = NULL;
			m_lock.LOCK();
			if( m_queue && m_curr<m_top )
			{
				res = m_queue[m_curr++];	
			}
			else
			{
				m_curr = 0;
				m_top  = 0;
			}
			m_lock.UNLOCK();
			return res;
		}

		_Queue():m_queue(NULL){}

		~_Queue()
		{
			Purge();
		}

		inline void Purge()
		{
			m_lock.LOCK();
			m_top	=	0;
			m_curr	=	0;
			if( m_queue )	{	Plat_Free(m_queue);	}
			m_queue = NULL;
			m_lock.UNLOCK();
		}

		inline void Clear()
		{
			m_lock.LOCK();
			m_top	=	0;
			m_curr	=	0;
			m_lock.UNLOCK();
		}

		T**				m_queue;
		uint			m_top;
		uint			m_curr;
		uint			m_max;
		CGLock			m_lock;
	};

public:
	CDoubleQueue()
	{
		m_pQueueFree  = &m_queue1;
		m_pQueueAlloc = &m_queue2;
	}

	inline bool	Init( uint nSize )
	{
		if ( m_queue1.Init( nSize ) )
		{
			if( m_queue2.Init( nSize ) )
			{
				return true;
			}
		}
		return false;
	}

	inline bool	Push( T* mem )
	{
		return m_pQueueFree->Push( mem );
	}

	inline T*	Pop( void )
	{
		T* res = m_pQueueAlloc->Pop();

		if( res == NULL )
		{
			m_lock.LOCK();
			res = m_pQueueAlloc->Pop();
			if( res == NULL )
			{
#				ifdef WIN32
				m_pQueueAlloc = (_Queue*)InterlockedExchangePointer((void**)&m_pQueueFree,(void*)m_pQueueAlloc);
#				else
				_Queue* pQueue = m_pQueueFree;
				atomic_store_rel_ptr((uintptr_t *)&m_pQueueFree,(uintptr_t)m_pQueueAlloc);
				atomic_store_rel_ptr((uintptr_t *)&m_pQueueAlloc,(uintptr_t)pQueue);
#				endif
				res = m_pQueueAlloc->Pop();
			}
			m_lock.UNLOCK();
		}
		return res;
	}

	inline void Clear()
	{
		m_queue1.Clear();
		m_queue2.Clear();
	}

private:
	_Queue* m_pQueueAlloc;
	_Queue* m_pQueueFree;
	_Queue	m_queue1;
	_Queue	m_queue2;
	CGLock	m_lock;
};
