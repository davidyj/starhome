#include "../stdafx.h"
#include "BaseObj.h"
#include "dbg.h"


const struct CClass IBaseObj::classIBaseObj =
{ "IBaseObj", NULL };

CClass* IBaseObj::GetClass() const
{
	return GET_CLASS( IBaseObj );
}

BOOL IBaseObj::IsKindOf(const CClass* pClass) const
{
	AssertValidThis( );

	CClass* pClassThis = GetClass( );
	return pClassThis->IsDerivedFrom( pClass );
}

BOOL CClass::IsDerivedFrom(const CClass* pBaseClass) const
{
	//	CHECK_POINTER(this, sizeof(CClass));
	//	CHECK_POINTER(pBaseClass, sizeof(CClass));

	const CClass* pClassThis = this;
	while ( pClassThis != NULL )
	{
		if ( pClassThis == pBaseClass )
			return TRUE;

		pClassThis = pClassThis->m_pBaseClass;
	}
	return FALSE;       // walked to the top, no match
}

IBaseObj::IBaseObj( )
{
}

IBaseObj::~IBaseObj( )
{
}
/*
void* IBaseObj::operator new(size_t nSize)
{
	return Plat_Alloc(nSize);
}

void IBaseObj::operator delete(void* p)
{
	Plat_Free(p);
}

void* IBaseObj::operator new(size_t nSize,LPCSTR lpszFileName, int nLine)
{
	Log("%s %d alloc memeory %d ",lpszFileName, nLine,nSize);
	return Plat_Alloc(nSize);
}

void IBaseObj::operator delete(void* p,LPCSTR lpszFileName, int nLine)
{
	Plat_Free(p);
}

void* IBaseObj::operator new[](size_t nSize,LPCSTR lpszFileName, int nLine)
{
	Log("%s %d alloc memeory %d ",lpszFileName, nLine,nSize);
	return Plat_Alloc(nSize);
}

void IBaseObj::operator delete[](void* p,LPCSTR lpszFileName, int nLine)
{
	Plat_Free(p);
}
*/
/*
void* operator new(size_t nSize)
{
	return Plat_Alloc( nSize );
}

void operator delete(void* p)
{
	Plat_Free( p );
}

void* operator new[](size_t cb)
{
	return Plat_Alloc( cb );
}

void operator delete[](void* p)
{
	Plat_Free( p );
}

void* operator new(size_t nSize, LPCSTR lpszFileName, int nLine)
{
	Log(" %s %d alloc memory size = %d",lpszFileName,nLine,nSize);
	return Plat_Alloc( nSize );
}

void operator delete(void* p, LPCSTR lpszFileName, int nLine)
{
	Plat_Free( p );
}

void* operator new[](size_t nSize, LPCSTR lpszFileName, int nLine)
{
	Log(" %s %d alloc memory size = %d",lpszFileName,nLine,nSize);
	return Plat_Alloc( nSize );
}

void operator delete[](void* p, LPCSTR lpszFileName, int nLine)
{
	Plat_Free( p );
}


/*
void *__cdecl operator new[](size_t cb)
{
	return Plat_Alloc( cb );
}

void __cdecl operator delete[](void*p)
{
	Plat_Free( p );
}
*/
