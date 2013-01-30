#include "../stdafx.h"
#include "ExcelTable.h"
#include "strtools.h"
#include "FileStdio.h"
#include "Encrypt.h" // StrEncrypt
#include "dbg.h"
//#include "pathFunc.h"

#ifndef WIN32
#include <stdlib.h>
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "memdbgon.h"


CExcelTable::CExcelTable( )
{
	m_nMaxLine		= 0;
	m_nMaxCol		= 0;
	m_aExcelTable	= NULL;
	m_LineMap		= NULL;
}

CExcelTable::~CExcelTable( )
{
	Close( );
}

void CExcelTable::Close( )
{
	Reset( );
	ReleaseXML( );
}

void CExcelTable::Reset( )
{
	if( m_aExcelTable )
	{
		for( int i = 0; i < m_nMaxLine; i++ )	
		{
			/*		if( m_aExcelTable[i] && m_aExcelTable[i][0].Base( ) )
			{
			char szData[256] = { 0 };
			WideCharToChar( m_aExcelTable[i][0].Base( ), szData, 256 );
			Log( szData );
			}*/

			SAFE_DELETE_ARRAY( m_aExcelTable[i] );
		}

		Plat_Free( m_aExcelTable );
		m_aExcelTable = NULL;
	}

	if ( m_LineMap )
	{
		for( int j = 0; j < m_nMaxCol; j++ )
		{
			uint Index, IndexTemp;
			for( Index = m_LineMap[j].FirstInorder( ); m_LineMap[j].IsValidIndex( IndexTemp = Index ); )
			{
				Line_List * pLine = m_LineMap[j][IndexTemp];
				delete pLine;
				Index = m_LineMap[j].NextInorder( IndexTemp );
			}
			m_LineMap[j].RemoveAll( );
		}
		SAFE_DELETE_ARRAY( m_LineMap );
	}
	
	m_nMaxLine	= 0;
	m_nMaxCol	= 0;
}

void	CExcelTable::ReadInt( int iLn,int iCol,WORD	&iData )
{
	int	i;
	ReadInt( iLn, iCol, i );
	iData = i;
}

void CExcelTable::ReadByte( int nLine, int nCol, BYTE &bData )
{
	int nValue = 0;
	ReadInt( nLine, nCol, nValue );
	bData = nValue;
}

void	CExcelTable::ReadStr( int nLine, int nCol, wchar_t* output, int nSize )
{
	if( !IsOpened( ) )
		return;

	if( ISIN( nLine, 0, m_nMaxLine - 1 ) && ISIN( nCol, 0, m_nMaxCol - 1 ) &&
		m_aExcelTable[nLine] && m_aExcelTable[nLine][nCol].Base( ) )
	{
		LPWSTR szTemp = (LPWSTR)m_aExcelTable[nLine][nCol].Base( );
		if( szTemp )
		{
			int nLen = wcslen( szTemp );
			Assert( nLen < nSize );
			if( nLen <= 0 )
				memset( output, 0, nSize * sizeof( wchar_t) );
			else
				wcscpy( output, szTemp );
		}
		else
		{
			memset( output, 0, nSize * sizeof( wchar_t) );
		}
	}
	else
	{
		memset( output, 0, nSize * sizeof( wchar_t) );
	}
}
void	CExcelTable::ReadStr( int nLine,int nCol,char* output,int nSize )
{
	if( !IsOpened( ) )
		return;

	if( ISIN( nLine ,0,m_nMaxLine-1 ) && ISIN( nCol ,0,m_nMaxCol-1 ) &&
		m_aExcelTable[nLine] && m_aExcelTable[nLine][nCol].Base( ) )
	{
		LPWSTR szTemp	= (LPWSTR)m_aExcelTable[nLine][nCol].Base( );
		if( szTemp )
		{
			int	   nLen		= wcslen( szTemp );
			Assert( nLen < nSize );
			if( nLen <= 0 )
				memset( output, 0, nSize );
			else
				WideCharToChar( szTemp, output, nSize );
		}
		else
		{
			memset( output, 0, nSize );
		}
	}
	else
	{
		memset( output, 0, nSize );
	}
}

void	CExcelTable::ReadInt( int iLn,int iCol,int	&iData )
{
	if( !IsOpened( ) )
		return;

	wchar_t szTemp[256] = { 0 };
	ReadStr( iLn,iCol,szTemp,256 );
	int	   iLen	= wcslen( szTemp );
	if( iLen <= 0 )
		iData = EXCEL_INVALID;
	else iData = _wtoi( szTemp );
}

/*
 * _wtof's declaretion:
 * double _wtof(const wchar_t *str); // of vc++
 *
 * its equivalent function is wcstod //c99
 *
 */
void	CExcelTable::ReadFloat( int nLine, int nCol, float &fData )
{
	if( !IsOpened( ) )
		return;

	wchar_t szTemp[256] = { 0 };
	ReadStr( nLine,nCol,szTemp,256 );
	int	   iLen	= wcslen( szTemp );
	if( iLen <= 0 )
		fData = EXCEL_INVALID;
	else 
#ifdef WIN32		
		fData = _wtof( szTemp );
#else	
		fData = wcstod( szTemp, NULL ); //fData is type of float
#endif	
}

int	CExcelTable::FindLine( int nCol, int iData )
{
	if( !IsOpened( ) )
		return -1;

	wchar_t szData[256];
#ifdef WIN32	
	swprintf( szData, L"%d", iData );
#else	
	swprintf( szData, 256, L"%d", iData );
#endif
	return FindLine( nCol, szData );
/*
	int nIndex = m_LineMap[nCol].Find( szData );
	if( m_LineMap[nCol].IsValidIndex( nIndex ) )
		return (*m_LineMap[nCol][nIndex])[0];
	return -1;*/
/*
	int nTempData;
	int i;
	for( i=1;i<m_nMaxLine;i++ )
	{
		ReadInt( i,nCol,nTempData );
		if( iData == nTempData )
			return	i;
	}
	return -1;*/
}

int		CExcelTable::FindLine( int nCol, const char* szData )
{
	if( !IsOpened( ) )
		return -1;

	wchar_t szwData[256];
	CharToWideChar( szData, szwData, 256 );
	return FindLine( nCol, szwData );
/*
	int nIndex = m_LineMap[nCol].Find( szwData );
	if( m_LineMap[nCol].IsValidIndex( nIndex ) )
		return (*m_LineMap[nCol][nIndex])[0];
	return -1;*/
/*
	char szTemp[256] = { 0 };
	int i;
	for( i=1;i<m_nMaxLine;i++ )
	{
		ReadStr( i,nCol,szTemp,256 );
		if( Q_strcmp( szTemp, szData ) == 0 )
			return	i;
	}
	return -1;*/
}

int		CExcelTable::FindLine( int nCol, const wchar_t* szData )
{
	int nIndex = m_LineMap[nCol].Find( szData );
	if( m_LineMap[nCol].IsValidIndex( nIndex ) )
		return (*m_LineMap[nCol][nIndex])[0];
	return -1;
/*
	wchar_t szTemp[256] = { 0 };
	int i;
	for( i=1;i<m_nMaxLine;i++ )
	{
		ReadStr( i,nCol,szTemp,256 );
		if( wcscmp( szTemp, szData ) == 0 )
			return	i;
	}
	return -1;*/
}

int CExcelTable::FindLineEx( int nCol, int nMin, int nMax, int * pLines, int nCount )
{
	if( !IsOpened( ) )
		return -1;

	AssertValidWritePtr( pLines, sizeof( int ) * nCount );

	int nCounter = 0;
	int nRemainCount = 0;
	for( int i = nMin; i <= nMax; i++ )
	{
		wchar_t szData[256];
#ifdef WIN32		
		swprintf( szData, L"%d", i );
#else		
		swprintf( szData, 256, L"%d", i );
#endif		
		int nIndex = m_LineMap[nCol].Find( szData );
		if( m_LineMap[nCol].IsValidIndex( nIndex ) )
		{
			Line_List * pLineList = m_LineMap[nCol][nIndex];
			nCounter += pLineList->Count( );
			if( nCounter > nCount )
				nCounter = nCount;
			memcpy( pLines, pLineList->Base( ), ( nCounter - nRemainCount ) * sizeof( int ) );
			if( nCounter == nCount )
				break;
			pLines += nCounter - nRemainCount;
			nRemainCount = nCounter;
		}
	}

	return nCounter;
/*
	int i, nTempData, nCounter = 0;
	for( i=1;i<m_nMaxLine;i++ )
	{
		ReadInt( i,nCol,nTempData );
		if( nTempData >= nMin && nTempData <= nMax )
		{
			pLines[nCounter] = i;
			nCounter++;
			if( nCounter == nCount )
				break;
		}
	}*/
	return nCounter;
}

int CExcelTable::FindLineEx( int nCol, int nData, int * pLines, int nCount )
{
	wchar_t szData[256];
#ifdef WIN32	
	swprintf( szData, L"%d", nData );
#else	
	swprintf( szData, 256, L"%d", nData );
#endif	
	return FindLineEx( nCol, szData, pLines, nCount );
}

int		CExcelTable::FindLineEx( int nCol, const char* szData, int * pLines, int nCount )
{
	if( !IsOpened( ) )
		return -1;

	AssertValidWritePtr( pLines, sizeof( int ) * nCount );

	wchar_t szwData[256];
	CharToWideChar( szData, szwData, 256 );
	return FindLineEx( nCol, szwData, pLines, nCount );
/*
	int nCounter = 0;
	Line_List * pLineList = NULL;

	int nIndex = m_LineMap[nCol].Find( szData );
	if( m_LineMap[nCol].IsValidIndex( nIndex ) )
		pLineList = m_LineMap[nCol][nIndex];

	nCounter = pLineList->Count( ) > nCount ? nCount : pLineList->Count( );
	memcpy( pLines, pLineList->Base( ), nCounter );

	return nCounter;*/
/*
	char szTemp[256] = { 0};
	int i, nCounter = 0;
	for( i=1;i<m_nMaxLine;i++ )
	{
		ReadStr( i, nCol, szTemp, 256 );
		if( Q_strcmp( szTemp, szData ) == 0 )
		{
			pLines[nCounter] = i;
			nCounter++;
			if( nCounter == nCount )
				break;
		}
	}
	return nCounter;*/
}

int		CExcelTable::FindLineEx( int nCol, const wchar_t* szData, int * pLines, int nCount )
{
	if( !IsOpened( ) )
		return -1;

	AssertValidWritePtr( pLines, sizeof( int ) * nCount );

	int nCounter = 0;
	Line_List * pLineList = NULL;

	int nIndex = m_LineMap[nCol].Find( szData );
	if( m_LineMap[nCol].IsValidIndex( nIndex ) )
		pLineList = m_LineMap[nCol][nIndex];

	if( pLineList )
	{
		nCounter = pLineList->Count( ) > nCount ? nCount : pLineList->Count( );
		memcpy( pLines, pLineList->Base( ), nCounter * sizeof( int ) );
	}

	return nCounter;
/*
	wchar_t szTemp[256] = { 0};
	int i, nCounter = 0;
	for( i=1;i<m_nMaxLine;i++ )
	{
		ReadStr( i, nCol, szTemp, 256 );
		if( wcscmp( szTemp, szData ) == 0 )
		{
			pLines[nCounter] = i;
			nCounter++;
			if( nCounter == nCount )
				break;
		}
	}
	return nCounter;*/
}

BOOL	CExcelTable::SaveSubWeight( LPCSTR szName, LPCSTR szPathID )
{
	if( IsOpened() || !szName || !szPathID )
	{
		return FALSE;
	}
	//if( FALSE == BackupFileByFileSystem( szName, szPathID ) )
	//	return FALSE;
	if( !Open( szName, szPathID ) )
		return FALSE;

	IXMLParser Workbook = m_Excel[L"xml/mso-application/Workbook"];
	//////////////////////// 存储用Workbook //////////////////////////////////
	IXMLParser c_Workbook( NULL, L"xml/mso-application/Workbook" );
	//////////////////////////////////////////////////////////////////////////
	if( wcscmp( Workbook.GetName( ), L"Workbook" ) == 0 )
	{
		int nWorkbookCount = Workbook.GetChildCount( );
		for( int j = 0; j < nWorkbookCount; j++ )
		{
			IXMLParser Worksheet = Workbook[j];
			if( wcscmp( Worksheet.GetName( ), L"Worksheet" ) == 0 )
			{
				wchar_t szValue[256] = { 0};
				Worksheet.GetAttribute( L"ss:Name", szValue, 256 );
				//////////////////// 存储用Worksheet /////////////////////////////
				IXMLParser c_Worksheet( &c_Workbook, L"Worksheet" );
				//////////////////////////////////////////////////////////////////
				c_Worksheet.SetAttribute( L"ss:Name", szValue );
				if( !_SubSheet( Worksheet, c_Worksheet ) )
				{
					c_Workbook.Release( );
					m_Excel.Release( );
					return FALSE;
				}
			}
		}
	}
	BOOL bIsOKDais = c_Workbook.Save( szName, szPathID );
	m_Excel.Release( );
	c_Workbook.Release();
	return bIsOKDais;
}

BOOL	CExcelTable::Open( LPCWSTR szName, LPCWSTR szPathID )
{
	return m_Excel.Load( szName, szPathID );
}

BOOL	CExcelTable::Open( LPCSTR szName, LPCSTR szPathID )
{
	wchar_t szwName[256] = { 0};
	wchar_t szwPath[256] = { 0};
	CharToWideChar( szName, szwName, 256 );
	CharToWideChar( szPathID, szwPath, 256 );
	return Open( szwName, szwPath );
}

BOOL	CExcelTable::ReadAllSheet( )
{
	IXMLParser Workbook = m_Excel[L"xml/mso-application/Workbook"];
	if( wcscmp( Workbook.GetName( ), L"Workbook" ) == 0 )
	{
		int nIndex = 0;
		int nWorkbookCount = Workbook.GetChildCount( );
		for( int j = 0; j < nWorkbookCount; j++ )
		{
			IXMLParser Worksheet = Workbook[j];
			if( wcscmp( Worksheet.GetName( ), L"Worksheet" ) == 0 )
			{
				wchar_t szValue[256] = { 0};
				Worksheet.GetAttribute( L"ss:Name", szValue, 256 );
				if( !_ReadSheet( Worksheet, nIndex ) )
				{
					Reset( );
					return FALSE;
				}
			}
		}
	}
	return TRUE;
}

void	CExcelTable::ReleaseXML( )
{
	m_Excel.Release( );
}

BOOL	CExcelTable::_SubSheet( IXMLParser & Worksheet, IXMLParser & c_Worksheet )
{
	int nWorksheetCount = Worksheet.GetChildCount( );
	for( int m = 0; m < nWorksheetCount; m++ )
	{
		IXMLParser Table = Worksheet[m];
		if( wcscmp( Table.GetName( ), L"Table" ) == 0 )
		{
			////////////////////// 存储用Table /////////////////////////////
			IXMLParser c_Table( &c_Worksheet, L"Table" );
			////////////////////////////////////////////////////////////////
			int nMaxCol = 0;
			int nMaxLine = 0;
			Table.GetAttribute( L"ss:ExpandedColumnCount", nMaxCol );
			Table.GetAttribute( L"ss:ExpandedRowCount", nMaxLine );
			if( nMaxCol <= 0 || nMaxLine <= 0 )
			{
				AssertMsg( FALSE, "表格为空！" );
				return FALSE;
			}
			c_Table.SetAttribute( L"ss:ExpandedColumnCount", nMaxCol );
			c_Table.SetAttribute( L"ss:ExpandedRowCount", nMaxLine );

			int nRowCount = Table.GetChildCount( );
			for( int k = 0; k < nRowCount; k++ )
			{
				// 取得一行数据
				IXMLParser Row = Table[k];
				if( wcscmp( Row.GetName( ), L"Row" ) == 0 )
				{
					////////////////////// 存储用Row ///////////////////////////////
					IXMLParser c_Row( &c_Table, L"Row" );
					////////////////////////////////////////////////////////////////
					int nTempRow = 0;
					Row.GetAttribute( L"ss:Index", nTempRow );
					if( nTempRow > 0 ) 
						c_Row.SetAttribute( L"ss:Index", nTempRow );

					int nCellCount = Row.GetChildCount( );
					for( int l = 0; l < nCellCount; l++ )
					{
						IXMLParser Cell = Row[l];
						////////////////////// 存储用Cell //////////////////////////
						IXMLParser c_Cell( &c_Row, L"Cell" );
						////////////////////////////////////////////////////////////
						int nTempCol = 0;
						Cell.GetAttribute( L"ss:Index", nTempCol );
						if( nTempCol > 0 ) 
							c_Cell.SetAttribute( L"ss:Index", nTempCol );

						int nDataCount = Cell.GetChildCount( );
						for( int m = 0; m < nDataCount; m++ )
						{
							IXMLParser Data = Cell[m];
							////////////////////// 存储用Cell //////////////////////
							IXMLParser c_Data( &c_Cell, L"Data" );
							////////////////////////////////////////////////////////
							LPCWSTR lpText = Data.GetText( );
							if( lpText )
								c_Data.SetText( lpText );
						}
					}
				}
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL	CExcelTable::AddText( IXMLParser & Cell, CUtlVector<wchar_t> ** pExcelTable, int nColIndex, int nBaseIndex, int nRowIndex )
{
	int nDataCount = Cell.GetChildCount( );
	for( int m = 0; m < nDataCount; m++ )
	{
		// 取得数据
		IXMLParser Data = Cell[m];
		if( wcscmp( Data.GetName( ), L"Data" ) != 0 && wcscmp( Data.GetName( ), L"ss:Data" ) != 0 )
			continue;
		LPCWSTR lpText = Data.GetText( );
		if( lpText )
		{
			Assert( pExcelTable[nRowIndex][nColIndex].Count( ) == 0 );
			pExcelTable[nRowIndex][nColIndex].Purge( );
			pExcelTable[nRowIndex][nColIndex].AddMultipleToTail( 
				wcslen( lpText ) + 1, lpText );

			Line_List * pLine = NULL;
			wchar_t * szData = pExcelTable[nRowIndex][nColIndex].Base( );
			int nDataIndex = m_LineMap[nColIndex].Find( szData );
			if( m_LineMap[nColIndex].IsValidIndex( nDataIndex ) )
				pLine = m_LineMap[nColIndex][nDataIndex];
			else
			{
				pLine = new Line_List;
				m_LineMap[nColIndex].Insert( szData, pLine );
			}
			pLine->AddToTail( nBaseIndex + nRowIndex );
		}
		else
		{
			AddText( Data, pExcelTable, nColIndex, nBaseIndex, nRowIndex );
		}
	}

	return TRUE;
}

BOOL	CExcelTable::_ReadSheet( IXMLParser & Worksheet, int & nBaseIndex )
{
	/**************************************************
	XML格式的Excel文件标识如下
	<Workbook>"
		<Worksheet ss:Name="Sheet1">
			<Table ss:ExpandedColumnCount="53" ss:ExpandedRowCount="56" ... >
				<Row ss:AutoFitHeight="0">
					<Cell><Data ss:Type="String">数据1</Data></Cell>
					<Cell ss:Index="10"><Data ss:Type="String">数据2</Data></Cell>
					<Cell ss:Index="20"><Data ss:Type="Number">20</Data></Cell>
				</Row>
				<Row ss:Index="16" ss:AutoFitHeight="0">
					<Cell><Data ss:Type="String">数据1</Data></Cell>
					<Cell ss:Index="10"><Data ss:Type="String">数据2</Data></Cell>
					<Cell ss:Index="20"><Data ss:Type="Number">20</Data></Cell>
				</Row>
			</Table>
		</Worksheet>
		<Worksheet ss:Name="Sheet2">
		...
		</Worksheet>
	</Workbook>
	**************************************************/

	// 取得工作表
	int nWorksheetCount = Worksheet.GetChildCount( );
	for( int m = 0; m < nWorksheetCount; m++ )
	{
		IXMLParser Table = Worksheet[m];
		if( wcscmp( Table.GetName( ), L"Table" ) == 0 )
		{
			int nMaxCol = 0;
			int nMaxLine = 0;
			Table.GetAttribute( L"ss:ExpandedColumnCount", nMaxCol );
			Table.GetAttribute( L"ss:ExpandedRowCount", nMaxLine );
			if( nMaxCol == 0 || nMaxLine == 0 )
			{
				AssertMsg( FALSE, "表格为空！" );
				return FALSE;
			}

			if( m_nMaxCol == 0 )
			{
				m_LineMap = new CUtlMap<const wchar_t*,Line_List*>[nMaxCol];
				for( int a = 0; a < nMaxCol; a++ )
				{
					SetDefLessFunc( m_LineMap[a] );
				}
			}
//			if( m_nMaxCol == 0 )
//				m_nMaxCol = nMaxCol;
//			else if( m_nMaxCol > nMaxCol )
//				m_nMaxCol = nMaxCol;
			if( m_nMaxCol < nMaxCol )
				m_nMaxCol = nMaxCol;

			int nRowIndex = -1;
			int nRowCount = Table.GetChildCount( );

			CUtlVector<wchar_t> ** pExcelTable = (CUtlVector<wchar_t>**)new LPTSTR[nMaxLine];
			memset( pExcelTable, 0, nMaxLine * sizeof( LPTSTR ) );

			for( int k = 0; k < nRowCount; k++ )
			{
				int nColIndex = -1;
				int nTempRow = 0;
				// 取得一行数据
				IXMLParser Row = Table[k];
				if( wcscmp( Row.GetName( ), L"Row" ) == 0 )
				{
					Row.GetAttribute( L"ss:Index", nTempRow );
					if( nTempRow == 0 ) 
						nRowIndex++;
					else 
						nRowIndex = nTempRow - 1;

					Assert( pExcelTable[nRowIndex] == NULL );
					pExcelTable[nRowIndex] = new CUtlVector<wchar_t>[nMaxCol];
					memset( pExcelTable[nRowIndex], 0, nMaxCol * sizeof( CUtlVector<wchar_t> ) );

					int nCellCount = Row.GetChildCount( );
					for( int l = 0; l < nCellCount; l++ )
					{
						int nTempCol = 0;
						// 取得元素数据
						IXMLParser Cell = Row[l];
						// 查看有无索引属性
						Cell.GetAttribute( L"ss:Index", nTempCol );
						if( nTempCol == 0 ) 
							nColIndex++;
						else 
							nColIndex = nTempCol - 1;
						Assert( nColIndex >= 0 && nColIndex < nMaxCol );

						AddText( Cell, pExcelTable, nColIndex, nBaseIndex, nRowIndex );
					}
				}
			}
			if( m_aExcelTable )
			{
				m_aExcelTable = (CUtlVector<wchar_t>**)Plat_Realloc( m_aExcelTable, ( nBaseIndex + nMaxLine ) * sizeof( LPSTR ) );
			}
			else
			{
				m_aExcelTable = (CUtlVector<wchar_t>**)Plat_Alloc( ( nBaseIndex + nMaxLine ) * sizeof( LPSTR ) );
			}
			memcpy( ( m_aExcelTable + nBaseIndex ), pExcelTable, sizeof( LPSTR ) * nMaxLine );
			nBaseIndex += nMaxLine;
			m_nMaxLine += nMaxLine;
			SAFE_DELETE_ARRAY( pExcelTable );
			return TRUE;
		}
	}
	return FALSE;
}

BOOL	CExcelTable::ReadSheet( LPCWSTR lpszSheet )
{
	char szSheet[256] = { 0};
	WideCharToChar( lpszSheet, szSheet, 256 );
	AssertMsg1( m_Excel.GetElement( ), "m_Excel.GetElement( ) == NULL %s", szSheet );

	Reset( );

	McbXMLElement * pWorkbook = m_Excel[L"xml/mso-application/Workbook"];
	if( !pWorkbook )
		pWorkbook = m_Excel[L"xml/Workbook"];
	if( !pWorkbook )
		return FALSE;

	IXMLParser Workbook = pWorkbook;
	if( wcscmp( Workbook.GetName( ), L"Workbook" ) == 0 )
	{
		int nWorkbookCount = Workbook.GetChildCount( );
		for( int j = 0; j < nWorkbookCount; j++ )
		{
			IXMLParser Worksheet = Workbook[j];
			if( wcscmp( Worksheet.GetName( ), L"Worksheet" ) == 0 )
			{
				wchar_t szValue[256] = { 0};
				Worksheet.GetAttribute( L"ss:Name", szValue, 256 );
				if( wcscmp( szValue, lpszSheet ) == 0 )
				{
					int nIndex = 0;
					return _ReadSheet( Worksheet, nIndex );
				}
			}
		}
	}
	return FALSE;
}

BOOL	CExcelTable::ReadSheet( LPCSTR lpszSheet )
{
	wchar_t szwSheet[256] = { 0};
	CharToWideChar( lpszSheet, szwSheet, 256 );

	return ReadSheet( szwSheet );
}

BOOL	CExcelTable::ReadExcelTable( LPCSTR szName, LPCSTR lpszSheet, LPCSTR szPathID )
{
	wchar_t szwName[256] = { 0};
	wchar_t szwSheet[256]= { 0};
	wchar_t szwPath[256]= { 0};
	CharToWideChar( szName, szwName, 256 );
	CharToWideChar( lpszSheet, szwSheet, 256 );
	CharToWideChar( szPathID, szwPath, 256 );
	return ReadExcelTable( szwName, szwSheet, szwPath );
}

BOOL	CExcelTable::ReadExcelTable( LPCWSTR szName, LPCWSTR lpszSheet, LPCWSTR szPathID )
{
	Assert( m_Excel.GetElement( ) == NULL );

	if( !Open( szName, szPathID ) )
	{
		Log("[Log] Not found %S in %S ...\n",szName,szPathID);
		return FALSE;
	}
	BOOL bRet = ReadSheet( lpszSheet );
//	m_Excel.Release( );
	return bRet;
}
