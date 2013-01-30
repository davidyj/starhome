#include "StdAfx.h"
#include "ParamTable.h"

CParamTable& ParamTalbe()
{
	static CParamTable table;
	return table;
}
//////////////////////////////////////////////////////////////////////////
//

CParamTable::CParamTable()
{
	for(int i=0;i<Param_ID_End;i++)
		m_ParamTable[i] = 0;
}

CParamTable::~CParamTable()
{

}

void CParamTable::SetParam(int nID,int nValue)
{
	if(nID >= 0 && nID <Param_ID_End)
		m_ParamTable[nID] = nValue;
}

int CParamTable::GetParam(int nID)
{
	if(nID >= 0 && nID <Param_ID_End)
		return m_ParamTable[nID];
	return 1;
}

