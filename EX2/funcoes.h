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
    int campoVazio;
    char removido;
    int encadeamento;
    unsigned int idConecta; //sem valores repetidos
    char siglaPais[2];
    int idPoPsConectado;
    char unidadeMedida;
    int velocidade;
    char nomePoPs[30];
    char nomePais[30];
} Registro;

Cabecalho InicializaStructCabecalho();

Cabecalho getHeader(FILE* file);


//FUNCOES FORNECIDAS 

void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);

//FUNCOES DE MANIPULAÇÃO DE ARQUIVOS

void CriaHeader(FILE *arq_out, Cabecalho *header);

void PreencheLixo(FILE *file);

int LeRegistro(FILE *file_in, Registro *Register);

void TransfereDados(FILE *file_in, FILE *file_out);

void EscreveRegistro(FILE *file_out, Registro *Register);

int ChecaStatus(FILE *file_in);

#endif
