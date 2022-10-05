#include<stdio.h>
#include<stdlib.h>

#include "funcoes.h"

int main(int argv, char *argc[]){
    int option;
    int n;
    char arq_entrada[32];
    char arq_saida[32];

    scanf("%d", &option);		    

    FILE *file_in = NULL;
    FILE *file_out = NULL;

    Cabecalho *header = malloc(sizeof(Cabecalho));
    *header = InicializaStructCabecalho();
    
    switch (option)
    {
    case 1:    //CREATE TABLE
    	scanf("%s %s", arq_entrada, arq_saida);
        if(!(file_out = fopen(arq_saida, "wb")) || !(file_in = fopen(arq_entrada, "rb"))) {    // testa se o arquivo existe
            printf("Falha no processamento do arquivo\n");
            break;
        }
        CriaHeader(file_out, header);
        TransfereDados(file_in, file_out);

        break;
    case 2:
        if(!(file_in = fopen(arq_entrada, "rb"))) {    // testa se o arquivo existe
            printf("Falha no processamento do arquivo\n");
            break;
        }
	scanf("%d", &n);

	break;
    case 3:
        if(!(file_in = fopen(arq_entrada, "rb"))) {    // testa se o arquivo existe
            printf("Falha no processamento do arquivo\n");
            break;
        }
	scanf("%d", &n);

	break;
    case 4:
        if(!(file_in = fopen(arq_entrada, "rb"))) {    // testa se o arquivo existe
            printf("Falha no processamento do arquivo\n");
            break;
        }
	scanf("%d", &n);

	break;
    case 5:
        if(!(file_in = fopen(arq_entrada, "rb"))) {    // testa se o arquivo existe
            printf("Falha no processamento do arquivo\n");
            break;
        }
	scanf("%d", &n);

	break;
    case 6:
        if(!(file_in = fopen(arq_entrada, "rb"))) {    // testa se o arquivo existe
            printf("Falha no processamento do arquivo\n");
            break;
        }

	break;	
    default:
        break;
    }

    free(header);
    fclose(file_in);
    fclose(file_out);
}
