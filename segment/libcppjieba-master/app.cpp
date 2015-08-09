/*************************************************************************
  > File Name: ./app.cpp
  > Author: 
  > Mail: 
  > Created Time: Mon 03 Aug 2015 10:13:19 AM CST
 ************************************************************************/

#include<iostream>
int a = 10;
std::string  str("hello");

CppJieba::Application app("./dict/jieba.dict.utf8",
        "./dict/hmm_model.utf8",
        "./dict/user.dict.utf8",
        "./dict/idf.utf8",
        "./dict/stop_words.utf8");

using namespace std;

void test()
{
    app.cut(std::string, std::vector<std::string>)
    {
        
    }
}
