/*********************************************
> File  : MyPoolThread.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#include "../include/MyPoolThread.h"
#include "../include/ThreadPool.h"

MyPoolThread::MyPoolThread(ThreadPool & threadpool)
	: m_threadpool(threadpool)
{
}

void MyPoolThread::run()
{
	m_threadpool.runInThread();
}
