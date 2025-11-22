#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"
#include "queue.h"

/* Parcours en largeur (Breadth-First Search) */
void bfs(Graphe* graphe, int sommetDepart, int* distances) {
	
	if (sommetDepart < 0 || sommetDepart >= graphe->nombreSommets) {
		fprintf(stderr, "Erreur : sommet de départ invalide\n");
		return;
	}
	
	/* Réinitialiser tous les sommets comme non visités */
	reinitialiserVisite(graphe);
	
	/* Initialiser toutes les distances à -1 (non atteint) */
	for (int i = 0; i < graphe->nombreSommets; i++) {
		distances[i] = -1;
	}
	
	/* Créer la queue pour BFS */
	Queue* q = creerQueue();
	
	/* Marquer le sommet de départ comme visité et distance 0 */
	graphe->visite[sommetDepart] = 1;
	distances[sommetDepart] = 0;
	enfiler(q, sommetDepart);
	
	/* Parcours BFS */
	while (!estVide(q)) {
		/* Défiler un sommet */
		int sommetActuel = defiler(q);
		
		/* Explorer tous les voisins du sommet actuel */
		Noeud* temp = graphe->listesAdjacence[sommetActuel];
		while (temp != NULL) {
			int voisin = temp->sommet;
			
			/* Si le voisin n'a pas été visité */
			if (graphe->visite[voisin] == 0) {
				graphe->visite[voisin] = 1;
				distances[voisin] = distances[sommetActuel] + 1;
				enfiler(q, voisin);
			}
			
			temp = temp->suivant;
		}
	}
	
	libererQueue(q);
}

/* Afficher les distances depuis le sommet de départ */
void afficherDistancesBFS(Graphe* graphe, int sommetDepart, int* distances) {
	printf("\n=== Résultats BFS depuis le sommet %d ===\n", sommetDepart);
	printf("Sommet | Distance\n");
	printf("-------|----------\n");
	
	for (int i = 0; i < graphe->nombreSommets; i++) {
		printf("  %3d  |  ", i);
		if (distances[i] == -1) {
			printf("Non atteint\n");
		} else {
			printf("%d\n", distances[i]);
		}
	}
	printf("\n");
}
