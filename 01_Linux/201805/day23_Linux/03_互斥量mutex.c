#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock;

void *funcA(void *arg)
{
    srand(time(NULL));

    while(1){
       pthread_mutex_lock(&lock);
        printf("hello ");
        sleep(rand() % 3);
        printf("world\n");
        pthread_mutex_unlock(&lock);
        sleep(rand() % 3);
    }
    
    return NULL;

}


int main()
{
    pthread_t tid;
    srand(time(NULL));
    
    pthread_mutex_init(&lock, NULL);   //  理解为 lock == 1

    pthread_create(&tid, NULL, funcA, NULL);
    while(1){
        pthread_mutex_lock(&lock);
        printf("HELLO ");
        sleep(rand() %3);
        printf("WORLD\n");
        pthread_mutex_unlock(&lock);
        sleep(rand() %3);
    
    }
    pthread_mutex_destroy(&lock);
    /* pthread_join(tid, NULL); */

    pthread_exit((void*)1);
}
