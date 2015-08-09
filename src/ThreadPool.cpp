/*********************************************
> File  : ThreadPool.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#include "../include/ThreadPool.h"
#include "../include/MyPoolThread.h"
#include "../include/MyTask.h"

ThreadPool::~ThreadPool()
{
	if(m_isExit == false)
	{
		m_isExit = true;
		std::vector<Thread *>::iterator it;
		for(it = m_vec_threads.begin(); it != m_vec_threads.end(); ++it)
		{
			(*it)->join();
			delete *it;
		}
	}
	m_vec_threads.clear();
}
void ThreadPool::start()
{
	for(std::size_t idx = 0; idx != m_num_threads; ++idx)
	{
		Thread *pThread = new MyPoolThread(*this);
		m_vec_threads.push_back(pThread);
		pThread->start();
	}
}
void ThreadPool::addTask(MyTask *ptask)
{
	m_buffer.push(ptask);
}
MyTask * ThreadPool::getTask()
{
	return m_buffer.pop();
}
void ThreadPool::runInThread()
{
	while(!m_isExit)
	{
		MyTask *ptask = getTask();	
		if(ptask != NULL)
		ptask->process();
	}
}
