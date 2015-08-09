/*********************************************
> File  : MyCondition.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:49:13 PM CST
 ********************************************/

#ifndef _MYCONDITION_H
#define _MYCONDITION_H

#include "Noncopyable.h"
#include <pthread.h>

class MutexLock;//Ç°ÏòÉùÃ÷
class Condition : public Noncopyable
{
public:
	Condition(MutexLock &mutex);
	~Condition();

	void wait();
	void notify();
	void notifyall();

private:
	pthread_cond_t cond_;
	MutexLock & mutex_;
};

#endif
