#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphe.h"
#include "queue.h"
#include "bfs.h"
#include "dfs.h"

/* Fonction pour générer un graphe aléatoire avec une densité donnée */
static Graphe* genererGrapheAleatoire(int nombreSommets, double densite) {
	Graphe* graphe = creerGraphe(nombreSommets);
	
	/* Calculer le nombre maximum d'arêtes possibles (graphe non orienté) */
	int maxArretes = (nombreSommets * (nombreSommets - 1)) / 2;
	int nombreArretes = (int)(maxArretes * densite);
	
	/* Ajouter des arêtes aléatoires */
	int arretesAjoutees = 0;
	while (arretesAjoutees < nombreArretes) {
		int src = rand() % nombreSommets;
		int dest = rand() % nombreSommets;
		
		/* Éviter les boucles (src == dest) */
		if (src != dest) {
			/* Vérifier si l'arête existe déjà */
			int existe = 0;
			Noeud* temp = graphe->listesAdjacence[src];
			while (temp != NULL) {
				if (temp->sommet == dest) {
					existe = 1;
					break;
				}
				temp = temp->suivant;
			}
			
			/* Ajouter l'arête si elle n'existe pas */
			if (!existe) {
				ajouterArrete(graphe, src, dest);
				arretesAjoutees++;
			}
		}
	}
	
	return graphe;
}

int main() {
	srand(time(NULL));
	
	printf("=== COMPARAISON BFS vs DFS ===\n\n");
	
	/* ============================================
	   TEST 1 : Exemple simple avec affichage
	   ============================================ */
	printf("--- TEST 1 : Démonstration sur petit graphe ---\n");
	
	Graphe* grapheDemo = creerGraphe(8);
	
	/* Créer le graphe de l'exemple (Figure 3.6) */
	/* s(0); r(1); v(2); w(3); t(4); u(5); x(6); y(7) */
	ajouterArrete(grapheDemo, 0, 1);
	ajouterArrete(grapheDemo, 0, 3);
	ajouterArrete(grapheDemo, 1, 2);
	ajouterArrete(grapheDemo, 3, 4);
	ajouterArrete(grapheDemo, 3, 6);
	ajouterArrete(grapheDemo, 4, 5);
	ajouterArrete(grapheDemo, 4, 6);
	ajouterArrete(grapheDemo, 5, 6);
	ajouterArrete(grapheDemo, 5, 7);
	ajouterArrete(grapheDemo, 6, 7);
	
	afficherGraphe(grapheDemo);
	
	/* BFS avec affichage */
	int* distances = malloc(grapheDemo->nombreSommets * sizeof(int));
	if (distances == NULL) {
		perror("Erreur d'allocation mémoire");
		return 1;
	}
	bfs(grapheDemo, 0, distances);
	afficherDistancesBFS(grapheDemo, 0, distances);
	free(distances);
	
	/* DFS avec affichage */
	int* tempsDecouverte = malloc(grapheDemo->nombreSommets * sizeof(int));
	int* tempsFin = malloc(grapheDemo->nombreSommets * sizeof(int));
	if (tempsDecouverte == NULL || tempsFin == NULL) {
		perror("Erreur d'allocation mémoire");
		return 1;
	}
	dfs(grapheDemo, 0, tempsDecouverte, tempsFin);
	afficherResultatsDFS(grapheDemo, 0, tempsDecouverte, tempsFin);
	free(tempsDecouverte);
	free(tempsFin);
	
	libererGraphe(grapheDemo);
	
	/* ============================================
	   TEST 2 : Comparaison de performance
	   ============================================ */
	printf("--- TEST 2 : Analyse de performance ---\n\n");
	
	FILE* f = fopen("resultats_comparaison_graphes.csv", "w");
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier");
		return 1;
	}
	
	fprintf(f, "Sommets,Densite,Type,Temps_BFS,Temps_DFS\n");
	
	/* Tailles de graphes à tester */
	int tailles[] = {50, 100, 200, 500, 1000, 2000};
	int nb_tailles = sizeof(tailles) / sizeof(tailles[0]);
	
	/* Densités à tester */
	double densites[] = {0.1, 0.3, 0.7};
	char* types[] = {"Sparse", "Medium", "Dense"};
	int nb_densites = sizeof(densites) / sizeof(densites[0]);
	
	for (int i = 0; i < nb_tailles; i++) {
		int n = tailles[i];
		
		printf("Test : %d sommets :\n", n);
		
		for (int j = 0; j < nb_densites; j++) {
			double densite = densites[j];
			char* type = types[j];
			
			printf("  densité %.1f%% (%s) :\n", densite * 100, type);
			
			/* Générer un graphe aléatoire */
			Graphe* grapheTest = genererGrapheAleatoire(n, densite);
			
			/* Allouer les tableaux de résultats */
			int* dist = malloc(n * sizeof(int));
			int* tDecouverte = malloc(n * sizeof(int));
			int* tFin = malloc(n * sizeof(int));
			
			if (dist == NULL || tDecouverte == NULL || tFin == NULL) {
				perror("Erreur d'allocation mémoire");
				return 1;
			}
			
			/* Mesure BFS */
			clock_t start_bfs = clock();
			bfs(grapheTest, 0, dist);
			clock_t end_bfs = clock();
			double temps_bfs = ((double)(end_bfs - start_bfs) / CLOCKS_PER_SEC) * 1000;
			
			/* Mesure DFS */
			clock_t start_dfs = clock();
			dfs(grapheTest, 0, tDecouverte, tFin);
			clock_t end_dfs = clock();
			double temps_dfs = ((double)(end_dfs - start_dfs) / CLOCKS_PER_SEC) * 1000;
			
			printf("     BFS : %.2f ms\n     DFS : %.2f ms\n\n", temps_bfs, temps_dfs);
			
			/* Sauvegarder dans le CSV */
			fprintf(f, "%d,%.1f,%s,%.2f,%.2f\n", n, densite, type, temps_bfs, temps_dfs);
			
			/* Libérer la mémoire */
			free(dist);
			free(tDecouverte);
			free(tFin);
			libererGraphe(grapheTest);
		}
	}
	
	fclose(f);
	
	printf("=== ANALYSE THÉORIQUE ===\n");
	printf("Complexité BFS : O(V + E)\n");
	printf("Complexité DFS : O(V + E)\n");
	printf("  V = nombre de sommets\n");
	printf("  E = nombre d'arêtes\n\n");
	
	printf("Les résultats ont été sauvegardés dans 'resultats_comparaison_graphes.csv'\n");
	printf("Exécutez 'python3 generer_graphiques_graphes.py' pour visualiser les courbes.\n");
	
	return 0;
}
