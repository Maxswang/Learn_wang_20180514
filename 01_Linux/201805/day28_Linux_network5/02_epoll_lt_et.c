#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <errno.h>

#define MAXLINE 10

int main()
{
    int efd, i;
    int pfd[2];
    pid_t pid;
    char buf[MAXLINE];
   char ch = 'a';


    pipe(pfd);
    pid = fork();

    if(pid == 0)
    {
        close(pfd[0]);
        while(1)
        {
            for(i = 0; i < MAXLINE/2; i++)
                buf[i] = ch;
            buf[i-1] = '\n';
            ch++;
            for( ; i < MAXLINE; i++)
                buf[i] = ch;
            buf[i-1] = '\n';
            ch++;

            write(pfd[1], buf, sizeof(buf));
            sleep(5);
        }
        close(pfd[1]);
    }
    else if(pid > 0)
    {
        struct epoll_event evt;
        struct epoll_event revt[10];

        int res, len;

        close(pfd[1]);
        efd = epoll_create(10);

        evt.events = EPOLLIN | EPOLLET;
        /* evt.events = EPOLLIN;   //默认模式 水平触发 */
        evt.data.fd = pfd[0];
        epoll_ctl(efd, EPOLL_CTL_ADD, pfd[0], &evt);

        while(1){
            res = epoll_wait(efd,revt, 10, -1 );
            printf("res %d\n", res);
            if(revt[0].data.fd == pfd[0])
            {
                len = read(pfd[0], buf, MAXLINE/2);
                write(STDOUT_FILENO, buf, len);
            
            }
        
        }
        close(pfd[0]);
        close(efd);
    }
    else
    {
        perror("fork");
        exit(1);
    }

    return 0;
}
