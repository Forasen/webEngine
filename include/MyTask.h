/*********************************************
  > File  : MyTask.h
  > Author: NewYork
  > Mail  : 2287794993@qq.com 
  > Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/
#ifndef _MYTASK_H
#define _MYTASK_H

#include<algorithm>
#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<queue>
#include<set>

#include "Task.h"
#include "MySocket.h"
#include "MyResult.h"
#include "MyCompare.h"
#include "MyConf.h"
#include "MyWebSort.h"

class Task;

class MyTask: public Task
{
    public:
        MyTask(){

        };
        MyTask(MyConf& conf)
            :m_vec(&(conf.m_vec_dict)),
            m_index_task(&conf.m_map_index_vec)
    {
        memset(&m_addr, 0, sizeof(m_addr));
    }
        MyTask(MyConf& conf, const struct sockaddr_in& addr, std::vector<std::string>& vec)
            :m_addr(addr),
            m_inputVec(vec),
            m_vec(&(conf.m_vec_dict)),
            m_index_task(&conf.m_map_index_vec)
    {
    }
        void process()
        {
            MyConf mconf("./conf.dat");
            m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            std::string spellchecked_buf = spellCheck();

            std::cout<<"将客户端的信息纠正后的结果为："<<spellchecked_buf<<std::endl;
            std::string send_buf = mywebsort.handleSearch(spellchecked_buf);

            int send_len = send_buf.size();

            int ret_send = sendto(m_sockfd, send_buf.c_str(), 
                    send_len, 0, (struct sockaddr*)&m_addr, sizeof(m_addr));
            std::cout<<"server has send : "<<ret_send<<" bytes data!"<<std::endl;

        }

        std::string spellCheck()
        {
            std::string spell_buf;
            for(auto it_vec: m_inputVec)
            {
                spell_buf += getResult(it_vec);
                spell_buf += " ";
            }
            return spell_buf;
        }
        std::size_t nBytesCode(const char ch)
        {
            std::size_t nBytes = 0;
            if(ch & (1 << 7))
            {
                if((ch & 0xF0)==0xC0 || (ch & 0xF0) == 0xD0)
                {
                    nBytes = 2;
                }
                else if((ch & 0xF0) == 0xE0)
                {
                    nBytes = 3;
                }
                else if((ch & 0xF0) == 0xF0)
                {
                    nBytes = 4;
                }
                else if((ch & 0xFF) == 0xFE)
                {
                    nBytes = 6;
                }
            }
            else 
            {
                nBytes = 1;
            }
            return nBytes;
        }

        std::size_t length(const char* str)
        {
            std::size_t len = 0;
            std::size_t nlen = strlen(str);
            for(std::size_t index=0; index != nlen; index++)
            {
                std::size_t nBytes = nBytesCode(str[index]);
                index += (nBytes - 1);
                len++;
            }
            return len;
        }

        int editDistance(const std::string& left, const std::string& right)
        {
            const char* s1 = left.c_str();
            const char* s2 = right.c_str();

            int len1 = length(s1);
            int len2 = length(s2);
            int** d=new int*[len1+1];
            for(int k=0;k<=len1;k++)
                d[k]=new int[len2+1];  
            int i,j;   
            for(i = 0;i <= len1;i++)   
                d[i][0] = i;   
            for(j = 0;j <= len2;j++)   
                d[0][j] = j;   
            for(i = 1;i <= len1;i++)   
                for(j = 1;j <= len2;j++)
                {
                    int cost = s1[i] == s2[j] ? 0 : 1;   
                    int deletion = d[i-1][j] + 1;   
                    int insertion = d[i][j-1] + 1;   
                    int substitution = d[i-1][j-1] + cost;   
                    d[i][j] = min(deletion,insertion,substitution);   
                }   
            for(int k=0;i<=len1;k++)
                delete[] d[k];
            delete[] d;

            return d[len1][len2];
        }

        void compute_vec_edit(std::string query_word, std::set<int>& iset)
        {
            while(!m_queue_result.empty())
            {
                m_queue_result.pop();
            }
            for(auto it: iset)
            {
                int dist;
                if((dist = editDistance(query_word, m_vec->at(it).first)) < 3)
                {
                    MyResult retTmp;
                    retTmp.m_word = m_vec->at(it).first;
                    retTmp.m_freq = m_vec->at(it).second;

                    retTmp.m_dist = dist;
                    m_queue_result.push(retTmp);
                }
            }
            std::string tmp_word = m_queue_result.top().m_word;

            int tmp_freq = m_queue_result.top().m_freq;

            double tmp_dist = m_queue_result.top().m_dist;

            while(!m_queue_result.empty())
            {
                m_queue_result.pop();
            }
            MyResult retTmp;

            retTmp.m_word = tmp_word;
            retTmp.m_freq = tmp_freq;
            retTmp.m_dist = tmp_dist;

            m_queue_result.push(retTmp);
        }

        std::string getResult(std::string query_word)
        {
            std::string ch;

            int character_cnt = 0, character_original_cnt = 0;
            int ch_cnt = 0, ch_original_cnt = 0;
            bool character_flag = false;
            bool ch_flag = false;
            bool first_flag = true;
            for(std::size_t index=0; index<query_word.size();)
            {
                char tmp = query_word[index];

                if(first_flag)
                {
                    if(isalpha(tmp))
                    {
                        ch_flag = true;
                        ch_cnt = query_word.size();
                        ch_original_cnt = ch_cnt;
                    }
                    else
                    {
                        character_flag = true;
                        character_cnt = query_word.size() / 3;
                        character_original_cnt = character_cnt;
                    }
                    first_flag = false;
                }
                if(isalpha(tmp))
                {
                    ch = query_word.substr(index, 1);
                    index++;
                }
                else
                {
                    ch = query_word.substr(index, 3);
                    index += 3;
                }
                if((*m_index_task).find(ch) != (*m_index_task).end())
                {
                    if(ch_flag)
                    {
                        ch_cnt--;
                    }
                    if(character_flag)
                    {
                        character_cnt--;
                    }
                    compute_vec_edit(query_word, (*m_index_task)[ch]);
                }
            }

            if(ch_flag && (ch_cnt==ch_original_cnt))
            {
                return query_word; 
            }
            if(character_flag && (character_cnt==character_original_cnt))
            {
                return query_word;
            }

            std::size_t index = 0;

            std::string arr_ret;
            if(m_queue_result.empty())
            {
                std::cout<<"queue empty!"<<std::endl;
                exit(-1);
            }
            arr_ret += m_queue_result.top().m_word;

            return arr_ret;
        }

        ~MyTask()
        {
            close(m_sockfd);
        }

    private:
        std::vector<std::pair<std::string, int> >* m_vec;
        std::map<std::string, set<int> >* m_index_task;
        std::priority_queue<MyResult, std::vector<MyResult>, MyCompare> m_queue_result;
        std::vector<std::string> m_inputVec;
        struct sockaddr_in m_addr;
        MyWebSort mywebsort;
        int m_sockfd;
        int min(int a,int b,int c) {int t = a < b ? a : b;   return t < c ? t : c;}   
};
#endif
