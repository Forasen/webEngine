/*************************************************************************
	> File Name: test_lines.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 29 Jul 2015 08:40:20 PM CST
 ************************************************************************/

#include<iostream>
#include<cstring>
using namespace std;

int main(void)
{
    std::string line = "nihao中国";
    std::cout<<"line.size="<<line.size()<<std::endl;

    line += "\n";
    std::cout<<"line.size="<<line.size()<<std::endl;
    //if(line[line.size()-1] == '\n')
    if(line[line.size()-1] == '\r')
    std::cout<<"最后一个是换行符"<<std::endl;

    return 0;
}
