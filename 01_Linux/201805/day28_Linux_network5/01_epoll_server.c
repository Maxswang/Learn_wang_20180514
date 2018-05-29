#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <ctype.h>

#include "wrap.h"

#define MAXLINE 8192
#define SERV_PORT 6666
#define OPEN_MAX 65535

int main()
{
    int i, listenfd, connfd, sockfd;
    int n, num = 0;
    int  nready , efd, res;
    char buf[MAXLINE], str[INET_ADDRSTRLEN];
    socklen_t clilen;

    struct sockaddr_in cliaddr, servaddr;
    struct epoll_event tep, ep[OPEN_MAX];

    listenfd  = Socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr= htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    Listen(listenfd, 128);
    
    efd = epoll_create(OPEN_MAX);
    if(efd < 0)
    {
        perr_exit("epoll_create error");
    }
    
    tep.events = EPOLLIN;
    tep.data.fd = listenfd;

    res = epoll_ctl(efd, EPOLL_CTL_ADD,listenfd, &tep);
    if(res == -1)
        perr_exit("epoll_ctl error");

    for( ; ; )
    {
        nready = epoll_wait(efd, ep, OPEN_MAX, -1);
        if(nready == -1)
            perr_exit("epoll_wait error");

        for(i = 0; i < nready; i++)
        {
            if( !ep[i].events & EPOLLIN)
                continue;
            if(ep[i].data.fd == listenfd)
            {
                clilen = sizeof(cliaddr);
                connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
                printf("received from %s at PORT %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)), ntohs(cliaddr.sin_port));
                printf("cfd %d ---client %d\n", connfd, ++num);
                tep.events = EPOLLIN;
                tep.data.fd = connfd;
                res = epoll_ctl(efd, EPOLL_CTL_ADD, connfd,&tep);
                if(res == -1)
                    perr_exit("epoll_ctl error");
            }
            else
            {
                sockfd = ep[i].data.fd;
                n = Read(sockfd, buf, MAXLINE);

                if(n == 0)
                {
                    res = epoll_ctl(efd, EPOLL_CTL_DEL,sockfd, NULL);
                    if(res == -1)
                        perr_exit("epoll_ctl error");
                    Close(sockfd);
                    printf("client[%d] closed connection\n", sockfd);
                }
                else if(n < 0)
                {
                
                    perror("read n < 0 error: ");
                    res = epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, NULL);
                }
                else
                {
                    for(i = 0 ; i < n; i++)
                        buf[i] = toupper(buf[i]);

                    Write(STDOUT_FILENO,buf, n);
                    Write(sockfd, buf, n);
                }
            
            }

        }
    }

    Close(listenfd);
    Close(efd);

    return 0;

}
