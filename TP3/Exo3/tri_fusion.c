#include <stdio.h>
#include <stdlib.h>
#include "tri_fusion.h"

/**
 * Recherche récursive d'une valeur encadrée dans un tableau trié
 * @param tab tableau d'entiers
 * @param debut indice de debut
 * @param fin indice de fin
 */
int *copier_tableau(int[] tab, int debut, int fin) {
	int size = fin - debut;
	int *res = malloc(size * sizeof(int));
	
	if (res == NULL) {
		perror("Erreur d'allocation mémoire");
		exit(EXIT_FAILURE);
	}
	
	for(int i = 0 ; i < size ; i++) {
		res[i] = tab[debut + i];
	}
	
	return res;
}

/**
 * Recherche récursive d'une valeur encadrée dans un tableau trié
 * @param gauche tableau d'entiers trié par ordre croissant
 * @param droite tableau d'entiers trié par ordre croissant
 */
int *fusionner(int[] gauche, int size_gauche, int[] droite, int size_droite) {
	int size = size_droite + size_gauche;
	
	int *res = malloc(size * sizeof(int));
	if (res == NULL) {
		perror("Erreur d'allocation mémoire");
		exit(EXIT_FAILURE);
	}
	
	int i = 0;
	int j = 0;
	int k = 0;
	
	while ((i < size_gauche) && (j < size_droite)) {
		if (gauche[i] < droite[j]) {
			res[k] = gauche[i];
			i++;
		} else {
			res[k] = droite[j];
			j++;
		}
		k++;
	}
	
	while (i < size_gauche) {
		res[k] = gauche[i];
		i++;
		k++;
	}

	while (j < size_droite) {
		res[k] = droite[j];
		j++;
		k++;
	}
	
	return res;
}

/**
 * Recherche linéaire naïve d'une valeur encadrée (pour comparaison)
 * @param tab tableau d'entiers
 * @param size taille du tableau tab
 */
int *tri_fusion(int[] tab, int size) {

	if (size <= 1) {
		return tab;
	}
	
	int milieu = size / 2;
	
	int *gauche = copier_tableau(tab, 0, milieu);
	int *droite = copier_tableau(tab, milieu, size);
	
	int size_gauche = sizeof(gauche) / sizeof(int);
	int size_droite = sizeof(droite) / sizeof(int);
	
	gauche = tri_fusion(gauche, size_gauche);
	droite = tri_fusion(droite, size_droite);
	
	int *res = fusionner(gauche, droite);
	
	free(gauche);
	free(droite);
	
	return res;
}


























