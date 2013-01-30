#pragma once

template<class T>
class CUtlSingleton
{
public:
	static T* Instance( ){
		static T* _instance = new T;
		return _instance; 
	}

protected:
	CUtlSingleton( );
};
