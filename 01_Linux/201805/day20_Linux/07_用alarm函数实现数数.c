#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>


int main()
{
    alarm(1);
    int i = 0;
    while(1)
    {
        printf("%d\n",i++);
    }
    
    return 0;
}
