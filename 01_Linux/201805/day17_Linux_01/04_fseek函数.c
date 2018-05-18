#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int fd = open("aaa", O_RDWR);
    if(fd == -1)
    {
        perror("open file");
        exit(1);
    }
    int ret = lseek(fd, 0, SEEK_END);
    printf("file length =%d\n", ret);
    //文件拓展
    ret = lseek(fd, 2000, SEEK_END);
    printf("return value %d\n", ret);

    //实现文件拓展， 需要再最后做一次写操作
    write(fd, "a", 1);
    
    close(fd);

    return 0;
}
