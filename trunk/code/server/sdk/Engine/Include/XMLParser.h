#pragma once
#include "BaseObj.h"
#include "McbXML.h"
#include "dbg.h" // AssertMsg3
#include "vector4d.h"

class ENGINE_CLASS IXMLParser : public IBaseObj
{
	DECLARE_CLASS( IXMLParser )
public:
	IXMLParser(void);
	IXMLParser( McbXMLElement * pElement );
	IXMLParser( IXMLParser * Element, LPCWSTR lpName );
	virtual ~IXMLParser(void);

	/*
	从文件中加载XML信息
	*/
	BOOL Load( LPCSTR lpName, LPCSTR lpPathID );
	BOOL Load( LPCWSTR lpName, LPCWSTR lpPathID );

	// 通过绝对路径访问文件 By Davidyang 2007-12-25
	BOOL LoadEx( LPCSTR	lpName );
	BOOL SaveEx( LPCSTR lpName );

	BOOL LoadFromBuffer( LPCWSTR lpText );
	/*
	保存XML信息到文件中
	*/
	BOOL Save( LPCSTR lpName, LPCSTR lpPathID );
	BOOL Save( LPCWSTR lpName, LPCWSTR lpPathID );

	/*
	根据pElement指定的元素创建
	*/
	BOOL Build( McbXMLElement * pElement );
	/*
	建立新节点，在pElement节点下面建立名为lpName的子节点，pElement为空则为根节点
	*/
	BOOL Build( IXMLParser * pElement, LPCWSTR lpName );
	void Release( );

	void Destroy( LPCWSTR lpPath );

	BOOL GetXMLString( LPWSTR & lpString, int & nLength );
	void ReleaseXMLString( LPWSTR & lpString );

	/*
	取得节点属性
	*/
	BOOL GetAttribute( LPCWSTR lpAttribute, LPWSTR lpValue, int nSize );
	BOOL GetAttribute( LPCWSTR lpAttribute, LPSTR lpValue, int nSize );
	BOOL GetAttribute( LPCWSTR lpAttribute, int & nValue );
	BOOL GetAttribute( LPCWSTR lpAttribute, uint & nValue );
	BOOL GetAttribute( LPCWSTR lpAttribute, uint16 & nValue );
	BOOL GetAttribute( LPCWSTR lpAttribute, float & nValue );
	BOOL GetAttribute( LPCWSTR lpAttribute, long & nValue );
	BOOL GetAttribute( LPCWSTR lpAttribute, uint8 & nValue );
	BOOL GetAttribute( LPCWSTR lpAttribute, int16 & nValue );
	BOOL GetAttribute( LPCWSTR lpAttribute, uint64 & nValue );
	BOOL GetAttribute( LPCWSTR lpAttribute, Vector4D& nValue ); // by Chord 2008.10.14
	/*
	设置节点属性，如果该节点没有需要设置的属性则创建该属性并且赋值
	*/
	BOOL SetAttribute( LPCWSTR lpAttribute, LPCWSTR lpValue );
	BOOL SetAttribute( LPCWSTR lpAttribute, LPCSTR lpValue );
	BOOL SetAttribute( LPCWSTR lpAttribute, int nValue );
	BOOL SetAttribute( LPCWSTR lpAttribute, uint nValue );
	BOOL SetAttribute( LPCWSTR lpAttribute, uint16 nValue );
	BOOL SetAttribute( LPCWSTR lpAttribute, float nValue );
	BOOL SetAttribute( LPCWSTR lpAttribute, long nValue );
	BOOL SetAttribute( LPCWSTR lpAttribute, uint8 nValue );
	BOOL SetAttribute( LPCWSTR lpAttribute, int16 nValue );
	BOOL SetAttribute( LPCWSTR lpAttribute, uint64 nValue );
	BOOL SetAttribute( LPCWSTR lpAttribute, Vector4D& nValue ); // by Chord 2008.10.14
	/*
	得到当前节点
	*/
	inline McbXMLElement * GetElement( ){ return m_pRoot; }

	inline BOOL IsExternBuild( ){ return m_bExtern; }

	/*
	获得节点名称
	*/
	LPCWSTR GetName( );
	/*
	设置节点名称
	*/
	void SetName( LPCWSTR lpName );
	/*
	获得节点内容
	*/
	LPCWSTR GetText( );
	/*
	设置节点内容
	lpText 要设置的内容字符串
	*/
	void SetText( LPCWSTR lpText );

	/*
	取得子节点个数，属性、内容也算作其子节点
	当循环遍历子节点的时候要注意：需要通过节点名称或者节点类型判定是否是自己真正需要的子节点
	因为属性、内容也被当作子节点看待了
	*/
	inline int GetChildCount( );

	/*
	取得子节点
	nIndex 要取得的节点索引，成功nIndex指向下一个节点
	*/
	inline McbXMLElement * GetChild( LPCWSTR lpPath );
	inline McbXMLElement * GetChild( int nIndex );
	inline McbXMLElement * GetChildByStartIndex(int nIndex , int& startIndex );
	inline McbXMLElement * operator [] ( int nIndex );
	inline McbXMLElement * operator [] ( LPCWSTR lpPath );

	inline IXMLParser & operator = ( IXMLParser & Element );

private:
	McbXMLElement * m_pRoot; // 根元素，其下面包含属性，内容以及子节点
	BOOL m_bExtern;
};


inline McbXMLElement * IXMLParser::GetChild( int nIndex )
{
	Assert( m_pRoot );
	int nCount = 0;
	int i = 0;
	McbXMLElement * pChild = NULL;
	while( (pChild = McbEnumElements( m_pRoot, &i )) )
	{
		if( nIndex == nCount )
			return pChild;
		nCount++;
	}

	return pChild;
}
// 从一个节点后再第几个  GetChildByStartIndex( 1 , 0 ) 取第一个 StartIndex 为了节省一次运算 返回的是当前取到节点的下一个位置 [8/7/2009 sun ]
inline McbXMLElement * IXMLParser::GetChildByStartIndex( int nIndex , int& startIndex )
{
	Assert( m_pRoot );
	int nCount = 1;
	McbXMLElement * pChild = NULL;

	while( (pChild = McbEnumElements( m_pRoot, &startIndex )) )
	{
		if( nIndex == nCount )
			return pChild;
		nCount++;
	}

	return pChild;
}

inline McbXMLElement * IXMLParser::GetChild( LPCWSTR lpPath )
{
	Assert( m_pRoot );

	return McbFindElement( m_pRoot, lpPath );
}

inline McbXMLElement * IXMLParser::operator [] ( int nIndex )
{
	Assert( m_pRoot );
	int i = 0;
	int nCount = 0;
	McbXMLElement * pChild = NULL;
	while( (pChild = McbEnumElements( m_pRoot, &i )) )
	{
		if( nIndex == nCount )
			return pChild;
		nCount++;
	}

	return pChild;
}

inline McbXMLElement * IXMLParser::operator [] ( LPCWSTR lpPath )
{
	//Assert( m_pRoot );

/*
	if (!m_pRoot) {
		printf("m_pRoot is NULL. in file %s\n", __FILE__);
	}
	printf("m_pRoot->nSize = %d in file %s line %d\n", m_pRoot->nSize, __FILE__, __LINE__);
*/
	if( m_pRoot )
		return McbFindElement( m_pRoot, lpPath );

	return NULL;
}

inline int IXMLParser::GetChildCount( )
{
	Assert( m_pRoot );
	int i = 0;
	int nCount = 0;
	McbXMLElement * pChild = NULL;
	while( (pChild = McbEnumElements( m_pRoot, &i )) )++nCount;
	return nCount;
}

inline IXMLParser & IXMLParser::operator = ( IXMLParser & Element )
{
	m_pRoot		= Element.GetElement( );
	m_bExtern	= Element.IsExternBuild( );
	return *this;
}

/*************************************
// Example
	IXMLParser Root( NULL, L"AAAA" );
	IXMLParser Child1( &Root, L"BBBB" );
	Child1.SetAttribute( L"CCCC", L"DDDD" );
	Child1.SetAttribute( L"EEEE", 100 );
	Child1.SetText( L"FFFF" );
	IXMLParser Child2( &Child1, L"GGGG" );
	Child2.SetAttribute( L"HHHH", L"IIII" );
	Child2.SetAttribute( L"JJJJ", 200 );
	Child2.SetText( L"KKKK" );
	Root.Save( "Scene001/111.xml", "RES_PATH" );
	Root.Release( );
	Root.Load( "Scene001/111.xml", "RES_PATH" );
	int nIndex = 0;
	IXMLParser Child3 = Root[L"AAAA/BBBB"];
	int n;
	Child3.GetAttribute( L"EEEE", n );
	Assert( n == 100 );
	nIndex = 0;
	IXMLParser Child4 = Child3[nIndex];
	Child4.GetAttribute( L"JJJJ", n );
	Assert( n == 200 );

DISPLAY:
	<AAAA>
		<BBBB CCCC= DDDD" EEEE=100>
			FFFF
			<GGGG HHHH="IIII" JJJJ=200>
				KKKK
			</GGGG>
		</BBBB>
	</AAAA>
*/
