/*************************************************************************
> File Name: server_json.cpp
> Author: 
> Mail: 
> Created Time: Thu 06 Aug 2015 08:28:46 AM CST
************************************************************************/

#include<iostream>
#include<sys/socket.h>
#include<netinet/in.h>
#include<cstring>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<unistd.h>
#include "./../../json/json.h"
using namespace std;

int main(void)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
    {
        fprintf(stderr, "error: socket!\n");
        exit(1);
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.1.152");
    addr.sin_port = htons(9999);
    if(-1 == bind(sockfd, (struct sockaddr*)&addr, (socklen_t)sizeof(addr)))
    {
        fprintf(stderr, "error: bind!\n");
        exit(1);
    }
    std::cout<<"Congratulation: bind success!"<<std::endl;
    socklen_t len = sizeof(struct sockaddr);

    char recv_buf[1024];
    memset(recv_buf, 0, sizeof(recv_buf));
    //std::string recv_buf;
    int recv_size = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&addr, &len);
    //int recv_size = recvfrom(sockfd, &recv_buf, 1024, 0, (struct sockaddr*)&addr, &len);
    std::cout<<"服务端接收到的数据大小为："<<recv_size<<std::endl;
    std::cout<<"服务端接受到的原始数据为："<<std::endl;
    std::cout<<recv_buf<<std::endl;
    std::string recv_str(recv_buf);
    Json::Reader reader;
    Json::Value root;
    if(reader.parse(recv_str, root))
    {
        std::string recv = root["content"].asString();    
        std::cout<<"服务端接收到数据的真实字符串为："<<std::endl;
        std::cout<<recv<<std::endl;
    }

    return 0;
}
