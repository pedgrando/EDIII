#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "miscelaneous.hpp"
#include "funcoes_io.hpp"
#include "data_structures.hpp"
#include "funcoes_principais.hpp"

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

	Registro *Register = (Registro*) malloc(sizeof(Registro)*1);

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
						}
					
					}
					break;
				case SIGLAPAIS:
					if(valorCampo[0] == Register->siglaPais[0] && valorCampo[1] == Register->siglaPais[1]){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						}
					
					}
					break;
				case IDPOPSCONECTADO:
					if(atoi(valorCampo) == Register->idPoPsConectado){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						}
					
					}
					break;
				case UNIDADEMEDIDA:
					if(valorCampo[0] == Register->unidadeMedida){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						}
					
					}
					break;
				case VELOCIDADE:
					if(atoi(valorCampo) == Register->velocidade){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						}
					
					}
					break;
				case NOMEPOPS:
					if(!strcmp(valorCampo, Register->nomePoPs)){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
						}
					
					}
					break;
				case NOMEPAIS:
					if(!strcmp(valorCampo, Register->nomePais)){
						encontrou_reg = 1;
						if(funcionalidade){
							ImprimeRegistro(Register);
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

