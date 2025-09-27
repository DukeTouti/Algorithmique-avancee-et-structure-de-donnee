#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "recherche_max_divise_pour_regner.h"
#include "recherche_max_incrementale.h"

void generer_tableau_aleatoire(int tab[], int n) {
	for (int i = 0 ; i < n ; i++) {
		tab[i] = rand() % 1000 ;
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


int main(){

	srand(time(NULL));
	
	FILE *f = fopen("resultats_temps.csv", "w");
	if (f == NULL) {
		perror("Erreur lors de l'ouverture du fichier\n");
		return 1;
	}
	
	fprintf(f, "Taille, Temps_Incremental, Temps_Diviser_pour_Regner\n");
	
	printf("=== COMPARAISON DES ALGORITHMES DE RECHERCHE DU MAXIMUM ===\n\n");
	
	int size[] = {50, 100, 500, 1000, 10000, 50000, 100000, 500000, 1000000};
	int nb_size = sizeof(size) / sizeof(size[0]);
	
	int i;
	
	for (i = 0 ; i < nb_size ; i++) {
		int n = size[i];
		int *tab = malloc(n * sizeof(int));
		
		if (tab == NULL) {
			perror("Erreur d'allocation memoire\n");
			return 1;
		}
		
		generer_tableau_aleatoire(tab, n);
		
		printf("Test avec un tableau de taille = %d éléments\n", n);
		
		if (n <= 20) {
			afficher_tableau(tab, n);
		}
		
		// ==============================
		// Test avec méthode incrémentale
		// ==============================
	
		clock_t start_inc = clock();
		int max_incrementale = recherche_max_incrementale(tab, n);
		clock_t end_inc = clock();
		printf("Le maximum par la methode incrementale est : %d \n",max_incrementale);

		// =====================================
		// Test avec méthode diviser pour régner
		// =====================================
		clock_t start_dpr = clock();
		int max_dpr = d_p_r(tab, 0, n-1);
		clock_t end_dpr = clock();
		printf("Le maximum par la methode diviser pour regner est : %d \n",max_dpr);
		
		// =====================
		// Comparaison des temps
		// =====================
		double temps_inc = ((double) (end_inc - start_inc) / CLOCKS_PER_SEC) * 1000000;
		double temps_dpr = ((double) (end_dpr - start_dpr) / CLOCKS_PER_SEC) * 1000000;
		
		printf("Maximum trouvé : %d\n", max_incrementale);
		printf("Temps incrémental : %.2f µs\n", temps_inc);
		printf("Temps diviser pour régner : %.2f µs\n", temps_dpr);
		
		if (max_incrementale == max_dpr) {
			printf("\nVerification : Les deux algorithmes donnent le meme resultat\n\n");
		} else {
			printf("\nERREUR : Resultats differents !\n\n");
		}
		
		fprintf(f, "%d, %.2f, %.2f\n", n, temps_inc, temps_dpr);

		free(tab);
	}

	fclose(f);
	
	printf("=== ANALYSE THÉORIQUE ===\n");
	printf("Complexité incrémentale: O(n)\n");
	printf("Complexité diviser pour régner: O(n)\n");
	
	printf("Les résultats ont été sauvegardés dans 'resultats_temps.csv'\n");
	printf("Vous pouvez importer ce fichier dans Excel pour tracer les courbes.\n");

	return 0;
}
