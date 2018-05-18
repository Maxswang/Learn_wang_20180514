#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#define BUFSIZE 4096

int main()
{

    int n;
    char buf[BUFSIZE];
    memset(buf, 0, BUFSIZE);
    n = read(STDIN_FILENO,buf,BUFSIZE); 
    while(n)
        if(write(STDOUT_FILENO,buf,n) != n)
            perror("write error");
    if(n < 0)
        perror("read error");
    exit(0);
}
