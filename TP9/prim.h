#ifndef PRIM_H
#define PRIM_H

#include "graphe.h"

/* Structure pour stocker une arête du MST */
typedef struct AreteMST {
	int src;
	int dest;
	int poids;
} AreteMST;

/* Structure pour stocker le résultat du MST */
typedef struct ResultatMST {
	AreteMST* aretes;      /* Tableau des arêtes du MST */
	int nombreAretes;      /* Nombre d'arêtes dans le MST */
	int poidsTotal;        /* Poids total du MST */
} ResultatMST;

/* Algorithme de Prim */
ResultatMST* prim(Graphe* graphe);

/* Afficher le MST */
void afficherMST(ResultatMST* mst);

/* Libérer la mémoire du MST */
void libererMST(ResultatMST* mst);

#endif
