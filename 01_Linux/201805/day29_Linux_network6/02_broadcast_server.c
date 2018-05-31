#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>

#define SERV_PORT 8000
#define ClI_PORT 9000
#define MAXLINE 1500


#define BROADCAST_IP "192.168.176.255"

int main()
{
    int sockfd;
    struct sockaddr_in servaddr, clieaddr;
    char buf[MAXLINE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));
    bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

    bzero(&clieaddr, sizeof(clieaddr));
    clieaddr.sin_family = AF_INET;
    clieaddr.sin_port = htons(ClI_PORT);
    inet_pton(AF_INET, BROADCAST_IP, &clieaddr.sin_addr.s_addr);
    
    int i = 0;
    while(1)
    {
        sprintf(buf, "Drink %d glasses of water\n",i++);

        sendto(sockfd, buf, strlen(buf),0, (struct sockaddr*)&clieaddr, sizeof(clieaddr));

        sleep(1);
    }

    close(sockfd);

    return 0;


}
