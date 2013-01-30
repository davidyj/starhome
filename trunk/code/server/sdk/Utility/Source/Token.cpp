#pragma warning (disable:4786) 
#include "stdafx.h"
#include "Token.h"
#include <stdio.h>

void CToken::setToken(std::string s){
	delims=s;
	string_null = "";
}

bool CToken::parseString(std::string& line){

	token.clear();
	if(line.empty()){
		return false;
	}
	separtor(line);
	return true;
}

void CToken::separtor(std::string& line)
{
	std::string word;
	std::string::size_type begIdx, endIdx; 
	while((begIdx=line.find_first_not_of(delims))!= std::string::npos)
	{     
		endIdx = line.find_first_of(delims,begIdx);   
		
		if(endIdx == std::string::npos)
		{     
			endIdx = line.length();   
		}   
		
		word=line.substr(begIdx,(endIdx-begIdx));     
		token.push_back(word); 
		line=line.substr(endIdx,(line.length()-endIdx));
//		_tokenCount++;
	}
}

std::string& CToken::getStr( int idx )
{
	if( size() > idx  )
		return token[idx];
	else
		return string_null;
}
	
int32_t  CToken::getInt32( int idx )
{
	if( size() > idx  )
		return atoi(token[idx].c_str());
	else
	{
		return -1;
	}
}

int64_t  CToken::getInt64( int idx )
{
	int64_t iData = -1;

	if( size() > idx  )
		sscanf( token[idx].c_str(), INT64_FMT, &iData );

	return iData;
}
