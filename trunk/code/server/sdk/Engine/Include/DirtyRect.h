////////////////////////////////
//	Create by  soloman for 重画当前屏幕矩形  2000.4.19;	
//	Modified by  soloman    
///////////////////////////

#ifndef _CDirtyRect_H_
#define _CDirtyRect_H_

#include "EngineDefine.h"
#include "Rect.h"
#include "utlvector.h"

#pragma warning (disable:4251) // “identifier”: 类“type”需要有 dll 接口由类“type2”的客户端使用

class ENGINE_CLASS CDirtyRect
{
public:
	CDirtyRect();
	~CDirtyRect();

	BOOL Build( ); // 最多重画块
	void Release( );
	void Add( IRect & );	// 添加重画块
	BOOL Remove( int i );

	void SetMaxRect( const IRect & );

	inline void  Reset( ); // 清空所有数据
	inline int   GetCount( );
	inline const IRect & Get( int i );

private:
	CUtlVector<IRect>	m_RectArray;
	IRect				m_rcMax; // 最大矩形重画块
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
