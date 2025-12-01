#ifndef AFFICHAGE_FW_H
#define AFFICHAGE_FW_H

#include "floyd_warshall.h"

/* Prototypes des fonctions d'affichage */
void afficherMatriceFW(int matrix[][V], int iteration);
void afficherCheminFW(int pred[][V], int i, int j);
void afficherTousLesChemins(int matrix[][V], int pred[][V]);
void afficherGrapheOriginal(int graph[][V]);

#endif
