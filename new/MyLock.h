/*********************************************
  > File  : MyLock.h
  > Author: NewYork
  > Mail  : 2287794993@qq.com 
  > Time  : Sat 11 Jul 2015 10:47:13 PM CST
 ********************************************/

#ifndef _MYLOCK_H
#define _MYLOCK_H

#include "Noncopyable.h"
#include <pthread.h>

class MutexLock : public Noncopyable
{
public:
	MutexLock();
	~MutexLock();

	void lock();
	void unlock();

	bool isLocked() const;
	pthread_mutex_t *getMutexPtr();

private:	
	pthread_mutex_t mutex_;
	bool isLocking_;
};//end of class MutexLock


class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock & mutex);

	~MutexLockGuard();

private:
	MutexLock &mutex_;
};

#endif
