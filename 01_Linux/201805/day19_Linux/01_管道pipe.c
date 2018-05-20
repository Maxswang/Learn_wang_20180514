#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>


int main()
{
    int fd[2];
    pid_t pid;

    int ret = pipe(fd);

    if(ret == -1)
    {
        perror("pipe error");
        exit(1);

    }
    pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid == 0)
    {
        close(fd[1]); // 关闭写端
        char buf[1024];
       ret = read(fd[0], buf, sizeof(buf));
        if(ret == 0)
        {
            printf(" ------------\n");
        }
        write(STDOUT_FILENO, buf , ret);
    }
    else
    {
        sleep(1);
        close(fd[0]);
        write(fd[1],"hello pipe\n", strlen("hello pipe\n"));
        
    }
    return 0;
}
