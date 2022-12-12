#ifndef __FUNCOES_PRINCIPAIS_HPP__
#define __FUNCOES_PRINCIPAIS_HPP__

#include <stdio.h>
#include<stdlib.h>

#include "data_structures.hpp"

int BuscaRegistro(FILE *file, Cabecalho *header, int campoBuscado, char *valorCampo, int funcionalidade, int n);

int InsereRegistro(FILE *file, Registro *Register, Cabecalho *header);


#endif
