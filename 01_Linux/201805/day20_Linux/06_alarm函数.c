#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
    int ret = alarm(5);
    printf("ret = %d\n", ret);

    sleep(2);
    ret = alarm(2);
    printf("ret = %d\n", ret);
    while(1)
    {
        printf("hello, world!\n");
        sleep(1);
    }
    return 0;
}
