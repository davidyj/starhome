//
// utlthreadvector:
//		���̰߳�ȫ������
//	ע�⣺
//		֧�ֶ���̵߳���Ӻ�ɾ�������ǽ�����֤�Ը�Vector�İ�ȫ��
//		������֤��Vector����Ԫ�ص� ���̰߳�ȫ����������
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
	inline void remove(UINT32 key);			//��ȡ��һ����¼��ͬʱ����Ϊ��
	inline T*	get(UINT32 key);


protected:
	T**			m_ItemTable;		//����ָ��
	UINT32		m_TableSize;		//����Ĵ�С	
	LONG		m_writepoint;		//дָ��
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

//writepoint ��֤��ͬһʱ�̲����������߳�д��һ��λ��
//LocketSet��֤�˵�д��ɾ����ͬ��
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

// ֧�ֶ��߳�ɾ��
template<class T> 
inline void CUtlThreadVector<T>::remove(UINT32 key)
{
	if(key<0 || key>=m_TableSize)
		return;
	LocketSet((volatile LONG *)&m_ItemTable[key],(LONG)NULL);
}

// ���������а�ȫ������
// ���1�������߳�ͬʱ������ͬһ��key��obj������һ�������obj���˴�����ô�Ϳ��ܻ�һ�����
// David 2011-04-21 12:11
template<class T> 
inline T* CUtlThreadVector<T>::get(UINT32 key)
{
	if(key<0 || key>=m_TableSize)
		return NULL;
	return m_ItemTable[key] ;
}

#endif
