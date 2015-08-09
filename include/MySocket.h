/*********************************************
> File  : MySocket.h
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Mon 13 Jul 2015 03:37:04 PM CST
 ********************************************/

#ifndef _MYSOCKET_H
#define _MYSOCKET_H

#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<unistd.h>

#include "./MyConf.h"

class MySocket
{
public:
	class MyTask;
    MySocket(MyConf& conf)
        :m_conf(conf)
    {
        std::cout<<"本地ip : "<<m_conf.m_map_conf["ip"]<<", "<<"port : "<<m_conf.m_map_conf["port"]<<std::endl;
        m_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if(m_sockfd == -1)
        {
            fprintf(stderr, "error: socket!\n");
            exit(1);
        }
        m_addr.sin_family = AF_INET;
        m_addr.sin_addr.s_addr = inet_addr(m_conf.m_map_conf["ip"].c_str());
        m_addr.sin_port = htons(atoi(m_conf.m_map_conf["port"].c_str()));
        if(-1 == bind(m_sockfd, (struct sockaddr*)&m_addr, (socklen_t)sizeof(m_addr)))
        {
            fprintf(stderr, "error: bind!\n");
            exit(1);
        }
        std::cout<<"Congratulation: bind success!"<<std::endl;
    }
    int send_info(void* buf, int len)
    {
		socklen_t length = sizeof(struct sockaddr);
        std::cout<<"send info ..."<<std::endl;
        return sendto(m_sockfd, buf, len, 0, (struct sockaddr*)&m_addr, length);
    }
    int recv_info(void* buf, int len)
    {
		socklen_t length = sizeof(struct sockaddr);
        std::cout<<"handle request!!!!!"<<std::endl;
        return recvfrom(m_sockfd, buf, len, 0, (struct sockaddr*)&m_addr, &length);
    }

    const struct sockaddr_in getAddr() const
    {
        return m_addr;
    }
    ~MySocket()
    {
        close(m_sockfd);
    }

private:
    int m_sockfd;
    struct sockaddr_in m_addr;
    socklen_t m_len;
    MyConf& m_conf;
};
#endif
