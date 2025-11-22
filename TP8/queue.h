#ifndef QUEUE_H
#define QUEUE_H

#define TAILLE_MAX_QUEUE 10000

/* Structure de la file (FIFO) pour BFS */
typedef struct Queue {
	int items[TAILLE_MAX_QUEUE] ;
	int debut ;
	int fin ;
} Queue ;

/* Fonctions pour gérer la FIFO */
Queue* creerQueue();
int estVide(Queue* q);
void enfiler(Queue* q, int valeur);
int defiler(Queue* q);
void libererQueue(Queue* q);

#endif
