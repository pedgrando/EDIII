#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

//teste parte 2

Cabecalho InicializaStructCabecalho(){
    Cabecalho aux;
    aux.status = 0;
    aux.status = -1;
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

//FUNCOES DE MANIPULAÇÃO DE ARQUIVOS --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void CriaHeader(FILE *file, Cabecalho *header){
    PreencheLixo(file);
    fwrite(&header->status, sizeof(char), 1, file);
    fwrite(&header->topo, sizeof(int), 1, file);
    fwrite(&header->proxRRN, sizeof(int), 1, file);
    fwrite(&header->nroRegRem, sizeof(int), 1, file);
    fwrite(&header->nroPagDisco, sizeof(int), 1, file);
    fwrite(&header->qttCompacta, sizeof(int), 1, file);
}

void PreencheLixo(FILE *file){
	char lixo[960];
    for (int i = 0; i < PAG_DISCO; i++) lixo[i] = LIXO;
    fwrite(lixo, sizeof(char), PAG_DISCO, file);  
    fseek(file, 0, SEEK_SET);
}


void resetaRegistro(Registro *Register){
    Register->idConecta;
    Register->nomePoPs[0] = DEL;
    Register->nomePais[0] = DEL;
    strcpy(Register->siglaPais, "$$");
    Register->idPoPsConectado = -1;
    Register->unidadeMedida = '$';
    Register->velocidade = -1;
}

int LeRegistro(FILE *file_in, Registro *Register){
    char aux;
    char aux2[5];
    resetaRegistro(Register);
    
    int i = 0;
    while(1) {
        aux = fgetc(file_in);
        if (aux == ',') break;
        if (aux == EOF) return 0;
        aux2[i] = aux;
        i++;
    }
    if(i > 0){
        aux2[i] = '\0';
        Register->idConecta = atoi(aux2);
    }

    i = 0;
    while(1) {
        aux = fgetc(file_in);
        if (aux == ',') break;
        Register->nomePoPs[i] = aux;
        i++;
    }
    if (i > 0) Register->nomePoPs[i] = '\0';

    i = 0;
    while(1) {
        aux = fgetc(file_in);
        if (aux == ',') break;
        Register->nomePais[i] = aux;
        i++;
    } 
    if (i > 0) Register->nomePais[i] = '\0';

    i = 0;
    while(1) {
        aux = fgetc(file_in);
        if (aux == ',') break;
        Register->siglaPais[i] = aux;
        i++;
    }
    if (i > 0) Register->siglaPais[i] = '\0';

    i = 0;
    while(1) {
        aux = fgetc(file_in);
        if (aux == ',') break;
        aux2[i] = aux;
        i++;
    }
    if(i > 0){
        aux2[i] = '\0';
        Register->idPoPsConectado = atoi(aux2);
    }

    i = 0;
    while(1) {
        aux = fgetc(file_in);
        if (aux == ',') break;
        aux2[i] = aux;
        i++;
    }
    if(i > 0){
        Register->unidadeMedida = aux2[0];
    }

    i = 0;
    while(1) {
        aux = fgetc(file_in);
        if (aux == '\n' || aux == '\r' || aux == '\0') break;
        aux2[i] = aux;
        i++;
    }
    if(i > 0) {
        aux2[i] = '\0';
        Register->velocidade = atoi(aux2);
    }

    //printf("%d\n%s\n%s\n%s\n%d\n%c\n%d\n\n\n", Register->idConecta, Register->nomePoPs, Register->nomePais, Register->siglaPais, Register->idPoPsConectado, Register->unidadeMedida, Register->velocidade);
    return 1;
}   
 

void TransfereDados(FILE *file_in, FILE *file_out){
    char aux[64];
    while(fgetc(file_in) != '\n');
    Registro *Register = malloc(sizeof(Registro)); 
    while (LeRegistro(file_in, Register)){
        
        EscreveRegistro(file_out, Register);
    }    
    free(Register);
}

void EscreveRegistro(FILE *file, Registro *Register){
    fwrite(&Register->removido, sizeof(char), 1, file);
    fwrite(&Register->encadeamento, sizeof(int), 1, file);
    fwrite(&Register->idConecta, sizeof(char), 1, file);
    fwrite(Register->siglaPais, sizeof(char), 2, file);
    fwrite(&Register->idPoPsConectado, sizeof(int), 1, file);
    fwrite(&Register->unidadeMedida, sizeof(char), 1, file);
    fwrite(&Register->velocidade, sizeof(int), 1, file);
    fwrite(Register->nomePoPs, sizeof(Register->nomePoPs), 1, file);
    fwrite(Register->nomePais, sizeof(Register->nomePais), 1, file);
}



// FUNCOES PARA EXIBIR REGISTROS

void imprime_arq_tela(FILE *arq_entrada){
	Registro *







}


























