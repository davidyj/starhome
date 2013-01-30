//========= Copyright ?1996-2003, Valve LLC, All rights reserved. ============
//
// Purpose: Real-Time Hierarchical Profiling
//
// $NoKeywords: $
//=============================================================================

#ifndef VPROF_H
#define VPROF_H

#include "../../Port/config.h"
#include "dbg.h"
#include "fasttimer.h"

#include "memdbgoff.h"

//XXX: VPROF_ENABLED is disabled currently on FreeBSD by lujd
//#ifdef WIN32
#define VPROF_ENABLED
//#endif

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif

//-----------------------------------------------------------------------------
//
// Profiling instrumentation macros
//



#ifdef VPROF_ENABLED


#define	VPROF( name )						VPROF_(name, 0, VPROF_BUDGETGROUP_OTHER_UNACCOUNTED, false)
#define	VPROF_ASSERT_ACCOUNTED( name )		VPROF_(name, 0, VPROF_BUDGETGROUP_OTHER_UNACCOUNTED, true)
#define	VPROF_( name, detail, group, bAssertAccounted )		VPROF_##detail(name,group, bAssertAccounted)
#define VPROF_BUDGET( name, group )			VPROF_(name, 0, group, false)

#define VPROF_BUDGET_GROUP_ID_UNACCOUNTED 0

#define VPROF_BUDGETGROUP_OTHER_UNACCOUNTED			"Unaccounted"
#define VPROF_BUDGETGROUP_WORLD_RENDERING			"World Rendering"
#define VPROF_BUDGETGROUP_DISPLACEMENT_RENDERING	"Displacement Rendering"
#define VPROF_BUDGETGROUP_GAME						"Game"
#define VPROF_BUDGETGROUP_NPCS						"NPCs"
#define VPROF_BUDGETGROUP_NPC_ANIM					"NPC Animation"
#define VPROF_BUDGETGROUP_PHYSICS					"Physics"
#define VPROF_BUDGETGROUP_STATICPROP_RENDERING		"Static Prop Rendering"
#define VPROF_BUDGETGROUP_MODEL_RENDERING			"Other Model Rendering"
#define VPROF_BUDGETGROUP_BRUSHMODEL_RENDERING		"Brush Model Rendering"
#define VPROF_BUDGETGROUP_SHADOW_RENDERING			"Shadow Rendering"
#define VPROF_BUDGETGROUP_DETAILPROP_RENDERING		"Detail Prop Rendering"
#define VPROF_BUDGETGROUP_PARTICLE_RENDERING		"Particle/Effect Rendering"
#define VPROF_BUDGETGROUP_ROPES						"Ropes"
#define VPROF_BUDGETGROUP_DLIGHT_RENDERING			"Dynamic Light Rendering"
#define VPROF_BUDGETGROUP_OTHER_NETWORKING			"Networking"
#define VPROF_BUDGETGROUP_OTHER_ANIMATION			"Animation"
#define VPROF_BUDGETGROUP_OTHER_SOUND				"Sound"
#define VPROF_BUDGETGROUP_OTHER_VGUI				"VGUI"
#define VPROF_BUDGETGROUP_OTHER_FILESYSTEM			"FileSystem"
#define VPROF_BUDGETGROUP_PREDICTION				"Prediction"
#define VPROF_BUDGETGROUP_INTERPOLATION				"Interpolation"
#define VPROF_BUDGETGROUP_SWAP_BUFFERS				"Swap Buffers"

#define VPROF_HISTORY_COUNT 1024

//-------------------------------------

#ifndef VPROF_LEVEL
#define VPROF_LEVEL 0
#endif

#define	VPROF_0(name,group,assertAccounted)				CVProfScope VProf_(name, 0, group, assertAccounted);

#if VPROF_LEVEL > 0
#define	VPROF_1(name,group,assertAccounted)				CVProfScope VProf_(name, 1, group, assertAccounted);
#else
#define	VPROF_1(name,group,assertAccounted)				((void)0)
#endif

#if VPROF_LEVEL > 1
#define	VPROF_2(name,group,assertAccounted)				CVProfScope VProf_(name, 2, group, assertAccounted);
#else
#define	VPROF_2(name,group,assertAccounted)				((void)0)
#endif

#if VPROF_LEVEL > 2
#define	VPROF_3(name,group,assertAccounted)				CVProfScope VProf_(name, 3, group, assertAccounted);
#else
#define	VPROF_3(name,group,assertAccounted)				((void)0)
#endif

#if VPROF_LEVEL > 3
#define	VPROF_4(name,group,assertAccounted)				CVProfScope VProf_(name, 4, group, assertAccounted);
#else
#define	VPROF_4(name,group,assertAccounted)				((void)0)
#endif

//-------------------------------------

#else

#define	VPROF( name )				((void)0)
#define	VPROF_( name, detail )		((void)0)

#define	VPROF_ASSERT_ACCOUNTED( name )		((void)0)
#define VPROF_BUDGET( name, group )			((void)0)

#endif


//////////////////////////////////////////////////////////////////////////
//
#ifdef WIN32
#define CONSOLE_WIDTH   300
#define CONSOLE_HEIGHT  100
#define CONSOLE_TOP		8
#define CONSOLE_BOTTOM  2

static int g_nConsoleTop = CONSOLE_TOP;

void ConsoleScroll(int nTop,int nBottom);
void ConsoleSetSize(int nCharLen,int nLine);
#else
#include "unixdomsvr.h"
#endif

void Print(const char* pszfmt,...);
void Print(int nLine,const char* psz,...);

//////////////////////////////////////////////////////////////////////////
//
//-----------------------------------------------------------------------------

int	GetDebugOutLine();

#ifdef VPROF_ENABLED

//-----------------------------------------------------------------------------
//
// A node in the call graph hierarchy
//

class CVProfNode
{

public:
	CVProfNode( );
	CVProfNode( const char * pszName, int detailLevel, CVProfNode *pParent, const char *pBudgetGroupName );
	~CVProfNode( );

	void Init( const char * pszName, int detailLevel, CVProfNode *pParent, const int nBudgetGroupID );
	void Init( const char * pszName, int detailLevel, CVProfNode *pParent, const char *pBudgetGroupName );

	CVProfNode *GetSubNode( const char *pszName, int detailLevel, const char *pBudgetGroupName );
	CVProfNode *GetParent();
	CVProfNode *GetSibling();
	CVProfNode *GetPrevsibling();
	CVProfNode *GetChild();

	void MarkFrame();
	void ResetPeak();

	void Pause();
	void Resume();
	void Reset();

	void EnterScope();
	bool ExitScope();

	const char *GetName();

	int GetBudgetGroupID()
	{
		return m_BudgetGroupID;
	}

	int	GetCurCalls();
	double GetCurTime();
	int GetPrevCalls();
	double GetPrevTime();
	int	GetTotalCalls();
	double GetTotalTime();
	double GetPeakTime();

	double GetCurTimeLessChildren();
	double GetPrevTimeLessChildren();
	double GetTotalTimeLessChildren();

#ifdef WIN32
	static void FreeAll();
#endif

	void SetClientData( int iClientData )	{ m_iClientData = iClientData; }
	int GetClientData() const				{ return m_iClientData; }

private:
	const char *m_pszName;
	CFastTimer	m_Timer;

	int			m_nRecursions;

	unsigned	m_nCurFrameCalls;
	CCycleCount	m_CurFrameTime;

	unsigned	m_nPrevFrameCalls;
	CCycleCount	m_PrevFrameTime;

	unsigned	m_nTotalCalls;
	CCycleCount	m_TotalTime;

	CCycleCount	m_PeakTime;

	CVProfNode *m_pParent;
	CVProfNode *m_pChild;
	CVProfNode *m_pSibling;

	int m_BudgetGroupID;

	int m_iClientData;

	void *operator new( size_t );
#ifdef WIN32
	void operator delete( void * ) {}
#else
	void operator delete( void * );
#endif

};

//-----------------------------------------------------------------------------
//
// Coordinator and root node of the profile hierarchy tree
//

enum VProfReportType_t
{
	VPRT_SUMMARY						= 1 << 0,
	VPRT_HIERARCHY						= 1 << 1,
	VPRT_LIST_BY_TIME					= 1 << 2,
	VPRT_LIST_BY_TIME_LESS_CHILDREN		= 1 << 3,
	VPRT_LIST_BY_AVG_TIME				= 1 << 4,
	VPRT_LIST_BY_AVG_TIME_LESS_CHILDREN	= 1 << 5,
	VPRT_LIST_BY_PEAK_TIME				= 1 << 6,
	VPRT_LIST_BY_PEAK_OVER_AVERAGE		= 1 << 7,
	VPRT_FULL = VPRT_SUMMARY | VPRT_HIERARCHY |
				VPRT_LIST_BY_TIME | VPRT_LIST_BY_TIME_LESS_CHILDREN |
				VPRT_LIST_BY_AVG_TIME |	VPRT_LIST_BY_AVG_TIME_LESS_CHILDREN |
				VPRT_LIST_BY_PEAK_TIME | VPRT_LIST_BY_PEAK_OVER_AVERAGE,
};

class CVProfile
{
public:
	CVProfile();
	~CVProfile();
	// add by flyma 06.12.19
	void Release();
	//
	// Runtime operations
	//

	void Start();
	void Stop();

	void EnterScope( const char *pszName, int detailLevel, const char *pBudgetGroupName, bool bAssertAccounted );
	void ExitScope();

	void MarkFrame();
	void ResetPeaks();

	void ClearVprof( );

	int GetVprofSize( );

	char * GetVprofstr( int itPos );


	void Pause();
	void Resume();
	void Reset();

	bool IsEnabled() const;
	int GetDetailLevel() const;

	bool AtRoot() const;

	//
	// Queries
	//

	int NumFramesSampled()	{ return m_nFrames; }
	double GetPeakFrameTime();
	double GetTotalTimeSampled();
	double GetTimeLastFrame();

	CVProfNode *GetRoot();
	CVProfNode *FindNode( CVProfNode *pStartNode, const char *pszNode );

	void OutputReport( VProfReportType_t type = VPRT_FULL, const char *pszStartNode = NULL, int budgetGroupID = -1 );
	//char *GetReportServerMsg( );

	void Server_DumpNodes(CVProfNode *pNode, int indent);
	void Server_OutputReport( VProfReportType_t type = VPRT_FULL, const char *pszStartNode = NULL, int budgetGroupID = -1 );

	const char *GetBudgetGroupName( int budgetGroupID );
	int GetNumBudgetGroups( void );
	void GetBudgetGroupColor( int budgetGroupID, int &r, int &g, int &b, int &a );
	int BudgetGroupNameToBudgetGroupID( const char *pBudgetGroupName );
	void RegisterNumBudgetGroupsChangedCallBack( void (*pCallBack)(void) );



private:
	void SumTimes( const char *pszStartNode, int budgetGroupID );
	void SumTimes( CVProfNode *pNode, int budgetGroupID );
	void DumpNodes( CVProfNode *pNode, int indent );
	int FindBudgetGroupName( const char *pBudgetGroupName );
	int AddBudgetGroupName( const char *pBudgetGroupName );

	int 		m_enabled;
	bool		m_fAtRoot; // tracked for efficiency of the "not profiling" case
	CVProfNode *m_pCurNode;
	CVProfNode	m_Root;
	int			m_nFrames;
	int			m_ProfileDetailLevel;
	int			m_pausedEnabledDepth;
	char		**m_pBudgetGroupNames;
	int			m_nBudgetGroupNamesAllocated;
	int			m_nBudgetGroupNames;
	void		(*m_pNumBudgetGroupsChangedCallBack)(void);
};


//-----------------------------------------------------------------------------
// Singleton interface
//-----------------------------------------------------------------------------
CVProfile &VProfCurrentProfile( );

//-----------------------------------------------------------------------------
#define GETVPROF(modeulName) GetVprof##modeulName( )
#define DECLAREGETVPROF(modeulName) CVProfile& GETVPROF(modeulName)
#define IMPLEMENTGETVPROF(modeulName) DECLAREGETVPROF(modeulName) { return VProfCurrentProfile( ); }

class CVProfScope
{
public:
	CVProfScope( const char * pszName, int detailLevel, const char *pBudgetGroupName, bool bAssertAccounted );
	~CVProfScope();
};

//-----------------------------------------------------------------------------
//
// CVProfNode, inline methods
//
inline CVProfNode::CVProfNode( )
{
	m_nCurFrameCalls = 0;
	m_nPrevFrameCalls = 0;
	m_nRecursions = 0;
	m_pParent = NULL;
	m_pChild = NULL;
	m_pSibling = NULL;
	m_iClientData = -1;
}

inline CVProfNode::CVProfNode( const char * pszName, int detailLevel, CVProfNode *pParent, const char *pBudgetGroupName )
{
	Init( pszName, detailLevel, pParent, pBudgetGroupName );
}

inline void CVProfNode::Init( const char * pszName, int detailLevel, CVProfNode *pParent, const int nBudgetGroupID )
{
	m_pszName = pszName;
	m_nCurFrameCalls = 0;
	m_nPrevFrameCalls = 0;
	m_nRecursions = 0;
	m_pParent = pParent;
	m_pChild = NULL;
	m_pSibling = NULL;
	m_iClientData = -1;

	m_BudgetGroupID = nBudgetGroupID;
	Reset();
	if( m_pParent && ( m_BudgetGroupID == VPROF_BUDGET_GROUP_ID_UNACCOUNTED ) )
	{
		m_BudgetGroupID = m_pParent->GetBudgetGroupID();
	}
}

inline void CVProfNode::Init( const char * pszName, int detailLevel, CVProfNode *pParent, const char *pBudgetGroupName )
{
	m_pszName = pszName;
	m_nCurFrameCalls = 0;
	m_nPrevFrameCalls = 0;
	m_nRecursions = 0;
	m_pParent = pParent;
	m_pChild = NULL;
	m_pSibling = NULL;
	m_iClientData = -1;

	m_BudgetGroupID = VProfCurrentProfile( ).BudgetGroupNameToBudgetGroupID( pBudgetGroupName );
	Reset();
	if( m_pParent && ( m_BudgetGroupID == VPROF_BUDGET_GROUP_ID_UNACCOUNTED ) )
	{
		m_BudgetGroupID = m_pParent->GetBudgetGroupID();
	}
}

//-------------------------------------

inline CVProfNode::~CVProfNode()
{
#ifndef WIN32
	delete m_pChild;
	delete m_pSibling;
#endif
}

//-------------------------------------

inline CVProfNode *CVProfNode::GetParent()
{
	Assert( m_pParent );
	return m_pParent;
}

//-------------------------------------

inline CVProfNode *CVProfNode::GetSibling()
{
	return m_pSibling;
}

//-------------------------------------
// Hacky way to the previous sibling, only used from vprof panel at the moment,
// so it didn't seem like it was worth the memory waste to add the reverse
// link per node.

inline CVProfNode *CVProfNode::GetPrevsibling()
{
	CVProfNode* p = GetParent();

	if(!p)
		return NULL;

	CVProfNode* s;
	for( s = p->GetChild();
	     s && ( s->GetSibling() != this );
		 s = s->GetSibling() )
		;

	return s;
}

//-------------------------------------

inline CVProfNode *CVProfNode::GetChild()
{
	return m_pChild;
}

//-------------------------------------

inline void CVProfNode::EnterScope()
{
	m_nCurFrameCalls++;
	if ( m_nRecursions++ == 0 )
	{
		m_Timer.Start();
	}
}

//-------------------------------------

inline bool CVProfNode::ExitScope()
{
	m_nRecursions = m_nRecursions - 1;
	if ( m_nRecursions == 0 && m_nCurFrameCalls != 0 )
	{
		m_Timer.End();
		m_CurFrameTime += m_Timer.GetDuration();
	}
	return ( m_nRecursions == 0 );
}

//-------------------------------------

inline const char *CVProfNode::GetName()
{
	Assert( m_pszName );
	return m_pszName;
}

//-------------------------------------

inline int	CVProfNode::GetTotalCalls()
{
	return m_nTotalCalls;
}

//-------------------------------------

inline double CVProfNode::GetTotalTime()
{
	return m_TotalTime.GetMillisecondsF();
}

//-------------------------------------

inline int	CVProfNode::GetCurCalls()
{
	return m_nCurFrameCalls;
}

//-------------------------------------

inline double CVProfNode::GetCurTime()
{
	return m_CurFrameTime.GetMillisecondsF();
}

//-------------------------------------

inline int CVProfNode::GetPrevCalls()
{
	return m_nPrevFrameCalls;
}

//-------------------------------------

inline double CVProfNode::GetPrevTime()
{
	return m_PrevFrameTime.GetMillisecondsF();
}

//-------------------------------------

inline double CVProfNode::GetPeakTime()
{
	return m_PeakTime.GetMillisecondsF();
}

//-------------------------------------

inline double CVProfNode::GetTotalTimeLessChildren()
{
	double result = GetTotalTime();
	CVProfNode *pChild = GetChild();
	while ( pChild )
	{
		result -= pChild->GetTotalTime();
		pChild = pChild->GetSibling();
	}
	return result;
}

//-------------------------------------

inline double CVProfNode::GetCurTimeLessChildren()
{
	double result = GetCurTime();
	CVProfNode *pChild = GetChild();
	while ( pChild )
	{
		result -= pChild->GetCurTime();
		pChild = pChild->GetSibling();
	}
	return result;
}


//-----------------------------------------------------------------------------
inline double CVProfNode::GetPrevTimeLessChildren()
{
	double result = GetPrevTime();
	CVProfNode *pChild = GetChild();
	while ( pChild )
	{
		result -= pChild->GetPrevTime();
		pChild = pChild->GetSibling();
	}
	return result;
}

//-----------------------------------------------------------------------------
//
// CVProfile, inline methods
//

//-------------------------------------

inline bool CVProfile::IsEnabled() const
{
	return ( m_enabled != 0 );
}

//-------------------------------------

inline int CVProfile::GetDetailLevel() const
{
	return m_ProfileDetailLevel;
}


//-------------------------------------

inline bool CVProfile::AtRoot() const
{
	return m_fAtRoot;
}

//-------------------------------------

inline void CVProfile::Start()
{
	if ( ++m_enabled == 1 )
		m_Root.EnterScope();
}

//-------------------------------------

inline void CVProfile::Stop()
{
	if ( --m_enabled == 0 )
		m_Root.ExitScope();
}

//-------------------------------------

inline void CVProfile::EnterScope( const char *pszName, int detailLevel, const char *pBudgetGroupName, bool bAssertAccounted )
{
	if ( m_enabled != 0 || !m_fAtRoot ) // if became disabled, need to unwind back to root before stopping
	{
		// Only account for vprof stuff on the primary thread.
		//if( !Plat_IsPrimaryThread() )
		//	return;

		if ( pszName != m_pCurNode->GetName() )
		{
			m_pCurNode = m_pCurNode->GetSubNode( pszName, detailLevel, pBudgetGroupName );
		}
#ifdef _DEBUG
		if( bAssertAccounted )
		{
			// FIXME
//			Assert( m_pCurNode->GetBudgetGroup() != VPROF_BUDGETGROUP_OTHER_UNACCOUNTED );
		}
#endif
		m_pCurNode->EnterScope();
		m_fAtRoot = false;
	}
}

//-------------------------------------

inline void CVProfile::ExitScope()
{
	if ( !m_fAtRoot || m_enabled != 0 )
	{
		// Only account for vprof stuff on the primary thread.
		//if( !Plat_IsPrimaryThread() )
		//	return;

		// ExitScope will indicate whether we should back up to our parent (we may
		// be profiling a recursive function)
		if (m_pCurNode->ExitScope())
		{
			m_pCurNode = m_pCurNode->GetParent();
		}
		m_fAtRoot = ( m_pCurNode == &m_Root );
	}
}

//-------------------------------------

inline void CVProfile::Pause()
{
	m_pausedEnabledDepth = m_enabled;
	m_enabled = 0;
	if ( !AtRoot() )
		m_Root.Pause();
}

//-------------------------------------

inline void CVProfile::Resume()
{
	m_enabled = m_pausedEnabledDepth;
	if ( !AtRoot() )
		m_Root.Resume();
}

//-------------------------------------

inline void CVProfile::Reset()
{
	m_Root.Reset();
	m_nFrames = 0;
}

//-------------------------------------

inline void CVProfile::ResetPeaks()
{
	m_Root.ResetPeak();
}

//-------------------------------------

inline void CVProfile::MarkFrame()
{
	if ( m_enabled )
	{
		++m_nFrames;
		m_Root.ExitScope();
		m_Root.MarkFrame();
		m_Root.EnterScope();
	}
}

//-------------------------------------

inline double CVProfile::GetTotalTimeSampled()
{
	return m_Root.GetTotalTime();
}

//-------------------------------------

inline double CVProfile::GetPeakFrameTime()
{
	return m_Root.GetPeakTime();
}

//-------------------------------------

inline double CVProfile::GetTimeLastFrame()
{
	return m_Root.GetCurTime();
}

//-------------------------------------

inline CVProfNode *CVProfile::GetRoot()
{
	return &m_Root;
}

//-----------------------------------------------------------------------------

inline CVProfScope::CVProfScope( const char * pszName, int detailLevel, const char *pBudgetGroupName, bool bAssertAccounted )
{
	VProfCurrentProfile( ).EnterScope( pszName, detailLevel, pBudgetGroupName, bAssertAccounted );
}

//-------------------------------------

inline CVProfScope::~CVProfScope()
{
	VProfCurrentProfile( ).ExitScope();
}

//如果没有定义VPROF_ENABLED宏
#else
#define GETVPROF(modeulName)
#define DECLAREGETVPROF(modeulName)
#define IMPLEMENTGETVPROF(modeulName)

#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif

//------------Server Msg Struct
// struct GeneralProfMsg_t
// {
// 	int nTotalFrame;		//总采样帧数
// 	int nTotalTime;			//总采样时间, 单位 s
// 	int nAvgFps;			//平均帧速率
// 	int nAvgTime;			//平均每帧总耗费时间,单位 ms
// 	int nPeakTime;			//峰值帧耗费时间,单位 ms
// 	int nProfPct;			//采样比,  1000%
// 	int	nScopeCount;		//scope count
// };
//
// struct ScopeProfMsg_t
// {
// 	char szScope[15];		// Scope name
// 	int  nCallCount;		// 调用次数
//     int  nTime;				// 总耗费时间(包含子调用)，单位ms
// 	int  nTimePct;			// 总耗费时间占用比(包含子调用) 1000%
// 	int  nTimeLessChild;	// 总耗费时间(不包含子调用),单位ms
// 	int  nTimeLessChildPct;	// 总耗费时间占用比(不包含子调用) 1000%
// 	int	 nAvgTime;			// 平均每帧耗费时间(包含子调用), 单位ms
// 	int	 nAvgTimeLessChild;	// 平均每帧耗费时间(不包含子调用), 单位ms
// 	int	 nPeakTime;			// 峰值耗费时间, 单位ms
// };

#endif

//=============================================================================
