#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

#define IDCONECTA 906
#define SIGLAPAIS 925
#define IDPOPSCONECTADO 1503
#define UNIDADEMEDIDA 1310
#define VELOCIDADE 1040
#define NOMEPOPS 817
#define NOMEPAIS 828

#define BYTEOFFSET_IDCONECTA 5
#define BYTEOFFSET_SIGLAPAIS 9
#define BYTEOFFSET_IDPOPSCONECTADO 11
#define BYTEOFFSET_UNIDADEMEDIDA 15
#define BYTEOFFSET_VELOCIDADE 16
#define BYTEOFFSET_VARIAVEIS 20


//teste parte 2

Cabecalho InicializaStructCabecalho(){
    Cabecalho aux;
    aux.status = '0';
    aux.topo = -1;
    aux.proxRRN = 0;
    aux.nroRegRem = 0;
    aux.nroPagDisco = 0;
    aux.qttCompacta = 0;
    return aux;
}

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

//FUNCOES DE MANIPULAÇÃO DE ARQUIVOS --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void CriaHeader(FILE *file, Cabecalho *header){
	fseek(file, 0, SEEK_SET);
    escreveHeader(file, header);
	PreencheLixo(file);
	fseek(file, 0, SEEK_END);
}

void escreveHeader(FILE *file, Cabecalho *header){
    fwrite(&header->status, sizeof(char), 1, file);
    fwrite(&header->topo, sizeof(int), 1, file);
    fwrite(&header->proxRRN, sizeof(int), 1, file);
    fwrite(&header->nroRegRem, sizeof(int), 1, file);
    fwrite(&header->nroPagDisco, sizeof(int), 1, file);
    fwrite(&header->qttCompacta, sizeof(int), 1, file);
}

void PreencheLixo(FILE *file){
	char lixo[PAG_DISCO - 21];
    for (int i = 0; i < PAG_DISCO - 21; i++) lixo[i] = LIXO;
    fwrite(lixo, sizeof(lixo), 1, file);  
}

void resetaRegistro(Registro *Register){
    for (int i = 0; i < 7; i++) Register->campoVazio[i] = 1;
    Register->removido = '0';
    Register->encadeamento = -1;
    Register->nomePoPs[0] = '\0';
    Register->nomePais[0] = '\0';
    strcpy(Register->siglaPais, "$$\0");
    Register->idPoPsConectado = -1;
    Register->unidadeMedida = '$';
    Register->velocidade = -1;
}

int LeRegistro(FILE *file_in, Registro *Register){
    char aux;
    char aux2[5];
    resetaRegistro(Register);
    
    int j = 0;

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
 
void ImprimeRegistro(Registro *Register){
    if(!Register->campoVazio[0]) printf("Identificador do ponto: %d\n", Register->idConecta);
    if(!Register->campoVazio[1]) printf("Nome do Ponto: %s\n", Register->nomePoPs);
    if(!Register->campoVazio[2]) printf("Pais de localizacao: %s\n", Register->nomePais);
    if(!Register->campoVazio[3]) printf("Sigla do Pais: %c%c\n", Register->siglaPais[0], Register->siglaPais[1]);
    if(!Register->campoVazio[4]) printf("Identificador do ponto conectado: %d\n", Register->idPoPsConectado);
    if(!Register->campoVazio[5] && !Register->campoVazio[6]) printf("Velocidade de transmissao: %d %cbps\n", Register->velocidade, Register->unidadeMedida);
    printf("\n");
}

void TransfereDados(FILE *file_in, FILE *file_out, Cabecalho *header){
    while(fgetc(file_in) != '\n');
    Registro *Register = malloc(sizeof(Registro)); 
    while (LeRegistro(file_in, Register)){
        EscreveRegistro(file_out, Register);
        //ImprimeRegistro(Register);
    }
	header->nroPagDisco = (int) get_num_pag(file_out) / PAG_DISCO;
	header->status = '1';
    free(Register);
}

int get_num_pag(FILE *arq){
    long counter = 0;
    char temp[1]; 
    while(fread(temp, 1, 1, arq)) counter++;  // conta um por um dos caracteres ate o final
    return counter / PAG_DISCO;
}


void EscreveRegistro(FILE *file, Registro *Register){
	int bytes_ocupados = 22 + strlen(Register->nomePoPs) + strlen(Register->nomePais);

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

	for(int i = 0; i < (64 - bytes_ocupados); i++){
		fwrite("$", sizeof(char), 1, file);
	}
    
}

void CompactaArquivo(FILE* origem){
    FILE *aux = fopen("aux.bin", "wb");
    char linha[64];                                          
        
    Cabecalho *header = malloc(sizeof(Cabecalho));
    *header = InicializaStructCabecalho();
    CriaHeader(aux, header);

    fseek(origem, 960, SEEK_SET);
    while(!feof(origem)) {                  //MUDAR SEEK END

        fread (linha, sizeof(char), 64, origem);
        if(linha[0] == '0'){                                      //NUM SEI SE FUNCIONA 
            fwrite(linha, sizeof(char), 64, aux);
        }

    }

    //binarioNaTela("aux.bin");

    origem = aux;
    free(header);
    fclose(aux);
    
}

// FUNCOES PARA EXTRAIR OS DADOS BINARIOS

void imprime_arq(FILE *arq_entrada){
	Registro *Register = malloc(sizeof(Registro));
	Cabecalho *header = getHeader(arq_entrada);

	int tem_registro = 0;

	fseek(arq_entrada, 960, SEEK_SET);

	while(fread(&Register->removido, sizeof(char), 1, arq_entrada) != 0){

		if(Register->removido == '1'){

			fseek(arq_entrada, 63, SEEK_CUR); // pula registro logicamente removido

		} else {

			tem_registro = 1;

			resetaRegistro(Register);

			leRegistroBin(Register, arq_entrada);
				
			ImprimeRegistro(Register);
					
		}
	}

	if(!tem_registro){
		printf("Registro inexistente.\n");
	} else{
		imprime_pag_disco(header);
	}
}


void buscaRegistro(FILE *arq_entrada, int campoBuscado, char *valorCampo, int funcionalidade){
	Cabecalho *header = getHeader(arq_entrada);
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

			leRegistroBin(Register, arq_entrada);

			switch(campoBuscado){
				case IDCONECTA:
					if(atoi(valorCampo) == Register->idConecta){
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							remove_registro(arq_entrada, header, rrn);
						}
					
					}
					break;
				case SIGLAPAIS:
					if(atoi(valorCampo) == Register->idConecta){
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							remove_registro(arq_entrada, header, rrn);
						}
					
					}
					break;
				case IDPOPSCONECTADO:
					if(atoi(valorCampo) == Register->idConecta){
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							remove_registro(arq_entrada, header, rrn);
						}
					
					}
					break;
				case UNIDADEMEDIDA:
					if(atoi(valorCampo) == Register->idConecta){
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							remove_registro(arq_entrada, header, rrn);
						}
					
					}
					break;
				case VELOCIDADE:
					if(atoi(valorCampo) == Register->idConecta){
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							remove_registro(arq_entrada, header, rrn);
						}
					
					}
					break;
				case NOMEPOPS:
					if(atoi(valorCampo) == Register->idConecta){
						if(funcionalidade){
							ImprimeRegistro(Register);
						} else {
							remove_registro(arq_entrada, header, rrn);
						}
					
					}
					break;
				case NOMEPAIS:
					if(atoi(valorCampo) == Register->idConecta){
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
	free(Register);	
	free(header);
}

void imprime_pag_disco(Cabecalho *header){
	printf("Numero de paginas de disco: %d", header->nroPagDisco);
}


void leRegistroBin(Registro *Register, FILE *arq_entrada){

	int byteoffset = 20;

	readint(arq_entrada, &(Register->encadeamento));

	readint(arq_entrada, &(Register->idConecta));
	Register->campoVazio[0] = campovazio_int(Register->idConecta);

	readstring(arq_entrada, 2, Register->siglaPais);	
	Register->campoVazio[3] = campovazio_string(Register->siglaPais);

	readint(arq_entrada, &(Register->idPoPsConectado));
	Register->campoVazio[4] = campovazio_int(Register->idPoPsConectado);

	readstring(arq_entrada, 1, &(Register->unidadeMedida));
	Register->campoVazio[6] = campovazio_string(&(Register->unidadeMedida));

	readint(arq_entrada, &(Register->velocidade));
	Register->campoVazio[5] = campovazio_int(Register->velocidade);

	byteoffset += readstring_variavel(arq_entrada, Register->nomePoPs);
	Register->campoVazio[1] = campovazio_string_var(Register->nomePoPs);

	byteoffset += readstring_variavel(arq_entrada, Register->nomePais);
	Register->campoVazio[2] = campovazio_string_var(Register->nomePais);

	fseek(arq_entrada, 64 - byteoffset, SEEK_CUR);

	return;
}


// FUNCOES PARA LER DO ARQUIVO BINARIO ------------------------------------------------

void readint(FILE *arq, int *integer){
	fread(integer, sizeof(int), 1, arq); 
}

void readstring(FILE *arq, int num_char, char *string){
	fread(string, sizeof(char), num_char, arq); 
}


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

int hashfunction(char *str){
	int i = 0;
	int result = 0;
	while(str[i] != '\0'){
		result += str[i];	
		i++;
	}
	return result;
}


int compara_str(char *str1, char *str2){
	int i = 0;
	if(str1[0] == str2[0] && strlen(str2) == 1) return 0; // pega o caso de um só caracter
	while(str1[i] != '\0' && str2[i] != '\0'){
		if(str1[i] != str2[i]){
			return 1;
		}
		i++;
	}
	return 0;
}


void remove_registro(FILE *arq, Cabecalho *header, int rrn){
	int topo = header->topo;

	header->topo = rrn;
	header->nroRegRem++;

	fseek(arq, 0, SEEK_SET);
	escreveHeader(arq, header);

	fseek(arq, 960+64*rrn, SEEK_SET);

	char lixo[59];

	for(int i = 0; i < 59; i++) lixo[i] = LIXO;
	
	fwrite("1", sizeof(char), 1, arq);
	fwrite(&topo, sizeof(int), 1, arq);
       	fwrite(lixo, sizeof(char), 59, arq);
}


void tira_aspas(char *str){
	int i = 1;
	while(str[i] != '"'){
		str[i-1] = str[i];
		i++;
	}
	str[i] = '\0';
}







