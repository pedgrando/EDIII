#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

#include <stdio.h>
#include <stdlib.h>

// CONSTANTES IMPORTANTES

#define PAG_DISCO 960
#define CAB 21
#define DEL '|'
#define LIXO '$'
#define REM '*'
#define TAM_NO 65

// CODIGO HASH DOS CAMPOS

#define IDCONECTA 906
#define SIGLAPAIS 925
#define IDPOPSCONECTADO 1503
#define UNIDADEMEDIDA 1310
#define VELOCIDADE 1040
#define NOMEPOPS 817
#define NOMEPAIS 828

// CONSTANTES PARA SELECAO DO TIPO DE BUSCA

#define CONSULTA 1
#define REMOCAO 0

//STRUCTS DOS DADOS

typedef struct cabecalho{
	char status;
	int topo;
	int proxRRN;
    int nroRegRem;
    int nroPagDisco;  	//pagina tem 960 bytes
    int qttCompacta; 
} Cabecalho;

typedef struct registro{
    int idConecta; 	//sem valores repetidos
    char siglaPais[2];
    char nomePoPs[30];
    char nomePais[30];
    int idPoPsConectado;
    char unidadeMedida;
    int velocidade;
} Registro;

typedef struct elemento{
    	int idPoPs;
    	char unidadeMedida;
    	int velocidade;
	struct elemento *prox;
} no;

typedef struct elemento *lista;

typedef struct {
		lista *listaAdj;
		int numVerticesAdj;	
    	int idConecta; 	//sem valores repetidos
 		char siglaPais[2];
    	char nomePoPs[30];
    	char nomePais[30];
} Grafo;

typedef struct elem{
	int id;
	struct elem *prox;
} elemento_queue;

typedef elemento_queue *queue;

#endif
