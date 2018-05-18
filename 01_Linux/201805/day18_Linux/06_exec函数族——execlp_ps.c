#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main()
{
    int fd;
    fd = open("ps.out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd < 0)
    {
        perror("open ps.out error");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO);

    execlp("ps","ps", "-aux", NULL);
    //close(fd);
    return 0;
}
