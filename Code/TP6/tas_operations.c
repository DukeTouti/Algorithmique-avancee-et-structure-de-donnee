#include <stdlib.h>
#include "tas_operations.h"

/* Fonction qui restaure la propriété de tas max à partir du noeud d'indice i */
void entasserMax(noeud x, int i) {
	int indice_fils_gauche = gauche(i) ;
	int indice_fils_droit = droit(i) ;
	int indice_max_tmp = i ;
	
	if ((indice_fils_gauche < x->taille) && (x->tab[indice_fils_gauche] > x->tab[indice_max_tmp])) {
		indice_max_tmp = indice_fils_gauche ;
	}
	
	if ((indice_fils_droit < x->taille) && (x->tab[indice_fils_droit] > x->tab[indice_max_tmp])) {
		indice_max_tmp = indice_fils_droit ;
	}
	
	if (indice_max_tmp != i) {
		echangenoeud(x, indice_max_tmp, i) ;
		entasserMax(x, indice_max_tmp) ;
	}
}

/* Fonction qui restaure la propriété de tas min à partir du noeud d'indice i */
void entasserMin(noeud x, int i) {
	int indice_fils_gauche = gauche(i) ;
	int indice_fils_droit = droit(i) ;
	int indice_min_tmp = i ;
	
	if ((indice_fils_gauche < x->taille) && (x->tab[indice_fils_gauche] < x->tab[indice_min_tmp])) {
		indice_min_tmp = indice_fils_gauche ;
	}
	
	if ((indice_fils_droit < x->taille) && (x->tab[indice_fils_droit] < x->tab[indice_min_tmp])) {
		indice_min_tmp = indice_fils_droit ;
	}
	
	if (indice_min_tmp != i) {
		echangenoeud(x, indice_min_tmp, i) ;
		entasserMin(x, indice_min_tmp) ;
	}
}

/* Fonction qui construit un tas max à partir du tas x */
void construireTasMax(noeud x) {
	int deb = (x->taille) / 2 - 1 ;
	
	for (int i = deb ; i >= 0 ; i--) {
		entasserMax(x, i) ;
	}
}

/* Fonction qui construit un tas min à partir du tas x */
void construireTasMin(noeud x) {
	int deb = (x->taille) / 2 - 1 ;
	
	for (int i = deb ; i >= 0 ; i--) {
		entasserMin(x, i) ;
	}
}

void construireTasMaxInsertion(noeud x) {

	for (int i = 1; i < x->taille; i++) {
    
		int j = i;
		while (j > 0 && x->tab[parent(j)] < x->tab[j]) {
			echangenoeud(x, j, parent(j));
			j = parent(j);
		}
	}
}

void construireTasMinInsertion(noeud x) {

	for (int i = 1 ; i < x->taille ; i++) {
    
		int j = i ;
		while ((j > 0) && (x->tab[parent(j)] > x->tab[j])) {
			echangenoeud(x, j, parent(j));
			j = parent(j);
		}
	}
}

void triTas(int *tab, int taille) {

	noeud x = malloc(sizeof(*x));
	
	x->tab = tab;
	x->taille = taille;
	x->mem = taille;
	
	construireTasMax(x);
	
	for (int i = taille - 1 ; i > 0 ; i--) {
		echangenoeud(x, 0, i);
		
		x->taille--;
		
		entasserMax(x, 0);
	}
	
	free(x);
}











