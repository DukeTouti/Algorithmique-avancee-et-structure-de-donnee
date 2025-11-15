#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tas_min_max.h"
#include "tas_utils.h"

/* Fonction pour générer un tableau aléatoire */
static void generer_tableau_aleatoire(int tab[], int n) {
	for (int i = 0 ; i < n ; i++) {
		tab[i] = rand() % 100000 ;
	}
}

int main() {
	srand(time(NULL)) ;
	
	printf("=== COMPARAISON FILES DE PRIORITES VS TABLEAUX ===\n\n") ;
	
	/* ============================================
	   TEST 1 : Exemple simple avec affichage
	   ============================================ */
	printf("--- TEST 1 : Demonstration sur petit tableau ---\n") ;
	int donnees[10] = {15, 23, 8, 42, 5, 31, 12, 67, 19, 3} ;
	
	printf("Donnees initiales : [");
	for (int i = 0 ; i < 10 ; i++) {
		if (i == 0) {
			printf("%d", donnees[i]);
		} else {
			printf(", %d", donnees[i]);
		}
	}
	printf("]\n\n");
	
	// Test FILE DE PRIORITE
	noeud tas = nouveauTas();
	
	for (int i = 0 ; i < 10 ; i++) {
		insererTasMax(tas, donnees[i]);
	}
	
	
	printf("Extraction ordre décroissant : ");
	while (tas->taille > 0) {
		int max = extraireMax(tas);
		printf("%d", max);
		if (tas->taille > 0) {
			printf(" ; ");
		}
	}
	printf("\n\n");
	free(tas->tab);
	free(tas);
	
	// Test Tri par Fusion
	int tableau[10];
	int taille_tab = 0;
	
	for (int i = 0 ; i < 10 ; i++) {
		tableau[taille_tab++] = donnees[i];
	}
	
	printf("Extraction ordre décroissant : ");
	while (taille_tab > 0) {
		int indice_max = 0;
		
		for (int i = 0 ; i < taille_tab ; i++) {
			if (tableau[i] > tableau[indice_max]) {
				indice_max = i;
			}
		}
		
		int max = tableau[indice_max];
		printf("%d", max);
		
		/* On supprime le max en le replaçant par le dernier élément du tableau et ensuite en décrémentant la taille du tableau */
		tableau[indice_max] = tableau[taille_tab - 1];
		taille_tab-- ;
		
		if (taille_tab > 0) {
			printf(" ; ");
		}
	}
	printf("\n\n");
	
	/* ============================================
	   TEST 2 : Comparaison de performance
	   ============================================ */
	printf("--- TEST 2 : Analyse de performance ---\n\n") ;
	
	FILE *f = fopen("resultats_comparaison_files.csv", "w") ;
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier") ;
		return 1 ;
	}
	
	fprintf(f, "Taille,Temps_Insertion_Tas,Temps_Extraction_Tas,Temps_Insertion_Tableau,Temps_Extraction_Tableau\n") ;
	
	int sizes[] = {1000, 5000, 10000, 20000, 50000, 100000, 200000} ;
	int nb_sizes = sizeof(sizes) / sizeof(sizes[0]) ;
		
	for (int i = 0 ; i < nb_sizes ; i++) {
		int n = sizes[i] ;
			
		int *donnees_test = malloc(n * sizeof(int)) ;
		if (donnees_test == NULL) {
			perror("Erreur d'allocation memoire") ;
			fclose(f) ;
			return 1 ;
		}
		
		generer_tableau_aleatoire(donnees_test, n) ;

			
		printf("Test avec n = %d elements :\n", n) ;
			
		/* TEST TAS */
		noeud tas_test = nouveauTas();
		
		// Insertion du TAS
		clock_t start_ins_tas = clock();
		for (int j = 0; j < n; j++) {
			insererTasMax(tas_test, donnees_test[j]);
		}
		clock_t end_ins_tas = clock();
		double temps_ins_tas = ((double)(end_ins_tas - start_ins_tas) / CLOCKS_PER_SEC) * 1000;
		
		// Extraction du TAS
		clock_t start_ext_tas = clock();
		while (tas_test->taille > 0) {
			extraireMax(tas_test);
		}
		clock_t end_ext_tas = clock();
		double temps_ext_tas = ((double)(end_ext_tas - start_ext_tas) / CLOCKS_PER_SEC) * 1000;
		
		free(tas_test->tab);
		free(tas_test);
			
		/* TEST TABLEAU */
		int *tableau_test = malloc(n * sizeof(int));
		if (tableau_test == NULL) {
			perror("Erreur d'allocation mémoire");
			free(donnees_test);
			fclose(f);
			return 1;
		}
		
		int taille_tableau = 0;
		
		// Insertion dans TABLEAU
		clock_t start_ins_tab = clock();
		for (int j = 0; j < n; j++) {
			tableau_test[taille_tableau++] = donnees_test[j];  // O(1)
		}
		clock_t end_ins_tab = clock();
		double temps_ins_tab = ((double)(end_ins_tab - start_ins_tab) / CLOCKS_PER_SEC) * 1000;
		
		// Extraction du TABLEAU
		clock_t start_ext_tab = clock();
		while (taille_tableau > 0) {
		
			int indice_max = 0;
			
			for (int k = 1; k < taille_tableau; k++) {
				if (tableau_test[k] > tableau_test[indice_max]) {
					indice_max = k;
				}
			}
			
			tableau_test[indice_max] = tableau_test[taille_tableau - 1];
			taille_tableau--;
		}
		clock_t end_ext_tab = clock();
		double temps_ext_tab = ((double)(end_ext_tab - start_ext_tab) / CLOCKS_PER_SEC) * 1000;
		
		free(tableau_test);
		free(donnees_test);

		printf("  TAS     : Insertion %.2f ms | Extraction %.2f ms\n", temps_ins_tas, temps_ext_tas);
		printf("  TABLEAU : Insertion %.2f ms | Extraction %.2f ms\n\n", temps_ins_tab, temps_ext_tab);

		fprintf(f, "%d,%.2f,%.2f,%.2f,%.2f\n", n, temps_ins_tas, temps_ext_tas, temps_ins_tab, temps_ext_tab);

	}
	
	fclose(f) ;
	
	printf("=== ANALYSE THEORIQUE ===\n") ;
	printf("Complexite Insertion FILE DE PRIORITE  : O(log n)\n") ;
	printf("Complexite Extraction FILE DE PRIORITE : O(log n)\n") ;
	printf("Complexite Insertion TABLEAU SIMPLE    : O(1)\n") ;
	printf("Complexite Extraction TABLEAU SIMPLE   : O(n)\n") ;
	
	printf("Les resultats ont ete sauvegardes dans 'resultats_comparaison_files.csv'\n") ;
	printf("Executez 'python3 generer_graphiques_files.py' pour visualiser les courbes.\n") ;
	
	return 0 ;
}
