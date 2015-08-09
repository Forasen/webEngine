/*********************************************
> File  : client.cpp
> Author: NewYork
> Mail  : 2287794993@qq.com 
> Time  : Tue 14 Jul 2015 10:47:15 PM CST
********************************************/

#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include<vector>
#include<iostream>
#include<cstring>
#include "Result.h"
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

    printf("This is a UDP client\n");
    struct sockaddr_in addr;
    int sock;

    if ( (sock=socket(AF_INET, SOCK_DGRAM, 0)) <0)
    {
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8888);
    addr.sin_addr.s_addr = inet_addr("169.254.177.30");
    if (addr.sin_addr.s_addr == INADDR_NONE)
    {
        printf("Incorrect ip address!");
        close(sock);
        exit(1);
    }

    char buff[512];
    socklen_t len = sizeof(addr);
#if 1
	std::vector<Result> vec_ret;
	Result tmp;
	tmp.m_word = "xiaodong";
	tmp.m_freq = 1;
	tmp.m_dist = 1;
	vec_ret.push_back(tmp);
#endif
	sendto(sock, &vec_ret, 1000, 0, (struct sockaddr*)&addr, len);
#if 0

    while (1)
    {
        gets(buff);
        int n;
        n = sendto(sock, buff, strlen(buff), 0, (struct sockaddr *)&addr, sizeof(addr));
        if (n < 0)
        {
            perror("sendto");
            close(sock);
            break;
        }
        n = recvfrom(sock, buff, 512, 0, (struct sockaddr *)&addr, &len);
        if (n>0)
        {
            buff[n] = 0;
            printf("received:");
            puts(buff);
        }
        else if (n==0)
        {
            printf("server closed\n");
            close(sock);
            break;
        }
        else if (n == -1)
        {
            perror("recvfrom");
            close(sock);
            break;
        }
    }
#endif
    return 0;
}
