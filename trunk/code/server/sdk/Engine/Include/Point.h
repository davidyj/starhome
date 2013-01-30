#pragma once

#include <math.h>
#include "BaseObj.h"

class ENGINE_CLASS IPoint : public IBaseObj
{
	DECLARE_CLASS(IPoint)
public:
	/////////////////////////////////////////////////////////////////////
	// Construct & Destruct
	IPoint( ){ m_nX = 0.0f;	m_nY = 0.0f; }
	IPoint( float x, float y ){	m_nX = x;	m_nY = y; }

	virtual ~IPoint( ){ }

	/////////////////////////////////////////////////////////////////////
	// Operator
	inline	IPoint& operator =	( const IPoint& pt );
	inline	IPoint& operator += ( const IPoint& pt );
	inline	IPoint& operator -= ( const IPoint& pt );
	inline	IPoint& operator *= ( const IPoint& pt );
	inline	IPoint& operator /= ( const IPoint& pt );
	inline	IPoint	operator +	( const IPoint& pt );
	inline	IPoint	operator -	( const IPoint& pt );
	inline	BOOL	operator == ( const IPoint& pt ) const;
	inline	BOOL	operator != ( const IPoint& pt ) const;

	/////////////////////////////////////////////////////////////////////
	// Method
	inline	IPoint& Set( float x, float y );
	inline  BOOL	IsCloseTo( const IPoint& pt, float nDist ) const;

	inline  float		X( )	{ return m_nX; }
	inline  float		Y( )	{ return m_nY; }

	inline  float		GetX( )	{ return  m_nX; }
	inline  float		GetY( )	{ return  m_nY; }

	void	SetX( float x )	{ m_nX = x; }
	void	SetY( float y )	{ m_nY = y; }

public:
	union
	{
		float x;
		float m_nX;
	};
	union
	{
		float y;
		float m_nY;
	};
};

inline IPoint& IPoint::Set( float x , float y )
{
	m_nX = x;
	m_nY = y;
	return (*this);
}

inline BOOL IPoint::IsCloseTo( const IPoint& pt, float nDist ) const 
{
	if( ( fabs( m_nX - pt.m_nX ) < nDist ) && ( fabs( m_nX - pt.m_nY ) < nDist ) )
		return TRUE;
	else
		return FALSE;
}

inline BOOL IPoint::operator != ( const IPoint& pt ) const
{
	if((fabs(m_nX - pt.m_nX) < 0.0001) && (fabs(m_nY - pt.m_nY) < 0.0001))
		return FALSE;
	else
		return TRUE;
}

inline BOOL IPoint::operator == ( const IPoint& pt ) const
{
	if((fabs(m_nX - pt.m_nX) < 0.0001) && (fabs(m_nY - pt.m_nY) < 0.0001))
		return TRUE;
	else
		return FALSE;
}

inline IPoint IPoint::operator - ( const IPoint& pt )
{
	IPoint ptTmp;
	ptTmp.m_nX = m_nX - pt.m_nX;
	ptTmp.m_nY = m_nY - pt.m_nY;
	return ptTmp;
} 

inline IPoint IPoint::operator + ( const IPoint& pt )
{
	IPoint ptTmp;
	ptTmp.m_nX = m_nX + pt.m_nX;
	ptTmp.m_nY = m_nY + pt.m_nY;
	return ptTmp;
}

inline IPoint& IPoint::operator -= ( const IPoint& pt )
{
	m_nX -= pt.m_nX;
	m_nY -= pt.m_nY;
	return (*this);
}

inline IPoint& IPoint::operator *= ( const IPoint& pt )
{   
	m_nX *= pt.m_nX;
	m_nY *= pt.m_nY;
	return (*this);
}

inline IPoint& IPoint::operator /= ( const IPoint& pt )
{   
	m_nX /= pt.m_nX;
	m_nY /= pt.m_nY;
	return (*this);
}


inline IPoint& IPoint::operator += ( const IPoint& pt )
{
	m_nX += pt.m_nX;
	m_nY += pt.m_nY;
	return (*this);
}

inline IPoint& IPoint::operator = (const IPoint& pt )
{
	m_nX = pt.m_nX;
	m_nY = pt.m_nY;
	return (*this);
}