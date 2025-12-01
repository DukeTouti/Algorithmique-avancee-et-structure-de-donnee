#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define INFINITY 99
#define V 5

/* Structure pour stocker les résultats de Dijkstra */
typedef struct {
	int distance[V];
	int pred[V];
} ResultatDijkstra;

/* Prototypes des fonctions */
void dijkstra(int Graph[V][V], int n, int start, ResultatDijkstra *resultat);
void initialiserMatriceCout(int Graph[V][V], int cost[V][V], int n);
int trouverProchainNoeud(int distance[], int visited[], int n);
void relacherArcs(int Graph[V][V], int cost[V][V], int distance[], int pred[], int nextnode, int n);

#endif
