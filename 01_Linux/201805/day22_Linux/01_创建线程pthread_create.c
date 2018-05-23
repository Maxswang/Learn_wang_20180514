#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void *thrd_func(void *arg)
{
    printf("In thread: thread id = %lu, pid =%u\n",pthread_self(),getpid());//子线程ID
    return NULL;
}

int main()
{

    pthread_t  tid;
    int ret;

    printf("In main 1: thread id =%lu, pid=%u\n", pthread_self(), getpid()); // 主控线程
    ret = pthread_create(&tid, NULL, thrd_func, NULL);
    if(ret != 0)
    {
        fprintf(stderr, "ptrhead_create error:%s\n", strerror(ret));
        exit(1);
    }
    sleep(1);
    printf("In main 2: thread id =%lu, pid=%u\n", pthread_self(), getpid()); // 主控线程
    return 0;
}
