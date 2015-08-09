/*************************************************************************
	> File Name: test_pair.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 26 Jul 2015 10:05:20 AM CST
 ************************************************************************/

#include<utility>
#include<algorithm>
#include<set>
#include<cstring>
#include<vector>
#include<iterator>
#include<iostream>
using namespace std;

int main(void)
{
    /*
    std::pair<int, std::string> tmp(std::make_pair(1, "hello"));
    std::cout<<tmp.first<<", "<<tmp.second<<std::endl;

    std::vector<std::pair<int, std::string> > vec;
    vec.push_back(tmp);
    std::cout<<"display vec"<<std::endl;
    for(auto it=vec.begin(); it!=vec.end(); it++)
    {
        std::cout<<it->first<<"\t"<<it->second<<std::endl;
        it->
    }
    */
    std::set<std::string> set1 = {"我是", "你好", "你们", "中国", "美国"};
    std::set<std::string> set2 = {"我和", "你啦", "你们", "中美", "美国"};
    std::cout<<"set1...";
    for(auto it1: set1)
    {
        std::cout<<it1<<", ";
    }
    std::cout<<std::endl;
    std::cout<<"set2...";
    for(auto it2: set2)
    {
        std::cout<<it2<<", ";
    }
    std::cout<<std::endl;
    std::vector<std::string > vec;
    std::set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), std::back_inserter(vec));
    std::cout<<"vec.size="<<vec.size()<<std::endl;
    std::cout<<"intersection...";
    for(auto it3: vec)
    {
        std::cout<<it3<<", ";
    }
    std::cout<<std::endl;

    return 0;
}
