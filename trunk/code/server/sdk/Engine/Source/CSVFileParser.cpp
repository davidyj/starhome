#include "../stdafx.h"
#include "CSVFileParser.h"
#include "FileStdio.h"
//#include <string.h>

CCSVFileParser::CCSVFileParser()
{
	m_nLine= 0;
	m_nColumn= 0;
	m_lpXMLText = NULL;
	m_nLen = 0;
}

CCSVFileParser::~CCSVFileParser()
{
	Release();
}

void CCSVFileParser::Release()
{
	if(m_lpXMLText)
		Plat_Free( m_lpXMLText );
	m_lpXMLText = NULL;

	m_nLine= 0;
	m_nColumn= 0;

	m_ElementTable.Purge( );
}

BOOL CCSVFileParser::Load(LPCSTR lpName, LPCSTR lpPathID)
{
	CFileStdio File;
	if( File.Open( lpName, "rb", lpPathID ) )
	{
		// 读取文件内容
		m_nLen = File.GetLength( );
		m_lpXMLText= (LPSTR)Plat_Alloc( m_nLen );
		Assert( m_lpXMLText );
		if( !m_lpXMLText )
			return FALSE;

		File.Read( m_lpXMLText, m_nLen);

		Parser();

		File.Close( );
		return TRUE;
	}
	return FALSE;
}

// by tm
BOOL CCSVFileParser::LoadPlus( LPCSTR lpName , LPCSTR lpPathID )
{
	CFileStdio File;
	if( File.Open( lpName, "rb", lpPathID ) )
	{
		// 读取文件内容
		m_nLen = File.GetLength( );
		m_lpXMLText= (LPSTR)Plat_Alloc( m_nLen );
		Assert( m_lpXMLText );
		if( !m_lpXMLText )
			return FALSE;

		File.Read( m_lpXMLText, m_nLen);

		ParserPlus();

		File.Close( );
		return TRUE;
	}
	return FALSE;
}
// by tm
BOOL CCSVFileParser::ParserPlus()
{
	if(!m_lpXMLText)
		return FALSE;


	BOOL InsertFlag   = TRUE;  //是否插入的标记
	BOOL dFlag        = TRUE;

	BOOL InterSegMark = FALSE; // 插入seg标记
	segIndex          = 0;     // seg的数量

	LPSTR TempChar = m_lpXMLText;

	memset( &m_SegmentTable[0] , 0 , sizeof(SegmentPart) );

	while (TRUE)
	{
		if(m_lpXMLText + m_nLen <= TempChar)
			break;


		if(InsertFlag)
		{
			m_SegmentTable[segIndex].segTable.AddToTail(TempChar);
			InsertFlag = FALSE;
		}


		if(*TempChar == 0x09)       // '\t'
		{
			if(dFlag)
				m_SegmentTable[segIndex].column++;
			InsertFlag = TRUE;
			*TempChar ='\0';
		}
		else if(*TempChar == 0x0a)  // '\n'
		{
			dFlag = FALSE;
			InsertFlag = TRUE;
			m_SegmentTable[segIndex].line++;
			*TempChar = '\0';
		}
		else if(*TempChar == 0x24) // '$'
		{

			//向SegmentPart列表中添加新项
			//添加后所有变量恢复初始化值

			InsertFlag = TRUE ;
			dFlag      = TRUE ;
			InterSegMark = FALSE;

			segIndex++;
			memset( &m_SegmentTable[segIndex] , 0 , sizeof(SegmentPart) );

			*TempChar = '\0';
		}

		TempChar++;
	}
	return TRUE;
}

BOOL CCSVFileParser::Parser()
{
	if(!m_lpXMLText)
		return FALSE;

	BOOL InsertFlag =TRUE;//是否插入的标记
	BOOL dFlag = TRUE;
	m_ElementTable.EnsureCapacity( m_nLen );//不希望频繁GROW,不能是strlen
	LPSTR TempChar = m_lpXMLText;
	while (TRUE)
	{
		if(m_lpXMLText + m_nLen <= TempChar)
			break;

		if(InsertFlag)
		{
			m_ElementTable.AddToTail(TempChar);
			InsertFlag = FALSE;
		}

		if(*TempChar == 0x09)
		{
			if(dFlag)
				m_nColumn++;
			InsertFlag = TRUE;
			*TempChar ='\0';
		}
		else if(*TempChar == 0x0d)
		{
			if(dFlag)
				m_nColumn++;
			InsertFlag = TRUE;
			*TempChar ='\0';
		}
		else if(*TempChar == 0x0a)
		{
			dFlag = FALSE;
			InsertFlag = TRUE;
			m_nLine++;
			*TempChar = '\0';
		}

		TempChar++;
	}
	return TRUE;
}
