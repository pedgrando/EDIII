#ifndef __FUNCOES_H__
#define __FUNCOES_H__

#include <stdio.h>
#include<stdlib.h>

// CONSTANTES IMPORTANTES

#define PAG_DISCO 960
#define CAB 21
#define DEL '|'
#define LIXO '$'
#define REM '*'


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

#endif
