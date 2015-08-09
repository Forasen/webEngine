/*********************************************
  > File  : MyOldPages.h
  > Author: NewYork
  > Mail  : 2287794993@qq.com 
  > Time  : Tue 21 Jul 2015 08:26:51 AM CST
 ********************************************/

#ifndef _MYOLDPAGES_H
#define _MYOLDPAGES_H

#include<iostream>
#include<ctype.h>
#include<stdlib.h>
#include<iterator>
#include<string.h>
#include<fstream>
#include<sstream>
#include<set>
#include<vector>
#include<map>
#include<sys/types.h>

#include "./MySplit.h"

std::string wordSplit(std::string);

class MyOldPages
{
    public:
    MyOldPages()
    {
        std::ifstream input_stopList("./filedata/stopList_standard.txt");
        if(!input_stopList)
        {
            perror("input_stopList");
            exit(-1);
        }
        std::string word;
        while(input_stopList >> word)
        {
            m_set_stopword.insert(word);
        }
    }
    ~MyOldPages()
    {
    }

    void oldPageSplit()
    {
        std::ifstream input_old_offset("./test_generate_page/offset.lib");
        if(!input_old_offset)
        {
            perror("input_old_offset");
            exit(-1);
        }
        int doc_cnt = 0;

        std::ifstream input_ripepage("./test_generate_page/ripepage.lib");
        if(!input_ripepage)
        {
            perror("input_ripepage");
            exit(-1);
        }
        std::map<int, std::vector<std::string> > pre_m_map_stoplist;

        int num_int;
        int offset_int;
        int size_int;

        while(input_old_offset >> num_int >> offset_int >> size_int)
        {
            doc_cnt++;

            std::string curr_content;
            std::string real_curr_content;
            std::string line_content;
            int line_cnt = 0;

            input_ripepage.seekg(offset_int, std::fstream::beg);
            int curr_end_mark = offset_int + size_int;
            while(getline(input_ripepage, line_content) && ((input_ripepage.tellg()+19)<=curr_end_mark))
            {
                line_cnt++;
                std::string real_line_content;
                for(auto it: line_content)
                {
                    if(!isspace(it))
                    {
                        real_line_content += it;
                    }
                }
                if(line_cnt >= 6)
                {
                    real_curr_content += real_line_content;
                }
            }
            std::vector<std::string> tmp_vec_content;
            tmp_vec_content.push_back(real_curr_content);
            pre_m_map_stoplist[num_int] = tmp_vec_content;
        }
clock_t begin, end;
            begin = clock();

            end = clock();
            double clock_res1 = (double)(end - begin) / CLOCKS_PER_SEC;
            begin = clock();

            int count = 0;
            int count2 = 0;
            for(auto it1: pre_m_map_stoplist)
            {
                count++;
                for(auto it2: it1.second)
                {
                    std::string tmp_str = wordSplit(it2);

                    std::vector<std::string> tmp_vec_content1;
                    tmp_vec_content1.push_back(tmp_str);

                    m_map_stoplist[it1.first] = tmp_vec_content1;
                }
            }
            end = clock();
            double clock_res3 = (double)(end - begin) / CLOCKS_PER_SEC;

            std::cout<<"（原网页库）处理完"<<doc_cnt<<"篇文章共耗时："<<clock_res3<<std::endl;
        }

        std::map<int, std::vector<std::string> > getMapSplit()
        {
            oldPageSplit();
            return m_map_stoplist;
        }
private:
        bool is_stopword(std::string aword)
        {
            if(m_set_stopword.find(aword) == m_set_stopword.end())
            {
                return false;
            }
            else
            {

                return true;
            }
        }
private:
        std::map<int, std::vector<std::string> > m_map_stoplist;
        std::set<std::string> m_set_stopword;
        MySplit mysplit;
};
#endif
