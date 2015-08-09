/*************************************************************************
> File Name: test_lenght.cpp
> Author: 
> Mail: 
> Created Time: Sat 25 Jul 2015 09:28:55 PM CST
************************************************************************/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<cstring>

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
    /*
    //std::string str;
    char str;
    std::cout<<"Enter a string(chinese):";
    std::cin>>str;
    //std::cout<<"strlen(str)="<<strlen(str)<<std::endl;
    std::size_t ch_len = nBytesCode(str);
    std::cout<<"ch_len="<<ch_len<<std::endl;
    //std::size_t len = strlen(str) / sizeof(*str);
    //std::cout<<"len="<<len<<std::endl;
    for(std::size_t index=0; index!=strlen(str); index++)
    {
        std::cout<<str[index]<<std::endl;
    }
    */
    wchar_t ch = L'中国';
    printf("和的UTF-8编码为:%.4x\n", (unsigned short)ch);
    return 0;
}
