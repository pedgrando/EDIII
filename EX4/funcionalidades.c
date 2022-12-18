#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "miscelaneous.h"
#include "funcoes_io.h"
#include "data_structures.h"
#include "funcionalidades.h"
#include "limits.h"
#include "pilha.h"
#include "funcoes_principais.h"

// FUNCIONALIDADE 11

// Le o arquivo binario de registros construindo o grafo. A função retorna o número de vértices do grafo construído e 
// é usada nas outras funcionalidades, já que em todas exige-se a montagem do grafo. A impressão ordenada dos vértices
// é feita na main usando o retorno dessa funcionalidade.

int funcionalidade11(FILE *file, Cabecalho *header, Grafo *grafo){
    Registro *Register = (Registro*) malloc(sizeof(Registro));
    int num_vertices = 0;

    fseek(file, 960, SEEK_SET); // pula o header
    
    char aux;    
    while(fread(&aux, sizeof(char), 1, file) != 0){


		ResetaRegistro(Register);

		// le um registro nulo

		LeRegistroBin(Register, file); 

		if(Register->unidadeMedida == 'G') ConverteVelocidade(Register); 	// converte a velocidade que estiver em Gbps para Mbps
            
	    if(grafo[Register->idConecta - 1].idConecta == - 1){	// se a lista do vértice de número idConecta tiver vazia, preenche esse vértice com os dados do Registro lido
	    	grafo[Register->idConecta - 1].idConecta = Register->idConecta;
	    	strcpy(grafo[Register->idConecta - 1].nomePoPs, Register->nomePoPs);
	    	strcpy(grafo[Register->idConecta - 1].nomePais, Register->nomePais);
	    	strcpy(grafo[Register->idConecta - 1].siglaPais, Register->siglaPais);
			num_vertices++;
	    }

		// verifica se o registro está conectado a algum outro id -> se o campo idPoPsConectado nao esta vazio
	    // se não tiver, adiciona o registro na lista do idConecta e na lista do idPoPsConectado
		if(Register->idPoPsConectado != -1){	
			if(!insereLista(grafo[Register->idPoPsConectado - 1].listaAdj, Register->idConecta, Register->velocidade, Register->unidadeMedida)){ 
			    PrintErro();
		   	 return -1;
	    	}
			if(!insereLista(grafo[Register->idConecta - 1].listaAdj, Register->idPoPsConectado, Register->velocidade, Register->unidadeMedida)){ 
			    PrintErro();
		   	 return -1;
	    	}

			// incrementa a quantidade de vertices adjacentes das duas listas
	    	grafo[Register->idPoPsConectado -1].numVerticesAdj++;
	    	grafo[Register->idConecta -1].numVerticesAdj++;
	    }
    }
	free(Register);
    return num_vertices;
}

// FUNCIONALIDADE 12

// Calcula a quantidade de ciclos dentro do grafo usando o algoritmo de busca em profundidade (depth-first search)

void funcionalidade12(FILE *file, Cabecalho *header, Grafo *grafo){
	int num_vertices = funcionalidade11(file, header, grafo);	

	int *cor = malloc(sizeof(int) * num_vertices);

	dfs(grafo, num_vertices, cor);

	free(cor);
}

// FUNCIONALIDADE 13

// Calcula, através do algoritmo de Edmond-Karp, qual o fluxo máximo entre dois vértices. A entrada podem ser vários
// pares de origem e destino, com o fluxo sendo calculado para cada um desses pares.

void funcionalidade13(FILE *file, Cabecalho *header, Grafo *grafo){
	int num_vertices = funcionalidade11(file, header, grafo), n;	
	
	scanf("%d", &n);

	int origem[n], destino[n];

	for(int i = 0; i < n; i++){
		scanf("%d", &origem[i]);
		scanf("%d", &destino[i]);
	}

	for(int i = 0; i < n; i++){
		EdmondKarp(grafo,num_vertices, origem[i], destino[i]);
	}

}

// FUNCIONALIDADE 14

// Calcula a distância entre uma origem e uma parada e depois dessa parada até um destino e, então, soma as duas. 
// O cálculo da distância é feito através do algoritmo de Dijkstra e a entrada pode ser n valores de origem, destino e parada.

void funcionalidade14(FILE *file, Cabecalho *header, Grafo *grafo){
	int num_vertices = funcionalidade11(file, header, grafo), n;	
	int *distancia = malloc(num_vertices* sizeof(int));
	int *predecessor = malloc(num_vertices* sizeof(int));

	scanf("%d", &n);

	int origem[n], destino[n], parada[n];

	for(int i = 0; i < n; i++){
		scanf("%d", &origem[i]);
		scanf("%d", &destino[i]);
		scanf("%d", &parada[i]);
	}

	for(int i = 0; i < n; i++){

		int dist = 0;

		// usa o algoritmo de Dijkstra para calcular a menor distância entre dois vértices
		Dijkstra(grafo, origem[i], distancia, predecessor, num_vertices);
		if(distancia[parada[i] - 1] == INT_MAX){	// se o retorno for infinito, imprime com erro na formatação pedida pela especficacao do trabalho
			printf("Comprimento do caminho entre %d e %d parando em %d: -1\n", origem[i], destino[i], parada[i]);
		} else {

			dist += distancia[parada[i] - 1];

			// usa o algoritmo de Dijkstra para calcular a menor distância da origem ate a parada
			Dijkstra(grafo, parada[i], distancia, predecessor, num_vertices);
			if(distancia[destino[i] - 1] == INT_MAX){	// se o retorno for infinito, imprime com erro na formatação pedida pela especficacao do trabalho
				printf("Comprimento do caminho entre %d e %d parando em %d: -1\n", origem[i], destino[i], parada[i]);
			} else {

				// soma a distancia da parada ate o destino à da parada ate a origem
				dist += distancia[destino[i] - 1];

				printf("Comprimento do caminho entre %d e %d parando em %d: %dMbps\n", origem[i], destino[i], parada[i], dist);
			}
		}
	}

	free(distancia);
	free(predecessor);
}




