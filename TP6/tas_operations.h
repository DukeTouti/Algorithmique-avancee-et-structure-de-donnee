#ifndef TAS_OPERATIONS_H
#define TAS_OPERATIONS_H

#include "types_tas.h"
#include "tas_utils.h"

/* Fonction qui restaure la propriété de tas max à partir du noeud d'indice i */
void entasserMax(noeud x, int i);

/* Fonction qui restaure la propriété de tas min à partir du noeud d'indice i */
void entasserMin(noeud x, int i);

/* Fonction qui construit un tas max à partir du tas x */
void construireTasMax(noeud x);

/* Fonction qui construit un tas min à partir du tas x */
void construireTasMin(noeud x);

/* Fonction qui construit un tas max par insertion (élément par élément) */
void construireTasMaxInsertion(noeud x);

/* Fonction qui construit un tas min par insertion (élément par élément) */
void construireTasMinInsertion(noeud x);

/* Fonction qui tri récursivement un tas max (élément par élément) */
void triTas(int *tab,int taille);

#endif
