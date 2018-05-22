#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>


int main()
{
    while(1)
    {
        sigset_t pendset;
        sigpending(&pendset);
        for(int i = 1; i < 32; ++i)
        {
            if(sigismember(&pendset,i))
            {
            printf("1");
        }
            else
        {
            printf("0");
        }
    }
    printf("\n");
    sleep(1);
    }
    return 0;
}
