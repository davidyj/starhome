#pragma once
#include "EngineDefine.h"

#include "GLock.h"

class ENGINE_CLASS CIDTable
{
public:
	CIDTable(void);
	CIDTable(DWORD nSize);
	virtual ~CIDTable(void);

public:
	void *CreateArray(DWORD dSize);				

	BOOL IsEmpty( ){ return m_nCount == 0; }			

	void DeleteID( DWORD id );						
	void DeleteID( DWORD id, DWORD param );		

	void *GetID( DWORD id );						
	int SetID( DWORD id,void *param );
	int GetSize( ){ return m_nCount; }					

	int AddID( void *param );						
	int CreateID();
	void AddID( DWORD id, void *param );
//	int AddID( DWORD id, void *param );
	void DeleteID( DWORD id,void *param );		

	void DeleteArray( );							
	void *operator[]( DWORD id );				
	
	int GetCursor(){ return m_nCursor; }
	int Find( void *ptr );						
	DWORD MemorySize( ){ return m_nMemorySize; }

	void ClearUp( );	

protected:
	void InitArray( );							
								
	int SetCursor( );							
	void Lock( );
	void UnLock( );

private:	
//	DWORD *m_pArray;
	uintptr_t *m_pArray;
	DWORD m_nCursor;									
	DWORD m_nCount;									
	DWORD m_nMemorySize;
	CGLock m_Lock;
};
