#ifndef TAS_UTILS_H
#define TAS_UTILS_H

#include "types_tas.h"

/* Fonction pour créer un nouveau noeud */
noeud nouveauTas();

/* Fonction qui retourne l'indice du parent de l'element d'indice i */
int parent(int i);

/* Fonction qui retourne l'indice du fils gauche de l'element d'indice i */
int gauche(int i);

/* Fonction qui retourne l'indice du fils droit de l'element d'indice i */
int droit(int i);

/* Fonction qui retourne l'indice de la racine du tas x */
int racine(noeud x);

/* Fonction qui retourne l'indice du dernier element du tas x */
int dernier(noeud x);

/* Fonction qui retourne la taille du tas x */
int tailleTas(noeud x);

/* Fonction qui echange les elements dans les indices i et j du tas x entre eux */
void echangenoeud(noeud x, int i, int j);

/* Fonction qui affiche le tas x */
void affichernoeud(noeud x);

#endif
