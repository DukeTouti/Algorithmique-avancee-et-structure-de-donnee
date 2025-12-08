#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "bellman.h"

/* Afficher le chemin */
void afficherCheminBF(int* parent, int dest) {
	if (parent[dest] == -1) {
		printf("%d", dest);
		return;
	}
	afficherCheminBF(parent, parent[dest]);
	printf(" -> %d", dest);
}

/* Algorithme de Bellman-Ford */
void bellmanFord(Graphe* g, int source) {
	if (source < 0 || source >= g->nbSommets) {
		fprintf(stderr, "Erreur: sommet source invalide\n");
		return;
	}
	
	printf("\n=== Algorithme de Bellman-Ford depuis le sommet %d ===\n\n", source);
	
	int distance[MAX_SOMMETS];
	int parent[MAX_SOMMETS];
	
	/* Initialisation */
	for (int i = 0; i < g->nbSommets; i++) {
		distance[i] = INT_MAX;
		parent[i] = -1;
	}
	distance[source] = 0;
	
	printf("Phase 1: Initialisation\n");
	printf("distance[%d] = 0, autres = INFINI\n\n", source);
	
	/* Relâcher les arcs |V|-1 fois */
	printf("Phase 2: Relâchement des arcs\n");
	for (int i = 0; i < g->nbSommets - 1; i++) {
		printf("  Itération %d:\n", i + 1);
		int modifications = 0;
		
		for (int j = 0; j < g->nbArcs; j++) {
			int u = g->arcs[j].src;
			int v = g->arcs[j].dest;
			int poids = g->arcs[j].poids;
			
			if (distance[u] != INT_MAX && distance[u] + poids < distance[v]) {
				printf("    Relâcher (%d -> %d): distance[%d] = %d -> %d\n", 
					   u, v, v, distance[v], distance[u] + poids);
				distance[v] = distance[u] + poids;
				parent[v] = u;
				modifications++;
			}
		}
		
		if (modifications == 0) {
			printf("    Aucune modification, convergence atteinte!\n");
			break;
		}
	}
	
	/* Détecter les cycles négatifs */
	printf("\nPhase 3: Détection de cycle négatif\n");
	int cycleNegatif = 0;
	for (int i = 0; i < g->nbArcs; i++) {
		int u = g->arcs[i].src;
		int v = g->arcs[i].dest;
		int poids = g->arcs[i].poids;
		
		if (distance[u] != INT_MAX && distance[u] + poids < distance[v]) {
			printf("  Cycle négatif détecté sur l'arc (%d -> %d)!\n", u, v);
			cycleNegatif = 1;
			break;
		}
	}
	
	if (!cycleNegatif) {
		printf("  Aucun cycle négatif détecté.\n");
		
		/* Afficher les résultats */
		printf("\n=== Plus courts chemins depuis le sommet %d ===\n", source);
		for (int i = 0; i < g->nbSommets; i++) {
			if (i != source) {
				printf("Vers %d: ", i);
				if (distance[i] == INT_MAX) {
					printf("Inaccessible\n");
				} else {
					printf("distance=%d, chemin: ", distance[i]);
					afficherCheminBF(parent, i);
					printf("\n");
				}
			}
		}
	}
	
	printf("\n");
}
