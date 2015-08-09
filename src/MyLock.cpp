/*********************************************
> File  : MyLock.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#include "../include/MyLock.h"

MutexLock::MutexLock()
	: m_isLocking(false)
{
	pthread_mutex_init(&m_mutex, NULL);
}

MutexLock::~MutexLock()
{
	pthread_mutex_destroy(&m_mutex);
}

void MutexLock::lock()
{
	pthread_mutex_lock(&m_mutex);
	m_isLocking = true;
}

void MutexLock::unlock()
{
	pthread_mutex_unlock(&m_mutex);
	m_isLocking = false;
}

bool MutexLock::isLocked() const
{
	return m_isLocking;
}

pthread_mutex_t * MutexLock::getMutexPtr()
{
	return &m_mutex;
}

MutexLockGuard::MutexLockGuard(MutexLock & mutex)
	: m_mutex(mutex)
{
	m_mutex.lock();
}

MutexLockGuard::~MutexLockGuard()
{
	m_mutex.unlock();
}
