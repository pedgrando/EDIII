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
    char arq_saida[32];

    scanf("%d", &option);		    

    FILE *file_in = NULL;
    FILE *file_out = NULL;

    switch (option)
    {
    case 1:    
	
	// FUNCIONALIDADE 1
	// cria a tabela (arquivo binario de dados) ---------------------------------------------------------------------------------------

    	scanf("%s %s", arq_entrada, arq_saida);
        if(!(file_out = fopen(arq_saida, "wb")) || !(file_in = fopen(arq_entrada, "rb"))) {    // testa se o arquivo existe
            PrintErro();
            break;
        }

	    funcionalidade1(file_in, file_out, arq_saida);

    break;
    case 2:

	// FUNCIONALIDADE 2
	// lista todos os registros de um arquivo sequencialmente ---------------------------------------------------------------------------
	
	    scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb"))) {    // testa se o arquivo existe
            PrintErro();
            break;
        }

    	funcionalidade2(file_in);
    	fclose(file_in);

	break;
    case 3:

	// FUNCIONALIDADE 3
	// faz n consultas dados que atendam a uma exigencia especifica ----------------------------------------------------------------------

	    scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb"))) {    // testa se o arquivo existe
            PrintErro();
            break;
        }

	    funcionalidade3(file_in, arq_entrada);
		
	break;
    case 4:

	// FUNCIONALIDADE 4
	// remove logicamente n registros ---------------------------------------------------------------------------------------------------

	    scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe
            PrintErro();
            break;
        }
		
	    funcionalidade4(file_in, arq_entrada);

	break;
    case 5:

	// FUNCIONALIDADE 5

	    scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe
            PrintErro();
            break;
        }

	    funcionalidade5(file_in, arq_entrada);

	break;
    case 6:

	// FUNCIONALIDADE 6

        scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
            PrintErro();
            break;
        }

        funcionalidade6(file_in, arq_entrada);

	break;	
    default:
    break;
    }

}
