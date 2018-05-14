#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    pid_t pid;
    pid = fork();
    int fd = open("mytest.txt", O_CREAT | O_RDWR, 0664);

    return 0;
}