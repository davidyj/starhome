#include <stdio.h>
#include <windows.h>
extern   "C"   
{   
#include   "lua.h"   
#include   "lualib.h"   
#include   "lauxlib.h"   
}

int main(int argc, char *argv[])
{
	lua_State *state = lua_open();//����һ��Lua״̬����ʵ��	
	if (!state)	{
		printf("failed to open state\n");
	}

	printf("Hello\n");
	SleepEx(INFINITE, FALSE);
}