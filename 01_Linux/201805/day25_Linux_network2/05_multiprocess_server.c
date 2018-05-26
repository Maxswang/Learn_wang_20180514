#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "wrap.h"
#include <arpa/inet.h>
#define SERV_PORT 8888

void wait_child(int signo)
{
    while(waitpid(0, NULL, WNOHANG) > 0);

    return;

}
int main()
{
    int lfd, cfd;
    struct sockaddr_in serv_addr, clie_addr;
    pid_t pid;

    int n;
    char buf[BUFSIZ], clie_ip[BUFSIZ];
    lfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(lfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));

    Listen(lfd, 128);
    socklen_t clie_addr_len = sizeof(clie_addr);

    while(1){
    cfd = Accept(lfd, (struct sockaddr*)&clie_addr, &clie_addr_len);
    printf("client IP: %s, port:%d\n",  inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr, clie_ip, sizeof(clie_ip)), ntohs(clie_addr.sin_port));

    pid = fork();
    if(pid < 0)
    {
        perror("fork error");
        exit(1);

    }else if(pid == 0)  // 子进程
    {
        close(lfd);
        break;

    } else //父进程
    {
        close(cfd);
        signal(SIGCHLD, wait_child);
    }

    }


    if(pid == 0)
    {
        while(1)
        {
            n = Read(cfd, buf, sizeof(buf));
            if(n == 0 )
            {
                close(cfd);  //client关闭
                return 0;

            }
            else if(n == -1)
            {
                perror("read error");
                exit(1);

            } else
            {
                for(int i = 0; i < n; i++)
                    buf[i] = toupper(buf[i]);
                write(cfd, buf,n);

                write(STDOUT_FILENO, buf, n);
            }
        }

    }

    
    
    return 0;
}
