/*************************************************************************
  > File Name: ./test_space.cpp
  > Author: 
  > Mail: 
  > Created Time: Wed 22 Jul 2015 01:53:24 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main(void)
{

    std::string line = " + test string";

    std::string word;
    int index = 0;
    int location = 0;
    int num_space = 0;
    bool start_flag = true;
    for(auto it: line)
    {
        if(isspace(it) && start_flag)
        {
            num_space++;
            index++;
        }
        if(!isspace(it))
        {
            start_flag = false;
        }
        if(isalpha(it))
        {
            break;
        }
        location++;
    }
    for(int ind=location; ind!=line.size(); ind++)
    {
        word += line[ind];
    }
    std::cout<<"location="<<location<<std::endl;
    std::cout<<"num_space="<<num_space<<std::endl;
    std::cout<<"index="<<index<<std::endl;
    std::cout<<"word:("<<word.size()<<") : "<<word<<std::endl;


    return 0;
}
