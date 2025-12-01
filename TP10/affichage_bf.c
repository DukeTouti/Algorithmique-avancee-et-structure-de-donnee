#include "affichage_bf.h"
#include <stdio.h>

/* Afficher le graphe */
void afficherGraphe(Graphe *g) {
	printf("Graphe: %d sommets, %d arcs\n", g->S, g->A);
	printf("Liste des arcs:\n");
	for (int i = 0; i < g->A; i++) {
		printf("  Arc %d: %d -> %d (poids: %d)\n", 
			   i, g->arc[i].u, g->arc[i].v, g->arc[i].w);
	}
	printf("\n");
}

/* Afficher les distances */
void afficherDistancesBF(int distance[], int taille) {
	printf("Distances: ");
	for (int i = 0; i < taille; i++) {
		if (distance[i] == INFINITY)
			printf("infini ");
		else
			printf("%d ", distance[i]);
	}
	printf("\n");
}

/* Afficher les prédécesseurs */
void afficherPredecesseurs(int pred[], int taille) {
	printf("Prédécesseurs: ");
	for (int i = 0; i < taille; i++) {
		printf("%d ", pred[i]);
	}
	printf("\n");
}

/* Afficher le chemin de source à dest */
void afficherCheminBF(int pred[], int source, int dest) {
	if (dest == source) {
		printf("%d", source);
		return;
	}
	if (pred[dest] == 0 && dest != source) {
		printf("Pas de chemin");
		return;
	}
	
	afficherCheminBF(pred, source, pred[dest]);
	printf(" -> %d", dest);
}

/* Afficher les résultats finaux */
void afficherResultatsBF(int distance[], int pred[], int taille, int source) {
	printf("Tableau des distances: ");
	afficherDistancesBF(distance, taille);
	
	printf("Tableau des prédécesseurs: ");
	afficherPredecesseurs(pred, taille);
	
	printf("\nChemins les plus courts depuis le sommet %d:\n", source);
	for (int i = 0; i < taille; i++) {
		if (i != source) {
			printf("  Vers %d (distance = ", i);
			if (distance[i] == INFINITY)
				printf("infini");
			else
				printf("%d", distance[i]);
			printf("): ");
			afficherCheminBF(pred, source, i);
			printf("\n");
		}
	}
}
