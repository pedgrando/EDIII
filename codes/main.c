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
    int num_reg;

    switch (option)
    {
    case 1:
        if(!(arq = fopen(nome_arq, "wb"))) {    // testa se o arquivo existe
            printf("Falha no processamento do arquivo\n");
            break;
        }
        scanf("%d", &num_reg);
        for(int i = 0; i < num_reg; i++){
            get_register(reg);
            write_register(reg, arq);
        }
        fclose(arq);
        binarioNaTela(nome_arq);
        break;

    case 2:
        if(!(arq = fopen(nome_arq, "rb"))) {    // testa se o arquivo existe
            printf("Falha no processamento do arquivo\n");
            break;
        }
        num_reg = get_num_reg(arq);
        for(int i = 0; i < num_reg; i++) {
            fseek(arq, i * REG, SEEK_SET);
            read_register(arq, reg); 
            print_register(reg);
        }
        fclose(arq);
        break;

    case 3:
        if(!(arq = fopen(nome_arq, "rb"))) {    // testa se o arquivo existe
            printf("Falha no processamento do arquivo\n");
            break;
        }
        int RRN;
        scanf("%d", &RRN);
        if(get_num_reg(nome_arq) <=cd desko RRN) {
            printf("“Não foi possivel ler o arquivo");
            break;
        }
        fseek(arq, RRN * REG, SEEK_SET);  // coloca o ponteiro no inicio do registro (byte offset)
        read_register(arq, reg);
        print_register(reg);
        fclose(arq);
        break;
    
    default:
        printf("Entrada indisponível.");
        break;
    }
    
    free(reg);  // libera memoria do registro;

}
