#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "data_structures.h"
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

void insere_arvore(){

}

