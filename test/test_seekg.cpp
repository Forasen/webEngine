/*************************************************************************
	> File Name: test_seekg.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 30 Jul 2015 10:24:25 AM CST
 ************************************************************************/

#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;

int main(void)
{
    std::ifstream input("../test_generate_page/new_offset.lib");
    if(!input)
    {
        std::cout<<"error: input!"<<std::endl;
        exit(-1);
    }

    std::ifstream input_ripepage("../test_generate_page/new_ripepage.lib");
    if(!input_ripepage)
    {
        std::cout<<
    }
}
