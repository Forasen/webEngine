/*********************************************
> File  : Timer.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Wed 15 Jul 2015 11:18:41 AM CST
 ********************************************/

#include<iostream>
#include<timerfd.h>
#include<poll.h>
#include<unistd.h>
#include<>


Timer::Timer()
	:
int createTimerfd()
{
    int timerfd = timerfd_create(CLOCK_REALITIME, 0);
    if(-1 == timerfd)
    {
        perror("timerfd_create");
        exit(1);
    }
    return timerfd;
}
void setTimerfd(int fd, int value, int interval)
{
    struct timespec val;
    val.it_value.tv_sec = value;
    val.it__interval.tv_sec = interval;
    if(-1 == timerfd_settime(fd, 0, &value))
    {
        perror("timerfd_settime error!");
    }
}

void stopTimerfd(int fd)
{
    setTimerfd(fd, 0, 0);
}

Timer::~Timer()
{
	if(m_isStarted)
	{
		stop();
		m_isStarted = false;
	}
}

void Timer::start()
{
	setTimerfd(m_timerfd, m_val, m_interval);
	struct pollfd pfd;
	pollfd.fd = m_timerfd;
	pollfd.events = POLLIN;

	m_isStarted = true;
	while(m_isStarted)
	{
		int ret = poll(&pfd, 1, 5000);
		if(-1 == ret)
		{
			if(errno == EINTR)
			{
				continue;
			}
			perror("error: poll!");
			exit(1);
		}
		else if(0 == ret)
		{
			printf("timeout\n");
		}
		else if(pfd.revents == POLLIN)
		{
			uint64_t tmp = readTimerfd(m_timerfd);
			printf("read timerfd = %llu\n", tmp);
			m_cb();
		}
	}
}
 
void Timer::stop()
{
	stopTimerfd()
	if()
}
