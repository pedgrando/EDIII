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


// imprime todos os campos nao vazios de um registro, segundo a proposta do trabalho

void ImprimeRegistro(Registro *Register){
    printf("%d ", Register->idConecta);
    printf("%s ", Register->nomePoPs);
    printf("%s ", Register->nomePais);
    printf("%c%c ", Register->siglaPais[0], Register->siglaPais[1]);
    printf("%d ", Register->idPoPsConectado);
    printf("%d %cbps\n", Register->velocidade, Register->unidadeMedida);
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

void PrintErro(){
	printf("Falha no processamento do arquivo.\n");
}

void imprimeLista(lista *li){
    no *aux = (li->inicio);
	while(aux != NULL)
    {
        ImprimeRegistro(&aux->dados);
        aux = aux->prox;
    }
}
