//	
// CBaseObjMgr: 2011-04-21 18:34 by David
//		1.֧�ֶ��߳���Ӳ���
//		2.֧�ֶ��߳�ɾ������
//		3.���̵߳ı�������
//		4.�ڶ��߳�ɾ��ʱҪ����ע�⣬�����ظ�ɾ��ͬһ����ַ�Ĳ������������������
//========================================================================
// �޸ģ�2011-04-26 10:22  by David
//		1.������һ���̰߳�ȫ�Ķ�ȡָ�룬������Ϊ���̳߳ء��Ĵ���Ӧ��
//========================================================================
// �޸ģ� 2011-04-27 14:10  by david
//		1.������һ��Ԫ�ظ����ļ���
//========================================================================
#ifndef UTL_SAFE_VECTOR_H
#define UTL_SAFE_VECTOR_H
#pragma once
#include "platform.h"
#include "dbg.h"
#include "ThreadLibFunctions.h"

#define INVALID_SAFEVECTOR_IDX ((I)~0)

// ��������
#define FOR_EACH_SAFETABLE( rwName, iteratorName ) \
	for( UINT32 iteratorName=rwName.head(); iteratorName != rwName.end(); iteratorName = rwName.next(iteratorName) )

//	���reset_readpoint()ʹ��
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
	inline I next(I i){return ++i;}	//�̰߳�ȫ����Ϊi���̵߳ľֲ�����;��i = end����ʱ����������ﲻҪ���Զ�ָ��0�Ĳ���
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
	ULONG	m_writepoint;	//дָ��
	ULONG	m_readpoint;	//������
	ULONG	m_number;		//Ԫ�ظ���

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

// ��ȡ��һ����¼
// ֧�ֶ��̵߳Ķ�ȡ
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
