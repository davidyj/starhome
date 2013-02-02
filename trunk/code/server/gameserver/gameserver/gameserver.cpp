// gameserver.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "LuaEngine_Svr.h"

const int PATHSIZE = 512;
char g_szExePath[PATHSIZE] = {0};

int _tmain(int argc, _TCHAR* argv[])
{

	GetExePath( g_szExePath, PATHSIZE );

	//初始化lua引擎
	if( !GetLuaEngine_Svr().Init(10240) )
	{
		Log("初始化lua引擎失败！\n");
		return FALSE;
	}

	//初始化启动参数
	char g_szFilePath[256]= { 0 };
	sprintf(g_szFilePath,"%sconfig.lua", g_szExePath);
	if( !GetLuaEngine_Svr().LoadLuaFile( g_szFilePath ) )
	{
		Log("加载SvrConfig.lua失败！\n");
		return FALSE;
	}

	return 0;
}

