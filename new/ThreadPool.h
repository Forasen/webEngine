/*********************************************
> File  : ThreadPool.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include "Noncopyable.h"
#include "MyBuffer.h"
#include <vector>


class MyTask;
class Thread;
//class Task;

class ThreadPool //: public Noncopyable
{
public:
	ThreadPool(std::size_t numThreads,
			   std::size_t bufSize)
		: numThreads_(numThreads),
		  bufSize_(bufSize),
		  buffer_(bufSize),
		  isExit_(false)
	{}

	~ThreadPool();

	void start();
	void addTask(MyTask *ptask);//+_+_+
	void runInThread();
private:
	//Task * getTask();
	MyTask * getTask();
private:
	std::vector<Thread *> vecThreads_;
	std::size_t numThreads_;
	std::size_t bufSize_;
	Buffer buffer_;//这里需要是Buffer的实现,所以要引入的是头文件
	bool isExit_;
};

#endif
