#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define length 10
#define THREADS 2

void MostraVetor(int *vetor) {
  for(int i = 0; i < length; i++){
    printf("V[%2d] = %2d\n", i, vetor[i]);
  }
}

int SomaVetor(int *vetor) {
  int soma = 0;
  for(int i = 0; i < length; i++){
      soma += vetor[i];
  }
  return soma;
}

int SomaVetorGauss(int *vetor){
  int N = length;
  return (N * (N + 1)) / 2;
}

int main() {
    int *shmId, *shm_vetor;
    key_t key = IPC_PRIVATE;

    size_t SHM_SIZE = sizeof(int)* length;

    // Aloca segmento de memória compartilhada
    shmId = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

    if(shmId < 0) {
      perror("\n ::: Erro Alocando Memória Compartilhada! ::: \n");
      _exit(1);
    }
    
    // Faz um "Attach" da memória compartilhada de "shmId"
    shm_vetor = shmat(shmId, NULL, 0);

    if(shm_vetor == (int*) -1) {
      perror("\n ::: Erro Alocando Memória de Acesso! ::: \n");
      _exit(1);
    }

    // preenche o vetor
    for(int i = 0; i < length; i++) {
      shm_vetor[i]= i + 1;
    }

    MostraVetor(shm_vetor);
    printf("Soma: %d\n", SomaVetor(shm_vetor));
    printf("Soma Gauss: %d\n", SomaVetorGauss(shm_vetor));

    int qtdThreads = THREADS;
    bool processoPai = true;

    for(int i = 0; i < qtdThreads; i++) {
        pid_t newPID = fork();

        if(newPID < 0) {
          perror("\n ::: Erro Criando Processo! ::: \n");
          _exit(1);
        }

        if(newPID == 0) { // esse é o processo filho
          /**
           * * getpid() retorna o ID do processo atual
           * */
          printf("\n::Ola do processo[%d] %d. Soma do vetor: %d\n", i, getpid(), SomaVetorGauss(shm_vetor));
          processoPai = false;
          sleep(5);
          exit(0);
        }
    }

    if(processoPai) {
      printf("Sou pai! :::: PID = %d \n", getpid());
      exit(0);
    }

    return 0;
}

