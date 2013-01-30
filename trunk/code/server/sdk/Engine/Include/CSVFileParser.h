// ��ȡCSV��ʽ���ļ�
//				By David 2008-9-25
#pragma once
#include "BaseObj.h"
#include "dbg.h"
#include "utlvector.h"


#define  SegmentMax   2048

class ENGINE_CLASS CCSVFileParser : public IBaseObj
{
public:
	CCSVFileParser();
	~CCSVFileParser();

public:
	// -��ȡ�ļ�
	BOOL Load( LPCSTR lpName, LPCSTR lpPathID );
	BOOL LoadPlus( LPCSTR lpName , LPCSTR  lpPathID );  //by  tm

	// -�ͷ���Դ
	void Release();
	
	inline UINT	Line(){return m_nLine;}
	inline UINT	Column(){return m_nColumn;}

	inline BOOL GetAttribute(int nLine,int nColum,int &nData);
	inline BOOL GetAttribute(int nLine,int nColum,int64 &iData);
	inline BOOL GetAttribute(int nLine,int nColum,LPSTR szData);

protected:
	BOOL	Parser();
	BOOL    ParserPlus();  // by tm


protected:
	UINT	m_nLine;				// ��
	UINT	m_nColumn;				// ��
	UINT	m_nLen;					// �ļ��ĳ���
	LPSTR	m_lpXMLText;			// �ļ�����ʵ�ڴ�
	CUtlVector<LPSTR>	m_ElementTable;	//����ڵ��Vector

public:
	// by tm
	struct SegmentPart 
	{
		UINT line;
		UINT column;
		CUtlVector<LPSTR> segTable;
		
		// get int data 
		BOOL GetAttribute(int nLine,int nColum,int& nData)
		{	
			int nIndex = (nLine*column)+nColum+nLine;
			if(nIndex<segTable.Count())
			{			
				sscanf(segTable.Element(nIndex),"%d",&nData);		
				return TRUE;
			}
			return FALSE;
		}

		BOOL GetAttribute(int nLine,int nColum,LPSTR szData)
		{
			int nIndex = (nLine*column)+nColum+nLine;
			if(nIndex<segTable.Count())
			{			
				sscanf(segTable.Element(nIndex),"%s",szData);
				return TRUE;
			}
			return FALSE;
		}

	};
	int          segIndex;
	SegmentPart  m_SegmentTable[SegmentMax]; //����ÿ��seg�ı��
};


inline BOOL CCSVFileParser::GetAttribute(int nLine,int nColum,int& nData)
{	
	int nIndex = (nLine*m_nColumn)+nColum+nLine;
	if(nIndex<m_ElementTable.Count())
	{			
		sscanf(m_ElementTable.Element(nIndex),"%d",&nData);		
		return TRUE;
	} 
	return FALSE;
}

inline BOOL CCSVFileParser::GetAttribute(int nLine,int nColum,int64 &iData)
{
	int nIndex = (nLine*m_nColumn)+nColum+nLine;
	if(nIndex<m_ElementTable.Count())
	{			
		sscanf(m_ElementTable.Element(nIndex), INT64_FMT, &iData);		
		
		return TRUE;
	}
	return FALSE;
}

inline BOOL CCSVFileParser::GetAttribute(int nLine,int nColum,LPSTR szData)
{
	int nIndex = (nLine*m_nColumn)+nColum+nLine;
	if(nIndex<m_ElementTable.Count())
	{			
		strcpy(szData, m_ElementTable.Element(nIndex));		
		return TRUE;
	}
	return FALSE;
}
