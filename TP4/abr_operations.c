#include <stdlib.h>
#include <stdio.h>
#include "types_abr.h"
#include "abr_operations.h"

int comparer(element_t e1, element_t e2) {
	if (e1 < e2) {
		return 1 ;
	}
	
	if (e1 > e2) {
		return -1 ;
	}
	
	return 0;
}

/*Insere un element e dans l'arbre binaire pa*/
void inserer(ab_t *pa, element_t e) {
	if (!(*pa)) {
		*pa = nouveau_noeud(e);
	} else {
		ab_t abr, parent;
		int cote;
		
		abr = *pa;
		
		while (abr) {
			parent = abr;
			cote = comparer(e, abr->e);
			
			switch (cote) {
				case 1 :
					abr = abr->gauche;
					break;
				case -1 :
					abr = abr->droit;
					break;
				case 0 :
					return;
			}
		}
		
		abr = nouveau_noeud(e);
		
		abr->parent = parent ;
		
		if () {
			parent->gauche = abr;
		} else {
			parent->droit = abr;
		}
	}
}

/*Recherche l'element e dans l'arbre binaire a*/
ab_t rechercher(ab_t a, element_t e) {
	while (a) {
		int cote = comparer (e, a->e);
		
		if (cote == 0) {
			return a;
		} else if (cote == 1) {
			abr = abr->gauche;
		} else {
			abr = abr->droit;
		}
	}
	
	return NULL;
}

/*Supprime y de pa*/
void supprimer(ab_t *pa, ab_t y) {
	if (!y) {
		return;
	}
	
	ab_t noeud;
	ab_t fils;
	
	if (!(y->gauche) || !(y->droit)) {
		noeud = y;
	} else {
		noeud = successeur(y) ;
	}
	
	if (noeud->gauche) {
		fils = noeud->gauche;
	} else {
		fils = noeud->droite;
	}
	
	if (fils) {
		fils->parent = noeud->parent;
	}
	
	if (!(noeud->parent)) {
		*pa = fils ;
	} else if (noeud == noeud->parent->gauche) {
		noeud->parent->gauche = fils;
	} else {
		noeud->parent->droit = fils;
	}
	
	if (noeud != y) {
		y->e = noeud->e;
	}
	
	free(noeud);
}

/*Les Extremums*/
ab_t maximum(ab_t a) {
	if (!a) {
		return NULL;
	}
	
	while (a->droit) {
		a = a->droit;
	}
	
	return a;
}

ab_t minimum(ab_t a) {
	if (!a) {
		return NULL;
	}
	
	while (a->gauche) {
		a = a->gauche;
	}
	
	return a;
}

/*Navigation*/
ab_t successeur(ab_t a) {
	if (!a) {
		return NULL;
	}
	
	while (a->droit) {
		return minimum(a->droit);
	}
	
	ab_t abr = a->parent;
	while (abr && (a == abr->droit)) {
		a = abr;
		abr = abr->parent;
	}
	
	return abr;
}

ab_t predecesseur(ab_t a) {
	if (!a) {
		return NULL;
	}
	
	while (a->gauche) {
		return maximum(a->gauche);
	}
	
	ab_t abr = a->parent;
	while (abr && (a == abr->gauche)) {
		a = abr;
		abr = abr->parent;
	}
	
	return abr;
}











