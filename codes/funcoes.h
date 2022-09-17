#ifndef __FUNCOES_H__
#define __FUNCOES_H__

#include <stdio.h>
#include<stdlib.h>

#define REG 238
#define TRASH '$'


// estrutura de dados do registro

typedef struct reg{
	char firstname[51];
	char lastname[51];
	char email[81];
	char nationality[51];
	int age;
} registro;




// funcao fornecida para leitura de string da entrada padrao

void readline(char* string);


void binarioNaTela(char *nomeArquivoBinario); /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */




// funcao para imprimir registros consultados na tela

void printa_registro(FILE *arq);    


// funcao para descobrir o tamanho de um arquivo

int get_tam(FILE *arq);


// funcoes para adicao de lixo ao registro

void add_trash_2_register(registro *reg);

void add_trash_2_string(char *str);



// escreve um registro em um arquivo, na forma binaria

void write_register(registro *reg, FILE *arq);



// le informacoes da entrada padrao e atribui aos respectivos campos de um registro

void get_register(registro *reg);

#endif
