//
// utlthreadvector:
//		多线程安全的数组
//	注意：
//		1.可以有多个线程写。
//		2*.必须保证只有一个线程读取!!!
//		3.可以保证每条线程加入数据的顺序；但是线程间的顺序不可以保证！
//					2011-04-21 09:41		david 
//==================================================================
// 修改：2011-04-22 17:09  David
//		1.增加了对迭代器的支持
//		2.增加了遍历支持的宏
//==================================================================
// 修改：2011-04-25 10:47 David
//		1.修改了读取的bug，每次应该读取到写指针的位置才能结束
//==================================================================
// 修改：2011-04-26 12:06 David
//		1.每次读取完 都要情况当前位置的元素，否则没有办法再write了
//==================================================================
#ifndef UTL_RW_VECTOR_H
#define UTL_RW_VECTOR_H

#include "ThreadLibFunctions.h"
#include "platform.h"

#define FOR_EACH_RW( rwName, iteratorName ) \
	for( UINT32 iteratorName=rwName.readIndex(); iteratorName != rwName.writeIndex(); iteratorName = rwName.next() )

//#define READ_NEXT_RW( rwName, iteratorName ) \
//	for( ; iteratorName != rwName.writeIndex(); iteratorName = rwName.next() )

template<class T,class I = UINT32> 
class CUtlRWVector
{
public:
	CUtlRWVector(){
		m_ItemTable = NULL;
		m_TableSize = 0;
		m_readpoint = 0;
		m_writepoint = 0;
	}
	~CUtlRWVector(){
		if(m_ItemTable)
		{
			delete m_ItemTable;
			m_ItemTable = NULL;
		}
	}

	inline bool init(I nSize);
	inline I add(T* element);	

	inline I next();			//读取下一条记录，同时设置为空

	inline I invalidIndex(){return (I)~0;}
	inline I readIndex(){return m_readpoint % m_TableSize;}
	inline I writeIndex(){return m_writepoint % m_TableSize;}

	inline T* Element(I i);
	inline T* operator[](I i);

	inline bool isInit() { return (m_ItemTable==NULL ? false : true); }

protected:
	T**		m_ItemTable;		//保存指针的指针
	I		m_TableSize;		//数组的大小	
	I		m_readpoint;		//读取指针
	I		m_writepoint;		//写指针
};

template<class T,class I> 
inline bool CUtlRWVector<T,I>::init(I nSize)
{
	m_readpoint = 0;
	m_writepoint = 0;
	m_TableSize = nSize;	
	m_ItemTable = (T**)Plat_Alloc(nSize * sizeof(T*));
	if(!m_ItemTable)
		return false;
	//memset(m_ItemTable,0,m_TableSize);
	memset(m_ItemTable,0,nSize * sizeof(T*));
	return true;
}

template<class T,class I> 
inline I CUtlRWVector<T,I>::add(T* element)
{	
	I temp = ThreadLib::LocketAdd((volatile LONG *)&m_writepoint,1);
	temp %= m_TableSize;

	if(m_ItemTable[temp] == NULL)
	{
		m_ItemTable[temp] = element;	
		//ThreadLib::LocketSet( (volatile LONG *)&m_ItemTable[temp], (LONG)element );
		return temp;
	}
	else
	{
		for(I i=0;i<m_TableSize;i++)
		{
			temp = ThreadLib::LocketAdd((volatile LONG *)&m_writepoint,1);
			temp %= m_TableSize;
			//if(temp >= m_TableSize)
			//{
			//	ThreadLib::LocketSet((volatile LONG *)&m_writepoint,0);
			//	continue;
			//}
			if(m_ItemTable[temp] == NULL)
			{
				m_ItemTable[temp] = element;
				//ThreadLib::LocketSet( (volatile LONG *)&m_ItemTable[temp], (LONG)element );
				return temp;
			}
		}
	}
	
	return invalidIndex();
}

//移动读指针到下一个
template<class T,class I> 
inline I CUtlRWVector<T,I>::next()
{
//	ThreadLib::LockedIncrement((volatile LONG *)&m_readpoint);
	I tmp = ThreadLib::LocketAdd((volatile LONG *)&m_readpoint,1);
//	if(m_readpoint >= m_TableSize)
//		ThreadLib::LocketSet((volatile LONG *)&m_readpoint,0);
	return (tmp+1) % m_TableSize;
}

//每次访问完都会被清空
template<class T,class I> 
inline T* CUtlRWVector<T,I>::Element(I i)
{
	if( i<0 || i>=m_TableSize)
		return NULL;
	T* pTemp = m_ItemTable[i];
	m_ItemTable[i] = NULL;
//	ThreadLib::LocketSet( (volatile LONG *)&m_ItemTable[i] ,0 );
	
	return pTemp;
	
}

template<class T,class I> 
inline T* CUtlRWVector<T,I>::operator [](I i)
{
	return Element(i);
}
/*
// 读取时一般只有一个线程读取，所以读取间不用建立互斥
// 只需要做好 读写之间的 竞争关系就可以了
// 但是读取完，也有一个设置变量的操作
// 遇到NULL时指针不往下移动
/////////////////////////////////////////////////////
template<class T,class I> 
inline T* CUtlRWVector<T,I>::next()
{
	ULONG temp = m_readpoint;

	//如果不为空 指针++
	if(m_ItemTable[m_readpoint])
	{	
		// 指针下移
		m_ItemTable[m_readpoint] = NULL;		

		ThreadLib::LocketAdd(&m_readpoint,1);
		if(m_readpoint >= m_TableSize)
			ThreadLib::LocketSet(&m_readpoint,0);
	}

	return m_ItemTable[temp];	
}
*/
#endif
