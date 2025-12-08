#include <stdio.h>
#include <stdlib.h>
#include "topo.h"

/* DFS pour tri topologique */
void dfsTopoRecursif(Graphe* g, int sommet, int* visite, int* pile, int* indicePile) {
	visite[sommet] = 1;
	
	/* Explorer les voisins */
	Noeud* temp = g->listeAdj[sommet];
	while (temp != NULL) {
		int voisin = temp->sommet;
		if (visite[voisin] == 0) {
			dfsTopoRecursif(g, voisin, visite, pile, indicePile);
		}
		temp = temp->suivant;
	}
	
	/* Empiler le sommet après avoir visité tous ses descendants */
	pile[(*indicePile)++] = sommet;
}

/* Tri topologique principal */
void triTopologique(Graphe* g) {
	if (!g->oriente) {
		printf("Erreur: Le tri topologique nécessite un graphe orienté!\n");
		return;
	}
	
	printf("\n=== Tri Topologique ===\n\n");
	
	int visite[MAX_SOMMETS] = {0};
	int pile[MAX_SOMMETS];
	int indicePile = 0;
	
	/* Appliquer DFS sur tous les sommets non visités */
	for (int i = 0; i < g->nbSommets; i++) {
		if (visite[i] == 0) {
			dfsTopoRecursif(g, i, visite, pile, &indicePile);
		}
	}
	
	/* Afficher l'ordre topologique (pile inversée) */
	printf("Ordre topologique: ");
	for (int i = indicePile - 1; i >= 0; i--) {
		printf("%d ", pile[i]);
	}
	printf("\n\n");
}
