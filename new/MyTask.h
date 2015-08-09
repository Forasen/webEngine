/*********************************************
> File  : MyTask.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
 ********************************************/
#ifndef _MYTASK_H
#define _MYTASK_H

#include<iostream>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<queue>
#include<set>
#include "Task.h"
#include "./MySocket.h"
#include "./MyResult.h"
#include "./MyCompare.h"
#include "./MyConf.h"
class Task;

class MyTask: public Task
{
    public:
    MyTask(){
    
    };
    MyTask(MyConf& conf)
    :m_inputStr(""),
    m_vec(&(conf.m_vec_dict)),
    m_index_task(&conf.m_map_index_vec)
    {
        memset(&m_addr, 0, sizeof(m_addr));
    }
    #if 1
    //MyTask(MyConf& conf, const struct sockaddr_in& addr, std::string& input)
    MyTask(MyConf& conf, const struct sockaddr_in& addr, std::vector<std::string>& vec)
    :m_addr(addr),
    //m_inputStr(input),
	m_inputVec(vec),
    m_vec(&(conf.m_vec_dict)),

    //std::map<std::string, set<int> >* m_index_task;
    m_index_task(&(conf.m_map_index_vec))
    {

    }
    #endif

    void process()
    {
        MyConf mconf("./conf.dat");
#if 0
        MySocket msock(mconf);
        //MySocket msock;

        char recv_buf[1024];
        msock.recv_info(recv_buf, sizeof(recv_buf));

        std::cout<<"the data : "<<recv_buf<<std::endl;

        m_inputStr = recv_buf;
#endif
        m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);

        char send_buf[100];
        memset(send_buf, 0, sizeof(send_buf));
        //std::cout<<"send_buf::size(before) = "<<strlen(send_buf)<<std::endl;
        getResult(send_buf);
        std::cout<<"send_buf::size = "<<strlen(send_buf)<<std::endl;
        int send_len = strlen(send_buf);
        int ret_send = sendto(m_sockfd, send_buf, send_len, 0, (struct sockaddr*)&m_addr, sizeof(m_addr));
        std::cout<<"server has send : "<<ret_send<<" bytes data!"<<std::endl;
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
    int editDistance(const std::string& right)
    {
        const char* s1 = m_inputStr.c_str();
        const char* s2 = right.c_str();//***************try the const
        //int len1 = strlen(s1);
        //int len2 = right.size();
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
        //printf("%d\n",d[len1][len2]); 
        for(int k=0;i<=len1;k++)
        delete[] d[k];
        delete[] d;

        return d[len1][len2];
    }

    void compute_vec_edit(set<int>& iset)
    {
        std::cout<<"compute_vec_edit()"<<std::endl;
        for(auto it: iset)
        {
            int dist;
            //std::vector<std::pair<std::string, int> >& m_vec;
            if((dist = editDistance(m_vec->at(it).first)) < 5)
            {
                MyResult retTmp;
                retTmp.m_word = m_vec->at(it).first;
                retTmp.m_freq = m_vec->at(it).second;
                //retTmp.m_freq = atoi((m_vec->at(it).second).c_str());
                retTmp.m_dist = dist;
                m_result.push(retTmp);
            }
        }
    }

    void getResult(char* arr_ret)
    {
#if 0
        std::cout<<"m_inputStr.size() = "<<m_inputStr.size()<<std::endl;
        std::string character;
        for(std::size_t index=0; index<m_inputStr.size(); index++)
        {
            int tmp = m_inputStr[index];//handle a chinese character
            if(tmp>0 && tmp<255)//handle a chinese character
            {
                character = m_inputStr.substr(index, 1);
            }
            else
            {
                character = m_inputStr.substr(index, 2);
            }
            //std::map<std::string, set<int> >* m_index_task;
            if((*m_index_task).find(character) != (*m_index_task).end())
            {
                compute_vec_edit((*m_index_task)[character]);
            }
        }
#endif
		std::cout<<"m_inputVec.size() = "<<m_inputVec.size()<<std::endl;
        int cnt = 3;
        std::size_t index = 0;
        
        memset(arr_ret, 0, sizeof(arr_ret));
        while((!m_result.empty()) && cnt > 0)
        {
            strcat(arr_ret, m_result.top().m_word.c_str());
            strcat(arr_ret, "\t");

            char freq[10];
            sprintf(freq, "%d", m_result.top().m_freq);
            strcat(arr_ret, freq);
            strcat(arr_ret, "\t");
            sprintf(freq, "%d", m_result.top().m_dist);
            strcat(arr_ret, freq);

            strcat(arr_ret, "\n");

            m_result.pop();
            cnt--;
        }
        return;
    }

    ~MyTask()
    {
        close(m_sockfd);
    }

private:
    std::vector<std::pair<std::string, int> >* m_vec;
    std::map<std::string, set<int> >* m_index_task;
    std::priority_queue<MyResult, std::vector<MyResult>, MyCompare> m_result;
    //std::string  m_inputStr;
	std::vector<std::string> m_inputVec;
    struct sockaddr_in m_addr;
    int m_sockfd;
    int min(int a,int b,int c) {int t = a < b ? a : b;   return t < c ? t : c;}   
};

#endif
