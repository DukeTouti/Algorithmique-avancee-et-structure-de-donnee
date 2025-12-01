#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#define V 5

/* Prototypes des fonctions d'affichage */
void afficherMatrice(int G[][V], int n);
void afficherDistances(int distance[], int n, int start);
void afficherResultatsFinaux(int distance[], int pred[], int n, int start);
void afficherChemin(int pred[], int start, int end);

#endif
