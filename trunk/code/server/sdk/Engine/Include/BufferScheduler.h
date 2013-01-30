#pragma once

#include <list>
#include <algorithm>

#include "utlhashbucket.h"
#include "algo.h"

#define MD5LEN  16

//template<class TKey>
//struct _BufferContextComp : public std::binary_function<_BufferContext<TKey>*, _BufferContext<TKey>*, bool>
//{
//	bool operator()( const _BufferContext<TKey>* iter, const _BufferContext<TKey>* value ) const
//	{
//		return iter->weight < value->weight;
//	}
//};

#define  CONTEXTLIST        std::list<_BufferContext*>
#define  CONTEXTLIST_ITER   std::list<_BufferContext*>::iterator

class CBufferScheduler
{
private:

	struct _BufferContext
	{
		char      m_md5[MD5LEN];
		int       size;
		void*     buffer;
		_BufferContext():size(0),buffer(NULL){}
		~_BufferContext()
		{
			size   = 0;
			buffer = NULL;
		}
	};

	struct _GetKey : public std::unary_function<const char *, int>
	{
		int operator()( const char * const md5 ) const
		{
			return whashstr( md5, MD5LEN );
		}
	};

	struct _EqualKey : public std::binary_function<_BufferContext*, const char *, bool>
	{
		bool operator()( _BufferContext* const lfh, const char * const md5 ) const
		{
			if( !lfh || !md5 ) { return false; }

			int i = MD5LEN-1;
			while( i!=0 && lfh->m_md5[i] == md5[i] )
			{
				--i;
			}

			if( i == 0 )
				return true;

			return false;
		}
	};

private:

	CObjectMemoryPool<_BufferContext>							m_BCS;
	CHashBucket<const char*,_BufferContext,_GetKey,_EqualKey>	m_BufferContextHash;
	CONTEXTLIST													m_BufferContextList;

	CGLock		m_lock;
	uint		m_totalsize;
	uint		m_currsize;
	uint		m_onebuffsize;

	char		m_szReport[1024];

	uint		m_getCount;
	uint		m_setCount;
	uint		m_fileCount;

public:

	bool		m_bisinit;

	CBufferScheduler():m_totalsize(0),m_onebuffsize(0),m_getCount(0),m_setCount(0),m_fileCount(0),m_bisinit(false){}

	bool Init( const char* szName, uint totalSize, uint oneSize )
	{
		m_BufferContextHash.init( 65536, 8192 );
		m_BCS.Init( szName, 8192 );
		m_currsize      = 0;
		m_totalsize     = totalSize;
		m_onebuffsize	= oneSize;
		m_bisinit		= true;
		return true;
	}

	size_t getBuffer( const char* key, void* pOutput, int size )
	{
		m_lock.LOCK();

		m_getCount++;
		_BufferContext* pBC = m_BufferContextHash.Find( key );

		if( pBC )
		{
			assert( pBC->size == size );
			memcpy( pOutput, pBC->buffer, size );

			//for( CONTEXTLIST_ITER iter = m_BufferContextList.begin(); iter!=m_BufferContextList.end(); iter++ )
			//{
			//	if( *iter == pBC )
			//	{
			//		m_BufferContextList.erase(iter);
			//		break;
			//	}
			//}
			//m_BufferContextList.push_front(pBC);
			uint res = pBC->size;
			m_lock.UNLOCK();
			return res;
		}
		m_lock.UNLOCK();
		return 0;
	}

	void setBuffer( const char* key, void* pInput, uint size )
	{
		if( size > m_onebuffsize )	{  return;  }

		m_lock.LOCK();

		m_setCount++;
		_BufferContext* pBC = m_BufferContextHash.Find( key );

		if( !pBC )
		{
			while( m_currsize+size > m_totalsize )
			{
				_BufferContext* pBCTmp = *(--m_BufferContextList.end());
				m_BufferContextList.pop_back();
				m_currsize -= pBCTmp->size;
				m_BufferContextHash.Remove( pBCTmp->m_md5 );
				Plat_Free( pBCTmp->buffer );
				m_BCS.Free( pBCTmp );
				m_fileCount--;
			}

			pBC = m_BCS.Alloc();
			if( pBC )
			{
				pBC->buffer = Plat_Alloc( size );
				if( pBC->buffer == NULL )
				{
					Log("资源缓冲内存分配失败！");
					m_BCS.Free( pBC );
					m_lock.UNLOCK();
					return;
				}

				m_currsize += size;
				memcpy( pBC->buffer, pInput, size );
				memcpy( pBC->m_md5, key, MD5LEN );
				pBC->size   = size;
				m_BufferContextList.push_front( pBC );
				//m_BufferContextList.insert(
				//	std::lower_bound( m_BufferContextList.begin(), m_BufferContextList.end(), pBC, _BufferContextComp<TKey>() ), pBC );
				m_BufferContextHash.Insert( key, pBC );
				m_fileCount++;
			}
		}
		m_lock.UNLOCK();
		return;
	}

	const char* report()
	{
		sprintf( m_szReport, "总读取次数：%d  缺页次数：%d  缺页率：%d%%  文件个数：%d",
			m_getCount, m_setCount, int((float)((float)m_setCount/(float)m_getCount)*100), m_fileCount );
		return m_szReport;
	}

};

