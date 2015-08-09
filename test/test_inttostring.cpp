/*************************************************************************
	> File Name: test_inttostring.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 26 Jul 2015 08:48:14 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#include<cstring>

int main(void)
{
    int ival = 10;
    std::string str = static_cast<std::string>(ival);
    std::cout<<"str="<<str<<std::endl;

    return 0;
}

