/*********************************************
> File  : ThreadPool.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#include "ThreadPool.h"
#include "MyPoolThread.h"
#include "MyTask.h"

ThreadPool::~ThreadPool()
{
	if(isExit_ == false)
	{
		isExit_ = true;
		std::vector<Thread *>::iterator it;
		for(it = vecThreads_.begin(); it != vecThreads_.end(); ++it)
		{
			(*it)->join();
			delete *it;
		}
	}
	vecThreads_.clear();
}
void ThreadPool::start()
{
	for(std::size_t idx = 0; idx != numThreads_; ++idx)
	{
		Thread *pThread = new MyPoolThread(*this);
		vecThreads_.push_back(pThread);
		pThread->start();
	}
}
void ThreadPool::addTask(MyTask *ptask)
{
	buffer_.push(ptask);
}
MyTask * ThreadPool::getTask()
{
	return buffer_.pop();
}
void ThreadPool::runInThread()
{
	while(!isExit_)
	{
		MyTask *ptask = getTask();	
		if(ptask != NULL)
		ptask->process();//Ö´ÐÐÈÎÎñ
	}
}
