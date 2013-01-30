#ifndef OS_ALLOCATOR_H_
#define OS_ALLOCATOR_H_

#ifdef _MSC_VER
#pragma warning(disable:4251)
#pragma warning(disable:4267)
#endif

#include <list>

#ifndef WIN32		//	2010-11-27	li9chuan	for memset()
#include <string.h>
#endif

// Default node allocator.
// With a reasonable compiler, this should be roughly as fast as the
// original STL class-specific allocators, but with less fragmentation.
// Default_alloc_template parameters are experimental and MAY
// DISAPPEAR in the future.  Clients should just use alloc for now.
//
// Important implementation properties:
// 1. If the client request an object of size > _MAX_BYTES, the resulting
//    object will be obtained directly from malloc.
// 2. In all other cases, we allocate an object of size exactly
//    _S_round_up(requested_size).  Thus the client has enough size
//    information that we can return the object to the proper free list
//    without permanently losing part of the object.
//

// The first template parameter specifies whether more than one thread
// may use this allocator.  It is safe to allocate an object from
// one instance of a default_alloc and deallocate it with another
// one.  This effectively transfers its ownership to the second one.
// This may have undesirable effects on reference locality.
// The second parameter is unreferenced and serves only to allow the
// creation of multiple default_alloc instances.
// Node that containers built on different allocator instances have
// different types, limiting the utility of this approach.


class Allocator
{
	
private:
	// Really we should use static const int x = N
	// instead of enum { x = N }, but few compilers accept the former.
    enum {_ALIGN = 8};
	unsigned int _MAX_BYTES;
	unsigned int _NFREELISTS;
    //enum {_MAX_BYTES = 128};
    //enum {_NFREELISTS = 16}; // _MAX_BYTES/_ALIGN
	
	size_t
		_S_round_up(size_t __bytes) 
    { return (((__bytes) + (size_t) _ALIGN-1) & ~((size_t) _ALIGN - 1)); }
	
	union _Obj {
        union _Obj* _M_free_list_link;
        char _M_client_data[1];    /* The client sees this.        */
	};
private:
    _Obj* * _S_free_list; 
	
	size_t _S_freelist_index(size_t __bytes) {
        return (((__bytes) + (size_t)_ALIGN-1)/(size_t)_ALIGN - 1);
	}
	
	// Returns an object of size __n, and optionally adds to size __n free list.
	void* _S_refill(size_t __n);
	// Allocates a chunk for nobjs of size size.  nobjs may be reduced
	// if it is inconvenient to allocate the requested number.
	char* _S_chunk_alloc(size_t __size, int& __nobjs);
	
	// Chunk allocation state.
	char* _S_start_free;
	char* _S_end_free;
	size_t _S_heap_size;
	
	std::list<void*> _alloced_chucks;
		
public:
	Allocator(unsigned int maxBytes) :
		_S_start_free(0),
		_S_end_free(0),
		_S_heap_size(0)
	{
		_MAX_BYTES = _S_round_up(maxBytes);
		_NFREELISTS = _MAX_BYTES/_ALIGN;

//		_S_free_list = new _Obj*[_NFREELISTS];
		_S_free_list = (_Obj**)malloc( sizeof(_Obj*)*_NFREELISTS );
		memset(_S_free_list, 0, sizeof(_Obj*)*_NFREELISTS);
	}
	
	~Allocator()
	{
		for (std::list<void*>::iterator it = _alloced_chucks.begin(); it != _alloced_chucks.end(); ++it)
			free(*it);
		_alloced_chucks.clear();

		if( _S_free_list )
		{
			//delete [] _S_free_list;
			free(_S_free_list);
			_S_free_list = NULL;
		}
	}		

	void Renew( )
	{
		for (std::list<void*>::iterator it = _alloced_chucks.begin(); it != _alloced_chucks.end(); ++it)
			free(*it);
		_alloced_chucks.clear();

		if( _S_free_list )
		{
			//delete [] _S_free_list;
			free(_S_free_list);
			_S_free_list = NULL;
		}
		_S_start_free = 0;
		_S_end_free = 0;
		_S_heap_size = 0;
		{
			_MAX_BYTES = _S_round_up(1000);
			_NFREELISTS = _MAX_BYTES/_ALIGN;

			//		_S_free_list = new _Obj*[_NFREELISTS];
			_S_free_list = (_Obj**)malloc( sizeof(_Obj*)*_NFREELISTS );
			memset(_S_free_list, 0, sizeof(_Obj*)*_NFREELISTS);
		}
	}
	/* __n must be > 0      */
	void* allocate(size_t __n)
	{
		void* __ret = 0;
		
		if (__n > (size_t) _MAX_BYTES) {
			__ret = malloc(__n);
		}
		else {
			_Obj** __my_free_list
				= _S_free_list + _S_freelist_index(__n);
			
			_Obj* __result = *__my_free_list;
			if (__result == 0)
				__ret = _S_refill(_S_round_up(__n));
			else {
				*__my_free_list = __result -> _M_free_list_link;
				__ret = __result;
			}
		}
		
		return __ret;
	};
	
	/* __p may not be 0 */
	void deallocate(void* __p, size_t __n)
	{
		if (__n > (size_t) _MAX_BYTES)
			free(__p);
		else {
			_Obj**  __my_free_list
				= _S_free_list + _S_freelist_index(__n);
			_Obj* __q = (_Obj*)__p;
			
			__q -> _M_free_list_link = *__my_free_list;
			*__my_free_list = __q;
			
		}
	}
	
	void* reallocate(void* __p, size_t __old_sz, size_t __new_sz);
} ;

Allocator &MemoryAllocator( );

#endif // #ifndef OS_ALLOCATOR_H_
