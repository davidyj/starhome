//========= Copyright ?1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================
#pragma once

#include "EngineDefine.h"

// handle to a KeyValues key name symbol
typedef int HKeySymbol;
#define INVALID_KEY_SYMBOL (-1)

//-----------------------------------------------------------------------------
// Purpose: Interface to shared data repository for KeyValues (included in vgui_controls.lib)
//			allows for central data storage point of KeyValues symbol table
//-----------------------------------------------------------------------------
class IKeyValuesSystem
{
public:
	// registers the size of the KeyValues in the specified instance
	// so it can build a properly sized memory pool for the KeyValues objects
	// the sizes will usually never differ but this is for versioning safety
	virtual void RegisterSizeofKeyValues(int size) = 0;

	// allocates/frees a KeyValues object from the shared mempool
	virtual void *AllocKeyValuesMemory(int size) = 0;
	virtual void FreeKeyValuesMemory(void *pMem) = 0;

	// symbol table access (used for key names)
	virtual HKeySymbol GetSymbolForString(const char *name) = 0;
	virtual const char *GetStringForSymbol(HKeySymbol symbol) = 0;
};

ENGINE_GLOBAL IKeyValuesSystem * KeyValuesSystem();

// #define KEYVALUESSYSTEM_INTERFACE_VERSION "KeyValuesSystem001"
