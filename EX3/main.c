// PEDRO ANTONIO BRUNO GRANDO - 12547166 - 100% de contribuição
// PEDRO ARTHUR DO PRADO FRANÇOSO - 12547301 - 100% de contribuição


#include<stdio.h>
#include<stdlib.h>

#include "miscelaneous.h"
#include "funcoes_io.h"
#include "data_structures.h"
#include "funcionalidades.h"
#include "funcoes_principais.h"

void traverse(FILE* file, int rrn){
	int i;
	if(rrn != -1){
		Registro_Arvore* node = malloc(sizeof(Registro_Arvore));
		fseek(file, (rrn+1)*65, SEEK_SET);
		LeNoArvore(file, node, rrn);

		printf("%d ", node->RRNdoNo);
		for(i = 0; i < node->nroChavesNo; i++){
			traverse(file, node->P[i]);
		}
		traverse(file, node->P[i]);
	}

}

int main(int argv, char *argc[]){
    int option;
    char arq_entrada[32];

    scanf("%d", &option);		    

    FILE *file_in = NULL;

    Cabecalho *header = malloc(sizeof(Cabecalho));
    *header = ResetaCabecalho();
    
    switch (option)
    {
    case 7:

	// FUNCIONALIDADE 7

        scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
            PrintErro();
            break;
        }

        funcionalidade7(file_in);

	break;	
    case 8:

	// FUNCIONALIDADE 8

        scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
            PrintErro();
            break;
        }

        funcionalidade8(file_in);

	break;	
    case 9:

	// FUNCIONALIDADE 9

        scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
            PrintErro();
            break;
        }

        funcionalidade9(file_in, arq_entrada);

	break;	
    case 10:

	// FUNCIONALIDADE 10

        scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
            PrintErro();
            break;
        }

        funcionalidade10(file_in);

	break;	
    case 11:
			scanf("%s", arq_entrada);
			file_in = fopen(arq_entrada, "rb");
			Cabecalho_Arvore *header_a = malloc(sizeof(Cabecalho_Arvore));
			LeHeaderArvore(file_in, header_a);
			traverse(file_in, header_a->noRaiz);
			free(header_a);
 			break;

    default:
    break;
    }
    free(header);

}
