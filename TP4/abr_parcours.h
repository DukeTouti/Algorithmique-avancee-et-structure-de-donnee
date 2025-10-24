#ifndef ABR_PARCOURS_H
#define ABR_PARCOURS_H

#include "types_abr.h"

/* Parcours */
void parcours_infixe(ab_t a);
void parcours_prefixe(ab_t a);
void parcours_postfixe(ab_t a);

/* Proprietes et mesures */
int cardinal(ab_t a);
int hauteur(ab_t a);

#endif
