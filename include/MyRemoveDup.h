/*********************************************
  > File  : MyRemoveDup.h
  > Author: NewYork
  > Mail  : 2287794993@qq.com 
  > Time  : Sat 11 Jul 2015 10:47:13 PM CST
 ********************************************/

#ifndef _MYREMOVEDUP_H
#define _MYREMOVEDUP_H

#include<queue>
#include<unordered_map>
#include<utility>
#include<ctime>
#include<algorithm>
#include<iterator>

#include "MySplit.h"
#include "MyNewPages.h"
#include "MyOldPages.h"
#include "extractPage.h"

class MyRemoveDup
{
    public:
        MyRemoveDup()
        {
            m_new_map_split = mynewpages.getMapSplit();
            m_old_map_split = myoldpages.getMapSplit();
        }
        ~MyRemoveDup()
        {}
        std::map<int, std::vector<std::pair<std::string, int> > > getStatisticWord()
        {
            std::map<int, std::vector<std::pair<std::string, int> > > tmp_map_vec_article;
            for(auto it_first: m_old_map_split)
            {
                std::map<std::string, int> tmp_map_str;
                for(auto it_second: it_first.second)
                {
                    std::stringstream ss_word(it_second);

                    std::string word;
                    while(ss_word >> word)
                    {
                        tmp_map_str[word]++; 
                    }
                }
                std::multimap<int, std::string> tmp_invert;
                for(auto it_str: tmp_map_str)
                {
                    tmp_invert.insert(std::make_pair(it_str.second, it_str.first));
                }
                std::vector<std::pair<std::string, int> > tmp_vec;
                auto it_tmp_inv = tmp_invert.end();
                auto it_map_start = tmp_invert.begin();
                int count = 10;
                while(count)
                {
                    it_tmp_inv--;
                    count--;
                }
                for(; it_tmp_inv!=tmp_invert.end(); it_tmp_inv++)
                {
                    tmp_vec.push_back(std::make_pair(it_tmp_inv->second, it_tmp_inv->first));
                }
                tmp_map_vec_article[it_first.first] = tmp_vec;
            }
            return tmp_map_vec_article;
        }
        std::map<int, std::vector<std::pair<std::string, int> > > getStatisticWord_All()
        {
            std::map<int, std::vector<std::pair<std::string, int> > > tmp_map_vec_article;
            for(auto it_first: m_new_map_split)
            {
                std::map<std::string, int> tmp_map_str;
                for(auto it_second: it_first.second)
                {
                    std::stringstream ss_word(it_second);
                    std::string word;
                    while(ss_word >> word)
                    {
                        tmp_map_str[word]++; 
                    }
                }
                std::vector<std::pair<std::string, int> > tmp_vec(tmp_map_str.begin(), tmp_map_str.end());
                tmp_map_vec_article[it_first.first] = tmp_vec;
            }
            return tmp_map_vec_article;
        }
        void removeDup()
        {
            std::map<int, std::vector<std::pair<std::string, int> > > statistic_word = getStatisticWord();  
            std::map<int, std::set<std::string> > map_com;
            for(auto it: statistic_word)
            {
                std::set<std::string> set_com;
                for(auto it_1: it.second)
                {
                    set_com.insert(it_1.first);
                }
                map_com[it.first] = set_com;
            }
            for(auto it11=map_com.begin(); it11!=map_com.end(); it11++)
            {
                auto tmp_it = it11;
                auto it22 = ++tmp_it;
                if(it22 != map_com.end())
                {
                    while(it22 != map_com.end())
                    {
                        std::vector<std::string> tmp_vec_intersection;
                        std::set_intersection(it11->second.begin(), it11->second.end(),
                                it22->second.begin(), it22->second.end(),
                                std::back_inserter(tmp_vec_intersection));
                        if(tmp_vec_intersection.size() >= 6)
                        {
                            it22 = map_com.erase(it22);
                        }
                        else
                        {
                            it22++;
                        }
                    }
                }
            }
            std::ifstream input_offset("./test_generate_page/offset.lib");
            if(!input_offset)
            {
                perror("input_offset");
                exit(-1);
            }
            std::string line_offset;

            std::map<int, std::pair<int, int> > tmp_map_offset;
            while(getline(input_offset, line_offset))
            {
                std::string num_str;
                std::string offset_str;
                std::string size_str;
                std::stringstream ss(line_offset);
                ss >> num_str;
                ss >> offset_str;
                ss >> size_str;

                int num_int = atoi(num_str.c_str());
                int offset_int = atoi(offset_str.c_str());
                int size_int = atoi(size_str.c_str());

                std::pair<int, int> tmp_pair(std::make_pair(offset_int, size_int));
                tmp_map_offset[num_int] = tmp_pair;
            }
            std::cout<<"去重前网页总数："<<tmp_map_offset.size()<<std::endl;
            for(auto it1: tmp_map_offset)
            {
                auto del_offset = map_com.find(it1.first);
                if(del_offset == map_com.end())
                {
                    tmp_map_offset.erase(it1.first); 
                }
            }
            std::cout<<"去重后网页总数："<<tmp_map_offset.size()<<std::endl;
            std::vector<std::pair<int, std::string> > tmp_vec_pair_content;
            int doc_num = 0;
            int remove_cnt = 0;
            for(auto it_offset: tmp_map_offset)
            {
                remove_cnt++;
                int num_int = it_offset.first;
                int offset_int = it_offset.second.first;
                int size_int = it_offset.second.second;
                std::ifstream input_ripepage("./test_generate_page/ripepage.lib");
                if(!input_ripepage)
                {
                    perror("input_ripepage");
                    exit(-1);
                }
                input_ripepage.seekg(offset_int, std::fstream::beg);
                int curr_end_mark = offset_int + size_int;
                std::string real_curr_content;
                std::string line_content;
                int line_cnt = 0;
                doc_num++;
                while(getline(input_ripepage, line_content) && (input_ripepage.tellg()<=curr_end_mark))
                {
                    line_cnt++;
                    if(input_ripepage.tellg()<curr_end_mark)
                    {
                        line_content += '\n';
                    }
                    if(input_ripepage.tellg()==curr_end_mark)
                    {
                        line_content += " ";
                    }

                    real_curr_content += line_content;
                }
                tmp_vec_pair_content.push_back(std::make_pair(num_int, real_curr_content));
            }

            std::ofstream new_output_ripepage("./test_generate_page/new_ripepage.lib");
            if(!new_output_ripepage)
            {
                perror("new_output_ripepage");
                exit(-1);
            }
            ofstream new_output_offset("./test_generate_page/new_offset.lib");
            if(!new_output_offset)
            {
                perror("ofstream new_output_offset!");
                exit(-1);
            }
            int tmp_total_size = 0;
            int tmp_curr_size = 0;
            int offset_cnt = 0;
            int vec_cnt = 0;
            for(auto it: tmp_vec_pair_content)
            {
                vec_cnt++;
                tmp_curr_size = it.second.size();
                new_output_offset<<it.first<<"\t"<<tmp_total_size<<"\t"<<tmp_curr_size<<std::endl;
                tmp_total_size += tmp_curr_size;
                offset_cnt++;
                new_output_ripepage<<it.second<<std::endl;
            }
        }
    private:
        std::map<int, std::vector<std::string> > m_new_map_split;
        std::map<int, std::vector<std::string> > m_old_map_split;
        MyNewPages mynewpages;
        MyOldPages myoldpages;

};
#endif
