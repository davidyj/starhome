#pragma once

#include "CommDef.h"
#include "EngineDefine.h"
#include "utlvector.h"
#include "utlmap.h"
#include "XMLParser.h"

//����Excel��ά��
class ENGINE_CLASS CExcelTable
{
public:
	CExcelTable( );
	~CExcelTable( );

	CExcelTable( IXMLParser * pExcel ) : m_Excel( pExcel, NULL ){ };

	// ��ȡ�ļ������ڴ���Excel�ļ�ֻ��һҳ�����
	BOOL	ReadExcelTable( LPCSTR szName, LPCSTR lpszSheet, LPCSTR szPathID );
	BOOL	ReadExcelTable( LPCWSTR szName, LPCWSTR lpszSheet, LPCWSTR szPathID );

	// ��ȡ�ļ�����ҳ����
	BOOL	Open( LPCWSTR szName, LPCWSTR szPathID );
	BOOL	Open( LPCSTR szName, LPCSTR szPathID );
	BOOL	OpenFromOther( IXMLParser * pExcel ){ return m_Excel.Build( pExcel, NULL ); }
	BOOL	ReadSheet( LPCSTR lpszSheet );
	BOOL	ReadSheet( LPCWSTR lpszSheet );
	BOOL	ReadAllSheet( );
	void	ReleaseXML( );

	// �洢���ʲ��ɴ��ļ���Ϊ��ֹ��������Ѿ�Open���Ĳ����Դ�
	BOOL	SaveSubWeight( LPCSTR szName, LPCSTR szPathID );

	void	Reset( );
	void	Close( );
	inline BOOL IsOpened( ){ return m_Excel.GetElement( ) != NULL || m_aExcelTable != NULL; }

	//��û����д nData = EXCEL_INVALID,output = "";
	// nSize	:	�õ��ĺ�׺����󳤶ȣ����С������ַ������ڶ�������������ʵ���ȣ���������������
	void	ReadStr( int nLine, int nCol, char* output, int nSize );
	void	ReadStr( int nLine, int nCol, wchar_t* output, int nSize );
	void	ReadInt( int nLine, int nCol, int &nData );
	void	ReadInt( int nLine, int nCol, WORD &nData );
	void	ReadFloat( int nLine, int nCol, float &fData );
	void	ReadByte( int nLine, int nCol, BYTE &bData );

	int		FindLine( int nCol, int nData );
	int		FindLine( int nCol, const char* szData );
	int		FindLine( int nCol, const wchar_t* szData );

	int		FindLineEx( int nCol, int nMin, int nMax, int * pLines, int nCount );
	int		FindLineEx( int nCol, int nData, int * pLines, int nCount );
	int		FindLineEx( int nCol, const char* szData, int * pLines, int nCount );
	int		FindLineEx( int nCol, const wchar_t* szData, int * pLines, int nCount );

	int		GetMaxLine( ){ return m_nMaxLine; }
	int		GetMaxCol( ){ return m_nMaxCol; }

	IXMLParser & GetExcelXML( ){ return m_Excel; }

private:
	BOOL	_ReadSheet( IXMLParser & Worksheet, int & nBaseIndex );
	void	SubReadTable( LPCTSTR lpBuffer );
	// Worksheet �Ƿʵģ����ʺ�浽 c_Worksheet ��
	BOOL	_SubSheet( IXMLParser & Worksheet, IXMLParser & c_Worksheet );

	BOOL	AddText( IXMLParser & Cell, CUtlVector<wchar_t> ** pExcelTable, int nColIndex, int nBaseIndex, int nRowIndex );
private:
	int				m_nMaxLine;
	int				m_nMaxCol;
	CUtlVector<wchar_t>**	m_aExcelTable;
	typedef CUtlVector<int> Line_List;
	CUtlMap<const wchar_t*,Line_List*>	*m_LineMap;
	IXMLParser		m_Excel;
};
