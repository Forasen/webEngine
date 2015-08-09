/*********************************************
> File  : wordSplit.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/

#include<iostream>

#include "../include/seg_split.h"

std::string wordSplit(std::string str)
{
    std::vector<std::string> split_words;
    seg.cut(str, split_words);
    std::string sResult;
    for(auto it: split_words)
    {
        sResult += it;
        sResult += " ";
    }
    return sResult;
}
