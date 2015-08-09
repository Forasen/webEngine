/*********************************************
> File  : MyThreadPool.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#include "MyPoolThread.h"
#include "ThreadPool.h"

MyPoolThread::MyPoolThread(ThreadPool & threadpool)
	: threadpool_(threadpool)
{
}

void MyPoolThread::run()
{
	threadpool_.runInThread();
}
