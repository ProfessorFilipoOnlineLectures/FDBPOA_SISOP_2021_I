#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdbool.h>

#define length 10

void MostraVetor(int *vetor){

    for(int i = 0; i < length; i++){
        printf("V[%2d] = %2d\n", i, vetor[i]);
    }
}

int SomaVetor(int *vetor){
    int soma=0;
    for(int i = 0; i < length; i++){
        soma+= vetor[i];
    }
    return soma;
}

int SomaVetorGauss(int *vetor){
    int n = length;
    return (n*(n+1))/2;
}

int SomaSeguimentoVetor(int *vetor, int posInicial, int qt){
    int soma = 0;

    for(int i = posInicial; i < (posInicial+ qt); i++){
        soma+= vetor[i];
    }

    return soma;
}

int main()
{
    int *shmId, *shm_vetor;
    key_t key = IPC_PRIVATE;

    size_t shm_size = sizeof(int)* length;

    //Aloca segmento de memória compartilhada
    if((shmId = shmget(key, shm_size, IPC_CREAT | 0666)) < 0){
        perror("\n ::: Erro Alocando Memória Compartilhada! ::: \n");
        _exit(1);
    }

    if((shm_vetor = shmat(shmId, NULL, 0)) == (int*) - 1){
        perror("\n ::: Erro Alocando Memória de Acesso! ::: \n");
        _exit(1);
    }

    //preenche o vetor
    for(int i = 0; i < length; i++){
        shm_vetor[i]=i+1;
    }

    MostraVetor(shm_vetor);
    printf("Soma: %d\n", SomaVetor(shm_vetor));
    printf("Soma Gauss: %d\n", SomaVetorGauss(shm_vetor));

    int qtdThreads = 3;
    bool SouPai = true;

    for(int i = 0; i < qtdThreads; i++){
        pid_t newPID = fork();

        if(newPID < 0){
            perror("\n ::: Erro Criando Processo! ::: \n");
            _exit(1);
        }

        if(newPID == 0){ //esse eh o processo filho
            int soma = SomaSeguimentoVetor(shm_vetor, i*(length / qtdThreads), length / qtdThreads);
            printf("\n::Ola do processo[%d] %d. Soma do vetor: %d ::: somaSEguimento %d\n", i, getpid(), SomaVetorGauss(shm_vetor), soma);
            SouPai = false;
            sleep(5);
            exit(0);
        }
    }

    if(SouPai){
        printf("Sou pai! :::: PID = %d", getpid());
        exit(0);
    }

    return 0;
}
