#pragma	   once
#include "utlvector.h"
#include "utlsymbol.h"

class CErrorText
{
public:
	CErrorText();
	~CErrorText();

	BOOL	InitFile();
	void	Release();

	BOOL	CheckText(const char* szString);		//�ı��������ο�
	BOOL	CheckName(const char* szString);		//�������ο�
	BOOL	CheckSpace(const char* szString);
	void	ShieldText(const wchar_t* text, wchar_t* wtext);

protected:
	BOOL	AddText(char* szString, CUtlVector<CUtlSymbol>& vec);

	int		_CheckText(const wchar_t* szString, int& idest);

protected:
	CUtlVector<CUtlSymbol>	m_TextVector;
	CUtlVector<CUtlSymbol>	m_NameVector;
//	CUtlSymbolTable			m_SymbolTable;

};

CErrorText& ErrorText();


