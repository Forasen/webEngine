/*********************************************
> File  : server.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Tue 14 Jul 2015 10:45:27 PM CST
********************************************/

#include <sys/types.h>
#include <sys/socket.h>
#include<pthread.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<arpa/inet.h>
#include <stdlib.h>
#include<vector>
#include<string.h>
#include<cstring>
#include<iostream>

#include "Result.h"
//using namespace std;
#if 0
struct Result
{
	std::string m_word;
	int m_freq;
	int m_dist;
};
#endif
int main(int argc, char **argv)
{
#if 0
    if (argc != 2)
    {
        printf("Usage: %s port\n", argv[0]);
        exit(1);
    }
#endif
    printf("Welcome! This is a UDP server, I can only received message from client and reply with same message\n");

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int sock;
    if ( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {

        perror("socket");
        exit(1);
    }
    if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {

        perror("bind");
        exit(1);
    }
    std::cout<<"bind success~"<<std::endl;
    //char buff[512];
    struct sockaddr_in clientAddr;
    int n;
    socklen_t len = sizeof(clientAddr);
    std::vector<Result> buff;
#if 1
    recvfrom(sock, &buff, 1000, 0, (struct sockaddr*)&clientAddr, &len);
    for(auto it: buff)
    {
        std::cout<<it.m_word<<"\t"<<it.m_freq<<"\t"<<it.m_dist<<std::endl;
    }
#endif
#if 0
    while (1)
    {
        n = recvfrom(sock, &buff, 511, 0, (struct sockaddr*)&clientAddr, &len);
        if (n>0)
        {
            buff[n] = 0;
            printf("%s %u says: %s\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port), buff);
            n = sendto(sock, buff, n, 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
            if (n < 0)
            {
                perror("sendto");
                break;
            }
        }
        else
        {
            perror("recv");
            break;
        }
    }
#endif
    return 0;
}
