/*************************************************************************
  > File Name: ./client_json.cpp
  > Author: 
  > Mail: 
  > Created Time: Thu 06 Aug 2015 08:28:57 AM CST
 ************************************************************************/

#include<iostream>
#include<sys/socket.h>
#include<iostream>
#include<vector>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<queue>
#include<ctime>

#include "./../../json/json.h"
using namespace std;

int main(void)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
    {
        fprintf(stderr, "error: socket(client)!\n");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.1.152");
    addr.sin_port = htons(9999);

    socklen_t sock_len = sizeof(struct sockaddr);

    Json::Value root;
    root["content"] = Json::Value("hello, I am Json from client!");
    Json::StyledWriter styledwriter;
    std::string send_buf = styledwriter.write(root);
    int send_size = sendto(sockfd, send_buf.c_str(), send_buf.size(), 0, (struct sockaddr*)&addr, sock_len);
    //std::string send_buf = "hello, I am client!";
    //int send_size = sendto(sockfd, send_buf.c_str(), send_buf.size(), 0, (struct sockaddr*)&addr, sock_len);
    std::cout<<"客户端已经发送的数据（大小）为：..."
        <<send_buf.size()<<std::endl;
    std::cout<<"已经发送的真实大小为："<<send_size<<std::endl;
    std::cout<<"客户端发送的内容为：********"<<std::endl;
    std::cout<<send_buf<<std::endl;

    return 0;
}
