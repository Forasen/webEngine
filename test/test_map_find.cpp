/*************************************************************************
	> File Name: test_map_find.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Jul 2015 05:27:22 PM CST
 ************************************************************************/

#include<iostream>
#include<set>
#include<iterator>
#include<map>
#include<utility>
#include<vector>
using namespace std;

int main(void)
{

    std::map<int, std::pair<int, std::string> > tmp_map;
    std::set<std::pair<int, std::string> > tmp_set;
    tmp_set.insert(std::make_pair(1, "hello"));
    tmp_set.insert(std::make_pair(2, "world"));
    tmp_set.insert(std::make_pair(3, "how"));
    
    int cnt = 10;
    for(auto it_1: tmp_set)
    {
        tmp_map[cnt] = it_1;
        cnt++;
    }

    std::cout<<"inside the map"<<std::endl;
    for(auto it: tmp_map)
    {
        std::cout<<it.first<<"\t"<<it.second.first<<"\t"<<it.second.second<<std::endl;
    }
    //for(auto& it_del: tmp_map)
    {
        int del_num = tmp_map.erase(10);
        std::cout<<"\n"<<"del_num="<<del_num<<std::endl;
    }
    for(auto it: tmp_map)
    {
        std::cout<<it.first<<"\t"<<it.second.first<<"\t"<<it.second.second<<std::endl;
    }
    //std::string find_1 = "hello";
    //auto find_1 = std::make_pair("hello");
    //auto it_2 = tmp_map.first.second.find(find_1);
    /*
    if(it_2 == tmp_map.end())
    {
        std::cout<<"error!"<<std::endl;
        exit(-1);
    }
    */
    //std::cout<<"the res find:"<<std::endl;
    //std::cout<<it_2->first.first<<"\t"<<it_2->first.second<<"\t"<<it_2->second<<std::endl;

}
