#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tas_operations.h"

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

/* Fonction pour vérifier si un tas max est valide */
static int verifier_tas_max(noeud x) {
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
static int verifier_tas_min(noeud x) {
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
	
	printf("=== COMPARAISON DES METHODES DE CONSTRUCTION DE TAS ===\n\n") ;
	
	/* ============================================
	   TEST 1 : Exemple simple avec affichage
	   ============================================ */
	printf("--- TEST 1 : Demonstration sur petit tableau ---\n") ;
	int tas1[10] = {5, 8, 9, 10, 18, 56, 7, 11, 14, 45} ;
	
	noeud x = nouveauTas() ;
	x->tab = tas1 ;
	x->taille = 10 ;
	x->mem = 10 ;
	
	printf("Tas initial : ") ;
	affichernoeud(x) ;
	printf("\n") ;
	
	construireTasMax(x) ;
	printf("Tas Max (methode directe) : ") ;
	affichernoeud(x) ;
	int max_ok = verifier_tas_max(x) ;
	printf(" -> %s\n", max_ok ? "VALIDE" : "ERREUR") ;
	
	/* Test avec insertion */
	int tas2[10] = {5, 8, 9, 10, 18, 56, 7, 11, 14, 45} ;
	x->tab = tas2 ;
	
	printf("\nTas initial : ") ;
	affichernoeud(x) ;
	printf("\n") ;
	
	construireTasMaxInsertion(x) ;
	printf("Tas Max (methode insertion) : ") ;
	affichernoeud(x) ;
	int ins_ok = verifier_tas_max(x) ;
	printf(" -> %s\n\n", ins_ok ? "VALIDE" : "ERREUR") ;
	
	/* Test Tas Min pour montrer la complétude */
	int tas3[10] = {5, 8, 9, 10, 18, 56, 7, 11, 14, 45} ;
	x->tab = tas3 ;
	
	printf("Tas initial : ") ;
	affichernoeud(x) ;
	printf("\n") ;
	
	construireTasMin(x) ;
	printf("Tas Min (methode directe) : ") ;
	affichernoeud(x) ;
	int min_ok = verifier_tas_min(x) ;
	printf(" -> %s\n\n", min_ok ? "VALIDE" : "ERREUR") ;
	
	/* ============================================
	   TEST 2 : Comparaison de performance
	   ============================================ */
	printf("--- TEST 2 : Analyse de performance (Construction Tas Max) ---\n\n") ;
	
	FILE *f = fopen("resultats_tas.csv", "w") ;
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier") ;
		return 1 ;
	}
	
	fprintf(f, "Taille,Type,Temps_Direct,Temps_Insertion\n") ;
	
	int sizes[] = {1000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000} ;
	int nb_sizes = sizeof(sizes) / sizeof(sizes[0]) ;
	
	char* types[] = {"aleatoire", "croissant", "decroissant"} ;
	int nb_types = 3 ;
	
	for (int type_idx = 0 ; type_idx < nb_types ; type_idx++) {
		printf("\n=== Tests avec donnees %s ===\n", types[type_idx]) ;
		
		for (int i = 0 ; i < nb_sizes ; i++) {
			int n = sizes[i] ;
			
			int *tab = malloc(n * sizeof(int)) ;
			int *tab_copie = malloc(n * sizeof(int)) ;
			
			if (tab == NULL || tab_copie == NULL) {
				perror("Erreur d'allocation memoire") ;
				free(tab) ;
				free(tab_copie) ;
				fclose(f) ;
				return 1 ;
			}
			
			/* Générer le tableau selon le type */
			if (type_idx == 0) {
				generer_tableau_aleatoire(tab, n) ;
			} else if (type_idx == 1) {
				generer_tableau_croissant(tab, n) ;
			} else {
				generer_tableau_decroissant(tab, n) ;
			}
			
			printf("Test avec n = %d elements (%s)\n", n, types[type_idx]) ;
			
			/* Test Construction Directe (O(n)) */
			memcpy(tab_copie, tab, n * sizeof(int)) ;
			noeud tas_direct = nouveauTas() ;
			tas_direct->tab = tab_copie ;
			tas_direct->taille = n ;
			tas_direct->mem = n ;
			
			clock_t start_direct = clock() ;
			construireTasMax(tas_direct) ;
			clock_t end_direct = clock() ;
			
			int validation_direct = verifier_tas_max(tas_direct) ;
			printf("  Construction directe : %s\n", validation_direct ? "OK" : "ERREUR") ;
			
			/* Test Construction par Insertion (O(n log n)) */
			memcpy(tab_copie, tab, n * sizeof(int)) ;
			noeud tas_insertion = nouveauTas() ;
			tas_insertion->tab = tab_copie ;
			tas_insertion->taille = n ;
			tas_insertion->mem = n ;
			
			clock_t start_insertion = clock() ;
			construireTasMaxInsertion(tas_insertion) ;
			clock_t end_insertion = clock() ;
			
			int validation_insertion = verifier_tas_max(tas_insertion) ;
			printf("  Construction insertion : %s\n", validation_insertion ? "OK" : "ERREUR") ;
			
			/* Calcul des temps en microsecondes */
			double temps_direct = ((double)(end_direct - start_direct) / CLOCKS_PER_SEC) * 1000000 ;
			double temps_insertion = ((double)(end_insertion - start_insertion) / CLOCKS_PER_SEC) * 1000000 ;
			
			printf("  Temps Direct : %.2f µs\n", temps_direct) ;
			printf("  Temps Insertion : %.2f µs\n", temps_insertion) ;
			
			if (validation_direct && validation_insertion) {
				double ratio = temps_insertion / temps_direct ;
				printf("  Ratio : %.2fx\n", ratio) ;
			}
			printf("\n") ;
			
			
			fprintf(f, "%d,%s,%.2f,%.2f\n", n, types[type_idx], temps_direct, temps_insertion) ;
			
			/* Libération mémoire */
			free(tas_direct) ;
			free(tas_insertion) ;
			free(tab) ;
			free(tab_copie) ;
		}
	}
	
	fclose(f) ;
	free(x) ;
	
	printf("=== ANALYSE THEORIQUE ===\n") ;
	printf("Complexite construction directe : O(n)\n") ;
	printf("Complexite construction insertion : O(n log n)\n") ;
	printf("Complexite entasser : O(log n)\n\n") ;
	
	printf("Les resultats ont ete sauvegardes dans 'resultats_tas.csv'\n") ;
	printf("Executez 'python3 generer_graphiques_tas.py' pour visualiser les courbes.\n") ;
	
	return 0 ;
}
