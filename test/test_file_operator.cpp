/*************************************************************************
	> File Name: test_file_operator.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2015 10:11:38 PM CST
 ************************************************************************/

#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<fstream>
#include<sstream>
using namespace std;

int main(void)
{
#if 0
    ifstream input("./C15-Energy65.txt");
    std::string line;
    std::string word = "我";
    std::size_t alength = word.size();
    //fread(&line, alength, 100, input);
    read(input, &line, alength*100);
    std::cout<<"***********line************"<<std::endl;
    std::cout<<line<<std::endl;
#endif

    FILE* fp = fopen("./C15-Energy65.txt", "r");
    if(!fp)
    {
        perror("fopen");
        exit(-1);
    }
    std::string line;
    while(getline(fp, line))
    {
        std::cout<<line;
    }

    return 0;
}

