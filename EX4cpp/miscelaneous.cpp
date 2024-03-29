#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "miscelaneous.hpp"
#include "funcoes_io.hpp"
#include "data_structures.hpp"


// cria um header em memoria secundaria no arquvio
//
// escreve o header da memoria primaria no arquivo, colocando o lixo e mantendo o ponteiro do arquivo no inicio
//

void CriaHeader(FILE *file, Cabecalho *header){
	fseek(file, 0, SEEK_SET);
    EscreveHeader(file, header);
	PreencheLixo(file);
	fseek(file, 0, SEEK_END);
}

// volta uma variavel Registro em memoria primaria a situacao em que todos os campos sao vazios

void ResetaRegistro(Registro *Register){
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

// altera velocidade de MBps para GBps

void ConverteVelocidade(Registro *Register){
	Register->velocidade = Register->velocidade * 1024; 
	Register->unidadeMedida = 'M';
}

// volta uma variavel Cabecalho em que todos os campos sao vazios

Cabecalho ResetaCabecalho(){
    Cabecalho aux;
    aux.status = '0';
    aux.topo = -1;
    aux.proxRRN = 0;
    aux.nroRegRem = 0;
    aux.nroPagDisco = 0;
    aux.qttCompacta = 0;
    return aux;
}

// descobre o numero de paginas de disco do arquivo

int getNumPag(Cabecalho *header){
	if(header->proxRRN % 15 == 0){
		return ((header->proxRRN / 15) + 1);
	} else {
		return ((header->proxRRN / 15) + 2);
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
	if(string[0] == '\0'){
		return 1;
	} else {
		return 0;
	}	
}


// HASH FUNCTION PARA DESCOBRIR O CAMPO
// uma funcao hash simples: ela soma os valores dos caracteres de uma string ate o '\0' e retorna o resultado

int hashfunction(char *str){
	int i = 0;
	int result = 0;
	while(str[i] != '\0'){
		result += str[i];	
		i++;
	}
	return result;
}


