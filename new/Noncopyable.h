/*********************************************
> File  : MyResult.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H

class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable(){}

private:
	Noncopyable(const Noncopyable & rhs);
	Noncopyable &operator=(const Noncopyable & rhs);
};

#endif
