#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "recherche_binaire_iterative.h"
#include "recherche_binaire_recursive.h"

#define REPETITIONS 10000

int comparer(const void *a, const void *b) {
	return (*(int*)a - *(int*)b);
}

void generer_tableau_aleatoire_trie(int tab[], int n) {
	for (int i = 0; i < n; i++) {
		tab[i] = rand() % 1000000;
	}
	
	qsort(tab, n, sizeof(int), comparer);
}

int main(){

	srand(time(NULL));
	
	FILE *f = fopen("resultats_recherche_binaire.csv", "w");
	if (f == NULL) {
		perror("Erreur lors d'ouverture du fichier\n");
		return 1;
	}
	
	fprintf(f, "Taille, Temps_Iteratif, Temps_Recursif\n");

	printf("=== ETUDE COMPARATIVE DES ALGORITHMES DE RECHERCHE BINAIRE ===\n\n");

	int size[] = {1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728};
	int nb_size = sizeof(size) / sizeof(size[0]);
	
	for (int i = 0 ; i < nb_size ; i++) {
		int n = size[i];
		int *tab = malloc(n * sizeof(int));
		
		if (tab == NULL) {
			perror("Erreur d'allocation memoire\n");
			return 1;
		}
		
		generer_tableau_aleatoire_trie(tab, n);
		printf("Test avec un tableau de taille = %d éléments\n", n);
       
	        int indice_alea = rand() % n;
	        int valeur_existante = tab[indice_alea];
		printf("Recherche de valeur existante: %d\n", valeur_existante);
        
		// ===========================
		// Test avec méthode itérative
		// ===========================
		int res_iteratif;
		clock_t start_iter = clock();
		for(int rep = 0; rep < REPETITIONS; rep++) {
			res_iteratif = recherche_binaire_iterative(tab, valeur_existante, n);
		}
		clock_t end_iter = clock();
		printf("Resultat iteratif : indice %d\n", res_iteratif);
        
		// ===========================
		// Test avec méthode récursive
		// ===========================
		int res_recursif;
		clock_t start_rec = clock();
		for(int rep = 0; rep < REPETITIONS; rep++) {
			res_recursif = recherche_binaire_recursive(tab, 0, n-1, valeur_existante);
		}
		clock_t end_rec = clock();
		printf("Resultat recursif : indice %d\n", res_recursif);
        
		// =====================
		// Comparaison des temps
		// =====================
		double temps_iter = ((double) (end_iter - start_iter) / CLOCKS_PER_SEC) * 1000000 / REPETITIONS;
		double temps_rec = ((double) (end_rec - start_rec) / CLOCKS_PER_SEC) * 1000000 / REPETITIONS;
        
		printf("Temps iteratif : %.2f µs\n", temps_iter);
		printf("Temps recursif : %.2f µs\n", temps_rec);
        
		// Vérification corrigée pour gérer les doublons
		if ((res_iteratif >= 0 && res_recursif >= 0 && 
		     tab[res_iteratif] == valeur_existante && 
		     tab[res_recursif] == valeur_existante) || 
		    (res_iteratif == -1 && res_recursif == -1)) {
			printf("Verification : Les deux algorithmes donnent le meme resultat\n");
		} else {
			printf("ERREUR : Resultats differents !\n");
			// Debug : afficher les valeurs trouvées
			printf("  Debug - Valeur iterative (indice %d): %d\n", res_iteratif, res_iteratif >= 0 ? tab[res_iteratif] : -1);
			printf("  Debug - Valeur recursive (indice %d): %d\n", res_recursif, res_recursif >= 0 ? tab[res_recursif] : -1);
		}
        
		// Test avec valeur inexistante
		printf("Test avec valeur inexistante (INT_MAX): ");
		int res_iter_inexist = recherche_binaire_iterative(tab, INT_MAX, n);
		int res_rec_inexist = recherche_binaire_recursive(tab, 0, n-1, INT_MAX);
        
		if (res_iter_inexist == -1 && res_rec_inexist == -1) {
			printf("Correctement détectée\n\n");
		} else {
			printf("ERREUR dans la détection\n");
			printf("  Debug - Iteratif: %d, Recursif: %d\n\n", res_iter_inexist, res_rec_inexist);
		}
        
		fprintf(f, "%d, %.2f, %.2f\n", n, temps_iter, temps_rec);
        
		free(tab);
	}
	fclose(f);
    
	printf("=== ANALYSE THÉORIQUE ===\n");
	printf("Complexité iterative: O(log n)\n");
	printf("Complexité recursive: O(log n)\n");
    
	printf("Les résultats ont été sauvegardés dans 'resultats_recherche_binaire.csv'\n");
	printf("Vous pouvez importer ce fichier dans Excel pour tracer les courbes.\n");
	
	return 0;
}
