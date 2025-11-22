#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/* Créer une nouvelle queue */
Queue* creerQueue() {
	Queue* q = malloc(sizeof(Queue));
	if (q == NULL) {
		perror("Erreur d'allocation mémoire pour la queue");
		exit(EXIT_FAILURE);
	}
	q->debut = -1;
	q->fin = -1;
	return q;
}

/* Vérifier si la queue est vide */
int estVide(Queue* q) {
	return (q->fin == -1);
}

/* Ajouter un élément dans la queue (enqueue) */
void enfiler(Queue* q, int valeur) {
	if (q->fin == TAILLE_MAX_QUEUE - 1) {
		perror("Erreur : Queue pleine !\n");
		exit(EXIT_FAILURE);
	}
	
	if (q->debut == -1) {
		q->debut = 0;
	}
	
	q->fin++;
	q->items[q->fin] = valeur;
}

/* Retirer un élément de la queue (dequeue) */
int defiler(Queue* q) {
	if (estVide(q)) {
		perror("Erreur : Queue vide !\n");
		exit(EXIT_FAILURE);
	}
	
	int item = q->items[q->debut];
	q->debut++;
	
	/* Réinitialiser la queue si elle devient vide */
	if (q->debut > q->fin) {
		q->debut = -1;
		q->fin = -1;
	}
	
	return item;
}

/* Libérer la mémoire de la queue */
void libererQueue(Queue* q) {
	if (q != NULL) {
		free(q);
	}
}
