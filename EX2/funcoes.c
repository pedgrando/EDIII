#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcoes.h"

//teste parte 2

Cabecalho InicializaStructCabecalho(){
    Cabecalho aux;
    aux.status = 0;
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
    PreencheLixo(file);
    fwrite(&header->status, sizeof(char), 1, file);
    fwrite(&header->topo, sizeof(int), 1, file);
    fwrite(&header->proxRRN, sizeof(int), 1, file);
    fwrite(&header->nroRegRem, sizeof(int), 1, file);
    fwrite(&header->nroPagDisco, sizeof(int), 1, file);
    fwrite(&header->qttCompacta, sizeof(int), 1, file);
}

void PreencheLixo(FILE *file){
	char lixo[960];
    for (int i = 0; i < PAG_DISCO; i++) lixo[i] = LIXO;
    fwrite(lixo, sizeof(char), PAG_DISCO, file);  
    fseek(file, 0, SEEK_SET);
}

void resetaRegistro(Registro *Register){
    for (int i = 0; i < 7; i++) Register->campoVazio[i] = 1;
    Register->removido = '0';
    Register->encadeamento = -1;
    Register->nomePoPs[0] = DEL;
    Register->nomePais[0] = DEL;
    Register->nomePoPs[1] = '\0';
    Register->nomePais[1] = '\0';
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
        Register->campoVazio[j] = 0;;
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
        Register->campoVazio[j] = 0;;
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
        Register->campoVazio[j] = 0;;
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
        Register->campoVazio[j] = 0;;
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
        Register->campoVazio[j] = 0;;
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
        Register->campoVazio[j] = 0;;
    }

    
    return 1;
}   
 
void ImprimeRegistro(Registro *Register){
    if(!Register->campoVazio[0]) printf("Identificador do ponto: %d\n", Register->idConecta);
    if(!Register->campoVazio[1]) printf("Nome do Ponto: %s\n", Register->nomePoPs);
    if(!Register->campoVazio[2]) printf("Pais de localizacao: %s\n", Register->nomePais);
    if(!Register->campoVazio[3]) printf("Sigla do Pais: %s\n", Register->siglaPais);
    if(!Register->campoVazio[4]) printf("Identificador do ponto conectado: %d\n", Register->idPoPsConectado);
    if(!Register->campoVazio[5] && !Register->campoVazio[6]) printf("Velocidade de transmissao: %d %cbps\n", Register->velocidade, Register->unidadeMedida);
    printf("\n");
}

void TransfereDados(FILE *file_in, FILE *file_out){
    while(fgetc(file_in) != '\n');
    Registro *Register = malloc(sizeof(Registro)); 
    while (LeRegistro(file_in, Register)){
        EscreveRegistro(file_out, Register);
        //ImprimeRegistro(Register);
    }    
    free(Register);
}

void EscreveRegistro(FILE *file, Registro *Register){
    fwrite(&Register->removido, sizeof(char), 1, file);
    fwrite(&Register->encadeamento, sizeof(int), 1, file);
    fwrite(&Register->idConecta, sizeof(char), 1, file);
    fwrite(Register->siglaPais, sizeof(char), 2, file);
    fwrite(&Register->idPoPsConectado, sizeof(int), 1, file);
    fwrite(&Register->unidadeMedida, sizeof(char), 1, file);
    fwrite(&Register->velocidade, sizeof(int), 1, file);
    fwrite(Register->nomePoPs, sizeof(Register->nomePoPs), 1, file);
    fwrite(Register->nomePais, sizeof(Register->nomePais), 1, file);
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

void buscaRegistro(FILE *arq_entrada, int campoBuscado, char *valorCampo){
	Cabecalho *header = getHeader(arq_entrada);
	Registro *Register = malloc(sizeof(Registro)*1);
	char aux[2];
	int i = 0; // contador de registros;
	
	if(header->status == '0'){
		printf("Falha no processamento do arquivo.\n");
		return;
	}
	
	fseek(arq_entrada, 939, SEEK_SET); // pula o registro de cabecalho

	switch(campoBuscado){
		case 0:
			// imprime o arquivo inteiro
			
			while(fread(aux, sizeof(char), 1, arq_entrada) != 0){

				if(aux[0] == '1'){
					fseek(arq_entrada, 63, SEEK_CUR); // pula registro logicamente removido
				}
					
				LeRegistroBin(Register, arq_entrada);
				
				ImprimeRegistro(Register);
				
				if(ftell(arq_entrada) != (960 + 64*(i+1))){
					fseek(arq_entrada, 960+64*(i+1) - ftell(arq_entrada), SEEK_CUR);
				}


				i++;
			}

			imprime_pag_disco(header);

			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
	}

	free(Register);	
}

void imprime_pag_disco(Cabecalho *header){
	printf("Numero de paginas de disco: %d", header->nroPagDisco);
}


void leRegistroBin(Registro *Register, FILE *arq_entrada){

	// le encadeamento
	readint(arq_entrada, &(Register->encadeamento));

	readint(arq_entrada, &(Register->idConecta));
	Register->campoVazio[0] = campovazio_int(Register->idConecta);
	
	readstring(arq_entrada, 2, Register->siglaPais);	
	Register->campoVazio[1] = campovazio_string(Register->siglaPais);

	readint(arq_entrada, &(Register->idPoPsConectado));
	Register->campoVazio[2] = campovazio_int(Register->idPoPsConectado);

	readstring(arq_entrada, 1, &(Register->unidadeMedida));
	Register->campoVazio[3] = campovazio_string(&(Register->unidadeMedida));

	readint(arq_entrada, &(Register->velocidade));
	Register->campoVazio[4] = campovazio_int(Register->velocidade);

	readstring_variavel(arq_entrada, Register->nomePoPs);
	Register->campoVazio[5] = campovazio_string_var(Register->nomePoPs);

	readstring_variavel(arq_entrada, Register->nomePais);
	Register->campoVazio[6] = campovazio_string_var(Register->nomePais);

	return;
}


// FUNCOES PARA LER DO ARQUIVO BINARIO ------------------------------------------------

void readint(FILE *arq_entrada, int *integer){
	fread(integer, sizeof(int), 1, arq_entrada);
}

void readstring(FILE *arq_entrada, int reading_size, char *string){
	fread(string, sizeof(char), reading_size, arq_entrada);
	if(reading_size != 1){
		string[reading_size] = '\0';
	}
}

void readstring_variavel(FILE *arq_entrada, char *string){
	char aux = '\0';
	int i = 0;
	while(aux != '|'){
		fread(&aux, sizeof(char), 1, arq_entrada);
		string[i] = aux;	
		i++;
	}
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
	if(string[0] == '|'){
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
	}
	return result;
}
















