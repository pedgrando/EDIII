#ifndef __FUNCOES_PRINCIPAIS_H__
#define __FUNCOES_PRINCIPAIS_H__

#include <stdio.h>
#include<stdlib.h>

#include "data_structures.h"

void TransfereDados(FILE *file_in, FILE *file_out, Cabecalho* cabecalho);

void CompactaArquivo(FILE *file, char *arq);

int BuscaRegistro(FILE *file, Cabecalho *header, int campoBuscado, char *valorCampo, int funcionalidade, int n);

void RemoveRegistro(FILE *file, Cabecalho *header, int rrn);

void InsereRegistro(FILE *file, Registro *Register, Cabecalho *header);

void PrintArquivo(FILE *file);

#endif
