#pragma once
#include "../../Port/config.h"
#include "EngineDefine.h"
extern   "C"   
{   
#include   "lua.h"   
#include   "lualib.h"   
#include   "lauxlib.h"   
}
//#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料

class LuaParam
{
public:
	inline int Type()
	{
		return m_nType;
	}	
	inline void SetDataNum(lua_Number num)
	{
		m_nDataNumber = num;
		m_nType = LUA_TNUMBER;
	}
	inline void SetDataString(const char* string)
	{
		m_pData = (void*)string;
		m_nType = LUA_TSTRING;
	}
	inline void SetDataPointer(void* pointer)
	{
		m_pData = pointer;
		m_nType = LUA_TLIGHTUSERDATA;
	}
	inline void* Data()
	{
		if(m_nType == LUA_TNUMBER)
			return &m_nDataNumber;
		return (void*)m_pData;
	}
	inline lua_Number DataNumber()
	{
		return m_nDataNumber;
	}
	LuaParam(void) { m_nDataNumber = 0;m_nType = LUA_TNUMBER;}
	LuaParam(void* pointer){ m_pData = pointer; m_nType = LUA_TLIGHTUSERDATA; }
	virtual ~LuaParam(void){};

private:
	int				m_nType;
	void*			m_pData;
	lua_Number		m_nDataNumber;

};

class ENGINE_CLASS CLuaEngine_Svr
{
public:
	CLuaEngine_Svr(void);
	virtual ~CLuaEngine_Svr(void);

public:
	BOOL			Init(int stacksize);
	void			Release(void);
	lua_State *		GetLuaState(void);
	const char*		GetLastError(void);
	
	BOOL			RegUserFunc( const char *classname, const luaL_Reg *l);
	BOOL			RegUserFunc(const luaL_Reg* l);
	BOOL			RegGlobalFunc(const char* name, lua_CFunction func);
	
	BOOL			LoadLuaFile(const char* szName);
	BOOL			LoadLuaFile(const char* szName, const char* szPathID);
	BOOL			RunMemoryLua(const char* pLuaData, int nDataLen);
	BOOL			RunLuaFunction(const char* szFunName, const char* szTableName = NULL,  const char* szSubTableName = NULL,LuaParam * pInParam = NULL, int nInNum = 0, LuaParam * pOutParam = NULL, int nOutNum = 0);
	
	lua_Number		GetLuaVariableNumber( const char* szVariableName, const char* szTableName = NULL);
	const char*		GetLuaVariableString( const char* szVariableName, const char* szTableName = NULL);
private:
	BOOL			CreateLuaState(int stacksize);
	lua_State *		m_pLuaState;

};


// static CLuaEngine Object
ENGINE_GLOBAL CLuaEngine_Svr &GetLuaEngine_Svr();

