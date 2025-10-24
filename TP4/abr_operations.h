#ifndef ABR_OPERATIONS_H
#define ABR_OPERATIONS_H

#include "types_abr.h"

/*Comparaison entre deux éléments*/
int comparer(element_t e1, element_t e2);

/*Insere un element e dans l'arbre binaire pa*/
void inserer(ab_t *pa, element_t e);

/*Recherche l'element e dans l'arbre binaire a*/
ab_t rechercher(ab_t a, element_t e);

/*Supprime y de pa*/
void supprimer(ab_t *pa, ab_t y);

/*Les Extremums*/
ab_t maximum(ab_t a);
ab_t minimum(ab_t a);

/*Navigation*/
ab_t successeur(ab_t a);
ab_t predecesseur(ab_t a);

#endif
