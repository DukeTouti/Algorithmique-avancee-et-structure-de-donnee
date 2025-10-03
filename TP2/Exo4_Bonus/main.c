#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "chercher.h"

// Fonction de comparaison pour qsort
int comparer(const void *a, const void *b) {
	return (*(int*)a - *(int*)b);
}

void generer_tableau_trie(int tab[], int n) {
	// Génère des nombres aléatoires
	for (int i = 0; i < n; i++) {
		tab[i] = rand() % 1000000;
	}
	// Tri le tableau
	qsort(tab, n, sizeof(int), comparer);
}

void afficher_tableau(int tab[], int n) {
	printf("tab = {");
	for(int i = 0; i < n; i++) {
		if (i == 0) {
			printf("%d", tab[i]);
		} else {
			printf(", %d", tab[i]);
		}
	}
	printf("}\n");
}

int main() {
	srand(time(NULL));
    
	FILE *f = fopen("resultats_temps_encadre.csv", "w");
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier\n");
		return 1;
	}
    
	fprintf(f, "Taille, Temps_Lineaire, Temps_Recursif\n");
    
	printf("=== COMPARAISON DES ALGORITHMES DE RECHERCHE ENCADREE ===\n\n");
    
	// Tailles de test (puissances de 2 pour bien voir l'effet logarithmique)
	int size[] = {1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};
	int nb_size = sizeof(size) / sizeof(size[0]);
    
	for (int i = 0; i < nb_size; i++) {
		int n = size[i];
		int *tab = malloc(n * sizeof(int));
        
		if (tab == NULL) {
			perror("Erreur d'allocation memoire\n");
			return 1;
		}
        
		generer_tableau_trie(tab, n);
        
		printf("Test avec un tableau de taille = %d elements\n", n);
        
		if (n <= 20) {
			afficher_tableau(tab, n);
		}
        
		// Choisir des bornes : on prend une valeur au milieu du tableau
	        int a = tab[n/3];
		int b = tab[2*n/3];
        
		printf("Bornes de recherche : [%d, %d]\n", a, b);
        
		// Test avec méthode linéaire
		clock_t start_lin = clock();
		int resultat_lineaire = chercher_lineaire(tab, n, a, b);
		clock_t end_lin = clock();
        
		if (resultat_lineaire != -1) {
			printf("Valeur trouvee (lineaire) : tab[%d] = %d\n", resultat_lineaire, tab[resultat_lineaire]);
		} else {
			printf("Aucune valeur trouvee (lineaire)\n");
		}
        
		// Test avec méthode récursive (D&C)
		clock_t start_rec = clock();
		int resultat_recursif = chercher_recursif(tab, 0, n-1, a, b);
		clock_t end_rec = clock();
        
		if (resultat_recursif != -1) {
			printf("Valeur trouvee (recursive) : tab[%d] = %d\n", resultat_recursif, tab[resultat_recursif]);
		} else {
			printf("Aucune valeur trouvee (recursive)\n");
		}
        
		// Comparaison des temps
		double temps_lin = ((double)(end_lin - start_lin) / CLOCKS_PER_SEC) * 1000000;
		double temps_rec = ((double)(end_rec - start_rec) / CLOCKS_PER_SEC) * 1000000;
        
		printf("Temps lineaire : %.2f us\n", temps_lin);
		printf("Temps recursif (D&C) : %.2f us\n", temps_rec);
        
		// Vérification
		int valide_lin = (resultat_lineaire == -1) || (tab[resultat_lineaire] >= a && tab[resultat_lineaire] <= b);
		int valide_rec = (resultat_recursif == -1) || (tab[resultat_recursif] >= a && tab[resultat_recursif] <= b);
        
		if (valide_lin && valide_rec) {
			printf("Verification : Les deux algorithmes donnent des resultats valides\n\n");
		} else {
			printf("ERREUR : Resultats invalides !\n\n");
		}
        
		fprintf(f, "%d, %.2f, %.2f\n", n, temps_lin, temps_rec);
        
		free(tab);
	}
    
	fclose(f);
    
	printf("\n=== TESTS SPECIFIQUES ===\n");
    
	// Test 1 : Exemple du poly
	printf("\nTest 1 : Exemple du poly\n");
	int test1[] = {3, 7, 8, 43, 556};
	int res1 = chercher_recursif(test1, 0, 4, 40, 50);
	if (res1 != -1) {
		printf("Recherche dans [3, 7, 8, 43, 556] avec bornes [40, 50] : trouve a l'indice %d (valeur = %d)\n", res1, test1[res1]);
	} else {
		printf("Aucune valeur trouvee\n");
	}
    
	// Test 2 : Valeur non trouvée (toutes < a)
	printf("\nTest 2 : Valeur non trouvee (toutes < a)\n");
	int test2[] = {1, 2, 3, 4, 5};
	int res2 = chercher_recursif(test2, 0, 4, 10, 20);
	printf("Resultat : %d (attendu : -1)\n", res2);
    
	// Test 3 : Valeur non trouvée (toutes > b)
	printf("\nTest 3 : Valeur non trouvee (toutes > b)\n");
	int test3[] = {50, 60, 70, 80, 90};
	int res3 = chercher_recursif(test3, 0, 4, 10, 20);
	printf("Resultat : %d (attendu : -1)\n", res3);
    
	// Test 4 : Un seul élément dans l'intervalle
	printf("\nTest 4 : Un seul element dans l'intervalle\n");
	int test4[] = {15};
	int res4 = chercher_recursif(test4, 0, 0, 10, 20);
	if (res4 != -1) {
		printf("Trouve a l'indice %d (valeur = %d)\n", res4, test4[res4]);
	}
    
	printf("\n=== ANALYSE THEORIQUE ===\n");
	printf("Complexite lineaire : O(n)\n");
	printf("Complexite recursive (D&C) : O(log n)\n");
	printf("\nLes resultats ont ete sauvegardes dans 'resultats_temps_encadre.csv'\n");
	printf("Vous pouvez importer ce fichier dans Excel pour tracer les courbes.\n");
    
	return 0;
}
