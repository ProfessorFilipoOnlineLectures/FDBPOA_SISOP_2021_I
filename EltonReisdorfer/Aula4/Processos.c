#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t processId;

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

void exemploGetPid()
{
    processId = fork();

    if( processId != 0 )
    {
        //processo pai
        printf("\n::: Pai - %d : %d\n", processId, getpid());
        sleep(25);
        wait(0);
    }
    else
    {
        // processo filho
        printf("\n:::: Filho - id: %d ::: processo pai: %d\n", getpid(), getppid());
        sleep(10);
    }
}

int main()
{
    printf("\n\nExemplo Fork\n");

    //exemploFork();
    exemploGetPid();

    return 0;
}

