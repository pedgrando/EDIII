#ifndef __FUNCOES_H__
#define __FUNCOES_H__

#include <stdio.h>
#include<stdlib.h>

#define PAG_DISCO 960
#define CAB 20
#define DEL '|'
#define LIXO '$'
#define REM '*'


//STRUCTS DOS DADOS

typedef struct cabecalho{
	char status;
	int topo;
	int proxRRN;
    int nroRegRem;
    int nroPagDisco;  //pagina tem 960 bytes
    int qttCompacta; 
} Cabecalho;

typedef struct registro{
    char removido;
    int encadeamento;
    unsigned int idConecta; //sem valores repetidos
    char siglaPais[2];
    int idPoPsConectado;
    char unidadeMedida;
    int velocidade;
    char *nomePoPs;
    char *nomePais;
} Registro;

Cabecalho InicializaStructCabecalho();

//FUNCOES FORNECIDAS 

void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);

//FUNCOES DE MANIPULAÇÃO DE ARQUIVOS

void CriaHeader(FILE *arq_out, Cabecalho *header);

void PreencheLixo(FILE *file);

void LeRegistro(FILE *file_in, Registro *Register);

void TransfereDados(FILE *file_in, FILE *file_out);

#endif
