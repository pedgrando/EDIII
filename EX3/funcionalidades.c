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

// FUNCIONALIDADE 7 - cria o arquivo de indice (arvore b)

void funcionalidade7(FILE *file){
	FILE *index_in;
	char indice_entrada[32];
	scanf("%s", indice_entrada);
	if(!(index_in = fopen(indice_entrada, "wb+"))) {    // testa se o arquivo foi criado            
		PrintErro();
		return;
	}
	
	//CRIAR ARVORE
	criaArvore(file, index_in);

	fclose(index_in);
	fclose(file);
	binarioNaTela(indice_entrada);
}

// FUNCIONALIDADE 8 - realiza uma busca pelo arquivo de indice com base no IdConecta do registro

void funcionalidade8(FILE *file){
	FILE *index_in;
	char indice_entrada[32];
	scanf("%s", indice_entrada);
	if(!(index_in = fopen(indice_entrada, "rb"))) {    // testa se o arquivo foi aberto corretamente            
		PrintErro();
		return;
	}

	int n;
	scanf("%d", &n);       // le o numero de buscas a serem realizadas

	char (*valorCampo)[32] = malloc(sizeof(*valorCampo)*n);
	int *hash_campo = malloc(sizeof(int)*n);

	Cabecalho *header = NULL;
	header = getHeader(file); 	// le o header do arquivo de dados
	if(header->status == '0'){	// testa se o arquivo de dados é consistente    	
		PrintErro();
		return;
	}

	Cabecalho_Arvore *header_arv = malloc(sizeof(Cabecalho_Arvore)); 
	LeHeaderArvore(index_in, header_arv); 		// le o header do arquivo de indice
	if(header_arv->status == '0'){	// testa se o arquivo de indice é consistente    	
		PrintErro();
		return;
	}

	Registro *Register = malloc(sizeof(Registro));

	// le o nome do campo consultado e o valor da consulta

	for(int i = 0; i < n; i++){	
		char aux[32];

		scanf("%s", aux);

		scan_quote_string(valorCampo[i]);

		hash_campo[i] = hashfunction(aux);			//transforma o nome do campo em valor inteiro

	}

	//faz n buscas para as condicoes especificadas pela entrada fazendo a consulta (PrintaRegistro)
	
	
	int falha_de_processamento;
	int RRN_chave, pos_chave, pos_dados, num_pag_disco; 

	for(int i = 0; i < n; i++){
		num_pag_disco = 2;       // paginas dos headers

		if(hash_campo[i] == IDCONECTA){				//se o campo a ser buscado é a chave, faz a busca via arvore
			falha_de_processamento = !BuscaArvore(index_in, header_arv->noRaiz, atoi(valorCampo[i]), &RRN_chave, &pos_chave, &pos_dados, &num_pag_disco);  // busca o rrn pos_dado da chave consultada no arquivo de indice
			if(falha_de_processamento) break;

			fseek(file, 960 + 64*pos_dados, SEEK_SET);
			// acessa o registro no arquivo de dados com base no rrn encontrado na busca
			if(fread(&Register->removido, sizeof(char), 1, file) != 0 && Register->removido == '0'){
				LeRegistroBin(Register, file);
				num_pag_disco++; 	// pagina de disco do registro de dados
			}

			printf("Busca %d\n", i+1);
			ImprimeRegistro(Register);

			printf("Numero de paginas de disco: %d\n\n", num_pag_disco);
			
		} else {									//se o campo a ser buscado nao é a chave, faz a busca comum
			falha_de_processamento = BuscaRegistro(file, header, hash_campo[i], valorCampo[i], CONSULTA, i+1);  // faz a busca convencional
			if(falha_de_processamento) break;
		}

	}
		
	free(Register);
	free(header);
	free(header_arv);
	free(valorCampo);
	free(hash_campo);

	fclose(index_in);
}

// FUNCIONALIDADE 9 - insere um registro no arquivo de dados e atualiza o arquivo de registros

void funcionalidade9(FILE *file, char *arq){
	FILE *index_in;
	char indice_entrada[32];
	scanf("%s", indice_entrada); 			    
	if(!(index_in = fopen(indice_entrada, "rb+"))) {    // testa se o arquivo foi aberto corretamente            
		PrintErro();
		return;
	}

	Cabecalho *header = getHeader(file); 		// le o header do arquivo de dados
	if(header->status == '0'){	// testa se o arquivo é consistente    	
		PrintErro();
		fclose(file);
		fclose(index_in);
		free(header);
		return;
	}


	Cabecalho_Arvore *header_arv = malloc(sizeof(Cabecalho_Arvore));
	LeHeaderArvore(index_in, header_arv); 	// le o header do arquivo de indices
	if(header_arv->status == '0'){	// testa se o arquivo é consistente    	
		PrintErro();
		fclose(file);
		fclose(index_in);
		free(header);
		free(header_arv);
		return;
	}

	int n;
	scanf("%d", &n);  	// le o numero de insercoes a serem realizadas

	//ATUALIZAR ARVORE E INSERIR NO INDICE
	
	int rrn_reg;
	Registro Register;
	
	for(int i = 0; i < n; i++){
		
		LeEntradaRegistro(&Register);					//leitura do teclado
				
		rrn_reg = InsereRegistro(file, &Register, header);			//escreve registro no arquivo binario
		
		int chave_promovida, RRN_indice_promovido, RRN_filho_promovido;


		if(InsereArvore(header_arv, index_in, Register.idConecta, rrn_reg, header_arv->noRaiz, &chave_promovida, &RRN_indice_promovido, &RRN_filho_promovido) == 1){    // insere o registro no arquivo de indices

				// se o retorno da insercao na raiz retornar 1, significa que a raiz sofreu um split e uma chave foi promovida dela
				// nesse caso, cria-se um novo no e insere-se a chave promovida nela
				//
				// no algoritmo, a chave promovida eh o valor medio de dois nos da arvore, nesse caso, do root (com valores menores que o valor promovido) e do novo no criado no split (com valores maiores
				// que o promovido); portanto, os filhos desse novo no serao o root (filho da esquerda) e o no produzido no split (filho da direita) 

				Registro_Arvore *nova_pag = malloc(sizeof(Registro_Arvore));
				InicializaNo(nova_pag);

				// atualiza as informacoes do header e insere os valores no novo no raiz

				header_arv->alturaArvore++; 
				nova_pag->alturaNo = header_arv->alturaArvore;
				nova_pag->RRNdoNo = header_arv->RRNproxNo;
				header_arv->RRNproxNo++;

				nova_pag->C[0] = chave_promovida; 		// insere a chave promovida
				nova_pag->PR[0] = RRN_indice_promovido; 	// insere o rrn do arquivo de dados relativa a chave
				nova_pag->P[0] = header_arv->noRaiz; 		// insere o ponteiro da antiga raiz como filho esquerdo 
				nova_pag->P[1] = RRN_filho_promovido; 		// insere o ponteiro do no criado no split como filho direito
				nova_pag->nroChavesNo++;

				nova_pag->folha = '0';

				header_arv->noRaiz = nova_pag->RRNdoNo;
				
				EscreveNo(index_in, nova_pag, nova_pag->RRNdoNo);
		}
	
	}		

	fseek(file, 0, SEEK_SET);

	EscreveHeader(file, header);

	EscreveHeaderArvore(index_in, header_arv);

	free(header);
	free(header_arv);

	fclose(file);
	fclose(index_in);

	binarioNaTela(arq);
	binarioNaTela(indice_entrada);
}

// FUNCIONALIDADE 10 - faz a juncao de dois arquivos

void funcionalidade10(FILE *file){
	FILE *file_in2;
	char arq_entrada2[32];
	scanf("%s", arq_entrada2);
	if(!(file_in2 = fopen(arq_entrada2, "rb+"))) {    // testa se o arquivo foi aberto corretamente            
		PrintErro();
		return;
	}
	
	Cabecalho *header1 = NULL;
	header1 = getHeader(file); 	// le o header do arquivo de dados 1
	if(header1->status == '0'){     // verifica a integridade do arquivo
		PrintErro();
		free(header1);
		return;
	}

	Cabecalho *header2 = NULL;
	header2 = getHeader(file_in2);  // le o header do arquivo de dados 2
	if(header2->status == '0'){     // verifica a integridade do arquivo
		PrintErro();
		free(header1);
		free(header2);
		return;
	}

	// le os campos a serem buscados e comparados na juncao

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
		return;
	}
	
	Cabecalho_Arvore *header_arv = malloc(sizeof(Cabecalho_Arvore));
	LeHeaderArvore(index_in, header_arv); 		    // le o header do arquivo de indices
	if(header_arv->status == '0'){ 			    // verifica a integridade do arquivo
		PrintErro();
		free(header1);
		free(header2);
		free(header_arv);
		return;
	}
	
	fseek(file, 960, SEEK_SET);
	Registro Register1;
	Registro Register2;
	int falha_de_processamento, encontrou_reg = 0;
	
	// realiza o cruzamento dos dados 
	
	while(fread(&Register1.removido, sizeof(char), 1, file) != 0){
	
		if(Register1.removido == '1'){
			fseek(file, 63, SEEK_CUR);
		} else { 
			
			// le um registro do arquivo 1
			LeRegistroBin(&Register1, file);
			if(!Register1.campoVazio[4]){ 
				// se ele tiver o campo idPoPsConectado
				int RRN_chave, pos_chave, pos_dados, num_pag_disco = 2;
				falha_de_processamento = !BuscaArvore(index_in, header_arv->noRaiz, Register1.idPoPsConectado, &RRN_chave, &pos_chave, &pos_dados, &num_pag_disco); // busca o registro do arquivo 2 que tem
																						    //  iConecta == arquivo1.idPoPsConectado
				if(!falha_de_processamento){
					// se a busca deu certo
					fseek(file_in2, 960 + 64*pos_dados, SEEK_SET);
					if(fread(&Register2.removido, sizeof(char), 1, file_in2) != 0 && Register2.removido == '0'){
						LeRegistroBin(&Register2, file_in2);
						ImprimeRegistroCombinado(&Register1, &Register2); // imprime conforme as especificacoes
						encontrou_reg = 1;
					}
				}
			}
			
		}
	}

	if(!encontrou_reg) printf("Registro inexistente.\n");
	
	free(header_arv);
	free(header1);
	free(header2);
	fclose(index_in);
}



