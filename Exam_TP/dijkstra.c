#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "dijkstra.h"

/* Trouver le sommet avec la distance minimale */
int trouverMinDistance(int* distance, int* visite, int n) {
	int min = INT_MAX;
	int minIndex = -1;
	
	for (int i = 0; i < n; i++) {
		if (visite[i] == 0 && distance[i] < min) {
			min = distance[i];
			minIndex = i;
		}
	}
	
	return minIndex;
}

/* Afficher le chemin */
void afficherChemin(int* parent, int dest) {
	if (parent[dest] == -1) {
		printf("%d", dest);
		return;
	}
	afficherChemin(parent, parent[dest]);
	printf(" -> %d", dest);
}

/* Algorithme de Dijkstra */
void dijkstra(Graphe* g, int source) {
	if (source < 0 || source >= g->nbSommets) {
		fprintf(stderr, "Erreur: sommet source invalide\n");
		return;
	}
	
	printf("\n=== Algorithme de Dijkstra depuis le sommet %d ===\n\n", source);
	
	int distance[MAX_SOMMETS];
	int parent[MAX_SOMMETS];
	int visite[MAX_SOMMETS] = {0};
	
	/* Initialisation */
	for (int i = 0; i < g->nbSommets; i++) {
		distance[i] = INT_MAX;
		parent[i] = -1;
	}
	distance[source] = 0;
	
	printf("Itérations:\n");
	
	/* Algorithme principal */
	for (int count = 0; count < g->nbSommets; count++) {
		int u = trouverMinDistance(distance, visite, g->nbSommets);
		
		if (u == -1 || distance[u] == INT_MAX) break;
		
		visite[u] = 1;
		printf("  Itération %d: visiter sommet %d (distance=%d)\n", count + 1, u, distance[u]);
		
		/* Relâcher les arcs sortants */
		Noeud* temp = g->listeAdj[u];
		while (temp != NULL) {
			int v = temp->sommet;
			int poids = temp->poids;
			
			if (visite[v] == 0 && distance[u] != INT_MAX) {
				if (distance[u] + poids < distance[v]) {
					printf("    Relâcher (%d -> %d): distance[%d] = %d -> %d\n", 
						   u, v, v, distance[v], distance[u] + poids);
					distance[v] = distance[u] + poids;
					parent[v] = u;
				}
			}
			
			temp = temp->suivant;
		}
	}
	
	/* Afficher les résultats */
	printf("\n=== Plus courts chemins depuis le sommet %d ===\n", source);
	for (int i = 0; i < g->nbSommets; i++) {
		if (i != source) {
			printf("Vers %d: ", i);
			if (distance[i] == INT_MAX) {
				printf("Inaccessible\n");
			} else {
				printf("distance=%d, chemin: ", distance[i]);
				afficherChemin(parent, i);
				printf("\n");
			}
		}
	}
	printf("\n");
}
