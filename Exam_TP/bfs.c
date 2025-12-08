#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"

/* Créer une queue */
Queue* creerQueue() {
	Queue* q = malloc(sizeof(Queue));
	if (q == NULL) {
		perror("Erreur allocation queue");
		exit(EXIT_FAILURE);
	}
	q->debut = -1;
	q->fin = -1;
	return q;
}

/* Vérifier si vide */
int estVide(Queue* q) {
	return (q->fin == -1);
}

/* Enfiler */
void enfiler(Queue* q, int valeur) {
	if (q->fin == MAX_SOMMETS - 1) {
		fprintf(stderr, "Erreur: Queue pleine!\n");
		exit(EXIT_FAILURE);
	}
	
	if (q->debut == -1) {
		q->debut = 0;
	}
	
	q->fin++;
	q->items[q->fin] = valeur;
}

/* Défiler */
int defiler(Queue* q) {
	if (estVide(q)) {
		fprintf(stderr, "Erreur: Queue vide!\n");
		exit(EXIT_FAILURE);
	}
	
	int item = q->items[q->debut];
	q->debut++;
	
	if (q->debut > q->fin) {
		q->debut = -1;
		q->fin = -1;
	}
	
	return item;
}

/* Libérer queue */
void libererQueue(Queue* q) {
	if (q != NULL) {
		free(q);
	}
}

/* BFS principal */
void bfs(Graphe* g, int sommetDepart) {
	if (sommetDepart < 0 || sommetDepart >= g->nbSommets) {
		fprintf(stderr, "Erreur: sommet de départ invalide\n");
		return;
	}
	
	printf("\n=== BFS depuis le sommet %d ===\n\n", sommetDepart);
	
	/* Tableaux pour marquer les visités et distances */
	int visite[MAX_SOMMETS] = {0};
	int distance[MAX_SOMMETS];
	int parent[MAX_SOMMETS];
	
	/* Initialisation */
	for (int i = 0; i < g->nbSommets; i++) {
		distance[i] = -1;
		parent[i] = -1;
	}
	
	/* Créer la queue */
	Queue* q = creerQueue();
	
	/* Marquer le sommet de départ */
	visite[sommetDepart] = 1;
	distance[sommetDepart] = 0;
	enfiler(q, sommetDepart);
	
	printf("Ordre de visite: ");
	
	/* Parcours BFS */
	while (!estVide(q)) {
		int sommetActuel = defiler(q);
		printf("%d ", sommetActuel);
		
		/* Explorer les voisins */
		Noeud* temp = g->listeAdj[sommetActuel];
		while (temp != NULL) {
			int voisin = temp->sommet;
			
			if (visite[voisin] == 0) {
				visite[voisin] = 1;
				distance[voisin] = distance[sommetActuel] + 1;
				parent[voisin] = sommetActuel;
				enfiler(q, voisin);
			}
			
			temp = temp->suivant;
		}
	}
	
	printf("\n\n");
	
	/* Afficher les résultats */
	printf("Résultats:\n");
	printf("Sommet | Distance | Parent\n");
	printf("-------|----------|-------\n");
	for (int i = 0; i < g->nbSommets; i++) {
		printf("  %3d  |", i);
		if (distance[i] == -1) {
			printf(" Non atteint |   -\n");
		} else {
			printf("    %3d    | %3d\n", distance[i], parent[i]);
		}
	}
	printf("\n");
	
	libererQueue(q);
}
