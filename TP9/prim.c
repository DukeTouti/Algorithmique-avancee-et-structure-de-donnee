#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "prim.h"

/* Trouver le sommet qui a le plus petit poids pour être ajouté au MST */
static int extraireMin(int* key, int* dansF, int nombreSommets) {
	int min = INT_MAX;
	int min_index = -1;
	
	/* Regarder tous les sommets */
	for (int v = 0; v < nombreSommets; v++) {
		/* Si le sommet n'est pas encore dans le MST et son poids est le plus petit */
		if (dansF[v] == 1 && key[v] < min) {
			min = key[v];
			min_index = v;
		}
	}
	
	return min_index;
}

/* Construire l'arbre couvrant minimum avec l'algorithme de Prim */
ResultatMST* prim(Graphe* graphe) {
	int nombreSommets = graphe->nombreSommets;
	
	/* Créer les tableaux dont on a besoin */
	int* parent = malloc(nombreSommets * sizeof(int));  /* Pour savoir qui est connecté à qui */
	int* key = malloc(nombreSommets * sizeof(int));     /* Le poids minimum pour connecter chaque sommet */
	int* dansF = malloc(nombreSommets * sizeof(int));   /* Savoir quels sommets ne sont pas encore dans le MST */
	
	if (parent == NULL || key == NULL || dansF == NULL) {
		perror("Erreur d'allocation mémoire");
		exit(EXIT_FAILURE);
	}
	
	/* Au début, tous les sommets ont un poids infini et aucun parent */
	for (int u = 0; u < nombreSommets; u++) {
		key[u] = INT_MAX;  /* Poids infini pour commencer */
		parent[u] = -1;     /* Pas encore de parent */
		dansF[u] = 1;       /* Tous les sommets sont disponibles */
	}
	
	/* On commence par le sommet 0, donc son poids est 0 */
	key[0] = 0;
	
	/* Répéter jusqu'à avoir traité tous les sommets */
	for (int count = 0; count < nombreSommets; count++) {
		/* Trouver le sommet avec le plus petit poids qui n'est pas encore dans le MST */
		int u = extraireMin(key, dansF, nombreSommets);
		
		/* Si on ne trouve rien, le graphe n'est pas connexe */
		if (u == -1) {
			break;
		}
		
		/* Marquer ce sommet comme ajouté au MST */
		dansF[u] = 0;
		
		/* Regarder tous les voisins de ce sommet */
		Noeud* temp = graphe->listesAdjacence[u];
		while (temp != NULL) {
			int v = temp->sommet;
			int w_uv = temp->poids;  /* Le poids de l'arête entre u et v */
			
			/* Si v n'est pas encore dans le MST et que cette arête est plus légère */
			if (dansF[v] == 1 && w_uv < key[v]) {
				/* Mettre à jour le parent et le poids de v */
				parent[v] = u;       /* v sera connecté à u */
				key[v] = w_uv;       /* Le nouveau poids pour v */
			}
			
			temp = temp->suivant;
		}
	}
	
	/* Préparer la structure pour stocker le résultat */
	ResultatMST* resultat = malloc(sizeof(ResultatMST));
	if (resultat == NULL) {
		perror("Erreur d'allocation mémoire pour le résultat MST");
		exit(EXIT_FAILURE);
	}
	
	/* Un arbre avec n sommets a n-1 arêtes */
	resultat->nombreAretes = nombreSommets - 1;
	resultat->aretes = malloc(resultat->nombreAretes * sizeof(AreteMST));
	if (resultat->aretes == NULL) {
		perror("Erreur d'allocation mémoire pour les arêtes MST");
		free(resultat);
		exit(EXIT_FAILURE);
	}
	resultat->poidsTotal = 0;
	
	/* Construire la liste des arêtes du MST */
	int index = 0;
	for (int v = 1; v < nombreSommets; v++) {  /* On commence à 1 car 0 est la racine */
		if (parent[v] != -1) {
			/* Ajouter l'arête entre le parent et le sommet */
			resultat->aretes[index].src = parent[v];
			resultat->aretes[index].dest = v;
			resultat->aretes[index].poids = key[v];
			/* Ajouter le poids au total */
			resultat->poidsTotal += key[v];
			index++;
		}
	}
	
	resultat->nombreAretes = index;
	
	/* Libérer la mémoire temporaire */
	free(parent);
	free(key);
	free(dansF);
	
	return resultat;
}

/* Afficher les arêtes du MST et le poids total */
void afficherMST(ResultatMST* mst) {
	printf("\n=== Arbre Couvrant Minimum (MST) ===\n");
	printf("Arc       Poids\n");
	printf("-------------------\n");
	
	/* Afficher chaque arête */
	for (int i = 0; i < mst->nombreAretes; i++) {
		printf("%d - %d    %d\n", mst->aretes[i].src, mst->aretes[i].dest, mst->aretes[i].poids);
	}
	
	printf("-------------------\n");
	printf("Poids total : %d\n\n", mst->poidsTotal);
}

/* Libérer la mémoire utilisée par le MST */
void libererMST(ResultatMST* mst) {
	if (mst != NULL) {
		free(mst->aretes);
		free(mst);
	}
}
