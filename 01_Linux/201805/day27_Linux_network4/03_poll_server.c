#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <errno.h>
#include <ctype.h>


#include "wrap.h"
#define MAXLINE  80
#define SERV_PORT 6666
#define OPEN_MAX 1024


int main(int argc, char* argv[])
{
    int i, j, maxi, listenfd, connfd, sockfd;
    int nready;
    ssize_t n;

    char buf[MAXLINE], str[INET_ADDRSTRLEN];
    socklen_t clilen;
    struct pollfd client[OPEN_MAX];
    struct sockaddr_in cliaddr, servaddr;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    Listen(listenfd, 128);
    
    client[0].fd = listenfd;
    client[0].events = POLLIN;
    for(i = 1; i < OPEN_MAX; i++)
    {
        client[i].fd = -1;
    }
    maxi = 0;


    for( ; ; )
    {
        nready = poll(client, maxi +1, -1);
        if(client[0].revents & POLLIN)
        {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);

            printf("received from %s at PORT %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr,str,sizeof(str)),ntohs(cliaddr.sin_port));
            for(i = 1; i < OPEN_MAX; i++)
            {
                if(client[i].fd < 0)
                {
                    client[i].fd = connfd;
                    break;
                }
            }
            if(i == OPEN_MAX)
                perr_exit("too many clients");

            client[i].events = POLLIN;
            if(i > maxi)
                maxi = i;
            if(--nready <= 0)
                continue;
        }

        for(i = 1; i <= maxi; i++)
        {
            if((sockfd = client[i].fd) < 0)
                continue;
            if(client[i].revents & POLLIN)
            {
                if((n = Read(sockfd,buf, MAXLINE)) < 0)
                {
                    if(errno == ECONNRESET)
                    {
                        printf("client[%d] aborted connection\n", i);
                        Close(sockfd);
                        client[i].fd = -1;
                    }
                    else
                        perr_exit("read error");
                }else if (n == 0){
                    printf("client[%d] closed connection\n",i);
                    Close(sockfd);
                    client[i].fd = -1;
                }
                else
                {
                    for(j = 0; j < n; j++)
                        buf[j] = toupper(buf[j]);

                    Writen(sockfd, buf, n);
                }
                if(--nready <= 0)
                    break;
            }
        }






















    
    }
























}
