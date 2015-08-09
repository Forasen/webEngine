/*************************************************************************
	> File Name: test_oneword.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 29 Jul 2015 11:47:09 AM CST
 ************************************************************************/

#include<fstream>
#include<cstring>
#include<stdio.h>
#include<iostream>
using namespace std;

int main(void)
{
    std::ifstream input("./../filedata/stopList.txt");
    if(!input)
    {
        exit(1);
    }
    std::string word;
    int  cnt = 0;
    while(input >> word)
    {
        cnt ++;
        std::cout<<word<<std::endl;
        if(cnt > 100)
        break;
    }
}

