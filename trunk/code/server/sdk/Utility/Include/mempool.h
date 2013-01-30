//=========== (C) Copyright 2000 Valve, L.L.C. All rights reserved. ===========
//
// The copyright to the contents herein is the property of Valve, L.L.C.
// The contents may be used and/or copied only with the written permission of
// Valve, L.L.C., or in accordance with the terms and conditions stipulated in
// the agreement/contract under which the contents have been supplied.
//
// Purpose: 
//
// $Workfile:     $
// $Date:         $
//
//-----------------------------------------------------------------------------
// $Log: $
//
// $NoKeywords: $
//=============================================================================

#ifndef MEMPOOL_H
#define MEMPOOL_H
#include "platform.h"

// by zhao 2010-1-13	
#ifdef _MEM_FLAG 
#pragma  message("macro _MEM_FLAG defined")
#endif //_MEM_FLAG

//-----------------------------------------------------------------------------
// Purpose: Optimized pool memory allocator
//-----------------------------------------------------------------------------

typedef void (*MemoryPoolReportFunc_t)( char const* pMsg, ... );

class CMemoryPool
{
public:
	// Ways the memory pool can grow when it needs to make a new blob.
	enum
	{
		GROW_NONE=0,		// Don't allow new blobs.
		GROW_FAST=1,		// New blob size is numElements * (i+1)  (ie: the blocks it allocates
							// get larger and larger each time it allocates one).
		GROW_SLOW=2			// New blob size is numElements.
	};

	// by zhao 2010-1-13	
#ifdef _MEM_FLAG  
	//内存使用标记
	enum
	{
		Flag_Free	=0,		//空闲
		Flag_Use	=1,		//已使用
		Flag_Erro	=2,		//错误
	};
#endif //_MEM_FLAG  

	CMemoryPool(int blockSize, int numElements, int growMode = GROW_FAST);
	~CMemoryPool();

	void*		Alloc();	// Allocate the element size you specified in the constructor.
	void*		Alloc( unsigned int amount );
	void		Free(void *pMem);
	void		Clear();	// Frees everything
	inline int  BlobAllocCount(){ return m_BlocksAllocated; } // Add by David 2008-3-25
	inline int  BlobNums()		{ return m_NumBlobs; }		// Add by David 2009-2-11

// by zhao 2010-1-13	
#ifdef _MEM_FLAG  
	//得到标记
	int		GetFlag( void *memBlock );
	//内存是否空闲
	inline BOOL IsMemFree(void *memBlock ) {return Flag_Free==GetFlag(memBlock);};
#endif //_MEM_FLAG

	// Error reporting... 
	static void SetErrorReportFunc( MemoryPoolReportFunc_t func );
	

private:
	class CBlob
	{
	public:
		CBlob	*m_pPrev, *m_pNext;
		int		m_NumBytes;		// Number of bytes in this blob.
		char	m_Data[1];
	};


	// Resets the pool
	void		Init();
	void		AddNewBlob();
	void		ReportLeaks();


private:

	int			m_BlockSize;
	int			m_BlocksPerBlob;

	int			m_GrowMode;	// GROW_ enum.

	// FIXME: Change m_ppMemBlob into a growable array?
	CBlob			m_BlobHead;	
	void			*m_pHeadOfFreeList;
	int				m_BlocksAllocated;
	int				m_PeakAlloc;
	unsigned short	m_NumBlobs;

	CPlatformCS		m_MemCS;

	static MemoryPoolReportFunc_t g_ReportFunc;
};


//-----------------------------------------------------------------------------
// Wrapper macro to make an allocator that returns particular typed allocations
// and construction and destruction of objects.
//-----------------------------------------------------------------------------
template< class T >
class CClassMemoryPool : public CMemoryPool
{
public:
	CClassMemoryPool(int numElements, int growMode = GROW_FAST)	:
		CMemoryPool( sizeof(T), numElements, growMode ) {}

	T*		Alloc();
	void	Free( T *pMem );
	// add by majin
	T*		AllocEx();
};


template< class T >
T* CClassMemoryPool<T>::Alloc()
{
	T *pRet = (T*)CMemoryPool::Alloc();
	if ( pRet )
	{
		Construct( pRet );
	}
	return pRet;

}
// add by majin 
template< class T >
T* CClassMemoryPool<T>::AllocEx()
{
	T *pRet = (T*)CMemoryPool::Alloc();
//	if ( pRet )
//	{
//		(pRet)::T();
//	}
	return pRet;
}

template< class T >
void CClassMemoryPool<T>::Free(T *pMem)
{
	//内存使用标记 by zhao 2010-1-13
#ifdef _MEM_FLAG
	//if(Flag_Free==GetFlag(pMem))
	//{
	//	AssertMsg(0,"不能释放未使用的内存(该内存可能已经释放或从未使用)");
	//	return;
	//}
#endif //_MEM_FLAG
	if ( pMem )
	{
		Destruct( pMem );
	}

	CMemoryPool::Free( pMem );
}


//-----------------------------------------------------------------------------
// Macros that make it simple to make a class use a fixed-size allocator
// Put DECLARE_FIXEDSIZE_ALLOCATOR in the private section of a class,
// Put DEFINE_FIXEDSIZE_ALLOCATOR in the CPP file
//-----------------------------------------------------------------------------
#define DECLARE_FIXEDSIZE_ALLOCATOR( _class )									\
   public:																		\
      inline void* operator new( size_t size, void * p ) { return p; }   \
	  inline void  operator delete( void *, void * ){return; } \
	  inline void* operator new( size_t size ) { return s_Allocator.Alloc(size); }   \
      inline void* operator new( size_t size, int nBlockUse, const char *pFileName, int nLine ) { return s_Allocator.Alloc(size); }   \
      inline void  operator delete( void* p ) { s_Allocator.Free(p); }		\
      inline void  operator delete( void* p, int nBlockUse, const char *pFileName, int nLine ) { s_Allocator.Free(p); }   \
  	  static void ReleaseMemPool(){ s_Allocator.Clear(); }		\
  private:																		\
      static   CMemoryPool   s_Allocator
    
#define DECLARE_FIXEDSIZE_ALLOCATOR_EX( _class )									\
   public:																		\
   inline void* operator new( size_t size ) { return s_Allocator.Alloc(size); }   \
   inline void* operator new( size_t size, int nBlockUse, const char *pFileName, int nLine ) { return s_Allocator.Alloc(size); }   \
   inline void  operator delete( void* p ) { s_Allocator.Free(p); }		\
   inline void  operator delete( void* p, int nBlockUse, const char *pFileName, int nLine ) { s_Allocator.Free(p); }   \
   static void ReleaseMemPool(){ s_Allocator.Clear(); }		\
  public:																		\
  static   CMemoryPool   s_Allocator

#define DEFINE_FIXEDSIZE_ALLOCATOR( _class, _initsize, _grow )					\
   CMemoryPool   _class::s_Allocator(sizeof(_class), _initsize, _grow)


//-----------------------------------------------------------------------------
// Macros that make it simple to make a class use a fixed-size allocator
// This version allows us to use a memory pool which is externally defined...
// Put DECLARE_FIXEDSIZE_ALLOCATOR_EXTERNAL in the private section of a class,
// Put DEFINE_FIXEDSIZE_ALLOCATOR_EXTERNAL in the CPP file
//-----------------------------------------------------------------------------

#define DECLARE_FIXEDSIZE_ALLOCATOR_EXTERNAL( _class, _allocator )				\
   public:																		\
      inline void* operator new( size_t size )  { return s_pAllocator->Alloc(size); }   \
      inline void* operator new( size_t size, int nBlockUse, const char *pFileName, int nLine )  { return s_pAllocator->Alloc(size); }   \
      inline void  operator delete( void* p )   { s_pAllocator->Free(p); }		\
   private:																		\
      static   CMemoryPool*   s_pAllocator
    
#define DEFINE_FIXEDSIZE_ALLOCATOR_EXTERNAL( _class, _allocator )				\
   CMemoryPool*   _class::s_pAllocator = _allocator

#endif // MEMPOOL_H
