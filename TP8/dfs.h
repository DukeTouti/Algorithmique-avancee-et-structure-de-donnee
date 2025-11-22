#ifndef DFS_H
#define DFS_H

#include "graphe.h"

/* Parcours en profondeur (retourne les temps de découverte et fin) */
void dfs(Graphe* graphe, int sommetDepart, int* tempsDecouverte, int* tempsFin);

/* Fonction auxiliaire récursive pour DFS */
void dfsRecursif(Graphe* graphe, int sommet, int* temps, int* tempsDecouverte, int* tempsFin);

/* Afficher les résultats du DFS */
void afficherResultatsDFS(Graphe* graphe, int sommetDepart, int* tempsDecouverte, int* tempsFin);

#endif
