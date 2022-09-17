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
    switch (option)
    {
    case 1:
	arq = fopen(nome_arq, "wb");
	int num_reg;
	scanf("%d", &num_reg);
	registro *reg = malloc(sizeof(registro));
	for(int i = 0; i < num_reg; i++){
		get_register(reg);
		write_register(reg, arq);
	}
	free(reg);
        break;

    case 2:
        arq = fopen(nome_arq, "rb");
        int tam = get_tam(arq);
        printf("\n\nExistem %d registros.\n\n", tam);
        for(int i = 0; i < tam; i++) {
            fseek(arq, i * REG, SEEK_SET);
            printa_registro(arq);
        }
        break;

    case 3:
        arq = fopen(nome_arq, "rb");
        int RRN;
        scanf("%d", &RRN);
        fseek(arq, RRN * REG, SEEK_SET);
        printa_registro(arq);
        break;
    
    default:
        printf("Entrada indisponível.");
        break;
    }

	// libera memoria pro registro;

    fclose(arq);
}
