#ifndef TIMER_POSIX_INC_H
#define TIMER_POSIX_INC_H

#define SIGMYTIMER (SIGRTMAX-1)
timer_t m_WaitableTimer;
static void OnTimer(int signo, siginfo_t* info, void* context);

int SetTimer(int milliseconds, int nMode);
bool SetSignalHandler();
#endif
