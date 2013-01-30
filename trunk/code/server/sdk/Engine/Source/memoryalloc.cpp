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


// ����ʺ��ڴ��С��һƬ�ڴ�ռ�
#define GET_SIZE_MEMEORY( chunk_begin,chunk,nSize ) \
	for( s_memory_chunk* chunk = chunk_begin ; chunk != NULL;chunk = chunk->nextChunk) \
	{													\
		AssertMsg(chunk->startAddress,"��ַ����!");		\
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
	AssertMsg(m_memorypool,"�ڴ����ʧ�ܣ�");
	if(!m_memorypool)
		return false;
	m_memorypoolSize = nSize;
	return true;
}

// �ҵ��ʺϴ�С���ڴ�����
s_memory_chunk* CMemoryAlloc::getChunk(size_t nSize)
{
	//�ӵ�ǰchunk��ʼ����
	//GET_SIZE_MEMEORY( m_CurrentChunk,chunk ,nSize)		
	for( s_memory_chunk* chunk = m_pCurrentChunk ; chunk != NULL;chunk = chunk->nextChunk) 
	{							
		AssertMsg(chunk->startAddress,"��ַ����!");
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
	

	//���ʼ����
	//GET_SIZE_MEMEORY(m_MemoryChunkBegin,chunk,nSize)	
	for( s_memory_chunk* chunk = m_pMemoryChunkBegin ; chunk != NULL;chunk = chunk->nextChunk) 
	{													
		AssertMsg(chunk->startAddress,"��ַ����!");		
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

// �����ڴ��ַ��ȫ�ַ�Χ�ڲ��� chunk �ṹ
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
		AssertMsg(m_memorypool,"�ڴ����ʧ�ܣ�");
		if(!m_memorypool)
			return NULL;
		m_memorypoolSize = MEMORY_POOL_SIZE;
	}

	s_memory_chunk* pNewChunk = NULL;
	
	//�����ڴ�أ��ҵ��ʺϴ�С��size
	if(m_pMemoryChunkBegin == NULL)
	{	//��һ��Ԫ��		
		pNewChunk = (s_memory_chunk*)malloc ( sizeof(s_memory_chunk) );
		if(!pNewChunk)
			return NULL;
		pNewChunk->Init();
		pNewChunk->startAddress = m_memorypool;
		pNewChunk->memorySize = nSize;			
		
		
		//�����ڴ�ʹ����
		m_memoryUsedSize+=nSize;
		
		m_pMemoryChunkBegin = pNewChunk;				
		
		// ���÷���ĵ�ǰ��ָ��
		m_pCurrentChunk = m_pMemoryChunkBegin;
	}
	else
	{	//������Ԫ�أ���Ҫ���������ʺϵ�Ԫ��	
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

			//�����ڴ�ʹ����
			m_memoryUsedSize += nSize;			
		}
	}			

	if( !pNewChunk|| !pNewChunk->startAddress )
	{		
		AssertMsg(pNewChunk->startAddress,"�ڴ治��!");
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

	//���õ�ǰ�α��λ��
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

	//��map��ɾ��
	m_MemoryChunkMap.RemoveAt(index);	

	--m_memoryChunkCount;

	//�����ڴ�ʹ����
	m_memoryUsedSize -= p->memorySize;

	// �����趨current point��λ�� 
	// �������������free���п��ܳ����⣬���Ա����ж� 
	if( m_pCurrentChunk->startAddress >= p->startAddress && p->preChunk)
		m_pCurrentChunk = p->preChunk;

	//�� ���� ��ɾ��
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