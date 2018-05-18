#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main()
{
    int fd = open("a.txt", O_RDWR);
    if(fd == -1)
    {
        perror("open file");
        exit(1);
    }
    printf("file open fd = %d \n",fd);

    int ret  = dup(fd);
    if(ret == -1)
    {
        perror("dup");
        exit(1);

    }
    printf("dup fd =%d\n", ret);
    char* buf = "你是猴子派来的救兵吗？？？\n";
    char* buf1="你大爷的， 我是程序猿！！！\n";

    write(fd, buf, strlen(buf));
    write(fd, buf1, strlen(buf1));

    close(fd);
    return 0;
}
