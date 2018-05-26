#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "wrap.h"
#define SERV_PORT 6666
#define SERV_IP "192.168.176.136"




int main()
{
    int serv_fd, cli_fd, n;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_addr_len = sizeof(cli_addr);
    char buf[BUFSIZ];
    serv_fd = Socket(AF_INET,SOCK_STREAM,0 );
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET,SERV_IP,&serv_addr.sin_addr.s_addr);
    int ret = Bind(serv_fd,(struct sockaddr*) &serv_addr, sizeof(serv_addr));
    ret = Listen(serv_fd, 128);

    cli_fd = Accept(serv_fd, (struct sockaddr*)&cli_addr,&cli_addr_len);
    char buf1[cli_addr_len];
    printf("登录的IP: %s, 端口：%d\n", inet_ntop(AF_INET,&cli_addr.sin_addr,buf1,cli_addr_len),ntohs(cli_addr.sin_port));

    while(1){
        n = Read(cli_fd, buf, sizeof(buf));
        for(int i = 0 ; i < n; i++)
            buf[i] = toupper(buf[i]);
        Write(cli_fd, buf, n);
    }
    close(serv_fd);
    close(cli_fd);


    return 0;
}
