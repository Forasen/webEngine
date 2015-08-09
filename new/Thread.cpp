/*********************************************
> File  : Thread.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#include "Thread.h"
#include <iostream>

Thread::Thread()
	: pthId_(0),
	  isRunning_(false)
{
	std::cout <<"Thread::Thread()" << std::endl;
}

Thread::~Thread()
{
	pthread_detach(pthId_);
}

void Thread::start()
{
	pthread_create(&pthId_, NULL, runInThread, this);
	isRunning_ = true;
}

void Thread::join()
{
	pthread_join(pthId_, NULL);
	isRunning_ = false;
}

void* Thread::runInThread(void *arg)//static, 不带this指针
{
	Thread *pThread = static_cast<Thread *>(arg);
	pThread->run();
	return NULL;
}
