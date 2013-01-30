// stdafx.cpp : source file that includes just the standard includes
//	BaseSrc.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "../stdafx.h"
#include "mynew.h"

#ifdef WIN32
#include <malloc.h>
#else
#include <stdlib.h>
#endif

#include "dbg.h"
#include "osAllocator.h"

Allocator g_Allocator(1000);

Allocator* GetAllocator( )
{
	return &g_Allocator;
}
//#define _ANALYZEMEMORY


class NewNode// : public CHAINITEM
{
public:
	NewNode( )
	{
		nSize = 0;
		nCount = 0;
		nMax = 0;
	}
	int nSize;
	int nCount;
	int nMax;
};

#include <map>

typedef std::map<int,NewNode*> MemSizeMap_t;

MemSizeMap_t & MemSizeMap( )
{
	static MemSizeMap_t g_MemSizeMap;
	return g_MemSizeMap;
}

int g_nTotalSize = 0;
int g_nNewCount = 0;
int g_nCurSize = 0;
int g_nCurNewCount = 0;
/*
/////////////////////////////////////////////////////////////////////
struct CMemoryBlockHeader
{
	BYTE bValid;
};

class CMemoryGroup
{
public:
	CMemoryGroup( );
	~CMemoryGroup( );

	void Create( int nMax, int nDataSize );
	void Destroy( );

	void * GetMem( );
	void ReleaseMem( void * p );

public:
	BYTE * m_pGroupData;
	int m_nCur;
	int m_nMax;
	int m_nDataSize;
};

CMemoryGroup::CMemoryGroup( )
{
	m_pGroupData = NULL;
	m_nCur = 0;
	m_nMax = 0;
	m_nDataSize = 0;
}

CMemoryGroup::~CMemoryGroup( )
{
	Destroy( );
}

void CMemoryGroup::Create( int nMax, int nDataSize )
{
	m_nMax = nMax;
	m_nDataSize = nDataSize + sizeof(CMemoryBlockHeader);
	m_pGroupData = ( BYTE * )malloc( sizeof( BYTE ) * m_nMax*m_nDataSize );
	memset( m_pGroupData, 0, m_nMax*m_nDataSize );
}

void CMemoryGroup::Destroy( )
{
	if( m_pGroupData )
	{
		free( m_pGroupData );
		m_pGroupData = NULL;
	}
	m_nDataSize = 0;
	m_nMax = 0;
}

void * CMemoryGroup::GetMem( )
{
	if( m_nCur >= m_nMax )
		m_nCur = 0;
	CMemoryBlockHeader * pHead;
	BYTE * pData = &m_pGroupData[m_nCur*m_nDataSize];
	for( int nCount = 0; nCount < m_nMax; nCount++, m_nCur++ )
	{
		pHead = (CMemoryBlockHeader*)pData;
		if( pHead->bValid == 0 )
		{
			pHead->bValid = 1;
			return pData + sizeof(CMemoryBlockHeader);
		}
		else
			pData += m_nDataSize;
		if( m_nCur >= m_nMax )
		{
			m_nCur = 0;
			pData = &m_pGroupData[m_nCur];
		}
	}
	return NULL;
}

void CMemoryGroup::ReleaseMem( void * p )
{
	CMemoryBlockHeader * pHead;
	pHead = ((CMemoryBlockHeader*)p)-1;
	pHead->bValid = 0;
}


class CMemoryPool
{
public:
	CMemoryPool( );
	~CMemoryPool( );

	void Create( int nMax );
	void Destroy(  );

	void InitPoolData( int nIndex, int nNum, int nDataSize );

	void * GetMem( size_t size );
	void ReleaseMem( void * p );

private:
	CMemoryGroup * m_pPoolData;
	int m_nMax;
};

CMemoryPool::CMemoryPool( )
{
	m_pPoolData = NULL;
	m_nMax = 0;
}

CMemoryPool::~CMemoryPool( )
{
	Destroy( );
}

void CMemoryPool::Create( int nMax )
{
	m_nMax = nMax;
	m_pPoolData = ( CMemoryGroup * )malloc( sizeof( CMemoryGroup ) * m_nMax );
	for( int i = 0; i < m_nMax; i++ )
		new( &(m_pPoolData)[i] )CMemoryGroup;
}

void CMemoryPool::Destroy(  )
{
	if( m_pPoolData )
	{
		for( int i = 0; i < m_nMax; i++ )
			m_pPoolData[i].Destroy( );
		free( m_pPoolData );
		m_pPoolData = NULL;
	}
	m_nMax = 0;
}

void CMemoryPool::InitPoolData( int nIndex, int nNum, int nDataSize )
{
	Assert( nIndex >= 0 && nIndex < m_nMax );
	m_pPoolData[nIndex].Create( nNum, nDataSize );
}

void * CMemoryPool::GetMem( size_t size )
{
	void * p = NULL;
	CMemoryGroup * pData;
	for( int i = 0; i < m_nMax; i++ )
	{
		pData = &m_pPoolData[i];
		if( size < pData->m_nDataSize )
		{
			p = pData->GetMem( );
			break;
		}
	}
	if( p == NULL )
		p = analyzealloc( size );
	return p;
}

void CMemoryPool::ReleaseMem( void * p )
{
	CMemoryGroup * pData;
	for( int i = 0; i < m_nMax; i++ )
	{
		pData = &m_pPoolData[i];
		if( p >= &pData->m_pGroupData[0] && 
			p <= &pData->m_pGroupData[pData->m_nMax*pData->m_nDataSize-1] )
		{
			pData->ReleaseMem( p );
			return;
		}
	}
	analyzefree( p );
}
*/

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


void * analyzealloc( size_t size )
{
	NewNode * node = NULL;
	if( !MemSizeMap( ).empty( ) )
	{
		MemSizeMap_t::iterator iter = MemSizeMap( ).find( size );
		if( iter != MemSizeMap( ).end( ) )
		{
			iter->second->nCount++;
			if( iter->second->nMax < iter->second->nCount )
				iter->second->nMax = iter->second->nCount;
			goto newnew;
		}
	}

 	node = new NewNode;
	node->nSize = size;
	node->nCount++;
	if( node->nMax < node->nCount )
		node->nMax = node->nCount;
	MemSizeMap( ).insert( std::pair<int,NewNode*>( size, node ) );
newnew:
	g_nTotalSize += size;
	g_nNewCount++;
	g_nCurSize += size;
	g_nCurNewCount++;
	void * p = malloc( size + sizeof( int ) );
	*(int*)p = size;
	return ( (BYTE*)p + sizeof( int ) );
	return 0;
}

void * analyzerealloc( void * p, size_t size )
{
	NewNode *node = NULL;
	if( p )
	{
		p = (BYTE*)p - sizeof( int );

		if( !MemSizeMap( ).empty( ) )
		{
			MemSizeMap_t::iterator iter = MemSizeMap( ).find( *(int*)p );
			if( iter != MemSizeMap( ).end( ) )
			{
				iter->second->nCount--;
				g_nCurSize -= iter->second->nSize;
				g_nCurNewCount--;
			}
		}
	}

	if( !MemSizeMap( ).empty( ) )
	{
		MemSizeMap_t::iterator iter = MemSizeMap( ).find( size );
		if( iter != MemSizeMap( ).end( ) )
		{
			iter->second->nCount++;
			if( iter->second->nMax < iter->second->nCount )
				iter->second->nMax = iter->second->nCount;
			goto newnew;
		}
	}

	node = new NewNode;
	node->nSize = size;
	node->nCount++;
	if( node->nMax < node->nCount )
		node->nMax = node->nCount;
	MemSizeMap( ).insert( std::pair<int,NewNode*>( size, node ) );
newnew:
	g_nTotalSize += size;
	g_nNewCount++;
	g_nCurSize += size;
	g_nCurNewCount++;
	p = realloc( p, size + sizeof( int ) );
	*(int*)p = size;
	return ( (BYTE*)p + sizeof( int ) );
}

void analyzefree( void * p )
{
	if( p )
	{

		p = (BYTE*)p - sizeof( int );

		if( !MemSizeMap( ).empty( ) )
		{
			MemSizeMap_t::iterator iter = MemSizeMap( ).find( *(int*)p );
			if( iter != MemSizeMap( ).end( ) )
			{
				iter->second->nCount--;
				g_nCurSize -= iter->second->nSize;
				g_nCurNewCount--;
				goto newnew1;
			}
		}
		Assert( FALSE );
newnew1:;
		free( p );
	}
}

void initnew( )
{
#ifdef _ANALYZEMEMORY
#else
/*	extern BOOL g_bOnlyServer;
	if( g_bOnlyServer == 2 || g_bOnlyServer == 4 )
	{
		g_MemoryPool.Create( 21 );
		g_MemoryPool.InitPoolData( 0, 10000, 28 );
		g_MemoryPool.InitPoolData( 1, 2000, 32 );
		g_MemoryPool.InitPoolData( 2, 5000, 60 );
		g_MemoryPool.InitPoolData( 3, 100, 64 );
		g_MemoryPool.InitPoolData( 4, 40000, 160 );
		g_MemoryPool.InitPoolData( 5, 2000, 172 );
		g_MemoryPool.InitPoolData( 6, 50, 256 );
		g_MemoryPool.InitPoolData( 7, 2000, 512 );
		g_MemoryPool.InitPoolData( 8, 10, 768 );
		g_MemoryPool.InitPoolData( 9, 200, 1024 );
		g_MemoryPool.InitPoolData( 10, 100, 1280 );
		g_MemoryPool.InitPoolData( 11, 1000, 1536 );
		g_MemoryPool.InitPoolData( 12, 1000, 1792 );
		g_MemoryPool.InitPoolData( 13, 5000, 2048 );
		g_MemoryPool.InitPoolData( 14, 50, 2156 );
		g_MemoryPool.InitPoolData( 15, 2000, 2304 );
		g_MemoryPool.InitPoolData( 16, 100, 2816 );
		g_MemoryPool.InitPoolData( 17, 400, 3072 );
		g_MemoryPool.InitPoolData( 18, 300, 3584 );
		g_MemoryPool.InitPoolData( 19, 5000, 4154 );
		g_MemoryPool.InitPoolData( 20, 50, 4512 );
	}
	else
	{
		g_MemoryPool.Create( 19 );
		g_MemoryPool.InitPoolData( 0, 12000, 3 );
		g_MemoryPool.InitPoolData( 1, 10000, 12 );
		g_MemoryPool.InitPoolData( 2, 1000, 28 );
		g_MemoryPool.InitPoolData( 3, 5000, 32 );
		g_MemoryPool.InitPoolData( 4, 1500, 56 );
		g_MemoryPool.InitPoolData( 5, 400, 68 );
		g_MemoryPool.InitPoolData( 6, 300, 88 );
		g_MemoryPool.InitPoolData( 7, 2000, 96 );
		g_MemoryPool.InitPoolData( 8, 500, 159 );
		g_MemoryPool.InitPoolData( 9, 4000, 172 );
		g_MemoryPool.InitPoolData( 10, 300, 236 );
		g_MemoryPool.InitPoolData( 11, 400, 256 );
		g_MemoryPool.InitPoolData( 12, 40, 448 );
		g_MemoryPool.InitPoolData( 13, 1200, 512 );
		g_MemoryPool.InitPoolData( 14, 80, 1301 );
		g_MemoryPool.InitPoolData( 15, 350, 1536 );
		g_MemoryPool.InitPoolData( 16, 1000, 3584 );
		g_MemoryPool.InitPoolData( 17, 120, 4556 );
		g_MemoryPool.InitPoolData( 18, 10, 8000 );
	}*/
/*
	int pnMultiCount[] = { 25000, 10000, 800, 11000, 28000, 10200, 500, 140, 290,
		290, 4850, 200, 150, 2250, 300, 29500, 1600, 150, 160, 2500, 25, 54 };
	int pnMultiSize[] = { 4, 12, 24, 28, 32, 35, 40, 44, 48, 56, 60, 68, 96, 120,
		155, 160, 172, 800, 1239, 2156, 4556, 8000 };
	
	int pnSingleCount[] = { 12000, 10000, 1000, 5000, 1500, 400, 200, 2000, 500, 4000,
		300, 400, 40, 1200, 80, 350, 1000, 120, 10 };
	int pnSingleSize[] = { 3, 12, 28, 32, 56, 68, 88, 96, 159, 172, 236, 256, 448, 
		512, 1301, 1536, 3584, 4556, 8000 };
	
	extern BOOL g_bOnlyServer;
	if( g_bOnlyServer == 2 || g_bOnlyServer == 4 )
		g_MemPool.Build( sizeof( pnMultiCount ) / sizeof( int ), pnMultiSize, pnMultiCount );
	else
		g_MemPool.Build( sizeof( pnSingleCount ) / sizeof( int ), pnSingleSize, pnSingleCount );*/
#endif
}

void uninitnew( )
{
	reportstate( );

	MemSizeMap_t::iterator iter = MemSizeMap( ).begin( );
	while( iter != MemSizeMap( ).end( ) )
	{
		delete iter->second;
		iter++;
	}
	MemSizeMap( ).erase( MemSizeMap( ).begin( ), MemSizeMap( ).end( ) );
}

void reportstate( )
{
#ifndef _ANALYZEMEMORY
	Log( "/////////////////////Pool Mode/////////////////////\n", g_nTotalSize, g_nNewCount );
#endif
	Log( "TotalSize : %d\tCount : %d", g_nTotalSize, g_nNewCount );
	Log( "CurSize : %d\tCurCount : %d", g_nCurSize, g_nCurNewCount );

	MemSizeMap_t::iterator iter = MemSizeMap( ).begin( );
	while( iter != MemSizeMap( ).end( ) )
	{
		Log( "Size:\t%d\tCount:\t%d\tMax:\t%d\t\t%2.2f%%\t%2.2f%%", iter->second->nSize, iter->second->nCount, iter->second->nMax, 
			( float )( iter->second->nCount * iter->second->nSize ) * 100 / ( float )g_nCurSize, 
			( float )( iter->second->nMax * iter->second->nSize ) * 100 / ( float )g_nTotalSize );
		iter++;
	}
}

void * mynew( size_t size )
{
#ifdef _ANALYZEMEMORY
	return analyzealloc( size );
#else
//	return malloc( size );
//	return g_MemoryPool.GetMem( size );
//	return g_MemPool.GetMem( size );
	size_t newsz = size + sizeof(size_t);
	void* ptr = g_Allocator.allocate(newsz);
	*(size_t*)ptr = newsz;
	return (char*)ptr + sizeof(size_t);
#endif
}

void * myrenew( void * p, size_t size )
{
	if( !p )
		return mynew( size );

	size_t newsz = size + sizeof(size_t);
	void * ptr = (char*)p - sizeof(size_t);
	size_t oldsize = *(size_t*)ptr;

	void* newptr = g_Allocator.reallocate( ptr, oldsize, newsz );
	*(size_t*)newptr = newsz;
	return (char*)newptr + sizeof(size_t);
}

void mydelete( void * p )
{
#ifdef _ANALYZEMEMORY
	analyzefree( p );
#else
//	free( p );
//	g_MemoryPool.ReleaseMem( p );
//	g_MemPool.ReturnMem( p );
	void * ptr = (char*)p - sizeof(size_t);
	size_t size = *(size_t*)ptr;
	g_Allocator.deallocate(ptr, size);
#endif
}

MYCHAINITEM *    ChainRemoveCurrent( CHAINHEADER * pChain )
{
	  MYCHAINITEM *    pPreviousCurrent = (MYCHAINITEM * )pChain->Current( );

	  if (pPreviousCurrent)
	  {
		  MYCHAINITEM *    pReturn = (MYCHAINITEM * )pChain->Current( )->Next();
  		/***********************************
		IMPORTANT!!!
		After call DisConnect() pCurrent will be chged
		************************************/
		  pChain->Current( )->DisConnect();
		  QS_DELETE( pPreviousCurrent );
		  return  pReturn;
	  }
	  else
		   return   NULL;
}

void    ChainRemoveAll( CHAINHEADER * pChain )
{
	pChain->First();
	while(ChainRemoveCurrent(pChain)){
	  ;
	}
	pChain->SetNum( 0 );
}
