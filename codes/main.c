#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

int main(int argv, char *argc[]){
    int option;
    char nome_arq[32];
    scanf("%d %s", &option, nome_arq);
    FILE *arq;
    registro *reg = malloc(sizeof(registro));
    switch (option)
    {
    case 1:
        if(!(arq = fopen(nome_arq, "wb"))) {
            printf("Falha no processamento do arquivo\n");
            break;
        }
        int num_reg;
        scanf("%d", &num_reg);
        for(int i = 0; i < num_reg; i++){
            get_register(reg);
            write_register(reg, arq);
        }
        fclose(arq);
        binarioNaTela(nome_arq);
        break;

    case 2:
        if(!(arq = fopen(nome_arq, "rb"))) {
            printf("Falha no processamento do arquivo\n");
            break;
        }
        int tam = get_tam(arq);
        // printf("\n\nExistem %d registros.\n\n", tam);
        for(int i = 0; i < tam; i++) {
            fseek(arq, i * REG, SEEK_SET);
            read_register(arq, reg); 
            print_register(reg);
        }
        fclose(arq);
        break;

    case 3:
        if(!(arq = fopen(nome_arq, "rb"))) {
            printf("Falha no processamento do arquivo\n");
            break;
        }
        int RRN;
        scanf("%d", &RRN);
        fseek(arq, RRN * REG, SEEK_SET);
        read_register(arq, reg);
        print_register(reg);
        fclose(arq);
        break;
    
    default:
        printf("Entrada indisponível.");
        break;
    }

	// libera memoria pro registro;
    free(reg);
}
