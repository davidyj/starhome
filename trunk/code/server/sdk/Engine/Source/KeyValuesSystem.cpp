//========= Copyright ?1996-2003, Valve LLC, All rights reserved. ============
//
// The copyright to the contents herein is the property of Valve, L.L.C.
// The contents may be used and/or copied only with the written permission of
// Valve, L.L.C., or in accordance with the terms and conditions stipulated in
// the agreement/contract under which the contents have been supplied.
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================
//by  2009.1.14 去掉 m_MemCS; 应该是后来加的.有什么用??

#include "../stdafx.h"
#include "IKeyValuesSystem.h"
#include "KeyValues.h"
#include "mempool.h"
#include "utlsymbol.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "memdbgon.h"

//-----------------------------------------------------------------------------
// Purpose: Central storage point for KeyValues memory and symbols
//-----------------------------------------------------------------------------
class CKeyValuesSystem : public IKeyValuesSystem
{
public:
	CKeyValuesSystem();
	~CKeyValuesSystem();

	// registers the size of the KeyValues in the specified instance
	// so it can build a properly sized memory pool for the KeyValues objects
	// the sizes will usually never differ but this is for versioning safety
	void RegisterSizeofKeyValues(int size);

	// allocates/frees a KeyValues object from the shared mempool
	void *AllocKeyValuesMemory(int size);
	void FreeKeyValuesMemory(void *pMem);

	// symbol table access (used for key names)
	HKeySymbol GetSymbolForString(const char *name);
	const char *GetStringForSymbol(HKeySymbol symbol);

private:
	CMemoryPool *m_pMemPool;
	CUtlSymbolTable m_SymbolTable;

	int m_iMaxKeyValuesSize;
};

//-----------------------------------------------------------------------------
// Singleton interface
//-----------------------------------------------------------------------------
ENGINE_GLOBAL IKeyValuesSystem *KeyValuesSystem()
{
	static CKeyValuesSystem s_KeyValuesSystem;
	return &s_KeyValuesSystem;
}

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CKeyValuesSystem::CKeyValuesSystem() : m_SymbolTable(0, 1024, true)
{
	m_pMemPool = NULL;
	m_iMaxKeyValuesSize = sizeof(KeyValues);
}

//-----------------------------------------------------------------------------
// Purpose: Destructor
//-----------------------------------------------------------------------------
CKeyValuesSystem::~CKeyValuesSystem()
{
	delete m_pMemPool;
}

//-----------------------------------------------------------------------------
// Purpose: registers the size of the KeyValues in the specified instance
//			so it can build a properly sized memory pool for the KeyValues objects
//			the sizes will usually never differ but this is for versioning safety
//-----------------------------------------------------------------------------
void CKeyValuesSystem::RegisterSizeofKeyValues(int size)
{
	if (size > m_iMaxKeyValuesSize)
	{
		m_iMaxKeyValuesSize = size;
	}
}

//-----------------------------------------------------------------------------
// Purpose: allocates a KeyValues object from the shared mempool
//-----------------------------------------------------------------------------
void *CKeyValuesSystem::AllocKeyValuesMemory(int size)
{
	// allocate, if we don't have one yet
	if (!m_pMemPool)
	{
		m_pMemPool = new CMemoryPool(m_iMaxKeyValuesSize, 1024);
	}

	void * pRet = m_pMemPool->Alloc(size);
	return pRet;
}

//-----------------------------------------------------------------------------
// Purpose: frees a KeyValues object from the shared mempool
//-----------------------------------------------------------------------------
void CKeyValuesSystem::FreeKeyValuesMemory(void *pMem)
{
	m_pMemPool->Free(pMem);
}

//-----------------------------------------------------------------------------
// Purpose: symbol table access (used for key names)
//-----------------------------------------------------------------------------
HKeySymbol CKeyValuesSystem::GetSymbolForString(const char *name)
{
	return m_SymbolTable.AddString(name);
}

//-----------------------------------------------------------------------------
// Purpose: symbol table access
//-----------------------------------------------------------------------------
const char *CKeyValuesSystem::GetStringForSymbol(HKeySymbol symbol)
{
	return m_SymbolTable.String(symbol);
}


// EXPOSE_SINGLE_INTERFACE(CKeyValuesSystem, IKeyValuesSystem, KEYVALUES_INTERFACE_VERSION);

