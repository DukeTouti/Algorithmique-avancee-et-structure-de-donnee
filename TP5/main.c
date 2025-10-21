#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tas_operations.h"

/* Fonction pour générer un tableau aléatoire */
void generer_tableau_aleatoire(int tab[], int n) {
	for (int i = 0 ; i < n ; i++) {
		tab[i] = rand() % 1000 ;
	}
}

/* Fonction pour vérifier si un tas max est valide */
int verifier_tas_max(noeud x) {
	for (int i = 0 ; i < x->taille ; i++) {
		int g = gauche(i) ;
		int d = droit(i) ;
		
		if (g < x->taille && x->tab[i] < x->tab[g]) {
			return 0 ;
		}
		if (d < x->taille && x->tab[i] < x->tab[d]) {
			return 0 ;
		}
	}
	return 1 ;
}

/* Fonction pour vérifier si un tas min est valide */
int verifier_tas_min(noeud x) {
	for (int i = 0 ; i < x->taille ; i++) {
		int g = gauche(i) ;
		int d = droit(i) ;
		
		if (g < x->taille && x->tab[i] > x->tab[g]) {
			return 0 ;
		}
		if (d < x->taille && x->tab[i] > x->tab[d]) {
			return 0 ;
		}
	}
	return 1 ;
}

int main() {
	srand(time(NULL)) ;
	
	printf("=== TESTS DES OPERATIONS SUR TAS BINAIRE ===\n\n") ;
	
	/* ============================================
	   TEST 1 : Exemple simple avec affichage
	   ============================================ */
	printf("--- TEST 1 : Construction de tas avec tableau fixe ---\n") ;
	int tas1[10] = {5, 8, 9, 10, 18, 56, 7, 11, 14, 45} ;
	
	noeud x = nouveauTas() ;
	x->tab = tas1 ;
	x->taille = 10 ;
	x->mem = 10 ;
	
	printf("Tas initial : ") ;
	affichernoeud(x) ;
	printf("\n") ;
	
	construireTasMax(x) ;
	printf("Tas Max : ") ;
	affichernoeud(x) ;
	int max_ok = verifier_tas_max(x) ;
	printf(" -> %s\n", max_ok ? "VALIDE" : "ERREUR") ;
	
	/* Réinitialiser le tableau */
	int tas2[10] = {5, 8, 9, 10, 18, 56, 7, 11, 14, 45} ;
	x->tab = tas2 ;
	
	printf("\nTas initial : ") ;
	affichernoeud(x) ;
	printf("\n") ;
	
	construireTasMin(x) ;
	printf("Tas Min : ") ;
	affichernoeud(x) ;
	int min_ok = verifier_tas_min(x) ;
	printf(" -> %s\n\n", min_ok ? "VALIDE" : "ERREUR") ;
	
	/* ============================================
	   TEST 2 : Tests de performance
	   ============================================ */
	printf("--- TEST 2 : Analyse de performance ---\n\n") ;
	
	FILE *f = fopen("resultats_tas.csv", "w") ;
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier") ;
		return 1 ;
	}
	
	fprintf(f, "Taille, Temps_TasMax, Temps_TasMin\n") ;
	
	int sizes[] = {100, 500, 1000, 5000, 10000, 50000, 100000, 500000} ;
	int nb_sizes = sizeof(sizes) / sizeof(sizes[0]) ;
	
	for (int i = 0 ; i < nb_sizes ; i++) {
		int n = sizes[i] ;
		
		int *tab = malloc(n * sizeof(int)) ;
		int *tab_copie = malloc(n * sizeof(int)) ;
		
		if (tab == NULL || tab_copie == NULL) {
			perror("Erreur d'allocation mémoire") ;
			free(tab) ;
			free(tab_copie) ;
			fclose(f) ;
			return 1 ;
		}
		
		generer_tableau_aleatoire(tab, n) ;
		
		printf("Test avec n = %d elements\n", n) ;
		
		/* Test Tas Max */
		memcpy(tab_copie, tab, n*sizeof(int)) ;
		noeud tas_max = nouveauTas() ;
		tas_max->tab = tab_copie ;
		tas_max->taille = n ;
		tas_max->mem = n ;
		
		clock_t start_max = clock() ;
		construireTasMax(tas_max) ;
		clock_t end_max = clock() ;
		
		int validation_max = verifier_tas_max(tas_max) ;
		printf("  Construction Tas Max : %s\n", validation_max ? "OK" : "ERREUR") ;
		
		/* Test Tas Min */
		memcpy(tab_copie, tab, n*sizeof(int)) ;
		noeud tas_min = nouveauTas() ;
		tas_min->tab = tab_copie ;
		tas_min->taille = n ;
		tas_min->mem = n ;
		
		clock_t start_min = clock() ;
		construireTasMin(tas_min) ;
		clock_t end_min = clock() ;
		
		int validation_min = verifier_tas_min(tas_min) ;
		printf("  Construction Tas Min : %s\n", validation_min ? "OK" : "ERREUR") ;
		
		/* Calcul des temps en microsecondes */
		double temps_max = ((double)(end_max - start_max) / CLOCKS_PER_SEC) * 1000000 ;
		double temps_min = ((double)(end_min - start_min) / CLOCKS_PER_SEC) * 1000000 ;
		
		printf("  Temps Tas Max : %.2f µs\n", temps_max) ;
		printf("  Temps Tas Min : %.2f µs\n\n", temps_min) ;
		
		fprintf(f, "%d, %.2f, %.2f\n", n, temps_max, temps_min) ;
		
		/* Libération mémoire */
		free(tas_max) ;
		free(tas_min) ;
		free(tab) ;
		free(tab_copie) ;
	}
	
	fclose(f) ;
	free(x) ;
	
	printf("=== ANALYSE THEORIQUE ===\n") ;
	printf("Complexite construction tas : O(n)\n") ;
	printf("Complexite entasser : O(log n)\n\n") ;
	
	printf("Les resultats ont ete sauvegardes dans 'resultats_tas.csv'\n") ;
	printf("Executez 'python3 generer_graphiques_tas.py' pour visualiser les courbes.\n") ;
	
	return 0 ;
}
