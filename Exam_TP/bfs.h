#ifndef BFS_H
#define BFS_H

#include "graphe.h"

/* Structure pour la file (FIFO) */
typedef struct Queue {
	int items[MAX_SOMMETS];
	int debut;
	int fin;
} Queue;

/* Fonctions de la queue */
Queue* creerQueue();
int estVide(Queue* q);
void enfiler(Queue* q, int valeur);
int defiler(Queue* q);
void libererQueue(Queue* q);

/* BFS */
void bfs(Graphe* g, int sommetDepart);

#endif
