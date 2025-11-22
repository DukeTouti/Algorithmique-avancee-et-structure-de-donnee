#include <stdio.h>
#include <stdlib.h>
#include "dfs.h"

/* Fonction auxiliaire récursive pour DFS */
void dfsRecursif(Graphe* graphe, int sommet, int* temps, int* tempsDecouverte, int* tempsFin) {
	
	/* Marquer le sommet comme visité et enregistrer le temps de découverte */
	graphe->visite[sommet] = 1;
	(*temps)++;
	tempsDecouverte[sommet] = *temps;
	
	/* Explorer tous les voisins du sommet */
	Noeud* temp = graphe->listesAdjacence[sommet];
	while (temp != NULL) {
		int voisin = temp->sommet;
		
		/* Si le voisin n'a pas été visité, appel récursif */
		if (graphe->visite[voisin] == 0) {
			dfsRecursif(graphe, voisin, temps, tempsDecouverte, tempsFin);
		}
		
		temp = temp->suivant;
	}
	
	/* Enregistrer le temps de fin */
	(*temps)++;
	tempsFin[sommet] = *temps;
}

/* Parcours en profondeur (Depth-First Search) */
void dfs(Graphe* graphe, int sommetDepart, int* tempsDecouverte, int* tempsFin) {
	
	if (sommetDepart < 0 || sommetDepart >= graphe->nombreSommets) {
		fprintf(stderr, "Erreur : sommet de départ invalide\n");
		return;
	}
	
	/* Réinitialiser tous les sommets comme non visités */
	reinitialiserVisite(graphe);
	
	/* Initialiser tous les temps à -1 */
	for (int i = 0; i < graphe->nombreSommets; i++) {
		tempsDecouverte[i] = -1;
		tempsFin[i] = -1;
	}
	
	/* Variable pour suivre le temps global */
	int temps = 0;
	
	/* Lancer le DFS depuis le sommet de départ */
	dfsRecursif(graphe, sommetDepart, &temps, tempsDecouverte, tempsFin);
}

/* Afficher les résultats du DFS */
void afficherResultatsDFS(Graphe* graphe, int sommetDepart, int* tempsDecouverte, int* tempsFin) {
	printf("\n=== Résultats DFS depuis le sommet %d ===\n", sommetDepart);
	printf("Sommet | Découverte | Fin\n");
	printf("-------|------------|-----\n");
	
	for (int i = 0; i < graphe->nombreSommets; i++) {
		printf("  %3d  |  ", i);
		if (tempsDecouverte[i] == -1) {
			printf("Non atteint | -\n");
		} else {
			printf("%6d     | %3d\n", tempsDecouverte[i], tempsFin[i]);
		}
	}
	printf("\n");
}
