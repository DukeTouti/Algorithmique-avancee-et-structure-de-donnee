#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tas_operations.h"
#include "tri_fusion.h"
#include "tri_insertion.h"

/* Fonction pour générer un tableau aléatoire */
static void generer_tableau_aleatoire(int tab[], int n) {
	for (int i = 0 ; i < n ; i++) {
		tab[i] = rand() % 100000 ;
	}
}

/* Fonction pour générer un tableau trié croissant */
static void generer_tableau_croissant(int tab[], int n) {
	for (int i = 0 ; i < n ; i++) {
		tab[i] = i ;
	}
}

/* Fonction pour générer un tableau trié décroissant */
static void generer_tableau_decroissant(int tab[], int n) {
	for (int i = 0 ; i < n ; i++) {
		tab[i] = n - i ;
	}
}

/* Fonction pour verifier si un tableau est triè ou pas */
static int verifier_tri(int tab[]) {
	int taille = sizeof(*tab) / sizeof(int);

	for (int i = 0 ; i < taille - 1 ; i++) {
		if (tab[i] > tab[i+1]) {
			return 0 ;
		}
	}
	return 1;	
}

int main() {
	srand(time(NULL)) ;
	
	printf("=== COMPARAISON DES METHODES DE TRI ===\n") ;
	printf("=== Tri par Insertion * Tri par Fusion * Tri par Tas ===\n\n") ;
	
	/* ============================================
	   TEST 1 : Exemple simple avec affichage
	   ============================================ */
	printf("--- TEST 1 : Demonstration sur petit tableau ---\n") ;
	int tas[10] = {5, 8, 9, 10, 18, 56, 7, 11, 14, 45} ;
	
	printf("Tableau initial : [");
	for (int i = 0 ; i < 10 ; i++) {
		if (i == 0) {
			printf("%d", tas[i]);
		} else {
			printf(", %d", tas[i]);
		}
	}
	printf("]\n\n");
	
	// Test Tri par Insertion
	int tas1[10];
	memcpy(tas1, tas, 10 * sizeof(int));
	tri_insertion(tas1, 10);
	printf("Tri par Insertion : [");
	for (int i = 0 ; i < 10 ; i++) {
		if (i == 0) {
			printf("%d", tas1[i]);
		} else {
			printf(", %d", tas1[i]);
		}
	}
	printf("] %s\n", verifier_tri(tas1) ? "OK" : "ERREUR");
	
	// Test Tri par Fusion
	int tas2[10];
	memcpy(tas2, tas, 10 * sizeof(int));
	tri_fusion(tas2, 0, 10);
	printf("Tri par Fusion    : [");
	for (int i = 0 ; i < 10 ; i++) {
		if (i == 0) {
			printf("%d", tas2[i]);
		} else {
			printf(", %d", tas2[i]);
		}
	}
	printf("] %s\n", verifier_tri(tas2) ? "OK" : "ERREUR");
	
	// Test Tri par Tas
	int tas3[10];
	memcpy(tas3, tas, 10 * sizeof(int));
	triTas(tas3, 10);
	printf("Tri par Tas       : [");
	for (int i = 0 ; i < 10 ; i++) {
		if (i == 0) {
			printf("%d", tas3[i]);
		} else {
			printf(", %d", tas3[i]);
		}
	}
	printf("] %s\n\n", verifier_tri(tas3) ? "OK" : "ERREUR");
	
	/* ============================================
	   TEST 2 : Comparaison de performance
	   ============================================ */
	printf("--- TEST 2 : Analyse de performance (Construction Tas Max) ---\n\n") ;
	
	FILE *f = fopen("resultats_comparaison_tri.csv", "w") ;
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier") ;
		return 1 ;
	}
	
	fprintf(f, "Taille,Type,Temps_Insertion,Temps_Fusion,Temps_Tas\n") ;
	
	int sizes[] = {1000, 5000, 10000, 20000, 50000, 100000, 200000} ;
	int nb_sizes = sizeof(sizes) / sizeof(sizes[0]) ;
	
	char* types[] = {"aleatoire", "croissant", "decroissant"} ;
	int nb_types = 3 ;
	
	for (int type_idx = 0 ; type_idx < nb_types ; type_idx++) {
		printf("\n=== Tests avec donnees %s ===\n", types[type_idx]) ;
		
		for (int i = 0 ; i < nb_sizes ; i++) {
			int n = sizes[i] ;
			
			int *tas = malloc(n * sizeof(int)) ;
			int *tas1 = malloc(n * sizeof(int)) ;
			int *tas2 = malloc(n * sizeof(int)) ;
			int *tas3 = malloc(n * sizeof(int)) ;
			
			if (tas == NULL || tas1 == NULL || tas2 == NULL || tas3 == NULL) {
				perror("Erreur d'allocation memoire") ;
				free(tas) ;
				free(tas1) ;
				free(tas2) ;
				free(tas3) ;
				fclose(f) ;
				return 1 ;
			}
			
			/* Générer le tableau selon le type */
			if (type_idx == 0) {
				generer_tableau_aleatoire(tas, n) ;
			} else if (type_idx == 1) {
				generer_tableau_croissant(tas, n) ;
			} else {
				generer_tableau_decroissant(tas, n) ;
			}
			
			printf("Test avec n = %d elements (%s)\n", n, types[type_idx]) ;
			
			/* Test Tri par Insertion */
			memcpy(tas1, tas, n * sizeof(int)) ;
			clock_t start1 = clock() ;
			tri_insertion(tas1, n) ;
			clock_t end1 = clock() ;
			double temps1 = ((double)(end1 - start1) / CLOCKS_PER_SEC) * 1000;
			
			int valid1 = verifier_tri(tas1) ;
			printf("  Tri par Insertion : %s\n", valid1 ? "OK" : "ERREUR") ;
			
			/* Test Tri par Fusion */
			memcpy(tas2, tas, n * sizeof(int));
			clock_t start2 = clock();
			tri_fusion(tas2, 0, n);
			clock_t end2 = clock();
			double temps2 = ((double)(end2 - start2) / CLOCKS_PER_SEC) * 1000;
			
			int valid2 = verifier_tri(tas2) ;
			printf("  Tri par Fusion    : %s\n", valid2 ? "OK" : "ERREUR") ;
			
			/* Test Tri par Tas */
			memcpy(tas3, tas, n * sizeof(int));
			clock_t start3 = clock();
			triTas(tas3, n);
			clock_t end3 = clock();
			double temps3 = ((double)(end3 - start3) / CLOCKS_PER_SEC) * 1000;
			
			int valid3 = verifier_tri(tas3) ;
			printf("  Tri par Tas       : %s\n", valid3 ? "OK" : "ERREUR") ;
			
			
			printf("  Temps Insertion   : %.2f µs\n", temps1) ;
			printf("  Temps Fusion      : %.2f µs\n", temps2) ;
			printf("  Temps Tas         : %.2f µs\n\n", temps3) ;
			
			
			
			fprintf(f, "%d,%s,%.2f,%.2f,%.2f\n", n, types[type_idx], temps1, temps2, temps3) ;
			
			/* Libération mémoire */
			free(tas) ;
			free(tas1) ;
			free(tas2) ;
			free(tas3) ;
		}
	}
	
	fclose(f) ;
	
	printf("=== ANALYSE THEORIQUE ===\n") ;
	printf("Complexite Tri Insertion : O(n²)\n") ;
	printf("Complexite Tri Fusion    : O(n log n)\n") ;
	printf("Complexite Tri par Tas   : O(n log n)\n\n") ;
	
	printf("Les resultats ont ete sauvegardes dans 'resultats_comparaison_tri.csv'\n") ;
	printf("Executez 'python3 generer_graphiques_tas.py' pour visualiser les courbes.\n") ;
	
	return 0 ;
}
