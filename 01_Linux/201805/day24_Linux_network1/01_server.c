#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <ctype.h>

#define SER_PORT  5555
#define SER_IP "127.0.0.1"
int main()
{

    int sfd, cfd;
    struct sockaddr_in addr, cli_addr;
    socklen_t cli_addr_len;
    sfd = socket(AF_INET,SOCK_STREAM,0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SER_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sfd, (struct sockaddr*)&addr,sizeof(addr));
    
    listen(sfd, 128);
    cli_addr_len = sizeof(cli_addr);
    cfd = accept(sfd, (struct sockaddr*)&cli_addr, &cli_addr_len);
    
    char buf[BUFSIZ];
    while(1){
   int n=  read(cfd, buf, sizeof(buf));
   
    for(int i = 0; i < n ; i++)
    {
        buf[i] = toupper(buf[i]);
    }
    
    write(cfd, buf, n);
    printf("你已经输入了字符\n");
    }


    close(sfd);
    close(cfd);
    return 0;
}
