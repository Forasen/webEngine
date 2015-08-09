/*********************************************
> File  : MyBuffer.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:49:13 PM CST
 ********************************************/
#ifndef _MYBUFFER_H
#define _MYBUFFER_H

#include <queue>

#include "Noncopyable.h"
#include "MyLock.h"
#include "MyCondition.h"

class MyTask;

class Buffer
{
public:
	explicit Buffer(std::size_t num);
	~Buffer();

	void push(MyTask *ptask);

	MyTask * pop();

	bool empty();
	bool full();

private:
	MutexLock m_mutex;
	Condition m_notFull;
	Condition m_notEmpty;
	std::size_t m_maxSize;
	std::queue<MyTask *> m_queue;
};

#endif
