#ifndef __ARVORE_B_H__
#define __ARVORE_B_H__

#include "data_structures.h"
#include<stdio.h>
#include<stdlib.h>

void InserePagina(Registro_Arvore *pagina, int chave_promovida, int RRN_indice_promovido, int RRN_filho_promovido);

int BuscaNo(int chave, Registro_Arvore pagina, int* pos);

int BuscaArvore(FILE *arq, int RRN, int chave, int* RRN_chave, int* pos_chave, int *pos_dados, int *num_pag_disco);

int InsereArvore(Cabecalho_Arvore *header, FILE *arq, int chave, int RRN_indice_chave, int RRN_atual, int *chave_promovida, int *RRN_indice_promovido, int *RRN_filho_promovido);

void InicializaNo(Registro_Arvore *pagina);

void split(FILE* arq, Cabecalho_Arvore *header, int chave_inserir, int RRN_inserir, int RRN_filho_inserir, Registro_Arvore *pagina, int* chave_promovida, int* RRN_indice_promovido, int* RRN_filho_promovido, Registro_Arvore *nova_pagina);

void ResetaDadosNo(Registro_Arvore *pagina);

void InicializaHeaderArvore(Cabecalho_Arvore *header);


#endif
