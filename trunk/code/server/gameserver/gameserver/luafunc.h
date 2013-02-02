#ifndef LUA_FUNC_H
#define LUA_FUNC_H


#ifdef __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#ifdef __cplusplus
}
#endif

#ifdef LUA_FUNCTION_IMPLEMENTATION
const luaL_Reg user_funcs[] = 
{	
	{"setbuildint",					lua_setbuildint		},	
	{ NULL, NULL},                                                   
};
#else
extern const luaL_Reg user_funcs[];
#endif

#endif
