#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "funcoes.h"
#include "miscelaneous.h"
#include "funcoes_io.h"
#include "data_structures.h"
#include "funcionalidades.h"

Cabecalho *getHeader(FILE *arq){
    Cabecalho *aux = malloc(sizeof(Cabecalho)*1);
    fread(&(aux->status), sizeof(char), 1, arq);
    fread((&aux->topo), sizeof(int), 1, arq);
    fread((&aux->proxRRN), sizeof(int), 1, arq);
    fread((&aux->nroRegRem), sizeof(int), 1, arq);
    fread((&aux->nroPagDisco), sizeof(int), 1, arq);
    fread((&aux->qttCompacta), sizeof(int), 1, arq);
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

// escreve os campos do header no arquivo

void escreveHeader(FILE *file, Cabecalho *header){
    fwrite(&header->status, sizeof(char), 1, file);
    fwrite(&header->topo, sizeof(int), 1, file);
    fwrite(&header->proxRRN, sizeof(int), 1, file);
    fwrite(&header->nroRegRem, sizeof(int), 1, file);
    fwrite(&header->nroPagDisco, sizeof(int), 1, file);
    fwrite(&header->qttCompacta, sizeof(int), 1, file);
}

// le um registro de um arquivo .csv e passa para memoria primaria

int LeRegistro(FILE *file_in, Registro *Register){
    char aux;
    char aux2[5];
    resetaRegistro(Register); 		// reseta a variavel registro
    
    int j = 0;


    // para cada campo, le-se ate a virgula e depois o valor e passado para o campo correspondente da variavel Registro
    // tambem se testa se o campo esta vazio ou nao

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
		while(Register->nomePoPs[i-1] == ' ' ) Register->nomePoPs[--i] = '\0'; // tira espaço caso tenha no final
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
		while(Register->nomePais[i-1] == ' ' ) Register->nomePais[--i] = '\0';
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

// FUNCOES PARA EXTRAIR OS DADOS BINARIOS

// imprime todos os registros validos de um arquivo

void imprime_arq(FILE *arq_entrada){
	Registro *Register = malloc(sizeof(Registro));
	Cabecalho *header = getHeader(arq_entrada);

	if(header->status == '0'){  // confere se o arquivo eh valido
		PrintarErro();
		free(Register);
		return;
	}

	int tem_registro = 0; // flag para descobrir se algum registro foi encontrado

	fseek(arq_entrada, 960, SEEK_SET); // pula o header

	while(fread(&Register->removido, sizeof(char), 1, arq_entrada) != 0){

		if(Register->removido == '1'){

			fseek(arq_entrada, 63, SEEK_CUR); // pula registro logicamente removido

		} else {

			tem_registro = 1;  // foi encontrado ao menos um registro

			resetaRegistro(Register);

			// le um registro e imprime seu conteudo

			leRegistroBin(Register, arq_entrada); 
				
			ImprimeRegistro(Register);
					
		}
	}

	if(!tem_registro){ 				// se nao tem registros
		printf("Registro inexistente.\n\n");
	}
	imprime_pag_disco(header); // mostra o numero de paginas de disco
}

// busca um registro em especifico para executar uma funcionalidade
/*
 * Essa funcao eh comum as funcionalidades 3 e 4; nela sao passados um arquivo com suas informacoes de header, um campo de busca e um valor buscado, qual das funcionalidades
 * sera executada (CONSULTA = 1, referente a funcionalidade 3, e REMOCAO = 0, referente a funcionalidade 4), alem de um inteiro indentificando o numero da operacao, e.g., 3
 * referente a terceira busca.
 *
 * ela se utiliza de um esquema de hash para identificar qual o campo buscado, os valores tabelados podem ser encontrados nos arquivos de header, e mais informacoes estao na
 * funcao de hash
 */

int buscaRegistro(FILE *arq_entrada, Cabecalho *header, int campoBuscado, char *valorCampo, int funcionalidade, int n){

	fseek(arq_entrada, 0 , SEEK_SET);

	Registro *Register = malloc(sizeof(Registro)*1);

	int rrn = 0; 			// contagem de rrn
	int encontrou_reg = 0; 		// flag para indicar se ao menos um registro foi encontrado
	
	if(header->status == '0'){
		PrintarErro();
		return 1;
	}

	if( n != 0) printf("Busca %d\n", n);  // especificacao do trabalho -> a cada pesquisa, imprime o id dela
	
	fseek(arq_entrada, 960, SEEK_SET); // pula o registro de cabecalho

	while(fread(&Register->removido, sizeof(char), 1, arq_entrada) != 0){

		if(Register->removido == '1'){

			fseek(arq_entrada, 63, SEEK_CUR); // pula registro logicamente removido

		} else {

			leRegistroBin(Register, arq_entrada);
			
			// O switch descobre qual campo deve ser comparado
			// se o valor do campo coincindir com o da busca, marca-se que foi encontrado algum registro, e 
			// executa a funcionalidade desejada (remocao ou consulta)

			switch(campoBuscado){
				case IDCONECTA:
					if(atoi(valorCampo) == Register->idConecta){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							remove_registro(arq_entrada, header, rrn);
						}
					
					}
					break;
				case SIGLAPAIS:
					if(valorCampo[0] == Register->siglaPais[0] && valorCampo[1] == Register->siglaPais[1]){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							remove_registro(arq_entrada, header, rrn);
						}
					
					}
					break;
				case IDPOPSCONECTADO:
					if(atoi(valorCampo) == Register->idPoPsConectado){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							remove_registro(arq_entrada, header, rrn);
						}
					
					}
					break;
				case UNIDADEMEDIDA:
					if(valorCampo[0] == Register->unidadeMedida){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							remove_registro(arq_entrada, header, rrn);
						}
					
					}
					break;
				case VELOCIDADE:
					if(atoi(valorCampo) == Register->velocidade){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							remove_registro(arq_entrada, header, rrn);
						}
					
					}
					break;
				case NOMEPOPS:
					if(!strcmp(valorCampo, Register->nomePoPs)){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							remove_registro(arq_entrada, header, rrn);
						}
					
					}
					break;
				case NOMEPAIS:
					if(!strcmp(valorCampo, Register->nomePais)){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							remove_registro(arq_entrada, header, rrn);
						}
					
					}
					break;
			}
			
		}
		rrn++;
	}

	if(!encontrou_reg && funcionalidade)              // se for consulta -> diz se encontrou ou nao algum registro
		printf("Registro inexistente.\n\n");

	if(funcionalidade){                               // se for consulta -> imprime o numero de paginas de disco
		imprime_pag_disco(header);
	}

	free(Register);	

	return 0;
}

// imprime o numero de paginas de disco do arquivo

void imprime_pag_disco(Cabecalho *header){
	printf("Numero de paginas de disco: %d\n\n", header->nroPagDisco);
}


// le um registro de um arquivo binario e passa ele para memoria primaria
//  o vetor campo vazio dessa funcao pode ser melhor compreendido com a explicacao presente no arquivos .h

void leRegistroBin(Registro *Register, FILE *arq_entrada){

	int byteoffset = 20; // byteoffset comeca em 20 porque ja se considera os campos de tamanho fixo, mas o status do registro ja foi lido, entao o ponteiro de arquivo ja esta no primeiro byte

	readint(arq_entrada, &(Register->encadeamento)); 				// le o encadeamento do registro

	readint(arq_entrada, &(Register->idConecta)); 					// le o idConecta e confere se ele eh vazio 
	Register->campoVazio[0] = campovazio_int(Register->idConecta);

	readstring(arq_entrada, 2, Register->siglaPais);				// le a siglaPais e confere se ela eh vazia
	Register->campoVazio[3] = campovazio_string(Register->siglaPais);

	readint(arq_entrada, &(Register->idPoPsConectado)); 				// le o idPoPsConectado e confere se ele eh vazio
	Register->campoVazio[4] = campovazio_int(Register->idPoPsConectado);

	readstring(arq_entrada, 1, &(Register->unidadeMedida));                         // le a unidadeMedida e confere se ela eh vazia
	Register->campoVazio[6] = campovazio_string(&(Register->unidadeMedida));

	readint(arq_entrada, &(Register->velocidade)); 					// le a velocidade e confere se ela eh vazia
	Register->campoVazio[5] = campovazio_int(Register->velocidade);

	byteoffset += readstring_variavel(arq_entrada, Register->nomePoPs);  		// le o nomePoPs, incrementa o byteoffset e testa se ele eh vazio
	Register->campoVazio[1] = campovazio_string_var(Register->nomePoPs);

	byteoffset += readstring_variavel(arq_entrada, Register->nomePais); 		// le o nomePais, incrementa o byteoffset e testa se ele eh vazio
	Register->campoVazio[2] = campovazio_string_var(Register->nomePais);

	fseek(arq_entrada, 64 - byteoffset, SEEK_CUR); 					// pula o restante de lixo no registro

	return;
}


// FUNCOES PARA LER DO ARQUIVO BINARIO ------------------------------------------------

// le um inteiro e atribui a uma variavel passada por referencia

void readint(FILE *arq, int *integer){
	fread(integer, sizeof(int), 1, arq); 
}

// le uma string de tamanho fixo "num_char" e atribui a uma variavel passada por referencia

void readstring(FILE *arq, int num_char, char *string){
	fread(string, sizeof(char), num_char, arq); 
}

// le uma string de tamanho variavel e atribui a uma variavel passada por referencia, retornando o numero de caracteres que foram lidos do arquivo
// o retorno eh util para a atualizacao do byteoffset

int readstring_variavel(FILE *arq, char *string){
	char aux = '\0';
	int i = 0;
	while(fread(&aux, sizeof(char), 1, arq)){ 
		if(aux == '|'){
			break;
		}
		string[i] = aux;
		i++;
	}
	string[i] = '\0';
	return i+1;
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
// uma funcao hash simples: ela soma os valores dos caracteres de uma string ate o '\0' e retorna o resultado

int hashfunction(char *str){
	int i = 0;
	int result = 0;
	while(str[i] != '\0'){
		result += str[i];	
		i++;
	}
	return result;
}

// remove um registro de um arquivo binario
//
// atribui o rrn do registro ao topo e guarda o topo antigo como encadeamento
// o status do registro fica como removido ("1") e o resto eh preenchido com lixo

void remove_registro(FILE *arq, Cabecalho *header, int rrn){
	int topo = header->topo;

	header->topo = rrn;
	header->nroRegRem++;

	fseek(arq, -64, SEEK_CUR);

	char lixo[59];

	for(int i = 0; i < 59; i++) lixo[i] = LIXO;
	
	fwrite("1", sizeof(char), 1, arq);
	fwrite(&topo, sizeof(int), 1, arq);
       	fwrite(lixo, sizeof(char), 59, arq);
}

void leEntradaRegistro(Registro *Register){
	resetaRegistro(Register);

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


void insereRegistro(FILE *arq, Registro *Register, Cabecalho *header){


	if(header->topo == -1){
		fseek(arq, 960+64*(header->proxRRN), SEEK_SET);
		(header->proxRRN)++;

	} else {
		int novo_topo;
		fseek(arq, 961+64*(header->topo), SEEK_SET);
		
		fread(&novo_topo, sizeof(int), 1, arq);
		header->topo = novo_topo;	

		fseek(arq, -5, SEEK_CUR);
		(header->nroRegRem)--;
	}

	EscreveRegistro(arq, Register);

}

void PrintarErro(){
	printf("Falha no processamento do arquivo.\n");
}












