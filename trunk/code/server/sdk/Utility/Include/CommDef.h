#ifndef COMMON_DEF_H
#define COMMON_DEF_H

#include "../../Port/config.h"
#ifdef WIN32
#include "WIN32/CommDef_.h"
#else
#include "POSIX/CommDef_.h"
#endif

#endif
