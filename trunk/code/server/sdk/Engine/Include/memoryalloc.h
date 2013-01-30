#ifndef UTILITY_MEMORY_ALLOC_H
#define UTILITY_MEMORY_ALLOC_H
#include "EngineDefine.h"
#include "dbg.h"
#include "utlmap.h"
#include "GLock.h"
#include "memalloc.h"


#define MEMORY	int		//�ڴ��ַ

// �����ڴ��������Ľ����
struct s_memory_chunk 
{
	//MEMORY		indexAddress;	//���ظ��ϲ�ʹ�õ��ڴ��ʶ
	uintptr_t		startAddress;	//�ڴ�ʵ�ʿ�ʼ��λ��
	//uintptr_t		endAddress;		//�ڴ�ʵ�ʽ�����λ��
	size_t			memorySize;		//�ڴ�Ĵ�С
	char			fileName[256];		//�����ڴ���ļ�
	int			fileLine;		//�����ļ��ĺ���
	s_memory_chunk* preChunk;	//ǰһ��chunck
	s_memory_chunk* nextChunk;	//��һ��chunck

	void Init(){
		//indexAddress = 0;			//���ظ��ϲ�ʹ�õ��ڴ��ʶ
		startAddress = NULL;	//�ڴ�ʵ�ʿ�ʼ��λ��
		//endAddress;			//�ڴ�ʵ�ʽ�����λ��
		memorySize = 0;			//�ڴ�Ĵ�С
		fileName[0] = '\0';		//�����ڴ���ļ�
		fileLine = 0;			//�����ļ��ĺ���
		preChunk = NULL;		//ǰһ��chunck
		nextChunk= NULL;		//��һ��chunck
	}
};

typedef CUtlMap<uintptr_t,s_memory_chunk*,int>				CMemoryChunkMap;


// �ڴ�ķ�����
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
	
	void clearup();						//�ڴ����� 
	inline float getMemoryUsedPercent() {return (float)m_memoryUsedSize/(float)m_memorypoolSize*100.00;}
	
	s_memory_chunk* findChunk(MEMORY Index);//

	inline void lock()	{return;m_Lock.LOCK();}
	inline void unlock(){return;m_Lock.UNLOCK();}
protected:
	s_memory_chunk* getChunk(size_t nSize);	//�����ʺϵĿռ�alloc���ڴ�
	s_memory_chunk*	findChunk(void* p);			
	
	inline bool isValidAddress(uintptr_t address){ if( address >= m_memorypool && address < (m_memorypool + m_memorypoolSize))return true;return false;}

private:
	uintptr_t	m_memorypool;					//�ڴ�ص�ַ
	size_t		m_memorypoolSize;
	int			m_memoryChunkCount;				//�����ڴ����
	UINT		m_memoryUsedSize;				//�Ѿ��õ����ڴ��С
	CMemoryChunkMap	m_MemoryChunkMap;			
	CGLock		m_Lock;
	
	s_memory_chunk* m_pMemoryChunkBegin;
	s_memory_chunk*	m_pCurrentChunk;			//��ǰ�����ָ�룬ÿ�η��������ڵ㿪ʼ
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
		Log("�ڴ����ʧ��\n");
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


