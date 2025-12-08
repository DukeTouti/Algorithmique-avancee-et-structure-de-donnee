#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "floyd.h"

/* Afficher le chemin entre deux sommets */
void afficherCheminFW(int pred[MAX_SOMMETS][MAX_SOMMETS], int i, int j) {
	if (pred[i][j] == -1) {
		if (i == j) {
			printf("%d", i);
		} else {
			printf("Pas de chemin");
		}
		return;
	}
	
	if (i == j) {
		printf("%d", i);
		return;
	}
	
	afficherCheminFW(pred, i, pred[i][j]);
	printf(" -> %d", j);
}

/* Algorithme de Floyd-Warshall */
void floydWarshall(Graphe* g) {
	printf("\n=== Algorithme de Floyd-Warshall ===\n\n");
	
	int dist[MAX_SOMMETS][MAX_SOMMETS];
	int pred[MAX_SOMMETS][MAX_SOMMETS];
	
	/* Initialisation */
	printf("Phase 1: Initialisation\n");
	for (int i = 0; i < g->nbSommets; i++) {
		for (int j = 0; j < g->nbSommets; j++) {
			if (i == j) {
				dist[i][j] = 0;
				pred[i][j] = -1;
			} else if (g->matrice[i][j] != INFINI) {
				dist[i][j] = g->matrice[i][j];
				pred[i][j] = i;
			} else {
				dist[i][j] = INT_MAX / 2;
				pred[i][j] = -1;
			}
		}
	}
	
	/* Algorithme principal */
	printf("\nPhase 2: Calcul des plus courts chemins\n");
	for (int k = 0; k < g->nbSommets; k++) {
		printf("  Itération %d (via sommet %d):\n", k + 1, k);
		int modifications = 0;
		
		for (int i = 0; i < g->nbSommets; i++) {
			for (int j = 0; j < g->nbSommets; j++) {
				if (dist[i][k] != INT_MAX / 2 && dist[k][j] != INT_MAX / 2) {
					if (dist[i][k] + dist[k][j] < dist[i][j]) {
						printf("    Amélioration: dist[%d][%d] = %d -> %d (via %d)\n", 
							   i, j, dist[i][j], dist[i][k] + dist[k][j], k);
						dist[i][j] = dist[i][k] + dist[k][j];
						pred[i][j] = pred[k][j];
						modifications++;
					}
				}
			}
		}
		
		if (modifications == 0) {
			printf("    Aucune amélioration\n");
		}
	}
	
	/* Détecter les cycles négatifs */
	printf("\nPhase 3: Détection de cycles négatifs\n");
	int cycleNegatif = 0;
	for (int i = 0; i < g->nbSommets; i++) {
		if (dist[i][i] < 0) {
			printf("  Cycle négatif détecté au sommet %d!\n", i);
			cycleNegatif = 1;
		}
	}
	
	if (!cycleNegatif) {
		printf("  Aucun cycle négatif détecté.\n");
		
		/* Afficher tous les plus courts chemins */
		printf("\n=== Plus courts chemins (toutes paires) ===\n");
		for (int i = 0; i < g->nbSommets; i++) {
			printf("\nDepuis le sommet %d:\n", i);
			for (int j = 0; j < g->nbSommets; j++) {
				if (i != j) {
					printf("  Vers %d: ", j);
					if (dist[i][j] == INT_MAX / 2) {
						printf("Inaccessible\n");
					} else {
						printf("distance=%d, chemin: ", dist[i][j]);
						afficherCheminFW(pred, i, j);
						printf("\n");
					}
				}
			}
		}
	}
	
	printf("\n");
}
