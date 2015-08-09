/*********************************************
> File  : NonCopyable.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Wed 15 Jul 2015 11:51:31 AM CST
 ********************************************/

#ifndef _NONCOPYABLE_H
#define _NONCOPYABLE_H

class NonCopyable
{
    protected:
    NonCopyable(){

    }
    ~NonCopyable(){

    }


private:
    NonCopyable(const NonCopyable& rhs);
    NonCopyable& operator=(const NonCopyable& rhs);
};

#endif
