#include <stdio.h>
#include <stdlib.h>
#include "dfs.h"

/* DFS récursif */
void dfsRecursif(Graphe* g, int sommet, int* visite, int* temps, int* decouverte, int* fin) {
	/* Marquer comme visité */
	visite[sommet] = 1;
	(*temps)++;
	decouverte[sommet] = *temps;
	
	printf("%d ", sommet);
	
	/* Explorer les voisins */
	Noeud* temp = g->listeAdj[sommet];
	while (temp != NULL) {
		int voisin = temp->sommet;
		
		if (visite[voisin] == 0) {
			dfsRecursif(g, voisin, visite, temps, decouverte, fin);
		}
		
		temp = temp->suivant;
	}
	
	/* Enregistrer le temps de fin */
	(*temps)++;
	fin[sommet] = *temps;
}

/* DFS principal */
void dfs(Graphe* g, int sommetDepart) {
	if (sommetDepart < 0 || sommetDepart >= g->nbSommets) {
		fprintf(stderr, "Erreur: sommet de départ invalide\n");
		return;
	}
	
	printf("\n=== DFS depuis le sommet %d ===\n\n", sommetDepart);
	
	/* Tableaux */
	int visite[MAX_SOMMETS] = {0};
	int decouverte[MAX_SOMMETS];
	int fin[MAX_SOMMETS];
	
	/* Initialisation */
	for (int i = 0; i < g->nbSommets; i++) {
		decouverte[i] = -1;
		fin[i] = -1;
	}
	
	int temps = 0;
	
	printf("Ordre de visite: ");
	dfsRecursif(g, sommetDepart, visite, &temps, decouverte, fin);
	printf("\n\n");
	
	/* Afficher les résultats */
	printf("Résultats:\n");
	printf("Sommet | Découverte | Fin\n");
	printf("-------|------------|-----\n");
	for (int i = 0; i < g->nbSommets; i++) {
		printf("  %3d  |", i);
		if (decouverte[i] == -1) {
			printf(" Non atteint |  -\n");
		} else {
			printf("    %3d     | %3d\n", decouverte[i], fin[i]);
		}
	}
	printf("\n");
}
