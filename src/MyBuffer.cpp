/*********************************************
> File  : MyBuffer.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#include <iostream>
#include "../include/MyBuffer.h"

Buffer::Buffer(std::size_t num)
	: m_notFull(m_mutex),
	  m_notEmpty(m_mutex),
	  m_maxSize(num)
{
}

Buffer::~Buffer()
{
}
	
void Buffer::push(MyTask *ptask)
{
	MutexLockGuard mtg(m_mutex);
	while(full())
	{
		m_notFull.wait();	
	}

	m_queue.push(ptask);
	m_notEmpty.notify();
}

MyTask *Buffer::pop()
{
	MutexLockGuard mtg(m_mutex);
	while(empty())
	{
		m_notEmpty.wait();
	}

	MyTask *ptask = m_queue.front();
	m_queue.pop();
	m_notFull.notify();
	return ptask;
}

bool Buffer::empty()
{
	return m_queue.empty();
}

bool Buffer::full()
{
	return m_maxSize == m_queue.size();
}
