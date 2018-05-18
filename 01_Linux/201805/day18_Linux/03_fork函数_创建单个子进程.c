#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
    pid_t pid;
    printf("xxxxxxxxxxxxxx\n");
    pid = fork();
    if(pid == -1)
    {
        perror("fork");
        exit(1);
    }
    else if(pid == 0)
    {
        printf("I'm child ,pid =%u, ppid =%u\n", getpid(), getppid());

    }
    else
    {
        printf("I'm father, pid =%u, ppid = %u\n",getpid(), getppid());
        sleep(2);
    }
    printf("yyyyyyyyyyyyyyyyyy\n");
    return 0;
}
