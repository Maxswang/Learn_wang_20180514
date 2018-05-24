#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

int 
void* funcA(void *arg)
{


}

void* funcB(void *arg)
{



}

int main()


{
pthread_t  p1, p2;
pthread_mutex_init(&mutex, NULL);

pthread_create(&p1,NULL, funcA, NULL);
pthread_create(&p2, NULL, funcB, NULL);


pthread_join(p1, NULL);
pthread_join(p2, NULL);

pthread_mutex_destroy(&mutex);

pthread_exit((void*)1);  // 主控线程退出
}
