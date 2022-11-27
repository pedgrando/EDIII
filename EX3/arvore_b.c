#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "data_structures.h"
#include "funcoes_io.h"
#include "arvore_b.h"
#include "funcoes_io.h"

// funcao recursiva de busca utilizando a arvore b

int BuscaArvore(FILE *arq, int RRN, int chave, int* RRN_chave, int* pos_chave, int *pos_dado, int *num_pag_disco){
	if(RRN == -1){ 
		return 0;
	} else {
		int pos;  // variavel pos tem duas utilidades -> se achou, diz em que posicao do vetor esta; se não achou, diz para qual no a recursao deve seguir
		Registro_Arvore pagina;

		LeNoArvore(arq, &pagina, RRN);
		(*num_pag_disco)++;

		if(BuscaNo(chave, pagina, &pos) == 1){ 		//realiza a recursividade
			*RRN_chave = RRN;	
			*pos_chave = pos;
			*pos_dado = pagina.PR[pos];
			return 1;
		} else {
			return(BuscaArvore(arq, pagina.P[pos], chave, RRN_chave, pos_chave, pos_dado, num_pag_disco));	
		}	
	}
}

// funcao que complementa a busca recursia, lendo os nós da árvore durante a navegação recursiva

int BuscaNo(int chave, Registro_Arvore pagina, int* pos){
	for(int i = 0; i < pagina.nroChavesNo; i++){
		*pos = i;
		if(chave < pagina.C[i]){
			return 0;	
		} else if(chave == pagina.C[i]){
			return 1;
		}
	}
	*pos = pagina.nroChavesNo;
	return 0;
}

// funcao de insercao atualizando a arvore e seu cabeçalho

int InsereArvore(Cabecalho_Arvore *header, FILE *arq, int chave, int RRN_indice_chave, int RRN_atual, int *chave_promovida, int *RRN_indice_promovido, int *RRN_filho_promovido){
	if(RRN_atual == -1){
		*chave_promovida = chave;
		*RRN_indice_promovido = RRN_indice_chave;
		*RRN_filho_promovido = -1;

		header->nroChavesTotal++;
		return 1;
	} else {
		Registro_Arvore *pagina = malloc(sizeof(Registro_Arvore));
		LeNoArvore(arq, pagina, RRN_atual);

		int pos;
		int sucesso = BuscaNo(chave, *pagina, &pos);
			
		if(sucesso){
			free(pagina);
			printf("Erro. A chave ja esta inserida\n");
			exit(-1);	
		}
		
		int chave_a_promover;
		int RRN_a_promover;
		int RRN_filho_a_promover;

		int promocao = InsereArvore(header, arq, chave, RRN_indice_chave, pagina->P[pos], &chave_a_promover, &RRN_a_promover, &RRN_filho_a_promover);

		
		if(promocao != 1){
			free(pagina);
			return 0;
		} else if(pagina->nroChavesNo < 4){
			InserePagina(pagina, chave_a_promover, RRN_a_promover, RRN_filho_a_promover);
			EscreveNo(arq, pagina, RRN_atual);
			free(pagina);
			return 0;
		} else {
			Registro_Arvore *nova_pagina = malloc(sizeof(Registro_Arvore));
			InicializaNo(nova_pagina);
			split(header, chave_a_promover, RRN_a_promover, RRN_filho_a_promover, pagina, chave_promovida, RRN_indice_promovido, RRN_filho_promovido, nova_pagina); 
			EscreveNo(arq, pagina, RRN_atual);
			EscreveNo(arq, nova_pagina, *RRN_filho_promovido);
			free(nova_pagina);	
			free(pagina);
		    return 1;
		}
	}
}

// funcao de split para balancear a arvore

void split(Cabecalho_Arvore *header, int chave_inserir, int RRN_inserir, int RRN_filho_inserir, Registro_Arvore *pagina, int *chave_promovida, int *RRN_indice_promovido, int *RRN_filho_promovido, Registro_Arvore *nova_pagina){
	NoAux pag_auxiliar;
	int i;
	for(i = 0; i < 4; i++){
		pag_auxiliar.C[i] = pagina->C[i];
		pag_auxiliar.P[i] = pagina->P[i];
		pag_auxiliar.PR[i] = pagina->PR[i];
	}
	pag_auxiliar.P[4] = pagina->P[4];
	
	i = 0;	
	while(chave_inserir > pagina->C[i]) i++;

	for(int j = 4; j >= i; j--){
		pag_auxiliar.C[j] = pag_auxiliar.C[j-1];
		pag_auxiliar.PR[j] = pag_auxiliar.PR[j-1];
		pag_auxiliar.P[j+1] = pag_auxiliar.P[j];
	}
	
	pag_auxiliar.C[i] = chave_inserir;
	pag_auxiliar.PR[i] = RRN_inserir;
	pag_auxiliar.P[i+1] = RRN_filho_inserir;

	nova_pagina->alturaNo = pagina->alturaNo;
	nova_pagina->RRNdoNo = header->RRNproxNo;
	header->RRNproxNo++;
	if(nova_pagina->alturaNo == 1) nova_pagina->folha = '1';
	
	*chave_promovida = pag_auxiliar.C[2];
	*RRN_indice_promovido = pag_auxiliar.PR[2];
	*RRN_filho_promovido = nova_pagina->RRNdoNo;
	
	ResetaDadosNo(pagina);
	ResetaDadosNo(nova_pagina);
	
	for(i = 0; i < 2; i++){
		pagina->C[i] = pag_auxiliar.C[i];	
		pagina->PR[i] = pag_auxiliar.PR[i];	
		pagina->P[i] = pag_auxiliar.P[i];	
	}
	pagina->P[i] = pag_auxiliar.P[i];	
	i++;
	for(int j = 0; j < 2; j++){
		nova_pagina->C[j] = pag_auxiliar.C[i];
		nova_pagina->PR[j] = pag_auxiliar.PR[i];
		nova_pagina->P[j] = pag_auxiliar.P[i];
		i++;
	}
	nova_pagina->P[2] = pag_auxiliar.P[i];

	pagina->nroChavesNo = 2;
	nova_pagina->nroChavesNo = 2;
	if(pagina->alturaNo <= 1){
		pagina->folha = '1';
	}
	nova_pagina->folha = pagina->folha;
	nova_pagina->alturaNo = pagina->alturaNo;
}

// funcao para preenchimento de paginas com as chaves e rrns

void InserePagina(Registro_Arvore *pagina, int chave_promovida, int RRN_indice_promovido, int RRN_filho_promovido){
	int i = 0;

	while(chave_promovida > pagina->C[i] && i < 4) i++; 
	
	for( int j = 4; j > i; j--){
		pagina->C[j] = pagina->C[j-1];
		pagina->PR[j] = pagina->PR[j-1];	
		pagina->P[j+1] = pagina->PR[j];
	}	

	pagina->C[i] = chave_promovida;
	pagina->PR[i] = RRN_indice_promovido;
	pagina->P[i+1] = RRN_filho_promovido;

	pagina->nroChavesNo++;
	if(pagina->nroChavesNo == 1){
		pagina->alturaNo++;
	}
}

//funcao que inicializa um nó com os dados de nó vazio

void InicializaNo(Registro_Arvore *pagina){
	pagina->folha = '1';
	pagina->nroChavesNo = 0;
	pagina->alturaNo = 1;
	pagina->RRNdoNo = -1;
	for(int i = 0; i < 4; i++){
		pagina->P[i] = -1;
		pagina->PR[i] = -1;
		pagina->C[i] = -1;
	}
	pagina->P[4] = -1;
}

// funcao que reseta os dados do nó

void ResetaDadosNo(Registro_Arvore *pagina){
	for(int i = 0; i < pagina->nroChavesNo; i++){
		pagina->C[i] = -1;
		pagina->PR[i] = -1;
		pagina->P[i] = -1;
	}
	pagina->P[pagina->nroChavesNo] = -1;
	pagina->nroChavesNo = 0;
}









