#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "tri_insertion.h"
#include "tri_fusion.h"

void generer_tableau_aleatoire(int tab[], int n) {
	for (int i = 0 ; i < n ; i++) {
		tab[i] = rand() % 1000000;
	}
}

void afficher_tableau(int tab[], int n) {
	printf("tab = {");
	for(int i = 0 ; i < n ; i++) {
		if (i == 0) {
			printf("%d",tab[i]);
		} else {
			printf(", %d",tab[i]);
		}
	}
	printf("}\n");
}

int est_trie(int tab[], int n) {
	for (int i = 0; i < n - 1; i++) {
		if (tab[i] > tab[i + 1]) {
			return 0;
		}
	}
	return 1;
}

int main(){

	srand(time(NULL));
	
	FILE *f = fopen("resultats_tri.csv", "w");
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier\n");
		return 1;
	}
	
	fprintf(f, "Taille, Temps_Insertion, Temps_Fusion\n");
	
	printf("=== COMPARAISON DES ALGORITHMES DE TRI ===\n\n");
	
	int size[] = {5000, 10000, 20000, 50000, 100000, 500000, 1000000, 5000000, 1000000000};
	int nb_size = sizeof(size) / sizeof(size[0]);
	
	int i;
	
	for (i = 0 ; i < nb_size ; i++) {
		int n = size[i];
		int *tab = malloc(n * sizeof(int));
		int *tab_copie = malloc(n * sizeof(int));
		
		if (tab == NULL || tab_copie == NULL) {
			perror("Erreur d'allocation memoire\n");
			free(tab);
			free(tab_copie);
			return 1;
		}
		
		generer_tableau_aleatoire(tab, n);
		
		printf("Test avec un tableau de taille = %d elements\n", n);
		
		if (n <= 20) {
			afficher_tableau(tab, n);
		}
		
		// ==============================
		// Test avec tri par insertion
		// ==============================
		memcpy(tab_copie, tab, n * sizeof(int));
		clock_t start_ins = clock();
		tri_insertion(tab_copie, n);
		clock_t end_ins = clock();
		
		int insertion_ok = est_trie(tab_copie, n);
		printf("Tri par insertion : %s\n", insertion_ok ? "OK" : "ERREUR");
		
		// ==============================
		// Test avec tri par fusion
		// ==============================
		memcpy(tab_copie, tab, n * sizeof(int));
		clock_t start_fus = clock();
		tri_fusion(tab_copie, 0, n);
		clock_t end_fus = clock();
		
		int fusion_ok = est_trie(tab_copie, n);
		printf("Tri par fusion : %s\n", fusion_ok ? "OK" : "ERREUR");
		
		// =====================
		// Comparaison des temps
		// =====================
		double temps_ins = ((double) (end_ins - start_ins) / CLOCKS_PER_SEC) * 1000000;
		double temps_fus = ((double) (end_fus - start_fus) / CLOCKS_PER_SEC) * 1000000;
		
		printf("Temps insertion : %.2f µs\n", temps_ins);
		printf("Temps fusion : %.2f µs\n", temps_fus);
		
		if (insertion_ok && fusion_ok) {
			double ratio = temps_ins / temps_fus;
			printf("Ratio : %.2fx\n", ratio);
			printf("\nVerification : Les deux algorithmes ont trie correctement\n\n");
		} else {
			printf("\nERREUR : Un des algorithmes n'a pas trie correctement !\n\n");
		}
		
		fprintf(f, "%d, %.2f, %.2f\n", n, temps_ins, temps_fus);

		free(tab);
		free(tab_copie);
	}

	fclose(f);
	
	printf("=== ANALYSE THEORIQUE ===\n");
	printf("Complexite tri par insertion: O(n^2)\n");
	printf("Complexite tri par fusion: O(n log n)\n");
	
	printf("Les resultats ont ete sauvegardes dans 'resultats_temps.csv'\n");
	printf("Vous pouvez importer ce fichier dans Excel pour tracer les courbes.\n");

	return 0;
}
