#include <iostream>
#include <vector>
#include <list>

using namespace std;

#include "data_structures.hpp"

class Aresta
{
	int vertice1, vertice2, peso;
	Registro *Register;

public:

	void InicializaAresta(Registro *reg);

	int obterVertice1();

	int obterVertice2();
	
	int obterPeso();

	// sobrescrita do operador "<"
	bool operator < (const Aresta& aresta2) const;
};


class Grafo
{
	int num_vertices; // número de vértices
	vector<Aresta> arestas; // vetor de arestas
	list<Registro*> *adjacentes;

public:

	void InicializaGrafo(int V);

	void adicionarAresta(Registro *reg);

	int buscar(int subset[], int i);
    
    void unir(int subset[], int v1, int v2);

	void kruskal();

	void ImprimeGrafo();

	bool VerticeVago(int v);

};