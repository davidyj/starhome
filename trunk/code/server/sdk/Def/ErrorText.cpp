#include "StdAfx.h"
#include "ErrorText.h"
#include "CSVFileParser.h"
#include "strtools.h"

CErrorText& ErrorText()
{
	static CErrorText text;
	return text;
}
//////////////////////////////////////////////////////////////////////////
//
CErrorText::CErrorText()
{
}

CErrorText::~CErrorText()
{
}

BOOL CErrorText::InitFile()
{
	//加载errortext.csv
	CCSVFileParser TextFile;
	if( !TextFile.Load("errortext.csv","DATA_PATH") )
	{
		Log("加载errortext.csv失败！");
		return FALSE;
	}
	for(UINT i = 0;i<TextFile.Line();i++)
	{
		char szString[50]={0};
		TextFile.GetAttribute(i,1,szString);

		AddText(szString, m_TextVector);
	}
	TextFile.Release();

	//加载nametext.csv
	CCSVFileParser NameFile;
	if( !NameFile.Load("nametext.csv","DATA_PATH") )
	{
		Log("加载nametext.csv失败！");
		return FALSE;
	}
	for(UINT i = 0;i<NameFile.Line();i++)
	{
		char szString[50]={0};
		NameFile.GetAttribute(i,1,szString);

		AddText(szString, m_NameVector);
	}
	NameFile.Release();

	return TRUE;
}

void CErrorText::Release()
{

}

BOOL CErrorText::AddText(char* szString, CUtlVector<CUtlSymbol>& vec)
{
	CUtlSymbol symbol(szString);// = m_SymbolTable.AddString(szString);

	int index = vec.Find(symbol);
	if(vec.IsValidIndex(index))
	{
		DEBUG_Log(" +-ErrorText添加出错:%s\n", szString);
		return FALSE;
	}
	vec.AddToTail(symbol);
	return TRUE;
}

int CErrorText::_CheckText(const wchar_t* szString, int& idest)
{
	wchar_t cText[2048];
	wcscpy(cText,szString);
	for(int i=0; i<m_TextVector.Count(); i++)
	{
		wchar_t wText[128];
		//CUtlSymbol symbol = m_TextVector.Element(i);
		//const char* szp = m_SymbolTable.String(symbol);
		const char* szp = m_TextVector.Element(i).String();
		CharToWideChar(szp,wText,128);
		wchar_t* temp;
		if ((temp = wcsstr(cText,wText)))
		{
			idest = temp - cText;
			return wcslen(wText);
		}
	}
	return 0;
}

BOOL CErrorText::CheckText(const char* szString)
{
	wchar_t cText[2048];
	CharToWideChar(szString,cText,2048);
	for(int i=0; i<m_TextVector.Count(); i++)
	{
		wchar_t wText[128];
		//CUtlSymbol symbol = m_TextVector.Element(i);
		//const char* szp = m_SymbolTable.String(symbol);
		const char* szp = m_TextVector.Element(i).String();
		CharToWideChar(szp,wText,128);
		//wchar_t* temp;
		if (/*temp = */wcsstr(cText,wText))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CErrorText::CheckName(const char* szString)
{
	if(!szString)
		return FALSE;
	char* szDestination= NULL;
	szDestination = (char*)malloc(strlen(szString)+1);
	strcpy(szDestination,szString);
	_strlwr(szDestination);
	wchar_t cText[2048];
	CharToWideChar(szDestination,cText,2048);

	for(int i=0; i<m_NameVector.Count(); i++)
	{
		wchar_t wText[128];
		const char* szp = m_NameVector.Element(i).String();
		char* szSource  = NULL;
		szSource = (char*)malloc(strlen(szp)+1);
		strcpy(szSource,szp);
		_strlwr(szSource);
		CharToWideChar(szSource,wText,128);
		if (wcsstr(cText,wText))
		{
			free(szSource);
			return FALSE;
		}
		free(szSource);
	}
	free(szDestination);
	return CheckSpace(szString);
}

BOOL CErrorText::CheckSpace(const char* szString)
{
	if(!szString)
		return FALSE;
	while(*szString != '\0')
	{
		if (*szString == 32)
			return FALSE;
		if (*szString == -95  && *(szString+1) == -95 )
			return FALSE;
		szString = szString + 1;
	}
	return TRUE;
}

void CErrorText::ShieldText(const wchar_t* text, wchar_t* ctext)
{
	int len, idest=0;
	//WideCharToChar(text, ctext, 2048);
	wcscpy(ctext, text);
	while((len = _CheckText(ctext, idest)))
	{
		for (int i=0; i<len; ++i)
		{
			ctext[idest + i] = '*';
		}
	}

	return;
}
