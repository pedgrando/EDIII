#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "miscelaneous.h"
#include "funcoes_io.h"
#include "data_structures.h"
#include "funcionalidades.h"

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

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		int i = 1;
		while((R = getchar()) != EOF && !isspace(R)){
			str[i] = R;
			i++;
		}
		str[i] = '\0';

	} else { // EOF
		strcpy(str, "");
	}
}

// le o cabecalho de um arquivo binario e retorna ele

Cabecalho *getHeader(FILE *file){
    Cabecalho *aux = malloc(sizeof(Cabecalho)*1);
    fread(&(aux->status), sizeof(char), 1, file);
    fread((&aux->topo), sizeof(int), 1, file);
    fread((&aux->proxRRN), sizeof(int), 1, file);
    fread((&aux->nroRegRem), sizeof(int), 1, file);
    fread((&aux->nroPagDisco), sizeof(int), 1, file);
    fread((&aux->qttCompacta), sizeof(int), 1, file);
	return aux;
}

//FUNCOES DE MANIPULAÇÃO DE ARQUIVOS --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// escreve os campos do header no arquivo

void EscreveHeader(FILE *file, Cabecalho *header){
    fwrite(&header->status, sizeof(char), 1, file);
    fwrite(&header->topo, sizeof(int), 1, file);
    fwrite(&header->proxRRN, sizeof(int), 1, file);
    fwrite(&header->nroRegRem, sizeof(int), 1, file);
    fwrite(&header->nroPagDisco, sizeof(int), 1, file);
    fwrite(&header->qttCompacta, sizeof(int), 1, file);
}

// preenche o espaço restante de um header com lixo ate completar 960 bytes ( 1 pag de disco )

void PreencheLixo(FILE *file){
	char lixo[PAG_DISCO - 21];
    for (int i = 0; i < PAG_DISCO - 21; i++) lixo[i] = LIXO;
    fwrite(lixo, sizeof(lixo), 1, file);  
}

// le um registro de um arquivo .csv e passa para memoria primaria

int getRegistroCsv(FILE *file_csv, Registro *Register){
    char aux;
    char aux2[5];
    ResetaRegistro(Register); 		// reseta a variavel registro
    
    int j = 0;


    // para cada campo, le-se ate a virgula e depois o valor e passado para o campo correspondente da variavel Registro
    // tambem se testa se o campo esta vazio ou nao

    int i = 0;
    while(1) {
        aux = fgetc(file_csv);
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
        aux = fgetc(file_csv);
        if (aux == ',') break;
        Register->nomePoPs[i] = aux;
        i++;
    }
    if (i > 0) {
	    Register->nomePoPs[i] = '\0'; 
		while(Register->nomePoPs[i-1] == ' ' ) Register->nomePoPs[--i] = '\0'; // tira espaço caso tenha no final
        Register->campoVazio[j] = 0;
    }

    j++;
    i = 0;
    while(1) {
        aux = fgetc(file_csv);
        if (aux == ',') break;
        Register->nomePais[i] = aux;
        i++;
    } 
    if (i > 0){
		Register->nomePais[i] = '\0';
		while(Register->nomePais[i-1] == ' ' ) Register->nomePais[--i] = '\0';
		Register->campoVazio[j] = 0;
    }

    j++;
    i = 0;
    while(1) {
        aux = fgetc(file_csv);
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
        aux = fgetc(file_csv);
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
        aux = fgetc(file_csv);
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
        aux = fgetc(file_csv);
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
 
// imprime todos os campos nao vazios de um registro, segundo a proposta do trabalho

void ImprimeRegistro(Registro *Register){
    if(!Register->campoVazio[0]) printf("Identificador do ponto: %d\n", Register->idConecta);
    if(!Register->campoVazio[1]) printf("Nome do ponto: %s\n", Register->nomePoPs);
    if(!Register->campoVazio[2]) printf("Pais de localizacao: %s\n", Register->nomePais);
    if(!Register->campoVazio[3]) printf("Sigla do pais: %c%c\n", Register->siglaPais[0], Register->siglaPais[1]);
    if(!Register->campoVazio[4]) printf("Identificador do ponto conectado: %d\n", Register->idPoPsConectado);
    if(!Register->campoVazio[5] && !Register->campoVazio[6]) printf("Velocidade de transmissao: %d %cbps\n", Register->velocidade, Register->unidadeMedida);
    printf("\n");
}


// escreve o registro da memoria primaria no arquivo binario, incluindo o lixo

void EscreveRegistro(FILE *file, Registro *Register){
	int bytes_ocupados = 22 + strlen(Register->nomePoPs) + strlen(Register->nomePais); 	// descobre o numero de bytes ocupados pelo registro (apesar do strlen retornar 1 a mais por conta do '\0', ele eh compensado pelo '|')

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

	for(int i = 0; i < (64 - bytes_ocupados); i++){  	// preenche o que nao foi ocupado pelos dados com lixo
		fwrite("$", sizeof(char), 1, file);
	}
    
}

// imprime o numero de paginas de disco do arquivo

void PrintPagDisco(Cabecalho *header){
	printf("Numero de paginas de disco: %d\n\n", header->nroPagDisco);
}

// le um registro de um arquivo binario e passa ele para memoria primaria
//  o vetor campo vazio dessa funcao pode ser melhor compreendido com a explicacao presente no arquivos .h

void LeRegistroBin(Registro *Register, FILE *file){

	int byteoffset = 20; // byteoffset comeca em 20 porque ja se considera os campos de tamanho fixo, mas o status do registro ja foi lido, entao o ponteiro de arquivo ja esta no primeiro byte

	readint(file, &(Register->encadeamento)); 				// le o encadeamento do registro

	readint(file, &(Register->idConecta)); 					// le o idConecta e confere se ele eh vazio 
	Register->campoVazio[0] = campovazio_int(Register->idConecta);

	readstring(file, 2, Register->siglaPais);				// le a siglaPais e confere se ela eh vazia
	Register->campoVazio[3] = campovazio_string(Register->siglaPais);

	readint(file, &(Register->idPoPsConectado)); 				// le o idPoPsConectado e confere se ele eh vazio
	Register->campoVazio[4] = campovazio_int(Register->idPoPsConectado);

	readstring(file, 1, &(Register->unidadeMedida));                         // le a unidadeMedida e confere se ela eh vazia
	Register->campoVazio[6] = campovazio_string(&(Register->unidadeMedida));

	readint(file, &(Register->velocidade)); 					// le a velocidade e confere se ela eh vazia
	Register->campoVazio[5] = campovazio_int(Register->velocidade);

	byteoffset += readstring_variavel(file, Register->nomePoPs);  		// le o nomePoPs, incrementa o byteoffset e testa se ele eh vazio
	Register->campoVazio[1] = campovazio_string_var(Register->nomePoPs);

	byteoffset += readstring_variavel(file, Register->nomePais); 		// le o nomePais, incrementa o byteoffset e testa se ele eh vazio
	Register->campoVazio[2] = campovazio_string_var(Register->nomePais);

	fseek(file, 64 - byteoffset, SEEK_CUR); 					// pula o restante de lixo no registro

	return;
}

// le um inteiro e atribui a uma variavel passada por referencia

void readint(FILE *file, int *integer){
	fread(integer, sizeof(int), 1, file); 
}

// le uma string de tamanho fixo "num_char" e atribui a uma variavel passada por referencia

void readstring(FILE *file, int num_char, char *string){
	fread(string, sizeof(char), num_char, file); 
}

// le uma string de tamanho variavel e atribui a uma variavel passada por referencia, retornando o numero de caracteres que foram lidos do arquivo
// o retorno eh util para a atualizacao do byteoffset

int readstring_variavel(FILE *file, char *string){
	char aux = '\0';
	int i = 0;
	while(fread(&aux, sizeof(char), 1, file)){ 
		if(aux == '|'){
			break;
		}
		string[i] = aux;
		i++;
	}
	string[i] = '\0';
	return i+1;
}

// le cada campo de um registro pela entrada padrao e atribui esses valores a um registro
// os valores de entrada podem estar entre " ", serem inteiros ou serem nulos (NULO)

void LeEntradaRegistro(Registro *Register){
	ResetaRegistro(Register);

	char aux[64];
	
	scanf("%d", &Register->idConecta);
	
	scan_quote_string(aux);
	if(strcmp(aux, "")){
		strcpy(Register->nomePoPs, aux);
	}

	scan_quote_string(aux);
	if(strcmp(aux, "")){
		strcpy(Register->nomePais, aux);
	}

	scan_quote_string(aux);
	if(strcmp(aux, "")){
		strcpy(Register->siglaPais, aux);
	}

	scan_quote_string(aux);
	if(strcmp(aux, "")){
		Register->idPoPsConectado = atoi(aux);
	}

	scan_quote_string(aux);
	if(strcmp(aux, "")){
		Register->unidadeMedida = aux[0];
	}

	scan_quote_string(aux);
	if(strcmp(aux, "")){
		Register->velocidade = atoi(aux);
	}

}

void PrintErro(){
	printf("Falha no processamento do arquivo.\n");
}


void le_no_arvore(FILE *arq_arv, Registro_Arvore *pagina, int RRN){
	if(arq_arv == NULL) return;

	fseek(arq_arv, 65*(RRN+1), SEEK_SET);

	readstring(arq_arv, 1, &(pagina->folha));

	readint(arq_arv, &(pagina->nroChavesNo));
	readint(arq_arv, &(pagina->alturaNo));
	readint(arq_arv, &(pagina->RRNdoNo));

	for(int i = 0; i < 4; i++){
		readint(arq_arv, &(pagina->P[i]));
		readint(arq_arv, &(pagina->C[i]));
		readint(arq_arv, &(pagina->PR[i]));
	}

	readint(arq_arv, &(pagina->P[4]));
}

void escreve_no(FILE *arq_arv, Registro_Arvore *pagina, int RRN){
	fseek(arq_arv, 65*(RRN+1), SEEK_SET);
	
	fwrite(&pagina->folha, sizeof(char), 1, arq_arv);
	fwrite(&pagina->nroChavesNo, sizeof(int), 1, arq_arv);
	fwrite(&pagina->alturaNo, sizeof(int), 1, arq_arv);
	fwrite(&pagina->RRNdoNo, sizeof(int), 1, arq_arv);
	fwrite(&pagina->P[0], sizeof(int), 1, arq_arv);

	for(int i = 0; i < 4; i++){
		fwrite(&pagina->C[i],sizeof(int), 1, arq_arv);
		fwrite(&pagina->PR[i],sizeof(int), 1, arq_arv);
		fwrite(&pagina->P[i+1],sizeof(int), 1, arq_arv);
	}
}


void le_header_arv(FILE *arq_arv, Cabecalho_Arvore *header){
	if(arq_arv == NULL) return;
	
	rewind(arq_arv);
	readstring(arq_arv, 1, &header->status);
	readint(arq_arv, &header->noRaiz);
	readint(arq_arv, &header->nroChavesTotal);
	readint(arq_arv, &header->alturaArvore);
	readint(arq_arv, &header->RRNproxNo);

	fseek(arq_arv, 49, SEEK_CUR);
}

void escreve_header_arv(FILE* arv, Cabecalho_Arvore *header){
	fseek(arv, 0, SEEK_SET);

	fwrite(&header->status, sizeof(char), 1, arv);
	fwrite(&header->noRaiz, sizeof(int), 1, arv);
	fwrite(&header->nroChavesTotal, sizeof(int), 1, arv);
	fwrite(&header->alturaArvore, sizeof(int), 1, arv);
	fwrite(&header->RRNproxNo, sizeof(int), 1, arv);

	for(int i = 0; i < 48; i++){
		fwrite("$", sizeof(char), 1, arv);
	}
}


void ImprimeRegistroCombinado(Registro *Register1, Registro *Register2){
	
	if(!Register1->campoVazio[0]) printf("Identificador do ponto: %d\n", Register1->idConecta);
	if(!Register1->campoVazio[1]) printf("Nome do ponto: %s\n", Register1->nomePoPs);
	if(!Register1->campoVazio[2]) printf("Pais de localizacao: %s\n", Register1->nomePais);
	if(!Register1->campoVazio[3]) printf("Sigla do pais: %s\n", Register1->siglaPais);
	if(!Register1->campoVazio[4]) printf("Identificador do ponto conectado: %d\n", Register1->idPoPsConectado);
	if(!Register2->campoVazio[1]) printf("Nome do ponto conectado: %s\n", Register2->nomePoPs);
	if(!Register2->campoVazio[2]) printf("Nome do pais conectado: %s\n", Register2->nomePais);
	if(!Register2->campoVazio[3]) printf("Sigla do pais: %s\n", Register2->siglaPais);
	if(!Register1->campoVazio[5] && !Register1->campoVazio[6]) printf("Velocidade de transmissao: %d %cbps\n", Register1->velocidade, Register1->unidadeMedida);
	printf("\n");
}











