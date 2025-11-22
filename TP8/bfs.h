#ifndef BFS_H
#define BFS_H

#include "graphe.h"

/* Parcours en largeur (retourne les distances) */
void bfs(Graphe* graphe, int sommetDepart, int* distances);

/* Fonction pour afficher les distances depuis le sommet de départ */
void afficherDistancesBFS(Graphe* graphe, int sommetDepart, int* distances);

#endif
