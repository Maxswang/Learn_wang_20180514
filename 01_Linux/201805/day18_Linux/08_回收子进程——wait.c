#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if(pid == -1)
    {
        perror("fork error");
        exit(1);

    }
    else if(pid  == 0)
    {
        printf("---------child,my parent =%d, going to sleep 10s\n", getppid());
        sleep(10);
        printf("------------child  die-----------\n");
    }
    else
    {
        pid_t wpid = wait(NULL);
        if(wpid == -1)
        {
            perror("wait error");
            exit(1);
        }
        while(1)
        {
        
            printf("I'm father, pid =%u, myson =%u\n",getpid(),pid);
            sleep(1);
        }
    }
    return 0;
}
