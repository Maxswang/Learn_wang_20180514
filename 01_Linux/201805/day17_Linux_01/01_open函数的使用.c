#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int  fd1;
    //打开已经存在的文件 
    /*fd = open("hello.c", O_RDWR );
    if(fd == -1)
    {
        perror("open file");
        exit(1);
    }
*/
   fd1= open("myhello.c", O_RDWR | O_TRUNC );
  if(fd1 == -1)
  {
    perror("open file1");
    exit(1);
  } 

    //关闭文件
    int ret = close(fd1);
    if(ret == -1)
    {
        perror("close file"); 
    }
    printf("ret = %d\n", ret);
    return 0;
}
