#pragma once

#include <string>
#include <vector>
#include "inttypes.h"
//#include <fstream>
//#include <iostream>

//using namespace std;

class CToken
{
private:

//	int _tokenCount;
	std::vector<std::string> token;
	std::string delims;
	std::string string_null;
	void separtor( std::string& line );

public:

	void setToken( std::string delims );
	bool parseString( std::string& line );
	//inline int size(){ return _tokenCount; }
	inline int size(){ return token.size(); }

	std::string& getStr( int idx );
	int32_t  getInt32( int idx );
	int64_t  getInt64( int idx );
};
