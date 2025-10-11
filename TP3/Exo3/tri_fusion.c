#include <stdio.h>
#include <stdlib.h>
#include "tri_fusion.h"

/**
 * Copie une portion d'un tableau dans un nouveau tableau alloué
 */
int *copier_tableau(int tab[], int debut, int fin) {
	int size = fin - debut;
	int *res = malloc(size * sizeof(int));
	
	if (res == NULL) {
		perror("Erreur d'allocation mémoire");
		exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < size; i++) {
		res[i] = tab[debut + i];
	}
	
	return res;
}

/**
 * Fusionne deux tableaux triés en un seul tableau trié
 */
int *fusionner(int gauche[], int size_gauche, int droite[], int size_droite) {
	int size = size_droite + size_gauche;
	
	int *res = malloc(size * sizeof(int));
	if (res == NULL) {
		perror("Erreur d'allocation mémoire");
		exit(EXIT_FAILURE);
	}
	
	int i = 0; // indice du tableau gauche
	int j = 0; // indice du tableau droite
	int k = 0; // indice du tableau res
	
	// Fusion des deux tableaux
	while ((i < size_gauche) && (j < size_droite)) {
		if (gauche[i] <= droite[j]) {
			res[k] = gauche[i];
			i++;
		} else {
			res[k] = droite[j];
			j++;
		}
		k++;
	}
	
	// Copier les éléments restants de gauche
	while (i < size_gauche) {
		res[k] = gauche[i];
		i++;
		k++;
	}

	// Copier les éléments restants de droite
	while (j < size_droite) {
		res[k] = droite[j];
		j++;
		k++;
	}
	
	return res;
}

/**
 * Trie un tableau d'entiers par l'algorithme de tri fusion
 * Tout est fait dans cette fonction, récursion incluse
 * Complexité : O(n log n)
 * @param tab tableau d'entiers à trier
 * @param debut indice de début (inclus)
 * @param fin indice de fin (exclus)
 */
void tri_fusion(int tab[], int debut, int fin) {
	// Cas de base : tableau de taille 0 ou 1
	if (fin - debut <= 1) {
		return;
	}
	
	// Calculer le milieu du tableau tab
	int milieu = debut + (fin - debut) / 2;
	
	// Trier récursivement les deux moitiés
	tri_fusion(tab, debut, milieu);
	tri_fusion(tab, milieu, fin);
	
	// Copier les deux moitiés
	int size_gauche = milieu - debut;
	int size_droite = fin - milieu;
	
	int *gauche = copier_tableau(tab, debut, milieu);
	int *droite = copier_tableau(tab, milieu, fin);
	
	// Fusionner les deux moitiés triées
	int *resultat = fusionner(gauche, size_gauche, droite, size_droite);
	
	// Recopier le résultat dans le tableau original
	for (int i = 0; i < (fin - debut); i++) {
		tab[debut + i] = resultat[i];
	}
	
	// Libérer la mémoire
	free(gauche);
	free(droite);
	free(resultat);
}
