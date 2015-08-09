/*********************************************
> File  : Task.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#ifndef _TASK_H
#define _TASK_H

class Task
{
public:
	virtual ~Task(){}
	virtual void process()=0;
};


#endif
