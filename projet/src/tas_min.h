#ifndef TAS_MIN_H
#define TAS_MIN_H

#include "types.h"

/* Creer un noeud Huffman */
NoeudHuffman* creer_noeud(char c, int freq, int est_feuille);

/* Creer un tas-min vide */
TasMin* creer_tas_min(int capacite);

/* Fonction qui retourne l'indice du parent de l'element d'indice i */
int parent(int i);

/* Fonction qui retourne l'indice du fils gauche de l'element d'indice i */
int gauche(int i);

/* Fonction qui retourne l'indice du fils droit de l'element d'indice i */
int droit(int i);

/* Echanger deux noeuds dans le tas */
void echanger(TasMin* tas, int i, int j);

/* Restaurer la propriete de tas-min a partir de l'indice i */
void entasser_min(TasMin* tas, int i);

/* Inserer un noeud dans le tas */
void inserer(TasMin* tas, NoeudHuffman* noeud);

/* Extraire le noeud de frequence minimale */
NoeudHuffman* extraire_min(TasMin* tas);

/* Construire un tas-min a partir d'un tableau de noeuds */
void construire_tas_min(TasMin* tas);

/* Verifier si le tas contient un seul element */
int est_singleton(TasMin* tas);

/* Afficher le tas (pour debug) */
void afficher_tas(TasMin* tas);

/* Liberer la memoire du tas */
void detruire_tas(TasMin* tas);

#endif
