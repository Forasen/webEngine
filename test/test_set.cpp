/*************************************************************************
	> File Name: test_set.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 23 Jul 2015 09:14:19 PM CST
 ************************************************************************/

#include<iostream>
#include<vector>
#include<set>
using namespace std;

int main(void)
{
#if 0
    std::set<std::string> set_str;
    std::string word;
    int cnt = 0;
    std::cout<<"Enter a word!"<<std::endl;
    while(cnt < 5)
    {
        std::cout<<"Enter a word!"<<std::endl;
        std::cin>>word;
        set_str.insert(word);
        cnt++;
    }
    for(auto it: set_str)
    {
        std::cout<<it<<" ";
    }
    std::cout<<std::endl;
#endif
    int arr[5] = {1, 2, 3, 4, 5};
    std::vector<int> vec(arr, arr+5);
    auto it = vec.begin();
    auto curr = (it+vec.size()-1);
    std::cout<<"int="<<*curr<<std::endl;

    return 0;
}
