#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "prim.h"

/* Trouver le sommet avec la clé minimale */
int extraireMin(int* cle, int* dansMST, int n) {
	int min = INT_MAX;
	int minIndex = -1;
	
	for (int v = 0; v < n; v++) {
		if (dansMST[v] == 0 && cle[v] < min) {
			min = cle[v];
			minIndex = v;
		}
	}
	
	return minIndex;
}

/* Algorithme de Prim */
void prim(Graphe* g) {
	if (g->oriente) {
		printf("Attention: Prim fonctionne sur les graphes non orientés!\n");
	}
	
	printf("\n=== Algorithme de Prim ===\n\n");
	
	int parent[MAX_SOMMETS];
	int cle[MAX_SOMMETS];
	int dansMST[MAX_SOMMETS] = {0};
	
	/* Initialisation */
	for (int i = 0; i < g->nbSommets; i++) {
		cle[i] = INT_MAX;
		parent[i] = -1;
	}
	
	/* Commencer par le sommet 0 */
	cle[0] = 0;
	
	printf("Construction du MST:\n");
	
	for (int count = 0; count < g->nbSommets; count++) {
		/* Extraire le sommet avec la clé minimale */
		int u = extraireMin(cle, dansMST, g->nbSommets);
		
		if (u == -1) break;
		
		dansMST[u] = 1;
		
		if (parent[u] != -1) {
			printf("  Ajouter arc (%d -> %d) poids=%d\n", parent[u], u, cle[u]);
		}
		
		/* Mettre à jour les clés des voisins */
		Noeud* temp = g->listeAdj[u];
		while (temp != NULL) {
			int v = temp->sommet;
			int poids = temp->poids;
			
			if (dansMST[v] == 0 && poids < cle[v]) {
				parent[v] = u;
				cle[v] = poids;
			}
			
			temp = temp->suivant;
		}
	}
	
	/* Afficher le MST */
	printf("\n=== Arbre Couvrant Minimum ===\n");
	printf("Arcs du MST:\n");
	int poidsTotal = 0;
	for (int i = 1; i < g->nbSommets; i++) {
		if (parent[i] != -1) {
			printf("  %d - %d (poids=%d)\n", parent[i], i, cle[i]);
			poidsTotal += cle[i];
		}
	}
	printf("Poids total: %d\n\n", poidsTotal);
}
