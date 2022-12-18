#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "miscelaneous.h"
#include "funcoes_io.h"
#include "data_structures.h"
#include "funcionalidades.h"
#include "pilha.h"


// volta uma variavel Registro em memoria primaria a situacao em que todos os campos sao vazios

void ResetaRegistro(Registro *Register){
    Register->nomePoPs[0] = '\0';
    Register->nomePais[0] = '\0';
    Register->idConecta = -1;
    strcpy(Register->siglaPais, "$$\0");
    Register->idPoPsConectado = -1;
    Register->unidadeMedida = '$';
    Register->velocidade = -1;
}

// volta uma variavel Cabecalho em que todos os campos sao vazios

Cabecalho ResetaCabecalho(){
    Cabecalho aux;
    aux.status = '0';
    aux.topo = -1;
    aux.proxRRN = 0;
    aux.nroRegRem = 0;
    aux.nroPagDisco = 0;
    aux.qttCompacta = 0;
    return aux;
}

// descobre o numero de paginas de disco do arquivo

int getNumPag(Cabecalho *header){
	if(header->proxRRN % 15 == 0){
		return ((header->proxRRN / 15) + 1);
	} else {
		return ((header->proxRRN / 15) + 2);
	}
}

// FUNCOES PARA CONFERIR SE O CAMPO ESTA VAZIO ------------------------------------------------------------

int campovazio_int(int interger){
	if(interger == -1){
	        return 1;
	} else {
		return 0;
	}		
}

int campovazio_string(char *string){
	if(string[0] == '$'){
		return 1;
	} else {
		return 0;
	}	
}

int campovazio_string_var(char *string){
	if(string[0] == '\0'){
		return 1;
	} else {
		return 0;
	}	
}

// HASH FUNCTION PARA DESCOBRIR O CAMPO
// uma funcao hash simples: ela soma os valores dos caracteres de uma string ate o '\0' e retorna o resultado

int hashfunction(char *str){
	int i = 0;
	int result = 0;
	while(str[i] != '\0'){
		result += str[i];	
		i++;
	}
	return result;
}

void ConverteVelocidade(Registro *Register){
	Register->velocidade = Register->velocidade * 1024; 
	Register->unidadeMedida = 'M'; 
}

lista *cria_lista(){
	lista *li = malloc(sizeof(lista));
	if(li == NULL){
		exit(-1);
	}
	return li;
}

void libera_lista(lista *li){
	no *aux1, *aux2;
	if(li == NULL || *li == NULL){
		return;		
	}
	aux1 = *li;
	while(aux1 != NULL){
		aux2 = aux1;
		aux1 = aux1->prox;
		free(aux2);
	}
	free(aux2);
}

int insereLista(lista *li, int idPoPs, int velocidade, char unidadeMedida){
	if(li == NULL) return 0;

	no *novo_dado = malloc(sizeof(no));

	// copia dos dados a inserir para o novo no
	
	novo_dado->idPoPs = idPoPs;
	novo_dado->velocidade = velocidade;
	novo_dado->unidadeMedida = unidadeMedida;

	if(*li == NULL){
		novo_dado->prox = *li;
		*li = novo_dado;
	} else {
		no *aux1 = *li;
		no *aux2 = aux1;
		while(aux1 != NULL && aux1->idPoPs < idPoPs){
			aux2 = aux1;
			aux1 = aux1->prox;	
		}

		if(aux1 != NULL && aux1->idPoPs == idPoPs){
			if((aux1->velocidade > velocidade && velocidade != -1) || aux1->velocidade == -1){
				aux1->velocidade = velocidade;
				aux1->unidadeMedida = unidadeMedida;
			}
		} else if (aux1 == *li){
			novo_dado->prox = aux1;
			*li = novo_dado;
		} else {
			novo_dado->prox = aux2->prox;		
			aux2->prox = novo_dado;
		}
	}
		return 1;
}

int buscaLista(lista *li, int idConectaBuscado){
	if(li == NULL || *li == NULL) return 0;

	no *aux = *li;
	
	while(aux != NULL && aux->idPoPs != idConectaBuscado){
		aux = aux->prox;
	}

	if( aux == NULL){
	       	return 0;
	} else {
		return 1;
	}
}

void troca(dado *x, dado *y){
	int aux1 = x->idConecta;
	int aux2 = x->velocidade;
	x->idConecta = y->idConecta;
	x->velocidade = y->velocidade;
	y->idConecta = aux1;
	y->velocidade = aux2;
}

void trocaInt(int *x, int *y){
	int aux = *x;
	*x = *y;
	*y = aux;
}

int min(int x, int y){
	if(x < y){
		return x;
	} else {
		return y;
	}
}

void push(queue *q, int id){
	if(q == NULL){
		return;
	}

	elemento_queue *no = malloc(sizeof(elemento_queue));
	no->id = id;

	if(*q == NULL){
		*q = no;
		no->prox = NULL;
	} else {
		no->prox = *q;
		*q = no;
	}
}

int pop(queue *q){
	if(q == NULL || *q == NULL){
		return -1;
	}

	int id = (*q)->id;

	elemento_queue *aux = (*q);
	(*q) = (*q)->prox;

	free(aux);
	return id;
}

void libera_queue(queue *q){
	if(q == NULL || *q == NULL){
		return;
	}

	elemento_queue *aux1 = (*q), *aux2;
	while(aux1 != NULL){
		aux2 = aux1;
		aux1 = aux1->prox;
		free(aux2);
	}
}

queue *cria_queue(){
	queue *q = malloc(sizeof(queue));

	*q = NULL;
	return q;

}











