#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void foo()
{
    printf("foo() run\n");
}
int main()

{
    printf("Hello, Makefile\n");
    foo();
    return 0;
}
