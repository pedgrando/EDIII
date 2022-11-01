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

Cabecalho InicializaStructCabecalho();

void CriaHeader(FILE *arq_out, Cabecalho *header);

void PreencheLixo(FILE *file);

void resetaRegistro(Registro *Register);

int get_num_pag(Cabecalho *header);

int ChecaStatus(FILE *file_in);

int campovazio_int(int interger);

int campovazio_string(char *string);

int campovazio_string_var(char *string);

int hashfunction(char *str);

#endif
