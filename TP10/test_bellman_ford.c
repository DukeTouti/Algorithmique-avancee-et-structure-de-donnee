#include "bellman_ford.h"
#include "affichage_bf.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	printf("========================================\n");
	printf("   Algorithme de Bellman-Ford\n");
	printf("========================================\n\n");
	
	/* Création du graphe g, voir Figure 3.32, page 101 */
	printf("Création du graphe (Figure 3.32)\n");
	Graphe *g = creerGraphe(5, 10);  /* 5 sommets, 10 arcs */
	
	ajouterArc(g, 0, 0, 1, 6);    // Arc s -> t
	ajouterArc(g, 1, 0, 4, 7);    // Arc s → y
	ajouterArc(g, 2, 1, 2, 5);    // Arc t → x
	ajouterArc(g, 3, 1, 3, -4);   // Arc t → z
	ajouterArc(g, 4, 1, 4, 8);    // Arc t → y
	ajouterArc(g, 5, 2, 1, -2);   // Arc x → 1
	ajouterArc(g, 6, 3, 2, 7);    // Arc z → x
	ajouterArc(g, 7, 3, 0, 2);    // Arc z → s
	ajouterArc(g, 8, 4, 2, -3);   // Arc y → x
	ajouterArc(g, 9, 4, 3, 9);    // Arc y → z
	
	afficherGraphe(g);
	
	/* Exécuter Bellman-Ford depuis le sommet source 0 */
	int source = 0;
	printf("\n========================================\n");
	printf("Exécution depuis le sommet source: %d\n", source);
	printf("========================================\n\n");
	
	ResultatBellmanFord *resultat = bellmanFord(g, source);
	
	/* Libérer la mémoire */
	libererResultat(resultat);
	libererGraphe(g);
	
	return 0;
}
