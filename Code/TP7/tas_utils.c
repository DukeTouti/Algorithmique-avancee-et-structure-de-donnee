#include <stdio.h>
#include <stdlib.h>

#include "tas_utils.h"

/* Fonction pour créer un nouveau noeud */
noeud nouveauTas() {
	noeud x ;
	x = malloc(sizeof(*x)) ;

	if (x == NULL) {
		perror("Erreur d'allocation mémoire") ;
	}
	
	x->tab = NULL ;
	x->taille = 0 ;
	x -> mem = 0 ;
	
	return x ;	
}

/* Fonction qui retourne l'indice du parent de l'element d'indice i */
int parent(int i) {
	return (i - 1) / 2 ;
}

/* Fonction qui retourne l'indice du fils gauche de l'element d'indice i */
int gauche(int i) {
	return 2*i + 1 ;
}

/* Fonction qui retourne l'indice du fils droit de l'element d'indice i */
int droit(int i) {
	return 2*i + 2 ;
}

/* Fonction qui retourne l'indice de la racine du tas x */
int racine(noeud x) {
	(void) x ;
	return 0 ;
}

/* Fonction qui retourne l'indice du dernier element du tas x */
int dernier(noeud x) {
	return x->taille - 1 ;
}

/* Fonction qui retourne la taille du tas x */
int tailleTas(noeud x) {
	return x->taille ;
}

/* Fonction qui echange les elements dans les indices i et j du tas x entre eux */
void echangenoeud(noeud x, int i, int j) {
	int e ;
	e = x->tab[i] ;
	x->tab[i] = x->tab[j] ;
	x->tab[j] = e ;
}

/* Fonction qui affiche le tas x */
void affichernoeud(noeud x) {
	printf("[ ") ;
	
	for (int i = 0 ; i < x->taille ; i++) {
		if (i == 0) {
			printf(" %d", x->tab[i]) ;
		} else {
			printf(", %d", x->tab[i]) ;
		}
	}
	printf(" ]") ;
}














