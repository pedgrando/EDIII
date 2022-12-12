#ifndef __FUNCOES_IO_HPP__
#define __FUNCOES_IO_HPP__

#include <stdio.h>
#include <stdlib.h>

#include "data_structures.hpp"
#include "miscelaneous.hpp"

//FUNCOES FORNECIDAS 

void readline(char* string);

void binarioNaTela(char *nomeArquivoBinario);

void scan_quote_string(char *string);

//FUNCOES DE MANIPULAÇÃO DE ARQUIVOS

Cabecalho *getHeader(FILE *file);

void PreencheLixo(FILE *file);

void ImprimeRegistro(Registro *Register);

void ImprimePagDisco(Cabecalho *header);

void EscreveHeader(FILE *file, Cabecalho *header);

void EscreveRegistro(FILE *file, Registro *Register);

void LeRegistroBin(Registro *Register, FILE *file);

void LeEntradaRegistro(Registro *Register);

void PrintErro();

void readint(FILE *file, int *integer);

void readstring(FILE *file, int reading_size, char *string);

int readstring_variavel(FILE *file, char *string);


#endif
