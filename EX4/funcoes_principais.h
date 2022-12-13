#ifndef __FUNCOES_PRINCIPAIS_H__
#define __FUNCOES_PRINCIPAIS_H__

#include <stdio.h>
#include <stdlib.h>

#include "data_structures.h"

int BuscaRegistro(FILE *file, Cabecalho *header, int campoBuscado, char *valorCampo, int funcionalidade, int n);

int InsereRegistro(FILE *file, Registro *Register, Cabecalho *header);

#endif
