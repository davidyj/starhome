#include "../stdafx.h"
#include "Geo.h"

ENGINE_GLOBAL BOOL	IsRange( const IPoint & ptBegin, const IPoint & ptEnd, int nMax, int nMin )
{
	int cx = abs( ptBegin.m_nX - ptEnd.m_nX );
	int cy = abs( ptBegin.m_nY - ptEnd.m_nY );
	if( ( cx <= nMax && cy <= nMax ) && ( cx > nMin || cy > nMin ) )
		return true;

	return false;
}

ENGINE_GLOBAL BOOL	IsMaxRange( const IPoint & ptBegin, const IPoint & ptEnd, int nMax)
{
	int cx = abs( ptBegin.m_nX - ptEnd.m_nX );
	int cy = abs( ptBegin.m_nY - ptEnd.m_nY );
	if( cx <= nMax && cy <= nMax )
		return true;

	return false;
}

ENGINE_GLOBAL BOOL IsMinRange( const IPoint & ptBegin, const IPoint & ptEnd, int nMin )
{
	int cx = abs( ptBegin.m_nX - ptEnd.m_nX );
	int cy = abs( ptBegin.m_nY - ptEnd.m_nY );
	if(	cx > nMin || cy > nMin )	
		return true;

	return false;
}

ENGINE_GLOBAL float GetAngle( const IPoint &ptStart, const IPoint &ptEnd )
{
	float fAngle;
	IPoint ptDir;
	ptDir.m_nX = ptStart.m_nX - ptEnd.m_nX;
	ptDir.m_nY = ptStart.m_nY - ptEnd.m_nY;


	if( ptDir.m_nX > 0.0f )
		fAngle = -atanf( (float)ptDir.m_nY / (float)ptDir.m_nX ) + G_PI / 2;
	else if( ptDir.m_nX < 0.0f )
		fAngle = -atanf( (float)ptDir.m_nY / (float)ptDir.m_nX  ) - G_PI / 2;
	else
	{
		if( ptDir.m_nY > 0  )
			fAngle = 0;
		else
			fAngle = -G_PI;
	}

	return fAngle;
}
ENGINE_GLOBAL void MoveForAngle( IPoint &ptOut, const IPoint &ptCur, float fAngle, float fSpeed )
{
	ptOut.m_nY = ptCur.m_nY + ( cosf( fAngle + G_PI ) * fSpeed );
	ptOut.m_nX = ptCur.m_nX + ( sinf( fAngle + G_PI ) * fSpeed );
}
