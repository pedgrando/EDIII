#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "pilha.h"
#include "data_structures.h"
#include "miscelaneous.h"


void Dijkstra(Grafo *grafo, int origem, int *distancia, int *predecessor, int num_vertices){
	int i, *pos_heap = malloc(num_vertices*sizeof(int)), dist, id;
	
	dado aux;	


	for(i = 0; i < num_vertices; i++){
		distancia[i] = INT_MAX;
		predecessor[i] = -1;
	}
	distancia[origem - 1] = 0;

	Heap *h = criaHeap(num_vertices);
	for(int i = 0; i < num_vertices; i++){
		h->dados[i].idConecta = i+1;
		h->dados[i].velocidade = distancia[i];
		pos_heap[i] = i;
	}

	h->tam_heap = num_vertices;

	troca(&h->dados[origem - 1], &h->dados[0]);
	trocaInt(&pos_heap[origem - 1], &pos_heap[0]);

	while(h->tam_heap > 0){
		removeMin(h, pos_heap, &aux);	

		int vertice = aux.idConecta;
	
		// varre-se a lista de adjacencia do vertice atual e faz-se o relaxamento das arestas em relacao a ele	
		no *atual = *(grafo[vertice - 1].listaAdj);
		while(atual != NULL){
			id = atual->idPoPs;
			dist = atual->velocidade;
			if(distancia[id - 1] > distancia[vertice - 1] + dist){
				distancia[id - 1] = distancia[vertice - 1] + dist;
				predecessor[id - 1] = vertice - 1;

				aux.idConecta = id;
				aux.velocidade = dist;
				atualizaHeap(h, pos_heap, aux);
			}
			atual = atual->prox;
		}
		
	}
	free(h->dados);
	free(h);
}

