/*************************************************************************
	> File Name: test_vector.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 25 Jul 2015 07:16:06 PM CST
 ************************************************************************/

#include<iostream>
#include<map>
#include<unordered_map>
#include<vector>
using namespace std;


int main(void)
{
/*
    int  arr[5] = {9, 1, 3, 2, 6};
    std::vector<int> vec(arr, arr+5);

    for(auto it: vec)
    {
        std::cout<<it<<", ";
    }
    std::cout<<std::endl;
*/
    std::map<int, std::string> m;
    m.insert(std::make_pair(3, "str33"));
    m.insert(std::make_pair(2, "str22"));
    m.insert(std::make_pair(9, "str99"));
    m.insert(std::make_pair(1, "str11"));

    for(auto it: m)
    {
        std::cout<<it.first<<"\t"<<it.second<<std::endl;
    }
    std::cout<<"***********************"<<std::endl;

    std::unordered_map<int, std::string> invert_map(m.begin(), m.end());
    for(auto it: invert_map)
    {
        std::cout<<it.first<<"\t"<<it.second<<std::endl;
    }

    return 0;
}
