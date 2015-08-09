/*********************************
 *@fileName: Buffer.cc
 *@author  : lemon
 *@email   : haohb13@gmail.com
 *@created : 2015-07-02 11:20:58
**********************************/

#include "MyBuffer.h"
#include <iostream>

Buffer::Buffer(std::size_t num)
	: notFull_(mutex_),
	  notEmpty_(mutex_),
	  maxSize_(num)
{
	std::cout <<"Buffer::Buffer(int)" << std::endl;
}

Buffer::~Buffer()
{
	std::cout <<"Buffer::~Buffer()" << std::endl;
}
	
void Buffer::push(MyTask *ptask)
{
	MutexLockGuard mtg(mutex_);//执行了加锁操作,它会自动解锁
	while(full())
	{
		notFull_.wait();	
	}

	que_.push(ptask);//往缓冲区中添加数据
	notEmpty_.notify();//再发一个通知
}

MyTask *Buffer::pop()
//Task *Buffer::pop()
{
	MutexLockGuard mtg(mutex_);
	while(empty())
	{
		notEmpty_.wait();
	}

	MyTask *ptask = que_.front();
	que_.pop();
	notFull_.notify();
	return ptask;
}

bool Buffer::empty()
{
	return que_.empty();
}

bool Buffer::full()
{
	return maxSize_ == que_.size();
}
