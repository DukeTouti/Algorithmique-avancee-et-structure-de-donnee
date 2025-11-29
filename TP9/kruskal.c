#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"

/* Créer un détecteur de cycles pour n sommets */
DetecteurCycles* creerDetecteur(int taille) {
	DetecteurCycles* dc = malloc(sizeof(DetecteurCycles));
	if (dc == NULL) {
		perror("Erreur d'allocation mémoire pour le détecteur");
		exit(EXIT_FAILURE);
	}
	
	dc->taille = taille;
	dc->parent = malloc(taille * sizeof(int));
	dc->rang = malloc(taille * sizeof(int));
	
	if (dc->parent == NULL || dc->rang == NULL) {
		perror("Erreur d'allocation mémoire");
		exit(EXIT_FAILURE);
	}
	
	/* Au début, chaque sommet forme son propre ensemble isolé */
	for (int i = 0; i < taille; i++) {
		dc->parent[i] = i;  /* Chaque sommet est son propre parent */
		dc->rang[i] = 0;    /* Tous les ensembles ont une profondeur de 0 */
	}
	
	return dc;
}

/* Trouver dans quel ensemble se trouve un sommet */
int trouverRepresentant(DetecteurCycles* dc, int x) {
	/* Remonter jusqu'à la racine de l'arbre */
	if (dc->parent[x] != x) {
		dc->parent[x] = trouverRepresentant(dc, dc->parent[x]);
	}
	return dc->parent[x];
}

/* Fusionner deux ensembles */
void fusionnerEnsembles(DetecteurCycles* dc, int x, int y) {
	/* Trouver les chefs de groupe de x et y */
	int racineX = trouverRepresentant(dc, x);
	int racineY = trouverRepresentant(dc, y);
	
	/* Si déjà dans le même groupe, rien à faire */
	if (racineX == racineY) {
		return;
	}
	
	/* Attacher le petit arbre sous le grand pour garder une faible profondeur */
	if (dc->rang[racineX] < dc->rang[racineY]) {
		dc->parent[racineX] = racineY;
	} else if (dc->rang[racineX] > dc->rang[racineY]) {
		dc->parent[racineY] = racineX;
	} else {
		/* Même profondeur : choisir arbitrairement et augmenter la profondeur */
		dc->parent[racineY] = racineX;
		dc->rang[racineX]++;
	}
}

/* Libérer la mémoire du détecteur */
void libererDetecteur(DetecteurCycles* dc) {
	if (dc != NULL) {
		free(dc->parent);
		free(dc->rang);
		free(dc);
	}
}

/* Comparer deux arêtes par leur poids (pour le tri) */
static int comparerAretes(const void* a, const void* b) {
	Arete* areteA = (Arete*)a;
	Arete* areteB = (Arete*)b;
	return areteA->poids - areteB->poids;
}

/* Construire l'arbre couvrant minimum avec l'algorithme de Kruskal */
ResultatMST* kruskal(Graphe* graphe) {
	/* Préparer la structure pour stocker le résultat */
	ResultatMST* resultat = malloc(sizeof(ResultatMST));
	if (resultat == NULL) {
		perror("Erreur d'allocation mémoire pour le résultat MST");
		exit(EXIT_FAILURE);
	}
	
	/* Un arbre avec n sommets a exactement n-1 arêtes */
	resultat->aretes = malloc((graphe->nombreSommets - 1) * sizeof(AreteMST));
	if (resultat->aretes == NULL) {
		perror("Erreur d'allocation mémoire pour les arêtes MST");
		free(resultat);
		exit(EXIT_FAILURE);
	}
	resultat->nombreAretes = 0;
	resultat->poidsTotal = 0;
	
	/* Créer le détecteur de cycles : chaque sommet commence dans son propre ensemble */
	DetecteurCycles* dc = creerDetecteur(graphe->nombreSommets);
	
	/* Trier toutes les arêtes par poids croissant (du plus léger au plus lourd) */
	qsort(graphe->aretes, graphe->nombreAretes, sizeof(Arete), comparerAretes);
	
	/* Parcourir les arêtes dans l'ordre croissant de poids */
	for (int i = 0; i < graphe->nombreAretes; i++) {
		int u = graphe->aretes[i].src;
		int v = graphe->aretes[i].dest;
		int poids = graphe->aretes[i].poids;
		
		/* Vérifier si u et v sont dans des ensembles différents */
		/* (Si oui, l'arête ne crée pas de cycle) */
		if (trouverRepresentant(dc, u) != trouverRepresentant(dc, v)) {
			/* Ajouter cette arête au MST */
			resultat->aretes[resultat->nombreAretes].src = u;
			resultat->aretes[resultat->nombreAretes].dest = v;
			resultat->aretes[resultat->nombreAretes].poids = poids;
			resultat->nombreAretes++;
			resultat->poidsTotal += poids;
			
			/* Fusionner les ensembles de u et v (ils sont maintenant connectés) */
			fusionnerEnsembles(dc, u, v);
		}
		
		/* Si on a déjà n-1 arêtes, le MST est complet */
		if (resultat->nombreAretes == graphe->nombreSommets - 1) {
			break;
		}
	}
	
	/* Libérer le détecteur de cycles */
	libererDetecteur(dc);
	
	/* Retourner le MST construit */
	return resultat;
}
