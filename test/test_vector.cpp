/*************************************************************************
	> File Name: test_vector.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 29 Jul 2015 08:47:18 AM CST
 ************************************************************************/

#include<iostream>
#include<set>
#include<vector>
using namespace std;

int main(void)
{
    int arr[5] = {1, 10, 4, 2, 9};
    std::vector<int> vec(arr, arr+5);
    //std::set<int> set1(arr, arr+5);
    for(auto it: vec)
    {
        std::cout<<it<<", ";
    }
    std::cout<<std::endl;

    return 0;
}
