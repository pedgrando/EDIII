#ifndef __FUNCOES_H__
#define __FUNCOES_H__

#include <stdio.h>
#include<stdlib.h>

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




#define CONSULTA 1
#define REMOCAO 0


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
    int campoVazio[7];
    char removido;
    int encadeamento;
    int idConecta; //sem valores repetidos
    char siglaPais[2];
    int idPoPsConectado;
    char unidadeMedida;
    int velocidade;
    char nomePoPs[30];
    char nomePais[30];
} Registro;

Cabecalho InicializaStructCabecalho();

Cabecalho *getHeader(FILE *arq);

//FUNCOES FORNECIDAS 

void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);

//FUNCOES DE MANIPULAÇÃO DE ARQUIVOS

void CriaHeader(FILE *arq_out, Cabecalho *header);

void escreveHeader(FILE *file, Cabecalho *header);

void PreencheLixo(FILE *file);

int LeRegistro(FILE *file_in, Registro *Register);

int get_num_pag(FILE *arq);

void TransfereDados(FILE *file_in, FILE *file_out, Cabecalho* cabecalho);

void EscreveRegistro(FILE *file_out, Registro *Register);

int ChecaStatus(FILE *file_in);

void CompactaArquivo(char *file_in);

void readint(FILE *arq, int *integer);

void readstring(FILE *arq, int reading_size, char *string);

int readstring_variavel(FILE *arq, char *string);

int campovazio_int(int interger);

int campovazio_string(char *string);

int campovazio_string_var(char *string);

void imprime_pag_disco(Cabecalho *header);

void leRegistroBin(Registro *Register, FILE *arq_entrada);

int buscaRegistro(FILE *arq_entrada, Cabecalho *header, int campoBuscado, char *valorCampo, int funcionalidade, int n);

int hashfunction(char *str);

int procura_valor(char *valorCampo, int tipo, int tamanho_campo, int byteoffset, FILE *arq);

void imprime_arq(FILE *arq_entrada);

void remove_registro(FILE *arq, Cabecalho *header, int rrn);

void funcionalidade3(FILE *arq);

void funcionalidade4(FILE *arq);

void funcionalidade5(FILE *arq);

void funcionalidade6(char *arq);

void leEntradaRegistro(Registro *Register);

void insereRegistro(FILE *arq, Registro *Register, Cabecalho *header);

void PrintarErro();






#endif
