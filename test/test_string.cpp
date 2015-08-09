/*************************************************************************
> File Name: test_string.cpp
> Author: 
> Mail: 
> Created Time: Wed 29 Jul 2015 05:35:01 PM CST
************************************************************************/

#include<iostream>
using namespace std;

std::size_t nBytesCode(const char ch)
{
    std::size_t nBytes = 0;
    if(ch & (1 << 7))
    {
        if((ch & 0xF0)==0xC0 || (ch & 0xF0) == 0xD0)
        {
            nBytes = 2;
        }
        else if((ch & 0xF0) == 0xE0)
        {
            nBytes = 3;
        }
        else if((ch & 0xF0) == 0xF0)
        {
            nBytes = 4;
        }
        else if((ch & 0xFF) == 0xFE)
        {
            nBytes = 6;
        }
    }
    else 
    {
        nBytes = 1;
    }
    return nBytes;
}
int main(void)
{
    std::string str = "我是中国人";
    std::string line;
    for(auto it: str)
    {
        line += it;
        //std::cout<<it<<std::endl;
    }
    std::cout<<"line:"<<line<<std::endl;


    std::string s1 = ",";
    std::string s2 = "，";
    std::cout<<"s1="<<s1.size()<<std::endl;
    std::cout<<"s2="<<s2.size()<<std::endl;
    return 0;
}
