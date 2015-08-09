/*********************************************
> File  : Thread.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#ifndef _THREAD_H
#define _THREAD_H

#include <pthread.h>

#include "Noncopyable.h"

class Thread : public Noncopyable
{
public:
	Thread();
	~Thread();

	void start();
	void join();

	bool isRunning();

	virtual void run() = 0;

    static void* runInThread(void *arg);
private:
	pthread_t m_pthread_id;
	bool m_isRunning;
};
#endif
