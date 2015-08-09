/*********************************************
> File  : ThreadPool.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include <vector>
#include<iostream>

#include "Noncopyable.h"
#include "MyBuffer.h"

class MyTask;
class Thread;

class ThreadPool
{
public:
	ThreadPool(std::size_t numThreads,
			   std::size_t bufSize)
		: m_num_threads(numThreads),
		  m_bufferSize(bufSize),
		  m_buffer(bufSize),
		  m_isExit(false)
    {
        std::cout<<"The ThreadPool is starting..."<<std::endl;
        std::cout<<"threads_num="<<numThreads
            <<"\nbuffers_num="<<bufSize<<std::endl;
    }

	~ThreadPool();

	void start();
	void addTask(MyTask *ptask);
	void runInThread();
private:
	MyTask * getTask();
private:
	std::vector<Thread *> m_vec_threads;
	std::size_t m_num_threads;
	std::size_t m_bufferSize;
	Buffer m_buffer;
	bool m_isExit;
};
#endif
