#pragma once

#include  <float.h>
#include "Point.h"
#include "dbg.h"
#include "vector.h"

#include "def.h"

//////////////////////////////////////////////////////////////////////////////
// ���봦����

/*
	����ľ����Ƿ���ָ����Χ֮��
*/
inline BOOL IsDistIn( const IPoint& pt0, const IPoint& pt1, const float nDist )
{	
	return ( fabs( pt0.m_nX - pt1.m_nX ) < nDist ) && ( fabs( pt0.m_nY - pt1.m_nY ) < nDist );
}
/*
	���������������
*/
inline float FastDist( const IPoint& pt0, const IPoint& pt1 )
{
	return fabs( pt0.m_nX - pt1.m_nX ) +  fabs( pt0.m_nY - pt1.m_nY );
}
/*
	���������������
*/
inline float FastDist( float x0, float y0, float x1, float y1 )
{
	return fabs( x1 - x0 ) + fabs( y1 - y0 );
}
/*
	����һ����ԭ��֮��ľ���
*/
inline float Dist( float x, float y )
{
    return ( sqrtf( x * x + y * y ) ) ; 
}

/*
	��������֮�����
*/
inline float Dist( float x0, float y0, float x1, float y1 )
{
    return Dist( MAX( x0, x1 ) - MIN( x0, x1 ), MAX( y0, y1 ) - MIN( y0, y1 ) );
}

/*
	��������֮�����
*/
inline float Dist( const IPoint& pt0, const IPoint& pt1 )
{
    return Dist( MAX( pt0.m_nX, pt1.m_nX ) - MIN( pt0.m_nX, pt1.m_nX ),MAX( pt0.m_nY, pt1.m_nY ) - MIN( pt0.m_nY, pt1.m_nY ) );
}

/*
��������֮�����
*/

//by 
/*
inline int Dist( const vect2_t& pt0, const vect2_t& pt1 )
{
	return Dist( MAX( pt0.x, pt1.x ) - MIN( pt0.x, pt1.x ),MAX( pt0.y, pt1.y ) - MIN( pt0.y, pt1.y ) );
}
*/

/*
	�������ƽ����
*/
inline float SquareAdd( float x0, float y0, float x1, float y1 )
{
	return ( x1 - x0 ) * ( x1 - x0 ) + ( y1 - y0 ) * ( y1 - y0 );
}

/*
	�������ƽ����
*/
inline float SquareAdd( const IPoint& pt0, const IPoint& pt1 )
{
	return ( pt0.m_nX - pt1.m_nX ) * ( pt0.m_nX - pt1.m_nX ) + ( pt0.m_nY - pt1.m_nY ) * ( pt0.m_nY - pt1.m_nY );
}
/*
	�ж���������Ƿ���ָ����Χ֮��
	ptBegin	��ʼ��
	ptEnd	Ŀ���
	nMax	������
	nMin	��С����
*/
ENGINE_GLOBAL BOOL	IsRange( const IPoint & ptBegin,const IPoint & ptEnd,int nMax,int nMin );
/*
	�ж���������Ƿ������Χ֮��
	ptBegin	��ʼ��
	ptEnd	Ŀ���
	nMax	������
*/
ENGINE_GLOBAL BOOL	IsMaxRange( const IPoint & ptBegin,const IPoint & ptEnd,int nMax);
/*
	�ж���������Ƿ�����С��Χ֮��
	ptBegin	��ʼ��
	ptEnd	Ŀ���
	nMin	��С����
*/
ENGINE_GLOBAL BOOL	IsMinRange( const IPoint & ptBegin,const IPoint & ptEnd,int nMin );

/*
	�������֮�����ߵļн���X��ĽǶ�
	ptBegin	��ʼ��
	ptEnd	Ŀ���
*/
ENGINE_GLOBAL float GetAngle( const IPoint &ptStart, const IPoint &ptEnd );
/*
	��һ�㰴��ָ���ĽǶȺ��ٶ��ƶ�
	ptOut	Ŀ�ĵ�
	ptCur	��ǰ��
*/
ENGINE_GLOBAL void MoveForAngle( IPoint &ptOut, const IPoint &ptCur, float fAngle, float fSpeed );

