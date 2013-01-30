#pragma once
//////////////////////////////////////////////////////////////////////////
//用于快速遍历的模板List  by zhao
//使用时默认开辟空间大小，如需开辟自定义空间大小，使用方法Purge(size)
//////////////////////////////////////////////////////////////////////////
#include "GLock.h"
#include "HashMap.h"
#include "atomic.h"

#define  INVALID_LISTINDEX(x) (x)(-1)

const int Default_ListSize=2000;

template <class T, class I = unsigned short>
class CQuickList
{
public:
	struct struct_listparam
	{
		I	index;				//序号
		T		param;				// 对应的元素
		struct_listparam *	lastpram;			//指向的上一个
		struct_listparam *	nextpram;			// 指向的下一个
		int nRef;				//引用
		void Init()
		{
			nRef=0;
			param = NULL;
			lastpram=NULL;
			nextpram = NULL;
		}
	};

	CQuickList(int initSize =Default_ListSize);
	~CQuickList();

	//分配内存
	void Purge(I nSize);

	//取元素的操作
	T&   Element( I index );
	T&   operator[]( I index );

	//添加链头和链尾
	I	AddToHead( T & src );
	I	AddToTail( T & src );

	//取头序号
	I  Head();
	//取尾序号
	I  Tail();

	//取当前序号的下一个
	I  Next( I index);
	//取上一个序号
	I Previous(I index);

	//是否是无效序号
	bool  IsValidIndex(I index) ;

	inline I    InvalidIndex(){return INVALID_LISTINDEX(I);}
	//按序号删除
	void	Remove(I index );
	//全部删除
	void	RemoveAll();

	void	Release();

	int	 Count(); //list中元素的数量

	inline struct_listparam* GetListTable(){return m_ElementTable;}

protected:
	struct_listparam* m_ElementTable;  //元素表
	I					m_TableSize;  //最大值
	LONG		m_nCount;  //当前计数
	I					m_CurrentRef;  //当前引用序号
	T		    m_Invalid;
	I			m_HeadIndex;
	I			m_TailIndex;
};

template <class T, class I>
CQuickList<T,I>::CQuickList(int initSize)
{
	m_TableSize = 0;
	m_nCount	= 0;
	m_ElementTable = NULL;
	m_Invalid=NULL;
	m_CurrentRef=0;
	m_HeadIndex=INVALID_LISTINDEX(I);
	m_TailIndex=INVALID_LISTINDEX(I);
	//默认大小的内存，2倍连续内存，一半用于hash表直接索引，后一半用于备用
	//m_ElementTable		= (CQuickList<T,I>::struct_listparam *)Plat_Alloc(sizeof(CQuickList<T,I>::struct_listparam )*initSize*2);	2010-12-28		li9chuan
	m_ElementTable		= (struct_listparam *)Plat_Alloc(sizeof(struct_listparam )*initSize*2);
	if(m_ElementTable)
	{
		//2倍大小，用于配合CHashMap
		m_TableSize=initSize*2;
		for(int i=0;i<m_TableSize;i++)
		{
			m_ElementTable[i].Init();
		}
	}
}

template <class T, class I>
CQuickList<T,I>::~CQuickList()
{
	Release();
}

template <class T, class I>
void	CQuickList<T,I>::Release()
{
	if(m_ElementTable)
	{
		Plat_Free(m_ElementTable);
		m_ElementTable = NULL;
	}
}

template <class T, class I>
void CQuickList<T,I>::Purge(I nSize)
{
	if(!m_ElementTable)
		return;

	//重新分配
	//m_ElementTable		= (CQuickList<T,I>::struct_listparam *)Plat_Realloc(m_ElementTable,sizeof(CQuickList<T,I>::struct_listparam )*nSize);	2010-12-28		li9chuan
	m_ElementTable		= (struct_listparam *)Plat_Realloc(m_ElementTable,sizeof(struct_listparam )*nSize);
	if(m_ElementTable)
	{

		//2倍大小，用于配合CHashMap
		m_TableSize			= nSize*2;

		for(int i=0;i<m_TableSize;i++)
		{
			m_ElementTable[i].Init();
		}
	}

}

//取元素的操作
template <class T, class I>
T&   CQuickList<T,I>::Element( I index )
{
	if(index<0||index>=m_TableSize)
		return m_Invalid;

	//CQuickList<T,I>::struct_listparam* p=&m_ElementTable[index];	2010-12-28		li9chuan
	struct_listparam* p=&m_ElementTable[index];
	if(p)
		return p->param;

	return m_Invalid;
}

template <class T, class I>
T&   CQuickList<T,I>::operator[]( I index )
{
	if(index<0||index>=m_TableSize)
		return m_Invalid;

	//CQuickList<T,I>::struct_listparam* p=&m_ElementTable[index];	2010-12-28		li9chuan
	struct_listparam* p=&m_ElementTable[index];
	if(p)
		return p->param;

	return m_Invalid;
}

//添加链头和链尾

template <class T, class I>
I	CQuickList<T,I>::AddToHead( T & src )
{
	I returnindex=INVALID_LISTINDEX(I);
	//次数限制
	for(int i=0;i<m_TableSize;i++)
	{
		if(m_ElementTable[m_CurrentRef].nRef==0)
		{
			m_ElementTable[m_CurrentRef].nRef++;
			m_ElementTable[m_CurrentRef].param=src;

			//取头部
			I index=Head();


			if(index==INVALID_LISTINDEX(I))
			{
				//没有头的情况下，头，尾设置
				m_HeadIndex=m_CurrentRef;
				m_TailIndex=m_CurrentRef;
				m_ElementTable[m_CurrentRef].lastpram=NULL;
				m_ElementTable[m_CurrentRef].nextpram=NULL;

			}
			else
			{
				if(index<0||index>=m_TableSize)
				{
					Log("QuickList 头部链接严重错误!");
					//return INVALID_LISTINDEX(I)	2010-12-28		li9chuan
					return INVALID_LISTINDEX(I);
				}
				//有头，则连接
				m_HeadIndex=m_CurrentRef;
				m_ElementTable[index].lastpram=&m_ElementTable[m_CurrentRef];
				m_ElementTable[m_CurrentRef].nextpram=&m_ElementTable[index];
				m_ElementTable[m_CurrentRef].lastpram=NULL;
			}

			returnindex=m_CurrentRef;
			break;
		}
	}

	if(m_CurrentRef++>=m_TableSize)
		m_CurrentRef=0;

	InterlockedIncrement(&m_nCount);

	return returnindex;
}

template <class T, class I>
I	CQuickList<T,I>::AddToTail( T & src )
{
	I returnindex=INVALID_LISTINDEX(I);
	//次数限制
	for(int i=0;i<m_TableSize;i++)
	{
		if(m_ElementTable[m_CurrentRef].nRef==0)
		{
			m_ElementTable[m_CurrentRef].nRef++;
			m_ElementTable[m_CurrentRef].param=src;

			//取尾部
			I index=Tail();


			if(index==INVALID_LISTINDEX(I))
			{
				//没有尾的情况下，头，尾设置
				m_HeadIndex=m_CurrentRef;
				m_TailIndex=m_CurrentRef;
				m_ElementTable[m_CurrentRef].lastpram=NULL;
				m_ElementTable[m_CurrentRef].nextpram=NULL;

			}
			else
			{
				if(index<0||index>=m_TableSize)
				{
					Log("QuickList 尾部链接严重错误!");
					return INVALID_LISTINDEX(I);

				}
				//有尾，则连接
				m_TailIndex=m_CurrentRef;
				m_ElementTable[m_CurrentRef].lastpram=&m_ElementTable[index];
				m_ElementTable[index].nextpram=&m_ElementTable[m_CurrentRef];
				m_ElementTable[m_CurrentRef].nextpram=NULL;
			}

			returnindex=m_CurrentRef;
			break;
		}
	}

	if(m_CurrentRef++>=m_TableSize)
		m_CurrentRef=0;

	InterlockedIncrement(&m_nCount);

	return returnindex;
}

//取头序号
template <class T, class I>
I  CQuickList<T,I>::Head()
{
	return m_HeadIndex;
}

//取尾序号
template <class T, class I>
I  CQuickList<T,I>::Tail()
{
	return m_TailIndex;;
}


//取当前序号的下一个
template <class T, class I>
I  CQuickList<T,I>::Next( I index)
{
	if(index<0||index>=m_TableSize)
		return INVALID_LISTINDEX(I);

	struct_listparam* p=&m_ElementTable[index];
	if(p)
	{
		if(p->nextpram)
		{
			return p->nextpram->index;
		}
	}

	return INVALID_LISTINDEX(I);
}

//取当前序号的上一个
template <class T, class I>
I CQuickList<T,I>::Previous(I index)
{
	if(index<0||index>=m_TableSize)
		return INVALID_LISTINDEX(I);

	struct_listparam* p=&m_ElementTable[index];
	if(p)
	{
		if(p->lastpram)
		{
			return p->lastpram->index;
		}
	}

	return INVALID_LISTINDEX(I);
}

//是否是无效序号
template <class T, class I>
bool  CQuickList<T,I>::IsValidIndex(I index)
{
	if(index<0||index>=m_TableSize)
		return false;

	struct_listparam* p=&m_ElementTable[index];
	if(p)
	{
		if(p->nRef!=0)
			return true;
	}

	return false;
}


//按序号删除
template <class T, class I>
void	CQuickList<T,I>::Remove(I index )
{
	if(index<0||index>=m_TableSize)
		return;

	struct_listparam* p=&m_ElementTable[index];
	if(p)
	{
		//如果是头部
		if(p->index==Head())
		{
			//有下一个节点
			if(p->nextpram)
			{
				//头部重新分配序号
				m_HeadIndex=p->nextpram->index;
				p->nextpram->lastpram=NULL;
				p->Init();

			}
			else
			{
				//没有下一个节点，那么链表空了
				m_HeadIndex=INVALID_LISTINDEX(I);
				m_TailIndex=INVALID_LISTINDEX(I);
				p->Init();

			}
			InterlockedDecrement(&m_nCount);
			return;
		}

		//如果是尾部
		if(p->index=Tail())
		{
			//有上一个节点
			if(p->lastpram)
			{
				//尾部重新分配序号
				m_TailIndex=p->lastpram->index;
				p->lastpram->nextpram=NULL;
				p->Init();

			}
			else
			{
				//没有上一个节点，那么链表空了
				m_HeadIndex=INVALID_LISTINDEX(I);
				m_TailIndex=INVALID_LISTINDEX(I);
				p->Init();

			}
			InterlockedDecrement(&m_nCount);
			return;
		}

		//中间节点的处理，一个脱链的过程
		if(p->lastpram&&p->nextpram)
		{
			//重新连接上下节点
			p->lastpram->nextpram=p->nextpram;
			p->nextpram->lastpram=p->lastpram;
			p->Init();
		}
		else
		{
			Log("QuickList remove 严重错误！");
			return;
		}
		InterlockedDecrement(&m_nCount);
	}
}

//全部删除
template <class T, class I>
void	CQuickList<T,I>::RemoveAll()
{
	m_HeadIndex=INVALID_LISTINDEX(I);
	m_TailIndex=INVALID_LISTINDEX(I);
	for(int i=0;i<m_TableSize;i++)
	{
		m_ElementTable[i].Init();
	}
	m_nCount=0;

}

template <class T, class I>
int	 CQuickList<T,I>::Count()
{
	return m_nCount;
}
