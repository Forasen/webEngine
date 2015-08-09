/*************************************************************************
	> File Name: test_length.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2015 04:44:05 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;


int main(void)
{
    std::string str = "^M";
    std::cout<<"str.size="<<str.size()<<std::endl;
    std::string str1 = "hello,world";
    std::cout<<"str1.substr(5)"<<str1.substr(5)<<std::endl;
    return 0;
}
