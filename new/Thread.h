/*********************************************
> File  : Thread.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#ifndef _THREAD_H
#define _THREAD_H

#include "Noncopyable.h"
#include <pthread.h>

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
	pthread_t pthId_;
	bool isRunning_;
};

#endif

