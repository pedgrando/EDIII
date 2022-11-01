#ifndef __FUNCOES_PRINCIPAIS_H__
#define __FUNCOES_PRINCIPAIS_H__

#include <stdio.h>
#include<stdlib.h>

#include "data_structures.h"

void TransfereDados(FILE *file_in, FILE *file_out, Cabecalho* cabecalho);

void CompactaArquivo(FILE *file_in, char *arq_entrada);

int buscaRegistro(FILE *arq_entrada, Cabecalho *header, int campoBuscado, char *valorCampo, int funcionalidade, int n);

void remove_registro(FILE *arq, Cabecalho *header, int rrn);

void insereRegistro(FILE *arq, Registro *Register, Cabecalho *header);

void imprime_arq(FILE *arq_entrada);

#endif
