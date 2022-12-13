#include <iostream>
#include <list>

#include "grafo.hpp"
#include "funcoes_io.hpp"
#include "data_structures.hpp"

using namespace std;

int main(int argv, char *argc[]){
    int option;
    char arq_entrada[32];

    scanf("%d", &option);		    

    FILE *file_in = NULL;

    Registro *Register = (Registro*) malloc(sizeof(Registro));

    Cabecalho *header = (Cabecalho*) malloc(sizeof(Cabecalho));
    *header = ResetaCabecalho();

    Grafo grafo;
 
    switch (option)
    {
    case 11:

	// FUNCIONALIDADE 11

        scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
            PrintErro();
            break;
        }

        header = getHeader(file_in);
        grafo.InicializaGrafo(header->proxRRN);

        fseek(file_in, 960, SEEK_SET); // pula o header

        while(fread(&Register->removido, sizeof(char), 1, file_in) != 0){

            if(Register->removido == '1'){

                fseek(file_in, 63, SEEK_CUR); // pula registro logicamente removido

            } else {

                ResetaRegistro(Register);

                // le um registro e imprime seu conteudo

                LeRegistroBin(Register, file_in); 

                if(Register->unidadeMedida == 'G') ConverteVelocidade(Register);
                    
                if(grafo.VerticeVago(Register->idPoPsConectado)) grafo.adicionarAresta(Register);

                //ImprimeRegistro(Register);

            }
        }

        grafo.ImprimeGrafo();      

	break;	
    case 12:

	// FUNCIONALIDADE 12

        scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
            PrintErro();
            break;
        }

        header = getHeader(file_in);
        grafo.InicializaGrafo(header->proxRRN);


	break;	
    case 13:

	// FUNCIONALIDADE 13

        scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
            PrintErro();
            break;
        }

        header = getHeader(file_in);
        grafo.InicializaGrafo(header->proxRRN);


	break;	
    case 14:

	// FUNCIONALIDADE 14

        scanf("%s", arq_entrada);
        if(!(file_in = fopen(arq_entrada, "rb+"))) {    // testa se o arquivo existe            
            PrintErro();
            break;
        }

        header = getHeader(file_in);
        grafo.InicializaGrafo(header->proxRRN);


	break;	
    default:
    break;
    }
    free(header);

}
