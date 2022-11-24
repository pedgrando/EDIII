#ifndef __FUNCOES_IO_H__
#define __FUNCOES_IO_H__

#include <stdio.h>
#include<stdlib.h>

#include "data_structures.h"
#include "miscelaneous.h"

//FUNCOES FORNECIDAS 

void readline(char* string);

void binarioNaTela(char *nomeArquivoBinario);

void scan_quote_string(char *string);

//FUNCOES DE MANIPULAÇÃO DE ARQUIVOS

Cabecalho *getHeader(FILE *file);

int getRegistroCsv(FILE *file_csv, Registro *Register);

void PreencheLixo(FILE *file);

void EscreveHeader(FILE *file, Cabecalho *header);

void EscreveRegistro(FILE *file, Registro *Register);

int getRegistroCsv(FILE *file_csv, Registro *Register);

void EscreveRegistro(FILE *file, Registro *Register);

void PrintPagDisco(Cabecalho *header);

void ImprimeRegistro(Registro *Register);

void LeRegistroBin(Registro *Register, FILE *file);

void LeEntradaRegistro(Registro *Register);

void PrintRegistro(Registro *Register);

void PrintPagDisco(Cabecalho *header);

void PrintErro();

void readint(FILE *file, int *integer);

void readstring(FILE *file, int reading_size, char *string);

int readstring_variavel(FILE *file, char *string);

void le_no_arvore(FILE *arq_arv, Registro_Arvore *pagina, int RRN);

#endif
