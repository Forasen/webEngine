/*********************************************
> File  : MyCondition.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:49:13 PM CST
 ********************************************/

#ifndef _MYCONDITION_H
#define _MYCONDITION_H

#include <pthread.h>

#include "Noncopyable.h"

class MutexLock;
class Condition : public Noncopyable
{
public:
	Condition(MutexLock &mutex);
	~Condition();

	void wait();
	void notify();
	void notifyall();

private:
	pthread_cond_t m_condition;
	MutexLock & m_mutex;
};
#endif
