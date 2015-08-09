/*************************************************************************
	> File Name: test_wordSplit.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 03 Aug 2015 10:50:19 AM CST
 ************************************************************************/

#include<iostream>
#include<cstring>
std::string wordSplit(std::string& str);
using namespace std;

int main(void)
{
    std::string str = "我是中国人民银行";
    std::string res = wordSplit(str);
    std::cout<<"结果为："<<res<<std::endl;

    return 0;
}
