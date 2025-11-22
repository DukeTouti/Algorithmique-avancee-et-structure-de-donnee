#ifndef GRAPH_H
#define GRAPH_H

/* Structure d'un noeud dans la liste d'adjacence */
typedef struct Noeud {
	int sommet ;
	struct Noeud* suivant ;
} Noeud;

/* Structure du graphe */
typedef struct Graphe {
	int nombreSommets ;       /* Nombre de sommets */
	Noeud** listesAdjacence ; /* Tableau de listes d'adjacence */
	int* visite ;             /* Tableau pour marquer les sommets visités (utilisé par BFS/DFS) */
} Graphe;

/* Fonctions de base pour le graphe */
Noeud* creerNoeud(int sommet) ;
Graphe* creerGraphe(int nombreSommets) ;
void ajouterArrete(Graphe* graphe, int src, int dest) ;
void afficherGraphe(Graphe* graphe) ;
void libererGraphe(Graphe* graphe) ;

/* Fonction pour réinitialiser le tableau visite */
void reinitialiserVisite(Graphe* graphe) ;

#endif
