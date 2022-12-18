// PEDRO ANTONIO BRUNO GRANDO - 12547166 - 100% de contribuição
// PEDRO ARTHUR DO PRADO FRANÇOSO - 12547301 - 100% de contribuição


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "miscelaneous.h"
#include "funcoes_io.h"
#include "data_structures.h"
#include "funcionalidades.h"

int main(int argv, char *argc[]){
    int option;
    char arq_entrada[32];

    scanf("%d", &option);		    

    FILE *file_in = NULL;

    Cabecalho *header = malloc(sizeof(Cabecalho));
    *header = ResetaCabecalho();
    
    scanf("%s", arq_entrada);
    if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
        PrintErro();
        exit(0);
    }

    header = getHeader(file_in);
    if(header->status == '0'){
	    PrintErro();
	    exit(-1);
    }

    Grafo *grafo = malloc(sizeof(Grafo) * header->proxRRN);

    for (int i = 0; i < header->proxRRN; i++) {
        grafo[i].listaAdj = cria_lista();
        grafo[i].numVerticesAdj = 0;
	grafo[i].idConecta = -1;
    }
    
    switch (option)
    {
    case 11:

	// FUNCIONALIDADE 11

        funcionalidade11(file_in, header, grafo);

    	for(int i = 0; i < header->proxRRN; i++){
        	if(grafo[i].idConecta != -1){
		
			imprimeLista(grafo[i].listaAdj, grafo[i]);
		}
    	}
	break;	
    case 12:

	// FUNCIONALIDADE 12

        funcionalidade12(file_in, header, grafo);

	break;	
    case 13:

	// FUNCIONALIDADE 13

        funcionalidade13(file_in, header, grafo);

	break;	
    case 14:

	// FUNCIONALIDADE 14
	
	funcionalidade14(file_in, header, grafo);

	break;	
    default:
    break;
    }
	
    free(header);
    fclose(file_in);

}
