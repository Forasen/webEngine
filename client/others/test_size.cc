/*********************************************
> File  : test_size.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Tue 14 Jul 2015 08:13:23 PM CST
 ********************************************/

#include<iostream>
#include<string.h>

int main(void)
{
    std::string str = "hello";
    int ret = str.size();
    std::cout<<"ret(string) = "<<ret<<std::endl;
    int ret1 = 10;
    std::cout<<"ret(int   ) = "<<ret1.size()<<std::endl;
    return 0;
}
