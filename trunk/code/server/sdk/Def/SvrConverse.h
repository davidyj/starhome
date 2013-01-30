#ifndef _SVR_CONVERSE_H_
#define _SVR_CONVERSE_H_

#include "SimpleIni.h"

#define CONVERSE_STRING_LENTH	1024

struct ConverseObj
{
	long		out_time;
	long		out_user;
	char		in_SwitchOpen[CONVERSE_STRING_LENTH];
	char		in_SwitchClose[CONVERSE_STRING_LENTH];

	ConverseObj()
	{
		out_time = -1;
		out_user = -1;
		in_SwitchOpen[0] = '\0';
		in_SwitchClose[0]= '\0';
	}
};

class ConverseMgr
{
public:
	static ConverseMgr& Instance()
	{
		static ConverseMgr mgr;
		return mgr;
	}

	bool ConverseOutput(const char* szIni, ConverseObj* pConver);
	bool ConverseInput(const char* szIni, ConverseObj* pConver);

protected:
	ConverseMgr();
	~ConverseMgr();

	inline bool	getConverse( CSimpleIniA& ini, const char* szIni )
	{
		if( !szIni || !strlen(szIni) )
			return false;
		//ini.SetUnicode();
		return (ini.LoadFile( szIni ) >= 0);
	}
	inline bool	SaveConverse( CSimpleIniA& ini, const char* szIni )	
	{
		if( !szIni || !strlen(szIni) )
			return false;
		return (ini.SaveFile(szIni) >= 0); 
	}

};

#endif
