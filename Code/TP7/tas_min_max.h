#ifndef TAS_MIN_MAX_H
#define TAS_MIN_MAX_H

#include "types_tas.h"
#include "tas_utils.h"

/* Fonction qui augmente la clé (recursive) */
void augmenterCle(noeud x, int i);

/* Fonction qui diminue la clé (recursive) */
void diminuerCle(noeud x, int i);

/* Fonction qui augmente la clé (boucle) */
void augmenterCle2(noeud x, int i,int cle);

/* Fonction qui diminue la clé (boucle) */
void diminuerCle2(noeud x, int i,int cle);

/* Fonction qui ajoute un element e dans le tas max x */
void insererTasMax(noeud x, int e);

/* Fonction qui ajoute un element e dans le tas min x */
void insererTasMin(noeud x, int e);

/* Fonction qui extrait le maximum de l'arbre x */
int extraireMax(noeud x);

/* Fonction qui extrait le minimum de l'arbre x */
int extraireMin(noeud x);

#endif 
