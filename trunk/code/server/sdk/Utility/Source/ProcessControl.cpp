/*
 * ���̲�����غ���
 *
 * ������:³���� 
 * ʱ��:2009.10.20
 */

#include "../Port/config.h"
#include "ProcessControl.h"



#ifndef WIN32
int GetCurrentProcessId()
{
	return getpid();
}
#endif

