#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "wrap.h"
#define SERV_PORT  6666 
/* #define SERV_IP "192.168.176.136" */

int main()
{
    int cli_fd;
    struct  sockaddr_in serv_addr;
    cli_fd = Socket(AF_INET, SOCK_STREAM,0);  // 使用 IPv4, 流式协议， 默认 tcp
    socklen_t serv_addr_len;
    serv_addr_len = sizeof(serv_addr);
    memset(&serv_addr, 0,serv_addr_len);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    /* inet_pton(AF_INET,SERV_IP, &serv_addr.sin_addr.s_addr); */
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    Connect(cli_fd,(struct sockaddr*) &serv_addr,serv_addr_len);
    char buf[BUFSIZ];
    while(1){
        fgets(buf, sizeof(buf),stdin);
        Write(cli_fd, buf, strlen(buf));
        int n =  Read(cli_fd, buf, sizeof(buf));
        Write(STDOUT_FILENO, buf, n);
    }




    return 0;
}
