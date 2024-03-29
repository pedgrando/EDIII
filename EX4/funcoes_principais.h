#ifndef __FUNCOES_PRINCIPAIS_H__
#define __FUNCOES_PRINCIPAIS_H__

#include "data_structures.h"
#include "pilha.h"
#include "miscelaneous.h"

void Dijkstra(Grafo *grafo, int origem, int *distancia, int *predecessor, int num_vertices);

void dfs(Grafo *grafo, int num_vertices, int *cor);

void dfs_loop(Grafo *grafo, int *ciclos, int x, int *cor);

void EdmondKarp(Grafo *grafo, int num_vertices, int origem, int destino);

#endif

