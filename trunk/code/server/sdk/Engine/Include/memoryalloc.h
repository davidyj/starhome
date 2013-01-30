#ifndef UTILITY_MEMORY_ALLOC_H
#define UTILITY_MEMORY_ALLOC_H
#include "EngineDefine.h"
#include "dbg.h"
#include "utlmap.h"
#include "GLock.h"
#include "memalloc.h"


#define MEMORY	int		//内存地址

// 管理内存分配情况的结果体
struct s_memory_chunk 
{
	//MEMORY		indexAddress;	//返回给上层使用的内存标识
	uintptr_t		startAddress;	//内存实际开始的位置
	//uintptr_t		endAddress;		//内存实际结束的位置
	size_t			memorySize;		//内存的大小
	char			fileName[256];		//分配内存的文件
	int			fileLine;		//分配文件的函数
	s_memory_chunk* preChunk;	//前一个chunck
	s_memory_chunk* nextChunk;	//后一个chunck

	void Init(){
		//indexAddress = 0;			//返回给上层使用的内存标识
		startAddress = NULL;	//内存实际开始的位置
		//endAddress;			//内存实际结束的位置
		memorySize = 0;			//内存的大小
		fileName[0] = '\0';		//分配内存的文件
		fileLine = 0;			//分配文件的函数
		preChunk = NULL;		//前一个chunck
		nextChunk= NULL;		//后一个chunck
	}
};

typedef CUtlMap<uintptr_t,s_memory_chunk*,int>				CMemoryChunkMap;


// 内存的分配器
class ENGINE_CLASS  CMemoryAlloc
{
private:
	CMemoryAlloc();
	~CMemoryAlloc();

public:
	//
	static CMemoryAlloc * getSingle(){
		static CMemoryAlloc g_instance;
		return &g_instance;
	}
	
public:
	bool Init(size_t nSize);

	//void* Alloc(size_t nSize);
	//void  Free(void* pSize);

	void* Alloc(size_t nSize,LPCSTR filename = NULL,int nLine = 0);
	void Free(void* p,LPCSTR filename = NULL,int nLine = 0);
	
	void clearup();						//内存整理 
	inline float getMemoryUsedPercent() {return (float)m_memoryUsedSize/(float)m_memorypoolSize*100.00;}
	
	s_memory_chunk* findChunk(MEMORY Index);//

	inline void lock()	{return;m_Lock.LOCK();}
	inline void unlock(){return;m_Lock.UNLOCK();}
protected:
	s_memory_chunk* getChunk(size_t nSize);	//查找适合的空间alloc新内存
	s_memory_chunk*	findChunk(void* p);			
	
	inline bool isValidAddress(uintptr_t address){ if( address >= m_memorypool && address < (m_memorypool + m_memorypoolSize))return true;return false;}

private:
	uintptr_t	m_memorypool;					//内存池地址
	size_t		m_memorypoolSize;
	int			m_memoryChunkCount;				//分配内存计数
	UINT		m_memoryUsedSize;				//已经用掉的内存大小
	CMemoryChunkMap	m_MemoryChunkMap;			
	CGLock		m_Lock;
	
	s_memory_chunk* m_pMemoryChunkBegin;
	s_memory_chunk*	m_pCurrentChunk;			//当前分配的指针，每次分配从这个节点开始
};


//
inline void _G_strcpy(MEMORY pDest,MEMORY pSrc)
{
	s_memory_chunk* pDestChunk = CMemoryAlloc::getSingle()->findChunk(pDest);
	s_memory_chunk* pSrcChunk = CMemoryAlloc::getSingle()->findChunk(pSrc);
	if(pDestChunk && pSrcChunk ){
		strcpy((char*)pDestChunk->startAddress,(const char *)pDestChunk->startAddress);
	}
	
}
//inline void _G_strncpy();
//inline void _G_memcpy();
//inline void _G_memset();

#if 0
static void* __cdecl operator new(size_t nSize)
{	
	CMemoryAlloc::getSingle()->lock();
	void* p = CMemoryAlloc::getSingle()->Alloc(nSize);
	CMemoryAlloc::getSingle()->unlock();
	return p;
}

static void __cdecl operator delete(void* p)
{
	CMemoryAlloc::getSingle()->lock();
	CMemoryAlloc::getSingle()->Free(p);
	CMemoryAlloc::getSingle()->unlock();
}

static void* __cdecl operator new[](size_t cb)
{
	CMemoryAlloc::getSingle()->lock();
	void* p = CMemoryAlloc::getSingle()->Alloc(cb);
	CMemoryAlloc::getSingle()->unlock();
	return p;
	//return Plat_Alloc( cb );
}

static void __cdecl operator delete[](void* p)
{
	CMemoryAlloc::getSingle()->lock();
	CMemoryAlloc::getSingle()->Free(p);
	CMemoryAlloc::getSingle()->unlock();
	//Plat_Free( p );
}

static void* __cdecl operator new(size_t nSize, LPCSTR lpszFileName, int nLine)
{
	CMemoryAlloc::getSingle()->lock();
	void* p = CMemoryAlloc::getSingle()->Alloc(nSize,lpszFileName,nLine);
	CMemoryAlloc::getSingle()->unlock();
	return p;	
}

static void __cdecl operator delete(void* p, LPCSTR lpszFileName, int nLine)
{
	CMemoryAlloc::getSingle()->lock();
	CMemoryAlloc::getSingle()->Free(p,lpszFileName,nLine);
	CMemoryAlloc::getSingle()->unlock();
}

static void* __cdecl operator new[](size_t nSize, LPCSTR lpszFileName, int nLine)
{
	CMemoryAlloc::getSingle()->lock();
	void* p = CMemoryAlloc::getSingle()->Alloc(nSize,lpszFileName,nLine);
	CMemoryAlloc::getSingle()->unlock();
	return p;
	//Log(" %s %d alloc memory size = %d",lpszFileName,nLine,nSize);
	//return new( nSize );
}

static void __cdecl operator delete[](void* p, LPCSTR lpszFileName, int nLine)
{
	CMemoryAlloc::getSingle()->lock();
	CMemoryAlloc::getSingle()->Free(p,lpszFileName,nLine);	
	CMemoryAlloc::getSingle()->unlock();
}

static bool InitMemorySize(size_t nSize)
{
	if(!CMemoryAlloc::getSingle()->Init(nSize)){
		Log("内存分配失败\n");
		return false;
	}
	return true;
}
#endif 
static float getMemoryUsedPercent(){
	return 0;
	return CMemoryAlloc::getSingle()->getMemoryUsedPercent();
}
//#define NEW		new(__FILE__,__LINE__)

#define NEW new

#if 0

class ENGINE_CLASS CTbbMemoryMalloc
{
public:
	CTbbMemoryMalloc(){};
	~CTbbMemoryMalloc(){};
	void * TbbMalloc(size_t size);
	void * TbbRealloc(void* ptr, size_t size);
	void TbbFree(void* ptr);
};

static CTbbMemoryMalloc*  g_TbbMemoryMalloc = new CTbbMemoryMalloc;

static void* operator new(size_t size)
{
	return g_TbbMemoryMalloc->TbbMalloc(size);
}

static void operator delete(void* ptr)
{
	g_TbbMemoryMalloc->TbbFree(ptr);
}

static void* operator new[] (size_t size)
{
	return g_TbbMemoryMalloc->TbbMalloc(size);
}

static void operator delete[] (void* ptr)
{
	g_TbbMemoryMalloc->TbbFree(ptr);
}

#ifdef Plat_Alloc
#undef Plat_Alloc
#endif

#ifdef Plat_Realloc
#undef Plat_Realloc
#endif

#ifdef Plat_Free
#undef Plat_Free
#endif

static void* Tbb_Plat_Alloc( size_t size )
{
	return g_TbbMemoryMalloc->TbbMalloc(size);
}

static void* Tbb_Plat_Realloc( void *ptr, size_t size )
{
	return g_TbbMemoryMalloc->TbbRealloc(ptr, size);
}

static void Tbb_Plat_Free( void *ptr )
{
	g_TbbMemoryMalloc->TbbFree(ptr);
}

#define Plat_Alloc( size ) Tbb_Plat_Alloc( size )
#define	Plat_Realloc( ptr, size ) Tbb_Plat_Realloc( ptr, size )
#define	Plat_Free( ptr ) Tbb_Plat_Free( ptr )

#endif

#ifndef _DEBUG

#if !defined(X64_WIN) && !defined(FREEBSD) 

static void* operator new(size_t size)
{
	return MemAlloc( ).Alloc(size);
}

static void operator delete(void* ptr)
{
	MemAlloc( ).Free(ptr);
}

static void* operator new[] (size_t size)
{
	return MemAlloc( ).Alloc(size);
}

static void operator delete[] (void* ptr)
{
	MemAlloc( ).Free(ptr);
}

#endif //X64_WIN
#endif //_DEBUG

#endif //UTILITY_MEMORY_ALLOC_H


