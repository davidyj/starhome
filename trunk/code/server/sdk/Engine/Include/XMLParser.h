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
	���ļ��м���XML��Ϣ
	*/
	BOOL Load( LPCSTR lpName, LPCSTR lpPathID );
	BOOL Load( LPCWSTR lpName, LPCWSTR lpPathID );

	// ͨ������·�������ļ� By Davidyang 2007-12-25
	BOOL LoadEx( LPCSTR	lpName );
	BOOL SaveEx( LPCSTR lpName );

	BOOL LoadFromBuffer( LPCWSTR lpText );
	/*
	����XML��Ϣ���ļ���
	*/
	BOOL Save( LPCSTR lpName, LPCSTR lpPathID );
	BOOL Save( LPCWSTR lpName, LPCWSTR lpPathID );

	/*
	����pElementָ����Ԫ�ش���
	*/
	BOOL Build( McbXMLElement * pElement );
	/*
	�����½ڵ㣬��pElement�ڵ����潨����ΪlpName���ӽڵ㣬pElementΪ����Ϊ���ڵ�
	*/
	BOOL Build( IXMLParser * pElement, LPCWSTR lpName );
	void Release( );

	void Destroy( LPCWSTR lpPath );

	BOOL GetXMLString( LPWSTR & lpString, int & nLength );
	void ReleaseXMLString( LPWSTR & lpString );

	/*
	ȡ�ýڵ�����
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
	���ýڵ����ԣ�����ýڵ�û����Ҫ���õ������򴴽������Բ��Ҹ�ֵ
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
	�õ���ǰ�ڵ�
	*/
	inline McbXMLElement * GetElement( ){ return m_pRoot; }

	inline BOOL IsExternBuild( ){ return m_bExtern; }

	/*
	��ýڵ�����
	*/
	LPCWSTR GetName( );
	/*
	���ýڵ�����
	*/
	void SetName( LPCWSTR lpName );
	/*
	��ýڵ�����
	*/
	LPCWSTR GetText( );
	/*
	���ýڵ�����
	lpText Ҫ���õ������ַ���
	*/
	void SetText( LPCWSTR lpText );

	/*
	ȡ���ӽڵ���������ԡ�����Ҳ�������ӽڵ�
	��ѭ�������ӽڵ��ʱ��Ҫע�⣺��Ҫͨ���ڵ����ƻ��߽ڵ������ж��Ƿ����Լ�������Ҫ���ӽڵ�
	��Ϊ���ԡ�����Ҳ�������ӽڵ㿴����
	*/
	inline int GetChildCount( );

	/*
	ȡ���ӽڵ�
	nIndex Ҫȡ�õĽڵ��������ɹ�nIndexָ����һ���ڵ�
	*/
	inline McbXMLElement * GetChild( LPCWSTR lpPath );
	inline McbXMLElement * GetChild( int nIndex );
	inline McbXMLElement * GetChildByStartIndex(int nIndex , int& startIndex );
	inline McbXMLElement * operator [] ( int nIndex );
	inline McbXMLElement * operator [] ( LPCWSTR lpPath );

	inline IXMLParser & operator = ( IXMLParser & Element );

private:
	McbXMLElement * m_pRoot; // ��Ԫ�أ�������������ԣ������Լ��ӽڵ�
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
// ��һ���ڵ���ٵڼ���  GetChildByStartIndex( 1 , 0 ) ȡ��һ�� StartIndex Ϊ�˽�ʡһ������ ���ص��ǵ�ǰȡ���ڵ����һ��λ�� [8/7/2009 sun ]
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
