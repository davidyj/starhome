// gameserver.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "LuaEngine_Svr.h"
#include "PathFunc.h"

const int PATHSIZE = 512;
char g_szExePath[PATHSIZE] = {0};

int _tmain(int argc, _TCHAR* argv[])
{

	Plat_SetSimpleLogName("gameserver.log");

	GetExePath( g_szExePath, PATHSIZE );
	Log("work path %s",g_szExePath);

	//��ʼ��lua����
	if( !GetLuaEngine_Svr().Init(10240) )
	{
		Log("��ʼ��lua����ʧ�ܣ�\n");
		return FALSE;
	}

	//��ʼ����������
	char g_szFilePath[256]= { 0 };
	sprintf(g_szFilePath,"%sconfig.lua", g_szExePath);
	if( !GetLuaEngine_Svr().LoadLuaFile( g_szFilePath ) )
	{
		Log("����SvrConfig.luaʧ�ܣ�\n");
		return FALSE;
	}

	return 0;
}

