#include "SvrConverse.h"


ConverseMgr::ConverseMgr()
{
}

ConverseMgr::~ConverseMgr()
{
}

bool ConverseMgr::ConverseOutput(const char* szIni, ConverseObj* pConver)
{
	if( !szIni || !strlen(szIni) || !pConver )
		return false;

	CSimpleIniA ini;
	if( !getConverse(ini, szIni) )
		return false;

	ini.SetLongValue("status", "time", pConver->out_time);
	ini.SetLongValue("status", "user", pConver->out_user);

	return SaveConverse(ini, szIni);
}

bool ConverseMgr::ConverseInput(const char* szIni, ConverseObj* pConver)
{
	if( !szIni || !strlen(szIni) || !pConver )
		return false;

	CSimpleIniA ini;
	if( !getConverse(ini, szIni) )
		return false;

	const char* szOpen = ini.GetValue("status", "switchopen");
	const char* szClose= ini.GetValue("status", "switchclose");

	if( szOpen && strlen(szOpen) < CONVERSE_STRING_LENTH )
		sprintf( pConver->in_SwitchOpen, "%s", szOpen );
	if( szClose && strlen(szClose) < CONVERSE_STRING_LENTH )
		sprintf( pConver->in_SwitchClose, "%s", szClose );

	return true;
}
