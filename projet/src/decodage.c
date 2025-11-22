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
		
		/* Parser la ligne */
		if (strncmp(ligne, "\\n ", 3) == 0) {
			table[i].caractere = '\n';
			strcpy(table[i].code, ligne + 3);
		} else if (strncmp(ligne, "\\s ", 3) == 0) {
			table[i].caractere = ' ';
			strcpy(table[i].code, ligne + 3);
		} else if (strncmp(ligne, "\\t ", 3) == 0) {
			table[i].caractere = '\t';
			strcpy(table[i].code, ligne + 3);
		} else {
			table[i].caractere = ligne[0];
			strcpy(table[i].code, ligne + 2);
		}
		
		/* Enlever le \n a la fin du code */
		table[i].code[strcspn(table[i].code, "\n")] = '\0';
	}
	
	fclose(f);
	return nb_codes;
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
		if (courant->est_feuille) {
			fputc(courant->caractere, sortie);
			courant = racine;	/* Recommencer depuis la racine */
		}
	}
	
	fclose(compresse);
	fclose(sortie);
	
	printf("Decompression terminee!\n");
	return 0;
}
