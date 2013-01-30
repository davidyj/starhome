#include "stdafx.h"
#include "chunkmgr.h"

GAMENETCOMMON_GLOBAL	int		g_GetChunkAllocIndex()
{
	return ChunkMgr().AllocIndex();
}
//////////////////////////////////////////////////////////////////////////
//
CChunkMgr& ChunkMgr()
{
	static CChunkMgr mgr;
	return mgr;
}