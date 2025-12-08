#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

/* Initialiser Union-Find */
void initUnionFind(UnionFind* uf, int n) {
	for (int i = 0; i < n; i++) {
		uf->parent[i] = i;
		uf->rang[i] = 0;
	}
}

/* Trouver le représentant */
int trouve(UnionFind* uf, int x) {
	if (uf->parent[x] != x) {
		uf->parent[x] = trouve(uf, uf->parent[x]);
	}
	return uf->parent[x];
}

/* Union de deux ensembles */
void unionEnsembles(UnionFind* uf, int x, int y) {
	int racineX = trouve(uf, x);
	int racineY = trouve(uf, y);
	
	if (racineX == racineY) return;
	
	if (uf->rang[racineX] < uf->rang[racineY]) {
		uf->parent[racineX] = racineY;
	} else if (uf->rang[racineX] > uf->rang[racineY]) {
		uf->parent[racineY] = racineX;
	} else {
		uf->parent[racineY] = racineX;
		uf->rang[racineX]++;
	}
}

/* Comparateur pour trier les arcs */
int comparerArcs(const void* a, const void* b) {
	Arc* arcA = (Arc*)a;
	Arc* arcB = (Arc*)b;
	return arcA->poids - arcB->poids;
}

/* Algorithme de Kruskal */
void kruskal(Graphe* g) {
	if (g->oriente) {
		printf("Attention: Kruskal fonctionne sur les graphes non orientés!\n");
	}
	
	printf("\n=== Algorithme de Kruskal ===\n\n");
	
	/* Trier les arcs par poids croissant */
	qsort(g->arcs, g->nbArcs, sizeof(Arc), comparerArcs);
	
	UnionFind uf;
	initUnionFind(&uf, g->nbSommets);
	
	Arc mst[MAX_SOMMETS];
	int nbAretesMST = 0;
	int poidsTotal = 0;
	
	printf("Arcs triés par poids:\n");
	for (int i = 0; i < g->nbArcs; i++) {
		printf("  (%d -> %d) poids=%d\n", g->arcs[i].src, g->arcs[i].dest, g->arcs[i].poids);
	}
	printf("\n");
	
	printf("Construction du MST:\n");
	for (int i = 0; i < g->nbArcs; i++) {
		int u = g->arcs[i].src;
		int v = g->arcs[i].dest;
		int poids = g->arcs[i].poids;
		
		if (trouve(&uf, u) != trouve(&uf, v)) {
			printf("  Ajouter arc (%d -> %d) poids=%d\n", u, v, poids);
			mst[nbAretesMST++] = g->arcs[i];
			poidsTotal += poids;
			unionEnsembles(&uf, u, v);
		} else {
			printf("  Rejeter arc (%d -> %d) poids=%d (créerait un cycle)\n", u, v, poids);
		}
		
		if (nbAretesMST == g->nbSommets - 1) {
			break;
		}
	}
	
	printf("\n=== Arbre Couvrant Minimum ===\n");
	printf("Arcs du MST:\n");
	for (int i = 0; i < nbAretesMST; i++) {
		printf("  %d - %d (poids=%d)\n", mst[i].src, mst[i].dest, mst[i].poids);
	}
	printf("Poids total: %d\n\n", poidsTotal);
}
