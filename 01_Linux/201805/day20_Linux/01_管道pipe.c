//练习： 父子进程间通信 通过管道实现ps aux | grep bash
  // 实现提示：  dup2  和 execlp
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret == -1)
    {
        perror("pipe error");
        exit(1);
    }
    pid_t pid;
    pid = fork();
    if(pid == -1)
    {
        perror("fork error");
        exit(1);
    }
    else if(pid == 0)
    {
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        execlp("grep","grep","--color=auto","bash",NULL);

    }
    else
    {

        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ps","ps","aux",NULL);
    }
    printf("fd[0] = %d\n", fd[0]);
    printf("fd[1] = %d \n", fd[1]);

    close(fd[0]);
    close(fd[1]);

    return 0;
}
