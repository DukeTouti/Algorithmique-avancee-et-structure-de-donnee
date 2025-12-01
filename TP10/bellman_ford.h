#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#define INFINITY 99

/* Structure pour les arêtes du graphe */
typedef struct {
	int u;  /* Le sommet de départ de l'arête */
	int v;  /* Le sommet d'extrémité de l'arête */
	int w;  /* Le poids de l'arête (u,v) */
} Arc;

/* Le graphe est composé d'arcs */
typedef struct {
	int S;        /* Le nombre total de Sommets dans le graphe */
	int A;        /* Le nombre total d'Arêtes dans le graphe */
	Arc *arc;     /* Le tableau d'arêtes */
} Graphe;

/* Structure pour stocker les résultats de Bellman-Ford */
typedef struct {
	int *distance;
	int *pred;
	int cyclenegatif;
} ResultatBellmanFord;

/* Prototypes des fonctions */
Graphe* creerGraphe(int nombreSommets, int nombreArcs);
void ajouterArc(Graphe *g, int index, int u, int v, int w);
void libererGraphe(Graphe *g);
void initialiserDistances(int distance[], int pred[], int tV, int source);
int relacherArcs(Graphe *g, int distance[], int pred[]);
int detecterCycleNegatif(Graphe *g, int distance[]);
ResultatBellmanFord* bellmanFord(Graphe *g, int source);
void libererResultat(ResultatBellmanFord *resultat);

#endif
