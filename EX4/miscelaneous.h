#ifndef __MISCELANEOUS_H__
#define __MISCELANEOUS_H__

#include <stdio.h>
#include<stdlib.h>

#include "data_structures.h"

void CriaHeader(FILE *file, Cabecalho *header);

Cabecalho ResetaCabecalho();

void ResetaRegistro(Registro *Register);

int getNumPag(Cabecalho *header);

int campovazio_int(int interger);

int campovazio_string(char *string);

int campovazio_string_var(char *string);

int hashfunction(char *str);

#endif
