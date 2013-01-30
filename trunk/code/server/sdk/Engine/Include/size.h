#pragma once

#include <math.h>
#include "BaseObj.h"

class ENGINE_CLASS ISize : public IBaseObj
{
	DECLARE_CLASS(ISize)
public:
	/////////////////////////////////////////////////////////////////////
	// Construct & Destruct
	ISize( ){ m_nX = 0;	m_nY = 0; }
	ISize( int x, int y ){	m_nX = x;	m_nY = y; }
	virtual ~ISize( ){ }

	/////////////////////////////////////////////////////////////////////
	// Operator
	inline	ISize& operator =	( const ISize& pt );
	inline	ISize& operator += ( const ISize& pt );
	inline	ISize& operator -= ( const ISize& pt );
	inline	ISize& operator *= ( const ISize& pt );
	inline	ISize& operator /= ( const ISize& pt );
	inline	ISize	operator +	( const ISize& pt );
	inline	ISize	operator -	( const ISize& pt );
	inline	BOOL	operator == ( const ISize& pt ) const;
	inline	BOOL	operator != ( const ISize& pt ) const;

	/////////////////////////////////////////////////////////////////////
	// Method
	inline	ISize& Set( int x, int y );
	inline  BOOL	IsCloseTo( const ISize& pt, int nDist ) const;

	inline  int		X( )	{ return m_nX; }
	inline  int		Y( )	{ return m_nY; }

	inline  int&	RefX( )	{ return m_nX; }
	inline  int&	RefY( )	{ return m_nY; }

	inline  int		GetX( )	{ return  m_nX; }
	inline  int		GetY( )	{ return  m_nY; }

	void	SetX( int x )	{ m_nX = x; }
	void	SetY( int y )	{ m_nY = y; }

public:
	union
	{
		int m_nX;
		int x;
	};
	union
	{
		int m_nY;
		int y;
	};
};

inline ISize& ISize::Set( int x , int y )
{
	m_nX = x;
	m_nY = y;
	return (*this);
}

inline BOOL ISize::IsCloseTo( const ISize& pt, int nDist ) const 
{
	if( ( abs( m_nX - pt.m_nX ) < nDist ) && ( abs( m_nX - pt.m_nY ) < nDist ) )
		return TRUE;
	else
		return FALSE;
}

inline BOOL ISize::operator != ( const ISize& pt ) const
{
	if( ( m_nX == pt.m_nX ) && ( m_nY == pt.m_nY ) )
		return FALSE;
	else
		return TRUE;
}

inline BOOL ISize::operator == ( const ISize& pt ) const
{
	if( ( m_nX == pt.m_nX ) && ( m_nY == pt.m_nY ) )
		return TRUE;
	else
		return FALSE;
}

inline ISize ISize::operator - ( const ISize& pt )
{
	ISize ptTmp;
	ptTmp.m_nX = m_nX - pt.m_nX;
	ptTmp.m_nY = m_nY - pt.m_nY;
	return ptTmp;
} 

inline ISize ISize::operator + ( const ISize& pt )
{
	ISize ptTmp;
	ptTmp.m_nX = m_nX + pt.m_nX;
	ptTmp.m_nY = m_nY + pt.m_nY;
	return ptTmp;
}

inline ISize& ISize::operator -= ( const ISize& pt )
{
	m_nX -= pt.m_nX;
	m_nY -= pt.m_nY;
	return (*this);
}

inline ISize& ISize::operator *= ( const ISize& pt )
{   
	m_nX *= pt.m_nX;
	m_nY *= pt.m_nY;
	return (*this);
}

inline ISize& ISize::operator /= ( const ISize& pt )
{   
	m_nX /= pt.m_nX;
	m_nY /= pt.m_nY;
	return (*this);
}


inline ISize& ISize::operator += ( const ISize& pt )
{
	m_nX += pt.m_nX;
	m_nY += pt.m_nY;
	return (*this);
}

inline ISize& ISize::operator = (const ISize& pt )
{
	m_nX = pt.m_nX;
	m_nY = pt.m_nY;
	return (*this);
}


