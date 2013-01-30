#pragma once
#include "Point.h"

class ENGINE_CLASS IRect : public IPoint
{
	DECLARE_CLASS(IRect)
public:
	/////////////////////////////////////////////////////////////////////
	// Construct & Destruct
	IRect( ) : IPoint( ){ m_nCX = 0.0f;	m_nCY = 0.0f; }

	IRect( const IPoint& pt ) : IPoint( pt.m_nX, pt.m_nY ){ m_nCX = 0.0f;	m_nCY = 0.0f; }
	IRect( const IRect& rc ) : IPoint( rc.m_nX, rc.m_nY ){ m_nCX = rc.m_nCX; m_nCY = rc.m_nCY; }

	IRect( float cx, float cy ) : IPoint( 0.0f, 0.0f ){ m_nCX = cx; m_nCY = cy; }
	IRect( float x, float y, float cx, float cy ) : IPoint( x, y ){ m_nCX = cx; m_nCY = cy; }

	virtual ~IRect( ){ }

	/////////////////////////////////////////////////////////////////////
	// Operator
	inline IRect&	operator = ( const IRect& rc );
	inline IRect&	operator = ( const IPoint& pt );

	inline IRect&	operator |= ( const IRect& rc );

	inline BOOL		operator == ( const IRect& pt) const;
	inline BOOL		operator != ( const IRect& pt) const;

	inline IRect&	operator += ( const IRect& rc);
	inline IRect&	operator -= ( const IRect& rc);
	
	inline IRect&	operator += ( const IPoint& pt) {
		(*((IPoint*)this)) += (pt);
		return *this;
	}
	inline IRect&	operator -= ( const IPoint& pt){
		(*((IPoint*)this)) -= (pt);
		return *this;
	}

	inline BOOL		operator >= ( const IRect& pt) const;
	inline BOOL		operator <= ( const IRect& pt) const;

	/////////////////////////////////////////////////////////////////////
	// Method
	inline IRect&	Assign( const IRect& rc );
	inline IRect&	Set( float x, float y, float width, float height );

	inline BOOL		IsContain( const IPoint& pt ) const;
	inline BOOL		IsContain( float x, float y ) const;

	inline float	CX( ) const { return m_nCX; }
	inline float	CY( ) const { return m_nCY; }
	inline float	GetCX( ) const { return m_nCX; }
	inline float	GetCY( ) const { return m_nCY; }
	inline void		SetCX( float w ) { SetW( w ); }
	inline void		SetCY( float h ) { SetH( h ); }

	inline float	GetW( )	const  { return  m_nCX; }
	inline float	GetH( )	const  { return  m_nCY; }

	inline void		SetW( float w )  { m_nCX = w;	}
	inline void		SetH( float h )  { m_nCY = h;	}

	inline  BOOL    Intersect( const IRect& rect1, const IRect& rect2 );
	inline  BOOL    Intersect( const IRect& rDest );

	inline  BOOL    IsContain( const IRect& tested ) const;
	inline  BOOL    IsIntersect( const IRect& rDest ) const;
	inline  BOOL	IsTrueIntersect( const IRect& rDest ) const;

	/////////////////////////////////////////////////////////////////////
	// RECT Support
	IRect( const RECT& rc ){
		m_nX = rc.left; m_nY = rc.top;
		m_nCX = rc.right - rc.left; m_nCY = rc.bottom - rc.top;
	}
	inline IRect&	operator = ( const RECT& rc ){
		m_nX = rc.left; m_nY = rc.top;
		m_nCX = rc.right - rc.left; m_nCY = rc.bottom - rc.top;
		return  (*this);
	}
	inline BOOL		operator == ( const RECT& rc) const{   //operator  " == "
		return ( ( m_nX == rc.left ) && ( m_nY == rc.top ) && ( m_nX + m_nCX == rc.right ) && ( m_nY + m_nCY == rc.bottom ) );
	}
	inline BOOL		operator != ( const RECT& rc) const{
		return ( ( m_nX != rc.left ) || ( m_nY != rc.top ) || ( m_nX + m_nCX != rc.right ) || ( m_nY + m_nCY != rc.bottom ) );
	}
	inline IRect&	operator += ( const RECT& rc);
	inline IRect&	operator -= ( const RECT& rc);
	inline	operator RECT( ){
		RECT rc = { m_nX, m_nY, m_nX + m_nCX, m_nY + m_nCY };
		return rc;
	}
	inline  BOOL IsContain( const RECT& tested ) const;
	inline  BOOL IsContainBy( const RECT& tested ) const;

public:
	union
	{
		float m_nCX;
		float cx;
	};
	union
	{
		float m_nCY;
		float cy;
	};
};

inline IRect& IRect::operator = ( const IRect& rc )
{
	m_nX = rc.m_nX;
	m_nY = rc.m_nY;
	m_nCX = rc.m_nCX;
	m_nCY = rc.m_nCY;

	return  (*this);
}

inline IRect& IRect::operator = ( const IPoint& pt )
{
	m_nX = pt.m_nX;
	m_nY = pt.m_nY;
	return  (*this);
}

inline IRect&	IRect::operator |= ( const IRect& rc )
{
	float nTempX = m_nX;
	float nTempY = m_nY;
	m_nX = MIN( m_nX, rc.m_nX );
	m_nY = MIN( m_nY, rc.m_nY );
	m_nCX = MAX( nTempX + m_nCX, rc.m_nX + rc.m_nCX ) - m_nX;
	m_nCY = MAX( nTempY + m_nCY, rc.m_nY + rc.m_nCY ) - m_nY;
	return  (*this);
}


inline IRect& IRect::Assign( const IRect& rc )
{
	m_nX = rc.m_nX;
	m_nY = rc.m_nY;
	m_nCX = rc.m_nCX;
	m_nCY = rc.m_nCY;
	return  (*this);
}

inline void Adjust( const IPoint * pgpDest, const IPoint * pgpSour, IPoint& pt ){
	pt.m_nX += pgpSour->m_nX - pgpDest->m_nX;
	pt.m_nY += pgpSour->m_nY - pgpDest->m_nY;
}

inline BOOL IRect::Intersect( const IRect& rect1, const IRect& rect2 )
{
	float x0 = MAX( rect1.m_nX, rect2.m_nX ),
		y0 = MAX( rect1.m_nY, rect2.m_nY ),
		x1 = MIN( rect1.m_nX + rect1.m_nCX - 1, rect2.m_nX + rect2.m_nCX - 1 ) ,
		y1 = MIN( rect1.m_nY + rect1.m_nCY - 1, rect2.m_nY + rect2.m_nCY - 1 ) ;

	if( x0 > x1 || y0 > y1 ) 	
		return  FALSE;

	m_nX = x0;
	m_nY = y0;
	m_nCX = x1 - x0 + 1;
	m_nCY = y1 - y0 + 1;

	return  TRUE ;
}


inline BOOL IRect::IsTrueIntersect( const IRect& rDest ) const
{
	float xLeftUp	= MAX( m_nX, rDest.m_nX ),
		yLeftUp		= MAX( m_nY, rDest.m_nY ),
		xRightDown	= MIN( m_nX + m_nCX - 1, rDest.m_nX + rDest.m_nCX - 1 ) ,
		yRightDown	= MIN( m_nY + m_nCY - 1, rDest.m_nY + rDest.m_nCY - 1 ) ;

	if( xLeftUp >= xRightDown || yLeftUp >= yRightDown ) 	
		return FALSE;
	else
		return TRUE ;
}

/*******************************************************************************
* 函数名称 : IRect::IsIntersect
* 功能描述 : 连个rect是否有相交
* 参　　数 : const IRect& rDest
* 返 回 值 : inlineBOOL 
* 作　　者 : david
* 设计日期 : 2010年12月31日
* 注    意 : * 修改日期     修改人    修改内容
*******************************************************************************/
inline BOOL IRect::IsIntersect( const IRect& rDest ) const
{
	float xLeftUp	= MAX( m_nX, rDest.m_nX ),
		yLeftUp		= MAX( m_nY, rDest.m_nY ),
		xRightDown  = MIN( m_nX + m_nCX - 1, rDest.m_nX + rDest.m_nCX - 1 ) ,
		yRightDown  = MIN( m_nY + m_nCY - 1, rDest.m_nY + rDest.m_nCY - 1 ) ;

	if( xLeftUp > xRightDown || yLeftUp > yRightDown )
		return FALSE;
	else
		return TRUE ;
}


inline BOOL IRect::Intersect( const IRect& rDest )
{
	float xLeftUp	= MAX( m_nX, rDest.m_nX ),
		yLeftUp		= MAX( m_nY, rDest.m_nY ),
		xRightDown  = MIN( m_nX + m_nCX - 1, rDest.m_nX + rDest.m_nCX - 1 ) ,
		yRightDown  = MIN( m_nY + m_nCY - 1, rDest.m_nY + rDest.m_nCY - 1 ) ;

	if( xLeftUp > xRightDown || yLeftUp > yRightDown )
		return  FALSE;

	m_nX  = xLeftUp;
	m_nY  = yLeftUp;
	m_nCX = LENGTH( xLeftUp, xRightDown );
	m_nCY = LENGTH( yLeftUp, yRightDown );

	return  TRUE;
}

inline IRect& IRect::Set( float x, float y, float width, float height )
{
	m_nX = x;
	m_nY = y;
	m_nCX = width;
	m_nCY = height;

	return (*this);
}


inline BOOL IRect::IsContain( const IRect& tested ) const
{
	return	(	( tested.m_nX >= m_nX ) && ( tested.m_nY >= m_nY ) &&
				( tested.m_nX + tested.m_nCX - 1 <= m_nX + m_nCX -1 ) &&
				( tested.m_nY + tested.m_nCY - 1 <= m_nY + m_nCY -1 )	);
}


inline BOOL	IRect::IsContain( const IPoint& pt ) const
{
	if( !ISIN( pt.m_nX, m_nX, m_nX + m_nCX - 1 ) || !ISIN( pt.m_nY, m_nY, m_nY + m_nCY - 1 ) )
		return FALSE;
	return TRUE;
}

inline BOOL	 IRect::IsContain( float x, float y ) const
{
	if( !ISIN( x, m_nX, m_nX + m_nCX - 1.0f ) || !ISIN( y, m_nY, m_nY + m_nCY - 1.0f ) )
		return FALSE;
	return TRUE;
}

inline BOOL IRect::operator != ( const IRect& rc ) const
{
	if(( fabs(m_nX - rc.m_nX) > 0.0001 ) || ( fabs(m_nY - rc.m_nY) > 0.0001 ) || ( fabs(m_nCX - rc.m_nCX) > 0.0001 ) || ( fabs(m_nCY - rc.m_nCY) > 0.0001 ))
		return TRUE;
	else
		return FALSE;
}

inline BOOL IRect::operator == ( const IRect& rc ) const
{
	if( ( fabs(m_nX - rc.m_nX )) > 0.0001 || ( fabs(m_nY - rc.m_nY) > 0.0001 ) || ( fabs(m_nCX - rc.m_nCX) > 0.0001 ) || ( fabs(m_nCY - rc.m_nCY) > 0.0001 ) )
		return FALSE;
	else
		return TRUE;
}

inline IRect& IRect::operator += ( const IRect& rc )
{
	IPoint	gpRightDown = *(IPoint*)this;
	gpRightDown.m_nX += m_nCX;
	gpRightDown.m_nY += m_nCY;

	if ( gpRightDown.m_nX < rc.m_nX + rc.m_nCX )
		gpRightDown.m_nX = rc.m_nX + rc.m_nCX;
	if ( gpRightDown.m_nY < rc.m_nY + rc.m_nCY )
		gpRightDown.m_nY = rc.m_nY + rc.m_nCY;

	if ( m_nX > rc.m_nX )
		m_nX = rc.m_nX;
	if ( m_nY > rc.m_nY )
		m_nY = rc.m_nY;

	m_nCX = gpRightDown.m_nX - m_nX;
	m_nCY = gpRightDown.m_nY - m_nY;

	return (*this);
}

inline IRect& IRect::operator -= ( const IRect& rc )
{
	if( IsIntersect( rc ) )
	{
		m_nX =	MIN( m_nX, rc.m_nX );
		m_nY =	MIN( m_nX, rc.m_nY );
		m_nCX = m_nX - rc.m_nX + 1;
		m_nCY = m_nY - rc.m_nY + 1;
	}
	return (*this);
}

inline IRect& IRect::operator += ( const RECT& rc )
{
	m_nX =	MIN( m_nX, rc.left );
	m_nY =  MIN( m_nY, rc.top );
	m_nCX = MAX( m_nX + m_nCX, rc.right );
	m_nCY = MAX( m_nY + m_nCY, rc.bottom );

	return (*this);
}

inline IRect& IRect::operator -= ( const RECT& rc )
{
	if( IsContain( IRect( rc ) ) )
	{
		m_nCX = m_nX - rc.left + 1;
		m_nCY = m_nY - rc.top + 1;
	}
	return (*this);
}

inline BOOL IRect::IsContain(const RECT& tested ) const
{
	return	(	( tested.left >= m_nX ) && ( tested.top >= m_nY ) &&
				( tested.right <= m_nY + m_nCX - 1 ) &&
				( tested.bottom <= m_nY + m_nCY - 1 ) );
}

inline BOOL IRect::IsContainBy(const RECT& tested ) const
{
	return	(	( m_nX >= tested.left ) && ( m_nY >= tested.top ) &&
				( m_nX + m_nCX - 1 <= tested.right ) &&
				( m_nY + m_nCY - 1 <= tested.bottom ) );
}


inline BOOL IRect::operator >= ( const IRect& rc ) const
{
	if( ( m_nX >= rc.m_nX ) && ( m_nY >= rc.m_nY ) && ( m_nCX >= rc.m_nCX ) && ( m_nCY >= rc.m_nCY ) )
		return TRUE;
	else
		return FALSE;
}

inline BOOL IRect::operator <= ( const IRect& rc ) const
{
	if( ( m_nX <= rc.m_nX ) && ( m_nY <= rc.m_nY ) && ( m_nCX <= rc.m_nCX ) && ( m_nCY <= rc.m_nCY ) )
		return TRUE;
	else
		return FALSE;
}
