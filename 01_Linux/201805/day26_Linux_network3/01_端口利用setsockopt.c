#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

//线程1的回调函数
void *recv_one(void *arg)
{
        printf("================recv_one================\n");
        int sockfd = (int)arg;
        while(1){
        int recv_len;
        char recv_buf[512]="";
        struct sockaddr_in client_addr;
        char cli_ip[INET_ADDRSTRLEN] = "";
        socklen_t cliaddr_len = sizeof(client_addr);

        recv_len = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&client_addr,&cliaddr_len);
        inet_ntop(AF_INET,&client_addr.sin_addr, cli_ip, INET_ADDRSTRLEN);
        printf("\nip:%s, port:%d\n", cli_ip, ntohs(client_addr.sin_port));
        printf("sockfd_one ===========data(%d):%s\n", recv_len, recv_buf);
        
        }
        return NULL;
}

//线程2的回调函数
void *recv_two(void*arg)
{
    printf("+++++++++++++recv_two++++++++++++\n");
    int sockfd = (int)arg;
    while(1)
    {
        int recv_len;
        char recv_buf[512]= "";
        struct sockaddr_in client_addr;
        char cli_ip[INET_ADDRSTRLEN]= "";
        socklen_t cliaddr_len = sizeof(client_addr);

        recv_len = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr*)&client_addr, &cliaddr_len);

        inet_ntop(AF_INET, &client_addr.sin_addr, cli_ip,INET_ADDRSTRLEN);
        printf("\nip:%s, port:%d\n", cli_ip, ntohs(client_addr.sin_port));
        printf("sockfd_two @@@@@@@@@@@ data(%d):%s\n", recv_len, recv_buf);

    
    }
    return NULL;
}


int main(int argc ,char *arg[])
{
    int sockfd_one;
    int err_log;
    sockfd_one = socket(AF_INET, SOCK_DGRAM, 0); //创建 UDP套接字
    if(sockfd_one < 0)
    {
        perror("sockfd_one");
        exit(-1);
    }

    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(8000);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt = 1;
    setsockopt(sockfd_one, SOL_SOCKET, SO_REUSEADDR,(const void*)&opt, sizeof(opt));
    err_log = bind(sockfd_one, (struct sockaddr*)&my_addr, sizeof(my_addr));
    if(err_log != 0)
    {
        perror("bind sockfd_one");
        close(sockfd_one);
        exit(-1);
    }

    pthread_t tid_one;
    pthread_create(&tid_one, NULL, recv_one, (void *)sockfd_one);

    int sockfd_two;
    sockfd_two = socket(AF_INET, SOCK_DGRAM, 0);  // 创建UDP套接字2
    if(sockfd_two < 0)
    {
        perror("sockfd_two");
        exit(-1);
    }
    
    opt = 1;
    setsockopt(sockfd_two, SOL_SOCKET, SO_REUSEADDR, (const void*)&opt, sizeof(opt));
    err_log = bind(sockfd_two, (struct sockaddr*)&my_addr, sizeof(my_addr));
    if(err_log != 0)
    {
        perror("bind sockfd_two");
        exit(-1);
    }
    
    pthread_t tid_two;
    pthread_create(&tid_two, NULL, recv_two, (void *)sockfd_two);

    while(1) ;
    close(sockfd_one);
    close(sockfd_two);

    return 0;
}
