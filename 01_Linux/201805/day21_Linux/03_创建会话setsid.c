#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>



int main()
{

    pid_t pid = fork();
    if(pid> 0)
    {
        exit(1);
    }
    else if (pid == 0)
    {
        setsid();// 创建会话  会长就是一个守护进程
        while(1);
    }
    return 0;
}
