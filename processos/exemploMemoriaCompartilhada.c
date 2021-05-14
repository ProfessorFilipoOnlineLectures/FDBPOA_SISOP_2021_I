#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdbool.h>

#define length 12

struct registro
{
    pid_t PID;
    int Valor;
};

typedef struct registro Nodo_t;

int SomaGauss(int *vetor)
{
    int soma=0;
    int p,q;

    p = vetor[0];
    q = vetor[length -1];
    soma  = (p + q) * length;
    soma /= 2;

    return soma;

}

int SomaVetor(int* vetor)
{
    int i, soma=0;
    for(i=0; i<length; i++)
    {
        soma += vetor[i];
    }

    return soma;
}

int SomaSegmentoVetor(int* vetor, int posInicial, int qt)
{
    int soma=0;
    for(int i=posInicial; i <(posInicial+qt); i++)
    {
        soma += vetor[i];
    }
    return soma;
}

void MostraVetor(int *vetor)
{
    int i;
    for(i=0; i<length; i++)
    {
        printf("V[%3d] : %3d\n", i, vetor[i]);
    }
}

int main()
{

    int *shmId, *shmRetId;
    key_t key = IPC_PRIVATE;
    int *shm_array;

    size_t SHM_SIZE = sizeof(int) * length;

    if ((shmId = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0 )
    {
        perror("\n:::Erro alocando memoria compartilhada!\n");
        _exit(1);
    }

    if ((shm_array = shmat(shmId, NULL, 0)) == (int*) -1)
    {
        perror("\n:::Erro associando memoria compartilhada!\n");
        _exit(1);
    }


    //preenche o vetor
    for(int i=0; i < length; i++)
    {
        shm_array[i] = i+1;
    }

    MostraVetor(shm_array);
    printf("Soma de Gauss: %3d\n", SomaGauss(shm_array));
    printf("Somatorio do vetor: %3d\n", SomaVetor(shm_array));



    // aloca espaço para a área de retorno
    int qtThreads = 4; //
    size_t SHM_RET_SIZE = sizeof(Nodo_t) * qtThreads;
    Nodo_t* areaRetorno;

    if ((shmRetId = shmget(key, SHM_RET_SIZE, IPC_CREAT | 0666)) < 0 )
    {
        perror("\n:::Erro alocando memoria compartilhada!\n");
        _exit(1);
    }

    if ((areaRetorno = shmat(shmRetId, NULL, 0)) == (Nodo_t*) -1)
    {
        perror("\n:::Erro associando memoria compartilhada!\n");
        _exit(1);
    }

    // cria as threads e atualiza a area de controle
    bool SouPai = true;
    for(int i=0; i<qtThreads; i++)
    {

        pid_t newPID = fork();

        if (newPID < 0) // erro criando thread
        {
            perror("\n:::Erro criando thread!\n");
            _exit(1);
        }

        if (newPID == 0) // processo filho
        {
            areaRetorno[i].PID = getpid();
            areaRetorno[i].Valor =  SomaSegmentoVetor(shm_array, i * (length / qtThreads), length / qtThreads); //i + qtThreads; //getpid(); //SomaVetor(shm_array);
            SouPai = false;
            sleep(1);
            break;
        }
    }


    if ( SouPai )
    {
        // aguarda pelo retorno de todos os filhos
        int status;
        for(int i=0; i<qtThreads; i++)
        {
            waitpid(areaRetorno[i].PID, &status, 0); //sleep(1);
            printf("::::: Filho[%d]: %d ::: PID %d\n", i, areaRetorno[i].Valor, areaRetorno[i].PID);
        }
    }

    // libera a memoria compartilhada
    if (shmdt(shm_array) == -1 || shmdt(areaRetorno) == -1)
    {
        perror("\nErro desanexando memoria compartilhada!\n");
        _exit(1);
    }
    /*if (shmctl(shmId, IPC_RMID, NULL) == -1 )
    {
        perror("\nErro liberando memoria compartilhada! 1\n");
        _exit(1);
    }

    if (shmctl(shmRetId, IPC_RMID, NULL) == -1)
    {
        perror("\nErro liberando memoria compartilhada! 2\n");
        _exit(1);
    }
    */

    return 0;
}
