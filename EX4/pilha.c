#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "miscelaneous.h"
#include "pilha.h"

// Funcoes relacionadas à pilha, usada no algoritmo de Djikstra

Heap *criaHeap(int capacidade){
	Heap *h = malloc(sizeof(Heap));
	h->dados = calloc(capacidade, sizeof(dado));
	h->capacidade = capacidade;
	h->tam_heap = 0;
	return h;
}

int filhoEsquerda(int i){
	return (2*i + 1);
}

int filhoDireita(int i){
	return (2*i + 2);

}

int pai(int i){
	return (i-1)/2;
}


//sobe o elemento h->dados[pos_dado] ate restaurar a heap
void sobeHeap(Heap *h, int *pos_heap, int pos_dado){
	int x = pos_dado;

	while(x > 0 && h->dados[pai(x)].velocidade > h->dados[x].velocidade){
		troca(&h->dados[pai(x)], &h->dados[x]);
		trocaInt(&pos_heap[h->dados[x].idConecta - 1], &pos_heap[h->dados[pai(x)].idConecta - 1]);
		x = pai(x);
	}
}

void insere(Heap *h, int *pos_heap, dado x){
	h->dados[h->tam_heap] = x;
	pos_heap[x.idConecta - 1] = h->tam_heap;
	sobeHeap(h, pos_heap, h->tam_heap);
	h->tam_heap++;
}

void desceHeap(Heap *h, int *pos_heap, int pos_dado){
	int x = pos_dado, y;
 	while(filhoEsquerda(x) < h->tam_heap && (h->dados[filhoEsquerda(x)].velocidade < h->dados[x].velocidade || (filhoDireita(x) < h->tam_heap && h->dados[filhoDireita(x)].velocidade < h->dados[x].velocidade))){
		y = filhoEsquerda(x);
		if(filhoDireita(x) < h->tam_heap && h->dados[filhoDireita(x)].velocidade < h->dados[y].velocidade){
			y = filhoDireita(x);
		}
		troca(&h->dados[x], &h->dados[y]);
		trocaInt(&pos_heap[h->dados[x].idConecta - 1], &pos_heap[h->dados[y].idConecta - 1]);
		x = y;
	}
}

void removeMin(Heap *h, int *pos_heap, dado *elem){
	elem->idConecta = h->dados[0].idConecta;
	elem->velocidade = h->dados[0].velocidade;
	troca(&h->dados[0], &h->dados[h->tam_heap - 1]);
	trocaInt(&pos_heap[h->dados[0].idConecta - 1], &pos_heap[h->dados[h->tam_heap - 1].idConecta - 1]);
	h->tam_heap--;
	desceHeap(h, pos_heap, 0);

}

void atualizaHeap(Heap *h, int *pos_heap, dado x){
	int pos_dados_x = pos_heap[x.idConecta - 1];
	h->dados[pos_dados_x].velocidade = x.velocidade;
	sobeHeap(h, pos_heap, pos_dados_x);
}









