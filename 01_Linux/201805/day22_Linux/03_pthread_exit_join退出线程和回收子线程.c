#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef struct{
char ch;
int var;
char str[64];

}exit_t;


void* thrd_func(void *arg)
{
    exit_t *retvar = (exit_t*)arg;

    retvar->ch = 'm';
    retvar->var = 200;
    strcpy(retvar->str, "my thread\n");

    pthread_exit((void *)retvar);
}

int main()
{
    pthread_t tid;
    int ret;
    exit_t *retval = (exit_t*)malloc(sizeof(exit_t));

    printf("In main 1: thread id = %lu, pid = %u\n", pthread_self(), getpid());
    ret = pthread_create(&tid, NULL, thrd_func, (void*)retval);
    if(ret != 0)
    {
        fprintf(stderr, "pthread_create error: %s\n",strerror(ret));
        exit(1);
    }
    pthread_join(tid, (void **)&retval);
    printf("ch = %c, var = %d, str = %s\n",retval->ch, retval->var, retval->str);


    free(retval);
    pthread_exit((void *)1);






    return 0;
}
