#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

/* Créer un nouveau noeud pour la liste d'adjacence */
Noeud* creerNoeud(int sommet) {

	Noeud* nouveauNoeud = malloc(sizeof(Noeud));
	if (nouveauNoeud == NULL) {
		perror("Erreur d'allocation mémoire pour le noeud\n");
		exit(EXIT_FAILURE);
	}

	nouveauNoeud->sommet = sommet;
	nouveauNoeud->suivant = NULL;
	return nouveauNoeud;
}

/* Créer un graphe avec un nombre donné de sommets */
Graphe* creerGraphe(int nombreSommets) {
	Graphe* graphe = malloc(sizeof(Graphe));
	if (graphe == NULL) {
		perror("Erreur d'allocation mémoire pour le graphe\n");
		exit(EXIT_FAILURE);
	}
   
	graphe->nombreSommets = nombreSommets;
    
	graphe->listesAdjacence = malloc(nombreSommets * sizeof(Noeud*));
	if (graphe->listesAdjacence == NULL) {
		perror("Erreur d'allocation mémoire pour les listes\n");
		free(graphe);
		exit(EXIT_FAILURE);
	}
    
	graphe->visite = malloc(nombreSommets * sizeof(int));
	if (graphe->visite == NULL) {
		perror("Erreur d'allocation mémoire pour le tableau visite\n");
		free(graphe->listesAdjacence);
		free(graphe);
		exit(EXIT_FAILURE);
	}
    
	// Initialiser toutes les listes à NULL et visite à 0
	for (int i = 0; i < nombreSommets; i++) {
		graphe->listesAdjacence[i] = NULL;
		graphe->visite[i] = 0;
	}
    
	return graphe;
}

/* Ajouter une arête non orientée entre deux sommets */
void ajouterArrete(Graphe* graphe, int src, int dest) {
	
	// Vérifier que les sommets sont valides
	if ((src < 0) || (src >= graphe->nombreSommets) || (dest < 0) || (dest >= graphe->nombreSommets)) {
		perror("Erreur : sommets invalides\n");
		return;
	}
   
	// Ajouter une arête de src vers dest
	Noeud* nouveauNoeud = creerNoeud(dest);
	nouveauNoeud->suivant = graphe->listesAdjacence[src];
	graphe->listesAdjacence[src] = nouveauNoeud;
    
	// Ajouter une arête de dest vers src (graphe non orienté)
	nouveauNoeud = creerNoeud(src);
	nouveauNoeud->suivant = graphe->listesAdjacence[dest];
	graphe->listesAdjacence[dest] = nouveauNoeud;
}

/* Afficher le graphe (listes d'adjacence) */
void afficherGraphe(Graphe* graphe) {
	
	printf("\n=== Structure du graphe ===\n");

	for (int i = 0; i < graphe->nombreSommets; i++) {
		Noeud* temp = graphe->listesAdjacence[i];
		printf("Sommet %d : ", i);
        
		if (temp == NULL) {
			printf("(aucune arête)");
		} else {
			while (temp) {
				printf("%d", temp->sommet);
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

/* Réinitialiser tous les sommets comme non visités */
void reinitialiserVisite(Graphe* graphe) {
	for (int i = 0; i < graphe->nombreSommets; i++) {
		graphe->visite[i] = 0;
	}
}

/* Libérer toute la mémoire allouée pour le graphe */
void libererGraphe(Graphe* graphe) {

	if (graphe == NULL) {
		return;
	}
    
	for (int i = 0; i < graphe->nombreSommets; i++) {
		Noeud* current = graphe->listesAdjacence[i];
		while (current != NULL) {
			Noeud* temp = current;
			current = current->suivant;
			free(temp);
		}
	}

	free(graphe->listesAdjacence);
	free(graphe->visite);
	free(graphe);
}
