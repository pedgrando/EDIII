#ifndef __MISCELANEOUS_H__
#define __MISCELANEOUS_H__

#include <stdio.h>
#include<stdlib.h>

#include "data_structures.h"
#include "pilha.h"


Cabecalho ResetaCabecalho();

void ResetaRegistro(Registro *Register);

int getNumPag(Cabecalho *header);

int campovazio_int(int interger);

int campovazio_string(char *string);

int campovazio_string_var(char *string);

int hashfunction(char *str);

void ConverteVelocidade(Registro *Register);

lista *cria_lista();

void libera_lista(lista *li);

int insereLista(lista *li, int idPoPs, int velocidade, char unidadeMedida);

int insereListaInicio(lista *li, int idPoPs, int velocidade, char unidadeMedida);

int buscaLista(lista *li, int idConectaBuscado);

int temAberto(int *a, int i);

int menorDist(int *pesos, int *aberto, int num_vertices);
	
void troca(dado *x, dado *y);

void trocaInt(int *x, int *y);

void push(queue *q, int id);

int pop(queue *q);

void libera_queue(queue *q);

queue *cria_queue();

int min(int x, int y);

void libera_grafo(Grafo *g, int tam);

#endif
