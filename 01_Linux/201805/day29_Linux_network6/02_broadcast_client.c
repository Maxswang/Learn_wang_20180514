#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <strings.h>


#define SERV_PORT 8000
#define CLIE_PORT 9000
#define MAXLINE 4096


int main()
{
    struct sockaddr_in localaddr;
    int connfd;
    ssize_t len;
    char buf[MAXLINE];

    connfd= socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&localaddr, sizeof(localaddr));
    localaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "0.0.0.0", &localaddr.sin_addr.s_addr);
    localaddr.sin_port = htons(CLIE_PORT);

    int ret = bind(connfd, (struct sockaddr*)&localaddr, sizeof(localaddr));
    if(ret == 0)
        printf("-----bind ok-----\n");
    while(1)
    {
        len = recvfrom(connfd,buf, sizeof(buf), 0, NULL, 0);
        write(STDOUT_FILENO, buf, len);
    

    }
    close(connfd);
    return 0;

}
