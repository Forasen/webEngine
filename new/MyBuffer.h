/*********************************************
> File  : MyBuffer.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:49:13 PM CST
 ********************************************/
#ifndef _MYBUFFER_H
#define _MYBUFFER_H

#include "Noncopyable.h"
#include "MyLock.h"
#include "MyCondition.h"
#include <queue>

class MyTask;
//class Task;

class Buffer //: public Noncopyable
{
public:
	explicit Buffer(std::size_t num);//explicit防止隐式转换
	~Buffer();

	//void push(Task *ptask);
	void push(MyTask *ptask);

	//Task * pop();
	MyTask * pop();

	bool empty();
	bool full();

private:
	MutexLock mutex_;
	Condition notFull_;
	Condition notEmpty_;

	std::size_t maxSize_;
	//std::queue<Task *> que_;
	std::queue<MyTask *> que_;
};

#endif
