/*********************************
 *@fileName: Condition.cc
 *@author  : lemon
 *@email   : haohb13@gmail.com
 *@created : 2015-07-02 11:09:57
**********************************/


#include "MyLock.h"
#include "MyCondition.h"


Condition::Condition(MutexLock & mutex)
	: mutex_(mutex)
{
	pthread_cond_init(&cond_, NULL);
}

Condition::~Condition()
{
	pthread_cond_destroy(&cond_);
}

void Condition::wait()
{
	pthread_cond_wait(&cond_, mutex_.getMutexPtr());
}

void Condition::notify()
{
	pthread_cond_signal(&cond_);
}

void Condition::notifyall()
{
	pthread_cond_broadcast(&cond_);
}

