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

int funcionalidade11(FILE *file, Cabecalho *header, Grafo *grafo){
    Registro *Register = (Registro*) malloc(sizeof(Registro));
    int num_vertices = 0;

    fseek(file, 960, SEEK_SET); // pula o header
    
    char aux;    
    while(fread(&aux, sizeof(char), 1, file) != 0){


            ResetaRegistro(Register);

            // le um registro e imprime seu conteudo

            LeRegistroBin(Register, file); 

            if(Register->unidadeMedida == 'G') ConverteVelocidade(Register);
            
	    if(grafo[Register->idConecta - 1].idConecta == - 1){    
	    	grafo[Register->idConecta - 1].idConecta = Register->idConecta;
	    	strcpy(grafo[Register->idConecta - 1].nomePoPs, Register->nomePoPs);
	    	strcpy(grafo[Register->idConecta - 1].nomePais, Register->nomePais);
	    	strcpy(grafo[Register->idConecta - 1].siglaPais, Register->siglaPais);
		num_vertices++;
	    }

	    if(Register->idPoPsConectado != -1){
            	if(!insereLista(grafo[Register->idPoPsConectado - 1].listaAdj, Register->idConecta, Register->velocidade, Register->unidadeMedida)){ 
			    PrintErro();
		   	 return -1;
	    	}
            	if(!insereLista(grafo[Register->idConecta - 1].listaAdj, Register->idPoPsConectado, Register->velocidade, Register->unidadeMedida)){ 
			    PrintErro();
		   	 return -1;
	    	}

	    	grafo[Register->idPoPsConectado -1].numVerticesAdj++;
	    	grafo[Register->idConecta -1].numVerticesAdj++;
	    }
    }
    return num_vertices;
}

// FUNCIONALIDADE 12

void funcionalidade12(FILE *file, Cabecalho *header, Grafo *grafo){
	funcionalidade11(file, header, grafo);	











}

// FUNCIONALIDADE 13

void funcionalidade13(FILE *file, Cabecalho *header, Grafo *grafo){
	funcionalidade11(file, header, grafo);	

}

// FUNCIONALIDADE 14

void funcionalidade14(FILE *file, Cabecalho *header, Grafo *grafo){
	int num_vertices = funcionalidade11(file, header, grafo), n;	
	int *distancia = malloc(num_vertices* sizeof(int));
	int *predecessor = malloc(num_vertices* sizeof(int));

	scanf("%d", &n);

	for(int i = 0; i < n; i++){

		int dist = 0;

		int origem, parada, destino;

		scanf("%d", &origem);
		scanf("%d", &destino);
		scanf("%d", &parada);

		Dijkstra(grafo, origem, distancia, predecessor, num_vertices);
		if(distancia[parada - 1] == INT_MAX){
			printf("Comprimento do caminho entre %d e %d parando em %d: -1\n", origem, destino, parada);
			break;
		}

		dist += distancia[parada - 1];

		Dijkstra(grafo, parada, distancia, predecessor, num_vertices);
		if(distancia[destino - 1] == INT_MAX){
			printf("Comprimento do caminho entre %d e %d parando em %d: -1\n", origem, destino, parada);
			break;
		}

		dist += distancia[destino - 1];

		printf("Comprimento do caminho entre %d e %d parando em %d: %dMbps\n", origem, destino, parada, dist);
	}

	free(distancia);
	free(predecessor);
}




