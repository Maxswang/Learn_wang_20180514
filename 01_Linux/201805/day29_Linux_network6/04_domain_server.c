#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

int main()
{

    int lfd, cfd, len, size, i;
    struct sockaddr_un servaddr, cliaddr;
    char buf[4096];

    lfd = socket(AF_UNIX, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_UNIX;
    strcpy(servaddr.sun_path, "servaddr.socket");

    len = offsetof(struct sockaddr_un, sun_path) + strlen(servaddr.sun_path);
    unlink("servaddr.socket");
    bind(lfd,(struct sockaddr*)&servaddr, len);

    listen(lfd, 20);
    printf("Accept ...\n");
    while(1){
        len = sizeof(cliaddr);
        cfd = accept(lfd, (struct sockaddr*)&cliaddr, (socklen_t *)&len);

        len -= offsetof(struct sockaddr_un,  sun_path);
        cliaddr.sun_path[len] = '\0';
        printf("client bind filename %s\n", cliaddr.sun_path);
        while((size = read(cfd, buf, sizeof(buf)))>0)
        {
            for(i = 0; i < size; i++)
                buf[i] = toupper(buf[i]);
            write(cfd, buf, size);
        }
        close(cfd);
    
    }
}
