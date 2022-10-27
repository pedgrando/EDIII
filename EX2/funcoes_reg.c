#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include "funcoes.h"

//================== EM ARQUIVOS BINARIOS ===========================

void EscreveRegistroBin(FILE *file, Registro *Register){
	
	int bytes_ocupados = 22 + strlen(Register->nomePoPs) + strlen(Register->nomePais);

	fwrite(&Register->removido, sizeof(char), 1, file);
	fwrite(&Register->encadeamento, sizeof(int), 1, file);
	fwrite(&Register->idConecta, sizeof(int), 1, file);
	fwrite(Register->siglaPais, sizeof(char), 2, file);
	fwrite(&Register->idPoPsConectado, sizeof(int), 1, file);
	fwrite(&Register->unidadeMedida, sizeof(char), 1, file);
	fwrite(&Register->velocidade, sizeof(int), 1, file);
	fwrite(Register->nomePoPs, sizeof(char), strlen(Register->nomePoPs), file);
	fwrite("|", sizeof(char), 1, file);
	fwrite(Register->nomePais, sizeof(char), strlen(Register->nomePais), file);
	fwrite("|", sizeof(char), 1, file);

	for(int i = 0; i < (64 - bytes_ocupados); i++){
		fwrite("$", sizeof(char), 1, file);
	}
    
}

void LeRegistroBin(Registro *Register, FILE *arq_entrada){

	int byteoffset = 20;

	fseek(arq_entrada, 960, SEEK_SET);

	readstring(arq_entrada, 1, &(Register->removido));

	readint(arq_entrada, &(Register->encadeamento));

	readint(arq_entrada, &(Register->idConecta));
	Register->campoVazio[0] = campovazio_int(Register->idConecta);

	readstring(arq_entrada, 2, Register->siglaPais);	
	Register->campoVazio[3] = campovazio_string(Register->siglaPais);

	readint(arq_entrada, &(Register->idPoPsConectado));
	Register->campoVazio[4] = campovazio_int(Register->idPoPsConectado);

	readstring(arq_entrada, 1, &(Register->unidadeMedida));
	Register->campoVazio[6] = campovazio_string(&(Register->unidadeMedida));

	readint(arq_entrada, &(Register->velocidade));
	Register->campoVazio[5] = campovazio_int(Register->velocidade);

	byteoffset += readstring_variavel(arq_entrada, Register->nomePoPs);
	Register->campoVazio[1] = campovazio_string_var(Register->nomePoPs);

	byteoffset += readstring_variavel(arq_entrada, Register->nomePais);
	Register->campoVazio[2] = campovazio_string_var(Register->nomePais);

	fseek(arq_entrada, 64 - byteoffset, SEEK_CUR);

	return;
}


void RemoveRegistro(FILE *arq, Cabecalho *header, int rrn){
	int topo = header->topo;

	header->topo = rrn;
	header->nroRegRem++;

	fseek(arq, 0, SEEK_SET);
	EscreveHeaderBin(arq, header);

	fseek(arq, 960+64*rrn, SEEK_SET);

	char lixo[59];

	for(int i = 0; i < 59; i++) lixo[i] = LIXO;
	
	fwrite("1", sizeof(char), 1, arq);
	fwrite(topo, sizeof(int), 1, arq);
    fwrite(lixo, sizeof(char), 59, arq);
}

//====================== COMO STRUCT ======================


void resetaRegistro(Registro *Register){
    for (int i = 0; i < 7; i++) Register->campoVazio[i] = 1;
    Register->removido = '0';
    Register->encadeamento = -1;
    Register->nomePoPs[0] = '\0';
    Register->nomePais[0] = '\0';
    strcpy(Register->siglaPais, "$$\0");
    Register->idPoPsConectado = -1;
    Register->unidadeMedida = '$';
    Register->velocidade = -1;
}

int LeRegistro(FILE *file_in, Registro *Register){
    char aux;
    char aux2[5];
    resetaRegistro(Register);
    
    int j = 0;

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
        Register->campoVazio[j] = 0;
    }

    j++;
    i = 0;
    while(1) {
        aux = fgetc(file_in);
        if (aux == ',') break;
        Register->nomePoPs[i] = aux;
        i++;
    }
    if (i > 0) {
		Register->nomePoPs[i] = '\0';
		//while(Register->nomePoPs[i--] == ' ' ) Register->nomePoPs[i] = '\0';
        Register->campoVazio[j] = 0;
    }

    j++;
    i = 0;
    while(1) {
        aux = fgetc(file_in);
        if (aux == ',') break;
        Register->nomePais[i] = aux;
        i++;
    } 
    if (i > 0){
		Register->nomePais[i] = '\0';
		//while(Register->nomePais[i--] == ' ' ) Register->nomePais[i] = '\0';
		Register->campoVazio[j] = 0;
    }

    j++;
    i = 0;
    while(1) {
        aux = fgetc(file_in);
        if (aux == ',') break;
        Register->siglaPais[i] = aux;
        i++;
    }
    if (i > 0) {
        Register->siglaPais[i] = '\0';
        Register->campoVazio[j] = 0;
    }

    j++;
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
        Register->campoVazio[j] = 0;
    }

    j++;
    i = 0;
    while(1) {
        aux = fgetc(file_in);
        if (aux == ',') break;
        aux2[i] = aux;
        i++;
    }
    if(i > 0){
        Register->unidadeMedida = aux2[0];
        Register->campoVazio[j] = 0;
    }

    j++;
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
        Register->campoVazio[j] = 0;
    }

    return 1;
}   
 
void ImprimeRegistro(Registro *Register){
    if(!Register->campoVazio[0]) printf("Identificador do ponto: %d\n", Register->idConecta);
    if(!Register->campoVazio[1]) printf("Nome do ponto: %s\n", Register->nomePoPs);
    if(!Register->campoVazio[2]) printf("Pais de localizacao: %s\n", Register->nomePais);
    if(!Register->campoVazio[3]) printf("Sigla do pais: %c%c\n", Register->siglaPais[0], Register->siglaPais[1]);
    if(!Register->campoVazio[4]) printf("Identificador do ponto conectado: %d\n", Register->idPoPsConectado);
    if(!Register->campoVazio[5] && !Register->campoVazio[6]) printf("Velocidade de transmissao: %d %cbps\n", Register->velocidade, Register->unidadeMedida);
    printf("\n");
}

