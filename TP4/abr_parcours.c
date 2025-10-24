#include <stdlib.h>
#include <stdio.h>

#include "types_abr.h"
#include "abr_parcours.h"
#include "abr_affichage.h"

static int max(int p, int q) {
	return (p > q) ? p : q;
}

/* Parcours */
void parcours_infixe(ab_t a) {
	if (a) {
		parcours_infixe(a->gauche);
		affiche_element(a->e);
		parcours_infixe(a->droit);
	}
}

void parcours_prefixe(ab_t a) {
	if (a) {
		affiche_element(a->e);
		parcours_prefixe(a->gauche);
		parcours_prefixe(a->droit);
	}
}

void parcours_postfixe(ab_t a) {
	if (a) {
		parcours_postfixe(a->gauche);
		parcours_postfixe(a->droit);
		affiche_element(a->e);
	}
}

/* Proprietes et mesures */
int cardinal(ab_t a) {
	if (!a) {
		return 0;
	}
	return 1 + cardinal(a->gauche) + cardinal(a->droit);
}

int hauteur(ab_t a) {
	if (!a) {
		return -1;
	}
	return 1 + max(hauteur(a->gauche), hauteur(a->droit));
}













