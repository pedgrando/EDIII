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

void LeRegistro(FILE *file_in, Registro *Register){
    char aux2;
    char aux[64];
    while((aux2 = fgetc(file_in)) != '\n');
    printf("%s", aux);
    fscanf(file_in, "%s", aux);
    printf("%s\n\n\n", aux);
    fscanf(file_in, "%s", aux);
    printf("%s\n\n\n", aux);
    fscanf(file_in, "%s", aux);
    printf("%s\n\n\n", aux);
    fscanf(file_in, "%d,%s,%d,%c,%d,%s,%s", &Register->idConecta, Register->siglaPais, &Register->idPoPsConectado, &Register->unidadeMedida, &Register->velocidade, Register->nomePoPs, Register->nomePais);
    printf("%d\n%s\n%d\n%c\n%d\n%s\n%s\n\n\n", Register->idConecta, Register->siglaPais, Register->idPoPsConectado, Register->unidadeMedida, Register->velocidade, Register->nomePoPs, Register->nomePais);

}   
 

void TransfereDados(FILE *file_in, FILE *file_out){
    Registro *Register = malloc(sizeof(Registro)); 
    char aux[64];
    LeRegistro(file_in, Register);
    free(Register);
}


// FUNCOES PARA EXIBIR REGISTROS

void imprime_arq_tela(FILE *arq_entrada){
	Registro *







}



























