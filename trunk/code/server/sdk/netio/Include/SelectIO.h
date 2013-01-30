#ifndef SELECT_IO_H
#define SELECT_IO_H 

#ifdef WIN32
#include "./WIN32/SelectIO.h"
#else
#include "./POSIX/SelectIO.h"
#endif
#endif
