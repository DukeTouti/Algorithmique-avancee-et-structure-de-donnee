#ifndef AFFICHAGE_BF_H
#define AFFICHAGE_BF_H

#include "bellman_ford.h"

/* Prototypes des fonctions d'affichage */
void afficherGraphe(Graphe *g);
void afficherDistancesBF(int distance[], int taille);
void afficherPredecesseurs(int pred[], int taille);
void afficherResultatsBF(int distance[], int pred[], int taille, int source);
void afficherCheminBF(int pred[], int source, int dest);

#endif
