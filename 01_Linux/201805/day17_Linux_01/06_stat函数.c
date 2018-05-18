#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char* argv[])
{
    if(argc <2)
    {
        printf("./a.out filename\n");
        exit(1);
    }
    struct stat st;
   int ret = stat(argv[1], &st);
    if(ret == -1)
    {
        perror("stat");
        exit(1);
    }
    //获取文件 大小 
    int size = (int)st.st_size;  //  需要类型转换
    printf("file size = %d\n", size);
    
    return 0;
}
