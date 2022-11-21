#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

#include <stdio.h>
#include<stdlib.h>

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
    int campoVazio[7];
    char removido;
    int encadeamento;
    int idConecta; 	//sem valores repetidos
    char siglaPais[2];
    int idPoPsConectado;
    char unidadeMedida;
    int velocidade;
    char nomePoPs[30];
    char nomePais[30];
} Registro;


typedef struct cabecalho_arvore{
	char status;
	int noRaiz;
	int nroChavesTotal;
    int alturaArvore;
    int RRNproxNo;
} Cabecalho_Arvore;

typedef struct registro_arvore{
	char folha;
	int nroChavesNo;
    int alturaNo;
    int RRNdoNo;
    int P1;
    int C1;
    int PR1;
    int P2;
    int C2;
    int PR2;
    int P3;
    int C3;
    int PR3;
    int P4;
    int C4;
    int PR4;
    int P5;
} Registro_Arvore;

#endif
