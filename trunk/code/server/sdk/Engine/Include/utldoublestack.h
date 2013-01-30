#pragma once

#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif

#include "platform.h"

template<class T>
class CDoubleStack
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
				Plat_BlockLog("m_stack alloc failed£¡\n");
				m_lock.UNLOCK();
				return false;
			}
			memset( m_stack, 0, sizeof(T*)*nSize );
			m_top = 0;
			m_max = nSize;
			m_lock.UNLOCK();
			return true;
		}

		inline bool	Push( T* mem )
		{
			bool res = false;
			m_lock.LOCK();
			if( m_stack && (m_top+1<m_max) )
			{
				m_stack[m_top++] = mem;
				res = true;
			}
			m_lock.UNLOCK();
			return res;
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
		uint			m_max;
		CGLock			m_lock;
	};

public:
	CDoubleStack()
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

	inline bool	Push( T* mem )
	{
		return m_pStackFree->Push( mem );
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
