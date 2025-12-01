#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dijkstra.h"
#include "bellman_ford.h"
#include "floyd_warshall.h"
#include "affichage.h"
#include "affichage_bf.h"
#include "affichage_fw.h"

/* Fonction pour générer un graphe aléatoire avec une densité donnée */
static Graphe* genererGrapheAleatoirePondere(int nombreSommets, double densite, int poidsMin, int poidsMax) {
	Graphe* graphe = creerGraphe(nombreSommets);
	
	/* Calculer le nombre maximum d'arêtes possibles (graphe orienté) */
	int maxArretes = nombreSommets * (nombreSommets - 1);
	int nombreArretes = (int)(maxArretes * densite);
	
	/* Ajouter des arêtes aléatoires avec poids aléatoires */
	int arretesAjoutees = 0;
	while (arretesAjoutees < nombreArretes) {
		int src = rand() % nombreSommets;
		int dest = rand() % nombreSommets;
		
		/* Éviter les boucles (src == dest) */
		if (src != dest) {
			/* Vérifier si l'arête existe déjà */
			int existe = 0;
			
			/* Ajouter l'arête avec un poids aléatoire */
			if (!existe) {
				int poids = poidsMin + (rand() % (poidsMax - poidsMin + 1));
				ajouterArete(graphe, src, dest, poids);
				arretesAjoutees++;
			}
		}
	}
	
	return graphe;
}

int main() {
	srand(time(NULL));
	
	printf("=== COMPARAISON DIJKSTRA vs BELLMAN-FORD vs FLOYD-WARSHALL ===\n\n");
	
	/* ============================================
	   TEST 1 : Exemple simple avec affichage
	   ============================================ */
	printf("--- TEST 1 : Démonstration sur petit graphe ---\n");
	
	/* Créer le graphe de démonstration (5 sommets) */
	Graphe* grapheDemo = creerGraphe(5);
	
	/* Ajouter les arêtes (graphe de la Figure 3.35 pour Floyd-Warshall) */
	ajouterArete(grapheDemo, 0, 1, 3);
	ajouterArete(grapheDemo, 0, 2, 8);
	ajouterArete(grapheDemo, 0, 4, -4);
	ajouterArete(grapheDemo, 1, 3, 1);
	ajouterArete(grapheDemo, 1, 4, 7);
	ajouterArete(grapheDemo, 2, 1, 4);
	ajouterArete(grapheDemo, 3, 0, 2);
	ajouterArete(grapheDemo, 3, 2, -5);
	ajouterArete(grapheDemo, 4, 3, 6);
	
	afficherGrapheDemo(grapheDemo);
	
	/* Dijkstra depuis chaque sommet */
	printf("\n--- Algorithme de DIJKSTRA (depuis chaque sommet) ---\n");
	for (int source = 0 ; source < grapheDemo->nombreSommets ; source++) {
		printf("\nSource: %d\n", source);
		ResultatDijkstra resultatDij;
		dijkstra(grapheDemo, grapheDemo->nombreSommets, source, &resultatDij);
		afficherDistancesBrief(resultatDij.distance, grapheDemo->nombreSommets, source);
	}
	
	/* Bellman-Ford depuis chaque sommet */
	printf("\n--- Algorithme de BELLMAN-FORD (depuis chaque sommet) ---\n");
	for (int source = 0 ; source < grapheDemo->nombreSommets ; source++) {
		printf("\nSource: %d\n", source);
		ResultatBellmanFord* resultatBF = bellmanFord(grapheDemo, source);
		afficherDistancesBrief(resultatBF->distance, grapheDemo->nombreSommets, source);
		libererResultat(resultatBF);
	}
	
	/* Floyd-Warshall */
	printf("\n--- Algorithme de FLOYD-WARSHALL ---\n");
	ResultatFloydWarshall resultatFW;
	floydWarshall(grapheDemo, &resultatFW);
	afficherMatriceFWBrief(resultatFW.matrix);
	
	libererGraphe(grapheDemo);
	
	/* ============================================
	   TEST 2 : Comparaison de performance
	   ============================================ */
	printf("\n--- TEST 2 : Analyse de performance ---\n\n");
	
	FILE* f = fopen("resultats_comparaison_chemins.csv", "w");
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier");
		return 1;
	}
	
	fprintf(f, "Sommets,Densite,Type,Temps_Dijkstra,Temps_BellmanFord,Temps_FloydWarshall\n");
	
	/* Tailles de graphes à tester */
	int tailles[] = {50, 100, 200, 500, 1000, 2000};
	int nb_tailles = sizeof(tailles) / sizeof(tailles[0]);
	
	/* Densités à tester */
	double densites[] = {0.1, 0.3, 0.7};
	char* types[] = {"Sparse", "Medium", "Dense"};
	int nb_densites = sizeof(densites) / sizeof(densites[0]);
	
	for (int i = 0 ; i < nb_tailles ; i++) {
		int n = tailles[i];
		
		printf("Test : %d sommets :\n", n);
		
		for (int j = 0 ; j < nb_densites ; j++) {
			double densite = densites[j];
			char* type = types[j];
			
			printf("  densité %.1f%% (%s) :\n", densite * 100, type);
			
			/* Générer un graphe aléatoire pondéré */
			Graphe* grapheTest = genererGrapheAleatoirePondere(n, densite, 1, 100);
			
			/* Mesure Dijkstra (depuis chaque sommet) */
			clock_t start_dijkstra = clock();
			for (int source = 0 ; source < n ; source++) {
				ResultatDijkstra resultatD;
				dijkstra(grapheTest, n, source, &resultatD);
			}
			clock_t end_dijkstra = clock();
			double temps_dijkstra = ((double)(end_dijkstra - start_dijkstra) / CLOCKS_PER_SEC) * 1000;
			
			/* Mesure Bellman-Ford (depuis chaque sommet) */
			clock_t start_bellman = clock();
			for (int source = 0 ; source < n ; source++) {
				ResultatBellmanFord* resultatB = bellmanFord(grapheTest, source);
				libererResultat(resultatB);
			}
			clock_t end_bellman = clock();
			double temps_bellman = ((double)(end_bellman - start_bellman) / CLOCKS_PER_SEC) * 1000;
			
			/* Mesure Floyd-Warshall (une seule fois) */
			clock_t start_floyd = clock();
			ResultatFloydWarshall resultatF;
			floydWarshall(grapheTest, &resultatF);
			clock_t end_floyd = clock();
			double temps_floyd = ((double)(end_floyd - start_floyd) / CLOCKS_PER_SEC) * 1000;
			
			printf("     Dijkstra     : %.2f ms\n", temps_dijkstra);
			printf("     Bellman-Ford : %.2f ms\n", temps_bellman);
			printf("     Floyd-Warsh. : %.2f ms\n\n", temps_floyd);
			
			/* Sauvegarder dans le CSV */
			fprintf(f, "%d,%.1f,%s,%.2f,%.2f,%.2f\n", 
				n, densite, type, temps_dijkstra, temps_bellman, temps_floyd);
			
			/* Libérer la mémoire */
			libererGraphe(grapheTest);
		}
	}
	
	fclose(f);
	
	printf("=== ANALYSE THÉORIQUE ===\n");
	printf("Complexité Dijkstra (tous sommets)   : O(V × (V + E) log V) avec min-heap\n");
	printf("                                       : O(V^3) avec implémentation simple\n");
	printf("Complexité Bellman-Ford (tous sommets): O(V^2 × E)\n");
	printf("Complexité Floyd-Warshall             : O(V^3)\n");
	printf("  V = nombre de sommets\n");
	printf("  E = nombre d'arêtes\n\n");
	
	printf("Les résultats ont été sauvegardés dans 'resultats_comparaison_chemins.csv'\n");
	printf("Exécutez 'python3 generer_graphiques_chemins.py' pour visualiser les courbes.\n");
	
	return 0;
}
