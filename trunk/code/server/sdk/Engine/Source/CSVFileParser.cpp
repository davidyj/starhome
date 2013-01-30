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
		// ��ȡ�ļ�����
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
		// ��ȡ�ļ�����
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


	BOOL InsertFlag   = TRUE;  //�Ƿ����ı��
	BOOL dFlag        = TRUE;

	BOOL InterSegMark = FALSE; // ����seg���
	segIndex          = 0;     // seg������

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

			//��SegmentPart�б����������
			//��Ӻ����б����ָ���ʼ��ֵ

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

	BOOL InsertFlag =TRUE;//�Ƿ����ı��
	BOOL dFlag = TRUE;
	m_ElementTable.EnsureCapacity( m_nLen );//��ϣ��Ƶ��GROW,������strlen
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
