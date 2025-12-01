#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_V 2000
#define INF 99999

/* ==================== GÉNÉRATION DE GRAPHES ==================== */

static void genererGrapheAleatoirePondere(int graph[MAX_V][MAX_V], int n, double densite, int poidsMin, int poidsMax) {
	int i, j;
	
	// Initialiser à INF
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) {
				graph[i][j] = 0;
			} else {
				graph[i][j] = INF;
			}
		}
	}
	
	// Ajouter arêtes selon densité
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i != j) {
				double random = (double)rand() / RAND_MAX;
				if (random < densite) {
					graph[i][j] = poidsMin + rand() % (poidsMax - poidsMin + 1);
				}
			}
		}
	}
}

/* ==================== DIJKSTRA (SILENCIEUX) ==================== */

static int trouverMinDistance(int distance[], int visited[], int n) {
	int min = INF, minIndex = -1;
	int i;
	
	for (i = 0; i < n; i++) {
		if (!visited[i] && distance[i] < min) {
			min = distance[i];
			minIndex = i;
		}
	}
	
	return minIndex;
}

static void dijkstraSilencieux(int graph[MAX_V][MAX_V], int n, int start, int distance[]) {
	int visited[MAX_V] = {0};
	int i, j, u, count;
	
	// Initialisation
	for (i = 0; i < n; i++) {
		distance[i] = INF;
	}
	distance[start] = 0;
	
	// Algorithme principal
	for (count = 0; count < n - 1; count++) {
		u = trouverMinDistance(distance, visited, n);
		if (u == -1) break;
		
		visited[u] = 1;
		
		// Relaxation
		for (j = 0; j < n; j++) {
			if (!visited[j] && graph[u][j] != INF && 
			    distance[u] != INF && 
			    distance[u] + graph[u][j] < distance[j]) {
				distance[j] = distance[u] + graph[u][j];
			}
		}
	}
}

/* ==================== BELLMAN-FORD (SILENCIEUX) ==================== */

static void bellmanFordSilencieux(int graph[MAX_V][MAX_V], int n, int start, int distance[]) {
	int i, j, k;
	
	// Initialisation
	for (i = 0; i < n; i++) {
		distance[i] = INF;
	}
	distance[start] = 0;
	
	// Relaxation V-1 fois
	for (k = 0; k < n - 1; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (graph[i][j] != INF && distance[i] != INF) {
					if (distance[i] + graph[i][j] < distance[j]) {
						distance[j] = distance[i] + graph[i][j];
					}
				}
			}
		}
	}
}

/* ==================== FLOYD-WARSHALL (SILENCIEUX) ==================== */

static void floydWarshallSilencieux(int graph[MAX_V][MAX_V], int n, int result[MAX_V][MAX_V]) {
	int i, j, k;
	
	// Copier le graphe
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			result[i][j] = graph[i][j];
		}
	}
	
	// Algorithme Floyd-Warshall
	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (result[i][k] != INF && result[k][j] != INF) {
					if (result[i][k] + result[k][j] < result[i][j]) {
						result[i][j] = result[i][k] + result[k][j];
					}
				}
			}
		}
	}
}

/* ==================== MAIN ==================== */

int main() {
	static int graph[MAX_V][MAX_V];
	static int result[MAX_V][MAX_V];
	int distance[MAX_V];
	int tailles[] = {10, 20, 30, 50, 75, 100, 150, 200};
	double densites[] = {0.1, 0.3, 0.7};
	const char *types[] = {"Sparse", "Medium", "Dense"};
	int nbTailles = 8;
	int nbDensites = 3;
	int i, j, t, d;
	clock_t debut, fin;
	double tempsDijkstra, tempsBellman, tempsFloyd;
	FILE *fichier;
	
	srand(time(NULL));
	
	printf("=== COMPARAISON DIJKSTRA vs BELLMAN-FORD vs FLOYD-WARSHALL ===\n\n");
	
	/* ==================== TEST 1 : Démonstration ==================== */
	printf("--- TEST 1 : Démonstration sur petit graphe ---\n");
	
	// Graphe Figure 3.35 (5 sommets)
	int graphTest[5][5] = {
		{0, 3, 8, INF, -4},
		{INF, 0, INF, 1, 7},
		{INF, 4, 0, INF, INF},
		{2, INF, -5, 0, INF},
		{INF, INF, INF, 6, 0}
	};
	
	// Copier dans graph
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			graph[i][j] = graphTest[i][j];
		}
	}
	
	printf("Graphe de test (5 sommets):\n");
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (graph[i][j] == INF) {
				printf(" infini ");
			} else {
				printf("%3d ", graph[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
	
	// Dijkstra depuis sommet 0
	printf("Dijkstra (source 0): ");
	dijkstraSilencieux(graph, 5, 0, distance);
	for (i = 0; i < 5; i++) {
		if (distance[i] == INF) {
			printf("infini ");
		} else {
			printf("%d ", distance[i]);
		}
	}
	printf("\n");
	
	// Bellman-Ford depuis sommet 0
	printf("Bellman-Ford (source 0): ");
	bellmanFordSilencieux(graph, 5, 0, distance);
	for (i = 0; i < 5; i++) {
		if (distance[i] == INF) {
			printf("infini ");
		} else {
			printf("%d ", distance[i]);
		}
	}
	printf("\n");
	
	// Floyd-Warshall
	printf("Floyd-Warshall (toutes paires):\n");
	floydWarshallSilencieux(graph, 5, result);
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 5; j++) {
			if (result[i][j] == INF) {
				printf(" inifini ");
			} else {
				printf("%3d ", result[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
	
	/* ==================== TEST 2 : Performance ==================== */
	printf("--- TEST 2 : Analyse de performance ---\n\n");
	
	fichier = fopen("resultats_comparaison_chemins.csv", "w");
	if (fichier == NULL) {
		fprintf(stderr, "Erreur: impossible de créer le fichier CSV\n");
		return 1;
	}
	
	fprintf(fichier, "Sommets,Densite,Type,Temps_Dijkstra_us,Temps_BellmanFord_us,Temps_FloydWarshall_us\n");
	
	for (t = 0; t < nbTailles; t++) {
		int n = tailles[t];
		
		printf("Taille: %d sommets\n", n);
		
		for (d = 0; d < nbDensites; d++) {
			double densite = densites[d];
			const char *type = types[d];
			
			printf("  Densité: %.2f (%s)\n", densite, type);
			
			// Générer graphe
			genererGrapheAleatoirePondere(graph, n, densite, 1, 100);
			
			// Dijkstra (tous sommets)
			debut = clock();
			for (i = 0; i < n; i++) {
				dijkstraSilencieux(graph, n, i, distance);
			}
			fin = clock();
			tempsDijkstra = ((double)(fin - debut)) * 1000000.0 / CLOCKS_PER_SEC;
			
			// Bellman-Ford (tous sommets)
			debut = clock();
			for (i = 0; i < n; i++) {
				bellmanFordSilencieux(graph, n, i, distance);
			}
			fin = clock();
			tempsBellman = ((double)(fin - debut)) * 1000000.0 / CLOCKS_PER_SEC;
			
			// Floyd-Warshall (une seule fois)
			debut = clock();
			floydWarshallSilencieux(graph, n, result);
			fin = clock();
			tempsFloyd = ((double)(fin - debut)) * 1000000.0 / CLOCKS_PER_SEC;
			
			printf("    Temps Dijkstra      : %.2f µs\n", tempsDijkstra);
			printf("    Temps Bellman-Ford  : %.2f µs\n", tempsBellman);
			printf("    Temps Floyd-Warshall: %.2f µs\n", tempsFloyd);
			
			fprintf(fichier, "%d,%.2f,%s,%.2f,%.2f,%.2f\n", 
			        n, densite, type, tempsDijkstra, tempsBellman, tempsFloyd);
		}
		printf("\n");
	}
	
	fclose(fichier);
	
	printf("=== ANALYSE THÉORIQUE ===\n");
	printf("Complexité Dijkstra (tous sommets)   : O(V^3) avec implémentation simple\n");
	printf("                                       : O(V × (V + E) log V) avec min-heap\n");
	printf("Complexité Bellman-Ford (tous sommets): O(V^2 × E)\n");
	printf("Complexité Floyd-Warshall             : O(V^3)\n");
	printf("  V = nombre de sommets\n");
	printf("  E = nombre d'arêtes\n\n");
	
	printf("Les résultats ont été sauvegardés dans 'resultats_comparaison_chemins.csv'\n");
	printf("Exécutez 'python3 generer_graphiques.py' pour visualiser les courbes.\n");
	
	return 0;
}
