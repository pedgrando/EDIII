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

// FUNCIONALIDADE 11

void funcionalidade11(FILE *file, Cabecalho *header, ListaAdj *grafo){
    Registro *Register = (Registro*) malloc(sizeof(Registro));

    fseek(file, 960, SEEK_SET); // pula o header
        
    while(fread(&Register->removido, sizeof(char), 1, file) != 0){

        if(Register->removido == '1'){

            fseek(file, 63, SEEK_CUR); // pula registro logicamente removido

        } else {

            ResetaRegistro(Register);

            // le um registro e imprime seu conteudo

            LeRegistroBin(Register, file); 

            if(Register->unidadeMedida == 'G') ConverteVelocidade(Register);
                
            if(!insereLista(grafo[Register->idConecta - 1].listaAdj, *Register)) PrintErro();

            //ImprimeRegistro(Register);

        }
    }

    for(int i = 0; i < header->proxRRN; i++){
        if(grafo[i].numVerticesAdj != -1) imprimeLista(grafo[i].listaAdj);
    }

}

// FUNCIONALIDADE 12

void funcionalidade12(FILE *file){
	
}

// FUNCIONALIDADE 13

void funcionalidade13(FILE *file){

}

// FUNCIONALIDADE 14

void funcionalidade14(FILE *file){

}




