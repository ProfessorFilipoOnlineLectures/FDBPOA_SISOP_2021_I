/*
** Multiplicação de Matrizes Quadradas (N x N)
** Prof. Filipo Mór - filipomor.com
** 24 de março de 2021
**
**Alterado por Diego Cassolli
**Tarefa 3
** 1 - adaptar o código visto em aula para:
**  a) utilizar as duas abordagens de indexação de matrizes vistas na Aula 02; feito o/
**      M [linha,coluna] -> v[linha * largura + coluna]
**      M [linha, coluna] -> v[coluna * altura + coluna]
**  b) trabalhar com diferentes valores de N (tamanho de matrizes). feito o/
**  c) permitir o funcionamento com matrizes que nao sejam quadradas.
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MostraMatriz(int Altura, int Largura, int* M, char* Titulo)
{
    int L, C; //Linha e Coluna
    printf(" %s \n", Titulo);
    for(L = 0; L < Altura; L++)
    {
        for(C = 0; C < Largura; C++)
        {
            printf(" %2d ", M[L * Altura + C]);
        }
        printf("\n");
    }
}

void PreencheMatriz(int Altura, int Largura, int* M, int Valor)
{
    int L, C; //Linha e Coluna

    for(L = 0; L < Altura; L++)
    {
        for(C = 0; C < Largura; C++)
        {
            M[L * Altura + C] = Valor;
        }
    }

}

int main()
{

    int linhaA  = 0, colunaA = 0, linhaB  = 0, colunaB = 0, ab = 0 , at = 1 ;

    //printf("\n Automático? 0 ou 1");
    //scanf("%d",&at);

    if(at = 1){
        linhaA  = 3, colunaA = 4, linhaB  = 4, colunaB = 3, ab = 1;
    }else{
        printf("\n Informe o número linhas da matriz A : ");
        scanf("%d",&linhaA);

        printf("\n Informe o número colunas da matriz A : ");
        scanf("%d",&colunaA);

        printf("\n Informe o número linhas da matriz B : ");
        scanf("%d",&linhaB);

        printf("\n Informe o número colunas da matriz B : ");
        scanf("%d",&colunaB);

        printf("\n Qual abordagem? ");
        scanf("%d",&ab);
    }

    int* Ma = (int*)malloc(sizeof(int) * linhaA * colunaA);
    if ( Ma == NULL )
    {
        printf("\nErro alocando memoria! \n");
        exit( EXIT_FAILURE );
    }

    int* Mb = (int*)malloc(sizeof(int) * linhaB * colunaB);
    if ( Mb == NULL )
    {
        printf("\nErro alocando memoria! \n");
        exit( EXIT_FAILURE );
    }

    int linhaC = linhaB;
    int colunaC = colunaA;

    int* Mc = (int*)malloc(sizeof(int) * linhaC * colunaC);
    if ( Mc == NULL )
    {
        printf("\nErro alocando memoria! \n");
        exit( EXIT_FAILURE );
    }

    PreencheMatriz(linhaA, colunaA, Ma, 1);
    PreencheMatriz(linhaB, colunaB, Mb, 3);
    PreencheMatriz(linhaC, colunaC, Mc, 0);

    MostraMatriz(linhaA, colunaA, Ma, " Matriz A ");
    MostraMatriz(linhaB, colunaB, Mb, " Matriz B ");
    MostraMatriz(linhaC, colunaC, Mc, " Matriz C ");
/*
**  a) utilizar as duas abordagens de indexação de matrizes vistas na Aula 02;
**      M [linha,coluna] -> v[linha * largura + coluna]
**      M [linha, coluna] -> v[coluna * altura + coluna]
*/
    int L, C, K;

        for(L=0; L<linhaC; L++)
        {
            for(C=0; C<colunaC; C++)
            {
                if(ab == 1){
                    printf("\n Abordagem 1\n ");
                    for(K=0; K <linhaC; K++)
                    {
                        printf("\n INICIO");

                        printf("Linha %2d ", L); printf("\n");
                        printf("Coluna %2d ", C); printf("\n");
                        printf("ColunaC %2d ", colunaC); printf("\n");
                        printf("ColunaA %2d ", colunaA); printf("\n");
                        printf("LinhaB %2d ", linhaB); printf("\n");
                        printf("K %2d ", K); printf("\n");


                        Mc[L * colunaC + C] += Ma[L * colunaA + K] * Mb[K * linhaB + C];
                        printf("Mc %2d ", Mc[L * colunaC + C]); printf("\n");
                        printf("Mc valor %2d ", L * colunaC + C); printf("\n");

                        printf("\n FIM");
                        MostraMatriz(linhaB, colunaA, Mc, " Matriz C ");
                        system("read -p 'dsds' var");
                    }
                }else{
                    printf("\n Abordagem 2\n ");
                    for(K=0; K<colunaA; K++)
                    {
                        Mc[L * colunaC + C] += Ma[C * linhaA + K] * Mb[K * colunaB + L];
                    }
                }
            }
        }

    MostraMatriz(linhaB, colunaA, Mc, " Matriz C ");
    return 0;
}
