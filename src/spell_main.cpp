/*********************************************
> File  : spell_main.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 11:28:16 PM CST
********************************************/

#include<iostream>
#include <iostream>
#include<unistd.h>

#include "../include/MyTask.h"
#include "../include/MyConf.h"
#include "../include/ThreadPool.h"
#include "../include/MySocket.h"
#include "../include/MySplit.h"
#include "../include/MyResult.h"
#include "../include/MyJson.h"

std::string wordSplit(std::string);

class ThreadPool;

int main(int argc, char* argv[])
{
    std::string path = "../data/conf.dat";
    MyConf mcf(path); 
    struct sockaddr_in address;
    MySocket msock(mcf);
    char recv_buf[1024];
    ThreadPool threadpool(4, 10);
    threadpool.start();
    MySplit mysplit;
    MyJson myjson;

    while(1)
    {
        memset(recv_buf, 0, sizeof(recv_buf));
        msock.recv_info(recv_buf, sizeof(recv_buf));

        std::cout<<"从客户端接受的原始数据为..."<<std::endl;
        std::cout<<recv_buf<<std::endl;

        std::string recv_buf_str(recv_buf);
        std::string recv_str = wordSplit(recv_buf_str); 
        std::stringstream ss(recv_str);
        std::string word;
        std::cout<<"从客户端接收到的数据的分词结果(已去停用词)为："<<std::endl;

        std::vector<std::string> recv_vec;
        while(ss >> word)
        {
            if(!mysplit.is_stopword(word))
            {
                std::cout<<word<<" ";
                recv_vec.push_back(word);
            }
        }
        std::cout<<"\n--------------------------\n"<<std::endl;
        MyTask* pTask = new MyTask(mcf, msock.getAddr(), recv_vec);
        threadpool.addTask(pTask);
    }
    return 0;
}
