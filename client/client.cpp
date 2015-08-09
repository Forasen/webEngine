/*********************************************
  > File  : client.cpp
  > Author: NewYork
  > Mail  : 2287794993@qq.com 
  > Time  : Mon 13 Jul 2015 05:27:47 PM CST
 ********************************************/

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
#include "./../MyJson.h"

#include "./../json/json.h"
#include "../MyCompare.h"
#include "../MyResult.h"

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
    char send_buf[128];
    memset(send_buf, 0, sizeof(send_buf));
    //std::cout<<"Enter a word : ";
    //std::cin>>send_buf;

    //std::string task_str;
    std::cout<<"亲，百度一下看看神马情况：";
    std::cin>>send_buf;
    //std::cin>>task_str;
    /*对send_buf封装成json对象*/
#if 1
    MyJson myjson;
    std::string send_buf_json = myjson.json_handle_str(send_buf);
#endif 

    //char* send_buf = "hello";
    clock_t begin, end;
    begin = clock();
    int ret_send = sendto(sockfd, &send_buf, strlen(send_buf), 0, (struct sockaddr*)&addr, sock_len);
    //int ret_send = sendto(sockfd, send_buf_json.c_str(), send_buf_json.size(), 0, (struct sockaddr*)&addr, sock_len);
    //std::cout<<"客户端已经发送的json内容为："<<std::endl;
    //std::cout<<send_buf_json<<std::endl;
    std::cout<<"client has sended : "<<ret_send<<" bytes data!"<<std::endl;

    char recv_buf_vec[100000];
    //std::cout<<"at the begining(recv_buf_vec.size()) : "<<sizeof(recv_buf_vec)<<" bytes data!"<<std::endl;
    std::size_t recv_len = sizeof(recv_buf_vec);
    ssize_t ret_recv = recvfrom(sockfd, recv_buf_vec, recv_len, 0, (struct sockaddr*)&addr, &sock_len);
    std::cout<<"ret_recv(recvfrom).size = "<<ret_recv<<std::endl;

    /*display the result*/
    std::cout<<"*************查询到的网页信息****************"<<std::endl;
    //std::cout<<"WORD"<<"\t"<<"FREQ"<<"\t"<<"DIST"<<std::endl;
    //!!std::cout<<recv_buf_vec;
    std::string ret_buf_str(recv_buf_vec);
    std::cout<<"来自Json的处理结果！！！！！"<<std::endl;
    myjson.json_handle_reader(ret_buf_str);

    std::cout<<"***************本次查询结束****************"<<std::endl;

    end = clock();
    double run_time = (double)(end - begin) / CLOCKS_PER_SEC;
    std::cout<<"@@@@@@@@@@@@@@@本次查询耗时："<<run_time<<"s@@@@@@@@@@@@@@@@@"<<std::endl;
    return 0;
}
