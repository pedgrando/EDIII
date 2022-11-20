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


void funcionalidade1(FILE *file_in, FILE *file_out, Cabecalho *header, char *arq){
	CriaHeader(file_out, header);
	TransfereDados(file_in, file_out, header);

	fclose(file_in);
	fclose(file_out);
	binarioNaTela(arq);
}


void funcionalidade3(FILE *file, char *arq){
	int n;

	scanf("%d", &n);

	char (*valorCampo)[32] = malloc(sizeof(*valorCampo)*n);
	int *hash_campo = malloc(sizeof(int)*n);

	Cabecalho *header = NULL;
	header = getHeader(file);


	for(int i = 0; i < n; i++){	
		char aux[32];

		scanf("%s", aux);

		scan_quote_string(valorCampo[i]);

		hash_campo[i] = hashfunction(aux);

		// dentro da funcao, recebe os parametros da busca 

	}
	
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
	int n;
	int falha_de_processamento;

	scanf("%d", &n);

	char valorCampo[32];
	int hash_campo;
	char aux[32];

	Cabecalho *header = NULL;
	header = getHeader(file);


	for(int i = 0; i < n; i++){	

		scanf("%s", aux);

		scan_quote_string(valorCampo);

		hash_campo = hashfunction(aux);

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

void funcionalidade7(){
}

void funcionalidade8(){
}

void funcionalidade9(){
}

void funcionalidade10(){
}



