#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mutex;   //定义锁


void *tfn(void *arg)
{
    srand(time(NULL));
    while(1)
    {
        pthread_mutex_lock(&mutex);
        printf("hello ");
        sleep(rand()%3);
        printf("world\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand()%3);
    }
    return NULL;
}

int  main()
{
    int flg = 5;
    pthread_t tid;

    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tid, NULL, tfn, NULL);
    while(flg--)
    {
        pthread_mutex_lock(&mutex);
        printf("HELLO ");
        sleep(rand()%3);
        printf("WORLD\n");
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }
    pthread_cancel(tid); // 取消线程或杀死线程
    pthread_join(tid, NULL); //  回收线程
    pthread_mutex_destroy(&mutex);
    return 0;

}
