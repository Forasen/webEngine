/*************************************************************************
	> File Name: test_intersection.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 29 Jul 2015 09:36:44 AM CST
 ************************************************************************/

#include<iostream>
#include<iterator>
#include<algorithm>
#include<set>
#include<vector>
#include<map>
#include<utility>
using namespace std;

int main(void)
{
    map1.insert(std::make_pair("hello", 1));
    map1.insert(std::make_pair("world", 2));
    map1.insert(std::make_pair("how", 3));
    map2.insert(std::make_pair("wo", 222));
    map2.insert(std::make_pair("ni",1));
    map2.insert(std::make_pair("hello", 222));
    for(auto it1: map1)
    {
        std::cout<<it1.first<<"\t"<<it1.second<<std::endl;
    }
    std::cout<<"---------------------------"<<std::endl;
    for(auto it1: map2)
    {
        std::cout<<it1.first<<"\t"<<it1.second<<std::endl;
    }

    std::map<std::string, int> map1;
    std::map<std::string, int> map2;

    std::vector<std::string, int> vec;

    std::set_intersection(map1.begin(), map1.end(),
                          map2.begin(), map2.end(),
                          std::back_inserter(vec));



    std::cout<<"***********the result*************"<<std::endl;
    for(auto it: vec)
    {
        std::cout<<it.first<<"\t"<<it.second<<std::endl;
    }
    return 0; 
}
