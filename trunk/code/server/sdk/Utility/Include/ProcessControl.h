#ifndef PROCESS_H
#define PROCESS_H
#ifndef WIN32
#include <sys/types.h>
#include <unistd.h>
#endif


/*
 * ���̲�����صĺ���
 */
#ifndef WIN32
//��ȡ��ǰ����id,win32��ͬ������
int GetCurrentProcessId();
#endif

#endif
