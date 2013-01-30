//	
// CBaseObjMgr: 2011-04-21 18:34 by David
//		1.支持多线程添加操作
//		2.支持多线程删除操作
//		3.单线程的便利操作
//		4.在多线程删除时要格外注意，避免重复删除同一个地址的操作，否则会留下隐患
//========================================================================
// 修改：2011-04-26 10:22  by David
//		1.增加了一个线程安全的读取指针，方便作为“线程池”的处理应用
//========================================================================
// 修改： 2011-04-27 14:10  by david
//		1.增加了一个元素个数的计数
//========================================================================
#ifndef UTL_SAFE_VECTOR_H
#define UTL_SAFE_VECTOR_H
#pragma once
#include "platform.h"
#include "dbg.h"
#include "ThreadLibFunctions.h"

#define INVALID_SAFEVECTOR_IDX ((I)~0)

// 遍历操作
#define FOR_EACH_SAFETABLE( rwName, iteratorName ) \
	for( UINT32 iteratorName=rwName.head(); iteratorName != rwName.end(); iteratorName = rwName.next(iteratorName) )

//	配合reset_readpoint()使用
#define TH_FOR_EACH_SAFETABLE( rwName, iteratorName ) \
//	for( UINT32 iteratorName=0 ; (iteratorName = rwName.get_readpoint()) < rwName.size(); rwName.next_readpoint() )
	for( UINT32 iteratorName=rwName.next_readpoint(); rwName.get_readpoint()<rwName.size(); iteratorName = rwName.next_readpoint() )

template<class T,class I = UINT32>
class CUtlSafeVector
{
public:
	CUtlSafeVector(){
		m_table = 0;
		m_tableSize = 0;
		m_writepoint = 0;
		m_readpoint = 0;
		m_number = 0;
	}
	~CUtlSafeVector(){};

	inline bool init(I size);

	inline I add(T* p);
	inline void	remove(I i);
	inline I count(){return m_number;}

	inline I head()	{return 0;}
	inline I end()	{return m_tableSize;}
	inline I next(I i){return ++i;}	//线程安全的因为i是线程的局部变量;当i = end（）时在这个函数里不要做自动指向0的操作
//	inline T* read_next();

	inline void reset_readpoint() { ThreadLib::LocketSet( (volatile LONG*)&(m_readpoint), -1 ); };
	inline ULONG get_readpoint() { return m_readpoint/*ThreadLib::LocketRead((volatile LONG *)&m_readpoint)*/; };
	inline ULONG next_readpoint() { ThreadLib::LocketAdd((volatile LONG*)&m_readpoint)+1; };


	inline I size()	{return m_tableSize;}
	inline static I  invalidIndex()  { return INVALID_SAFEVECTOR_IDX; }

	inline T* element(I i);
	inline T* operator[](I i);

protected:
	T**		m_table;
	I		m_tableSize;	//table size	
	ULONG	m_writepoint;	//写指针
	ULONG	m_readpoint;	//读操作
	ULONG	m_number;		//元素个数

};

template<class T,class I>
inline bool CUtlSafeVector<T,I>::init(I size)
{
	m_tableSize = size;
	m_table = (T**)Plat_Alloc(size * sizeof(T*));
	if(!m_table){
		AssertMsg(m_table,"Alloc NULL!");
		return false;
	}
	memset(m_table,0,size * sizeof(T*));
	return true;
}

template<class T,class I>
inline I CUtlSafeVector<T,I>::add(T* element)
{
	ULONG temp = ThreadLib::LocketAdd((volatile LONG *)&m_writepoint,1);
	temp %= m_tableSize;

	if(m_table[temp] == NULL)
	{
		m_table[temp] = element;		 
		ThreadLib::LockedIncrement((volatile LONG*)&m_number);
		return temp;
	}
	else
	{
		for(I i=0;i<m_tableSize;i++)
		{
			temp = ThreadLib::LocketAdd((volatile LONG *)&m_writepoint,1);
			temp %= m_tableSize;
			//if(temp >= m_tableSize)
			//{
			//	ThreadLib::LocketSet((volatile LONG *)&m_writepoint,0);
			//	continue;
			//}
			if(m_table[temp] == NULL)
			{
				m_table[temp] = element;
				ThreadLib::LockedIncrement((volatile LONG*)&m_number);
				return temp;
			}
		}
	}

	return invalidIndex();
}


template<class T,class I>
inline void CUtlSafeVector<T,I>::remove(I i)
{
	if(i>=0 && i<m_tableSize){
		m_table[i] = NULL;
		ThreadLib::LockedDecrement((volatile LONG*)&m_number);
	}
}

template<class T,class I>
inline T* CUtlSafeVector<T,I>::element(I i)
{
	if(!m_table)
		return NULL;

	if(i>=0 && i<m_tableSize)
		return m_table[i] ;
	return NULL;
}

template<class T,class I>
inline T* CUtlSafeVector<T,I>::operator [](I i)
{
	return element(i);
}

// 读取下一条记录
// 支持多线程的读取
//template<class T,class I>
//inline T* CUtlSafeVector<T,I>::read_next()
//{
//	I temp = ThreadLib::LocketAdd((volatile LONG *)&m_readpoint,1);
//
//	//if(temp >= m_tableSize){
//	//	ThreadLib::LocketSet((volatile LONG*)&m_readpoint,0);
//	//	temp = 0;
//	//}
//	return element( temp%m_tableSize );
//}
#endif
