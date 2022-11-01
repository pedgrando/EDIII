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

void TransfereDados(FILE *file_in, FILE *file_out, Cabecalho *header){
    while(fgetc(file_in) != '\n'); 					// pula a primeira linha do .csv

    Registro *Register = malloc(sizeof(Registro));

    while (LeRegistro(file_in, Register)){ 				// le um registro e ja escreve ele no arquivo binario
        EscreveRegistro(file_out, Register);

	header->proxRRN++; 						// incrementa o prox RRN disponivel
    }
	header->nroPagDisco = get_num_pag(header);  // atualiza o numero de paginas de disco
	header->status = '1'; 						// define o status do arquivo como valido
	
	fseek(file_out, 0, SEEK_SET);
	escreveHeader(file_out, header);

    free(Register);
}

    
// compacta o arquivo, removendo todos os registros removidos e reescrendo os registros validos sequencialmente

void CompactaArquivo(FILE *file_in, char *arq_entrada){    

    fseek(file_in, 0, SEEK_SET);
    Cabecalho *header = getHeader(file_in);
	if(header->status == '0') {    // testa se o arquivo é consistente            
		printf("Falha no processamento do arquivo.\n");
		return;
	}
	Registro *Register = malloc(sizeof(Registro));

	FILE *aux = fopen("aux.bin", "w+b");
	CriaHeader(aux, header);
    fseek(aux, 960, SEEK_SET);

	char removido;
	fseek(file_in, 960, SEEK_SET);
	while(fread(&removido, sizeof(char), 1, file_in) != 0){

		if(removido == '0'){

			resetaRegistro(Register);

			leRegistroBin(Register, file_in);
				
			EscreveRegistro(aux, Register);

		} else {

			header->nroRegRem--;
			header->proxRRN--;
			fseek(file_in, 63, SEEK_CUR); // pula registro logicamente removido

		}
	}

	header->status = '1';
	header->topo = -1;
	header->qttCompacta++;
	header->nroPagDisco = get_num_pag(header);
	fseek(aux, 0, SEEK_SET);
	escreveHeader(aux, header);

	fclose(aux);
   	 free(header);

    	fclose(file_in);

	remove(arq_entrada);
	rename("aux.bin", arq_entrada); 

	binarioNaTela(arq_entrada);
}

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

// recebe um registro pela entrada padrao e insere no arquivo binario

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


