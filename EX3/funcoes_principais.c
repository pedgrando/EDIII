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

// busca um registro em especifico para executar uma funcionalidade
/*
 Essa funcao era comum as funcionalidades 3 e 4; nela sao passados um arquivo com suas informacoes de header, um campo de busca e um valor buscado, qual das funcionalidades
 sera executada (CONSULTA = 1, referente a funcionalidade 3, e REMOCAO = 0, referente a funcionalidade 4), alem de um inteiro indentificando o numero da operacao, e.g., 3
 referente a terceira busca.
 Agora, ela eh utilizada como na funcionalidade 3 para buscas que nao sejam a partir do idConectado

 ela se utiliza de um esquema de hash para identificar qual o campo buscado, os valores tabelados podem ser encontrados nos arquivos de header, e mais informacoes estao na
 funcao de hash
 */

int BuscaRegistro(FILE *file, Cabecalho *header, int campoBuscado, char *valorCampo, int funcionalidade, int n){

	fseek(file, 0 , SEEK_SET);

	Registro *Register = malloc(sizeof(Registro)*1);

	int rrn = 0; 			// contagem de rrn
	int encontrou_reg = 0; 		// flag para indicar se ao menos um registro foi encontrado
	
	if(header->status == '0'){
		PrintErro();
		return 1;
	}

	if( n != 0) printf("Busca %d\n", n);  // especificacao do trabalho -> a cada pesquisa, imprime o id dela
	
	fseek(file, 960, SEEK_SET); // pula o registro de cabecalho

	while(fread(&Register->removido, sizeof(char), 1, file) != 0){

		if(Register->removido == '1'){

			fseek(file, 63, SEEK_CUR); // pula registro logicamente removido

		} else {

			LeRegistroBin(Register, file);
			
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
							RemoveRegistro(file, header, rrn);
						}
					
					}
					break;
				case SIGLAPAIS:
					if(valorCampo[0] == Register->siglaPais[0] && valorCampo[1] == Register->siglaPais[1]){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							RemoveRegistro(file, header, rrn);
						}
					
					}
					break;
				case IDPOPSCONECTADO:
					if(atoi(valorCampo) == Register->idPoPsConectado){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							RemoveRegistro(file, header, rrn);
						}
					
					}
					break;
				case UNIDADEMEDIDA:
					if(valorCampo[0] == Register->unidadeMedida){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							RemoveRegistro(file, header, rrn);
						}
					
					}
					break;
				case VELOCIDADE:
					if(atoi(valorCampo) == Register->velocidade){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							RemoveRegistro(file, header, rrn);
						}
					
					}
					break;
				case NOMEPOPS:
					if(!strcmp(valorCampo, Register->nomePoPs)){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							RemoveRegistro(file, header, rrn);
						}
					
					}
					break;
				case NOMEPAIS:
					if(!strcmp(valorCampo, Register->nomePais)){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							RemoveRegistro(file, header, rrn);
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
		ImprimePagDisco(header);
	}

	free(Register);	

	return 0;
}


// recebe um registro pela entrada padrao e insere no arquivo binario

int InsereRegistro(FILE *file, Registro *Register, Cabecalho *header){
	int rrn_reg;

	if(header->topo == -1){
		fseek(file, 960+64*(header->proxRRN), SEEK_SET);
		rrn_reg = header->proxRRN;
		(header->proxRRN)++;
	} else {
		int novo_topo;
		fseek(file, 961+64*(header->topo), SEEK_SET);
		rrn_reg = header->topo;
		
		fread(&novo_topo, sizeof(int), 1, file);
		header->topo = novo_topo;	

		fseek(file, -5, SEEK_CUR);
		(header->nroRegRem)--;
	}

	EscreveRegistro(file, Register);

	return rrn_reg;
}

// cria um arquivo de indices (arvore b)

void criaArvore(FILE *arq_dados, FILE *arv){
	Registro *Register = malloc(sizeof(Registro));
	Cabecalho *header = getHeader(arq_dados); 	// le o header do arquivo de dados
	if(header->status == '0'){ 			// verifica a integridade do arquivo de dados
		PrintErro();
		exit(-1);
	}
	
	Cabecalho_Arvore *header_arv = malloc(sizeof(Cabecalho_Arvore));
	InicializaHeaderArvore(header_arv);  	// cria e inicializa o header da arvore

	int rrn_reg = 0;
	fseek(arq_dados, 960, SEEK_SET);

	while(fread(&Register->removido, sizeof(char), 1, arq_dados) != 0){

		if(Register->removido == '1'){

			fseek(arq_dados, 63, SEEK_CUR); // pula registro logicamente removido

		} else {
			ResetaRegistro(Register);     // reseta o registro

			// le um registro e imprime seu conteudo

			LeRegistroBin(Register, arq_dados);  // le um registro do arquivo binario
				
			int chave_promovida;
			int RRN_indice_promovido;
			int RRN_filho_promovido;

			if(InsereArvore(header_arv, arv, Register->idConecta, rrn_reg, header_arv->noRaiz, &chave_promovida, &RRN_indice_promovido, &RRN_filho_promovido) == 1){   // 
				// se o retorno da insercao na raiz retornar 1, significa que a raiz sofreu um split e uma chave foi promovida dela
				// nesse caso, cria-se um novo no e insere-se a chave promovida nela
				//
				// no algoritmo, a chave promovida eh o valor medio de dois nos da arvore, nesse caso, do root (com valores menores que o valor promovido) e do novo no criado no split (com valores maiores
				// que o promovido); portanto, os filhos desse novo no serao o root (filho da esquerda) e o no produzido no split (filho da direita) 

				Registro_Arvore *nova_pag = malloc(sizeof(Registro_Arvore));
				InicializaNo(nova_pag);
				header_arv->alturaArvore++;
				nova_pag->alturaNo = header_arv->alturaArvore;
				nova_pag->RRNdoNo = header_arv->RRNproxNo;
				header_arv->RRNproxNo++;

				nova_pag->C[0] = chave_promovida;
				nova_pag->PR[0] = RRN_indice_promovido;
				nova_pag->P[0] = header_arv->noRaiz;
				nova_pag->P[1] = RRN_filho_promovido;
				nova_pag->nroChavesNo++;

				nova_pag->folha = '0';

				header_arv->noRaiz = nova_pag->RRNdoNo;
				
				EscreveNo(arv, nova_pag, nova_pag->RRNdoNo);
				free(nova_pag);
			}
		}

		rrn_reg++;
	}
	EscreveHeaderArvore(arv, header_arv);

	free(Register);
	free(header);
	free(header_arv);
}
