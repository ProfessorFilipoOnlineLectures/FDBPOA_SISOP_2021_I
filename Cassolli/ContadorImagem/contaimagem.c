#include <stdio.h>
#include <stdlib.h>

geraImagem(int *I,int tamanho){

    int* Ma = (int*)malloc(sizeof(int) * tamanho * tamanho);
    if ( Ma == NULL )
    {
        printf("\nErro alocando memoria! \n");
        exit( EXIT_FAILURE );
    }

    int l, c; 

    for(l = 0; l < tamanho; l++)
    {
        for(c = 0; c < tamanho; c++)
        {
            if (c == '2' & (l == '2' || l == '4' || l == '5' || l == '6'))
            {
                Ma[l * tamanho + c] = 1;
            }else if ((c == '3' || c == '4' || c == '5') & (l == '2' || l == '5' ))
            {
                Ma[l * tamanho + c] = 1;
            }else if ((c == '6') & (l == '2' || l == '3' || l == '4' || l == '5' || l == '6' ))
            {
                Ma[l * tamanho + c] = 1;
            }else{
                Ma[l * tamanho + c] = 0;
            }
        
        }
    }
    MostraMatriz(tamanho, tamanho, Ma, " Imagem ");
}


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


int main()
{
    int tamanho = 6;
    int I[tamanho];
    geraImagem(I, tamanho);
    
    return 0;
}