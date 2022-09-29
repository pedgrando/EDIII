#include<stdio.h>
#include<stdlib.h>

#include "funcoes.h"

void main(){
    int option;
    char arq_entrada[32];
    char arq_saida[32];
    scanf("%d %s %s", &option, arq_entrada, arq_saida);
    FILE *file_in;
    FILE *file_out;

    Cabecalho *header = malloc(sizeof(Cabecalho));
    *header = InicializaStructCabecalho();
    
    switch (option)
    {
    case 1:    //CREATE TABLE
        if(!(file_out = fopen(arq_saida, "wb")) || !(file_in = fopen(arq_entrada, "rb"))) {    // testa se o arquivo existe
            printf("Falha no processamento do arquivo\n");
            break;
        }
        CriaHeader(file_out, header);
        TransfereDados(file_in, file_out);

        break;
    
    default:
        break;
    }

    free(header);
    fclose(file_in);
    fclose(file_out);
}