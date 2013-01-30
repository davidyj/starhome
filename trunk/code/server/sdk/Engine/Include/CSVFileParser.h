// 读取CSV格式的文件
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
	// -读取文件
	BOOL Load( LPCSTR lpName, LPCSTR lpPathID );
	BOOL LoadPlus( LPCSTR lpName , LPCSTR  lpPathID );  //by  tm

	// -释放资源
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
	UINT	m_nLine;				// 行
	UINT	m_nColumn;				// 列
	UINT	m_nLen;					// 文件的长度
	LPSTR	m_lpXMLText;			// 文件的真实内存
	CUtlVector<LPSTR>	m_ElementTable;	//保存节点的Vector

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
	SegmentPart  m_SegmentTable[SegmentMax]; //保存每个seg的标记
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
