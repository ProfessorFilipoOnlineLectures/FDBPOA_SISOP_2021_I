
#include <stdio.h>
#include <conio.h>

main()
{

//Definição de variaveis
int i, j, l, c, l1, c1, X;

//Entrada de dados
printf("\n Informe a quntidade de linhas da matriz A : ");
scanf("%d",&l);
printf("\n Informe a quantidade de colunas da matriz A : ");
scanf("%d",&c);
printf("\n Informe a quntidade de linhas da matriz B : ");
scanf("%d",&l1);
printf("\n Informe a quantidade de colunas da matriz B : ");
scanf("%d",&c1);
float matrizA[l][c],matrizB[l1][c1],matrizC[c][l1],Aux=0;
if(c==l1)
{
for(i=0; i<l; i++)
{
         for(j=0; j<c; j++)
         {
         printf("\n\n Informe o valor da %d%c Linha e da %d%c Coluna da Matriz A: ", i+1, 167, j+1, 167);
         scanf("%f", &matrizA[i][j]);
         }
         printf("\n");
         }
for(i=0; i<l1; i++)
{        
         for(j=0; j<c1; j++)
         {
         printf("\n\n Informe o valor da %d%c Linha e da %d%c Coluna da 2%c Matriz B: ", i+1, 167, j+1, 167, 167);
         scanf("%f", &matrizB[i][j]);
         }
         printf("\n");
         }
printf("---------------------------- 1 - Matriz Gerada ---------------------------------\n\n");
for(i=0; i<l; i++)
{        
         for(j=0; j<c; j++)
         {
         printf("%6.f", matrizA[i][j]);
         }
         printf("\n\n");
         }
printf("---------------------------- 2 - Matriz Gerada ---------------------------------\n\n");
for(i=0; i<l1; i++)
{
         for(j=0; j<c1; j++)
         {
         printf("%6.f", matrizB[i][j]);
         }
         printf("\n\n");
         }
//Processamento e saida em tela
for(i=0; i<l; i++)
{
         for(j=0; j<c1; j++)
         {
                  matrizC[i][j]=0;
                  for(X=0; X<l1; X++)
                  {
                  Aux += matrizA[i][X] * matrizB[X][j];
                  }
                  matrizC[i][j]=Aux;
                  Aux=0;
                  }
                  }
                  printf("\n\n");
printf("---------------------------- 3 - Matriz Gerada ---------------------------------\n\n");
for(i=0; i<l; i++)
{
         for(j=0; j<c1; j++)
         {
         printf("%6.f", matrizC[i][j]);
         }
         printf("\n\n");
         }
         printf("\n\n");
         }
else
{
printf("\n\n Nao ha com multiplicar as matrizes dadas ");
}

} 
