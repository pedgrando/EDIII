#ifndef __FUNCOES_H__
#define __FUNCOES_H__

#include <stdio.h>
#include<stdlib.h>

#define PAG_DISCO 960
#define CAB 20
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
    char siglaPais[3];
    int idPoPsConectado;
    char unidadeMedida;
    int velocidade;
    char nomePoPs[30];
    char nomePais[30];
} Registro;

Cabecalho InicializaStructCabecalho();

Cabecalho *getHeader(FILE* file);


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

void CompactaArquivo(FILE *file_in);

void readstring(FILE *arq_entrada, int reading_size, char *string);

void readstring_variavel(FILE *arq_entrada, char *string);

void readint(FILE *arq_entrada, int *integer);

int campovazio_int(int interger);

int campovazio_string(char *string);

int campovazio_string_var(char *string);

void imprime_pag_disco(Cabecalho *header);

void leRegistroBin(Registro *Register, FILE *arq_entrada);

void buscaRegistro(FILE *arq_entrada, int campoBuscado, char *valorCampo, int funcionalidade);

int hashfunction(char *str);

int compara_str(char *str1, char *str2);

int procura_valor(char *valorCampo, int tipo, int tamanho_campo, int byteoffset, FILE *arq);

void imprime_arq(FILE *arq_entrada);

void remove_registro(FILE *arq, Cabecalho *header, int rrn);














#endif
