#include <stdlib.h>
#include <stdio.h>
#include "tas_min_max.h"
#include "tas_operations.h"

#define MEM_INITIAL 256

static void augmenterCapacite(noeud x) {
	if (x->taille >= x->mem) {
		x->mem *= 2;
		x->tab = realloc(x->tab, x->mem * sizeof(int));
	}
}

/* Fonction qui augmente la clé (recursive) */
void augmenterCle(noeud x, int i) {
	if ((i > 0) && (x->tab[parent(i)] < x->tab[i])) {
		echangenoeud(x, i, parent(i));
		augmenterCle(x, parent(i));
	}
}

/* Fonction qui diminue la clé (recursive) */
void diminuerCle(noeud x, int i) {
	if ((i > 0) && (x->tab[parent(i)] > x->tab[i])) {
		echangenoeud(x, i, parent(i));
		diminuerCle(x, parent(i));
	}
}

/* Fonction qui augmente la clé (boucle) */
void augmenterCle2(noeud x, int i, int cle) {
	if (cle < x->tab[i]) {
		perror("Erreur : nouvelle clé plus petite que clé actuelle\n");
		return;
	}
	
	x->tab[i] = cle;

	while ((i > 0) && (x->tab[parent(i)] < x->tab[i])) {
		echangenoeud(x, i, parent(i));
		i = parent(i);
	}
}

/* Fonction qui diminue la clé (boucle) */
void diminuerCle2(noeud x, int i,int cle) {
	if (cle > x->tab[i]) {
		perror("Erreur : nouvelle clé plus grande que clé actuelle\n");
		return;
	}
	
	x->tab[i] = cle;

	while ((i > 0) && (x->tab[parent(i)] > x->tab[i])) {
		echangenoeud(x, i, parent(i));
		i = parent(i);
	}
}

/* Fonction qui ajoute un element e dans le tas max x */
void insererTasMax(noeud x, int e) {
	if (x == NULL) {
		fprintf(stderr, "Erreur : tas NULL\n");
		exit(EXIT_FAILURE);
	}
	
	if (x->tab == NULL) {
		x->tab = malloc(MEM_INITIAL * sizeof(int));
		if (x->tab == NULL) {
			perror("Erreur d'allocation mémoire");
			exit(EXIT_FAILURE);
		}
		x->mem = MEM_INITIAL;
		x->taille = 0;
	}
	
	augmenterCapacite(x);
	
	x->tab[x->taille] = e;
	
	int i = x->taille;
	while ((i > 0) && (x->tab[parent(i)] < x->tab[i])) {
		echangenoeud(x, i, parent(i));
		i = parent(i);
	}
	
	x->taille++;
}

/* Fonction qui ajoute un element e dans le tas min x */
void insererTasMin(noeud x, int e) {
	if (x == NULL) {
		fprintf(stderr, "Erreur : tas NULL\n");
		exit(EXIT_FAILURE);
	}
	
	if (x->tab == NULL) {
		x->tab = malloc(MEM_INITIAL * sizeof(int));
		if (x->tab == NULL) {
			perror("Erreur d'allocation mémoire");
			exit(EXIT_FAILURE);
		}
		x->mem = MEM_INITIAL;
		x->taille = 0;
	}
	
	augmenterCapacite(x);
	
	x->tab[x->taille] = e;
	
	int i = x->taille;
	while (i > 0 && x->tab[parent(i)] > x->tab[i]) {
		echangenoeud(x, i, parent(i));
		i = parent(i);
	}
	
	x->taille++;
}

/* Fonction qui extrait le maximum de l'arbre x */
int extraireMax(noeud x) {
	if (x == NULL || x->taille == 0) {
		perror("Erreur : tas vide ou NULL\n");
		exit(EXIT_FAILURE);
	}
	
	int max = x->tab[0];
	
	x->taille--;
	x->tab[0] = x->tab[x->taille];
	
	if (x->taille > 0) {
		entasserMax(x, 0);
	}
	
	return max;
}

/* Fonction qui extrait le minimum de l'arbre x */
int extraireMin(noeud x) {
	if (x == NULL || x->taille == 0) {
		perror("Erreur : tas vide ou NULL\n");
		exit(EXIT_FAILURE);
	}
	
	int min = x->tab[0];
	
	x->taille--;
	x->tab[0] = x->tab[x->taille];
	
	if (x->taille > 0) {
		entasserMin(x, 0);
	}
	
	return min;
}





