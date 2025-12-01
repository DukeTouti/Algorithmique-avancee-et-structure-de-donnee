#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#define V 5
#define INF 99

/* Structure pour stocker les résultats de Floyd-Warshall */
typedef struct {
	int matrix[V][V];
	int pred[V][V];
} ResultatFloydWarshall;

/* Prototypes des fonctions */
void initialiserMatrice(int graph[][V], int matrix[][V]);
void initialiserPredecesseurs(int pred[][V], int graph[][V]);
void floydWarshall(int graph[][V], ResultatFloydWarshall *resultat);
int detecterCycleNegatifFW(int matrix[][V]);

#endif
