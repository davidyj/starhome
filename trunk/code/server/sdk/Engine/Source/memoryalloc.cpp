#include "..\stdafx.h"
#include "memoryalloc.h"
#include "dbg.h"

#define REMOVE_MEMORY_CHUNK(chunk)				\
	if(chunk)									\
	{											\
		if(chunk->preChunk)						\
		{										\
			chunk->preChunk->nextChunk = chunk->nextChunk;\
		}										\
		else									\
		{										\
			CMemoryAlloc::getSingle()->m_pMemoryChunkBegin = chunk->nextChunk;\
		}										\
		if(chunk->nextChunk)					\
		{										\
			chunk->nextChunk->preChunk = chunk->preChunk;\
		}										\
	}

#define FOR_EACH_MEMORY_CHUNK(chunk_begin,chunk)	\
	for( s_memory_chunk* chunk = chunk_begin;chunk != NULL;chunk = chunk->nextChunk)


// 获得适合内存大小的一片内存空间
#define GET_SIZE_MEMEORY( chunk_begin,chunk,nSize ) \
	for( s_memory_chunk* chunk = chunk_begin ; chunk != NULL;chunk = chunk->nextChunk) \
	{													\
		AssertMsg(chunk->startAddress,"地址错误!");		\
		if(chunk->nextChunk)						   \
		{												\
			if((chunk->startAddress + chunk->memorySize + nSize) < chunk->nextChunk->startAddress )	\
				return chunk;							\
		}												\
		else					\
		{						\
			if( isValidAddress( chunk->startAddress + chunk->memorySize + nSize) )\
			{					\
				return chunk;	\
			}					\
		}						\
	}
///////////////////////////////////////////////////////////////////////
//
CMemoryAlloc::CMemoryAlloc()
{
	m_memorypool = 0;
	m_memorypoolSize = 0;
	m_memoryChunkCount=0;
	m_memoryUsedSize = 0;
	m_pCurrentChunk = m_pMemoryChunkBegin = NULL;	
	SetDefLessFunc(m_MemoryChunkMap);
}

CMemoryAlloc::~CMemoryAlloc()
{
	if(m_memorypool)
		free((void*)m_memorypool);
	m_memorypool = 0;
}

bool CMemoryAlloc::Init(size_t nSize)
{
	m_memorypool = (uintptr_t)malloc(nSize);
	AssertMsg(m_memorypool,"内存分配失败！");
	if(!m_memorypool)
		return false;
	m_memorypoolSize = nSize;
	return true;
}

// 找到适合大小的内存区域
s_memory_chunk* CMemoryAlloc::getChunk(size_t nSize)
{
	//从当前chunk开始遍历
	//GET_SIZE_MEMEORY( m_CurrentChunk,chunk ,nSize)		
	for( s_memory_chunk* chunk = m_pCurrentChunk ; chunk != NULL;chunk = chunk->nextChunk) 
	{							
		AssertMsg(chunk->startAddress,"地址错误!");
		if(chunk->nextChunk)						   
		{												
			if((chunk->startAddress + chunk->memorySize + nSize) < chunk->nextChunk->startAddress )	
				return chunk;							
		}												
		else					
		{						
			if( isValidAddress( chunk->startAddress + chunk->memorySize + nSize) )
			{					
				return chunk;	
			}					
		}						
	}
	

	//从最开始便利
	//GET_SIZE_MEMEORY(m_MemoryChunkBegin,chunk,nSize)	
	for( s_memory_chunk* chunk = m_pMemoryChunkBegin ; chunk != NULL;chunk = chunk->nextChunk) 
	{													
		AssertMsg(chunk->startAddress,"地址错误!");		
		if(chunk->nextChunk)						   
		{												
			if((chunk->startAddress + chunk->memorySize + nSize) < chunk->nextChunk->startAddress )	
				return chunk;							
		}												
		else					
		{						
			if( isValidAddress( chunk->startAddress + chunk->memorySize + nSize) )
			{					
				return chunk;	
			}					
		}						
	}
	return NULL;
}

// 根据内存地址从全局范围内查找 chunk 结构
s_memory_chunk* CMemoryAlloc::findChunk(void *p)
{	
	FOR_EACH_MEMORY_CHUNK(m_pMemoryChunkBegin,chunk)
	{			
		if(chunk)
		{
			if(chunk->startAddress == (uintptr_t)p)
				return chunk;
		}
	}
	return NULL;
}

s_memory_chunk* CMemoryAlloc::findChunk(MEMORY index)
{
	
	FOR_EACH_MEMORY_CHUNK(m_pMemoryChunkBegin,chunk)
	{			
		if(chunk)
		{
			//if(chunk->indexAddress = index)
			//	return chunk;
		}
	}
	return NULL;
}

#define MEMORY_POOL_SIZE 1024*1024*400
void* CMemoryAlloc::Alloc(size_t nSize,LPCSTR filename,int nLine)
{	
	if(m_memorypool == NULL)
	{
		m_memorypool = (uintptr_t)malloc(MEMORY_POOL_SIZE);
		AssertMsg(m_memorypool,"内存分配失败！");
		if(!m_memorypool)
			return NULL;
		m_memorypoolSize = MEMORY_POOL_SIZE;
	}

	s_memory_chunk* pNewChunk = NULL;
	
	//遍历内存池，找到适合大小的size
	if(m_pMemoryChunkBegin == NULL)
	{	//第一个元素		
		pNewChunk = (s_memory_chunk*)malloc ( sizeof(s_memory_chunk) );
		if(!pNewChunk)
			return NULL;
		pNewChunk->Init();
		pNewChunk->startAddress = m_memorypool;
		pNewChunk->memorySize = nSize;			
		
		
		//更新内存使用率
		m_memoryUsedSize+=nSize;
		
		m_pMemoryChunkBegin = pNewChunk;				
		
		// 设置分配的当前的指针
		m_pCurrentChunk = m_pMemoryChunkBegin;
	}
	else
	{	//有其他元素，需要遍历查找适合的元素	
		s_memory_chunk* pPreChunk = getChunk(nSize);
		if(pPreChunk)
		{			
			pNewChunk = (s_memory_chunk*) malloc ( sizeof(s_memory_chunk) );
			if(!pNewChunk)
				return NULL;			
			pNewChunk->Init();
			pNewChunk->startAddress = pPreChunk->startAddress + pPreChunk->memorySize;			
			pNewChunk->memorySize = nSize;			

			pNewChunk->preChunk = pPreChunk;

			pNewChunk->nextChunk = pPreChunk->nextChunk;

			if(pPreChunk->nextChunk)
				pPreChunk->nextChunk->preChunk = pNewChunk;			

			pPreChunk->nextChunk = pNewChunk;			

			//更新内存使用率
			m_memoryUsedSize += nSize;			
		}
	}			

	if( !pNewChunk|| !pNewChunk->startAddress )
	{		
		AssertMsg(pNewChunk->startAddress,"内存不足!");
		free( pNewChunk );
		pNewChunk = NULL;
		return NULL;
	}
	
	++m_memoryChunkCount;
	
	//set file name & line
	if(filename != NULL){	
		strcpy(pNewChunk->fileName,filename);
		pNewChunk->fileLine = nLine;
	}

	//设置当前游标的位置
	if(m_pCurrentChunk->startAddress < pNewChunk->startAddress)
		m_pCurrentChunk = pNewChunk;
	//m_CurrentChunk = pTempChunk;

	//insert in map
	m_MemoryChunkMap.Insert(pNewChunk->startAddress,pNewChunk);

	return (void*)pNewChunk->startAddress;
}


void CMemoryAlloc::Free(void* pMemory,LPCSTR filename,int nLine)
{
	//Log("Memory Free %d\n",pMemory);
	//s_memory_chunk* p = findChunk(pMemory);
	int index = m_MemoryChunkMap.Find((uintptr_t)pMemory);
	if(!m_MemoryChunkMap.IsValidIndex(index)){
		Log("Memory Alloc Not Free %d\n",pMemory);
		return;
	}
	s_memory_chunk* p = m_MemoryChunkMap[index];
	if(!p){
		Log("Memory Alloc Not Free \n");
		return;
	}

	//从map中删除
	m_MemoryChunkMap.RemoveAt(index);	

	--m_memoryChunkCount;

	//更新内存使用率
	m_memoryUsedSize -= p->memorySize;

	// 重新设定current point的位置 
	// 如果有连续两次free，有可能出问题，所以必须判定 
	if( m_pCurrentChunk->startAddress >= p->startAddress && p->preChunk)
		m_pCurrentChunk = p->preChunk;

	//从 链表 中删除
	REMOVE_MEMORY_CHUNK(p)		

	free(p);
	p = NULL;
}
/*
void* CMemoryAlloc::Alloc(size_t nSize,LPCSTR filename,int nLine)
{	
	//Log("%s %d alloc memroy %d \n",filename,nLine,nSize);
	return Alloc(nSize);
}

void CMemoryAlloc::Free(void* p,LPCSTR filename,int nLine)
{
	Free(p);
}
*/
#if 0
void* CTbbMemoryMalloc::TbbMalloc(size_t size)
{
	if (size == 0)
	{
		size =1;
	}

	void *ptr = scalable_malloc(size);

	if (ptr)
	{
		return ptr;
	}
	else
	{
		return NULL;
	}
}

void CTbbMemoryMalloc::TbbFree(void* ptr)
{
	if (ptr)
	{
		scalable_free(ptr);
	}
}

void* CTbbMemoryMalloc::TbbRealloc(void* ptr, size_t size)
{
	if (size == 0)
	{
		size = 1;
	}

	if (ptr)
	{
		return scalable_realloc(ptr, size);
	}
	else
	{
		return scalable_malloc(size);
	}
}
#endif