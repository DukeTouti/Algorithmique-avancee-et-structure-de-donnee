#include "floyd_warshall.h"
#include "affichage_fw.h"
#include <stdio.h>

/* Initialiser la matrice des distances */
void initialiserMatrice(int graph[][V], int matrix[][V]) {
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			matrix[i][j] = graph[i][j];
		}
	}
}

/* Initialiser la matrice des prédécesseurs */
void initialiserPredecesseurs(int pred[][V], int graph[][V]) {
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (i == j || graph[i][j] == INF) {
				pred[i][j] = -1;
			} else {
				pred[i][j] = i;
			}
		}
	}
}

/* Détecter un cycle négatif */
int detecterCycleNegatifFW(int matrix[][V]) {
	for (int i = 0; i < V; i++) {
		if (matrix[i][i] < 0) {
			printf("\n  Cycle de poids négatif détecté au sommet %d!\n", i);
			return 1;
		}
	}
	return 0;
}

/* Algorithme Floyd-Warshall */
void floydWarshall(int graph[][V], ResultatFloydWarshall *resultat) {
	printf("=== Initialisation ===\n");
	initialiserMatrice(graph, resultat->matrix);
	initialiserPredecesseurs(resultat->pred, graph);
	afficherMatriceFW(resultat->matrix, -1);
	
	/* Ajouter les sommets intermédiaires un par un */
	for (int k = 0; k < V; k++) {
		printf("\n=== Itération %d (via sommet %d) ===\n", k + 1, k);
		
		for (int i = 0; i < V; i++) {
			for (int j = 0; j < V; j++) {
				if (resultat->matrix[i][k] != INF && 
					resultat->matrix[k][j] != INF &&
					resultat->matrix[i][k] + resultat->matrix[k][j] < resultat->matrix[i][j]) {
					
					printf("Amélioration: d[%d][%d] = %d → %d (via %d)\n", 
						   i, j, resultat->matrix[i][j], 
						   resultat->matrix[i][k] + resultat->matrix[k][j], k);
					
					resultat->matrix[i][j] = resultat->matrix[i][k] + resultat->matrix[k][j];
					resultat->pred[i][j] = resultat->pred[k][j];
				}
			}
		}
		afficherMatriceFW(resultat->matrix, k);
	}
	
	/* Vérifier les cycles négatifs */
	printf("\n=== Vérification des cycles négatifs ===\n");
	if (detecterCycleNegatifFW(resultat->matrix)) {
		printf("Le graphe contient un cycle de poids négatif!\n");
	} else {
		printf("Aucun cycle de poids négatif détecté.\n");
	}
}
