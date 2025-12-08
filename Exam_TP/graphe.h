#ifndef GRAPHE_H
#define GRAPHE_H

#define MAX_SOMMETS 100
#define INFINI 99999

/* Structure pour un noeud dans la liste d'adjacence */
typedef struct Noeud {
	int sommet;
	int poids;
	struct Noeud* suivant;
} Noeud;

/* Structure pour un arc (utilisé par Bellman-Ford, Kruskal) */
typedef struct Arc {
	int src;
	int dest;
	int poids;
} Arc;

/* Structure du graphe */
typedef struct Graphe {
	int nbSommets;
	int nbArcs;
	int oriente;						/* 1 = orienté, 0 = non orienté */
	Noeud** listeAdj;					/* Listes d'adjacence */
	int matrice[MAX_SOMMETS][MAX_SOMMETS];	                /* Matrice d'adjacence */
	Arc* arcs;						/* Tableau des arcs (pour certains algos) */
	int capaciteArcs;
} Graphe;

/* Fonctions de base */
Graphe* creerGraphe(int nbSommets, int oriente);
void ajouterArrete(Graphe* g, int src, int dest, int poids);
void afficherGraphe(Graphe* g);
void afficherMatrice(Graphe* g);
void libererGraphe(Graphe* g);

#endif
