// PEDRO ANTONIO BRUNO GRANDO - 12547166 - 100% de contribuição
// PEDRO ARTHUR DO PRADO FRANÇOSO - 12547301 - 100% de contribuição


#include<stdio.h>
#include<stdlib.h>

#include "miscelaneous.h"
#include "funcoes_io.h"
#include "data_structures.h"
#include "funcionalidades.h"
#include "funcoes_principais.h"

int main(int argv, char *argc[]){
    int option;
    char arq_entrada[32];

    scanf("%d", &option);		    

    FILE *file_in = NULL;

    Cabecalho *header = malloc(sizeof(Cabecalho));
    *header = ResetaCabecalho();
    
    switch (option)
    {
    case 11:

	// FUNCIONALIDADE 11

        scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
            PrintErro();
            break;
        }

	    header = getHeader(file_in);

        funcionalidade11(file_in, header);

	break;	
    case 12:

	// FUNCIONALIDADE 12

        scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
            PrintErro();
            break;
        }

        funcionalidade12(file_in);

	break;	
    case 13:

	// FUNCIONALIDADE 13

        scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
            PrintErro();
            break;
        }

        funcionalidade13(file_in);

	break;	
    case 14:

	// FUNCIONALIDADE 14

        scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
            PrintErro();
            break;
        }

        funcionalidade14(file_in);

	break;	
    default:
    break;
    }
    free(header);

}
