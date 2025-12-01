#include "affichage_fw.h"
#include <stdio.h>

/* Afficher le graphe original */
void afficherGrapheOriginal(int graph[][V]) {
	printf("Graphe original (matrice d'adjacence):\n");
	printf("     ");
	for (int j = 0; j < V; j++) {
		printf("%4d", j);
	}
	printf("\n");
	printf("    ");
	for (int j = 0; j < V; j++) {
		printf("----");
	}
	printf("\n");
	
	for (int i = 0; i < V; i++) {
		printf("%4d|", i);
		for (int j = 0; j < V; j++) {
			if (graph[i][j] == INF)
				printf("%4s", "infini");
			else
				printf("%4d", graph[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/* Afficher la matrice des distances */
void afficherMatriceFW(int matrix[][V], int iteration) {
	if (iteration == -1) {
		printf("Matrice initiale:\n");
	} else {
		printf("Après passage par le sommet %d:\n", iteration);
	}
	
	printf("     ");
	for (int j = 0; j < V; j++) {
		printf("%4d", j);
	}
	printf("\n");
	printf("    ");
	for (int j = 0; j < V; j++) {
		printf("----");
	}
	printf("\n");
	
	for (int i = 0; i < V; i++) {
		printf("%4d|", i);
		for (int j = 0; j < V; j++) {
			if (matrix[i][j] == INF)
				printf("%4s", "infini");
			else
				printf("%4d", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/* Afficher le chemin de i à j */
void afficherCheminFW(int pred[][V], int i, int j) {
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

/* Afficher tous les chemins les plus courts */
void afficherTousLesChemins(int matrix[][V], int pred[][V]) {
	printf("=== Tous les plus courts chemins ===\n\n");
	
	for (int i = 0; i < V; i++) {
		printf("Depuis le sommet %d:\n", i);
		for (int j = 0; j < V; j++) {
			if (i != j) {
				printf("  -> %d (distance = ", j);
				if (matrix[i][j] == INF)
					printf("infini");
				else
					printf("%d", matrix[i][j]);
				printf("): ");
				afficherCheminFW(pred, i, j);
				printf("\n");
			}
		}
		printf("\n");
	}
}
