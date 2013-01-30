#ifndef OSNET_H
#define OSNET_H 

#ifdef WIN32
#include "./WIN32/IOCP.h"
#else
#include "./POSIX/KQueue.h"
#endif

#endif
