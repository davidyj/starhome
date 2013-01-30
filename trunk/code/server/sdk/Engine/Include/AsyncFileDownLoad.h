#pragma once
#if 0
#include "enginedefine.h"
#include "sfile2.h"
#include "slock.h"

ENGINE_GLOBAL void BackDownloadThreadInitial( );
ENGINE_GLOBAL void BackDownloadThreadDestroy( );
ENGINE_GLOBAL void TestEvent();

BOOL InitReadList();
void create_paths(const char* szNewPath);
BOOL fexist( char* fileName );
#endif