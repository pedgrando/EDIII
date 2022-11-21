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


<<<<<<< HEAD
void funcionalidade1(FILE *file_in, FILE *file_out, char *arq){
	Cabecalho *header = malloc(sizeof(Cabecalho));
	*header = ResetaCabecalho();
	header->status = '0';
=======
void funcionalidade1(FILE *file_in, FILE *file_out, Cabecalho *header, char *arq){
>>>>>>> 3232f41462f2656ad959c1414b3144c4cd146683
	CriaHeader(file_out, header);
	TransfereDados(file_in, file_out, header);

	fclose(file_in);
	fclose(file_out);
	binarioNaTela(arq);
<<<<<<< HEAD
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
=======
>>>>>>> 3232f41462f2656ad959c1414b3144c4cd146683
}


void funcionalidade3(FILE *file, char *arq){
<<<<<<< HEAD
	Cabecalho *header = getHeader(file);
	if(header->status == '0'){	// testa se o arquivo é consistente    	
		PrintErro();
		return;
	}

	int n;									//quantas consultas serão realizadas
	int falha_de_processamento;				//flag para caso não consiga remover
=======
	int n;
>>>>>>> 3232f41462f2656ad959c1414b3144c4cd146683

	scanf("%d", &n);

	char (*valorCampo)[32] = malloc(sizeof(*valorCampo)*n);
	int *hash_campo = malloc(sizeof(int)*n);

<<<<<<< HEAD
=======
	Cabecalho *header = NULL;
	header = getHeader(file);


>>>>>>> 3232f41462f2656ad959c1414b3144c4cd146683
	for(int i = 0; i < n; i++){	
		char aux[32];

		scanf("%s", aux);

		scan_quote_string(valorCampo[i]);

<<<<<<< HEAD
		hash_campo[i] = hashfunction(aux);			//transforma o nome do campo em valor inteiro
=======
		hash_campo[i] = hashfunction(aux);
>>>>>>> 3232f41462f2656ad959c1414b3144c4cd146683

		// dentro da funcao, recebe os parametros da busca 

	}
<<<<<<< HEAD

	//faz n buscas para as condicoes especificadas pela entrada fazendo a consulta (PrintaRegistro)
	
=======
	
	int falha_de_processamento;

>>>>>>> 3232f41462f2656ad959c1414b3144c4cd146683
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
<<<<<<< HEAD
	Cabecalho *header = getHeader(file);
	if(header->status == '0'){	// testa se o arquivo é consistente    	
		PrintErro();
		return;
	}

	int n;									//quantas consultas serão realizadas
	int falha_de_processamento;				//flag para caso não consiga remover

	scanf("%d", &n);		
=======
	int n;
	int falha_de_processamento;

	scanf("%d", &n);
>>>>>>> 3232f41462f2656ad959c1414b3144c4cd146683

	char valorCampo[32];
	int hash_campo;
	char aux[32];

<<<<<<< HEAD
	//faz n buscas para as condicoes especificadas pela entrada fazendo a remocao (RemoveRegistro)
=======
	Cabecalho *header = NULL;
	header = getHeader(file);

>>>>>>> 3232f41462f2656ad959c1414b3144c4cd146683

	for(int i = 0; i < n; i++){	

		scanf("%s", aux);

		scan_quote_string(valorCampo);

<<<<<<< HEAD
		hash_campo = hashfunction(aux);				//transforma o nome do campo em valor inteiro
=======
		hash_campo = hashfunction(aux);
>>>>>>> 3232f41462f2656ad959c1414b3144c4cd146683

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
<<<<<<< HEAD
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
=======
	int n;

	Cabecalho *header = getHeader(file);
	
	scanf("%d", &n);

	if(header->status == '0'){		
		PrintErro();
		return;
	}


	Registro Register[n];

	//Registro *Register = malloc(sizeof(Registro));
	//for(int i = 0; i < n - 1; i++) Register = realloc(Register, sizeof(Registro));

	for(int i = 0; i < n; i++){
		
		LeEntradaRegistro(&Register[i]);
				
		InsereRegistro(file, &Register[i], header);
>>>>>>> 3232f41462f2656ad959c1414b3144c4cd146683
	
	}		

	fseek(file, 0, SEEK_SET);

	EscreveHeader(file, header);

	free(header);
	fclose(file);
	binarioNaTela(arq);

}

// funcionalidade 6 -> compacta um arquivo

void funcionalidade6(FILE *file, char *arq){
<<<<<<< HEAD

	CompactaArquivo(file, arq);

}


void funcionalidade7(FILE *file){
	char arq_indice[32];
	scanf("%s", arq_indice);
	FILE *file_index = fopen(arq_indice, "w+b");			//cria o arquivo de indice
	
}
=======
	
	CompactaArquivo(file, arq);
}

void funcionalidade7(){
}

void funcionalidade8(){
}

void funcionalidade9(){
}

void funcionalidade10(){
}



>>>>>>> 3232f41462f2656ad959c1414b3144c4cd146683
