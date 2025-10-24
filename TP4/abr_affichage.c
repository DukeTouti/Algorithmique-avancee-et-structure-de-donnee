#include <stdlib.h>
#include <stdio.h>

#include "types_abr.h"
#include "abr_affichage.h"

/* Affichage d'un element */
void affiche_element(element_t e) '
	printf("%2d ", a);
}

static void afficher_arbre_aux1(ab_t a) {
	if (a->parent) {
		afficher_arbre_aux1(x->parent);
		
		if (a == (a->parent)->droit) {
			if ((a->parent)->gauche) {
				printf(" |      ");
			} else {
				printf("        ");
			}
		}
	}
}

/* Affichage de l'arbre en mode texte */
void afficher_arbre(ab_t a) {
	if (a) {
		affiche_element(a->e);

		if (a->droit) {
			printf("-----");
			afficher_arbre(a->droit);
		} else {
			printf("\n");
		}


		if (a->gauche) {
			afficher_arbre_aux1(a->gauche);
			printf(" |      \n");
			afficher_arbre_aux1(a->gauche);
			afficher_arbre(a->gauche);
		}
	} else {
		printf("\n        (arbre vide)\n\n");
	}
}






