#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

#include "funcoes.h"

void TransfereDados(FILE *file_in, FILE *file_out, Cabecalho *header){
    while(fgetc(file_in) != '\n');
    Registro *Register = malloc(sizeof(Registro)); 
    while (LeRegistro(file_in, Register)){
        EscreveRegistroBin(file_out, Register);
		ImprimeRegistro(Register);
		header->proxRRN++;

    }
	header->nroPagDisco = ceil(GetNumPag(file_out) / PAG_DISCO);
	header->status = '1';
    free(Register);
}


void CompactaArquivo(FILE* origem, Cabecalho *header){
    FILE *aux = fopen("aux.bin", "wb");

	header->qttCompacta++;

    CriaHeader(aux, header);

	Registro *Register = malloc(sizeof(Register));
    fseek(origem, 960, SEEK_SET);

	int numReg = GetNumReg(origem);
    while(numReg) {                  

		LeRegistroBin(Register, origem);
        if(Register->removido == '0'){                                      
        	EscreveRegistroBin(aux, Register);
			header->nroRegRem--;
		}

    }

    //binarioNaTela("aux.bin");

    EscreveHeaderBin(aux, header);
    origem = aux;
    fclose(aux);

}


void buscaRegistro(FILE *arq_entrada, int campoBuscado, char *valorCampo, int funcionalidade){
	Cabecalho *header = LeHeaderBin(arq_entrada);
	Registro *Register = malloc(sizeof(Registro)*1);
	int rrn = 0;
	
	if(header->status == '0'){
		printf("Falha no processamento do arquivo.\n");
		return;
	}
	
	fseek(arq_entrada, 939, SEEK_SET); // pula o registro de cabecalho

	while(fread(&Register->removido, sizeof(char), 1, arq_entrada) != 0){

		if(Register->removido == '1'){

			fseek(arq_entrada, 63, SEEK_CUR); // pula registro logicamente removido

		} else {

			LeRegistroBin(Register, arq_entrada);

			switch(campoBuscado){
				case IDCONECTA:
					if(atoi(valorCampo) == Register->idConecta){
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							RemoveRegistro(arq_entrada, header, rrn);
						}
					
					}
					break;

				case SIGLAPAIS:
					if(atoi(valorCampo) == Register->idConecta){
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							RemoveRegistro(arq_entrada, header, rrn);
						}
					
					}
					break;

				case IDPOPSCONECTADO:
					if(atoi(valorCampo) == Register->idConecta){
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							RemoveRegistro(arq_entrada, header, rrn);
						}
					
					}
					break;

				case UNIDADEMEDIDA:
					if(atoi(valorCampo) == Register->idConecta){
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							RemoveRegistro(arq_entrada, header, rrn);
						}
					
					}
					break;

				case VELOCIDADE:
					if(atoi(valorCampo) == Register->idConecta){
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							RemoveRegistro(arq_entrada, header, rrn);
						}
					
					}
					break;

				case NOMEPOPS:
					if(atoi(valorCampo) == Register->idConecta){
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							RemoveRegistro(arq_entrada, header, rrn);
						}
					
					}
					break;
					
				case NOMEPAIS:
					if(atoi(valorCampo) == Register->idConecta){
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							RemoveRegistro(arq_entrada, header, rrn);
						}
					
					}
					break;
			}
			
		}
		rrn++;
	}
	free(Register);	
	free(header);
}

// FUNCOES PARA EXTRAIR OS DADOS BINARIOS

void imprime_arq(FILE *arq_entrada){
	Registro *Register = malloc(sizeof(Registro));
	Cabecalho *header = LeHeaderBin(arq_entrada);

	if(header->status == '0'){
		printf("Falha no processamento do arquivo.\n");
		free(Register);
		return;
	}

	int tem_registro = 0;

	fseek(arq_entrada, 960, SEEK_SET);

	while(fread(&Register->removido, sizeof(char), 1, arq_entrada) != 0){

		if(Register->removido == '1'){

			fseek(arq_entrada, 63, SEEK_CUR); // pula registro logicamente removido

		} else {

			tem_registro = 1;

			resetaRegistro(Register);

			LeRegistroBin(Register, arq_entrada);
				
			ImprimeRegistro(Register);
					
		}
	}

	if(!tem_registro){
		printf("Registro inexistente.\n\n");
	}
	imprime_pag_disco(header);
}


//============ LEITURA BINARIA =======================================

void readint(FILE *arq, int *integer){
	fread(integer, sizeof(int), 1, arq); 
}

void readstring(FILE *arq, int num_char, char *string){
	fread(string, sizeof(char), num_char, arq);
}

int readstring_variavel(FILE *arq, char *string){
	char aux;
	int i = 0;
	while(fread(&aux, sizeof(char), 1, arq)){ 
		if(aux == '|'){
			break;
		}
		string[i] = aux;
		i++;
	}
	string[i] = '\0';
	return i;
}