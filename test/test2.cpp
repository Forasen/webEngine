/*********************************************
> File  : test2.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Fri 17 Jul 2015 04:55:15 PM CST
 ********************************************/

//#include "NLPIR.h"
#include<iostream>
#include<stdio.h>
#include<string.h>
#include "NLPIR.h"

int main(int argc, char* argv[])
{
    char sSentence[2000];
    const char* sResult;
    //if(!NLPIR_Init("../../", UTF8_CODE))
    if(!NLPIR_Init("./", UTF8_CODE))
    {
        std::cout<<"error: Init!"<<std::endl;
        return -1;
    }
    std::cout<<"Input sentence now('q' to quit)!"<<std::endl;
    std::cin>>sSentence;
    while(strcmp(sSentence, "q") != 0)
    {
        sResult = NLPIR_ParagraphProcess(sSentence, 0);
        printf("%s\nInput string now('q') to quit!\n", sResult);
        std::cin>>sSentence;
    }

    memset(sSentence, 0, sizeof(sSentence));
    const char* pstr = "我是中国人";
    std::cout<<"sizeof(pstr) = "<<sizeof(pstr)<<std::endl;
    sResult = NLPIR_ParagraphProcess(pstr, 0);
    //std::stringstream (sResult);
    std::cout<<"sResult : "<<sResult<<std::endl;

    NLPIR_Exit();
    return 0;
}
