/*********************************************
  > File  : MyWebSort.h
  > Author: NewYork
  > Mail  : 2287794993@qq.com 
  > Time  : Sat 11 Jul 2015 10:47:13 PM CST
 ********************************************/

#ifndef _MYWEBSORT_H
#define _MYWEBSORT_H

#include<fstream>
#include<sstream>
#include<iostream>
#include<map>
#include<iterator>
#include<vector>
#include<set>
#include<utility>

#include "extractPage.h"
#include "MyInvertIndex.h"
#include "MyRemoveDup.h"

#include "MyNewPages.h"
#include "MySplit.h"
#include "MyJson.h"

class MyWebSort
{
    public:
        MyWebSort()
        {}
        ~MyWebSort()
        {}

        std::map<std::string, std::map<int, std::pair<int, double> > > readInvertIndex(std::string invertfilename)
        {
            std::ifstream input_invert(invertfilename);
            if(!input_invert)
            {
                perror("input_invert");
                exit(-1);
            }

            std::map<std::string, std::map<int, std::pair<int, double> > > tmp_map_invert_index;

            std::string line_invert;
            while(getline(input_invert, line_invert))
            {
                std::stringstream ss_invert(line_invert);
                std::string tmp_word;

                ss_invert >> tmp_word;

                std::string docid_str;
                std::string freq_str;
                std::string weight_str;

                std::map<int, std::pair<int, double> > tmp_map_mid;

                while(ss_invert >> docid_str >> freq_str >> weight_str)
                {
                    int docid_int = atoi(docid_str.c_str());
                    int freq_int = atoi(freq_str.c_str());
                    double weight_double = atof(weight_str.c_str());

                    tmp_map_mid[docid_int] = std::make_pair(freq_int, weight_double);
                }
                tmp_map_invert_index[tmp_word] = tmp_map_mid;
            }


            int circulation_cnt = 0;

            std::cout<<"整个网页库的词语总数："<<tmp_map_invert_index.size()<<std::endl;

            return tmp_map_invert_index;

        }
        std::string handleSearch(std::string task_str)
        {
            std::map<std::string, std::string> search_docs_map;

            clock_t begin;
            clock_t end;
            begin = clock();

            MySplit mysplit;
            MyJson myjson;

            std::stringstream ss_task(task_str);
            std::string task_word;

            std::map<std::string, int> task_map_content;
            std::vector<std::string> task_vec_original_words;
            while(ss_task >> task_word)
            {
                    task_map_content[task_word]++;
                    task_vec_original_words.push_back(task_word);
            }
            std::map<std::string, std::pair<int, double> > task_invertindex;
            int words_cnt = task_map_content.size();
            for(auto it_task: task_map_content)
            {
                double task_idf = log((double)1 / (0.000001 + it_task.second));
                double task_weight = task_idf * it_task.second;
                task_invertindex[it_task.first] = std::make_pair(it_task.second, task_weight);
            }
            std::string invertfile_name = "./test_generate_page/invertindex.lib";
            std::map<std::string, std::map<int, std::pair<int, double> > > words_map_inverindex 
                = readInvertIndex(invertfile_name);
            std::map<std::string, std::set<int> > word_article;

            for(auto it_task: task_invertindex)
            {
                auto it_find = words_map_inverindex.find(it_task.first);
                if(it_find == words_map_inverindex.end())
                {
                    std::cout<<"Sorry! not find the task word!"<<std::endl;
                    return myjson.resNull();
                    exit(-1);
                }
                std::set<int> tmp_set_docid;
                for(auto it_invertindex: it_find->second)
                {
                    tmp_set_docid.insert(it_invertindex.first);
                }
                word_article[it_task.first] = tmp_set_docid; 
            }
            std::vector<int> tmp_vec_intersection;
            for(auto it_res=word_article.begin(); it_res!=word_article.end(); it_res++)
            {
                if(it_res == word_article.begin())
                {
                    for(auto it_beg: it_res->second)
                    {
                        tmp_vec_intersection.push_back(it_beg);
                    }
                    continue;
                }
                std::vector<int> vec_mid;
                std::set_intersection(tmp_vec_intersection.begin(), tmp_vec_intersection.end(),
                        it_res->second.begin(), it_res->second.end(),
                        std::back_inserter(vec_mid));    

                tmp_vec_intersection.clear();
                tmp_vec_intersection = vec_mid;
                if(vec_mid.size() == 0)
                {
                    std::cout<<"error: no search information! exit..."<<std::endl;
                }
            }
            std::map<int, std::set<std::pair<std::string, double> > > all_docs_query;
            for(auto it_docid: tmp_vec_intersection)
            {
                std::set<std::pair<std::string, double> > doc_res;
                for(auto it11: word_article)
                {
                    auto it_word = words_map_inverindex.find(it11.first);
                    if(it_word == words_map_inverindex.end())
                    {
                        perror("error: query words not found!");
                        exit(-1);
                    }
                    auto it_article = it_word->second.find(it_docid);

                    if(it_article == it_word->second.end())
                    {
                        perror("error: the article of query words not found!");
                        exit(-1);
                    }
                    doc_res.insert(std::make_pair(it11.first, it_article->second.second));
                }
                all_docs_query[it_docid] = doc_res;
            }
            std::map<double, int> query_result;
            for(auto it_all: all_docs_query)
            {
                if(it_all.second.size() != task_invertindex.size())
                {
                    std::cout<<"error! the count of datas not equal!!!!"<<std::endl;
                    exit(-1);
                }
                double member = 0;
                double denominator_query = 0;
                double denominator_lib = 0;
                auto it_query=task_invertindex.begin();
                auto it_lib=it_all.second.begin();
                for(; it_query!=task_invertindex.end(), it_lib!=it_all.second.end();it_query++, it_lib++)
                {
                    member += it_query->second.second * it_lib->second;
                    denominator_query += pow(it_query->second.second, 2);
                    denominator_lib += pow(it_lib->second, 2);
                }
                denominator_query = sqrt(denominator_query);
                denominator_lib = sqrt(denominator_lib);
                double cosine = (double)member / ((denominator_query * denominator_lib));
                query_result[cosine] = it_all.first;
            }

            int doc_cnt = 0;
            int arr_docid[query_result.size()];
            int arr_index = query_result.size() - 1;
            int index_end = arr_index;

            for(auto it: query_result)
            {
                arr_docid[arr_index--] = it.second; 
                if(arr_index < -1)
                {
                    std::cout<<"error: arr_index too small!"<<std::endl;
                }
            }
            std::string return_str;

            for(int index=0; index<=index_end; index++)
            {
                doc_cnt++;
                if(doc_cnt > 8)
                {
                    break;
                }
                auto summary_pair = mysplit.backup_getSummary(arr_docid[index], 
                        4, task_vec_original_words, doc_cnt);
                std::string return_str = summary_pair.second;

                search_docs_map[summary_pair.first] = return_str; 
            }
            end = clock();
            double T = (double)(end - begin) / CLOCKS_PER_SEC;
            std::string time_str;

            char* time_suffix =" ------------------------";
            char time_str_char[1024];
            char* tmp_str_run = "程序运行时间：";
            memset(time_str_char, 0, sizeof(time_str_char));
            sprintf(time_str_char, "%s\n%s%lf\n%s\n", time_suffix, tmp_str_run, T, time_suffix);
            
            return_str += time_str_char;

            if(search_docs_map.size() > 0)
            {
                return myjson.json_handle(search_docs_map);
            }
            else
            {
                return myjson.resNull();
            }
        }
};
#endif
