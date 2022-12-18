#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "pilha.h"
#include "data_structures.h"
#include "miscelaneous.h"
#include "funcoes_principais.h"


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

void dfs(Grafo *grafo, int num_vertices, int *cor){
	int ciclos = 0;

	for(int i = 0; i < num_vertices; i++){
		cor[i] = 0;
	}

	for(int i = 0; i < num_vertices; i++){
		if(cor[i] == 0) dfs_loop(grafo, &ciclos, i, cor);	
	}

	printf("Quantidade de ciclos: %d\n", ciclos);
}

void dfs_loop(Grafo *grafo, int *ciclos, int x, int *cor){
	cor[x] = 1;	

	no *aux = *grafo[x].listaAdj;
	
	while(aux != NULL){
		if(cor[aux->idPoPs - 1] == 0){
	  		dfs_loop(grafo, ciclos, aux->idPoPs - 1, cor);	
		} else if(cor[aux->idPoPs - 1] == 2){
			(*ciclos)++;
		}
		aux = aux->prox;	
	}
	
	cor[x] = 2;
}

void edmondkarp(Grafo *grafo, int num_vertices, int origem, int destino){
	int **fluxo = malloc(sizeof(int *) * num_vertices);	
	int **capacidade = malloc(sizeof(int *) * num_vertices);

	for(int i = 0; i < num_vertices; i++){
		fluxo[i] = malloc(sizeof(int) * num_vertices);
		capacidade[i] = malloc(sizeof(int) * num_vertices);
		
	}


	no *aux = NULL;

	for(int i = 0; i < num_vertices; i++){
		aux = *grafo[i].listaAdj;	
		while(aux != NULL){
			capacidade[i][aux->idPoPs - 1] = aux->velocidade;
			fluxo[i][aux->idPoPs - 1] = 0;
			aux = aux->prox;
		}
	}


	queue *q = cria_queue();

	int *antecessores = malloc(sizeof(int) * num_vertices);
	int fluxo_max = 0;
	
	while(1){
		for(int i = 0; i < num_vertices; i++){
			antecessores[i] = -1;
		}	

		
		push(q, origem);	
		
		while(*q != NULL){
			int id = pop(q);		

			no *atual = *grafo[id - 1].listaAdj;
			while(atual != NULL){
				if(antecessores[atual->idPoPs - 1] == -1 && fluxo[id -1][atual->idPoPs - 1] < capacidade[id - 1][atual->idPoPs - 1]){
					antecessores[atual->idPoPs - 1] = id;
					push(q, atual->idPoPs);
				}	
				atual = atual->prox;
			}
		}

		if(antecessores[destino - 1] == -1){
			break;
		} else {
			int fluxo_min = INT_MAX;

			int filho = destino;
			int pai = antecessores[filho - 1];
			
			while(filho != origem){
				fluxo_min = min(fluxo_min, capacidade[pai - 1][filho - 1] - fluxo[pai - 1][filho - 1]);
				filho = pai;
				pai = antecessores[pai - 1];
				
			}	
	
			filho = destino;
			pai = antecessores[filho - 1];
	
			while(filho != origem){
				fluxo[pai - 1][filho - 1] += fluxo_min;
				fluxo[filho - 1][pai - 1] -= fluxo_min;
				filho = pai;
				pai = antecessores[pai - 1];
				
			}	
			
			fluxo_max += fluxo_min;
		}
	}
	
	if(fluxo_max != 0){
		printf("Fluxo máximo entre %d e %d: %d Mbps\n", origem, destino, fluxo_max);
	} else {
		printf("Fluxo máximo entre %d e %d: -1\n", origem, destino);
	}

	libera_queue(q);
	free(q);

	free(antecessores);
	for(int i = 0; i < num_vertices; i++){
		free(fluxo[i]);
		free(capacidade[i]);
		
	}
	free(fluxo);
	free(capacidade);

}
































