#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if(pid > 0)
    {
        while(1)
            {
                printf("parent process, %d\n", getpid());
                sleep(1);
            }
    }
    else if(pid == 0)
        // 子进程   杀死父进程
    {
        sleep(2);
        kill(getppid(), SIGKILL);
    }
    return 0;
}
