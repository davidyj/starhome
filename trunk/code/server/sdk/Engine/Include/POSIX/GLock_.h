#ifndef GLOCK_POSIX_H
#define GLOCK_POSIX_H
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>

#include "atomic.h"

class CGLock
{
public:
	CGLock()
	{
		pthread_mutex_init(&mtx, NULL);
	}

	virtual ~CGLock()
	{
		pthread_mutex_destroy(&mtx);
	}

	inline void LOCK()
	{
		pthread_mutex_lock(&mtx);

	}

	inline void UNLOCK()
	{
		pthread_mutex_unlock(&mtx);
	}

private:
	pthread_mutex_t mtx;
};

#ifndef WAIT_OBJECT_0
#define WAIT_OBJECT_0 0
#endif

#ifndef WAIT_TIMEOUT
#define WAIT_TIMEOUT  ((int)258)
#endif

class CGEvent
{
public:
	CGEvent()
	{
		pthread_cond_init(&cond, NULL);
		pthread_mutex_init(&mtx, NULL);
	}

	virtual ~CGEvent()
	{

	}

	inline void Event()
	{
		pthread_cond_broadcast(&cond);
	}

	/*
	 * on WIN32, this function returns WAIT_OBJECT_0 (0)
	 */
	inline int Wait()
	{
		pthread_mutex_lock(&mtx);
		pthread_cond_wait(&cond, &mtx);
		pthread_mutex_unlock(&mtx);
		return WAIT_OBJECT_0;
	}

	/*
	 * its return value must be exactly the same as the WIN32 version of this function
	 */
	inline int Wait(int millisecond)
	{
		struct timespec abstime;
		struct timeval now;
		gettimeofday(&now, NULL);
		int nsec = millisecond % 1000;
		int sec = millisecond/1000;

		nsec = nsec * 1000 * 1000 + now.tv_usec *1000;
		sec += now.tv_sec;

		while (nsec > 1000*1000*1000) {
			sec++;
			nsec -= 1000*1000*1000;
		}
		abstime.tv_sec = sec;
		abstime.tv_nsec = nsec;

		int result = 0;
		pthread_mutex_lock(&mtx);
		result = pthread_cond_timedwait(&cond, &mtx, &abstime);
		pthread_mutex_unlock(&mtx);
		if (!result) {
			return WAIT_OBJECT_0;
		}else {
			return WAIT_TIMEOUT;
		}
	}

protected:
	pthread_cond_t cond;
	pthread_mutex_t mtx;
};


class CGCount
{
public :
	CGCount()
	{
		m_Index = 0;
	}
	virtual ~CGCount()
	{
	}

	inline CGCount& operator++(int)
	{
		InterlockedIncrement(&m_Index);
//		apr_atomic_inc32((unsigned int *)&m_Index);
		return (*this);
	}
	inline CGCount& operator--(int)
	{
		InterlockedDecrement(&m_Index);
//		apr_atomic_dec32((unsigned *)&m_Index);
		return(*this);
	}
	int Get(){
		return m_Index;
	}

protected:
	long m_Index;
};
#endif
