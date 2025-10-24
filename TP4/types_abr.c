#include <stdlib.h>
#include <stdio.h>
#include "types_abr.h"

ab_t nouveau_noeud(element_t a) {
	ab_t abr;
	
	abr = (ab_t) malloc(sizeof(struct noeud_s));
	if (!abr) {
		perror("Erreur d'allocation memoire\n");
		exit(1);
	}
	
	abr->parent = NULL;
	abr->gauche = NULL;
	abr->droit = NULL;
	abr->e = a;
	
	return abr;
}

void vider(ab_t *pa) {
	ab_t abr;
	
	abr = *pa;
	if (abr) {
		vider(&(abr->gauche));
		vider(&(abr->droit));
		free(abr);
		*pa = NULL;
	}
}
