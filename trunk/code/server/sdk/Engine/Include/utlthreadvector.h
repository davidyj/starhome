//
// utlthreadvector:
//		多线程安全的数组
//	注意：
//		支持多个线程的添加和删除，但是仅仅保证对该Vector的安全，
//		并不保证对Vector包含元素的 多线程安全！！！！！
//		david 2011-04-21 09:41
/////////////////////////////////////////////////
#ifndef UTL_THREAD_VECTOR_H
#define UTL_THREAD_VECTOR_H

#include "ThreadLibFunctions.h"
#include "platform.h"
using namespace ThreadLib;

template<class T> 
class CUtlThreadVector
{
public:
	CUtlThreadVector(){
		m_ItemTable = NULL;
		m_TableSize = 0;		
		m_writepoint = 0;
	}
	~CUtlThreadVector(){
		if(m_ItemTable)
		{
			delete m_ItemTable;
			m_ItemTable = NULL;
		}
	}

	inline bool init(UINT32 nSize);
	inline INT32 add(T* element);	
	inline void remove(UINT32 key);			//读取下一条记录，同时设置为空
	inline T*	get(UINT32 key);


protected:
	T**			m_ItemTable;		//数组指针
	UINT32		m_TableSize;		//数组的大小	
	LONG		m_writepoint;		//写指针
};

template<class T> 
inline bool CUtlThreadVector<T>::init(UINT32 nSize)
{
	m_TableSize = nSize;	
	m_ItemTable = (T**)Plat_Alloc(m_TableSize * sizeof(T*));
	if(!m_ItemTable)
		return false;
	memset(m_ItemTable,0,m_TableSize * sizeof(T*));
	return true;
}

//writepoint 保证了同一时刻不会用两个线程写东一个位置
//LocketSet保证了的写和删除的同步
template<class T> 
inline INT32 CUtlThreadVector<T>::add(T* element)
{	
	LONG temp = LocketAdd(&m_writepoint,1);
	if(m_ItemTable[temp] == NULL)
	{
		LocketSet((volatile LONG *)&m_ItemTable[temp],(LONG)element);
		return temp;
	}
	else
	{
		for(UINT32 i=0;i<m_TableSize;i++)
		{
			temp = LocketAdd(&m_writepoint,1);
			if(temp >= m_TableSize)
			{
				LocketSet(&m_writepoint,-1);
				continue;
			}
			if(m_ItemTable[temp] == NULL)
			{
				LocketSet((volatile LONG *)&m_ItemTable[temp], (LONG)element);
				return temp;
			}
		}
	}

	return -1;
}

// 支持多线程删除
template<class T> 
inline void CUtlThreadVector<T>::remove(UINT32 key)
{
	if(key<0 || key>=m_TableSize)
		return;
	LocketSet((volatile LONG *)&m_ItemTable[key],(LONG)NULL);
}

// 在这里是有安全隐患的
// 情况1：两个线程同时访问了同一个key的obj，其中一个如果对obj做了处理，那么就可能会一起崩溃
// David 2011-04-21 12:11
template<class T> 
inline T* CUtlThreadVector<T>::get(UINT32 key)
{
	if(key<0 || key>=m_TableSize)
		return NULL;
	return m_ItemTable[key] ;
}

#endif
