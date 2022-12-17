#ifndef __PILHA_H__
#define __PILHA_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dado_heap{
	int idConecta;
	int velocidade;
} dado;

typedef struct heap{
	dado *dados;
	int capacidade;
	int tam_heap;
} Heap;


void sobeHeap(Heap *h, int *pos_heap, int pos_dado);

void insere(Heap *h, int *pos_heap, dado x);

void desceHeap(Heap *h, int *pos_heap, int pos_dado);

void removeMin(Heap *h, int *pos_heap, dado *elem);

void atualizaHeap(Heap *h, int *pos_heap, dado x);

Heap *criaHeap(int capacidade);

int filhoEsquerda(int i);

int filhoDireita(int i);

int pai(int i);

#endif



