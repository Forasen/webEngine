/*********************************************
  > File  : MyLock.h
  > Author: NewYork
  > Mail  : 2287794993@qq.com 
  > Time  : Sat 11 Jul 2015 10:47:13 PM CST
 ********************************************/

#ifndef _MYLOCK_H
#define _MYLOCK_H

#include <pthread.h>

#include "Noncopyable.h"

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
	pthread_mutex_t m_mutex;
	bool m_isLocking;
};


class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock & mutex);

	~MutexLockGuard();

private:
	MutexLock &m_mutex;
};

#endif
