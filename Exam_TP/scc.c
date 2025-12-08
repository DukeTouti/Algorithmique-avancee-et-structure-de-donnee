#include <stdio.h>
#include <stdlib.h>
#include "scc.h"

/* DFS pour remplir la pile */
void dfsSCC1(Graphe* g, int sommet, int* visite, int* pile, int* indicePile) {
	visite[sommet] = 1;
	
	Noeud* temp = g->listeAdj[sommet];
	while (temp != NULL) {
		int voisin = temp->sommet;
		if (visite[voisin] == 0) {
			dfsSCC1(g, voisin, visite, pile, indicePile);
		}
		temp = temp->suivant;
	}
	
	pile[(*indicePile)++] = sommet;
}

/* DFS pour identifier une composante */
void dfsSCC2(Graphe* gTranspose, int sommet, int* visite) {
	visite[sommet] = 1;
	printf("%d ", sommet);
	
	Noeud* temp = gTranspose->listeAdj[sommet];
	while (temp != NULL) {
		int voisin = temp->sommet;
		if (visite[voisin] == 0) {
			dfsSCC2(gTranspose, voisin, visite);
		}
		temp = temp->suivant;
	}
}

/* Transposer le graphe */
Graphe* transposerGraphe(Graphe* g) {
	Graphe* gT = creerGraphe(g->nbSommets, 1);
	
	for (int i = 0; i < g->nbSommets; i++) {
		Noeud* temp = g->listeAdj[i];
		while (temp != NULL) {
			ajouterArrete(gT, temp->sommet, i, temp->poids);
			temp = temp->suivant;
		}
	}
	
	return gT;
}

/* Algorithme de Kosaraju */
void kosaraju(Graphe* g) {
	if (!g->oriente) {
		printf("Erreur: Les SCC nécessitent un graphe orienté!\n");
		return;
	}
	
	printf("\n=== Composantes Fortement Connexes (Kosaraju) ===\n\n");
	
	int visite[MAX_SOMMETS] = {0};
	int pile[MAX_SOMMETS];
	int indicePile = 0;
	
	/* Étape 1: DFS sur le graphe original */
	printf("Étape 1: Premier DFS\n");
	for (int i = 0; i < g->nbSommets; i++) {
		if (visite[i] == 0) {
			dfsSCC1(g, i, visite, pile, &indicePile);
		}
	}
	
	/* Étape 2: Transposer le graphe */
	printf("Étape 2: Transposition du graphe\n");
	Graphe* gTranspose = transposerGraphe(g);
	
	/* Étape 3: DFS sur le graphe transposé */
	printf("Étape 3: Identification des composantes\n\n");
	for (int i = 0; i < g->nbSommets; i++) {
		visite[i] = 0;
	}
	
	int numComposante = 1;
	for (int i = indicePile - 1; i >= 0; i--) {
		int sommet = pile[i];
		if (visite[sommet] == 0) {
			printf("Composante %d: ", numComposante++);
			dfsSCC2(gTranspose, sommet, visite);
			printf("\n");
		}
	}
	
	printf("\n");
	libererGraphe(gTranspose);
}
