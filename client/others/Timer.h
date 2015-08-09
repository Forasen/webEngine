/*********************************************
> File  : Timer.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Wed 15 Jul 2015 11:36:33 AM CST
 ********************************************/

#ifndef _TIMER_H
#define _TIMER_H

#include<iostream>
#include "NonCopyable.h"
#include<functional.h>
class Timer: private NonCopyable
{
public:
    typedef std::function<void()> TimerCallback;
    Timer(int val, int interval, TimerCallback cb);
    ~Timer();

    void start();
    void stop();


private:
    int m_timerfd;
    int m_val;
    int m_interval;
    TimerCallback m_cb;
    bool m_isStarted;
};

#endif
