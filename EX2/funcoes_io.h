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

Cabecalho *getHeader(FILE *arq);

void escreveHeader(FILE *file, Cabecalho *header);

int LeRegistro(FILE *file_in, Registro *Register);

void EscreveRegistro(FILE *file_out, Registro *Register);

void readint(FILE *arq, int *integer);

void readstring(FILE *arq, int reading_size, char *string);

int readstring_variavel(FILE *arq, char *string);

void imprime_pag_disco(Cabecalho *header);

void leRegistroBin(Registro *Register, FILE *arq_entrada);

void imprime_arq(FILE *arq_entrada);

void leEntradaRegistro(Registro *Register);

void PrintarErro();

#endif
