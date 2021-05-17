#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdbool.h>
#include <sys/shm.h>

#define length 43

void MostraVetor(int *vetor)
{
    for(int i=0; i<length; i++)
    {
        printf("V[%2d] = %2d\n", i, vetor[i]);
    }
}

int SomaVetor(int *vetor)
{
    int soma=0;
    for(int i=0; i<length; i++)
    {
        soma += vetor[i];
    }
    return soma;
}

int SomaVetorGauss(int *vetor)
{
    int N = length;
    return (N * (N+1)) / 2;
}

int SomaSegmentoVetor(int *vetor, int posInicial, int qt)
{
    int soma=0;
    for(int i = posInicial; i < (posInicial+qt); i++)
    {
        printf("\nposInicial %d posInicial+qt %d soma %d vetor %d", posInicial, posInicial+qt, soma, vetor[i]);
        soma += vetor[i];
    }
    return soma;
}


int main()
{
    int *shmId, *shm_vetor;
    key_t key = IPC_PRIVATE;

    size_t SHM_SIZE = sizeof(int) * length;

    // aloca segmento de memoria compartilhada
    if ((shmId = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        perror("\n:::Erro alocando memoria compartilhada!\n");
        _exit(1);
    }

    if ((shm_vetor = shmat(shmId, NULL, 0)) == (int*) -1)
    {
        perror("\n:::Erro alocando memoria de acesso!\n");
        _exit(1);
    }

    // preenche o vetor
    for(int i=0; i < length; i++)
    {
        shm_vetor[i] = i+1;
    }
    MostraVetor(shm_vetor);
    printf("Soma: %d\n", SomaVetor(shm_vetor));
    printf("Soma Gauss: %d\n", SomaVetorGauss(shm_vetor));

    int qtThreads = 3;
    bool SouPai=true;

    for(int i=0; i<qtThreads; i++)
    {
        pid_t newPID = fork();

        if (newPID < 0)
        {
            perror("\n:::Erro criando processo!\n");
            _exit(1);
        }
     
        if (newPID == 0) // esse eh o processo filho!!!
        {
            //if (qtThreads == (i+1) && ((qtThreads%2) != 0 || (length%2) != 0 ))
            //{
            //um = 1; 
            //}
            int sobrou = 0;
            if (qtThreads == (i+1))
            {
            sobrou = (int)ceil((length-(length/qtThreads)*qtThreads));
            printf("Sobrou %d",sobrou);
            }

            int soma = SomaSegmentoVetor(shm_vetor, i*(length/qtThreads), (length/qtThreads)+sobrou);
            printf("\n:: Processo Filho[%d] %d. Soma do vetor: %d ::: soma segmento: %d\n", i, getpid(), SomaVetor(shm_vetor), soma);

            SouPai = false;
            sleep(1);
            exit(0);
            //break;
        }
    }

    if ( SouPai )
    {
        printf("sou o pai! : PID = %d", getpid());
        exit(0);
    }

    return 0;
}