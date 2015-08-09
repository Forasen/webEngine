/*********************************************
> File  : MySplit.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 20 Jul 2015 07:20:58 PM CST
********************************************/

#ifndef _MYSPLIT_H
#define _MYSPLIT_H

#include<iostream>
#include<stdlib.h>
#include<iterator>
#include<string.h>
#include<fstream>
#include<sstream>
#include<set>
#include<vector>
#include<map>
#include<sys/types.h>

std::string wordSplit(std::string);

class MySplit
{
    public:
    MySplit()
    {
    }
    ~MySplit()
    {
    }
    void pageSplit()
    {
        std::ifstream input_offset("./test_generate_page/offset.lib");
        if(!input_offset)
        {
            perror("input_offset");
            exit(-1);
        }
        std::string line_offset;
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

            std::ifstream input_ripepage("./test_generate_page/ripepage.lib");

            if(!input_ripepage)
            {
                perror("input_ripepage");
                exit(-1);
            }
            input_ripepage.seekg(offset_int, std::fstream::beg);

            int curr_end_mark = offset_int + size_int;
            std::string curr_content;
            std::string real_curr_content;
            std::string line_content;

            int content_size = 0;
            std::vector<std::string> tmp_vec_content;
            int line_cnt = 0;
            while(getline(input_ripepage, line_content) && ((input_ripepage.tellg()+19)<=curr_end_mark))
            {
                line_cnt++;
                curr_content += line_content;
                content_size += line_content.size();
                if(content_size == size_int)
                {
                    std::cout<<"content_size==size_int->break!(inside the MySplit.h)"<<std::endl;
                    break;
                }

                std::string real_line_content;
                if(line_cnt >= 6)
                {
                    for(auto it: line_content)
                    {
                        if(!isspace(it))
                        {
                            real_line_content += it;
                        }
                    }
                    tmp_vec_content.push_back(real_line_content);
                }
            }
            m_map_stoplist.insert({num_int, tmp_vec_content});

                }
                int for_cnt = 0;

            clock_t begin, begin1;
            clock_t end;
            begin = clock();
            begin1 = clock();
            for(auto& it_first: m_map_stoplist)
            {
                for_cnt++;
                std::string tmp_article;
                for(auto it_second: it_first.second)
                {
                    tmp_article += it_second;
                }
                std::string tmp_res = wordSplit(tmp_article);

                std::stringstream ss_res(tmp_res);
                std::string tmp_word;
                std::string tmp_content;
                while(ss_res >> tmp_word)
                {
                    if(!is_stopword(tmp_word))
                    {
                        tmp_content += tmp_word; 
                        tmp_content += " ";
                    }
                }
                it_first.second.clear();
                it_first.second.push_back(tmp_content);
                if(for_cnt % 20 == 0)
                {
                    end = clock();
                    double time1 = (double)(end-begin) / CLOCKS_PER_SEC;
                    begin = end;
                    std::cout<<"handle for_cnt="<<for_cnt<<", TIME = "<<time1<<std::endl;
                }
            }
            clock_t end_2;
            end_2 = clock();
            double time_for = (double)(end_2-begin1) / CLOCKS_PER_SEC;
            std::cout<<"TOTAL TIME(for circulation)="<<time_for<<std::endl;

            std::cout<<"m_map_stoplist.size(已分词的文章总数)="<<m_map_stoplist.size()<<std::endl;
            }
            void new_pageSplit()
            {
                std::ifstream input_offset("./test_generate_page/new_offset.lib");
                if(!input_offset)
                {
                    perror("input_offset");
                    exit(-1);
                }
                std::string line_offset;
                int cnt_tmp = 0;
                while(getline(input_offset, line_offset))
                {
                    cnt_tmp++;
                    std::string num_str;
                    std::string offset_str;
                    std::string size_str;
                    std::stringstream ss(line_offset);
                    ss >> num_str;
                    ss >> offset_str;
                    ss >> size_str;
                    std::cout<<"num_str:"<<num_str<<", "<<"offset_str:"
                    <<offset_str<<", "<<"size_str:"<<size_str<<std::endl;

                    int num_int = atoi(num_str.c_str());
                    int offset_int = atoi(offset_str.c_str());
                    int size_int = atoi(size_str.c_str());
                    std::ifstream input_ripepage("./test_generate_page/new_ripepage.lib");

                    if(!input_ripepage)
                    {
                        perror("input_ripepage");
                        exit(-1);
                    }
                    input_ripepage.seekg(offset_int, std::fstream::beg);
                    int curr_end_mark = offset_int + size_int;

                    std::string curr_content;
                    std::string real_curr_content;
                    std::string line_content;

                    int content_size = 0;
                    std::vector<std::string> tmp_vec_content;
                    int line_cnt = 0;
                    while(getline(input_ripepage, line_content) && ((input_ripepage.tellg()+19)<=curr_end_mark))
                    {
                        line_cnt++;
                        curr_content += line_content;
                        content_size += line_content.size();

                        if(content_size == size_int)
                        {
                            std::cout<<"content_size==size_int->break!(inside the MySplit.h)"<<std::endl;
                            break;
                        }

                        std::string real_line_content;
                        if(line_cnt >= 6)
                        {
                            for(auto it: line_content)
                            {
                                if(!isspace(it))
                                {
                                    real_line_content += it;
                                }
                            }
                            tmp_vec_content.push_back(real_line_content);
                        }
                    }
            m_map_stoplist.insert({num_int, tmp_vec_content});
            }
            int for_cnt = 0;

            clock_t begin, begin1;
            clock_t end;
            begin = clock();
            begin1 = clock();
            for(auto& it_first: new_m_map_stoplist)
            {
                for_cnt++;
                std::string tmp_article;

                for(auto it_second: it_first.second)
                {
                    tmp_article += it_second;
                }
                std::string tmp_res = wordSplit(tmp_article);
                std::stringstream ss_res(tmp_res);
                std::string tmp_word;

                std::string tmp_content;
                while(ss_res >> tmp_word)
                {
                    if(!is_stopword(tmp_word))
                    {
                        tmp_content += tmp_word; 
                        tmp_content += " ";
                    }
                }
                it_first.second.clear();
                it_first.second.push_back(tmp_content);

                if(for_cnt % 20 == 0)
                {
                    end = clock();
                    double time1 = (double)(end-begin) / CLOCKS_PER_SEC;
                    begin = end;
                    std::cout<<"handle for_cnt="<<for_cnt<<", TIME = "<<time1<<std::endl;
                }
            }
            clock_t end_2;
            end_2 = clock();
            double time_for = (double)(end_2-begin1) / CLOCKS_PER_SEC;
            std::cout<<"TOTAL TIME(for circulation)="<<time_for<<std::endl;

            std::cout<<"new_m_map_stoplist.size(已分词的文章总数)="<<new_m_map_stoplist.size()<<std::endl;
            }
            void extractNewPage()
            {
                std::cout<<"calling function: extractNewPage()"<<std::endl;
                std::ifstream input_offset("./test_generate_page/offset.lib");
                if(!input_offset)
                {
                    perror("input_offset");
                    exit(-1);
                }
                std::string line_offset;

                int remove_cnt = 0;
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

                    std::vector<std::string> tmp_vec_content;
                    int doc_num = 0;
                    remove_cnt++;

                    std::ifstream input_ripepage("./test_generate_page/ripepage.lib");
                    if(!input_ripepage)
                    {
                        perror("input_ripepage");
                        exit(-1);
                    }
                    input_ripepage.seekg(offset_int, std::fstream::beg);
                    int curr_end_mark = offset_int + size_int;
                    std::string curr_content;
                    std::string real_curr_content;
                    std::string line_content;

                    int content_size = 0;
                    int line_cnt = 0;

                    while(getline(input_ripepage, line_content) && ((input_ripepage.tellg()+19)<=curr_end_mark))
                    {
                        line_cnt++;
                        curr_content += line_content;
                        content_size += curr_content.size();

                        std::string real_line_content;
                        if(line_cnt == 6)
                        {
                            std::cout<<"第6行："<<line_content<<std::endl;
                        }
                        if(line_cnt >= 6)
                        {


                            for(auto it: line_content)
                            {
                                real_line_content += it;
                            }
                            real_curr_content += line_content;

                            if(input_ripepage.tellg()<curr_end_mark)
                            {
                                real_curr_content += "\n";
                            }
                        }
                        if(line_cnt == 6)
                        {
                            std::cout<<"第6行："<<line_content<<std::endl;
                        }
                    }
            if(remove_cnt == 8)
            {
                std::cout<<"real_curr_content: as following...第八(haha)篇\n"<<real_curr_content<<std::endl;
            }
            tmp_vec_content.push_back(real_curr_content);
            }
            }
            void extractNewPage_backup()
            {
                std::ifstream input_offset("./test_generate_page/new_offset.lib");
                if(!input_offset)
                {
                    perror("input_offset");
                    exit(-1);
                }
                std::string line_offset;
                int offset_cnt = -1;
                while(getline(input_offset, line_offset))
                {
                    offset_cnt++;
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

                    std::ifstream input_ripepage("./test_generate_page/new_ripepage.lib");
                    if(!input_ripepage)
                    {
                        perror("input_ripepage");
                        exit(-1);
                    }
                    input_ripepage.seekg(offset_int, std::fstream::beg);
                    std::cout<<"input_ripepage.tellg="<<input_ripepage.tellg()<<std::endl;

                    int curr_end_mark = offset_int + size_int;
                    std::string curr_content;
                    std::string real_curr_content;
                    std::string line_content;

                    int content_size = 0;
                    std::vector<std::string> tmp_vec_content;
                    int line_cnt = 0;
                    while(getline(input_ripepage, line_content) && ((input_ripepage.tellg()+19)<=curr_end_mark))
                    {
                        line_cnt++;
                        curr_content += line_content;
                        content_size += line_content.size();
                        if(content_size == size_int)
                        {
                            std::cout<<"content_size==size_int->break!(inside the MySplit.h)"<<std::endl;
                            break;
                        }
                        std::string real_line_content;
                        if(line_cnt >= 6)
                        {
                            std::stringstream ss(line_content);
                            std::string word;
                            while(ss >> word)
                            {
                                real_line_content += word;
                            }
                            tmp_vec_content.push_back(real_line_content);
                        }
                    }
            m_map_stoplist.insert({num_int, tmp_vec_content});
            input_ripepage.close();
            for(auto it: tmp_vec_content)
            {
                std::cout<<it;
            }    
            std::cout<<std::endl<<std::endl;
            }
            std::cout<<"分词前的文章"<<std::endl;
            for(auto it: m_map_stoplist)
            {
                if(it.first % 10 == 0)
                {

                    std::cout<<"article_num="<<it.first<<std::endl;
                    for(auto it2: it.second)
                    {
                        std::cout<<it2;
                    }
                    std::cout<<std::endl;
                }
            }
            int for_cnt = 0;
            for(auto& it_first: m_map_stoplist)
            {
                for_cnt++;
                std::string tmp_article;
                for(auto it_second: it_first.second)
                {
                    tmp_article += it_second;
                }
                std::string tmp_res = wordSplit(tmp_article);

                std::stringstream ss_res(tmp_res);
                std::string tmp_word;
                std::string tmp_content;
                while(ss_res >> tmp_word)
                {
                    if(!is_stopword(tmp_word))
                    {
                        tmp_content += tmp_word; 
                        tmp_content += " ";
                    }
                }
                it_first.second.clear();
                it_first.second.push_back(tmp_content);
            }
            }
            std::map<int, std::vector<std::string> >& getMapSplit()
            {
                pageSplit();
                return m_map_stoplist;
            }
            std::map<int, std::vector<std::string> > new_getMapSplit()
            {
                new_pageSplit();
                std::cout<<"in new_getMapSplit()$$new_m_map_stoplist.size="<<new_m_map_stoplist.size()<<std::endl;
                return new_m_map_stoplist;
            }
            std::pair<std::string, std::string>  backup_getSummary(int docidSummary, int maxSummarySize, 
                                                                   std::vector<std::string> vec_words,
                                                                   int number)
            std::ifstream input_original_offset("./generate_page/offset.lib");
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
            std::map<int, std::pair<int, int> > map_new_offset;
            while(input_original_offset >> num_int >> offset_int>> size_int)
            {
                map_new_offset[num_int] = std::make_pair(offset_int, size_int);
            }
            std::string line_offset;

            auto it_new_original = map_original_offset.find(docidSummary);
            if(it_new_original == map_original_offset.end())
            {
                std::cout<<"Sorry! the new_offset docid not exist int original offset.lib"<<std::endl;
                std::cout<<"error: not found the docidSummary!"<<std::endl;
                exit(-1);
            }
            std::string curr_content;
            std::string real_curr_content;
            std::string line_content;
            int line_cnt = 0;
            std::ifstream input_ripepage("./generate_page/ripepage.lib");
            if(!input_ripepage)
            {
                perror("input_ripepage(getSummary())");
                exit(-1);
            }
            input_ripepage.seekg(it_new_original->second.first, std::fstream::beg);
            int curr_end_mark = it_new_original->second.first + it_new_original->second.second;

            std::string index_title;
            int index_line_cnt = 0;
            bool title_flag = false;

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
                std::string first_tmp_title;
                if(line_cnt >= 6)
                {
                    real_curr_content += real_line_content;
                    if(index_line_cnt == 0)
                    {
                        first_tmp_title = line_content;
                    }
                    if(index_line_cnt < 13)
                    {
                        std::string flag_title = "【 标  题 】";
                        if((line_content.substr(0, 16) == flag_title))
                        {
                            for(int ind=16; ind<line_content.size(); ind++)
                            {
                                index_title += line_content[ind];
                            }
                            title_flag = true;
                        }

                    }
                    index_line_cnt++;
                }
                if(!title_flag)
                {
                    index_title = first_tmp_title;
                }
            }
            std::string docstr_split = wordSplit(real_curr_content);
            bool start_flag = false;
            bool end_flag = false;
            std::stringstream ss_doc_str(docstr_split);
            std::string doc_str_word;
            std::string line_sentence;
            std::set<std::string> tmp_words;
            std::vector<std::pair<std::string, std::set<std::string> > > tmp_return;
            bool first_word = false;
            while(ss_doc_str >> doc_str_word)
            {
                first_word = true;
                std::string tmp_unuseful;
                if(first_word)
                {
                    first_word = false;
                    if(is_stopsentence(doc_str_word))
                    {
                        start_flag = true;
                        ss_doc_str >> tmp_unuseful;
                    }
                }
                if(is_stopsentence(doc_str_word))
                {
                    start_flag = true;
                    ss_doc_str >> tmp_unuseful;
                }
                tmp_words.insert(doc_str_word);
                line_sentence += doc_str_word;
                if(start_flag = true)
                {
                    if(is_stopsentence(doc_str_word))
                    {
                        ss_doc_str >> tmp_unuseful;
                        end_flag = true;
                        tmp_return.push_back(std::make_pair(line_sentence, tmp_words));
                        line_sentence.erase(0);
                        start_flag = false;
                        end_flag = false;
                    }
                }
            }
            char* summary = "\0";
            std::string summarySentences;

            int summary_cnt = 0;
            for(auto it_search:vec_words)
            {
                for(auto it_sentence: tmp_return)
                {
                    if(sentenceSearchWord(it_sentence.second, it_search))
                    {
                        summary_cnt++;
                        summarySentences += it_sentence.first;
                        summarySentences += "\n";

                        if(summary_cnt >= maxSummarySize)
                        {
                            break;
                        }
                    }
                }
            }
            if(summarySentences[summarySentences.size()-1] != '\n')
            {
                summarySentences += "\n";
            }
            summarySentences = summary + summarySentences;
            std::cout<<"index_title:"<<index_title<<std::endl;
            if(index_title.size() < 1)
            {
                index_title = "！！亲，系统未检测到该篇文章的标题，不好意思哦！哈哈...";
            }
            return std::make_pair(index_title, summarySentences);
        }
        bool is_stopword(std::string aword)
        {
            std::ifstream input_stopList("./filedata/stopList_standard.txt");
            if(!input_stopList)
            {
                perror("input_stopList");
                exit(-1);
            }
            std::set<std::string> set_stopword;
            std::string word;
            while(input_stopList >> word)
            {
                set_stopword.insert(word);
            }
            if(set_stopword.find(aword) == set_stopword.end())
            {
                return false;
            }
            return true;
        }
        bool is_stopsentence(std::string aword)
        {
            std::set<std::string> set_stopsentence = {".", "?", "!", "。", "？", "！", "；", ";"};
            if(set_stopsentence.find(aword) == set_stopsentence.end())
            {
                return false;
            }
            return true;
        }
        bool sentenceSearchWord(std::set<std::string> sentence_words, std::string word)
        {
            if(sentence_words.find(word) != sentence_words.end())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        private:
            std::map<int, std::vector<std::string> > m_map_stoplist;
            std::map<int, std::vector<std::string> > new_m_map_stoplist;
            };
            #endif
