#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

#define REG 238   // tamanho de cada registro
#define TRASH '$'
#define FN 51   // tamanho de cada campo
#define LN 51
#define EMAIL 81
#define NAT 51


// funcao fornecida para leitura de string da entrada padrao

void readline(char* string){
    char c = 0;

    do{
        c = (char) getchar();

    } while(c == '\n' || c == '\r');

    int i = 0;

    do{
        string[i] = c;
        i++;
        c = getchar();
    } while(c != '\n' && c != '\r');

    string[i]  = '\0';
}

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}




// funcao para imprimir registros consultados na tela

void print_register(registro *reg){  
    printf("Firstname: %s\n", reg->firstname);
    printf("Lastname: %s\n", reg->lastname);    
    printf("Email: %s\n", reg->email);
    printf("Nationality: %s\n", reg->nationality);
    printf("Age: %d\n\n", reg->age); 
}


// le registro 

void read_register(FILE *arq, registro *reg){  
    fread(reg->firstname, sizeof(char), 51, arq);
    fread(reg->lastname, sizeof(char), 51, arq);
    fread(reg->email, sizeof(char), 81, arq);
    fread(reg->nationality, sizeof(char), 51, arq);
    fread(&reg->age, sizeof(int), 1, arq);
}



// funcao para descobrir o tamanho de um arquivo

int get_num_reg(FILE *arq){
    long counter = 0;
    char temp[1]; 
    while(fread(temp, 1, 1, arq)) counter++;  // conta um por um dos caracteres ate o final
    return counter / REG;
}




// funcoes para adicao de lixo ao registro

void add_trash_2_register(registro *reg){
	add_trash_2_string(reg->firstname, FN);
	add_trash_2_string(reg->lastname, LN);
	add_trash_2_string(reg->email, EMAIL);
	add_trash_2_string(reg->nationality, NAT);
	return;
}

void add_trash_2_string(char *str, int sizeof_field){
	int str_length = strlen(str) + 1; // pegar o tamanho da string, incluindo o \0
	for(int i = str_length; i < sizeof_field; i++){
		str[i] = TRASH; 		// completa de lixo a partir do \0 ate o final do campo
	}	
}




// escreve um registro em um arquivo, na forma binaria

void write_register(registro *reg, FILE *arq){
	fwrite(reg->firstname, sizeof(char), 51, arq);  
	fwrite(reg->lastname, sizeof(char), 51, arq);  
	fwrite(reg->email, sizeof(char), 81, arq);  
	fwrite(reg->nationality, sizeof(char), 51, arq);
	fwrite(&reg->age, sizeof(int), 1, arq);
	return;
}




// le informacoes da entrada padrao e atribui aos respectivos campos de um registro

void get_register(registro *reg){

	// le nome
	readline(reg->firstname);
	
	// le sobrenome	
	readline(reg->lastname);

	// le email	
	readline(reg->email);
	
	// le nacionalidade
	readline(reg->nationality);

	// le idade
	scanf("%d", &(reg->age));
	
	add_trash_2_register(reg); // adiciona lixo aos byte nao preenchidos dos campos do registro

	return;
}

