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

	BOOL	CheckText(const char* szString);		//ÎÄ±¾ÄÚÈÝÆÁ±Î¿â
	BOOL	CheckName(const char* szString);		//Ãû×ÖÆÁ±Î¿â
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


