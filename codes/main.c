#include <stdio.h>
#include <stdlib.h>

#define REG 238

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

void printa_registro(FILE *arq){    
    printf("Firstname: ");
    char buffer[81];
    fread(buffer, 51, 1, arq);
    printf("%s\n", buffer);
    printf("Lastname: ");
    fread(buffer, 51, 1, arq);
    printf("%s\n", buffer);    
    printf("Email: ");
    fread(buffer, 81, 1, arq);
    printf("%s\n", buffer);
    printf("Nationality: ");
    fread(buffer, 51, 1, arq);
    printf("%s\n", buffer);  
    printf("Age: ");
    fread(buffer, 4, 1, arq);
    printf("%s\n\n", buffer);        
}

int get_tam(FILE *arq){
    long counter = 0;
    char temp[1]; 
    while(fread(temp, 1, 1, arq)) counter++;
    return counter / REG;
}

void main(){
    int option;
    char *nome_arq;
    scanf("%d %s", &option, nome_arq);
    FILE *arq;
    switch (option)
    {
    case 1:
        /* code */
        break;

    case 2:
        arq = fopen(nome_arq, "rb");
        int tam = get_tam(arq);
        printf("\n\nExistem %d registros.\n\n", tam);
        for(int i = 0; i < tam; i++) {
            fseek(arq, i * REG, SEEK_SET);
            printa_registro(arq);
        }
        break;

    case 3:
        arq = fopen(nome_arq, "rb");
        int RRN;
        scanf("%d", &RRN);
        fseek(arq, RRN * REG, SEEK_SET);
        printa_registro(arq);
        break;
    
    default:
        printf("Entrada indisponível.");
        break;
    }
    fclose(arq);
}