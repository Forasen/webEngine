/*********************************************
> File  : MyCondition.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#include "./../include/MyLock.h"
#include "./../include/MyCondition.h"

Condition::Condition(MutexLock & mutex)
	: m_mutex(mutex)
{
	pthread_cond_init(&m_condition, NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(&m_condition);
}

void Condition::wait()
{
	pthread_cond_wait(&m_condition, m_mutex.getMutexPtr());
}

void Condition::notify()
{
	pthread_cond_signal(&m_condition);
}

void Condition::notifyall()
{
	pthread_cond_broadcast(&m_condition);
}

