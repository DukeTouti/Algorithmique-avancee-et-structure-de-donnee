#ifndef TOPO_H
#define TOPO_H

#include "graphe.h"

/* Tri topologique */
void triTopologique(Graphe* g);
void dfsTopoRecursif(Graphe* g, int sommet, int* visite, int* pile, int* indicePile);

#endif
