#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
    int n=5, i;
    pid_t p, q, wpid;

    if(argc == 2)
    {
    n = atoi(argv[1]); 
    }
    for(i = 0; i < n; i++)
    {
        p = fork();
        if(p == 0)
        {
            break;
        } 
        else if (i == 3)
        {
            q = p;
        }
    }
    if(n == i)
    {
        sleep(n);
        printf("I am parent , pid = %d\n", getpid());
// while(wait(NULL));
        do{
       wpid  =  waitpid(-1, NULL,WNOHANG );
        if(wpid > 0)
        {
            n--;
        }
        sleep(1);
        }
        while(n > 0);
        printf("wait finish\n");
    }else{
        sleep(i);
        printf("I'm %dth child, pid =%d, gpid = %d\n", i+1, getpid(),getgid());
    }
    



return 0;
}
