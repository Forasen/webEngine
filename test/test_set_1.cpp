/*************************************************************************
	> File Name: test_set_1.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 29 Jul 2015 10:22:03 AM CST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

int main(void)
{
    std::set<std::pair<string, int> > set_pair;
    set_pair.insert(std::make_pair("bbb", 1));
    set_pair.insert(std::make_pair("ccc", 2));
    set_pair.insert(std::make_pair("aaa", 3));

    std::cout<<"set_pair"<<std::endl;
    for(auto it: set_pair)
    {
        std::cout<<it.first<<"\t"<<it.second<<std::endl;
    }
    return 0;
}

#if 0
void test()
{
    std::set<int> set1;
    for(int index=0; index<5; index++)
    {
        set1.insert(index);
    }
    for(auto it:set1)
    {
        std::cout<<it<<", ";
    }
    std::cout<<std::endl;

    std::set<int> set2 = set1;
    std::cout<<"set2..."<<std::endl;
    for(auto it2: set2)
    {
        std::cout<<it2<<"\t";
    }
    std::cout<<std::endl;

    //std::set<int> set3;
    std::vector<int> set3;
    std::set_intersection(set1.begin(), set1.end(),
                         set2.begin(), set2.end(),
                         back_inserter(set3));

    std::cout<<"set_intersection vec3..."<<std::endl;
    for(auto it3: set3)
    {
        std::cout<<it3<<",   ";
    }
    std::cout<<std::endl;
    std::cout<<"----------------------------------------"<<std::endl;
    //std::vector<int> vec4(set3.begin(), set3.end());
    std::vector<int> vec4;
    //vec4.insert(set3.begin(), set3.end());
    for(auto it3: set3)
    vec4.push_back(it3);
    std::cout<<"vec4(set.begin, end)"<<std::endl;
    for(auto it_vec: vec4)
    {
        std::cout<<it_vec<<",      ";
    }
    std::cout<<std::endl;

}
#endif
