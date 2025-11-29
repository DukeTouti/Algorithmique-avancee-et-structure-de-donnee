#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "graphe.h"
#include "prim.h"

/* Structure pour détecter les cycles (savoir si deux sommets sont déjà connectés) */
typedef struct DetecteurCycles {
	int* parent;   /* Parent de chaque sommet dans son ensemble */
	int* rang;     /* Profondeur de l'arbre pour optimiser les unions */
	int taille;    /* Nombre de sommets */
} DetecteurCycles;

/* Fonctions pour la détection de cycles */
DetecteurCycles* creerDetecteur(int taille);
int trouverRepresentant(DetecteurCycles* dc, int x);
void fusionnerEnsembles(DetecteurCycles* dc, int x, int y);
void libererDetecteur(DetecteurCycles* dc);

/* Algorithme de Kruskal */
ResultatMST* kruskal(Graphe* graphe);

#endif
