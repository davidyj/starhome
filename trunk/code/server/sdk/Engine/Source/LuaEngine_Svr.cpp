// CLuaEngine.cpp : 定义 DLL 应用程序的入口点。
//

//#include "StdAfx.h"
#include "LuaEngine_Svr.h"
#include "BaseFileSystem.h"
extern   "C"   
{   
#include   "lua.h"   
#include   "lualib.h"   
#include   "lauxlib.h"   
#include   "lstate.h"   
}

#define DEBUG_STROUT Log

//如果选择所有模块，OpenLuaLibs相当于luaL_openlibs
static const luaL_Reg mylualibs[] = 
{
  {"", luaopen_base},  
  {LUA_LOADLIBNAME, luaopen_package},
  {LUA_TABLIBNAME, luaopen_table},
  {LUA_IOLIBNAME, luaopen_io},
  {LUA_OSLIBNAME, luaopen_os},
  {LUA_STRLIBNAME, luaopen_string},
  //{LUA_MATHLIBNAME, luaopen_math}, //+,-,*,/,%运算不需要数学库
#ifdef _DEBUG
  {LUA_DBLIBNAME, luaopen_debug},
#endif
  {NULL, NULL}
};

void OpenLuaLibs (lua_State *L) 
{
	const luaL_Reg *lib = mylualibs;
	for (; lib->func; lib++) {
		lua_pushcfunction(L, lib->func);
		lua_pushstring(L, lib->name);
		lua_call(L, 1, 0);
	}
}

static int Lua_print(lua_State *L)
{

	int n = lua_gettop(L);  //传进来的参数个数
	int i;
//	const char* str = lua_tostring(L,-1);
	lua_getglobal(L, "tostring"); //将脚本变量tostring（脚本库函数）压栈
	for (i=1; i<=n; i++) {
		const char *s;
		lua_pushvalue(L, -1);  //将栈顶的变量，即为tostring 函数再次压栈
		lua_pushvalue(L, i);   //将要打印的值，也就是脚本中调用时传入的参数压栈
		lua_call(L, 1, 1);     //调用脚本函数tostring
		s = lua_tostring(L, -1);  //将返回值从栈中读出
		if (s == NULL)
			return luaL_error(L, "`tostring' must return a string to `print'");
		if (i>1) DEBUG_STROUT("\t");
		DEBUG_STROUT(s);
		lua_pop(L, 1);  //弹出返回值
	}
	DEBUG_STROUT("\n");
	return 0;
}

void Lua_Trace(lua_State *L, lua_Debug *debug_msg)
{
	char tmp[6]={0};
	char * what = tmp;
	strcpy(what,"nl\0\0");	
	switch(debug_msg->event)
	{
	case LUA_HOOKCALL:
		what = strcat(what,"uS");
		DEBUG_STROUT("LUA_HOOKCALL  ");
		break;
	case LUA_HOOKRET:
		what = strcat(what,"u");
		DEBUG_STROUT("LUA_HOOKRETURN  ");
		break;
	case LUA_HOOKTAILRET:
		what = strcat(what,"uS");
		DEBUG_STROUT("LUA_HOOKTAILRETURN  ");
		break;
	case LUA_HOOKLINE:
		what = strcat(what,"uS");
		DEBUG_STROUT("LUA_HOOKLINE  ");
		break;
	case LUA_HOOKCOUNT:
		break;
	default:
		break;
	}
	//printf("%s",what);
	if(debug_msg->currentline >0 )	
		printf("当前运行：第 %d 行，",debug_msg->currentline);

	if(lua_getinfo(L, what, debug_msg))
	{
		//printf("开始于%d行，结束于%d行，使用外部变量%d个", debug_msg->linedefined,debug_msg->lastlinedefined,debug_msg->nups);
		if(debug_msg->short_src != NULL) printf(debug_msg->short_src);
		printf("   ");
		if(debug_msg->what != NULL) printf(debug_msg->what);
		printf("   ");
		if(debug_msg->source != NULL) printf(debug_msg->source);
		printf("   ");
		if(debug_msg->name != NULL) printf(debug_msg->name);
		if(debug_msg->namewhat != NULL)printf(debug_msg->namewhat);
		printf("\n");
	}
	printf("\n");
}

// write to server.out file
// write by  david 2012-5-24
static int Lua_Note(lua_State *L)
{
	FileHandle_t f = NULL;
	f = FileSystem().Open("d:\\server.out","a");
	if(f == NULL)
		return 0;

	int n = lua_gettop(L);  //传进来的参数个数
	int i;
	lua_getglobal(L, "tostring"); //将脚本变量tostring（脚本库函数）压栈
	for (i=1; i<=n; i++) {
		const char *s;
		lua_pushvalue(L, -1);  //将栈顶的变量，即为tostring 函数再次压栈
		lua_pushvalue(L, i);   //将要打印的值，也就是脚本中调用时传入的参数压栈
		lua_call(L, 1, 1);     //调用脚本函数tostring
		s = lua_tostring(L, -1);  //将返回值从栈中读出
		if (s == NULL){
			return luaL_error(L, "`tostring' must return a string to `print'");			
		}
		if (i>1) 
			FileSystem().Write("\t",1,f);
		FileSystem().Write(s,strlen(s),f);
		lua_pop(L, 1);  //弹出返回值
	}
	FileSystem().Write("\n",1,f);
	FileSystem().Close(f);
	return 0;
}


CLuaEngine_Svr::CLuaEngine_Svr(void)
{
	m_pLuaState = NULL;
	//CreateLuaState();
}

CLuaEngine_Svr::~CLuaEngine_Svr(void)
{
}

BOOL CLuaEngine_Svr::Init(int stacksize)
{
	return CreateLuaState(stacksize);
}

void CLuaEngine_Svr::Release(void)
{
	if(m_pLuaState != NULL)
	{
		lua_close(m_pLuaState);
	}
	delete this;
}

lua_State *	CLuaEngine_Svr::GetLuaState(void)
{
	return m_pLuaState;
}

LPCSTR CLuaEngine_Svr::GetLastError(void)
{
	return lua_tostring(m_pLuaState, -1);
}

BOOL CLuaEngine_Svr::CreateLuaState(int stacksize)
{
	if(m_pLuaState!=NULL)
		return TRUE;
	
	m_pLuaState = lua_open();	//创建一个Lua状态机的实例	
	if(m_pLuaState==NULL)
	{
		DEBUG_STROUT("Lua状态机创建失败\n");
		return FALSE;
	}
#ifdef USE_STANDARAD_LUA_LIBS	
	luaL_openlibs(m_pLuaState);           //加载Lua的基本库
#else
	OpenLuaLibs(m_pLuaState);
#endif
	
	if( !lua_checkstack(m_pLuaState, stacksize) )     //增加Lua的堆栈大小，防止因为堆栈过小而死机
	{
		DEBUG_STROUT("设置LuaState大小失败(stacksize=%d, top=%d, base=%d)\n", stacksize, m_pLuaState->top, m_pLuaState->base);
		return FALSE;
	}

//#ifdef _DEBUG
//	lua_sethook( m_pLuaState, Lua_Trace, LUA_MASKLINE , 0);
//#endif

	lua_register( m_pLuaState,"print",Lua_print ); //注册常用函数
	lua_register( m_pLuaState,"note",Lua_Note);
	
	return TRUE;
}

BOOL CLuaEngine_Svr::LoadLuaFile(LPCSTR fileName)
{
	int top = lua_gettop(m_pLuaState);			
	if( !luaL_loadfile(m_pLuaState, fileName) )
	{
		if( !lua_pcall(m_pLuaState, 0, 0, 0) )
		{
			lua_settop(m_pLuaState, top);			
			return TRUE;
		}
	}		
	DEBUG_STROUT("[CLuaEngine] 载入%s文件失败，失败原因：%s", fileName, GetLastError());	
	lua_settop(m_pLuaState, top);		
	return FALSE;
}

BOOL CLuaEngine_Svr::LoadLuaFile(LPCSTR szName, LPCSTR szPathID)
{
	if( !szName||! strlen( szName )) 
	{
		return false;
	}
	char szFileName[512] = {0};
	strcat( szFileName,FileSystem().GetSearchPath(szPathID));
#ifdef WIN32	
	strcat(szFileName,"\\");
#else	
	char *p = (char *)(szName + strlen(szName) -1);
	while (p >= szName){
		if ((*p) == '\\')
			*p = '/';
		p--;
	}	
	strcat(szFileName,"/");
#endif	
	
	strcat( szFileName,szName );
	
	int top = lua_gettop(m_pLuaState);			
	if( !luaL_loadfile(m_pLuaState, szFileName) )
	{
		if( !lua_pcall(m_pLuaState, 0, 0, 0) )
		{
			lua_settop(m_pLuaState, top);			
			return true;
		}
	}		
	DEBUG_STROUT("[CLuaEngine] 载入%s文件失败，失败原因：%s", szFileName, GetLastError());	
	lua_settop(m_pLuaState, top);		

	return false;
}

BOOL CLuaEngine_Svr::RunMemoryLua(LPCSTR pLuaData, int nDataLen)
{
	if(pLuaData == NULL || nDataLen <= 0)
	{
		return false;
	}	
	int top = lua_gettop(m_pLuaState);
	if( !luaL_loadbuffer(m_pLuaState, pLuaData, nDataLen, pLuaData) )
	{
		if( !lua_pcall(m_pLuaState, 0, 0, 0) )
		{
			lua_settop(m_pLuaState, top);
			return true;
		}
	}

	DEBUG_STROUT("[CLuaEngine] 执行内存lua失败，失败原因：%s", GetLastError());
	lua_settop(m_pLuaState, top);	
	return false;
}

BOOL CLuaEngine_Svr::RunLuaFunction(LPCSTR szFunName,  LPCSTR szTableName, LPCSTR szSubTableName, 
					LuaParam * pInParam, int nInNum, LuaParam * pOutParam, int nOutNum)
{
	int top = lua_gettop(m_pLuaState);
	if(szTableName==NULL)
	{
		lua_getglobal(m_pLuaState, szFunName);
	}
	else if(szSubTableName==NULL)
	{
		lua_getglobal(m_pLuaState, szTableName);
		if(lua_istable(m_pLuaState, -1))
		{
			lua_getfield(m_pLuaState,-1,szFunName);
		}
	}
	else
	{
		lua_getglobal(m_pLuaState, szTableName);
		if(lua_istable(m_pLuaState, -1))
		{
			lua_getfield(m_pLuaState, -1,szSubTableName);
			if(lua_istable(m_pLuaState, -1))
			{
				lua_getfield(m_pLuaState,-1,szFunName);
			}
		}

	}
	
	if(!lua_isfunction(m_pLuaState, -1))
	{
//		DEBUG_STROUT("调用%s函数失败，找不到此函数！", szFunName);
		lua_settop(m_pLuaState, top);
		return false;
	}
	for(int i = 0; i < nInNum; i++)
	{
		switch(pInParam[i].Type())
		{
			case LUA_TNUMBER:				
				lua_pushnumber(m_pLuaState, *(lua_Number*)pInParam[i].Data());						
				break;			
			case LUA_TSTRING:
				lua_pushstring(m_pLuaState, (LPCSTR)pInParam[i].Data());
				break;
			case LUA_TLIGHTUSERDATA:
				lua_pushlightuserdata(m_pLuaState, pInParam[i].Data());
				break;
			default:
				DEBUG_STROUT("调用%s函数失败，输入参数类型错误！", szFunName);
				lua_settop(m_pLuaState, top);
				return false;
		}
	}
	if( !lua_pcall(m_pLuaState, nInNum, nOutNum, 0) )
	{
		for(int n = 0; n < nOutNum; n++)
		{
			int nType = lua_type(m_pLuaState, -1);
			switch(nType)
			{
				case LUA_TNUMBER:
					pOutParam[n].SetDataNum( lua_tonumber(m_pLuaState, -1) );
					lua_pop(m_pLuaState, 1);
					break;
				case LUA_TBOOLEAN:
					pOutParam[n].SetDataNum( lua_toboolean(m_pLuaState, -1) );
					lua_pop(m_pLuaState, 1);
					break;
				case LUA_TSTRING:
					pOutParam[n].SetDataString((LPCSTR)lua_tostring(m_pLuaState, -1));
					lua_pop(m_pLuaState, 1);
					break;
				case LUA_TLIGHTUSERDATA:
					pOutParam[n].SetDataPointer((void*)lua_topointer(m_pLuaState, -1));
					lua_pop(m_pLuaState, 1);
					break;
				default:
					DEBUG_STROUT("[CLuaEngine] 调用%s函数失败，输出参数类型错误！", szFunName);
					lua_settop(m_pLuaState, top);
					return false;					
			}
		}

		lua_settop(m_pLuaState, top);   //恢复栈成为未调用时的状态。
		return true;
	}	
	
	DEBUG_STROUT("[CLuaEngine] 调用%s函数失败，失败原因：%s", szFunName, GetLastError());
	lua_settop(m_pLuaState, top);
	return false;
}

BOOL CLuaEngine_Svr::RegUserFunc( const char *classname, const luaL_Reg *l)
{
	if(!classname)
		return RegUserFunc(l);
	luaL_register(m_pLuaState,classname,l);
	return true;
}

BOOL CLuaEngine_Svr::RegUserFunc(const luaL_Reg* l)
{
	lua_pushvalue(m_pLuaState,LUA_GLOBALSINDEX);
	luaL_register(m_pLuaState,NULL,l);
	return true;
}

BOOL CLuaEngine_Svr::RegGlobalFunc(const char* name, lua_CFunction func)
{
	lua_register(m_pLuaState,name,func);
	return true;
}

lua_Number CLuaEngine_Svr::GetLuaVariableNumber( LPCSTR szVariableName, LPCSTR szTableName /* = NULL */)
{
	int top = lua_gettop(m_pLuaState);
	if(szTableName==NULL)
	{
		lua_getglobal(m_pLuaState, szVariableName);
	}
	else 
	{
		lua_getglobal(m_pLuaState, szTableName);
		if(lua_istable(m_pLuaState, -1))
		{
			lua_getfield(m_pLuaState,-1,szVariableName);
		}
	}
	lua_Number result = 0;
	if (lua_isnumber(m_pLuaState, -1))
	{
		result = lua_tonumber(m_pLuaState, -1);
	}
	lua_settop(m_pLuaState, top);

	return result;
}

const char* CLuaEngine_Svr::GetLuaVariableString( LPCSTR szVariableName, LPCSTR szTableName /* = NULL */)
{
	int top = lua_gettop(m_pLuaState);
	if(szTableName==NULL)
	{
		lua_getglobal(m_pLuaState, szVariableName);
	}
	else 
	{
		lua_getglobal(m_pLuaState, szTableName);
		if(lua_istable(m_pLuaState, -1))
		{
			lua_getfield(m_pLuaState,-1,szVariableName);
		}
	}
	const char *result = 0;
	if (lua_isstring(m_pLuaState, -1))
	{
		result = lua_tostring(m_pLuaState, -1);
	}
	lua_settop(m_pLuaState, top);

	return result;
}


// static CLuaEngine Object
CLuaEngine_Svr &GetLuaEngine_Svr()
{
	static CLuaEngine_Svr s_LuaEngine;
	return s_LuaEngine;
}

