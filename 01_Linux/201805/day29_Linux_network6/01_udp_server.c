#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>



#define SERV_PORT 8000

int main()
{
    struct sockaddr_in servaddr, cliaddr;
    socklen_t cliaddr_len;
    int sockfd;
    char buf[BUFSIZ];
    char str[INET_ADDRSTRLEN];
    int i, n;

    sockfd = socket(AF_INET, SOCK_DGRAM,0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    printf("Accepting, connection ...\n");
    while(1){
        cliaddr_len = sizeof(cliaddr);
        n = recvfrom(sockfd, buf, BUFSIZ,0, (struct sockaddr*)&cliaddr, &cliaddr_len);
        if(n == -1)
            perror("recvfrom error");
        printf("received from %s at PORT %d\n", inet_ntop(AF_INET, &cliaddr.sin_addr,str, sizeof(str)), ntohs(cliaddr.sin_port));

        for(i = 0; i < n; i++)
            buf[i] = toupper(buf[i]);
        n = sendto(sockfd, buf, n, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
        if(n == -1)
            perror("sendto error");

    }

    close(sockfd);

    return 0;

}
