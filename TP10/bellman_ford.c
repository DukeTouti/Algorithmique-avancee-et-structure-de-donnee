#include "bellman_ford.h"
#include "affichage_bf.h"
#include <stdio.h>
#include <stdlib.h>

/* Créer un graphe */
Graphe* creerGraphe(int nombreSommets, int nombreArcs) {
	Graphe *g = (Graphe *)malloc(sizeof(Graphe));
	g->S = nombreSommets;
	g->A = nombreArcs;
	g->arc = (Arc *)malloc(g->A * sizeof(Arc));
	return g;
}

/* Ajouter un arc au graphe */
void ajouterArc(Graphe *g, int index, int u, int v, int w) {
	g->arc[index].u = u;
	g->arc[index].v = v;
	g->arc[index].w = w;
}

/* Libérer la mémoire du graphe */
void libererGraphe(Graphe *g) {
	free(g->arc);
	free(g);
}

/* Initialisation des distances et prédécesseurs */
void initialiserDistances(int distance[], int pred[], int tV, int source) {
	for (int i = 0; i < tV; i++) {
		distance[i] = INFINITY;
		pred[i] = -1;
	}
	distance[source] = 0;
}

/* Relâcher les arcs |V|-1 fois */
int relacherArcs(Graphe *g, int distance[], int pred[]) {
	int tV = g->S;
	int tE = g->A;
	int modifications = 0;
	
	for (int i = 1; i <= tV - 1; i++) {
		printf("\n=== Itération %d ===\n", i);
		int modif_iteration = 0;
		
		for (int j = 0; j < tE; j++) {
			int u = g->arc[j].u;
			int v = g->arc[j].v;
			int w = g->arc[j].w;
			
			/* Relâcher l'arc (u,v,w) */
			if (distance[u] != INFINITY && distance[v] > distance[u] + w) {
				printf("Relâchement arc (%d -> %d): ", u, v);
				printf("distance[%d] = %d -> %d\n", v, distance[v], distance[u] + w);
				distance[v] = distance[u] + w;
				pred[v] = u;
				modif_iteration++;
			}
		}
		
		if (modif_iteration == 0) {
			printf("Aucune modification, convergence atteinte!\n");
			break;
		}
		modifications += modif_iteration;
		afficherDistancesBF(distance, tV);
	}
	
	return modifications;
}

/* Détecter un cycle négatif */
int detecterCycleNegatif(Graphe *g, int distance[]) {
	int tE = g->A;
	
	printf("\n=== Détection de cycle négatif ===\n");
	for (int i = 0; i < tE; i++) {
		int u = g->arc[i].u;
		int v = g->arc[i].v;
		int w = g->arc[i].w;
		
		if (distance[u] != INFINITY && distance[v] > distance[u] + w) {
			printf("Cycle de poids négatif détecté sur l'arc (%d -> %d)!\n", u, v);
			return 1;
		}
	}
	printf("Aucun cycle de poids négatif détecté.\n");
	return 0;
}

/* Algorithme Bellman-Ford principal */
ResultatBellmanFord* bellmanFord(Graphe *g, int source) {
	int tV = g->S;
	
	/* Allocation du résultat */
	ResultatBellmanFord *resultat = (ResultatBellmanFord *)malloc(sizeof(ResultatBellmanFord));
	resultat->distance = (int *)malloc(tV * sizeof(int));
	resultat->pred = (int *)malloc(tV * sizeof(int));
	resultat->cyclenegatif = 0;
	
	printf("=== Phase 1: Initialisation ===\n");
	printf("Source: %d\n", source);
	initialiserDistances(resultat->distance, resultat->pred, tV, source);
	afficherDistancesBF(resultat->distance, tV);
	
	printf("\n=== Phase 2: Relâchement des arcs ===\n");
	relacherArcs(g, resultat->distance, resultat->pred);
	
	printf("\n=== Phase 3: Vérification ===\n");
	resultat->cyclenegatif = detecterCycleNegatif(g, resultat->distance);
	
	if (!resultat->cyclenegatif) {
		printf("\n=== Résultats finaux ===\n");
		afficherResultatsBF(resultat->distance, resultat->pred, tV, source);
	}
	
	return resultat;
}

/* Libérer le résultat */
void libererResultat(ResultatBellmanFord *resultat) {
	free(resultat->distance);
	free(resultat->pred);
	free(resultat);
}
