#ifndef ENGINE_BASE_H
#define ENGINE_BASE_H
#pragma once
//#include "malloc.h"
#include "EngineDefine.h"

/*
void* operator new(size_t nSize );
void operator delete(void* p);
void* operator new[](size_t cb);
void operator delete[](void* p);

void* operator new(size_t nSize,LPCSTR lpszFileName, int nLine);
void operator delete(void* p, LPCSTR lpszFileName, int nLine);
void* operator new[](size_t nSize,LPCSTR lpszFileName, int nLine);
void operator delete[](void* p, LPCSTR lpszFileName, int nLine);


#define ENGINE_NEW			new(__FILE__,__LINE__)
#define ENGINE_CONSTRUCT	new					//构造函数
*/
//////////////////////////////////////////////////////////////////////
// 对类进行串行化管理：
struct CClass
{
	LPCSTR m_lpszClassName;	//类名
	CClass* m_pBaseClass;	//基类指针
	BOOL IsDerivedFrom(const CClass* pBaseClass) const; //自己是否从指定类继承
};

class ENGINE_CLASS IBaseObj
{
	// 串行化处理
public:
	virtual CClass* GetClass() const;
	BOOL IsKindOf(const CClass* pClass) const;
	static const CClass classIBaseObj;

public:
	IBaseObj( );
	virtual ~IBaseObj( );

	/*
	inline void *operator new(size_t, void *_P){return (_P); }
	inline void operator delete(void *, void *){return; }
	void* operator new(size_t nSize);
	void operator delete(void* p);

	void* operator new(size_t nSize,LPCSTR lpszFileName, int nLine);
	void operator delete(void* p,LPCSTR lpszFileName, int nLine);

	void* operator new[](size_t nSize, LPCSTR lpszFileName, int nLine);
	void operator delete[](void* p, LPCSTR lpszFileName, int nLine);
	*/
};

#define GET_CLASS(class_name) ((CClass*)(&class_name::class##class_name))

#define DECLARE_CLASS(class_name)\
public: \
	static const CClass class##class_name; \
	virtual CClass* GetClass() const; \

#define IMPLEMENT_CLASS(class_name,base_class_name)\
	const CClass class_name::class##class_name = { \
#class_name, GET_CLASS(base_class_name) }; \
	CClass* class_name::GetClass() const \
	{ return GET_CLASS(class_name); }
//#ifndef _ENGINELIB
//void *__cdecl operator new[](size_t);
//void __cdecl operator delete[](void*p);
//#endif
#endif

