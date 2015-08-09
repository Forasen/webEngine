/*************************************************************************
  > File Name: wordSplit.cpp
  > Author: 
  > Mail: 
  > Created Time: Mon 03 Aug 2015 10:25:27 AM CST
 ************************************************************************/

#include<iostream>
#include "./seg_split.h"

MixSegment seg(JIEBA_DICT_FILE, HMM_DICT_FILE, USER_DICT_FILE);

std::string wordSplit(std::string& str)
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
