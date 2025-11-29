#ifndef GRAPH_H
#define GRAPH_H

/* Structure pour représenter une arête pondérée (pour Kruskal) */
typedef struct Arete {
	int src ;
	int dest ;
	int poids ;
} Arete;


/* Structure d'un noeud dans la liste d'adjacence (pour Prim) */
typedef struct Noeud {
	int sommet ;              /* Sommet adjacent */
	int poids ;               /* Poids de l'arête */
	struct Noeud* suivant ;   /* Noeud suivant */
} Noeud;

/* Structure du graphe */
typedef struct Graphe {
	int nombreSommets ;       /* Nombre de sommets */
	int nombreAretes ;        /* Nombre d'arêtes */
	Noeud** listesAdjacence ; /* Tableau de listes d'adjacence (pour Prim) */
	Arete* aretes ;           /* Tableau de toutes les arêtes (pour Kruskal) */
	int capaciteAretes ;      /* Capacité du tableau aretes */
} Graphe;

/* Fonctions de base pour le graphe */
Graphe* creerGraphe(int nombreSommets) ;
void ajouterArete(Graphe* graphe, int src, int dest, int poids) ;
void afficherGraphe(Graphe* graphe) ;
void libererGraphe(Graphe* graphe) ;

/* Fonction pour réinitialiser le tableau visite */
Graphe* genererGrapheAleatoire(int nombreSommets, double densite, int poidsMin, int poidsMax);

#endif
