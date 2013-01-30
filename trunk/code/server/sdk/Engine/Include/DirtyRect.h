////////////////////////////////
//	Create by  soloman for �ػ���ǰ��Ļ����  2000.4.19;	
//	Modified by  soloman    
///////////////////////////

#ifndef _CDirtyRect_H_
#define _CDirtyRect_H_

#include "EngineDefine.h"
#include "Rect.h"
#include "utlvector.h"

#pragma warning (disable:4251) // ��identifier��: �ࡰtype����Ҫ�� dll �ӿ����ࡰtype2���Ŀͻ���ʹ��

class ENGINE_CLASS CDirtyRect
{
public:
	CDirtyRect();
	~CDirtyRect();

	BOOL Build( ); // ����ػ���
	void Release( );
	void Add( IRect & );	// ����ػ���
	BOOL Remove( int i );

	void SetMaxRect( const IRect & );

	inline void  Reset( ); // �����������
	inline int   GetCount( );
	inline const IRect & Get( int i );

private:
	CUtlVector<IRect>	m_RectArray;
	IRect				m_rcMax; // �������ػ���
};

inline void  CDirtyRect::Reset()
{
	m_RectArray.RemoveAll( );
}

inline int   CDirtyRect::GetCount( )
{
	return m_RectArray.Count( );
}

inline const IRect & CDirtyRect::Get( int i )
{
	return m_RectArray[i];
}

#endif 
