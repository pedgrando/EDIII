#include "grafo.hpp"
#include <list>
#include <algorithm>
#include <string.h>
#include "data_structures.hpp"

void Aresta::InicializaAresta(Registro *reg)
{
	vertice1 = reg->idConecta;
	vertice2 = reg->idPoPsConectado;
	this->peso = reg->velocidade;
}

int Aresta::obterVertice1()
{
	return vertice1;
}

int Aresta::obterVertice2()
{
	return vertice2;
}

int Aresta::obterPeso()
{
	return peso;
}

// sobrescrita do operador "<"
bool Aresta::operator < (const Aresta& aresta2) const
{
	return (peso < aresta2.peso);
}

void Grafo::InicializaGrafo(int V)
{
	this->num_vertices = V;
	this->adjacentes = new list<Registro*>[V];
}

// função que adiciona uma aresta
void Grafo::adicionarAresta(Registro *reg)
{
	Aresta aresta;
	aresta.InicializaAresta(reg);
	arestas.push_back(aresta);
	adjacentes[reg->idPoPsConectado].push_back(reg);
}

// função que busca o subconjunto de um elemento "i"
int Grafo::buscar(int subset[], int i)
{
	if(subset[i] == -1)
		return i;
	return buscar(subset, subset[i]);
}

// função para unir dois subconjuntos em um único subconjunto
void Grafo::unir(int subset[], int v1, int v2)
{
	int v1_set = buscar(subset, v1);
	int v2_set = buscar(subset, v2);
	subset[v1_set] = v2_set;
}

/// função que roda o algoritmo de Kruskal
void Grafo::kruskal()
{
	vector<Aresta> arvore;
	int size_arestas = arestas.size();

	// ordena as arestas pelo menor peso
	sort(arestas.begin(), arestas.end());

	// aloca memória para criar "V" subconjuntos
	int * subset = new int[num_vertices];

	// inicializa todos os subconjuntos como conjuntos de um único elemento
	memset(subset, -1, sizeof(int) * num_vertices);

	for(int i = 0; i < size_arestas; i++)
	{
		int v1 = buscar(subset, arestas[i].obterVertice1());
		int v2 = buscar(subset, arestas[i].obterVertice2());

		if(v1 != v2)
		{
			// se forem diferentes é porque NÃO forma ciclo, insere no vetor
			arvore.push_back(arestas[i]);
			unir(subset, v1, v2); // faz a união
		}
	}

	int size_arvore = arvore.size();

	// mostra as arestas selecionadas com seus respectivos pesos
	for(int i = 0; i < size_arvore; i++)
	{
		char v1 = 'A' + arvore[i].obterVertice1();
		char v2 = 'A' + arvore[i].obterVertice2();
		cout << "(" << v1 << ", " << v2 << ") = " << arvore[i].obterPeso() << endl;
	}
}

void Grafo::ImprimeGrafo(){
	for(int i = 0; i < this->num_vertices; i++){

		adjacentes[i].sort([](const Registro *f, const Registro *s) { 
		return f->idConecta < s->idConecta; });
		
		std::list<Registro*>::iterator it = adjacentes[i].begin();
    	while(it != adjacentes[i].end()) {
			std::cout << (*it)->idConecta << ' ';
			it++;
    	}

	}
}

bool Grafo::VerticeVago(int v){
	return (adjacentes[v].empty());
}
