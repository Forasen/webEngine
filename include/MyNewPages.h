/*********************************************
  > File  : MyNewPages.h
  > Author: NewYork
  > Mail  : 2287794993@qq.com 
  > Time  : Tue 21 Jul 2015 08:26:51 AM CST
 ********************************************/

#ifndef _MYNEWPAGES_H
#define _MYNEWPAGES_H

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

#include "MySplit.h"

std::string wordSplit(std::string);

using namespace std;

class MyNewPages
{
    public:
        MyNewPages()
        {
#if 1
            std::ifstream input_stopList("./../data/filedata/stopList_standard.txt");
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
#endif
        }
        ~MyNewPages()
        {
        }
        void newPageSplit()
        {
            std::ifstream input_original_offset("./test_generate_page/offset.lib");
            if(!input_original_offset)
            {
                perror("input_original_offset");
                exit(-1);
            }
            std::map<int, std::pair<int, int> > map_original_offset;
            int num_int;
            int offset_int;
            int size_int;
            while(input_original_offset >> num_int >> offset_int>> size_int)
            {
                map_original_offset[num_int] = std::make_pair(offset_int, size_int);
            }
            std::ifstream input_new_offset("./generate_page/new_offset.lib");
            if(!input_new_offset)
            {
                perror("input_new_offset");
                exit(-1);
            }
            int doc_cnt = 0;
            std::ifstream input_ripepage("./generate_page/ripepage.lib");
            if(!input_ripepage)
            {
                perror("input_ripepage");
                exit(-1);
            }
            std::map<int, std::vector<std::string> > pre_m_map_stoplist;
            clock_t begin88;
            clock_t end88;
            begin88 = clock();
            while(input_new_offset >> num_int >> offset_int >> size_int)
            {
                doc_cnt++;
                auto it_new_original = map_original_offset.find(num_int);
                if(it_new_original == map_original_offset.end())
                {
                    std::cout<<"Sorry! the new_offset docid not exist int original offset.lib"<<std::endl;
                    exit(-1);
                }
                std::string curr_content;
                std::string real_curr_content;
                std::string line_content;

                int line_cnt = 0;

                input_ripepage.seekg(it_new_original->second.first, std::fstream::beg);
                int curr_end_mark = it_new_original->second.first + it_new_original->second.second;
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
                clock_t end99 = clock();
                double clock_res99 = (double)(end99 - begin) / CLOCKS_PER_SEC;
                if(count % 100 == 0)
                {
                    std::cout<<"处理完"<<count<<"篇文章用时："<<clock_res99<<"s"<<std::endl;
                }
            }
            end = clock();
            double clock_res3 = (double)(end - begin) / CLOCKS_PER_SEC;
            std::cout<<"（去重后的网页库）处理完"<<doc_cnt<<"篇文章共耗时："<<clock_res3<<std::endl;
        }

        std::map<int, std::vector<std::string> > getMapSplit()
        {
            newPageSplit();
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
