#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "data_structures.h"
#include "funcoes_io.h"
#include "arvore_b.h"
#include "funcoes_io.h"

/*
typedef struct cabecalho_arvore{
	char status;
	int noRaiz;
	int nroChavesTotal;
    int alturaArvore;
    int RRNproxNo;
} Cabecalho_Arvore;

typedef struct registro_arvore{
	char folha;
	int nroChavesNo;
	int alturaNo;
    	int RRNdoNo;
	int P[5];
    	int C[4];
    	int PR[4];
} Registro_Arvore;
*/


int busca_arvore(FILE *arq, int RRN, int chave, int* RRN_chave, int* pos_chave){
	if(RRN == -1){ 
		return -1;
	} else {
		int pos;  // variavel pos tem duas utilidades -> se achou, diz em que posicao do vetor esta; se não achou, diz para qual no a recursao deve seguir
		Registro_Arvore pagina;

		le_no_arvore(arq, &pagina, RRN);

		if(busca_no(chave, pagina, &pos)){
			*RRN_chave = RRN;	
			*pos_chave = pos;
			return 1;
		} else {
			return(busca_arvore(arq, pagina.P[pos], chave, RRN_chave, pos_chave));	
		}	
	}
}

int busca_no(int chave, Registro_Arvore pagina, int* pos){
	for(int i = 0; i < 4; i++){
		*pos = i;
		if(chave < pagina.C[i]){
			return 0;	
		} else if(chave == pagina.C[i]){
			return 1;
		}
	}
	*pos = 4;
	return 0;
}

int insere_arvore(Cabecalho_Arvore *header, FILE *arq, int chave, int RRN_indice_chave, int RRN_atual, int *chave_promovida, int *RRN_indice_promovido, int *RRN_filho_promovido){
	if(RRN_atual == -1){
		*chave_promovida = chave;
		*RRN_indice_promovido = RRN_indice_chave;
		*RRN_filho_promovido = -1;
		return 1;
	} else {
		Registro_Arvore *pagina = malloc(sizeof(Registro_Arvore));
		le_no_arvore(arq, pagina, RRN_atual);

		int pos;
		int sucesso = busca_no(chave, *pagina, &pos);
			
		if(sucesso){
			printf("Erro. A chave ja esta inserida\n");
			return -1;
		}
		
		int chave_a_promover;
		int RRN_a_promover;
		int RRN_filho_a_promover;

		int promocao = insere_arvore(header, arq, chave, RRN_indice_chave, pagina->P[pos], &chave_a_promover, &RRN_a_promover, &RRN_filho_a_promover);
		
		if(promocao != 1){
			free(pagina);
			return promocao;
		} else if(pagina->nroChavesNo < 4){
			free(pagina);
			insere_pagina(pagina, *chave_promovida, *RRN_indice_promovido, *RRN_filho_promovido);
			escreve_no(arq, pagina, *RRN_filho_promovido);
			return 0;
		} else {
			Registro_Arvore *nova_pagina = malloc(sizeof(Registro_Arvore));
			inicializa_no(nova_pagina);
			split(header, chave_a_promover, RRN_a_promover, RRN_filho_a_promover, pagina, chave_promovida, RRN_indice_promovido, RRN_filho_promovido, nova_pagina); 
			escreve_no(arq, pagina, RRN_atual);
 		       	escreve_no(arq, nova_pagina, *RRN_filho_promovido);
			free(nova_pagina);	
			free(pagina);
		       	return 1;
		}
	}
}

int split(Cabecalho_Arvore *header, int chave_inserir, int RRN_inserir, int RRN_filho_inserir, Registro_Arvore *pagina, int chave_promovida, int RRN_indice_promovido, int RRN_filho_promovido, Registro_Arvore *nova_pagina){
	NoAux pag_auxiliar;
	for(int i = 0; i < 4; i++){
		pag_auxiliar.C[i] = pagina->C[i];
		pag_auxiliar.P[i] = pagina->P[i];
		pag_auxiliar.PR[i] = pagina->PR[i];
	}
	pag_auxiliar.P[4] = pagina->P[4];
			
	for(int j = 0; j < 4; j++){
		if(
	}










}

void insere_pagina(Registro_Arvore *pagina, int chave_promovida, int RRN_indice_promovido, int RRN_filho_promovido){
	int i = 0;

	while(chave_promovida > pagina->C[i]) i++; 
	
	for( int j = i; j < 3; j++){
		pagina->C[j+1] = pagina->C[j];
		pagina->PR[j+1] = pagina->PR[j];	
		pagina->P[j+2] = pagina->PR[j+1];
	}	

	pagina->C[i] = chave_promovida;
	pagina->PR[i] = RRN_indice_promovido;
	pagina->P[i+1] = RRN_filho_promovido;

}

void inicializa_no(Registro_Arvore *pagina){
	pagina->folha = '0';
	pagina->nroChavesNo = 0;
	pagina->alturaNo = -1;
	pagina->RRNdoNo = -1;
	for(int i = 0; i < 4; i++){
		pagina->P[i] = -1;
		pagina->PR[i] = -1;
		pagina->C[i] = -1;
	}
	pagina->P[4] = -1;
}












