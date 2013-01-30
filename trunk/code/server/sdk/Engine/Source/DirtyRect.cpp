#include "../stdafx.h"
#include "DirtyRect.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDirtyRect::CDirtyRect()
{
}

CDirtyRect::~CDirtyRect()
{
	Release( );
}

BOOL CDirtyRect::Build( )
{
	m_RectArray.EnsureCapacity( 50 );

	return true;
}

void CDirtyRect::Release( )
{
	m_RectArray.Purge( );
}

void CDirtyRect::SetMaxRect( const IRect & rc ) 
{
	m_rcMax = rc;
}

void CDirtyRect::Add( IRect & rc )
{
	if(! rc.Intersect( m_rcMax ) )
		return;

	IRect rcClip;
	IRect rcSum;
	for( int i = 0; i < m_RectArray.Count( ); i++ )
	{
loop1:;
		if( rcClip.Intersect( rc, m_RectArray[i] ) )
		{
			int nClipSize		= rcClip.cx * rcClip.cy;
			int nNewSize		= rc.cx * rc.cy;
			int nSize			= m_RectArray[i].cx * m_RectArray[i].cy;
			rcSum = rc;
			rcSum += m_RectArray[i];
			int nSumSize = rcSum.cx * rcSum.cy;
			if( nSumSize - nSize - nNewSize <= nClipSize )
			{
				rc = rcSum;
				if( Remove( i ) )
					goto loop1;
				else 
					goto out1;
			}
		}
	}
out1:;
	m_RectArray.AddToTail( rc );
}

BOOL CDirtyRect::Remove( int i )
{
	if( i == m_RectArray.Count( ) - 1 )
	{
		//最后一个
		m_RectArray.Remove( i );
		return false;
	}

	m_RectArray.Remove( i );

	return true;
}
