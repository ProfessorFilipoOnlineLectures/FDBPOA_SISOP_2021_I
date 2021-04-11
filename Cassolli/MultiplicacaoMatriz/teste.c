#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {

int matA[3][4], matB[4][3], matR[4][4]; //variaveis
int i = 0, j = 0;

for (i=0; i<4; i++) { //laco repeticao
for (j=0; j<4; j++) { //laco
printf("Informe o valor para matriz A[%d][%d]: ", i, j); //solicitacao valor usuario
scanf("%d", &matA[i][j]); //gravando dados
}
}
printf("\n");

for (i=0; i<4; i++) { //laco repeticao
for (j=0; j<4; j++) { //laco
printf("Informe o valor para matriz B[%d][%d]: ", i, j); //solicitacao valor usuario
scanf("%d", &matB[i][j]); //gravando dados
}
}

for (i=0; i<4; i++) { //percorrendo laco
for (j=0; j<4; j++) { //percorrendo laco
matR[i][j] = matA[i][j] * matB[j][i]; //formula
printf("%d\t", matR[i][j]); //resultado
}
}
return 0;
}