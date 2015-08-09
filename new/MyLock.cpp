/*********************************
 *@fileName: MutexLock.cc
 *@author  : lemon
 *@email   : haohb13@gmail.com
 *@created : 2015-07-02 11:02:13
**********************************/

#include "MyLock.h"

MutexLock::MutexLock()
	: isLocking_(false)
{
	pthread_mutex_init(&mutex_, NULL);
}

MutexLock::~MutexLock()
{
	pthread_mutex_destroy(&mutex_);
}

void MutexLock::lock()
{
	pthread_mutex_lock(&mutex_);
	isLocking_ = true;
}

void MutexLock::unlock()
{
	pthread_mutex_unlock(&mutex_);
	isLocking_ = false;
}

bool MutexLock::isLocked() const
{
	return isLocking_;
}

pthread_mutex_t * MutexLock::getMutexPtr()
{
	return &mutex_;
}

MutexLockGuard::MutexLockGuard(MutexLock & mutex)
	: mutex_(mutex)
{
	mutex_.lock();
}

MutexLockGuard::~MutexLockGuard()
{
	mutex_.unlock();
}
