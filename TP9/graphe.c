#include <stdio.h>
#include <stdlib.h>
#include "graphe.h"

/* Créer un graphe avec un nombre donné de sommets */
Graphe* creerGraphe(int nombreSommets) {
	Graphe* graphe = malloc(sizeof(Graphe));
	if (graphe == NULL) {
		perror("Erreur d'allocation mémoire pour le graphe\n");
		exit(EXIT_FAILURE);
	}
   
	graphe->nombreSommets = nombreSommets;
	graphe->nombreAretes = 0;
    
	graphe->listesAdjacence = malloc(nombreSommets * sizeof(Noeud*));
	if (graphe->listesAdjacence == NULL) {
		perror("Erreur d'allocation mémoire pour les listes\n");
		free(graphe);
		exit(EXIT_FAILURE);
	}
	
	/* Initialiser toutes les listes à NULL */
	for (int i = 0 ; i < nombreSommets ; i++) {
		graphe->listesAdjacence[i] = NULL;
	}
    
	/* Allouer le tableau d'arêtes (capacité initiale) */
	int maxAretes = (nombreSommets * (nombreSommets - 1)) / 2;
	
	graphe->capaciteAretes = maxAretes;
	graphe->aretes = malloc(maxAretes * sizeof(Arete));
	
	if (graphe->aretes == NULL) {
		perror("Erreur d'allocation mémoire pour le tableau d'arêtes\n");
		free(graphe->listesAdjacence);
		free(graphe);
		exit(EXIT_FAILURE);
	}
    
	return graphe;
}

/* Ajouter une arête non orientée entre deux sommets */
void ajouterArrete(Graphe* graphe, int src, int dest, int poids) {
	
	// Vérifier que les sommets sont valides
	if ((src < 0) || (src >= graphe->nombreSommets) || (dest < 0) || (dest >= graphe->nombreSommets)) {
		fprintf(stderr, "Erreur : sommets invalides (%d, %d)\n", src, dest);
		return;
	}

	/* Éviter les boucles (arête vers soi-même) */
	if (src == dest) {
		return;
	}
   
	/* Ajouter l'arête dans le tableau (pour Kruskal) une seule fois */
	if (graphe->nombreAretes < graphe->capaciteAretes) {
		graphe->aretes[graphe->nombreAretes].src = src;
		graphe->aretes[graphe->nombreAretes].dest = dest;
		graphe->aretes[graphe->nombreAretes].poids = poids;
		graphe->nombreAretes++;
	}
	
	/* Ajouter dans la liste d'adjacence de src */
	Noeud* nouveauNoeud = malloc(sizeof(Noeud));
	if (nouveauNoeud == NULL) {
		perror("Erreur d'allocation mémoire pour le noeud");
		exit(EXIT_FAILURE);
	}
	
	nouveauNoeud->sommet = dest;
	nouveauNoeud->poids = poids;
	nouveauNoeud->suivant = graphe->listesAdjacence[src];
	graphe->listesAdjacence[src] = nouveauNoeud;

	/* Ajouter dans la liste d'adjacence de dest (graphe non orienté) */
	nouveauNoeud = malloc(sizeof(Noeud));
	if (nouveauNoeud == NULL) {
		perror("Erreur d'allocation mémoire pour le noeud");
		exit(EXIT_FAILURE);
	}
	nouveauNoeud->sommet = src;
	nouveauNoeud->poids = poids;
	nouveauNoeud->suivant = graphe->listesAdjacence[dest];
	graphe->listesAdjacence[dest] = nouveauNoeud;
}

/* Afficher le graphe (listes d'adjacence) */
void afficherGraphe(Graphe* graphe) {
	
	printf("\n=== Structure du graphe ===\n");
	printf("Nombre de sommets : %d\n", graphe->nombreSommets);
	printf("Nombre d'arêtes : %d\n\n", graphe->nombreAretes);

	for (int i = 0 ; i < graphe->nombreSommets ; i++) {
		Noeud* temp = graphe->listesAdjacence[i];
		printf("Sommet %d : ", i);
        
		if (temp == NULL) {
			printf("(aucune arête)");
		} else {
			while (temp) {
				printf("%d (poids = %d)", temp->sommet, temp->poids);
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

/* Libérer toute la mémoire allouée pour le graphe */
void libererGraphe(Graphe* graphe) {

	if (graphe == NULL) {
		return;
	}

	/* Libérer les listes d'adjacence */
	for (int i = 0 ; i < graphe->nombreSommets ; i++) {
		Noeud* current = graphe->listesAdjacence[i];
		while (current != NULL) {
			Noeud* temp = current;
			current = current->suivant;
			free(temp);
		}
	}

	free(graphe->listesAdjacence);
	free(graphe->aretes);
	free(graphe);
}

/* Générer un graphe aléatoire pondéré avec une densité donnée */
Graphe* genererGrapheAleatoire(int nombreSommets, double densite, int poidsMin, int poidsMax) {
	Graphe* graphe = creerGraphe(nombreSommets);
	
	/* Calculer le nombre maximum d'arêtes possibles (graphe non orienté) */
	int maxAretes = (nombreSommets * (nombreSommets - 1)) / 2;
	int nombreAretesVoulues = (int)(maxAretes * densite);
	
	/* Tableau pour éviter les doublons */
	int** matrice = malloc(nombreSommets * sizeof(int*));
	for (int i = 0; i < nombreSommets; i++) {
		matrice[i] = calloc(nombreSommets, sizeof(int));
	}
	
	/* Ajouter des arêtes aléatoires */
	int arretesAjoutees = 0;
	while (arretesAjoutees < nombreAretesVoulues) {
		int src = rand() % nombreSommets;
		int dest = rand() % nombreSommets;
		
		/* Éviter les boucles et les doublons */
		if (src != dest && matrice[src][dest] == 0) {
			int poids = poidsMin + (rand() % (poidsMax - poidsMin + 1));
			ajouterArete(graphe, src, dest, poids);
			matrice[src][dest] = 1;
			matrice[dest][src] = 1;
			arretesAjoutees++;
		}
	}
	
	/* Libérer la matrice temporaire */
	for (int i = 0; i < nombreSommets; i++) {
		free(matrice[i]);
	}
	free(matrice);
	
	return graphe;
}







