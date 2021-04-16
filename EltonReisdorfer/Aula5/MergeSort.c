#include <stdio.h>

#define MAX 16

void mostravetor(int v[]) {
	int i, j;
	for (i = MAX-1; i >=0; i--) {
	printf("|");
	for (j = 0; j < MAX; j++) {
		if (v[j] == i){
			printf(" XXX");
		}else{
			printf("    ");
		}
	}

	printf("\n");
	}
	for (j = 0; j <= 4* MAX; j++){ 
		printf("-");    
	}
	printf("\n");
	printf ("{  %2d", v[0]);

	for (i = 1; i < MAX; i++) {
		printf (", %2d", v[i]);
	}

	printf ("}\n");

}

void merge(int *v, int l, int m, int r){
	int aux[MAX];
	int i=l,j=m+1,k=0;
	// Intercala as metades do vetor
	while(i<=m && j<=r){
		if(v[i] <= v[j]){
			aux[k++]=v[i++];
		}else{
			aux[k++]=v[j++];
		}
	}
	// Copia o restante do vetor que sobrou
	while(i<=m){
		aux[k++]=v[i++];
	}
	while(j<=r){
		aux[k++]=v[j++];
	}
	// Vamos copiar de volta para do vetor auxiliar para o vetor va_arg
	for(i=l,k=0;i<=r;i++,k++){
		v[i]=aux[k];
	}
}

void mergesort(int *v,int l,int r){
	int m=(l+r)/2;
	if(l<r){
		// Divisão
		mergesort(v,l,m);
		mergesort(v,m+1,r);
		// Intercalação das duas metades
		merge(v,l,m,r);
		//
		//mostravetor(v); // Para efeitos de debug e teste somente
	}
}

int main(){
	//
	int vetor[MAX] = {13,7,2,5,9,11,4,15,0,10,1,12,6,14,3,8};
	//
	mostravetor(vetor);
	mergesort (vetor, 0, MAX-1);
	mostravetor(vetor);
	return 0;
}
