/*********************************************
> File  : test_leetcode1.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Fri 17 Jul 2015 04:01:50 PM CST
 ********************************************/

#include<iostream>

int main(void)
{
    int row_num = 5;
    int col_num = 2;
    int** arr = new int*[row_num];
    for(int index=0; index<row_num; index++)
    {
        arr[index] = new int[col_num];
    }
    int ret  = sizeof(arr) / sizeof(arr[0][0]);
    std::cout<<"sizeof(arr) = "<<sizeof(arr)<<std::endl;
    std::cout<<"sizeof(arr[0][0]) = "<<sizeof(arr[0][0])<<std::endl;
    std::cout<<"ret = "<<ret<<std::endl;

    int** arr = new int*[row_num];

    int cnt = 0;
    for(int index=0; index<row_num; index++)
    {
        for(int index_j=0; index_j<col_num; index_j++)
        {
            arr[index][index_j] = cnt++;
        }
    }
    for(int index=0; index<5; index++)
    {
        for(int index_j=0; index_j<col_num; index_j++)
        {
            std::cout<<arr[index][index_j]<<"\t";
        }
        std::cout<<std::endl;
    }
    return 0;
}
