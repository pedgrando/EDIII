#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "pilha.h"
#include "data_structures.h"
#include "miscelaneous.h"
#include "funcoes_principais.h"

// Algoritmo de Dijkstra -> encontra o menor caminho possivel em um grafo, partindo de um vertice ate outro
//
// O algoritmo de Dijkstra basicamente mede as distancias relativas de todos os vertices do grafo em relacao ao vertice de origem
// Partindo do vertice de origem, o algoritmo caminha pelos vertices vizinhos atualizando a distancia entre eles para a menor possivel e o antecessor desse vertice para aquele que gera o vertice que gera esse menor caminho
// No processo, existe a verificacao constante se foi encontrado um novo caminho menor ate certo vertice
//
// Ao fim do algoritmo, eh possivel saber a distancia relativa entre o vertice de origem e o fim, e o caminho que gera essa menor distancia
//

void Dijkstra(Grafo *grafo, int origem, int *distancia, int *predecessor, int num_vertices){
	int i, *pos_heap = malloc(num_vertices*sizeof(int)), dist, id;
	
	// pos_heap eh um vetor que mantem registrado onde cada vertice esta na heap (v[x] eh a posicao na heap do vertice de idConecta x+1)

	dado aux;	

	// inicializa todas as distancias relativas como infinitas e os predecessores do vertices como invalidos
	for(i = 0; i < num_vertices; i++){
		distancia[i] = INT_MAX;
		predecessor[i] = -1;
	}

	// define a distancia relativa entre a origem pra ela mesma como zero
	distancia[origem - 1] = 0;

	// cria-se uma heap que sera utilizada como lista de prioridades
	// inicializa-se a heap colocando todos os vertices 
	Heap *h = criaHeap(num_vertices);
	for(i = 0; i < num_vertices; i++){
		h->dados[i].idConecta = i+1;
		h->dados[i].velocidade = distancia[i];
		pos_heap[i] = i;
	}

	// atualiza o tamanho da heap
	h->tam_heap = num_vertices;
	
	// coloca-se o vertice de origem como primeiro da lista de prioridades, mantendo-na ordenada	
	trocaDados(&h->dados[origem - 1], &h->dados[0]);
	trocaInt(&pos_heap[origem - 1], &pos_heap[0]);

	// enquanto nao forem percorridos todos os nos
	while(h->tam_heap > 0){
		// pega o vertice para ser analisado na lista de prioridades
		removeMin(h, pos_heap, &aux);	

		int vertice = aux.idConecta;
	
		// varre-se a lista de adjacencia do vertice atual e faz-se o relaxamento das arestas em relacao a ele	
		no *atual = *(grafo[vertice - 1].listaAdj);
		while(atual != NULL){
			// variavel dist guarda a velocidade da aresta entre o vertice analisado atualmente e o vertice de onde esse parte
			id = atual->idPoPs;
			dist = atual->velocidade;

			// se menor distancia conhecida para id > distancia vertice que leva a id em relacao a origem + distancia do vertice que leva a id ate id
			// em outras palavras, se a distancia conhecida para um vertice eh maior que uma nova distancia obtida pelo caminho analisado
			// caso isso ocorra, significa que foi encontrado outro caminho ate o vertice atual que passa pelo vertice retirado da heap
			if(distancia[id - 1] > distancia[vertice - 1] + dist){
				// atualiza as distancias e o predecessor (aquele que gera o caminho com essa distancia)
				distancia[id - 1] = distancia[vertice - 1] + dist;
				predecessor[id - 1] = vertice - 1;

				aux.idConecta = id;
				aux.velocidade = dist;

				// insere o vertice analisado na heap para que se analise os proximos caminhos a partir desse vertice, que gerou um novo caminho melhor
				atualizaHeap(h, pos_heap, aux);
			}

			// varre o proximo vertice da lista
			atual = atual->prox;
		}
		
	}
	free(h->dados);
	free(h);
}

// Busca em profundidad -> varre todo o grafo, classificando as arestas por cor
// 
// Nesse caso, como a busca em profundidade so eh utilizada para encontrar o numero de ciclos, nao eh necessario
// classificar arestas como de cruzamento ou avanco, mas apenas saber que elas sao arestas dessa natureza, pois
// conta-las resulta no numero de ciclos simples do grafo

void dfs(Grafo *grafo, int num_vertices, int *cor){
	int ciclos = 0;

	// cores
	// 0 -> branco
	// 1 -> cinza
	// 2 -> preto

	// define todos os vertices como brancos, i.e., nao analisados ainda
	for(int i = 0; i < num_vertices; i++){
		cor[i] = 0;
	}

	// para cada vertice do grafo que nao foi analisado ainda, faz-se a analise de todos os vertices aos quais ele se liga
	for(int i = 0; i < num_vertices; i++){
		if(cor[i] == 0) dfs_loop(grafo, &ciclos, i, cor);	
	}

	printf("Quantidade de ciclos: %d\n", ciclos);
}

void dfs_loop(Grafo *grafo, int *ciclos, int x, int *cor){
	// define-se a cor do vertice como cinza, i.e., em analise
	cor[x] = 1;	

	no *aux = *grafo[x].listaAdj;
	
	// varre-se a lista de vertices adjacentes analisando quem ainda nao foi analisado
	// o procedimento da busca eh ir cada vez mais fundo, entao, logo ao se encontrar um vertice adjacente ao atual e que nao foi analisado
	// aplica-se o mesmo procedimento para esse novo vertice
	while(aux != NULL){
		if(cor[aux->idPoPs - 1] == 0){

	  		dfs_loop(grafo, ciclos, aux->idPoPs - 1, cor);	// progride-se cada vez mais fundo no grafo
									//
		} else if(cor[aux->idPoPs - 1] == 2){ // caso o vertice analisado esteja se ligando a um vertice que ja foi analisado (preto, cor == 2), incrementa-se o numero de ciclos

			(*ciclos)++;

		}
		aux = aux->prox;	
	}

	// ao terminar de analisar toda a subarvore derivada do no atual, marca-o como fechado (cor == 2, preto)	
	cor[x] = 2;
}

// Algoritmo de Edmond-Karp -> busca o fluxo maximo entre dois vertices do grafo
//
// O algoritmo funciona com base nos conceitos de capacidade e fluxo. A capacidade eh o maximo que uma aresta consegue transmitir, nesse caso, a velocidade de conexao dela; ja o fluxo eh o que esta sendo transmitido no momento.
// Ele realiza buscas em largura para encontrar os caminhos mais curtos validos, i.e., os caminhos mais curtos que nao esta com sua capacidade no maximo. Assim que cada caminho eh encontrado, faz se a atribuicao de um fluxo 
// a ele, que eh igual a menor capacidade disponivel de todo caminho. Ao final de cada execucao, soma-se essa menor capacidade disponivel ao fluxo maximo.
// O algoritmo termina quando nao houver mais caminhos validos para se trafegar da origem ate o destino.
//

void EdmondKarp(Grafo *grafo, int num_vertices, int origem, int destino){
	// fluxo e capacidade sao matrizes que associam o fluxo e capacidade direcionados (i.e. fluxo[a][b] != fluxo[b][a])
	// isso eh importante de se considerar pelo conceito de fluxo de volta, que eh o fluxo oposto em uma aresta 
	int **fluxo = malloc(sizeof(int *) * num_vertices);	
	int **capacidade = malloc(sizeof(int *) * num_vertices);

	for(int i = 0; i < num_vertices; i++){
		fluxo[i] = malloc(sizeof(int) * num_vertices);
		capacidade[i] = malloc(sizeof(int) * num_vertices);
		
	}

	no *aux = NULL;
	
	// inicializa-se as capacidades como as velocidades de cada aresta e os fluxos como 	
	for(int i = 0; i < num_vertices; i++){
		aux = *grafo[i].listaAdj;	
		while(aux != NULL){
			capacidade[i][aux->idPoPs - 1] = aux->velocidade;
			fluxo[i][aux->idPoPs - 1] = 0;
			aux = aux->prox;
		}
	}

	// cria uma fila em que serao inseridos os proximos vertices a serem analisados
	queue *q = cria_queue();

	// cria-se um vetor de antecessores, que guarda o vertice v[x] que leva ao vertice de idConecta x+1
	int *antecessores = malloc(sizeof(int) * num_vertices);

	// fluxo maximo sera a saida do algoritmo
	int fluxo_max = 0;
	
	// o loop infinito se da pelo fato de que o algoritmo roda ate achar um caminho invalido, verificacao que eh feita dentro do while antes de se fazer as devidads atribuicoes para calculo de fluxo
	while(1){
		// para cada execucao, define-se os antecessores como -1, valor invalido
		for(int i = 0; i < num_vertices; i++){
			antecessores[i] = -1;
		}	

		// insere a origem na fila para ser analisada
		push(q, origem);	
		
		// o procedimento abaixo eh uma implementacao da busca em largura
		// enquanto a fila nao estiver vazia, i.e., enquanto nao se chegar ao fim de um caminho
		while(*q != NULL){
			// pega o idConecta do primeiro valor da lista e remove ele
			int id = pop(q);		
	
			// varre-se a lista de adjacencia desse vertice ate o fim; se o vertice nao tiver sido incluido em um caminho e o fluxo da aresta ate ele for menor que capacidade da aresta
			// ou seja, se o vertice for valido, inclui-o no caminho e insere-no na lista para ser analisado
			no *atual = *grafo[id - 1].listaAdj;
			while(atual != NULL){
				if(antecessores[atual->idPoPs - 1] == -1 && fluxo[id -1][atual->idPoPs - 1] < capacidade[id - 1][atual->idPoPs - 1]){
					antecessores[atual->idPoPs - 1] = id;
					push(q, atual->idPoPs);
				}	
				atual = atual->prox;
			}
		}

		// condicao de saida -> nao foi possivel definir um caminho ate o destino
		if(antecessores[destino - 1] == -1){
			break;
		} else {

			// define-se o fluxo minimo no caminho como infinito, para se buscar o menor
			int fluxo_min = INT_MAX;

			int filho = destino;
			int pai = antecessores[filho - 1];
			
			// enquanto o caminho nao chegar a origem, varre-se cada no que antecede destino e precede origem no caminho;
			while(filho != origem){
				// fluxo minimo recebe o menor entre o fluxo que ja se tem como minimo ou a capacidade util dessa aresta
				fluxo_min = min(fluxo_min, capacidade[pai - 1][filho - 1] - fluxo[pai - 1][filho - 1]);
				filho = pai;
				pai = antecessores[pai - 1];
				
			}	
	
			filho = destino;
			pai = antecessores[filho - 1];
	
			// novamente, refaz-se o caminho, mas agora para definir os fluxos e contrafluxos de cada caminho
			while(filho != origem){
				fluxo[pai - 1][filho - 1] += fluxo_min;
				fluxo[filho - 1][pai - 1] -= fluxo_min;
				filho = pai;
				pai = antecessores[pai - 1];
				
			}	
			
			// incrementa-se o fluxo com o fluxo minimo desse caminho
			fluxo_max += fluxo_min;
		}
	}
	
	if(fluxo_max != 0){
		printf("Fluxo máximo entre %d e %d: %d Mbps\n", origem, destino, fluxo_max);
	} else {
		printf("Fluxo máximo entre %d e %d: -1\n", origem, destino);
	}

	libera_queue(q);
	free(q);

	free(antecessores);
	for(int i = 0; i < num_vertices; i++){
		free(fluxo[i]);
		free(capacidade[i]);
		
	}
	free(fluxo);
	free(capacidade);
}


