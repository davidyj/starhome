#pragma once


//²ÎÊý±í
enum Param_ID							
{	
	Param_ID_End							= 500,
};



class CParamTable
{
public:
	CParamTable();
	~CParamTable();

	void	SetParam(int nID,int nValue);
	int		GetParam(int nID);

protected:
	int			m_ParamTable[Param_ID_End];
};

CParamTable& ParamTalbe();



