/*************************************************************************
	> File Name: ./test/test_isStopList.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 24 Jul 2015 05:42:09 PM CST
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<fstream>
#include<sstream>
#include<set>
#include<cstring>

using namespace std;

            bool is_stopword(std::string aword)
            {
                std::cout<<"calling is_stopword function!!!!!!!!!!!!!!!!!!!!"<<std::endl;
                std::ifstream input_stopList("../filedata/stopList.txt");
                if(!input_stopList)
                {
                    perror("input_stopList");
                    exit(-1);
                }
                std::ofstream output_stopList("../filedata/stopList2.txt");
                if(!output_stopList)
                {
                    std::cout<<"exit"<<std::endl;
                    exit(-1);
                }
                std::set<std::string> set_stopword;
                std::string word;
                while(getline(input_stopList, word))
                {
                    //std::cout<<word<<std::endl;
                    set_stopword.insert(word);
                    output_stopList<<word;
                    output_stopList<<"\n";
                }
                if(set_stopword.find(aword) == set_stopword.end())
                {
                    return false;
                }
                std::cout<<"return true;"<<std::endl;
                return true;
            }


int main(void)
{
    std::cout<<"Enter a word:";
    std::string word;
    std::cin>>word;
    bool flag = is_stopword(word);
    if(flag)
    {
        std::cout<<"Congratulation! the word is exists! word is:"<<word<<std::endl;
    }
    std::cout<<"flag:"<<flag<<std::endl;


    return 0;
}
