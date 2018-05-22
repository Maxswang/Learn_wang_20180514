#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>


int main()
{
    struct itimerval new_val;
//第一次触发的时间
    new_val.it_value.tv_sec = 2;//设置秒
    new_val.it_value.tv_usec = 0;  // 设置微秒时间 

    //周期性定时
    new_val.it_interval.tv_sec = 1;
    new_val.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &new_val, NULL);
    while(1)
    {
        printf("hello, world\n");
        sleep(1);
    }

    return 0;
}
