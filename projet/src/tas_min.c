#include <stdio.h>
#include <stdlib.h>
#include "tas_min.h"

/* Creer un noeud Huffman */
NoeudHuffman* creer_noeud(char c, int freq, int est_feuille) {
	NoeudHuffman* noeud = malloc(sizeof(NoeudHuffman));
	
	if (noeud == NULL) {
		perror("Erreur d'allocation memoire pour le noeud");
		exit(1);
	}
	
	noeud->caractere = c;
	noeud->frequence = freq;
	noeud->gauche = NULL;
	noeud->droit = NULL;
	noeud->est_feuille = est_feuille;
	
	return noeud;
}

/* Creer un tas-min vide */
TasMin* creer_tas_min(int capacite) {
	TasMin* tas = malloc(sizeof(TasMin));
	
	if (tas == NULL) {
		perror("Erreur d'allocation memoire pour le tas");
		exit(1);
	}
	
	tas->noeuds = malloc(capacite * sizeof(NoeudHuffman*));
	
	if (tas->noeuds == NULL) {
		perror("Erreur d'allocation memoire pour le tableau de noeuds");
		exit(1);
	}
	
	tas->taille = 0;
	tas->capacite = capacite;
	
	return tas;
}

/* Fonction qui retourne l'indice du parent de l'element d'indice i */
int parent(int i) {
	return (i - 1) / 2;
}

/* Fonction qui retourne l'indice du fils gauche de l'element d'indice i */
int gauche(int i) {
	return 2 * i + 1;
}

/* Fonction qui retourne l'indice du fils droit de l'element d'indice i */
int droit(int i) {
	return 2 * i + 2;
}

/* Echanger deux noeuds dans le tas */
void echanger(TasMin* tas, int i, int j) {
	NoeudHuffman* temp = tas->noeuds[i];
	tas->noeuds[i] = tas->noeuds[j];
	tas->noeuds[j] = temp;
}

/* Restaurer la propriete de tas-min a partir de l'indice i */
void entasser_min(TasMin* tas, int i) {
	int g = gauche(i);
	int d = droit(i);
	int min = i;
	
	/* Comparer avec le fils gauche */
	if (g < tas->taille && tas->noeuds[g]->frequence < tas->noeuds[min]->frequence) {
		min = g;
	}
	
	/* Comparer avec le fils droit */
	if (d < tas->taille && tas->noeuds[d]->frequence < tas->noeuds[min]->frequence) {
		min = d;
	}
	
	/* Si le minimum n'est pas le noeud actuel, echanger et continuer */
	if (min != i) {
		echanger(tas, i, min);
		entasser_min(tas, min);
	}
}

/* Inserer un noeud dans le tas */
void inserer(TasMin* tas, NoeudHuffman* noeud) {
	if (tas->taille >= tas->capacite) {
		fprintf(stderr, "Erreur: tas plein\n");
		return;
	}
	
	/* Inserer a la fin */
	tas->taille++;
	int i = tas->taille - 1;
	tas->noeuds[i] = noeud;
	
	/* Remonter le noeud jusqu'a retrouver la propriete de tas-min */
	while (i > 0 && tas->noeuds[parent(i)]->frequence > tas->noeuds[i]->frequence) {
		echanger(tas, i, parent(i));
		i = parent(i);
	}
}

/* Extraire le noeud de frequence minimale */
NoeudHuffman* extraire_min(TasMin* tas) {
	if (tas->taille == 0) {
		fprintf(stderr, "Erreur: tas vide\n");
		return NULL;
	}
	
	/* Sauvegarder le minimum (racine) */
	NoeudHuffman* min = tas->noeuds[0];
	
	/* Remplacer la racine par le dernier element */
	tas->noeuds[0] = tas->noeuds[tas->taille - 1];
	tas->taille--;
	
	/* Restaurer la propriete de tas-min */
	if (tas->taille > 0) {
		entasser_min(tas, 0);
	}
	
	return min;
}

/* Construire un tas-min a partir d'un tableau de noeuds */
void construire_tas_min(TasMin* tas) {
	int debut = (tas->taille / 2) - 1;
	
	for (int i = debut; i >= 0; i--) {
		entasser_min(tas, i);
	}
}

/* Verifier si le tas contient un seul element */
int est_singleton(TasMin* tas) {
	return tas->taille == 1;
}

/* Afficher le tas (pour debug) */
void afficher_tas(TasMin* tas) {
	printf("Tas-Min (taille = %d): [", tas->taille);
	
	for (int i = 0; i < tas->taille; i++) {
		if (tas->noeuds[i]->est_feuille) {
			printf(" '%c' : %d", tas->noeuds[i]->caractere, tas->noeuds[i]->frequence);
		} else {
			printf(" *:%d", tas->noeuds[i]->frequence);
		}
		
		if (i < tas->taille - 1) {
			printf(",");
		}
	}
	
	printf(" ]\n");
}

/* Liberer la memoire du tas */
void detruire_tas(TasMin* tas) {
	if (tas != NULL) {
		if (tas->noeuds != NULL) {
			free(tas->noeuds);
		}
		free(tas);
	}
}
