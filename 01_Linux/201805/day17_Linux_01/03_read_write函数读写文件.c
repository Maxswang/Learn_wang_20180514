#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFSIZE 1024

int main()
{
    int fd = open("english.txt", O_RDONLY);
    if(fd == -1)
    {
        perror("open file");
        exit(1);
    }
    int fd1 = open("mycp_english.txt", O_WRONLY | O_CREAT , 0777);
    if(fd1 == -1)
    {
        close(fd);
         perror("open file1");
         exit(1);
    }
    char buf[BUFSIZE] = {0}; 
    int ret = read(fd,buf, BUFSIZE);
    if(ret == -1)
    {
        perror("read error");
        exit(1);
    }
    while(ret)
    {
        int n = write(fd1, buf, ret);
        if(n != ret)
        {
            perror("write error");
            exit(1);
        }
        ret = read(fd, buf, BUFSIZE);
    }
    
    close(fd);
    close(fd1);
    
    return 0;
}
