#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodage.h"

/* Charger la table des codes depuis un fichier */
int charger_table_codes(const char* fichier, TableCode* table) {
	FILE* f = fopen(fichier, "r");
	
	if (f == NULL) {
		perror("Erreur d'ouverture du fichier de codes");
		return -1;
	}
	
	int nb_codes;
	fscanf(f, "%d\n", &nb_codes);
	
	for (int i = 0; i < nb_codes; i++) {
		char ligne[300];
		if (fgets(ligne, sizeof(ligne), f) == NULL) {
			break;
		}
		
		/* Parser la ligne (on ignore la frequence maintenant) */
		int frequence;
		if (strncmp(ligne, "\\n ", 3) == 0) {
			sscanf(ligne + 3, "%s %d", table[i].code, &frequence);
			table[i].caractere = '\n';
		} else if (strncmp(ligne, "\\s ", 3) == 0) {
			sscanf(ligne + 3, "%s %d", table[i].code, &frequence);
			table[i].caractere = ' ';
		} else if (strncmp(ligne, "\\t ", 3) == 0) {
			sscanf(ligne + 3, "%s %d", table[i].code, &frequence);
			table[i].caractere = '\t';
		} else {
			sscanf(ligne, "%c %s %d", &table[i].caractere, table[i].code, &frequence);
		}
	}
	
	fclose(f);
	return nb_codes;
}

/* Construire l'arbre depuis les codes */
NoeudHuffman* construire_arbre_depuis_codes(TableCode* table, int nb_codes) {
	/* Creer la racine */
	NoeudHuffman* racine = malloc(sizeof(NoeudHuffman));
	racine->caractere = '\0';
	racine->frequence = 0;
	racine->gauche = NULL;
	racine->droit = NULL;
	racine->est_feuille = 0;
	
	/* Pour chaque code, inserer dans l'arbre */
	for (int i = 0; i < nb_codes; i++) {
		NoeudHuffman* courant = racine;
		char* code = table[i].code;
		int longueur = strlen(code);
		
		/* Parcourir le code bit par bit */
		for (int j = 0; j < longueur; j++) {
			if (code[j] == '0') {
				/* Aller a gauche */
				if (courant->gauche == NULL) {
					courant->gauche = malloc(sizeof(NoeudHuffman));
					courant->gauche->caractere = '\0';
					courant->gauche->frequence = 0;
					courant->gauche->gauche = NULL;
					courant->gauche->droit = NULL;
					courant->gauche->est_feuille = 0;
				}
				courant = courant->gauche;
			} else {
				/* Aller a droite */
				if (courant->droit == NULL) {
					courant->droit = malloc(sizeof(NoeudHuffman));
					courant->droit->caractere = '\0';
					courant->droit->frequence = 0;
					courant->droit->gauche = NULL;
					courant->droit->droit = NULL;
					courant->droit->est_feuille = 0;
				}
				courant = courant->droit;
			}
		}
		
		/* Arrivé a la feuille, mettre le caractere */
		courant->caractere = table[i].caractere;
		courant->est_feuille = 1;
	}
	
	return racine;
}

/* Decompresser un fichier */
int decompresser_fichier(const char* fichier_compresse, const char* fichier_sortie, NoeudHuffman* racine) {
	FILE* compresse = fopen(fichier_compresse, "r");
	FILE* sortie = fopen(fichier_sortie, "w");
	
	if (compresse == NULL || sortie == NULL) {
		perror("Erreur d'ouverture des fichiers");
		if (compresse) fclose(compresse);
		if (sortie) fclose(sortie);
		return -1;
	}
	
	NoeudHuffman* courant = racine;
	int c;
	
	/* Lire chaque bit du fichier compresse */
	while ((c = fgetc(compresse)) != EOF) {
		if (c == '0') {
			/* Aller a gauche */
			courant = courant->gauche;
		} else if (c == '1') {
			/* Aller a droite */
			courant = courant->droit;
		} else {
			/* Caractere invalide, ignorer */
			continue;
		}
		
		/* Si on atteint une feuille, ecrire le caractere */
		if (courant != NULL && courant->est_feuille) {
			fputc(courant->caractere, sortie);
			courant = racine;	/* Recommencer depuis la racine */
		}
	}
	
	fclose(compresse);
	fclose(sortie);
	
	printf("Decompression terminee!\n");
	return 0;
}
