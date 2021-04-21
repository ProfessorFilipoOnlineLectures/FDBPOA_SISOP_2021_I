#include <stdio.h>
#include <stdlib.h>

geraImagem(int *I,int tamanho){

    for(int l = 0; l < tamanho; l++)
    {
        for(int c = 0; c < tamanho; c++)
        {
            if ((l == 1) & (c == 1 || c == 3 || c == 4 || c == 5))
            {
                I[l * tamanho + c] = 1;
            }else if ((l == 2 || l == 3 || l == 4) & (c == 1 || c == 5 ))
            {
                I[l * tamanho + c] = 1;
            }else if ((l == 5) & (c == 1 || c == 2 || c == 3 || c == 4 || c == 5 ))
            {
                I[l * tamanho + c] = 1;
            }else if ((l == 7 || l == 8 || l == 9 || l == 10 || l ==11 ) & (c == 7 || c == 9)){
                I[l * tamanho + c] = 1;
            }else if ((l == 9) & (c == 8 || c == 10 || c == 11)){
                I[l * tamanho + c] = 1;
            }else{
                I[l * tamanho + c] = 99;
            }
        
        }
    }
}

void MostraImagem(int Altura, int Largura, int* M, char* Titulo)
{
    printf(" %s \n", Titulo);
    /*
        Para exibir o número das colunas
    */
    for(int col = 0; col < Largura; col++){
        if (col == 0 ){
           printf("      %2d|", col); 
        }else if (col == (Largura-1)){
            printf(" %2d|\n", col);
        }else{
           printf(" %2d|", col);
        }
    }
    for(int L = 0; L < Altura; L++)
    {
        /*
        Para exibir o número das linhas
        */
        printf(" %2d |", L);

        for(int C = 0; C < Largura; C++)
        {
            printf(" %2d ", M[L * Altura + C]);
        }
        printf("\n");
    }
}
/*
void ImagemVetor(vetor,tamanho){
    int* vetor = (int*)malloc(sizeof(int) * tamanho * tamanho);
    if ( vetor == NULL )
    {
        printf("\nErro alocando memoria! \n");
        exit( EXIT_FAILURE );
    }

}
*/
void ProcuraPontoImagem(int *I,int tamanho){
    //ImagemVetor('Imagem1',tamanho);
    int* ImagemA = (int*)malloc(sizeof(int) * tamanho * tamanho);
     if ( ImagemA == NULL )
    {
        printf("\nErro alocando memoria! \n");
        exit( EXIT_FAILURE );
    }
    int p = 0;
    for(int l = 0; l < tamanho; l++)
    {
        for(int c = 0; c < tamanho; c++)
        {   
            if (I[l * tamanho + c] == 1){
                
                //printf("[%2d].", l);
                ImagemA[p] = l;
                //printf("[%2d].", ImagemA[p]);
                p++;
                //printf("[%2d].", c);
                ImagemA[p] = c;
                //printf("[%2d].", ImagemA[p]);
                p++;
            }
            ProcuraPontosImagem(I, ImagemA, tamanho, p);
        }
    }
    /* Debug
    for(int z=0; z < tamanho*tamanho; z++){
        if( z % 2 == 0){
           printf("ImagemA[%2d] = [%2d].",z, ImagemA[z]);
        }else{
           printf("ImagemA[%2d] = [%2d]\n",z, ImagemA[z]);
        }
    }*/
    
}

void ProcuraPontosImagem(int *I, int *ImagemA, int tamanho, int p){
    
    for(int l = ImagemA[0]; l < tamanho; l++)
    {
        for(int c = ImagemA[1]; c < tamanho; c++)
        {   
            printf("linha = %2d coluna = %2d ",ImagemA[0],ImagemA[1]);
            return 1;
        }
    }

}

int main()
{
    int tamanho = 14;

    int* I = (int*)malloc(sizeof(int) * tamanho * tamanho);
    if ( I == NULL )
    {
        printf("\nErro alocando memoria! \n");
        exit( EXIT_FAILURE );
    }

    geraImagem(I, tamanho);
    MostraImagem(tamanho, tamanho, I, " Imagem Gerada:");
    ProcuraPontoImagem(I,tamanho);
    
    return 0;
}