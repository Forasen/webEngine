/*********************************************
> File  : output_file.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Tue 21 Jul 2015 11:25:01 PM CST
 ********************************************/

#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;
int main(void)
{
    ifstream input("./scandir.dat");
    std::string line;
    if(input){
        while(getline(input, line))
        {
            std::cout<<line<<std::endl;
        }
    }
    //shutdown(input, SHUT_RDWR);
    input.close();
    std::cout<<"***********************"<<std::endl;
    ifstream input_1("./scandir.dat");
    std::string line_1;
    if(input_1){
        while(getline(input_1, line_1))
        {
            std::cout<<line_1<<std::endl;
        }
    }
    input_1.close();
    return 0;
}
