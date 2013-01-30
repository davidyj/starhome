#pragma once
//////////////////////////////////////////////////////////////////////////
//���ڿ��ٱ�����ģ��List  by zhao
//ʹ��ʱĬ�Ͽ��ٿռ��С�����迪���Զ���ռ��С��ʹ�÷���Purge(size)
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
		I	index;				//���
		T		param;				// ��Ӧ��Ԫ��
		struct_listparam *	lastpram;			//ָ�����һ��
		struct_listparam *	nextpram;			// ָ�����һ��
		int nRef;				//����
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

	//�����ڴ�
	void Purge(I nSize);

	//ȡԪ�صĲ���
	T&   Element( I index );
	T&   operator[]( I index );

	//�����ͷ����β
	I	AddToHead( T & src );
	I	AddToTail( T & src );

	//ȡͷ���
	I  Head();
	//ȡβ���
	I  Tail();

	//ȡ��ǰ��ŵ���һ��
	I  Next( I index);
	//ȡ��һ�����
	I Previous(I index);

	//�Ƿ�����Ч���
	bool  IsValidIndex(I index) ;

	inline I    InvalidIndex(){return INVALID_LISTINDEX(I);}
	//�����ɾ��
	void	Remove(I index );
	//ȫ��ɾ��
	void	RemoveAll();

	void	Release();

	int	 Count(); //list��Ԫ�ص�����

	inline struct_listparam* GetListTable(){return m_ElementTable;}

protected:
	struct_listparam* m_ElementTable;  //Ԫ�ر�
	I					m_TableSize;  //���ֵ
	LONG		m_nCount;  //��ǰ����
	I					m_CurrentRef;  //��ǰ�������
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
	//Ĭ�ϴ�С���ڴ棬2�������ڴ棬һ������hash��ֱ����������һ�����ڱ���
	//m_ElementTable		= (CQuickList<T,I>::struct_listparam *)Plat_Alloc(sizeof(CQuickList<T,I>::struct_listparam )*initSize*2);	2010-12-28		li9chuan
	m_ElementTable		= (struct_listparam *)Plat_Alloc(sizeof(struct_listparam )*initSize*2);
	if(m_ElementTable)
	{
		//2����С���������CHashMap
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

	//���·���
	//m_ElementTable		= (CQuickList<T,I>::struct_listparam *)Plat_Realloc(m_ElementTable,sizeof(CQuickList<T,I>::struct_listparam )*nSize);	2010-12-28		li9chuan
	m_ElementTable		= (struct_listparam *)Plat_Realloc(m_ElementTable,sizeof(struct_listparam )*nSize);
	if(m_ElementTable)
	{

		//2����С���������CHashMap
		m_TableSize			= nSize*2;

		for(int i=0;i<m_TableSize;i++)
		{
			m_ElementTable[i].Init();
		}
	}

}

//ȡԪ�صĲ���
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

//�����ͷ����β

template <class T, class I>
I	CQuickList<T,I>::AddToHead( T & src )
{
	I returnindex=INVALID_LISTINDEX(I);
	//��������
	for(int i=0;i<m_TableSize;i++)
	{
		if(m_ElementTable[m_CurrentRef].nRef==0)
		{
			m_ElementTable[m_CurrentRef].nRef++;
			m_ElementTable[m_CurrentRef].param=src;

			//ȡͷ��
			I index=Head();


			if(index==INVALID_LISTINDEX(I))
			{
				//û��ͷ������£�ͷ��β����
				m_HeadIndex=m_CurrentRef;
				m_TailIndex=m_CurrentRef;
				m_ElementTable[m_CurrentRef].lastpram=NULL;
				m_ElementTable[m_CurrentRef].nextpram=NULL;

			}
			else
			{
				if(index<0||index>=m_TableSize)
				{
					Log("QuickList ͷ���������ش���!");
					//return INVALID_LISTINDEX(I)	2010-12-28		li9chuan
					return INVALID_LISTINDEX(I);
				}
				//��ͷ��������
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
	//��������
	for(int i=0;i<m_TableSize;i++)
	{
		if(m_ElementTable[m_CurrentRef].nRef==0)
		{
			m_ElementTable[m_CurrentRef].nRef++;
			m_ElementTable[m_CurrentRef].param=src;

			//ȡβ��
			I index=Tail();


			if(index==INVALID_LISTINDEX(I))
			{
				//û��β������£�ͷ��β����
				m_HeadIndex=m_CurrentRef;
				m_TailIndex=m_CurrentRef;
				m_ElementTable[m_CurrentRef].lastpram=NULL;
				m_ElementTable[m_CurrentRef].nextpram=NULL;

			}
			else
			{
				if(index<0||index>=m_TableSize)
				{
					Log("QuickList β���������ش���!");
					return INVALID_LISTINDEX(I);

				}
				//��β��������
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

//ȡͷ���
template <class T, class I>
I  CQuickList<T,I>::Head()
{
	return m_HeadIndex;
}

//ȡβ���
template <class T, class I>
I  CQuickList<T,I>::Tail()
{
	return m_TailIndex;;
}


//ȡ��ǰ��ŵ���һ��
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

//ȡ��ǰ��ŵ���һ��
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

//�Ƿ�����Ч���
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


//�����ɾ��
template <class T, class I>
void	CQuickList<T,I>::Remove(I index )
{
	if(index<0||index>=m_TableSize)
		return;

	struct_listparam* p=&m_ElementTable[index];
	if(p)
	{
		//�����ͷ��
		if(p->index==Head())
		{
			//����һ���ڵ�
			if(p->nextpram)
			{
				//ͷ�����·������
				m_HeadIndex=p->nextpram->index;
				p->nextpram->lastpram=NULL;
				p->Init();

			}
			else
			{
				//û����һ���ڵ㣬��ô�������
				m_HeadIndex=INVALID_LISTINDEX(I);
				m_TailIndex=INVALID_LISTINDEX(I);
				p->Init();

			}
			InterlockedDecrement(&m_nCount);
			return;
		}

		//�����β��
		if(p->index=Tail())
		{
			//����һ���ڵ�
			if(p->lastpram)
			{
				//β�����·������
				m_TailIndex=p->lastpram->index;
				p->lastpram->nextpram=NULL;
				p->Init();

			}
			else
			{
				//û����һ���ڵ㣬��ô�������
				m_HeadIndex=INVALID_LISTINDEX(I);
				m_TailIndex=INVALID_LISTINDEX(I);
				p->Init();

			}
			InterlockedDecrement(&m_nCount);
			return;
		}

		//�м�ڵ�Ĵ���һ�������Ĺ���
		if(p->lastpram&&p->nextpram)
		{
			//�����������½ڵ�
			p->lastpram->nextpram=p->nextpram;
			p->nextpram->lastpram=p->lastpram;
			p->Init();
		}
		else
		{
			Log("QuickList remove ���ش���");
			return;
		}
		InterlockedDecrement(&m_nCount);
	}
}

//ȫ��ɾ��
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
