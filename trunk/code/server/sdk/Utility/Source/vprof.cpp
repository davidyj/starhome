//========= Copyright ?1996-2001, Valve LLC, All rights reserved. ============
//
// Purpose: Real-Time Hierarchical Profiling
//
// $NoKeywords: $
//=============================================================================

#include "../stdafx.h"
#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4786)
#pragma warning(disable:4530)
#pragma warning(disable:4267)
#endif
#include <map>
#include <vector>
#include <algorithm>
#ifdef WIN32
#pragma warning(pop)
#endif

#include "vprof.h"

#ifdef WIN32

//static int g_nConsoleTop = CONSOLE_TOP;
#endif

// NOTE: Explicitly and intentionally using STL in here to not generate any
// cyclical dependencies between the low-level debug library and the higher
// level data structures (toml 01-27-03)
using namespace std;

//-----------------------------------------------------------------------------
static int g_nDebugOutLine = 0;
int	GetDebugOutLine()
{
	return g_nDebugOutLine;
}

void Print(const char* pszfmt,...)
{
#ifdef WIN32
	va_list arg_ptr;
	va_start(arg_ptr, pszfmt);
	vprintf(pszfmt,arg_ptr);
	va_end(arg_ptr);

	ConsoleScroll(g_nConsoleTop,CONSOLE_BOTTOM);
#else

#define SCR
#ifdef SCR
	char stmp[512];
	va_list arg_ptr;
	va_start(arg_ptr, pszfmt);
	vsprintf(stmp,pszfmt,arg_ptr);
	va_end(arg_ptr);
	printf("%s",stmp);
#else
	if( udsvr::IsConn() )
	{
		///*
		char stmp[512];
		va_list arg_ptr;
		va_start(arg_ptr, pszfmt);
		vsprintf(stmp,pszfmt,arg_ptr);
		va_end(arg_ptr);

		udsvr::tomoniter::SendToMoniter( stmp );
		//*/
	}
#endif

#endif

}

void Print(int nLine,const char* psz,...)
{
#ifdef WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	//保存光标位置
	if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
	{
		return;
	}

	//跳转
	COORD curPos=csbiInfo.dwSize;
	curPos.X=0;
	curPos.Y=nLine;
	SetConsoleCursorPosition(hStdout,curPos);
/*
#endif
*/
	va_list arg_ptr;
//	int j=0;
	va_start(arg_ptr, psz);
	vprintf(psz,arg_ptr);
	va_end(arg_ptr);
/*
#ifdef WIN32
*/
	if(nLine>=g_nConsoleTop)
		g_nConsoleTop=nLine+1;
	//恢复光标位置
	//SetConsoleCursorPosition(hStdout,csbiInfo.dwCursorPosition);

	curPos=csbiInfo.dwCursorPosition;
	if(curPos.Y<g_nConsoleTop)
		curPos.Y=g_nConsoleTop;
	SetConsoleCursorPosition(hStdout,curPos);
#else

	//	printf( "Print line %s\n", udsvr::IsConn()?"true":"false" );
	if( udsvr::IsConn() )
	{
		//*
		char stmp[512];
		memset(stmp,0,512);
		va_list arg_ptr;
		va_start(arg_ptr, psz);
		vsprintf(stmp,psz,arg_ptr);
		va_end(arg_ptr);

		udsvr::tomoniter::SendToMoniter( nLine, stmp );
		//*/
	}

#endif

}


#ifdef VPROF_ENABLED

//-----------------------------------------------------------------------------
// Singleton interface
//-----------------------------------------------------------------------------
//CVProfile g_VProfCurrentProfile;
CVProfile & VProfCurrentProfile( )
{
//	return g_VProfCurrentProfile;
	static CVProfile s_VProfCurrentProfile;
	return s_VProfCurrentProfile;
}

#ifdef WIN32

void ConsoleScroll(int nTop,int nBottom)
{

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	SMALL_RECT srctScrollRect, srctClipRect;
	CHAR_INFO chiFill;
	COORD coordDest;

	HANDLE hStdout;

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Get the screen buffer size.

	if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
	{
		printf("GetConsoleScreenBufferInfo failed %d\n", GetLastError());
		return;
	}


	//CONSOLE_SCREEN_BUFFER_INFO  buffinfo;
	//GetConsoleScreenBufferInfo(hStdout,&buffinfo);
	if(csbiInfo.dwCursorPosition.Y< csbiInfo.dwSize.Y-1-nBottom-1)
	{
		return;
	}

	// The scrolling rectangle is the bottom 15 rows of the
	// screen buffer.
	srctScrollRect.Top =    nTop;
	srctScrollRect.Bottom = csbiInfo.dwSize.Y -1-nBottom;
	srctScrollRect.Left = 0;
	srctScrollRect.Right = csbiInfo.dwSize.X - 1;

	// The destination for the scroll rectangle is one row up.

	coordDest.X = 0;
	coordDest.Y = nTop-1;

	// The clipping rectangle is the same as the scrolling rectangle.
	// The destination row is left unchanged.

	srctClipRect = srctScrollRect;

	// Fill the bottom row with green blanks.

	chiFill.Attributes = 0;//BACKGROUND_INTENSITY| FOREGROUND_INTENSITY;
	chiFill.Char.AsciiChar = (char)' ';

	// Scroll up one line.

	if(!ScrollConsoleScreenBuffer(
		hStdout,         // screen buffer handle
		&srctScrollRect, // scrolling rectangle
		&srctClipRect,   // clipping rectangle
		coordDest,       // top left destination cell
		&chiFill))       // fill character and color
	{
		printf("ScrollConsoleScreenBuffer failed %d\n", GetLastError());
		return;
	}

	COORD curPos=csbiInfo.dwSize;
	curPos.X=0;
	curPos.Y=csbiInfo.dwSize.Y -1-nBottom-2;

	SetConsoleCursorPosition(hStdout,curPos);

}

void ConsoleSetSize(int nCharLen,int nLine)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
	{
		return;
	}


	COORD sz={nCharLen,nLine};
	/*BOOL bRet = */SetConsoleScreenBufferSize(hStdout,sz);

	//这里设置窗口大小
	//SMALL_RECT rt={0,0,nCharLen-1,nLine-1};
	//SetConsoleWindowInfo(hStdout,1,&rt);

}


//////////////////////////////////////////////////////////////////////////
//
class CMemoryRegion
{
public:
	CMemoryRegion( unsigned maxSize, unsigned commitSize = 0 );
	~CMemoryRegion();

	bool Init();
	void Term();

	void *Alloc( unsigned bytes );
	void FreeAll();

	void Access( void **ppRegion, unsigned *pBytes );

private:
	unsigned char *m_pNextAlloc;
	unsigned char *m_pCommitLimit;

	unsigned char *m_pBase;
	unsigned	   m_commitSize;
	unsigned	   m_size;
#ifdef _DEBUG
	unsigned char *m_pAllocLimit;
#endif
};

//-------------------------------------

CMemoryRegion::CMemoryRegion( unsigned maxSize, unsigned commitSize )
 : 	m_pBase( NULL ),
 	m_commitSize( commitSize ),
 	m_size( maxSize )
{
	Init();
}

//-------------------------------------

CMemoryRegion::~CMemoryRegion()
{
	Term();
}

//-------------------------------------

bool CMemoryRegion::Init()
{
	Assert( !m_pBase );

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	if ( m_commitSize == 0 )
	{
		m_commitSize = sysInfo.dwPageSize;
	}
	else if ( m_commitSize % sysInfo.dwPageSize != 0 )
	{
		m_commitSize = m_commitSize + ( sysInfo.dwPageSize  - ( m_commitSize % sysInfo.dwPageSize ) );
	}

	if ( m_size % m_commitSize != 0 )
		m_size = m_size + ( m_commitSize - ( m_size % m_commitSize ) );

	Assert( m_size % sysInfo.dwPageSize == 0 && m_commitSize % sysInfo.dwPageSize == 0 && m_commitSize <= m_size );

	m_pBase = (unsigned char *)VirtualAlloc( NULL, m_size, MEM_RESERVE, PAGE_NOACCESS );
	Assert( m_pBase );
	m_pCommitLimit = m_pNextAlloc = m_pBase;

#ifdef _DEBUG
	m_pAllocLimit = m_pBase + m_size;
#endif

	return ( m_pBase != NULL );
}

//-------------------------------------

void *CMemoryRegion::Alloc( unsigned bytes )
{
	Assert( m_pBase );
	Assert( bytes <= m_commitSize );

	void *pResult = m_pNextAlloc;
	m_pNextAlloc += bytes;

	if ( m_pNextAlloc > m_pCommitLimit )
	{
		Assert( m_pCommitLimit + m_commitSize < m_pAllocLimit );
		if ( !VirtualAlloc( m_pCommitLimit, m_commitSize, MEM_COMMIT, PAGE_READWRITE ) )
		{
			Assert( 0 );
			return NULL;
		}
		m_pCommitLimit += m_commitSize;
	}

	return pResult;
}

//-------------------------------------

void CMemoryRegion::FreeAll()
{
	if ( m_pBase && m_pCommitLimit - m_pBase > 0 )
	{
		VirtualFree( m_pBase, m_pCommitLimit - m_pBase, MEM_DECOMMIT );
		m_pCommitLimit = m_pNextAlloc = m_pBase;
	}
}

//-------------------------------------

void CMemoryRegion::Term()
{
	FreeAll();
	if ( m_pBase )
	{
		VirtualFree( m_pBase, 0, MEM_RELEASE );
		m_pBase = NULL;
	}
}

//-------------------------------------

void CMemoryRegion::Access( void **ppRegion, unsigned *pBytes )
{
	*ppRegion = m_pBase;
	*pBytes = ( m_pNextAlloc - m_pBase);
}

//-----------------------------------------------------------------------------
// Singleton interface
//-----------------------------------------------------------------------------
CMemoryRegion g_NodeMemRegion( 0x400000, 0x10000 );
CMemoryRegion & NodeMemRegion( )
{
	static CMemoryRegion s_NodeMemRegion( 0x400000, 0x10000 );
	return s_NodeMemRegion;
}

//-------------------------------------

void *CVProfNode::operator new( size_t bytes )
{
	return g_NodeMemRegion.Alloc( bytes );
}

//-------------------------------------

void CVProfNode::FreeAll()
{
	g_NodeMemRegion.FreeAll();
}


//-----------------------------------------------------------------------------

#else

//-----------------------------------------------------------------------------

void *CVProfNode::operator new( size_t bytes )
{
	return ::new char[bytes];
}

//-------------------------------------

void CVProfNode::operator delete( void *p )
{
	//::delete [] p;
	::delete [] (char *)p;
}
#endif

//-------------------------------------

CVProfNode *CVProfNode::GetSubNode( const char *pszName, int detailLevel, const char *pBudgetGroupName )
{
	// Try to find this sub node
	CVProfNode * child = m_pChild;
	while ( child )
	{
		if ( child->m_pszName == pszName )
		{
			return child;
		}
		child = child->m_pSibling;
	}

	// We didn't find it, so add it
	CVProfNode * node = new CVProfNode( pszName, detailLevel, this, pBudgetGroupName );
	node->m_pSibling = m_pChild;
	m_pChild = node;
	return node;
}

//-------------------------------------

void CVProfNode::Pause()
{
	if ( m_nRecursions > 0 )
	{
		m_Timer.End();
		m_CurFrameTime += m_Timer.GetDuration();
	}
	if ( m_pChild )
	{
		m_pChild->Pause();
	}
	if ( m_pSibling )
	{
		m_pSibling->Pause();
	}
}

//-------------------------------------

void CVProfNode::Resume()
{
	if ( m_nRecursions > 0 )
	{
		m_Timer.Start();
	}
	if ( m_pChild )
	{
		m_pChild->Resume();
	}
	if ( m_pSibling )
	{
		m_pSibling->Resume();
	}
}

//-------------------------------------

void CVProfNode::Reset()
{
	m_nPrevFrameCalls = 0;
	m_PrevFrameTime.Init();

	m_nCurFrameCalls = 0;
	m_CurFrameTime.Init();

	m_nTotalCalls = 0;
	m_TotalTime.Init();

	m_PeakTime.Init();

	if ( m_pChild )
	{
		m_pChild->Reset();
	}
	if ( m_pSibling )
	{
		m_pSibling->Reset();
	}
}


//-------------------------------------

void CVProfNode::MarkFrame()
{
	m_nPrevFrameCalls = m_nCurFrameCalls;
	m_PrevFrameTime = m_CurFrameTime;

	m_nTotalCalls += m_nCurFrameCalls;
	m_TotalTime += m_CurFrameTime;

	if ( m_PeakTime.IsLessThan( m_CurFrameTime ) )
		m_PeakTime = m_CurFrameTime;

	m_CurFrameTime.Init();
	m_nCurFrameCalls = 0;

	if ( m_pChild )
	{
		m_pChild->MarkFrame();
	}
	if ( m_pSibling )
	{
		m_pSibling->MarkFrame();
	}
}

//-------------------------------------

void CVProfNode::ResetPeak()
{
	m_PeakTime.Init();

	if ( m_pChild )
	{
		m_pChild->ResetPeak();
	}
	if ( m_pSibling )
	{
		m_pSibling->ResetPeak();
	}
}

//-----------------------------------------------------------------------------

struct TimeSums_t
{
	const char *pszProfileScope;
	unsigned	calls;
	double 		time;
	double 		timeLessChildren;
	double		peak;
};

static bool TimeCompare( const TimeSums_t &lhs, const TimeSums_t &rhs )
{
	return ( lhs.time > rhs.time );
}

static bool TimeLessChildrenCompare( const TimeSums_t &lhs, const TimeSums_t &rhs )
{
	return ( lhs.timeLessChildren > rhs.timeLessChildren );
}

static bool PeakCompare( const TimeSums_t &lhs, const TimeSums_t &rhs )
{
	return ( lhs.peak > rhs.peak );
}

static bool AverageTimeCompare( const TimeSums_t &lhs, const TimeSums_t &rhs )
{
	double avgLhs = ( lhs.calls ) ? lhs.time / (double)lhs.calls : 0.0;
	double avgRhs = ( rhs.calls ) ? rhs.time / (double)rhs.calls : 0.0;
	return ( avgLhs > avgRhs );
}

static bool AverageTimeLessChildrenCompare( const TimeSums_t &lhs, const TimeSums_t &rhs )
{
	double avgLhs = ( lhs.calls ) ? lhs.timeLessChildren / (double)lhs.calls : 0.0;
	double avgRhs = ( rhs.calls ) ? rhs.timeLessChildren / (double)rhs.calls : 0.0;
	return ( avgLhs > avgRhs );

}
static bool PeakOverAverageCompare( const TimeSums_t &lhs, const TimeSums_t &rhs )
{
	double avgLhs = ( lhs.calls ) ? lhs.timeLessChildren / (double)lhs.calls : 0.0;
	double avgRhs = ( rhs.calls ) ? rhs.timeLessChildren / (double)rhs.calls : 0.0;

	double lhsPoA = ( avgLhs != 0 ) ? lhs.peak / avgLhs : 0.0;
	double rhsPoA = ( avgRhs != 0 ) ? rhs.peak / avgRhs : 0.0;

	return ( lhsPoA > rhsPoA );
}

map<CVProfNode *, double> 	g_TimesLessChildren;
map<const char *, unsigned> g_TimeSumsMap;
vector<TimeSums_t> 			g_TimeSums;

//-------------------------------------

void CVProfile::SumTimes( CVProfNode *pNode, int budgetGroupID )
{
	if ( !pNode )
		return; // this generally only happens on a failed FindNode()

	if ( GetRoot() != pNode )
	{
		if ( budgetGroupID == -1 || pNode->GetBudgetGroupID() == budgetGroupID )
		{
			double timeLessChildren = pNode->GetTotalTimeLessChildren();

			g_TimesLessChildren.insert( make_pair( pNode, timeLessChildren ) );

			map<const char *, unsigned>::iterator iter;
			iter = g_TimeSumsMap.find( pNode->GetName() ); // intenionally using address of string rather than string compare (toml 01-27-03)
			if ( iter == g_TimeSumsMap.end() )
			{
				TimeSums_t timeSums = { pNode->GetName(), pNode->GetTotalCalls(), pNode->GetTotalTime(), timeLessChildren, pNode->GetPeakTime() };
				g_TimeSumsMap.insert( make_pair( pNode->GetName(), g_TimeSums.size() ) );
				g_TimeSums.push_back( timeSums );
			}
			else
			{
				TimeSums_t &timeSums = g_TimeSums[iter->second];
				timeSums.calls += pNode->GetTotalCalls();
				timeSums.time += pNode->GetTotalTime();
				timeSums.timeLessChildren += timeLessChildren;
				if ( pNode->GetPeakTime() > timeSums.peak )
					timeSums.peak = pNode->GetPeakTime();
			}
		}

		if( pNode->GetSibling() )
		{
			SumTimes( pNode->GetSibling(), budgetGroupID );
		}
	}

	if( pNode->GetChild() )
	{
		SumTimes( pNode->GetChild(), budgetGroupID );
	}

}

//-------------------------------------

CVProfNode *CVProfile::FindNode( CVProfNode *pStartNode, const char *pszNode )
{
	if ( strcmp( pStartNode->GetName(), pszNode ) != 0 )
	{
		CVProfNode *pFoundNode = NULL;
		if ( pStartNode->GetSibling() )
		{
			pFoundNode = FindNode( pStartNode->GetSibling(), pszNode );
		}

		if ( !pFoundNode && pStartNode->GetChild() )
		{
			pFoundNode = FindNode( pStartNode->GetChild(), pszNode );
		}

		return pFoundNode;
	}
	return pStartNode;
}

//-------------------------------------

void CVProfile::SumTimes( const char *pszStartNode, int budgetGroupID )
{
	if ( GetRoot()->GetChild() )
	{
		CVProfNode *pStartNode;
		if ( pszStartNode == NULL )
			pStartNode = GetRoot();
		else
		{
			// This only works for nodes that show up only once in tree
			pStartNode = FindNode( GetRoot(), pszStartNode );
		}
		SumTimes( pStartNode, budgetGroupID );
	}

}

//-------------------------------------

void CVProfile::DumpNodes( CVProfNode *pNode, int indent )
{
	if ( !pNode )
		return; // this generally only happens on a failed FindNode()

	bool fIsRoot = ( pNode == GetRoot() );

	if ( !fIsRoot )
	{
		char szIndent[100];
		szIndent[0] = 0;
		for ( int i = 0; i < indent; i++ )
			//Msg( "  " );
			strcat( szIndent, "    " );//by jinsheng
		map<CVProfNode *, double>::iterator iterTimeLessChildren = g_TimesLessChildren.find( pNode );

		Msg("%s%s: Sum[%dc, func+child %.3f, func %.3f] Avg[ func+child %.3f, func %.3f], Peak[%.3f]\n",
			         szIndent,
					 pNode->GetName(),
					 pNode->GetTotalCalls(), pNode->GetTotalTime(), iterTimeLessChildren->second,
					 ( pNode->GetTotalCalls() > 0 ) ? pNode->GetTotalTime() / (double)pNode->GetTotalCalls() : 0,
					 ( pNode->GetTotalCalls() > 0 ) ? iterTimeLessChildren->second / (double)pNode->GetTotalCalls() : 0,
					 pNode->GetPeakTime()  );

	}

	if( pNode->GetChild() )
	{
		DumpNodes( pNode->GetChild(), indent + 1 );
	}

	if( !fIsRoot && pNode->GetSibling() )
	{
		DumpNodes( pNode->GetSibling(), indent );
	}
}

//-------------------------------------

static void DumpSorted( const char *pszHeading, double totalTime, bool (*pfnSort)( const TimeSums_t &, const TimeSums_t & ) )
{
	unsigned i;
	vector<TimeSums_t> sortedSums;
	sortedSums = g_TimeSums;
#ifdef kkk
	sort( sortedSums.begin(), sortedSums.end(), pfnSort );
#endif
	MonitorMsg( "%s\n", pszHeading);
    MonitorMsg( "Calls        Time+Child   Pct     Time          Pct    Avg+Child    Avg          Peak       Scope                                   \n");
    MonitorMsg( "---------- ------------ ------ ------------ ------ ------------ ------------ ------------ ----------------------------------------\n");
    for ( i = 0; i < sortedSums.size(); i++ )
    {
		double avg = ( sortedSums[i].calls ) ? sortedSums[i].time / (double)sortedSums[i].calls : 0.0;
		double avgLessChildren = ( sortedSums[i].calls ) ? sortedSums[i].timeLessChildren / (double)sortedSums[i].calls : 0.0;

        MonitorMsg( "%10d %12.3f %6.2f %12.3f %6.2f %12.3f %12.3f %12.3f %35s\n",
             sortedSums[i].calls,
			 sortedSums[i].time,
			 ( sortedSums[i].time / totalTime ) * 100.0,
			 sortedSums[i].timeLessChildren,
			 ( sortedSums[i].timeLessChildren / totalTime ) * 100.0,
			 avg,
			 avgLessChildren,
			 sortedSums[i].peak,
			 sortedSums[i].pszProfileScope);
	}
}

void CVProfile::OutputReport( VProfReportType_t type, const char *pszStartNode, int budgetGroupID )
{
	//MonitorMsg( "******** BEGIN VPROF CLIENT REPORT ********\n");
	//MonitorMsg( "  (note: this report exceeds the output capacity of MSVC debug window. Use console window or console log.) \n");
	if ( NumFramesSampled() == 0 || GetTotalTimeSampled() == 0){
	//	MonitorMsg( "No samples\n" );
	}
	else
	{
		if ( type & VPRT_SUMMARY )
		{
			MonitorMsg( "-- Summary --\n" );
			MonitorMsg( "%d frames sampled for %.2f seconds\n", NumFramesSampled(), GetTotalTimeSampled() / 1000.0 );
			MonitorMsg( "Average %.2f fps, %.2f ms per frame\n", 1000.0 / ( GetTotalTimeSampled() / NumFramesSampled() ), GetTotalTimeSampled() / NumFramesSampled() );
			MonitorMsg( "Peak %.2f ms frame\n", GetPeakFrameTime() );

			double timeAccountedFor = 100.0 - ( m_Root.GetTotalTimeLessChildren() / m_Root.GetTotalTime() );
			MonitorMsg( "%.0f pct of time accounted for\n", min( 100.0, timeAccountedFor ) );
			MonitorMsg( "\n" );
		}

		if ( pszStartNode == NULL )
		{
			pszStartNode = GetRoot()->GetName();
		}

		SumTimes( pszStartNode, budgetGroupID );

		// Dump the hierarchy
		if ( type & VPRT_HIERARCHY )
		{
		//	MonitorMsg( "-- Hierarchical Call Graph --\n");
		//	DumpNodes( (pszStartNode == NULL ) ? GetRoot() : FindNode( GetRoot(), pszStartNode ), 0 );
		//	MonitorMsg( "\n" );
		}

		if ( type & VPRT_LIST_BY_TIME )
		{
			DumpSorted( "-- Profile scopes sorted by time (including children) --", GetTotalTimeSampled(), TimeCompare );
			MonitorMsg( "\n" );
		}
		if ( type & VPRT_LIST_BY_TIME_LESS_CHILDREN )
		{
		//	DumpSorted( "-- Profile scopes sorted by time (without children) --", GetTotalTimeSampled(), TimeLessChildrenCompare );
		//	MonitorMsg( "\n" );
		}
		if ( type & VPRT_LIST_BY_AVG_TIME )
		{
		//	DumpSorted( "-- Profile scopes sorted by average time (including children) --", GetTotalTimeSampled(), AverageTimeCompare );
		//	MonitorMsg( "\n" );
		}
		if ( type & VPRT_LIST_BY_AVG_TIME_LESS_CHILDREN )
		{
		//	DumpSorted( "-- Profile scopes sorted by average time (without children) --", GetTotalTimeSampled(), AverageTimeLessChildrenCompare );
		//	MonitorMsg( "\n" );
		}
		if ( type & VPRT_LIST_BY_PEAK_TIME )
		{
		//	DumpSorted( "-- Profile scopes sorted by peak --", GetTotalTimeSampled(), PeakCompare );
		//	MonitorMsg( "\n" );
		}
		if ( type & VPRT_LIST_BY_PEAK_OVER_AVERAGE )
		{
		//	DumpSorted( "-- Profile scopes sorted by peak over average (including children) --", GetTotalTimeSampled(), PeakOverAverageCompare );
		//	MonitorMsg( "\n" );
		}

		// TODO: Functions by time less children
		// TODO: Functions by time averages
		// TODO: Functions by peak
		// TODO: Peak deviation from average
		g_TimesLessChildren.clear();
		g_TimeSumsMap.clear();
		g_TimeSums.clear();
	}
	MonitorMsg( "******** END VPROF REPORT ********\n");

}


void CVProfile::ClearVprof( )
{
	_ClearVprof( );
}

int CVProfile::GetVprofSize( )
{
	return _GetVprofSize( );
}

char * CVProfile::GetVprofstr( int itPos )
{
	return _GetVprofstr( itPos );
}
//////////////////////////////////////////////////////////////////////////
//about Server

void CVProfile::Server_DumpNodes( CVProfNode *pNode, int indent )
{
	if ( !pNode )
		return; // this generally only happens on a failed FindNode()

	bool fIsRoot = ( pNode == GetRoot() );

	if ( !fIsRoot )
	{
		char szIndent[100];
		szIndent[0] = 0;
		//for ( int i = 0; i < indent; i++ )
			//Print( g_nDebugOutLine++,"  " );
		map<CVProfNode *, double>::iterator iterTimeLessChildren = g_TimesLessChildren.find( pNode );

		Print( g_nDebugOutLine++,"%s%s: Sum[%dc, func+child %.3f, func %.3f] Avg[ func+child %.3f, func %.3f], Peak[%.3f]\n",
			szIndent,
			pNode->GetName(),
			pNode->GetTotalCalls(), pNode->GetTotalTime(), iterTimeLessChildren->second,
			( pNode->GetTotalCalls() > 0 ) ? pNode->GetTotalTime() / (double)pNode->GetTotalCalls() : 0,
			( pNode->GetTotalCalls() > 0 ) ? iterTimeLessChildren->second / (double)pNode->GetTotalCalls() : 0,
			pNode->GetPeakTime()  );

	}

	if( pNode->GetChild() )
	{
		Server_DumpNodes( pNode->GetChild(), indent + 1 );
	}

	if( !fIsRoot && pNode->GetSibling() )
	{
		Server_DumpNodes( pNode->GetSibling(), indent );
	}
}


static void Server_DumpSorted( const char *pszHeading, double totalTime, bool (*pfnSort)( const TimeSums_t &, const TimeSums_t & ) )
{
	unsigned i;
	vector<TimeSums_t> sortedSums;
	sortedSums = g_TimeSums;
#ifdef kkk
	sort( sortedSums.begin(), sortedSums.end(), pfnSort );
#endif
	Print( g_nDebugOutLine++,"%s\n", pszHeading);
	Print( g_nDebugOutLine++,"            Scope              Calls      Time+Child   Pct+Child     Time       Pct    Avg+Child     Avg         Peak   \n");
	Print( g_nDebugOutLine++,"   ----------------------- ------------- ------------ ----------- ----------- ------- ----------- ----------- ----------\n");
	for ( i = 0; i < sortedSums.size(); i++ )
	{
		double avg = ( sortedSums[i].calls ) ? sortedSums[i].time / (double)sortedSums[i].calls : 0.0;
		double avgLessChildren = ( sortedSums[i].calls ) ? sortedSums[i].timeLessChildren / (double)sortedSums[i].calls : 0.0;

		Print( g_nDebugOutLine++,"   %20s	%10d	%9.3f        %3.2f    %9.3f      %3.2f     %6.3f      %6.3f     %7.3f\n",
			sortedSums[i].pszProfileScope,
			sortedSums[i].calls,
			sortedSums[i].time,
			( sortedSums[i].time / totalTime ) * 100.0,
			sortedSums[i].timeLessChildren,
			( sortedSums[i].timeLessChildren / totalTime ) * 100.0,
			avg,
			avgLessChildren,
			sortedSums[i].peak );
	}

}

void CVProfile::Server_OutputReport( VProfReportType_t type, const char *pszStartNode, int budgetGroupID )
{
	g_nDebugOutLine = 0;
	//Print(g_nDebugOutLine++, "************************ BEGIN VPROF REPORT *************************\n");
	//Print(g_nDebugOutLine++, "  (note: this report exceeds the output capacity of MSVC debug window. Use console window or console log.) \n");

	if ( NumFramesSampled() == 0 || GetTotalTimeSampled() == 0)
	{
		Print(g_nDebugOutLine++, "No samples\n" );
	}
	else
	{
		if ( type & VPRT_SUMMARY )
		{
			Print( g_nDebugOutLine++, "-- Summary --												\n" );
			Print( g_nDebugOutLine++,"%d frames sampled for %.2f seconds							\n", NumFramesSampled(), GetTotalTimeSampled() / 1000.0 );
			Print( g_nDebugOutLine++,"Average %.2f fps, %.2f ms per frame							\n", 1000.0 / ( GetTotalTimeSampled() / NumFramesSampled() ), GetTotalTimeSampled() / NumFramesSampled() );
			Print( g_nDebugOutLine++,"Peak %.2f ms frame											\n", GetPeakFrameTime() );

			double timeAccountedFor = 100.0 - ( m_Root.GetTotalTimeLessChildren() / m_Root.GetTotalTime() );
			Print( g_nDebugOutLine++,"%.0f pct of time accounted for\n", min( 100.0, timeAccountedFor ) );
			Print( g_nDebugOutLine++,"																\n" );
		}

		if ( pszStartNode == NULL )
		{
			pszStartNode = GetRoot()->GetName();
		}

		SumTimes( pszStartNode, budgetGroupID );

		// Dump the hierarchy
		if ( type & VPRT_HIERARCHY )
		{
// 			Print( g_nDebugOutLine++,"-- Hierarchical Call Graph --\n");
// 			Server_DumpNodes( (pszStartNode == NULL ) ? GetRoot() : FindNode( GetRoot(), pszStartNode ), 0 );
// 			Print( g_nDebugOutLine++,"\n" );
		}

		if ( type & VPRT_LIST_BY_TIME )
		{
			Server_DumpSorted( "-- Profile scopes sorted by time (including children) --", GetTotalTimeSampled(), TimeCompare );
			Print( g_nDebugOutLine++,"																\n" );
		}
		if ( type & VPRT_LIST_BY_TIME_LESS_CHILDREN )
		{
//			Server_DumpSorted( "-- Profile scopes sorted by time (without children) --", GetTotalTimeSampled(), TimeLessChildrenCompare );
//			Print( g_nDebugOutLine++,"\n" );
		}
		if ( type & VPRT_LIST_BY_AVG_TIME )
		{
//			Server_DumpSorted( "-- Profile scopes sorted by average time (including children) --", GetTotalTimeSampled(), AverageTimeCompare );
//			Print( g_nDebugOutLine++,"\n" );
		}
		if ( type & VPRT_LIST_BY_AVG_TIME_LESS_CHILDREN )
		{
//			Server_DumpSorted( "-- Profile scopes sorted by average time (without children) --", GetTotalTimeSampled(), AverageTimeLessChildrenCompare );
//			Print( g_nDebugOutLine++,"\n" );
		}
		if ( type & VPRT_LIST_BY_PEAK_TIME )
		{
//			Server_DumpSorted( "-- Profile scopes sorted by peak --", GetTotalTimeSampled(), PeakCompare );
//			Print( g_nDebugOutLine++,"\n" );
		}
		if ( type & VPRT_LIST_BY_PEAK_OVER_AVERAGE )
		{
//			Server_DumpSorted( "-- Profile scopes sorted by peak over average (including children) --", GetTotalTimeSampled(), PeakOverAverageCompare );
//			Print( g_nDebugOutLine++,"\n" );
		}

		// TODO: Functions by time less children
		// TODO: Functions by time averages
		// TODO: Functions by peak
		// TODO: Peak deviation from average
		g_TimesLessChildren.clear();
		g_TimeSumsMap.clear();
		g_TimeSums.clear();
	}
//	Print(g_nDebugOutLine++,"********************* END VPROF REPORT *************************\n");

}

//=============================================================================

CVProfile::CVProfile()
: 	m_nFrames( 0 ),
 	m_enabled( 0 ),
 	m_pausedEnabledDepth( 0 ),
	m_fAtRoot( true )
{
	// Go ahead and allocate 32 slots for budget group names
	m_pBudgetGroupNames = ( char ** )malloc( sizeof( char * ) * 32 );
	m_nBudgetGroupNames = 0;
	m_nBudgetGroupNamesAllocated = 32;
	g_nDebugOutLine		= 0;

	m_Root.Init( "Root", 0, NULL, BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_OTHER_UNACCOUNTED ) ),
//	m_Root.Init( "Root", 0, NULL, VPROF_BUDGETGROUP_OTHER_UNACCOUNTED ),
	m_pCurNode = &m_Root;

	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_OTHER_UNACCOUNTED );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_WORLD_RENDERING );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_DISPLACEMENT_RENDERING );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_GAME );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_NPCS );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_NPC_ANIM );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_PHYSICS );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_STATICPROP_RENDERING );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_MODEL_RENDERING );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_BRUSHMODEL_RENDERING );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_SHADOW_RENDERING );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_DETAILPROP_RENDERING );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_PARTICLE_RENDERING );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_ROPES );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_DLIGHT_RENDERING );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_OTHER_NETWORKING );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_OTHER_ANIMATION );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_OTHER_SOUND );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_OTHER_VGUI );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_OTHER_FILESYSTEM );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_PREDICTION );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_INTERPOLATION );
	BudgetGroupNameToBudgetGroupID( VPROF_BUDGETGROUP_SWAP_BUFFERS );
}

CVProfile::~CVProfile()
{
	Release( );
}

// add by flyma 06.12.19
void CVProfile::Release()
{
#ifdef WIN32
	CVProfNode::FreeAll();
#endif
	int i;
	for( i = 0; i < m_nBudgetGroupNames; i++ )
	{
		free( m_pBudgetGroupNames[i] );
	}
	if( m_pBudgetGroupNames != 0 )
	{
		free( m_pBudgetGroupNames );
		m_pBudgetGroupNames = 0;
	}
	m_nBudgetGroupNames = 0;
}

const char *CVProfile::GetBudgetGroupName( int budgetGroupID )
{
//	COMPILE_TIME_ASSERT( sizeof( g_pBudgetGroupNames ) / sizeof( g_pBudgetGroupNames[0] ) == VPROF_NUM_BUDGETGROUPS );
	Assert( budgetGroupID >= 0 && budgetGroupID < m_nBudgetGroupNames );
	return m_pBudgetGroupNames[budgetGroupID];
}

#define COLORMIN 160
#define COLORMAX 255

static int g_ColorLookup[4] =
{
	COLORMIN,
	COLORMAX,
	COLORMIN+(COLORMAX-COLORMIN)/3,
	COLORMIN+((COLORMAX-COLORMIN)*2)/3,
};

#define GET_BIT( val, bitnum ) ( ( val >> bitnum ) & 0x1 )

void CVProfile::GetBudgetGroupColor( int budgetGroupID, int &r, int &g, int &b, int &a )
{
	budgetGroupID = budgetGroupID % ( 1 << 6 );

	int index;
	index = GET_BIT( budgetGroupID, 0 ) | ( GET_BIT( budgetGroupID, 5 ) << 1 );
	r = g_ColorLookup[index];
	index = GET_BIT( budgetGroupID, 1 ) | ( GET_BIT( budgetGroupID, 4 ) << 1 );
	g = g_ColorLookup[index];
	index = GET_BIT( budgetGroupID, 2 ) | ( GET_BIT( budgetGroupID, 3 ) << 1 );
	b = g_ColorLookup[index];
	a = 255;
}

// return -1 if it doesn't exist.
int CVProfile::FindBudgetGroupName( const char *pBudgetGroupName )
{
	int i;
	for( i = 0; i < m_nBudgetGroupNames; i++ )
	{
		if( stricmp( pBudgetGroupName, m_pBudgetGroupNames[i] ) == 0 )
		{
			return i;
		}
	}
	return -1;
}

int CVProfile::AddBudgetGroupName( const char *pBudgetGroupName )
{
	char *pNewString = ( char * )malloc( strlen( pBudgetGroupName ) + 1 );
	strcpy( pNewString, pBudgetGroupName );
	if( m_nBudgetGroupNames + 1 > m_nBudgetGroupNamesAllocated )
	{
		m_nBudgetGroupNamesAllocated *= 2;
		m_pBudgetGroupNames = ( char ** )realloc( m_pBudgetGroupNames, sizeof( char * ) * m_nBudgetGroupNamesAllocated );
	}

	m_pBudgetGroupNames[m_nBudgetGroupNames] = pNewString;
	m_nBudgetGroupNames++;
	if( m_pNumBudgetGroupsChangedCallBack )
	{
		(*m_pNumBudgetGroupsChangedCallBack)();
	}
	return m_nBudgetGroupNames - 1;
}

int CVProfile::BudgetGroupNameToBudgetGroupID( const char *pBudgetGroupName )
{
	int budgetGroupID = FindBudgetGroupName( pBudgetGroupName );
	if( budgetGroupID == -1 )
	{
		budgetGroupID = AddBudgetGroupName( pBudgetGroupName );
	}
	return budgetGroupID;
}

int CVProfile::GetNumBudgetGroups( void )
{
	return m_nBudgetGroupNames;
}

void CVProfile::RegisterNumBudgetGroupsChangedCallBack( void (*pCallBack)(void) )
{
	m_pNumBudgetGroupsChangedCallBack = pCallBack;
}

#endif

/*
//-------------------------------------
//by jinsheng 2008.2.19 方便服务器输出,修改输出结果
static char s_szServerReportMsg[4 + sizeof(GeneralProfMsg_t)+100*sizeof(ScopeProfMsg_t)];
char* CVProfile::GetReportServerMsg( )
{
return s_szServerReportMsg;
}
void CVProfile::OutputReportServer(   )
{

memset( s_szServerReportMsg, 0, 4);

if ( NumFramesSampled() == 0 || GetTotalTimeSampled() == 0)
{
return;
}

SumTimes( GetRoot()->GetName(), -1 );

//summary
GeneralProfMsg_t summary;

summary.nTotalFrame = NumFramesSampled();
summary.nTotalTime  = GetTotalTimeSampled() / 1000.0 ;
summary.nAvgFps = 1000.0 / ( GetTotalTimeSampled() / NumFramesSampled() );
summary.nAvgTime = GetTotalTimeSampled() / NumFramesSampled() ;
summary.nPeakTime = GetPeakFrameTime() ;

double timeAccountedFor = 100.0 - ( m_Root.GetTotalTimeLessChildren() / m_Root.GetTotalTime() );
summary.nProfPct = timeAccountedFor * 1000;


//time
unsigned i;
vector<TimeSums_t> sortedSums;
sortedSums = g_TimeSums;
sort( sortedSums.begin(), sortedSums.end(), TimeCompare );

summary.nScopeCount = sortedSums.size( );

double totalTime = GetTotalTimeSampled();

memcpy( s_szServerReportMsg+4, &summary, sizeof(GeneralProfMsg_t));

for ( i = 0; i < sortedSums.size(); i++ )
{
if ( i >= 100 )
break;
ScopeProfMsg_t ScopeProf;
memset( &ScopeProf, 0, sizeof( ScopeProfMsg_t ));
double avg = ( sortedSums[i].calls ) ? sortedSums[i].time / (double)sortedSums[i].calls : 0.0;
double avgLessChildren = ( sortedSums[i].calls ) ? sortedSums[i].timeLessChildren / (double)sortedSums[i].calls : 0.0;
#if 0
Msg( "   %32s%12d%12.3f%6.2f%12.3f%6.2f%12.3f%12.3f%12.3f\n",
sortedSums[i].pszProfileScope,
sortedSums[i].calls,
sortedSums[i].time,
( sortedSums[i].time / totalTime ) * 100.0,
sortedSums[i].timeLessChildren,
( sortedSums[i].timeLessChildren / totalTime ) * 100.0,
avg,
avgLessChildren,
sortedSums[i].peak );
#else
strncpy( ScopeProf.szScope, sortedSums[i].pszProfileScope , 15 );
ScopeProf.nCallCount = sortedSums[i].calls;
ScopeProf.nTime = sortedSums[i].time;
ScopeProf.nTimePct =  ( sortedSums[i].time / totalTime ) * 100.0 * 1000;
ScopeProf.nTimeLessChild = sortedSums[i].timeLessChildren;
ScopeProf.nTimeLessChildPct = ( sortedSums[i].timeLessChildren / totalTime ) * 100.0 * 1000,
ScopeProf.nAvgTime = avg;
ScopeProf.nAvgTimeLessChild = avgLessChildren;
ScopeProf.nPeakTime = sortedSums[i].peak;
#endif
memcpy( s_szServerReportMsg + 4 + sizeof(GeneralProfMsg_t) + sizeof( ScopeProfMsg_t ) * i,
&ScopeProf, sizeof(ScopeProfMsg_t));

}

int size = sizeof(GeneralProfMsg_t) + sizeof( ScopeProfMsg_t ) * sortedSums.size() ;
memcpy( s_szServerReportMsg, &size, 4 );

g_TimesLessChildren.clear();
g_TimeSumsMap.clear();
g_TimeSums.clear();

}
*/
