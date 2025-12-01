#include "dijkstra.h"
#include "affichage.h"
#include <stdio.h>

/* Initialiser la matrice de coût */
void initialiserMatriceCout(int Graph[V][V], int cost[V][V], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (Graph[i][j] == 0) {
				cost[i][j] = INFINITY;
			} else {
				cost[i][j] = Graph[i][j];
			}
		}
	}
}

/* Trouver le noeud non visité avec la distance minimale */
int trouverProchainNoeud(int distance[], int visited[], int n) {
	int mindistance = INFINITY;
	int nextnode = -1;
	
	for (int i = 0; i < n; i++) {
		if (distance[i] < mindistance && !visited[i]) {
			mindistance = distance[i];
			nextnode = i;
		}
	}
	return nextnode;
}

/* Relâcher les arcs sortants du noeud courant */
void relacherArcs(int Graph[V][V], int cost[V][V], int distance[], int pred[], int nextnode, int n) {
	int mindistance = distance[nextnode];
	
	for (int i = 0; i < n; i++) {
		if (Graph[nextnode][i] != 0) { /* Si voisin */
			if (mindistance + cost[nextnode][i] < distance[i]) {
				distance[i] = mindistance + cost[nextnode][i];
				pred[i] = nextnode;
			}
		}
	}
}

/* Algorithme de Dijkstra principal */
void dijkstra(int Graph[V][V], int n, int start, ResultatDijkstra *resultat) {
	int cost[V][V];
	int visited[V];
	int count;
	
	/* Initialisation de la matrice coût */
	initialiserMatriceCout(Graph, cost, n);
	
	printf("Après initialisation\n");
	afficherMatrice(cost, n);
	
	/* Initialisation des tableaux distance, pred et visited */
	for (int i = 0; i < n; i++) {
		resultat->distance[i] = INFINITY;
		resultat->pred[i] = -1;
		visited[i] = 0;
	}
	
	/* Distance du noeud source à lui-même = 0 */
	resultat->distance[start] = 0;
	
	printf("\nInitialisation des distances:\n");
	afficherDistances(resultat->distance, n, start);
	
	/* Boucle principale de Dijkstra */
	count = 0;
	while (count < n) {
		/* Sélectionner le prochain noeud à visiter */
		int nextnode = trouverProchainNoeud(resultat->distance, visited, n);
		
		printf("\n=== Itération %d ===\n", count);
		printf("Noeud à visiter: %d\n", nextnode);
		afficherDistances(resultat->distance, n, start);
		
		/* Marquer comme visité */
		visited[nextnode] = 1;
		
		/* Relâcher tous les arcs sortants */
		relacherArcs(Graph, cost, resultat->distance, resultat->pred, nextnode, n);
		
		count++;
	}
	
	printf("\n=== Résultats finaux ===\n");
	afficherResultatsFinaux(resultat->distance, resultat->pred, n, start);
}
