#include "../stdafx.h"
#include "TextTable.h"
#include "ExcelTable.h"

#include "ICommandLine.h" // CommandLine
#include "strtools.h" // CharToWideChar


// 依赖于CommandLine模块，和Run.cfg
CTextTable::CTextTable(void)
{
	SetDefLessFunc( m_TextMapTable );
}

CTextTable::~CTextTable(void)
{
	Close( );
}

BOOL CTextTable::Open( const wchar_t * szName, const wchar_t * szTable, const wchar_t * szPath )
{
	// szPathID + LanguageID + szName
	// "Language/" + "CHS/" + "task1.xml"
	CExcelTable TextExcel;
	const char * szLanguage = CommandLine( ).ParmValue( "Language", "CHS" );
	wchar_t szTableName[256] = { L"\0" };
	if( szLanguage[0] != 0 )
	{
		CharToWideChar( szLanguage, szTableName, 256 );
		wcscat( szTableName, L"/" );
	}
	wcscat( szTableName, szName );
	if( TextExcel.ReadExcelTable( szTableName, szTable, szPath ) )
	{
		// 两列，序号和内容
		Assert( TextExcel.GetMaxCol( ) == 2 );
		int nID;
		wchar_t szData[2048];
		int nLine = TextExcel.GetMaxLine( );
		for( int i = 0; i < nLine; i++ )
		{
			TextExcel.ReadInt( i, 0, nID );
			TextExcel.ReadStr( i, 1, szData, 2048 );
			int nLen = wcslen( szData ) + 1;
			wchar_t * pszData = (wchar_t *)Plat_Alloc( sizeof( wchar_t ) * nLen );
			wcscpy( pszData, szData );
			m_TextMapTable.Insert( nID, pszData );
		}

		return TRUE;
	}

	return FALSE;
}

BOOL CTextTable::Open( const wchar_t * szName, const wchar_t * szPath )
{
	// szPathID + LanguageID + szName
	// "Language/" + "CHS/" + "task1.xml"
	CExcelTable TextExcel;
	const char * szLanguage = GetLanguagePath( );
	wchar_t szTableName[256] = { L"\0" };
	if( szLanguage[0] != 0 )
	{
		CharToWideChar( szLanguage, szTableName, 256 );
		wcscat( szTableName, L"/" );
	}
	wcscat( szTableName, szName );
	if( TextExcel.Open( szTableName, szPath ) && 
		TextExcel.ReadAllSheet( ) )
	{
		// 两列，序号和内容
		Assert( TextExcel.GetMaxCol( ) >= 2 );
		int nID;
		wchar_t szData[2048];
		int nLine = TextExcel.GetMaxLine( );
		for( int i = 0; i < nLine; i++ )
		{
			TextExcel.ReadStr( i, 0, szData, 2048 );
			if( !IsNumber( szData ) )
				continue;
			TextExcel.ReadInt( i, 0, nID );
			TextExcel.ReadStr( i, 1, szData, 2048 );
			int nLen = wcslen( szData ) + 1;
			wchar_t * pszData = (wchar_t *)Plat_Alloc( sizeof( wchar_t ) * nLen );
			wcscpy( pszData, szData );
			m_TextMapTable.Insert( nID, pszData );
		}

		return TRUE;
	}

	return FALSE;
}

void CTextTable::Close( )
{
	for( int nIndex = m_TextMapTable.FirstInorder( ); m_TextMapTable.IsValidIndex( nIndex ); )
	{
		wchar_t * pszData = m_TextMapTable[nIndex];
		Plat_Free( pszData );
		nIndex = m_TextMapTable.NextInorder( nIndex );
	}
	m_TextMapTable.RemoveAll( );
}

wchar_t * CTextTable::GetText( int nID )
{
	int nIndex = m_TextMapTable.Find( nID );
	if( m_TextMapTable.IsValidIndex( nIndex ) )
		return m_TextMapTable[nIndex];
#ifdef WIN32	
	return L"";
#else
	return (wchar_t *)NULL;
#endif	
}

int CTextTable::GetIDByText( wchar_t * szText )
{
	for( int nIndex = m_TextMapTable.FirstInorder( ); 
			m_TextMapTable.IsValidIndex( nIndex );
			nIndex = m_TextMapTable.NextInorder( nIndex ) )
	{
		if( wcscmp( m_TextMapTable[nIndex], szText ) == 0 )
			return m_TextMapTable.Key( nIndex );
	}
	return -1;
}

const char * GetLanguagePath( )
{
	return CommandLine( ).ParmValue( "Language", "CHS" );
}
