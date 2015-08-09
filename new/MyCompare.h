/*********************************************
> File  : MyCompare.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:49:13 PM CST
 ********************************************/

#ifndef _MYCOMPARE_H
#define _MYCOMPARE_H

#include "MyResult.h"
class MyCompare
{
public:
    bool operator()(const MyResult& lhs, const MyResult& rhs)
    {
        if(lhs.m_dist > rhs.m_dist)
        {
            return true;
        }
        else if((lhs.m_dist==rhs.m_dist) && (lhs.m_freq < rhs.m_freq))
        {
            return true;
        }
        else if((lhs.m_dist==rhs.m_dist)&&(rhs.m_freq==lhs.m_freq)&&(lhs.m_word > rhs.m_word))
        {
            return 0;
        }
        else
        {
            return false;
        }
    }
};



#endif
