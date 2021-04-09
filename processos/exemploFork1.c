#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void exemploFork()
{
    if( fork() == 0 )
    {
        printf("\n:: Pai \n");
    }
    else
    {
        printf("\n::: Filho \n");
    }
}

int main()
{
    printf("\n\nExemplo Fork\n");

    exemploFork();

    return 0;
}
