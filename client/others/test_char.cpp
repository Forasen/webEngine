/*********************************************
> File  : test_char.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Wed 15 Jul 2015 10:57:53 AM CST
 ********************************************/

#include<iostream>
#include<string.h>

int main(void)
{

    char arr[1000];
    char* str1 = "hello";
    char* str2 = ", world1";
    strcpy(arr, str1);
    strcat(arr, str2);
    std::cout<<"arr : "<<arr<<std::endl;
    return 0;
}
