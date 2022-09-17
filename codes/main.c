#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REG 238

#define TRASH '$'

#include "funcoes.h"

int main(int argv, char *argc[]){
    int option;
    char *nome_arq;
    scanf("%d %s", &option, nome_arq);
    FILE *arq;
    registro *reg = malloc(sizeof(registro));
    switch (option)
    {
    case 1:
        arq = fopen(nome_arq, "wb");
        int num_reg;
        scanf("%d", &num_reg);
        // for(int i = 0; i < num_reg; i++){
        //     get_register(reg);
        //     write_register(reg, arq);
        // }
        break;

    case 2:
        arq = fopen(nome_arq, "rb");
        int tam = get_tam(arq);
        // printf("\n\nExistem %d registros.\n\n", tam);
        for(int i = 0; i < tam; i++) {
            fseek(arq, i * REG, SEEK_SET);
            read_register(arq, reg); 
            print_register(reg);
        }
        break;

    case 3:
        arq = fopen(nome_arq, "rb");
        int RRN;
        scanf("%d", &RRN);
        fseek(arq, RRN * REG, SEEK_SET);
        read_register(arq, reg);
        print_register(reg);
        break;
    
    default:
        printf("Entrada indisponível.");
        break;
    }




	// libera memoria pro registro;
    free(reg);
    fclose(arq);
}
