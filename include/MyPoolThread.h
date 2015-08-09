/*********************************************
  > File  : MyPoolThread.h
  > Author: NewYork
  > Mail  : 2287794993@qq.com 
  > Time  : Sat 11 Jul 2015 10:47:13 PM CST
 ********************************************/

#ifndef _MYPOOLTHREAD_
#define _MYPOOLTHREAD_

#include "Thread.h"

class ThreadPool;

class MyPoolThread : public Thread
{
public:
	MyPoolThread(ThreadPool & threadpool);

	void run();

private:
	ThreadPool & m_threadpool;
};
#endif
