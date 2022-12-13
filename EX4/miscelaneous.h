#ifndef __MISCELANEOUS_H__
#define __MISCELANEOUS_H__

#include <stdio.h>
#include<stdlib.h>

#include "data_structures.h"

Cabecalho ResetaCabecalho();

void ResetaRegistro(Registro *Register);

int getNumPag(Cabecalho *header);

int campovazio_int(int interger);

int campovazio_string(char *string);

int campovazio_string_var(char *string);

int hashfunction(char *str);

void ConverteVelocidade(Registro *Register);

lista *cria_lista();

void libera_lista(lista *li);

int insereLista(lista *li, Registro info);

int buscaLista(lista *li, int idConectaBuscado);

#endif
