#include "affichage.h"
#include <stdio.h>

/* Afficher une matrice */
void afficherMatrice(int G[][V], int n) {
	for (int i = 0; i < n; i++) {
		printf("%d: ", i);
		for (int j = 0; j < n; j++) {
			if (G[i][j] == 99)
				printf("infini ");
			else
				printf("%d ", G[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/* Afficher les distances actuelles */
void afficherDistances(int distance[], int n, int start) {
	for (int i = 0; i < n; i++) {
		printf("Distance de %d à %d: ", start, i);
		if (distance[i] == 99)
			printf("infini\n");
		else
			printf("%d\n", distance[i]);
	}
}

/* Afficher le chemin de start à end */
void afficherChemin(int pred[], int start, int end) {
	if (end == start) {
		printf("%d", start);
		return;
	}
	if (pred[end] == -1) {
		printf("Pas de chemin");
		return;
	}
	
	afficherChemin(pred, start, pred[end]);
	printf(" → %d", end);
}

/* Afficher les résultats finaux avec chemins */
void afficherResultatsFinaux(int distance[], int pred[], int n, int start) {
	for (int i = 0; i < n; i++) {
		if (i != start) {
			printf("\nNoeud %d:\n", i);
			printf("  Distance: ");
			if (distance[i] == 99)
				printf("infini\n");
			else
				printf("%d\n", distance[i]);
			
			printf("  Chemin: ");
			afficherChemin(pred, start, i);
			printf("\n");
		}
	}
}
