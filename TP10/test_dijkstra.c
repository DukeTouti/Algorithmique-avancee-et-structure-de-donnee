#include "dijkstra.h"
#include "affichage.h"
#include <stdio.h>

int main() {
	int M[V][V];
	ResultatDijkstra resultat;
	
	/* Graphe de la Figure 3.30 page 99 */
	/* s(0); t(8); x(9); z(7); y(5); */
	
	printf("=== Graphe Figure 3.30 ===\n");
	printf("Sommets: s(0), t(1), x(2), z(3), y(4)\n\n");
	
	int graphe[V][V] = {
		{0, 10, 0, 0, 5},    /* s(0) -> t(10), y(5) */
		{0,  0, 1, 2, 0},    /* t(0) -> x(1), y(2) */
		{0,  0, 0, 4, 0},    /* x(0) -> z(4) */
		{7,  0, 6, 0, 0},    /* z(0) -> s(7), x(6) */
		{0,  3, 9, 2, 0}     /* y(0) -> t(8), x(9), z(2) */
	};
	
	/* Copier le graphe */
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			M[i][j] = graphe[i][j];
		}
	}
	
	printf("Matrice d'adjacence:\n");
	afficherMatrice(M, V);
	
	/* Exécuter Dijkstra depuis le noeud source 0 (s) */
	int source = 0;
	printf("\n========================================\n");
	printf("Exécution de Dijkstra depuis le noeud %d\n", source);
	printf("========================================\n\n");
	
	dijkstra(M, V, source, &resultat);
	
	return 0;
}
