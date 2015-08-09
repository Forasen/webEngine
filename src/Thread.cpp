/*********************************************
> File  : Thread.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#include "../include/Thread.h"

#include <iostream>

Thread::Thread()
	: m_pthread_id(0),
	  m_isRunning(false)
{
}

Thread::~Thread()
{
	pthread_detach(m_pthread_id);
}

void Thread::start()
{
	pthread_create(&m_pthread_id, NULL, runInThread, this);
	m_isRunning = true;
}

void Thread::join()
{
	pthread_join(m_pthread_id, NULL);
	m_isRunning= false;
}

void* Thread::runInThread(void *arg)
{
	Thread *pThread = static_cast<Thread *>(arg);
	pThread->run();
	return NULL;
}
