#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <net/if.h>


#define SERV_PORT 8000
#define CLIE_PORT 9000
#define MAXLINE 1500


#define GROUP "239.0.0.2"


int main()
{
    int sockfd;
    struct sockaddr_in servaddr, clieaddr;
    char buf[MAXLINE] = "abcdefg\n";
    struct ip_mreqn group;
    
    sockfd = socket(AF_INET, SOCK_DGRAM,0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    inet_pton(AF_INET, GROUP, &group.imr_multiaddr);
    inet_pton(AF_INET,"0.0.0.0", &group.imr_address);
    group.imr_ifindex = if_nametoindex("ens33");


    setsockopt(sockfd, IPPROTO_IP,IP_MULTICAST_IF, &group, sizeof(group));
    
    bzero(&clieaddr, sizeof(clieaddr));
    clieaddr.sin_family = AF_INET;
    inet_pton(AF_INET, GROUP, &clieaddr.sin_addr.s_addr);
    clieaddr.sin_port = htons(CLIE_PORT);

    int i = 0;
    while(1){
        sprintf(buf, "wgm %d\n", i++);
        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&clieaddr, sizeof(clieaddr));
        sleep(1);
    
    }
    close(sockfd);
    return 0;
}
