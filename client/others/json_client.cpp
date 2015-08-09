/*************************************************************************
	> File Name: json_client.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Aug 2015 05:11:13 PM CST
 ************************************************************************/

#include<iostream>
#include "./../json/json.h"
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
    addr.sin_port = htons(8888);

    socklen_t sock_len = sizeof(struct sockaddr);

    //std::string send_buf;
    //char send_buf[128];
    //memset(send_buf, 0, sizeof(send_buf));
    Json::Value root;
    root["content"] = Json::Value("hello, world");
    Json::StyledWriter styledwriter;
    std::string send_buf = styledwriter.write(root);
    socklen_t len = sizeof(struct sockaddr);
    //int send_size = sendto(sockfd, send_buf.c_str(), send_buf.size(), 0, (struct sockaddr*)&addr, len);
    int send_size = sendto(sockfd, &send_buf, send_buf.size(), 0, (struct sockaddr*)&addr, len);
    std::cout<<"客户端已经发送的数据量为："<<send_size<<std::endl;
    std::cout<<"所发送的内容为："<<send_buf<<std::endl;

}
