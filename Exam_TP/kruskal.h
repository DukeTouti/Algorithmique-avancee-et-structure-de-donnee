#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graphe.h"

/* Structure Union-Find */
typedef struct {
	int parent[MAX_SOMMETS];
	int rang[MAX_SOMMETS];
} UnionFind;

/* Union-Find */
void initUnionFind(UnionFind* uf, int n);
int trouve(UnionFind* uf, int x);
void unionEnsembles(UnionFind* uf, int x, int y);

/* Kruskal */
void kruskal(Graphe* g);

#endif
