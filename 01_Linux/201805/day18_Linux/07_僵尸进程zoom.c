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
        printf("I'm child, I will sleep 10s\n");
        sleep(10);
        printf("I'm going to die");
    }
    else
    {
        while(1)
        {
        
            printf("I'm father, pid =%u\n",getpid());
            sleep(1);
        }
    }
    return 0;
}
