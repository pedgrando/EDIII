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

void LeRegistroBin(Registro *Register, FILE *file);

void PrintErro();

void readint(FILE *file, int *integer);

void readstring(FILE *file, int reading_size, char *string);

int readstring_variavel(FILE *file, char *string);

void imprimeLista(lista *li, Grafo vertice);

#endif
