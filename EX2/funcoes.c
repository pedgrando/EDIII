#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include "funcoes.h"

//teste parte 2

Cabecalho InicializaStructCabecalho(){
    Cabecalho aux;
    aux.status = '0';
    aux.topo = -1;
    aux.proxRRN = 0;
    aux.nroRegRem = 0;
    aux.nroPagDisco = 0;
    aux.qttCompacta = 0;
    return aux;
}

//FUNCOES FORNECIDAS

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

//================== PAGINAS DE DISCO ====================================

int GetNumPag(FILE *arq){
    long aux = 0;
    char temp[1]; 
    while(fread(temp, 1, 1, arq)) aux++;  // Conta os caracteres do arquivo
    return aux / PAG_DISCO;
}

void imprime_pag_disco(Cabecalho *header){
	printf("Numero de paginas de disco: %d\n\n", header->nroPagDisco);
}

// FUNCOES PARA CONFERIR SE O CAMPO ESTA VAZIO ------------------------------------------------------------

int campovazio_int(int interger){
	if(interger == -1){
	        return 1;
	} else {
		return 0;
	}		
}

int campovazio_string(char *string){
	if(string[0] == '$'){
		return 1;
	} else {
		return 0;
	}	
}

int campovazio_string_var(char *string){
	if(string[0] == '\0'){
		return 1;
	} else {
		return 0;
	}	
}


// HASH FUNCTION PARA DESCOBRIR O CAMPO

int hashfunction(char *str){
	int i = 0;
	int result = 0;
	while(str[i] != '\0'){
		result += str[i];	
		i++;
	}
	return result;
}


int compara_str(char *str1, char *str2){
	int i = 0;
	if(str1[0] == str2[0] && strlen(str2) == 1) return 0; // pega o caso de um só caracter
	while(str1[i] != '\0' && str2[i] != '\0'){
		if(str1[i] != str2[i]){
			return 1;
		}
		i++;
	}
	return 0;
}

void tira_aspas(char *str){
	int i = 1;
	while(str[i] != '"'){
		str[i-1] = str[i];
		i++;
	}
	str[i] = '\0';
}
