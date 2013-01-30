#pragma	  once
#pragma warning(disable:4311)
#include "EngineDefine.h"
/** Bit Array field.
Creates and manages bit array objects.
@ingroup unicode
*/
class ENGINE_CLASS BitArray
{
public:
	/** Creates bit array with specified number of stored bitfields.
	*/
	BitArray(int size = 256);
	~BitArray();
	
	inline void setBit(int pos);			//Sets bit at position @c pos 
	inline void clearBit(int pos);					/** Clears bit at position @c pos */
	inline void addRange(int s, int e);			/** Sets bit range */
	inline void clearRange(int s, int e);			/** Clears bit range */
	inline void addBitArray(BitArray*);			/** Sets bits to 1, whose corresponding values
											in passed bit array are also 1 (bitwize OR) */
	
	inline void clearBitArray(BitArray*);			/** Sets bits to 0, whose corresponding values
											in passed bit array are also 1 */
	
	inline void intersectBitArray(BitArray*);		/** Makes intersection of current and
											the passed bit array (bitwize AND) */
	
	inline void addBitArray(char*, int);			/** Adds bit array from the passed byte stream. */
	
	inline void clearBitArray(char*, int);			/** Clears bit array from the passed byte stream. */
	
	inline bool getBit(int pos);					/** Returns bit value at position @c pos. */

	inline int*	Array(){return array;}				/** return array  By David*/
	inline int	Size(){return size;}				/** return size of array */
	inline void Init(int size);						/** Init Array When it not construct  by zhao */
private:
	int *array;
	int size;
	void createArray(bool set = false);
};


inline void BitArray::Init(int size)				
{
	array = 0;
	this->size = size/8/4+1;
	if (size % 8 == 0 && size/8%4 == 0) this->size--;
	createArray();
}

inline void BitArray::createArray(bool set)
{
	array = new int[size];
	memset(array, set?0xFF:0, size*sizeof(int));
}

inline void BitArray::setBit(int pos)
{
	if (!array) createArray();
//	if (int(array) == 1) return;
	if (intptr_t(array) == 1) return;
	array[pos>>5] |= 1 << (pos&0x1f);
}

inline void BitArray::clearBit(int pos)
{
	if (!array) return;
//	if (int(array) == 1) createArray(true);
	if (intptr_t(array) == 1) createArray(true);
	array[pos>>5] &= ~(1 << (pos&0x1f));
}

inline void BitArray::addRange(int s, int e)
{
//	if (int(array) == 1) return;
	if (intptr_t(array) == 1) return;
	if (!array) createArray();
	int cs = s>>5;
	if (s&0x1f){
		int fillbytes = 0xFFFFFFFF << (s&0x1f);
		if ((e>>5) == (s>>5)) fillbytes &= 0xFFFFFFFF >> (0x1F - e&0x1F);
		array[cs] |= fillbytes;
		cs++;
	};
	int ce = e>>5;
	if (s>>5 != ce && (e&0x1f) != 0x1f){
		array[ce] |= 0xFFFFFFFF >> (0x1F - e&0x1F);
		ce--;
	};
	for(int idx = cs; idx <= ce; idx++)
		array[idx] = 0xFFFFFFFF;
	if (cs == 0 && ce == size-1){
		delete[] array;
		array = (int*)1;
	};
}

inline void BitArray::clearRange(int s, int e)
{
	if (!array) return;
//	if (int(array) == 1) createArray(true);
	if (intptr_t(array) == 1) createArray(true);
	int cs = s>>5;
	if (s&0x1f){
		int fillbytes = 0xFFFFFFFF << (s&0x1f);
		if ((e&0x1F) == (s&0x1F)) fillbytes &= 0xFFFFFFFF >> (0x1F - e&0x1F);
		array[cs] &= ~fillbytes;
		cs++;
	};
	int ce = e>>5;
	if (s>>5 != ce && (e&0x1f) != 0x1f){
		array[ce] &= ~(0xFFFFFFFF >> (0x1F-(e&0x1F)));
		ce--;
	};
	for(int idx = cs; idx <= ce; idx++)
		array[idx] = 0x0;
	if (cs == 0 && ce == size-1){
		delete[] array;
		array = (int*)0;
	};
}
inline void BitArray::addBitArray(BitArray* ba){
//	if (int(array) == 1) return;
	if (intptr_t(array) == 1) return;
	if (!ba || !ba->array) return;
//	if (int(ba->array) == 1){
	if (intptr_t(ba->array) == 1){
		array = (int*)1;
		return;
	};
	if (!array) createArray();
	for(int i = 0; i < size; i++)
		array[i] |= ba->array[i];
}

inline void BitArray::clearBitArray(BitArray* ba)
{
	if (array == NULL) return;
	if (ba == NULL || ba->array == NULL) return;
//	if (int(array) == 1) createArray(true);
//	if (int(ba->array) == 1){
	if (intptr_t(array) == 1) createArray(true);
	if (intptr_t(ba->array) == 1){
		if (array != NULL) delete[] array;
		array = 0;
		return;
	};
	for(int i = 0; i < size; i++)
		array[i] &= ~ba->array[i];
}

inline void BitArray::intersectBitArray(BitArray*ba)
{
	if (array == NULL) return;
	if (ba == NULL || ba->array == NULL){
		delete[] array;
		array = 0;
		return;
	};
//	if (int(ba->array) == 1) return;
//	if (int(array) == 1) createArray(true);
	if (intptr_t(ba->array) == 1) return;
	if (intptr_t(array) == 1) createArray(true);
	for(int i = 0; i < size; i++)
		array[i] &= ba->array[i];
}


inline void BitArray::addBitArray(char *bits, int size)
{
//	if (int(array) == 1) return;
	if (intptr_t(array) == 1) return;
	if (!array) createArray();
	for(int i = 0; i < size && i < this->size*4;i++)
		((char*)array)[i] |= bits[i];
}

inline void BitArray::clearBitArray(char *bits, int size)
{
	if (!array) return;
//	if (int(array) == 1) createArray(true);
	if (intptr_t(array) == 1) createArray(true);
	for(int i = 0; i < size && i < this->size*4;i++)
		((char*)array)[i] &= ~bits[i];
}

inline bool BitArray::getBit(int pos)
{
	if (!array) return false;
//	if (int(array) == 1) return true;
	if (intptr_t(array) == 1) return true;
	return (array[pos>>5] & (1<<(pos&0x1f))) != 0;
}
