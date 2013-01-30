#include "../stdafx.h"
#include "BitArray.h"
BitArray::BitArray(int size /* = 256 */)
{
	array = 0;
	this->size = size/8/4+1;
	if (size % 8 == 0 && size/8%4 == 0) this->size--;
	createArray();
}

BitArray::~BitArray()
{
	//if (array && int(array) != 1) delete[] array;
	if (array && intptr_t(array) != 1) delete[] array;
}
