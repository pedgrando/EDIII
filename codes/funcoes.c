#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

#define REG 238
#define TRASH '$'


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

void printa_registro(FILE *arq){    
    printf("Firstname: ");
    char buffer[81];
    fread(buffer, 51, 1, arq);
    printf("%s\n", buffer);
    printf("Lastname: ");
    fread(buffer, 51, 1, arq);
    printf("%s\n", buffer);    
    printf("Email: ");
    fread(buffer, 81, 1, arq);
    printf("%s\n", buffer);
    printf("Nationality: ");
    fread(buffer, 51, 1, arq);
    printf("%s\n", buffer);  
    printf("Age: ");
    fread(buffer, 4, 1, arq);
    printf("%s\n\n", buffer);        
}




// funcao para descobrir o tamanho de um arquivo

int get_tam(FILE *arq){
    long counter = 0;
    char temp[1]; 
    while(fread(temp, 1, 1, arq)) counter++;
    return counter / REG;
}




// funcoes para adicao de lixo ao registro

void add_trash_2_register(registro *reg){
	add_trash_2_string(reg->firstname);
	add_trash_2_string(reg->lastname);
	add_trash_2_string(reg->email);
	add_trash_2_string(reg->nationality);
	return;
}

void add_trash_2_string(char *str){
	int sizeof_field = sizeof(str);
	int str_length = strlen(str) + 1; // pegar o tamanho da string, incluindo o \0
	for(int i = str_length; i < (sizeof_field - 1); i++){
		str[i] = TRASH; 		// completa de lixo a partir do \0 ate o final do campo
	}	
}




// escreve um registro em um arquivo, na forma binaria

void write_register(registro *reg, FILE *arq){
	fwrite(reg->firstname, sizeof(char), 51, arq);  
	fwrite(reg->lastname, sizeof(char), 51, arq);  
	fwrite(reg->email, sizeof(char), 51, arq);  
	fwrite(reg->nationality, sizeof(char), 51, arq);  
	fwrite(&reg->age, sizeof(int), 1, arq);  
	return;
}




// le informacoes da entrada padrao e atribui aos respectivos campos de um registro

void get_register(registro *reg){
	// variaveis auxiliares
	int aux;
	char aux_c[81];


	// le nome e sobrenome e separa os respectivos campos
	readline(aux_c);
	int i = 0, j = 0;
	while(aux_c[i] != ' '){
		reg->firstname[i] = aux_c[i];
		i++;
	}
	i++;
	reg->firstname[i] = '\0';

	while(aux_c[i] != '\0'){
		reg->lastname[j] = aux_c[i];
		i++;
		j++;
	}
	j++;
	reg->lastname[j] = '\0';

	// le email	
	readline(aux_c);
	i = 0;
	while(aux_c[i] != '\0'){
		reg->email[i] = aux_c[i];
		i++;
	}	
	i++;
	reg->email[i] = '\0';
	
	// le nacionalidade
	readline(aux_c);
	i = 0;
	while(aux_c[i] != '\0'){
		reg->nationality[i] = aux_c[i];
		i++;
	}
	i++;
	reg->nationality[i] = '\0';

	// le idade
	scanf("%d ", &aux);
	reg->age = aux;
	
	add_trash_2_register(reg); // adiciona lixo aos byte nao preenchidos dos campos do registro

	return;
}

