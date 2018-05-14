#include <stdlib.h>
#include <stdio.h>

void f(void)
{
    int* x = malloc(10*sizeof(int));
    x[10] = 0; // 问题一： 
} //

int main(void)
{
    int i;
    f();
    printf("i=%d\n",i); // 
    return 0;
}
