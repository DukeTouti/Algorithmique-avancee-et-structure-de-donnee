#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "frequences.h"

#define TAILLE_ALPHABET 256

/* Lire un fichier et calculer les frequences de chaque caractere */
Frequence* calculer_frequences(const char* nom_fichier, int* nb_caracteres) {
	FILE* fichier = fopen(nom_fichier, "r");
	
	if (fichier == NULL) {
		perror("Erreur d'ouverture du fichier");
		return NULL;
	}
	
	/* Tableau temporaire pour compter les occurrences */
	int compteur[TAILLE_ALPHABET] = {0};
	int c;
	
	/* Compter chaque caractere */
	while ((c = fgetc(fichier)) != EOF) {
		compteur[c]++;
	}
	
	fclose(fichier);
	
	/* Compter combien de caracteres differents */
	int nb = 0;
	for (int i = 0; i < TAILLE_ALPHABET; i++) {
		if (compteur[i] > 0) {
			nb++;
		}
	}
	
	/* Allouer le tableau de frequences */
	Frequence* freq = malloc(nb * sizeof(Frequence));
	
	if (freq == NULL) {
		perror("Erreur d'allocation memoire pour les frequences");
		return NULL;
	}
	
	/* Remplir le tableau */
	int index = 0;
	for (int i = 0; i < TAILLE_ALPHABET; i++) {
		if (compteur[i] > 0) {
			freq[index].caractere = (char)i;
			freq[index].frequence = compteur[i];
			index++;
		}
	}
	
	*nb_caracteres = nb;
	return freq;
}

/* Afficher les frequences (pour debug) */
void afficher_frequences(Frequence* freq, int nb) {
	printf("\n=== Frequences des caracteres ===\n");
	
	for (int i = 0; i < nb; i++) {
		if (freq[i].caractere == '\n') {
			printf("'\\n' : %d\n", freq[i].frequence);
		} else if (freq[i].caractere == ' ') {
			printf("' '  : %d\n", freq[i].frequence);
		} else if (freq[i].caractere == '\t') {
			printf("'\\t' : %d\n", freq[i].frequence);
		} else {
			printf("'%c'  : %d\n", freq[i].caractere, freq[i].frequence);
		}
	}
	
	printf("\nNombre de caracteres differents: %d\n", nb);
}

/* Liberer la memoire des frequences */
void liberer_frequences(Frequence* freq) {
	if (freq != NULL) {
		free(freq);
	}
}
