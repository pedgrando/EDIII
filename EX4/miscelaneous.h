#ifndef __MISCELANEOUS_H__
#define __MISCELANEOUS_H__

#include <stdio.h>
#include<stdlib.h>

#include "data_structures.h"

#define IDCONECTA 906
#define SIGLAPAIS 925
#define IDPOPSCONECTADO 1503
#define UNIDADEMEDIDA 1310
#define VELOCIDADE 1040
#define NOMEPOPS 817
#define NOMEPAIS 828

void CriaHeader(FILE *file, Cabecalho *header);

Cabecalho ResetaCabecalho();

void ResetaRegistro(Registro *Register);

int getNumPag(Cabecalho *header);

int campovazio_int(int interger);

int campovazio_string(char *string);

int campovazio_string_var(char *string);

int hashfunction(char *str);

#endif
