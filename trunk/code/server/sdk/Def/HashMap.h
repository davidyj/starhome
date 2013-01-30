#pragma once
//////////////////////////////////////////////////////////////////////////
//基于hash的模板map  by zhao
//使用时默认开辟空间大小，如需开辟自定义空间大小，使用方法Purge(size)
//////////////////////////////////////////////////////////////////////////
#include "GLock.h"
#include "QuickList.h"
#define INVALID_HASH(x) (x)(-1)  //无效值

const int Default_Size= 100;

template <typename K, typename T, typename I = unsigned short>
class CHashMap
{
	//节点
	struct struct_hashparam
	{
		K	pid;				// key
		I	index;				//map的序号
		T		param;				// 对应的元素
		struct_hashparam *	nextpram;			// 指向的下一个元素

		void Init()
		{
			pid = (K)(-1);
			param = NULL;
			nextpram = NULL;
			index=INVALID_HASH(I);
		}
	};

public:
	CHashMap( int initSize = Default_Size);
	~CHashMap();

	//分配内存
	void Purge(I nSize);

	void Release();

	//插入
	I Insert(K pid,T p); // 插入到map
	I Find(K pid);  //通过key值查找到序号

	bool RemoveAt(I index);  //通过序号删除
	bool Remove(K pid);  //通过key删除

	void RemoveAll();// 全部删除

	int	 Count(); //map中元素的数量
	inline I InvalidIndex(){return INVALID_HASH(I);}  // 无效值

	bool IsValidIndex(I index);   //是否是有效值

	T& Element(I index);  //返回元素
	T&   operator[]( I index );//[]操作符返回元素





protected:
	I			m_TableSize;   //map的元素最大值
	int			m_HashKey;    //hash值
	//CGLock		m_Lock;
	struct_hashparam *	m_ElementTable;
	LONG		m_nCount;  //当前计数
	T		    m_Invalid;




};


template <typename K, typename T, typename I >
CHashMap<K,T,I>::CHashMap(int initSize )
{
	m_TableSize = 0;
	m_nCount	= 0;
	m_ElementTable = NULL;
	m_HashKey=0;
	m_Invalid=NULL;
	//默认大小的内存，2倍连续内存，一半用于hash表直接索引，后一半用于备用
	//m_ElementTable		= (CHashMap<K,T,I>::struct_hashparam *)Plat_Alloc(sizeof(CHashMap<K,T,I>::struct_hashparam )*initSize*2);	2010-12-28		li9chuan
	m_ElementTable		= (struct_hashparam *)Plat_Alloc(sizeof(struct_hashparam )*initSize*2);
	if(m_ElementTable)
	{
		m_TableSize=initSize;

		for(int i=0;i<initSize*2;i++)
		{
			m_ElementTable[i].Init();
		}
	}

}

template <typename K, typename T, typename I>
CHashMap<K,T,I>::~CHashMap()
{
	Release();
}

template <typename K, typename T, typename I>
void CHashMap<K,T,I>::Purge(I nSize)
{
	//构造函数中没有成功分配
	if(!m_ElementTable)
		return;


	m_HashKey=m_TableSize/2-1;
	//Realloc重新开辟，2倍连续内存，一半用于hash表直接索引，后一半用于备用
	//m_ElementTable		= (CHashMap<K,T,I>::struct_hashparam *)Plat_Realloc(m_ElementTable,sizeof(CHashMap<K,T,I>::struct_hashparam )*nSize*2);	2010-12-28		li9chuan
	m_ElementTable		= (struct_hashparam *)Plat_Realloc(m_ElementTable,sizeof(struct_hashparam )*nSize*2);
	if(m_ElementTable)
	{
		m_TableSize			= nSize;

		for(int i=0;i<m_TableSize*2;i++)
		{
			m_ElementTable[i].Init();
		}
	}

}

template <typename K, typename T, typename I>
void CHashMap<K,T,I>::Release()
{
	if(m_ElementTable)
	{
		Plat_Free(m_ElementTable);
		m_ElementTable = NULL;
	}
}

template <typename K, typename T, typename I>
I CHashMap<K,T,I>::Insert(K pid,T p)
{
	if(pid == -1)
		return INVALID_HASH(I);

	//m_Lock.LOCK();
	I key = pid % m_HashKey;

	if( m_ElementTable[key].pid == -1)
	{
		m_ElementTable[key].pid = pid;
		m_ElementTable[key].param = p;
		InterlockedIncrement(&m_nCount);
		m_ElementTable[key].index=key;  //序号
		//m_Lock.UNLOCK();
		return key;
	}

	//CHashMap<K,T,I>::struct_hashparam * np = NULL;	2010-12-28		li9chuan
	struct_hashparam * np = NULL;
	I returnkey=INVALID_HASH(I);
	//在备用table找到一个空闲的位置
	for(int i=m_TableSize/2;i<m_TableSize;i++)
	{
		if(m_ElementTable[i].pid == -1)
		{
			m_ElementTable[i].pid = pid;
			m_ElementTable[i].param = p;
			np = &m_ElementTable[i];
			np->index=returnkey=i;  //序号

			break;
		}
	}
	if(!np)
		return INVALID_HASH(I);

	//CHashMap<K,T,I>::struct_hashparam * tp = &m_ElementTable[key];	2010-12-28		li9chuan
	struct_hashparam * tp = &m_ElementTable[key];
	while(tp)
	{
		if(!tp->nextpram)
		{
			tp->nextpram = np;
			break;
		}
		else
			tp = tp->nextpram;
	}
	InterlockedIncrement(&m_nCount);
	//m_Lock.UNLOCK();
	return returnkey;
}

template <typename K, typename T, typename I>
I CHashMap<K,T,I>::Find(K pid)
{
	if(pid == -1)
		return INVALID_HASH(I);

	int key = pid % m_HashKey;

	//CHashMap<K,T,I>::struct_hashparam * tp = &m_ElementTable[key];	2010-12-28		li9chuan
	struct_hashparam * tp = &m_ElementTable[key];
	while(true)
	{
		if( tp->pid == pid)
			return tp->index;
		tp = tp->nextpram;
		if(!tp)
			return INVALID_HASH(I);
	}

	return INVALID_HASH(I);

}


template <typename K, typename T, typename I>
bool CHashMap<K,T,I>::RemoveAt(I index)
{
	if(index == INVALID_HASH(I))
		return false;

	if(index<0||index>=m_TableSize)
		return false;

	//m_Lock.LOCK();

	//CHashMap<K,T,I>::struct_hashparam * p = &m_ElementTable[index];	2010-12-28		li9chuan
	struct_hashparam * p = &m_ElementTable[index];
	if(p)
	{
		if(p->nextpram)
		{
			//CHashMap<K,T,I>::struct_hashparam * tp = p->nextpram;	2010-12-28		li9chuan
			struct_hashparam * tp = p->nextpram;

			//保证链表的连续
			p->pid		= tp->pid;
			p->param	= tp->param;
			p->nextpram = tp->nextpram;
			tp->Init();
			InterlockedDecrement(&m_nCount);
		}
		else
		{
			p->Init();
			InterlockedDecrement(&m_nCount);
		}

	}
	else
	{
		//m_Lock.UNLOCK();
		return false;
	}
	//m_Lock.UNLOCK();
	return true;
}
template <typename K, typename T, typename I>
bool CHashMap<K,T,I>::Remove(K pid)
{
	I index=Find(pid);
	if(index!=INVALID_HASH(I))
	{
		return RemoveAt(index);
	}
	return false;
}

template <typename K, typename T, typename I>
int CHashMap<K,T,I>::Count()
{
	return m_nCount;

}

template <typename K, typename T, typename I>
bool CHashMap<K,T,I>::IsValidIndex(I index)
{
	if(index<0||index>=m_TableSize)
		return false;

	//CHashMap<K,T,I>::struct_hashparam* p=&m_ElementTable[index];	2010-12-28		li9chuan
	struct_hashparam* p=&m_ElementTable[index];
	if(p)
	{
		if(p->pid!=(K)(-1))
			return true;
	}

	return false;
}

template <typename K, typename T, typename I>
T& CHashMap<K,T,I>::Element(I index)
{
	if(index<0||index>=m_TableSize)
		return m_Invalid;

	//CHashMap<K,T,I>::struct_hashparam* p=&m_ElementTable[index];	2010-12-28		li9chuan
	struct_hashparam* p=&m_ElementTable[index];
	if(p)
	{
		return p->param;
	}

	return m_Invalid;
}

template <typename K, typename T, typename I>
T&   CHashMap<K,T,I>::operator[]( I index )
{
	if(index<0||index>=m_TableSize)
		return m_Invalid;

	//CHashMap<K,T,I>::struct_hashparam* p=&m_ElementTable[index];	2010-12-28		li9chuan
	struct_hashparam* p=&m_ElementTable[index];
	if(p)
	{
		return p->param;
	}

	return m_Invalid;
}

template <typename K, typename T, typename I>
void CHashMap<K,T,I>::RemoveAll()
{
	for(int i=0;i<m_TableSize*2;i++)
	{
		m_ElementTable[i].Init();
	}
	m_nCount=0;

}


/*
template <typename K, typename T, typename I= unsigned short >
class CHashListMap :public CHashMap<K,T,I>
{
public:
	CHashListMap(int initSize = Default_Size):CHashMap(initSize)
	{

	}
	~CHashListMap()
	{

	}

	//分配内存
	void Purge(I nSize);

	void Release();

	//插入
	I Insert(K pid,T p); // 插入到map
	I Find(K pid);  //通过key值查找到序号

	bool RemoveAt(I index);  //通过序号删除
	bool Remove(K pid);  //通过key删除

	void RemoveAll();// 全部删除

	//用于便历的方法
	I  FirstInorder();
	I  NextInorder( I i ) ;
	I  PrevInorder( I i ) ;
	I  LastInorder() ;
protected:
	CQuickList<T,I> m_QuickList;
};

template <typename K, typename T, typename I >
void CHashListMap<K,T,I>::Purge(I nSize)
{
	CHashMap<K,T,I>::Purge(nSize);
	m_QuickList.Purge(nSize);
}

template <typename K, typename T, typename I >
void CHashListMap<K,T,I>::Release()
{
	CHashMap<K,T,I>::Release();
	m_QuickList.Release();
}

template <typename K, typename T, typename I >
I CHashListMap<K,T,I>::Insert(K pid,T p) // 插入到map
{
	I mapindex=CHashMap<K,T,I>::Insert(pid,p);
	I listindex=m_QuickList.AddToTail(p);
	if(mapindex!=INVALID_HASH(I)&&listindex!=INVALID_LISTINDEX(I))
	{
		if(&m_QuickList.GetListTable())
		{
			&(m_QuickList.GetListTable()[listindex])->hashmapindex=mapindex;
		}
		m_ElementTable[mapindex].listindex=listindex;
	}
}



template <typename K, typename T, typename I >
bool CHashListMap<K,T,I>::RemoveAt(I index)  //通过序号删除
{
	if(index<0||index>=m_TableSize)
		return false;

	struct_hashparam* p=&m_ElementTable[index];
	if(p)
	{
		m_QuickList.Remove(p->listindex);
		CHashMap<K,T,I>::RemoveAt(index);
		return true;
	}
	return false;

}


template <typename K, typename T, typename I >
void CHashListMap<K,T,I>::RemoveAll()// 全部删除
{
	CHashMap<K,T,I>::RemoveAll();
	m_QuickList.RemoveAll();
}

template <typename K, typename T, typename I >
I  CHashListMap<K,T,I>::FirstInorder()
{
	I listindex=m_QuickList.Head();
	if(listindex!=INVALID_LISTINDEX(I))
	{
		if(&m_QuickList.GetListTable()[listindex])
		{
			return &(m_QuickList.GetListTable()[listindex])->hashmapindex;
		}
	}
	return INVALID_HASH(I);
}

template <typename K, typename T, typename I >
I  CHashListMap<K,T,I>::NextInorder( I i )
{
	if(index<0||index>=m_TableSize)
		return INVALID_HASH(I);

	if(i!=INVALID_HASH(I))
	{
		if(&m_ElementTable[i])
			I listindex=m_QuickList.Next(&m_ElementTable[i]->listindex);
		if(I!=INVALID_LISTINDEX(I))
		{
			if(&m_QuickList.GetListTable()[listindex])
				return &(m_QuickList.GetListTable()[listindex])->hashmapindex;
		}
	}

	return INVALID_HASH(I);
}

template <typename K, typename T, typename I >
I  CHashListMap<K,T,I>::PrevInorder( I i )
{
	if(index<0||index>=m_TableSize)
		return INVALID_HASH(I);

	if(i!=INVALID_HASH(I))
	{
		if(&m_ElementTable[i])
			I listindex=m_QuickList.Previous(&m_ElementTable[i]->listindex);
		if(I!=INVALID_LISTINDEX(I))
		{
			if(&m_QuickList.GetListTable()[listindex])
				return &(m_QuickList.GetListTable()[listindex])->hashmapindex;
		}
	}

	return INVALID_HASH(I);
}

template <typename K, typename T, typename I >
I  CHashListMap<K,T,I>::LastInorder()
{
	I listindex=m_QuickList.Tail();
	if(listindex!=INVALID_LISTINDEX(I))
	{
		if(&m_QuickList.GetListTable()[listindex])
		{
			return &(m_QuickList.GetListTable()[listindex])->hashmapindex;
		}
	}
	return INVALID_HASH(I);
}
*/
