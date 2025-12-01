#include "floyd_warshall.h"
#include "affichage_fw.h"
#include <stdio.h>

int main(void) {
	printf("========================================\n");
	printf("   Algorithme de Floyd-Warshall\n");
	printf("========================================\n\n");
	
	/* Graphe de la Figure 3.35 */
	printf("Exemple de la Figure 3.35\n\n");
	int M[V][V] = {
		{0, 3, 8, INF, -4},
		{INF, 0, INF, 1, 7},
		{INF, 4, 0, INF, INF},
		{2, INF, -5, 0, INF},
		{INF, INF, INF, 6, 0}
	};
	
	afficherGrapheOriginal(M);
	
	/* Exécuter Floyd-Warshall */
	ResultatFloydWarshall resultat;
	
	printf("\n========================================\n");
	printf("Exécution de Floyd-Warshall\n");
	printf("========================================\n\n");
	
	floydWarshall(M, &resultat);
	
	/* Afficher tous les chemins */
	printf("\n========================================\n");
	printf("Résultats finaux\n");
	printf("========================================\n\n");
	
	afficherTousLesChemins(resultat.matrix, resultat.pred);
	
	return 0;
}
