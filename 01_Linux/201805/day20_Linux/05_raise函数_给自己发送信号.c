#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if(pid > 0)
    {
        int s;
        pid_t wpid = wait(&s);
        printf("child died pid = %d\n",wpid);
        if(WIFSIGNALED(s))
        {
            printf("died by signal: %d\n", WTERMSIG(s));
        }
    }
    else if(pid == 0)
    {
        raise(SIGINT);
    }
    return 0;
}
