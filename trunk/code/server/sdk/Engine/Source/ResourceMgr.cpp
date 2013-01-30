#include "../stdafx.h"
#include "strtools.h" // WideCharToChar Q_strlen
#include "ResourceMgr.h"

// memdbgon must be the last include file in a .cpp file!!!
//#include "memdbgon.h"


IMPLEMENT_CLASS( ResourceUnit, IBaseObj )
IMPLEMENT_CLASS( FileUnit, ResourceUnit )
IMPLEMENT_CLASS( XMLUnit, ResourceUnit )



#if 0
//////////////////////////////////////////////////////////////////
// 注册默认的资源构造器
class CRegisterDefaultResUnit
{
public:
	CRegisterDefaultResUnit( )
	{
		CResourceMgr::getSingle().RegisterResConstruct( CResourceMgr::FILEUNIT, ConstructFileUnit );
		CResourceMgr::getSingle().RegisterResConstruct( CResourceMgr::XMLUNIT, ConstructXMLUnit );
//		CResourceMgr::RegisterResConstruct( CResourceMgr::ABIUNIT, ConstructABIUnit );
	//	CResourceMgr::RegisterResConstruct( CResourceMgr::MESHABIUNIT, ConstructMeshABIUnit );
	}
	~CRegisterDefaultResUnit( )
	{
		CResourceMgr::getSingle().UnRegisterAllResConstruct( );
	}
};

static CRegisterDefaultResUnit s_RegisterDefaultResUnit;
#endif

//////////////////////////////////////////////////////////////////

CResourceMgr::CResourceMgr(void)
{
	SetDefLessFunc(m_ConstructMap);
	SetDefLessFunc(m_ResourceMap);

	m_nMaxSize = 0;
	m_nSize = 0;
	m_bBuild = FALSE;
	m_nResTypeCount = OTHERUNIT;
	m_szPathID[0] = '\0';

	
	
}

CResourceMgr::~CResourceMgr(void)
{
	Release( );
}

BOOL CResourceMgr::Build( const char * szPathID, uint nMaxSize )
{
	RegisterResConstruct( CResourceMgr::FILEUNIT, ConstructFileUnit );
	RegisterResConstruct( CResourceMgr::XMLUNIT, ConstructXMLUnit );
	//RegisterResConstruct( CResourceMgr::ABIUNIT, ConstructABIUnit );
	//RegisterResConstruct( CResourceMgr::MESHABIUNIT, ConstructMeshABIUnit );

	strcpy( m_szPathID, szPathID);	
	m_nMaxSize = nMaxSize;
	m_Timer.Start( );	
	m_bBuild = TRUE;

	return TRUE;
}

BOOL CResourceMgr::Build( const wchar_t * szPathID, uint nMaxSize )
{
	char szAnsiPathID[256];
	WideCharToChar( szPathID, szAnsiPathID, 256 );
	return Build( szAnsiPathID, nMaxSize );
}

void CResourceMgr::Release( )
{	
	uint Index, IndexTemp;
	for( Index = m_ResourceMap.FirstInorder( ); m_ResourceMap.IsValidIndex( IndexTemp = Index ); )
	{
		ResourceUnit* pUnit = m_ResourceMap[IndexTemp];
		pUnit->Release( );
		Index = m_ResourceMap.NextInorder( IndexTemp );
		m_ResourceMap.RemoveAt( IndexTemp );
		delete pUnit;
	}
	m_vResClear.Purge();

	m_Timer.End( );
	m_bBuild = FALSE;

	UnRegisterAllResConstruct( );
}

BOOL CResourceMgr::RegisterResConstruct( int nType, ResUnitConstruct pConstruct )
{
	uint nIndex = m_ConstructMap.Find( nType );
	if( m_ConstructMap.IsValidIndex( nIndex ) )
		return TRUE;

	PCONSTRUCT_RESUNIT pConRes = new CONSTRUCT_RESUNIT( nType, pConstruct );

	if(m_ConstructMap.InvalidIndex() == m_ConstructMap.Insert( nType, pConRes )){
		SAFE_DELETE(pConRes)
		return FALSE;
	}

	return TRUE;
}

void CResourceMgr::UnRegisterResConstruct( int nType )
{
	int nIndex = m_ConstructMap.Find( nType );
	if( m_ConstructMap.IsValidIndex( nIndex ) )
	{
		PCONSTRUCT_RESUNIT pConRes = m_ConstructMap[nIndex];
		SAFE_DELETE(pConRes)
		m_ConstructMap.RemoveAt( nIndex );
		return;
	}

	UNREACHABLE( );
}

void CResourceMgr::UnRegisterAllResConstruct( )
{
	for( int nIndex = m_ConstructMap.FirstInorder( );m_ConstructMap.IsValidIndex( nIndex );nIndex = m_ConstructMap.NextInorder( nIndex ) )
	{
		PCONSTRUCT_RESUNIT pConRes = m_ConstructMap[nIndex];
		SAFE_DELETE(pConRes)
	}
	m_ConstructMap.RemoveAll( );
}

ResourceUnit * CResourceMgr::GetResourceUnit( const wchar_t * szName, int nResType )
{
	Assert( m_bBuild );

	char szAnsiName[256];
	WideCharToChar( szName, szAnsiName, 256 );
	return GetResourceUnit( szAnsiName, nResType );
}

ResourceUnit * CResourceMgr::GetResourceUnit( const char * szName, int nResType )
{
	Assert( m_bBuild );

	CUtlSymbol symName = m_NameIDTable.AddString( szName );
	return GetResourceUnit( symName, nResType );
}

ResourceUnit * CResourceMgr::GetResourceUnit( CUtlSymbol syName, int nResType )
{
//	if( m_nSize > m_nMaxSize / 3 * 2 )
//		RemoveAllNoUseByRefOrTime( 0, 60000000 );

	uint Index = m_ResourceMap.Find( syName );
	if( m_ResourceMap.IsValidIndex( Index ) )
	{
		ResourceUnit* pUnit = m_ResourceMap[Index];
		if( !pUnit->pData )
		{
			// 资源由于资源调度策略被暂时释放掉了
			// 或者是第一次使用 by zzp 05-09-23
			if( !pUnit->Load( ) )
				goto LoadResourceError;
		}
		pUnit->nTime = m_Timer.GetDurationInProgress( ).GetMilliseconds( );
		return pUnit;
	}

LoadResourceError:;
//	AssertMsg1( FALSE, "资源没有初始化(%s)", m_NameIDTable.String( syName ) );
	//Log( "资源没有初始化(%s)", m_NameIDTable.String( syName ) );
	return NULL;
//	else
//		return InitResourceUnit( syName, nResType );
}

int CResourceMgr::GetResourceUnit( CUtlVector <void*> & vRes )
{
	vRes.RemoveAll();
	int Index;
	for( Index = m_ResourceMap.FirstInorder( ); m_ResourceMap.IsValidIndex( Index ); )
	{
		ResourceUnit* pUnit = m_ResourceMap[Index];
		if( pUnit && pUnit->IsBuild() )
			vRes.AddToTail( (void*)pUnit );
		Index = m_ResourceMap.NextInorder( Index );
	}
	return vRes.Count();
}

BOOL CResourceMgr::BuildData( const wchar_t * szName, int nResType )
{
	Assert( m_bBuild );

	char szAnsiName[256];
	WideCharToChar( szName, szAnsiName, 256 );
	return BuildData( szAnsiName, nResType );
}

BOOL CResourceMgr::BuildData( const char * szName, int nResType )
{
	Assert( m_bBuild );

	CUtlSymbol symName = m_NameIDTable.AddString( szName );
	return BuildData( symName, nResType );
}

BOOL CResourceMgr::BuildData( CUtlSymbol syName, int nResType )
{
	Assert( m_bBuild );

	ResourceUnit* pUnit = NULL;
	uint Index = m_ResourceMap.Find( syName );
	if( m_ResourceMap.IsValidIndex( Index ) )
		pUnit = m_ResourceMap[Index];
	else
		pUnit = InitResourceUnit( syName, nResType );
	if( pUnit )
	{
		pUnit->IncreaseRef( );
		return TRUE;
	}

	//AssertMsg1( FALSE, "没找到对应的资源(%s)", m_NameIDTable.String( syName ) );
	Log( "没找到对应的资源(%s)\n", m_NameIDTable.String( syName ) );
	return FALSE;
}

void * CResourceMgr::GetData( const wchar_t * szName, int nResType )
{
	Assert( m_bBuild );

	char szAnsiName[256];
	WideCharToChar( szName, szAnsiName, 256 );
	return GetData( szAnsiName, nResType );
}

void * CResourceMgr::GetData( const char * szName, int nResType )
{
	Assert( m_bBuild );

	CUtlSymbol symName = m_NameIDTable.AddString( szName );
	return GetData( symName, nResType );
}

void * CResourceMgr::GetData( CUtlSymbol syName, int nResType )
{
	Assert( m_bBuild );

	ResourceUnit* pUnit = GetResourceUnit( syName, nResType );
	if( pUnit )
	{
		Assert( pUnit->IsBuild( ) );
		return pUnit->pData;
	}

	return NULL;
}

int CResourceMgr::GetData( CUtlVector <void*> & vData, int nResType )
{
	vData.RemoveAll();
	int Index;
	for( Index = m_ResourceMap.FirstInorder( ); m_ResourceMap.IsValidIndex( Index ); )
	{
		ResourceUnit* pUnit = m_ResourceMap[Index];
		if( pUnit && pUnit->IsBuild() && pUnit->pData )
			vData.AddToTail( pUnit->pData );
		Index = m_ResourceMap.NextInorder( Index );
	}
	return vData.Count();
}

//CUtlVector <DWORD> * CResourceMgr::GetClearData(  )
CUtlVector <uintptr_t> * CResourceMgr::GetClearData(  )
{
	m_vResClear.Purge();
	int Index;
	for( Index = m_ResourceMap.FirstInorder( ); m_ResourceMap.IsValidIndex( Index ); )
	{
		ResourceUnit* pUnit = m_ResourceMap[Index];
		if( pUnit && pUnit->IsBuild() && pUnit->pData )
//			m_vResClear.AddToTail( (DWORD)(pUnit->pData) );
			m_vResClear.AddToTail( (uintptr_t)(pUnit->pData) );
		Index = m_ResourceMap.NextInorder( Index );
	}
	return &m_vResClear;
}

void CResourceMgr::ReleaseData( const wchar_t * szName, int nCut )
{
	Assert( m_bBuild );

	char szAnsiName[256];
	WideCharToChar( szName, szAnsiName, 256 );
	ReleaseData( szAnsiName, nCut );
}

void CResourceMgr::ReleaseData( const char * szName, int nCut )
{
	Assert( m_bBuild );

	CUtlSymbol symName = m_NameIDTable.AddString( szName );
	ReleaseData( symName, nCut );
}

void CResourceMgr::ReleaseData( CUtlSymbol syName, int nCut )
{
	//Assert( m_bBuild );

	uint Index = m_ResourceMap.Find( syName );
	if( m_ResourceMap.IsValidIndex( Index ) )
	{
		ResourceUnit* pUnit = m_ResourceMap[Index];
		pUnit->DecreaseRef( );

		if( nCut > 1 )
		{
			while( pUnit->IsBuild() )
			{
				pUnit->DecreaseRef( );
				if( --nCut < 0 )
					break;
			}
		}
		Assert( pUnit->nRefCount >= 0 );
		if( pUnit->nRefCount <= 0 )
		{
			// 如果内存还没有到临界值，暂时先不释放内存
			if( m_nSize > m_nMaxSize * 3 / 2 )
			{
				m_nSize -= pUnit->GetLength( );
				pUnit->Release( );
				m_ResourceMap.RemoveAt( Index );
				delete pUnit;
			}
		}
	}
}

void CResourceMgr::RemoveAllNoUseByRef( uint nRef /*= 0*/ )
{
	Assert( m_bBuild );
/*
	uint Index, IndexTemp;
	for( Index = m_List.FirstInorder( ); m_List.IsValidIndex( IndexTemp = Index ); )
	{
		ResourceUnit* pUnit = m_List[IndexTemp];
		if( pUnit->nRefCount <= nRef )
		{
			pUnit->Release( );
			Index = m_List.NextInorder( IndexTemp );
			m_List.RemoveAt( IndexTemp );
			delete pUnit;
		}
		else
			Index = m_List.NextInorder( IndexTemp );
	}
*/
	uint Index;
	for( Index = m_ResourceMap.FirstInorder( ); m_ResourceMap.IsValidIndex( Index ); )
	{
//		if( m_nSize <= m_nMaxSize / 3 * 2 )
//			break;
		ResourceUnit* pUnit = m_ResourceMap[Index];
		if( pUnit->nRefCount <= (int)nRef )
		{
			m_nSize -= pUnit->GetLength( );
			pUnit->Release( );
		}
		Index = m_ResourceMap.NextInorder( Index );
	}
}

void CResourceMgr::RemoveAllNoUseByTime( uint nTime )
{
	Assert( m_bBuild );
/*
	uint Index, IndexTemp;
	for( Index = m_List.FirstInorder( ); m_List.IsValidIndex( IndexTemp = Index ); )
	{
		ResourceUnit* pUnit = m_List[IndexTemp];
		if( pUnit->nTime > nTime )
		{
			pUnit->Release( );
			Index = m_List.NextInorder( IndexTemp );
			m_List.RemoveAt( IndexTemp );
			delete pUnit;
		}
		else
			Index = m_List.NextInorder( IndexTemp );
	}
*/
	uint Index;
	for( Index = m_ResourceMap.FirstInorder( ); m_ResourceMap.IsValidIndex( Index ); )
	{
//		if( m_nSize <= m_nMaxSize / 3 * 2 )
//			break;
		ResourceUnit* pUnit = m_ResourceMap[Index];
		if( pUnit->nTime > nTime )
		{
			m_nSize -= pUnit->GetLength( );
			pUnit->Release( );
		}
		Index = m_ResourceMap.NextInorder( Index );
	}
}

// 释放最近最少使用的内存
void CResourceMgr::RemoveAllNoUseByRefOrTime( uint nRef, uint nTime )
{
	uint Index;
	for( Index = m_ResourceMap.FirstInorder( ); m_ResourceMap.IsValidIndex( Index ); )
	{
//		if( m_nSize <= m_nMaxSize / 3 * 2 )
//			break;
		ResourceUnit* pUnit = m_ResourceMap[Index];
		if( pUnit->nRefCount <= (int)nRef || pUnit->nTime > nTime )
		{
			m_nSize -= pUnit->GetLength( );
			pUnit->Release( );
		}

		Index = m_ResourceMap.NextInorder( Index );
	}
}

void CResourceMgr::RemoveAllNoUseByRefAndTime( uint nRef, uint nTime )
{
	Assert( m_bBuild );
/*
	uint Index, IndexTemp;
	for( Index = m_List.FirstInorder( ); m_List.IsValidIndex( IndexTemp = Index ); )
	{
		ResourceUnit* pUnit = m_List[IndexTemp];
		if( pUnit->nRefCount <= nRef && pUnit->nTime > nTime )
		{
			pUnit->Release( );
			Index = m_List.NextInorder( IndexTemp );
			m_List.RemoveAt( IndexTemp );
			delete pUnit;
		}
		else
			Index = m_List.NextInorder( IndexTemp );
	}
*/
	uint Index;
	for( Index = m_ResourceMap.FirstInorder( ); m_ResourceMap.IsValidIndex( Index ); )
	{
//		if( m_nSize <= m_nMaxSize / 3 * 2 )
//			break;
		ResourceUnit* pUnit = m_ResourceMap[Index];
		if( pUnit->nRefCount <= (int)nRef && pUnit->nTime > nTime )
		{
			m_nSize -= pUnit->GetLength( );
			pUnit->Release( );
		}

		Index = m_ResourceMap.NextInorder( Index );
	}
}
ResourceUnit * CResourceMgr::InitResourceUnit( CUtlSymbol syName, int nResType )
{
	Assert( m_bBuild );

	char szName[256] = { 0 };
	strcpy( szName, m_NameIDTable.String( syName ) );
	return InitResourceUnit( szName, nResType );
}

ResourceUnit * CResourceMgr::InitResourceUnit( const char * szName, int nResType )
{
	Assert( m_bBuild );
	if(!szName || !strlen(szName))
		return NULL;
/*
	ResourceUnit * pUnit = NULL;
	PRESOURCEUNIT_INFO pInfo = NULL;
	switch( nResType )
	{
	case FILEUNIT:
		pUnit = new FileUnit;
		pInfo = new FILEUNIT_INFO;
		((PFILEUNIT_INFO)pInfo)->nSize = sizeof( FILEUNIT_INFO );
		((PFILEUNIT_INFO)pInfo)->szName = szName;
		((PFILEUNIT_INFO)pInfo)->szPathID = m_szPathID;
		break;
	case XMLUNIT:
		pUnit = new XMLUnit;
		pInfo = new XMLUNIT_INFO;
		((PXMLUNIT_INFO)pInfo)->nSize = sizeof( FILEUNIT_INFO );
		((PXMLUNIT_INFO)pInfo)->szName = szName;
		((PXMLUNIT_INFO)pInfo)->szPathID = m_szPathID;
		break;
	case ABIUNIT:
		pUnit = new ABIUnit;
		pInfo = new ABIUNIT_INFO;
		((PABIUNIT_INFO)pInfo)->nSize = sizeof( ABIUNIT_INFO );
		((PABIUNIT_INFO)pInfo)->szName = szName;
		((PABIUNIT_INFO)pInfo)->szPathID = m_szPathID;
		break;
	case MESHABIUNIT:
		pUnit = new MeshABIUnit;
		pInfo = new MeshABIUNIT_INFO;
		((PMeshABIUNIT_INFO)pInfo)->nSize = sizeof( MeshABIUNIT_INFO );
		((PMeshABIUNIT_INFO)pInfo)->szName = szName;
		((PMeshABIUNIT_INFO)pInfo)->szPathID = m_szPathID;
		break;
	default:
		break;
	}

	if( pInfo && pUnit && pUnit->Build( pInfo ) )
	{
		CUtlSymbol symName = m_NameIDTable.AddString( szName );
		m_List.Insert( symName, pUnit );
		pUnit->nTime = m_Timer.GetDurationInProgress( ).GetMilliseconds( );
		pUnit->nRefCount++;
		m_nSize += pUnit->GetLength( );

		SAFE_DELETE( pInfo );

		return pUnit->pData;
	}
	SAFE_DELETE( pInfo );
	SAFE_DELETE( pUnit );
*/
	ResourceUnit * pUnit = NULL;
	int nIndex = m_ConstructMap.Find( nResType );
	if( m_ConstructMap.IsValidIndex( nIndex ) )
	{
		PCONSTRUCT_RESUNIT pConRes = m_ConstructMap[nIndex];
		if( (pUnit = (*pConRes->pConstruct)( szName, m_szPathID )) )
		{
			CUtlSymbol symName = m_NameIDTable.AddString( szName );
			m_ResourceMap.Insert( symName, pUnit );
			pUnit->nTime = m_Timer.GetDurationInProgress( ).GetMilliseconds( );
			m_nSize += pUnit->GetLength( );
		}
		else
		{
			Log( "没找到对应的资源(%s) \n", szName );
			if( (pUnit = (*pConRes->pConstruct)( "uiRes\\false.ani", m_szPathID )) )
			{
				CUtlSymbol symName = m_NameIDTable.AddString( szName );
				m_ResourceMap.Insert( symName, pUnit );
				pUnit->nTime = m_Timer.GetDurationInProgress( ).GetMilliseconds( );
				m_nSize += pUnit->GetLength( );
			}
		}
	}

	return pUnit;
}

void CResourceMgr::OutputResInfo( )
{
	Log( "----------------CResourceMgr::OutputResInfo( )------------------" );
	uint Index;
	for( Index = m_ResourceMap.FirstInorder( ); m_ResourceMap.IsValidIndex( Index ); )
	{
		ResourceUnit* pUnit = m_ResourceMap[Index];
		Log( "%s\t%d\t%d", m_NameIDTable.String( pUnit->syName ), pUnit->nRefCount, pUnit->nTime );
		Index = m_ResourceMap.NextInorder( Index );
	}
}
