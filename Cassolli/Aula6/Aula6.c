#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct registro
{
	int Linha;
	int Coluna;
	struct registro* Proximo;
};

typedef struct registro Nodo_t;

void MostraMatriz(int* Matriz, int N, int M)
{
	int i, j;

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			printf(" %c", Matriz[i * N + j] ? '#' : '.');
		}
		printf("\n");
	}
}

void InsereNodo(int Linha, int Coluna, Nodo_t* p)
{
	Nodo_t* NovoNodo;
	NovoNodo = (Nodo_t*)malloc(sizeof(Nodo_t));
	NovoNodo->Linha = Linha;
	NovoNodo->Coluna = Coluna;

	NovoNodo->Proximo = p->Proximo;
	p->Proximo = NovoNodo;

}

void MostraLista(Nodo_t* Lista)
{
	if (Lista != NULL)
	{
		printf(" ::: L: %3d :: C: %3d\n", Lista->Linha, Lista->Coluna);
		MostraLista(Lista->Proximo);
	}
}

bool ExisteNodo(int Linha, int Coluna, Nodo_t* Lista)
{
	bool retorno = false;

	if (Lista == NULL)
	{
		retorno = false;
	}
	else if (Lista->Linha == Linha && Lista->Coluna == Coluna)
	{
		retorno = true;
	}
	else retorno = ExisteNodo(Linha, Coluna, Lista->Proximo);

	return retorno;

}

int SegueTrilha(int Linha, int Coluna, int* Matriz, int N, int M, Nodo_t* Lista)
{
	int qtInserida = 0;

	// a posição ja esta na lista? E esta preenchida?
	if (ExisteNodo(Linha, Coluna, Lista) || Matriz[Linha * N + Coluna] != 1)
	{
		return qtInserida;
	}

	// Insere o ponto na lista
	InsereNodo(Linha, Coluna, Lista);
	qtInserida++;

	// testa as células ao redor do ponto inicial
	if (Linha > 0) // acima
	{
		qtInserida += SegueTrilha(Linha - 1, Coluna, Matriz, N, M, Lista);
	}

	if (Linha < N-1) // abaixo
	{
		qtInserida += SegueTrilha(Linha + 1, Coluna, Matriz, N, M, Lista);
	}

	if (Coluna > 0) // esquerda
	{
		qtInserida += SegueTrilha(Linha, Coluna - 1, Matriz, N, M, Lista);
	}

	if (Coluna < M - 1) // direita
	{
		qtInserida += SegueTrilha(Linha, Coluna + 1, Matriz, N, M, Lista);
	}

	if (Linha > 0 && Coluna > 0) // diagonal superior esquerda
	{
		qtInserida += SegueTrilha(Linha - 1, Coluna - 1, Matriz, N, M, Lista);
	}

	if (Linha > 0 && Coluna < M - 1) // diagonal superior direita
	{
		qtInserida += SegueTrilha(Linha - 1, Coluna + 1, Matriz, N, M, Lista);
	}

	if (Linha < N - 1 && Coluna > 0) // diagonal inferior esquerda
	{
		qtInserida += SegueTrilha(Linha + 1, Coluna - 1, Matriz, N, M, Lista);
	}

	if (Linha < N - 1 && Coluna < M - 1) // diagonal inferior direita
	{
		qtInserida += SegueTrilha(Linha + 1, Coluna + 1, Matriz, N, M, Lista);
	}

	return qtInserida;
}


int main()
{
	int Matriz[] = {
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0,
		0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0,
		1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
		1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0,
		0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
		0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0
	};

	int N = 20, M = 20; // N: qt linhas e M qt colunas

	Nodo_t* CabecaLista = NULL;
	CabecaLista = (Nodo_t*)malloc(sizeof(Nodo_t));
	CabecaLista->Linha = -1;
	CabecaLista->Coluna = -1;
	CabecaLista->Proximo = NULL;


	MostraMatriz(Matriz, N, M);
	
	int L, C, qtNodos=0, qtObjetos=0;
	for (L = 0; L < N; L++)
	{
		for (C = 0; C < M; C++)
		{
			qtNodos = SegueTrilha(L, C, Matriz, N, M, CabecaLista);
			if (qtNodos > 0) qtObjetos++;
		}
	}

	printf("\n::: %d objetos identificados!\n", qtObjetos);

	// 7 0
	//int qt = SegueTrilha(16, 14, Matriz, N, M, CabecaLista);
	//MostraLista(CabecaLista);
	//printf("\nInseriu %d elementos\n", qt);

	/*if (ExisteNodo(5, 1, CabecaLista))
	{
		printf("Nodo [%d:%d] existe!\n", 5, 1);
	}
	else printf("Nodo não existe!\n"); */

}
