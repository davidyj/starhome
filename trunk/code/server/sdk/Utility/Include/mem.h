#pragma once

#include <stddef.h>
#include "platform.h"

//-----------------------------------------------------------------------------
// DLL-exported methods for particular kinds of memory
//-----------------------------------------------------------------------------
void *MemAllocScratch( int nMemSize );
void MemFreeScratch();
void MemReleaseScratch( );//by jinsheng fix memmory leak for studio engine
