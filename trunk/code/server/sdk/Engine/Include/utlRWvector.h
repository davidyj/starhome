//
// utlthreadvector:
//		���̰߳�ȫ������
//	ע�⣺
//		1.�����ж���߳�д��
//		2*.���뱣ֻ֤��һ���̶߳�ȡ!!!
//		3.���Ա�֤ÿ���̼߳������ݵ�˳�򣻵����̼߳��˳�򲻿��Ա�֤��
//					2011-04-21 09:41		david 
//==================================================================
// �޸ģ�2011-04-22 17:09  David
//		1.�����˶Ե�������֧��
//		2.�����˱���֧�ֵĺ�
//==================================================================
// �޸ģ�2011-04-25 10:47 David
//		1.�޸��˶�ȡ��bug��ÿ��Ӧ�ö�ȡ��дָ���λ�ò��ܽ���
//==================================================================
// �޸ģ�2011-04-26 12:06 David
//		1.ÿ�ζ�ȡ�� ��Ҫ�����ǰλ�õ�Ԫ�أ�����û�а취��write��
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

	inline I next();			//��ȡ��һ����¼��ͬʱ����Ϊ��

	inline I invalidIndex(){return (I)~0;}
	inline I readIndex(){return m_readpoint % m_TableSize;}
	inline I writeIndex(){return m_writepoint % m_TableSize;}

	inline T* Element(I i);
	inline T* operator[](I i);

	inline bool isInit() { return (m_ItemTable==NULL ? false : true); }

protected:
	T**		m_ItemTable;		//����ָ���ָ��
	I		m_TableSize;		//����Ĵ�С	
	I		m_readpoint;		//��ȡָ��
	I		m_writepoint;		//дָ��
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

//�ƶ���ָ�뵽��һ��
template<class T,class I> 
inline I CUtlRWVector<T,I>::next()
{
//	ThreadLib::LockedIncrement((volatile LONG *)&m_readpoint);
	I tmp = ThreadLib::LocketAdd((volatile LONG *)&m_readpoint,1);
//	if(m_readpoint >= m_TableSize)
//		ThreadLib::LocketSet((volatile LONG *)&m_readpoint,0);
	return (tmp+1) % m_TableSize;
}

//ÿ�η����궼�ᱻ���
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
// ��ȡʱһ��ֻ��һ���̶߳�ȡ�����Զ�ȡ�䲻�ý�������
// ֻ��Ҫ���� ��д֮��� ������ϵ�Ϳ�����
// ���Ƕ�ȡ�꣬Ҳ��һ�����ñ����Ĳ���
// ����NULLʱָ�벻�����ƶ�
/////////////////////////////////////////////////////
template<class T,class I> 
inline T* CUtlRWVector<T,I>::next()
{
	ULONG temp = m_readpoint;

	//�����Ϊ�� ָ��++
	if(m_ItemTable[m_readpoint])
	{	
		// ָ������
		m_ItemTable[m_readpoint] = NULL;		

		ThreadLib::LocketAdd(&m_readpoint,1);
		if(m_readpoint >= m_TableSize)
			ThreadLib::LocketSet(&m_readpoint,0);
	}

	return m_ItemTable[temp];	
}
*/
#endif
