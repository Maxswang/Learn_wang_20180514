#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main()
{
    int fd;
    int flag;

    char *p = "我们是一个有中国特色的社会主义国家！！！！";
    char *q = "呵呵， 社会主义好哇！！！";

    fd = open("test.txt", O_WRONLY);
    if(fd == -1)
    {
        perror("open");
        exit(1);
    }
    if( write(fd,p , strlen(p)) == -1)
    {
        perror("write");
        exit(1);
    }

    flag = fcntl(fd, F_GETFL, 0);
    if(flag == -1)
    {
        perror("fcntl");
        exit(1);
    }

    flag |= O_APPEND;
    if(fcntl(fd, F_SETFL, flag) == -1)
    {
        perror("fcntl -- append write");
        exit(1);
    }
    if(write(fd, q, strlen(q)) == -1)
    {
        perror("write again");
        exit(1);
    }

    close(fd);
    return 0;
}
