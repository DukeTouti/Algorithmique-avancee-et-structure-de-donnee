#include <stdio.h>
#include <stdlib.h>
#include "coloration.h"

/* Vérifier si une couleur est disponible pour un sommet */
int estCouleurDisponible(Graphe* g, int sommet, int couleur, int* couleurs) {
	Noeud* temp = g->listeAdj[sommet];
	while (temp != NULL) {
		int voisin = temp->sommet;
		if (couleurs[voisin] == couleur) {
			return 0;
		}
		temp = temp->suivant;
	}
	return 1;
}

/* Algorithme de coloration glouton */
void colorationGraphe(Graphe* g) {
	printf("\n=== Coloration de Graphe (Algorithme Glouton) ===\n\n");
	
	int couleurs[MAX_SOMMETS];
	
	/* Initialisation */
	for (int i = 0; i < g->nbSommets; i++) {
		couleurs[i] = -1;
	}
	
	/* Attribuer la couleur 0 au premier sommet */
	couleurs[0] = 0;
	printf("Sommet 0: couleur 0\n");
	
	/* Attribuer des couleurs aux sommets restants */
	for (int i = 1; i < g->nbSommets; i++) {
		/* Trouver la plus petite couleur disponible */
		int couleur = 0;
		while (!estCouleurDisponible(g, i, couleur, couleurs)) {
			couleur++;
		}
		
		couleurs[i] = couleur;
		printf("Sommet %d: couleur %d\n", i, couleur);
	}
	
	/* Compter le nombre de couleurs utilisées */
	int nbCouleurs = 0;
	for (int i = 0; i < g->nbSommets; i++) {
		if (couleurs[i] + 1 > nbCouleurs) {
			nbCouleurs = couleurs[i] + 1;
		}
	}
	
	printf("\n=== Résultat ===\n");
	printf("Nombre chromatique (couleurs utilisées): %d\n", nbCouleurs);
	
	/* Afficher les ensembles de sommets par couleur */
	printf("\nSommets par couleur:\n");
	for (int c = 0; c < nbCouleurs; c++) {
		printf("  Couleur %d: ", c);
		for (int i = 0; i < g->nbSommets; i++) {
			if (couleurs[i] == c) {
				printf("%d ", i);
			}
		}
		printf("\n");
	}
	
	printf("\n");
}
