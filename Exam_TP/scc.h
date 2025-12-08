#ifndef SCC_H
#define SCC_H

#include "graphe.h"

/* Composantes fortement connexes */
void kosaraju(Graphe* g);
void dfsSCC1(Graphe* g, int sommet, int* visite, int* pile, int* indicePile);
void dfsSCC2(Graphe* gTranspose, int sommet, int* visite);
Graphe* transposerGraphe(Graphe* g);

#endif
