/*********************************************
> File  : main_timer.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Wed 15 Jul 2015 11:53:56 AM CST
 ********************************************/

#include<iostream>
#include"Timer.h"
#include<unistd.h>
#include<stdio.h>

void foo()
{
    printf("timer call\n");
}

int main()
{
    Timer timer(4, 5, &foo);
    timer.start(0);
    while(1)
    {
        printf("hello world!");
        sleep(1);
    }
    timer.stop();

    return 0;
}
