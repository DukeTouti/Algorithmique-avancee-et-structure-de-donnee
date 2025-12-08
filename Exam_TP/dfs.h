#ifndef DFS_H
#define DFS_H

#include "graphe.h"

/* DFS */
void dfs(Graphe* g, int sommetDepart);
void dfsRecursif(Graphe* g, int sommet, int* visite, int* temps, int* decouverte, int* fin);

#endif
