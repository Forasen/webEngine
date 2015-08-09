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
            //m_inputStr(""),
            :m_vec(&(conf.m_vec_dict)),
            m_index_task(&conf.m_map_index_vec)
             //std::map<std::string, set<int> >* m_index_task;
    {
        //std::cout<<"m_index_task.size="<<m_index_task->size()<<std::endl;
        memset(&m_addr, 0, sizeof(m_addr));
    }
#if 1
        //MyTask(MyConf& conf, const struct sockaddr_in& addr, std::string& input)
        MyTask(MyConf& conf, const struct sockaddr_in& addr, std::vector<std::string>& vec)
            :m_addr(addr),
            //m_inputStr(input),
            m_inputVec(vec),//存放待查询的单词
            m_vec(&(conf.m_vec_dict)),
            m_index_task(&conf.m_map_index_vec)
             //std::map<std::string, set<int> >* m_index_task;
             //88m_index_task(&(conf.m_map_index_vec))
             //^^!!std::map<std::string, set<int> >* m_index_task;
    {
        //std::cout<<"m_index_task.size="<<m_index_task->size()<<std::endl;
    }
#endif

        void process()
        {
            //std::cout<<"******************process()"<<std::endl;
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

            //char send_buf[100];
            //memset(send_buf, 0, sizeof(send_buf));
            //std::cout<<"send_buf::size(before) = "<<strlen(send_buf)<<std::endl;
            std::string send_buf;//存放最终所有单词的纠错后的单词结果
            //!!std::string getResult(std::string query_word)
            /*处理每一个分词（已去停用词，减少没必要的时间消耗）后单词*/
#if 0
            std::cout<<"m_inputVec="<<m_inputVec.size()<<std::endl;
            std::cout<<"vector中的内容：";
            for(auto it_vec: m_inputVec)
            {
                std::cout<<it_vec<<", ";
            }
            std::cout<<std::endl;
#endif

            //!!m_inputVec(vec),//存放待查询的单词
            //std::cout<<"m_inputVec->";
            for(auto it_vec: m_inputVec)
            {
                //std::cout<<it_vec<<", ";
                send_buf += getResult(it_vec);
                //std::cout<<"before:"<<it_vec<<std::endl;
                //std::string tmp_str = getResult(it_vec);
                //std::cout<<"tmp_str:"<<tmp_str<<std::endl;
            }
            //std::cout<<std::endl;
            //std::cout<<"send_buf.size="<<send_buf.size()<<std::endl;
            int send_len = send_buf.size();
            int ret_send = sendto(m_sockfd, send_buf.c_str(), send_len, 0, (struct sockaddr*)&m_addr, sizeof(m_addr));
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

        //!!int editDistance_1(const std::string& left, const std::string& right)
        int editDistance_1(const std::string& left, const std::string& right)
        {
            //std::cout <<__FILE__<<std::endl ;
            //std::cout << " ----------edit_dist right:------------" << right <<"  size:" << right.size() << std::endl ;
            //int len_left = length(m_express);
            //int len_right = length(right);
            int len_left = left.size();
            int len_right = right.size();
            std::cout<<"len_left="<<len_left<<", len_right="<<len_right<<std::endl;
            //int len_left = lenght(left);
            //int len_right = length(right);
            int ** arr_dist = new int* [len_left + 1];
            int index , index_left, index_right;
            std::string subleft , subright ;
            for(index = 0 ; index <= len_left ; index ++)
            {
                arr_dist[index] = new int[len_right + 1];
            }
            int index_i , index_j ;
            for(index_i = 0 , index_j = 0 ; index_j <= len_right ; index_j ++)
            {
                arr_dist[index_i][index_j] = index_j ;
            }
            for(index_i = 1 , index_j = 0 ; index_i <= len_left; index_i ++)
            {
                arr_dist[index_i][index_j] = index_i ;
            }
            for(index_i = 1 , index_left = 0;  index_i <= len_left; index_i ++, index_left ++)
            {
                //if(m_express[index_left] & (1 << 7))
                //if(left[index_left] & (1 << 7))
                if(!isalpha(left[index_left]))
                {
                    //subleft = m_express.substr(index_left, 2);
                    subleft = left.substr(index_left, 3);
                    index_left += 2; 
                }else 
                {
                    //subleft = m_express[index_left];
                    subleft = left[index_left];

                }
                for(index_j = 1 , index_right = 0; index_j <= len_right; index_j ++ ,index_right ++)
                {
                    //if(right[index_right] & (1 << 7)) 
                    if(!isalpha(right[index_right])) 
                    {
                        subright = right.substr(index_right, 3);
                        index_right += 2;
                    }else 
                    {
                        subright = right[index_right];
                    }
                    int a = arr_dist[index_i - 1][index_j - 1] + (subleft == subright ? 0 : 1) ;
                    //arr_dist[index_i][index_j] =  triple_min(a, arr_dist[index_i - 1][index_j] + 1, arr_dist[index_i][index_j - 1] + 1);
                    arr_dist[index_i][index_j] =  min(a, arr_dist[index_i - 1][index_j] + 1, arr_dist[index_i][index_j - 1] + 1);
                }
            }
            int result = arr_dist[len_left][len_right] ;
            for(index = 0 ; index <= len_left; index ++)
            {
                delete [] arr_dist[index];
            }
            delete [] arr_dist ;
            return result ;

        }
        int editDistance(const std::string& left, const std::string& right)
        {
            //const char* s1 = m_inputStr.c_str();
            const char* s1 = left.c_str();
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

        /*待查询单词和这个单词里面的单字对应的所有索引的编辑距离的计算*/
        void compute_vec_edit(std::string query_word, std::set<int>& iset)
        {
            std::cout<<"compute_vec_edit()"<<std::endl;
            for(auto it: iset)
            {
                int dist;
                //!!std::vector<std::pair<std::string, int> >* m_vec;
                if((dist = editDistance(query_word, m_vec->at(it).first)) < 3)
                {
                    MyResult retTmp;
                    retTmp.m_word = m_vec->at(it).first;//注意下标操作符
                    retTmp.m_freq = m_vec->at(it).second;//对应的词频
                    //retTmp.m_freq = atoi((m_vec->at(it).second).c_str());
                    retTmp.m_dist = dist;
                    m_queue_result.push(retTmp);//存入优先队列
                }
            }
        }

        //void getResult(char* arr_ret)
        /*处理输入的单词，依据字母索引进行查询*/
        /*只要一个最优结果
         * 返回结果为：单词、词频、最小编辑距离
         * */
        std::string getResult(std::string query_word)
        {
            std::cout<<"getResult()"<<std::endl;
#if 1
            std::string ch;
            /*对汉字和英文字符进行处理*/
            for(std::size_t index=0; index<query_word.size();)
            {
                char tmp = query_word[index];
                //if(tmp && (1 << 7))
                if(isalpha(tmp))
                {
                    ch = query_word.substr(index, 1);
                    index++;
                }
                else//handle a chinese character
                {
                    ch = query_word.substr(index, 3);
                    index += 3;
                }
                /*
                 *仅仅是针对query_word这个单词里面所有的单字进行计算
                 * */
                /*每处理完一个单字便对单字对应的所有单词（序号索引表示）进行编辑距离计算*/
                //!!std::map<std::string, set<int> >* m_index_task;
                if((*m_index_task).find(ch) != (*m_index_task).end())
                {
                    compute_vec_edit(query_word, (*m_index_task)[ch]);
                }
#if 0
                else
                {
                    std::cout<<"未发现该单词的单字对应的单词->"<<ch<<std::endl;
                    //exit(-1);
                }
#endif
            }
#endif
            //!!void compute_vec_edit(set<int>& iset)
            //!!std::map<std::string, set<int> >* m_index_task;//里面存放的是单字而非单词
            //!!std::vector<std::string> m_inputVec;
            //!!std::cout<<"m_inputVec.size() = "<<m_inputVec.size()<<std::endl;
            //int cnt =1;
            std::size_t index = 0;

            std::string arr_ret;
            if(m_queue_result.empty())
            {
                std::cout<<"queue empty!"<<std::endl;
                exit(-1);
            }
            arr_ret += m_queue_result.top().m_word;
            arr_ret += "\t";

            char freq_char[10];
            sprintf(freq_char, "%d", m_queue_result.top().m_freq);
            arr_ret += freq_char;
            arr_ret += "\t";
            memset(freq_char, 0, sizeof(freq_char));
            sprintf(freq_char, "%d", m_queue_result.top().m_dist);
            arr_ret += freq_char;
            arr_ret += "\n";

            //!!弹出最优结果
            m_queue_result.pop();
            
            while(!m_queue_result.empty())
            {
                m_queue_result.pop();
            }
            
            return arr_ret;
        }

        ~MyTask()
        {
            close(m_sockfd);
        }

    private:
        /*单词和对应的词频*/
        std::vector<std::pair<std::string, int> >* m_vec;
        std::map<std::string, set<int> >* m_index_task;
        std::priority_queue<MyResult, std::vector<MyResult>, MyCompare> m_queue_result;
        //std::string  m_inputStr;
        /*存放待查询的单词*/
        std::vector<std::string> m_inputVec;
        struct sockaddr_in m_addr;
        int m_sockfd;
        int min(int a,int b,int c) {int t = a < b ? a : b;   return t < c ? t : c;}   
};

#endif
