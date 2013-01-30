#pragma once

#include  <float.h>
#include "Point.h"
#include "dbg.h"
#include "vector.h"

#include "def.h"

//////////////////////////////////////////////////////////////////////////////
// 距离处理函数

/*
	两点的距离是否在指定范围之内
*/
inline BOOL IsDistIn( const IPoint& pt0, const IPoint& pt1, const float nDist )
{	
	return ( fabs( pt0.m_nX - pt1.m_nX ) < nDist ) && ( fabs( pt0.m_nY - pt1.m_nY ) < nDist );
}
/*
	快速求出两点间距离
*/
inline float FastDist( const IPoint& pt0, const IPoint& pt1 )
{
	return fabs( pt0.m_nX - pt1.m_nX ) +  fabs( pt0.m_nY - pt1.m_nY );
}
/*
	快速求出两点间距离
*/
inline float FastDist( float x0, float y0, float x1, float y1 )
{
	return fabs( x1 - x0 ) + fabs( y1 - y0 );
}
/*
	计算一点与原点之间的距离
*/
inline float Dist( float x, float y )
{
    return ( sqrtf( x * x + y * y ) ) ; 
}

/*
	计算两点之间距离
*/
inline float Dist( float x0, float y0, float x1, float y1 )
{
    return Dist( MAX( x0, x1 ) - MIN( x0, x1 ), MAX( y0, y1 ) - MIN( y0, y1 ) );
}

/*
	计算两点之间距离
*/
inline float Dist( const IPoint& pt0, const IPoint& pt1 )
{
    return Dist( MAX( pt0.m_nX, pt1.m_nX ) - MIN( pt0.m_nX, pt1.m_nX ),MAX( pt0.m_nY, pt1.m_nY ) - MIN( pt0.m_nY, pt1.m_nY ) );
}

/*
计算两点之间距离
*/

//by 
/*
inline int Dist( const vect2_t& pt0, const vect2_t& pt1 )
{
	return Dist( MAX( pt0.x, pt1.x ) - MIN( pt0.x, pt1.x ),MAX( pt0.y, pt1.y ) - MIN( pt0.y, pt1.y ) );
}
*/

/*
	求两点的平方和
*/
inline float SquareAdd( float x0, float y0, float x1, float y1 )
{
	return ( x1 - x0 ) * ( x1 - x0 ) + ( y1 - y0 ) * ( y1 - y0 );
}

/*
	求两点的平方和
*/
inline float SquareAdd( const IPoint& pt0, const IPoint& pt1 )
{
	return ( pt0.m_nX - pt1.m_nX ) * ( pt0.m_nX - pt1.m_nX ) + ( pt0.m_nY - pt1.m_nY ) * ( pt0.m_nY - pt1.m_nY );
}
/*
	判定两点距离是否在指定范围之内
	ptBegin	起始点
	ptEnd	目标点
	nMax	最大距离
	nMin	最小距离
*/
ENGINE_GLOBAL BOOL	IsRange( const IPoint & ptBegin,const IPoint & ptEnd,int nMax,int nMin );
/*
	判定两点距离是否在最大范围之内
	ptBegin	起始点
	ptEnd	目标点
	nMax	最大距离
*/
ENGINE_GLOBAL BOOL	IsMaxRange( const IPoint & ptBegin,const IPoint & ptEnd,int nMax);
/*
	判定两点距离是否在最小范围之内
	ptBegin	起始点
	ptEnd	目标点
	nMin	最小距离
*/
ENGINE_GLOBAL BOOL	IsMinRange( const IPoint & ptBegin,const IPoint & ptEnd,int nMin );

/*
	获得两点之间连线的夹角与X轴的角度
	ptBegin	起始点
	ptEnd	目标点
*/
ENGINE_GLOBAL float GetAngle( const IPoint &ptStart, const IPoint &ptEnd );
/*
	将一点按照指定的角度和速度移动
	ptOut	目的点
	ptCur	当前点
*/
ENGINE_GLOBAL void MoveForAngle( IPoint &ptOut, const IPoint &ptCur, float fAngle, float fSpeed );

