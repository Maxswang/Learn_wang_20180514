#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void* thrd_func(void *arg)
{
    // int i = *((int*)arg);
    int i = (int)arg;
    sleep(i);
    printf("%dth thread: thread id =%lu, pid =%u\n",i+1, pthread_self(), getpid());
    return NULL;
}

int main()
{
    pthread_t tid[5];
    int ret, i;
    for(i = 0; i < 5; i++)
    {
        ret = pthread_create(&tid[i], NULL,thrd_func, (void*)i);// 此处 第四个参数 用传值方式 但需要强转类型
        // ret = pthread_create(&tid, NULL, thrd_func, (void*)&i);
        if(ret != 0)
        {
            fprintf(stderr, "pthread_create error:%s\n", strerror(ret));
            exit(1);
        }
    }
    sleep(i);

return 0;
}
