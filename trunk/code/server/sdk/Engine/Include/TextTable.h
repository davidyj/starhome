#pragma once

#include "EngineDefine.h"
#include "utlmap.h"

#pragma warning (disable:4251) // “identifier”: 类“type”需要有 dll 接口由类“type2”的客户端使用

class ENGINE_CLASS CTextTable
{
public:
	CTextTable(void);
	~CTextTable(void);

	BOOL Open( const wchar_t * szName, const wchar_t * szTable, const wchar_t * szPath );
	BOOL Open( const wchar_t * szName, const wchar_t * szPath );
	void Close( );
	wchar_t * GetText( int nID );
	int GetIDByText( wchar_t * szText );

private:
	CUtlMap<int,wchar_t*,int> m_TextMapTable;
};

ENGINE_GLOBAL const char * GetLanguagePath( );
