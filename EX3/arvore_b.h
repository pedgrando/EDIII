#ifndef __ARVORE_B_H__
#define __ARVORE_B_H__

#include "data_structures.h"
#include<stdio.h>
#include<stdlib.h>

void insere_pagina(Registro_Arvore *pagina, int chave_promovida, int RRN_indice_promovido, int RRN_filho_promovido);

int busca_no(int chave, Registro_Arvore pagina, int* pos);

int busca_arvore(FILE *arq, int RRN, int chave, int* RRN_chave, int* pos_chave, int *pos_dados, int *num_pag_disco);

int insere_arvore(Cabecalho_Arvore *header, FILE *arq, int chave, int RRN_indice_chave, int RRN_atual, int *chave_promovida, int *RRN_indice_promovido, int *RRN_filho_promovido);

void inicializa_no(Registro_Arvore *pagina);

void split(Cabecalho_Arvore *header, int chave_inserir, int RRN_inserir, int RRN_filho_inserir, Registro_Arvore *pagina, int* chave_promovida, int* RRN_indice_promovido, int* RRN_filho_promovido, Registro_Arvore *nova_pagina);

void zera_dados_no(Registro_Arvore *pagina);



#endif
