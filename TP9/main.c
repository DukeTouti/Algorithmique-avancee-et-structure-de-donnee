#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graphe.h"
#include "prim.h"
#include "kruskal.h"

int main() {
	srand(time(NULL));
	
	printf("=== COMPARAISON PRIM vs KRUSKAL ===\n\n");
	
	/* ============================================
	   TEST 1 : Exemple simple avec affichage
	   ============================================ */
	printf("--- TEST 1 : Démonstration sur petit graphe ---\n");
	
	/* Créer le graphe de la Figure 3.24 du cours (9 sommets) */
	Graphe* grapheDemo = creerGraphe(9);
	
	ajouterArete(grapheDemo, 0, 1, 4);
	ajouterArete(grapheDemo, 0, 7, 8);
	ajouterArete(grapheDemo, 1, 2, 8);
	ajouterArete(grapheDemo, 1, 7, 11);
	ajouterArete(grapheDemo, 2, 3, 7);
	ajouterArete(grapheDemo, 2, 5, 4);
	ajouterArete(grapheDemo, 2, 8, 2);
	ajouterArete(grapheDemo, 3, 4, 9);
	ajouterArete(grapheDemo, 3, 5, 14);
	ajouterArete(grapheDemo, 4, 5, 10);
	ajouterArete(grapheDemo, 5, 6, 2);
	ajouterArete(grapheDemo, 6, 7, 1);
	ajouterArete(grapheDemo, 6, 8, 6);
	ajouterArete(grapheDemo, 7, 8, 7);
	
	afficherGraphe(grapheDemo);
	
	/* Algorithme de Prim */
	printf("\n--- Algorithme de PRIM ---\n");
	ResultatMST* mstPrim = prim(grapheDemo);
	afficherMST(mstPrim);
	
	/* Algorithme de Kruskal */
	printf("\n--- Algorithme de KRUSKAL ---\n");
	ResultatMST* mstKruskal = kruskal(grapheDemo);
	afficherMST(mstKruskal);
	
	libererMST(mstPrim);
	libererMST(mstKruskal);
	libererGraphe(grapheDemo);
	
	/* ============================================
	   TEST 2 : Comparaison de performance
	   ============================================ */
	printf("--- TEST 2 : Analyse de performance ---\n\n");
	
	FILE* f = fopen("resultats_comparaison_mst.csv", "w");
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier");
		return 1;
	}
	
	fprintf(f, "Sommets,Densite,Type,Temps_Prim,Temps_Kruskal\n");
	
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
			
			/* Générer un graphe aléatoire pondéré */
			Graphe* grapheTest = genererGrapheAleatoire(n, densite, 1, 100);
			
			/* Mesure Prim */
			clock_t start_prim = clock();
			ResultatMST* mst_prim = prim(grapheTest);
			clock_t end_prim = clock();
			double temps_prim = ((double)(end_prim - start_prim) / CLOCKS_PER_SEC) * 1000;
			
			/* Mesure Kruskal */
			clock_t start_kruskal = clock();
			ResultatMST* mst_kruskal = kruskal(grapheTest);
			clock_t end_kruskal = clock();
			double temps_kruskal = ((double)(end_kruskal - start_kruskal) / CLOCKS_PER_SEC) * 1000;
			
			printf("     Prim    : %.2f ms\n     Kruskal : %.2f ms\n\n", temps_prim, temps_kruskal);
			
			/* Sauvegarder dans le CSV */
			fprintf(f, "%d,%.1f,%s,%.2f,%.2f\n", n, densite, type, temps_prim, temps_kruskal);
			
			/* Libérer la mémoire */
			libererMST(mst_prim);
			libererMST(mst_kruskal);
			libererGraphe(grapheTest);
		}
	}
	
	fclose(f);
	
	printf("=== ANALYSE THÉORIQUE ===\n");
	printf("Complexité Prim    : O((V + E) log V) avec min-heap\n");
	printf("Complexité Kruskal : O(E log E)\n");
	printf("  V = nombre de sommets\n");
	printf("  E = nombre d'arêtes\n\n");
	
	printf("Les résultats ont été sauvegardés dans 'resultats_comparaison_mst.csv'\n");
	printf("Exécutez 'python3 generer_graphiques_mst.py' pour visualiser les courbes.\n");
	
	return 0;
}
