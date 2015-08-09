/*************************************************************************
	> File Name: test_file.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2015 03:08:47 PM CST
 ************************************************************************/

#include<iostream>
#include<fstream>
#include<sstream>
#include<stdio.h>
#include<stdlib.h>

using namespace std;


int main(void)
{
    ifstream input("./C15-Energy65.txt");
    //ifstream input("./small.txt");
    if(!input)
    {
        perror("input");
        exit(-1);
    }
    std::string line;
    std::string content;
    while(getline(input, line))
    {
        //std::cout<<line<<std::endl;
        content+= line;
        content += "\n";
        //std::cout<<"content:"<<content<<std::endl;
    }
    std::cout<<"*******article***********"<<std::endl;
    std::cout<<content<<std::endl;

    return 0;
}
