/*************************************************************************
> File Name: generateSpellCheckDict.h
> Author: 
> Mail: 
> Created Time: Sat 01 Aug 2015 11:10:11 PM CST
************************************************************************/

#ifndef _GENERATESPELLCHECKDICT_H
#define _GENERATESPELLCHECKDICT_H

#include<cctype>
#include<iostream>
#include<set>
#include<fstream>
#include<sstream>
#include<cstring>

class generateSpellCheckDict
{
    public:
    void handle()
    {
        std::ifstream input("./test_generate_page/invertindex.lib");
        //std::ifstream input("./1.txt");
        if(!input)
        {
            std::cout<<"input generateSpellCheckDict error!"<<std::endl;
            exit(-1);
        }

        std::string  line;
        int cnt = 0;
        std::set<std::string> tmp_set;
        while(getline(input, line))
        {
            std::stringstream ss(line);
            std::string word;
            ss >> word;

            if(!isdigit(word[0]) && !isspace(word[0]))
            {
                tmp_set.insert(word);
            }
            cnt++;
            continue;
        }
        std::cout<<"cnt = "<<cnt<<std::endl;

        std::cout<<"tmp_set.size="<<tmp_set.size()<<std::endl;
        std::ofstream output("./filedata/dict.dat");
        //std::ofstream output("./2.txt");
        if(!output)
        {
            std::cout<<"output dict.dat error!"<<std::endl;
            exit(-1);
        }
        for(auto it: tmp_set)
        {
            output << it;
            output << "\n";
        }

    }
};
#endif

int main(void)
{
    generateSpellCheckDict gscd;
    gscd.handle();

    return 0;
}
