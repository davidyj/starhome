#pragma once

#include <new>
#include "Chain.h"

class Allocator;
Allocator* GetAllocator( );

void initnew( );
void uninitnew( );
void * mynew( size_t size );
void mydelete( void * p );
void * myrenew( void * p, size_t size );

void * analyzealloc( size_t size );
void * analyzerealloc( void * p, size_t size );
void analyzefree( void * p );
void reportstate( );


class  MYCHAINITEM : public CHAINITEM
{
public:
	virtual void Clear( ){};
};


#define QS_NEW( p, classname ) \
	{ \
		(p) = ( classname * )mynew( sizeof( classname ) ); \
		new( (p) )classname; \
	} \

#define QS_DELETE( p ) \
	{ \
		if( p ) \
		{ \
			(p)->Clear( ); \
			mydelete( (p) ); \
			p = NULL; \
		} \
	} \

#define QS_NEW_ARRAY( p, classname, num ) \
	{ \
		(p) = ( classname * )mynew( sizeof( classname ) * (num) ); \
		for( int _i_count_temp_ = 0; _i_count_temp_ < (num); _i_count_temp_++ ) \
			new( &(p)[_i_count_temp_] )classname; \
	} \

#define QS_NEW_ARRAY2( p, classname, classtype, num ) \
	{ \
		(p) = ( classtype )mynew( sizeof( classname ) * (num) ); \
		for( int _i_count_temp_ = 0; _i_count_temp_ < (num); _i_count_temp_++ ) \
			new( &(p)[_i_count_temp_] )classname; \
	} \

#define QS_DELETE_ARRAY( p ) \
	{ \
		if( p ) \
		{ \
			mydelete( (p) ); \
			p = NULL; \
		} \
	} \

/*
#define QS_NEW( p, classname ) \
	{ \
		(p) = new classname; \
	} \

#define QS_DELETE( p ) \
	{ \
		if( p ) \
		{ \
			delete p; \
			p = NULL; \
		} \
	} \

#define QS_NEW_ARRAY( p, classname, num ) \
	{ \
		(p) = new classname[(num)]; \
	} \

#define QS_NEW_ARRAY2( p, classname, classtype, num ) \
	{ \
		(p) = ( classtype )new classname[(num)]; \
	} \

#define QS_DELETE_ARRAY( p ) \
	{ \
		if( p ) \
		{ \
			delete [] p; \
			p = NULL; \
		} \
	} \
*/
MYCHAINITEM *    ChainRemoveCurrent( CHAINHEADER * pChain );
void    ChainRemoveAll( CHAINHEADER * pChain );
