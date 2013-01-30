// utlguidmap:
//		1.专门用来处理key = int64的指针
//		2.其处理都是线程安全的
//		3.不支持遍历操作！
//					David  2011-04-20
////////////////////////////////////////////////
#ifndef UTL_GUID_MAP_H
#define UTL_GUID_MAP_H

#include "ThreadLibFunctions.h"
#include "platform.h"


const int GUIDMAP_OK =		0;
const int GUIDMAP_ERROR	=	1;
const int GUIDMAP_NO_SPACE	=2;

template<class T,class K = UINT32,class I = UINT32>
class Item
{
public:
	Item()
	{
		key = -1;
		flag = 0;
		element = NULL;
	}
	~Item(){}

	LONG	flag;		//关键信号量
	K		key;		//key
	T*		element;	//指针
	inline void   Increace(){
		ThreadLib::LockedIncrement(&flag);
	}
	inline void   Decreace(){
		ThreadLib::LockedDecrement(&flag);
	}
};

template<class T,class K = UINT32,class I = UINT32>
class CUtlNumberMap
{
public:
	CUtlNumberMap(){
		m_ItemTable = NULL;
		m_TableSize = 0;
	}
	~CUtlNumberMap(){
		if(m_ItemTable)
		{
			Plat_Free(m_ItemTable);
			m_ItemTable = NULL;
		}
	}

	inline bool init(I nSize);
	inline int add(K key,T* element);
	inline void remove(K key);
	inline T* get(K key);


protected:
	Item<T>*	m_ItemTable;		//数组指针
	I			m_TableSize;		//数组的大小
	I			m_HalfTableSize;
};

template<class T,class K,class I>
inline bool CUtlNumberMap<T,K,I>::init(I nSize)
{
	m_TableSize = nSize;
	m_HalfTableSize = m_TableSize / 2;
	m_ItemTable = (Item<T>*)Plat_Alloc(m_TableSize * sizeof(Item<T>));
	if(!m_ItemTable)
		return false;
	memset(m_ItemTable,0,m_TableSize * sizeof(Item<T>));
	return true;
}

template<class T,class K,class I>
inline int CUtlNumberMap<T,K,I>::add(K key,T* element)
{
	//每个线程都会分配这个临时变量，所以是线程安全的 david 2011-04-20
	I temp = key % m_TableSize;

	if(  !m_ItemTable[temp].flag && m_ItemTable[temp].element == NULL )
	{
		m_ItemTable[temp].Increace();
		m_ItemTable[temp].key = key;
		m_ItemTable[temp].element = element;
		m_ItemTable[temp].Decreace();
		return GUIDMAP_OK;
	}
	else
	{
		if(temp <= m_HalfTableSize)
		{
			for(I i = m_HalfTableSize;i<m_TableSize;i++)
			{
				if( !m_ItemTable[i].flag && m_ItemTable[i].element == NULL )
				{
					m_ItemTable[i].Increace();
					m_ItemTable[i].key = key;
					m_ItemTable[i].element = element;
					m_ItemTable[i].Decreace();
					return GUIDMAP_OK;
				}
			}
		}
		else
		{
			for(int j = m_HalfTableSize;j>0;j--)
			{
				if( !m_ItemTable[j].flag && m_ItemTable[j].element == NULL )
				{
					m_ItemTable[j].Increace();
					m_ItemTable[j].key = key;
					m_ItemTable[j].element = element;
					m_ItemTable[j].Decreace();
					return GUIDMAP_OK;
				}
			}
		}
	}

	return GUIDMAP_NO_SPACE;
}

template<class T,class K,class I>
inline void CUtlNumberMap<T,K,I>::remove(K key)
{
	//每个线程都会分配这个临时变量，所以是线程安全的 david 2011-04-20
	I temp = key % m_TableSize;

	if(  !m_ItemTable[temp].flag && m_ItemTable[temp].key == key )
	{
		m_ItemTable[temp].Increace();
		m_ItemTable[temp].key = -1;
		m_ItemTable[temp].element = NULL;
		m_ItemTable[temp].Decreace();
	}
	else
	{
		if(temp <= m_HalfTableSize)
		{
			for(I i = m_HalfTableSize;i<m_TableSize;i++)
			{
				if( !m_ItemTable[i].flag && m_ItemTable[i].key == key )
				{
					m_ItemTable[i].Increace();
					m_ItemTable[i].key = -1;
					m_ItemTable[i].element = NULL;
					m_ItemTable[i].Decreace();
				}
			}
		}
		else
		{
			for(int j = m_HalfTableSize;j>0;j--)
			{
				if( !m_ItemTable[j].flag && m_ItemTable[j].key == key )
				{
					m_ItemTable[j].Increace();
					m_ItemTable[j].key = -1;
					m_ItemTable[j].element = NULL;
					m_ItemTable[j].Decreace();
				}
			}
		}
	}	
}

template<class T,class K,class I>
inline T* CUtlNumberMap<T,K,I>::get(K key)
{
	//每个线程都会分配这个临时变量，所以是线程安全的 david 2011-04-20
	I temp = key % m_TableSize;

	if(  m_ItemTable[temp].key == key )
	{	
		return m_ItemTable[temp].element;		
	}
	else
	{
		if(temp <= m_HalfTableSize)
		{
			for(I i = m_HalfTableSize;i<m_TableSize;i++)
			{
				if( m_ItemTable[i].key == key )
				{
					return m_ItemTable[i].element;
				}
			}
		}
		else
		{
			for(I j = m_HalfTableSize;j>0;j--)
			{
				if( m_ItemTable[j].key == key )
				{
					return m_ItemTable[j].element;
				}
			}
		}
	}	
	return NULL;
}

#endif
