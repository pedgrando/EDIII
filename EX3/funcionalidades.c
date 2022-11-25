#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "miscelaneous.h"
#include "funcoes_io.h"
#include "data_structures.h"
#include "funcionalidades.h"
#include "funcoes_principais.h"
#include "arvore_b.h"

void funcionalidade1(FILE *file_in, FILE *file_out, char *arq){
	Cabecalho *header = malloc(sizeof(Cabecalho));
	*header = ResetaCabecalho();
	header->status = '0';
	CriaHeader(file_out, header);
	TransfereDados(file_in, file_out, header);

	fclose(file_in);
	fclose(file_out);
	binarioNaTela(arq);
	free(header);
}

void funcionalidade2(FILE *file){
	Cabecalho *header = getHeader(file);
	if(header->status == '0'){  // confere se o arquivo eh valido
		PrintErro();
		return;
	}

	PrintArquivo(file, header);
	free(header);
}


void funcionalidade3(FILE *file, char *arq){
	Cabecalho *header = getHeader(file);
	if(header->status == '0'){	// testa se o arquivo é consistente    	
		PrintErro();
		return;
	}

	int n;									//quantas consultas serão realizadas
	int falha_de_processamento;				//flag para caso não consiga remover

	scanf("%d", &n);

	char (*valorCampo)[32] = malloc(sizeof(*valorCampo)*n);
	int *hash_campo = malloc(sizeof(int)*n);

	Cabecalho *header = NULL;
	header = getHeader(file);


	for(int i = 0; i < n; i++){	
		char aux[32];

		scanf("%s", aux);

		scan_quote_string(valorCampo[i]);

		hash_campo[i] = hashfunction(aux);			//transforma o nome do campo em valor inteiro

		// dentro da funcao, recebe os parametros da busca 

	}

	//faz n buscas para as condicoes especificadas pela entrada fazendo a consulta (PrintaRegistro)
	
	
	int falha_de_processamento;

	for(int i = 0; i < n; i++){
		falha_de_processamento = BuscaRegistro(file, header, hash_campo[i], valorCampo[i], CONSULTA, i+1);

		if(falha_de_processamento) break;
	}
		
	free(header);
	free(valorCampo);
	free(hash_campo);

	fclose(file);
}


void funcionalidade4(FILE *file, char *arq){
	Cabecalho *header = getHeader(file);
	if(header->status == '0'){	// testa se o arquivo é consistente    	
		PrintErro();
		return;
	}

	int n;									//quantas consultas serão realizadas
	int falha_de_processamento;				//flag para caso não consiga remover

	scanf("%d", &n);		

	char valorCampo[32];
	int hash_campo;
	char aux[32];

	//faz n buscas para as condicoes especificadas pela entrada fazendo a remocao (RemoveRegistro)
	Cabecalho *header = NULL;
	header = getHeader(file);


	for(int i = 0; i < n; i++){	

		scanf("%s", aux);

		scan_quote_string(valorCampo);

		hash_campo = hashfunction(aux);				//transforma o nome do campo em valor inteiro

		// dentro da funcao, recebe os parametros da busca 
		falha_de_processamento = BuscaRegistro(file, header, hash_campo, valorCampo, REMOCAO, 0);

		if(falha_de_processamento)
			break;
	}
	fseek(file, 0, SEEK_SET);
	EscreveHeader(file, header);
	
	free(header);
	fclose(file);
	binarioNaTela(arq);
}

void funcionalidade5(FILE *file, char *arq){
	int n;			//numero de insercoes
	scanf("%d", &n);		

	Cabecalho *header = getHeader(file);
	if(header->status == '0'){	// testa se o arquivo é consistente    	
		PrintErro();
		return;
	}
	
	Registro Register[n];

	for(int i = 0; i < n; i++){
		
		LeEntradaRegistro(&Register[i]);					//leitura do teclado
				
		InsereRegistro(file, &Register[i], header);			//escreve registro no arquivo binario
	
	}		

	fseek(file, 0, SEEK_SET);

	EscreveHeader(file, header);

	free(header);
	fclose(file);
	binarioNaTela(arq);

}

// funcionalidade 6 -> compacta um arquivo

void funcionalidade6(FILE *file, char *arq){
	
	CompactaArquivo(file, arq);
}

void funcionalidade7(FILE *file){
	FILE *index_in;
	char indice_entrada[32];
	scanf("%s", indice_entrada);
	if(!(index_in = fopen(indice_entrada, "w+b"))) {    // testa se o arquivo foi criado            
		PrintErro();
		break;
	}
	
	//CRIAR ARVORE

	fclose(index_in);
}

void funcionalidade8(FILE *file){
	FILE *index_in;
	char indice_entrada[32];
	scanf("%s", indice_entrada);
	if(!(index_in = fopen(indice_entrada, "rb+"))) {    // testa se o arquivo foi aberto corretamente            
		PrintErro();
		break;
	}

	int n;
	scanf("%d", n);

	char (*valorCampo)[32] = malloc(sizeof(*valorCampo)*n);
	int *hash_campo = malloc(sizeof(int)*n);

	Cabecalho *header = NULL;
	header = getHeader(file);


	for(int i = 0; i < n; i++){	
		char aux[32];

		scanf("%s", aux);

		scan_quote_string(valorCampo[i]);

		hash_campo[i] = hashfunction(aux);			//transforma o nome do campo em valor inteiro

		// dentro da funcao, recebe os parametros da busca 

	}

	//faz n buscas para as condicoes especificadas pela entrada fazendo a consulta (PrintaRegistro)
	
	
	int falha_de_processamento;

	for(int i = 0; i < n; i++){
		if(hash_campo[i] == IDCONECTA){
			//falha_de_processamento = BuscaArvore(file, header, hash_campo[i], valorCampo[i], CONSULTA, i+1);
		} else {
			falha_de_processamento = BuscaRegistro(file, header, hash_campo[i], valorCampo[i], CONSULTA, i+1);
		}

		if(falha_de_processamento) break;
	}
		
	free(header);
	free(valorCampo);
	free(hash_campo);

	fclose(index_in);
}

void funcionalidade9(FILE *file, char *arq){
	FILE *index_in;
	char indice_entrada[32];
	scanf("%s", indice_entrada);
	if(!(index_in = fopen(indice_entrada, "rb+"))) {    // testa se o arquivo foi aberto corretamente            
		PrintErro();
		break;
	}

	funcionalidade5(file, arq);

	//ATUALIZAR ARVORE E INSERIR NO INDICE
}

void funcionalidade10(FILE *file){
	FILE *file_in2;
	char arq_entrada2[32];
	scanf("%s", arq_entrada2);
	if(!(file_in2 = fopen(arq_entrada2, "rb+"))) {    // testa se o arquivo foi aberto corretamente            
		PrintErro();
		break;
	}
	
	Cabecalho *header1 = NULL;
	header1 = getHeader(file);

	Cabecalho *header2 = NULL;
	header2 = getHeader(file_in2);

	char campo1[32];
	char campo2[32];
	scanf("%s", campo1);
	scanf("%s", campo2);
	
	int hash_campo1;
	int hash_campo2;
	hash_campo1 = hashfunction(campo1);
	hash_campo2 = hashfunction(campo2);

	FILE *index_in;
	char indice_entrada[32];
	scanf("%s", indice_entrada);
	if(!(index_in = fopen(indice_entrada, "rb+"))) {    // testa se o arquivo foi aberto corretamente            
		PrintErro();
		break;
	}

	for(int i = 0; i < header1.proxRRN; i++){
		for(int j = 0; j < header2.proxRRN; j++){
			//BUSCAR REGISTROS COMPATIVEIS
		}
	}
}



