#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

/* Créer un graphe */
Graphe* creerGraphe(int nbSommets, int oriente) {
	Graphe* g = malloc(sizeof(Graphe));
	if (g == NULL) {
		perror("Erreur allocation graphe");
		exit(EXIT_FAILURE);
	}
	
	g->nbSommets = nbSommets;
	g->nbArcs = 0;
	g->oriente = oriente;
	
	/* Allouer les listes d'adjacence */
	g->listeAdj = malloc(nbSommets * sizeof(Noeud*));
	if (g->listeAdj == NULL) {
		perror("Erreur allocation listes");
		free(g);
		exit(EXIT_FAILURE);
	}
	
	/* Initialiser les listes à NULL et la matrice à INFINI */
	for (int i = 0; i < nbSommets; i++) {
		g->listeAdj[i] = NULL;
		for (int j = 0; j < nbSommets; j++) {
			if (i == j) {
				g->matrice[i][j] = 0;
			} else {
				g->matrice[i][j] = INFINI;
			}
		}
	}
	
	/* Allouer tableau des arcs */
	g->capaciteArcs = nbSommets * nbSommets;
	g->arcs = malloc(g->capaciteArcs * sizeof(Arc));
	if (g->arcs == NULL) {
		perror("Erreur allocation arcs");
		free(g->listeAdj);
		free(g);
		exit(EXIT_FAILURE);
	}
	
	return g;
}

/* Ajouter une arête */
void ajouterArrete(Graphe* g, int src, int dest, int poids) {
	if (src < 0 || src >= g->nbSommets || dest < 0 || dest >= g->nbSommets) {
		fprintf(stderr, "Erreur: sommets invalides (%d, %d)\n", src, dest);
		return;
	}
	
	/* Ajouter dans la matrice */
	g->matrice[src][dest] = poids;
	
	/* Ajouter dans le tableau des arcs */
	if (g->nbArcs < g->capaciteArcs) {
		g->arcs[g->nbArcs].src = src;
		g->arcs[g->nbArcs].dest = dest;
		g->arcs[g->nbArcs].poids = poids;
		g->nbArcs++;
	}
	
	/* Ajouter dans la liste d'adjacence de src */
	Noeud* nouveau = malloc(sizeof(Noeud));
	if (nouveau == NULL) {
		perror("Erreur allocation noeud");
		exit(EXIT_FAILURE);
	}
	nouveau->sommet = dest;
	nouveau->poids = poids;
	nouveau->suivant = g->listeAdj[src];
	g->listeAdj[src] = nouveau;
	
	/* Si graphe non orienté, ajouter l'arête inverse */
	if (!g->oriente) {
		g->matrice[dest][src] = poids;
		
		Noeud* nouveau2 = malloc(sizeof(Noeud));
		if (nouveau2 == NULL) {
			perror("Erreur allocation noeud");
			exit(EXIT_FAILURE);
		}
		nouveau2->sommet = src;
		nouveau2->poids = poids;
		nouveau2->suivant = g->listeAdj[dest];
		g->listeAdj[dest] = nouveau2;
	}
}

/* Afficher le graphe (listes d'adjacence) */
void afficherGraphe(Graphe* g) {
	printf("\n=== Graphe (%s) ===\n", g->oriente ? "orienté" : "non orienté");
	printf("Nombre de sommets: %d\n", g->nbSommets);
	printf("Nombre d'arcs: %d\n\n", g->nbArcs);
	
	for (int i = 0; i < g->nbSommets; i++) {
		printf("Sommet %d: ", i);
		Noeud* temp = g->listeAdj[i];
		if (temp == NULL) {
			printf("(aucune arête)");
		} else {
			while (temp != NULL) {
				printf("%d(poids=%d)", temp->sommet, temp->poids);
				if (temp->suivant != NULL) {
					printf(" -> ");
				}
				temp = temp->suivant;
			}
		}
		printf("\n");
	}
	printf("\n");
}

/* Afficher la matrice d'adjacence */
void afficherMatrice(Graphe* g) {
	printf("\n=== Matrice d'adjacence ===\n");
	printf("     ");
	for (int j = 0; j < g->nbSommets; j++) {
		printf("%5d", j);
	}
	printf("\n");
	
	for (int i = 0; i < g->nbSommets; i++) {
		printf("%5d", i);
		for (int j = 0; j < g->nbSommets; j++) {
			if (g->matrice[i][j] == INFINI) {
				printf("  inf");
			} else {
				printf("%5d", g->matrice[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
}

/* Libérer le graphe */
void libererGraphe(Graphe* g) {
	if (g == NULL) return;
	
	/* Libérer les listes d'adjacence */
	for (int i = 0; i < g->nbSommets; i++) {
		Noeud* current = g->listeAdj[i];
		while (current != NULL) {
			Noeud* temp = current;
			current = current->suivant;
			free(temp);
		}
	}
	
	free(g->listeAdj);
	free(g->arcs);
	free(g);
}
