#pragma once
#include "BaseObj.h"
#include "utlmap.h"
#include "utlsymbol.h"
#include "utllinkedlist.h"
#include "fasttimer.h"
#include "FileStdio.h"
#include "XMLParser.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "memdbgon.h"

typedef struct _ResourceUnit_Info
{
	int nSize;
	LPCSTR szName;
	LPCSTR szPathID;
}RESOURCEUNIT_INFO,*PRESOURCEUNIT_INFO,**LPRESOURCEUNIT_INFO;

class CResourceMgr;
class ENGINE_CLASS ResourceUnit : public IBaseObj
{
	DECLARE_CLASS( ResourceUnit )
	friend class CResourceMgr;
private:
	uint nTime;		// 最后一次被访问到的时间
	int  nRefCount;	// 引用计数
public:
	CUtlSymbol syName;
	CUtlSymbol syPathID;
	uint nLength;
	void * pData;	// 数据

	ResourceUnit( )
	{
		nLength = 0;
		nTime = 0;
		nRefCount = 0;
		pData = NULL;
	}

	inline BOOL IsBuild( ){ return nRefCount > 0; }
	inline void IncreaseRef( ){ nRefCount++; }
	inline void DecreaseRef( ){ nRefCount--; }

	inline int GetLength( ){ return nLength; }

	virtual void Release( ){ pData = NULL; nLength = 0; }
	virtual BOOL Build( PRESOURCEUNIT_INFO pInfo ) = 0;
	virtual BOOL Load( ){ return TRUE; }
};

///////////////////////////////////////////////////////////////////
// 资源构造器
typedef ResourceUnit * (*ResUnitConstruct)( const char * szName, const char * szPathID );

typedef struct CONSTRUCT_RESUNIT
{
	int nType;
	ResUnitConstruct pConstruct;
	CONSTRUCT_RESUNIT( int nTypeArg, ResUnitConstruct pConstructArg )
	{
		Assert( pConstructArg );
		nType		= nTypeArg;
		pConstruct	= pConstructArg;
	}
}*PCONSTRUCT_RESUNIT, **LPCONSTRUCT_RESUNIT;

#define CONSTRUCT_X_UNIT( UnitClass, UnitInfo, Name, PathID ) \
	UnitClass * pUnit	= new UnitClass; \
	UnitInfo * pInfo= new UnitInfo; \
	if( !pUnit || !pInfo ) \
		return NULL; \
	pInfo->nSize			= sizeof( UnitInfo ); \
	pInfo->szName			= szName; \
	pInfo->szPathID			= szPathID; \
	if( pUnit->Build( pInfo ) ) \
	{ \
		delete pInfo; \
		return pUnit; \
	} \
	delete pUnit; \
	delete pInfo; \
	return NULL;

/////////////////////////////////////////////////////////////////////
///
class ENGINE_CLASS CResourceMgr : public IBaseObj
{
public:
	enum RESUNIT_TYPE
	{
		FILEUNIT = 0,
		XMLUNIT,
		ABIUNIT,  // CAbi pointer by 
		MESHABIUNIT,
		OTHERUNIT,
	};
	
	static CResourceMgr& getSingle(){
		static CResourceMgr mgr;
		return mgr;
	}
protected:
	CResourceMgr(void);
	virtual ~CResourceMgr(void);

public:
	BOOL Build( const char * szPathID, uint nMaxSize );
	BOOL Build( const wchar_t * szPathID, uint nMaxSize );
	void Release( );

	BOOL RegisterResConstruct( int nType, ResUnitConstruct pConstruct );
	void UnRegisterResConstruct( int nType );
	void UnRegisterAllResConstruct( );	

	ResourceUnit * GetResourceUnit( const wchar_t * szName, int nResType );
	ResourceUnit * GetResourceUnit( const char * szName, int nResType );
	ResourceUnit * GetResourceUnit( CUtlSymbol syName, int nResType );
	int		GetResourceUnit( CUtlVector <void*> & vRes );

	BOOL BuildData( const wchar_t * szName, int nResType );
	BOOL BuildData( const char * szName, int nResType );
	BOOL BuildData( CUtlSymbol syName, int nResType );

	void * GetData( const wchar_t * szName, int nResType );
	void * GetData( const char * szName, int nResType );
	void * GetData( CUtlSymbol syName, int nResType );
	int		GetData( CUtlVector <void*> & vData, int nResType );

	void ReleaseData( const wchar_t * szName, int nCut = 0 );
	void ReleaseData( const char * szName, int nCut = 0 );
	void ReleaseData( CUtlSymbol syName, int nCut = 0 );

	//CUtlVector <DWORD> * GetClearData(  );
	CUtlVector <uintptr_t> * GetClearData(  );
	// 释放小于指定引用次数的内存
	void RemoveAllNoUseByRef( uint nRef = 0 );
	// 释放大于指定引用时间的内存
	void RemoveAllNoUseByTime( uint nTime = 0 );
	// 释放最近最少使用的内存
	void RemoveAllNoUseByRefAndTime( uint nRef = 0, uint nTime = 0 );
	// 释放最近最少使用的内存
	void RemoveAllNoUseByRefOrTime( uint nRef = 0, uint nTime = 0 );

	inline 	uint GetSize( ){ return m_nSize; }

	inline BOOL IsBuild( ){ return m_bBuild; }

	CUtlSymbolTable* GetNameTable( ){ return &m_NameIDTable; }

	int IncreaseResType( ){return m_nResTypeCount++;}

	void OutputResInfo( );

private:
	ResourceUnit * InitResourceUnit( const char * szName, int nResType );
	ResourceUnit * InitResourceUnit( CUtlSymbol syName, int nResType );

private:
	CUtlSymbolTable m_NameIDTable;								// 资源名称表
	CUtlMap<int,PCONSTRUCT_RESUNIT> m_ConstructMap;			// 构造资源表
//	static CUtlLinkedList<PCONSTRUCT_RESUNIT, uint8> m_ConstructList;	// 构造资源表
	int m_nResTypeCount;

	CUtlMap<CUtlSymbol, ResourceUnit*, int> m_ResourceMap;						// 资源
	//CUtlDict<ResourceUnit*,int>			m_ResourceDict;

//	CUtlVector <DWORD> m_vResClear;
	CUtlVector <uintptr_t> m_vResClear;
	CFastTimer m_Timer;
	uint m_nMaxSize;
	uint m_nSize;
	char m_szPathID[256];
	BOOL m_bBuild;
};


///////////////////////////////////////////////////////////////////

class ENGINE_CLASS FileUnit : public ResourceUnit
{
	DECLARE_CLASS( FileUnit )
public:
	virtual void Release( )
	{
		if( pData )
			ReleaseFileBuffer( pData );

		ResourceUnit::Release( );
	}
	virtual BOOL Build( PRESOURCEUNIT_INFO pInfo )
	{
		Assert( pInfo != NULL );
		AssertValidReadPtr( pInfo, sizeof( RESOURCEUNIT_INFO ) );

		syName = CResourceMgr::getSingle().GetNameTable( )->AddString( pInfo->szName );
		syPathID = CResourceMgr::getSingle().GetNameTable( )->AddString( pInfo->szPathID );

		nLength = GetFileLength( pInfo->szName, pInfo->szPathID );
		if( nLength > 0 )
			return TRUE;
		return FALSE;
	}
	virtual BOOL Load( )
	{
		const char * szName = CResourceMgr::getSingle().GetNameTable( )->String( syName );
		const char * szPathID = CResourceMgr::getSingle().GetNameTable( )->String( syPathID );
		pData = LoadFileToBuffer( szName, szPathID, &nLength );
		if( pData )
			return TRUE;
		return FALSE;
	}
};

inline ResourceUnit * ConstructFileUnit( const char * szName, const char * szPathID )
{
	CONSTRUCT_X_UNIT( FileUnit, RESOURCEUNIT_INFO, szName, szPathID );
}

class ENGINE_CLASS XMLUnit : public ResourceUnit
{
	DECLARE_CLASS( XMLUnit )
public:
	virtual void Release( )
	{
		IXMLParser* pXML = (IXMLParser*)pData;
		SAFE_DELETE( pXML );

		ResourceUnit::Release( );
	}
	virtual BOOL Build( PRESOURCEUNIT_INFO pInfo )
	{
		Assert( pInfo != NULL );
		AssertValidReadPtr( pInfo, sizeof( RESOURCEUNIT_INFO ) );

		syName = CResourceMgr::getSingle().GetNameTable( )->AddString( pInfo->szName );
		syPathID = CResourceMgr::getSingle().GetNameTable( )->AddString( pInfo->szPathID );

		nLength = GetFileLength( pInfo->szName, pInfo->szPathID );
		if( nLength > 0 )
			return TRUE;
		return FALSE;
	}
	virtual BOOL Load( )
	{
		const char * szName = CResourceMgr::getSingle().GetNameTable( )->String( syName );
		const char * szPathID = CResourceMgr::getSingle().GetNameTable( )->String( syPathID );
		wchar_t * pXMLText = (wchar_t *)LoadFileToBuffer( szName, szPathID, &nLength );
		if( pXMLText )
		{
			pData = new IXMLParser;
			if( pData )
			{
				if( ((IXMLParser*)pData)->LoadFromBuffer( pXMLText ) )
				{
					ReleaseFileBuffer( pXMLText );
					return TRUE;
				}
				IXMLParser* pXML = (IXMLParser*)pData;
				SAFE_DELETE( pXML );
			}
		}
		ReleaseFileBuffer( pXMLText );
		return FALSE;
	}
};

inline ResourceUnit * ConstructXMLUnit( const char * szName, const char * szPathID )
{
	CONSTRUCT_X_UNIT( XMLUnit, RESOURCEUNIT_INFO, szName, szPathID );
}

